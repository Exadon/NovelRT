// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <memory>

using namespace NovelRT::Experimental::Windowing::Glfw;
using namespace NovelRT::Experimental::Windowing;
using namespace NovelRT::Experimental::Graphics::Vulkan;
using namespace NovelRT::Experimental::Graphics;

std::vector<uint8_t> LoadSpv(std::filesystem::path relativeTarget)
{
    std::filesystem::path finalPath = NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Shaders" / relativeTarget;
    std::ifstream file(finalPath.string(), std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw NovelRT::Exceptions::FileNotFoundException(finalPath.string());
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<uint8_t> buffer(fileSize);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    file.close();

    return buffer;
}

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    auto device = std::shared_ptr<IWindowingDevice>(new GlfwWindowingDevice());

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));
    auto gfxDevice = std::shared_ptr<ILLGraphicsDevice>(new VulkanGraphicsDevice());
    gfxDevice->Initialise(device);

    auto vertShaderData = LoadSpv("vert.spv");
    auto pixelShaderData = LoadSpv("frag.spv");

    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
    auto signature = gfxDevice->CreatePipelineSignature();
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);

    return 0;
}