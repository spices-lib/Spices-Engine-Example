//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: FrameReset00.cpp
// 
//-----------------------------------------------------------------------------

#include <vector>
#include <sstream>

#include <vulkan/vulkan.h>

#include "VulkanHelpers.h"
#include "VulkanReplay.h"
#include "Helpers.h"
#include "CommonReplay.h"
#include "Resources.h"
#include "Application.h"

NV_REPLAY_BEGIN_FRAME_SETUP()

//-----------------------------------------------------------------------------
// ResetInitialFrameState00
//-----------------------------------------------------------------------------
void ResetInitialFrameState00(bool firstTime, bool isAsync)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    NV_VK_REPLAY(VulkanHelper_ResetInstanceResourcesBegin(VkInstance_uid_1));

    // Reset VkImage_uid_15
    {
        BEGIN_DATA_SCOPE();

        static VkImageSubresource VkImageSubresource_temp_85 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_85 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_85 = VkExtent3D{
        /* width = */ 2200u,
        /* height = */ 1300u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateSwapchainImage(VkDevice_uid_4, 0u, VkImage_uid_15, VulkanHelper_PopulateImageFlags(0), VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VkImageSubresource_temp_85, VkOffset3D_temp_85, VkExtent3D_temp_85, 11440000ull, NV_GET_RESOURCE(const uint32_t*, 352)));
    }

    // Reset VkImage_uid_6887
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_80[1] = { VK_IMAGE_LAYOUT_GENERAL };
        static VkImageSubresource VkImageSubresource_temp_86 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_86 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_86 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6887, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_80, VkImageSubresource_temp_86, VkOffset3D_temp_86, VkExtent3D_temp_86, 23277632ull, NV_GET_RESOURCE(const uint32_t*, 353), nullptr));
    }

    // Reset VkImage_uid_6892
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_81[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_87 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_87 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_87 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_42[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6892, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_81, VkImageSubresource_temp_87, VkOffset3D_temp_87, VkExtent3D_temp_87, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 354), unionVkClearValue_temp_42));
    }

    // Reset VkImage_uid_6909
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_82[1] = { VK_IMAGE_LAYOUT_GENERAL };
        static VkImageSubresource VkImageSubresource_temp_88 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_88 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_88 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6909, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_82, VkImageSubresource_temp_88, VkOffset3D_temp_88, VkExtent3D_temp_88, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 355), nullptr));
    }

    // Reset VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_83[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_89 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_89 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_89 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_43[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_83, VkImageSubresource_temp_89, VkOffset3D_temp_89, VkExtent3D_temp_89, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 356), unionVkClearValue_temp_43));
    }

    // Reset VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_84[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_90 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 1u};
        static VkOffset3D VkOffset3D_temp_90 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_90 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_44[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_84, VkImageSubresource_temp_90, VkOffset3D_temp_90, VkExtent3D_temp_90, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 357), unionVkClearValue_temp_44));
    }

    // Reset VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_85[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_91 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 2u};
        static VkOffset3D VkOffset3D_temp_91 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_91 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_45[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_85, VkImageSubresource_temp_91, VkOffset3D_temp_91, VkExtent3D_temp_91, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 358), unionVkClearValue_temp_45));
    }

    // Reset VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_86[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_92 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 3u};
        static VkOffset3D VkOffset3D_temp_92 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_92 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_46[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_86, VkImageSubresource_temp_92, VkOffset3D_temp_92, VkExtent3D_temp_92, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 359), unionVkClearValue_temp_46));
    }

    // Reset VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_87[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_93 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 4u};
        static VkOffset3D VkOffset3D_temp_93 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_93 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_47[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_87, VkImageSubresource_temp_93, VkOffset3D_temp_93, VkExtent3D_temp_93, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 360), unionVkClearValue_temp_47));
    }

    // Reset VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_88[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_94 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 5u};
        static VkOffset3D VkOffset3D_temp_94 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_94 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_48[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_88, VkImageSubresource_temp_94, VkOffset3D_temp_94, VkExtent3D_temp_94, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 361), unionVkClearValue_temp_48));
    }

    // Reset VkImage_uid_6922
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_89[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_95 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_95 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_95 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_49[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6922, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_89, VkImageSubresource_temp_95, VkOffset3D_temp_95, VkExtent3D_temp_95, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 362), unionVkClearValue_temp_49));
    }

    // Reset VkImage_uid_6939
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_90[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_96 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_96 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_96 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_50[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6939, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_90, VkImageSubresource_temp_96, VkOffset3D_temp_96, VkExtent3D_temp_96, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 363), unionVkClearValue_temp_50));
    }

    NV_VK_REPLAY(VulkanHelper_ResetInstanceResourcesEnd(VkInstance_uid_1));
}

//-----------------------------------------------------------------------------
// ResetState00
//-----------------------------------------------------------------------------
void ResetState00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    NV_VK_REPLAY(VulkanHelper_ResetInstanceState(VkInstance_uid_1));
}

NV_REPLAY_END_FRAME_SETUP()
