// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSDEVICE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
    {
    private:
        std::shared_ptr<GraphicsAdapter> _adapter;
        std::shared_ptr<IGraphicsSurface> _surface;

    protected:
        [[nodiscard]] virtual GraphicsMemoryAllocator* GetMemoryAllocatorInternal() const noexcept = 0;

    public:
        GraphicsDevice(std::shared_ptr<GraphicsAdapter> adapter, std::shared_ptr<IGraphicsSurface> surface)
            : _adapter(std::move(adapter)), _surface(std::move(surface))
        {
            if (_adapter == nullptr)
            {
                throw Exceptions::NullPointerException("The supplied GraphicsAdapter is nullptr.");
            }

            if (surface == nullptr)
            {
                throw Exceptions::NullPointerException("The supplied IGraphicsSurface is nullptr.");
            }
        }

        virtual void TearDown() = 0;

        [[nodiscard]] inline std::shared_ptr<GraphicsAdapter> GetAdapter() const noexcept
        {
            return _adapter;
        }

        [[nodiscard]] virtual size_t GetContextIndex() const noexcept = 0;

        [[nodiscard]] virtual gsl::span<const std::shared_ptr<GraphicsContext>> GetContexts() const noexcept = 0;


        [[nodiscard]] inline std::shared_ptr<GraphicsContext> GetCurrentContext() const noexcept
        {
            return GetContexts()[GetContextIndex()];
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsMemoryAllocator> GetMemoryAllocator() const noexcept
        {
            return std::dynamic_pointer_cast<GraphicsMemoryAllocator>(GetMemoryAllocatorInternal()->shared_from_this());
        }

        [[nodiscard]] inline std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept
        {
            return _surface;
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipeline> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature> signature,
            std::shared_ptr<ShaderProgram> vertexShader,
            std::shared_ptr<ShaderProgram> pixelShader) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipelineSignature> CreatePipelineSignature(
            gsl::span<GraphicsPipelineInput> inputs,
            gsl::span<GraphicsPipelineResource> resources) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPrimitive> CreatePrimitive(
            std::shared_ptr<GraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource> indexBufferRegion,
            uint32_t indexBufferStride,
            gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions) = 0;

        [[nodiscard]] virtual std::shared_ptr<ShaderProgram> CreateShaderProgram(std::string entryPointName,
                                                                                 ShaderProgramKind kind,
                                                                                 gsl::span<uint8_t> byteData) = 0;

        virtual void PresentFrame() = 0;
        virtual void Signal(std::shared_ptr<GraphicsFence> fence) = 0;
        virtual void WaitForIdle() = 0;

        virtual ~GraphicsDevice() = default;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSDEVICE_H