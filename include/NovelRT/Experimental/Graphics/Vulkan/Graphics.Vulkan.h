// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H

/**
 * @brief The default Vulkan implementation for the Graphics plugin API.
 */
namespace NovelRT::Experimental::Graphics::Vulkan
{
    struct QueueFamilyIndices;
    struct SwapChainSupportDetails;
    class VulkanGraphicsDevice;
    class VulkanGraphicsPipeline;
    class VulkanShaderProgram;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;
    class VulkanGraphicsContext;
    class VulkanGraphicsFence;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;
    class VulkanGraphicsPrimitive;
    class VulkanGraphicsProvider;
    class VulkanGraphicsMemoryAllocator;
    class VulkanGraphicsMemoryBlockCollection;
    class VulkanGraphicsMemoryBlock;
    class VulkanGraphicsAdapter;
}

//Graphics.Vulkan dependencies
#include <array>
#include <bit>
#include <optional>
#include <set>
#include <map>
#include <vector>
#include <vulkan/vulkan.h>
#include "../Graphics.h"
#include "../../EngineConfig.h"
#include "../../../LoggingService.h"
#include "../../../Utilities/Lazy.h"
#include "../../../Exceptions/Exceptions.h"
#include "../../../Utilities/Misc.h"

// Graphics.Vulkan types

// clang-format off

#include "Utilities/Graphics.Vulkan.Utilities.h"
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "VulkanGraphicsAdapter.h"
#include "VulkanGraphicsFence.h"
#include "VulkanGraphicsDevice.h"
#include "VulkanGraphicsMemoryAllocator.h"
#include "VulkanGraphicsMemoryBlock.h"
#include "VulkanGraphicsMemoryBlockCollection.h"
#include "VulkanGraphicsContext.h"
#include "VulkanGraphicsBuffer.h"
#include "VulkanShaderProgram.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanGraphicsPipelineSignature.h"
#include "VulkanGraphicsPrimitive.h"
#include "VulkanGraphicsProvider.h"
#include "VulkanShaderProgram.h"
#include "VulkanGraphicsTexture.h"

// clang-format on

#endif // NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H