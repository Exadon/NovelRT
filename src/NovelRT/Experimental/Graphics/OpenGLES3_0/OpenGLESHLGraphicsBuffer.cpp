// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/NotSupportedException.h>
#include <NovelRT/Experimental/Graphics/OpenGLES3_0/OpenGLESHLGraphicsBuffer.h>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Experimental::Graphics::OpenGLES3_0
{
    GLbitfield OpenGLESHLGraphicsBuffer::ValidateAndTranslateAccessMode(
        GraphicsResourceCpuAccessKind accessMode) const
    {
        if ((GetEnabledAccessMode() & accessMode) != accessMode || accessMode == GraphicsResourceCpuAccessKind::None ||
            (accessMode & GraphicsResourceCpuAccessKind::None) == GraphicsResourceCpuAccessKind::None)
        {
            throw Exceptions::NotSupportedException(
                "This resource does not support the specified access mode for mapping.");
        }

        GLbitfield mode = GL_READ_ONLY;
        switch (accessMode)
        {
            case GraphicsResourceCpuAccessKind::None:
                throw std::runtime_error("It should be impossible to see this.");
                break;
            case GraphicsResourceCpuAccessKind::Read:
                mode = GL_READ_ONLY;
                break;
            case GraphicsResourceCpuAccessKind::Write:
                mode = GL_WRITE_ONLY;
                break;
            case GraphicsResourceCpuAccessKind::ReadWrite:
                mode = GL_READ_WRITE;
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "This resource does not support the specified access mode for mapping.");
        }
        return mode;
    }

    OpenGLESHLGraphicsBuffer::OpenGLESHLGraphicsBuffer(GraphicsResourceCpuAccessKind accessKind) noexcept
        : HLGraphicsBuffer(accessKind), _glMappedAccessMode(0), _bufferId(0)
    {
    }

    gsl::span<std::byte> OpenGLESHLGraphicsBuffer::MapUntyped(GraphicsResourceCpuAccessKind accessMode)
    {
        GLint output = 0;
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId); //TODO: this is such a hack. :(
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &output);
        return MapRangeUntyped(accessMode, 0, output);
    }

    gsl::span<std::byte> OpenGLESHLGraphicsBuffer::MapRangeUntyped(GraphicsResourceCpuAccessKind accessMode,
                                                                   size_t offset,
                                                                   size_t range)
    {
        GLbitfield mode = ValidateAndTranslateAccessMode(accessMode);

        _glMappedAccessMode = accessMode == GraphicsResourceCpuAccessKind::Read ? GL_COPY_READ_BUFFER : GL_COPY_WRITE_BUFFER;

        glBindBuffer(_glMappedAccessMode, _bufferId);

        return gsl::span<std::byte>(static_cast<std::byte*>(glMapBufferRange(_glMappedAccessMode, offset, range, mode)),
                                    sizeof(std::byte) * range);
    }

    std::shared_ptr<LLGraphicsResource> OpenGLESHLGraphicsBuffer::GetLLResourceUntyped() const
    {
        throw Exceptions::NotSupportedException();
    }

    void OpenGLESHLGraphicsBuffer::Unmap()
    {
        glUnmapBuffer(_glMappedAccessMode);
        glBindBuffer(_glMappedAccessMode, 0);
    }
} // namespace NovelRT::Experimental::Graphics::OpenGLES3_0