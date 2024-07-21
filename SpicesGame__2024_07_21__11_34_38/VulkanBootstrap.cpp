//---------------------------------------------------------------------------
// File: Resources\VulkanBootstrap.cpp
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#if defined(NV_VULKAN_SC_SUPPORT)
#include <vulkan/vulkan_sc_core.hpp>

#ifdef VK_USE_PLATFORM_SCI
#include <nvscibuf.h>
#include <nvscisync.h>
#include <vulkan/vulkan_sci.h>
#endif
#else
#include <vulkan/vulkan.h>
#endif

#if defined(_WIN32)
#include <Windows.h>
#elif defined(ANDROID) || defined(__linux__) || defined(__QNX__)
#include <dlfcn.h>
#else
#error "Unsupported platform"
#endif

#include "function_overrides.h"

#if defined(VK_VERSION_1_0)
static PFN_vkCreateInstance s_vkCreateInstance = nullptr;
static PFN_vkDestroyInstance s_vkDestroyInstance = nullptr;
static PFN_vkEnumeratePhysicalDevices s_vkEnumeratePhysicalDevices = nullptr;
static PFN_vkGetDeviceProcAddr s_vkGetDeviceProcAddr = nullptr;
static PFN_vkGetInstanceProcAddr s_vkGetInstanceProcAddr = nullptr;
static PFN_vkGetPhysicalDeviceProperties s_vkGetPhysicalDeviceProperties = nullptr;
static PFN_vkGetPhysicalDeviceQueueFamilyProperties s_vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
static PFN_vkGetPhysicalDeviceMemoryProperties s_vkGetPhysicalDeviceMemoryProperties = nullptr;
static PFN_vkGetPhysicalDeviceFeatures s_vkGetPhysicalDeviceFeatures = nullptr;
static PFN_vkGetPhysicalDeviceFormatProperties s_vkGetPhysicalDeviceFormatProperties = nullptr;
static PFN_vkGetPhysicalDeviceImageFormatProperties s_vkGetPhysicalDeviceImageFormatProperties = nullptr;
static PFN_vkCreateDevice s_vkCreateDevice = nullptr;
static PFN_vkDestroyDevice s_vkDestroyDevice = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_1)
static PFN_vkEnumerateInstanceVersion s_vkEnumerateInstanceVersion = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_VERSION_1_0)
static PFN_vkEnumerateInstanceLayerProperties s_vkEnumerateInstanceLayerProperties = nullptr;
static PFN_vkEnumerateInstanceExtensionProperties s_vkEnumerateInstanceExtensionProperties = nullptr;
static PFN_vkEnumerateDeviceLayerProperties s_vkEnumerateDeviceLayerProperties = nullptr;
static PFN_vkEnumerateDeviceExtensionProperties s_vkEnumerateDeviceExtensionProperties = nullptr;
static PFN_vkGetDeviceQueue s_vkGetDeviceQueue = nullptr;
static PFN_vkQueueSubmit s_vkQueueSubmit = nullptr;
static PFN_vkQueueWaitIdle s_vkQueueWaitIdle = nullptr;
static PFN_vkDeviceWaitIdle s_vkDeviceWaitIdle = nullptr;
static PFN_vkAllocateMemory s_vkAllocateMemory = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkFreeMemory s_vkFreeMemory = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkMapMemory s_vkMapMemory = nullptr;
static PFN_vkUnmapMemory s_vkUnmapMemory = nullptr;
static PFN_vkFlushMappedMemoryRanges s_vkFlushMappedMemoryRanges = nullptr;
static PFN_vkInvalidateMappedMemoryRanges s_vkInvalidateMappedMemoryRanges = nullptr;
static PFN_vkGetDeviceMemoryCommitment s_vkGetDeviceMemoryCommitment = nullptr;
static PFN_vkGetBufferMemoryRequirements s_vkGetBufferMemoryRequirements = nullptr;
static PFN_vkBindBufferMemory s_vkBindBufferMemory = nullptr;
static PFN_vkGetImageMemoryRequirements s_vkGetImageMemoryRequirements = nullptr;
static PFN_vkBindImageMemory s_vkBindImageMemory = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkGetImageSparseMemoryRequirements s_vkGetImageSparseMemoryRequirements = nullptr;
static PFN_vkGetPhysicalDeviceSparseImageFormatProperties s_vkGetPhysicalDeviceSparseImageFormatProperties = nullptr;
static PFN_vkQueueBindSparse s_vkQueueBindSparse = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkCreateFence s_vkCreateFence = nullptr;
static PFN_vkDestroyFence s_vkDestroyFence = nullptr;
static PFN_vkResetFences s_vkResetFences = nullptr;
static PFN_vkGetFenceStatus s_vkGetFenceStatus = nullptr;
static PFN_vkWaitForFences s_vkWaitForFences = nullptr;
static PFN_vkCreateSemaphore s_vkCreateSemaphore = nullptr;
static PFN_vkDestroySemaphore s_vkDestroySemaphore = nullptr;
static PFN_vkCreateEvent s_vkCreateEvent = nullptr;
static PFN_vkDestroyEvent s_vkDestroyEvent = nullptr;
static PFN_vkGetEventStatus s_vkGetEventStatus = nullptr;
static PFN_vkSetEvent s_vkSetEvent = nullptr;
static PFN_vkResetEvent s_vkResetEvent = nullptr;
static PFN_vkCreateQueryPool s_vkCreateQueryPool = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkDestroyQueryPool s_vkDestroyQueryPool = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkGetQueryPoolResults s_vkGetQueryPoolResults = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_2)
static PFN_vkResetQueryPool s_vkResetQueryPool = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_EXT_host_query_reset)
static PFN_vkResetQueryPoolEXT s_vkResetQueryPoolEXT = nullptr;
#endif // VK_EXT_host_query_reset

#if defined(VK_VERSION_1_0)
static PFN_vkCreateBuffer s_vkCreateBuffer = nullptr;
static PFN_vkDestroyBuffer s_vkDestroyBuffer = nullptr;
static PFN_vkCreateBufferView s_vkCreateBufferView = nullptr;
static PFN_vkDestroyBufferView s_vkDestroyBufferView = nullptr;
static PFN_vkCreateImage s_vkCreateImage = nullptr;
static PFN_vkDestroyImage s_vkDestroyImage = nullptr;
static PFN_vkGetImageSubresourceLayout s_vkGetImageSubresourceLayout = nullptr;
static PFN_vkCreateImageView s_vkCreateImageView = nullptr;
static PFN_vkDestroyImageView s_vkDestroyImageView = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkCreateShaderModule s_vkCreateShaderModule = nullptr;
static PFN_vkDestroyShaderModule s_vkDestroyShaderModule = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkCreatePipelineCache s_vkCreatePipelineCache = nullptr;
static PFN_vkDestroyPipelineCache s_vkDestroyPipelineCache = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkGetPipelineCacheData s_vkGetPipelineCacheData = nullptr;
static PFN_vkMergePipelineCaches s_vkMergePipelineCaches = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkCreateGraphicsPipelines s_vkCreateGraphicsPipelines = nullptr;
static PFN_vkCreateComputePipelines s_vkCreateComputePipelines = nullptr;
static PFN_vkDestroyPipeline s_vkDestroyPipeline = nullptr;
static PFN_vkCreatePipelineLayout s_vkCreatePipelineLayout = nullptr;
static PFN_vkDestroyPipelineLayout s_vkDestroyPipelineLayout = nullptr;
static PFN_vkCreateSampler s_vkCreateSampler = nullptr;
static PFN_vkDestroySampler s_vkDestroySampler = nullptr;
static PFN_vkCreateDescriptorSetLayout s_vkCreateDescriptorSetLayout = nullptr;
static PFN_vkDestroyDescriptorSetLayout s_vkDestroyDescriptorSetLayout = nullptr;
static PFN_vkCreateDescriptorPool s_vkCreateDescriptorPool = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkDestroyDescriptorPool s_vkDestroyDescriptorPool = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkResetDescriptorPool s_vkResetDescriptorPool = nullptr;
static PFN_vkAllocateDescriptorSets s_vkAllocateDescriptorSets = nullptr;
static PFN_vkFreeDescriptorSets s_vkFreeDescriptorSets = nullptr;
static PFN_vkUpdateDescriptorSets s_vkUpdateDescriptorSets = nullptr;
static PFN_vkCreateFramebuffer s_vkCreateFramebuffer = nullptr;
static PFN_vkDestroyFramebuffer s_vkDestroyFramebuffer = nullptr;
static PFN_vkCreateRenderPass s_vkCreateRenderPass = nullptr;
static PFN_vkDestroyRenderPass s_vkDestroyRenderPass = nullptr;
static PFN_vkGetRenderAreaGranularity s_vkGetRenderAreaGranularity = nullptr;
static PFN_vkCreateCommandPool s_vkCreateCommandPool = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
static PFN_vkDestroyCommandPool s_vkDestroyCommandPool = nullptr;
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
static PFN_vkResetCommandPool s_vkResetCommandPool = nullptr;
static PFN_vkAllocateCommandBuffers s_vkAllocateCommandBuffers = nullptr;
static PFN_vkFreeCommandBuffers s_vkFreeCommandBuffers = nullptr;
static PFN_vkBeginCommandBuffer s_vkBeginCommandBuffer = nullptr;
static PFN_vkEndCommandBuffer s_vkEndCommandBuffer = nullptr;
static PFN_vkResetCommandBuffer s_vkResetCommandBuffer = nullptr;
static PFN_vkCmdBindPipeline s_vkCmdBindPipeline = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
static PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT s_vkCmdSetAttachmentFeedbackLoopEnableEXT = nullptr;
#endif // VK_EXT_attachment_feedback_loop_dynamic_state

#if defined(VK_VERSION_1_0)
static PFN_vkCmdSetViewport s_vkCmdSetViewport = nullptr;
static PFN_vkCmdSetScissor s_vkCmdSetScissor = nullptr;
static PFN_vkCmdSetLineWidth s_vkCmdSetLineWidth = nullptr;
static PFN_vkCmdSetDepthBias s_vkCmdSetDepthBias = nullptr;
static PFN_vkCmdSetBlendConstants s_vkCmdSetBlendConstants = nullptr;
static PFN_vkCmdSetDepthBounds s_vkCmdSetDepthBounds = nullptr;
static PFN_vkCmdSetStencilCompareMask s_vkCmdSetStencilCompareMask = nullptr;
static PFN_vkCmdSetStencilWriteMask s_vkCmdSetStencilWriteMask = nullptr;
static PFN_vkCmdSetStencilReference s_vkCmdSetStencilReference = nullptr;
static PFN_vkCmdBindDescriptorSets s_vkCmdBindDescriptorSets = nullptr;
static PFN_vkCmdBindIndexBuffer s_vkCmdBindIndexBuffer = nullptr;
static PFN_vkCmdBindVertexBuffers s_vkCmdBindVertexBuffers = nullptr;
static PFN_vkCmdDraw s_vkCmdDraw = nullptr;
static PFN_vkCmdDrawIndexed s_vkCmdDrawIndexed = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_EXT_multi_draw)
static PFN_vkCmdDrawMultiEXT s_vkCmdDrawMultiEXT = nullptr;
static PFN_vkCmdDrawMultiIndexedEXT s_vkCmdDrawMultiIndexedEXT = nullptr;
#endif // VK_EXT_multi_draw

#if defined(VK_VERSION_1_0)
static PFN_vkCmdDrawIndirect s_vkCmdDrawIndirect = nullptr;
static PFN_vkCmdDrawIndexedIndirect s_vkCmdDrawIndexedIndirect = nullptr;
static PFN_vkCmdDispatch s_vkCmdDispatch = nullptr;
static PFN_vkCmdDispatchIndirect s_vkCmdDispatchIndirect = nullptr;
static PFN_vkCmdCopyBuffer s_vkCmdCopyBuffer = nullptr;
static PFN_vkCmdCopyImage s_vkCmdCopyImage = nullptr;
static PFN_vkCmdBlitImage s_vkCmdBlitImage = nullptr;
static PFN_vkCmdCopyBufferToImage s_vkCmdCopyBufferToImage = nullptr;
static PFN_vkCmdCopyImageToBuffer s_vkCmdCopyImageToBuffer = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_NV_copy_memory_indirect)
static PFN_vkCmdCopyMemoryIndirectNV s_vkCmdCopyMemoryIndirectNV = nullptr;
static PFN_vkCmdCopyMemoryToImageIndirectNV s_vkCmdCopyMemoryToImageIndirectNV = nullptr;
#endif // VK_NV_copy_memory_indirect

#if defined(VK_VERSION_1_0)
static PFN_vkCmdUpdateBuffer s_vkCmdUpdateBuffer = nullptr;
static PFN_vkCmdFillBuffer s_vkCmdFillBuffer = nullptr;
static PFN_vkCmdClearColorImage s_vkCmdClearColorImage = nullptr;
static PFN_vkCmdClearDepthStencilImage s_vkCmdClearDepthStencilImage = nullptr;
static PFN_vkCmdClearAttachments s_vkCmdClearAttachments = nullptr;
static PFN_vkCmdResolveImage s_vkCmdResolveImage = nullptr;
static PFN_vkCmdSetEvent s_vkCmdSetEvent = nullptr;
static PFN_vkCmdResetEvent s_vkCmdResetEvent = nullptr;
static PFN_vkCmdWaitEvents s_vkCmdWaitEvents = nullptr;
static PFN_vkCmdPipelineBarrier s_vkCmdPipelineBarrier = nullptr;
static PFN_vkCmdBeginQuery s_vkCmdBeginQuery = nullptr;
static PFN_vkCmdEndQuery s_vkCmdEndQuery = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_EXT_conditional_rendering)
static PFN_vkCmdBeginConditionalRenderingEXT s_vkCmdBeginConditionalRenderingEXT = nullptr;
static PFN_vkCmdEndConditionalRenderingEXT s_vkCmdEndConditionalRenderingEXT = nullptr;
#endif // VK_EXT_conditional_rendering

#if defined(VK_VERSION_1_0)
static PFN_vkCmdResetQueryPool s_vkCmdResetQueryPool = nullptr;
static PFN_vkCmdWriteTimestamp s_vkCmdWriteTimestamp = nullptr;
static PFN_vkCmdCopyQueryPoolResults s_vkCmdCopyQueryPoolResults = nullptr;
static PFN_vkCmdPushConstants s_vkCmdPushConstants = nullptr;
static PFN_vkCmdBeginRenderPass s_vkCmdBeginRenderPass = nullptr;
static PFN_vkCmdNextSubpass s_vkCmdNextSubpass = nullptr;
static PFN_vkCmdEndRenderPass s_vkCmdEndRenderPass = nullptr;
static PFN_vkCmdExecuteCommands s_vkCmdExecuteCommands = nullptr;
#endif // VK_VERSION_1_0

#if defined(VK_KHR_android_surface)
static PFN_vkCreateAndroidSurfaceKHR s_vkCreateAndroidSurfaceKHR = nullptr;
#endif // VK_KHR_android_surface

#if defined(VK_KHR_display)
static PFN_vkGetPhysicalDeviceDisplayPropertiesKHR s_vkGetPhysicalDeviceDisplayPropertiesKHR = nullptr;
static PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR s_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = nullptr;
static PFN_vkGetDisplayPlaneSupportedDisplaysKHR s_vkGetDisplayPlaneSupportedDisplaysKHR = nullptr;
static PFN_vkGetDisplayModePropertiesKHR s_vkGetDisplayModePropertiesKHR = nullptr;
static PFN_vkCreateDisplayModeKHR s_vkCreateDisplayModeKHR = nullptr;
static PFN_vkGetDisplayPlaneCapabilitiesKHR s_vkGetDisplayPlaneCapabilitiesKHR = nullptr;
static PFN_vkCreateDisplayPlaneSurfaceKHR s_vkCreateDisplayPlaneSurfaceKHR = nullptr;
#endif // VK_KHR_display

#if defined(VK_KHR_display_swapchain)
static PFN_vkCreateSharedSwapchainsKHR s_vkCreateSharedSwapchainsKHR = nullptr;
#endif // VK_KHR_display_swapchain

#if defined(VK_KHR_surface)
static PFN_vkDestroySurfaceKHR s_vkDestroySurfaceKHR = nullptr;
static PFN_vkGetPhysicalDeviceSurfaceSupportKHR s_vkGetPhysicalDeviceSurfaceSupportKHR = nullptr;
static PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR s_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
static PFN_vkGetPhysicalDeviceSurfaceFormatsKHR s_vkGetPhysicalDeviceSurfaceFormatsKHR = nullptr;
static PFN_vkGetPhysicalDeviceSurfacePresentModesKHR s_vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;
#endif // VK_KHR_surface

#if defined(VK_KHR_swapchain)
static PFN_vkCreateSwapchainKHR s_vkCreateSwapchainKHR = nullptr;
#endif // VK_KHR_swapchain

#if defined(VK_KHR_swapchain) && !defined(VKSC_VERSION_1_0)
static PFN_vkDestroySwapchainKHR s_vkDestroySwapchainKHR = nullptr;
#endif // VK_KHR_swapchain && !VKSC_VERSION_1_0

#if defined(VK_KHR_swapchain)
static PFN_vkGetSwapchainImagesKHR s_vkGetSwapchainImagesKHR = nullptr;
static PFN_vkAcquireNextImageKHR s_vkAcquireNextImageKHR = nullptr;
static PFN_vkQueuePresentKHR s_vkQueuePresentKHR = nullptr;
#endif // VK_KHR_swapchain

#if defined(VK_KHR_wayland_surface)
static PFN_vkCreateWaylandSurfaceKHR s_vkCreateWaylandSurfaceKHR = nullptr;
static PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR s_vkGetPhysicalDeviceWaylandPresentationSupportKHR = nullptr;
#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_win32_surface)
static PFN_vkCreateWin32SurfaceKHR s_vkCreateWin32SurfaceKHR = nullptr;
static PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR s_vkGetPhysicalDeviceWin32PresentationSupportKHR = nullptr;
#endif // VK_KHR_win32_surface

#if defined(VK_KHR_xlib_surface)
static PFN_vkCreateXlibSurfaceKHR s_vkCreateXlibSurfaceKHR = nullptr;
static PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR s_vkGetPhysicalDeviceXlibPresentationSupportKHR = nullptr;
#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
static PFN_vkCreateXcbSurfaceKHR s_vkCreateXcbSurfaceKHR = nullptr;
static PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR s_vkGetPhysicalDeviceXcbPresentationSupportKHR = nullptr;
#endif // VK_KHR_xcb_surface

#if defined(VK_EXT_debug_report)
static PFN_vkCreateDebugReportCallbackEXT s_vkCreateDebugReportCallbackEXT = nullptr;
static PFN_vkDestroyDebugReportCallbackEXT s_vkDestroyDebugReportCallbackEXT = nullptr;
static PFN_vkDebugReportMessageEXT s_vkDebugReportMessageEXT = nullptr;
#endif // VK_EXT_debug_report

#if defined(VK_EXT_debug_marker)
static PFN_vkDebugMarkerSetObjectNameEXT s_vkDebugMarkerSetObjectNameEXT = nullptr;
static PFN_vkDebugMarkerSetObjectTagEXT s_vkDebugMarkerSetObjectTagEXT = nullptr;
static PFN_vkCmdDebugMarkerBeginEXT s_vkCmdDebugMarkerBeginEXT = nullptr;
static PFN_vkCmdDebugMarkerEndEXT s_vkCmdDebugMarkerEndEXT = nullptr;
static PFN_vkCmdDebugMarkerInsertEXT s_vkCmdDebugMarkerInsertEXT = nullptr;
#endif // VK_EXT_debug_marker

#if defined(VK_NV_external_memory_capabilities)
static PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV s_vkGetPhysicalDeviceExternalImageFormatPropertiesNV = nullptr;
#endif // VK_NV_external_memory_capabilities

#if defined(VK_NV_external_memory_win32)
static PFN_vkGetMemoryWin32HandleNV s_vkGetMemoryWin32HandleNV = nullptr;
#endif // VK_NV_external_memory_win32

#if defined(VK_NV_device_generated_commands)
static PFN_vkCmdExecuteGeneratedCommandsNV s_vkCmdExecuteGeneratedCommandsNV = nullptr;
static PFN_vkCmdPreprocessGeneratedCommandsNV s_vkCmdPreprocessGeneratedCommandsNV = nullptr;
static PFN_vkCmdBindPipelineShaderGroupNV s_vkCmdBindPipelineShaderGroupNV = nullptr;
static PFN_vkGetGeneratedCommandsMemoryRequirementsNV s_vkGetGeneratedCommandsMemoryRequirementsNV = nullptr;
static PFN_vkCreateIndirectCommandsLayoutNV s_vkCreateIndirectCommandsLayoutNV = nullptr;
static PFN_vkDestroyIndirectCommandsLayoutNV s_vkDestroyIndirectCommandsLayoutNV = nullptr;
#endif // VK_NV_device_generated_commands

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceFeatures2 s_vkGetPhysicalDeviceFeatures2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceFeatures2KHR s_vkGetPhysicalDeviceFeatures2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceProperties2 s_vkGetPhysicalDeviceProperties2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceProperties2KHR s_vkGetPhysicalDeviceProperties2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceFormatProperties2 s_vkGetPhysicalDeviceFormatProperties2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceFormatProperties2KHR s_vkGetPhysicalDeviceFormatProperties2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceImageFormatProperties2 s_vkGetPhysicalDeviceImageFormatProperties2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceImageFormatProperties2KHR s_vkGetPhysicalDeviceImageFormatProperties2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceQueueFamilyProperties2 s_vkGetPhysicalDeviceQueueFamilyProperties2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR s_vkGetPhysicalDeviceQueueFamilyProperties2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceMemoryProperties2 s_vkGetPhysicalDeviceMemoryProperties2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceMemoryProperties2KHR s_vkGetPhysicalDeviceMemoryProperties2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
static PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 s_vkGetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_physical_device_properties2)
static PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR s_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = nullptr;
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_KHR_push_descriptor)
static PFN_vkCmdPushDescriptorSetKHR s_vkCmdPushDescriptorSetKHR = nullptr;
#endif // VK_KHR_push_descriptor

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
static PFN_vkTrimCommandPool s_vkTrimCommandPool = nullptr;
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_maintenance1) && !defined(VKSC_VERSION_1_0)
static PFN_vkTrimCommandPoolKHR s_vkTrimCommandPoolKHR = nullptr;
#endif // VK_KHR_maintenance1 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceExternalBufferProperties s_vkGetPhysicalDeviceExternalBufferProperties = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_memory_capabilities)
static PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR s_vkGetPhysicalDeviceExternalBufferPropertiesKHR = nullptr;
#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_memory_win32)
static PFN_vkGetMemoryWin32HandleKHR s_vkGetMemoryWin32HandleKHR = nullptr;
static PFN_vkGetMemoryWin32HandlePropertiesKHR s_vkGetMemoryWin32HandlePropertiesKHR = nullptr;
#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
static PFN_vkGetMemoryFdKHR s_vkGetMemoryFdKHR = nullptr;
static PFN_vkGetMemoryFdPropertiesKHR s_vkGetMemoryFdPropertiesKHR = nullptr;
#endif // VK_KHR_external_memory_fd

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceExternalSemaphoreProperties s_vkGetPhysicalDeviceExternalSemaphoreProperties = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_semaphore_capabilities)
static PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR s_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = nullptr;
#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_KHR_external_semaphore_win32)
static PFN_vkGetSemaphoreWin32HandleKHR s_vkGetSemaphoreWin32HandleKHR = nullptr;
static PFN_vkImportSemaphoreWin32HandleKHR s_vkImportSemaphoreWin32HandleKHR = nullptr;
#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
static PFN_vkGetSemaphoreFdKHR s_vkGetSemaphoreFdKHR = nullptr;
static PFN_vkImportSemaphoreFdKHR s_vkImportSemaphoreFdKHR = nullptr;
#endif // VK_KHR_external_semaphore_fd

#if defined(VK_VERSION_1_1)
static PFN_vkGetPhysicalDeviceExternalFenceProperties s_vkGetPhysicalDeviceExternalFenceProperties = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_fence_capabilities)
static PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR s_vkGetPhysicalDeviceExternalFencePropertiesKHR = nullptr;
#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_external_fence_win32)
static PFN_vkGetFenceWin32HandleKHR s_vkGetFenceWin32HandleKHR = nullptr;
static PFN_vkImportFenceWin32HandleKHR s_vkImportFenceWin32HandleKHR = nullptr;
#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
static PFN_vkGetFenceFdKHR s_vkGetFenceFdKHR = nullptr;
static PFN_vkImportFenceFdKHR s_vkImportFenceFdKHR = nullptr;
#endif // VK_KHR_external_fence_fd

#if defined(VK_EXT_direct_mode_display)
static PFN_vkReleaseDisplayEXT s_vkReleaseDisplayEXT = nullptr;
#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
static PFN_vkAcquireXlibDisplayEXT s_vkAcquireXlibDisplayEXT = nullptr;
static PFN_vkGetRandROutputDisplayEXT s_vkGetRandROutputDisplayEXT = nullptr;
#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
static PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT s_vkGetPhysicalDeviceSurfaceCapabilities2EXT = nullptr;
#endif // VK_EXT_display_surface_counter

#if defined(VK_VERSION_1_1)
static PFN_vkEnumeratePhysicalDeviceGroups s_vkEnumeratePhysicalDeviceGroups = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group_creation)
static PFN_vkEnumeratePhysicalDeviceGroupsKHR s_vkEnumeratePhysicalDeviceGroupsKHR = nullptr;
#endif // VK_KHR_device_group_creation

#if defined(VK_VERSION_1_1)
static PFN_vkGetDeviceGroupPeerMemoryFeatures s_vkGetDeviceGroupPeerMemoryFeatures = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
static PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR s_vkGetDeviceGroupPeerMemoryFeaturesKHR = nullptr;
#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1)
static PFN_vkBindBufferMemory2 s_vkBindBufferMemory2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
static PFN_vkBindBufferMemory2KHR s_vkBindBufferMemory2KHR = nullptr;
#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
static PFN_vkBindImageMemory2 s_vkBindImageMemory2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
static PFN_vkBindImageMemory2KHR s_vkBindImageMemory2KHR = nullptr;
#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
static PFN_vkCmdSetDeviceMask s_vkCmdSetDeviceMask = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
static PFN_vkCmdSetDeviceMaskKHR s_vkCmdSetDeviceMaskKHR = nullptr;
#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
static PFN_vkGetDeviceGroupPresentCapabilitiesKHR s_vkGetDeviceGroupPresentCapabilitiesKHR = nullptr;
static PFN_vkGetDeviceGroupSurfacePresentModesKHR s_vkGetDeviceGroupSurfacePresentModesKHR = nullptr;
static PFN_vkAcquireNextImage2KHR s_vkAcquireNextImage2KHR = nullptr;
#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1)
static PFN_vkCmdDispatchBase s_vkCmdDispatchBase = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
static PFN_vkCmdDispatchBaseKHR s_vkCmdDispatchBaseKHR = nullptr;
#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
static PFN_vkGetPhysicalDevicePresentRectanglesKHR s_vkGetPhysicalDevicePresentRectanglesKHR = nullptr;
#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
static PFN_vkCreateDescriptorUpdateTemplate s_vkCreateDescriptorUpdateTemplate = nullptr;
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
static PFN_vkCreateDescriptorUpdateTemplateKHR s_vkCreateDescriptorUpdateTemplateKHR = nullptr;
#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
static PFN_vkDestroyDescriptorUpdateTemplate s_vkDestroyDescriptorUpdateTemplate = nullptr;
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
static PFN_vkDestroyDescriptorUpdateTemplateKHR s_vkDestroyDescriptorUpdateTemplateKHR = nullptr;
#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
static PFN_vkUpdateDescriptorSetWithTemplate s_vkUpdateDescriptorSetWithTemplate = nullptr;
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
static PFN_vkUpdateDescriptorSetWithTemplateKHR s_vkUpdateDescriptorSetWithTemplateKHR = nullptr;
#endif // VK_KHR_descriptor_update_template

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
static PFN_vkCmdPushDescriptorSetWithTemplateKHR s_vkCmdPushDescriptorSetWithTemplateKHR = nullptr;
#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

#if defined(VK_EXT_hdr_metadata)
static PFN_vkSetHdrMetadataEXT s_vkSetHdrMetadataEXT = nullptr;
#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_shared_presentable_image)
static PFN_vkGetSwapchainStatusKHR s_vkGetSwapchainStatusKHR = nullptr;
#endif // VK_KHR_shared_presentable_image

#if defined(VK_NV_clip_space_w_scaling)
static PFN_vkCmdSetViewportWScalingNV s_vkCmdSetViewportWScalingNV = nullptr;
#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_discard_rectangles)
static PFN_vkCmdSetDiscardRectangleEXT s_vkCmdSetDiscardRectangleEXT = nullptr;
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
static PFN_vkCmdSetDiscardRectangleEnableEXT s_vkCmdSetDiscardRectangleEnableEXT = nullptr;
static PFN_vkCmdSetDiscardRectangleModeEXT s_vkCmdSetDiscardRectangleModeEXT = nullptr;
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_sample_locations)
static PFN_vkCmdSetSampleLocationsEXT s_vkCmdSetSampleLocationsEXT = nullptr;
static PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT s_vkGetPhysicalDeviceMultisamplePropertiesEXT = nullptr;
#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_surface_capabilities2)
static PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR s_vkGetPhysicalDeviceSurfaceCapabilities2KHR = nullptr;
static PFN_vkGetPhysicalDeviceSurfaceFormats2KHR s_vkGetPhysicalDeviceSurfaceFormats2KHR = nullptr;
#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
static PFN_vkGetPhysicalDeviceDisplayProperties2KHR s_vkGetPhysicalDeviceDisplayProperties2KHR = nullptr;
static PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR s_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = nullptr;
static PFN_vkGetDisplayModeProperties2KHR s_vkGetDisplayModeProperties2KHR = nullptr;
static PFN_vkGetDisplayPlaneCapabilities2KHR s_vkGetDisplayPlaneCapabilities2KHR = nullptr;
#endif // VK_KHR_get_display_properties2

#if defined(VK_VERSION_1_1)
static PFN_vkGetBufferMemoryRequirements2 s_vkGetBufferMemoryRequirements2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
static PFN_vkGetBufferMemoryRequirements2KHR s_vkGetBufferMemoryRequirements2KHR = nullptr;
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1)
static PFN_vkGetImageMemoryRequirements2 s_vkGetImageMemoryRequirements2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
static PFN_vkGetImageMemoryRequirements2KHR s_vkGetImageMemoryRequirements2KHR = nullptr;
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
static PFN_vkGetImageSparseMemoryRequirements2 s_vkGetImageSparseMemoryRequirements2 = nullptr;
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_memory_requirements2)
static PFN_vkGetImageSparseMemoryRequirements2KHR s_vkGetImageSparseMemoryRequirements2KHR = nullptr;
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_3)
static PFN_vkGetDeviceBufferMemoryRequirements s_vkGetDeviceBufferMemoryRequirements = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
static PFN_vkGetDeviceBufferMemoryRequirementsKHR s_vkGetDeviceBufferMemoryRequirementsKHR = nullptr;
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
static PFN_vkGetDeviceImageMemoryRequirements s_vkGetDeviceImageMemoryRequirements = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
static PFN_vkGetDeviceImageMemoryRequirementsKHR s_vkGetDeviceImageMemoryRequirementsKHR = nullptr;
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
static PFN_vkGetDeviceImageSparseMemoryRequirements s_vkGetDeviceImageSparseMemoryRequirements = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
static PFN_vkGetDeviceImageSparseMemoryRequirementsKHR s_vkGetDeviceImageSparseMemoryRequirementsKHR = nullptr;
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_1)
static PFN_vkCreateSamplerYcbcrConversion s_vkCreateSamplerYcbcrConversion = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
static PFN_vkCreateSamplerYcbcrConversionKHR s_vkCreateSamplerYcbcrConversionKHR = nullptr;
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
static PFN_vkDestroySamplerYcbcrConversion s_vkDestroySamplerYcbcrConversion = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
static PFN_vkDestroySamplerYcbcrConversionKHR s_vkDestroySamplerYcbcrConversionKHR = nullptr;
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
static PFN_vkGetDeviceQueue2 s_vkGetDeviceQueue2 = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_EXT_validation_cache)
static PFN_vkCreateValidationCacheEXT s_vkCreateValidationCacheEXT = nullptr;
static PFN_vkDestroyValidationCacheEXT s_vkDestroyValidationCacheEXT = nullptr;
static PFN_vkGetValidationCacheDataEXT s_vkGetValidationCacheDataEXT = nullptr;
static PFN_vkMergeValidationCachesEXT s_vkMergeValidationCachesEXT = nullptr;
#endif // VK_EXT_validation_cache

#if defined(VK_VERSION_1_1)
static PFN_vkGetDescriptorSetLayoutSupport s_vkGetDescriptorSetLayoutSupport = nullptr;
#endif // VK_VERSION_1_1

#if defined(VK_KHR_maintenance3)
static PFN_vkGetDescriptorSetLayoutSupportKHR s_vkGetDescriptorSetLayoutSupportKHR = nullptr;
#endif // VK_KHR_maintenance3

#if defined(VK_AMD_shader_info)
static PFN_vkGetShaderInfoAMD s_vkGetShaderInfoAMD = nullptr;
#endif // VK_AMD_shader_info

#if defined(VK_EXT_calibrated_timestamps)
static PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT s_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = nullptr;
static PFN_vkGetCalibratedTimestampsEXT s_vkGetCalibratedTimestampsEXT = nullptr;
#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
static PFN_vkSetDebugUtilsObjectNameEXT s_vkSetDebugUtilsObjectNameEXT = nullptr;
static PFN_vkSetDebugUtilsObjectTagEXT s_vkSetDebugUtilsObjectTagEXT = nullptr;
static PFN_vkQueueBeginDebugUtilsLabelEXT s_vkQueueBeginDebugUtilsLabelEXT = nullptr;
static PFN_vkQueueEndDebugUtilsLabelEXT s_vkQueueEndDebugUtilsLabelEXT = nullptr;
static PFN_vkQueueInsertDebugUtilsLabelEXT s_vkQueueInsertDebugUtilsLabelEXT = nullptr;
static PFN_vkCmdBeginDebugUtilsLabelEXT s_vkCmdBeginDebugUtilsLabelEXT = nullptr;
static PFN_vkCmdEndDebugUtilsLabelEXT s_vkCmdEndDebugUtilsLabelEXT = nullptr;
static PFN_vkCmdInsertDebugUtilsLabelEXT s_vkCmdInsertDebugUtilsLabelEXT = nullptr;
static PFN_vkCreateDebugUtilsMessengerEXT s_vkCreateDebugUtilsMessengerEXT = nullptr;
static PFN_vkDestroyDebugUtilsMessengerEXT s_vkDestroyDebugUtilsMessengerEXT = nullptr;
static PFN_vkSubmitDebugUtilsMessageEXT s_vkSubmitDebugUtilsMessageEXT = nullptr;
#endif // VK_EXT_debug_utils

#if defined(VK_EXT_external_memory_host)
static PFN_vkGetMemoryHostPointerPropertiesEXT s_vkGetMemoryHostPointerPropertiesEXT = nullptr;
#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
static PFN_vkCmdWriteBufferMarkerAMD s_vkCmdWriteBufferMarkerAMD = nullptr;
#endif // VK_AMD_buffer_marker

#if defined(VK_VERSION_1_2)
static PFN_vkCreateRenderPass2 s_vkCreateRenderPass2 = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
static PFN_vkCreateRenderPass2KHR s_vkCreateRenderPass2KHR = nullptr;
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
static PFN_vkCmdBeginRenderPass2 s_vkCmdBeginRenderPass2 = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
static PFN_vkCmdBeginRenderPass2KHR s_vkCmdBeginRenderPass2KHR = nullptr;
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
static PFN_vkCmdNextSubpass2 s_vkCmdNextSubpass2 = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
static PFN_vkCmdNextSubpass2KHR s_vkCmdNextSubpass2KHR = nullptr;
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
static PFN_vkCmdEndRenderPass2 s_vkCmdEndRenderPass2 = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
static PFN_vkCmdEndRenderPass2KHR s_vkCmdEndRenderPass2KHR = nullptr;
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
static PFN_vkGetSemaphoreCounterValue s_vkGetSemaphoreCounterValue = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
static PFN_vkGetSemaphoreCounterValueKHR s_vkGetSemaphoreCounterValueKHR = nullptr;
#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
static PFN_vkWaitSemaphores s_vkWaitSemaphores = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
static PFN_vkWaitSemaphoresKHR s_vkWaitSemaphoresKHR = nullptr;
#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
static PFN_vkSignalSemaphore s_vkSignalSemaphore = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
static PFN_vkSignalSemaphoreKHR s_vkSignalSemaphoreKHR = nullptr;
#endif // VK_KHR_timeline_semaphore

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
static PFN_vkGetAndroidHardwareBufferPropertiesANDROID s_vkGetAndroidHardwareBufferPropertiesANDROID = nullptr;
static PFN_vkGetMemoryAndroidHardwareBufferANDROID s_vkGetMemoryAndroidHardwareBufferANDROID = nullptr;
#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_VERSION_1_2)
static PFN_vkCmdDrawIndirectCount s_vkCmdDrawIndirectCount = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
static PFN_vkCmdDrawIndirectCountKHR s_vkCmdDrawIndirectCountKHR = nullptr;
#endif // VK_KHR_draw_indirect_count

#if defined(VK_VERSION_1_2)
static PFN_vkCmdDrawIndexedIndirectCount s_vkCmdDrawIndexedIndirectCount = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
static PFN_vkCmdDrawIndexedIndirectCountKHR s_vkCmdDrawIndexedIndirectCountKHR = nullptr;
#endif // VK_KHR_draw_indirect_count

#if defined(VK_NV_device_diagnostic_checkpoints)
static PFN_vkCmdSetCheckpointNV s_vkCmdSetCheckpointNV = nullptr;
static PFN_vkGetQueueCheckpointDataNV s_vkGetQueueCheckpointDataNV = nullptr;
#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_EXT_transform_feedback)
static PFN_vkCmdBindTransformFeedbackBuffersEXT s_vkCmdBindTransformFeedbackBuffersEXT = nullptr;
static PFN_vkCmdBeginTransformFeedbackEXT s_vkCmdBeginTransformFeedbackEXT = nullptr;
static PFN_vkCmdEndTransformFeedbackEXT s_vkCmdEndTransformFeedbackEXT = nullptr;
static PFN_vkCmdBeginQueryIndexedEXT s_vkCmdBeginQueryIndexedEXT = nullptr;
static PFN_vkCmdEndQueryIndexedEXT s_vkCmdEndQueryIndexedEXT = nullptr;
static PFN_vkCmdDrawIndirectByteCountEXT s_vkCmdDrawIndirectByteCountEXT = nullptr;
#endif // VK_EXT_transform_feedback

#if defined(VK_NV_scissor_exclusive)
static PFN_vkCmdSetExclusiveScissorNV s_vkCmdSetExclusiveScissorNV = nullptr;
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
static PFN_vkCmdSetExclusiveScissorEnableNV s_vkCmdSetExclusiveScissorEnableNV = nullptr;
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_shading_rate_image)
static PFN_vkCmdBindShadingRateImageNV s_vkCmdBindShadingRateImageNV = nullptr;
static PFN_vkCmdSetViewportShadingRatePaletteNV s_vkCmdSetViewportShadingRatePaletteNV = nullptr;
static PFN_vkCmdSetCoarseSampleOrderNV s_vkCmdSetCoarseSampleOrderNV = nullptr;
#endif // VK_NV_shading_rate_image

#if defined(VK_NV_mesh_shader)
static PFN_vkCmdDrawMeshTasksNV s_vkCmdDrawMeshTasksNV = nullptr;
static PFN_vkCmdDrawMeshTasksIndirectNV s_vkCmdDrawMeshTasksIndirectNV = nullptr;
static PFN_vkCmdDrawMeshTasksIndirectCountNV s_vkCmdDrawMeshTasksIndirectCountNV = nullptr;
#endif // VK_NV_mesh_shader

#if defined(VK_EXT_mesh_shader)
static PFN_vkCmdDrawMeshTasksEXT s_vkCmdDrawMeshTasksEXT = nullptr;
static PFN_vkCmdDrawMeshTasksIndirectEXT s_vkCmdDrawMeshTasksIndirectEXT = nullptr;
static PFN_vkCmdDrawMeshTasksIndirectCountEXT s_vkCmdDrawMeshTasksIndirectCountEXT = nullptr;
#endif // VK_EXT_mesh_shader

#if defined(VK_NV_ray_tracing)
static PFN_vkCompileDeferredNV s_vkCompileDeferredNV = nullptr;
static PFN_vkCreateAccelerationStructureNV s_vkCreateAccelerationStructureNV = nullptr;
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
static PFN_vkDestroyAccelerationStructureKHR s_vkDestroyAccelerationStructureKHR = nullptr;
#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
static PFN_vkDestroyAccelerationStructureNV s_vkDestroyAccelerationStructureNV = nullptr;
static PFN_vkGetAccelerationStructureMemoryRequirementsNV s_vkGetAccelerationStructureMemoryRequirementsNV = nullptr;
static PFN_vkBindAccelerationStructureMemoryNV s_vkBindAccelerationStructureMemoryNV = nullptr;
static PFN_vkCmdCopyAccelerationStructureNV s_vkCmdCopyAccelerationStructureNV = nullptr;
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
static PFN_vkCmdCopyAccelerationStructureKHR s_vkCmdCopyAccelerationStructureKHR = nullptr;
static PFN_vkCopyAccelerationStructureKHR s_vkCopyAccelerationStructureKHR = nullptr;
static PFN_vkCmdCopyAccelerationStructureToMemoryKHR s_vkCmdCopyAccelerationStructureToMemoryKHR = nullptr;
static PFN_vkCopyAccelerationStructureToMemoryKHR s_vkCopyAccelerationStructureToMemoryKHR = nullptr;
static PFN_vkCmdCopyMemoryToAccelerationStructureKHR s_vkCmdCopyMemoryToAccelerationStructureKHR = nullptr;
static PFN_vkCopyMemoryToAccelerationStructureKHR s_vkCopyMemoryToAccelerationStructureKHR = nullptr;
static PFN_vkCmdWriteAccelerationStructuresPropertiesKHR s_vkCmdWriteAccelerationStructuresPropertiesKHR = nullptr;
#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
static PFN_vkCmdWriteAccelerationStructuresPropertiesNV s_vkCmdWriteAccelerationStructuresPropertiesNV = nullptr;
static PFN_vkCmdBuildAccelerationStructureNV s_vkCmdBuildAccelerationStructureNV = nullptr;
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
static PFN_vkWriteAccelerationStructuresPropertiesKHR s_vkWriteAccelerationStructuresPropertiesKHR = nullptr;
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
static PFN_vkCmdTraceRaysKHR s_vkCmdTraceRaysKHR = nullptr;
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
static PFN_vkCmdTraceRaysNV s_vkCmdTraceRaysNV = nullptr;
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
static PFN_vkGetRayTracingShaderGroupHandlesKHR s_vkGetRayTracingShaderGroupHandlesKHR = nullptr;
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
static PFN_vkGetRayTracingShaderGroupHandlesNV s_vkGetRayTracingShaderGroupHandlesNV = nullptr;
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
static PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR s_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
static PFN_vkGetAccelerationStructureHandleNV s_vkGetAccelerationStructureHandleNV = nullptr;
static PFN_vkCreateRayTracingPipelinesNV s_vkCreateRayTracingPipelinesNV = nullptr;
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
static PFN_vkCreateRayTracingPipelinesKHR s_vkCreateRayTracingPipelinesKHR = nullptr;
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_cooperative_matrix)
static PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV s_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = nullptr;
#endif // VK_NV_cooperative_matrix

#if defined(VK_KHR_ray_tracing_pipeline)
static PFN_vkCmdTraceRaysIndirectKHR s_vkCmdTraceRaysIndirectKHR = nullptr;
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_ray_tracing_maintenance1)
static PFN_vkCmdTraceRaysIndirect2KHR s_vkCmdTraceRaysIndirect2KHR = nullptr;
#endif // VK_KHR_ray_tracing_maintenance1

#if defined(VK_KHR_acceleration_structure)
static PFN_vkGetDeviceAccelerationStructureCompatibilityKHR s_vkGetDeviceAccelerationStructureCompatibilityKHR = nullptr;
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
static PFN_vkGetRayTracingShaderGroupStackSizeKHR s_vkGetRayTracingShaderGroupStackSizeKHR = nullptr;
static PFN_vkCmdSetRayTracingPipelineStackSizeKHR s_vkCmdSetRayTracingPipelineStackSizeKHR = nullptr;
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NVX_image_view_handle)
static PFN_vkGetImageViewHandleNVX s_vkGetImageViewHandleNVX = nullptr;
static PFN_vkGetImageViewAddressNVX s_vkGetImageViewAddressNVX = nullptr;
#endif // VK_NVX_image_view_handle

#if defined(VK_EXT_full_screen_exclusive)
static PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT s_vkGetPhysicalDeviceSurfacePresentModes2EXT = nullptr;
static PFN_vkGetDeviceGroupSurfacePresentModes2EXT s_vkGetDeviceGroupSurfacePresentModes2EXT = nullptr;
static PFN_vkAcquireFullScreenExclusiveModeEXT s_vkAcquireFullScreenExclusiveModeEXT = nullptr;
static PFN_vkReleaseFullScreenExclusiveModeEXT s_vkReleaseFullScreenExclusiveModeEXT = nullptr;
#endif // VK_EXT_full_screen_exclusive

#if defined(VK_VERSION_1_2)
static PFN_vkGetBufferOpaqueCaptureAddress s_vkGetBufferOpaqueCaptureAddress = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
static PFN_vkGetBufferOpaqueCaptureAddressKHR s_vkGetBufferOpaqueCaptureAddressKHR = nullptr;
#endif // VK_KHR_buffer_device_address

#if defined(VK_VERSION_1_2)
static PFN_vkGetBufferDeviceAddress s_vkGetBufferDeviceAddress = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
static PFN_vkGetBufferDeviceAddressKHR s_vkGetBufferDeviceAddressKHR = nullptr;
#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_buffer_device_address)
static PFN_vkGetBufferDeviceAddressEXT s_vkGetBufferDeviceAddressEXT = nullptr;
#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_headless_surface)
static PFN_vkCreateHeadlessSurfaceEXT s_vkCreateHeadlessSurfaceEXT = nullptr;
#endif // VK_EXT_headless_surface

#if defined(VK_NV_coverage_reduction_mode)
static PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV s_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = nullptr;
#endif // VK_NV_coverage_reduction_mode

#if defined(VK_VERSION_1_2)
static PFN_vkGetDeviceMemoryOpaqueCaptureAddress s_vkGetDeviceMemoryOpaqueCaptureAddress = nullptr;
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
static PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR s_vkGetDeviceMemoryOpaqueCaptureAddressKHR = nullptr;
#endif // VK_KHR_buffer_device_address

#if defined(VK_KHR_pipeline_executable_properties)
static PFN_vkGetPipelineExecutablePropertiesKHR s_vkGetPipelineExecutablePropertiesKHR = nullptr;
static PFN_vkGetPipelineExecutableStatisticsKHR s_vkGetPipelineExecutableStatisticsKHR = nullptr;
static PFN_vkGetPipelineExecutableInternalRepresentationsKHR s_vkGetPipelineExecutableInternalRepresentationsKHR = nullptr;
#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_EXT_line_rasterization)
static PFN_vkCmdSetLineStippleEXT s_vkCmdSetLineStippleEXT = nullptr;
#endif // VK_EXT_line_rasterization

#if defined(VKSC_VERSION_1_0)
static PFN_vkGetFaultData s_vkGetFaultData = nullptr;
#endif // VKSC_VERSION_1_0

#if defined(VK_VERSION_1_3)
static PFN_vkGetPhysicalDeviceToolProperties s_vkGetPhysicalDeviceToolProperties = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_tooling_info)
static PFN_vkGetPhysicalDeviceToolPropertiesEXT s_vkGetPhysicalDeviceToolPropertiesEXT = nullptr;
#endif // VK_EXT_tooling_info

#if defined(VK_KHR_acceleration_structure)
static PFN_vkCreateAccelerationStructureKHR s_vkCreateAccelerationStructureKHR = nullptr;
static PFN_vkCmdBuildAccelerationStructuresKHR s_vkCmdBuildAccelerationStructuresKHR = nullptr;
static PFN_vkCmdBuildAccelerationStructuresIndirectKHR s_vkCmdBuildAccelerationStructuresIndirectKHR = nullptr;
static PFN_vkBuildAccelerationStructuresKHR s_vkBuildAccelerationStructuresKHR = nullptr;
static PFN_vkGetAccelerationStructureDeviceAddressKHR s_vkGetAccelerationStructureDeviceAddressKHR = nullptr;
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_deferred_host_operations)
static PFN_vkCreateDeferredOperationKHR s_vkCreateDeferredOperationKHR = nullptr;
static PFN_vkDestroyDeferredOperationKHR s_vkDestroyDeferredOperationKHR = nullptr;
static PFN_vkGetDeferredOperationMaxConcurrencyKHR s_vkGetDeferredOperationMaxConcurrencyKHR = nullptr;
static PFN_vkGetDeferredOperationResultKHR s_vkGetDeferredOperationResultKHR = nullptr;
static PFN_vkDeferredOperationJoinKHR s_vkDeferredOperationJoinKHR = nullptr;
#endif // VK_KHR_deferred_host_operations

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetCullMode s_vkCmdSetCullMode = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetCullModeEXT s_vkCmdSetCullModeEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetFrontFace s_vkCmdSetFrontFace = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetFrontFaceEXT s_vkCmdSetFrontFaceEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetPrimitiveTopology s_vkCmdSetPrimitiveTopology = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetPrimitiveTopologyEXT s_vkCmdSetPrimitiveTopologyEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetViewportWithCount s_vkCmdSetViewportWithCount = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetViewportWithCountEXT s_vkCmdSetViewportWithCountEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetScissorWithCount s_vkCmdSetScissorWithCount = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetScissorWithCountEXT s_vkCmdSetScissorWithCountEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdBindVertexBuffers2 s_vkCmdBindVertexBuffers2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdBindVertexBuffers2EXT s_vkCmdBindVertexBuffers2EXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetDepthTestEnable s_vkCmdSetDepthTestEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetDepthTestEnableEXT s_vkCmdSetDepthTestEnableEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetDepthWriteEnable s_vkCmdSetDepthWriteEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetDepthWriteEnableEXT s_vkCmdSetDepthWriteEnableEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetDepthCompareOp s_vkCmdSetDepthCompareOp = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetDepthCompareOpEXT s_vkCmdSetDepthCompareOpEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetDepthBoundsTestEnable s_vkCmdSetDepthBoundsTestEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetDepthBoundsTestEnableEXT s_vkCmdSetDepthBoundsTestEnableEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetStencilTestEnable s_vkCmdSetStencilTestEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetStencilTestEnableEXT s_vkCmdSetStencilTestEnableEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetStencilOp s_vkCmdSetStencilOp = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetStencilOpEXT s_vkCmdSetStencilOpEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetPatchControlPointsEXT s_vkCmdSetPatchControlPointsEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetRasterizerDiscardEnable s_vkCmdSetRasterizerDiscardEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetRasterizerDiscardEnableEXT s_vkCmdSetRasterizerDiscardEnableEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetDepthBiasEnable s_vkCmdSetDepthBiasEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetDepthBiasEnableEXT s_vkCmdSetDepthBiasEnableEXT = nullptr;
static PFN_vkCmdSetLogicOpEXT s_vkCmdSetLogicOpEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetPrimitiveRestartEnable s_vkCmdSetPrimitiveRestartEnable = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetPrimitiveRestartEnableEXT s_vkCmdSetPrimitiveRestartEnableEXT = nullptr;
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state3) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetTessellationDomainOriginEXT s_vkCmdSetTessellationDomainOriginEXT = nullptr;
static PFN_vkCmdSetDepthClampEnableEXT s_vkCmdSetDepthClampEnableEXT = nullptr;
static PFN_vkCmdSetPolygonModeEXT s_vkCmdSetPolygonModeEXT = nullptr;
static PFN_vkCmdSetRasterizationSamplesEXT s_vkCmdSetRasterizationSamplesEXT = nullptr;
static PFN_vkCmdSetSampleMaskEXT s_vkCmdSetSampleMaskEXT = nullptr;
static PFN_vkCmdSetAlphaToCoverageEnableEXT s_vkCmdSetAlphaToCoverageEnableEXT = nullptr;
static PFN_vkCmdSetAlphaToOneEnableEXT s_vkCmdSetAlphaToOneEnableEXT = nullptr;
static PFN_vkCmdSetLogicOpEnableEXT s_vkCmdSetLogicOpEnableEXT = nullptr;
static PFN_vkCmdSetColorBlendEnableEXT s_vkCmdSetColorBlendEnableEXT = nullptr;
static PFN_vkCmdSetColorBlendEquationEXT s_vkCmdSetColorBlendEquationEXT = nullptr;
static PFN_vkCmdSetColorWriteMaskEXT s_vkCmdSetColorWriteMaskEXT = nullptr;
static PFN_vkCmdSetRasterizationStreamEXT s_vkCmdSetRasterizationStreamEXT = nullptr;
static PFN_vkCmdSetConservativeRasterizationModeEXT s_vkCmdSetConservativeRasterizationModeEXT = nullptr;
static PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT s_vkCmdSetExtraPrimitiveOverestimationSizeEXT = nullptr;
static PFN_vkCmdSetDepthClipEnableEXT s_vkCmdSetDepthClipEnableEXT = nullptr;
static PFN_vkCmdSetSampleLocationsEnableEXT s_vkCmdSetSampleLocationsEnableEXT = nullptr;
static PFN_vkCmdSetColorBlendAdvancedEXT s_vkCmdSetColorBlendAdvancedEXT = nullptr;
static PFN_vkCmdSetProvokingVertexModeEXT s_vkCmdSetProvokingVertexModeEXT = nullptr;
static PFN_vkCmdSetLineRasterizationModeEXT s_vkCmdSetLineRasterizationModeEXT = nullptr;
static PFN_vkCmdSetLineStippleEnableEXT s_vkCmdSetLineStippleEnableEXT = nullptr;
static PFN_vkCmdSetDepthClipNegativeOneToOneEXT s_vkCmdSetDepthClipNegativeOneToOneEXT = nullptr;
static PFN_vkCmdSetViewportWScalingEnableNV s_vkCmdSetViewportWScalingEnableNV = nullptr;
static PFN_vkCmdSetViewportSwizzleNV s_vkCmdSetViewportSwizzleNV = nullptr;
static PFN_vkCmdSetCoverageToColorEnableNV s_vkCmdSetCoverageToColorEnableNV = nullptr;
static PFN_vkCmdSetCoverageToColorLocationNV s_vkCmdSetCoverageToColorLocationNV = nullptr;
static PFN_vkCmdSetCoverageModulationModeNV s_vkCmdSetCoverageModulationModeNV = nullptr;
static PFN_vkCmdSetCoverageModulationTableEnableNV s_vkCmdSetCoverageModulationTableEnableNV = nullptr;
static PFN_vkCmdSetCoverageModulationTableNV s_vkCmdSetCoverageModulationTableNV = nullptr;
static PFN_vkCmdSetShadingRateImageEnableNV s_vkCmdSetShadingRateImageEnableNV = nullptr;
static PFN_vkCmdSetCoverageReductionModeNV s_vkCmdSetCoverageReductionModeNV = nullptr;
static PFN_vkCmdSetRepresentativeFragmentTestEnableNV s_vkCmdSetRepresentativeFragmentTestEnableNV = nullptr;
#endif // VK_EXT_extended_dynamic_state3 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
static PFN_vkCreatePrivateDataSlot s_vkCreatePrivateDataSlot = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
static PFN_vkCreatePrivateDataSlotEXT s_vkCreatePrivateDataSlotEXT = nullptr;
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
static PFN_vkDestroyPrivateDataSlot s_vkDestroyPrivateDataSlot = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
static PFN_vkDestroyPrivateDataSlotEXT s_vkDestroyPrivateDataSlotEXT = nullptr;
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
static PFN_vkSetPrivateData s_vkSetPrivateData = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
static PFN_vkSetPrivateDataEXT s_vkSetPrivateDataEXT = nullptr;
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
static PFN_vkGetPrivateData s_vkGetPrivateData = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
static PFN_vkGetPrivateDataEXT s_vkGetPrivateDataEXT = nullptr;
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
static PFN_vkCmdCopyBuffer2 s_vkCmdCopyBuffer2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
static PFN_vkCmdCopyBuffer2KHR s_vkCmdCopyBuffer2KHR = nullptr;
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdCopyImage2 s_vkCmdCopyImage2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
static PFN_vkCmdCopyImage2KHR s_vkCmdCopyImage2KHR = nullptr;
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdBlitImage2 s_vkCmdBlitImage2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
static PFN_vkCmdBlitImage2KHR s_vkCmdBlitImage2KHR = nullptr;
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdCopyBufferToImage2 s_vkCmdCopyBufferToImage2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
static PFN_vkCmdCopyBufferToImage2KHR s_vkCmdCopyBufferToImage2KHR = nullptr;
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdCopyImageToBuffer2 s_vkCmdCopyImageToBuffer2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
static PFN_vkCmdCopyImageToBuffer2KHR s_vkCmdCopyImageToBuffer2KHR = nullptr;
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdResolveImage2 s_vkCmdResolveImage2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
static PFN_vkCmdResolveImage2KHR s_vkCmdResolveImage2KHR = nullptr;
#endif // VK_KHR_copy_commands2

#if defined(VK_KHR_fragment_shading_rate)
static PFN_vkCmdSetFragmentShadingRateKHR s_vkCmdSetFragmentShadingRateKHR = nullptr;
static PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR s_vkGetPhysicalDeviceFragmentShadingRatesKHR = nullptr;
#endif // VK_KHR_fragment_shading_rate

#if defined(VK_NV_fragment_shading_rate_enums)
static PFN_vkCmdSetFragmentShadingRateEnumNV s_vkCmdSetFragmentShadingRateEnumNV = nullptr;
#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_acceleration_structure)
static PFN_vkGetAccelerationStructureBuildSizesKHR s_vkGetAccelerationStructureBuildSizesKHR = nullptr;
#endif // VK_KHR_acceleration_structure

#if defined(VK_EXT_vertex_input_dynamic_state) || defined(VK_EXT_shader_object)
static PFN_vkCmdSetVertexInputEXT s_vkCmdSetVertexInputEXT = nullptr;
#endif // VK_EXT_vertex_input_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_color_write_enable)
static PFN_vkCmdSetColorWriteEnableEXT s_vkCmdSetColorWriteEnableEXT = nullptr;
#endif // VK_EXT_color_write_enable

#if defined(VK_VERSION_1_3)
static PFN_vkCmdSetEvent2 s_vkCmdSetEvent2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
static PFN_vkCmdSetEvent2KHR s_vkCmdSetEvent2KHR = nullptr;
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdResetEvent2 s_vkCmdResetEvent2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
static PFN_vkCmdResetEvent2KHR s_vkCmdResetEvent2KHR = nullptr;
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdWaitEvents2 s_vkCmdWaitEvents2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
static PFN_vkCmdWaitEvents2KHR s_vkCmdWaitEvents2KHR = nullptr;
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdPipelineBarrier2 s_vkCmdPipelineBarrier2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
static PFN_vkCmdPipelineBarrier2KHR s_vkCmdPipelineBarrier2KHR = nullptr;
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
static PFN_vkQueueSubmit2 s_vkQueueSubmit2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
static PFN_vkQueueSubmit2KHR s_vkQueueSubmit2KHR = nullptr;
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
static PFN_vkCmdWriteTimestamp2 s_vkCmdWriteTimestamp2 = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
static PFN_vkCmdWriteTimestamp2KHR s_vkCmdWriteTimestamp2KHR = nullptr;
static PFN_vkCmdWriteBufferMarker2AMD s_vkCmdWriteBufferMarker2AMD = nullptr;
static PFN_vkGetQueueCheckpointData2NV s_vkGetQueueCheckpointData2NV = nullptr;
#endif // VK_KHR_synchronization2

#if defined(VKSC_VERSION_1_0)
static PFN_vkGetCommandPoolMemoryConsumption s_vkGetCommandPoolMemoryConsumption = nullptr;
#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_video_queue)
static PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR s_vkGetPhysicalDeviceVideoCapabilitiesKHR = nullptr;
static PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR s_vkGetPhysicalDeviceVideoFormatPropertiesKHR = nullptr;
static PFN_vkCreateVideoSessionKHR s_vkCreateVideoSessionKHR = nullptr;
static PFN_vkDestroyVideoSessionKHR s_vkDestroyVideoSessionKHR = nullptr;
static PFN_vkCreateVideoSessionParametersKHR s_vkCreateVideoSessionParametersKHR = nullptr;
static PFN_vkUpdateVideoSessionParametersKHR s_vkUpdateVideoSessionParametersKHR = nullptr;
static PFN_vkDestroyVideoSessionParametersKHR s_vkDestroyVideoSessionParametersKHR = nullptr;
static PFN_vkGetVideoSessionMemoryRequirementsKHR s_vkGetVideoSessionMemoryRequirementsKHR = nullptr;
static PFN_vkBindVideoSessionMemoryKHR s_vkBindVideoSessionMemoryKHR = nullptr;
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
static PFN_vkCmdDecodeVideoKHR s_vkCmdDecodeVideoKHR = nullptr;
#endif // VK_KHR_video_decode_queue

#if defined(VK_KHR_video_queue)
static PFN_vkCmdBeginVideoCodingKHR s_vkCmdBeginVideoCodingKHR = nullptr;
static PFN_vkCmdControlVideoCodingKHR s_vkCmdControlVideoCodingKHR = nullptr;
static PFN_vkCmdEndVideoCodingKHR s_vkCmdEndVideoCodingKHR = nullptr;
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_encode_queue)
static PFN_vkCmdEncodeVideoKHR s_vkCmdEncodeVideoKHR = nullptr;
#endif // VK_KHR_video_encode_queue

#if defined(VK_NV_memory_decompression)
static PFN_vkCmdDecompressMemoryNV s_vkCmdDecompressMemoryNV = nullptr;
static PFN_vkCmdDecompressMemoryIndirectCountNV s_vkCmdDecompressMemoryIndirectCountNV = nullptr;
#endif // VK_NV_memory_decompression

#if defined(VK_NVX_binary_import)
static PFN_vkCreateCuModuleNVX s_vkCreateCuModuleNVX = nullptr;
static PFN_vkCreateCuFunctionNVX s_vkCreateCuFunctionNVX = nullptr;
static PFN_vkDestroyCuModuleNVX s_vkDestroyCuModuleNVX = nullptr;
static PFN_vkDestroyCuFunctionNVX s_vkDestroyCuFunctionNVX = nullptr;
static PFN_vkCmdCuLaunchKernelNVX s_vkCmdCuLaunchKernelNVX = nullptr;
#endif // VK_NVX_binary_import

#if defined(VK_EXT_descriptor_buffer)
static PFN_vkGetDescriptorSetLayoutSizeEXT s_vkGetDescriptorSetLayoutSizeEXT = nullptr;
static PFN_vkGetDescriptorSetLayoutBindingOffsetEXT s_vkGetDescriptorSetLayoutBindingOffsetEXT = nullptr;
static PFN_vkGetDescriptorEXT s_vkGetDescriptorEXT = nullptr;
static PFN_vkCmdBindDescriptorBuffersEXT s_vkCmdBindDescriptorBuffersEXT = nullptr;
static PFN_vkCmdSetDescriptorBufferOffsetsEXT s_vkCmdSetDescriptorBufferOffsetsEXT = nullptr;
static PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT s_vkCmdBindDescriptorBufferEmbeddedSamplersEXT = nullptr;
static PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT s_vkGetBufferOpaqueCaptureDescriptorDataEXT = nullptr;
static PFN_vkGetImageOpaqueCaptureDescriptorDataEXT s_vkGetImageOpaqueCaptureDescriptorDataEXT = nullptr;
static PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT s_vkGetImageViewOpaqueCaptureDescriptorDataEXT = nullptr;
static PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT s_vkGetSamplerOpaqueCaptureDescriptorDataEXT = nullptr;
static PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT s_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = nullptr;
#endif // VK_EXT_descriptor_buffer

#if defined(VK_EXT_pageable_device_local_memory)
static PFN_vkSetDeviceMemoryPriorityEXT s_vkSetDeviceMemoryPriorityEXT = nullptr;
#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_present_wait)
static PFN_vkWaitForPresentKHR s_vkWaitForPresentKHR = nullptr;
#endif // VK_KHR_present_wait

#if defined(VK_VERSION_1_3)
static PFN_vkCmdBeginRendering s_vkCmdBeginRendering = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
static PFN_vkCmdBeginRenderingKHR s_vkCmdBeginRenderingKHR = nullptr;
#endif // VK_KHR_dynamic_rendering

#if defined(VK_VERSION_1_3)
static PFN_vkCmdEndRendering s_vkCmdEndRendering = nullptr;
#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
static PFN_vkCmdEndRenderingKHR s_vkCmdEndRenderingKHR = nullptr;
#endif // VK_KHR_dynamic_rendering

#if defined(VK_EXT_opacity_micromap)
static PFN_vkCreateMicromapEXT s_vkCreateMicromapEXT = nullptr;
static PFN_vkCmdBuildMicromapsEXT s_vkCmdBuildMicromapsEXT = nullptr;
static PFN_vkBuildMicromapsEXT s_vkBuildMicromapsEXT = nullptr;
static PFN_vkDestroyMicromapEXT s_vkDestroyMicromapEXT = nullptr;
static PFN_vkCmdCopyMicromapEXT s_vkCmdCopyMicromapEXT = nullptr;
static PFN_vkCopyMicromapEXT s_vkCopyMicromapEXT = nullptr;
static PFN_vkCmdCopyMicromapToMemoryEXT s_vkCmdCopyMicromapToMemoryEXT = nullptr;
static PFN_vkCopyMicromapToMemoryEXT s_vkCopyMicromapToMemoryEXT = nullptr;
static PFN_vkCmdCopyMemoryToMicromapEXT s_vkCmdCopyMemoryToMicromapEXT = nullptr;
static PFN_vkCopyMemoryToMicromapEXT s_vkCopyMemoryToMicromapEXT = nullptr;
static PFN_vkCmdWriteMicromapsPropertiesEXT s_vkCmdWriteMicromapsPropertiesEXT = nullptr;
static PFN_vkWriteMicromapsPropertiesEXT s_vkWriteMicromapsPropertiesEXT = nullptr;
static PFN_vkGetDeviceMicromapCompatibilityEXT s_vkGetDeviceMicromapCompatibilityEXT = nullptr;
static PFN_vkGetMicromapBuildSizesEXT s_vkGetMicromapBuildSizesEXT = nullptr;
#endif // VK_EXT_opacity_micromap

#if defined(VK_EXT_shader_module_identifier)
static PFN_vkGetShaderModuleIdentifierEXT s_vkGetShaderModuleIdentifierEXT = nullptr;
static PFN_vkGetShaderModuleCreateInfoIdentifierEXT s_vkGetShaderModuleCreateInfoIdentifierEXT = nullptr;
#endif // VK_EXT_shader_module_identifier

#if defined(VK_EXT_image_compression_control)
static PFN_vkGetImageSubresourceLayout2EXT s_vkGetImageSubresourceLayout2EXT = nullptr;
#endif // VK_EXT_image_compression_control

#if defined(VK_EXT_device_fault)
static PFN_vkGetDeviceFaultInfoEXT s_vkGetDeviceFaultInfoEXT = nullptr;
#endif // VK_EXT_device_fault

#if defined(VK_EXT_swapchain_maintenance1)
static PFN_vkReleaseSwapchainImagesEXT s_vkReleaseSwapchainImagesEXT = nullptr;
#endif // VK_EXT_swapchain_maintenance1

#if defined(VK_KHR_map_memory2)
static PFN_vkMapMemory2KHR s_vkMapMemory2KHR = nullptr;
static PFN_vkUnmapMemory2KHR s_vkUnmapMemory2KHR = nullptr;
#endif // VK_KHR_map_memory2

#if defined(VK_EXT_shader_object)
static PFN_vkCreateShadersEXT s_vkCreateShadersEXT = nullptr;
static PFN_vkDestroyShaderEXT s_vkDestroyShaderEXT = nullptr;
static PFN_vkGetShaderBinaryDataEXT s_vkGetShaderBinaryDataEXT = nullptr;
static PFN_vkCmdBindShadersEXT s_vkCmdBindShadersEXT = nullptr;
#endif // VK_EXT_shader_object

#if defined(VK_NV_external_memory_sci_buf)
static PFN_vkGetMemorySciBufNV s_vkGetMemorySciBufNV = nullptr;
static PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV s_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV = nullptr;
static PFN_vkGetPhysicalDeviceSciBufAttributesNV s_vkGetPhysicalDeviceSciBufAttributesNV = nullptr;
#endif // VK_NV_external_memory_sci_buf

// Dispatch macros

#if defined(VK_VERSION_1_0)
#ifndef VKCREATEINSTANCE_PRE
#define VKCREATEINSTANCE_PRE(...)
#endif
#ifndef VKCREATEINSTANCE
#define VKCREATEINSTANCE(pCreateInfo, pAllocator, pInstance) VkResult result = s_vkCreateInstance(pCreateInfo, pAllocator, pInstance)
#endif
#ifndef VKCREATEINSTANCE_POST
#define VKCREATEINSTANCE_POST(...) return result
#endif

#ifndef VKDESTROYINSTANCE_PRE
#define VKDESTROYINSTANCE_PRE(...)
#endif
#ifndef VKDESTROYINSTANCE
#define VKDESTROYINSTANCE(instance, pAllocator) s_vkDestroyInstance(instance, pAllocator)
#endif
#ifndef VKDESTROYINSTANCE_POST
#define VKDESTROYINSTANCE_POST(...)
#endif

#ifndef VKENUMERATEPHYSICALDEVICES_PRE
#define VKENUMERATEPHYSICALDEVICES_PRE(...)
#endif
#ifndef VKENUMERATEPHYSICALDEVICES
#define VKENUMERATEPHYSICALDEVICES(instance, pPhysicalDeviceCount, pPhysicalDevices) VkResult result = s_vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices)
#endif
#ifndef VKENUMERATEPHYSICALDEVICES_POST
#define VKENUMERATEPHYSICALDEVICES_POST(...) return result
#endif

#ifndef VKGETDEVICEPROCADDR_PRE
#define VKGETDEVICEPROCADDR_PRE(...)
#endif
#ifndef VKGETDEVICEPROCADDR
#define VKGETDEVICEPROCADDR(device, pName) PFN_vkVoidFunction result = s_vkGetDeviceProcAddr(device, pName)
#endif
#ifndef VKGETDEVICEPROCADDR_POST
#define VKGETDEVICEPROCADDR_POST(...) return result
#endif

#ifndef VKGETINSTANCEPROCADDR_PRE
#define VKGETINSTANCEPROCADDR_PRE(...)
#endif
#ifndef VKGETINSTANCEPROCADDR
#define VKGETINSTANCEPROCADDR(instance, pName) PFN_vkVoidFunction result = s_vkGetInstanceProcAddr(instance, pName)
#endif
#ifndef VKGETINSTANCEPROCADDR_POST
#define VKGETINSTANCEPROCADDR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEPROPERTIES_PRE
#define VKGETPHYSICALDEVICEPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEPROPERTIES
#define VKGETPHYSICALDEVICEPROPERTIES(physicalDevice, pProperties) s_vkGetPhysicalDeviceProperties(physicalDevice, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEPROPERTIES_POST
#define VKGETPHYSICALDEVICEPROPERTIES_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES_PRE
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties) s_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties)
#endif
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES_POST
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES_PRE
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES(physicalDevice, pMemoryProperties) s_vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties)
#endif
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES_POST
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEFEATURES_PRE
#define VKGETPHYSICALDEVICEFEATURES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFEATURES
#define VKGETPHYSICALDEVICEFEATURES(physicalDevice, pFeatures) s_vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures)
#endif
#ifndef VKGETPHYSICALDEVICEFEATURES_POST
#define VKGETPHYSICALDEVICEFEATURES_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES_PRE
#define VKGETPHYSICALDEVICEFORMATPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES
#define VKGETPHYSICALDEVICEFORMATPROPERTIES(physicalDevice, format, pFormatProperties) s_vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES_POST
#define VKGETPHYSICALDEVICEFORMATPROPERTIES_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES_PRE
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties) VkResult result = s_vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES_POST
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES_POST(...) return result
#endif

#ifndef VKCREATEDEVICE_PRE
#define VKCREATEDEVICE_PRE(...)
#endif
#ifndef VKCREATEDEVICE
#define VKCREATEDEVICE(physicalDevice, pCreateInfo, pAllocator, pDevice) VkResult result = s_vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice)
#endif
#ifndef VKCREATEDEVICE_POST
#define VKCREATEDEVICE_POST(...) return result
#endif

#ifndef VKDESTROYDEVICE_PRE
#define VKDESTROYDEVICE_PRE(...)
#endif
#ifndef VKDESTROYDEVICE
#define VKDESTROYDEVICE(device, pAllocator) s_vkDestroyDevice(device, pAllocator)
#endif
#ifndef VKDESTROYDEVICE_POST
#define VKDESTROYDEVICE_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_1)
#ifndef VKENUMERATEINSTANCEVERSION_PRE
#define VKENUMERATEINSTANCEVERSION_PRE(...)
#endif
#ifndef VKENUMERATEINSTANCEVERSION
#define VKENUMERATEINSTANCEVERSION(pApiVersion) VkResult result = s_vkEnumerateInstanceVersion(pApiVersion)
#endif
#ifndef VKENUMERATEINSTANCEVERSION_POST
#define VKENUMERATEINSTANCEVERSION_POST(...) return result
#endif

#endif // VK_VERSION_1_1

#if defined(VK_VERSION_1_0)
#ifndef VKENUMERATEINSTANCELAYERPROPERTIES_PRE
#define VKENUMERATEINSTANCELAYERPROPERTIES_PRE(...)
#endif
#ifndef VKENUMERATEINSTANCELAYERPROPERTIES
#define VKENUMERATEINSTANCELAYERPROPERTIES(pPropertyCount, pProperties) VkResult result = s_vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties)
#endif
#ifndef VKENUMERATEINSTANCELAYERPROPERTIES_POST
#define VKENUMERATEINSTANCELAYERPROPERTIES_POST(...) return result
#endif

#ifndef VKENUMERATEINSTANCEEXTENSIONPROPERTIES_PRE
#define VKENUMERATEINSTANCEEXTENSIONPROPERTIES_PRE(...)
#endif
#ifndef VKENUMERATEINSTANCEEXTENSIONPROPERTIES
#define VKENUMERATEINSTANCEEXTENSIONPROPERTIES(pLayerName, pPropertyCount, pProperties) VkResult result = s_vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties)
#endif
#ifndef VKENUMERATEINSTANCEEXTENSIONPROPERTIES_POST
#define VKENUMERATEINSTANCEEXTENSIONPROPERTIES_POST(...) return result
#endif

#ifndef VKENUMERATEDEVICELAYERPROPERTIES_PRE
#define VKENUMERATEDEVICELAYERPROPERTIES_PRE(...)
#endif
#ifndef VKENUMERATEDEVICELAYERPROPERTIES
#define VKENUMERATEDEVICELAYERPROPERTIES(physicalDevice, pPropertyCount, pProperties) VkResult result = s_vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties)
#endif
#ifndef VKENUMERATEDEVICELAYERPROPERTIES_POST
#define VKENUMERATEDEVICELAYERPROPERTIES_POST(...) return result
#endif

#ifndef VKENUMERATEDEVICEEXTENSIONPROPERTIES_PRE
#define VKENUMERATEDEVICEEXTENSIONPROPERTIES_PRE(...)
#endif
#ifndef VKENUMERATEDEVICEEXTENSIONPROPERTIES
#define VKENUMERATEDEVICEEXTENSIONPROPERTIES(physicalDevice, pLayerName, pPropertyCount, pProperties) VkResult result = s_vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties)
#endif
#ifndef VKENUMERATEDEVICEEXTENSIONPROPERTIES_POST
#define VKENUMERATEDEVICEEXTENSIONPROPERTIES_POST(...) return result
#endif

#ifndef VKGETDEVICEQUEUE_PRE
#define VKGETDEVICEQUEUE_PRE(...)
#endif
#ifndef VKGETDEVICEQUEUE
#define VKGETDEVICEQUEUE(device, queueFamilyIndex, queueIndex, pQueue) s_vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue)
#endif
#ifndef VKGETDEVICEQUEUE_POST
#define VKGETDEVICEQUEUE_POST(...)
#endif

#ifndef VKQUEUESUBMIT_PRE
#define VKQUEUESUBMIT_PRE(...)
#endif
#ifndef VKQUEUESUBMIT
#define VKQUEUESUBMIT(queue, submitCount, pSubmits, fence) VkResult result = s_vkQueueSubmit(queue, submitCount, pSubmits, fence)
#endif
#ifndef VKQUEUESUBMIT_POST
#define VKQUEUESUBMIT_POST(...) return result
#endif

#ifndef VKQUEUEWAITIDLE_PRE
#define VKQUEUEWAITIDLE_PRE(...)
#endif
#ifndef VKQUEUEWAITIDLE
#define VKQUEUEWAITIDLE(queue) VkResult result = s_vkQueueWaitIdle(queue)
#endif
#ifndef VKQUEUEWAITIDLE_POST
#define VKQUEUEWAITIDLE_POST(...) return result
#endif

#ifndef VKDEVICEWAITIDLE_PRE
#define VKDEVICEWAITIDLE_PRE(...)
#endif
#ifndef VKDEVICEWAITIDLE
#define VKDEVICEWAITIDLE(device) VkResult result = s_vkDeviceWaitIdle(device)
#endif
#ifndef VKDEVICEWAITIDLE_POST
#define VKDEVICEWAITIDLE_POST(...) return result
#endif

#ifndef VKALLOCATEMEMORY_PRE
#define VKALLOCATEMEMORY_PRE(...)
#endif
#ifndef VKALLOCATEMEMORY
#define VKALLOCATEMEMORY(device, pAllocateInfo, pAllocator, pMemory) VkResult result = s_vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory)
#endif
#ifndef VKALLOCATEMEMORY_POST
#define VKALLOCATEMEMORY_POST(...) return result
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKFREEMEMORY_PRE
#define VKFREEMEMORY_PRE(...)
#endif
#ifndef VKFREEMEMORY
#define VKFREEMEMORY(device, memory, pAllocator) s_vkFreeMemory(device, memory, pAllocator)
#endif
#ifndef VKFREEMEMORY_POST
#define VKFREEMEMORY_POST(...)
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKMAPMEMORY_PRE
#define VKMAPMEMORY_PRE(...)
#endif
#ifndef VKMAPMEMORY
#define VKMAPMEMORY(device, memory, offset, size, flags, ppData) VkResult result = s_vkMapMemory(device, memory, offset, size, flags, ppData)
#endif
#ifndef VKMAPMEMORY_POST
#define VKMAPMEMORY_POST(...) return result
#endif

#ifndef VKUNMAPMEMORY_PRE
#define VKUNMAPMEMORY_PRE(...)
#endif
#ifndef VKUNMAPMEMORY
#define VKUNMAPMEMORY(device, memory) s_vkUnmapMemory(device, memory)
#endif
#ifndef VKUNMAPMEMORY_POST
#define VKUNMAPMEMORY_POST(...)
#endif

#ifndef VKFLUSHMAPPEDMEMORYRANGES_PRE
#define VKFLUSHMAPPEDMEMORYRANGES_PRE(...)
#endif
#ifndef VKFLUSHMAPPEDMEMORYRANGES
#define VKFLUSHMAPPEDMEMORYRANGES(device, memoryRangeCount, pMemoryRanges) VkResult result = s_vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges)
#endif
#ifndef VKFLUSHMAPPEDMEMORYRANGES_POST
#define VKFLUSHMAPPEDMEMORYRANGES_POST(...) return result
#endif

#ifndef VKINVALIDATEMAPPEDMEMORYRANGES_PRE
#define VKINVALIDATEMAPPEDMEMORYRANGES_PRE(...)
#endif
#ifndef VKINVALIDATEMAPPEDMEMORYRANGES
#define VKINVALIDATEMAPPEDMEMORYRANGES(device, memoryRangeCount, pMemoryRanges) VkResult result = s_vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges)
#endif
#ifndef VKINVALIDATEMAPPEDMEMORYRANGES_POST
#define VKINVALIDATEMAPPEDMEMORYRANGES_POST(...) return result
#endif

#ifndef VKGETDEVICEMEMORYCOMMITMENT_PRE
#define VKGETDEVICEMEMORYCOMMITMENT_PRE(...)
#endif
#ifndef VKGETDEVICEMEMORYCOMMITMENT
#define VKGETDEVICEMEMORYCOMMITMENT(device, memory, pCommittedMemoryInBytes) s_vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes)
#endif
#ifndef VKGETDEVICEMEMORYCOMMITMENT_POST
#define VKGETDEVICEMEMORYCOMMITMENT_POST(...)
#endif

#ifndef VKGETBUFFERMEMORYREQUIREMENTS_PRE
#define VKGETBUFFERMEMORYREQUIREMENTS_PRE(...)
#endif
#ifndef VKGETBUFFERMEMORYREQUIREMENTS
#define VKGETBUFFERMEMORYREQUIREMENTS(device, buffer, pMemoryRequirements) s_vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements)
#endif
#ifndef VKGETBUFFERMEMORYREQUIREMENTS_POST
#define VKGETBUFFERMEMORYREQUIREMENTS_POST(...)
#endif

#ifndef VKBINDBUFFERMEMORY_PRE
#define VKBINDBUFFERMEMORY_PRE(...)
#endif
#ifndef VKBINDBUFFERMEMORY
#define VKBINDBUFFERMEMORY(device, buffer, memory, memoryOffset) VkResult result = s_vkBindBufferMemory(device, buffer, memory, memoryOffset)
#endif
#ifndef VKBINDBUFFERMEMORY_POST
#define VKBINDBUFFERMEMORY_POST(...) return result
#endif

#ifndef VKGETIMAGEMEMORYREQUIREMENTS_PRE
#define VKGETIMAGEMEMORYREQUIREMENTS_PRE(...)
#endif
#ifndef VKGETIMAGEMEMORYREQUIREMENTS
#define VKGETIMAGEMEMORYREQUIREMENTS(device, image, pMemoryRequirements) s_vkGetImageMemoryRequirements(device, image, pMemoryRequirements)
#endif
#ifndef VKGETIMAGEMEMORYREQUIREMENTS_POST
#define VKGETIMAGEMEMORYREQUIREMENTS_POST(...)
#endif

#ifndef VKBINDIMAGEMEMORY_PRE
#define VKBINDIMAGEMEMORY_PRE(...)
#endif
#ifndef VKBINDIMAGEMEMORY
#define VKBINDIMAGEMEMORY(device, image, memory, memoryOffset) VkResult result = s_vkBindImageMemory(device, image, memory, memoryOffset)
#endif
#ifndef VKBINDIMAGEMEMORY_POST
#define VKBINDIMAGEMEMORY_POST(...) return result
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS_PRE
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS_PRE(...)
#endif
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements) s_vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements)
#endif
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS_POST
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES_PRE
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties) s_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES_POST
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES_POST(...)
#endif

#ifndef VKQUEUEBINDSPARSE_PRE
#define VKQUEUEBINDSPARSE_PRE(...)
#endif
#ifndef VKQUEUEBINDSPARSE
#define VKQUEUEBINDSPARSE(queue, bindInfoCount, pBindInfo, fence) VkResult result = s_vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence)
#endif
#ifndef VKQUEUEBINDSPARSE_POST
#define VKQUEUEBINDSPARSE_POST(...) return result
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKCREATEFENCE_PRE
#define VKCREATEFENCE_PRE(...)
#endif
#ifndef VKCREATEFENCE
#define VKCREATEFENCE(device, pCreateInfo, pAllocator, pFence) VkResult result = s_vkCreateFence(device, pCreateInfo, pAllocator, pFence)
#endif
#ifndef VKCREATEFENCE_POST
#define VKCREATEFENCE_POST(...) return result
#endif

#ifndef VKDESTROYFENCE_PRE
#define VKDESTROYFENCE_PRE(...)
#endif
#ifndef VKDESTROYFENCE
#define VKDESTROYFENCE(device, fence, pAllocator) s_vkDestroyFence(device, fence, pAllocator)
#endif
#ifndef VKDESTROYFENCE_POST
#define VKDESTROYFENCE_POST(...)
#endif

#ifndef VKRESETFENCES_PRE
#define VKRESETFENCES_PRE(...)
#endif
#ifndef VKRESETFENCES
#define VKRESETFENCES(device, fenceCount, pFences) VkResult result = s_vkResetFences(device, fenceCount, pFences)
#endif
#ifndef VKRESETFENCES_POST
#define VKRESETFENCES_POST(...) return result
#endif

#ifndef VKGETFENCESTATUS_PRE
#define VKGETFENCESTATUS_PRE(...)
#endif
#ifndef VKGETFENCESTATUS
#define VKGETFENCESTATUS(device, fence) VkResult result = s_vkGetFenceStatus(device, fence)
#endif
#ifndef VKGETFENCESTATUS_POST
#define VKGETFENCESTATUS_POST(...) return result
#endif

#ifndef VKWAITFORFENCES_PRE
#define VKWAITFORFENCES_PRE(...)
#endif
#ifndef VKWAITFORFENCES
#define VKWAITFORFENCES(device, fenceCount, pFences, waitAll, timeout) VkResult result = s_vkWaitForFences(device, fenceCount, pFences, waitAll, timeout)
#endif
#ifndef VKWAITFORFENCES_POST
#define VKWAITFORFENCES_POST(...) return result
#endif

#ifndef VKCREATESEMAPHORE_PRE
#define VKCREATESEMAPHORE_PRE(...)
#endif
#ifndef VKCREATESEMAPHORE
#define VKCREATESEMAPHORE(device, pCreateInfo, pAllocator, pSemaphore) VkResult result = s_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore)
#endif
#ifndef VKCREATESEMAPHORE_POST
#define VKCREATESEMAPHORE_POST(...) return result
#endif

#ifndef VKDESTROYSEMAPHORE_PRE
#define VKDESTROYSEMAPHORE_PRE(...)
#endif
#ifndef VKDESTROYSEMAPHORE
#define VKDESTROYSEMAPHORE(device, semaphore, pAllocator) s_vkDestroySemaphore(device, semaphore, pAllocator)
#endif
#ifndef VKDESTROYSEMAPHORE_POST
#define VKDESTROYSEMAPHORE_POST(...)
#endif

#ifndef VKCREATEEVENT_PRE
#define VKCREATEEVENT_PRE(...)
#endif
#ifndef VKCREATEEVENT
#define VKCREATEEVENT(device, pCreateInfo, pAllocator, pEvent) VkResult result = s_vkCreateEvent(device, pCreateInfo, pAllocator, pEvent)
#endif
#ifndef VKCREATEEVENT_POST
#define VKCREATEEVENT_POST(...) return result
#endif

#ifndef VKDESTROYEVENT_PRE
#define VKDESTROYEVENT_PRE(...)
#endif
#ifndef VKDESTROYEVENT
#define VKDESTROYEVENT(device, event, pAllocator) s_vkDestroyEvent(device, event, pAllocator)
#endif
#ifndef VKDESTROYEVENT_POST
#define VKDESTROYEVENT_POST(...)
#endif

#ifndef VKGETEVENTSTATUS_PRE
#define VKGETEVENTSTATUS_PRE(...)
#endif
#ifndef VKGETEVENTSTATUS
#define VKGETEVENTSTATUS(device, event) VkResult result = s_vkGetEventStatus(device, event)
#endif
#ifndef VKGETEVENTSTATUS_POST
#define VKGETEVENTSTATUS_POST(...) return result
#endif

#ifndef VKSETEVENT_PRE
#define VKSETEVENT_PRE(...)
#endif
#ifndef VKSETEVENT
#define VKSETEVENT(device, event) VkResult result = s_vkSetEvent(device, event)
#endif
#ifndef VKSETEVENT_POST
#define VKSETEVENT_POST(...) return result
#endif

#ifndef VKRESETEVENT_PRE
#define VKRESETEVENT_PRE(...)
#endif
#ifndef VKRESETEVENT
#define VKRESETEVENT(device, event) VkResult result = s_vkResetEvent(device, event)
#endif
#ifndef VKRESETEVENT_POST
#define VKRESETEVENT_POST(...) return result
#endif

#ifndef VKCREATEQUERYPOOL_PRE
#define VKCREATEQUERYPOOL_PRE(...)
#endif
#ifndef VKCREATEQUERYPOOL
#define VKCREATEQUERYPOOL(device, pCreateInfo, pAllocator, pQueryPool) VkResult result = s_vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool)
#endif
#ifndef VKCREATEQUERYPOOL_POST
#define VKCREATEQUERYPOOL_POST(...) return result
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKDESTROYQUERYPOOL_PRE
#define VKDESTROYQUERYPOOL_PRE(...)
#endif
#ifndef VKDESTROYQUERYPOOL
#define VKDESTROYQUERYPOOL(device, queryPool, pAllocator) s_vkDestroyQueryPool(device, queryPool, pAllocator)
#endif
#ifndef VKDESTROYQUERYPOOL_POST
#define VKDESTROYQUERYPOOL_POST(...)
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKGETQUERYPOOLRESULTS_PRE
#define VKGETQUERYPOOLRESULTS_PRE(...)
#endif
#ifndef VKGETQUERYPOOLRESULTS
#define VKGETQUERYPOOLRESULTS(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags) VkResult result = s_vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags)
#endif
#ifndef VKGETQUERYPOOLRESULTS_POST
#define VKGETQUERYPOOLRESULTS_POST(...) return result
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_2)
#ifndef VKRESETQUERYPOOL_PRE
#define VKRESETQUERYPOOL_PRE(...)
#endif
#ifndef VKRESETQUERYPOOL
#define VKRESETQUERYPOOL(device, queryPool, firstQuery, queryCount) s_vkResetQueryPool(device, queryPool, firstQuery, queryCount)
#endif
#ifndef VKRESETQUERYPOOL_POST
#define VKRESETQUERYPOOL_POST(...)
#endif

#endif // VK_VERSION_1_2

#if defined(VK_EXT_host_query_reset)
#ifndef VKRESETQUERYPOOLEXT_PRE
#define VKRESETQUERYPOOLEXT_PRE(...)
#endif
#ifndef VKRESETQUERYPOOLEXT
#define VKRESETQUERYPOOLEXT(device, queryPool, firstQuery, queryCount) s_vkResetQueryPoolEXT(device, queryPool, firstQuery, queryCount)
#endif
#ifndef VKRESETQUERYPOOLEXT_POST
#define VKRESETQUERYPOOLEXT_POST(...)
#endif

#endif // VK_EXT_host_query_reset

#if defined(VK_VERSION_1_0)
#ifndef VKCREATEBUFFER_PRE
#define VKCREATEBUFFER_PRE(...)
#endif
#ifndef VKCREATEBUFFER
#define VKCREATEBUFFER(device, pCreateInfo, pAllocator, pBuffer) VkResult result = s_vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer)
#endif
#ifndef VKCREATEBUFFER_POST
#define VKCREATEBUFFER_POST(...) return result
#endif

#ifndef VKDESTROYBUFFER_PRE
#define VKDESTROYBUFFER_PRE(...)
#endif
#ifndef VKDESTROYBUFFER
#define VKDESTROYBUFFER(device, buffer, pAllocator) s_vkDestroyBuffer(device, buffer, pAllocator)
#endif
#ifndef VKDESTROYBUFFER_POST
#define VKDESTROYBUFFER_POST(...)
#endif

#ifndef VKCREATEBUFFERVIEW_PRE
#define VKCREATEBUFFERVIEW_PRE(...)
#endif
#ifndef VKCREATEBUFFERVIEW
#define VKCREATEBUFFERVIEW(device, pCreateInfo, pAllocator, pView) VkResult result = s_vkCreateBufferView(device, pCreateInfo, pAllocator, pView)
#endif
#ifndef VKCREATEBUFFERVIEW_POST
#define VKCREATEBUFFERVIEW_POST(...) return result
#endif

#ifndef VKDESTROYBUFFERVIEW_PRE
#define VKDESTROYBUFFERVIEW_PRE(...)
#endif
#ifndef VKDESTROYBUFFERVIEW
#define VKDESTROYBUFFERVIEW(device, bufferView, pAllocator) s_vkDestroyBufferView(device, bufferView, pAllocator)
#endif
#ifndef VKDESTROYBUFFERVIEW_POST
#define VKDESTROYBUFFERVIEW_POST(...)
#endif

#ifndef VKCREATEIMAGE_PRE
#define VKCREATEIMAGE_PRE(...)
#endif
#ifndef VKCREATEIMAGE
#define VKCREATEIMAGE(device, pCreateInfo, pAllocator, pImage) VkResult result = s_vkCreateImage(device, pCreateInfo, pAllocator, pImage)
#endif
#ifndef VKCREATEIMAGE_POST
#define VKCREATEIMAGE_POST(...) return result
#endif

#ifndef VKDESTROYIMAGE_PRE
#define VKDESTROYIMAGE_PRE(...)
#endif
#ifndef VKDESTROYIMAGE
#define VKDESTROYIMAGE(device, image, pAllocator) s_vkDestroyImage(device, image, pAllocator)
#endif
#ifndef VKDESTROYIMAGE_POST
#define VKDESTROYIMAGE_POST(...)
#endif

#ifndef VKGETIMAGESUBRESOURCELAYOUT_PRE
#define VKGETIMAGESUBRESOURCELAYOUT_PRE(...)
#endif
#ifndef VKGETIMAGESUBRESOURCELAYOUT
#define VKGETIMAGESUBRESOURCELAYOUT(device, image, pSubresource, pLayout) s_vkGetImageSubresourceLayout(device, image, pSubresource, pLayout)
#endif
#ifndef VKGETIMAGESUBRESOURCELAYOUT_POST
#define VKGETIMAGESUBRESOURCELAYOUT_POST(...)
#endif

#ifndef VKCREATEIMAGEVIEW_PRE
#define VKCREATEIMAGEVIEW_PRE(...)
#endif
#ifndef VKCREATEIMAGEVIEW
#define VKCREATEIMAGEVIEW(device, pCreateInfo, pAllocator, pView) VkResult result = s_vkCreateImageView(device, pCreateInfo, pAllocator, pView)
#endif
#ifndef VKCREATEIMAGEVIEW_POST
#define VKCREATEIMAGEVIEW_POST(...) return result
#endif

#ifndef VKDESTROYIMAGEVIEW_PRE
#define VKDESTROYIMAGEVIEW_PRE(...)
#endif
#ifndef VKDESTROYIMAGEVIEW
#define VKDESTROYIMAGEVIEW(device, imageView, pAllocator) s_vkDestroyImageView(device, imageView, pAllocator)
#endif
#ifndef VKDESTROYIMAGEVIEW_POST
#define VKDESTROYIMAGEVIEW_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKCREATESHADERMODULE_PRE
#define VKCREATESHADERMODULE_PRE(...)
#endif
#ifndef VKCREATESHADERMODULE
#define VKCREATESHADERMODULE(device, pCreateInfo, pAllocator, pShaderModule) VkResult result = s_vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule)
#endif
#ifndef VKCREATESHADERMODULE_POST
#define VKCREATESHADERMODULE_POST(...) return result
#endif

#ifndef VKDESTROYSHADERMODULE_PRE
#define VKDESTROYSHADERMODULE_PRE(...)
#endif
#ifndef VKDESTROYSHADERMODULE
#define VKDESTROYSHADERMODULE(device, shaderModule, pAllocator) s_vkDestroyShaderModule(device, shaderModule, pAllocator)
#endif
#ifndef VKDESTROYSHADERMODULE_POST
#define VKDESTROYSHADERMODULE_POST(...)
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKCREATEPIPELINECACHE_PRE
#define VKCREATEPIPELINECACHE_PRE(...)
#endif
#ifndef VKCREATEPIPELINECACHE
#define VKCREATEPIPELINECACHE(device, pCreateInfo, pAllocator, pPipelineCache) VkResult result = s_vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache)
#endif
#ifndef VKCREATEPIPELINECACHE_POST
#define VKCREATEPIPELINECACHE_POST(...) return result
#endif

#ifndef VKDESTROYPIPELINECACHE_PRE
#define VKDESTROYPIPELINECACHE_PRE(...)
#endif
#ifndef VKDESTROYPIPELINECACHE
#define VKDESTROYPIPELINECACHE(device, pipelineCache, pAllocator) s_vkDestroyPipelineCache(device, pipelineCache, pAllocator)
#endif
#ifndef VKDESTROYPIPELINECACHE_POST
#define VKDESTROYPIPELINECACHE_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKGETPIPELINECACHEDATA_PRE
#define VKGETPIPELINECACHEDATA_PRE(...)
#endif
#ifndef VKGETPIPELINECACHEDATA
#define VKGETPIPELINECACHEDATA(device, pipelineCache, pDataSize, pData) VkResult result = s_vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData)
#endif
#ifndef VKGETPIPELINECACHEDATA_POST
#define VKGETPIPELINECACHEDATA_POST(...) return result
#endif

#ifndef VKMERGEPIPELINECACHES_PRE
#define VKMERGEPIPELINECACHES_PRE(...)
#endif
#ifndef VKMERGEPIPELINECACHES
#define VKMERGEPIPELINECACHES(device, dstCache, srcCacheCount, pSrcCaches) VkResult result = s_vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches)
#endif
#ifndef VKMERGEPIPELINECACHES_POST
#define VKMERGEPIPELINECACHES_POST(...) return result
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKCREATEGRAPHICSPIPELINES_PRE
#define VKCREATEGRAPHICSPIPELINES_PRE(...)
#endif
#ifndef VKCREATEGRAPHICSPIPELINES
#define VKCREATEGRAPHICSPIPELINES(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines) VkResult result = s_vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines)
#endif
#ifndef VKCREATEGRAPHICSPIPELINES_POST
#define VKCREATEGRAPHICSPIPELINES_POST(...) return result
#endif

#ifndef VKCREATECOMPUTEPIPELINES_PRE
#define VKCREATECOMPUTEPIPELINES_PRE(...)
#endif
#ifndef VKCREATECOMPUTEPIPELINES
#define VKCREATECOMPUTEPIPELINES(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines) VkResult result = s_vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines)
#endif
#ifndef VKCREATECOMPUTEPIPELINES_POST
#define VKCREATECOMPUTEPIPELINES_POST(...) return result
#endif

#ifndef VKDESTROYPIPELINE_PRE
#define VKDESTROYPIPELINE_PRE(...)
#endif
#ifndef VKDESTROYPIPELINE
#define VKDESTROYPIPELINE(device, pipeline, pAllocator) s_vkDestroyPipeline(device, pipeline, pAllocator)
#endif
#ifndef VKDESTROYPIPELINE_POST
#define VKDESTROYPIPELINE_POST(...)
#endif

#ifndef VKCREATEPIPELINELAYOUT_PRE
#define VKCREATEPIPELINELAYOUT_PRE(...)
#endif
#ifndef VKCREATEPIPELINELAYOUT
#define VKCREATEPIPELINELAYOUT(device, pCreateInfo, pAllocator, pPipelineLayout) VkResult result = s_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout)
#endif
#ifndef VKCREATEPIPELINELAYOUT_POST
#define VKCREATEPIPELINELAYOUT_POST(...) return result
#endif

#ifndef VKDESTROYPIPELINELAYOUT_PRE
#define VKDESTROYPIPELINELAYOUT_PRE(...)
#endif
#ifndef VKDESTROYPIPELINELAYOUT
#define VKDESTROYPIPELINELAYOUT(device, pipelineLayout, pAllocator) s_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator)
#endif
#ifndef VKDESTROYPIPELINELAYOUT_POST
#define VKDESTROYPIPELINELAYOUT_POST(...)
#endif

#ifndef VKCREATESAMPLER_PRE
#define VKCREATESAMPLER_PRE(...)
#endif
#ifndef VKCREATESAMPLER
#define VKCREATESAMPLER(device, pCreateInfo, pAllocator, pSampler) VkResult result = s_vkCreateSampler(device, pCreateInfo, pAllocator, pSampler)
#endif
#ifndef VKCREATESAMPLER_POST
#define VKCREATESAMPLER_POST(...) return result
#endif

#ifndef VKDESTROYSAMPLER_PRE
#define VKDESTROYSAMPLER_PRE(...)
#endif
#ifndef VKDESTROYSAMPLER
#define VKDESTROYSAMPLER(device, sampler, pAllocator) s_vkDestroySampler(device, sampler, pAllocator)
#endif
#ifndef VKDESTROYSAMPLER_POST
#define VKDESTROYSAMPLER_POST(...)
#endif

#ifndef VKCREATEDESCRIPTORSETLAYOUT_PRE
#define VKCREATEDESCRIPTORSETLAYOUT_PRE(...)
#endif
#ifndef VKCREATEDESCRIPTORSETLAYOUT
#define VKCREATEDESCRIPTORSETLAYOUT(device, pCreateInfo, pAllocator, pSetLayout) VkResult result = s_vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout)
#endif
#ifndef VKCREATEDESCRIPTORSETLAYOUT_POST
#define VKCREATEDESCRIPTORSETLAYOUT_POST(...) return result
#endif

#ifndef VKDESTROYDESCRIPTORSETLAYOUT_PRE
#define VKDESTROYDESCRIPTORSETLAYOUT_PRE(...)
#endif
#ifndef VKDESTROYDESCRIPTORSETLAYOUT
#define VKDESTROYDESCRIPTORSETLAYOUT(device, descriptorSetLayout, pAllocator) s_vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator)
#endif
#ifndef VKDESTROYDESCRIPTORSETLAYOUT_POST
#define VKDESTROYDESCRIPTORSETLAYOUT_POST(...)
#endif

#ifndef VKCREATEDESCRIPTORPOOL_PRE
#define VKCREATEDESCRIPTORPOOL_PRE(...)
#endif
#ifndef VKCREATEDESCRIPTORPOOL
#define VKCREATEDESCRIPTORPOOL(device, pCreateInfo, pAllocator, pDescriptorPool) VkResult result = s_vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool)
#endif
#ifndef VKCREATEDESCRIPTORPOOL_POST
#define VKCREATEDESCRIPTORPOOL_POST(...) return result
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKDESTROYDESCRIPTORPOOL_PRE
#define VKDESTROYDESCRIPTORPOOL_PRE(...)
#endif
#ifndef VKDESTROYDESCRIPTORPOOL
#define VKDESTROYDESCRIPTORPOOL(device, descriptorPool, pAllocator) s_vkDestroyDescriptorPool(device, descriptorPool, pAllocator)
#endif
#ifndef VKDESTROYDESCRIPTORPOOL_POST
#define VKDESTROYDESCRIPTORPOOL_POST(...)
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKRESETDESCRIPTORPOOL_PRE
#define VKRESETDESCRIPTORPOOL_PRE(...)
#endif
#ifndef VKRESETDESCRIPTORPOOL
#define VKRESETDESCRIPTORPOOL(device, descriptorPool, flags) VkResult result = s_vkResetDescriptorPool(device, descriptorPool, flags)
#endif
#ifndef VKRESETDESCRIPTORPOOL_POST
#define VKRESETDESCRIPTORPOOL_POST(...) return result
#endif

#ifndef VKALLOCATEDESCRIPTORSETS_PRE
#define VKALLOCATEDESCRIPTORSETS_PRE(...)
#endif
#ifndef VKALLOCATEDESCRIPTORSETS
#define VKALLOCATEDESCRIPTORSETS(device, pAllocateInfo, pDescriptorSets) VkResult result = s_vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets)
#endif
#ifndef VKALLOCATEDESCRIPTORSETS_POST
#define VKALLOCATEDESCRIPTORSETS_POST(...) return result
#endif

#ifndef VKFREEDESCRIPTORSETS_PRE
#define VKFREEDESCRIPTORSETS_PRE(...)
#endif
#ifndef VKFREEDESCRIPTORSETS
#define VKFREEDESCRIPTORSETS(device, descriptorPool, descriptorSetCount, pDescriptorSets) VkResult result = s_vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets)
#endif
#ifndef VKFREEDESCRIPTORSETS_POST
#define VKFREEDESCRIPTORSETS_POST(...) return result
#endif

#ifndef VKUPDATEDESCRIPTORSETS_PRE
#define VKUPDATEDESCRIPTORSETS_PRE(...)
#endif
#ifndef VKUPDATEDESCRIPTORSETS
#define VKUPDATEDESCRIPTORSETS(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies) s_vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies)
#endif
#ifndef VKUPDATEDESCRIPTORSETS_POST
#define VKUPDATEDESCRIPTORSETS_POST(...)
#endif

#ifndef VKCREATEFRAMEBUFFER_PRE
#define VKCREATEFRAMEBUFFER_PRE(...)
#endif
#ifndef VKCREATEFRAMEBUFFER
#define VKCREATEFRAMEBUFFER(device, pCreateInfo, pAllocator, pFramebuffer) VkResult result = s_vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer)
#endif
#ifndef VKCREATEFRAMEBUFFER_POST
#define VKCREATEFRAMEBUFFER_POST(...) return result
#endif

#ifndef VKDESTROYFRAMEBUFFER_PRE
#define VKDESTROYFRAMEBUFFER_PRE(...)
#endif
#ifndef VKDESTROYFRAMEBUFFER
#define VKDESTROYFRAMEBUFFER(device, framebuffer, pAllocator) s_vkDestroyFramebuffer(device, framebuffer, pAllocator)
#endif
#ifndef VKDESTROYFRAMEBUFFER_POST
#define VKDESTROYFRAMEBUFFER_POST(...)
#endif

#ifndef VKCREATERENDERPASS_PRE
#define VKCREATERENDERPASS_PRE(...)
#endif
#ifndef VKCREATERENDERPASS
#define VKCREATERENDERPASS(device, pCreateInfo, pAllocator, pRenderPass) VkResult result = s_vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass)
#endif
#ifndef VKCREATERENDERPASS_POST
#define VKCREATERENDERPASS_POST(...) return result
#endif

#ifndef VKDESTROYRENDERPASS_PRE
#define VKDESTROYRENDERPASS_PRE(...)
#endif
#ifndef VKDESTROYRENDERPASS
#define VKDESTROYRENDERPASS(device, renderPass, pAllocator) s_vkDestroyRenderPass(device, renderPass, pAllocator)
#endif
#ifndef VKDESTROYRENDERPASS_POST
#define VKDESTROYRENDERPASS_POST(...)
#endif

#ifndef VKGETRENDERAREAGRANULARITY_PRE
#define VKGETRENDERAREAGRANULARITY_PRE(...)
#endif
#ifndef VKGETRENDERAREAGRANULARITY
#define VKGETRENDERAREAGRANULARITY(device, renderPass, pGranularity) s_vkGetRenderAreaGranularity(device, renderPass, pGranularity)
#endif
#ifndef VKGETRENDERAREAGRANULARITY_POST
#define VKGETRENDERAREAGRANULARITY_POST(...)
#endif

#ifndef VKCREATECOMMANDPOOL_PRE
#define VKCREATECOMMANDPOOL_PRE(...)
#endif
#ifndef VKCREATECOMMANDPOOL
#define VKCREATECOMMANDPOOL(device, pCreateInfo, pAllocator, pCommandPool) VkResult result = s_vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool)
#endif
#ifndef VKCREATECOMMANDPOOL_POST
#define VKCREATECOMMANDPOOL_POST(...) return result
#endif

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
#ifndef VKDESTROYCOMMANDPOOL_PRE
#define VKDESTROYCOMMANDPOOL_PRE(...)
#endif
#ifndef VKDESTROYCOMMANDPOOL
#define VKDESTROYCOMMANDPOOL(device, commandPool, pAllocator) s_vkDestroyCommandPool(device, commandPool, pAllocator)
#endif
#ifndef VKDESTROYCOMMANDPOOL_POST
#define VKDESTROYCOMMANDPOOL_POST(...)
#endif

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
#ifndef VKRESETCOMMANDPOOL_PRE
#define VKRESETCOMMANDPOOL_PRE(...)
#endif
#ifndef VKRESETCOMMANDPOOL
#define VKRESETCOMMANDPOOL(device, commandPool, flags) VkResult result = s_vkResetCommandPool(device, commandPool, flags)
#endif
#ifndef VKRESETCOMMANDPOOL_POST
#define VKRESETCOMMANDPOOL_POST(...) return result
#endif

#ifndef VKALLOCATECOMMANDBUFFERS_PRE
#define VKALLOCATECOMMANDBUFFERS_PRE(...)
#endif
#ifndef VKALLOCATECOMMANDBUFFERS
#define VKALLOCATECOMMANDBUFFERS(device, pAllocateInfo, pCommandBuffers) VkResult result = s_vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers)
#endif
#ifndef VKALLOCATECOMMANDBUFFERS_POST
#define VKALLOCATECOMMANDBUFFERS_POST(...) return result
#endif

#ifndef VKFREECOMMANDBUFFERS_PRE
#define VKFREECOMMANDBUFFERS_PRE(...)
#endif
#ifndef VKFREECOMMANDBUFFERS
#define VKFREECOMMANDBUFFERS(device, commandPool, commandBufferCount, pCommandBuffers) s_vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers)
#endif
#ifndef VKFREECOMMANDBUFFERS_POST
#define VKFREECOMMANDBUFFERS_POST(...)
#endif

#ifndef VKBEGINCOMMANDBUFFER_PRE
#define VKBEGINCOMMANDBUFFER_PRE(...)
#endif
#ifndef VKBEGINCOMMANDBUFFER
#define VKBEGINCOMMANDBUFFER(commandBuffer, pBeginInfo) VkResult result = s_vkBeginCommandBuffer(commandBuffer, pBeginInfo)
#endif
#ifndef VKBEGINCOMMANDBUFFER_POST
#define VKBEGINCOMMANDBUFFER_POST(...) return result
#endif

#ifndef VKENDCOMMANDBUFFER_PRE
#define VKENDCOMMANDBUFFER_PRE(...)
#endif
#ifndef VKENDCOMMANDBUFFER
#define VKENDCOMMANDBUFFER(commandBuffer) VkResult result = s_vkEndCommandBuffer(commandBuffer)
#endif
#ifndef VKENDCOMMANDBUFFER_POST
#define VKENDCOMMANDBUFFER_POST(...) return result
#endif

#ifndef VKRESETCOMMANDBUFFER_PRE
#define VKRESETCOMMANDBUFFER_PRE(...)
#endif
#ifndef VKRESETCOMMANDBUFFER
#define VKRESETCOMMANDBUFFER(commandBuffer, flags) VkResult result = s_vkResetCommandBuffer(commandBuffer, flags)
#endif
#ifndef VKRESETCOMMANDBUFFER_POST
#define VKRESETCOMMANDBUFFER_POST(...) return result
#endif

#ifndef VKCMDBINDPIPELINE_PRE
#define VKCMDBINDPIPELINE_PRE(...)
#endif
#ifndef VKCMDBINDPIPELINE
#define VKCMDBINDPIPELINE(commandBuffer, pipelineBindPoint, pipeline) s_vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline)
#endif
#ifndef VKCMDBINDPIPELINE_POST
#define VKCMDBINDPIPELINE_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
#ifndef VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT_PRE
#define VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT
#define VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT(commandBuffer, aspectMask) s_vkCmdSetAttachmentFeedbackLoopEnableEXT(commandBuffer, aspectMask)
#endif
#ifndef VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT_POST
#define VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT_POST(...)
#endif

#endif // VK_EXT_attachment_feedback_loop_dynamic_state

#if defined(VK_VERSION_1_0)
#ifndef VKCMDSETVIEWPORT_PRE
#define VKCMDSETVIEWPORT_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORT
#define VKCMDSETVIEWPORT(commandBuffer, firstViewport, viewportCount, pViewports) s_vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports)
#endif
#ifndef VKCMDSETVIEWPORT_POST
#define VKCMDSETVIEWPORT_POST(...)
#endif

#ifndef VKCMDSETSCISSOR_PRE
#define VKCMDSETSCISSOR_PRE(...)
#endif
#ifndef VKCMDSETSCISSOR
#define VKCMDSETSCISSOR(commandBuffer, firstScissor, scissorCount, pScissors) s_vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors)
#endif
#ifndef VKCMDSETSCISSOR_POST
#define VKCMDSETSCISSOR_POST(...)
#endif

#ifndef VKCMDSETLINEWIDTH_PRE
#define VKCMDSETLINEWIDTH_PRE(...)
#endif
#ifndef VKCMDSETLINEWIDTH
#define VKCMDSETLINEWIDTH(commandBuffer, lineWidth) s_vkCmdSetLineWidth(commandBuffer, lineWidth)
#endif
#ifndef VKCMDSETLINEWIDTH_POST
#define VKCMDSETLINEWIDTH_POST(...)
#endif

#ifndef VKCMDSETDEPTHBIAS_PRE
#define VKCMDSETDEPTHBIAS_PRE(...)
#endif
#ifndef VKCMDSETDEPTHBIAS
#define VKCMDSETDEPTHBIAS(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor) s_vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor)
#endif
#ifndef VKCMDSETDEPTHBIAS_POST
#define VKCMDSETDEPTHBIAS_POST(...)
#endif

#ifndef VKCMDSETBLENDCONSTANTS_PRE
#define VKCMDSETBLENDCONSTANTS_PRE(...)
#endif
#ifndef VKCMDSETBLENDCONSTANTS
#define VKCMDSETBLENDCONSTANTS(commandBuffer, blendConstants) s_vkCmdSetBlendConstants(commandBuffer, blendConstants)
#endif
#ifndef VKCMDSETBLENDCONSTANTS_POST
#define VKCMDSETBLENDCONSTANTS_POST(...)
#endif

#ifndef VKCMDSETDEPTHBOUNDS_PRE
#define VKCMDSETDEPTHBOUNDS_PRE(...)
#endif
#ifndef VKCMDSETDEPTHBOUNDS
#define VKCMDSETDEPTHBOUNDS(commandBuffer, minDepthBounds, maxDepthBounds) s_vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds)
#endif
#ifndef VKCMDSETDEPTHBOUNDS_POST
#define VKCMDSETDEPTHBOUNDS_POST(...)
#endif

#ifndef VKCMDSETSTENCILCOMPAREMASK_PRE
#define VKCMDSETSTENCILCOMPAREMASK_PRE(...)
#endif
#ifndef VKCMDSETSTENCILCOMPAREMASK
#define VKCMDSETSTENCILCOMPAREMASK(commandBuffer, faceMask, compareMask) s_vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask)
#endif
#ifndef VKCMDSETSTENCILCOMPAREMASK_POST
#define VKCMDSETSTENCILCOMPAREMASK_POST(...)
#endif

#ifndef VKCMDSETSTENCILWRITEMASK_PRE
#define VKCMDSETSTENCILWRITEMASK_PRE(...)
#endif
#ifndef VKCMDSETSTENCILWRITEMASK
#define VKCMDSETSTENCILWRITEMASK(commandBuffer, faceMask, writeMask) s_vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask)
#endif
#ifndef VKCMDSETSTENCILWRITEMASK_POST
#define VKCMDSETSTENCILWRITEMASK_POST(...)
#endif

#ifndef VKCMDSETSTENCILREFERENCE_PRE
#define VKCMDSETSTENCILREFERENCE_PRE(...)
#endif
#ifndef VKCMDSETSTENCILREFERENCE
#define VKCMDSETSTENCILREFERENCE(commandBuffer, faceMask, reference) s_vkCmdSetStencilReference(commandBuffer, faceMask, reference)
#endif
#ifndef VKCMDSETSTENCILREFERENCE_POST
#define VKCMDSETSTENCILREFERENCE_POST(...)
#endif

#ifndef VKCMDBINDDESCRIPTORSETS_PRE
#define VKCMDBINDDESCRIPTORSETS_PRE(...)
#endif
#ifndef VKCMDBINDDESCRIPTORSETS
#define VKCMDBINDDESCRIPTORSETS(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets) s_vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets)
#endif
#ifndef VKCMDBINDDESCRIPTORSETS_POST
#define VKCMDBINDDESCRIPTORSETS_POST(...)
#endif

#ifndef VKCMDBINDINDEXBUFFER_PRE
#define VKCMDBINDINDEXBUFFER_PRE(...)
#endif
#ifndef VKCMDBINDINDEXBUFFER
#define VKCMDBINDINDEXBUFFER(commandBuffer, buffer, offset, indexType) s_vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType)
#endif
#ifndef VKCMDBINDINDEXBUFFER_POST
#define VKCMDBINDINDEXBUFFER_POST(...)
#endif

#ifndef VKCMDBINDVERTEXBUFFERS_PRE
#define VKCMDBINDVERTEXBUFFERS_PRE(...)
#endif
#ifndef VKCMDBINDVERTEXBUFFERS
#define VKCMDBINDVERTEXBUFFERS(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets) s_vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets)
#endif
#ifndef VKCMDBINDVERTEXBUFFERS_POST
#define VKCMDBINDVERTEXBUFFERS_POST(...)
#endif

#ifndef VKCMDDRAW_PRE
#define VKCMDDRAW_PRE(...)
#endif
#ifndef VKCMDDRAW
#define VKCMDDRAW(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance) s_vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance)
#endif
#ifndef VKCMDDRAW_POST
#define VKCMDDRAW_POST(...)
#endif

#ifndef VKCMDDRAWINDEXED_PRE
#define VKCMDDRAWINDEXED_PRE(...)
#endif
#ifndef VKCMDDRAWINDEXED
#define VKCMDDRAWINDEXED(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance) s_vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance)
#endif
#ifndef VKCMDDRAWINDEXED_POST
#define VKCMDDRAWINDEXED_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_EXT_multi_draw)
#ifndef VKCMDDRAWMULTIEXT_PRE
#define VKCMDDRAWMULTIEXT_PRE(...)
#endif
#ifndef VKCMDDRAWMULTIEXT
#define VKCMDDRAWMULTIEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride) s_vkCmdDrawMultiEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride)
#endif
#ifndef VKCMDDRAWMULTIEXT_POST
#define VKCMDDRAWMULTIEXT_POST(...)
#endif

#ifndef VKCMDDRAWMULTIINDEXEDEXT_PRE
#define VKCMDDRAWMULTIINDEXEDEXT_PRE(...)
#endif
#ifndef VKCMDDRAWMULTIINDEXEDEXT
#define VKCMDDRAWMULTIINDEXEDEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset) s_vkCmdDrawMultiIndexedEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset)
#endif
#ifndef VKCMDDRAWMULTIINDEXEDEXT_POST
#define VKCMDDRAWMULTIINDEXEDEXT_POST(...)
#endif

#endif // VK_EXT_multi_draw

#if defined(VK_VERSION_1_0)
#ifndef VKCMDDRAWINDIRECT_PRE
#define VKCMDDRAWINDIRECT_PRE(...)
#endif
#ifndef VKCMDDRAWINDIRECT
#define VKCMDDRAWINDIRECT(commandBuffer, buffer, offset, drawCount, stride) s_vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride)
#endif
#ifndef VKCMDDRAWINDIRECT_POST
#define VKCMDDRAWINDIRECT_POST(...)
#endif

#ifndef VKCMDDRAWINDEXEDINDIRECT_PRE
#define VKCMDDRAWINDEXEDINDIRECT_PRE(...)
#endif
#ifndef VKCMDDRAWINDEXEDINDIRECT
#define VKCMDDRAWINDEXEDINDIRECT(commandBuffer, buffer, offset, drawCount, stride) s_vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride)
#endif
#ifndef VKCMDDRAWINDEXEDINDIRECT_POST
#define VKCMDDRAWINDEXEDINDIRECT_POST(...)
#endif

#ifndef VKCMDDISPATCH_PRE
#define VKCMDDISPATCH_PRE(...)
#endif
#ifndef VKCMDDISPATCH
#define VKCMDDISPATCH(commandBuffer, groupCountX, groupCountY, groupCountZ) s_vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ)
#endif
#ifndef VKCMDDISPATCH_POST
#define VKCMDDISPATCH_POST(...)
#endif

#ifndef VKCMDDISPATCHINDIRECT_PRE
#define VKCMDDISPATCHINDIRECT_PRE(...)
#endif
#ifndef VKCMDDISPATCHINDIRECT
#define VKCMDDISPATCHINDIRECT(commandBuffer, buffer, offset) s_vkCmdDispatchIndirect(commandBuffer, buffer, offset)
#endif
#ifndef VKCMDDISPATCHINDIRECT_POST
#define VKCMDDISPATCHINDIRECT_POST(...)
#endif

#ifndef VKCMDCOPYBUFFER_PRE
#define VKCMDCOPYBUFFER_PRE(...)
#endif
#ifndef VKCMDCOPYBUFFER
#define VKCMDCOPYBUFFER(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions) s_vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions)
#endif
#ifndef VKCMDCOPYBUFFER_POST
#define VKCMDCOPYBUFFER_POST(...)
#endif

#ifndef VKCMDCOPYIMAGE_PRE
#define VKCMDCOPYIMAGE_PRE(...)
#endif
#ifndef VKCMDCOPYIMAGE
#define VKCMDCOPYIMAGE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions) s_vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions)
#endif
#ifndef VKCMDCOPYIMAGE_POST
#define VKCMDCOPYIMAGE_POST(...)
#endif

#ifndef VKCMDBLITIMAGE_PRE
#define VKCMDBLITIMAGE_PRE(...)
#endif
#ifndef VKCMDBLITIMAGE
#define VKCMDBLITIMAGE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter) s_vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter)
#endif
#ifndef VKCMDBLITIMAGE_POST
#define VKCMDBLITIMAGE_POST(...)
#endif

#ifndef VKCMDCOPYBUFFERTOIMAGE_PRE
#define VKCMDCOPYBUFFERTOIMAGE_PRE(...)
#endif
#ifndef VKCMDCOPYBUFFERTOIMAGE
#define VKCMDCOPYBUFFERTOIMAGE(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions) s_vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions)
#endif
#ifndef VKCMDCOPYBUFFERTOIMAGE_POST
#define VKCMDCOPYBUFFERTOIMAGE_POST(...)
#endif

#ifndef VKCMDCOPYIMAGETOBUFFER_PRE
#define VKCMDCOPYIMAGETOBUFFER_PRE(...)
#endif
#ifndef VKCMDCOPYIMAGETOBUFFER
#define VKCMDCOPYIMAGETOBUFFER(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions) s_vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions)
#endif
#ifndef VKCMDCOPYIMAGETOBUFFER_POST
#define VKCMDCOPYIMAGETOBUFFER_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_NV_copy_memory_indirect)
#ifndef VKCMDCOPYMEMORYINDIRECTNV_PRE
#define VKCMDCOPYMEMORYINDIRECTNV_PRE(...)
#endif
#ifndef VKCMDCOPYMEMORYINDIRECTNV
#define VKCMDCOPYMEMORYINDIRECTNV(commandBuffer, copyBufferAddress, copyCount, stride) s_vkCmdCopyMemoryIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride)
#endif
#ifndef VKCMDCOPYMEMORYINDIRECTNV_POST
#define VKCMDCOPYMEMORYINDIRECTNV_POST(...)
#endif

#ifndef VKCMDCOPYMEMORYTOIMAGEINDIRECTNV_PRE
#define VKCMDCOPYMEMORYTOIMAGEINDIRECTNV_PRE(...)
#endif
#ifndef VKCMDCOPYMEMORYTOIMAGEINDIRECTNV
#define VKCMDCOPYMEMORYTOIMAGEINDIRECTNV(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources) s_vkCmdCopyMemoryToImageIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources)
#endif
#ifndef VKCMDCOPYMEMORYTOIMAGEINDIRECTNV_POST
#define VKCMDCOPYMEMORYTOIMAGEINDIRECTNV_POST(...)
#endif

#endif // VK_NV_copy_memory_indirect

#if defined(VK_VERSION_1_0)
#ifndef VKCMDUPDATEBUFFER_PRE
#define VKCMDUPDATEBUFFER_PRE(...)
#endif
#ifndef VKCMDUPDATEBUFFER
#define VKCMDUPDATEBUFFER(commandBuffer, dstBuffer, dstOffset, dataSize, pData) s_vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData)
#endif
#ifndef VKCMDUPDATEBUFFER_POST
#define VKCMDUPDATEBUFFER_POST(...)
#endif

#ifndef VKCMDFILLBUFFER_PRE
#define VKCMDFILLBUFFER_PRE(...)
#endif
#ifndef VKCMDFILLBUFFER
#define VKCMDFILLBUFFER(commandBuffer, dstBuffer, dstOffset, size, data) s_vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data)
#endif
#ifndef VKCMDFILLBUFFER_POST
#define VKCMDFILLBUFFER_POST(...)
#endif

#ifndef VKCMDCLEARCOLORIMAGE_PRE
#define VKCMDCLEARCOLORIMAGE_PRE(...)
#endif
#ifndef VKCMDCLEARCOLORIMAGE
#define VKCMDCLEARCOLORIMAGE(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges) s_vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges)
#endif
#ifndef VKCMDCLEARCOLORIMAGE_POST
#define VKCMDCLEARCOLORIMAGE_POST(...)
#endif

#ifndef VKCMDCLEARDEPTHSTENCILIMAGE_PRE
#define VKCMDCLEARDEPTHSTENCILIMAGE_PRE(...)
#endif
#ifndef VKCMDCLEARDEPTHSTENCILIMAGE
#define VKCMDCLEARDEPTHSTENCILIMAGE(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges) s_vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges)
#endif
#ifndef VKCMDCLEARDEPTHSTENCILIMAGE_POST
#define VKCMDCLEARDEPTHSTENCILIMAGE_POST(...)
#endif

#ifndef VKCMDCLEARATTACHMENTS_PRE
#define VKCMDCLEARATTACHMENTS_PRE(...)
#endif
#ifndef VKCMDCLEARATTACHMENTS
#define VKCMDCLEARATTACHMENTS(commandBuffer, attachmentCount, pAttachments, rectCount, pRects) s_vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects)
#endif
#ifndef VKCMDCLEARATTACHMENTS_POST
#define VKCMDCLEARATTACHMENTS_POST(...)
#endif

#ifndef VKCMDRESOLVEIMAGE_PRE
#define VKCMDRESOLVEIMAGE_PRE(...)
#endif
#ifndef VKCMDRESOLVEIMAGE
#define VKCMDRESOLVEIMAGE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions) s_vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions)
#endif
#ifndef VKCMDRESOLVEIMAGE_POST
#define VKCMDRESOLVEIMAGE_POST(...)
#endif

#ifndef VKCMDSETEVENT_PRE
#define VKCMDSETEVENT_PRE(...)
#endif
#ifndef VKCMDSETEVENT
#define VKCMDSETEVENT(commandBuffer, event, stageMask) s_vkCmdSetEvent(commandBuffer, event, stageMask)
#endif
#ifndef VKCMDSETEVENT_POST
#define VKCMDSETEVENT_POST(...)
#endif

#ifndef VKCMDRESETEVENT_PRE
#define VKCMDRESETEVENT_PRE(...)
#endif
#ifndef VKCMDRESETEVENT
#define VKCMDRESETEVENT(commandBuffer, event, stageMask) s_vkCmdResetEvent(commandBuffer, event, stageMask)
#endif
#ifndef VKCMDRESETEVENT_POST
#define VKCMDRESETEVENT_POST(...)
#endif

#ifndef VKCMDWAITEVENTS_PRE
#define VKCMDWAITEVENTS_PRE(...)
#endif
#ifndef VKCMDWAITEVENTS
#define VKCMDWAITEVENTS(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers) s_vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers)
#endif
#ifndef VKCMDWAITEVENTS_POST
#define VKCMDWAITEVENTS_POST(...)
#endif

#ifndef VKCMDPIPELINEBARRIER_PRE
#define VKCMDPIPELINEBARRIER_PRE(...)
#endif
#ifndef VKCMDPIPELINEBARRIER
#define VKCMDPIPELINEBARRIER(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers) s_vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers)
#endif
#ifndef VKCMDPIPELINEBARRIER_POST
#define VKCMDPIPELINEBARRIER_POST(...)
#endif

#ifndef VKCMDBEGINQUERY_PRE
#define VKCMDBEGINQUERY_PRE(...)
#endif
#ifndef VKCMDBEGINQUERY
#define VKCMDBEGINQUERY(commandBuffer, queryPool, query, flags) s_vkCmdBeginQuery(commandBuffer, queryPool, query, flags)
#endif
#ifndef VKCMDBEGINQUERY_POST
#define VKCMDBEGINQUERY_POST(...)
#endif

#ifndef VKCMDENDQUERY_PRE
#define VKCMDENDQUERY_PRE(...)
#endif
#ifndef VKCMDENDQUERY
#define VKCMDENDQUERY(commandBuffer, queryPool, query) s_vkCmdEndQuery(commandBuffer, queryPool, query)
#endif
#ifndef VKCMDENDQUERY_POST
#define VKCMDENDQUERY_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_EXT_conditional_rendering)
#ifndef VKCMDBEGINCONDITIONALRENDERINGEXT_PRE
#define VKCMDBEGINCONDITIONALRENDERINGEXT_PRE(...)
#endif
#ifndef VKCMDBEGINCONDITIONALRENDERINGEXT
#define VKCMDBEGINCONDITIONALRENDERINGEXT(commandBuffer, pConditionalRenderingBegin) s_vkCmdBeginConditionalRenderingEXT(commandBuffer, pConditionalRenderingBegin)
#endif
#ifndef VKCMDBEGINCONDITIONALRENDERINGEXT_POST
#define VKCMDBEGINCONDITIONALRENDERINGEXT_POST(...)
#endif

#ifndef VKCMDENDCONDITIONALRENDERINGEXT_PRE
#define VKCMDENDCONDITIONALRENDERINGEXT_PRE(...)
#endif
#ifndef VKCMDENDCONDITIONALRENDERINGEXT
#define VKCMDENDCONDITIONALRENDERINGEXT(commandBuffer) s_vkCmdEndConditionalRenderingEXT(commandBuffer)
#endif
#ifndef VKCMDENDCONDITIONALRENDERINGEXT_POST
#define VKCMDENDCONDITIONALRENDERINGEXT_POST(...)
#endif

#endif // VK_EXT_conditional_rendering

#if defined(VK_VERSION_1_0)
#ifndef VKCMDRESETQUERYPOOL_PRE
#define VKCMDRESETQUERYPOOL_PRE(...)
#endif
#ifndef VKCMDRESETQUERYPOOL
#define VKCMDRESETQUERYPOOL(commandBuffer, queryPool, firstQuery, queryCount) s_vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount)
#endif
#ifndef VKCMDRESETQUERYPOOL_POST
#define VKCMDRESETQUERYPOOL_POST(...)
#endif

#ifndef VKCMDWRITETIMESTAMP_PRE
#define VKCMDWRITETIMESTAMP_PRE(...)
#endif
#ifndef VKCMDWRITETIMESTAMP
#define VKCMDWRITETIMESTAMP(commandBuffer, pipelineStage, queryPool, query) s_vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query)
#endif
#ifndef VKCMDWRITETIMESTAMP_POST
#define VKCMDWRITETIMESTAMP_POST(...)
#endif

#ifndef VKCMDCOPYQUERYPOOLRESULTS_PRE
#define VKCMDCOPYQUERYPOOLRESULTS_PRE(...)
#endif
#ifndef VKCMDCOPYQUERYPOOLRESULTS
#define VKCMDCOPYQUERYPOOLRESULTS(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags) s_vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags)
#endif
#ifndef VKCMDCOPYQUERYPOOLRESULTS_POST
#define VKCMDCOPYQUERYPOOLRESULTS_POST(...)
#endif

#ifndef VKCMDPUSHCONSTANTS_PRE
#define VKCMDPUSHCONSTANTS_PRE(...)
#endif
#ifndef VKCMDPUSHCONSTANTS
#define VKCMDPUSHCONSTANTS(commandBuffer, layout, stageFlags, offset, size, pValues) s_vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues)
#endif
#ifndef VKCMDPUSHCONSTANTS_POST
#define VKCMDPUSHCONSTANTS_POST(...)
#endif

#ifndef VKCMDBEGINRENDERPASS_PRE
#define VKCMDBEGINRENDERPASS_PRE(...)
#endif
#ifndef VKCMDBEGINRENDERPASS
#define VKCMDBEGINRENDERPASS(commandBuffer, pRenderPassBegin, contents) s_vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents)
#endif
#ifndef VKCMDBEGINRENDERPASS_POST
#define VKCMDBEGINRENDERPASS_POST(...)
#endif

#ifndef VKCMDNEXTSUBPASS_PRE
#define VKCMDNEXTSUBPASS_PRE(...)
#endif
#ifndef VKCMDNEXTSUBPASS
#define VKCMDNEXTSUBPASS(commandBuffer, contents) s_vkCmdNextSubpass(commandBuffer, contents)
#endif
#ifndef VKCMDNEXTSUBPASS_POST
#define VKCMDNEXTSUBPASS_POST(...)
#endif

#ifndef VKCMDENDRENDERPASS_PRE
#define VKCMDENDRENDERPASS_PRE(...)
#endif
#ifndef VKCMDENDRENDERPASS
#define VKCMDENDRENDERPASS(commandBuffer) s_vkCmdEndRenderPass(commandBuffer)
#endif
#ifndef VKCMDENDRENDERPASS_POST
#define VKCMDENDRENDERPASS_POST(...)
#endif

#ifndef VKCMDEXECUTECOMMANDS_PRE
#define VKCMDEXECUTECOMMANDS_PRE(...)
#endif
#ifndef VKCMDEXECUTECOMMANDS
#define VKCMDEXECUTECOMMANDS(commandBuffer, commandBufferCount, pCommandBuffers) s_vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers)
#endif
#ifndef VKCMDEXECUTECOMMANDS_POST
#define VKCMDEXECUTECOMMANDS_POST(...)
#endif

#endif // VK_VERSION_1_0

#if defined(VK_KHR_android_surface)
#ifndef VKCREATEANDROIDSURFACEKHR_PRE
#define VKCREATEANDROIDSURFACEKHR_PRE(...)
#endif
#ifndef VKCREATEANDROIDSURFACEKHR
#define VKCREATEANDROIDSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateAndroidSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEANDROIDSURFACEKHR_POST
#define VKCREATEANDROIDSURFACEKHR_POST(...) return result
#endif

#endif // VK_KHR_android_surface

#if defined(VK_KHR_display)
#ifndef VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR_PRE
#define VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR
#define VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR(physicalDevice, pPropertyCount, pProperties) VkResult result = s_vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR_POST
#define VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR_PRE
#define VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR
#define VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR(physicalDevice, pPropertyCount, pProperties) VkResult result = s_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR_POST
#define VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR_POST(...) return result
#endif

#ifndef VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR_PRE
#define VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR_PRE(...)
#endif
#ifndef VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR
#define VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays) VkResult result = s_vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays)
#endif
#ifndef VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR_POST
#define VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR_POST(...) return result
#endif

#ifndef VKGETDISPLAYMODEPROPERTIESKHR_PRE
#define VKGETDISPLAYMODEPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETDISPLAYMODEPROPERTIESKHR
#define VKGETDISPLAYMODEPROPERTIESKHR(physicalDevice, display, pPropertyCount, pProperties) VkResult result = s_vkGetDisplayModePropertiesKHR(physicalDevice, display, pPropertyCount, pProperties)
#endif
#ifndef VKGETDISPLAYMODEPROPERTIESKHR_POST
#define VKGETDISPLAYMODEPROPERTIESKHR_POST(...) return result
#endif

#ifndef VKCREATEDISPLAYMODEKHR_PRE
#define VKCREATEDISPLAYMODEKHR_PRE(...)
#endif
#ifndef VKCREATEDISPLAYMODEKHR
#define VKCREATEDISPLAYMODEKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode) VkResult result = s_vkCreateDisplayModeKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode)
#endif
#ifndef VKCREATEDISPLAYMODEKHR_POST
#define VKCREATEDISPLAYMODEKHR_POST(...) return result
#endif

#ifndef VKGETDISPLAYPLANECAPABILITIESKHR_PRE
#define VKGETDISPLAYPLANECAPABILITIESKHR_PRE(...)
#endif
#ifndef VKGETDISPLAYPLANECAPABILITIESKHR
#define VKGETDISPLAYPLANECAPABILITIESKHR(physicalDevice, mode, planeIndex, pCapabilities) VkResult result = s_vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, mode, planeIndex, pCapabilities)
#endif
#ifndef VKGETDISPLAYPLANECAPABILITIESKHR_POST
#define VKGETDISPLAYPLANECAPABILITIESKHR_POST(...) return result
#endif

#ifndef VKCREATEDISPLAYPLANESURFACEKHR_PRE
#define VKCREATEDISPLAYPLANESURFACEKHR_PRE(...)
#endif
#ifndef VKCREATEDISPLAYPLANESURFACEKHR
#define VKCREATEDISPLAYPLANESURFACEKHR(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateDisplayPlaneSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEDISPLAYPLANESURFACEKHR_POST
#define VKCREATEDISPLAYPLANESURFACEKHR_POST(...) return result
#endif

#endif // VK_KHR_display

#if defined(VK_KHR_display_swapchain)
#ifndef VKCREATESHAREDSWAPCHAINSKHR_PRE
#define VKCREATESHAREDSWAPCHAINSKHR_PRE(...)
#endif
#ifndef VKCREATESHAREDSWAPCHAINSKHR
#define VKCREATESHAREDSWAPCHAINSKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains) VkResult result = s_vkCreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains)
#endif
#ifndef VKCREATESHAREDSWAPCHAINSKHR_POST
#define VKCREATESHAREDSWAPCHAINSKHR_POST(...) return result
#endif

#endif // VK_KHR_display_swapchain

#if defined(VK_KHR_surface)
#ifndef VKDESTROYSURFACEKHR_PRE
#define VKDESTROYSURFACEKHR_PRE(...)
#endif
#ifndef VKDESTROYSURFACEKHR
#define VKDESTROYSURFACEKHR(instance, surface, pAllocator) s_vkDestroySurfaceKHR(instance, surface, pAllocator)
#endif
#ifndef VKDESTROYSURFACEKHR_POST
#define VKDESTROYSURFACEKHR_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICESURFACESUPPORTKHR_PRE
#define VKGETPHYSICALDEVICESURFACESUPPORTKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACESUPPORTKHR
#define VKGETPHYSICALDEVICESURFACESUPPORTKHR(physicalDevice, queueFamilyIndex, surface, pSupported) VkResult result = s_vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported)
#endif
#ifndef VKGETPHYSICALDEVICESURFACESUPPORTKHR_POST
#define VKGETPHYSICALDEVICESURFACESUPPORTKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIESKHR_PRE
#define VKGETPHYSICALDEVICESURFACECAPABILITIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIESKHR
#define VKGETPHYSICALDEVICESURFACECAPABILITIESKHR(physicalDevice, surface, pSurfaceCapabilities) VkResult result = s_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities)
#endif
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIESKHR_POST
#define VKGETPHYSICALDEVICESURFACECAPABILITIESKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICESURFACEFORMATSKHR_PRE
#define VKGETPHYSICALDEVICESURFACEFORMATSKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEFORMATSKHR
#define VKGETPHYSICALDEVICESURFACEFORMATSKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats) VkResult result = s_vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEFORMATSKHR_POST
#define VKGETPHYSICALDEVICESURFACEFORMATSKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR_PRE
#define VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR
#define VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR(physicalDevice, surface, pPresentModeCount, pPresentModes) VkResult result = s_vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR_POST
#define VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR_POST(...) return result
#endif

#endif // VK_KHR_surface

#if defined(VK_KHR_swapchain)
#ifndef VKCREATESWAPCHAINKHR_PRE
#define VKCREATESWAPCHAINKHR_PRE(...)
#endif
#ifndef VKCREATESWAPCHAINKHR
#define VKCREATESWAPCHAINKHR(device, pCreateInfo, pAllocator, pSwapchain) VkResult result = s_vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain)
#endif
#ifndef VKCREATESWAPCHAINKHR_POST
#define VKCREATESWAPCHAINKHR_POST(...) return result
#endif

#endif // VK_KHR_swapchain

#if defined(VK_KHR_swapchain) && !defined(VKSC_VERSION_1_0)
#ifndef VKDESTROYSWAPCHAINKHR_PRE
#define VKDESTROYSWAPCHAINKHR_PRE(...)
#endif
#ifndef VKDESTROYSWAPCHAINKHR
#define VKDESTROYSWAPCHAINKHR(device, swapchain, pAllocator) s_vkDestroySwapchainKHR(device, swapchain, pAllocator)
#endif
#ifndef VKDESTROYSWAPCHAINKHR_POST
#define VKDESTROYSWAPCHAINKHR_POST(...)
#endif

#endif // VK_KHR_swapchain && !VKSC_VERSION_1_0

#if defined(VK_KHR_swapchain)
#ifndef VKGETSWAPCHAINIMAGESKHR_PRE
#define VKGETSWAPCHAINIMAGESKHR_PRE(...)
#endif
#ifndef VKGETSWAPCHAINIMAGESKHR
#define VKGETSWAPCHAINIMAGESKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages) VkResult result = s_vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages)
#endif
#ifndef VKGETSWAPCHAINIMAGESKHR_POST
#define VKGETSWAPCHAINIMAGESKHR_POST(...) return result
#endif

#ifndef VKACQUIRENEXTIMAGEKHR_PRE
#define VKACQUIRENEXTIMAGEKHR_PRE(...)
#endif
#ifndef VKACQUIRENEXTIMAGEKHR
#define VKACQUIRENEXTIMAGEKHR(device, swapchain, timeout, semaphore, fence, pImageIndex) VkResult result = s_vkAcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex)
#endif
#ifndef VKACQUIRENEXTIMAGEKHR_POST
#define VKACQUIRENEXTIMAGEKHR_POST(...) return result
#endif

#ifndef VKQUEUEPRESENTKHR_PRE
#define VKQUEUEPRESENTKHR_PRE(...)
#endif
#ifndef VKQUEUEPRESENTKHR
#define VKQUEUEPRESENTKHR(queue, pPresentInfo) VkResult result = s_vkQueuePresentKHR(queue, pPresentInfo)
#endif
#ifndef VKQUEUEPRESENTKHR_POST
#define VKQUEUEPRESENTKHR_POST(...) return result
#endif

#endif // VK_KHR_swapchain

#if defined(VK_KHR_wayland_surface)
#ifndef VKCREATEWAYLANDSURFACEKHR_PRE
#define VKCREATEWAYLANDSURFACEKHR_PRE(...)
#endif
#ifndef VKCREATEWAYLANDSURFACEKHR
#define VKCREATEWAYLANDSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEWAYLANDSURFACEKHR_POST
#define VKCREATEWAYLANDSURFACEKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR_PRE
#define VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR
#define VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex, display) VkBool32 result = s_vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, display)
#endif
#ifndef VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR_POST
#define VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR_POST(...) return result
#endif

#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_win32_surface)
#ifndef VKCREATEWIN32SURFACEKHR_PRE
#define VKCREATEWIN32SURFACEKHR_PRE(...)
#endif
#ifndef VKCREATEWIN32SURFACEKHR
#define VKCREATEWIN32SURFACEKHR(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEWIN32SURFACEKHR_POST
#define VKCREATEWIN32SURFACEKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR_PRE
#define VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR
#define VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex) VkBool32 result = s_vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex)
#endif
#ifndef VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR_POST
#define VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR_POST(...) return result
#endif

#endif // VK_KHR_win32_surface

#if defined(VK_KHR_xlib_surface)
#ifndef VKCREATEXLIBSURFACEKHR_PRE
#define VKCREATEXLIBSURFACEKHR_PRE(...)
#endif
#ifndef VKCREATEXLIBSURFACEKHR
#define VKCREATEXLIBSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEXLIBSURFACEKHR_POST
#define VKCREATEXLIBSURFACEKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR_PRE
#define VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR
#define VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex, dpy, visualID) VkBool32 result = s_vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID)
#endif
#ifndef VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR_POST
#define VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR_POST(...) return result
#endif

#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
#ifndef VKCREATEXCBSURFACEKHR_PRE
#define VKCREATEXCBSURFACEKHR_PRE(...)
#endif
#ifndef VKCREATEXCBSURFACEKHR
#define VKCREATEXCBSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEXCBSURFACEKHR_POST
#define VKCREATEXCBSURFACEKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR_PRE
#define VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR
#define VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex, connection, visual_id) VkBool32 result = s_vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id)
#endif
#ifndef VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR_POST
#define VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR_POST(...) return result
#endif

#endif // VK_KHR_xcb_surface

#if defined(VK_EXT_debug_report)
#ifndef VKCREATEDEBUGREPORTCALLBACKEXT_PRE
#define VKCREATEDEBUGREPORTCALLBACKEXT_PRE(...)
#endif
#ifndef VKCREATEDEBUGREPORTCALLBACKEXT
#define VKCREATEDEBUGREPORTCALLBACKEXT(instance, pCreateInfo, pAllocator, pCallback) VkResult result = s_vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback)
#endif
#ifndef VKCREATEDEBUGREPORTCALLBACKEXT_POST
#define VKCREATEDEBUGREPORTCALLBACKEXT_POST(...) return result
#endif

#ifndef VKDESTROYDEBUGREPORTCALLBACKEXT_PRE
#define VKDESTROYDEBUGREPORTCALLBACKEXT_PRE(...)
#endif
#ifndef VKDESTROYDEBUGREPORTCALLBACKEXT
#define VKDESTROYDEBUGREPORTCALLBACKEXT(instance, callback, pAllocator) s_vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator)
#endif
#ifndef VKDESTROYDEBUGREPORTCALLBACKEXT_POST
#define VKDESTROYDEBUGREPORTCALLBACKEXT_POST(...)
#endif

#ifndef VKDEBUGREPORTMESSAGEEXT_PRE
#define VKDEBUGREPORTMESSAGEEXT_PRE(...)
#endif
#ifndef VKDEBUGREPORTMESSAGEEXT
#define VKDEBUGREPORTMESSAGEEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage) s_vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage)
#endif
#ifndef VKDEBUGREPORTMESSAGEEXT_POST
#define VKDEBUGREPORTMESSAGEEXT_POST(...)
#endif

#endif // VK_EXT_debug_report

#if defined(VK_EXT_debug_marker)
#ifndef VKDEBUGMARKERSETOBJECTNAMEEXT_PRE
#define VKDEBUGMARKERSETOBJECTNAMEEXT_PRE(...)
#endif
#ifndef VKDEBUGMARKERSETOBJECTNAMEEXT
#define VKDEBUGMARKERSETOBJECTNAMEEXT(device, pNameInfo)             \
    VkResult result = VkResult(0);                                   \
    if (s_vkDebugMarkerSetObjectNameEXT)                             \
    {                                                                \
        result = s_vkDebugMarkerSetObjectNameEXT(device, pNameInfo); \
    }
#endif
#ifndef VKDEBUGMARKERSETOBJECTNAMEEXT_POST
#define VKDEBUGMARKERSETOBJECTNAMEEXT_POST(...) return result
#endif

#ifndef VKDEBUGMARKERSETOBJECTTAGEXT_PRE
#define VKDEBUGMARKERSETOBJECTTAGEXT_PRE(...)
#endif
#ifndef VKDEBUGMARKERSETOBJECTTAGEXT
#define VKDEBUGMARKERSETOBJECTTAGEXT(device, pTagInfo)             \
    VkResult result = VkResult(0);                                 \
    if (s_vkDebugMarkerSetObjectTagEXT)                            \
    {                                                              \
        result = s_vkDebugMarkerSetObjectTagEXT(device, pTagInfo); \
    }
#endif
#ifndef VKDEBUGMARKERSETOBJECTTAGEXT_POST
#define VKDEBUGMARKERSETOBJECTTAGEXT_POST(...) return result
#endif

#ifndef VKCMDDEBUGMARKERBEGINEXT_PRE
#define VKCMDDEBUGMARKERBEGINEXT_PRE(...)
#endif
#ifndef VKCMDDEBUGMARKERBEGINEXT
#define VKCMDDEBUGMARKERBEGINEXT(commandBuffer, pMarkerInfo)    \
    if (s_vkCmdDebugMarkerBeginEXT)                             \
    {                                                           \
        s_vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo); \
    }
#endif
#ifndef VKCMDDEBUGMARKERBEGINEXT_POST
#define VKCMDDEBUGMARKERBEGINEXT_POST(...)
#endif

#ifndef VKCMDDEBUGMARKERENDEXT_PRE
#define VKCMDDEBUGMARKERENDEXT_PRE(...)
#endif
#ifndef VKCMDDEBUGMARKERENDEXT
#define VKCMDDEBUGMARKERENDEXT(commandBuffer)    \
    if (s_vkCmdDebugMarkerEndEXT)                \
    {                                            \
        s_vkCmdDebugMarkerEndEXT(commandBuffer); \
    }
#endif
#ifndef VKCMDDEBUGMARKERENDEXT_POST
#define VKCMDDEBUGMARKERENDEXT_POST(...)
#endif

#ifndef VKCMDDEBUGMARKERINSERTEXT_PRE
#define VKCMDDEBUGMARKERINSERTEXT_PRE(...)
#endif
#ifndef VKCMDDEBUGMARKERINSERTEXT
#define VKCMDDEBUGMARKERINSERTEXT(commandBuffer, pMarkerInfo)    \
    if (s_vkCmdDebugMarkerInsertEXT)                             \
    {                                                            \
        s_vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo); \
    }
#endif
#ifndef VKCMDDEBUGMARKERINSERTEXT_POST
#define VKCMDDEBUGMARKERINSERTEXT_POST(...)
#endif

#endif // VK_EXT_debug_marker

#if defined(VK_NV_external_memory_capabilities)
#ifndef VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV_PRE
#define VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV
#define VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties) VkResult result = s_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV_POST
#define VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV_POST(...) return result
#endif

#endif // VK_NV_external_memory_capabilities

#if defined(VK_NV_external_memory_win32)
#ifndef VKGETMEMORYWIN32HANDLENV_PRE
#define VKGETMEMORYWIN32HANDLENV_PRE(...)
#endif
#ifndef VKGETMEMORYWIN32HANDLENV
#define VKGETMEMORYWIN32HANDLENV(device, memory, handleType, pHandle) VkResult result = s_vkGetMemoryWin32HandleNV(device, memory, handleType, pHandle)
#endif
#ifndef VKGETMEMORYWIN32HANDLENV_POST
#define VKGETMEMORYWIN32HANDLENV_POST(...) return result
#endif

#endif // VK_NV_external_memory_win32

#if defined(VK_NV_device_generated_commands)
#ifndef VKCMDEXECUTEGENERATEDCOMMANDSNV_PRE
#define VKCMDEXECUTEGENERATEDCOMMANDSNV_PRE(...)
#endif
#ifndef VKCMDEXECUTEGENERATEDCOMMANDSNV
#define VKCMDEXECUTEGENERATEDCOMMANDSNV(commandBuffer, isPreprocessed, pGeneratedCommandsInfo) s_vkCmdExecuteGeneratedCommandsNV(commandBuffer, isPreprocessed, pGeneratedCommandsInfo)
#endif
#ifndef VKCMDEXECUTEGENERATEDCOMMANDSNV_POST
#define VKCMDEXECUTEGENERATEDCOMMANDSNV_POST(...)
#endif

#ifndef VKCMDPREPROCESSGENERATEDCOMMANDSNV_PRE
#define VKCMDPREPROCESSGENERATEDCOMMANDSNV_PRE(...)
#endif
#ifndef VKCMDPREPROCESSGENERATEDCOMMANDSNV
#define VKCMDPREPROCESSGENERATEDCOMMANDSNV(commandBuffer, pGeneratedCommandsInfo) s_vkCmdPreprocessGeneratedCommandsNV(commandBuffer, pGeneratedCommandsInfo)
#endif
#ifndef VKCMDPREPROCESSGENERATEDCOMMANDSNV_POST
#define VKCMDPREPROCESSGENERATEDCOMMANDSNV_POST(...)
#endif

#ifndef VKCMDBINDPIPELINESHADERGROUPNV_PRE
#define VKCMDBINDPIPELINESHADERGROUPNV_PRE(...)
#endif
#ifndef VKCMDBINDPIPELINESHADERGROUPNV
#define VKCMDBINDPIPELINESHADERGROUPNV(commandBuffer, pipelineBindPoint, pipeline, groupIndex) s_vkCmdBindPipelineShaderGroupNV(commandBuffer, pipelineBindPoint, pipeline, groupIndex)
#endif
#ifndef VKCMDBINDPIPELINESHADERGROUPNV_POST
#define VKCMDBINDPIPELINESHADERGROUPNV_POST(...)
#endif

#ifndef VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV_PRE
#define VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV_PRE(...)
#endif
#ifndef VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV
#define VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV(device, pInfo, pMemoryRequirements) s_vkGetGeneratedCommandsMemoryRequirementsNV(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV_POST
#define VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV_POST(...)
#endif

#ifndef VKCREATEINDIRECTCOMMANDSLAYOUTNV_PRE
#define VKCREATEINDIRECTCOMMANDSLAYOUTNV_PRE(...)
#endif
#ifndef VKCREATEINDIRECTCOMMANDSLAYOUTNV
#define VKCREATEINDIRECTCOMMANDSLAYOUTNV(device, pCreateInfo, pAllocator, pIndirectCommandsLayout) VkResult result = s_vkCreateIndirectCommandsLayoutNV(device, pCreateInfo, pAllocator, pIndirectCommandsLayout)
#endif
#ifndef VKCREATEINDIRECTCOMMANDSLAYOUTNV_POST
#define VKCREATEINDIRECTCOMMANDSLAYOUTNV_POST(...) return result
#endif

#ifndef VKDESTROYINDIRECTCOMMANDSLAYOUTNV_PRE
#define VKDESTROYINDIRECTCOMMANDSLAYOUTNV_PRE(...)
#endif
#ifndef VKDESTROYINDIRECTCOMMANDSLAYOUTNV
#define VKDESTROYINDIRECTCOMMANDSLAYOUTNV(device, indirectCommandsLayout, pAllocator) s_vkDestroyIndirectCommandsLayoutNV(device, indirectCommandsLayout, pAllocator)
#endif
#ifndef VKDESTROYINDIRECTCOMMANDSLAYOUTNV_POST
#define VKDESTROYINDIRECTCOMMANDSLAYOUTNV_POST(...)
#endif

#endif // VK_NV_device_generated_commands

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEFEATURES2_PRE
#define VKGETPHYSICALDEVICEFEATURES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFEATURES2
#define VKGETPHYSICALDEVICEFEATURES2(physicalDevice, pFeatures) s_vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures)
#endif
#ifndef VKGETPHYSICALDEVICEFEATURES2_POST
#define VKGETPHYSICALDEVICEFEATURES2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICEFEATURES2KHR_PRE
#define VKGETPHYSICALDEVICEFEATURES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFEATURES2KHR
#define VKGETPHYSICALDEVICEFEATURES2KHR(physicalDevice, pFeatures) s_vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures)
#endif
#ifndef VKGETPHYSICALDEVICEFEATURES2KHR_POST
#define VKGETPHYSICALDEVICEFEATURES2KHR_POST(...)
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEPROPERTIES2_PRE
#define VKGETPHYSICALDEVICEPROPERTIES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEPROPERTIES2
#define VKGETPHYSICALDEVICEPROPERTIES2(physicalDevice, pProperties) s_vkGetPhysicalDeviceProperties2(physicalDevice, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEPROPERTIES2_POST
#define VKGETPHYSICALDEVICEPROPERTIES2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICEPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEPROPERTIES2KHR
#define VKGETPHYSICALDEVICEPROPERTIES2KHR(physicalDevice, pProperties) s_vkGetPhysicalDeviceProperties2KHR(physicalDevice, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEPROPERTIES2KHR_POST(...)
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES2_PRE
#define VKGETPHYSICALDEVICEFORMATPROPERTIES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES2
#define VKGETPHYSICALDEVICEFORMATPROPERTIES2(physicalDevice, format, pFormatProperties) s_vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES2_POST
#define VKGETPHYSICALDEVICEFORMATPROPERTIES2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR
#define VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR(physicalDevice, format, pFormatProperties) s_vkGetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR_POST(...)
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2_PRE
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2(physicalDevice, pImageFormatInfo, pImageFormatProperties) VkResult result = s_vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2_POST
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2_POST(...) return result
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties) VkResult result = s_vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR_POST(...) return result
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2_PRE
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties) s_vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties)
#endif
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2_POST
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties) s_vkGetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties)
#endif
#ifndef VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR_POST(...)
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES2_PRE
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES2
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES2(physicalDevice, pMemoryProperties) s_vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties)
#endif
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES2_POST
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR(physicalDevice, pMemoryProperties) s_vkGetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties)
#endif
#ifndef VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR_POST(...)
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2_PRE
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2(physicalDevice, pFormatInfo, pPropertyCount, pProperties) s_vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2_POST
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2_POST(...)
#endif

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_physical_device_properties2)
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties) s_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR_POST(...)
#endif

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_KHR_push_descriptor)
#ifndef VKCMDPUSHDESCRIPTORSETKHR_PRE
#define VKCMDPUSHDESCRIPTORSETKHR_PRE(...)
#endif
#ifndef VKCMDPUSHDESCRIPTORSETKHR
#define VKCMDPUSHDESCRIPTORSETKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites) s_vkCmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites)
#endif
#ifndef VKCMDPUSHDESCRIPTORSETKHR_POST
#define VKCMDPUSHDESCRIPTORSETKHR_POST(...)
#endif

#endif // VK_KHR_push_descriptor

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
#ifndef VKTRIMCOMMANDPOOL_PRE
#define VKTRIMCOMMANDPOOL_PRE(...)
#endif
#ifndef VKTRIMCOMMANDPOOL
#define VKTRIMCOMMANDPOOL(device, commandPool, flags) s_vkTrimCommandPool(device, commandPool, flags)
#endif
#ifndef VKTRIMCOMMANDPOOL_POST
#define VKTRIMCOMMANDPOOL_POST(...)
#endif

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_maintenance1) && !defined(VKSC_VERSION_1_0)
#ifndef VKTRIMCOMMANDPOOLKHR_PRE
#define VKTRIMCOMMANDPOOLKHR_PRE(...)
#endif
#ifndef VKTRIMCOMMANDPOOLKHR
#define VKTRIMCOMMANDPOOLKHR(device, commandPool, flags) s_vkTrimCommandPoolKHR(device, commandPool, flags)
#endif
#ifndef VKTRIMCOMMANDPOOLKHR_POST
#define VKTRIMCOMMANDPOOLKHR_POST(...)
#endif

#endif // VK_KHR_maintenance1 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES_PRE
#define VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES
#define VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES(physicalDevice, pExternalBufferInfo, pExternalBufferProperties) s_vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES_POST
#define VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_memory_capabilities)
#ifndef VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR_PRE
#define VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR
#define VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties) s_vkGetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR_POST
#define VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR_POST(...)
#endif

#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_memory_win32)
#ifndef VKGETMEMORYWIN32HANDLEKHR_PRE
#define VKGETMEMORYWIN32HANDLEKHR_PRE(...)
#endif
#ifndef VKGETMEMORYWIN32HANDLEKHR
#define VKGETMEMORYWIN32HANDLEKHR(device, pGetWin32HandleInfo, pHandle) VkResult result = s_vkGetMemoryWin32HandleKHR(device, pGetWin32HandleInfo, pHandle)
#endif
#ifndef VKGETMEMORYWIN32HANDLEKHR_POST
#define VKGETMEMORYWIN32HANDLEKHR_POST(...) return result
#endif

#ifndef VKGETMEMORYWIN32HANDLEPROPERTIESKHR_PRE
#define VKGETMEMORYWIN32HANDLEPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETMEMORYWIN32HANDLEPROPERTIESKHR
#define VKGETMEMORYWIN32HANDLEPROPERTIESKHR(device, handleType, handle, pMemoryWin32HandleProperties) VkResult result = s_vkGetMemoryWin32HandlePropertiesKHR(device, handleType, handle, pMemoryWin32HandleProperties)
#endif
#ifndef VKGETMEMORYWIN32HANDLEPROPERTIESKHR_POST
#define VKGETMEMORYWIN32HANDLEPROPERTIESKHR_POST(...) return result
#endif

#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
#ifndef VKGETMEMORYFDKHR_PRE
#define VKGETMEMORYFDKHR_PRE(...)
#endif
#ifndef VKGETMEMORYFDKHR
#define VKGETMEMORYFDKHR(device, pGetFdInfo, pFd) VkResult result = s_vkGetMemoryFdKHR(device, pGetFdInfo, pFd)
#endif
#ifndef VKGETMEMORYFDKHR_POST
#define VKGETMEMORYFDKHR_POST(...) return result
#endif

#ifndef VKGETMEMORYFDPROPERTIESKHR_PRE
#define VKGETMEMORYFDPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETMEMORYFDPROPERTIESKHR
#define VKGETMEMORYFDPROPERTIESKHR(device, handleType, fd, pMemoryFdProperties) VkResult result = s_vkGetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties)
#endif
#ifndef VKGETMEMORYFDPROPERTIESKHR_POST
#define VKGETMEMORYFDPROPERTIESKHR_POST(...) return result
#endif

#endif // VK_KHR_external_memory_fd

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES_PRE
#define VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES
#define VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties) s_vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES_POST
#define VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_semaphore_capabilities)
#ifndef VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR_PRE
#define VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR
#define VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties) s_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR_POST
#define VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR_POST(...)
#endif

#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_KHR_external_semaphore_win32)
#ifndef VKGETSEMAPHOREWIN32HANDLEKHR_PRE
#define VKGETSEMAPHOREWIN32HANDLEKHR_PRE(...)
#endif
#ifndef VKGETSEMAPHOREWIN32HANDLEKHR
#define VKGETSEMAPHOREWIN32HANDLEKHR(device, pGetWin32HandleInfo, pHandle) VkResult result = s_vkGetSemaphoreWin32HandleKHR(device, pGetWin32HandleInfo, pHandle)
#endif
#ifndef VKGETSEMAPHOREWIN32HANDLEKHR_POST
#define VKGETSEMAPHOREWIN32HANDLEKHR_POST(...) return result
#endif

#ifndef VKIMPORTSEMAPHOREWIN32HANDLEKHR_PRE
#define VKIMPORTSEMAPHOREWIN32HANDLEKHR_PRE(...)
#endif
#ifndef VKIMPORTSEMAPHOREWIN32HANDLEKHR
#define VKIMPORTSEMAPHOREWIN32HANDLEKHR(device, pImportSemaphoreWin32HandleInfo) VkResult result = s_vkImportSemaphoreWin32HandleKHR(device, pImportSemaphoreWin32HandleInfo)
#endif
#ifndef VKIMPORTSEMAPHOREWIN32HANDLEKHR_POST
#define VKIMPORTSEMAPHOREWIN32HANDLEKHR_POST(...) return result
#endif

#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
#ifndef VKGETSEMAPHOREFDKHR_PRE
#define VKGETSEMAPHOREFDKHR_PRE(...)
#endif
#ifndef VKGETSEMAPHOREFDKHR
#define VKGETSEMAPHOREFDKHR(device, pGetFdInfo, pFd) VkResult result = s_vkGetSemaphoreFdKHR(device, pGetFdInfo, pFd)
#endif
#ifndef VKGETSEMAPHOREFDKHR_POST
#define VKGETSEMAPHOREFDKHR_POST(...) return result
#endif

#ifndef VKIMPORTSEMAPHOREFDKHR_PRE
#define VKIMPORTSEMAPHOREFDKHR_PRE(...)
#endif
#ifndef VKIMPORTSEMAPHOREFDKHR
#define VKIMPORTSEMAPHOREFDKHR(device, pImportSemaphoreFdInfo) VkResult result = s_vkImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo)
#endif
#ifndef VKIMPORTSEMAPHOREFDKHR_POST
#define VKIMPORTSEMAPHOREFDKHR_POST(...) return result
#endif

#endif // VK_KHR_external_semaphore_fd

#if defined(VK_VERSION_1_1)
#ifndef VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES_PRE
#define VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES
#define VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES(physicalDevice, pExternalFenceInfo, pExternalFenceProperties) s_vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES_POST
#define VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_fence_capabilities)
#ifndef VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR_PRE
#define VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR
#define VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties) s_vkGetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR_POST
#define VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR_POST(...)
#endif

#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_external_fence_win32)
#ifndef VKGETFENCEWIN32HANDLEKHR_PRE
#define VKGETFENCEWIN32HANDLEKHR_PRE(...)
#endif
#ifndef VKGETFENCEWIN32HANDLEKHR
#define VKGETFENCEWIN32HANDLEKHR(device, pGetWin32HandleInfo, pHandle) VkResult result = s_vkGetFenceWin32HandleKHR(device, pGetWin32HandleInfo, pHandle)
#endif
#ifndef VKGETFENCEWIN32HANDLEKHR_POST
#define VKGETFENCEWIN32HANDLEKHR_POST(...) return result
#endif

#ifndef VKIMPORTFENCEWIN32HANDLEKHR_PRE
#define VKIMPORTFENCEWIN32HANDLEKHR_PRE(...)
#endif
#ifndef VKIMPORTFENCEWIN32HANDLEKHR
#define VKIMPORTFENCEWIN32HANDLEKHR(device, pImportFenceWin32HandleInfo) VkResult result = s_vkImportFenceWin32HandleKHR(device, pImportFenceWin32HandleInfo)
#endif
#ifndef VKIMPORTFENCEWIN32HANDLEKHR_POST
#define VKIMPORTFENCEWIN32HANDLEKHR_POST(...) return result
#endif

#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
#ifndef VKGETFENCEFDKHR_PRE
#define VKGETFENCEFDKHR_PRE(...)
#endif
#ifndef VKGETFENCEFDKHR
#define VKGETFENCEFDKHR(device, pGetFdInfo, pFd) VkResult result = s_vkGetFenceFdKHR(device, pGetFdInfo, pFd)
#endif
#ifndef VKGETFENCEFDKHR_POST
#define VKGETFENCEFDKHR_POST(...) return result
#endif

#ifndef VKIMPORTFENCEFDKHR_PRE
#define VKIMPORTFENCEFDKHR_PRE(...)
#endif
#ifndef VKIMPORTFENCEFDKHR
#define VKIMPORTFENCEFDKHR(device, pImportFenceFdInfo) VkResult result = s_vkImportFenceFdKHR(device, pImportFenceFdInfo)
#endif
#ifndef VKIMPORTFENCEFDKHR_POST
#define VKIMPORTFENCEFDKHR_POST(...) return result
#endif

#endif // VK_KHR_external_fence_fd

#if defined(VK_EXT_direct_mode_display)
#ifndef VKRELEASEDISPLAYEXT_PRE
#define VKRELEASEDISPLAYEXT_PRE(...)
#endif
#ifndef VKRELEASEDISPLAYEXT
#define VKRELEASEDISPLAYEXT(physicalDevice, display) VkResult result = s_vkReleaseDisplayEXT(physicalDevice, display)
#endif
#ifndef VKRELEASEDISPLAYEXT_POST
#define VKRELEASEDISPLAYEXT_POST(...) return result
#endif

#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
#ifndef VKACQUIREXLIBDISPLAYEXT_PRE
#define VKACQUIREXLIBDISPLAYEXT_PRE(...)
#endif
#ifndef VKACQUIREXLIBDISPLAYEXT
#define VKACQUIREXLIBDISPLAYEXT(physicalDevice, dpy, display) VkResult result = s_vkAcquireXlibDisplayEXT(physicalDevice, dpy, display)
#endif
#ifndef VKACQUIREXLIBDISPLAYEXT_POST
#define VKACQUIREXLIBDISPLAYEXT_POST(...) return result
#endif

#ifndef VKGETRANDROUTPUTDISPLAYEXT_PRE
#define VKGETRANDROUTPUTDISPLAYEXT_PRE(...)
#endif
#ifndef VKGETRANDROUTPUTDISPLAYEXT
#define VKGETRANDROUTPUTDISPLAYEXT(physicalDevice, dpy, rrOutput, pDisplay) VkResult result = s_vkGetRandROutputDisplayEXT(physicalDevice, dpy, rrOutput, pDisplay)
#endif
#ifndef VKGETRANDROUTPUTDISPLAYEXT_POST
#define VKGETRANDROUTPUTDISPLAYEXT_POST(...) return result
#endif

#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT_PRE
#define VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT
#define VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT(physicalDevice, surface, pSurfaceCapabilities) VkResult result = s_vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surface, pSurfaceCapabilities)
#endif
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT_POST
#define VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT_POST(...) return result
#endif

#endif // VK_EXT_display_surface_counter

#if defined(VK_VERSION_1_1)
#ifndef VKENUMERATEPHYSICALDEVICEGROUPS_PRE
#define VKENUMERATEPHYSICALDEVICEGROUPS_PRE(...)
#endif
#ifndef VKENUMERATEPHYSICALDEVICEGROUPS
#define VKENUMERATEPHYSICALDEVICEGROUPS(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties) VkResult result = s_vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties)
#endif
#ifndef VKENUMERATEPHYSICALDEVICEGROUPS_POST
#define VKENUMERATEPHYSICALDEVICEGROUPS_POST(...) return result
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group_creation)
#ifndef VKENUMERATEPHYSICALDEVICEGROUPSKHR_PRE
#define VKENUMERATEPHYSICALDEVICEGROUPSKHR_PRE(...)
#endif
#ifndef VKENUMERATEPHYSICALDEVICEGROUPSKHR
#define VKENUMERATEPHYSICALDEVICEGROUPSKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties) VkResult result = s_vkEnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties)
#endif
#ifndef VKENUMERATEPHYSICALDEVICEGROUPSKHR_POST
#define VKENUMERATEPHYSICALDEVICEGROUPSKHR_POST(...) return result
#endif

#endif // VK_KHR_device_group_creation

#if defined(VK_VERSION_1_1)
#ifndef VKGETDEVICEGROUPPEERMEMORYFEATURES_PRE
#define VKGETDEVICEGROUPPEERMEMORYFEATURES_PRE(...)
#endif
#ifndef VKGETDEVICEGROUPPEERMEMORYFEATURES
#define VKGETDEVICEGROUPPEERMEMORYFEATURES(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures) s_vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures)
#endif
#ifndef VKGETDEVICEGROUPPEERMEMORYFEATURES_POST
#define VKGETDEVICEGROUPPEERMEMORYFEATURES_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
#ifndef VKGETDEVICEGROUPPEERMEMORYFEATURESKHR_PRE
#define VKGETDEVICEGROUPPEERMEMORYFEATURESKHR_PRE(...)
#endif
#ifndef VKGETDEVICEGROUPPEERMEMORYFEATURESKHR
#define VKGETDEVICEGROUPPEERMEMORYFEATURESKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures) s_vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures)
#endif
#ifndef VKGETDEVICEGROUPPEERMEMORYFEATURESKHR_POST
#define VKGETDEVICEGROUPPEERMEMORYFEATURESKHR_POST(...)
#endif

#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1)
#ifndef VKBINDBUFFERMEMORY2_PRE
#define VKBINDBUFFERMEMORY2_PRE(...)
#endif
#ifndef VKBINDBUFFERMEMORY2
#define VKBINDBUFFERMEMORY2(device, bindInfoCount, pBindInfos) VkResult result = s_vkBindBufferMemory2(device, bindInfoCount, pBindInfos)
#endif
#ifndef VKBINDBUFFERMEMORY2_POST
#define VKBINDBUFFERMEMORY2_POST(...) return result
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
#ifndef VKBINDBUFFERMEMORY2KHR_PRE
#define VKBINDBUFFERMEMORY2KHR_PRE(...)
#endif
#ifndef VKBINDBUFFERMEMORY2KHR
#define VKBINDBUFFERMEMORY2KHR(device, bindInfoCount, pBindInfos) VkResult result = s_vkBindBufferMemory2KHR(device, bindInfoCount, pBindInfos)
#endif
#ifndef VKBINDBUFFERMEMORY2KHR_POST
#define VKBINDBUFFERMEMORY2KHR_POST(...) return result
#endif

#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
#ifndef VKBINDIMAGEMEMORY2_PRE
#define VKBINDIMAGEMEMORY2_PRE(...)
#endif
#ifndef VKBINDIMAGEMEMORY2
#define VKBINDIMAGEMEMORY2(device, bindInfoCount, pBindInfos) VkResult result = s_vkBindImageMemory2(device, bindInfoCount, pBindInfos)
#endif
#ifndef VKBINDIMAGEMEMORY2_POST
#define VKBINDIMAGEMEMORY2_POST(...) return result
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
#ifndef VKBINDIMAGEMEMORY2KHR_PRE
#define VKBINDIMAGEMEMORY2KHR_PRE(...)
#endif
#ifndef VKBINDIMAGEMEMORY2KHR
#define VKBINDIMAGEMEMORY2KHR(device, bindInfoCount, pBindInfos) VkResult result = s_vkBindImageMemory2KHR(device, bindInfoCount, pBindInfos)
#endif
#ifndef VKBINDIMAGEMEMORY2KHR_POST
#define VKBINDIMAGEMEMORY2KHR_POST(...) return result
#endif

#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
#ifndef VKCMDSETDEVICEMASK_PRE
#define VKCMDSETDEVICEMASK_PRE(...)
#endif
#ifndef VKCMDSETDEVICEMASK
#define VKCMDSETDEVICEMASK(commandBuffer, deviceMask) s_vkCmdSetDeviceMask(commandBuffer, deviceMask)
#endif
#ifndef VKCMDSETDEVICEMASK_POST
#define VKCMDSETDEVICEMASK_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
#ifndef VKCMDSETDEVICEMASKKHR_PRE
#define VKCMDSETDEVICEMASKKHR_PRE(...)
#endif
#ifndef VKCMDSETDEVICEMASKKHR
#define VKCMDSETDEVICEMASKKHR(commandBuffer, deviceMask) s_vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask)
#endif
#ifndef VKCMDSETDEVICEMASKKHR_POST
#define VKCMDSETDEVICEMASKKHR_POST(...)
#endif

#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
#ifndef VKGETDEVICEGROUPPRESENTCAPABILITIESKHR_PRE
#define VKGETDEVICEGROUPPRESENTCAPABILITIESKHR_PRE(...)
#endif
#ifndef VKGETDEVICEGROUPPRESENTCAPABILITIESKHR
#define VKGETDEVICEGROUPPRESENTCAPABILITIESKHR(device, pDeviceGroupPresentCapabilities) VkResult result = s_vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities)
#endif
#ifndef VKGETDEVICEGROUPPRESENTCAPABILITIESKHR_POST
#define VKGETDEVICEGROUPPRESENTCAPABILITIESKHR_POST(...) return result
#endif

#ifndef VKGETDEVICEGROUPSURFACEPRESENTMODESKHR_PRE
#define VKGETDEVICEGROUPSURFACEPRESENTMODESKHR_PRE(...)
#endif
#ifndef VKGETDEVICEGROUPSURFACEPRESENTMODESKHR
#define VKGETDEVICEGROUPSURFACEPRESENTMODESKHR(device, surface, pModes) VkResult result = s_vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes)
#endif
#ifndef VKGETDEVICEGROUPSURFACEPRESENTMODESKHR_POST
#define VKGETDEVICEGROUPSURFACEPRESENTMODESKHR_POST(...) return result
#endif

#ifndef VKACQUIRENEXTIMAGE2KHR_PRE
#define VKACQUIRENEXTIMAGE2KHR_PRE(...)
#endif
#ifndef VKACQUIRENEXTIMAGE2KHR
#define VKACQUIRENEXTIMAGE2KHR(device, pAcquireInfo, pImageIndex) VkResult result = s_vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex)
#endif
#ifndef VKACQUIRENEXTIMAGE2KHR_POST
#define VKACQUIRENEXTIMAGE2KHR_POST(...) return result
#endif

#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1)
#ifndef VKCMDDISPATCHBASE_PRE
#define VKCMDDISPATCHBASE_PRE(...)
#endif
#ifndef VKCMDDISPATCHBASE
#define VKCMDDISPATCHBASE(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ) s_vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ)
#endif
#ifndef VKCMDDISPATCHBASE_POST
#define VKCMDDISPATCHBASE_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
#ifndef VKCMDDISPATCHBASEKHR_PRE
#define VKCMDDISPATCHBASEKHR_PRE(...)
#endif
#ifndef VKCMDDISPATCHBASEKHR
#define VKCMDDISPATCHBASEKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ) s_vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ)
#endif
#ifndef VKCMDDISPATCHBASEKHR_POST
#define VKCMDDISPATCHBASEKHR_POST(...)
#endif

#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
#ifndef VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR_PRE
#define VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR
#define VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR(physicalDevice, surface, pRectCount, pRects) VkResult result = s_vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects)
#endif
#ifndef VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR_POST
#define VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR_POST(...) return result
#endif

#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
#ifndef VKCREATEDESCRIPTORUPDATETEMPLATE_PRE
#define VKCREATEDESCRIPTORUPDATETEMPLATE_PRE(...)
#endif
#ifndef VKCREATEDESCRIPTORUPDATETEMPLATE
#define VKCREATEDESCRIPTORUPDATETEMPLATE(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate) VkResult result = s_vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate)
#endif
#ifndef VKCREATEDESCRIPTORUPDATETEMPLATE_POST
#define VKCREATEDESCRIPTORUPDATETEMPLATE_POST(...) return result
#endif

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
#ifndef VKCREATEDESCRIPTORUPDATETEMPLATEKHR_PRE
#define VKCREATEDESCRIPTORUPDATETEMPLATEKHR_PRE(...)
#endif
#ifndef VKCREATEDESCRIPTORUPDATETEMPLATEKHR
#define VKCREATEDESCRIPTORUPDATETEMPLATEKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate) VkResult result = s_vkCreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate)
#endif
#ifndef VKCREATEDESCRIPTORUPDATETEMPLATEKHR_POST
#define VKCREATEDESCRIPTORUPDATETEMPLATEKHR_POST(...) return result
#endif

#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
#ifndef VKDESTROYDESCRIPTORUPDATETEMPLATE_PRE
#define VKDESTROYDESCRIPTORUPDATETEMPLATE_PRE(...)
#endif
#ifndef VKDESTROYDESCRIPTORUPDATETEMPLATE
#define VKDESTROYDESCRIPTORUPDATETEMPLATE(device, descriptorUpdateTemplate, pAllocator) s_vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator)
#endif
#ifndef VKDESTROYDESCRIPTORUPDATETEMPLATE_POST
#define VKDESTROYDESCRIPTORUPDATETEMPLATE_POST(...)
#endif

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
#ifndef VKDESTROYDESCRIPTORUPDATETEMPLATEKHR_PRE
#define VKDESTROYDESCRIPTORUPDATETEMPLATEKHR_PRE(...)
#endif
#ifndef VKDESTROYDESCRIPTORUPDATETEMPLATEKHR
#define VKDESTROYDESCRIPTORUPDATETEMPLATEKHR(device, descriptorUpdateTemplate, pAllocator) s_vkDestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator)
#endif
#ifndef VKDESTROYDESCRIPTORUPDATETEMPLATEKHR_POST
#define VKDESTROYDESCRIPTORUPDATETEMPLATEKHR_POST(...)
#endif

#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
#ifndef VKUPDATEDESCRIPTORSETWITHTEMPLATE_PRE
#define VKUPDATEDESCRIPTORSETWITHTEMPLATE_PRE(...)
#endif
#ifndef VKUPDATEDESCRIPTORSETWITHTEMPLATE
#define VKUPDATEDESCRIPTORSETWITHTEMPLATE(device, descriptorSet, descriptorUpdateTemplate, pData) s_vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData)
#endif
#ifndef VKUPDATEDESCRIPTORSETWITHTEMPLATE_POST
#define VKUPDATEDESCRIPTORSETWITHTEMPLATE_POST(...)
#endif

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
#ifndef VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR_PRE
#define VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR_PRE(...)
#endif
#ifndef VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR
#define VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR(device, descriptorSet, descriptorUpdateTemplate, pData) s_vkUpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData)
#endif
#ifndef VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR_POST
#define VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR_POST(...)
#endif

#endif // VK_KHR_descriptor_update_template

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
#ifndef VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR_PRE
#define VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR_PRE(...)
#endif
#ifndef VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR
#define VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData) s_vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData)
#endif
#ifndef VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR_POST
#define VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR_POST(...)
#endif

#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

#if defined(VK_EXT_hdr_metadata)
#ifndef VKSETHDRMETADATAEXT_PRE
#define VKSETHDRMETADATAEXT_PRE(...)
#endif
#ifndef VKSETHDRMETADATAEXT
#define VKSETHDRMETADATAEXT(device, swapchainCount, pSwapchains, pMetadata) s_vkSetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata)
#endif
#ifndef VKSETHDRMETADATAEXT_POST
#define VKSETHDRMETADATAEXT_POST(...)
#endif

#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_shared_presentable_image)
#ifndef VKGETSWAPCHAINSTATUSKHR_PRE
#define VKGETSWAPCHAINSTATUSKHR_PRE(...)
#endif
#ifndef VKGETSWAPCHAINSTATUSKHR
#define VKGETSWAPCHAINSTATUSKHR(device, swapchain) VkResult result = s_vkGetSwapchainStatusKHR(device, swapchain)
#endif
#ifndef VKGETSWAPCHAINSTATUSKHR_POST
#define VKGETSWAPCHAINSTATUSKHR_POST(...) return result
#endif

#endif // VK_KHR_shared_presentable_image

#if defined(VK_NV_clip_space_w_scaling)
#ifndef VKCMDSETVIEWPORTWSCALINGNV_PRE
#define VKCMDSETVIEWPORTWSCALINGNV_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORTWSCALINGNV
#define VKCMDSETVIEWPORTWSCALINGNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings) s_vkCmdSetViewportWScalingNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings)
#endif
#ifndef VKCMDSETVIEWPORTWSCALINGNV_POST
#define VKCMDSETVIEWPORTWSCALINGNV_POST(...)
#endif

#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_discard_rectangles)
#ifndef VKCMDSETDISCARDRECTANGLEEXT_PRE
#define VKCMDSETDISCARDRECTANGLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDISCARDRECTANGLEEXT
#define VKCMDSETDISCARDRECTANGLEEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles) s_vkCmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles)
#endif
#ifndef VKCMDSETDISCARDRECTANGLEEXT_POST
#define VKCMDSETDISCARDRECTANGLEEXT_POST(...)
#endif

#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
#ifndef VKCMDSETDISCARDRECTANGLEENABLEEXT_PRE
#define VKCMDSETDISCARDRECTANGLEENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDISCARDRECTANGLEENABLEEXT
#define VKCMDSETDISCARDRECTANGLEENABLEEXT(commandBuffer, discardRectangleEnable) s_vkCmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable)
#endif
#ifndef VKCMDSETDISCARDRECTANGLEENABLEEXT_POST
#define VKCMDSETDISCARDRECTANGLEENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETDISCARDRECTANGLEMODEEXT_PRE
#define VKCMDSETDISCARDRECTANGLEMODEEXT_PRE(...)
#endif
#ifndef VKCMDSETDISCARDRECTANGLEMODEEXT
#define VKCMDSETDISCARDRECTANGLEMODEEXT(commandBuffer, discardRectangleMode) s_vkCmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode)
#endif
#ifndef VKCMDSETDISCARDRECTANGLEMODEEXT_POST
#define VKCMDSETDISCARDRECTANGLEMODEEXT_POST(...)
#endif

#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_sample_locations)
#ifndef VKCMDSETSAMPLELOCATIONSEXT_PRE
#define VKCMDSETSAMPLELOCATIONSEXT_PRE(...)
#endif
#ifndef VKCMDSETSAMPLELOCATIONSEXT
#define VKCMDSETSAMPLELOCATIONSEXT(commandBuffer, pSampleLocationsInfo) s_vkCmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo)
#endif
#ifndef VKCMDSETSAMPLELOCATIONSEXT_POST
#define VKCMDSETSAMPLELOCATIONSEXT_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT_PRE
#define VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT
#define VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT(physicalDevice, samples, pMultisampleProperties) s_vkGetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice, samples, pMultisampleProperties)
#endif
#ifndef VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT_POST
#define VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT_POST(...)
#endif

#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_surface_capabilities2)
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR_PRE
#define VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR
#define VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities) VkResult result = s_vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities)
#endif
#ifndef VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR_POST
#define VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICESURFACEFORMATS2KHR_PRE
#define VKGETPHYSICALDEVICESURFACEFORMATS2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEFORMATS2KHR
#define VKGETPHYSICALDEVICESURFACEFORMATS2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats) VkResult result = s_vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEFORMATS2KHR_POST
#define VKGETPHYSICALDEVICESURFACEFORMATS2KHR_POST(...) return result
#endif

#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
#ifndef VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR
#define VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR(physicalDevice, pPropertyCount, pProperties) VkResult result = s_vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR_PRE
#define VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR
#define VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR(physicalDevice, pPropertyCount, pProperties) VkResult result = s_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR_POST
#define VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR_POST(...) return result
#endif

#ifndef VKGETDISPLAYMODEPROPERTIES2KHR_PRE
#define VKGETDISPLAYMODEPROPERTIES2KHR_PRE(...)
#endif
#ifndef VKGETDISPLAYMODEPROPERTIES2KHR
#define VKGETDISPLAYMODEPROPERTIES2KHR(physicalDevice, display, pPropertyCount, pProperties) VkResult result = s_vkGetDisplayModeProperties2KHR(physicalDevice, display, pPropertyCount, pProperties)
#endif
#ifndef VKGETDISPLAYMODEPROPERTIES2KHR_POST
#define VKGETDISPLAYMODEPROPERTIES2KHR_POST(...) return result
#endif

#ifndef VKGETDISPLAYPLANECAPABILITIES2KHR_PRE
#define VKGETDISPLAYPLANECAPABILITIES2KHR_PRE(...)
#endif
#ifndef VKGETDISPLAYPLANECAPABILITIES2KHR
#define VKGETDISPLAYPLANECAPABILITIES2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities) VkResult result = s_vkGetDisplayPlaneCapabilities2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities)
#endif
#ifndef VKGETDISPLAYPLANECAPABILITIES2KHR_POST
#define VKGETDISPLAYPLANECAPABILITIES2KHR_POST(...) return result
#endif

#endif // VK_KHR_get_display_properties2

#if defined(VK_VERSION_1_1)
#ifndef VKGETBUFFERMEMORYREQUIREMENTS2_PRE
#define VKGETBUFFERMEMORYREQUIREMENTS2_PRE(...)
#endif
#ifndef VKGETBUFFERMEMORYREQUIREMENTS2
#define VKGETBUFFERMEMORYREQUIREMENTS2(device, pInfo, pMemoryRequirements) s_vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETBUFFERMEMORYREQUIREMENTS2_POST
#define VKGETBUFFERMEMORYREQUIREMENTS2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
#ifndef VKGETBUFFERMEMORYREQUIREMENTS2KHR_PRE
#define VKGETBUFFERMEMORYREQUIREMENTS2KHR_PRE(...)
#endif
#ifndef VKGETBUFFERMEMORYREQUIREMENTS2KHR
#define VKGETBUFFERMEMORYREQUIREMENTS2KHR(device, pInfo, pMemoryRequirements) s_vkGetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETBUFFERMEMORYREQUIREMENTS2KHR_POST
#define VKGETBUFFERMEMORYREQUIREMENTS2KHR_POST(...)
#endif

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1)
#ifndef VKGETIMAGEMEMORYREQUIREMENTS2_PRE
#define VKGETIMAGEMEMORYREQUIREMENTS2_PRE(...)
#endif
#ifndef VKGETIMAGEMEMORYREQUIREMENTS2
#define VKGETIMAGEMEMORYREQUIREMENTS2(device, pInfo, pMemoryRequirements) s_vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETIMAGEMEMORYREQUIREMENTS2_POST
#define VKGETIMAGEMEMORYREQUIREMENTS2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
#ifndef VKGETIMAGEMEMORYREQUIREMENTS2KHR_PRE
#define VKGETIMAGEMEMORYREQUIREMENTS2KHR_PRE(...)
#endif
#ifndef VKGETIMAGEMEMORYREQUIREMENTS2KHR
#define VKGETIMAGEMEMORYREQUIREMENTS2KHR(device, pInfo, pMemoryRequirements) s_vkGetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETIMAGEMEMORYREQUIREMENTS2KHR_POST
#define VKGETIMAGEMEMORYREQUIREMENTS2KHR_POST(...)
#endif

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS2_PRE
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS2_PRE(...)
#endif
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS2
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements) s_vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements)
#endif
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS2_POST
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS2_POST(...)
#endif

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_memory_requirements2)
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR_PRE
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR_PRE(...)
#endif
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements) s_vkGetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements)
#endif
#ifndef VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR_POST
#define VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR_POST(...)
#endif

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_3)
#ifndef VKGETDEVICEBUFFERMEMORYREQUIREMENTS_PRE
#define VKGETDEVICEBUFFERMEMORYREQUIREMENTS_PRE(...)
#endif
#ifndef VKGETDEVICEBUFFERMEMORYREQUIREMENTS
#define VKGETDEVICEBUFFERMEMORYREQUIREMENTS(device, pInfo, pMemoryRequirements) s_vkGetDeviceBufferMemoryRequirements(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETDEVICEBUFFERMEMORYREQUIREMENTS_POST
#define VKGETDEVICEBUFFERMEMORYREQUIREMENTS_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
#ifndef VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR_PRE
#define VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR_PRE(...)
#endif
#ifndef VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR
#define VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR(device, pInfo, pMemoryRequirements) s_vkGetDeviceBufferMemoryRequirementsKHR(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR_POST
#define VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR_POST(...)
#endif

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
#ifndef VKGETDEVICEIMAGEMEMORYREQUIREMENTS_PRE
#define VKGETDEVICEIMAGEMEMORYREQUIREMENTS_PRE(...)
#endif
#ifndef VKGETDEVICEIMAGEMEMORYREQUIREMENTS
#define VKGETDEVICEIMAGEMEMORYREQUIREMENTS(device, pInfo, pMemoryRequirements) s_vkGetDeviceImageMemoryRequirements(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETDEVICEIMAGEMEMORYREQUIREMENTS_POST
#define VKGETDEVICEIMAGEMEMORYREQUIREMENTS_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
#ifndef VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR_PRE
#define VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR_PRE(...)
#endif
#ifndef VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR
#define VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR(device, pInfo, pMemoryRequirements) s_vkGetDeviceImageMemoryRequirementsKHR(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR_POST
#define VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR_POST(...)
#endif

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
#ifndef VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS_PRE
#define VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS_PRE(...)
#endif
#ifndef VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS
#define VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements) s_vkGetDeviceImageSparseMemoryRequirements(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements)
#endif
#ifndef VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS_POST
#define VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
#ifndef VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR_PRE
#define VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR_PRE(...)
#endif
#ifndef VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR
#define VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements) s_vkGetDeviceImageSparseMemoryRequirementsKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements)
#endif
#ifndef VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR_POST
#define VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR_POST(...)
#endif

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_1)
#ifndef VKCREATESAMPLERYCBCRCONVERSION_PRE
#define VKCREATESAMPLERYCBCRCONVERSION_PRE(...)
#endif
#ifndef VKCREATESAMPLERYCBCRCONVERSION
#define VKCREATESAMPLERYCBCRCONVERSION(device, pCreateInfo, pAllocator, pYcbcrConversion) VkResult result = s_vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion)
#endif
#ifndef VKCREATESAMPLERYCBCRCONVERSION_POST
#define VKCREATESAMPLERYCBCRCONVERSION_POST(...) return result
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
#ifndef VKCREATESAMPLERYCBCRCONVERSIONKHR_PRE
#define VKCREATESAMPLERYCBCRCONVERSIONKHR_PRE(...)
#endif
#ifndef VKCREATESAMPLERYCBCRCONVERSIONKHR
#define VKCREATESAMPLERYCBCRCONVERSIONKHR(device, pCreateInfo, pAllocator, pYcbcrConversion) VkResult result = s_vkCreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion)
#endif
#ifndef VKCREATESAMPLERYCBCRCONVERSIONKHR_POST
#define VKCREATESAMPLERYCBCRCONVERSIONKHR_POST(...) return result
#endif

#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
#ifndef VKDESTROYSAMPLERYCBCRCONVERSION_PRE
#define VKDESTROYSAMPLERYCBCRCONVERSION_PRE(...)
#endif
#ifndef VKDESTROYSAMPLERYCBCRCONVERSION
#define VKDESTROYSAMPLERYCBCRCONVERSION(device, ycbcrConversion, pAllocator) s_vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator)
#endif
#ifndef VKDESTROYSAMPLERYCBCRCONVERSION_POST
#define VKDESTROYSAMPLERYCBCRCONVERSION_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
#ifndef VKDESTROYSAMPLERYCBCRCONVERSIONKHR_PRE
#define VKDESTROYSAMPLERYCBCRCONVERSIONKHR_PRE(...)
#endif
#ifndef VKDESTROYSAMPLERYCBCRCONVERSIONKHR
#define VKDESTROYSAMPLERYCBCRCONVERSIONKHR(device, ycbcrConversion, pAllocator) s_vkDestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator)
#endif
#ifndef VKDESTROYSAMPLERYCBCRCONVERSIONKHR_POST
#define VKDESTROYSAMPLERYCBCRCONVERSIONKHR_POST(...)
#endif

#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
#ifndef VKGETDEVICEQUEUE2_PRE
#define VKGETDEVICEQUEUE2_PRE(...)
#endif
#ifndef VKGETDEVICEQUEUE2
#define VKGETDEVICEQUEUE2(device, pQueueInfo, pQueue) s_vkGetDeviceQueue2(device, pQueueInfo, pQueue)
#endif
#ifndef VKGETDEVICEQUEUE2_POST
#define VKGETDEVICEQUEUE2_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_EXT_validation_cache)
#ifndef VKCREATEVALIDATIONCACHEEXT_PRE
#define VKCREATEVALIDATIONCACHEEXT_PRE(...)
#endif
#ifndef VKCREATEVALIDATIONCACHEEXT
#define VKCREATEVALIDATIONCACHEEXT(device, pCreateInfo, pAllocator, pValidationCache) VkResult result = s_vkCreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache)
#endif
#ifndef VKCREATEVALIDATIONCACHEEXT_POST
#define VKCREATEVALIDATIONCACHEEXT_POST(...) return result
#endif

#ifndef VKDESTROYVALIDATIONCACHEEXT_PRE
#define VKDESTROYVALIDATIONCACHEEXT_PRE(...)
#endif
#ifndef VKDESTROYVALIDATIONCACHEEXT
#define VKDESTROYVALIDATIONCACHEEXT(device, validationCache, pAllocator) s_vkDestroyValidationCacheEXT(device, validationCache, pAllocator)
#endif
#ifndef VKDESTROYVALIDATIONCACHEEXT_POST
#define VKDESTROYVALIDATIONCACHEEXT_POST(...)
#endif

#ifndef VKGETVALIDATIONCACHEDATAEXT_PRE
#define VKGETVALIDATIONCACHEDATAEXT_PRE(...)
#endif
#ifndef VKGETVALIDATIONCACHEDATAEXT
#define VKGETVALIDATIONCACHEDATAEXT(device, validationCache, pDataSize, pData) VkResult result = s_vkGetValidationCacheDataEXT(device, validationCache, pDataSize, pData)
#endif
#ifndef VKGETVALIDATIONCACHEDATAEXT_POST
#define VKGETVALIDATIONCACHEDATAEXT_POST(...) return result
#endif

#ifndef VKMERGEVALIDATIONCACHESEXT_PRE
#define VKMERGEVALIDATIONCACHESEXT_PRE(...)
#endif
#ifndef VKMERGEVALIDATIONCACHESEXT
#define VKMERGEVALIDATIONCACHESEXT(device, dstCache, srcCacheCount, pSrcCaches) VkResult result = s_vkMergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches)
#endif
#ifndef VKMERGEVALIDATIONCACHESEXT_POST
#define VKMERGEVALIDATIONCACHESEXT_POST(...) return result
#endif

#endif // VK_EXT_validation_cache

#if defined(VK_VERSION_1_1)
#ifndef VKGETDESCRIPTORSETLAYOUTSUPPORT_PRE
#define VKGETDESCRIPTORSETLAYOUTSUPPORT_PRE(...)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTSUPPORT
#define VKGETDESCRIPTORSETLAYOUTSUPPORT(device, pCreateInfo, pSupport) s_vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTSUPPORT_POST
#define VKGETDESCRIPTORSETLAYOUTSUPPORT_POST(...)
#endif

#endif // VK_VERSION_1_1

#if defined(VK_KHR_maintenance3)
#ifndef VKGETDESCRIPTORSETLAYOUTSUPPORTKHR_PRE
#define VKGETDESCRIPTORSETLAYOUTSUPPORTKHR_PRE(...)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTSUPPORTKHR
#define VKGETDESCRIPTORSETLAYOUTSUPPORTKHR(device, pCreateInfo, pSupport) s_vkGetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTSUPPORTKHR_POST
#define VKGETDESCRIPTORSETLAYOUTSUPPORTKHR_POST(...)
#endif

#endif // VK_KHR_maintenance3

#if defined(VK_AMD_shader_info)
#ifndef VKGETSHADERINFOAMD_PRE
#define VKGETSHADERINFOAMD_PRE(...)
#endif
#ifndef VKGETSHADERINFOAMD
#define VKGETSHADERINFOAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo) VkResult result = s_vkGetShaderInfoAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo)
#endif
#ifndef VKGETSHADERINFOAMD_POST
#define VKGETSHADERINFOAMD_POST(...) return result
#endif

#endif // VK_AMD_shader_info

#if defined(VK_EXT_calibrated_timestamps)
#ifndef VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT_PRE
#define VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT
#define VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT(physicalDevice, pTimeDomainCount, pTimeDomains) VkResult result = s_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice, pTimeDomainCount, pTimeDomains)
#endif
#ifndef VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT_POST
#define VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT_POST(...) return result
#endif

#ifndef VKGETCALIBRATEDTIMESTAMPSEXT_PRE
#define VKGETCALIBRATEDTIMESTAMPSEXT_PRE(...)
#endif
#ifndef VKGETCALIBRATEDTIMESTAMPSEXT
#define VKGETCALIBRATEDTIMESTAMPSEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation) VkResult result = s_vkGetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation)
#endif
#ifndef VKGETCALIBRATEDTIMESTAMPSEXT_POST
#define VKGETCALIBRATEDTIMESTAMPSEXT_POST(...) return result
#endif

#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
#ifndef VKSETDEBUGUTILSOBJECTNAMEEXT_PRE
#define VKSETDEBUGUTILSOBJECTNAMEEXT_PRE(...)
#endif
#ifndef VKSETDEBUGUTILSOBJECTNAMEEXT
#define VKSETDEBUGUTILSOBJECTNAMEEXT(device, pNameInfo) VkResult result = s_vkSetDebugUtilsObjectNameEXT(device, pNameInfo)
#endif
#ifndef VKSETDEBUGUTILSOBJECTNAMEEXT_POST
#define VKSETDEBUGUTILSOBJECTNAMEEXT_POST(...) return result
#endif

#ifndef VKSETDEBUGUTILSOBJECTTAGEXT_PRE
#define VKSETDEBUGUTILSOBJECTTAGEXT_PRE(...)
#endif
#ifndef VKSETDEBUGUTILSOBJECTTAGEXT
#define VKSETDEBUGUTILSOBJECTTAGEXT(device, pTagInfo) VkResult result = s_vkSetDebugUtilsObjectTagEXT(device, pTagInfo)
#endif
#ifndef VKSETDEBUGUTILSOBJECTTAGEXT_POST
#define VKSETDEBUGUTILSOBJECTTAGEXT_POST(...) return result
#endif

#ifndef VKQUEUEBEGINDEBUGUTILSLABELEXT_PRE
#define VKQUEUEBEGINDEBUGUTILSLABELEXT_PRE(...)
#endif
#ifndef VKQUEUEBEGINDEBUGUTILSLABELEXT
#define VKQUEUEBEGINDEBUGUTILSLABELEXT(queue, pLabelInfo) s_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo)
#endif
#ifndef VKQUEUEBEGINDEBUGUTILSLABELEXT_POST
#define VKQUEUEBEGINDEBUGUTILSLABELEXT_POST(...)
#endif

#ifndef VKQUEUEENDDEBUGUTILSLABELEXT_PRE
#define VKQUEUEENDDEBUGUTILSLABELEXT_PRE(...)
#endif
#ifndef VKQUEUEENDDEBUGUTILSLABELEXT
#define VKQUEUEENDDEBUGUTILSLABELEXT(queue) s_vkQueueEndDebugUtilsLabelEXT(queue)
#endif
#ifndef VKQUEUEENDDEBUGUTILSLABELEXT_POST
#define VKQUEUEENDDEBUGUTILSLABELEXT_POST(...)
#endif

#ifndef VKQUEUEINSERTDEBUGUTILSLABELEXT_PRE
#define VKQUEUEINSERTDEBUGUTILSLABELEXT_PRE(...)
#endif
#ifndef VKQUEUEINSERTDEBUGUTILSLABELEXT
#define VKQUEUEINSERTDEBUGUTILSLABELEXT(queue, pLabelInfo) s_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo)
#endif
#ifndef VKQUEUEINSERTDEBUGUTILSLABELEXT_POST
#define VKQUEUEINSERTDEBUGUTILSLABELEXT_POST(...)
#endif

#ifndef VKCMDBEGINDEBUGUTILSLABELEXT_PRE
#define VKCMDBEGINDEBUGUTILSLABELEXT_PRE(...)
#endif
#ifndef VKCMDBEGINDEBUGUTILSLABELEXT
#define VKCMDBEGINDEBUGUTILSLABELEXT(commandBuffer, pLabelInfo) s_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo)
#endif
#ifndef VKCMDBEGINDEBUGUTILSLABELEXT_POST
#define VKCMDBEGINDEBUGUTILSLABELEXT_POST(...)
#endif

#ifndef VKCMDENDDEBUGUTILSLABELEXT_PRE
#define VKCMDENDDEBUGUTILSLABELEXT_PRE(...)
#endif
#ifndef VKCMDENDDEBUGUTILSLABELEXT
#define VKCMDENDDEBUGUTILSLABELEXT(commandBuffer) s_vkCmdEndDebugUtilsLabelEXT(commandBuffer)
#endif
#ifndef VKCMDENDDEBUGUTILSLABELEXT_POST
#define VKCMDENDDEBUGUTILSLABELEXT_POST(...)
#endif

#ifndef VKCMDINSERTDEBUGUTILSLABELEXT_PRE
#define VKCMDINSERTDEBUGUTILSLABELEXT_PRE(...)
#endif
#ifndef VKCMDINSERTDEBUGUTILSLABELEXT
#define VKCMDINSERTDEBUGUTILSLABELEXT(commandBuffer, pLabelInfo) s_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo)
#endif
#ifndef VKCMDINSERTDEBUGUTILSLABELEXT_POST
#define VKCMDINSERTDEBUGUTILSLABELEXT_POST(...)
#endif

#ifndef VKCREATEDEBUGUTILSMESSENGEREXT_PRE
#define VKCREATEDEBUGUTILSMESSENGEREXT_PRE(...)
#endif
#ifndef VKCREATEDEBUGUTILSMESSENGEREXT
#define VKCREATEDEBUGUTILSMESSENGEREXT(instance, pCreateInfo, pAllocator, pMessenger) VkResult result = s_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger)
#endif
#ifndef VKCREATEDEBUGUTILSMESSENGEREXT_POST
#define VKCREATEDEBUGUTILSMESSENGEREXT_POST(...) return result
#endif

#ifndef VKDESTROYDEBUGUTILSMESSENGEREXT_PRE
#define VKDESTROYDEBUGUTILSMESSENGEREXT_PRE(...)
#endif
#ifndef VKDESTROYDEBUGUTILSMESSENGEREXT
#define VKDESTROYDEBUGUTILSMESSENGEREXT(instance, messenger, pAllocator) s_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator)
#endif
#ifndef VKDESTROYDEBUGUTILSMESSENGEREXT_POST
#define VKDESTROYDEBUGUTILSMESSENGEREXT_POST(...)
#endif

#ifndef VKSUBMITDEBUGUTILSMESSAGEEXT_PRE
#define VKSUBMITDEBUGUTILSMESSAGEEXT_PRE(...)
#endif
#ifndef VKSUBMITDEBUGUTILSMESSAGEEXT
#define VKSUBMITDEBUGUTILSMESSAGEEXT(instance, messageSeverity, messageTypes, pCallbackData) s_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData)
#endif
#ifndef VKSUBMITDEBUGUTILSMESSAGEEXT_POST
#define VKSUBMITDEBUGUTILSMESSAGEEXT_POST(...)
#endif

#endif // VK_EXT_debug_utils

#if defined(VK_EXT_external_memory_host)
#ifndef VKGETMEMORYHOSTPOINTERPROPERTIESEXT_PRE
#define VKGETMEMORYHOSTPOINTERPROPERTIESEXT_PRE(...)
#endif
#ifndef VKGETMEMORYHOSTPOINTERPROPERTIESEXT
#define VKGETMEMORYHOSTPOINTERPROPERTIESEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties) VkResult result = s_vkGetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties)
#endif
#ifndef VKGETMEMORYHOSTPOINTERPROPERTIESEXT_POST
#define VKGETMEMORYHOSTPOINTERPROPERTIESEXT_POST(...) return result
#endif

#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
#ifndef VKCMDWRITEBUFFERMARKERAMD_PRE
#define VKCMDWRITEBUFFERMARKERAMD_PRE(...)
#endif
#ifndef VKCMDWRITEBUFFERMARKERAMD
#define VKCMDWRITEBUFFERMARKERAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker) s_vkCmdWriteBufferMarkerAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker)
#endif
#ifndef VKCMDWRITEBUFFERMARKERAMD_POST
#define VKCMDWRITEBUFFERMARKERAMD_POST(...)
#endif

#endif // VK_AMD_buffer_marker

#if defined(VK_VERSION_1_2)
#ifndef VKCREATERENDERPASS2_PRE
#define VKCREATERENDERPASS2_PRE(...)
#endif
#ifndef VKCREATERENDERPASS2
#define VKCREATERENDERPASS2(device, pCreateInfo, pAllocator, pRenderPass) VkResult result = s_vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass)
#endif
#ifndef VKCREATERENDERPASS2_POST
#define VKCREATERENDERPASS2_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
#ifndef VKCREATERENDERPASS2KHR_PRE
#define VKCREATERENDERPASS2KHR_PRE(...)
#endif
#ifndef VKCREATERENDERPASS2KHR
#define VKCREATERENDERPASS2KHR(device, pCreateInfo, pAllocator, pRenderPass) VkResult result = s_vkCreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass)
#endif
#ifndef VKCREATERENDERPASS2KHR_POST
#define VKCREATERENDERPASS2KHR_POST(...) return result
#endif

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
#ifndef VKCMDBEGINRENDERPASS2_PRE
#define VKCMDBEGINRENDERPASS2_PRE(...)
#endif
#ifndef VKCMDBEGINRENDERPASS2
#define VKCMDBEGINRENDERPASS2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo) s_vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo)
#endif
#ifndef VKCMDBEGINRENDERPASS2_POST
#define VKCMDBEGINRENDERPASS2_POST(...)
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
#ifndef VKCMDBEGINRENDERPASS2KHR_PRE
#define VKCMDBEGINRENDERPASS2KHR_PRE(...)
#endif
#ifndef VKCMDBEGINRENDERPASS2KHR
#define VKCMDBEGINRENDERPASS2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo) s_vkCmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo)
#endif
#ifndef VKCMDBEGINRENDERPASS2KHR_POST
#define VKCMDBEGINRENDERPASS2KHR_POST(...)
#endif

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
#ifndef VKCMDNEXTSUBPASS2_PRE
#define VKCMDNEXTSUBPASS2_PRE(...)
#endif
#ifndef VKCMDNEXTSUBPASS2
#define VKCMDNEXTSUBPASS2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo) s_vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo)
#endif
#ifndef VKCMDNEXTSUBPASS2_POST
#define VKCMDNEXTSUBPASS2_POST(...)
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
#ifndef VKCMDNEXTSUBPASS2KHR_PRE
#define VKCMDNEXTSUBPASS2KHR_PRE(...)
#endif
#ifndef VKCMDNEXTSUBPASS2KHR
#define VKCMDNEXTSUBPASS2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo) s_vkCmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo)
#endif
#ifndef VKCMDNEXTSUBPASS2KHR_POST
#define VKCMDNEXTSUBPASS2KHR_POST(...)
#endif

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
#ifndef VKCMDENDRENDERPASS2_PRE
#define VKCMDENDRENDERPASS2_PRE(...)
#endif
#ifndef VKCMDENDRENDERPASS2
#define VKCMDENDRENDERPASS2(commandBuffer, pSubpassEndInfo) s_vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo)
#endif
#ifndef VKCMDENDRENDERPASS2_POST
#define VKCMDENDRENDERPASS2_POST(...)
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
#ifndef VKCMDENDRENDERPASS2KHR_PRE
#define VKCMDENDRENDERPASS2KHR_PRE(...)
#endif
#ifndef VKCMDENDRENDERPASS2KHR
#define VKCMDENDRENDERPASS2KHR(commandBuffer, pSubpassEndInfo) s_vkCmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo)
#endif
#ifndef VKCMDENDRENDERPASS2KHR_POST
#define VKCMDENDRENDERPASS2KHR_POST(...)
#endif

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
#ifndef VKGETSEMAPHORECOUNTERVALUE_PRE
#define VKGETSEMAPHORECOUNTERVALUE_PRE(...)
#endif
#ifndef VKGETSEMAPHORECOUNTERVALUE
#define VKGETSEMAPHORECOUNTERVALUE(device, semaphore, pValue) VkResult result = s_vkGetSemaphoreCounterValue(device, semaphore, pValue)
#endif
#ifndef VKGETSEMAPHORECOUNTERVALUE_POST
#define VKGETSEMAPHORECOUNTERVALUE_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
#ifndef VKGETSEMAPHORECOUNTERVALUEKHR_PRE
#define VKGETSEMAPHORECOUNTERVALUEKHR_PRE(...)
#endif
#ifndef VKGETSEMAPHORECOUNTERVALUEKHR
#define VKGETSEMAPHORECOUNTERVALUEKHR(device, semaphore, pValue) VkResult result = s_vkGetSemaphoreCounterValueKHR(device, semaphore, pValue)
#endif
#ifndef VKGETSEMAPHORECOUNTERVALUEKHR_POST
#define VKGETSEMAPHORECOUNTERVALUEKHR_POST(...) return result
#endif

#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
#ifndef VKWAITSEMAPHORES_PRE
#define VKWAITSEMAPHORES_PRE(...)
#endif
#ifndef VKWAITSEMAPHORES
#define VKWAITSEMAPHORES(device, pWaitInfo, timeout) VkResult result = s_vkWaitSemaphores(device, pWaitInfo, timeout)
#endif
#ifndef VKWAITSEMAPHORES_POST
#define VKWAITSEMAPHORES_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
#ifndef VKWAITSEMAPHORESKHR_PRE
#define VKWAITSEMAPHORESKHR_PRE(...)
#endif
#ifndef VKWAITSEMAPHORESKHR
#define VKWAITSEMAPHORESKHR(device, pWaitInfo, timeout) VkResult result = s_vkWaitSemaphoresKHR(device, pWaitInfo, timeout)
#endif
#ifndef VKWAITSEMAPHORESKHR_POST
#define VKWAITSEMAPHORESKHR_POST(...) return result
#endif

#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
#ifndef VKSIGNALSEMAPHORE_PRE
#define VKSIGNALSEMAPHORE_PRE(...)
#endif
#ifndef VKSIGNALSEMAPHORE
#define VKSIGNALSEMAPHORE(device, pSignalInfo) VkResult result = s_vkSignalSemaphore(device, pSignalInfo)
#endif
#ifndef VKSIGNALSEMAPHORE_POST
#define VKSIGNALSEMAPHORE_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
#ifndef VKSIGNALSEMAPHOREKHR_PRE
#define VKSIGNALSEMAPHOREKHR_PRE(...)
#endif
#ifndef VKSIGNALSEMAPHOREKHR
#define VKSIGNALSEMAPHOREKHR(device, pSignalInfo) VkResult result = s_vkSignalSemaphoreKHR(device, pSignalInfo)
#endif
#ifndef VKSIGNALSEMAPHOREKHR_POST
#define VKSIGNALSEMAPHOREKHR_POST(...) return result
#endif

#endif // VK_KHR_timeline_semaphore

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
#ifndef VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID_PRE
#define VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID_PRE(...)
#endif
#ifndef VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID
#define VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID(device, buffer, pProperties) VkResult result = s_vkGetAndroidHardwareBufferPropertiesANDROID(device, buffer, pProperties)
#endif
#ifndef VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID_POST
#define VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID_POST(...) return result
#endif

#ifndef VKGETMEMORYANDROIDHARDWAREBUFFERANDROID_PRE
#define VKGETMEMORYANDROIDHARDWAREBUFFERANDROID_PRE(...)
#endif
#ifndef VKGETMEMORYANDROIDHARDWAREBUFFERANDROID
#define VKGETMEMORYANDROIDHARDWAREBUFFERANDROID(device, pInfo, pBuffer) VkResult result = s_vkGetMemoryAndroidHardwareBufferANDROID(device, pInfo, pBuffer)
#endif
#ifndef VKGETMEMORYANDROIDHARDWAREBUFFERANDROID_POST
#define VKGETMEMORYANDROIDHARDWAREBUFFERANDROID_POST(...) return result
#endif

#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_VERSION_1_2)
#ifndef VKCMDDRAWINDIRECTCOUNT_PRE
#define VKCMDDRAWINDIRECTCOUNT_PRE(...)
#endif
#ifndef VKCMDDRAWINDIRECTCOUNT
#define VKCMDDRAWINDIRECTCOUNT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride) s_vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride)
#endif
#ifndef VKCMDDRAWINDIRECTCOUNT_POST
#define VKCMDDRAWINDIRECTCOUNT_POST(...)
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
#ifndef VKCMDDRAWINDIRECTCOUNTKHR_PRE
#define VKCMDDRAWINDIRECTCOUNTKHR_PRE(...)
#endif
#ifndef VKCMDDRAWINDIRECTCOUNTKHR
#define VKCMDDRAWINDIRECTCOUNTKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride) s_vkCmdDrawIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride)
#endif
#ifndef VKCMDDRAWINDIRECTCOUNTKHR_POST
#define VKCMDDRAWINDIRECTCOUNTKHR_POST(...)
#endif

#endif // VK_KHR_draw_indirect_count

#if defined(VK_VERSION_1_2)
#ifndef VKCMDDRAWINDEXEDINDIRECTCOUNT_PRE
#define VKCMDDRAWINDEXEDINDIRECTCOUNT_PRE(...)
#endif
#ifndef VKCMDDRAWINDEXEDINDIRECTCOUNT
#define VKCMDDRAWINDEXEDINDIRECTCOUNT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride) s_vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride)
#endif
#ifndef VKCMDDRAWINDEXEDINDIRECTCOUNT_POST
#define VKCMDDRAWINDEXEDINDIRECTCOUNT_POST(...)
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
#ifndef VKCMDDRAWINDEXEDINDIRECTCOUNTKHR_PRE
#define VKCMDDRAWINDEXEDINDIRECTCOUNTKHR_PRE(...)
#endif
#ifndef VKCMDDRAWINDEXEDINDIRECTCOUNTKHR
#define VKCMDDRAWINDEXEDINDIRECTCOUNTKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride) s_vkCmdDrawIndexedIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride)
#endif
#ifndef VKCMDDRAWINDEXEDINDIRECTCOUNTKHR_POST
#define VKCMDDRAWINDEXEDINDIRECTCOUNTKHR_POST(...)
#endif

#endif // VK_KHR_draw_indirect_count

#if defined(VK_NV_device_diagnostic_checkpoints)
#ifndef VKCMDSETCHECKPOINTNV_PRE
#define VKCMDSETCHECKPOINTNV_PRE(...)
#endif
#ifndef VKCMDSETCHECKPOINTNV
#define VKCMDSETCHECKPOINTNV(commandBuffer, pCheckpointMarker) s_vkCmdSetCheckpointNV(commandBuffer, pCheckpointMarker)
#endif
#ifndef VKCMDSETCHECKPOINTNV_POST
#define VKCMDSETCHECKPOINTNV_POST(...)
#endif

#ifndef VKGETQUEUECHECKPOINTDATANV_PRE
#define VKGETQUEUECHECKPOINTDATANV_PRE(...)
#endif
#ifndef VKGETQUEUECHECKPOINTDATANV
#define VKGETQUEUECHECKPOINTDATANV(queue, pCheckpointDataCount, pCheckpointData) s_vkGetQueueCheckpointDataNV(queue, pCheckpointDataCount, pCheckpointData)
#endif
#ifndef VKGETQUEUECHECKPOINTDATANV_POST
#define VKGETQUEUECHECKPOINTDATANV_POST(...)
#endif

#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_EXT_transform_feedback)
#ifndef VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT_PRE
#define VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT_PRE(...)
#endif
#ifndef VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT
#define VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes) s_vkCmdBindTransformFeedbackBuffersEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes)
#endif
#ifndef VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT_POST
#define VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT_POST(...)
#endif

#ifndef VKCMDBEGINTRANSFORMFEEDBACKEXT_PRE
#define VKCMDBEGINTRANSFORMFEEDBACKEXT_PRE(...)
#endif
#ifndef VKCMDBEGINTRANSFORMFEEDBACKEXT
#define VKCMDBEGINTRANSFORMFEEDBACKEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets) s_vkCmdBeginTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets)
#endif
#ifndef VKCMDBEGINTRANSFORMFEEDBACKEXT_POST
#define VKCMDBEGINTRANSFORMFEEDBACKEXT_POST(...)
#endif

#ifndef VKCMDENDTRANSFORMFEEDBACKEXT_PRE
#define VKCMDENDTRANSFORMFEEDBACKEXT_PRE(...)
#endif
#ifndef VKCMDENDTRANSFORMFEEDBACKEXT
#define VKCMDENDTRANSFORMFEEDBACKEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets) s_vkCmdEndTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets)
#endif
#ifndef VKCMDENDTRANSFORMFEEDBACKEXT_POST
#define VKCMDENDTRANSFORMFEEDBACKEXT_POST(...)
#endif

#ifndef VKCMDBEGINQUERYINDEXEDEXT_PRE
#define VKCMDBEGINQUERYINDEXEDEXT_PRE(...)
#endif
#ifndef VKCMDBEGINQUERYINDEXEDEXT
#define VKCMDBEGINQUERYINDEXEDEXT(commandBuffer, queryPool, query, flags, index) s_vkCmdBeginQueryIndexedEXT(commandBuffer, queryPool, query, flags, index)
#endif
#ifndef VKCMDBEGINQUERYINDEXEDEXT_POST
#define VKCMDBEGINQUERYINDEXEDEXT_POST(...)
#endif

#ifndef VKCMDENDQUERYINDEXEDEXT_PRE
#define VKCMDENDQUERYINDEXEDEXT_PRE(...)
#endif
#ifndef VKCMDENDQUERYINDEXEDEXT
#define VKCMDENDQUERYINDEXEDEXT(commandBuffer, queryPool, query, index) s_vkCmdEndQueryIndexedEXT(commandBuffer, queryPool, query, index)
#endif
#ifndef VKCMDENDQUERYINDEXEDEXT_POST
#define VKCMDENDQUERYINDEXEDEXT_POST(...)
#endif

#ifndef VKCMDDRAWINDIRECTBYTECOUNTEXT_PRE
#define VKCMDDRAWINDIRECTBYTECOUNTEXT_PRE(...)
#endif
#ifndef VKCMDDRAWINDIRECTBYTECOUNTEXT
#define VKCMDDRAWINDIRECTBYTECOUNTEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride) s_vkCmdDrawIndirectByteCountEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride)
#endif
#ifndef VKCMDDRAWINDIRECTBYTECOUNTEXT_POST
#define VKCMDDRAWINDIRECTBYTECOUNTEXT_POST(...)
#endif

#endif // VK_EXT_transform_feedback

#if defined(VK_NV_scissor_exclusive)
#ifndef VKCMDSETEXCLUSIVESCISSORNV_PRE
#define VKCMDSETEXCLUSIVESCISSORNV_PRE(...)
#endif
#ifndef VKCMDSETEXCLUSIVESCISSORNV
#define VKCMDSETEXCLUSIVESCISSORNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors) s_vkCmdSetExclusiveScissorNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors)
#endif
#ifndef VKCMDSETEXCLUSIVESCISSORNV_POST
#define VKCMDSETEXCLUSIVESCISSORNV_POST(...)
#endif

#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
#ifndef VKCMDSETEXCLUSIVESCISSORENABLENV_PRE
#define VKCMDSETEXCLUSIVESCISSORENABLENV_PRE(...)
#endif
#ifndef VKCMDSETEXCLUSIVESCISSORENABLENV
#define VKCMDSETEXCLUSIVESCISSORENABLENV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables) s_vkCmdSetExclusiveScissorEnableNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables)
#endif
#ifndef VKCMDSETEXCLUSIVESCISSORENABLENV_POST
#define VKCMDSETEXCLUSIVESCISSORENABLENV_POST(...)
#endif

#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_shading_rate_image)
#ifndef VKCMDBINDSHADINGRATEIMAGENV_PRE
#define VKCMDBINDSHADINGRATEIMAGENV_PRE(...)
#endif
#ifndef VKCMDBINDSHADINGRATEIMAGENV
#define VKCMDBINDSHADINGRATEIMAGENV(commandBuffer, imageView, imageLayout) s_vkCmdBindShadingRateImageNV(commandBuffer, imageView, imageLayout)
#endif
#ifndef VKCMDBINDSHADINGRATEIMAGENV_POST
#define VKCMDBINDSHADINGRATEIMAGENV_POST(...)
#endif

#ifndef VKCMDSETVIEWPORTSHADINGRATEPALETTENV_PRE
#define VKCMDSETVIEWPORTSHADINGRATEPALETTENV_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORTSHADINGRATEPALETTENV
#define VKCMDSETVIEWPORTSHADINGRATEPALETTENV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes) s_vkCmdSetViewportShadingRatePaletteNV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes)
#endif
#ifndef VKCMDSETVIEWPORTSHADINGRATEPALETTENV_POST
#define VKCMDSETVIEWPORTSHADINGRATEPALETTENV_POST(...)
#endif

#ifndef VKCMDSETCOARSESAMPLEORDERNV_PRE
#define VKCMDSETCOARSESAMPLEORDERNV_PRE(...)
#endif
#ifndef VKCMDSETCOARSESAMPLEORDERNV
#define VKCMDSETCOARSESAMPLEORDERNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders) s_vkCmdSetCoarseSampleOrderNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders)
#endif
#ifndef VKCMDSETCOARSESAMPLEORDERNV_POST
#define VKCMDSETCOARSESAMPLEORDERNV_POST(...)
#endif

#endif // VK_NV_shading_rate_image

#if defined(VK_NV_mesh_shader)
#ifndef VKCMDDRAWMESHTASKSNV_PRE
#define VKCMDDRAWMESHTASKSNV_PRE(...)
#endif
#ifndef VKCMDDRAWMESHTASKSNV
#define VKCMDDRAWMESHTASKSNV(commandBuffer, taskCount, firstTask) s_vkCmdDrawMeshTasksNV(commandBuffer, taskCount, firstTask)
#endif
#ifndef VKCMDDRAWMESHTASKSNV_POST
#define VKCMDDRAWMESHTASKSNV_POST(...)
#endif

#ifndef VKCMDDRAWMESHTASKSINDIRECTNV_PRE
#define VKCMDDRAWMESHTASKSINDIRECTNV_PRE(...)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTNV
#define VKCMDDRAWMESHTASKSINDIRECTNV(commandBuffer, buffer, offset, drawCount, stride) s_vkCmdDrawMeshTasksIndirectNV(commandBuffer, buffer, offset, drawCount, stride)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTNV_POST
#define VKCMDDRAWMESHTASKSINDIRECTNV_POST(...)
#endif

#ifndef VKCMDDRAWMESHTASKSINDIRECTCOUNTNV_PRE
#define VKCMDDRAWMESHTASKSINDIRECTCOUNTNV_PRE(...)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTCOUNTNV
#define VKCMDDRAWMESHTASKSINDIRECTCOUNTNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride) s_vkCmdDrawMeshTasksIndirectCountNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTCOUNTNV_POST
#define VKCMDDRAWMESHTASKSINDIRECTCOUNTNV_POST(...)
#endif

#endif // VK_NV_mesh_shader

#if defined(VK_EXT_mesh_shader)
#ifndef VKCMDDRAWMESHTASKSEXT_PRE
#define VKCMDDRAWMESHTASKSEXT_PRE(...)
#endif
#ifndef VKCMDDRAWMESHTASKSEXT
#define VKCMDDRAWMESHTASKSEXT(commandBuffer, groupCountX, groupCountY, groupCountZ) s_vkCmdDrawMeshTasksEXT(commandBuffer, groupCountX, groupCountY, groupCountZ)
#endif
#ifndef VKCMDDRAWMESHTASKSEXT_POST
#define VKCMDDRAWMESHTASKSEXT_POST(...)
#endif

#ifndef VKCMDDRAWMESHTASKSINDIRECTEXT_PRE
#define VKCMDDRAWMESHTASKSINDIRECTEXT_PRE(...)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTEXT
#define VKCMDDRAWMESHTASKSINDIRECTEXT(commandBuffer, buffer, offset, drawCount, stride) s_vkCmdDrawMeshTasksIndirectEXT(commandBuffer, buffer, offset, drawCount, stride)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTEXT_POST
#define VKCMDDRAWMESHTASKSINDIRECTEXT_POST(...)
#endif

#ifndef VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT_PRE
#define VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT_PRE(...)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT
#define VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride) s_vkCmdDrawMeshTasksIndirectCountEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride)
#endif
#ifndef VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT_POST
#define VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT_POST(...)
#endif

#endif // VK_EXT_mesh_shader

#if defined(VK_NV_ray_tracing)
#ifndef VKCOMPILEDEFERREDNV_PRE
#define VKCOMPILEDEFERREDNV_PRE(...)
#endif
#ifndef VKCOMPILEDEFERREDNV
#define VKCOMPILEDEFERREDNV(device, pipeline, shader) VkResult result = s_vkCompileDeferredNV(device, pipeline, shader)
#endif
#ifndef VKCOMPILEDEFERREDNV_POST
#define VKCOMPILEDEFERREDNV_POST(...) return result
#endif

#ifndef VKCREATEACCELERATIONSTRUCTURENV_PRE
#define VKCREATEACCELERATIONSTRUCTURENV_PRE(...)
#endif
#ifndef VKCREATEACCELERATIONSTRUCTURENV
#define VKCREATEACCELERATIONSTRUCTURENV(device, pCreateInfo, pAllocator, pAccelerationStructure) VkResult result = s_vkCreateAccelerationStructureNV(device, pCreateInfo, pAllocator, pAccelerationStructure)
#endif
#ifndef VKCREATEACCELERATIONSTRUCTURENV_POST
#define VKCREATEACCELERATIONSTRUCTURENV_POST(...) return result
#endif

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
#ifndef VKDESTROYACCELERATIONSTRUCTUREKHR_PRE
#define VKDESTROYACCELERATIONSTRUCTUREKHR_PRE(...)
#endif
#ifndef VKDESTROYACCELERATIONSTRUCTUREKHR
#define VKDESTROYACCELERATIONSTRUCTUREKHR(device, accelerationStructure, pAllocator) s_vkDestroyAccelerationStructureKHR(device, accelerationStructure, pAllocator)
#endif
#ifndef VKDESTROYACCELERATIONSTRUCTUREKHR_POST
#define VKDESTROYACCELERATIONSTRUCTUREKHR_POST(...)
#endif

#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
#ifndef VKDESTROYACCELERATIONSTRUCTURENV_PRE
#define VKDESTROYACCELERATIONSTRUCTURENV_PRE(...)
#endif
#ifndef VKDESTROYACCELERATIONSTRUCTURENV
#define VKDESTROYACCELERATIONSTRUCTURENV(device, accelerationStructure, pAllocator) s_vkDestroyAccelerationStructureNV(device, accelerationStructure, pAllocator)
#endif
#ifndef VKDESTROYACCELERATIONSTRUCTURENV_POST
#define VKDESTROYACCELERATIONSTRUCTURENV_POST(...)
#endif

#ifndef VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV_PRE
#define VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV_PRE(...)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV
#define VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV(device, pInfo, pMemoryRequirements) s_vkGetAccelerationStructureMemoryRequirementsNV(device, pInfo, pMemoryRequirements)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV_POST
#define VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV_POST(...)
#endif

#ifndef VKBINDACCELERATIONSTRUCTUREMEMORYNV_PRE
#define VKBINDACCELERATIONSTRUCTUREMEMORYNV_PRE(...)
#endif
#ifndef VKBINDACCELERATIONSTRUCTUREMEMORYNV
#define VKBINDACCELERATIONSTRUCTUREMEMORYNV(device, bindInfoCount, pBindInfos) VkResult result = s_vkBindAccelerationStructureMemoryNV(device, bindInfoCount, pBindInfos)
#endif
#ifndef VKBINDACCELERATIONSTRUCTUREMEMORYNV_POST
#define VKBINDACCELERATIONSTRUCTUREMEMORYNV_POST(...) return result
#endif

#ifndef VKCMDCOPYACCELERATIONSTRUCTURENV_PRE
#define VKCMDCOPYACCELERATIONSTRUCTURENV_PRE(...)
#endif
#ifndef VKCMDCOPYACCELERATIONSTRUCTURENV
#define VKCMDCOPYACCELERATIONSTRUCTURENV(commandBuffer, dst, src, mode) s_vkCmdCopyAccelerationStructureNV(commandBuffer, dst, src, mode)
#endif
#ifndef VKCMDCOPYACCELERATIONSTRUCTURENV_POST
#define VKCMDCOPYACCELERATIONSTRUCTURENV_POST(...)
#endif

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
#ifndef VKCMDCOPYACCELERATIONSTRUCTUREKHR_PRE
#define VKCMDCOPYACCELERATIONSTRUCTUREKHR_PRE(...)
#endif
#ifndef VKCMDCOPYACCELERATIONSTRUCTUREKHR
#define VKCMDCOPYACCELERATIONSTRUCTUREKHR(commandBuffer, pInfo) s_vkCmdCopyAccelerationStructureKHR(commandBuffer, pInfo)
#endif
#ifndef VKCMDCOPYACCELERATIONSTRUCTUREKHR_POST
#define VKCMDCOPYACCELERATIONSTRUCTUREKHR_POST(...)
#endif

#ifndef VKCOPYACCELERATIONSTRUCTUREKHR_PRE
#define VKCOPYACCELERATIONSTRUCTUREKHR_PRE(...)
#endif
#ifndef VKCOPYACCELERATIONSTRUCTUREKHR
#define VKCOPYACCELERATIONSTRUCTUREKHR(device, deferredOperation, pInfo) VkResult result = s_vkCopyAccelerationStructureKHR(device, deferredOperation, pInfo)
#endif
#ifndef VKCOPYACCELERATIONSTRUCTUREKHR_POST
#define VKCOPYACCELERATIONSTRUCTUREKHR_POST(...) return result
#endif

#ifndef VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR_PRE
#define VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR_PRE(...)
#endif
#ifndef VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR
#define VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR(commandBuffer, pInfo) s_vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo)
#endif
#ifndef VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR_POST
#define VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR_POST(...)
#endif

#ifndef VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR_PRE
#define VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR_PRE(...)
#endif
#ifndef VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR
#define VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR(device, deferredOperation, pInfo) VkResult result = s_vkCopyAccelerationStructureToMemoryKHR(device, deferredOperation, pInfo)
#endif
#ifndef VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR_POST
#define VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR_POST(...) return result
#endif

#ifndef VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_PRE
#define VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_PRE(...)
#endif
#ifndef VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR
#define VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR(commandBuffer, pInfo) s_vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo)
#endif
#ifndef VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_POST
#define VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_POST(...)
#endif

#ifndef VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_PRE
#define VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_PRE(...)
#endif
#ifndef VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR
#define VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR(device, deferredOperation, pInfo) VkResult result = s_vkCopyMemoryToAccelerationStructureKHR(device, deferredOperation, pInfo)
#endif
#ifndef VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_POST
#define VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_POST(...) return result
#endif

#ifndef VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_PRE
#define VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_PRE(...)
#endif
#ifndef VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR
#define VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery) s_vkCmdWriteAccelerationStructuresPropertiesKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery)
#endif
#ifndef VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_POST
#define VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_POST(...)
#endif

#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
#ifndef VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV_PRE
#define VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV_PRE(...)
#endif
#ifndef VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV
#define VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery) s_vkCmdWriteAccelerationStructuresPropertiesNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery)
#endif
#ifndef VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV_POST
#define VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV_POST(...)
#endif

#ifndef VKCMDBUILDACCELERATIONSTRUCTURENV_PRE
#define VKCMDBUILDACCELERATIONSTRUCTURENV_PRE(...)
#endif
#ifndef VKCMDBUILDACCELERATIONSTRUCTURENV
#define VKCMDBUILDACCELERATIONSTRUCTURENV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset) s_vkCmdBuildAccelerationStructureNV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset)
#endif
#ifndef VKCMDBUILDACCELERATIONSTRUCTURENV_POST
#define VKCMDBUILDACCELERATIONSTRUCTURENV_POST(...)
#endif

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
#ifndef VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_PRE
#define VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_PRE(...)
#endif
#ifndef VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR
#define VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride) VkResult result = s_vkWriteAccelerationStructuresPropertiesKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride)
#endif
#ifndef VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_POST
#define VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_POST(...) return result
#endif

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
#ifndef VKCMDTRACERAYSKHR_PRE
#define VKCMDTRACERAYSKHR_PRE(...)
#endif
#ifndef VKCMDTRACERAYSKHR
#define VKCMDTRACERAYSKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth) s_vkCmdTraceRaysKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth)
#endif
#ifndef VKCMDTRACERAYSKHR_POST
#define VKCMDTRACERAYSKHR_POST(...)
#endif

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
#ifndef VKCMDTRACERAYSNV_PRE
#define VKCMDTRACERAYSNV_PRE(...)
#endif
#ifndef VKCMDTRACERAYSNV
#define VKCMDTRACERAYSNV(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth) s_vkCmdTraceRaysNV(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth)
#endif
#ifndef VKCMDTRACERAYSNV_POST
#define VKCMDTRACERAYSNV_POST(...)
#endif

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
#ifndef VKGETRAYTRACINGSHADERGROUPHANDLESKHR_PRE
#define VKGETRAYTRACINGSHADERGROUPHANDLESKHR_PRE(...)
#endif
#ifndef VKGETRAYTRACINGSHADERGROUPHANDLESKHR
#define VKGETRAYTRACINGSHADERGROUPHANDLESKHR(device, pipeline, firstGroup, groupCount, dataSize, pData) VkResult result = s_vkGetRayTracingShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData)
#endif
#ifndef VKGETRAYTRACINGSHADERGROUPHANDLESKHR_POST
#define VKGETRAYTRACINGSHADERGROUPHANDLESKHR_POST(...) return result
#endif

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
#ifndef VKGETRAYTRACINGSHADERGROUPHANDLESNV_PRE
#define VKGETRAYTRACINGSHADERGROUPHANDLESNV_PRE(...)
#endif
#ifndef VKGETRAYTRACINGSHADERGROUPHANDLESNV
#define VKGETRAYTRACINGSHADERGROUPHANDLESNV(device, pipeline, firstGroup, groupCount, dataSize, pData) VkResult result = s_vkGetRayTracingShaderGroupHandlesNV(device, pipeline, firstGroup, groupCount, dataSize, pData)
#endif
#ifndef VKGETRAYTRACINGSHADERGROUPHANDLESNV_POST
#define VKGETRAYTRACINGSHADERGROUPHANDLESNV_POST(...) return result
#endif

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
#ifndef VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR_PRE
#define VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR_PRE(...)
#endif
#ifndef VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR
#define VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR(device, pipeline, firstGroup, groupCount, dataSize, pData) VkResult result = s_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData)
#endif
#ifndef VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR_POST
#define VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR_POST(...) return result
#endif

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
#ifndef VKGETACCELERATIONSTRUCTUREHANDLENV_PRE
#define VKGETACCELERATIONSTRUCTUREHANDLENV_PRE(...)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREHANDLENV
#define VKGETACCELERATIONSTRUCTUREHANDLENV(device, accelerationStructure, dataSize, pData) VkResult result = s_vkGetAccelerationStructureHandleNV(device, accelerationStructure, dataSize, pData)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREHANDLENV_POST
#define VKGETACCELERATIONSTRUCTUREHANDLENV_POST(...) return result
#endif

#ifndef VKCREATERAYTRACINGPIPELINESNV_PRE
#define VKCREATERAYTRACINGPIPELINESNV_PRE(...)
#endif
#ifndef VKCREATERAYTRACINGPIPELINESNV
#define VKCREATERAYTRACINGPIPELINESNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines) VkResult result = s_vkCreateRayTracingPipelinesNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines)
#endif
#ifndef VKCREATERAYTRACINGPIPELINESNV_POST
#define VKCREATERAYTRACINGPIPELINESNV_POST(...) return result
#endif

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
#ifndef VKCREATERAYTRACINGPIPELINESKHR_PRE
#define VKCREATERAYTRACINGPIPELINESKHR_PRE(...)
#endif
#ifndef VKCREATERAYTRACINGPIPELINESKHR
#define VKCREATERAYTRACINGPIPELINESKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines) VkResult result = s_vkCreateRayTracingPipelinesKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines)
#endif
#ifndef VKCREATERAYTRACINGPIPELINESKHR_POST
#define VKCREATERAYTRACINGPIPELINESKHR_POST(...) return result
#endif

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_cooperative_matrix)
#ifndef VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV_PRE
#define VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV
#define VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV(physicalDevice, pPropertyCount, pProperties) VkResult result = s_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice, pPropertyCount, pProperties)
#endif
#ifndef VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV_POST
#define VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV_POST(...) return result
#endif

#endif // VK_NV_cooperative_matrix

#if defined(VK_KHR_ray_tracing_pipeline)
#ifndef VKCMDTRACERAYSINDIRECTKHR_PRE
#define VKCMDTRACERAYSINDIRECTKHR_PRE(...)
#endif
#ifndef VKCMDTRACERAYSINDIRECTKHR
#define VKCMDTRACERAYSINDIRECTKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress) s_vkCmdTraceRaysIndirectKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress)
#endif
#ifndef VKCMDTRACERAYSINDIRECTKHR_POST
#define VKCMDTRACERAYSINDIRECTKHR_POST(...)
#endif

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_ray_tracing_maintenance1)
#ifndef VKCMDTRACERAYSINDIRECT2KHR_PRE
#define VKCMDTRACERAYSINDIRECT2KHR_PRE(...)
#endif
#ifndef VKCMDTRACERAYSINDIRECT2KHR
#define VKCMDTRACERAYSINDIRECT2KHR(commandBuffer, indirectDeviceAddress) s_vkCmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress)
#endif
#ifndef VKCMDTRACERAYSINDIRECT2KHR_POST
#define VKCMDTRACERAYSINDIRECT2KHR_POST(...)
#endif

#endif // VK_KHR_ray_tracing_maintenance1

#if defined(VK_KHR_acceleration_structure)
#ifndef VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR_PRE
#define VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR_PRE(...)
#endif
#ifndef VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR
#define VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR(device, pVersionInfo, pCompatibility) s_vkGetDeviceAccelerationStructureCompatibilityKHR(device, pVersionInfo, pCompatibility)
#endif
#ifndef VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR_POST
#define VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR_POST(...)
#endif

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
#ifndef VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR_PRE
#define VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR_PRE(...)
#endif
#ifndef VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR
#define VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR(device, pipeline, group, groupShader) VkDeviceSize result = s_vkGetRayTracingShaderGroupStackSizeKHR(device, pipeline, group, groupShader)
#endif
#ifndef VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR_POST
#define VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR_POST(...) return result
#endif

#ifndef VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR_PRE
#define VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR_PRE(...)
#endif
#ifndef VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR
#define VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR(commandBuffer, pipelineStackSize) s_vkCmdSetRayTracingPipelineStackSizeKHR(commandBuffer, pipelineStackSize)
#endif
#ifndef VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR_POST
#define VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR_POST(...)
#endif

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NVX_image_view_handle)
#ifndef VKGETIMAGEVIEWHANDLENVX_PRE
#define VKGETIMAGEVIEWHANDLENVX_PRE(...)
#endif
#ifndef VKGETIMAGEVIEWHANDLENVX
#define VKGETIMAGEVIEWHANDLENVX(device, pInfo) uint32_t result = s_vkGetImageViewHandleNVX(device, pInfo)
#endif
#ifndef VKGETIMAGEVIEWHANDLENVX_POST
#define VKGETIMAGEVIEWHANDLENVX_POST(...) return result
#endif

#ifndef VKGETIMAGEVIEWADDRESSNVX_PRE
#define VKGETIMAGEVIEWADDRESSNVX_PRE(...)
#endif
#ifndef VKGETIMAGEVIEWADDRESSNVX
#define VKGETIMAGEVIEWADDRESSNVX(device, imageView, pProperties) VkResult result = s_vkGetImageViewAddressNVX(device, imageView, pProperties)
#endif
#ifndef VKGETIMAGEVIEWADDRESSNVX_POST
#define VKGETIMAGEVIEWADDRESSNVX_POST(...) return result
#endif

#endif // VK_NVX_image_view_handle

#if defined(VK_EXT_full_screen_exclusive)
#ifndef VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT_PRE
#define VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT
#define VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes) VkResult result = s_vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes)
#endif
#ifndef VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT_POST
#define VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT_POST(...) return result
#endif

#ifndef VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT_PRE
#define VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT_PRE(...)
#endif
#ifndef VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT
#define VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT(device, pSurfaceInfo, pModes) VkResult result = s_vkGetDeviceGroupSurfacePresentModes2EXT(device, pSurfaceInfo, pModes)
#endif
#ifndef VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT_POST
#define VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT_POST(...) return result
#endif

#ifndef VKACQUIREFULLSCREENEXCLUSIVEMODEEXT_PRE
#define VKACQUIREFULLSCREENEXCLUSIVEMODEEXT_PRE(...)
#endif
#ifndef VKACQUIREFULLSCREENEXCLUSIVEMODEEXT
#define VKACQUIREFULLSCREENEXCLUSIVEMODEEXT(device, swapchain) VkResult result = s_vkAcquireFullScreenExclusiveModeEXT(device, swapchain)
#endif
#ifndef VKACQUIREFULLSCREENEXCLUSIVEMODEEXT_POST
#define VKACQUIREFULLSCREENEXCLUSIVEMODEEXT_POST(...) return result
#endif

#ifndef VKRELEASEFULLSCREENEXCLUSIVEMODEEXT_PRE
#define VKRELEASEFULLSCREENEXCLUSIVEMODEEXT_PRE(...)
#endif
#ifndef VKRELEASEFULLSCREENEXCLUSIVEMODEEXT
#define VKRELEASEFULLSCREENEXCLUSIVEMODEEXT(device, swapchain) VkResult result = s_vkReleaseFullScreenExclusiveModeEXT(device, swapchain)
#endif
#ifndef VKRELEASEFULLSCREENEXCLUSIVEMODEEXT_POST
#define VKRELEASEFULLSCREENEXCLUSIVEMODEEXT_POST(...) return result
#endif

#endif // VK_EXT_full_screen_exclusive

#if defined(VK_VERSION_1_2)
#ifndef VKGETBUFFEROPAQUECAPTUREADDRESS_PRE
#define VKGETBUFFEROPAQUECAPTUREADDRESS_PRE(...)
#endif
#ifndef VKGETBUFFEROPAQUECAPTUREADDRESS
#define VKGETBUFFEROPAQUECAPTUREADDRESS(device, pInfo) uint64_t result = s_vkGetBufferOpaqueCaptureAddress(device, pInfo)
#endif
#ifndef VKGETBUFFEROPAQUECAPTUREADDRESS_POST
#define VKGETBUFFEROPAQUECAPTUREADDRESS_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
#ifndef VKGETBUFFEROPAQUECAPTUREADDRESSKHR_PRE
#define VKGETBUFFEROPAQUECAPTUREADDRESSKHR_PRE(...)
#endif
#ifndef VKGETBUFFEROPAQUECAPTUREADDRESSKHR
#define VKGETBUFFEROPAQUECAPTUREADDRESSKHR(device, pInfo) uint64_t result = s_vkGetBufferOpaqueCaptureAddressKHR(device, pInfo)
#endif
#ifndef VKGETBUFFEROPAQUECAPTUREADDRESSKHR_POST
#define VKGETBUFFEROPAQUECAPTUREADDRESSKHR_POST(...) return result
#endif

#endif // VK_KHR_buffer_device_address

#if defined(VK_VERSION_1_2)
#ifndef VKGETBUFFERDEVICEADDRESS_PRE
#define VKGETBUFFERDEVICEADDRESS_PRE(...)
#endif
#ifndef VKGETBUFFERDEVICEADDRESS
#define VKGETBUFFERDEVICEADDRESS(device, pInfo) VkDeviceAddress result = s_vkGetBufferDeviceAddress(device, pInfo)
#endif
#ifndef VKGETBUFFERDEVICEADDRESS_POST
#define VKGETBUFFERDEVICEADDRESS_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
#ifndef VKGETBUFFERDEVICEADDRESSKHR_PRE
#define VKGETBUFFERDEVICEADDRESSKHR_PRE(...)
#endif
#ifndef VKGETBUFFERDEVICEADDRESSKHR
#define VKGETBUFFERDEVICEADDRESSKHR(device, pInfo) VkDeviceAddress result = s_vkGetBufferDeviceAddressKHR(device, pInfo)
#endif
#ifndef VKGETBUFFERDEVICEADDRESSKHR_POST
#define VKGETBUFFERDEVICEADDRESSKHR_POST(...) return result
#endif

#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_buffer_device_address)
#ifndef VKGETBUFFERDEVICEADDRESSEXT_PRE
#define VKGETBUFFERDEVICEADDRESSEXT_PRE(...)
#endif
#ifndef VKGETBUFFERDEVICEADDRESSEXT
#define VKGETBUFFERDEVICEADDRESSEXT(device, pInfo) VkDeviceAddress result = s_vkGetBufferDeviceAddressEXT(device, pInfo)
#endif
#ifndef VKGETBUFFERDEVICEADDRESSEXT_POST
#define VKGETBUFFERDEVICEADDRESSEXT_POST(...) return result
#endif

#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_headless_surface)
#ifndef VKCREATEHEADLESSSURFACEEXT_PRE
#define VKCREATEHEADLESSSURFACEEXT_PRE(...)
#endif
#ifndef VKCREATEHEADLESSSURFACEEXT
#define VKCREATEHEADLESSSURFACEEXT(instance, pCreateInfo, pAllocator, pSurface) VkResult result = s_vkCreateHeadlessSurfaceEXT(instance, pCreateInfo, pAllocator, pSurface)
#endif
#ifndef VKCREATEHEADLESSSURFACEEXT_POST
#define VKCREATEHEADLESSSURFACEEXT_POST(...) return result
#endif

#endif // VK_EXT_headless_surface

#if defined(VK_NV_coverage_reduction_mode)
#ifndef VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV_PRE
#define VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV
#define VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV(physicalDevice, pCombinationCount, pCombinations) VkResult result = s_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice, pCombinationCount, pCombinations)
#endif
#ifndef VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV_POST
#define VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV_POST(...) return result
#endif

#endif // VK_NV_coverage_reduction_mode

#if defined(VK_VERSION_1_2)
#ifndef VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS_PRE
#define VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS_PRE(...)
#endif
#ifndef VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS
#define VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS(device, pInfo) uint64_t result = s_vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo)
#endif
#ifndef VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS_POST
#define VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS_POST(...) return result
#endif

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
#ifndef VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR_PRE
#define VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR_PRE(...)
#endif
#ifndef VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR
#define VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR(device, pInfo) uint64_t result = s_vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, pInfo)
#endif
#ifndef VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR_POST
#define VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR_POST(...) return result
#endif

#endif // VK_KHR_buffer_device_address

#if defined(VK_KHR_pipeline_executable_properties)
#ifndef VKGETPIPELINEEXECUTABLEPROPERTIESKHR_PRE
#define VKGETPIPELINEEXECUTABLEPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPIPELINEEXECUTABLEPROPERTIESKHR
#define VKGETPIPELINEEXECUTABLEPROPERTIESKHR(device, pPipelineInfo, pExecutableCount, pProperties) VkResult result = s_vkGetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties)
#endif
#ifndef VKGETPIPELINEEXECUTABLEPROPERTIESKHR_POST
#define VKGETPIPELINEEXECUTABLEPROPERTIESKHR_POST(...) return result
#endif

#ifndef VKGETPIPELINEEXECUTABLESTATISTICSKHR_PRE
#define VKGETPIPELINEEXECUTABLESTATISTICSKHR_PRE(...)
#endif
#ifndef VKGETPIPELINEEXECUTABLESTATISTICSKHR
#define VKGETPIPELINEEXECUTABLESTATISTICSKHR(device, pExecutableInfo, pStatisticCount, pStatistics) VkResult result = s_vkGetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics)
#endif
#ifndef VKGETPIPELINEEXECUTABLESTATISTICSKHR_POST
#define VKGETPIPELINEEXECUTABLESTATISTICSKHR_POST(...) return result
#endif

#ifndef VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR_PRE
#define VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR_PRE(...)
#endif
#ifndef VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR
#define VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations) VkResult result = s_vkGetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations)
#endif
#ifndef VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR_POST
#define VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR_POST(...) return result
#endif

#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_EXT_line_rasterization)
#ifndef VKCMDSETLINESTIPPLEEXT_PRE
#define VKCMDSETLINESTIPPLEEXT_PRE(...)
#endif
#ifndef VKCMDSETLINESTIPPLEEXT
#define VKCMDSETLINESTIPPLEEXT(commandBuffer, lineStippleFactor, lineStipplePattern) s_vkCmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern)
#endif
#ifndef VKCMDSETLINESTIPPLEEXT_POST
#define VKCMDSETLINESTIPPLEEXT_POST(...)
#endif

#endif // VK_EXT_line_rasterization

#if defined(VKSC_VERSION_1_0)
#ifndef VKGETFAULTDATA_PRE
#define VKGETFAULTDATA_PRE(...)
#endif
#ifndef VKGETFAULTDATA
#define VKGETFAULTDATA(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults) VkResult result = s_vkGetFaultData(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults)
#endif
#ifndef VKGETFAULTDATA_POST
#define VKGETFAULTDATA_POST(...) return result
#endif

#endif // VKSC_VERSION_1_0

#if defined(VK_VERSION_1_3)
#ifndef VKGETPHYSICALDEVICETOOLPROPERTIES_PRE
#define VKGETPHYSICALDEVICETOOLPROPERTIES_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICETOOLPROPERTIES
#define VKGETPHYSICALDEVICETOOLPROPERTIES(physicalDevice, pToolCount, pToolProperties) VkResult result = s_vkGetPhysicalDeviceToolProperties(physicalDevice, pToolCount, pToolProperties)
#endif
#ifndef VKGETPHYSICALDEVICETOOLPROPERTIES_POST
#define VKGETPHYSICALDEVICETOOLPROPERTIES_POST(...) return result
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_tooling_info)
#ifndef VKGETPHYSICALDEVICETOOLPROPERTIESEXT_PRE
#define VKGETPHYSICALDEVICETOOLPROPERTIESEXT_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICETOOLPROPERTIESEXT
#define VKGETPHYSICALDEVICETOOLPROPERTIESEXT(physicalDevice, pToolCount, pToolProperties) VkResult result = s_vkGetPhysicalDeviceToolPropertiesEXT(physicalDevice, pToolCount, pToolProperties)
#endif
#ifndef VKGETPHYSICALDEVICETOOLPROPERTIESEXT_POST
#define VKGETPHYSICALDEVICETOOLPROPERTIESEXT_POST(...) return result
#endif

#endif // VK_EXT_tooling_info

#if defined(VK_KHR_acceleration_structure)
#ifndef VKCREATEACCELERATIONSTRUCTUREKHR_PRE
#define VKCREATEACCELERATIONSTRUCTUREKHR_PRE(...)
#endif
#ifndef VKCREATEACCELERATIONSTRUCTUREKHR
#define VKCREATEACCELERATIONSTRUCTUREKHR(device, pCreateInfo, pAllocator, pAccelerationStructure) VkResult result = s_vkCreateAccelerationStructureKHR(device, pCreateInfo, pAllocator, pAccelerationStructure)
#endif
#ifndef VKCREATEACCELERATIONSTRUCTUREKHR_POST
#define VKCREATEACCELERATIONSTRUCTUREKHR_POST(...) return result
#endif

#ifndef VKCMDBUILDACCELERATIONSTRUCTURESKHR_PRE
#define VKCMDBUILDACCELERATIONSTRUCTURESKHR_PRE(...)
#endif
#ifndef VKCMDBUILDACCELERATIONSTRUCTURESKHR
#define VKCMDBUILDACCELERATIONSTRUCTURESKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos) s_vkCmdBuildAccelerationStructuresKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos)
#endif
#ifndef VKCMDBUILDACCELERATIONSTRUCTURESKHR_POST
#define VKCMDBUILDACCELERATIONSTRUCTURESKHR_POST(...)
#endif

#ifndef VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR_PRE
#define VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR_PRE(...)
#endif
#ifndef VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR
#define VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts) s_vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts)
#endif
#ifndef VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR_POST
#define VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR_POST(...)
#endif

#ifndef VKBUILDACCELERATIONSTRUCTURESKHR_PRE
#define VKBUILDACCELERATIONSTRUCTURESKHR_PRE(...)
#endif
#ifndef VKBUILDACCELERATIONSTRUCTURESKHR
#define VKBUILDACCELERATIONSTRUCTURESKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos) VkResult result = s_vkBuildAccelerationStructuresKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos)
#endif
#ifndef VKBUILDACCELERATIONSTRUCTURESKHR_POST
#define VKBUILDACCELERATIONSTRUCTURESKHR_POST(...) return result
#endif

#ifndef VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR_PRE
#define VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR_PRE(...)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR
#define VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR(device, pInfo) VkDeviceAddress result = s_vkGetAccelerationStructureDeviceAddressKHR(device, pInfo)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR_POST
#define VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR_POST(...) return result
#endif

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_deferred_host_operations)
#ifndef VKCREATEDEFERREDOPERATIONKHR_PRE
#define VKCREATEDEFERREDOPERATIONKHR_PRE(...)
#endif
#ifndef VKCREATEDEFERREDOPERATIONKHR
#define VKCREATEDEFERREDOPERATIONKHR(device, pAllocator, pDeferredOperation) VkResult result = s_vkCreateDeferredOperationKHR(device, pAllocator, pDeferredOperation)
#endif
#ifndef VKCREATEDEFERREDOPERATIONKHR_POST
#define VKCREATEDEFERREDOPERATIONKHR_POST(...) return result
#endif

#ifndef VKDESTROYDEFERREDOPERATIONKHR_PRE
#define VKDESTROYDEFERREDOPERATIONKHR_PRE(...)
#endif
#ifndef VKDESTROYDEFERREDOPERATIONKHR
#define VKDESTROYDEFERREDOPERATIONKHR(device, operation, pAllocator) s_vkDestroyDeferredOperationKHR(device, operation, pAllocator)
#endif
#ifndef VKDESTROYDEFERREDOPERATIONKHR_POST
#define VKDESTROYDEFERREDOPERATIONKHR_POST(...)
#endif

#ifndef VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR_PRE
#define VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR_PRE(...)
#endif
#ifndef VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR
#define VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR(device, operation) uint32_t result = s_vkGetDeferredOperationMaxConcurrencyKHR(device, operation)
#endif
#ifndef VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR_POST
#define VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR_POST(...) return result
#endif

#ifndef VKGETDEFERREDOPERATIONRESULTKHR_PRE
#define VKGETDEFERREDOPERATIONRESULTKHR_PRE(...)
#endif
#ifndef VKGETDEFERREDOPERATIONRESULTKHR
#define VKGETDEFERREDOPERATIONRESULTKHR(device, operation) VkResult result = s_vkGetDeferredOperationResultKHR(device, operation)
#endif
#ifndef VKGETDEFERREDOPERATIONRESULTKHR_POST
#define VKGETDEFERREDOPERATIONRESULTKHR_POST(...) return result
#endif

#ifndef VKDEFERREDOPERATIONJOINKHR_PRE
#define VKDEFERREDOPERATIONJOINKHR_PRE(...)
#endif
#ifndef VKDEFERREDOPERATIONJOINKHR
#define VKDEFERREDOPERATIONJOINKHR(device, operation) VkResult result = s_vkDeferredOperationJoinKHR(device, operation)
#endif
#ifndef VKDEFERREDOPERATIONJOINKHR_POST
#define VKDEFERREDOPERATIONJOINKHR_POST(...) return result
#endif

#endif // VK_KHR_deferred_host_operations

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETCULLMODE_PRE
#define VKCMDSETCULLMODE_PRE(...)
#endif
#ifndef VKCMDSETCULLMODE
#define VKCMDSETCULLMODE(commandBuffer, cullMode) s_vkCmdSetCullMode(commandBuffer, cullMode)
#endif
#ifndef VKCMDSETCULLMODE_POST
#define VKCMDSETCULLMODE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETCULLMODEEXT_PRE
#define VKCMDSETCULLMODEEXT_PRE(...)
#endif
#ifndef VKCMDSETCULLMODEEXT
#define VKCMDSETCULLMODEEXT(commandBuffer, cullMode) s_vkCmdSetCullModeEXT(commandBuffer, cullMode)
#endif
#ifndef VKCMDSETCULLMODEEXT_POST
#define VKCMDSETCULLMODEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETFRONTFACE_PRE
#define VKCMDSETFRONTFACE_PRE(...)
#endif
#ifndef VKCMDSETFRONTFACE
#define VKCMDSETFRONTFACE(commandBuffer, frontFace) s_vkCmdSetFrontFace(commandBuffer, frontFace)
#endif
#ifndef VKCMDSETFRONTFACE_POST
#define VKCMDSETFRONTFACE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETFRONTFACEEXT_PRE
#define VKCMDSETFRONTFACEEXT_PRE(...)
#endif
#ifndef VKCMDSETFRONTFACEEXT
#define VKCMDSETFRONTFACEEXT(commandBuffer, frontFace) s_vkCmdSetFrontFaceEXT(commandBuffer, frontFace)
#endif
#ifndef VKCMDSETFRONTFACEEXT_POST
#define VKCMDSETFRONTFACEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETPRIMITIVETOPOLOGY_PRE
#define VKCMDSETPRIMITIVETOPOLOGY_PRE(...)
#endif
#ifndef VKCMDSETPRIMITIVETOPOLOGY
#define VKCMDSETPRIMITIVETOPOLOGY(commandBuffer, primitiveTopology) s_vkCmdSetPrimitiveTopology(commandBuffer, primitiveTopology)
#endif
#ifndef VKCMDSETPRIMITIVETOPOLOGY_POST
#define VKCMDSETPRIMITIVETOPOLOGY_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETPRIMITIVETOPOLOGYEXT_PRE
#define VKCMDSETPRIMITIVETOPOLOGYEXT_PRE(...)
#endif
#ifndef VKCMDSETPRIMITIVETOPOLOGYEXT
#define VKCMDSETPRIMITIVETOPOLOGYEXT(commandBuffer, primitiveTopology) s_vkCmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology)
#endif
#ifndef VKCMDSETPRIMITIVETOPOLOGYEXT_POST
#define VKCMDSETPRIMITIVETOPOLOGYEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETVIEWPORTWITHCOUNT_PRE
#define VKCMDSETVIEWPORTWITHCOUNT_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORTWITHCOUNT
#define VKCMDSETVIEWPORTWITHCOUNT(commandBuffer, viewportCount, pViewports) s_vkCmdSetViewportWithCount(commandBuffer, viewportCount, pViewports)
#endif
#ifndef VKCMDSETVIEWPORTWITHCOUNT_POST
#define VKCMDSETVIEWPORTWITHCOUNT_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETVIEWPORTWITHCOUNTEXT_PRE
#define VKCMDSETVIEWPORTWITHCOUNTEXT_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORTWITHCOUNTEXT
#define VKCMDSETVIEWPORTWITHCOUNTEXT(commandBuffer, viewportCount, pViewports) s_vkCmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports)
#endif
#ifndef VKCMDSETVIEWPORTWITHCOUNTEXT_POST
#define VKCMDSETVIEWPORTWITHCOUNTEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETSCISSORWITHCOUNT_PRE
#define VKCMDSETSCISSORWITHCOUNT_PRE(...)
#endif
#ifndef VKCMDSETSCISSORWITHCOUNT
#define VKCMDSETSCISSORWITHCOUNT(commandBuffer, scissorCount, pScissors) s_vkCmdSetScissorWithCount(commandBuffer, scissorCount, pScissors)
#endif
#ifndef VKCMDSETSCISSORWITHCOUNT_POST
#define VKCMDSETSCISSORWITHCOUNT_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETSCISSORWITHCOUNTEXT_PRE
#define VKCMDSETSCISSORWITHCOUNTEXT_PRE(...)
#endif
#ifndef VKCMDSETSCISSORWITHCOUNTEXT
#define VKCMDSETSCISSORWITHCOUNTEXT(commandBuffer, scissorCount, pScissors) s_vkCmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors)
#endif
#ifndef VKCMDSETSCISSORWITHCOUNTEXT_POST
#define VKCMDSETSCISSORWITHCOUNTEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDBINDVERTEXBUFFERS2_PRE
#define VKCMDBINDVERTEXBUFFERS2_PRE(...)
#endif
#ifndef VKCMDBINDVERTEXBUFFERS2
#define VKCMDBINDVERTEXBUFFERS2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides) s_vkCmdBindVertexBuffers2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides)
#endif
#ifndef VKCMDBINDVERTEXBUFFERS2_POST
#define VKCMDBINDVERTEXBUFFERS2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDBINDVERTEXBUFFERS2EXT_PRE
#define VKCMDBINDVERTEXBUFFERS2EXT_PRE(...)
#endif
#ifndef VKCMDBINDVERTEXBUFFERS2EXT
#define VKCMDBINDVERTEXBUFFERS2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides) s_vkCmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides)
#endif
#ifndef VKCMDBINDVERTEXBUFFERS2EXT_POST
#define VKCMDBINDVERTEXBUFFERS2EXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETDEPTHTESTENABLE_PRE
#define VKCMDSETDEPTHTESTENABLE_PRE(...)
#endif
#ifndef VKCMDSETDEPTHTESTENABLE
#define VKCMDSETDEPTHTESTENABLE(commandBuffer, depthTestEnable) s_vkCmdSetDepthTestEnable(commandBuffer, depthTestEnable)
#endif
#ifndef VKCMDSETDEPTHTESTENABLE_POST
#define VKCMDSETDEPTHTESTENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETDEPTHTESTENABLEEXT_PRE
#define VKCMDSETDEPTHTESTENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHTESTENABLEEXT
#define VKCMDSETDEPTHTESTENABLEEXT(commandBuffer, depthTestEnable) s_vkCmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable)
#endif
#ifndef VKCMDSETDEPTHTESTENABLEEXT_POST
#define VKCMDSETDEPTHTESTENABLEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETDEPTHWRITEENABLE_PRE
#define VKCMDSETDEPTHWRITEENABLE_PRE(...)
#endif
#ifndef VKCMDSETDEPTHWRITEENABLE
#define VKCMDSETDEPTHWRITEENABLE(commandBuffer, depthWriteEnable) s_vkCmdSetDepthWriteEnable(commandBuffer, depthWriteEnable)
#endif
#ifndef VKCMDSETDEPTHWRITEENABLE_POST
#define VKCMDSETDEPTHWRITEENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETDEPTHWRITEENABLEEXT_PRE
#define VKCMDSETDEPTHWRITEENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHWRITEENABLEEXT
#define VKCMDSETDEPTHWRITEENABLEEXT(commandBuffer, depthWriteEnable) s_vkCmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable)
#endif
#ifndef VKCMDSETDEPTHWRITEENABLEEXT_POST
#define VKCMDSETDEPTHWRITEENABLEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETDEPTHCOMPAREOP_PRE
#define VKCMDSETDEPTHCOMPAREOP_PRE(...)
#endif
#ifndef VKCMDSETDEPTHCOMPAREOP
#define VKCMDSETDEPTHCOMPAREOP(commandBuffer, depthCompareOp) s_vkCmdSetDepthCompareOp(commandBuffer, depthCompareOp)
#endif
#ifndef VKCMDSETDEPTHCOMPAREOP_POST
#define VKCMDSETDEPTHCOMPAREOP_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETDEPTHCOMPAREOPEXT_PRE
#define VKCMDSETDEPTHCOMPAREOPEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHCOMPAREOPEXT
#define VKCMDSETDEPTHCOMPAREOPEXT(commandBuffer, depthCompareOp) s_vkCmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp)
#endif
#ifndef VKCMDSETDEPTHCOMPAREOPEXT_POST
#define VKCMDSETDEPTHCOMPAREOPEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETDEPTHBOUNDSTESTENABLE_PRE
#define VKCMDSETDEPTHBOUNDSTESTENABLE_PRE(...)
#endif
#ifndef VKCMDSETDEPTHBOUNDSTESTENABLE
#define VKCMDSETDEPTHBOUNDSTESTENABLE(commandBuffer, depthBoundsTestEnable) s_vkCmdSetDepthBoundsTestEnable(commandBuffer, depthBoundsTestEnable)
#endif
#ifndef VKCMDSETDEPTHBOUNDSTESTENABLE_POST
#define VKCMDSETDEPTHBOUNDSTESTENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETDEPTHBOUNDSTESTENABLEEXT_PRE
#define VKCMDSETDEPTHBOUNDSTESTENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHBOUNDSTESTENABLEEXT
#define VKCMDSETDEPTHBOUNDSTESTENABLEEXT(commandBuffer, depthBoundsTestEnable) s_vkCmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable)
#endif
#ifndef VKCMDSETDEPTHBOUNDSTESTENABLEEXT_POST
#define VKCMDSETDEPTHBOUNDSTESTENABLEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETSTENCILTESTENABLE_PRE
#define VKCMDSETSTENCILTESTENABLE_PRE(...)
#endif
#ifndef VKCMDSETSTENCILTESTENABLE
#define VKCMDSETSTENCILTESTENABLE(commandBuffer, stencilTestEnable) s_vkCmdSetStencilTestEnable(commandBuffer, stencilTestEnable)
#endif
#ifndef VKCMDSETSTENCILTESTENABLE_POST
#define VKCMDSETSTENCILTESTENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETSTENCILTESTENABLEEXT_PRE
#define VKCMDSETSTENCILTESTENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETSTENCILTESTENABLEEXT
#define VKCMDSETSTENCILTESTENABLEEXT(commandBuffer, stencilTestEnable) s_vkCmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable)
#endif
#ifndef VKCMDSETSTENCILTESTENABLEEXT_POST
#define VKCMDSETSTENCILTESTENABLEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETSTENCILOP_PRE
#define VKCMDSETSTENCILOP_PRE(...)
#endif
#ifndef VKCMDSETSTENCILOP
#define VKCMDSETSTENCILOP(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp) s_vkCmdSetStencilOp(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp)
#endif
#ifndef VKCMDSETSTENCILOP_POST
#define VKCMDSETSTENCILOP_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETSTENCILOPEXT_PRE
#define VKCMDSETSTENCILOPEXT_PRE(...)
#endif
#ifndef VKCMDSETSTENCILOPEXT
#define VKCMDSETSTENCILOPEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp) s_vkCmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp)
#endif
#ifndef VKCMDSETSTENCILOPEXT_POST
#define VKCMDSETSTENCILOPEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETPATCHCONTROLPOINTSEXT_PRE
#define VKCMDSETPATCHCONTROLPOINTSEXT_PRE(...)
#endif
#ifndef VKCMDSETPATCHCONTROLPOINTSEXT
#define VKCMDSETPATCHCONTROLPOINTSEXT(commandBuffer, patchControlPoints) s_vkCmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints)
#endif
#ifndef VKCMDSETPATCHCONTROLPOINTSEXT_POST
#define VKCMDSETPATCHCONTROLPOINTSEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETRASTERIZERDISCARDENABLE_PRE
#define VKCMDSETRASTERIZERDISCARDENABLE_PRE(...)
#endif
#ifndef VKCMDSETRASTERIZERDISCARDENABLE
#define VKCMDSETRASTERIZERDISCARDENABLE(commandBuffer, rasterizerDiscardEnable) s_vkCmdSetRasterizerDiscardEnable(commandBuffer, rasterizerDiscardEnable)
#endif
#ifndef VKCMDSETRASTERIZERDISCARDENABLE_POST
#define VKCMDSETRASTERIZERDISCARDENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETRASTERIZERDISCARDENABLEEXT_PRE
#define VKCMDSETRASTERIZERDISCARDENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETRASTERIZERDISCARDENABLEEXT
#define VKCMDSETRASTERIZERDISCARDENABLEEXT(commandBuffer, rasterizerDiscardEnable) s_vkCmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable)
#endif
#ifndef VKCMDSETRASTERIZERDISCARDENABLEEXT_POST
#define VKCMDSETRASTERIZERDISCARDENABLEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETDEPTHBIASENABLE_PRE
#define VKCMDSETDEPTHBIASENABLE_PRE(...)
#endif
#ifndef VKCMDSETDEPTHBIASENABLE
#define VKCMDSETDEPTHBIASENABLE(commandBuffer, depthBiasEnable) s_vkCmdSetDepthBiasEnable(commandBuffer, depthBiasEnable)
#endif
#ifndef VKCMDSETDEPTHBIASENABLE_POST
#define VKCMDSETDEPTHBIASENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETDEPTHBIASENABLEEXT_PRE
#define VKCMDSETDEPTHBIASENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHBIASENABLEEXT
#define VKCMDSETDEPTHBIASENABLEEXT(commandBuffer, depthBiasEnable) s_vkCmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable)
#endif
#ifndef VKCMDSETDEPTHBIASENABLEEXT_POST
#define VKCMDSETDEPTHBIASENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETLOGICOPEXT_PRE
#define VKCMDSETLOGICOPEXT_PRE(...)
#endif
#ifndef VKCMDSETLOGICOPEXT
#define VKCMDSETLOGICOPEXT(commandBuffer, logicOp) s_vkCmdSetLogicOpEXT(commandBuffer, logicOp)
#endif
#ifndef VKCMDSETLOGICOPEXT_POST
#define VKCMDSETLOGICOPEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETPRIMITIVERESTARTENABLE_PRE
#define VKCMDSETPRIMITIVERESTARTENABLE_PRE(...)
#endif
#ifndef VKCMDSETPRIMITIVERESTARTENABLE
#define VKCMDSETPRIMITIVERESTARTENABLE(commandBuffer, primitiveRestartEnable) s_vkCmdSetPrimitiveRestartEnable(commandBuffer, primitiveRestartEnable)
#endif
#ifndef VKCMDSETPRIMITIVERESTARTENABLE_POST
#define VKCMDSETPRIMITIVERESTARTENABLE_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETPRIMITIVERESTARTENABLEEXT_PRE
#define VKCMDSETPRIMITIVERESTARTENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETPRIMITIVERESTARTENABLEEXT
#define VKCMDSETPRIMITIVERESTARTENABLEEXT(commandBuffer, primitiveRestartEnable) s_vkCmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable)
#endif
#ifndef VKCMDSETPRIMITIVERESTARTENABLEEXT_POST
#define VKCMDSETPRIMITIVERESTARTENABLEEXT_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state3) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETTESSELLATIONDOMAINORIGINEXT_PRE
#define VKCMDSETTESSELLATIONDOMAINORIGINEXT_PRE(...)
#endif
#ifndef VKCMDSETTESSELLATIONDOMAINORIGINEXT
#define VKCMDSETTESSELLATIONDOMAINORIGINEXT(commandBuffer, domainOrigin) s_vkCmdSetTessellationDomainOriginEXT(commandBuffer, domainOrigin)
#endif
#ifndef VKCMDSETTESSELLATIONDOMAINORIGINEXT_POST
#define VKCMDSETTESSELLATIONDOMAINORIGINEXT_POST(...)
#endif

#ifndef VKCMDSETDEPTHCLAMPENABLEEXT_PRE
#define VKCMDSETDEPTHCLAMPENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHCLAMPENABLEEXT
#define VKCMDSETDEPTHCLAMPENABLEEXT(commandBuffer, depthClampEnable) s_vkCmdSetDepthClampEnableEXT(commandBuffer, depthClampEnable)
#endif
#ifndef VKCMDSETDEPTHCLAMPENABLEEXT_POST
#define VKCMDSETDEPTHCLAMPENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETPOLYGONMODEEXT_PRE
#define VKCMDSETPOLYGONMODEEXT_PRE(...)
#endif
#ifndef VKCMDSETPOLYGONMODEEXT
#define VKCMDSETPOLYGONMODEEXT(commandBuffer, polygonMode) s_vkCmdSetPolygonModeEXT(commandBuffer, polygonMode)
#endif
#ifndef VKCMDSETPOLYGONMODEEXT_POST
#define VKCMDSETPOLYGONMODEEXT_POST(...)
#endif

#ifndef VKCMDSETRASTERIZATIONSAMPLESEXT_PRE
#define VKCMDSETRASTERIZATIONSAMPLESEXT_PRE(...)
#endif
#ifndef VKCMDSETRASTERIZATIONSAMPLESEXT
#define VKCMDSETRASTERIZATIONSAMPLESEXT(commandBuffer, rasterizationSamples) s_vkCmdSetRasterizationSamplesEXT(commandBuffer, rasterizationSamples)
#endif
#ifndef VKCMDSETRASTERIZATIONSAMPLESEXT_POST
#define VKCMDSETRASTERIZATIONSAMPLESEXT_POST(...)
#endif

#ifndef VKCMDSETSAMPLEMASKEXT_PRE
#define VKCMDSETSAMPLEMASKEXT_PRE(...)
#endif
#ifndef VKCMDSETSAMPLEMASKEXT
#define VKCMDSETSAMPLEMASKEXT(commandBuffer, samples, pSampleMask) s_vkCmdSetSampleMaskEXT(commandBuffer, samples, pSampleMask)
#endif
#ifndef VKCMDSETSAMPLEMASKEXT_POST
#define VKCMDSETSAMPLEMASKEXT_POST(...)
#endif

#ifndef VKCMDSETALPHATOCOVERAGEENABLEEXT_PRE
#define VKCMDSETALPHATOCOVERAGEENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETALPHATOCOVERAGEENABLEEXT
#define VKCMDSETALPHATOCOVERAGEENABLEEXT(commandBuffer, alphaToCoverageEnable) s_vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, alphaToCoverageEnable)
#endif
#ifndef VKCMDSETALPHATOCOVERAGEENABLEEXT_POST
#define VKCMDSETALPHATOCOVERAGEENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETALPHATOONEENABLEEXT_PRE
#define VKCMDSETALPHATOONEENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETALPHATOONEENABLEEXT
#define VKCMDSETALPHATOONEENABLEEXT(commandBuffer, alphaToOneEnable) s_vkCmdSetAlphaToOneEnableEXT(commandBuffer, alphaToOneEnable)
#endif
#ifndef VKCMDSETALPHATOONEENABLEEXT_POST
#define VKCMDSETALPHATOONEENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETLOGICOPENABLEEXT_PRE
#define VKCMDSETLOGICOPENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETLOGICOPENABLEEXT
#define VKCMDSETLOGICOPENABLEEXT(commandBuffer, logicOpEnable) s_vkCmdSetLogicOpEnableEXT(commandBuffer, logicOpEnable)
#endif
#ifndef VKCMDSETLOGICOPENABLEEXT_POST
#define VKCMDSETLOGICOPENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETCOLORBLENDENABLEEXT_PRE
#define VKCMDSETCOLORBLENDENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETCOLORBLENDENABLEEXT
#define VKCMDSETCOLORBLENDENABLEEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables) s_vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables)
#endif
#ifndef VKCMDSETCOLORBLENDENABLEEXT_POST
#define VKCMDSETCOLORBLENDENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETCOLORBLENDEQUATIONEXT_PRE
#define VKCMDSETCOLORBLENDEQUATIONEXT_PRE(...)
#endif
#ifndef VKCMDSETCOLORBLENDEQUATIONEXT
#define VKCMDSETCOLORBLENDEQUATIONEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations) s_vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations)
#endif
#ifndef VKCMDSETCOLORBLENDEQUATIONEXT_POST
#define VKCMDSETCOLORBLENDEQUATIONEXT_POST(...)
#endif

#ifndef VKCMDSETCOLORWRITEMASKEXT_PRE
#define VKCMDSETCOLORWRITEMASKEXT_PRE(...)
#endif
#ifndef VKCMDSETCOLORWRITEMASKEXT
#define VKCMDSETCOLORWRITEMASKEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks) s_vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks)
#endif
#ifndef VKCMDSETCOLORWRITEMASKEXT_POST
#define VKCMDSETCOLORWRITEMASKEXT_POST(...)
#endif

#ifndef VKCMDSETRASTERIZATIONSTREAMEXT_PRE
#define VKCMDSETRASTERIZATIONSTREAMEXT_PRE(...)
#endif
#ifndef VKCMDSETRASTERIZATIONSTREAMEXT
#define VKCMDSETRASTERIZATIONSTREAMEXT(commandBuffer, rasterizationStream) s_vkCmdSetRasterizationStreamEXT(commandBuffer, rasterizationStream)
#endif
#ifndef VKCMDSETRASTERIZATIONSTREAMEXT_POST
#define VKCMDSETRASTERIZATIONSTREAMEXT_POST(...)
#endif

#ifndef VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT_PRE
#define VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT_PRE(...)
#endif
#ifndef VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT
#define VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT(commandBuffer, conservativeRasterizationMode) s_vkCmdSetConservativeRasterizationModeEXT(commandBuffer, conservativeRasterizationMode)
#endif
#ifndef VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT_POST
#define VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT_POST(...)
#endif

#ifndef VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT_PRE
#define VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT_PRE(...)
#endif
#ifndef VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT
#define VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT(commandBuffer, extraPrimitiveOverestimationSize) s_vkCmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, extraPrimitiveOverestimationSize)
#endif
#ifndef VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT_POST
#define VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT_POST(...)
#endif

#ifndef VKCMDSETDEPTHCLIPENABLEEXT_PRE
#define VKCMDSETDEPTHCLIPENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHCLIPENABLEEXT
#define VKCMDSETDEPTHCLIPENABLEEXT(commandBuffer, depthClipEnable) s_vkCmdSetDepthClipEnableEXT(commandBuffer, depthClipEnable)
#endif
#ifndef VKCMDSETDEPTHCLIPENABLEEXT_POST
#define VKCMDSETDEPTHCLIPENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETSAMPLELOCATIONSENABLEEXT_PRE
#define VKCMDSETSAMPLELOCATIONSENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETSAMPLELOCATIONSENABLEEXT
#define VKCMDSETSAMPLELOCATIONSENABLEEXT(commandBuffer, sampleLocationsEnable) s_vkCmdSetSampleLocationsEnableEXT(commandBuffer, sampleLocationsEnable)
#endif
#ifndef VKCMDSETSAMPLELOCATIONSENABLEEXT_POST
#define VKCMDSETSAMPLELOCATIONSENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETCOLORBLENDADVANCEDEXT_PRE
#define VKCMDSETCOLORBLENDADVANCEDEXT_PRE(...)
#endif
#ifndef VKCMDSETCOLORBLENDADVANCEDEXT
#define VKCMDSETCOLORBLENDADVANCEDEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced) s_vkCmdSetColorBlendAdvancedEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced)
#endif
#ifndef VKCMDSETCOLORBLENDADVANCEDEXT_POST
#define VKCMDSETCOLORBLENDADVANCEDEXT_POST(...)
#endif

#ifndef VKCMDSETPROVOKINGVERTEXMODEEXT_PRE
#define VKCMDSETPROVOKINGVERTEXMODEEXT_PRE(...)
#endif
#ifndef VKCMDSETPROVOKINGVERTEXMODEEXT
#define VKCMDSETPROVOKINGVERTEXMODEEXT(commandBuffer, provokingVertexMode) s_vkCmdSetProvokingVertexModeEXT(commandBuffer, provokingVertexMode)
#endif
#ifndef VKCMDSETPROVOKINGVERTEXMODEEXT_POST
#define VKCMDSETPROVOKINGVERTEXMODEEXT_POST(...)
#endif

#ifndef VKCMDSETLINERASTERIZATIONMODEEXT_PRE
#define VKCMDSETLINERASTERIZATIONMODEEXT_PRE(...)
#endif
#ifndef VKCMDSETLINERASTERIZATIONMODEEXT
#define VKCMDSETLINERASTERIZATIONMODEEXT(commandBuffer, lineRasterizationMode) s_vkCmdSetLineRasterizationModeEXT(commandBuffer, lineRasterizationMode)
#endif
#ifndef VKCMDSETLINERASTERIZATIONMODEEXT_POST
#define VKCMDSETLINERASTERIZATIONMODEEXT_POST(...)
#endif

#ifndef VKCMDSETLINESTIPPLEENABLEEXT_PRE
#define VKCMDSETLINESTIPPLEENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETLINESTIPPLEENABLEEXT
#define VKCMDSETLINESTIPPLEENABLEEXT(commandBuffer, stippledLineEnable) s_vkCmdSetLineStippleEnableEXT(commandBuffer, stippledLineEnable)
#endif
#ifndef VKCMDSETLINESTIPPLEENABLEEXT_POST
#define VKCMDSETLINESTIPPLEENABLEEXT_POST(...)
#endif

#ifndef VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT_PRE
#define VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT_PRE(...)
#endif
#ifndef VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT
#define VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT(commandBuffer, negativeOneToOne) s_vkCmdSetDepthClipNegativeOneToOneEXT(commandBuffer, negativeOneToOne)
#endif
#ifndef VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT_POST
#define VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT_POST(...)
#endif

#ifndef VKCMDSETVIEWPORTWSCALINGENABLENV_PRE
#define VKCMDSETVIEWPORTWSCALINGENABLENV_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORTWSCALINGENABLENV
#define VKCMDSETVIEWPORTWSCALINGENABLENV(commandBuffer, viewportWScalingEnable) s_vkCmdSetViewportWScalingEnableNV(commandBuffer, viewportWScalingEnable)
#endif
#ifndef VKCMDSETVIEWPORTWSCALINGENABLENV_POST
#define VKCMDSETVIEWPORTWSCALINGENABLENV_POST(...)
#endif

#ifndef VKCMDSETVIEWPORTSWIZZLENV_PRE
#define VKCMDSETVIEWPORTSWIZZLENV_PRE(...)
#endif
#ifndef VKCMDSETVIEWPORTSWIZZLENV
#define VKCMDSETVIEWPORTSWIZZLENV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles) s_vkCmdSetViewportSwizzleNV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles)
#endif
#ifndef VKCMDSETVIEWPORTSWIZZLENV_POST
#define VKCMDSETVIEWPORTSWIZZLENV_POST(...)
#endif

#ifndef VKCMDSETCOVERAGETOCOLORENABLENV_PRE
#define VKCMDSETCOVERAGETOCOLORENABLENV_PRE(...)
#endif
#ifndef VKCMDSETCOVERAGETOCOLORENABLENV
#define VKCMDSETCOVERAGETOCOLORENABLENV(commandBuffer, coverageToColorEnable) s_vkCmdSetCoverageToColorEnableNV(commandBuffer, coverageToColorEnable)
#endif
#ifndef VKCMDSETCOVERAGETOCOLORENABLENV_POST
#define VKCMDSETCOVERAGETOCOLORENABLENV_POST(...)
#endif

#ifndef VKCMDSETCOVERAGETOCOLORLOCATIONNV_PRE
#define VKCMDSETCOVERAGETOCOLORLOCATIONNV_PRE(...)
#endif
#ifndef VKCMDSETCOVERAGETOCOLORLOCATIONNV
#define VKCMDSETCOVERAGETOCOLORLOCATIONNV(commandBuffer, coverageToColorLocation) s_vkCmdSetCoverageToColorLocationNV(commandBuffer, coverageToColorLocation)
#endif
#ifndef VKCMDSETCOVERAGETOCOLORLOCATIONNV_POST
#define VKCMDSETCOVERAGETOCOLORLOCATIONNV_POST(...)
#endif

#ifndef VKCMDSETCOVERAGEMODULATIONMODENV_PRE
#define VKCMDSETCOVERAGEMODULATIONMODENV_PRE(...)
#endif
#ifndef VKCMDSETCOVERAGEMODULATIONMODENV
#define VKCMDSETCOVERAGEMODULATIONMODENV(commandBuffer, coverageModulationMode) s_vkCmdSetCoverageModulationModeNV(commandBuffer, coverageModulationMode)
#endif
#ifndef VKCMDSETCOVERAGEMODULATIONMODENV_POST
#define VKCMDSETCOVERAGEMODULATIONMODENV_POST(...)
#endif

#ifndef VKCMDSETCOVERAGEMODULATIONTABLEENABLENV_PRE
#define VKCMDSETCOVERAGEMODULATIONTABLEENABLENV_PRE(...)
#endif
#ifndef VKCMDSETCOVERAGEMODULATIONTABLEENABLENV
#define VKCMDSETCOVERAGEMODULATIONTABLEENABLENV(commandBuffer, coverageModulationTableEnable) s_vkCmdSetCoverageModulationTableEnableNV(commandBuffer, coverageModulationTableEnable)
#endif
#ifndef VKCMDSETCOVERAGEMODULATIONTABLEENABLENV_POST
#define VKCMDSETCOVERAGEMODULATIONTABLEENABLENV_POST(...)
#endif

#ifndef VKCMDSETCOVERAGEMODULATIONTABLENV_PRE
#define VKCMDSETCOVERAGEMODULATIONTABLENV_PRE(...)
#endif
#ifndef VKCMDSETCOVERAGEMODULATIONTABLENV
#define VKCMDSETCOVERAGEMODULATIONTABLENV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable) s_vkCmdSetCoverageModulationTableNV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable)
#endif
#ifndef VKCMDSETCOVERAGEMODULATIONTABLENV_POST
#define VKCMDSETCOVERAGEMODULATIONTABLENV_POST(...)
#endif

#ifndef VKCMDSETSHADINGRATEIMAGEENABLENV_PRE
#define VKCMDSETSHADINGRATEIMAGEENABLENV_PRE(...)
#endif
#ifndef VKCMDSETSHADINGRATEIMAGEENABLENV
#define VKCMDSETSHADINGRATEIMAGEENABLENV(commandBuffer, shadingRateImageEnable) s_vkCmdSetShadingRateImageEnableNV(commandBuffer, shadingRateImageEnable)
#endif
#ifndef VKCMDSETSHADINGRATEIMAGEENABLENV_POST
#define VKCMDSETSHADINGRATEIMAGEENABLENV_POST(...)
#endif

#ifndef VKCMDSETCOVERAGEREDUCTIONMODENV_PRE
#define VKCMDSETCOVERAGEREDUCTIONMODENV_PRE(...)
#endif
#ifndef VKCMDSETCOVERAGEREDUCTIONMODENV
#define VKCMDSETCOVERAGEREDUCTIONMODENV(commandBuffer, coverageReductionMode) s_vkCmdSetCoverageReductionModeNV(commandBuffer, coverageReductionMode)
#endif
#ifndef VKCMDSETCOVERAGEREDUCTIONMODENV_POST
#define VKCMDSETCOVERAGEREDUCTIONMODENV_POST(...)
#endif

#ifndef VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV_PRE
#define VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV_PRE(...)
#endif
#ifndef VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV
#define VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV(commandBuffer, representativeFragmentTestEnable) s_vkCmdSetRepresentativeFragmentTestEnableNV(commandBuffer, representativeFragmentTestEnable)
#endif
#ifndef VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV_POST
#define VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV_POST(...)
#endif

#endif // VK_EXT_extended_dynamic_state3 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
#ifndef VKCREATEPRIVATEDATASLOT_PRE
#define VKCREATEPRIVATEDATASLOT_PRE(...)
#endif
#ifndef VKCREATEPRIVATEDATASLOT
#define VKCREATEPRIVATEDATASLOT(device, pCreateInfo, pAllocator, pPrivateDataSlot) VkResult result = s_vkCreatePrivateDataSlot(device, pCreateInfo, pAllocator, pPrivateDataSlot)
#endif
#ifndef VKCREATEPRIVATEDATASLOT_POST
#define VKCREATEPRIVATEDATASLOT_POST(...) return result
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
#ifndef VKCREATEPRIVATEDATASLOTEXT_PRE
#define VKCREATEPRIVATEDATASLOTEXT_PRE(...)
#endif
#ifndef VKCREATEPRIVATEDATASLOTEXT
#define VKCREATEPRIVATEDATASLOTEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot) VkResult result = s_vkCreatePrivateDataSlotEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot)
#endif
#ifndef VKCREATEPRIVATEDATASLOTEXT_POST
#define VKCREATEPRIVATEDATASLOTEXT_POST(...) return result
#endif

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
#ifndef VKDESTROYPRIVATEDATASLOT_PRE
#define VKDESTROYPRIVATEDATASLOT_PRE(...)
#endif
#ifndef VKDESTROYPRIVATEDATASLOT
#define VKDESTROYPRIVATEDATASLOT(device, privateDataSlot, pAllocator) s_vkDestroyPrivateDataSlot(device, privateDataSlot, pAllocator)
#endif
#ifndef VKDESTROYPRIVATEDATASLOT_POST
#define VKDESTROYPRIVATEDATASLOT_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
#ifndef VKDESTROYPRIVATEDATASLOTEXT_PRE
#define VKDESTROYPRIVATEDATASLOTEXT_PRE(...)
#endif
#ifndef VKDESTROYPRIVATEDATASLOTEXT
#define VKDESTROYPRIVATEDATASLOTEXT(device, privateDataSlot, pAllocator) s_vkDestroyPrivateDataSlotEXT(device, privateDataSlot, pAllocator)
#endif
#ifndef VKDESTROYPRIVATEDATASLOTEXT_POST
#define VKDESTROYPRIVATEDATASLOTEXT_POST(...)
#endif

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
#ifndef VKSETPRIVATEDATA_PRE
#define VKSETPRIVATEDATA_PRE(...)
#endif
#ifndef VKSETPRIVATEDATA
#define VKSETPRIVATEDATA(device, objectType, objectHandle, privateDataSlot, data) VkResult result = s_vkSetPrivateData(device, objectType, objectHandle, privateDataSlot, data)
#endif
#ifndef VKSETPRIVATEDATA_POST
#define VKSETPRIVATEDATA_POST(...) return result
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
#ifndef VKSETPRIVATEDATAEXT_PRE
#define VKSETPRIVATEDATAEXT_PRE(...)
#endif
#ifndef VKSETPRIVATEDATAEXT
#define VKSETPRIVATEDATAEXT(device, objectType, objectHandle, privateDataSlot, data) VkResult result = s_vkSetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, data)
#endif
#ifndef VKSETPRIVATEDATAEXT_POST
#define VKSETPRIVATEDATAEXT_POST(...) return result
#endif

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
#ifndef VKGETPRIVATEDATA_PRE
#define VKGETPRIVATEDATA_PRE(...)
#endif
#ifndef VKGETPRIVATEDATA
#define VKGETPRIVATEDATA(device, objectType, objectHandle, privateDataSlot, pData) s_vkGetPrivateData(device, objectType, objectHandle, privateDataSlot, pData)
#endif
#ifndef VKGETPRIVATEDATA_POST
#define VKGETPRIVATEDATA_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
#ifndef VKGETPRIVATEDATAEXT_PRE
#define VKGETPRIVATEDATAEXT_PRE(...)
#endif
#ifndef VKGETPRIVATEDATAEXT
#define VKGETPRIVATEDATAEXT(device, objectType, objectHandle, privateDataSlot, pData) s_vkGetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, pData)
#endif
#ifndef VKGETPRIVATEDATAEXT_POST
#define VKGETPRIVATEDATAEXT_POST(...)
#endif

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
#ifndef VKCMDCOPYBUFFER2_PRE
#define VKCMDCOPYBUFFER2_PRE(...)
#endif
#ifndef VKCMDCOPYBUFFER2
#define VKCMDCOPYBUFFER2(commandBuffer, pCopyBufferInfo) s_vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo)
#endif
#ifndef VKCMDCOPYBUFFER2_POST
#define VKCMDCOPYBUFFER2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
#ifndef VKCMDCOPYBUFFER2KHR_PRE
#define VKCMDCOPYBUFFER2KHR_PRE(...)
#endif
#ifndef VKCMDCOPYBUFFER2KHR
#define VKCMDCOPYBUFFER2KHR(commandBuffer, pCopyBufferInfo) s_vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo)
#endif
#ifndef VKCMDCOPYBUFFER2KHR_POST
#define VKCMDCOPYBUFFER2KHR_POST(...)
#endif

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDCOPYIMAGE2_PRE
#define VKCMDCOPYIMAGE2_PRE(...)
#endif
#ifndef VKCMDCOPYIMAGE2
#define VKCMDCOPYIMAGE2(commandBuffer, pCopyImageInfo) s_vkCmdCopyImage2(commandBuffer, pCopyImageInfo)
#endif
#ifndef VKCMDCOPYIMAGE2_POST
#define VKCMDCOPYIMAGE2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
#ifndef VKCMDCOPYIMAGE2KHR_PRE
#define VKCMDCOPYIMAGE2KHR_PRE(...)
#endif
#ifndef VKCMDCOPYIMAGE2KHR
#define VKCMDCOPYIMAGE2KHR(commandBuffer, pCopyImageInfo) s_vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo)
#endif
#ifndef VKCMDCOPYIMAGE2KHR_POST
#define VKCMDCOPYIMAGE2KHR_POST(...)
#endif

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDBLITIMAGE2_PRE
#define VKCMDBLITIMAGE2_PRE(...)
#endif
#ifndef VKCMDBLITIMAGE2
#define VKCMDBLITIMAGE2(commandBuffer, pBlitImageInfo) s_vkCmdBlitImage2(commandBuffer, pBlitImageInfo)
#endif
#ifndef VKCMDBLITIMAGE2_POST
#define VKCMDBLITIMAGE2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
#ifndef VKCMDBLITIMAGE2KHR_PRE
#define VKCMDBLITIMAGE2KHR_PRE(...)
#endif
#ifndef VKCMDBLITIMAGE2KHR
#define VKCMDBLITIMAGE2KHR(commandBuffer, pBlitImageInfo) s_vkCmdBlitImage2KHR(commandBuffer, pBlitImageInfo)
#endif
#ifndef VKCMDBLITIMAGE2KHR_POST
#define VKCMDBLITIMAGE2KHR_POST(...)
#endif

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDCOPYBUFFERTOIMAGE2_PRE
#define VKCMDCOPYBUFFERTOIMAGE2_PRE(...)
#endif
#ifndef VKCMDCOPYBUFFERTOIMAGE2
#define VKCMDCOPYBUFFERTOIMAGE2(commandBuffer, pCopyBufferToImageInfo) s_vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo)
#endif
#ifndef VKCMDCOPYBUFFERTOIMAGE2_POST
#define VKCMDCOPYBUFFERTOIMAGE2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
#ifndef VKCMDCOPYBUFFERTOIMAGE2KHR_PRE
#define VKCMDCOPYBUFFERTOIMAGE2KHR_PRE(...)
#endif
#ifndef VKCMDCOPYBUFFERTOIMAGE2KHR
#define VKCMDCOPYBUFFERTOIMAGE2KHR(commandBuffer, pCopyBufferToImageInfo) s_vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo)
#endif
#ifndef VKCMDCOPYBUFFERTOIMAGE2KHR_POST
#define VKCMDCOPYBUFFERTOIMAGE2KHR_POST(...)
#endif

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDCOPYIMAGETOBUFFER2_PRE
#define VKCMDCOPYIMAGETOBUFFER2_PRE(...)
#endif
#ifndef VKCMDCOPYIMAGETOBUFFER2
#define VKCMDCOPYIMAGETOBUFFER2(commandBuffer, pCopyImageToBufferInfo) s_vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo)
#endif
#ifndef VKCMDCOPYIMAGETOBUFFER2_POST
#define VKCMDCOPYIMAGETOBUFFER2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
#ifndef VKCMDCOPYIMAGETOBUFFER2KHR_PRE
#define VKCMDCOPYIMAGETOBUFFER2KHR_PRE(...)
#endif
#ifndef VKCMDCOPYIMAGETOBUFFER2KHR
#define VKCMDCOPYIMAGETOBUFFER2KHR(commandBuffer, pCopyImageToBufferInfo) s_vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo)
#endif
#ifndef VKCMDCOPYIMAGETOBUFFER2KHR_POST
#define VKCMDCOPYIMAGETOBUFFER2KHR_POST(...)
#endif

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDRESOLVEIMAGE2_PRE
#define VKCMDRESOLVEIMAGE2_PRE(...)
#endif
#ifndef VKCMDRESOLVEIMAGE2
#define VKCMDRESOLVEIMAGE2(commandBuffer, pResolveImageInfo) s_vkCmdResolveImage2(commandBuffer, pResolveImageInfo)
#endif
#ifndef VKCMDRESOLVEIMAGE2_POST
#define VKCMDRESOLVEIMAGE2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
#ifndef VKCMDRESOLVEIMAGE2KHR_PRE
#define VKCMDRESOLVEIMAGE2KHR_PRE(...)
#endif
#ifndef VKCMDRESOLVEIMAGE2KHR
#define VKCMDRESOLVEIMAGE2KHR(commandBuffer, pResolveImageInfo) s_vkCmdResolveImage2KHR(commandBuffer, pResolveImageInfo)
#endif
#ifndef VKCMDRESOLVEIMAGE2KHR_POST
#define VKCMDRESOLVEIMAGE2KHR_POST(...)
#endif

#endif // VK_KHR_copy_commands2

#if defined(VK_KHR_fragment_shading_rate)
#ifndef VKCMDSETFRAGMENTSHADINGRATEKHR_PRE
#define VKCMDSETFRAGMENTSHADINGRATEKHR_PRE(...)
#endif
#ifndef VKCMDSETFRAGMENTSHADINGRATEKHR
#define VKCMDSETFRAGMENTSHADINGRATEKHR(commandBuffer, pFragmentSize, combinerOps) s_vkCmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps)
#endif
#ifndef VKCMDSETFRAGMENTSHADINGRATEKHR_POST
#define VKCMDSETFRAGMENTSHADINGRATEKHR_POST(...)
#endif

#ifndef VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR_PRE
#define VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR
#define VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates) VkResult result = s_vkGetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates)
#endif
#ifndef VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR_POST
#define VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR_POST(...) return result
#endif

#endif // VK_KHR_fragment_shading_rate

#if defined(VK_NV_fragment_shading_rate_enums)
#ifndef VKCMDSETFRAGMENTSHADINGRATEENUMNV_PRE
#define VKCMDSETFRAGMENTSHADINGRATEENUMNV_PRE(...)
#endif
#ifndef VKCMDSETFRAGMENTSHADINGRATEENUMNV
#define VKCMDSETFRAGMENTSHADINGRATEENUMNV(commandBuffer, shadingRate, combinerOps) s_vkCmdSetFragmentShadingRateEnumNV(commandBuffer, shadingRate, combinerOps)
#endif
#ifndef VKCMDSETFRAGMENTSHADINGRATEENUMNV_POST
#define VKCMDSETFRAGMENTSHADINGRATEENUMNV_POST(...)
#endif

#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_acceleration_structure)
#ifndef VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR_PRE
#define VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR_PRE(...)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR
#define VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo) s_vkGetAccelerationStructureBuildSizesKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR_POST
#define VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR_POST(...)
#endif

#endif // VK_KHR_acceleration_structure

#if defined(VK_EXT_vertex_input_dynamic_state) || defined(VK_EXT_shader_object)
#ifndef VKCMDSETVERTEXINPUTEXT_PRE
#define VKCMDSETVERTEXINPUTEXT_PRE(...)
#endif
#ifndef VKCMDSETVERTEXINPUTEXT
#define VKCMDSETVERTEXINPUTEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions) s_vkCmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions)
#endif
#ifndef VKCMDSETVERTEXINPUTEXT_POST
#define VKCMDSETVERTEXINPUTEXT_POST(...)
#endif

#endif // VK_EXT_vertex_input_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_color_write_enable)
#ifndef VKCMDSETCOLORWRITEENABLEEXT_PRE
#define VKCMDSETCOLORWRITEENABLEEXT_PRE(...)
#endif
#ifndef VKCMDSETCOLORWRITEENABLEEXT
#define VKCMDSETCOLORWRITEENABLEEXT(commandBuffer, attachmentCount, pColorWriteEnables) s_vkCmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables)
#endif
#ifndef VKCMDSETCOLORWRITEENABLEEXT_POST
#define VKCMDSETCOLORWRITEENABLEEXT_POST(...)
#endif

#endif // VK_EXT_color_write_enable

#if defined(VK_VERSION_1_3)
#ifndef VKCMDSETEVENT2_PRE
#define VKCMDSETEVENT2_PRE(...)
#endif
#ifndef VKCMDSETEVENT2
#define VKCMDSETEVENT2(commandBuffer, event, pDependencyInfo) s_vkCmdSetEvent2(commandBuffer, event, pDependencyInfo)
#endif
#ifndef VKCMDSETEVENT2_POST
#define VKCMDSETEVENT2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
#ifndef VKCMDSETEVENT2KHR_PRE
#define VKCMDSETEVENT2KHR_PRE(...)
#endif
#ifndef VKCMDSETEVENT2KHR
#define VKCMDSETEVENT2KHR(commandBuffer, event, pDependencyInfo) s_vkCmdSetEvent2KHR(commandBuffer, event, pDependencyInfo)
#endif
#ifndef VKCMDSETEVENT2KHR_POST
#define VKCMDSETEVENT2KHR_POST(...)
#endif

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDRESETEVENT2_PRE
#define VKCMDRESETEVENT2_PRE(...)
#endif
#ifndef VKCMDRESETEVENT2
#define VKCMDRESETEVENT2(commandBuffer, event, stageMask) s_vkCmdResetEvent2(commandBuffer, event, stageMask)
#endif
#ifndef VKCMDRESETEVENT2_POST
#define VKCMDRESETEVENT2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
#ifndef VKCMDRESETEVENT2KHR_PRE
#define VKCMDRESETEVENT2KHR_PRE(...)
#endif
#ifndef VKCMDRESETEVENT2KHR
#define VKCMDRESETEVENT2KHR(commandBuffer, event, stageMask) s_vkCmdResetEvent2KHR(commandBuffer, event, stageMask)
#endif
#ifndef VKCMDRESETEVENT2KHR_POST
#define VKCMDRESETEVENT2KHR_POST(...)
#endif

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDWAITEVENTS2_PRE
#define VKCMDWAITEVENTS2_PRE(...)
#endif
#ifndef VKCMDWAITEVENTS2
#define VKCMDWAITEVENTS2(commandBuffer, eventCount, pEvents, pDependencyInfos) s_vkCmdWaitEvents2(commandBuffer, eventCount, pEvents, pDependencyInfos)
#endif
#ifndef VKCMDWAITEVENTS2_POST
#define VKCMDWAITEVENTS2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
#ifndef VKCMDWAITEVENTS2KHR_PRE
#define VKCMDWAITEVENTS2KHR_PRE(...)
#endif
#ifndef VKCMDWAITEVENTS2KHR
#define VKCMDWAITEVENTS2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos) s_vkCmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos)
#endif
#ifndef VKCMDWAITEVENTS2KHR_POST
#define VKCMDWAITEVENTS2KHR_POST(...)
#endif

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDPIPELINEBARRIER2_PRE
#define VKCMDPIPELINEBARRIER2_PRE(...)
#endif
#ifndef VKCMDPIPELINEBARRIER2
#define VKCMDPIPELINEBARRIER2(commandBuffer, pDependencyInfo) s_vkCmdPipelineBarrier2(commandBuffer, pDependencyInfo)
#endif
#ifndef VKCMDPIPELINEBARRIER2_POST
#define VKCMDPIPELINEBARRIER2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
#ifndef VKCMDPIPELINEBARRIER2KHR_PRE
#define VKCMDPIPELINEBARRIER2KHR_PRE(...)
#endif
#ifndef VKCMDPIPELINEBARRIER2KHR
#define VKCMDPIPELINEBARRIER2KHR(commandBuffer, pDependencyInfo) s_vkCmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo)
#endif
#ifndef VKCMDPIPELINEBARRIER2KHR_POST
#define VKCMDPIPELINEBARRIER2KHR_POST(...)
#endif

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
#ifndef VKQUEUESUBMIT2_PRE
#define VKQUEUESUBMIT2_PRE(...)
#endif
#ifndef VKQUEUESUBMIT2
#define VKQUEUESUBMIT2(queue, submitCount, pSubmits, fence) VkResult result = s_vkQueueSubmit2(queue, submitCount, pSubmits, fence)
#endif
#ifndef VKQUEUESUBMIT2_POST
#define VKQUEUESUBMIT2_POST(...) return result
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
#ifndef VKQUEUESUBMIT2KHR_PRE
#define VKQUEUESUBMIT2KHR_PRE(...)
#endif
#ifndef VKQUEUESUBMIT2KHR
#define VKQUEUESUBMIT2KHR(queue, submitCount, pSubmits, fence) VkResult result = s_vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence)
#endif
#ifndef VKQUEUESUBMIT2KHR_POST
#define VKQUEUESUBMIT2KHR_POST(...) return result
#endif

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
#ifndef VKCMDWRITETIMESTAMP2_PRE
#define VKCMDWRITETIMESTAMP2_PRE(...)
#endif
#ifndef VKCMDWRITETIMESTAMP2
#define VKCMDWRITETIMESTAMP2(commandBuffer, stage, queryPool, query) s_vkCmdWriteTimestamp2(commandBuffer, stage, queryPool, query)
#endif
#ifndef VKCMDWRITETIMESTAMP2_POST
#define VKCMDWRITETIMESTAMP2_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
#ifndef VKCMDWRITETIMESTAMP2KHR_PRE
#define VKCMDWRITETIMESTAMP2KHR_PRE(...)
#endif
#ifndef VKCMDWRITETIMESTAMP2KHR
#define VKCMDWRITETIMESTAMP2KHR(commandBuffer, stage, queryPool, query) s_vkCmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query)
#endif
#ifndef VKCMDWRITETIMESTAMP2KHR_POST
#define VKCMDWRITETIMESTAMP2KHR_POST(...)
#endif

#ifndef VKCMDWRITEBUFFERMARKER2AMD_PRE
#define VKCMDWRITEBUFFERMARKER2AMD_PRE(...)
#endif
#ifndef VKCMDWRITEBUFFERMARKER2AMD
#define VKCMDWRITEBUFFERMARKER2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker) s_vkCmdWriteBufferMarker2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker)
#endif
#ifndef VKCMDWRITEBUFFERMARKER2AMD_POST
#define VKCMDWRITEBUFFERMARKER2AMD_POST(...)
#endif

#ifndef VKGETQUEUECHECKPOINTDATA2NV_PRE
#define VKGETQUEUECHECKPOINTDATA2NV_PRE(...)
#endif
#ifndef VKGETQUEUECHECKPOINTDATA2NV
#define VKGETQUEUECHECKPOINTDATA2NV(queue, pCheckpointDataCount, pCheckpointData) s_vkGetQueueCheckpointData2NV(queue, pCheckpointDataCount, pCheckpointData)
#endif
#ifndef VKGETQUEUECHECKPOINTDATA2NV_POST
#define VKGETQUEUECHECKPOINTDATA2NV_POST(...)
#endif

#endif // VK_KHR_synchronization2

#if defined(VKSC_VERSION_1_0)
#ifndef VKGETCOMMANDPOOLMEMORYCONSUMPTION_PRE
#define VKGETCOMMANDPOOLMEMORYCONSUMPTION_PRE(...)
#endif
#ifndef VKGETCOMMANDPOOLMEMORYCONSUMPTION
#define VKGETCOMMANDPOOLMEMORYCONSUMPTION(device, commandPool, commandBuffer, pConsumption) s_vkGetCommandPoolMemoryConsumption(device, commandPool, commandBuffer, pConsumption)
#endif
#ifndef VKGETCOMMANDPOOLMEMORYCONSUMPTION_POST
#define VKGETCOMMANDPOOLMEMORYCONSUMPTION_POST(...)
#endif

#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_video_queue)
#ifndef VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR_PRE
#define VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR
#define VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR(physicalDevice, pVideoProfile, pCapabilities) VkResult result = s_vkGetPhysicalDeviceVideoCapabilitiesKHR(physicalDevice, pVideoProfile, pCapabilities)
#endif
#ifndef VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR_POST
#define VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR_PRE
#define VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR
#define VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties) VkResult result = s_vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties)
#endif
#ifndef VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR_POST
#define VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR_POST(...) return result
#endif

#ifndef VKCREATEVIDEOSESSIONKHR_PRE
#define VKCREATEVIDEOSESSIONKHR_PRE(...)
#endif
#ifndef VKCREATEVIDEOSESSIONKHR
#define VKCREATEVIDEOSESSIONKHR(device, pCreateInfo, pAllocator, pVideoSession) VkResult result = s_vkCreateVideoSessionKHR(device, pCreateInfo, pAllocator, pVideoSession)
#endif
#ifndef VKCREATEVIDEOSESSIONKHR_POST
#define VKCREATEVIDEOSESSIONKHR_POST(...) return result
#endif

#ifndef VKDESTROYVIDEOSESSIONKHR_PRE
#define VKDESTROYVIDEOSESSIONKHR_PRE(...)
#endif
#ifndef VKDESTROYVIDEOSESSIONKHR
#define VKDESTROYVIDEOSESSIONKHR(device, videoSession, pAllocator) s_vkDestroyVideoSessionKHR(device, videoSession, pAllocator)
#endif
#ifndef VKDESTROYVIDEOSESSIONKHR_POST
#define VKDESTROYVIDEOSESSIONKHR_POST(...)
#endif

#ifndef VKCREATEVIDEOSESSIONPARAMETERSKHR_PRE
#define VKCREATEVIDEOSESSIONPARAMETERSKHR_PRE(...)
#endif
#ifndef VKCREATEVIDEOSESSIONPARAMETERSKHR
#define VKCREATEVIDEOSESSIONPARAMETERSKHR(device, pCreateInfo, pAllocator, pVideoSessionParameters) VkResult result = s_vkCreateVideoSessionParametersKHR(device, pCreateInfo, pAllocator, pVideoSessionParameters)
#endif
#ifndef VKCREATEVIDEOSESSIONPARAMETERSKHR_POST
#define VKCREATEVIDEOSESSIONPARAMETERSKHR_POST(...) return result
#endif

#ifndef VKUPDATEVIDEOSESSIONPARAMETERSKHR_PRE
#define VKUPDATEVIDEOSESSIONPARAMETERSKHR_PRE(...)
#endif
#ifndef VKUPDATEVIDEOSESSIONPARAMETERSKHR
#define VKUPDATEVIDEOSESSIONPARAMETERSKHR(device, videoSessionParameters, pUpdateInfo) VkResult result = s_vkUpdateVideoSessionParametersKHR(device, videoSessionParameters, pUpdateInfo)
#endif
#ifndef VKUPDATEVIDEOSESSIONPARAMETERSKHR_POST
#define VKUPDATEVIDEOSESSIONPARAMETERSKHR_POST(...) return result
#endif

#ifndef VKDESTROYVIDEOSESSIONPARAMETERSKHR_PRE
#define VKDESTROYVIDEOSESSIONPARAMETERSKHR_PRE(...)
#endif
#ifndef VKDESTROYVIDEOSESSIONPARAMETERSKHR
#define VKDESTROYVIDEOSESSIONPARAMETERSKHR(device, videoSessionParameters, pAllocator) s_vkDestroyVideoSessionParametersKHR(device, videoSessionParameters, pAllocator)
#endif
#ifndef VKDESTROYVIDEOSESSIONPARAMETERSKHR_POST
#define VKDESTROYVIDEOSESSIONPARAMETERSKHR_POST(...)
#endif

#ifndef VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR_PRE
#define VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR_PRE(...)
#endif
#ifndef VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR
#define VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements) VkResult result = s_vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements)
#endif
#ifndef VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR_POST
#define VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR_POST(...) return result
#endif

#ifndef VKBINDVIDEOSESSIONMEMORYKHR_PRE
#define VKBINDVIDEOSESSIONMEMORYKHR_PRE(...)
#endif
#ifndef VKBINDVIDEOSESSIONMEMORYKHR
#define VKBINDVIDEOSESSIONMEMORYKHR(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos) VkResult result = s_vkBindVideoSessionMemoryKHR(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos)
#endif
#ifndef VKBINDVIDEOSESSIONMEMORYKHR_POST
#define VKBINDVIDEOSESSIONMEMORYKHR_POST(...) return result
#endif

#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
#ifndef VKCMDDECODEVIDEOKHR_PRE
#define VKCMDDECODEVIDEOKHR_PRE(...)
#endif
#ifndef VKCMDDECODEVIDEOKHR
#define VKCMDDECODEVIDEOKHR(commandBuffer, pDecodeInfo) s_vkCmdDecodeVideoKHR(commandBuffer, pDecodeInfo)
#endif
#ifndef VKCMDDECODEVIDEOKHR_POST
#define VKCMDDECODEVIDEOKHR_POST(...)
#endif

#endif // VK_KHR_video_decode_queue

#if defined(VK_KHR_video_queue)
#ifndef VKCMDBEGINVIDEOCODINGKHR_PRE
#define VKCMDBEGINVIDEOCODINGKHR_PRE(...)
#endif
#ifndef VKCMDBEGINVIDEOCODINGKHR
#define VKCMDBEGINVIDEOCODINGKHR(commandBuffer, pBeginInfo) s_vkCmdBeginVideoCodingKHR(commandBuffer, pBeginInfo)
#endif
#ifndef VKCMDBEGINVIDEOCODINGKHR_POST
#define VKCMDBEGINVIDEOCODINGKHR_POST(...)
#endif

#ifndef VKCMDCONTROLVIDEOCODINGKHR_PRE
#define VKCMDCONTROLVIDEOCODINGKHR_PRE(...)
#endif
#ifndef VKCMDCONTROLVIDEOCODINGKHR
#define VKCMDCONTROLVIDEOCODINGKHR(commandBuffer, pCodingControlInfo) s_vkCmdControlVideoCodingKHR(commandBuffer, pCodingControlInfo)
#endif
#ifndef VKCMDCONTROLVIDEOCODINGKHR_POST
#define VKCMDCONTROLVIDEOCODINGKHR_POST(...)
#endif

#ifndef VKCMDENDVIDEOCODINGKHR_PRE
#define VKCMDENDVIDEOCODINGKHR_PRE(...)
#endif
#ifndef VKCMDENDVIDEOCODINGKHR
#define VKCMDENDVIDEOCODINGKHR(commandBuffer, pEndCodingInfo) s_vkCmdEndVideoCodingKHR(commandBuffer, pEndCodingInfo)
#endif
#ifndef VKCMDENDVIDEOCODINGKHR_POST
#define VKCMDENDVIDEOCODINGKHR_POST(...)
#endif

#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_encode_queue)
#ifndef VKCMDENCODEVIDEOKHR_PRE
#define VKCMDENCODEVIDEOKHR_PRE(...)
#endif
#ifndef VKCMDENCODEVIDEOKHR
#define VKCMDENCODEVIDEOKHR(commandBuffer, pEncodeInfo) s_vkCmdEncodeVideoKHR(commandBuffer, pEncodeInfo)
#endif
#ifndef VKCMDENCODEVIDEOKHR_POST
#define VKCMDENCODEVIDEOKHR_POST(...)
#endif

#endif // VK_KHR_video_encode_queue

#if defined(VK_NV_memory_decompression)
#ifndef VKCMDDECOMPRESSMEMORYNV_PRE
#define VKCMDDECOMPRESSMEMORYNV_PRE(...)
#endif
#ifndef VKCMDDECOMPRESSMEMORYNV
#define VKCMDDECOMPRESSMEMORYNV(commandBuffer, decompressRegionCount, pDecompressMemoryRegions) s_vkCmdDecompressMemoryNV(commandBuffer, decompressRegionCount, pDecompressMemoryRegions)
#endif
#ifndef VKCMDDECOMPRESSMEMORYNV_POST
#define VKCMDDECOMPRESSMEMORYNV_POST(...)
#endif

#ifndef VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV_PRE
#define VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV_PRE(...)
#endif
#ifndef VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV
#define VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride) s_vkCmdDecompressMemoryIndirectCountNV(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride)
#endif
#ifndef VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV_POST
#define VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV_POST(...)
#endif

#endif // VK_NV_memory_decompression

#if defined(VK_NVX_binary_import)
#ifndef VKCREATECUMODULENVX_PRE
#define VKCREATECUMODULENVX_PRE(...)
#endif
#ifndef VKCREATECUMODULENVX
#define VKCREATECUMODULENVX(device, pCreateInfo, pAllocator, pModule) VkResult result = s_vkCreateCuModuleNVX(device, pCreateInfo, pAllocator, pModule)
#endif
#ifndef VKCREATECUMODULENVX_POST
#define VKCREATECUMODULENVX_POST(...) return result
#endif

#ifndef VKCREATECUFUNCTIONNVX_PRE
#define VKCREATECUFUNCTIONNVX_PRE(...)
#endif
#ifndef VKCREATECUFUNCTIONNVX
#define VKCREATECUFUNCTIONNVX(device, pCreateInfo, pAllocator, pFunction) VkResult result = s_vkCreateCuFunctionNVX(device, pCreateInfo, pAllocator, pFunction)
#endif
#ifndef VKCREATECUFUNCTIONNVX_POST
#define VKCREATECUFUNCTIONNVX_POST(...) return result
#endif

#ifndef VKDESTROYCUMODULENVX_PRE
#define VKDESTROYCUMODULENVX_PRE(...)
#endif
#ifndef VKDESTROYCUMODULENVX
#define VKDESTROYCUMODULENVX(device, module, pAllocator) s_vkDestroyCuModuleNVX(device, module, pAllocator)
#endif
#ifndef VKDESTROYCUMODULENVX_POST
#define VKDESTROYCUMODULENVX_POST(...)
#endif

#ifndef VKDESTROYCUFUNCTIONNVX_PRE
#define VKDESTROYCUFUNCTIONNVX_PRE(...)
#endif
#ifndef VKDESTROYCUFUNCTIONNVX
#define VKDESTROYCUFUNCTIONNVX(device, function, pAllocator) s_vkDestroyCuFunctionNVX(device, function, pAllocator)
#endif
#ifndef VKDESTROYCUFUNCTIONNVX_POST
#define VKDESTROYCUFUNCTIONNVX_POST(...)
#endif

#ifndef VKCMDCULAUNCHKERNELNVX_PRE
#define VKCMDCULAUNCHKERNELNVX_PRE(...)
#endif
#ifndef VKCMDCULAUNCHKERNELNVX
#define VKCMDCULAUNCHKERNELNVX(commandBuffer, pLaunchInfo) s_vkCmdCuLaunchKernelNVX(commandBuffer, pLaunchInfo)
#endif
#ifndef VKCMDCULAUNCHKERNELNVX_POST
#define VKCMDCULAUNCHKERNELNVX_POST(...)
#endif

#endif // VK_NVX_binary_import

#if defined(VK_EXT_descriptor_buffer)
#ifndef VKGETDESCRIPTORSETLAYOUTSIZEEXT_PRE
#define VKGETDESCRIPTORSETLAYOUTSIZEEXT_PRE(...)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTSIZEEXT
#define VKGETDESCRIPTORSETLAYOUTSIZEEXT(device, layout, pLayoutSizeInBytes) s_vkGetDescriptorSetLayoutSizeEXT(device, layout, pLayoutSizeInBytes)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTSIZEEXT_POST
#define VKGETDESCRIPTORSETLAYOUTSIZEEXT_POST(...)
#endif

#ifndef VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT_PRE
#define VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT_PRE(...)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT
#define VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT(device, layout, binding, pOffset) s_vkGetDescriptorSetLayoutBindingOffsetEXT(device, layout, binding, pOffset)
#endif
#ifndef VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT_POST
#define VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT_POST(...)
#endif

#ifndef VKGETDESCRIPTOREXT_PRE
#define VKGETDESCRIPTOREXT_PRE(...)
#endif
#ifndef VKGETDESCRIPTOREXT
#define VKGETDESCRIPTOREXT(device, pDescriptorInfo, dataSize, pDescriptor) s_vkGetDescriptorEXT(device, pDescriptorInfo, dataSize, pDescriptor)
#endif
#ifndef VKGETDESCRIPTOREXT_POST
#define VKGETDESCRIPTOREXT_POST(...)
#endif

#ifndef VKCMDBINDDESCRIPTORBUFFERSEXT_PRE
#define VKCMDBINDDESCRIPTORBUFFERSEXT_PRE(...)
#endif
#ifndef VKCMDBINDDESCRIPTORBUFFERSEXT
#define VKCMDBINDDESCRIPTORBUFFERSEXT(commandBuffer, bufferCount, pBindingInfos) s_vkCmdBindDescriptorBuffersEXT(commandBuffer, bufferCount, pBindingInfos)
#endif
#ifndef VKCMDBINDDESCRIPTORBUFFERSEXT_POST
#define VKCMDBINDDESCRIPTORBUFFERSEXT_POST(...)
#endif

#ifndef VKCMDSETDESCRIPTORBUFFEROFFSETSEXT_PRE
#define VKCMDSETDESCRIPTORBUFFEROFFSETSEXT_PRE(...)
#endif
#ifndef VKCMDSETDESCRIPTORBUFFEROFFSETSEXT
#define VKCMDSETDESCRIPTORBUFFEROFFSETSEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets) s_vkCmdSetDescriptorBufferOffsetsEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets)
#endif
#ifndef VKCMDSETDESCRIPTORBUFFEROFFSETSEXT_POST
#define VKCMDSETDESCRIPTORBUFFEROFFSETSEXT_POST(...)
#endif

#ifndef VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT_PRE
#define VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT_PRE(...)
#endif
#ifndef VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT
#define VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT(commandBuffer, pipelineBindPoint, layout, set) s_vkCmdBindDescriptorBufferEmbeddedSamplersEXT(commandBuffer, pipelineBindPoint, layout, set)
#endif
#ifndef VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT_POST
#define VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT_POST(...)
#endif

#ifndef VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT_PRE
#define VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT_PRE(...)
#endif
#ifndef VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT
#define VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData) VkResult result = s_vkGetBufferOpaqueCaptureDescriptorDataEXT(device, pInfo, pData)
#endif
#ifndef VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT_POST
#define VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT_POST(...) return result
#endif

#ifndef VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT_PRE
#define VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT_PRE(...)
#endif
#ifndef VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT
#define VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData) VkResult result = s_vkGetImageOpaqueCaptureDescriptorDataEXT(device, pInfo, pData)
#endif
#ifndef VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT_POST
#define VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT_POST(...) return result
#endif

#ifndef VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT_PRE
#define VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT_PRE(...)
#endif
#ifndef VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT
#define VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData) VkResult result = s_vkGetImageViewOpaqueCaptureDescriptorDataEXT(device, pInfo, pData)
#endif
#ifndef VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT_POST
#define VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT_POST(...) return result
#endif

#ifndef VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT_PRE
#define VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT_PRE(...)
#endif
#ifndef VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT
#define VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData) VkResult result = s_vkGetSamplerOpaqueCaptureDescriptorDataEXT(device, pInfo, pData)
#endif
#ifndef VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT_POST
#define VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT_POST(...) return result
#endif

#ifndef VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT_PRE
#define VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT_PRE(...)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT
#define VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData) VkResult result = s_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(device, pInfo, pData)
#endif
#ifndef VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT_POST
#define VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT_POST(...) return result
#endif

#endif // VK_EXT_descriptor_buffer

#if defined(VK_EXT_pageable_device_local_memory)
#ifndef VKSETDEVICEMEMORYPRIORITYEXT_PRE
#define VKSETDEVICEMEMORYPRIORITYEXT_PRE(...)
#endif
#ifndef VKSETDEVICEMEMORYPRIORITYEXT
#define VKSETDEVICEMEMORYPRIORITYEXT(device, memory, priority) s_vkSetDeviceMemoryPriorityEXT(device, memory, priority)
#endif
#ifndef VKSETDEVICEMEMORYPRIORITYEXT_POST
#define VKSETDEVICEMEMORYPRIORITYEXT_POST(...)
#endif

#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_present_wait)
#ifndef VKWAITFORPRESENTKHR_PRE
#define VKWAITFORPRESENTKHR_PRE(...)
#endif
#ifndef VKWAITFORPRESENTKHR
#define VKWAITFORPRESENTKHR(device, swapchain, presentId, timeout) VkResult result = s_vkWaitForPresentKHR(device, swapchain, presentId, timeout)
#endif
#ifndef VKWAITFORPRESENTKHR_POST
#define VKWAITFORPRESENTKHR_POST(...) return result
#endif

#endif // VK_KHR_present_wait

#if defined(VK_VERSION_1_3)
#ifndef VKCMDBEGINRENDERING_PRE
#define VKCMDBEGINRENDERING_PRE(...)
#endif
#ifndef VKCMDBEGINRENDERING
#define VKCMDBEGINRENDERING(commandBuffer, pRenderingInfo) s_vkCmdBeginRendering(commandBuffer, pRenderingInfo)
#endif
#ifndef VKCMDBEGINRENDERING_POST
#define VKCMDBEGINRENDERING_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
#ifndef VKCMDBEGINRENDERINGKHR_PRE
#define VKCMDBEGINRENDERINGKHR_PRE(...)
#endif
#ifndef VKCMDBEGINRENDERINGKHR
#define VKCMDBEGINRENDERINGKHR(commandBuffer, pRenderingInfo) s_vkCmdBeginRenderingKHR(commandBuffer, pRenderingInfo)
#endif
#ifndef VKCMDBEGINRENDERINGKHR_POST
#define VKCMDBEGINRENDERINGKHR_POST(...)
#endif

#endif // VK_KHR_dynamic_rendering

#if defined(VK_VERSION_1_3)
#ifndef VKCMDENDRENDERING_PRE
#define VKCMDENDRENDERING_PRE(...)
#endif
#ifndef VKCMDENDRENDERING
#define VKCMDENDRENDERING(commandBuffer) s_vkCmdEndRendering(commandBuffer)
#endif
#ifndef VKCMDENDRENDERING_POST
#define VKCMDENDRENDERING_POST(...)
#endif

#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
#ifndef VKCMDENDRENDERINGKHR_PRE
#define VKCMDENDRENDERINGKHR_PRE(...)
#endif
#ifndef VKCMDENDRENDERINGKHR
#define VKCMDENDRENDERINGKHR(commandBuffer) s_vkCmdEndRenderingKHR(commandBuffer)
#endif
#ifndef VKCMDENDRENDERINGKHR_POST
#define VKCMDENDRENDERINGKHR_POST(...)
#endif

#endif // VK_KHR_dynamic_rendering

#if defined(VK_EXT_opacity_micromap)
#ifndef VKCREATEMICROMAPEXT_PRE
#define VKCREATEMICROMAPEXT_PRE(...)
#endif
#ifndef VKCREATEMICROMAPEXT
#define VKCREATEMICROMAPEXT(device, pCreateInfo, pAllocator, pMicromap) VkResult result = s_vkCreateMicromapEXT(device, pCreateInfo, pAllocator, pMicromap)
#endif
#ifndef VKCREATEMICROMAPEXT_POST
#define VKCREATEMICROMAPEXT_POST(...) return result
#endif

#ifndef VKCMDBUILDMICROMAPSEXT_PRE
#define VKCMDBUILDMICROMAPSEXT_PRE(...)
#endif
#ifndef VKCMDBUILDMICROMAPSEXT
#define VKCMDBUILDMICROMAPSEXT(commandBuffer, infoCount, pInfos) s_vkCmdBuildMicromapsEXT(commandBuffer, infoCount, pInfos)
#endif
#ifndef VKCMDBUILDMICROMAPSEXT_POST
#define VKCMDBUILDMICROMAPSEXT_POST(...)
#endif

#ifndef VKBUILDMICROMAPSEXT_PRE
#define VKBUILDMICROMAPSEXT_PRE(...)
#endif
#ifndef VKBUILDMICROMAPSEXT
#define VKBUILDMICROMAPSEXT(device, deferredOperation, infoCount, pInfos) VkResult result = s_vkBuildMicromapsEXT(device, deferredOperation, infoCount, pInfos)
#endif
#ifndef VKBUILDMICROMAPSEXT_POST
#define VKBUILDMICROMAPSEXT_POST(...) return result
#endif

#ifndef VKDESTROYMICROMAPEXT_PRE
#define VKDESTROYMICROMAPEXT_PRE(...)
#endif
#ifndef VKDESTROYMICROMAPEXT
#define VKDESTROYMICROMAPEXT(device, micromap, pAllocator) s_vkDestroyMicromapEXT(device, micromap, pAllocator)
#endif
#ifndef VKDESTROYMICROMAPEXT_POST
#define VKDESTROYMICROMAPEXT_POST(...)
#endif

#ifndef VKCMDCOPYMICROMAPEXT_PRE
#define VKCMDCOPYMICROMAPEXT_PRE(...)
#endif
#ifndef VKCMDCOPYMICROMAPEXT
#define VKCMDCOPYMICROMAPEXT(commandBuffer, pInfo) s_vkCmdCopyMicromapEXT(commandBuffer, pInfo)
#endif
#ifndef VKCMDCOPYMICROMAPEXT_POST
#define VKCMDCOPYMICROMAPEXT_POST(...)
#endif

#ifndef VKCOPYMICROMAPEXT_PRE
#define VKCOPYMICROMAPEXT_PRE(...)
#endif
#ifndef VKCOPYMICROMAPEXT
#define VKCOPYMICROMAPEXT(device, deferredOperation, pInfo) VkResult result = s_vkCopyMicromapEXT(device, deferredOperation, pInfo)
#endif
#ifndef VKCOPYMICROMAPEXT_POST
#define VKCOPYMICROMAPEXT_POST(...) return result
#endif

#ifndef VKCMDCOPYMICROMAPTOMEMORYEXT_PRE
#define VKCMDCOPYMICROMAPTOMEMORYEXT_PRE(...)
#endif
#ifndef VKCMDCOPYMICROMAPTOMEMORYEXT
#define VKCMDCOPYMICROMAPTOMEMORYEXT(commandBuffer, pInfo) s_vkCmdCopyMicromapToMemoryEXT(commandBuffer, pInfo)
#endif
#ifndef VKCMDCOPYMICROMAPTOMEMORYEXT_POST
#define VKCMDCOPYMICROMAPTOMEMORYEXT_POST(...)
#endif

#ifndef VKCOPYMICROMAPTOMEMORYEXT_PRE
#define VKCOPYMICROMAPTOMEMORYEXT_PRE(...)
#endif
#ifndef VKCOPYMICROMAPTOMEMORYEXT
#define VKCOPYMICROMAPTOMEMORYEXT(device, deferredOperation, pInfo) VkResult result = s_vkCopyMicromapToMemoryEXT(device, deferredOperation, pInfo)
#endif
#ifndef VKCOPYMICROMAPTOMEMORYEXT_POST
#define VKCOPYMICROMAPTOMEMORYEXT_POST(...) return result
#endif

#ifndef VKCMDCOPYMEMORYTOMICROMAPEXT_PRE
#define VKCMDCOPYMEMORYTOMICROMAPEXT_PRE(...)
#endif
#ifndef VKCMDCOPYMEMORYTOMICROMAPEXT
#define VKCMDCOPYMEMORYTOMICROMAPEXT(commandBuffer, pInfo) s_vkCmdCopyMemoryToMicromapEXT(commandBuffer, pInfo)
#endif
#ifndef VKCMDCOPYMEMORYTOMICROMAPEXT_POST
#define VKCMDCOPYMEMORYTOMICROMAPEXT_POST(...)
#endif

#ifndef VKCOPYMEMORYTOMICROMAPEXT_PRE
#define VKCOPYMEMORYTOMICROMAPEXT_PRE(...)
#endif
#ifndef VKCOPYMEMORYTOMICROMAPEXT
#define VKCOPYMEMORYTOMICROMAPEXT(device, deferredOperation, pInfo) VkResult result = s_vkCopyMemoryToMicromapEXT(device, deferredOperation, pInfo)
#endif
#ifndef VKCOPYMEMORYTOMICROMAPEXT_POST
#define VKCOPYMEMORYTOMICROMAPEXT_POST(...) return result
#endif

#ifndef VKCMDWRITEMICROMAPSPROPERTIESEXT_PRE
#define VKCMDWRITEMICROMAPSPROPERTIESEXT_PRE(...)
#endif
#ifndef VKCMDWRITEMICROMAPSPROPERTIESEXT
#define VKCMDWRITEMICROMAPSPROPERTIESEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery) s_vkCmdWriteMicromapsPropertiesEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery)
#endif
#ifndef VKCMDWRITEMICROMAPSPROPERTIESEXT_POST
#define VKCMDWRITEMICROMAPSPROPERTIESEXT_POST(...)
#endif

#ifndef VKWRITEMICROMAPSPROPERTIESEXT_PRE
#define VKWRITEMICROMAPSPROPERTIESEXT_PRE(...)
#endif
#ifndef VKWRITEMICROMAPSPROPERTIESEXT
#define VKWRITEMICROMAPSPROPERTIESEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride) VkResult result = s_vkWriteMicromapsPropertiesEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride)
#endif
#ifndef VKWRITEMICROMAPSPROPERTIESEXT_POST
#define VKWRITEMICROMAPSPROPERTIESEXT_POST(...) return result
#endif

#ifndef VKGETDEVICEMICROMAPCOMPATIBILITYEXT_PRE
#define VKGETDEVICEMICROMAPCOMPATIBILITYEXT_PRE(...)
#endif
#ifndef VKGETDEVICEMICROMAPCOMPATIBILITYEXT
#define VKGETDEVICEMICROMAPCOMPATIBILITYEXT(device, pVersionInfo, pCompatibility) s_vkGetDeviceMicromapCompatibilityEXT(device, pVersionInfo, pCompatibility)
#endif
#ifndef VKGETDEVICEMICROMAPCOMPATIBILITYEXT_POST
#define VKGETDEVICEMICROMAPCOMPATIBILITYEXT_POST(...)
#endif

#ifndef VKGETMICROMAPBUILDSIZESEXT_PRE
#define VKGETMICROMAPBUILDSIZESEXT_PRE(...)
#endif
#ifndef VKGETMICROMAPBUILDSIZESEXT
#define VKGETMICROMAPBUILDSIZESEXT(device, buildType, pBuildInfo, pSizeInfo) s_vkGetMicromapBuildSizesEXT(device, buildType, pBuildInfo, pSizeInfo)
#endif
#ifndef VKGETMICROMAPBUILDSIZESEXT_POST
#define VKGETMICROMAPBUILDSIZESEXT_POST(...)
#endif

#endif // VK_EXT_opacity_micromap

#if defined(VK_EXT_shader_module_identifier)
#ifndef VKGETSHADERMODULEIDENTIFIEREXT_PRE
#define VKGETSHADERMODULEIDENTIFIEREXT_PRE(...)
#endif
#ifndef VKGETSHADERMODULEIDENTIFIEREXT
#define VKGETSHADERMODULEIDENTIFIEREXT(device, shaderModule, pIdentifier) s_vkGetShaderModuleIdentifierEXT(device, shaderModule, pIdentifier)
#endif
#ifndef VKGETSHADERMODULEIDENTIFIEREXT_POST
#define VKGETSHADERMODULEIDENTIFIEREXT_POST(...)
#endif

#ifndef VKGETSHADERMODULECREATEINFOIDENTIFIEREXT_PRE
#define VKGETSHADERMODULECREATEINFOIDENTIFIEREXT_PRE(...)
#endif
#ifndef VKGETSHADERMODULECREATEINFOIDENTIFIEREXT
#define VKGETSHADERMODULECREATEINFOIDENTIFIEREXT(device, pCreateInfo, pIdentifier) s_vkGetShaderModuleCreateInfoIdentifierEXT(device, pCreateInfo, pIdentifier)
#endif
#ifndef VKGETSHADERMODULECREATEINFOIDENTIFIEREXT_POST
#define VKGETSHADERMODULECREATEINFOIDENTIFIEREXT_POST(...)
#endif

#endif // VK_EXT_shader_module_identifier

#if defined(VK_EXT_image_compression_control)
#ifndef VKGETIMAGESUBRESOURCELAYOUT2EXT_PRE
#define VKGETIMAGESUBRESOURCELAYOUT2EXT_PRE(...)
#endif
#ifndef VKGETIMAGESUBRESOURCELAYOUT2EXT
#define VKGETIMAGESUBRESOURCELAYOUT2EXT(device, image, pSubresource, pLayout) s_vkGetImageSubresourceLayout2EXT(device, image, pSubresource, pLayout)
#endif
#ifndef VKGETIMAGESUBRESOURCELAYOUT2EXT_POST
#define VKGETIMAGESUBRESOURCELAYOUT2EXT_POST(...)
#endif

#endif // VK_EXT_image_compression_control

#if defined(VK_EXT_device_fault)
#ifndef VKGETDEVICEFAULTINFOEXT_PRE
#define VKGETDEVICEFAULTINFOEXT_PRE(...)
#endif
#ifndef VKGETDEVICEFAULTINFOEXT
#define VKGETDEVICEFAULTINFOEXT(device, pFaultCounts, pFaultInfo) VkResult result = s_vkGetDeviceFaultInfoEXT(device, pFaultCounts, pFaultInfo)
#endif
#ifndef VKGETDEVICEFAULTINFOEXT_POST
#define VKGETDEVICEFAULTINFOEXT_POST(...) return result
#endif

#endif // VK_EXT_device_fault

#if defined(VK_EXT_swapchain_maintenance1)
#ifndef VKRELEASESWAPCHAINIMAGESEXT_PRE
#define VKRELEASESWAPCHAINIMAGESEXT_PRE(...)
#endif
#ifndef VKRELEASESWAPCHAINIMAGESEXT
#define VKRELEASESWAPCHAINIMAGESEXT(device, pReleaseInfo) VkResult result = s_vkReleaseSwapchainImagesEXT(device, pReleaseInfo)
#endif
#ifndef VKRELEASESWAPCHAINIMAGESEXT_POST
#define VKRELEASESWAPCHAINIMAGESEXT_POST(...) return result
#endif

#endif // VK_EXT_swapchain_maintenance1

#if defined(VK_KHR_map_memory2)
#ifndef VKMAPMEMORY2KHR_PRE
#define VKMAPMEMORY2KHR_PRE(...)
#endif
#ifndef VKMAPMEMORY2KHR
#define VKMAPMEMORY2KHR(device, pMemoryMapInfo, ppData) VkResult result = s_vkMapMemory2KHR(device, pMemoryMapInfo, ppData)
#endif
#ifndef VKMAPMEMORY2KHR_POST
#define VKMAPMEMORY2KHR_POST(...) return result
#endif

#ifndef VKUNMAPMEMORY2KHR_PRE
#define VKUNMAPMEMORY2KHR_PRE(...)
#endif
#ifndef VKUNMAPMEMORY2KHR
#define VKUNMAPMEMORY2KHR(device, pMemoryUnmapInfo) VkResult result = s_vkUnmapMemory2KHR(device, pMemoryUnmapInfo)
#endif
#ifndef VKUNMAPMEMORY2KHR_POST
#define VKUNMAPMEMORY2KHR_POST(...) return result
#endif

#endif // VK_KHR_map_memory2

#if defined(VK_EXT_shader_object)
#ifndef VKCREATESHADERSEXT_PRE
#define VKCREATESHADERSEXT_PRE(...)
#endif
#ifndef VKCREATESHADERSEXT
#define VKCREATESHADERSEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders) VkResult result = s_vkCreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders)
#endif
#ifndef VKCREATESHADERSEXT_POST
#define VKCREATESHADERSEXT_POST(...) return result
#endif

#ifndef VKDESTROYSHADEREXT_PRE
#define VKDESTROYSHADEREXT_PRE(...)
#endif
#ifndef VKDESTROYSHADEREXT
#define VKDESTROYSHADEREXT(device, shader, pAllocator) s_vkDestroyShaderEXT(device, shader, pAllocator)
#endif
#ifndef VKDESTROYSHADEREXT_POST
#define VKDESTROYSHADEREXT_POST(...)
#endif

#ifndef VKGETSHADERBINARYDATAEXT_PRE
#define VKGETSHADERBINARYDATAEXT_PRE(...)
#endif
#ifndef VKGETSHADERBINARYDATAEXT
#define VKGETSHADERBINARYDATAEXT(device, shader, pDataSize, pData) VkResult result = s_vkGetShaderBinaryDataEXT(device, shader, pDataSize, pData)
#endif
#ifndef VKGETSHADERBINARYDATAEXT_POST
#define VKGETSHADERBINARYDATAEXT_POST(...) return result
#endif

#ifndef VKCMDBINDSHADERSEXT_PRE
#define VKCMDBINDSHADERSEXT_PRE(...)
#endif
#ifndef VKCMDBINDSHADERSEXT
#define VKCMDBINDSHADERSEXT(commandBuffer, stageCount, pStages, pShaders) s_vkCmdBindShadersEXT(commandBuffer, stageCount, pStages, pShaders)
#endif
#ifndef VKCMDBINDSHADERSEXT_POST
#define VKCMDBINDSHADERSEXT_POST(...)
#endif

#endif // VK_EXT_shader_object

#if defined(VK_NV_external_memory_sci_buf)
#ifndef VKGETMEMORYSCIBUFNV_PRE
#define VKGETMEMORYSCIBUFNV_PRE(...)
#endif
#ifndef VKGETMEMORYSCIBUFNV
#define VKGETMEMORYSCIBUFNV(device, pGetSciBufInfo, pHandle) VkResult result = s_vkGetMemorySciBufNV(device, pGetSciBufInfo, pHandle)
#endif
#ifndef VKGETMEMORYSCIBUFNV_POST
#define VKGETMEMORYSCIBUFNV_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV_PRE
#define VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV
#define VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV(physicalDevice, handleType, handle, pMemorySciBufProperties) VkResult result = s_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV(physicalDevice, handleType, handle, pMemorySciBufProperties)
#endif
#ifndef VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV_POST
#define VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV_POST(...) return result
#endif

#ifndef VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV_PRE
#define VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV_PRE(...)
#endif
#ifndef VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV
#define VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV(physicalDevice, pAttributes) VkResult result = s_vkGetPhysicalDeviceSciBufAttributesNV(physicalDevice, pAttributes)
#endif
#ifndef VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV_POST
#define VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV_POST(...) return result
#endif

#endif // VK_NV_external_memory_sci_buf

#if defined(_WIN32)
HMODULE PlatformLoadVulkanLoader()
{
    return LoadLibrary(L"vulkan-1.dll");
}

FARPROC PlatformGetProcAddress(HMODULE handle, const char* sym)
{
    return GetProcAddress(handle, sym);
}
#elif defined(ANDROID)
void* PlatformLoadVulkanLoader()
{
    return dlopen("libvulkan.so", RTLD_NOW | RTLD_GLOBAL);
}

void* PlatformGetProcAddress(void* handle, const char* sym)
{
    return dlsym(handle, sym);
}
#elif defined(__linux__) || defined(__QNX__)
void* PlatformLoadVulkanLoader()
{
#if defined(NV_VULKAN_SC_SUPPORT)
    return dlopen("libvulkansc.so.1", RTLD_NOW | RTLD_GLOBAL);
#else
    return dlopen("libvulkan.so.1", RTLD_NOW | RTLD_GLOBAL);
#endif
}

void* PlatformGetProcAddress(void* handle, const char* sym)
{
    return dlsym(handle, sym);
}
#else
#error "Unsupported platform"
#endif

void BootstrapICD()
{
    auto hVulkan = PlatformLoadVulkanLoader();

    s_vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(PlatformGetProcAddress(hVulkan, "vkCreateInstance"));
    s_vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(PlatformGetProcAddress(hVulkan, "vkEnumerateInstanceExtensionProperties"));
    s_vkEnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(PlatformGetProcAddress(hVulkan, "vkEnumerateInstanceLayerProperties"));
    s_vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(PlatformGetProcAddress(hVulkan, "vkGetInstanceProcAddr"));
    s_vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(PlatformGetProcAddress(hVulkan, "vkEnumerateInstanceVersion"));
}

void BootstrapInstance(VkInstance instance)
{
#if defined(VK_VERSION_1_0)
    s_vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(s_vkGetInstanceProcAddr(instance, "vkDestroyInstance"));
    s_vkEnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(s_vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDevices"));
    s_vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(s_vkGetInstanceProcAddr(instance, "vkGetDeviceProcAddr"));
    s_vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties"));
    s_vkGetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties"));
    s_vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties"));
    s_vkGetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures"));
    s_vkGetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties"));
    s_vkGetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties"));
    s_vkCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(s_vkGetInstanceProcAddr(instance, "vkCreateDevice"));
    s_vkEnumerateDeviceLayerProperties = reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(s_vkGetInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties"));
    s_vkEnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(s_vkGetInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkGetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_KHR_android_surface)
    s_vkCreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateAndroidSurfaceKHR"));
#endif // VK_KHR_android_surface

#if defined(VK_KHR_display)
    s_vkGetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceDisplayPropertiesKHR"));
    s_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
    s_vkGetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(s_vkGetInstanceProcAddr(instance, "vkGetDisplayPlaneSupportedDisplaysKHR"));
    s_vkGetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetDisplayModePropertiesKHR"));
    s_vkCreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateDisplayModeKHR"));
    s_vkGetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetDisplayPlaneCapabilitiesKHR"));
    s_vkCreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateDisplayPlaneSurfaceKHR"));
#endif // VK_KHR_display

#if defined(VK_KHR_surface)
    s_vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkDestroySurfaceKHR"));
    s_vkGetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceSupportKHR"));
    s_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
    s_vkGetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR"));
    s_vkGetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR"));
#endif // VK_KHR_surface

#if defined(VK_KHR_wayland_surface)
    s_vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateWaylandSurfaceKHR"));
    s_vkGetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_win32_surface)
    s_vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR"));
    s_vkGetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif // VK_KHR_win32_surface

#if defined(VK_KHR_xlib_surface)
    s_vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR"));
    s_vkGetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
    s_vkCreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(s_vkGetInstanceProcAddr(instance, "vkCreateXcbSurfaceKHR"));
    s_vkGetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif // VK_KHR_xcb_surface

#if defined(VK_EXT_debug_report)
    s_vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(s_vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
    s_vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(s_vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
    s_vkDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(s_vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT"));
#endif // VK_EXT_debug_report

#if defined(VK_NV_external_memory_capabilities)
    s_vkGetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#endif // VK_NV_external_memory_capabilities

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceFeatures2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceFeatures2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceImageFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceQueueFamilyProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceMemoryProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceMemoryProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
    s_vkGetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2"));
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_physical_device_properties2)
    s_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR"));
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceExternalBufferProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalBufferProperties"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_memory_capabilities)
    s_vkGetPhysicalDeviceExternalBufferPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHR"));
#endif // VK_KHR_external_memory_capabilities

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalSemaphoreProperties"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_semaphore_capabilities)
    s_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR"));
#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_VERSION_1_1)
    s_vkGetPhysicalDeviceExternalFenceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalFenceProperties"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_fence_capabilities)
    s_vkGetPhysicalDeviceExternalFencePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalFencePropertiesKHR"));
#endif // VK_KHR_external_fence_capabilities

#if defined(VK_EXT_direct_mode_display)
    s_vkReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(s_vkGetInstanceProcAddr(instance, "vkReleaseDisplayEXT"));
#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
    s_vkAcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(s_vkGetInstanceProcAddr(instance, "vkAcquireXlibDisplayEXT"));
    s_vkGetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(s_vkGetInstanceProcAddr(instance, "vkGetRandROutputDisplayEXT"));
#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
    s_vkGetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
#endif // VK_EXT_display_surface_counter

#if defined(VK_VERSION_1_1)
    s_vkEnumeratePhysicalDeviceGroups = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(s_vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceGroups"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group_creation)
    s_vkEnumeratePhysicalDeviceGroupsKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroupsKHR>(s_vkGetInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceGroupsKHR"));
#endif // VK_KHR_device_group_creation

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
    s_vkGetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDevicePresentRectanglesKHR"));
#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_EXT_sample_locations)
    s_vkGetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT"));
#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_surface_capabilities2)
    s_vkGetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
    s_vkGetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceFormats2KHR"));
#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
    s_vkGetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceDisplayProperties2KHR"));
    s_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
    s_vkGetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetDisplayModeProperties2KHR"));
    s_vkGetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(s_vkGetInstanceProcAddr(instance, "vkGetDisplayPlaneCapabilities2KHR"));
#endif // VK_KHR_get_display_properties2

#if defined(VK_EXT_calibrated_timestamps)
    s_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
    s_vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(s_vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    s_vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(s_vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    s_vkSubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(s_vkGetInstanceProcAddr(instance, "vkSubmitDebugUtilsMessageEXT"));
#endif // VK_EXT_debug_utils

#if defined(VK_NV_cooperative_matrix)
    s_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
#endif // VK_NV_cooperative_matrix

#if defined(VK_EXT_full_screen_exclusive)
    s_vkGetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif // VK_EXT_full_screen_exclusive

#if defined(VK_EXT_headless_surface)
    s_vkCreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(s_vkGetInstanceProcAddr(instance, "vkCreateHeadlessSurfaceEXT"));
#endif // VK_EXT_headless_surface

#if defined(VK_NV_coverage_reduction_mode)
    s_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#endif // VK_NV_coverage_reduction_mode

#if defined(VK_VERSION_1_3)
    s_vkGetPhysicalDeviceToolProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceToolProperties>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceToolProperties"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_tooling_info)
    s_vkGetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceToolPropertiesEXT>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceToolPropertiesEXT"));
#endif // VK_EXT_tooling_info

#if defined(VK_KHR_fragment_shading_rate)
    s_vkGetPhysicalDeviceFragmentShadingRatesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR"));
#endif // VK_KHR_fragment_shading_rate

#if defined(VK_KHR_video_queue)
    s_vkGetPhysicalDeviceVideoCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR"));
    s_vkGetPhysicalDeviceVideoFormatPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR"));
#endif // VK_KHR_video_queue

#if defined(VK_NV_external_memory_sci_buf)
    s_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV"));
    s_vkGetPhysicalDeviceSciBufAttributesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSciBufAttributesNV>(s_vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSciBufAttributesNV"));
#endif // VK_NV_external_memory_sci_buf
}

void BootstrapDevice(VkDevice device)
{
#if defined(VK_VERSION_1_0)
    s_vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(s_vkGetDeviceProcAddr(device, "vkDestroyDevice"));
    s_vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(s_vkGetDeviceProcAddr(device, "vkGetDeviceQueue"));
    s_vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(s_vkGetDeviceProcAddr(device, "vkQueueSubmit"));
    s_vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(s_vkGetDeviceProcAddr(device, "vkQueueWaitIdle"));
    s_vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(s_vkGetDeviceProcAddr(device, "vkDeviceWaitIdle"));
    s_vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(s_vkGetDeviceProcAddr(device, "vkAllocateMemory"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(s_vkGetDeviceProcAddr(device, "vkFreeMemory"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(s_vkGetDeviceProcAddr(device, "vkMapMemory"));
    s_vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(s_vkGetDeviceProcAddr(device, "vkUnmapMemory"));
    s_vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(s_vkGetDeviceProcAddr(device, "vkFlushMappedMemoryRanges"));
    s_vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(s_vkGetDeviceProcAddr(device, "vkInvalidateMappedMemoryRanges"));
    s_vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(s_vkGetDeviceProcAddr(device, "vkGetDeviceMemoryCommitment"));
    s_vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(s_vkGetDeviceProcAddr(device, "vkGetBufferMemoryRequirements"));
    s_vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(s_vkGetDeviceProcAddr(device, "vkBindBufferMemory"));
    s_vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(s_vkGetDeviceProcAddr(device, "vkGetImageMemoryRequirements"));
    s_vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(s_vkGetDeviceProcAddr(device, "vkBindImageMemory"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(s_vkGetDeviceProcAddr(device, "vkGetImageSparseMemoryRequirements"));
    s_vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(s_vkGetDeviceProcAddr(device, "vkQueueBindSparse"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(s_vkGetDeviceProcAddr(device, "vkCreateFence"));
    s_vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(s_vkGetDeviceProcAddr(device, "vkDestroyFence"));
    s_vkResetFences = reinterpret_cast<PFN_vkResetFences>(s_vkGetDeviceProcAddr(device, "vkResetFences"));
    s_vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(s_vkGetDeviceProcAddr(device, "vkGetFenceStatus"));
    s_vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(s_vkGetDeviceProcAddr(device, "vkWaitForFences"));
    s_vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(s_vkGetDeviceProcAddr(device, "vkCreateSemaphore"));
    s_vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(s_vkGetDeviceProcAddr(device, "vkDestroySemaphore"));
    s_vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(s_vkGetDeviceProcAddr(device, "vkCreateEvent"));
    s_vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(s_vkGetDeviceProcAddr(device, "vkDestroyEvent"));
    s_vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(s_vkGetDeviceProcAddr(device, "vkGetEventStatus"));
    s_vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(s_vkGetDeviceProcAddr(device, "vkSetEvent"));
    s_vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(s_vkGetDeviceProcAddr(device, "vkResetEvent"));
    s_vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(s_vkGetDeviceProcAddr(device, "vkCreateQueryPool"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(s_vkGetDeviceProcAddr(device, "vkDestroyQueryPool"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(s_vkGetDeviceProcAddr(device, "vkGetQueryPoolResults"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_2)
    s_vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(s_vkGetDeviceProcAddr(device, "vkResetQueryPool"));
#endif // VK_VERSION_1_2

#if defined(VK_EXT_host_query_reset)
    s_vkResetQueryPoolEXT = reinterpret_cast<PFN_vkResetQueryPoolEXT>(s_vkGetDeviceProcAddr(device, "vkResetQueryPoolEXT"));
#endif // VK_EXT_host_query_reset

#if defined(VK_VERSION_1_0)
    s_vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(s_vkGetDeviceProcAddr(device, "vkCreateBuffer"));
    s_vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(s_vkGetDeviceProcAddr(device, "vkDestroyBuffer"));
    s_vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(s_vkGetDeviceProcAddr(device, "vkCreateBufferView"));
    s_vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(s_vkGetDeviceProcAddr(device, "vkDestroyBufferView"));
    s_vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(s_vkGetDeviceProcAddr(device, "vkCreateImage"));
    s_vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(s_vkGetDeviceProcAddr(device, "vkDestroyImage"));
    s_vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(s_vkGetDeviceProcAddr(device, "vkGetImageSubresourceLayout"));
    s_vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(s_vkGetDeviceProcAddr(device, "vkCreateImageView"));
    s_vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(s_vkGetDeviceProcAddr(device, "vkDestroyImageView"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(s_vkGetDeviceProcAddr(device, "vkCreateShaderModule"));
    s_vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(s_vkGetDeviceProcAddr(device, "vkDestroyShaderModule"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(s_vkGetDeviceProcAddr(device, "vkCreatePipelineCache"));
    s_vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(s_vkGetDeviceProcAddr(device, "vkDestroyPipelineCache"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(s_vkGetDeviceProcAddr(device, "vkGetPipelineCacheData"));
    s_vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(s_vkGetDeviceProcAddr(device, "vkMergePipelineCaches"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(s_vkGetDeviceProcAddr(device, "vkCreateGraphicsPipelines"));
    s_vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(s_vkGetDeviceProcAddr(device, "vkCreateComputePipelines"));
    s_vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(s_vkGetDeviceProcAddr(device, "vkDestroyPipeline"));
    s_vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(s_vkGetDeviceProcAddr(device, "vkCreatePipelineLayout"));
    s_vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(s_vkGetDeviceProcAddr(device, "vkDestroyPipelineLayout"));
    s_vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(s_vkGetDeviceProcAddr(device, "vkCreateSampler"));
    s_vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(s_vkGetDeviceProcAddr(device, "vkDestroySampler"));
    s_vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(s_vkGetDeviceProcAddr(device, "vkCreateDescriptorSetLayout"));
    s_vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(s_vkGetDeviceProcAddr(device, "vkDestroyDescriptorSetLayout"));
    s_vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(s_vkGetDeviceProcAddr(device, "vkCreateDescriptorPool"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(s_vkGetDeviceProcAddr(device, "vkDestroyDescriptorPool"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(s_vkGetDeviceProcAddr(device, "vkResetDescriptorPool"));
    s_vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(s_vkGetDeviceProcAddr(device, "vkAllocateDescriptorSets"));
    s_vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(s_vkGetDeviceProcAddr(device, "vkFreeDescriptorSets"));
    s_vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(s_vkGetDeviceProcAddr(device, "vkUpdateDescriptorSets"));
    s_vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(s_vkGetDeviceProcAddr(device, "vkCreateFramebuffer"));
    s_vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(s_vkGetDeviceProcAddr(device, "vkDestroyFramebuffer"));
    s_vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(s_vkGetDeviceProcAddr(device, "vkCreateRenderPass"));
    s_vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(s_vkGetDeviceProcAddr(device, "vkDestroyRenderPass"));
    s_vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(s_vkGetDeviceProcAddr(device, "vkGetRenderAreaGranularity"));
    s_vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(s_vkGetDeviceProcAddr(device, "vkCreateCommandPool"));
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
    s_vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(s_vkGetDeviceProcAddr(device, "vkDestroyCommandPool"));
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
    s_vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(s_vkGetDeviceProcAddr(device, "vkResetCommandPool"));
    s_vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(s_vkGetDeviceProcAddr(device, "vkAllocateCommandBuffers"));
    s_vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(s_vkGetDeviceProcAddr(device, "vkFreeCommandBuffers"));
    s_vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(s_vkGetDeviceProcAddr(device, "vkBeginCommandBuffer"));
    s_vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(s_vkGetDeviceProcAddr(device, "vkEndCommandBuffer"));
    s_vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(s_vkGetDeviceProcAddr(device, "vkResetCommandBuffer"));
    s_vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(s_vkGetDeviceProcAddr(device, "vkCmdBindPipeline"));
#endif // VK_VERSION_1_0

#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
    s_vkCmdSetAttachmentFeedbackLoopEnableEXT = reinterpret_cast<PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetAttachmentFeedbackLoopEnableEXT"));
#endif // VK_EXT_attachment_feedback_loop_dynamic_state

#if defined(VK_VERSION_1_0)
    s_vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewport"));
    s_vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(s_vkGetDeviceProcAddr(device, "vkCmdSetScissor"));
    s_vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(s_vkGetDeviceProcAddr(device, "vkCmdSetLineWidth"));
    s_vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthBias"));
    s_vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(s_vkGetDeviceProcAddr(device, "vkCmdSetBlendConstants"));
    s_vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthBounds"));
    s_vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilCompareMask"));
    s_vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilWriteMask"));
    s_vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilReference"));
    s_vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(s_vkGetDeviceProcAddr(device, "vkCmdBindDescriptorSets"));
    s_vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(s_vkGetDeviceProcAddr(device, "vkCmdBindIndexBuffer"));
    s_vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(s_vkGetDeviceProcAddr(device, "vkCmdBindVertexBuffers"));
    s_vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(s_vkGetDeviceProcAddr(device, "vkCmdDraw"));
    s_vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndexed"));
#endif // VK_VERSION_1_0

#if defined(VK_EXT_multi_draw)
    s_vkCmdDrawMultiEXT = reinterpret_cast<PFN_vkCmdDrawMultiEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMultiEXT"));
    s_vkCmdDrawMultiIndexedEXT = reinterpret_cast<PFN_vkCmdDrawMultiIndexedEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMultiIndexedEXT"));
#endif // VK_EXT_multi_draw

#if defined(VK_VERSION_1_0)
    s_vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndirect"));
    s_vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirect"));
    s_vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(s_vkGetDeviceProcAddr(device, "vkCmdDispatch"));
    s_vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(s_vkGetDeviceProcAddr(device, "vkCmdDispatchIndirect"));
    s_vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(s_vkGetDeviceProcAddr(device, "vkCmdCopyBuffer"));
    s_vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(s_vkGetDeviceProcAddr(device, "vkCmdCopyImage"));
    s_vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(s_vkGetDeviceProcAddr(device, "vkCmdBlitImage"));
    s_vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(s_vkGetDeviceProcAddr(device, "vkCmdCopyBufferToImage"));
    s_vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(s_vkGetDeviceProcAddr(device, "vkCmdCopyImageToBuffer"));
#endif // VK_VERSION_1_0

#if defined(VK_NV_copy_memory_indirect)
    s_vkCmdCopyMemoryIndirectNV = reinterpret_cast<PFN_vkCmdCopyMemoryIndirectNV>(s_vkGetDeviceProcAddr(device, "vkCmdCopyMemoryIndirectNV"));
    s_vkCmdCopyMemoryToImageIndirectNV = reinterpret_cast<PFN_vkCmdCopyMemoryToImageIndirectNV>(s_vkGetDeviceProcAddr(device, "vkCmdCopyMemoryToImageIndirectNV"));
#endif // VK_NV_copy_memory_indirect

#if defined(VK_VERSION_1_0)
    s_vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(s_vkGetDeviceProcAddr(device, "vkCmdUpdateBuffer"));
    s_vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(s_vkGetDeviceProcAddr(device, "vkCmdFillBuffer"));
    s_vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(s_vkGetDeviceProcAddr(device, "vkCmdClearColorImage"));
    s_vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(s_vkGetDeviceProcAddr(device, "vkCmdClearDepthStencilImage"));
    s_vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(s_vkGetDeviceProcAddr(device, "vkCmdClearAttachments"));
    s_vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(s_vkGetDeviceProcAddr(device, "vkCmdResolveImage"));
    s_vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(s_vkGetDeviceProcAddr(device, "vkCmdSetEvent"));
    s_vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(s_vkGetDeviceProcAddr(device, "vkCmdResetEvent"));
    s_vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(s_vkGetDeviceProcAddr(device, "vkCmdWaitEvents"));
    s_vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(s_vkGetDeviceProcAddr(device, "vkCmdPipelineBarrier"));
    s_vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(s_vkGetDeviceProcAddr(device, "vkCmdBeginQuery"));
    s_vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(s_vkGetDeviceProcAddr(device, "vkCmdEndQuery"));
#endif // VK_VERSION_1_0

#if defined(VK_EXT_conditional_rendering)
    s_vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBeginConditionalRenderingEXT"));
    s_vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(s_vkGetDeviceProcAddr(device, "vkCmdEndConditionalRenderingEXT"));
#endif // VK_EXT_conditional_rendering

#if defined(VK_VERSION_1_0)
    s_vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(s_vkGetDeviceProcAddr(device, "vkCmdResetQueryPool"));
    s_vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(s_vkGetDeviceProcAddr(device, "vkCmdWriteTimestamp"));
    s_vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(s_vkGetDeviceProcAddr(device, "vkCmdCopyQueryPoolResults"));
    s_vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(s_vkGetDeviceProcAddr(device, "vkCmdPushConstants"));
    s_vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(s_vkGetDeviceProcAddr(device, "vkCmdBeginRenderPass"));
    s_vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(s_vkGetDeviceProcAddr(device, "vkCmdNextSubpass"));
    s_vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(s_vkGetDeviceProcAddr(device, "vkCmdEndRenderPass"));
    s_vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(s_vkGetDeviceProcAddr(device, "vkCmdExecuteCommands"));
#endif // VK_VERSION_1_0

#if defined(VK_KHR_display_swapchain)
    s_vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(s_vkGetDeviceProcAddr(device, "vkCreateSharedSwapchainsKHR"));
#endif // VK_KHR_display_swapchain

#if defined(VK_KHR_swapchain)
    s_vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(s_vkGetDeviceProcAddr(device, "vkCreateSwapchainKHR"));
#endif // VK_KHR_swapchain

#if defined(VK_KHR_swapchain) && !defined(VKSC_VERSION_1_0)
    s_vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(s_vkGetDeviceProcAddr(device, "vkDestroySwapchainKHR"));
#endif // VK_KHR_swapchain && !VKSC_VERSION_1_0

#if defined(VK_KHR_swapchain)
    s_vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(s_vkGetDeviceProcAddr(device, "vkGetSwapchainImagesKHR"));
    s_vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(s_vkGetDeviceProcAddr(device, "vkAcquireNextImageKHR"));
    s_vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(s_vkGetDeviceProcAddr(device, "vkQueuePresentKHR"));
#endif // VK_KHR_swapchain

#if defined(VK_EXT_debug_marker)
    s_vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(s_vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectNameEXT"));
    s_vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(s_vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectTagEXT"));
    s_vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDebugMarkerBeginEXT"));
    s_vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDebugMarkerEndEXT"));
    s_vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDebugMarkerInsertEXT"));
#endif // VK_EXT_debug_marker

#if defined(VK_NV_external_memory_win32)
    s_vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(s_vkGetDeviceProcAddr(device, "vkGetMemoryWin32HandleNV"));
#endif // VK_NV_external_memory_win32

#if defined(VK_NV_device_generated_commands)
    s_vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(s_vkGetDeviceProcAddr(device, "vkCmdExecuteGeneratedCommandsNV"));
    s_vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(s_vkGetDeviceProcAddr(device, "vkCmdPreprocessGeneratedCommandsNV"));
    s_vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(s_vkGetDeviceProcAddr(device, "vkCmdBindPipelineShaderGroupNV"));
    s_vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(s_vkGetDeviceProcAddr(device, "vkGetGeneratedCommandsMemoryRequirementsNV"));
    s_vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(s_vkGetDeviceProcAddr(device, "vkCreateIndirectCommandsLayoutNV"));
    s_vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(s_vkGetDeviceProcAddr(device, "vkDestroyIndirectCommandsLayoutNV"));
#endif // VK_NV_device_generated_commands

#if defined(VK_KHR_push_descriptor)
    s_vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(s_vkGetDeviceProcAddr(device, "vkCmdPushDescriptorSetKHR"));
#endif // VK_KHR_push_descriptor

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
    s_vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(s_vkGetDeviceProcAddr(device, "vkTrimCommandPool"));
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_maintenance1) && !defined(VKSC_VERSION_1_0)
    s_vkTrimCommandPoolKHR = reinterpret_cast<PFN_vkTrimCommandPoolKHR>(s_vkGetDeviceProcAddr(device, "vkTrimCommandPoolKHR"));
#endif // VK_KHR_maintenance1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_external_memory_win32)
    s_vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(s_vkGetDeviceProcAddr(device, "vkGetMemoryWin32HandleKHR"));
    s_vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(s_vkGetDeviceProcAddr(device, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
    s_vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(s_vkGetDeviceProcAddr(device, "vkGetMemoryFdKHR"));
    s_vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(s_vkGetDeviceProcAddr(device, "vkGetMemoryFdPropertiesKHR"));
#endif // VK_KHR_external_memory_fd

#if defined(VK_KHR_external_semaphore_win32)
    s_vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(s_vkGetDeviceProcAddr(device, "vkGetSemaphoreWin32HandleKHR"));
    s_vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(s_vkGetDeviceProcAddr(device, "vkImportSemaphoreWin32HandleKHR"));
#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
    s_vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(s_vkGetDeviceProcAddr(device, "vkGetSemaphoreFdKHR"));
    s_vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(s_vkGetDeviceProcAddr(device, "vkImportSemaphoreFdKHR"));
#endif // VK_KHR_external_semaphore_fd

#if defined(VK_KHR_external_fence_win32)
    s_vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(s_vkGetDeviceProcAddr(device, "vkGetFenceWin32HandleKHR"));
    s_vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(s_vkGetDeviceProcAddr(device, "vkImportFenceWin32HandleKHR"));
#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
    s_vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(s_vkGetDeviceProcAddr(device, "vkGetFenceFdKHR"));
    s_vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(s_vkGetDeviceProcAddr(device, "vkImportFenceFdKHR"));
#endif // VK_KHR_external_fence_fd

#if defined(VK_VERSION_1_1)
    s_vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(s_vkGetDeviceProcAddr(device, "vkGetDeviceGroupPeerMemoryFeatures"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
    s_vkGetDeviceGroupPeerMemoryFeaturesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceGroupPeerMemoryFeaturesKHR"));
#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1)
    s_vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(s_vkGetDeviceProcAddr(device, "vkBindBufferMemory2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
    s_vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(s_vkGetDeviceProcAddr(device, "vkBindBufferMemory2KHR"));
#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
    s_vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(s_vkGetDeviceProcAddr(device, "vkBindImageMemory2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
    s_vkBindImageMemory2KHR = reinterpret_cast<PFN_vkBindImageMemory2KHR>(s_vkGetDeviceProcAddr(device, "vkBindImageMemory2KHR"));
#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
    s_vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(s_vkGetDeviceProcAddr(device, "vkCmdSetDeviceMask"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
    s_vkCmdSetDeviceMaskKHR = reinterpret_cast<PFN_vkCmdSetDeviceMaskKHR>(s_vkGetDeviceProcAddr(device, "vkCmdSetDeviceMaskKHR"));
#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
    s_vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceGroupPresentCapabilitiesKHR"));
    s_vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceGroupSurfacePresentModesKHR"));
    s_vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(s_vkGetDeviceProcAddr(device, "vkAcquireNextImage2KHR"));
#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1)
    s_vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(s_vkGetDeviceProcAddr(device, "vkCmdDispatchBase"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
    s_vkCmdDispatchBaseKHR = reinterpret_cast<PFN_vkCmdDispatchBaseKHR>(s_vkGetDeviceProcAddr(device, "vkCmdDispatchBaseKHR"));
#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
    s_vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(s_vkGetDeviceProcAddr(device, "vkCreateDescriptorUpdateTemplate"));
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
    s_vkCreateDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplateKHR>(s_vkGetDeviceProcAddr(device, "vkCreateDescriptorUpdateTemplateKHR"));
#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
    s_vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(s_vkGetDeviceProcAddr(device, "vkDestroyDescriptorUpdateTemplate"));
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
    s_vkDestroyDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplateKHR>(s_vkGetDeviceProcAddr(device, "vkDestroyDescriptorUpdateTemplateKHR"));
#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
    s_vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(s_vkGetDeviceProcAddr(device, "vkUpdateDescriptorSetWithTemplate"));
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
    s_vkUpdateDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplateKHR>(s_vkGetDeviceProcAddr(device, "vkUpdateDescriptorSetWithTemplateKHR"));
#endif // VK_KHR_descriptor_update_template

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
    s_vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(s_vkGetDeviceProcAddr(device, "vkCmdPushDescriptorSetWithTemplateKHR"));
#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

#if defined(VK_EXT_hdr_metadata)
    s_vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(s_vkGetDeviceProcAddr(device, "vkSetHdrMetadataEXT"));
#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_shared_presentable_image)
    s_vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(s_vkGetDeviceProcAddr(device, "vkGetSwapchainStatusKHR"));
#endif // VK_KHR_shared_presentable_image

#if defined(VK_NV_clip_space_w_scaling)
    s_vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewportWScalingNV"));
#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_discard_rectangles)
    s_vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDiscardRectangleEXT"));
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
    s_vkCmdSetDiscardRectangleEnableEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDiscardRectangleEnableEXT"));
    s_vkCmdSetDiscardRectangleModeEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleModeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDiscardRectangleModeEXT"));
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_sample_locations)
    s_vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetSampleLocationsEXT"));
#endif // VK_EXT_sample_locations

#if defined(VK_VERSION_1_1)
    s_vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(s_vkGetDeviceProcAddr(device, "vkGetBufferMemoryRequirements2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
    s_vkGetBufferMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(s_vkGetDeviceProcAddr(device, "vkGetBufferMemoryRequirements2KHR"));
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1)
    s_vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(s_vkGetDeviceProcAddr(device, "vkGetImageMemoryRequirements2"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
    s_vkGetImageMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageMemoryRequirements2KHR>(s_vkGetDeviceProcAddr(device, "vkGetImageMemoryRequirements2KHR"));
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
    s_vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(s_vkGetDeviceProcAddr(device, "vkGetImageSparseMemoryRequirements2"));
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_memory_requirements2)
    s_vkGetImageSparseMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2KHR>(s_vkGetDeviceProcAddr(device, "vkGetImageSparseMemoryRequirements2KHR"));
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_3)
    s_vkGetDeviceBufferMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirements>(s_vkGetDeviceProcAddr(device, "vkGetDeviceBufferMemoryRequirements"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
    s_vkGetDeviceBufferMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirementsKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceBufferMemoryRequirementsKHR"));
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
    s_vkGetDeviceImageMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirements>(s_vkGetDeviceProcAddr(device, "vkGetDeviceImageMemoryRequirements"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
    s_vkGetDeviceImageMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirementsKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceImageMemoryRequirementsKHR"));
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
    s_vkGetDeviceImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageSparseMemoryRequirements>(s_vkGetDeviceProcAddr(device, "vkGetDeviceImageSparseMemoryRequirements"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
    s_vkGetDeviceImageSparseMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetDeviceImageSparseMemoryRequirementsKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceImageSparseMemoryRequirementsKHR"));
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_1)
    s_vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(s_vkGetDeviceProcAddr(device, "vkCreateSamplerYcbcrConversion"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
    s_vkCreateSamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversionKHR>(s_vkGetDeviceProcAddr(device, "vkCreateSamplerYcbcrConversionKHR"));
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
    s_vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(s_vkGetDeviceProcAddr(device, "vkDestroySamplerYcbcrConversion"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
    s_vkDestroySamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversionKHR>(s_vkGetDeviceProcAddr(device, "vkDestroySamplerYcbcrConversionKHR"));
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
    s_vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(s_vkGetDeviceProcAddr(device, "vkGetDeviceQueue2"));
#endif // VK_VERSION_1_1

#if defined(VK_EXT_validation_cache)
    s_vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(s_vkGetDeviceProcAddr(device, "vkCreateValidationCacheEXT"));
    s_vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(s_vkGetDeviceProcAddr(device, "vkDestroyValidationCacheEXT"));
    s_vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetValidationCacheDataEXT"));
    s_vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(s_vkGetDeviceProcAddr(device, "vkMergeValidationCachesEXT"));
#endif // VK_EXT_validation_cache

#if defined(VK_VERSION_1_1)
    s_vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(s_vkGetDeviceProcAddr(device, "vkGetDescriptorSetLayoutSupport"));
#endif // VK_VERSION_1_1

#if defined(VK_KHR_maintenance3)
    s_vkGetDescriptorSetLayoutSupportKHR = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupportKHR>(s_vkGetDeviceProcAddr(device, "vkGetDescriptorSetLayoutSupportKHR"));
#endif // VK_KHR_maintenance3

#if defined(VK_AMD_shader_info)
    s_vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(s_vkGetDeviceProcAddr(device, "vkGetShaderInfoAMD"));
#endif // VK_AMD_shader_info

#if defined(VK_EXT_calibrated_timestamps)
    s_vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(s_vkGetDeviceProcAddr(device, "vkGetCalibratedTimestampsEXT"));
#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
    s_vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(s_vkGetDeviceProcAddr(device, "vkSetDebugUtilsObjectNameEXT"));
    s_vkSetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(s_vkGetDeviceProcAddr(device, "vkSetDebugUtilsObjectTagEXT"));
    s_vkQueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(s_vkGetDeviceProcAddr(device, "vkQueueBeginDebugUtilsLabelEXT"));
    s_vkQueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(s_vkGetDeviceProcAddr(device, "vkQueueEndDebugUtilsLabelEXT"));
    s_vkQueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(s_vkGetDeviceProcAddr(device, "vkQueueInsertDebugUtilsLabelEXT"));
    s_vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBeginDebugUtilsLabelEXT"));
    s_vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(s_vkGetDeviceProcAddr(device, "vkCmdEndDebugUtilsLabelEXT"));
    s_vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(s_vkGetDeviceProcAddr(device, "vkCmdInsertDebugUtilsLabelEXT"));
#endif // VK_EXT_debug_utils

#if defined(VK_EXT_external_memory_host)
    s_vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(s_vkGetDeviceProcAddr(device, "vkGetMemoryHostPointerPropertiesEXT"));
#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
    s_vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(s_vkGetDeviceProcAddr(device, "vkCmdWriteBufferMarkerAMD"));
#endif // VK_AMD_buffer_marker

#if defined(VK_VERSION_1_2)
    s_vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(s_vkGetDeviceProcAddr(device, "vkCreateRenderPass2"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
    s_vkCreateRenderPass2KHR = reinterpret_cast<PFN_vkCreateRenderPass2KHR>(s_vkGetDeviceProcAddr(device, "vkCreateRenderPass2KHR"));
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
    s_vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(s_vkGetDeviceProcAddr(device, "vkCmdBeginRenderPass2"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
    s_vkCmdBeginRenderPass2KHR = reinterpret_cast<PFN_vkCmdBeginRenderPass2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdBeginRenderPass2KHR"));
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
    s_vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(s_vkGetDeviceProcAddr(device, "vkCmdNextSubpass2"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
    s_vkCmdNextSubpass2KHR = reinterpret_cast<PFN_vkCmdNextSubpass2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdNextSubpass2KHR"));
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
    s_vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(s_vkGetDeviceProcAddr(device, "vkCmdEndRenderPass2"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
    s_vkCmdEndRenderPass2KHR = reinterpret_cast<PFN_vkCmdEndRenderPass2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdEndRenderPass2KHR"));
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
    s_vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(s_vkGetDeviceProcAddr(device, "vkGetSemaphoreCounterValue"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
    s_vkGetSemaphoreCounterValueKHR = reinterpret_cast<PFN_vkGetSemaphoreCounterValueKHR>(s_vkGetDeviceProcAddr(device, "vkGetSemaphoreCounterValueKHR"));
#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
    s_vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(s_vkGetDeviceProcAddr(device, "vkWaitSemaphores"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
    s_vkWaitSemaphoresKHR = reinterpret_cast<PFN_vkWaitSemaphoresKHR>(s_vkGetDeviceProcAddr(device, "vkWaitSemaphoresKHR"));
#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
    s_vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(s_vkGetDeviceProcAddr(device, "vkSignalSemaphore"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
    s_vkSignalSemaphoreKHR = reinterpret_cast<PFN_vkSignalSemaphoreKHR>(s_vkGetDeviceProcAddr(device, "vkSignalSemaphoreKHR"));
#endif // VK_KHR_timeline_semaphore

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
    s_vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(s_vkGetDeviceProcAddr(device, "vkGetAndroidHardwareBufferPropertiesANDROID"));
    s_vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(s_vkGetDeviceProcAddr(device, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_VERSION_1_2)
    s_vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndirectCount"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
    s_vkCmdDrawIndirectCountKHR = reinterpret_cast<PFN_vkCmdDrawIndirectCountKHR>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndirectCountKHR"));
#endif // VK_KHR_draw_indirect_count

#if defined(VK_VERSION_1_2)
    s_vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirectCount"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
    s_vkCmdDrawIndexedIndirectCountKHR = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountKHR>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirectCountKHR"));
#endif // VK_KHR_draw_indirect_count

#if defined(VK_NV_device_diagnostic_checkpoints)
    s_vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCheckpointNV"));
    s_vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(s_vkGetDeviceProcAddr(device, "vkGetQueueCheckpointDataNV"));
#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_EXT_transform_feedback)
    s_vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBindTransformFeedbackBuffersEXT"));
    s_vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBeginTransformFeedbackEXT"));
    s_vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(s_vkGetDeviceProcAddr(device, "vkCmdEndTransformFeedbackEXT"));
    s_vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBeginQueryIndexedEXT"));
    s_vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(s_vkGetDeviceProcAddr(device, "vkCmdEndQueryIndexedEXT"));
    s_vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDrawIndirectByteCountEXT"));
#endif // VK_EXT_transform_feedback

#if defined(VK_NV_scissor_exclusive)
    s_vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetExclusiveScissorNV"));
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
    s_vkCmdSetExclusiveScissorEnableNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorEnableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetExclusiveScissorEnableNV"));
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_shading_rate_image)
    s_vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(s_vkGetDeviceProcAddr(device, "vkCmdBindShadingRateImageNV"));
    s_vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewportShadingRatePaletteNV"));
    s_vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoarseSampleOrderNV"));
#endif // VK_NV_shading_rate_image

#if defined(VK_NV_mesh_shader)
    s_vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMeshTasksNV"));
    s_vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMeshTasksIndirectNV"));
    s_vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMeshTasksIndirectCountNV"));
#endif // VK_NV_mesh_shader

#if defined(VK_EXT_mesh_shader)
    s_vkCmdDrawMeshTasksEXT = reinterpret_cast<PFN_vkCmdDrawMeshTasksEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMeshTasksEXT"));
    s_vkCmdDrawMeshTasksIndirectEXT = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMeshTasksIndirectEXT"));
    s_vkCmdDrawMeshTasksIndirectCountEXT = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountEXT>(s_vkGetDeviceProcAddr(device, "vkCmdDrawMeshTasksIndirectCountEXT"));
#endif // VK_EXT_mesh_shader

#if defined(VK_NV_ray_tracing)
    s_vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(s_vkGetDeviceProcAddr(device, "vkCompileDeferredNV"));
    s_vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(s_vkGetDeviceProcAddr(device, "vkCreateAccelerationStructureNV"));
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
    s_vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(s_vkGetDeviceProcAddr(device, "vkDestroyAccelerationStructureKHR"));
#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
    s_vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(s_vkGetDeviceProcAddr(device, "vkDestroyAccelerationStructureNV"));
    s_vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(s_vkGetDeviceProcAddr(device, "vkGetAccelerationStructureMemoryRequirementsNV"));
    s_vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(s_vkGetDeviceProcAddr(device, "vkBindAccelerationStructureMemoryNV"));
    s_vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(s_vkGetDeviceProcAddr(device, "vkCmdCopyAccelerationStructureNV"));
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
    s_vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyAccelerationStructureKHR"));
    s_vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(s_vkGetDeviceProcAddr(device, "vkCopyAccelerationStructureKHR"));
    s_vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyAccelerationStructureToMemoryKHR"));
    s_vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(s_vkGetDeviceProcAddr(device, "vkCopyAccelerationStructureToMemoryKHR"));
    s_vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyMemoryToAccelerationStructureKHR"));
    s_vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(s_vkGetDeviceProcAddr(device, "vkCopyMemoryToAccelerationStructureKHR"));
    s_vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(s_vkGetDeviceProcAddr(device, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
    s_vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(s_vkGetDeviceProcAddr(device, "vkCmdWriteAccelerationStructuresPropertiesNV"));
    s_vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(s_vkGetDeviceProcAddr(device, "vkCmdBuildAccelerationStructureNV"));
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
    s_vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(s_vkGetDeviceProcAddr(device, "vkWriteAccelerationStructuresPropertiesKHR"));
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
    s_vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(s_vkGetDeviceProcAddr(device, "vkCmdTraceRaysKHR"));
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
    s_vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(s_vkGetDeviceProcAddr(device, "vkCmdTraceRaysNV"));
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
    s_vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(s_vkGetDeviceProcAddr(device, "vkGetRayTracingShaderGroupHandlesKHR"));
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
    s_vkGetRayTracingShaderGroupHandlesNV = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesNV>(s_vkGetDeviceProcAddr(device, "vkGetRayTracingShaderGroupHandlesNV"));
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
    s_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(s_vkGetDeviceProcAddr(device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
    s_vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(s_vkGetDeviceProcAddr(device, "vkGetAccelerationStructureHandleNV"));
    s_vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(s_vkGetDeviceProcAddr(device, "vkCreateRayTracingPipelinesNV"));
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
    s_vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(s_vkGetDeviceProcAddr(device, "vkCreateRayTracingPipelinesKHR"));
    s_vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(s_vkGetDeviceProcAddr(device, "vkCmdTraceRaysIndirectKHR"));
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_ray_tracing_maintenance1)
    s_vkCmdTraceRaysIndirect2KHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirect2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdTraceRaysIndirect2KHR"));
#endif // VK_KHR_ray_tracing_maintenance1

#if defined(VK_KHR_acceleration_structure)
    s_vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
    s_vkGetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupStackSizeKHR>(s_vkGetDeviceProcAddr(device, "vkGetRayTracingShaderGroupStackSizeKHR"));
    s_vkCmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<PFN_vkCmdSetRayTracingPipelineStackSizeKHR>(s_vkGetDeviceProcAddr(device, "vkCmdSetRayTracingPipelineStackSizeKHR"));
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NVX_image_view_handle)
    s_vkGetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(s_vkGetDeviceProcAddr(device, "vkGetImageViewHandleNVX"));
    s_vkGetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(s_vkGetDeviceProcAddr(device, "vkGetImageViewAddressNVX"));
#endif // VK_NVX_image_view_handle

#if defined(VK_EXT_full_screen_exclusive)
    s_vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(s_vkGetDeviceProcAddr(device, "vkGetDeviceGroupSurfacePresentModes2EXT"));
    s_vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(s_vkGetDeviceProcAddr(device, "vkAcquireFullScreenExclusiveModeEXT"));
    s_vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(s_vkGetDeviceProcAddr(device, "vkReleaseFullScreenExclusiveModeEXT"));
#endif // VK_EXT_full_screen_exclusive

#if defined(VK_VERSION_1_2)
    s_vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(s_vkGetDeviceProcAddr(device, "vkGetBufferOpaqueCaptureAddress"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
    s_vkGetBufferOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddressKHR>(s_vkGetDeviceProcAddr(device, "vkGetBufferOpaqueCaptureAddressKHR"));
#endif // VK_KHR_buffer_device_address

#if defined(VK_VERSION_1_2)
    s_vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(s_vkGetDeviceProcAddr(device, "vkGetBufferDeviceAddress"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
    s_vkGetBufferDeviceAddressKHR = reinterpret_cast<PFN_vkGetBufferDeviceAddressKHR>(s_vkGetDeviceProcAddr(device, "vkGetBufferDeviceAddressKHR"));
#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_buffer_device_address)
    s_vkGetBufferDeviceAddressEXT = reinterpret_cast<PFN_vkGetBufferDeviceAddressEXT>(s_vkGetDeviceProcAddr(device, "vkGetBufferDeviceAddressEXT"));
#endif // VK_EXT_buffer_device_address

#if defined(VK_VERSION_1_2)
    s_vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(s_vkGetDeviceProcAddr(device, "vkGetDeviceMemoryOpaqueCaptureAddress"));
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
    s_vkGetDeviceMemoryOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR"));
#endif // VK_KHR_buffer_device_address

#if defined(VK_KHR_pipeline_executable_properties)
    s_vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(s_vkGetDeviceProcAddr(device, "vkGetPipelineExecutablePropertiesKHR"));
    s_vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(s_vkGetDeviceProcAddr(device, "vkGetPipelineExecutableStatisticsKHR"));
    s_vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(s_vkGetDeviceProcAddr(device, "vkGetPipelineExecutableInternalRepresentationsKHR"));
#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_EXT_line_rasterization)
    s_vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetLineStippleEXT"));
#endif // VK_EXT_line_rasterization

#if defined(VKSC_VERSION_1_0)
    s_vkGetFaultData = reinterpret_cast<PFN_vkGetFaultData>(s_vkGetDeviceProcAddr(device, "vkGetFaultData"));
#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_acceleration_structure)
    s_vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(s_vkGetDeviceProcAddr(device, "vkCreateAccelerationStructureKHR"));
    s_vkCmdBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(s_vkGetDeviceProcAddr(device, "vkCmdBuildAccelerationStructuresKHR"));
    s_vkCmdBuildAccelerationStructuresIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresIndirectKHR>(s_vkGetDeviceProcAddr(device, "vkCmdBuildAccelerationStructuresIndirectKHR"));
    s_vkBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkBuildAccelerationStructuresKHR>(s_vkGetDeviceProcAddr(device, "vkBuildAccelerationStructuresKHR"));
    s_vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(s_vkGetDeviceProcAddr(device, "vkGetAccelerationStructureDeviceAddressKHR"));
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_deferred_host_operations)
    s_vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(s_vkGetDeviceProcAddr(device, "vkCreateDeferredOperationKHR"));
    s_vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(s_vkGetDeviceProcAddr(device, "vkDestroyDeferredOperationKHR"));
    s_vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeferredOperationMaxConcurrencyKHR"));
    s_vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(s_vkGetDeviceProcAddr(device, "vkGetDeferredOperationResultKHR"));
    s_vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(s_vkGetDeviceProcAddr(device, "vkDeferredOperationJoinKHR"));
#endif // VK_KHR_deferred_host_operations

#if defined(VK_VERSION_1_3)
    s_vkCmdSetCullMode = reinterpret_cast<PFN_vkCmdSetCullMode>(s_vkGetDeviceProcAddr(device, "vkCmdSetCullMode"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetCullModeEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetFrontFace = reinterpret_cast<PFN_vkCmdSetFrontFace>(s_vkGetDeviceProcAddr(device, "vkCmdSetFrontFace"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetFrontFaceEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetPrimitiveTopology = reinterpret_cast<PFN_vkCmdSetPrimitiveTopology>(s_vkGetDeviceProcAddr(device, "vkCmdSetPrimitiveTopology"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetPrimitiveTopologyEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetViewportWithCount = reinterpret_cast<PFN_vkCmdSetViewportWithCount>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewportWithCount"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewportWithCountEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetScissorWithCount = reinterpret_cast<PFN_vkCmdSetScissorWithCount>(s_vkGetDeviceProcAddr(device, "vkCmdSetScissorWithCount"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetScissorWithCountEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdBindVertexBuffers2 = reinterpret_cast<PFN_vkCmdBindVertexBuffers2>(s_vkGetDeviceProcAddr(device, "vkCmdBindVertexBuffers2"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(s_vkGetDeviceProcAddr(device, "vkCmdBindVertexBuffers2EXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetDepthTestEnable = reinterpret_cast<PFN_vkCmdSetDepthTestEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthTestEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthTestEnableEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetDepthWriteEnable = reinterpret_cast<PFN_vkCmdSetDepthWriteEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthWriteEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthWriteEnableEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetDepthCompareOp = reinterpret_cast<PFN_vkCmdSetDepthCompareOp>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthCompareOp"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthCompareOpEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetDepthBoundsTestEnable = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthBoundsTestEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthBoundsTestEnableEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetStencilTestEnable = reinterpret_cast<PFN_vkCmdSetStencilTestEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilTestEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilTestEnableEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetStencilOp = reinterpret_cast<PFN_vkCmdSetStencilOp>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilOp"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetStencilOpEXT"));
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
    s_vkCmdSetPatchControlPointsEXT = reinterpret_cast<PFN_vkCmdSetPatchControlPointsEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetPatchControlPointsEXT"));
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetRasterizerDiscardEnable = reinterpret_cast<PFN_vkCmdSetRasterizerDiscardEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetRasterizerDiscardEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
    s_vkCmdSetRasterizerDiscardEnableEXT = reinterpret_cast<PFN_vkCmdSetRasterizerDiscardEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetRasterizerDiscardEnableEXT"));
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetDepthBiasEnable = reinterpret_cast<PFN_vkCmdSetDepthBiasEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthBiasEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
    s_vkCmdSetDepthBiasEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBiasEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthBiasEnableEXT"));
    s_vkCmdSetLogicOpEXT = reinterpret_cast<PFN_vkCmdSetLogicOpEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetLogicOpEXT"));
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCmdSetPrimitiveRestartEnable = reinterpret_cast<PFN_vkCmdSetPrimitiveRestartEnable>(s_vkGetDeviceProcAddr(device, "vkCmdSetPrimitiveRestartEnable"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
    s_vkCmdSetPrimitiveRestartEnableEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveRestartEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetPrimitiveRestartEnableEXT"));
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state3) || defined(VK_EXT_shader_object)
    s_vkCmdSetTessellationDomainOriginEXT = reinterpret_cast<PFN_vkCmdSetTessellationDomainOriginEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetTessellationDomainOriginEXT"));
    s_vkCmdSetDepthClampEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthClampEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthClampEnableEXT"));
    s_vkCmdSetPolygonModeEXT = reinterpret_cast<PFN_vkCmdSetPolygonModeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetPolygonModeEXT"));
    s_vkCmdSetRasterizationSamplesEXT = reinterpret_cast<PFN_vkCmdSetRasterizationSamplesEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetRasterizationSamplesEXT"));
    s_vkCmdSetSampleMaskEXT = reinterpret_cast<PFN_vkCmdSetSampleMaskEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetSampleMaskEXT"));
    s_vkCmdSetAlphaToCoverageEnableEXT = reinterpret_cast<PFN_vkCmdSetAlphaToCoverageEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetAlphaToCoverageEnableEXT"));
    s_vkCmdSetAlphaToOneEnableEXT = reinterpret_cast<PFN_vkCmdSetAlphaToOneEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetAlphaToOneEnableEXT"));
    s_vkCmdSetLogicOpEnableEXT = reinterpret_cast<PFN_vkCmdSetLogicOpEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetLogicOpEnableEXT"));
    s_vkCmdSetColorBlendEnableEXT = reinterpret_cast<PFN_vkCmdSetColorBlendEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetColorBlendEnableEXT"));
    s_vkCmdSetColorBlendEquationEXT = reinterpret_cast<PFN_vkCmdSetColorBlendEquationEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetColorBlendEquationEXT"));
    s_vkCmdSetColorWriteMaskEXT = reinterpret_cast<PFN_vkCmdSetColorWriteMaskEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetColorWriteMaskEXT"));
    s_vkCmdSetRasterizationStreamEXT = reinterpret_cast<PFN_vkCmdSetRasterizationStreamEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetRasterizationStreamEXT"));
    s_vkCmdSetConservativeRasterizationModeEXT = reinterpret_cast<PFN_vkCmdSetConservativeRasterizationModeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetConservativeRasterizationModeEXT"));
    s_vkCmdSetExtraPrimitiveOverestimationSizeEXT = reinterpret_cast<PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT"));
    s_vkCmdSetDepthClipEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthClipEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthClipEnableEXT"));
    s_vkCmdSetSampleLocationsEnableEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetSampleLocationsEnableEXT"));
    s_vkCmdSetColorBlendAdvancedEXT = reinterpret_cast<PFN_vkCmdSetColorBlendAdvancedEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetColorBlendAdvancedEXT"));
    s_vkCmdSetProvokingVertexModeEXT = reinterpret_cast<PFN_vkCmdSetProvokingVertexModeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetProvokingVertexModeEXT"));
    s_vkCmdSetLineRasterizationModeEXT = reinterpret_cast<PFN_vkCmdSetLineRasterizationModeEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetLineRasterizationModeEXT"));
    s_vkCmdSetLineStippleEnableEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetLineStippleEnableEXT"));
    s_vkCmdSetDepthClipNegativeOneToOneEXT = reinterpret_cast<PFN_vkCmdSetDepthClipNegativeOneToOneEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDepthClipNegativeOneToOneEXT"));
    s_vkCmdSetViewportWScalingEnableNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingEnableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewportWScalingEnableNV"));
    s_vkCmdSetViewportSwizzleNV = reinterpret_cast<PFN_vkCmdSetViewportSwizzleNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetViewportSwizzleNV"));
    s_vkCmdSetCoverageToColorEnableNV = reinterpret_cast<PFN_vkCmdSetCoverageToColorEnableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoverageToColorEnableNV"));
    s_vkCmdSetCoverageToColorLocationNV = reinterpret_cast<PFN_vkCmdSetCoverageToColorLocationNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoverageToColorLocationNV"));
    s_vkCmdSetCoverageModulationModeNV = reinterpret_cast<PFN_vkCmdSetCoverageModulationModeNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoverageModulationModeNV"));
    s_vkCmdSetCoverageModulationTableEnableNV = reinterpret_cast<PFN_vkCmdSetCoverageModulationTableEnableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoverageModulationTableEnableNV"));
    s_vkCmdSetCoverageModulationTableNV = reinterpret_cast<PFN_vkCmdSetCoverageModulationTableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoverageModulationTableNV"));
    s_vkCmdSetShadingRateImageEnableNV = reinterpret_cast<PFN_vkCmdSetShadingRateImageEnableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetShadingRateImageEnableNV"));
    s_vkCmdSetCoverageReductionModeNV = reinterpret_cast<PFN_vkCmdSetCoverageReductionModeNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetCoverageReductionModeNV"));
    s_vkCmdSetRepresentativeFragmentTestEnableNV = reinterpret_cast<PFN_vkCmdSetRepresentativeFragmentTestEnableNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetRepresentativeFragmentTestEnableNV"));
#endif // VK_EXT_extended_dynamic_state3 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
    s_vkCreatePrivateDataSlot = reinterpret_cast<PFN_vkCreatePrivateDataSlot>(s_vkGetDeviceProcAddr(device, "vkCreatePrivateDataSlot"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
    s_vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(s_vkGetDeviceProcAddr(device, "vkCreatePrivateDataSlotEXT"));
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
    s_vkDestroyPrivateDataSlot = reinterpret_cast<PFN_vkDestroyPrivateDataSlot>(s_vkGetDeviceProcAddr(device, "vkDestroyPrivateDataSlot"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
    s_vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(s_vkGetDeviceProcAddr(device, "vkDestroyPrivateDataSlotEXT"));
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
    s_vkSetPrivateData = reinterpret_cast<PFN_vkSetPrivateData>(s_vkGetDeviceProcAddr(device, "vkSetPrivateData"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
    s_vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(s_vkGetDeviceProcAddr(device, "vkSetPrivateDataEXT"));
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
    s_vkGetPrivateData = reinterpret_cast<PFN_vkGetPrivateData>(s_vkGetDeviceProcAddr(device, "vkGetPrivateData"));
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
    s_vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetPrivateDataEXT"));
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
    s_vkCmdCopyBuffer2 = reinterpret_cast<PFN_vkCmdCopyBuffer2>(s_vkGetDeviceProcAddr(device, "vkCmdCopyBuffer2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
    s_vkCmdCopyBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyBuffer2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyBuffer2KHR"));
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
    s_vkCmdCopyImage2 = reinterpret_cast<PFN_vkCmdCopyImage2>(s_vkGetDeviceProcAddr(device, "vkCmdCopyImage2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
    s_vkCmdCopyImage2KHR = reinterpret_cast<PFN_vkCmdCopyImage2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyImage2KHR"));
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
    s_vkCmdBlitImage2 = reinterpret_cast<PFN_vkCmdBlitImage2>(s_vkGetDeviceProcAddr(device, "vkCmdBlitImage2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
    s_vkCmdBlitImage2KHR = reinterpret_cast<PFN_vkCmdBlitImage2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdBlitImage2KHR"));
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
    s_vkCmdCopyBufferToImage2 = reinterpret_cast<PFN_vkCmdCopyBufferToImage2>(s_vkGetDeviceProcAddr(device, "vkCmdCopyBufferToImage2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
    s_vkCmdCopyBufferToImage2KHR = reinterpret_cast<PFN_vkCmdCopyBufferToImage2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyBufferToImage2KHR"));
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
    s_vkCmdCopyImageToBuffer2 = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2>(s_vkGetDeviceProcAddr(device, "vkCmdCopyImageToBuffer2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
    s_vkCmdCopyImageToBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdCopyImageToBuffer2KHR"));
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
    s_vkCmdResolveImage2 = reinterpret_cast<PFN_vkCmdResolveImage2>(s_vkGetDeviceProcAddr(device, "vkCmdResolveImage2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
    s_vkCmdResolveImage2KHR = reinterpret_cast<PFN_vkCmdResolveImage2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdResolveImage2KHR"));
#endif // VK_KHR_copy_commands2

#if defined(VK_KHR_fragment_shading_rate)
    s_vkCmdSetFragmentShadingRateKHR = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateKHR>(s_vkGetDeviceProcAddr(device, "vkCmdSetFragmentShadingRateKHR"));
#endif // VK_KHR_fragment_shading_rate

#if defined(VK_NV_fragment_shading_rate_enums)
    s_vkCmdSetFragmentShadingRateEnumNV = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateEnumNV>(s_vkGetDeviceProcAddr(device, "vkCmdSetFragmentShadingRateEnumNV"));
#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_acceleration_structure)
    s_vkGetAccelerationStructureBuildSizesKHR = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(s_vkGetDeviceProcAddr(device, "vkGetAccelerationStructureBuildSizesKHR"));
#endif // VK_KHR_acceleration_structure

#if defined(VK_EXT_vertex_input_dynamic_state) || defined(VK_EXT_shader_object)
    s_vkCmdSetVertexInputEXT = reinterpret_cast<PFN_vkCmdSetVertexInputEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetVertexInputEXT"));
#endif // VK_EXT_vertex_input_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_color_write_enable)
    s_vkCmdSetColorWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetColorWriteEnableEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetColorWriteEnableEXT"));
#endif // VK_EXT_color_write_enable

#if defined(VK_VERSION_1_3)
    s_vkCmdSetEvent2 = reinterpret_cast<PFN_vkCmdSetEvent2>(s_vkGetDeviceProcAddr(device, "vkCmdSetEvent2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
    s_vkCmdSetEvent2KHR = reinterpret_cast<PFN_vkCmdSetEvent2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdSetEvent2KHR"));
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
    s_vkCmdResetEvent2 = reinterpret_cast<PFN_vkCmdResetEvent2>(s_vkGetDeviceProcAddr(device, "vkCmdResetEvent2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
    s_vkCmdResetEvent2KHR = reinterpret_cast<PFN_vkCmdResetEvent2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdResetEvent2KHR"));
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
    s_vkCmdWaitEvents2 = reinterpret_cast<PFN_vkCmdWaitEvents2>(s_vkGetDeviceProcAddr(device, "vkCmdWaitEvents2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
    s_vkCmdWaitEvents2KHR = reinterpret_cast<PFN_vkCmdWaitEvents2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdWaitEvents2KHR"));
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
    s_vkCmdPipelineBarrier2 = reinterpret_cast<PFN_vkCmdPipelineBarrier2>(s_vkGetDeviceProcAddr(device, "vkCmdPipelineBarrier2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
    s_vkCmdPipelineBarrier2KHR = reinterpret_cast<PFN_vkCmdPipelineBarrier2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdPipelineBarrier2KHR"));
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
    s_vkQueueSubmit2 = reinterpret_cast<PFN_vkQueueSubmit2>(s_vkGetDeviceProcAddr(device, "vkQueueSubmit2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
    s_vkQueueSubmit2KHR = reinterpret_cast<PFN_vkQueueSubmit2KHR>(s_vkGetDeviceProcAddr(device, "vkQueueSubmit2KHR"));
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
    s_vkCmdWriteTimestamp2 = reinterpret_cast<PFN_vkCmdWriteTimestamp2>(s_vkGetDeviceProcAddr(device, "vkCmdWriteTimestamp2"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
    s_vkCmdWriteTimestamp2KHR = reinterpret_cast<PFN_vkCmdWriteTimestamp2KHR>(s_vkGetDeviceProcAddr(device, "vkCmdWriteTimestamp2KHR"));
    s_vkCmdWriteBufferMarker2AMD = reinterpret_cast<PFN_vkCmdWriteBufferMarker2AMD>(s_vkGetDeviceProcAddr(device, "vkCmdWriteBufferMarker2AMD"));
    s_vkGetQueueCheckpointData2NV = reinterpret_cast<PFN_vkGetQueueCheckpointData2NV>(s_vkGetDeviceProcAddr(device, "vkGetQueueCheckpointData2NV"));
#endif // VK_KHR_synchronization2

#if defined(VKSC_VERSION_1_0)
    s_vkGetCommandPoolMemoryConsumption = reinterpret_cast<PFN_vkGetCommandPoolMemoryConsumption>(s_vkGetDeviceProcAddr(device, "vkGetCommandPoolMemoryConsumption"));
#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_video_queue)
    s_vkCreateVideoSessionKHR = reinterpret_cast<PFN_vkCreateVideoSessionKHR>(s_vkGetDeviceProcAddr(device, "vkCreateVideoSessionKHR"));
    s_vkDestroyVideoSessionKHR = reinterpret_cast<PFN_vkDestroyVideoSessionKHR>(s_vkGetDeviceProcAddr(device, "vkDestroyVideoSessionKHR"));
    s_vkCreateVideoSessionParametersKHR = reinterpret_cast<PFN_vkCreateVideoSessionParametersKHR>(s_vkGetDeviceProcAddr(device, "vkCreateVideoSessionParametersKHR"));
    s_vkUpdateVideoSessionParametersKHR = reinterpret_cast<PFN_vkUpdateVideoSessionParametersKHR>(s_vkGetDeviceProcAddr(device, "vkUpdateVideoSessionParametersKHR"));
    s_vkDestroyVideoSessionParametersKHR = reinterpret_cast<PFN_vkDestroyVideoSessionParametersKHR>(s_vkGetDeviceProcAddr(device, "vkDestroyVideoSessionParametersKHR"));
    s_vkGetVideoSessionMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetVideoSessionMemoryRequirementsKHR>(s_vkGetDeviceProcAddr(device, "vkGetVideoSessionMemoryRequirementsKHR"));
    s_vkBindVideoSessionMemoryKHR = reinterpret_cast<PFN_vkBindVideoSessionMemoryKHR>(s_vkGetDeviceProcAddr(device, "vkBindVideoSessionMemoryKHR"));
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
    s_vkCmdDecodeVideoKHR = reinterpret_cast<PFN_vkCmdDecodeVideoKHR>(s_vkGetDeviceProcAddr(device, "vkCmdDecodeVideoKHR"));
#endif // VK_KHR_video_decode_queue

#if defined(VK_KHR_video_queue)
    s_vkCmdBeginVideoCodingKHR = reinterpret_cast<PFN_vkCmdBeginVideoCodingKHR>(s_vkGetDeviceProcAddr(device, "vkCmdBeginVideoCodingKHR"));
    s_vkCmdControlVideoCodingKHR = reinterpret_cast<PFN_vkCmdControlVideoCodingKHR>(s_vkGetDeviceProcAddr(device, "vkCmdControlVideoCodingKHR"));
    s_vkCmdEndVideoCodingKHR = reinterpret_cast<PFN_vkCmdEndVideoCodingKHR>(s_vkGetDeviceProcAddr(device, "vkCmdEndVideoCodingKHR"));
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_encode_queue)
    s_vkCmdEncodeVideoKHR = reinterpret_cast<PFN_vkCmdEncodeVideoKHR>(s_vkGetDeviceProcAddr(device, "vkCmdEncodeVideoKHR"));
#endif // VK_KHR_video_encode_queue

#if defined(VK_NV_memory_decompression)
    s_vkCmdDecompressMemoryNV = reinterpret_cast<PFN_vkCmdDecompressMemoryNV>(s_vkGetDeviceProcAddr(device, "vkCmdDecompressMemoryNV"));
    s_vkCmdDecompressMemoryIndirectCountNV = reinterpret_cast<PFN_vkCmdDecompressMemoryIndirectCountNV>(s_vkGetDeviceProcAddr(device, "vkCmdDecompressMemoryIndirectCountNV"));
#endif // VK_NV_memory_decompression

#if defined(VK_NVX_binary_import)
    s_vkCreateCuModuleNVX = reinterpret_cast<PFN_vkCreateCuModuleNVX>(s_vkGetDeviceProcAddr(device, "vkCreateCuModuleNVX"));
    s_vkCreateCuFunctionNVX = reinterpret_cast<PFN_vkCreateCuFunctionNVX>(s_vkGetDeviceProcAddr(device, "vkCreateCuFunctionNVX"));
    s_vkDestroyCuModuleNVX = reinterpret_cast<PFN_vkDestroyCuModuleNVX>(s_vkGetDeviceProcAddr(device, "vkDestroyCuModuleNVX"));
    s_vkDestroyCuFunctionNVX = reinterpret_cast<PFN_vkDestroyCuFunctionNVX>(s_vkGetDeviceProcAddr(device, "vkDestroyCuFunctionNVX"));
    s_vkCmdCuLaunchKernelNVX = reinterpret_cast<PFN_vkCmdCuLaunchKernelNVX>(s_vkGetDeviceProcAddr(device, "vkCmdCuLaunchKernelNVX"));
#endif // VK_NVX_binary_import

#if defined(VK_EXT_descriptor_buffer)
    s_vkGetDescriptorSetLayoutSizeEXT = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSizeEXT>(s_vkGetDeviceProcAddr(device, "vkGetDescriptorSetLayoutSizeEXT"));
    s_vkGetDescriptorSetLayoutBindingOffsetEXT = reinterpret_cast<PFN_vkGetDescriptorSetLayoutBindingOffsetEXT>(s_vkGetDeviceProcAddr(device, "vkGetDescriptorSetLayoutBindingOffsetEXT"));
    s_vkGetDescriptorEXT = reinterpret_cast<PFN_vkGetDescriptorEXT>(s_vkGetDeviceProcAddr(device, "vkGetDescriptorEXT"));
    s_vkCmdBindDescriptorBuffersEXT = reinterpret_cast<PFN_vkCmdBindDescriptorBuffersEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBindDescriptorBuffersEXT"));
    s_vkCmdSetDescriptorBufferOffsetsEXT = reinterpret_cast<PFN_vkCmdSetDescriptorBufferOffsetsEXT>(s_vkGetDeviceProcAddr(device, "vkCmdSetDescriptorBufferOffsetsEXT"));
    s_vkCmdBindDescriptorBufferEmbeddedSamplersEXT = reinterpret_cast<PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT"));
    s_vkGetBufferOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetBufferOpaqueCaptureDescriptorDataEXT"));
    s_vkGetImageOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetImageOpaqueCaptureDescriptorDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetImageOpaqueCaptureDescriptorDataEXT"));
    s_vkGetImageViewOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT"));
    s_vkGetSamplerOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT"));
    s_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT"));
#endif // VK_EXT_descriptor_buffer

#if defined(VK_EXT_pageable_device_local_memory)
    s_vkSetDeviceMemoryPriorityEXT = reinterpret_cast<PFN_vkSetDeviceMemoryPriorityEXT>(s_vkGetDeviceProcAddr(device, "vkSetDeviceMemoryPriorityEXT"));
#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_present_wait)
    s_vkWaitForPresentKHR = reinterpret_cast<PFN_vkWaitForPresentKHR>(s_vkGetDeviceProcAddr(device, "vkWaitForPresentKHR"));
#endif // VK_KHR_present_wait

#if defined(VK_VERSION_1_3)
    s_vkCmdBeginRendering = reinterpret_cast<PFN_vkCmdBeginRendering>(s_vkGetDeviceProcAddr(device, "vkCmdBeginRendering"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
    s_vkCmdBeginRenderingKHR = reinterpret_cast<PFN_vkCmdBeginRenderingKHR>(s_vkGetDeviceProcAddr(device, "vkCmdBeginRenderingKHR"));
#endif // VK_KHR_dynamic_rendering

#if defined(VK_VERSION_1_3)
    s_vkCmdEndRendering = reinterpret_cast<PFN_vkCmdEndRendering>(s_vkGetDeviceProcAddr(device, "vkCmdEndRendering"));
#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
    s_vkCmdEndRenderingKHR = reinterpret_cast<PFN_vkCmdEndRenderingKHR>(s_vkGetDeviceProcAddr(device, "vkCmdEndRenderingKHR"));
#endif // VK_KHR_dynamic_rendering

#if defined(VK_EXT_opacity_micromap)
    s_vkCreateMicromapEXT = reinterpret_cast<PFN_vkCreateMicromapEXT>(s_vkGetDeviceProcAddr(device, "vkCreateMicromapEXT"));
    s_vkCmdBuildMicromapsEXT = reinterpret_cast<PFN_vkCmdBuildMicromapsEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBuildMicromapsEXT"));
    s_vkBuildMicromapsEXT = reinterpret_cast<PFN_vkBuildMicromapsEXT>(s_vkGetDeviceProcAddr(device, "vkBuildMicromapsEXT"));
    s_vkDestroyMicromapEXT = reinterpret_cast<PFN_vkDestroyMicromapEXT>(s_vkGetDeviceProcAddr(device, "vkDestroyMicromapEXT"));
    s_vkCmdCopyMicromapEXT = reinterpret_cast<PFN_vkCmdCopyMicromapEXT>(s_vkGetDeviceProcAddr(device, "vkCmdCopyMicromapEXT"));
    s_vkCopyMicromapEXT = reinterpret_cast<PFN_vkCopyMicromapEXT>(s_vkGetDeviceProcAddr(device, "vkCopyMicromapEXT"));
    s_vkCmdCopyMicromapToMemoryEXT = reinterpret_cast<PFN_vkCmdCopyMicromapToMemoryEXT>(s_vkGetDeviceProcAddr(device, "vkCmdCopyMicromapToMemoryEXT"));
    s_vkCopyMicromapToMemoryEXT = reinterpret_cast<PFN_vkCopyMicromapToMemoryEXT>(s_vkGetDeviceProcAddr(device, "vkCopyMicromapToMemoryEXT"));
    s_vkCmdCopyMemoryToMicromapEXT = reinterpret_cast<PFN_vkCmdCopyMemoryToMicromapEXT>(s_vkGetDeviceProcAddr(device, "vkCmdCopyMemoryToMicromapEXT"));
    s_vkCopyMemoryToMicromapEXT = reinterpret_cast<PFN_vkCopyMemoryToMicromapEXT>(s_vkGetDeviceProcAddr(device, "vkCopyMemoryToMicromapEXT"));
    s_vkCmdWriteMicromapsPropertiesEXT = reinterpret_cast<PFN_vkCmdWriteMicromapsPropertiesEXT>(s_vkGetDeviceProcAddr(device, "vkCmdWriteMicromapsPropertiesEXT"));
    s_vkWriteMicromapsPropertiesEXT = reinterpret_cast<PFN_vkWriteMicromapsPropertiesEXT>(s_vkGetDeviceProcAddr(device, "vkWriteMicromapsPropertiesEXT"));
    s_vkGetDeviceMicromapCompatibilityEXT = reinterpret_cast<PFN_vkGetDeviceMicromapCompatibilityEXT>(s_vkGetDeviceProcAddr(device, "vkGetDeviceMicromapCompatibilityEXT"));
    s_vkGetMicromapBuildSizesEXT = reinterpret_cast<PFN_vkGetMicromapBuildSizesEXT>(s_vkGetDeviceProcAddr(device, "vkGetMicromapBuildSizesEXT"));
#endif // VK_EXT_opacity_micromap

#if defined(VK_EXT_shader_module_identifier)
    s_vkGetShaderModuleIdentifierEXT = reinterpret_cast<PFN_vkGetShaderModuleIdentifierEXT>(s_vkGetDeviceProcAddr(device, "vkGetShaderModuleIdentifierEXT"));
    s_vkGetShaderModuleCreateInfoIdentifierEXT = reinterpret_cast<PFN_vkGetShaderModuleCreateInfoIdentifierEXT>(s_vkGetDeviceProcAddr(device, "vkGetShaderModuleCreateInfoIdentifierEXT"));
#endif // VK_EXT_shader_module_identifier

#if defined(VK_EXT_image_compression_control)
    s_vkGetImageSubresourceLayout2EXT = reinterpret_cast<PFN_vkGetImageSubresourceLayout2EXT>(s_vkGetDeviceProcAddr(device, "vkGetImageSubresourceLayout2EXT"));
#endif // VK_EXT_image_compression_control

#if defined(VK_EXT_device_fault)
    s_vkGetDeviceFaultInfoEXT = reinterpret_cast<PFN_vkGetDeviceFaultInfoEXT>(s_vkGetDeviceProcAddr(device, "vkGetDeviceFaultInfoEXT"));
#endif // VK_EXT_device_fault

#if defined(VK_EXT_swapchain_maintenance1)
    s_vkReleaseSwapchainImagesEXT = reinterpret_cast<PFN_vkReleaseSwapchainImagesEXT>(s_vkGetDeviceProcAddr(device, "vkReleaseSwapchainImagesEXT"));
#endif // VK_EXT_swapchain_maintenance1

#if defined(VK_KHR_map_memory2)
    s_vkMapMemory2KHR = reinterpret_cast<PFN_vkMapMemory2KHR>(s_vkGetDeviceProcAddr(device, "vkMapMemory2KHR"));
    s_vkUnmapMemory2KHR = reinterpret_cast<PFN_vkUnmapMemory2KHR>(s_vkGetDeviceProcAddr(device, "vkUnmapMemory2KHR"));
#endif // VK_KHR_map_memory2

#if defined(VK_EXT_shader_object)
    s_vkCreateShadersEXT = reinterpret_cast<PFN_vkCreateShadersEXT>(s_vkGetDeviceProcAddr(device, "vkCreateShadersEXT"));
    s_vkDestroyShaderEXT = reinterpret_cast<PFN_vkDestroyShaderEXT>(s_vkGetDeviceProcAddr(device, "vkDestroyShaderEXT"));
    s_vkGetShaderBinaryDataEXT = reinterpret_cast<PFN_vkGetShaderBinaryDataEXT>(s_vkGetDeviceProcAddr(device, "vkGetShaderBinaryDataEXT"));
    s_vkCmdBindShadersEXT = reinterpret_cast<PFN_vkCmdBindShadersEXT>(s_vkGetDeviceProcAddr(device, "vkCmdBindShadersEXT"));
#endif // VK_EXT_shader_object

#if defined(VK_NV_external_memory_sci_buf)
    s_vkGetMemorySciBufNV = reinterpret_cast<PFN_vkGetMemorySciBufNV>(s_vkGetDeviceProcAddr(device, "vkGetMemorySciBufNV"));
#endif // VK_NV_external_memory_sci_buf
}

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    VKCREATEINSTANCE_PRE(pCreateInfo, pAllocator, pInstance);
    VKCREATEINSTANCE(pCreateInfo, pAllocator, pInstance);
    VKCREATEINSTANCE_POST(pCreateInfo, pAllocator, pInstance);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYINSTANCE_PRE(instance, pAllocator);
    VKDESTROYINSTANCE(instance, pAllocator);
    VKDESTROYINSTANCE_POST(instance, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
{
    VKENUMERATEPHYSICALDEVICES_PRE(instance, pPhysicalDeviceCount, pPhysicalDevices);
    VKENUMERATEPHYSICALDEVICES(instance, pPhysicalDeviceCount, pPhysicalDevices);
    VKENUMERATEPHYSICALDEVICES_POST(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
    VKGETDEVICEPROCADDR_PRE(device, pName);
    VKGETDEVICEPROCADDR(device, pName);
    VKGETDEVICEPROCADDR_POST(device, pName);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
    VKGETINSTANCEPROCADDR_PRE(instance, pName);
    VKGETINSTANCEPROCADDR(instance, pName);
    VKGETINSTANCEPROCADDR_POST(instance, pName);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties)
{
    VKGETPHYSICALDEVICEPROPERTIES_PRE(physicalDevice, pProperties);
    VKGETPHYSICALDEVICEPROPERTIES(physicalDevice, pProperties);
    VKGETPHYSICALDEVICEPROPERTIES_POST(physicalDevice, pProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties)
{
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES_PRE(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES_POST(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties)
{
    VKGETPHYSICALDEVICEMEMORYPROPERTIES_PRE(physicalDevice, pMemoryProperties);
    VKGETPHYSICALDEVICEMEMORYPROPERTIES(physicalDevice, pMemoryProperties);
    VKGETPHYSICALDEVICEMEMORYPROPERTIES_POST(physicalDevice, pMemoryProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures)
{
    VKGETPHYSICALDEVICEFEATURES_PRE(physicalDevice, pFeatures);
    VKGETPHYSICALDEVICEFEATURES(physicalDevice, pFeatures);
    VKGETPHYSICALDEVICEFEATURES_POST(physicalDevice, pFeatures);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties)
{
    VKGETPHYSICALDEVICEFORMATPROPERTIES_PRE(physicalDevice, format, pFormatProperties);
    VKGETPHYSICALDEVICEFORMATPROPERTIES(physicalDevice, format, pFormatProperties);
    VKGETPHYSICALDEVICEFORMATPROPERTIES_POST(physicalDevice, format, pFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties)
{
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES_PRE(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES_POST(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
    VKCREATEDEVICE_PRE(physicalDevice, pCreateInfo, pAllocator, pDevice);
    VKCREATEDEVICE(physicalDevice, pCreateInfo, pAllocator, pDevice);
    VKCREATEDEVICE_POST(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDEVICE_PRE(device, pAllocator);
    VKDESTROYDEVICE(device, pAllocator);
    VKDESTROYDEVICE_POST(device, pAllocator);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_1)
VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceVersion(uint32_t* pApiVersion)
{
    VKENUMERATEINSTANCEVERSION_PRE(pApiVersion);
    VKENUMERATEINSTANCEVERSION(pApiVersion);
    VKENUMERATEINSTANCEVERSION_POST(pApiVersion);
}

#endif // VK_VERSION_1_1

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    VKENUMERATEINSTANCELAYERPROPERTIES_PRE(pPropertyCount, pProperties);
    VKENUMERATEINSTANCELAYERPROPERTIES(pPropertyCount, pProperties);
    VKENUMERATEINSTANCELAYERPROPERTIES_POST(pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    VKENUMERATEINSTANCEEXTENSIONPROPERTIES_PRE(pLayerName, pPropertyCount, pProperties);
    VKENUMERATEINSTANCEEXTENSIONPROPERTIES(pLayerName, pPropertyCount, pProperties);
    VKENUMERATEINSTANCEEXTENSIONPROPERTIES_POST(pLayerName, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    VKENUMERATEDEVICELAYERPROPERTIES_PRE(physicalDevice, pPropertyCount, pProperties);
    VKENUMERATEDEVICELAYERPROPERTIES(physicalDevice, pPropertyCount, pProperties);
    VKENUMERATEDEVICELAYERPROPERTIES_POST(physicalDevice, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    VKENUMERATEDEVICEEXTENSIONPROPERTIES_PRE(physicalDevice, pLayerName, pPropertyCount, pProperties);
    VKENUMERATEDEVICEEXTENSIONPROPERTIES(physicalDevice, pLayerName, pPropertyCount, pProperties);
    VKENUMERATEDEVICEEXTENSIONPROPERTIES_POST(physicalDevice, pLayerName, pPropertyCount, pProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)
{
    VKGETDEVICEQUEUE_PRE(device, queueFamilyIndex, queueIndex, pQueue);
    VKGETDEVICEQUEUE(device, queueFamilyIndex, queueIndex, pQueue);
    VKGETDEVICEQUEUE_POST(device, queueFamilyIndex, queueIndex, pQueue);
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
    VKQUEUESUBMIT_PRE(queue, submitCount, pSubmits, fence);
    VKQUEUESUBMIT(queue, submitCount, pSubmits, fence);
    VKQUEUESUBMIT_POST(queue, submitCount, pSubmits, fence);
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueueWaitIdle(VkQueue queue)
{
    VKQUEUEWAITIDLE_PRE(queue);
    VKQUEUEWAITIDLE(queue);
    VKQUEUEWAITIDLE_POST(queue);
}

VKAPI_ATTR VkResult VKAPI_CALL vkDeviceWaitIdle(VkDevice device)
{
    VKDEVICEWAITIDLE_PRE(device);
    VKDEVICEWAITIDLE(device);
    VKDEVICEWAITIDLE_POST(device);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory)
{
    VKALLOCATEMEMORY_PRE(device, pAllocateInfo, pAllocator, pMemory);
    VKALLOCATEMEMORY(device, pAllocateInfo, pAllocator, pMemory);
    VKALLOCATEMEMORY_POST(device, pAllocateInfo, pAllocator, pMemory);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
    VKFREEMEMORY_PRE(device, memory, pAllocator);
    VKFREEMEMORY(device, memory, pAllocator);
    VKFREEMEMORY_POST(device, memory, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)
{
    VKMAPMEMORY_PRE(device, memory, offset, size, flags, ppData);
    VKMAPMEMORY(device, memory, offset, size, flags, ppData);
    VKMAPMEMORY_POST(device, memory, offset, size, flags, ppData);
}

VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(VkDevice device, VkDeviceMemory memory)
{
    VKUNMAPMEMORY_PRE(device, memory);
    VKUNMAPMEMORY(device, memory);
    VKUNMAPMEMORY_POST(device, memory);
}

VKAPI_ATTR VkResult VKAPI_CALL vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
    VKFLUSHMAPPEDMEMORYRANGES_PRE(device, memoryRangeCount, pMemoryRanges);
    VKFLUSHMAPPEDMEMORYRANGES(device, memoryRangeCount, pMemoryRanges);
    VKFLUSHMAPPEDMEMORYRANGES_POST(device, memoryRangeCount, pMemoryRanges);
}

VKAPI_ATTR VkResult VKAPI_CALL vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
    VKINVALIDATEMAPPEDMEMORYRANGES_PRE(device, memoryRangeCount, pMemoryRanges);
    VKINVALIDATEMAPPEDMEMORYRANGES(device, memoryRangeCount, pMemoryRanges);
    VKINVALIDATEMAPPEDMEMORYRANGES_POST(device, memoryRangeCount, pMemoryRanges);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes)
{
    VKGETDEVICEMEMORYCOMMITMENT_PRE(device, memory, pCommittedMemoryInBytes);
    VKGETDEVICEMEMORYCOMMITMENT(device, memory, pCommittedMemoryInBytes);
    VKGETDEVICEMEMORYCOMMITMENT_POST(device, memory, pCommittedMemoryInBytes);
}

VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements)
{
    VKGETBUFFERMEMORYREQUIREMENTS_PRE(device, buffer, pMemoryRequirements);
    VKGETBUFFERMEMORYREQUIREMENTS(device, buffer, pMemoryRequirements);
    VKGETBUFFERMEMORYREQUIREMENTS_POST(device, buffer, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    VKBINDBUFFERMEMORY_PRE(device, buffer, memory, memoryOffset);
    VKBINDBUFFERMEMORY(device, buffer, memory, memoryOffset);
    VKBINDBUFFERMEMORY_POST(device, buffer, memory, memoryOffset);
}

VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements)
{
    VKGETIMAGEMEMORYREQUIREMENTS_PRE(device, image, pMemoryRequirements);
    VKGETIMAGEMEMORYREQUIREMENTS(device, image, pMemoryRequirements);
    VKGETIMAGEMEMORYREQUIREMENTS_POST(device, image, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    VKBINDIMAGEMEMORY_PRE(device, image, memory, memoryOffset);
    VKBINDIMAGEMEMORY(device, image, memory, memoryOffset);
    VKBINDIMAGEMEMORY_POST(device, image, memory, memoryOffset);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements)
{
    VKGETIMAGESPARSEMEMORYREQUIREMENTS_PRE(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETIMAGESPARSEMEMORYREQUIREMENTS(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETIMAGESPARSEMEMORYREQUIREMENTS_POST(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties)
{
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES_PRE(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES_POST(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence)
{
    VKQUEUEBINDSPARSE_PRE(queue, bindInfoCount, pBindInfo, fence);
    VKQUEUEBINDSPARSE(queue, bindInfoCount, pBindInfo, fence);
    VKQUEUEBINDSPARSE_POST(queue, bindInfoCount, pBindInfo, fence);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence)
{
    VKCREATEFENCE_PRE(device, pCreateInfo, pAllocator, pFence);
    VKCREATEFENCE(device, pCreateInfo, pAllocator, pFence);
    VKCREATEFENCE_POST(device, pCreateInfo, pAllocator, pFence);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYFENCE_PRE(device, fence, pAllocator);
    VKDESTROYFENCE(device, fence, pAllocator);
    VKDESTROYFENCE_POST(device, fence, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences)
{
    VKRESETFENCES_PRE(device, fenceCount, pFences);
    VKRESETFENCES(device, fenceCount, pFences);
    VKRESETFENCES_POST(device, fenceCount, pFences);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceStatus(VkDevice device, VkFence fence)
{
    VKGETFENCESTATUS_PRE(device, fence);
    VKGETFENCESTATUS(device, fence);
    VKGETFENCESTATUS_POST(device, fence);
}

VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout)
{
    VKWAITFORFENCES_PRE(device, fenceCount, pFences, waitAll, timeout);
    VKWAITFORFENCES(device, fenceCount, pFences, waitAll, timeout);
    VKWAITFORFENCES_POST(device, fenceCount, pFences, waitAll, timeout);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    VKCREATESEMAPHORE_PRE(device, pCreateInfo, pAllocator, pSemaphore);
    VKCREATESEMAPHORE(device, pCreateInfo, pAllocator, pSemaphore);
    VKCREATESEMAPHORE_POST(device, pCreateInfo, pAllocator, pSemaphore);
}

VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSEMAPHORE_PRE(device, semaphore, pAllocator);
    VKDESTROYSEMAPHORE(device, semaphore, pAllocator);
    VKDESTROYSEMAPHORE_POST(device, semaphore, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent)
{
    VKCREATEEVENT_PRE(device, pCreateInfo, pAllocator, pEvent);
    VKCREATEEVENT(device, pCreateInfo, pAllocator, pEvent);
    VKCREATEEVENT_POST(device, pCreateInfo, pAllocator, pEvent);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYEVENT_PRE(device, event, pAllocator);
    VKDESTROYEVENT(device, event, pAllocator);
    VKDESTROYEVENT_POST(device, event, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetEventStatus(VkDevice device, VkEvent event)
{
    VKGETEVENTSTATUS_PRE(device, event);
    VKGETEVENTSTATUS(device, event);
    VKGETEVENTSTATUS_POST(device, event);
}

VKAPI_ATTR VkResult VKAPI_CALL vkSetEvent(VkDevice device, VkEvent event)
{
    VKSETEVENT_PRE(device, event);
    VKSETEVENT(device, event);
    VKSETEVENT_POST(device, event);
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetEvent(VkDevice device, VkEvent event)
{
    VKRESETEVENT_PRE(device, event);
    VKRESETEVENT(device, event);
    VKRESETEVENT_POST(device, event);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool)
{
    VKCREATEQUERYPOOL_PRE(device, pCreateInfo, pAllocator, pQueryPool);
    VKCREATEQUERYPOOL(device, pCreateInfo, pAllocator, pQueryPool);
    VKCREATEQUERYPOOL_POST(device, pCreateInfo, pAllocator, pQueryPool);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYQUERYPOOL_PRE(device, queryPool, pAllocator);
    VKDESTROYQUERYPOOL(device, queryPool, pAllocator);
    VKDESTROYQUERYPOOL_POST(device, queryPool, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags)
{
    VKGETQUERYPOOLRESULTS_PRE(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    VKGETQUERYPOOLRESULTS(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    VKGETQUERYPOOLRESULTS_POST(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_2)
VKAPI_ATTR void VKAPI_CALL vkResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    VKRESETQUERYPOOL_PRE(device, queryPool, firstQuery, queryCount);
    VKRESETQUERYPOOL(device, queryPool, firstQuery, queryCount);
    VKRESETQUERYPOOL_POST(device, queryPool, firstQuery, queryCount);
}

#endif // VK_VERSION_1_2

#if defined(VK_EXT_host_query_reset)
VKAPI_ATTR void VKAPI_CALL vkResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    VKRESETQUERYPOOLEXT_PRE(device, queryPool, firstQuery, queryCount);
    VKRESETQUERYPOOLEXT(device, queryPool, firstQuery, queryCount);
    VKRESETQUERYPOOLEXT_POST(device, queryPool, firstQuery, queryCount);
}

#endif // VK_EXT_host_query_reset

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer)
{
    VKCREATEBUFFER_PRE(device, pCreateInfo, pAllocator, pBuffer);
    VKCREATEBUFFER(device, pCreateInfo, pAllocator, pBuffer);
    VKCREATEBUFFER_POST(device, pCreateInfo, pAllocator, pBuffer);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYBUFFER_PRE(device, buffer, pAllocator);
    VKDESTROYBUFFER(device, buffer, pAllocator);
    VKDESTROYBUFFER_POST(device, buffer, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView)
{
    VKCREATEBUFFERVIEW_PRE(device, pCreateInfo, pAllocator, pView);
    VKCREATEBUFFERVIEW(device, pCreateInfo, pAllocator, pView);
    VKCREATEBUFFERVIEW_POST(device, pCreateInfo, pAllocator, pView);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYBUFFERVIEW_PRE(device, bufferView, pAllocator);
    VKDESTROYBUFFERVIEW(device, bufferView, pAllocator);
    VKDESTROYBUFFERVIEW_POST(device, bufferView, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage)
{
    VKCREATEIMAGE_PRE(device, pCreateInfo, pAllocator, pImage);
    VKCREATEIMAGE(device, pCreateInfo, pAllocator, pImage);
    VKCREATEIMAGE_POST(device, pCreateInfo, pAllocator, pImage);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYIMAGE_PRE(device, image, pAllocator);
    VKDESTROYIMAGE(device, image, pAllocator);
    VKDESTROYIMAGE_POST(device, image, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout)
{
    VKGETIMAGESUBRESOURCELAYOUT_PRE(device, image, pSubresource, pLayout);
    VKGETIMAGESUBRESOURCELAYOUT(device, image, pSubresource, pLayout);
    VKGETIMAGESUBRESOURCELAYOUT_POST(device, image, pSubresource, pLayout);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView)
{
    VKCREATEIMAGEVIEW_PRE(device, pCreateInfo, pAllocator, pView);
    VKCREATEIMAGEVIEW(device, pCreateInfo, pAllocator, pView);
    VKCREATEIMAGEVIEW_POST(device, pCreateInfo, pAllocator, pView);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYIMAGEVIEW_PRE(device, imageView, pAllocator);
    VKDESTROYIMAGEVIEW(device, imageView, pAllocator);
    VKDESTROYIMAGEVIEW_POST(device, imageView, pAllocator);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule)
{
    VKCREATESHADERMODULE_PRE(device, pCreateInfo, pAllocator, pShaderModule);
    VKCREATESHADERMODULE(device, pCreateInfo, pAllocator, pShaderModule);
    VKCREATESHADERMODULE_POST(device, pCreateInfo, pAllocator, pShaderModule);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSHADERMODULE_PRE(device, shaderModule, pAllocator);
    VKDESTROYSHADERMODULE(device, shaderModule, pAllocator);
    VKDESTROYSHADERMODULE_POST(device, shaderModule, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache)
{
    VKCREATEPIPELINECACHE_PRE(device, pCreateInfo, pAllocator, pPipelineCache);
    VKCREATEPIPELINECACHE(device, pCreateInfo, pAllocator, pPipelineCache);
    VKCREATEPIPELINECACHE_POST(device, pCreateInfo, pAllocator, pPipelineCache);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYPIPELINECACHE_PRE(device, pipelineCache, pAllocator);
    VKDESTROYPIPELINECACHE(device, pipelineCache, pAllocator);
    VKDESTROYPIPELINECACHE_POST(device, pipelineCache, pAllocator);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData)
{
    VKGETPIPELINECACHEDATA_PRE(device, pipelineCache, pDataSize, pData);
    VKGETPIPELINECACHEDATA(device, pipelineCache, pDataSize, pData);
    VKGETPIPELINECACHEDATA_POST(device, pipelineCache, pDataSize, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches)
{
    VKMERGEPIPELINECACHES_PRE(device, dstCache, srcCacheCount, pSrcCaches);
    VKMERGEPIPELINECACHES(device, dstCache, srcCacheCount, pSrcCaches);
    VKMERGEPIPELINECACHES_POST(device, dstCache, srcCacheCount, pSrcCaches);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    VKCREATEGRAPHICSPIPELINES_PRE(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATEGRAPHICSPIPELINES(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATEGRAPHICSPIPELINES_POST(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    VKCREATECOMPUTEPIPELINES_PRE(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATECOMPUTEPIPELINES(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATECOMPUTEPIPELINES_POST(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYPIPELINE_PRE(device, pipeline, pAllocator);
    VKDESTROYPIPELINE(device, pipeline, pAllocator);
    VKDESTROYPIPELINE_POST(device, pipeline, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    VKCREATEPIPELINELAYOUT_PRE(device, pCreateInfo, pAllocator, pPipelineLayout);
    VKCREATEPIPELINELAYOUT(device, pCreateInfo, pAllocator, pPipelineLayout);
    VKCREATEPIPELINELAYOUT_POST(device, pCreateInfo, pAllocator, pPipelineLayout);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYPIPELINELAYOUT_PRE(device, pipelineLayout, pAllocator);
    VKDESTROYPIPELINELAYOUT(device, pipelineLayout, pAllocator);
    VKDESTROYPIPELINELAYOUT_POST(device, pipelineLayout, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler)
{
    VKCREATESAMPLER_PRE(device, pCreateInfo, pAllocator, pSampler);
    VKCREATESAMPLER(device, pCreateInfo, pAllocator, pSampler);
    VKCREATESAMPLER_POST(device, pCreateInfo, pAllocator, pSampler);
}

VKAPI_ATTR void VKAPI_CALL vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSAMPLER_PRE(device, sampler, pAllocator);
    VKDESTROYSAMPLER(device, sampler, pAllocator);
    VKDESTROYSAMPLER_POST(device, sampler, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout)
{
    VKCREATEDESCRIPTORSETLAYOUT_PRE(device, pCreateInfo, pAllocator, pSetLayout);
    VKCREATEDESCRIPTORSETLAYOUT(device, pCreateInfo, pAllocator, pSetLayout);
    VKCREATEDESCRIPTORSETLAYOUT_POST(device, pCreateInfo, pAllocator, pSetLayout);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDESCRIPTORSETLAYOUT_PRE(device, descriptorSetLayout, pAllocator);
    VKDESTROYDESCRIPTORSETLAYOUT(device, descriptorSetLayout, pAllocator);
    VKDESTROYDESCRIPTORSETLAYOUT_POST(device, descriptorSetLayout, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool)
{
    VKCREATEDESCRIPTORPOOL_PRE(device, pCreateInfo, pAllocator, pDescriptorPool);
    VKCREATEDESCRIPTORPOOL(device, pCreateInfo, pAllocator, pDescriptorPool);
    VKCREATEDESCRIPTORPOOL_POST(device, pCreateInfo, pAllocator, pDescriptorPool);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDESCRIPTORPOOL_PRE(device, descriptorPool, pAllocator);
    VKDESTROYDESCRIPTORPOOL(device, descriptorPool, pAllocator);
    VKDESTROYDESCRIPTORPOOL_POST(device, descriptorPool, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags)
{
    VKRESETDESCRIPTORPOOL_PRE(device, descriptorPool, flags);
    VKRESETDESCRIPTORPOOL(device, descriptorPool, flags);
    VKRESETDESCRIPTORPOOL_POST(device, descriptorPool, flags);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets)
{
    VKALLOCATEDESCRIPTORSETS_PRE(device, pAllocateInfo, pDescriptorSets);
    VKALLOCATEDESCRIPTORSETS(device, pAllocateInfo, pDescriptorSets);
    VKALLOCATEDESCRIPTORSETS_POST(device, pAllocateInfo, pDescriptorSets);
}

VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
    VKFREEDESCRIPTORSETS_PRE(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    VKFREEDESCRIPTORSETS(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    VKFREEDESCRIPTORSETS_POST(device, descriptorPool, descriptorSetCount, pDescriptorSets);
}

VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies)
{
    VKUPDATEDESCRIPTORSETS_PRE(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    VKUPDATEDESCRIPTORSETS(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    VKUPDATEDESCRIPTORSETS_POST(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer)
{
    VKCREATEFRAMEBUFFER_PRE(device, pCreateInfo, pAllocator, pFramebuffer);
    VKCREATEFRAMEBUFFER(device, pCreateInfo, pAllocator, pFramebuffer);
    VKCREATEFRAMEBUFFER_POST(device, pCreateInfo, pAllocator, pFramebuffer);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYFRAMEBUFFER_PRE(device, framebuffer, pAllocator);
    VKDESTROYFRAMEBUFFER(device, framebuffer, pAllocator);
    VKDESTROYFRAMEBUFFER_POST(device, framebuffer, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
    VKCREATERENDERPASS_PRE(device, pCreateInfo, pAllocator, pRenderPass);
    VKCREATERENDERPASS(device, pCreateInfo, pAllocator, pRenderPass);
    VKCREATERENDERPASS_POST(device, pCreateInfo, pAllocator, pRenderPass);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYRENDERPASS_PRE(device, renderPass, pAllocator);
    VKDESTROYRENDERPASS(device, renderPass, pAllocator);
    VKDESTROYRENDERPASS_POST(device, renderPass, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity)
{
    VKGETRENDERAREAGRANULARITY_PRE(device, renderPass, pGranularity);
    VKGETRENDERAREAGRANULARITY(device, renderPass, pGranularity);
    VKGETRENDERAREAGRANULARITY_POST(device, renderPass, pGranularity);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool)
{
    VKCREATECOMMANDPOOL_PRE(device, pCreateInfo, pAllocator, pCommandPool);
    VKCREATECOMMANDPOOL(device, pCreateInfo, pAllocator, pCommandPool);
    VKCREATECOMMANDPOOL_POST(device, pCreateInfo, pAllocator, pCommandPool);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYCOMMANDPOOL_PRE(device, commandPool, pAllocator);
    VKDESTROYCOMMANDPOOL(device, commandPool, pAllocator);
    VKDESTROYCOMMANDPOOL_POST(device, commandPool, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags)
{
    VKRESETCOMMANDPOOL_PRE(device, commandPool, flags);
    VKRESETCOMMANDPOOL(device, commandPool, flags);
    VKRESETCOMMANDPOOL_POST(device, commandPool, flags);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
    VKALLOCATECOMMANDBUFFERS_PRE(device, pAllocateInfo, pCommandBuffers);
    VKALLOCATECOMMANDBUFFERS(device, pAllocateInfo, pCommandBuffers);
    VKALLOCATECOMMANDBUFFERS_POST(device, pAllocateInfo, pCommandBuffers);
}

VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
    VKFREECOMMANDBUFFERS_PRE(device, commandPool, commandBufferCount, pCommandBuffers);
    VKFREECOMMANDBUFFERS(device, commandPool, commandBufferCount, pCommandBuffers);
    VKFREECOMMANDBUFFERS_POST(device, commandPool, commandBufferCount, pCommandBuffers);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo)
{
    VKBEGINCOMMANDBUFFER_PRE(commandBuffer, pBeginInfo);
    VKBEGINCOMMANDBUFFER(commandBuffer, pBeginInfo);
    VKBEGINCOMMANDBUFFER_POST(commandBuffer, pBeginInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEndCommandBuffer(VkCommandBuffer commandBuffer)
{
    VKENDCOMMANDBUFFER_PRE(commandBuffer);
    VKENDCOMMANDBUFFER(commandBuffer);
    VKENDCOMMANDBUFFER_POST(commandBuffer);
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags)
{
    VKRESETCOMMANDBUFFER_PRE(commandBuffer, flags);
    VKRESETCOMMANDBUFFER(commandBuffer, flags);
    VKRESETCOMMANDBUFFER_POST(commandBuffer, flags);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
    VKCMDBINDPIPELINE_PRE(commandBuffer, pipelineBindPoint, pipeline);
    VKCMDBINDPIPELINE(commandBuffer, pipelineBindPoint, pipeline);
    VKCMDBINDPIPELINE_POST(commandBuffer, pipelineBindPoint, pipeline);
}

#endif // VK_VERSION_1_0

#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
VKAPI_ATTR void VKAPI_CALL vkCmdSetAttachmentFeedbackLoopEnableEXT(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask)
{
    VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT_PRE(commandBuffer, aspectMask);
    VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT(commandBuffer, aspectMask);
    VKCMDSETATTACHMENTFEEDBACKLOOPENABLEEXT_POST(commandBuffer, aspectMask);
}

#endif // VK_EXT_attachment_feedback_loop_dynamic_state

#if defined(VK_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports)
{
    VKCMDSETVIEWPORT_PRE(commandBuffer, firstViewport, viewportCount, pViewports);
    VKCMDSETVIEWPORT(commandBuffer, firstViewport, viewportCount, pViewports);
    VKCMDSETVIEWPORT_POST(commandBuffer, firstViewport, viewportCount, pViewports);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors)
{
    VKCMDSETSCISSOR_PRE(commandBuffer, firstScissor, scissorCount, pScissors);
    VKCMDSETSCISSOR(commandBuffer, firstScissor, scissorCount, pScissors);
    VKCMDSETSCISSOR_POST(commandBuffer, firstScissor, scissorCount, pScissors);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth)
{
    VKCMDSETLINEWIDTH_PRE(commandBuffer, lineWidth);
    VKCMDSETLINEWIDTH(commandBuffer, lineWidth);
    VKCMDSETLINEWIDTH_POST(commandBuffer, lineWidth);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor)
{
    VKCMDSETDEPTHBIAS_PRE(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    VKCMDSETDEPTHBIAS(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    VKCMDSETDEPTHBIAS_POST(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4])
{
    VKCMDSETBLENDCONSTANTS_PRE(commandBuffer, blendConstants);
    VKCMDSETBLENDCONSTANTS(commandBuffer, blendConstants);
    VKCMDSETBLENDCONSTANTS_POST(commandBuffer, blendConstants);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds)
{
    VKCMDSETDEPTHBOUNDS_PRE(commandBuffer, minDepthBounds, maxDepthBounds);
    VKCMDSETDEPTHBOUNDS(commandBuffer, minDepthBounds, maxDepthBounds);
    VKCMDSETDEPTHBOUNDS_POST(commandBuffer, minDepthBounds, maxDepthBounds);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask)
{
    VKCMDSETSTENCILCOMPAREMASK_PRE(commandBuffer, faceMask, compareMask);
    VKCMDSETSTENCILCOMPAREMASK(commandBuffer, faceMask, compareMask);
    VKCMDSETSTENCILCOMPAREMASK_POST(commandBuffer, faceMask, compareMask);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask)
{
    VKCMDSETSTENCILWRITEMASK_PRE(commandBuffer, faceMask, writeMask);
    VKCMDSETSTENCILWRITEMASK(commandBuffer, faceMask, writeMask);
    VKCMDSETSTENCILWRITEMASK_POST(commandBuffer, faceMask, writeMask);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference)
{
    VKCMDSETSTENCILREFERENCE_PRE(commandBuffer, faceMask, reference);
    VKCMDSETSTENCILREFERENCE(commandBuffer, faceMask, reference);
    VKCMDSETSTENCILREFERENCE_POST(commandBuffer, faceMask, reference);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets)
{
    VKCMDBINDDESCRIPTORSETS_PRE(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    VKCMDBINDDESCRIPTORSETS(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    VKCMDBINDDESCRIPTORSETS_POST(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType)
{
    VKCMDBINDINDEXBUFFER_PRE(commandBuffer, buffer, offset, indexType);
    VKCMDBINDINDEXBUFFER(commandBuffer, buffer, offset, indexType);
    VKCMDBINDINDEXBUFFER_POST(commandBuffer, buffer, offset, indexType);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets)
{
    VKCMDBINDVERTEXBUFFERS_PRE(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    VKCMDBINDVERTEXBUFFERS(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    VKCMDBINDVERTEXBUFFERS_POST(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
    VKCMDDRAW_PRE(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    VKCMDDRAW(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    VKCMDDRAW_POST(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
{
    VKCMDDRAWINDEXED_PRE(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    VKCMDDRAWINDEXED(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    VKCMDDRAWINDEXED_POST(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

#endif // VK_VERSION_1_0

#if defined(VK_EXT_multi_draw)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride)
{
    VKCMDDRAWMULTIEXT_PRE(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
    VKCMDDRAWMULTIEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
    VKCMDDRAWMULTIEXT_POST(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset)
{
    VKCMDDRAWMULTIINDEXEDEXT_PRE(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
    VKCMDDRAWMULTIINDEXEDEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
    VKCMDDRAWMULTIINDEXEDEXT_POST(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
}

#endif // VK_EXT_multi_draw

#if defined(VK_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    VKCMDDRAWINDIRECT_PRE(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWINDIRECT(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWINDIRECT_POST(commandBuffer, buffer, offset, drawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    VKCMDDRAWINDEXEDINDIRECT_PRE(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWINDEXEDINDIRECT(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWINDEXEDINDIRECT_POST(commandBuffer, buffer, offset, drawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    VKCMDDISPATCH_PRE(commandBuffer, groupCountX, groupCountY, groupCountZ);
    VKCMDDISPATCH(commandBuffer, groupCountX, groupCountY, groupCountZ);
    VKCMDDISPATCH_POST(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset)
{
    VKCMDDISPATCHINDIRECT_PRE(commandBuffer, buffer, offset);
    VKCMDDISPATCHINDIRECT(commandBuffer, buffer, offset);
    VKCMDDISPATCHINDIRECT_POST(commandBuffer, buffer, offset);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions)
{
    VKCMDCOPYBUFFER_PRE(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    VKCMDCOPYBUFFER(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    VKCMDCOPYBUFFER_POST(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions)
{
    VKCMDCOPYIMAGE_PRE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    VKCMDCOPYIMAGE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    VKCMDCOPYIMAGE_POST(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter)
{
    VKCMDBLITIMAGE_PRE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    VKCMDBLITIMAGE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    VKCMDBLITIMAGE_POST(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
    VKCMDCOPYBUFFERTOIMAGE_PRE(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    VKCMDCOPYBUFFERTOIMAGE(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    VKCMDCOPYBUFFERTOIMAGE_POST(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
    VKCMDCOPYIMAGETOBUFFER_PRE(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    VKCMDCOPYIMAGETOBUFFER(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    VKCMDCOPYIMAGETOBUFFER_POST(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

#endif // VK_VERSION_1_0

#if defined(VK_NV_copy_memory_indirect)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride)
{
    VKCMDCOPYMEMORYINDIRECTNV_PRE(commandBuffer, copyBufferAddress, copyCount, stride);
    VKCMDCOPYMEMORYINDIRECTNV(commandBuffer, copyBufferAddress, copyCount, stride);
    VKCMDCOPYMEMORYINDIRECTNV_POST(commandBuffer, copyBufferAddress, copyCount, stride);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources)
{
    VKCMDCOPYMEMORYTOIMAGEINDIRECTNV_PRE(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources);
    VKCMDCOPYMEMORYTOIMAGEINDIRECTNV(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources);
    VKCMDCOPYMEMORYTOIMAGEINDIRECTNV_POST(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources);
}

#endif // VK_NV_copy_memory_indirect

#if defined(VK_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData)
{
    VKCMDUPDATEBUFFER_PRE(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    VKCMDUPDATEBUFFER(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    VKCMDUPDATEBUFFER_POST(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data)
{
    VKCMDFILLBUFFER_PRE(commandBuffer, dstBuffer, dstOffset, size, data);
    VKCMDFILLBUFFER(commandBuffer, dstBuffer, dstOffset, size, data);
    VKCMDFILLBUFFER_POST(commandBuffer, dstBuffer, dstOffset, size, data);
}

VKAPI_ATTR void VKAPI_CALL vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    VKCMDCLEARCOLORIMAGE_PRE(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    VKCMDCLEARCOLORIMAGE(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    VKCMDCLEARCOLORIMAGE_POST(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}

VKAPI_ATTR void VKAPI_CALL vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    VKCMDCLEARDEPTHSTENCILIMAGE_PRE(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    VKCMDCLEARDEPTHSTENCILIMAGE(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    VKCMDCLEARDEPTHSTENCILIMAGE_POST(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}

VKAPI_ATTR void VKAPI_CALL vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects)
{
    VKCMDCLEARATTACHMENTS_PRE(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    VKCMDCLEARATTACHMENTS(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    VKCMDCLEARATTACHMENTS_POST(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}

VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions)
{
    VKCMDRESOLVEIMAGE_PRE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    VKCMDRESOLVEIMAGE(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    VKCMDRESOLVEIMAGE_POST(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
    VKCMDSETEVENT_PRE(commandBuffer, event, stageMask);
    VKCMDSETEVENT(commandBuffer, event, stageMask);
    VKCMDSETEVENT_POST(commandBuffer, event, stageMask);
}

VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
    VKCMDRESETEVENT_PRE(commandBuffer, event, stageMask);
    VKCMDRESETEVENT(commandBuffer, event, stageMask);
    VKCMDRESETEVENT_POST(commandBuffer, event, stageMask);
}

VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
    VKCMDWAITEVENTS_PRE(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    VKCMDWAITEVENTS(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    VKCMDWAITEVENTS_POST(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
    VKCMDPIPELINEBARRIER_PRE(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    VKCMDPIPELINEBARRIER(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    VKCMDPIPELINEBARRIER_POST(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags)
{
    VKCMDBEGINQUERY_PRE(commandBuffer, queryPool, query, flags);
    VKCMDBEGINQUERY(commandBuffer, queryPool, query, flags);
    VKCMDBEGINQUERY_POST(commandBuffer, queryPool, query, flags);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query)
{
    VKCMDENDQUERY_PRE(commandBuffer, queryPool, query);
    VKCMDENDQUERY(commandBuffer, queryPool, query);
    VKCMDENDQUERY_POST(commandBuffer, queryPool, query);
}

#endif // VK_VERSION_1_0

#if defined(VK_EXT_conditional_rendering)
VKAPI_ATTR void VKAPI_CALL vkCmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin)
{
    VKCMDBEGINCONDITIONALRENDERINGEXT_PRE(commandBuffer, pConditionalRenderingBegin);
    VKCMDBEGINCONDITIONALRENDERINGEXT(commandBuffer, pConditionalRenderingBegin);
    VKCMDBEGINCONDITIONALRENDERINGEXT_POST(commandBuffer, pConditionalRenderingBegin);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer)
{
    VKCMDENDCONDITIONALRENDERINGEXT_PRE(commandBuffer);
    VKCMDENDCONDITIONALRENDERINGEXT(commandBuffer);
    VKCMDENDCONDITIONALRENDERINGEXT_POST(commandBuffer);
}

#endif // VK_EXT_conditional_rendering

#if defined(VK_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    VKCMDRESETQUERYPOOL_PRE(commandBuffer, queryPool, firstQuery, queryCount);
    VKCMDRESETQUERYPOOL(commandBuffer, queryPool, firstQuery, queryCount);
    VKCMDRESETQUERYPOOL_POST(commandBuffer, queryPool, firstQuery, queryCount);
}

VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query)
{
    VKCMDWRITETIMESTAMP_PRE(commandBuffer, pipelineStage, queryPool, query);
    VKCMDWRITETIMESTAMP(commandBuffer, pipelineStage, queryPool, query);
    VKCMDWRITETIMESTAMP_POST(commandBuffer, pipelineStage, queryPool, query);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags)
{
    VKCMDCOPYQUERYPOOLRESULTS_PRE(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    VKCMDCOPYQUERYPOOLRESULTS(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    VKCMDCOPYQUERYPOOLRESULTS_POST(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}

VKAPI_ATTR void VKAPI_CALL vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues)
{
    VKCMDPUSHCONSTANTS_PRE(commandBuffer, layout, stageFlags, offset, size, pValues);
    VKCMDPUSHCONSTANTS(commandBuffer, layout, stageFlags, offset, size, pValues);
    VKCMDPUSHCONSTANTS_POST(commandBuffer, layout, stageFlags, offset, size, pValues);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents)
{
    VKCMDBEGINRENDERPASS_PRE(commandBuffer, pRenderPassBegin, contents);
    VKCMDBEGINRENDERPASS(commandBuffer, pRenderPassBegin, contents);
    VKCMDBEGINRENDERPASS_POST(commandBuffer, pRenderPassBegin, contents);
}

VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents)
{
    VKCMDNEXTSUBPASS_PRE(commandBuffer, contents);
    VKCMDNEXTSUBPASS(commandBuffer, contents);
    VKCMDNEXTSUBPASS_POST(commandBuffer, contents);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass(VkCommandBuffer commandBuffer)
{
    VKCMDENDRENDERPASS_PRE(commandBuffer);
    VKCMDENDRENDERPASS(commandBuffer);
    VKCMDENDRENDERPASS_POST(commandBuffer);
}

VKAPI_ATTR void VKAPI_CALL vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
    VKCMDEXECUTECOMMANDS_PRE(commandBuffer, commandBufferCount, pCommandBuffers);
    VKCMDEXECUTECOMMANDS(commandBuffer, commandBufferCount, pCommandBuffers);
    VKCMDEXECUTECOMMANDS_POST(commandBuffer, commandBufferCount, pCommandBuffers);
}

#endif // VK_VERSION_1_0

#if defined(VK_KHR_android_surface)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEANDROIDSURFACEKHR_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEANDROIDSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEANDROIDSURFACEKHR_POST(instance, pCreateInfo, pAllocator, pSurface);
}

#endif // VK_KHR_android_surface

#if defined(VK_KHR_display)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties)
{
    VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR_PRE(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPROPERTIESKHR_POST(physicalDevice, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties)
{
    VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR_PRE(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIESKHR_POST(physicalDevice, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays)
{
    VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR_PRE(physicalDevice, planeIndex, pDisplayCount, pDisplays);
    VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays);
    VKGETDISPLAYPLANESUPPORTEDDISPLAYSKHR_POST(physicalDevice, planeIndex, pDisplayCount, pDisplays);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties)
{
    VKGETDISPLAYMODEPROPERTIESKHR_PRE(physicalDevice, display, pPropertyCount, pProperties);
    VKGETDISPLAYMODEPROPERTIESKHR(physicalDevice, display, pPropertyCount, pProperties);
    VKGETDISPLAYMODEPROPERTIESKHR_POST(physicalDevice, display, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode)
{
    VKCREATEDISPLAYMODEKHR_PRE(physicalDevice, display, pCreateInfo, pAllocator, pMode);
    VKCREATEDISPLAYMODEKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode);
    VKCREATEDISPLAYMODEKHR_POST(physicalDevice, display, pCreateInfo, pAllocator, pMode);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities)
{
    VKGETDISPLAYPLANECAPABILITIESKHR_PRE(physicalDevice, mode, planeIndex, pCapabilities);
    VKGETDISPLAYPLANECAPABILITIESKHR(physicalDevice, mode, planeIndex, pCapabilities);
    VKGETDISPLAYPLANECAPABILITIESKHR_POST(physicalDevice, mode, planeIndex, pCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEDISPLAYPLANESURFACEKHR_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEDISPLAYPLANESURFACEKHR(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEDISPLAYPLANESURFACEKHR_POST(instance, pCreateInfo, pAllocator, pSurface);
}

#endif // VK_KHR_display

#if defined(VK_KHR_display_swapchain)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains)
{
    VKCREATESHAREDSWAPCHAINSKHR_PRE(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
    VKCREATESHAREDSWAPCHAINSKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
    VKCREATESHAREDSWAPCHAINSKHR_POST(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
}

#endif // VK_KHR_display_swapchain

#if defined(VK_KHR_surface)
VKAPI_ATTR void VKAPI_CALL vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSURFACEKHR_PRE(instance, surface, pAllocator);
    VKDESTROYSURFACEKHR(instance, surface, pAllocator);
    VKDESTROYSURFACEKHR_POST(instance, surface, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported)
{
    VKGETPHYSICALDEVICESURFACESUPPORTKHR_PRE(physicalDevice, queueFamilyIndex, surface, pSupported);
    VKGETPHYSICALDEVICESURFACESUPPORTKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
    VKGETPHYSICALDEVICESURFACESUPPORTKHR_POST(physicalDevice, queueFamilyIndex, surface, pSupported);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities)
{
    VKGETPHYSICALDEVICESURFACECAPABILITIESKHR_PRE(physicalDevice, surface, pSurfaceCapabilities);
    VKGETPHYSICALDEVICESURFACECAPABILITIESKHR(physicalDevice, surface, pSurfaceCapabilities);
    VKGETPHYSICALDEVICESURFACECAPABILITIESKHR_POST(physicalDevice, surface, pSurfaceCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats)
{
    VKGETPHYSICALDEVICESURFACEFORMATSKHR_PRE(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    VKGETPHYSICALDEVICESURFACEFORMATSKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    VKGETPHYSICALDEVICESURFACEFORMATSKHR_POST(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
    VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR_PRE(physicalDevice, surface, pPresentModeCount, pPresentModes);
    VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
    VKGETPHYSICALDEVICESURFACEPRESENTMODESKHR_POST(physicalDevice, surface, pPresentModeCount, pPresentModes);
}

#endif // VK_KHR_surface

#if defined(VK_KHR_swapchain)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
    VKCREATESWAPCHAINKHR_PRE(device, pCreateInfo, pAllocator, pSwapchain);
    VKCREATESWAPCHAINKHR(device, pCreateInfo, pAllocator, pSwapchain);
    VKCREATESWAPCHAINKHR_POST(device, pCreateInfo, pAllocator, pSwapchain);
}

#endif // VK_KHR_swapchain

#if defined(VK_KHR_swapchain) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSWAPCHAINKHR_PRE(device, swapchain, pAllocator);
    VKDESTROYSWAPCHAINKHR(device, swapchain, pAllocator);
    VKDESTROYSWAPCHAINKHR_POST(device, swapchain, pAllocator);
}

#endif // VK_KHR_swapchain && !VKSC_VERSION_1_0

#if defined(VK_KHR_swapchain)
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
    VKGETSWAPCHAINIMAGESKHR_PRE(device, swapchain, pSwapchainImageCount, pSwapchainImages);
    VKGETSWAPCHAINIMAGESKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
    VKGETSWAPCHAINIMAGESKHR_POST(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
    VKACQUIRENEXTIMAGEKHR_PRE(device, swapchain, timeout, semaphore, fence, pImageIndex);
    VKACQUIRENEXTIMAGEKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
    VKACQUIRENEXTIMAGEKHR_POST(device, swapchain, timeout, semaphore, fence, pImageIndex);
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
    VKQUEUEPRESENTKHR_PRE(queue, pPresentInfo);
    VKQUEUEPRESENTKHR(queue, pPresentInfo);
    VKQUEUEPRESENTKHR_POST(queue, pPresentInfo);
}

#endif // VK_KHR_swapchain

#if defined(VK_KHR_wayland_surface)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEWAYLANDSURFACEKHR_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEWAYLANDSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEWAYLANDSURFACEKHR_POST(instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display)
{
    VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR_PRE(physicalDevice, queueFamilyIndex, display);
    VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex, display);
    VKGETPHYSICALDEVICEWAYLANDPRESENTATIONSUPPORTKHR_POST(physicalDevice, queueFamilyIndex, display);
}

#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_win32_surface)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEWIN32SURFACEKHR_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEWIN32SURFACEKHR(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEWIN32SURFACEKHR_POST(instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex)
{
    VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR_PRE(physicalDevice, queueFamilyIndex);
    VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex);
    VKGETPHYSICALDEVICEWIN32PRESENTATIONSUPPORTKHR_POST(physicalDevice, queueFamilyIndex);
}

#endif // VK_KHR_win32_surface

#if defined(VK_KHR_xlib_surface)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEXLIBSURFACEKHR_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEXLIBSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEXLIBSURFACEKHR_POST(instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID)
{
    VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR_PRE(physicalDevice, queueFamilyIndex, dpy, visualID);
    VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex, dpy, visualID);
    VKGETPHYSICALDEVICEXLIBPRESENTATIONSUPPORTKHR_POST(physicalDevice, queueFamilyIndex, dpy, visualID);
}

#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEXCBSURFACEKHR_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEXCBSURFACEKHR(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEXCBSURFACEKHR_POST(instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id)
{
    VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR_PRE(physicalDevice, queueFamilyIndex, connection, visual_id);
    VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR(physicalDevice, queueFamilyIndex, connection, visual_id);
    VKGETPHYSICALDEVICEXCBPRESENTATIONSUPPORTKHR_POST(physicalDevice, queueFamilyIndex, connection, visual_id);
}

#endif // VK_KHR_xcb_surface

#if defined(VK_EXT_debug_report)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
{
    VKCREATEDEBUGREPORTCALLBACKEXT_PRE(instance, pCreateInfo, pAllocator, pCallback);
    VKCREATEDEBUGREPORTCALLBACKEXT(instance, pCreateInfo, pAllocator, pCallback);
    VKCREATEDEBUGREPORTCALLBACKEXT_POST(instance, pCreateInfo, pAllocator, pCallback);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDEBUGREPORTCALLBACKEXT_PRE(instance, callback, pAllocator);
    VKDESTROYDEBUGREPORTCALLBACKEXT(instance, callback, pAllocator);
    VKDESTROYDEBUGREPORTCALLBACKEXT_POST(instance, callback, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage)
{
    VKDEBUGREPORTMESSAGEEXT_PRE(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    VKDEBUGREPORTMESSAGEEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    VKDEBUGREPORTMESSAGEEXT_POST(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
}

#endif // VK_EXT_debug_report

#if defined(VK_EXT_debug_marker)
VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo)
{
    VKDEBUGMARKERSETOBJECTNAMEEXT_PRE(device, pNameInfo);
    VKDEBUGMARKERSETOBJECTNAMEEXT(device, pNameInfo);
    VKDEBUGMARKERSETOBJECTNAMEEXT_POST(device, pNameInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo)
{
    VKDEBUGMARKERSETOBJECTTAGEXT_PRE(device, pTagInfo);
    VKDEBUGMARKERSETOBJECTTAGEXT(device, pTagInfo);
    VKDEBUGMARKERSETOBJECTTAGEXT_POST(device, pTagInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo)
{
    VKCMDDEBUGMARKERBEGINEXT_PRE(commandBuffer, pMarkerInfo);
    VKCMDDEBUGMARKERBEGINEXT(commandBuffer, pMarkerInfo);
    VKCMDDEBUGMARKERBEGINEXT_POST(commandBuffer, pMarkerInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer)
{
    VKCMDDEBUGMARKERENDEXT_PRE(commandBuffer);
    VKCMDDEBUGMARKERENDEXT(commandBuffer);
    VKCMDDEBUGMARKERENDEXT_POST(commandBuffer);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo)
{
    VKCMDDEBUGMARKERINSERTEXT_PRE(commandBuffer, pMarkerInfo);
    VKCMDDEBUGMARKERINSERTEXT(commandBuffer, pMarkerInfo);
    VKCMDDEBUGMARKERINSERTEXT_POST(commandBuffer, pMarkerInfo);
}

#endif // VK_EXT_debug_marker

#if defined(VK_NV_external_memory_capabilities)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties)
{
    VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV_PRE(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
    VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
    VKGETPHYSICALDEVICEEXTERNALIMAGEFORMATPROPERTIESNV_POST(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
}

#endif // VK_NV_external_memory_capabilities

#if defined(VK_NV_external_memory_win32)
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle)
{
    VKGETMEMORYWIN32HANDLENV_PRE(device, memory, handleType, pHandle);
    VKGETMEMORYWIN32HANDLENV(device, memory, handleType, pHandle);
    VKGETMEMORYWIN32HANDLENV_POST(device, memory, handleType, pHandle);
}

#endif // VK_NV_external_memory_win32

#if defined(VK_NV_device_generated_commands)
VKAPI_ATTR void VKAPI_CALL vkCmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo)
{
    VKCMDEXECUTEGENERATEDCOMMANDSNV_PRE(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
    VKCMDEXECUTEGENERATEDCOMMANDSNV(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
    VKCMDEXECUTEGENERATEDCOMMANDSNV_POST(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo)
{
    VKCMDPREPROCESSGENERATEDCOMMANDSNV_PRE(commandBuffer, pGeneratedCommandsInfo);
    VKCMDPREPROCESSGENERATEDCOMMANDSNV(commandBuffer, pGeneratedCommandsInfo);
    VKCMDPREPROCESSGENERATEDCOMMANDSNV_POST(commandBuffer, pGeneratedCommandsInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex)
{
    VKCMDBINDPIPELINESHADERGROUPNV_PRE(commandBuffer, pipelineBindPoint, pipeline, groupIndex);
    VKCMDBINDPIPELINESHADERGROUPNV(commandBuffer, pipelineBindPoint, pipeline, groupIndex);
    VKCMDBINDPIPELINESHADERGROUPNV_POST(commandBuffer, pipelineBindPoint, pipeline, groupIndex);
}

VKAPI_ATTR void VKAPI_CALL vkGetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV_PRE(device, pInfo, pMemoryRequirements);
    VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV(device, pInfo, pMemoryRequirements);
    VKGETGENERATEDCOMMANDSMEMORYREQUIREMENTSNV_POST(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout)
{
    VKCREATEINDIRECTCOMMANDSLAYOUTNV_PRE(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
    VKCREATEINDIRECTCOMMANDSLAYOUTNV(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
    VKCREATEINDIRECTCOMMANDSLAYOUTNV_POST(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYINDIRECTCOMMANDSLAYOUTNV_PRE(device, indirectCommandsLayout, pAllocator);
    VKDESTROYINDIRECTCOMMANDSLAYOUTNV(device, indirectCommandsLayout, pAllocator);
    VKDESTROYINDIRECTCOMMANDSLAYOUTNV_POST(device, indirectCommandsLayout, pAllocator);
}

#endif // VK_NV_device_generated_commands

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures)
{
    VKGETPHYSICALDEVICEFEATURES2_PRE(physicalDevice, pFeatures);
    VKGETPHYSICALDEVICEFEATURES2(physicalDevice, pFeatures);
    VKGETPHYSICALDEVICEFEATURES2_POST(physicalDevice, pFeatures);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2KHR* pFeatures)
{
    VKGETPHYSICALDEVICEFEATURES2KHR_PRE(physicalDevice, pFeatures);
    VKGETPHYSICALDEVICEFEATURES2KHR(physicalDevice, pFeatures);
    VKGETPHYSICALDEVICEFEATURES2KHR_POST(physicalDevice, pFeatures);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties)
{
    VKGETPHYSICALDEVICEPROPERTIES2_PRE(physicalDevice, pProperties);
    VKGETPHYSICALDEVICEPROPERTIES2(physicalDevice, pProperties);
    VKGETPHYSICALDEVICEPROPERTIES2_POST(physicalDevice, pProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2KHR* pProperties)
{
    VKGETPHYSICALDEVICEPROPERTIES2KHR_PRE(physicalDevice, pProperties);
    VKGETPHYSICALDEVICEPROPERTIES2KHR(physicalDevice, pProperties);
    VKGETPHYSICALDEVICEPROPERTIES2KHR_POST(physicalDevice, pProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties)
{
    VKGETPHYSICALDEVICEFORMATPROPERTIES2_PRE(physicalDevice, format, pFormatProperties);
    VKGETPHYSICALDEVICEFORMATPROPERTIES2(physicalDevice, format, pFormatProperties);
    VKGETPHYSICALDEVICEFORMATPROPERTIES2_POST(physicalDevice, format, pFormatProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2KHR* pFormatProperties)
{
    VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR_PRE(physicalDevice, format, pFormatProperties);
    VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR(physicalDevice, format, pFormatProperties);
    VKGETPHYSICALDEVICEFORMATPROPERTIES2KHR_POST(physicalDevice, format, pFormatProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties)
{
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2_PRE(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2_POST(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2KHR* pImageFormatInfo, VkImageFormatProperties2KHR* pImageFormatProperties)
{
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR_PRE(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    VKGETPHYSICALDEVICEIMAGEFORMATPROPERTIES2KHR_POST(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties)
{
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2_PRE(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2_POST(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2KHR* pQueueFamilyProperties)
{
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR_PRE(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    VKGETPHYSICALDEVICEQUEUEFAMILYPROPERTIES2KHR_POST(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties)
{
    VKGETPHYSICALDEVICEMEMORYPROPERTIES2_PRE(physicalDevice, pMemoryProperties);
    VKGETPHYSICALDEVICEMEMORYPROPERTIES2(physicalDevice, pMemoryProperties);
    VKGETPHYSICALDEVICEMEMORYPROPERTIES2_POST(physicalDevice, pMemoryProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2KHR* pMemoryProperties)
{
    VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR_PRE(physicalDevice, pMemoryProperties);
    VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR(physicalDevice, pMemoryProperties);
    VKGETPHYSICALDEVICEMEMORYPROPERTIES2KHR_POST(physicalDevice, pMemoryProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties)
{
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2_PRE(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2_POST(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_physical_device_properties2)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2KHR* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2KHR* pProperties)
{
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR_PRE(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICESPARSEIMAGEFORMATPROPERTIES2KHR_POST(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_KHR_push_descriptor)
VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites)
{
    VKCMDPUSHDESCRIPTORSETKHR_PRE(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    VKCMDPUSHDESCRIPTORSETKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    VKCMDPUSHDESCRIPTORSETKHR_POST(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

#endif // VK_KHR_push_descriptor

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags)
{
    VKTRIMCOMMANDPOOL_PRE(device, commandPool, flags);
    VKTRIMCOMMANDPOOL(device, commandPool, flags);
    VKTRIMCOMMANDPOOL_POST(device, commandPool, flags);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_maintenance1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkTrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlagsKHR flags)
{
    VKTRIMCOMMANDPOOLKHR_PRE(device, commandPool, flags);
    VKTRIMCOMMANDPOOLKHR(device, commandPool, flags);
    VKTRIMCOMMANDPOOLKHR_POST(device, commandPool, flags);
}

#endif // VK_KHR_maintenance1 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties)
{
    VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES_PRE(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIES_POST(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_memory_capabilities)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHR* pExternalBufferInfo, VkExternalBufferPropertiesKHR* pExternalBufferProperties)
{
    VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR_PRE(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    VKGETPHYSICALDEVICEEXTERNALBUFFERPROPERTIESKHR_POST(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_memory_win32)
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle)
{
    VKGETMEMORYWIN32HANDLEKHR_PRE(device, pGetWin32HandleInfo, pHandle);
    VKGETMEMORYWIN32HANDLEKHR(device, pGetWin32HandleInfo, pHandle);
    VKGETMEMORYWIN32HANDLEKHR_POST(device, pGetWin32HandleInfo, pHandle);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties)
{
    VKGETMEMORYWIN32HANDLEPROPERTIESKHR_PRE(device, handleType, handle, pMemoryWin32HandleProperties);
    VKGETMEMORYWIN32HANDLEPROPERTIESKHR(device, handleType, handle, pMemoryWin32HandleProperties);
    VKGETMEMORYWIN32HANDLEPROPERTIESKHR_POST(device, handleType, handle, pMemoryWin32HandleProperties);
}

#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd)
{
    VKGETMEMORYFDKHR_PRE(device, pGetFdInfo, pFd);
    VKGETMEMORYFDKHR(device, pGetFdInfo, pFd);
    VKGETMEMORYFDKHR_POST(device, pGetFdInfo, pFd);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties)
{
    VKGETMEMORYFDPROPERTIESKHR_PRE(device, handleType, fd, pMemoryFdProperties);
    VKGETMEMORYFDPROPERTIESKHR(device, handleType, fd, pMemoryFdProperties);
    VKGETMEMORYFDPROPERTIESKHR_POST(device, handleType, fd, pMemoryFdProperties);
}

#endif // VK_KHR_external_memory_fd

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties)
{
    VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES_PRE(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIES_POST(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_semaphore_capabilities)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHR* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHR* pExternalSemaphoreProperties)
{
    VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR_PRE(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    VKGETPHYSICALDEVICEEXTERNALSEMAPHOREPROPERTIESKHR_POST(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_KHR_external_semaphore_win32)
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle)
{
    VKGETSEMAPHOREWIN32HANDLEKHR_PRE(device, pGetWin32HandleInfo, pHandle);
    VKGETSEMAPHOREWIN32HANDLEKHR(device, pGetWin32HandleInfo, pHandle);
    VKGETSEMAPHOREWIN32HANDLEKHR_POST(device, pGetWin32HandleInfo, pHandle);
}

VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo)
{
    VKIMPORTSEMAPHOREWIN32HANDLEKHR_PRE(device, pImportSemaphoreWin32HandleInfo);
    VKIMPORTSEMAPHOREWIN32HANDLEKHR(device, pImportSemaphoreWin32HandleInfo);
    VKIMPORTSEMAPHOREWIN32HANDLEKHR_POST(device, pImportSemaphoreWin32HandleInfo);
}

#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd)
{
    VKGETSEMAPHOREFDKHR_PRE(device, pGetFdInfo, pFd);
    VKGETSEMAPHOREFDKHR(device, pGetFdInfo, pFd);
    VKGETSEMAPHOREFDKHR_POST(device, pGetFdInfo, pFd);
}

VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo)
{
    VKIMPORTSEMAPHOREFDKHR_PRE(device, pImportSemaphoreFdInfo);
    VKIMPORTSEMAPHOREFDKHR(device, pImportSemaphoreFdInfo);
    VKIMPORTSEMAPHOREFDKHR_POST(device, pImportSemaphoreFdInfo);
}

#endif // VK_KHR_external_semaphore_fd

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties)
{
    VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES_PRE(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIES_POST(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_fence_capabilities)
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfoKHR* pExternalFenceInfo, VkExternalFencePropertiesKHR* pExternalFenceProperties)
{
    VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR_PRE(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    VKGETPHYSICALDEVICEEXTERNALFENCEPROPERTIESKHR_POST(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_external_fence_win32)
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle)
{
    VKGETFENCEWIN32HANDLEKHR_PRE(device, pGetWin32HandleInfo, pHandle);
    VKGETFENCEWIN32HANDLEKHR(device, pGetWin32HandleInfo, pHandle);
    VKGETFENCEWIN32HANDLEKHR_POST(device, pGetWin32HandleInfo, pHandle);
}

VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo)
{
    VKIMPORTFENCEWIN32HANDLEKHR_PRE(device, pImportFenceWin32HandleInfo);
    VKIMPORTFENCEWIN32HANDLEKHR(device, pImportFenceWin32HandleInfo);
    VKIMPORTFENCEWIN32HANDLEKHR_POST(device, pImportFenceWin32HandleInfo);
}

#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd)
{
    VKGETFENCEFDKHR_PRE(device, pGetFdInfo, pFd);
    VKGETFENCEFDKHR(device, pGetFdInfo, pFd);
    VKGETFENCEFDKHR_POST(device, pGetFdInfo, pFd);
}

VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo)
{
    VKIMPORTFENCEFDKHR_PRE(device, pImportFenceFdInfo);
    VKIMPORTFENCEFDKHR(device, pImportFenceFdInfo);
    VKIMPORTFENCEFDKHR_POST(device, pImportFenceFdInfo);
}

#endif // VK_KHR_external_fence_fd

#if defined(VK_EXT_direct_mode_display)
VKAPI_ATTR VkResult VKAPI_CALL vkReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display)
{
    VKRELEASEDISPLAYEXT_PRE(physicalDevice, display);
    VKRELEASEDISPLAYEXT(physicalDevice, display);
    VKRELEASEDISPLAYEXT_POST(physicalDevice, display);
}

#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
VKAPI_ATTR VkResult VKAPI_CALL vkAcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display)
{
    VKACQUIREXLIBDISPLAYEXT_PRE(physicalDevice, dpy, display);
    VKACQUIREXLIBDISPLAYEXT(physicalDevice, dpy, display);
    VKACQUIREXLIBDISPLAYEXT_POST(physicalDevice, dpy, display);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay)
{
    VKGETRANDROUTPUTDISPLAYEXT_PRE(physicalDevice, dpy, rrOutput, pDisplay);
    VKGETRANDROUTPUTDISPLAYEXT(physicalDevice, dpy, rrOutput, pDisplay);
    VKGETRANDROUTPUTDISPLAYEXT_POST(physicalDevice, dpy, rrOutput, pDisplay);
}

#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities)
{
    VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT_PRE(physicalDevice, surface, pSurfaceCapabilities);
    VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT(physicalDevice, surface, pSurfaceCapabilities);
    VKGETPHYSICALDEVICESURFACECAPABILITIES2EXT_POST(physicalDevice, surface, pSurfaceCapabilities);
}

#endif // VK_EXT_display_surface_counter

#if defined(VK_VERSION_1_1)
VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties)
{
    VKENUMERATEPHYSICALDEVICEGROUPS_PRE(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    VKENUMERATEPHYSICALDEVICEGROUPS(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    VKENUMERATEPHYSICALDEVICEGROUPS_POST(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group_creation)
VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupPropertiesKHR* pPhysicalDeviceGroupProperties)
{
    VKENUMERATEPHYSICALDEVICEGROUPSKHR_PRE(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    VKENUMERATEPHYSICALDEVICEGROUPSKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    VKENUMERATEPHYSICALDEVICEGROUPSKHR_POST(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

#endif // VK_KHR_device_group_creation

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures)
{
    VKGETDEVICEGROUPPEERMEMORYFEATURES_PRE(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    VKGETDEVICEGROUPPEERMEMORYFEATURES(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    VKGETDEVICEGROUPPEERMEMORYFEATURES_POST(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlagsKHR* pPeerMemoryFeatures)
{
    VKGETDEVICEGROUPPEERMEMORYFEATURESKHR_PRE(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    VKGETDEVICEGROUPPEERMEMORYFEATURESKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    VKGETDEVICEGROUPPEERMEMORYFEATURESKHR_POST(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1)
VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos)
{
    VKBINDBUFFERMEMORY2_PRE(device, bindInfoCount, pBindInfos);
    VKBINDBUFFERMEMORY2(device, bindInfoCount, pBindInfos);
    VKBINDBUFFERMEMORY2_POST(device, bindInfoCount, pBindInfos);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfoKHR* pBindInfos)
{
    VKBINDBUFFERMEMORY2KHR_PRE(device, bindInfoCount, pBindInfos);
    VKBINDBUFFERMEMORY2KHR(device, bindInfoCount, pBindInfos);
    VKBINDBUFFERMEMORY2KHR_POST(device, bindInfoCount, pBindInfos);
}

#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos)
{
    VKBINDIMAGEMEMORY2_PRE(device, bindInfoCount, pBindInfos);
    VKBINDIMAGEMEMORY2(device, bindInfoCount, pBindInfos);
    VKBINDIMAGEMEMORY2_POST(device, bindInfoCount, pBindInfos);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfoKHR* pBindInfos)
{
    VKBINDIMAGEMEMORY2KHR_PRE(device, bindInfoCount, pBindInfos);
    VKBINDIMAGEMEMORY2KHR(device, bindInfoCount, pBindInfos);
    VKBINDIMAGEMEMORY2KHR_POST(device, bindInfoCount, pBindInfos);
}

#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask)
{
    VKCMDSETDEVICEMASK_PRE(commandBuffer, deviceMask);
    VKCMDSETDEVICEMASK(commandBuffer, deviceMask);
    VKCMDSETDEVICEMASK_POST(commandBuffer, deviceMask);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask)
{
    VKCMDSETDEVICEMASKKHR_PRE(commandBuffer, deviceMask);
    VKCMDSETDEVICEMASKKHR(commandBuffer, deviceMask);
    VKCMDSETDEVICEMASKKHR_POST(commandBuffer, deviceMask);
}

#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities)
{
    VKGETDEVICEGROUPPRESENTCAPABILITIESKHR_PRE(device, pDeviceGroupPresentCapabilities);
    VKGETDEVICEGROUPPRESENTCAPABILITIESKHR(device, pDeviceGroupPresentCapabilities);
    VKGETDEVICEGROUPPRESENTCAPABILITIESKHR_POST(device, pDeviceGroupPresentCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes)
{
    VKGETDEVICEGROUPSURFACEPRESENTMODESKHR_PRE(device, surface, pModes);
    VKGETDEVICEGROUPSURFACEPRESENTMODESKHR(device, surface, pModes);
    VKGETDEVICEGROUPSURFACEPRESENTMODESKHR_POST(device, surface, pModes);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex)
{
    VKACQUIRENEXTIMAGE2KHR_PRE(device, pAcquireInfo, pImageIndex);
    VKACQUIRENEXTIMAGE2KHR(device, pAcquireInfo, pImageIndex);
    VKACQUIRENEXTIMAGE2KHR_POST(device, pAcquireInfo, pImageIndex);
}

#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    VKCMDDISPATCHBASE_PRE(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    VKCMDDISPATCHBASE(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    VKCMDDISPATCHBASE_POST(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
VKAPI_ATTR void VKAPI_CALL vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    VKCMDDISPATCHBASEKHR_PRE(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    VKCMDDISPATCHBASEKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    VKCMDDISPATCHBASEKHR_POST(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects)
{
    VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR_PRE(physicalDevice, surface, pRectCount, pRects);
    VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR(physicalDevice, surface, pRectCount, pRects);
    VKGETPHYSICALDEVICEPRESENTRECTANGLESKHR_POST(physicalDevice, surface, pRectCount, pRects);
}

#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate)
{
    VKCREATEDESCRIPTORUPDATETEMPLATE_PRE(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    VKCREATEDESCRIPTORUPDATETEMPLATE(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    VKCREATEDESCRIPTORUPDATETEMPLATE_POST(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplateKHR* pDescriptorUpdateTemplate)
{
    VKCREATEDESCRIPTORUPDATETEMPLATEKHR_PRE(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    VKCREATEDESCRIPTORUPDATETEMPLATEKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    VKCREATEDESCRIPTORUPDATETEMPLATEKHR_POST(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDESCRIPTORUPDATETEMPLATE_PRE(device, descriptorUpdateTemplate, pAllocator);
    VKDESTROYDESCRIPTORUPDATETEMPLATE(device, descriptorUpdateTemplate, pAllocator);
    VKDESTROYDESCRIPTORUPDATETEMPLATE_POST(device, descriptorUpdateTemplate, pAllocator);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDESCRIPTORUPDATETEMPLATEKHR_PRE(device, descriptorUpdateTemplate, pAllocator);
    VKDESTROYDESCRIPTORUPDATETEMPLATEKHR(device, descriptorUpdateTemplate, pAllocator);
    VKDESTROYDESCRIPTORUPDATETEMPLATEKHR_POST(device, descriptorUpdateTemplate, pAllocator);
}

#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData)
{
    VKUPDATEDESCRIPTORSETWITHTEMPLATE_PRE(device, descriptorSet, descriptorUpdateTemplate, pData);
    VKUPDATEDESCRIPTORSETWITHTEMPLATE(device, descriptorSet, descriptorUpdateTemplate, pData);
    VKUPDATEDESCRIPTORSETWITHTEMPLATE_POST(device, descriptorSet, descriptorUpdateTemplate, pData);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const void* pData)
{
    VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR_PRE(device, descriptorSet, descriptorUpdateTemplate, pData);
    VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
    VKUPDATEDESCRIPTORSETWITHTEMPLATEKHR_POST(device, descriptorSet, descriptorUpdateTemplate, pData);
}

#endif // VK_KHR_descriptor_update_template

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData)
{
    VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR_PRE(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    VKCMDPUSHDESCRIPTORSETWITHTEMPLATEKHR_POST(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

#if defined(VK_EXT_hdr_metadata)
VKAPI_ATTR void VKAPI_CALL vkSetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata)
{
    VKSETHDRMETADATAEXT_PRE(device, swapchainCount, pSwapchains, pMetadata);
    VKSETHDRMETADATAEXT(device, swapchainCount, pSwapchains, pMetadata);
    VKSETHDRMETADATAEXT_POST(device, swapchainCount, pSwapchains, pMetadata);
}

#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_shared_presentable_image)
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain)
{
    VKGETSWAPCHAINSTATUSKHR_PRE(device, swapchain);
    VKGETSWAPCHAINSTATUSKHR(device, swapchain);
    VKGETSWAPCHAINSTATUSKHR_POST(device, swapchain);
}

#endif // VK_KHR_shared_presentable_image

#if defined(VK_NV_clip_space_w_scaling)
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings)
{
    VKCMDSETVIEWPORTWSCALINGNV_PRE(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
    VKCMDSETVIEWPORTWSCALINGNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
    VKCMDSETVIEWPORTWSCALINGNV_POST(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
}

#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_discard_rectangles)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles)
{
    VKCMDSETDISCARDRECTANGLEEXT_PRE(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
    VKCMDSETDISCARDRECTANGLEEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
    VKCMDSETDISCARDRECTANGLEEXT_POST(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable)
{
    VKCMDSETDISCARDRECTANGLEENABLEEXT_PRE(commandBuffer, discardRectangleEnable);
    VKCMDSETDISCARDRECTANGLEENABLEEXT(commandBuffer, discardRectangleEnable);
    VKCMDSETDISCARDRECTANGLEENABLEEXT_POST(commandBuffer, discardRectangleEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode)
{
    VKCMDSETDISCARDRECTANGLEMODEEXT_PRE(commandBuffer, discardRectangleMode);
    VKCMDSETDISCARDRECTANGLEMODEEXT(commandBuffer, discardRectangleMode);
    VKCMDSETDISCARDRECTANGLEMODEEXT_POST(commandBuffer, discardRectangleMode);
}

#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_sample_locations)
VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo)
{
    VKCMDSETSAMPLELOCATIONSEXT_PRE(commandBuffer, pSampleLocationsInfo);
    VKCMDSETSAMPLELOCATIONSEXT(commandBuffer, pSampleLocationsInfo);
    VKCMDSETSAMPLELOCATIONSEXT_POST(commandBuffer, pSampleLocationsInfo);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties)
{
    VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT_PRE(physicalDevice, samples, pMultisampleProperties);
    VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT(physicalDevice, samples, pMultisampleProperties);
    VKGETPHYSICALDEVICEMULTISAMPLEPROPERTIESEXT_POST(physicalDevice, samples, pMultisampleProperties);
}

#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_surface_capabilities2)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities)
{
    VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR_PRE(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
    VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
    VKGETPHYSICALDEVICESURFACECAPABILITIES2KHR_POST(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats)
{
    VKGETPHYSICALDEVICESURFACEFORMATS2KHR_PRE(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
    VKGETPHYSICALDEVICESURFACEFORMATS2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
    VKGETPHYSICALDEVICESURFACEFORMATS2KHR_POST(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
}

#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties)
{
    VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR_PRE(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPROPERTIES2KHR_POST(physicalDevice, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties)
{
    VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR_PRE(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICEDISPLAYPLANEPROPERTIES2KHR_POST(physicalDevice, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties)
{
    VKGETDISPLAYMODEPROPERTIES2KHR_PRE(physicalDevice, display, pPropertyCount, pProperties);
    VKGETDISPLAYMODEPROPERTIES2KHR(physicalDevice, display, pPropertyCount, pProperties);
    VKGETDISPLAYMODEPROPERTIES2KHR_POST(physicalDevice, display, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities)
{
    VKGETDISPLAYPLANECAPABILITIES2KHR_PRE(physicalDevice, pDisplayPlaneInfo, pCapabilities);
    VKGETDISPLAYPLANECAPABILITIES2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities);
    VKGETDISPLAYPLANECAPABILITIES2KHR_POST(physicalDevice, pDisplayPlaneInfo, pCapabilities);
}

#endif // VK_KHR_get_display_properties2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    VKGETBUFFERMEMORYREQUIREMENTS2_PRE(device, pInfo, pMemoryRequirements);
    VKGETBUFFERMEMORYREQUIREMENTS2(device, pInfo, pMemoryRequirements);
    VKGETBUFFERMEMORYREQUIREMENTS2_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    VKGETBUFFERMEMORYREQUIREMENTS2KHR_PRE(device, pInfo, pMemoryRequirements);
    VKGETBUFFERMEMORYREQUIREMENTS2KHR(device, pInfo, pMemoryRequirements);
    VKGETBUFFERMEMORYREQUIREMENTS2KHR_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    VKGETIMAGEMEMORYREQUIREMENTS2_PRE(device, pInfo, pMemoryRequirements);
    VKGETIMAGEMEMORYREQUIREMENTS2(device, pInfo, pMemoryRequirements);
    VKGETIMAGEMEMORYREQUIREMENTS2_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    VKGETIMAGEMEMORYREQUIREMENTS2KHR_PRE(device, pInfo, pMemoryRequirements);
    VKGETIMAGEMEMORYREQUIREMENTS2KHR(device, pInfo, pMemoryRequirements);
    VKGETIMAGEMEMORYREQUIREMENTS2KHR_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements)
{
    VKGETIMAGESPARSEMEMORYREQUIREMENTS2_PRE(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETIMAGESPARSEMEMORYREQUIREMENTS2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETIMAGESPARSEMEMORYREQUIREMENTS2_POST(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_memory_requirements2)
VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2KHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements)
{
    VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR_PRE(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETIMAGESPARSEMEMORYREQUIREMENTS2KHR_POST(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    VKGETDEVICEBUFFERMEMORYREQUIREMENTS_PRE(device, pInfo, pMemoryRequirements);
    VKGETDEVICEBUFFERMEMORYREQUIREMENTS(device, pInfo, pMemoryRequirements);
    VKGETDEVICEBUFFERMEMORYREQUIREMENTS_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR_PRE(device, pInfo, pMemoryRequirements);
    VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR(device, pInfo, pMemoryRequirements);
    VKGETDEVICEBUFFERMEMORYREQUIREMENTSKHR_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    VKGETDEVICEIMAGEMEMORYREQUIREMENTS_PRE(device, pInfo, pMemoryRequirements);
    VKGETDEVICEIMAGEMEMORYREQUIREMENTS(device, pInfo, pMemoryRequirements);
    VKGETDEVICEIMAGEMEMORYREQUIREMENTS_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR_PRE(device, pInfo, pMemoryRequirements);
    VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR(device, pInfo, pMemoryRequirements);
    VKGETDEVICEIMAGEMEMORYREQUIREMENTSKHR_POST(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements)
{
    VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS_PRE(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTS_POST(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirementsKHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements)
{
    VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR_PRE(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    VKGETDEVICEIMAGESPARSEMEMORYREQUIREMENTSKHR_POST(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_1)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion)
{
    VKCREATESAMPLERYCBCRCONVERSION_PRE(device, pCreateInfo, pAllocator, pYcbcrConversion);
    VKCREATESAMPLERYCBCRCONVERSION(device, pCreateInfo, pAllocator, pYcbcrConversion);
    VKCREATESAMPLERYCBCRCONVERSION_POST(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversionKHR* pYcbcrConversion)
{
    VKCREATESAMPLERYCBCRCONVERSIONKHR_PRE(device, pCreateInfo, pAllocator, pYcbcrConversion);
    VKCREATESAMPLERYCBCRCONVERSIONKHR(device, pCreateInfo, pAllocator, pYcbcrConversion);
    VKCREATESAMPLERYCBCRCONVERSIONKHR_POST(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSAMPLERYCBCRCONVERSION_PRE(device, ycbcrConversion, pAllocator);
    VKDESTROYSAMPLERYCBCRCONVERSION(device, ycbcrConversion, pAllocator);
    VKDESTROYSAMPLERYCBCRCONVERSION_POST(device, ycbcrConversion, pAllocator);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversionKHR ycbcrConversion, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSAMPLERYCBCRCONVERSIONKHR_PRE(device, ycbcrConversion, pAllocator);
    VKDESTROYSAMPLERYCBCRCONVERSIONKHR(device, ycbcrConversion, pAllocator);
    VKDESTROYSAMPLERYCBCRCONVERSIONKHR_POST(device, ycbcrConversion, pAllocator);
}

#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue)
{
    VKGETDEVICEQUEUE2_PRE(device, pQueueInfo, pQueue);
    VKGETDEVICEQUEUE2(device, pQueueInfo, pQueue);
    VKGETDEVICEQUEUE2_POST(device, pQueueInfo, pQueue);
}

#endif // VK_VERSION_1_1

#if defined(VK_EXT_validation_cache)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache)
{
    VKCREATEVALIDATIONCACHEEXT_PRE(device, pCreateInfo, pAllocator, pValidationCache);
    VKCREATEVALIDATIONCACHEEXT(device, pCreateInfo, pAllocator, pValidationCache);
    VKCREATEVALIDATIONCACHEEXT_POST(device, pCreateInfo, pAllocator, pValidationCache);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYVALIDATIONCACHEEXT_PRE(device, validationCache, pAllocator);
    VKDESTROYVALIDATIONCACHEEXT(device, validationCache, pAllocator);
    VKDESTROYVALIDATIONCACHEEXT_POST(device, validationCache, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData)
{
    VKGETVALIDATIONCACHEDATAEXT_PRE(device, validationCache, pDataSize, pData);
    VKGETVALIDATIONCACHEDATAEXT(device, validationCache, pDataSize, pData);
    VKGETVALIDATIONCACHEDATAEXT_POST(device, validationCache, pDataSize, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkMergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches)
{
    VKMERGEVALIDATIONCACHESEXT_PRE(device, dstCache, srcCacheCount, pSrcCaches);
    VKMERGEVALIDATIONCACHESEXT(device, dstCache, srcCacheCount, pSrcCaches);
    VKMERGEVALIDATIONCACHESEXT_POST(device, dstCache, srcCacheCount, pSrcCaches);
}

#endif // VK_EXT_validation_cache

#if defined(VK_VERSION_1_1)
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport)
{
    VKGETDESCRIPTORSETLAYOUTSUPPORT_PRE(device, pCreateInfo, pSupport);
    VKGETDESCRIPTORSETLAYOUTSUPPORT(device, pCreateInfo, pSupport);
    VKGETDESCRIPTORSETLAYOUTSUPPORT_POST(device, pCreateInfo, pSupport);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_maintenance3)
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupportKHR* pSupport)
{
    VKGETDESCRIPTORSETLAYOUTSUPPORTKHR_PRE(device, pCreateInfo, pSupport);
    VKGETDESCRIPTORSETLAYOUTSUPPORTKHR(device, pCreateInfo, pSupport);
    VKGETDESCRIPTORSETLAYOUTSUPPORTKHR_POST(device, pCreateInfo, pSupport);
}

#endif // VK_KHR_maintenance3

#if defined(VK_AMD_shader_info)
VKAPI_ATTR VkResult VKAPI_CALL vkGetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo)
{
    VKGETSHADERINFOAMD_PRE(device, pipeline, shaderStage, infoType, pInfoSize, pInfo);
    VKGETSHADERINFOAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo);
    VKGETSHADERINFOAMD_POST(device, pipeline, shaderStage, infoType, pInfoSize, pInfo);
}

#endif // VK_AMD_shader_info

#if defined(VK_EXT_calibrated_timestamps)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainEXT* pTimeDomains)
{
    VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT_PRE(physicalDevice, pTimeDomainCount, pTimeDomains);
    VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT(physicalDevice, pTimeDomainCount, pTimeDomains);
    VKGETPHYSICALDEVICECALIBRATEABLETIMEDOMAINSEXT_POST(physicalDevice, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation)
{
    VKGETCALIBRATEDTIMESTAMPSEXT_PRE(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
    VKGETCALIBRATEDTIMESTAMPSEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
    VKGETCALIBRATEDTIMESTAMPSEXT_POST(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}

#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo)
{
    VKSETDEBUGUTILSOBJECTNAMEEXT_PRE(device, pNameInfo);
    VKSETDEBUGUTILSOBJECTNAMEEXT(device, pNameInfo);
    VKSETDEBUGUTILSOBJECTNAMEEXT_POST(device, pNameInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo)
{
    VKSETDEBUGUTILSOBJECTTAGEXT_PRE(device, pTagInfo);
    VKSETDEBUGUTILSOBJECTTAGEXT(device, pTagInfo);
    VKSETDEBUGUTILSOBJECTTAGEXT_POST(device, pTagInfo);
}

VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    VKQUEUEBEGINDEBUGUTILSLABELEXT_PRE(queue, pLabelInfo);
    VKQUEUEBEGINDEBUGUTILSLABELEXT(queue, pLabelInfo);
    VKQUEUEBEGINDEBUGUTILSLABELEXT_POST(queue, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(VkQueue queue)
{
    VKQUEUEENDDEBUGUTILSLABELEXT_PRE(queue);
    VKQUEUEENDDEBUGUTILSLABELEXT(queue);
    VKQUEUEENDDEBUGUTILSLABELEXT_POST(queue);
}

VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    VKQUEUEINSERTDEBUGUTILSLABELEXT_PRE(queue, pLabelInfo);
    VKQUEUEINSERTDEBUGUTILSLABELEXT(queue, pLabelInfo);
    VKQUEUEINSERTDEBUGUTILSLABELEXT_POST(queue, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    VKCMDBEGINDEBUGUTILSLABELEXT_PRE(commandBuffer, pLabelInfo);
    VKCMDBEGINDEBUGUTILSLABELEXT(commandBuffer, pLabelInfo);
    VKCMDBEGINDEBUGUTILSLABELEXT_POST(commandBuffer, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer)
{
    VKCMDENDDEBUGUTILSLABELEXT_PRE(commandBuffer);
    VKCMDENDDEBUGUTILSLABELEXT(commandBuffer);
    VKCMDENDDEBUGUTILSLABELEXT_POST(commandBuffer);
}

VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    VKCMDINSERTDEBUGUTILSLABELEXT_PRE(commandBuffer, pLabelInfo);
    VKCMDINSERTDEBUGUTILSLABELEXT(commandBuffer, pLabelInfo);
    VKCMDINSERTDEBUGUTILSLABELEXT_POST(commandBuffer, pLabelInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger)
{
    VKCREATEDEBUGUTILSMESSENGEREXT_PRE(instance, pCreateInfo, pAllocator, pMessenger);
    VKCREATEDEBUGUTILSMESSENGEREXT(instance, pCreateInfo, pAllocator, pMessenger);
    VKCREATEDEBUGUTILSMESSENGEREXT_POST(instance, pCreateInfo, pAllocator, pMessenger);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDEBUGUTILSMESSENGEREXT_PRE(instance, messenger, pAllocator);
    VKDESTROYDEBUGUTILSMESSENGEREXT(instance, messenger, pAllocator);
    VKDESTROYDEBUGUTILSMESSENGEREXT_POST(instance, messenger, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
{
    VKSUBMITDEBUGUTILSMESSAGEEXT_PRE(instance, messageSeverity, messageTypes, pCallbackData);
    VKSUBMITDEBUGUTILSMESSAGEEXT(instance, messageSeverity, messageTypes, pCallbackData);
    VKSUBMITDEBUGUTILSMESSAGEEXT_POST(instance, messageSeverity, messageTypes, pCallbackData);
}

#endif // VK_EXT_debug_utils

#if defined(VK_EXT_external_memory_host)
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties)
{
    VKGETMEMORYHOSTPOINTERPROPERTIESEXT_PRE(device, handleType, pHostPointer, pMemoryHostPointerProperties);
    VKGETMEMORYHOSTPOINTERPROPERTIESEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
    VKGETMEMORYHOSTPOINTERPROPERTIESEXT_POST(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}

#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
VKAPI_ATTR void VKAPI_CALL vkCmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker)
{
    VKCMDWRITEBUFFERMARKERAMD_PRE(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
    VKCMDWRITEBUFFERMARKERAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
    VKCMDWRITEBUFFERMARKERAMD_POST(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
}

#endif // VK_AMD_buffer_marker

#if defined(VK_VERSION_1_2)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
    VKCREATERENDERPASS2_PRE(device, pCreateInfo, pAllocator, pRenderPass);
    VKCREATERENDERPASS2(device, pCreateInfo, pAllocator, pRenderPass);
    VKCREATERENDERPASS2_POST(device, pCreateInfo, pAllocator, pRenderPass);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
    VKCREATERENDERPASS2KHR_PRE(device, pCreateInfo, pAllocator, pRenderPass);
    VKCREATERENDERPASS2KHR(device, pCreateInfo, pAllocator, pRenderPass);
    VKCREATERENDERPASS2KHR_POST(device, pCreateInfo, pAllocator, pRenderPass);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfo* pSubpassBeginInfo)
{
    VKCMDBEGINRENDERPASS2_PRE(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    VKCMDBEGINRENDERPASS2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    VKCMDBEGINRENDERPASS2_POST(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfoKHR* pSubpassBeginInfo)
{
    VKCMDBEGINRENDERPASS2KHR_PRE(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    VKCMDBEGINRENDERPASS2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    VKCMDBEGINRENDERPASS2KHR_POST(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo* pSubpassBeginInfo, const VkSubpassEndInfo* pSubpassEndInfo)
{
    VKCMDNEXTSUBPASS2_PRE(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    VKCMDNEXTSUBPASS2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    VKCMDNEXTSUBPASS2_POST(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR* pSubpassBeginInfo, const VkSubpassEndInfoKHR* pSubpassEndInfo)
{
    VKCMDNEXTSUBPASS2KHR_PRE(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    VKCMDNEXTSUBPASS2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    VKCMDNEXTSUBPASS2KHR_POST(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo* pSubpassEndInfo)
{
    VKCMDENDRENDERPASS2_PRE(commandBuffer, pSubpassEndInfo);
    VKCMDENDRENDERPASS2(commandBuffer, pSubpassEndInfo);
    VKCMDENDRENDERPASS2_POST(commandBuffer, pSubpassEndInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR* pSubpassEndInfo)
{
    VKCMDENDRENDERPASS2KHR_PRE(commandBuffer, pSubpassEndInfo);
    VKCMDENDRENDERPASS2KHR(commandBuffer, pSubpassEndInfo);
    VKCMDENDRENDERPASS2KHR_POST(commandBuffer, pSubpassEndInfo);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    VKGETSEMAPHORECOUNTERVALUE_PRE(device, semaphore, pValue);
    VKGETSEMAPHORECOUNTERVALUE(device, semaphore, pValue);
    VKGETSEMAPHORECOUNTERVALUE_POST(device, semaphore, pValue);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    VKGETSEMAPHORECOUNTERVALUEKHR_PRE(device, semaphore, pValue);
    VKGETSEMAPHORECOUNTERVALUEKHR(device, semaphore, pValue);
    VKGETSEMAPHORECOUNTERVALUEKHR_POST(device, semaphore, pValue);
}

#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
VKAPI_ATTR VkResult VKAPI_CALL vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    VKWAITSEMAPHORES_PRE(device, pWaitInfo, timeout);
    VKWAITSEMAPHORES(device, pWaitInfo, timeout);
    VKWAITSEMAPHORES_POST(device, pWaitInfo, timeout);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
VKAPI_ATTR VkResult VKAPI_CALL vkWaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfoKHR* pWaitInfo, uint64_t timeout)
{
    VKWAITSEMAPHORESKHR_PRE(device, pWaitInfo, timeout);
    VKWAITSEMAPHORESKHR(device, pWaitInfo, timeout);
    VKWAITSEMAPHORESKHR_POST(device, pWaitInfo, timeout);
}

#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
VKAPI_ATTR VkResult VKAPI_CALL vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    VKSIGNALSEMAPHORE_PRE(device, pSignalInfo);
    VKSIGNALSEMAPHORE(device, pSignalInfo);
    VKSIGNALSEMAPHORE_POST(device, pSignalInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
VKAPI_ATTR VkResult VKAPI_CALL vkSignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfoKHR* pSignalInfo)
{
    VKSIGNALSEMAPHOREKHR_PRE(device, pSignalInfo);
    VKSIGNALSEMAPHOREKHR(device, pSignalInfo);
    VKSIGNALSEMAPHOREKHR_POST(device, pSignalInfo);
}

#endif // VK_KHR_timeline_semaphore

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties)
{
    VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID_PRE(device, buffer, pProperties);
    VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID(device, buffer, pProperties);
    VKGETANDROIDHARDWAREBUFFERPROPERTIESANDROID_POST(device, buffer, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer)
{
    VKGETMEMORYANDROIDHARDWAREBUFFERANDROID_PRE(device, pInfo, pBuffer);
    VKGETMEMORYANDROIDHARDWAREBUFFERANDROID(device, pInfo, pBuffer);
    VKGETMEMORYANDROIDHARDWAREBUFFERANDROID_POST(device, pInfo, pBuffer);
}

#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_VERSION_1_2)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    VKCMDDRAWINDIRECTCOUNT_PRE(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDIRECTCOUNT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDIRECTCOUNT_POST(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    VKCMDDRAWINDIRECTCOUNTKHR_PRE(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDIRECTCOUNTKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDIRECTCOUNTKHR_POST(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_KHR_draw_indirect_count

#if defined(VK_VERSION_1_2)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    VKCMDDRAWINDEXEDINDIRECTCOUNT_PRE(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDEXEDINDIRECTCOUNT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDEXEDINDIRECTCOUNT_POST(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    VKCMDDRAWINDEXEDINDIRECTCOUNTKHR_PRE(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDEXEDINDIRECTCOUNTKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWINDEXEDINDIRECTCOUNTKHR_POST(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_KHR_draw_indirect_count

#if defined(VK_NV_device_diagnostic_checkpoints)
VKAPI_ATTR void VKAPI_CALL vkCmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker)
{
    VKCMDSETCHECKPOINTNV_PRE(commandBuffer, pCheckpointMarker);
    VKCMDSETCHECKPOINTNV(commandBuffer, pCheckpointMarker);
    VKCMDSETCHECKPOINTNV_POST(commandBuffer, pCheckpointMarker);
}

VKAPI_ATTR void VKAPI_CALL vkGetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData)
{
    VKGETQUEUECHECKPOINTDATANV_PRE(queue, pCheckpointDataCount, pCheckpointData);
    VKGETQUEUECHECKPOINTDATANV(queue, pCheckpointDataCount, pCheckpointData);
    VKGETQUEUECHECKPOINTDATANV_POST(queue, pCheckpointDataCount, pCheckpointData);
}

#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_EXT_transform_feedback)
VKAPI_ATTR void VKAPI_CALL vkCmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes)
{
    VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT_PRE(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
    VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
    VKCMDBINDTRANSFORMFEEDBACKBUFFERSEXT_POST(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets)
{
    VKCMDBEGINTRANSFORMFEEDBACKEXT_PRE(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
    VKCMDBEGINTRANSFORMFEEDBACKEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
    VKCMDBEGINTRANSFORMFEEDBACKEXT_POST(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets)
{
    VKCMDENDTRANSFORMFEEDBACKEXT_PRE(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
    VKCMDENDTRANSFORMFEEDBACKEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
    VKCMDENDTRANSFORMFEEDBACKEXT_POST(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index)
{
    VKCMDBEGINQUERYINDEXEDEXT_PRE(commandBuffer, queryPool, query, flags, index);
    VKCMDBEGINQUERYINDEXEDEXT(commandBuffer, queryPool, query, flags, index);
    VKCMDBEGINQUERYINDEXEDEXT_POST(commandBuffer, queryPool, query, flags, index);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index)
{
    VKCMDENDQUERYINDEXEDEXT_PRE(commandBuffer, queryPool, query, index);
    VKCMDENDQUERYINDEXEDEXT(commandBuffer, queryPool, query, index);
    VKCMDENDQUERYINDEXEDEXT_POST(commandBuffer, queryPool, query, index);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride)
{
    VKCMDDRAWINDIRECTBYTECOUNTEXT_PRE(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
    VKCMDDRAWINDIRECTBYTECOUNTEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
    VKCMDDRAWINDIRECTBYTECOUNTEXT_POST(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
}

#endif // VK_EXT_transform_feedback

#if defined(VK_NV_scissor_exclusive)
VKAPI_ATTR void VKAPI_CALL vkCmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors)
{
    VKCMDSETEXCLUSIVESCISSORNV_PRE(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
    VKCMDSETEXCLUSIVESCISSORNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
    VKCMDSETEXCLUSIVESCISSORNV_POST(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
}

#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
VKAPI_ATTR void VKAPI_CALL vkCmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables)
{
    VKCMDSETEXCLUSIVESCISSORENABLENV_PRE(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables);
    VKCMDSETEXCLUSIVESCISSORENABLENV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables);
    VKCMDSETEXCLUSIVESCISSORENABLENV_POST(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables);
}

#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_shading_rate_image)
VKAPI_ATTR void VKAPI_CALL vkCmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout)
{
    VKCMDBINDSHADINGRATEIMAGENV_PRE(commandBuffer, imageView, imageLayout);
    VKCMDBINDSHADINGRATEIMAGENV(commandBuffer, imageView, imageLayout);
    VKCMDBINDSHADINGRATEIMAGENV_POST(commandBuffer, imageView, imageLayout);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes)
{
    VKCMDSETVIEWPORTSHADINGRATEPALETTENV_PRE(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes);
    VKCMDSETVIEWPORTSHADINGRATEPALETTENV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes);
    VKCMDSETVIEWPORTSHADINGRATEPALETTENV_POST(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders)
{
    VKCMDSETCOARSESAMPLEORDERNV_PRE(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
    VKCMDSETCOARSESAMPLEORDERNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
    VKCMDSETCOARSESAMPLEORDERNV_POST(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
}

#endif // VK_NV_shading_rate_image

#if defined(VK_NV_mesh_shader)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask)
{
    VKCMDDRAWMESHTASKSNV_PRE(commandBuffer, taskCount, firstTask);
    VKCMDDRAWMESHTASKSNV(commandBuffer, taskCount, firstTask);
    VKCMDDRAWMESHTASKSNV_POST(commandBuffer, taskCount, firstTask);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    VKCMDDRAWMESHTASKSINDIRECTNV_PRE(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTNV(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTNV_POST(commandBuffer, buffer, offset, drawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    VKCMDDRAWMESHTASKSINDIRECTCOUNTNV_PRE(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTCOUNTNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTCOUNTNV_POST(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_NV_mesh_shader

#if defined(VK_EXT_mesh_shader)
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    VKCMDDRAWMESHTASKSEXT_PRE(commandBuffer, groupCountX, groupCountY, groupCountZ);
    VKCMDDRAWMESHTASKSEXT(commandBuffer, groupCountX, groupCountY, groupCountZ);
    VKCMDDRAWMESHTASKSEXT_POST(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    VKCMDDRAWMESHTASKSINDIRECTEXT_PRE(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTEXT(commandBuffer, buffer, offset, drawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTEXT_POST(commandBuffer, buffer, offset, drawCount, stride);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT_PRE(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    VKCMDDRAWMESHTASKSINDIRECTCOUNTEXT_POST(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_EXT_mesh_shader

#if defined(VK_NV_ray_tracing)
VKAPI_ATTR VkResult VKAPI_CALL vkCompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader)
{
    VKCOMPILEDEFERREDNV_PRE(device, pipeline, shader);
    VKCOMPILEDEFERREDNV(device, pipeline, shader);
    VKCOMPILEDEFERREDNV_POST(device, pipeline, shader);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure)
{
    VKCREATEACCELERATIONSTRUCTURENV_PRE(device, pCreateInfo, pAllocator, pAccelerationStructure);
    VKCREATEACCELERATIONSTRUCTURENV(device, pCreateInfo, pAllocator, pAccelerationStructure);
    VKCREATEACCELERATIONSTRUCTURENV_POST(device, pCreateInfo, pAllocator, pAccelerationStructure);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
VKAPI_ATTR void VKAPI_CALL vkDestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYACCELERATIONSTRUCTUREKHR_PRE(device, accelerationStructure, pAllocator);
    VKDESTROYACCELERATIONSTRUCTUREKHR(device, accelerationStructure, pAllocator);
    VKDESTROYACCELERATIONSTRUCTUREKHR_POST(device, accelerationStructure, pAllocator);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
VKAPI_ATTR void VKAPI_CALL vkDestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYACCELERATIONSTRUCTURENV_PRE(device, accelerationStructure, pAllocator);
    VKDESTROYACCELERATIONSTRUCTURENV(device, accelerationStructure, pAllocator);
    VKDESTROYACCELERATIONSTRUCTURENV_POST(device, accelerationStructure, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkGetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV_PRE(device, pInfo, pMemoryRequirements);
    VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV(device, pInfo, pMemoryRequirements);
    VKGETACCELERATIONSTRUCTUREMEMORYREQUIREMENTSNV_POST(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos)
{
    VKBINDACCELERATIONSTRUCTUREMEMORYNV_PRE(device, bindInfoCount, pBindInfos);
    VKBINDACCELERATIONSTRUCTUREMEMORYNV(device, bindInfoCount, pBindInfos);
    VKBINDACCELERATIONSTRUCTUREMEMORYNV_POST(device, bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode)
{
    VKCMDCOPYACCELERATIONSTRUCTURENV_PRE(commandBuffer, dst, src, mode);
    VKCMDCOPYACCELERATIONSTRUCTURENV(commandBuffer, dst, src, mode);
    VKCMDCOPYACCELERATIONSTRUCTURENV_POST(commandBuffer, dst, src, mode);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo)
{
    VKCMDCOPYACCELERATIONSTRUCTUREKHR_PRE(commandBuffer, pInfo);
    VKCMDCOPYACCELERATIONSTRUCTUREKHR(commandBuffer, pInfo);
    VKCMDCOPYACCELERATIONSTRUCTUREKHR_POST(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo)
{
    VKCOPYACCELERATIONSTRUCTUREKHR_PRE(device, deferredOperation, pInfo);
    VKCOPYACCELERATIONSTRUCTUREKHR(device, deferredOperation, pInfo);
    VKCOPYACCELERATIONSTRUCTUREKHR_POST(device, deferredOperation, pInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo)
{
    VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR_PRE(commandBuffer, pInfo);
    VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR(commandBuffer, pInfo);
    VKCMDCOPYACCELERATIONSTRUCTURETOMEMORYKHR_POST(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo)
{
    VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR_PRE(device, deferredOperation, pInfo);
    VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR(device, deferredOperation, pInfo);
    VKCOPYACCELERATIONSTRUCTURETOMEMORYKHR_POST(device, deferredOperation, pInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo)
{
    VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_PRE(commandBuffer, pInfo);
    VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR(commandBuffer, pInfo);
    VKCMDCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_POST(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo)
{
    VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_PRE(device, deferredOperation, pInfo);
    VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR(device, deferredOperation, pInfo);
    VKCOPYMEMORYTOACCELERATIONSTRUCTUREKHR_POST(device, deferredOperation, pInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery)
{
    VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_PRE(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
    VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
    VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_POST(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
VKAPI_ATTR void VKAPI_CALL vkCmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery)
{
    VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV_PRE(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
    VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
    VKCMDWRITEACCELERATIONSTRUCTURESPROPERTIESNV_POST(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset)
{
    VKCMDBUILDACCELERATIONSTRUCTURENV_PRE(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
    VKCMDBUILDACCELERATIONSTRUCTURENV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
    VKCMDBUILDACCELERATIONSTRUCTURENV_POST(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
VKAPI_ATTR VkResult VKAPI_CALL vkWriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, size_t dataSize, void* pData, size_t stride)
{
    VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_PRE(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
    VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
    VKWRITEACCELERATIONSTRUCTURESPROPERTIESKHR_POST(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth)
{
    VKCMDTRACERAYSKHR_PRE(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
    VKCMDTRACERAYSKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
    VKCMDTRACERAYSKHR_POST(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth)
{
    VKCMDTRACERAYSNV_PRE(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
    VKCMDTRACERAYSNV(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
    VKCMDTRACERAYSNV_POST(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData)
{
    VKGETRAYTRACINGSHADERGROUPHANDLESKHR_PRE(device, pipeline, firstGroup, groupCount, dataSize, pData);
    VKGETRAYTRACINGSHADERGROUPHANDLESKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
    VKGETRAYTRACINGSHADERGROUPHANDLESKHR_POST(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData)
{
    VKGETRAYTRACINGSHADERGROUPHANDLESNV_PRE(device, pipeline, firstGroup, groupCount, dataSize, pData);
    VKGETRAYTRACINGSHADERGROUPHANDLESNV(device, pipeline, firstGroup, groupCount, dataSize, pData);
    VKGETRAYTRACINGSHADERGROUPHANDLESNV_POST(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData)
{
    VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR_PRE(device, pipeline, firstGroup, groupCount, dataSize, pData);
    VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
    VKGETRAYTRACINGCAPTUREREPLAYSHADERGROUPHANDLESKHR_POST(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
VKAPI_ATTR VkResult VKAPI_CALL vkGetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData)
{
    VKGETACCELERATIONSTRUCTUREHANDLENV_PRE(device, accelerationStructure, dataSize, pData);
    VKGETACCELERATIONSTRUCTUREHANDLENV(device, accelerationStructure, dataSize, pData);
    VKGETACCELERATIONSTRUCTUREHANDLENV_POST(device, accelerationStructure, dataSize, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    VKCREATERAYTRACINGPIPELINESNV_PRE(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATERAYTRACINGPIPELINESNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATERAYTRACINGPIPELINESNV_POST(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    VKCREATERAYTRACINGPIPELINESKHR_PRE(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATERAYTRACINGPIPELINESKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    VKCREATERAYTRACINGPIPELINESKHR_POST(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_cooperative_matrix)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties)
{
    VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV_PRE(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV(physicalDevice, pPropertyCount, pProperties);
    VKGETPHYSICALDEVICECOOPERATIVEMATRIXPROPERTIESNV_POST(physicalDevice, pPropertyCount, pProperties);
}

#endif // VK_NV_cooperative_matrix

#if defined(VK_KHR_ray_tracing_pipeline)
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress)
{
    VKCMDTRACERAYSINDIRECTKHR_PRE(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
    VKCMDTRACERAYSINDIRECTKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
    VKCMDTRACERAYSINDIRECTKHR_POST(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_ray_tracing_maintenance1)
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress)
{
    VKCMDTRACERAYSINDIRECT2KHR_PRE(commandBuffer, indirectDeviceAddress);
    VKCMDTRACERAYSINDIRECT2KHR(commandBuffer, indirectDeviceAddress);
    VKCMDTRACERAYSINDIRECT2KHR_POST(commandBuffer, indirectDeviceAddress);
}

#endif // VK_KHR_ray_tracing_maintenance1

#if defined(VK_KHR_acceleration_structure)
VKAPI_ATTR void VKAPI_CALL vkGetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility)
{
    VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR_PRE(device, pVersionInfo, pCompatibility);
    VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR(device, pVersionInfo, pCompatibility);
    VKGETDEVICEACCELERATIONSTRUCTURECOMPATIBILITYKHR_POST(device, pVersionInfo, pCompatibility);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
VKAPI_ATTR VkDeviceSize VKAPI_CALL vkGetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader)
{
    VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR_PRE(device, pipeline, group, groupShader);
    VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR(device, pipeline, group, groupShader);
    VKGETRAYTRACINGSHADERGROUPSTACKSIZEKHR_POST(device, pipeline, group, groupShader);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize)
{
    VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR_PRE(commandBuffer, pipelineStackSize);
    VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR(commandBuffer, pipelineStackSize);
    VKCMDSETRAYTRACINGPIPELINESTACKSIZEKHR_POST(commandBuffer, pipelineStackSize);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NVX_image_view_handle)
VKAPI_ATTR uint32_t VKAPI_CALL vkGetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo)
{
    VKGETIMAGEVIEWHANDLENVX_PRE(device, pInfo);
    VKGETIMAGEVIEWHANDLENVX(device, pInfo);
    VKGETIMAGEVIEWHANDLENVX_POST(device, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties)
{
    VKGETIMAGEVIEWADDRESSNVX_PRE(device, imageView, pProperties);
    VKGETIMAGEVIEWADDRESSNVX(device, imageView, pProperties);
    VKGETIMAGEVIEWADDRESSNVX_POST(device, imageView, pProperties);
}

#endif // VK_NVX_image_view_handle

#if defined(VK_EXT_full_screen_exclusive)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
    VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT_PRE(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes);
    VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes);
    VKGETPHYSICALDEVICESURFACEPRESENTMODES2EXT_POST(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes)
{
    VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT_PRE(device, pSurfaceInfo, pModes);
    VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT(device, pSurfaceInfo, pModes);
    VKGETDEVICEGROUPSURFACEPRESENTMODES2EXT_POST(device, pSurfaceInfo, pModes);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain)
{
    VKACQUIREFULLSCREENEXCLUSIVEMODEEXT_PRE(device, swapchain);
    VKACQUIREFULLSCREENEXCLUSIVEMODEEXT(device, swapchain);
    VKACQUIREFULLSCREENEXCLUSIVEMODEEXT_POST(device, swapchain);
}

VKAPI_ATTR VkResult VKAPI_CALL vkReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain)
{
    VKRELEASEFULLSCREENEXCLUSIVEMODEEXT_PRE(device, swapchain);
    VKRELEASEFULLSCREENEXCLUSIVEMODEEXT(device, swapchain);
    VKRELEASEFULLSCREENEXCLUSIVEMODEEXT_POST(device, swapchain);
}

#endif // VK_EXT_full_screen_exclusive

#if defined(VK_VERSION_1_2)
VKAPI_ATTR uint64_t VKAPI_CALL vkGetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo)
{
    VKGETBUFFEROPAQUECAPTUREADDRESS_PRE(device, pInfo);
    VKGETBUFFEROPAQUECAPTUREADDRESS(device, pInfo);
    VKGETBUFFEROPAQUECAPTUREADDRESS_POST(device, pInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
VKAPI_ATTR uint64_t VKAPI_CALL vkGetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfoKHR* pInfo)
{
    VKGETBUFFEROPAQUECAPTUREADDRESSKHR_PRE(device, pInfo);
    VKGETBUFFEROPAQUECAPTUREADDRESSKHR(device, pInfo);
    VKGETBUFFEROPAQUECAPTUREADDRESSKHR_POST(device, pInfo);
}

#endif // VK_KHR_buffer_device_address

#if defined(VK_VERSION_1_2)
VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo)
{
    VKGETBUFFERDEVICEADDRESS_PRE(device, pInfo);
    VKGETBUFFERDEVICEADDRESS(device, pInfo);
    VKGETBUFFERDEVICEADDRESS_POST(device, pInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfoKHR* pInfo)
{
    VKGETBUFFERDEVICEADDRESSKHR_PRE(device, pInfo);
    VKGETBUFFERDEVICEADDRESSKHR(device, pInfo);
    VKGETBUFFERDEVICEADDRESSKHR_POST(device, pInfo);
}

#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_buffer_device_address)
VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfoEXT* pInfo)
{
    VKGETBUFFERDEVICEADDRESSEXT_PRE(device, pInfo);
    VKGETBUFFERDEVICEADDRESSEXT(device, pInfo);
    VKGETBUFFERDEVICEADDRESSEXT_POST(device, pInfo);
}

#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_headless_surface)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateHeadlessSurfaceEXT(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    VKCREATEHEADLESSSURFACEEXT_PRE(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEHEADLESSSURFACEEXT(instance, pCreateInfo, pAllocator, pSurface);
    VKCREATEHEADLESSSURFACEEXT_POST(instance, pCreateInfo, pAllocator, pSurface);
}

#endif // VK_EXT_headless_surface

#if defined(VK_NV_coverage_reduction_mode)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations)
{
    VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV_PRE(physicalDevice, pCombinationCount, pCombinations);
    VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV(physicalDevice, pCombinationCount, pCombinations);
    VKGETPHYSICALDEVICESUPPORTEDFRAMEBUFFERMIXEDSAMPLESCOMBINATIONSNV_POST(physicalDevice, pCombinationCount, pCombinations);
}

#endif // VK_NV_coverage_reduction_mode

#if defined(VK_VERSION_1_2)
VKAPI_ATTR uint64_t VKAPI_CALL vkGetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo)
{
    VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS_PRE(device, pInfo);
    VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS(device, pInfo);
    VKGETDEVICEMEMORYOPAQUECAPTUREADDRESS_POST(device, pInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
VKAPI_ATTR uint64_t VKAPI_CALL vkGetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfoKHR* pInfo)
{
    VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR_PRE(device, pInfo);
    VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR(device, pInfo);
    VKGETDEVICEMEMORYOPAQUECAPTUREADDRESSKHR_POST(device, pInfo);
}

#endif // VK_KHR_buffer_device_address

#if defined(VK_KHR_pipeline_executable_properties)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutablePropertiesKHR(VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties)
{
    VKGETPIPELINEEXECUTABLEPROPERTIESKHR_PRE(device, pPipelineInfo, pExecutableCount, pProperties);
    VKGETPIPELINEEXECUTABLEPROPERTIESKHR(device, pPipelineInfo, pExecutableCount, pProperties);
    VKGETPIPELINEEXECUTABLEPROPERTIESKHR_POST(device, pPipelineInfo, pExecutableCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutableStatisticsKHR(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics)
{
    VKGETPIPELINEEXECUTABLESTATISTICSKHR_PRE(device, pExecutableInfo, pStatisticCount, pStatistics);
    VKGETPIPELINEEXECUTABLESTATISTICSKHR(device, pExecutableInfo, pStatisticCount, pStatistics);
    VKGETPIPELINEEXECUTABLESTATISTICSKHR_POST(device, pExecutableInfo, pStatisticCount, pStatistics);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutableInternalRepresentationsKHR(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations)
{
    VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR_PRE(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
    VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
    VKGETPIPELINEEXECUTABLEINTERNALREPRESENTATIONSKHR_POST(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
}

#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_EXT_line_rasterization)
VKAPI_ATTR void VKAPI_CALL vkCmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern)
{
    VKCMDSETLINESTIPPLEEXT_PRE(commandBuffer, lineStippleFactor, lineStipplePattern);
    VKCMDSETLINESTIPPLEEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
    VKCMDSETLINESTIPPLEEXT_POST(commandBuffer, lineStippleFactor, lineStipplePattern);
}

#endif // VK_EXT_line_rasterization

#if defined(VKSC_VERSION_1_0)
VKAPI_ATTR VkResult VKAPI_CALL vkGetFaultData(VkDevice device, VkFaultQueryBehavior faultQueryBehavior, VkBool32* pUnrecordedFaults, uint32_t* pFaultCount, VkFaultData* pFaults)
{
    VKGETFAULTDATA_PRE(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults);
    VKGETFAULTDATA(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults);
    VKGETFAULTDATA_POST(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults);
}

#endif // VKSC_VERSION_1_0

#if defined(VK_VERSION_1_3)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties)
{
    VKGETPHYSICALDEVICETOOLPROPERTIES_PRE(physicalDevice, pToolCount, pToolProperties);
    VKGETPHYSICALDEVICETOOLPROPERTIES(physicalDevice, pToolCount, pToolProperties);
    VKGETPHYSICALDEVICETOOLPROPERTIES_POST(physicalDevice, pToolCount, pToolProperties);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_tooling_info)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolPropertiesEXT* pToolProperties)
{
    VKGETPHYSICALDEVICETOOLPROPERTIESEXT_PRE(physicalDevice, pToolCount, pToolProperties);
    VKGETPHYSICALDEVICETOOLPROPERTIESEXT(physicalDevice, pToolCount, pToolProperties);
    VKGETPHYSICALDEVICETOOLPROPERTIESEXT_POST(physicalDevice, pToolCount, pToolProperties);
}

#endif // VK_EXT_tooling_info

#if defined(VK_KHR_acceleration_structure)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAccelerationStructureKHR(VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure)
{
    VKCREATEACCELERATIONSTRUCTUREKHR_PRE(device, pCreateInfo, pAllocator, pAccelerationStructure);
    VKCREATEACCELERATIONSTRUCTUREKHR(device, pCreateInfo, pAllocator, pAccelerationStructure);
    VKCREATEACCELERATIONSTRUCTUREKHR_POST(device, pCreateInfo, pAllocator, pAccelerationStructure);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructuresKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos)
{
    VKCMDBUILDACCELERATIONSTRUCTURESKHR_PRE(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
    VKCMDBUILDACCELERATIONSTRUCTURESKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
    VKCMDBUILDACCELERATIONSTRUCTURESKHR_POST(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts)
{
    VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR_PRE(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
    VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
    VKCMDBUILDACCELERATIONSTRUCTURESINDIRECTKHR_POST(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBuildAccelerationStructuresKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos)
{
    VKBUILDACCELERATIONSTRUCTURESKHR_PRE(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
    VKBUILDACCELERATIONSTRUCTURESKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
    VKBUILDACCELERATIONSTRUCTURESKHR_POST(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
}

VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo)
{
    VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR_PRE(device, pInfo);
    VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR(device, pInfo);
    VKGETACCELERATIONSTRUCTUREDEVICEADDRESSKHR_POST(device, pInfo);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_deferred_host_operations)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation)
{
    VKCREATEDEFERREDOPERATIONKHR_PRE(device, pAllocator, pDeferredOperation);
    VKCREATEDEFERREDOPERATIONKHR(device, pAllocator, pDeferredOperation);
    VKCREATEDEFERREDOPERATIONKHR_POST(device, pAllocator, pDeferredOperation);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYDEFERREDOPERATIONKHR_PRE(device, operation, pAllocator);
    VKDESTROYDEFERREDOPERATIONKHR(device, operation, pAllocator);
    VKDESTROYDEFERREDOPERATIONKHR_POST(device, operation, pAllocator);
}

VKAPI_ATTR uint32_t VKAPI_CALL vkGetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation)
{
    VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR_PRE(device, operation);
    VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR(device, operation);
    VKGETDEFERREDOPERATIONMAXCONCURRENCYKHR_POST(device, operation);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation)
{
    VKGETDEFERREDOPERATIONRESULTKHR_PRE(device, operation);
    VKGETDEFERREDOPERATIONRESULTKHR(device, operation);
    VKGETDEFERREDOPERATIONRESULTKHR_POST(device, operation);
}

VKAPI_ATTR VkResult VKAPI_CALL vkDeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation)
{
    VKDEFERREDOPERATIONJOINKHR_PRE(device, operation);
    VKDEFERREDOPERATIONJOINKHR(device, operation);
    VKDEFERREDOPERATIONJOINKHR_POST(device, operation);
}

#endif // VK_KHR_deferred_host_operations

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode)
{
    VKCMDSETCULLMODE_PRE(commandBuffer, cullMode);
    VKCMDSETCULLMODE(commandBuffer, cullMode);
    VKCMDSETCULLMODE_POST(commandBuffer, cullMode);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode)
{
    VKCMDSETCULLMODEEXT_PRE(commandBuffer, cullMode);
    VKCMDSETCULLMODEEXT(commandBuffer, cullMode);
    VKCMDSETCULLMODEEXT_POST(commandBuffer, cullMode);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace)
{
    VKCMDSETFRONTFACE_PRE(commandBuffer, frontFace);
    VKCMDSETFRONTFACE(commandBuffer, frontFace);
    VKCMDSETFRONTFACE_POST(commandBuffer, frontFace);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace)
{
    VKCMDSETFRONTFACEEXT_PRE(commandBuffer, frontFace);
    VKCMDSETFRONTFACEEXT(commandBuffer, frontFace);
    VKCMDSETFRONTFACEEXT_POST(commandBuffer, frontFace);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology)
{
    VKCMDSETPRIMITIVETOPOLOGY_PRE(commandBuffer, primitiveTopology);
    VKCMDSETPRIMITIVETOPOLOGY(commandBuffer, primitiveTopology);
    VKCMDSETPRIMITIVETOPOLOGY_POST(commandBuffer, primitiveTopology);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology)
{
    VKCMDSETPRIMITIVETOPOLOGYEXT_PRE(commandBuffer, primitiveTopology);
    VKCMDSETPRIMITIVETOPOLOGYEXT(commandBuffer, primitiveTopology);
    VKCMDSETPRIMITIVETOPOLOGYEXT_POST(commandBuffer, primitiveTopology);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports)
{
    VKCMDSETVIEWPORTWITHCOUNT_PRE(commandBuffer, viewportCount, pViewports);
    VKCMDSETVIEWPORTWITHCOUNT(commandBuffer, viewportCount, pViewports);
    VKCMDSETVIEWPORTWITHCOUNT_POST(commandBuffer, viewportCount, pViewports);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports)
{
    VKCMDSETVIEWPORTWITHCOUNTEXT_PRE(commandBuffer, viewportCount, pViewports);
    VKCMDSETVIEWPORTWITHCOUNTEXT(commandBuffer, viewportCount, pViewports);
    VKCMDSETVIEWPORTWITHCOUNTEXT_POST(commandBuffer, viewportCount, pViewports);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors)
{
    VKCMDSETSCISSORWITHCOUNT_PRE(commandBuffer, scissorCount, pScissors);
    VKCMDSETSCISSORWITHCOUNT(commandBuffer, scissorCount, pScissors);
    VKCMDSETSCISSORWITHCOUNT_POST(commandBuffer, scissorCount, pScissors);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors)
{
    VKCMDSETSCISSORWITHCOUNTEXT_PRE(commandBuffer, scissorCount, pScissors);
    VKCMDSETSCISSORWITHCOUNTEXT(commandBuffer, scissorCount, pScissors);
    VKCMDSETSCISSORWITHCOUNTEXT_POST(commandBuffer, scissorCount, pScissors);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides)
{
    VKCMDBINDVERTEXBUFFERS2_PRE(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    VKCMDBINDVERTEXBUFFERS2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    VKCMDBINDVERTEXBUFFERS2_POST(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides)
{
    VKCMDBINDVERTEXBUFFERS2EXT_PRE(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    VKCMDBINDVERTEXBUFFERS2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    VKCMDBINDVERTEXBUFFERS2EXT_POST(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable)
{
    VKCMDSETDEPTHTESTENABLE_PRE(commandBuffer, depthTestEnable);
    VKCMDSETDEPTHTESTENABLE(commandBuffer, depthTestEnable);
    VKCMDSETDEPTHTESTENABLE_POST(commandBuffer, depthTestEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable)
{
    VKCMDSETDEPTHTESTENABLEEXT_PRE(commandBuffer, depthTestEnable);
    VKCMDSETDEPTHTESTENABLEEXT(commandBuffer, depthTestEnable);
    VKCMDSETDEPTHTESTENABLEEXT_POST(commandBuffer, depthTestEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable)
{
    VKCMDSETDEPTHWRITEENABLE_PRE(commandBuffer, depthWriteEnable);
    VKCMDSETDEPTHWRITEENABLE(commandBuffer, depthWriteEnable);
    VKCMDSETDEPTHWRITEENABLE_POST(commandBuffer, depthWriteEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable)
{
    VKCMDSETDEPTHWRITEENABLEEXT_PRE(commandBuffer, depthWriteEnable);
    VKCMDSETDEPTHWRITEENABLEEXT(commandBuffer, depthWriteEnable);
    VKCMDSETDEPTHWRITEENABLEEXT_POST(commandBuffer, depthWriteEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp)
{
    VKCMDSETDEPTHCOMPAREOP_PRE(commandBuffer, depthCompareOp);
    VKCMDSETDEPTHCOMPAREOP(commandBuffer, depthCompareOp);
    VKCMDSETDEPTHCOMPAREOP_POST(commandBuffer, depthCompareOp);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp)
{
    VKCMDSETDEPTHCOMPAREOPEXT_PRE(commandBuffer, depthCompareOp);
    VKCMDSETDEPTHCOMPAREOPEXT(commandBuffer, depthCompareOp);
    VKCMDSETDEPTHCOMPAREOPEXT_POST(commandBuffer, depthCompareOp);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable)
{
    VKCMDSETDEPTHBOUNDSTESTENABLE_PRE(commandBuffer, depthBoundsTestEnable);
    VKCMDSETDEPTHBOUNDSTESTENABLE(commandBuffer, depthBoundsTestEnable);
    VKCMDSETDEPTHBOUNDSTESTENABLE_POST(commandBuffer, depthBoundsTestEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable)
{
    VKCMDSETDEPTHBOUNDSTESTENABLEEXT_PRE(commandBuffer, depthBoundsTestEnable);
    VKCMDSETDEPTHBOUNDSTESTENABLEEXT(commandBuffer, depthBoundsTestEnable);
    VKCMDSETDEPTHBOUNDSTESTENABLEEXT_POST(commandBuffer, depthBoundsTestEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable)
{
    VKCMDSETSTENCILTESTENABLE_PRE(commandBuffer, stencilTestEnable);
    VKCMDSETSTENCILTESTENABLE(commandBuffer, stencilTestEnable);
    VKCMDSETSTENCILTESTENABLE_POST(commandBuffer, stencilTestEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable)
{
    VKCMDSETSTENCILTESTENABLEEXT_PRE(commandBuffer, stencilTestEnable);
    VKCMDSETSTENCILTESTENABLEEXT(commandBuffer, stencilTestEnable);
    VKCMDSETSTENCILTESTENABLEEXT_POST(commandBuffer, stencilTestEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp)
{
    VKCMDSETSTENCILOP_PRE(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    VKCMDSETSTENCILOP(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    VKCMDSETSTENCILOP_POST(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp)
{
    VKCMDSETSTENCILOPEXT_PRE(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    VKCMDSETSTENCILOPEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    VKCMDSETSTENCILOPEXT_POST(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints)
{
    VKCMDSETPATCHCONTROLPOINTSEXT_PRE(commandBuffer, patchControlPoints);
    VKCMDSETPATCHCONTROLPOINTSEXT(commandBuffer, patchControlPoints);
    VKCMDSETPATCHCONTROLPOINTSEXT_POST(commandBuffer, patchControlPoints);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable)
{
    VKCMDSETRASTERIZERDISCARDENABLE_PRE(commandBuffer, rasterizerDiscardEnable);
    VKCMDSETRASTERIZERDISCARDENABLE(commandBuffer, rasterizerDiscardEnable);
    VKCMDSETRASTERIZERDISCARDENABLE_POST(commandBuffer, rasterizerDiscardEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable)
{
    VKCMDSETRASTERIZERDISCARDENABLEEXT_PRE(commandBuffer, rasterizerDiscardEnable);
    VKCMDSETRASTERIZERDISCARDENABLEEXT(commandBuffer, rasterizerDiscardEnable);
    VKCMDSETRASTERIZERDISCARDENABLEEXT_POST(commandBuffer, rasterizerDiscardEnable);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable)
{
    VKCMDSETDEPTHBIASENABLE_PRE(commandBuffer, depthBiasEnable);
    VKCMDSETDEPTHBIASENABLE(commandBuffer, depthBiasEnable);
    VKCMDSETDEPTHBIASENABLE_POST(commandBuffer, depthBiasEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable)
{
    VKCMDSETDEPTHBIASENABLEEXT_PRE(commandBuffer, depthBiasEnable);
    VKCMDSETDEPTHBIASENABLEEXT(commandBuffer, depthBiasEnable);
    VKCMDSETDEPTHBIASENABLEEXT_POST(commandBuffer, depthBiasEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp)
{
    VKCMDSETLOGICOPEXT_PRE(commandBuffer, logicOp);
    VKCMDSETLOGICOPEXT(commandBuffer, logicOp);
    VKCMDSETLOGICOPEXT_POST(commandBuffer, logicOp);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable)
{
    VKCMDSETPRIMITIVERESTARTENABLE_PRE(commandBuffer, primitiveRestartEnable);
    VKCMDSETPRIMITIVERESTARTENABLE(commandBuffer, primitiveRestartEnable);
    VKCMDSETPRIMITIVERESTARTENABLE_POST(commandBuffer, primitiveRestartEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable)
{
    VKCMDSETPRIMITIVERESTARTENABLEEXT_PRE(commandBuffer, primitiveRestartEnable);
    VKCMDSETPRIMITIVERESTARTENABLEEXT(commandBuffer, primitiveRestartEnable);
    VKCMDSETPRIMITIVERESTARTENABLEEXT_POST(commandBuffer, primitiveRestartEnable);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state3) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin)
{
    VKCMDSETTESSELLATIONDOMAINORIGINEXT_PRE(commandBuffer, domainOrigin);
    VKCMDSETTESSELLATIONDOMAINORIGINEXT(commandBuffer, domainOrigin);
    VKCMDSETTESSELLATIONDOMAINORIGINEXT_POST(commandBuffer, domainOrigin);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable)
{
    VKCMDSETDEPTHCLAMPENABLEEXT_PRE(commandBuffer, depthClampEnable);
    VKCMDSETDEPTHCLAMPENABLEEXT(commandBuffer, depthClampEnable);
    VKCMDSETDEPTHCLAMPENABLEEXT_POST(commandBuffer, depthClampEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode)
{
    VKCMDSETPOLYGONMODEEXT_PRE(commandBuffer, polygonMode);
    VKCMDSETPOLYGONMODEEXT(commandBuffer, polygonMode);
    VKCMDSETPOLYGONMODEEXT_POST(commandBuffer, polygonMode);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples)
{
    VKCMDSETRASTERIZATIONSAMPLESEXT_PRE(commandBuffer, rasterizationSamples);
    VKCMDSETRASTERIZATIONSAMPLESEXT(commandBuffer, rasterizationSamples);
    VKCMDSETRASTERIZATIONSAMPLESEXT_POST(commandBuffer, rasterizationSamples);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask* pSampleMask)
{
    VKCMDSETSAMPLEMASKEXT_PRE(commandBuffer, samples, pSampleMask);
    VKCMDSETSAMPLEMASKEXT(commandBuffer, samples, pSampleMask);
    VKCMDSETSAMPLEMASKEXT_POST(commandBuffer, samples, pSampleMask);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable)
{
    VKCMDSETALPHATOCOVERAGEENABLEEXT_PRE(commandBuffer, alphaToCoverageEnable);
    VKCMDSETALPHATOCOVERAGEENABLEEXT(commandBuffer, alphaToCoverageEnable);
    VKCMDSETALPHATOCOVERAGEENABLEEXT_POST(commandBuffer, alphaToCoverageEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable)
{
    VKCMDSETALPHATOONEENABLEEXT_PRE(commandBuffer, alphaToOneEnable);
    VKCMDSETALPHATOONEENABLEEXT(commandBuffer, alphaToOneEnable);
    VKCMDSETALPHATOONEENABLEEXT_POST(commandBuffer, alphaToOneEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable)
{
    VKCMDSETLOGICOPENABLEEXT_PRE(commandBuffer, logicOpEnable);
    VKCMDSETLOGICOPENABLEEXT(commandBuffer, logicOpEnable);
    VKCMDSETLOGICOPENABLEEXT_POST(commandBuffer, logicOpEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables)
{
    VKCMDSETCOLORBLENDENABLEEXT_PRE(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
    VKCMDSETCOLORBLENDENABLEEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
    VKCMDSETCOLORBLENDENABLEEXT_POST(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations)
{
    VKCMDSETCOLORBLENDEQUATIONEXT_PRE(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
    VKCMDSETCOLORBLENDEQUATIONEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
    VKCMDSETCOLORBLENDEQUATIONEXT_POST(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks)
{
    VKCMDSETCOLORWRITEMASKEXT_PRE(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
    VKCMDSETCOLORWRITEMASKEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
    VKCMDSETCOLORWRITEMASKEXT_POST(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream)
{
    VKCMDSETRASTERIZATIONSTREAMEXT_PRE(commandBuffer, rasterizationStream);
    VKCMDSETRASTERIZATIONSTREAMEXT(commandBuffer, rasterizationStream);
    VKCMDSETRASTERIZATIONSTREAMEXT_POST(commandBuffer, rasterizationStream);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode)
{
    VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT_PRE(commandBuffer, conservativeRasterizationMode);
    VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT(commandBuffer, conservativeRasterizationMode);
    VKCMDSETCONSERVATIVERASTERIZATIONMODEEXT_POST(commandBuffer, conservativeRasterizationMode);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize)
{
    VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT_PRE(commandBuffer, extraPrimitiveOverestimationSize);
    VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT(commandBuffer, extraPrimitiveOverestimationSize);
    VKCMDSETEXTRAPRIMITIVEOVERESTIMATIONSIZEEXT_POST(commandBuffer, extraPrimitiveOverestimationSize);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable)
{
    VKCMDSETDEPTHCLIPENABLEEXT_PRE(commandBuffer, depthClipEnable);
    VKCMDSETDEPTHCLIPENABLEEXT(commandBuffer, depthClipEnable);
    VKCMDSETDEPTHCLIPENABLEEXT_POST(commandBuffer, depthClipEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable)
{
    VKCMDSETSAMPLELOCATIONSENABLEEXT_PRE(commandBuffer, sampleLocationsEnable);
    VKCMDSETSAMPLELOCATIONSENABLEEXT(commandBuffer, sampleLocationsEnable);
    VKCMDSETSAMPLELOCATIONSENABLEEXT_POST(commandBuffer, sampleLocationsEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced)
{
    VKCMDSETCOLORBLENDADVANCEDEXT_PRE(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
    VKCMDSETCOLORBLENDADVANCEDEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
    VKCMDSETCOLORBLENDADVANCEDEXT_POST(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode)
{
    VKCMDSETPROVOKINGVERTEXMODEEXT_PRE(commandBuffer, provokingVertexMode);
    VKCMDSETPROVOKINGVERTEXMODEEXT(commandBuffer, provokingVertexMode);
    VKCMDSETPROVOKINGVERTEXMODEEXT_POST(commandBuffer, provokingVertexMode);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode)
{
    VKCMDSETLINERASTERIZATIONMODEEXT_PRE(commandBuffer, lineRasterizationMode);
    VKCMDSETLINERASTERIZATIONMODEEXT(commandBuffer, lineRasterizationMode);
    VKCMDSETLINERASTERIZATIONMODEEXT_POST(commandBuffer, lineRasterizationMode);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable)
{
    VKCMDSETLINESTIPPLEENABLEEXT_PRE(commandBuffer, stippledLineEnable);
    VKCMDSETLINESTIPPLEENABLEEXT(commandBuffer, stippledLineEnable);
    VKCMDSETLINESTIPPLEENABLEEXT_POST(commandBuffer, stippledLineEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne)
{
    VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT_PRE(commandBuffer, negativeOneToOne);
    VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT(commandBuffer, negativeOneToOne);
    VKCMDSETDEPTHCLIPNEGATIVEONETOONEEXT_POST(commandBuffer, negativeOneToOne);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable)
{
    VKCMDSETVIEWPORTWSCALINGENABLENV_PRE(commandBuffer, viewportWScalingEnable);
    VKCMDSETVIEWPORTWSCALINGENABLENV(commandBuffer, viewportWScalingEnable);
    VKCMDSETVIEWPORTWSCALINGENABLENV_POST(commandBuffer, viewportWScalingEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles)
{
    VKCMDSETVIEWPORTSWIZZLENV_PRE(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
    VKCMDSETVIEWPORTSWIZZLENV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
    VKCMDSETVIEWPORTSWIZZLENV_POST(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable)
{
    VKCMDSETCOVERAGETOCOLORENABLENV_PRE(commandBuffer, coverageToColorEnable);
    VKCMDSETCOVERAGETOCOLORENABLENV(commandBuffer, coverageToColorEnable);
    VKCMDSETCOVERAGETOCOLORENABLENV_POST(commandBuffer, coverageToColorEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation)
{
    VKCMDSETCOVERAGETOCOLORLOCATIONNV_PRE(commandBuffer, coverageToColorLocation);
    VKCMDSETCOVERAGETOCOLORLOCATIONNV(commandBuffer, coverageToColorLocation);
    VKCMDSETCOVERAGETOCOLORLOCATIONNV_POST(commandBuffer, coverageToColorLocation);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode)
{
    VKCMDSETCOVERAGEMODULATIONMODENV_PRE(commandBuffer, coverageModulationMode);
    VKCMDSETCOVERAGEMODULATIONMODENV(commandBuffer, coverageModulationMode);
    VKCMDSETCOVERAGEMODULATIONMODENV_POST(commandBuffer, coverageModulationMode);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable)
{
    VKCMDSETCOVERAGEMODULATIONTABLEENABLENV_PRE(commandBuffer, coverageModulationTableEnable);
    VKCMDSETCOVERAGEMODULATIONTABLEENABLENV(commandBuffer, coverageModulationTableEnable);
    VKCMDSETCOVERAGEMODULATIONTABLEENABLENV_POST(commandBuffer, coverageModulationTableEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable)
{
    VKCMDSETCOVERAGEMODULATIONTABLENV_PRE(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
    VKCMDSETCOVERAGEMODULATIONTABLENV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
    VKCMDSETCOVERAGEMODULATIONTABLENV_POST(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable)
{
    VKCMDSETSHADINGRATEIMAGEENABLENV_PRE(commandBuffer, shadingRateImageEnable);
    VKCMDSETSHADINGRATEIMAGEENABLENV(commandBuffer, shadingRateImageEnable);
    VKCMDSETSHADINGRATEIMAGEENABLENV_POST(commandBuffer, shadingRateImageEnable);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode)
{
    VKCMDSETCOVERAGEREDUCTIONMODENV_PRE(commandBuffer, coverageReductionMode);
    VKCMDSETCOVERAGEREDUCTIONMODENV(commandBuffer, coverageReductionMode);
    VKCMDSETCOVERAGEREDUCTIONMODENV_POST(commandBuffer, coverageReductionMode);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable)
{
    VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV_PRE(commandBuffer, representativeFragmentTestEnable);
    VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV(commandBuffer, representativeFragmentTestEnable);
    VKCMDSETREPRESENTATIVEFRAGMENTTESTENABLENV_POST(commandBuffer, representativeFragmentTestEnable);
}

#endif // VK_EXT_extended_dynamic_state3 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
VKAPI_ATTR VkResult VKAPI_CALL vkCreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot)
{
    VKCREATEPRIVATEDATASLOT_PRE(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    VKCREATEPRIVATEDATASLOT(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    VKCREATEPRIVATEDATASLOT_POST(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
VKAPI_ATTR VkResult VKAPI_CALL vkCreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlotEXT* pPrivateDataSlot)
{
    VKCREATEPRIVATEDATASLOTEXT_PRE(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    VKCREATEPRIVATEDATASLOTEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    VKCREATEPRIVATEDATASLOTEXT_POST(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkDestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYPRIVATEDATASLOT_PRE(device, privateDataSlot, pAllocator);
    VKDESTROYPRIVATEDATASLOT(device, privateDataSlot, pAllocator);
    VKDESTROYPRIVATEDATASLOT_POST(device, privateDataSlot, pAllocator);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
VKAPI_ATTR void VKAPI_CALL vkDestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlotEXT privateDataSlot, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYPRIVATEDATASLOTEXT_PRE(device, privateDataSlot, pAllocator);
    VKDESTROYPRIVATEDATASLOTEXT(device, privateDataSlot, pAllocator);
    VKDESTROYPRIVATEDATASLOTEXT_POST(device, privateDataSlot, pAllocator);
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
VKAPI_ATTR VkResult VKAPI_CALL vkSetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data)
{
    VKSETPRIVATEDATA_PRE(device, objectType, objectHandle, privateDataSlot, data);
    VKSETPRIVATEDATA(device, objectType, objectHandle, privateDataSlot, data);
    VKSETPRIVATEDATA_POST(device, objectType, objectHandle, privateDataSlot, data);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
VKAPI_ATTR VkResult VKAPI_CALL vkSetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t data)
{
    VKSETPRIVATEDATAEXT_PRE(device, objectType, objectHandle, privateDataSlot, data);
    VKSETPRIVATEDATAEXT(device, objectType, objectHandle, privateDataSlot, data);
    VKSETPRIVATEDATAEXT_POST(device, objectType, objectHandle, privateDataSlot, data);
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkGetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData)
{
    VKGETPRIVATEDATA_PRE(device, objectType, objectHandle, privateDataSlot, pData);
    VKGETPRIVATEDATA(device, objectType, objectHandle, privateDataSlot, pData);
    VKGETPRIVATEDATA_POST(device, objectType, objectHandle, privateDataSlot, pData);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
VKAPI_ATTR void VKAPI_CALL vkGetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t* pData)
{
    VKGETPRIVATEDATAEXT_PRE(device, objectType, objectHandle, privateDataSlot, pData);
    VKGETPRIVATEDATAEXT(device, objectType, objectHandle, privateDataSlot, pData);
    VKGETPRIVATEDATAEXT_POST(device, objectType, objectHandle, privateDataSlot, pData);
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo)
{
    VKCMDCOPYBUFFER2_PRE(commandBuffer, pCopyBufferInfo);
    VKCMDCOPYBUFFER2(commandBuffer, pCopyBufferInfo);
    VKCMDCOPYBUFFER2_POST(commandBuffer, pCopyBufferInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2KHR* pCopyBufferInfo)
{
    VKCMDCOPYBUFFER2KHR_PRE(commandBuffer, pCopyBufferInfo);
    VKCMDCOPYBUFFER2KHR(commandBuffer, pCopyBufferInfo);
    VKCMDCOPYBUFFER2KHR_POST(commandBuffer, pCopyBufferInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo)
{
    VKCMDCOPYIMAGE2_PRE(commandBuffer, pCopyImageInfo);
    VKCMDCOPYIMAGE2(commandBuffer, pCopyImageInfo);
    VKCMDCOPYIMAGE2_POST(commandBuffer, pCopyImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2KHR* pCopyImageInfo)
{
    VKCMDCOPYIMAGE2KHR_PRE(commandBuffer, pCopyImageInfo);
    VKCMDCOPYIMAGE2KHR(commandBuffer, pCopyImageInfo);
    VKCMDCOPYIMAGE2KHR_POST(commandBuffer, pCopyImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo)
{
    VKCMDBLITIMAGE2_PRE(commandBuffer, pBlitImageInfo);
    VKCMDBLITIMAGE2(commandBuffer, pBlitImageInfo);
    VKCMDBLITIMAGE2_POST(commandBuffer, pBlitImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2KHR* pBlitImageInfo)
{
    VKCMDBLITIMAGE2KHR_PRE(commandBuffer, pBlitImageInfo);
    VKCMDBLITIMAGE2KHR(commandBuffer, pBlitImageInfo);
    VKCMDBLITIMAGE2KHR_POST(commandBuffer, pBlitImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo)
{
    VKCMDCOPYBUFFERTOIMAGE2_PRE(commandBuffer, pCopyBufferToImageInfo);
    VKCMDCOPYBUFFERTOIMAGE2(commandBuffer, pCopyBufferToImageInfo);
    VKCMDCOPYBUFFERTOIMAGE2_POST(commandBuffer, pCopyBufferToImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2KHR* pCopyBufferToImageInfo)
{
    VKCMDCOPYBUFFERTOIMAGE2KHR_PRE(commandBuffer, pCopyBufferToImageInfo);
    VKCMDCOPYBUFFERTOIMAGE2KHR(commandBuffer, pCopyBufferToImageInfo);
    VKCMDCOPYBUFFERTOIMAGE2KHR_POST(commandBuffer, pCopyBufferToImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo)
{
    VKCMDCOPYIMAGETOBUFFER2_PRE(commandBuffer, pCopyImageToBufferInfo);
    VKCMDCOPYIMAGETOBUFFER2(commandBuffer, pCopyImageToBufferInfo);
    VKCMDCOPYIMAGETOBUFFER2_POST(commandBuffer, pCopyImageToBufferInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2KHR* pCopyImageToBufferInfo)
{
    VKCMDCOPYIMAGETOBUFFER2KHR_PRE(commandBuffer, pCopyImageToBufferInfo);
    VKCMDCOPYIMAGETOBUFFER2KHR(commandBuffer, pCopyImageToBufferInfo);
    VKCMDCOPYIMAGETOBUFFER2KHR_POST(commandBuffer, pCopyImageToBufferInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo)
{
    VKCMDRESOLVEIMAGE2_PRE(commandBuffer, pResolveImageInfo);
    VKCMDRESOLVEIMAGE2(commandBuffer, pResolveImageInfo);
    VKCMDRESOLVEIMAGE2_POST(commandBuffer, pResolveImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2KHR* pResolveImageInfo)
{
    VKCMDRESOLVEIMAGE2KHR_PRE(commandBuffer, pResolveImageInfo);
    VKCMDRESOLVEIMAGE2KHR(commandBuffer, pResolveImageInfo);
    VKCMDRESOLVEIMAGE2KHR_POST(commandBuffer, pResolveImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_KHR_fragment_shading_rate)
VKAPI_ATTR void VKAPI_CALL vkCmdSetFragmentShadingRateKHR(VkCommandBuffer commandBuffer, const VkExtent2D* pFragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2])
{
    VKCMDSETFRAGMENTSHADINGRATEKHR_PRE(commandBuffer, pFragmentSize, combinerOps);
    VKCMDSETFRAGMENTSHADINGRATEKHR(commandBuffer, pFragmentSize, combinerOps);
    VKCMDSETFRAGMENTSHADINGRATEKHR_POST(commandBuffer, pFragmentSize, combinerOps);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates)
{
    VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR_PRE(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
    VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
    VKGETPHYSICALDEVICEFRAGMENTSHADINGRATESKHR_POST(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
}

#endif // VK_KHR_fragment_shading_rate

#if defined(VK_NV_fragment_shading_rate_enums)
VKAPI_ATTR void VKAPI_CALL vkCmdSetFragmentShadingRateEnumNV(VkCommandBuffer commandBuffer, VkFragmentShadingRateNV shadingRate, const VkFragmentShadingRateCombinerOpKHR combinerOps[2])
{
    VKCMDSETFRAGMENTSHADINGRATEENUMNV_PRE(commandBuffer, shadingRate, combinerOps);
    VKCMDSETFRAGMENTSHADINGRATEENUMNV(commandBuffer, shadingRate, combinerOps);
    VKCMDSETFRAGMENTSHADINGRATEENUMNV_POST(commandBuffer, shadingRate, combinerOps);
}

#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_acceleration_structure)
VKAPI_ATTR void VKAPI_CALL vkGetAccelerationStructureBuildSizesKHR(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo)
{
    VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR_PRE(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
    VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
    VKGETACCELERATIONSTRUCTUREBUILDSIZESKHR_POST(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_EXT_vertex_input_dynamic_state) || defined(VK_EXT_shader_object)
VKAPI_ATTR void VKAPI_CALL vkCmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions)
{
    VKCMDSETVERTEXINPUTEXT_PRE(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
    VKCMDSETVERTEXINPUTEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
    VKCMDSETVERTEXINPUTEXT_POST(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}

#endif // VK_EXT_vertex_input_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_color_write_enable)
VKAPI_ATTR void VKAPI_CALL vkCmdSetColorWriteEnableEXT(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkBool32* pColorWriteEnables)
{
    VKCMDSETCOLORWRITEENABLEEXT_PRE(commandBuffer, attachmentCount, pColorWriteEnables);
    VKCMDSETCOLORWRITEENABLEEXT(commandBuffer, attachmentCount, pColorWriteEnables);
    VKCMDSETCOLORWRITEENABLEEXT_POST(commandBuffer, attachmentCount, pColorWriteEnables);
}

#endif // VK_EXT_color_write_enable

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent2(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo* pDependencyInfo)
{
    VKCMDSETEVENT2_PRE(commandBuffer, event, pDependencyInfo);
    VKCMDSETEVENT2(commandBuffer, event, pDependencyInfo);
    VKCMDSETEVENT2_POST(commandBuffer, event, pDependencyInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfoKHR* pDependencyInfo)
{
    VKCMDSETEVENT2KHR_PRE(commandBuffer, event, pDependencyInfo);
    VKCMDSETEVENT2KHR(commandBuffer, event, pDependencyInfo);
    VKCMDSETEVENT2KHR_POST(commandBuffer, event, pDependencyInfo);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent2(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask)
{
    VKCMDRESETEVENT2_PRE(commandBuffer, event, stageMask);
    VKCMDRESETEVENT2(commandBuffer, event, stageMask);
    VKCMDRESETEVENT2_POST(commandBuffer, event, stageMask);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2KHR stageMask)
{
    VKCMDRESETEVENT2KHR_PRE(commandBuffer, event, stageMask);
    VKCMDRESETEVENT2KHR(commandBuffer, event, stageMask);
    VKCMDRESETEVENT2KHR_POST(commandBuffer, event, stageMask);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents2(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfo* pDependencyInfos)
{
    VKCMDWAITEVENTS2_PRE(commandBuffer, eventCount, pEvents, pDependencyInfos);
    VKCMDWAITEVENTS2(commandBuffer, eventCount, pEvents, pDependencyInfos);
    VKCMDWAITEVENTS2_POST(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents2KHR(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfoKHR* pDependencyInfos)
{
    VKCMDWAITEVENTS2KHR_PRE(commandBuffer, eventCount, pEvents, pDependencyInfos);
    VKCMDWAITEVENTS2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
    VKCMDWAITEVENTS2KHR_POST(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier2(VkCommandBuffer commandBuffer, const VkDependencyInfo* pDependencyInfo)
{
    VKCMDPIPELINEBARRIER2_PRE(commandBuffer, pDependencyInfo);
    VKCMDPIPELINEBARRIER2(commandBuffer, pDependencyInfo);
    VKCMDPIPELINEBARRIER2_POST(commandBuffer, pDependencyInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier2KHR(VkCommandBuffer commandBuffer, const VkDependencyInfoKHR* pDependencyInfo)
{
    VKCMDPIPELINEBARRIER2KHR_PRE(commandBuffer, pDependencyInfo);
    VKCMDPIPELINEBARRIER2KHR(commandBuffer, pDependencyInfo);
    VKCMDPIPELINEBARRIER2KHR_POST(commandBuffer, pDependencyInfo);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit2(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence)
{
    VKQUEUESUBMIT2_PRE(queue, submitCount, pSubmits, fence);
    VKQUEUESUBMIT2(queue, submitCount, pSubmits, fence);
    VKQUEUESUBMIT2_POST(queue, submitCount, pSubmits, fence);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit2KHR(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence)
{
    VKQUEUESUBMIT2KHR_PRE(queue, submitCount, pSubmits, fence);
    VKQUEUESUBMIT2KHR(queue, submitCount, pSubmits, fence);
    VKQUEUESUBMIT2KHR_POST(queue, submitCount, pSubmits, fence);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp2(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query)
{
    VKCMDWRITETIMESTAMP2_PRE(commandBuffer, stage, queryPool, query);
    VKCMDWRITETIMESTAMP2(commandBuffer, stage, queryPool, query);
    VKCMDWRITETIMESTAMP2_POST(commandBuffer, stage, queryPool, query);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp2KHR(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkQueryPool queryPool, uint32_t query)
{
    VKCMDWRITETIMESTAMP2KHR_PRE(commandBuffer, stage, queryPool, query);
    VKCMDWRITETIMESTAMP2KHR(commandBuffer, stage, queryPool, query);
    VKCMDWRITETIMESTAMP2KHR_POST(commandBuffer, stage, queryPool, query);
}

VKAPI_ATTR void VKAPI_CALL vkCmdWriteBufferMarker2AMD(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker)
{
    VKCMDWRITEBUFFERMARKER2AMD_PRE(commandBuffer, stage, dstBuffer, dstOffset, marker);
    VKCMDWRITEBUFFERMARKER2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker);
    VKCMDWRITEBUFFERMARKER2AMD_POST(commandBuffer, stage, dstBuffer, dstOffset, marker);
}

VKAPI_ATTR void VKAPI_CALL vkGetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData)
{
    VKGETQUEUECHECKPOINTDATA2NV_PRE(queue, pCheckpointDataCount, pCheckpointData);
    VKGETQUEUECHECKPOINTDATA2NV(queue, pCheckpointDataCount, pCheckpointData);
    VKGETQUEUECHECKPOINTDATA2NV_POST(queue, pCheckpointDataCount, pCheckpointData);
}

#endif // VK_KHR_synchronization2

#if defined(VKSC_VERSION_1_0)
VKAPI_ATTR void VKAPI_CALL vkGetCommandPoolMemoryConsumption(VkDevice device, VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkCommandPoolMemoryConsumption* pConsumption)
{
    VKGETCOMMANDPOOLMEMORYCONSUMPTION_PRE(device, commandPool, commandBuffer, pConsumption);
    VKGETCOMMANDPOOLMEMORYCONSUMPTION(device, commandPool, commandBuffer, pConsumption);
    VKGETCOMMANDPOOLMEMORYCONSUMPTION_POST(device, commandPool, commandBuffer, pConsumption);
}

#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_video_queue)
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceVideoCapabilitiesKHR(VkPhysicalDevice physicalDevice, const VkVideoProfileInfoKHR* pVideoProfile, VkVideoCapabilitiesKHR* pCapabilities)
{
    VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR_PRE(physicalDevice, pVideoProfile, pCapabilities);
    VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR(physicalDevice, pVideoProfile, pCapabilities);
    VKGETPHYSICALDEVICEVIDEOCAPABILITIESKHR_POST(physicalDevice, pVideoProfile, pCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceVideoFormatPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoFormatInfoKHR* pVideoFormatInfo, uint32_t* pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR* pVideoFormatProperties)
{
    VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR_PRE(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties);
    VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties);
    VKGETPHYSICALDEVICEVIDEOFORMATPROPERTIESKHR_POST(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession)
{
    VKCREATEVIDEOSESSIONKHR_PRE(device, pCreateInfo, pAllocator, pVideoSession);
    VKCREATEVIDEOSESSIONKHR(device, pCreateInfo, pAllocator, pVideoSession);
    VKCREATEVIDEOSESSIONKHR_POST(device, pCreateInfo, pAllocator, pVideoSession);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYVIDEOSESSIONKHR_PRE(device, videoSession, pAllocator);
    VKDESTROYVIDEOSESSIONKHR(device, videoSession, pAllocator);
    VKDESTROYVIDEOSESSIONKHR_POST(device, videoSession, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters)
{
    VKCREATEVIDEOSESSIONPARAMETERSKHR_PRE(device, pCreateInfo, pAllocator, pVideoSessionParameters);
    VKCREATEVIDEOSESSIONPARAMETERSKHR(device, pCreateInfo, pAllocator, pVideoSessionParameters);
    VKCREATEVIDEOSESSIONPARAMETERSKHR_POST(device, pCreateInfo, pAllocator, pVideoSessionParameters);
}

VKAPI_ATTR VkResult VKAPI_CALL vkUpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo)
{
    VKUPDATEVIDEOSESSIONPARAMETERSKHR_PRE(device, videoSessionParameters, pUpdateInfo);
    VKUPDATEVIDEOSESSIONPARAMETERSKHR(device, videoSessionParameters, pUpdateInfo);
    VKUPDATEVIDEOSESSIONPARAMETERSKHR_POST(device, videoSessionParameters, pUpdateInfo);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYVIDEOSESSIONPARAMETERSKHR_PRE(device, videoSessionParameters, pAllocator);
    VKDESTROYVIDEOSESSIONPARAMETERSKHR(device, videoSessionParameters, pAllocator);
    VKDESTROYVIDEOSESSIONPARAMETERSKHR_POST(device, videoSessionParameters, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements)
{
    VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR_PRE(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements);
    VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements);
    VKGETVIDEOSESSIONMEMORYREQUIREMENTSKHR_POST(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos)
{
    VKBINDVIDEOSESSIONMEMORYKHR_PRE(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos);
    VKBINDVIDEOSESSIONMEMORYKHR(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos);
    VKBINDVIDEOSESSIONMEMORYKHR_POST(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos);
}

#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
VKAPI_ATTR void VKAPI_CALL vkCmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo)
{
    VKCMDDECODEVIDEOKHR_PRE(commandBuffer, pDecodeInfo);
    VKCMDDECODEVIDEOKHR(commandBuffer, pDecodeInfo);
    VKCMDDECODEVIDEOKHR_POST(commandBuffer, pDecodeInfo);
}

#endif // VK_KHR_video_decode_queue

#if defined(VK_KHR_video_queue)
VKAPI_ATTR void VKAPI_CALL vkCmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo)
{
    VKCMDBEGINVIDEOCODINGKHR_PRE(commandBuffer, pBeginInfo);
    VKCMDBEGINVIDEOCODINGKHR(commandBuffer, pBeginInfo);
    VKCMDBEGINVIDEOCODINGKHR_POST(commandBuffer, pBeginInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo)
{
    VKCMDCONTROLVIDEOCODINGKHR_PRE(commandBuffer, pCodingControlInfo);
    VKCMDCONTROLVIDEOCODINGKHR(commandBuffer, pCodingControlInfo);
    VKCMDCONTROLVIDEOCODINGKHR_POST(commandBuffer, pCodingControlInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo)
{
    VKCMDENDVIDEOCODINGKHR_PRE(commandBuffer, pEndCodingInfo);
    VKCMDENDVIDEOCODINGKHR(commandBuffer, pEndCodingInfo);
    VKCMDENDVIDEOCODINGKHR_POST(commandBuffer, pEndCodingInfo);
}

#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_encode_queue)
VKAPI_ATTR void VKAPI_CALL vkCmdEncodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo)
{
    VKCMDENCODEVIDEOKHR_PRE(commandBuffer, pEncodeInfo);
    VKCMDENCODEVIDEOKHR(commandBuffer, pEncodeInfo);
    VKCMDENCODEVIDEOKHR_POST(commandBuffer, pEncodeInfo);
}

#endif // VK_KHR_video_encode_queue

#if defined(VK_NV_memory_decompression)
VKAPI_ATTR void VKAPI_CALL vkCmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions)
{
    VKCMDDECOMPRESSMEMORYNV_PRE(commandBuffer, decompressRegionCount, pDecompressMemoryRegions);
    VKCMDDECOMPRESSMEMORYNV(commandBuffer, decompressRegionCount, pDecompressMemoryRegions);
    VKCMDDECOMPRESSMEMORYNV_POST(commandBuffer, decompressRegionCount, pDecompressMemoryRegions);
}

VKAPI_ATTR void VKAPI_CALL vkCmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride)
{
    VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV_PRE(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride);
    VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride);
    VKCMDDECOMPRESSMEMORYINDIRECTCOUNTNV_POST(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride);
}

#endif // VK_NV_memory_decompression

#if defined(VK_NVX_binary_import)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule)
{
    VKCREATECUMODULENVX_PRE(device, pCreateInfo, pAllocator, pModule);
    VKCREATECUMODULENVX(device, pCreateInfo, pAllocator, pModule);
    VKCREATECUMODULENVX_POST(device, pCreateInfo, pAllocator, pModule);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction)
{
    VKCREATECUFUNCTIONNVX_PRE(device, pCreateInfo, pAllocator, pFunction);
    VKCREATECUFUNCTIONNVX(device, pCreateInfo, pAllocator, pFunction);
    VKCREATECUFUNCTIONNVX_POST(device, pCreateInfo, pAllocator, pFunction);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYCUMODULENVX_PRE(device, module, pAllocator);
    VKDESTROYCUMODULENVX(device, module, pAllocator);
    VKDESTROYCUMODULENVX_POST(device, module, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYCUFUNCTIONNVX_PRE(device, function, pAllocator);
    VKDESTROYCUFUNCTIONNVX(device, function, pAllocator);
    VKDESTROYCUFUNCTIONNVX_POST(device, function, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo)
{
    VKCMDCULAUNCHKERNELNVX_PRE(commandBuffer, pLaunchInfo);
    VKCMDCULAUNCHKERNELNVX(commandBuffer, pLaunchInfo);
    VKCMDCULAUNCHKERNELNVX_POST(commandBuffer, pLaunchInfo);
}

#endif // VK_NVX_binary_import

#if defined(VK_EXT_descriptor_buffer)
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes)
{
    VKGETDESCRIPTORSETLAYOUTSIZEEXT_PRE(device, layout, pLayoutSizeInBytes);
    VKGETDESCRIPTORSETLAYOUTSIZEEXT(device, layout, pLayoutSizeInBytes);
    VKGETDESCRIPTORSETLAYOUTSIZEEXT_POST(device, layout, pLayoutSizeInBytes);
}

VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset)
{
    VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT_PRE(device, layout, binding, pOffset);
    VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT(device, layout, binding, pOffset);
    VKGETDESCRIPTORSETLAYOUTBINDINGOFFSETEXT_POST(device, layout, binding, pOffset);
}

VKAPI_ATTR void VKAPI_CALL vkGetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor)
{
    VKGETDESCRIPTOREXT_PRE(device, pDescriptorInfo, dataSize, pDescriptor);
    VKGETDESCRIPTOREXT(device, pDescriptorInfo, dataSize, pDescriptor);
    VKGETDESCRIPTOREXT_POST(device, pDescriptorInfo, dataSize, pDescriptor);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos)
{
    VKCMDBINDDESCRIPTORBUFFERSEXT_PRE(commandBuffer, bufferCount, pBindingInfos);
    VKCMDBINDDESCRIPTORBUFFERSEXT(commandBuffer, bufferCount, pBindingInfos);
    VKCMDBINDDESCRIPTORBUFFERSEXT_POST(commandBuffer, bufferCount, pBindingInfos);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets)
{
    VKCMDSETDESCRIPTORBUFFEROFFSETSEXT_PRE(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
    VKCMDSETDESCRIPTORBUFFEROFFSETSEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
    VKCMDSETDESCRIPTORBUFFEROFFSETSEXT_POST(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set)
{
    VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT_PRE(commandBuffer, pipelineBindPoint, layout, set);
    VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT(commandBuffer, pipelineBindPoint, layout, set);
    VKCMDBINDDESCRIPTORBUFFEREMBEDDEDSAMPLERSEXT_POST(commandBuffer, pipelineBindPoint, layout, set);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT_PRE(device, pInfo, pData);
    VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData);
    VKGETBUFFEROPAQUECAPTUREDESCRIPTORDATAEXT_POST(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT_PRE(device, pInfo, pData);
    VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData);
    VKGETIMAGEOPAQUECAPTUREDESCRIPTORDATAEXT_POST(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT_PRE(device, pInfo, pData);
    VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData);
    VKGETIMAGEVIEWOPAQUECAPTUREDESCRIPTORDATAEXT_POST(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT_PRE(device, pInfo, pData);
    VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData);
    VKGETSAMPLEROPAQUECAPTUREDESCRIPTORDATAEXT_POST(device, pInfo, pData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT_PRE(device, pInfo, pData);
    VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT(device, pInfo, pData);
    VKGETACCELERATIONSTRUCTUREOPAQUECAPTUREDESCRIPTORDATAEXT_POST(device, pInfo, pData);
}

#endif // VK_EXT_descriptor_buffer

#if defined(VK_EXT_pageable_device_local_memory)
VKAPI_ATTR void VKAPI_CALL vkSetDeviceMemoryPriorityEXT(VkDevice device, VkDeviceMemory memory, float priority)
{
    VKSETDEVICEMEMORYPRIORITYEXT_PRE(device, memory, priority);
    VKSETDEVICEMEMORYPRIORITYEXT(device, memory, priority);
    VKSETDEVICEMEMORYPRIORITYEXT_POST(device, memory, priority);
}

#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_present_wait)
VKAPI_ATTR VkResult VKAPI_CALL vkWaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout)
{
    VKWAITFORPRESENTKHR_PRE(device, swapchain, presentId, timeout);
    VKWAITFORPRESENTKHR(device, swapchain, presentId, timeout);
    VKWAITFORPRESENTKHR_POST(device, swapchain, presentId, timeout);
}

#endif // VK_KHR_present_wait

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdBeginRendering(VkCommandBuffer commandBuffer, const VkRenderingInfo* pRenderingInfo)
{
    VKCMDBEGINRENDERING_PRE(commandBuffer, pRenderingInfo);
    VKCMDBEGINRENDERING(commandBuffer, pRenderingInfo);
    VKCMDBEGINRENDERING_POST(commandBuffer, pRenderingInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderingKHR(VkCommandBuffer commandBuffer, const VkRenderingInfoKHR* pRenderingInfo)
{
    VKCMDBEGINRENDERINGKHR_PRE(commandBuffer, pRenderingInfo);
    VKCMDBEGINRENDERINGKHR(commandBuffer, pRenderingInfo);
    VKCMDBEGINRENDERINGKHR_POST(commandBuffer, pRenderingInfo);
}

#endif // VK_KHR_dynamic_rendering

#if defined(VK_VERSION_1_3)
VKAPI_ATTR void VKAPI_CALL vkCmdEndRendering(VkCommandBuffer commandBuffer)
{
    VKCMDENDRENDERING_PRE(commandBuffer);
    VKCMDENDRENDERING(commandBuffer);
    VKCMDENDRENDERING_POST(commandBuffer);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderingKHR(VkCommandBuffer commandBuffer)
{
    VKCMDENDRENDERINGKHR_PRE(commandBuffer);
    VKCMDENDRENDERINGKHR(commandBuffer);
    VKCMDENDRENDERINGKHR_POST(commandBuffer);
}

#endif // VK_KHR_dynamic_rendering

#if defined(VK_EXT_opacity_micromap)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMicromapEXT(VkDevice device, const VkMicromapCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkMicromapEXT* pMicromap)
{
    VKCREATEMICROMAPEXT_PRE(device, pCreateInfo, pAllocator, pMicromap);
    VKCREATEMICROMAPEXT(device, pCreateInfo, pAllocator, pMicromap);
    VKCREATEMICROMAPEXT_POST(device, pCreateInfo, pAllocator, pMicromap);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBuildMicromapsEXT(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos)
{
    VKCMDBUILDMICROMAPSEXT_PRE(commandBuffer, infoCount, pInfos);
    VKCMDBUILDMICROMAPSEXT(commandBuffer, infoCount, pInfos);
    VKCMDBUILDMICROMAPSEXT_POST(commandBuffer, infoCount, pInfos);
}

VKAPI_ATTR VkResult VKAPI_CALL vkBuildMicromapsEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos)
{
    VKBUILDMICROMAPSEXT_PRE(device, deferredOperation, infoCount, pInfos);
    VKBUILDMICROMAPSEXT(device, deferredOperation, infoCount, pInfos);
    VKBUILDMICROMAPSEXT_POST(device, deferredOperation, infoCount, pInfos);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYMICROMAPEXT_PRE(device, micromap, pAllocator);
    VKDESTROYMICROMAPEXT(device, micromap, pAllocator);
    VKDESTROYMICROMAPEXT_POST(device, micromap, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo)
{
    VKCMDCOPYMICROMAPEXT_PRE(commandBuffer, pInfo);
    VKCMDCOPYMICROMAPEXT(commandBuffer, pInfo);
    VKCMDCOPYMICROMAPEXT_POST(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo)
{
    VKCOPYMICROMAPEXT_PRE(device, deferredOperation, pInfo);
    VKCOPYMICROMAPEXT(device, deferredOperation, pInfo);
    VKCOPYMICROMAPEXT_POST(device, deferredOperation, pInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo)
{
    VKCMDCOPYMICROMAPTOMEMORYEXT_PRE(commandBuffer, pInfo);
    VKCMDCOPYMICROMAPTOMEMORYEXT(commandBuffer, pInfo);
    VKCMDCOPYMICROMAPTOMEMORYEXT_POST(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo)
{
    VKCOPYMICROMAPTOMEMORYEXT_PRE(device, deferredOperation, pInfo);
    VKCOPYMICROMAPTOMEMORYEXT(device, deferredOperation, pInfo);
    VKCOPYMICROMAPTOMEMORYEXT_POST(device, deferredOperation, pInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo)
{
    VKCMDCOPYMEMORYTOMICROMAPEXT_PRE(commandBuffer, pInfo);
    VKCMDCOPYMEMORYTOMICROMAPEXT(commandBuffer, pInfo);
    VKCMDCOPYMEMORYTOMICROMAPEXT_POST(commandBuffer, pInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo)
{
    VKCOPYMEMORYTOMICROMAPEXT_PRE(device, deferredOperation, pInfo);
    VKCOPYMEMORYTOMICROMAPEXT(device, deferredOperation, pInfo);
    VKCOPYMEMORYTOMICROMAPEXT_POST(device, deferredOperation, pInfo);
}

VKAPI_ATTR void VKAPI_CALL vkCmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery)
{
    VKCMDWRITEMICROMAPSPROPERTIESEXT_PRE(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
    VKCMDWRITEMICROMAPSPROPERTIESEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
    VKCMDWRITEMICROMAPSPROPERTIESEXT_POST(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
}

VKAPI_ATTR VkResult VKAPI_CALL vkWriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, size_t dataSize, void* pData, size_t stride)
{
    VKWRITEMICROMAPSPROPERTIESEXT_PRE(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
    VKWRITEMICROMAPSPROPERTIESEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
    VKWRITEMICROMAPSPROPERTIESEXT_POST(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility)
{
    VKGETDEVICEMICROMAPCOMPATIBILITYEXT_PRE(device, pVersionInfo, pCompatibility);
    VKGETDEVICEMICROMAPCOMPATIBILITYEXT(device, pVersionInfo, pCompatibility);
    VKGETDEVICEMICROMAPCOMPATIBILITYEXT_POST(device, pVersionInfo, pCompatibility);
}

VKAPI_ATTR void VKAPI_CALL vkGetMicromapBuildSizesEXT(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapBuildSizesInfoEXT* pSizeInfo)
{
    VKGETMICROMAPBUILDSIZESEXT_PRE(device, buildType, pBuildInfo, pSizeInfo);
    VKGETMICROMAPBUILDSIZESEXT(device, buildType, pBuildInfo, pSizeInfo);
    VKGETMICROMAPBUILDSIZESEXT_POST(device, buildType, pBuildInfo, pSizeInfo);
}

#endif // VK_EXT_opacity_micromap

#if defined(VK_EXT_shader_module_identifier)
VKAPI_ATTR void VKAPI_CALL vkGetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier)
{
    VKGETSHADERMODULEIDENTIFIEREXT_PRE(device, shaderModule, pIdentifier);
    VKGETSHADERMODULEIDENTIFIEREXT(device, shaderModule, pIdentifier);
    VKGETSHADERMODULEIDENTIFIEREXT_POST(device, shaderModule, pIdentifier);
}

VKAPI_ATTR void VKAPI_CALL vkGetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier)
{
    VKGETSHADERMODULECREATEINFOIDENTIFIEREXT_PRE(device, pCreateInfo, pIdentifier);
    VKGETSHADERMODULECREATEINFOIDENTIFIEREXT(device, pCreateInfo, pIdentifier);
    VKGETSHADERMODULECREATEINFOIDENTIFIEREXT_POST(device, pCreateInfo, pIdentifier);
}

#endif // VK_EXT_shader_module_identifier

#if defined(VK_EXT_image_compression_control)
VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout)
{
    VKGETIMAGESUBRESOURCELAYOUT2EXT_PRE(device, image, pSubresource, pLayout);
    VKGETIMAGESUBRESOURCELAYOUT2EXT(device, image, pSubresource, pLayout);
    VKGETIMAGESUBRESOURCELAYOUT2EXT_POST(device, image, pSubresource, pLayout);
}

#endif // VK_EXT_image_compression_control

#if defined(VK_EXT_device_fault)
VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo)
{
    VKGETDEVICEFAULTINFOEXT_PRE(device, pFaultCounts, pFaultInfo);
    VKGETDEVICEFAULTINFOEXT(device, pFaultCounts, pFaultInfo);
    VKGETDEVICEFAULTINFOEXT_POST(device, pFaultCounts, pFaultInfo);
}

#endif // VK_EXT_device_fault

#if defined(VK_EXT_swapchain_maintenance1)
VKAPI_ATTR VkResult VKAPI_CALL vkReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo)
{
    VKRELEASESWAPCHAINIMAGESEXT_PRE(device, pReleaseInfo);
    VKRELEASESWAPCHAINIMAGESEXT(device, pReleaseInfo);
    VKRELEASESWAPCHAINIMAGESEXT_POST(device, pReleaseInfo);
}

#endif // VK_EXT_swapchain_maintenance1

#if defined(VK_KHR_map_memory2)
VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData)
{
    VKMAPMEMORY2KHR_PRE(device, pMemoryMapInfo, ppData);
    VKMAPMEMORY2KHR(device, pMemoryMapInfo, ppData);
    VKMAPMEMORY2KHR_POST(device, pMemoryMapInfo, ppData);
}

VKAPI_ATTR VkResult VKAPI_CALL vkUnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo)
{
    VKUNMAPMEMORY2KHR_PRE(device, pMemoryUnmapInfo);
    VKUNMAPMEMORY2KHR(device, pMemoryUnmapInfo);
    VKUNMAPMEMORY2KHR_POST(device, pMemoryUnmapInfo);
}

#endif // VK_KHR_map_memory2

#if defined(VK_EXT_shader_object)
VKAPI_ATTR VkResult VKAPI_CALL vkCreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders)
{
    VKCREATESHADERSEXT_PRE(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
    VKCREATESHADERSEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
    VKCREATESHADERSEXT_POST(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator)
{
    VKDESTROYSHADEREXT_PRE(device, shader, pAllocator);
    VKDESTROYSHADEREXT(device, shader, pAllocator);
    VKDESTROYSHADEREXT_POST(device, shader, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData)
{
    VKGETSHADERBINARYDATAEXT_PRE(device, shader, pDataSize, pData);
    VKGETSHADERBINARYDATAEXT(device, shader, pDataSize, pData);
    VKGETSHADERBINARYDATAEXT_POST(device, shader, pDataSize, pData);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders)
{
    VKCMDBINDSHADERSEXT_PRE(commandBuffer, stageCount, pStages, pShaders);
    VKCMDBINDSHADERSEXT(commandBuffer, stageCount, pStages, pShaders);
    VKCMDBINDSHADERSEXT_POST(commandBuffer, stageCount, pStages, pShaders);
}

#endif // VK_EXT_shader_object

#if defined(VK_NV_external_memory_sci_buf)
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemorySciBufNV(VkDevice device, const VkMemoryGetSciBufInfoNV* pGetSciBufInfo, NvSciBufObj* pHandle)
{
    VKGETMEMORYSCIBUFNV_PRE(device, pGetSciBufInfo, pHandle);
    VKGETMEMORYSCIBUFNV(device, pGetSciBufInfo, pHandle);
    VKGETMEMORYSCIBUFNV_POST(device, pGetSciBufInfo, pHandle);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV(VkPhysicalDevice physicalDevice, VkExternalMemoryHandleTypeFlagBits handleType, NvSciBufObj handle, VkMemorySciBufPropertiesNV* pMemorySciBufProperties)
{
    VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV_PRE(physicalDevice, handleType, handle, pMemorySciBufProperties);
    VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV(physicalDevice, handleType, handle, pMemorySciBufProperties);
    VKGETPHYSICALDEVICEEXTERNALMEMORYSCIBUFPROPERTIESNV_POST(physicalDevice, handleType, handle, pMemorySciBufProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSciBufAttributesNV(VkPhysicalDevice physicalDevice, NvSciBufAttrList pAttributes)
{
    VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV_PRE(physicalDevice, pAttributes);
    VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV(physicalDevice, pAttributes);
    VKGETPHYSICALDEVICESCIBUFATTRIBUTESNV_POST(physicalDevice, pAttributes);
}

#endif // VK_NV_external_memory_sci_buf

//------------------------------------------------------------------------------------------------
// Hand Edits
//------------------------------------------------------------------------------------------------
bool Has_vkEnumerateInstanceVersion()
{
    return s_vkEnumerateInstanceVersion != nullptr;
}