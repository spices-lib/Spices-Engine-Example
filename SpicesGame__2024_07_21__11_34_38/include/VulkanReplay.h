//---------------------------------------------------------------------------
// File: Resources\VulkanReplay.h
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#pragma once

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

#include "CommonReplay.h"
#include "ReadOnlyDatabase.h"

#include <functional>

#if !defined(VK_KHR_video_queue)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkVideoSessionKHR);
struct VkBindVideoSessionMemoryInfoKHR;
#endif

#if !defined(VK_NV_ray_tracing)
struct VkBindAccelerationStructureMemoryInfoNV;
#endif

//------------------------------------------------------------------------------
// Vulkan Helpers
//------------------------------------------------------------------------------

typedef void (*PFN_RecordCommandBuffer)(VkCommandBuffer);

enum VulkanHelper_PopulateImageFlags
{
    NV_VK_IMAGE_INITIALIZED_IN_FRAME = 1 << 0,
    NV_VK_IMAGE_SWAPCHAIN = 1 << 1,
};

struct VulkanHelper_InitializeDeviceMemoryInfo
{
    uint32_t version;
    VkDeviceAddress address = 0;
    uint32_t bufferBindCount = 0;
    const VkBindBufferMemoryInfo* pBindBufferMemoryInfo = nullptr;
    uint32_t imageBindCount = 0;
    const VkBindImageMemoryInfo* pBindImageMemoryInfo = nullptr;
    uint32_t accelerationStructureBindCount = 0;
    const VkBindAccelerationStructureMemoryInfoNV* pBindAccelerationStructureMemoryInfoNV = nullptr;
    uint32_t videoBindMemoryCount = 0;
    const VkVideoSessionKHR* pVideoSessions = nullptr;
    const VkBindVideoSessionMemoryInfoKHR* pVideoBindMemory = nullptr;
    VkBool32 injectedCaptureReplay = VK_FALSE;
};

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
// NV_ray_tracing control
struct VulkanHelper_GeometryDataNV
{
    VkDeviceSize vertexBufferSize;
    VkDeviceSize unpackedVertexStride;
    VkDeviceSize packedVertexStride;
    const uint8_t* pVertexBufferData;
    VkDeviceSize indexBufferSize;
    const uint8_t* pIndexBufferData;
    VkDeviceSize transformBufferSize;
    const uint8_t* pTransformBufferData;
};

// KHR_acceleration_structure control
struct VulkanHelper_InitializeAccelerationStructureInfoKHR
{
    uint32_t version;
    VkAccelerationStructureTypeKHR type;
    VkBuildAccelerationStructureFlagsKHR flags;
    VkBuildAccelerationStructureModeKHR mode;
    VkBool32 hasHostGeometryData;
    VkBool32 hasHostTransformData;
    VkBool32 hasHostInstanceData;
    VkBool32 isCompacted;
};

struct VulkanHelper_ShaderBindTableEntry
{
    uint32_t version;
    VkPipeline pipeline;
    uint32_t group;
    VkDeviceSize inlineDataSize;
    const uint8_t* pInlineData;
};

struct VulkanHelper_ShaderBindTable
{
    uint32_t version;
    uint32_t entryCount;
    const VulkanHelper_ShaderBindTableEntry* pEntries;
};

struct VulkanHelper_AccelerationStructureInstance
{
    uint32_t version;
    const float* pTransform;
    uint32_t instanceCustomIndex;
    uint32_t mask;
    uint32_t instanceShaderBindingTableRecordOffset;
    VkGeometryInstanceFlagsKHR flags;
    VkAccelerationStructureKHR accelerationStructure;
};

struct VulkanHelper_AccelerationStructureMotionInstance
{
    uint32_t version;
    VkAccelerationStructureMotionInstanceTypeNV type;
    const float* pTransformT0;
    const float* pTransformT1;
    uint32_t instanceCustomIndex;
    uint32_t mask;
    uint32_t instanceShaderBindingTableRecordOffset;
    VkGeometryInstanceFlagsKHR flags;
    VkAccelerationStructureKHR accelerationStructure;
};
#endif

struct VulkanHelper_CallingContext
{
    unsigned int structSize;
    const char* pFile;
    int line;
};

NV_REPLAY_EXPORT VkResult VulkanHelper_InitBegin(VkInstance instance);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitEnd(VkInstance instace);
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetInstanceState(VkInstance instance);
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetInstanceResourcesBegin(VkInstance instance);
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetInstanceResourcesEnd(VkInstance instance);
NV_REPLAY_EXPORT VkResult VulkanHelper_ExecuteCommands(VkDevice device, VkQueueFlags queueFlags, std::function<void(VkCommandBuffer)>&& fnWork);
NV_REPLAY_EXPORT VkResult VulkanHelper_ExecuteCommands(VkDevice device, uint32_t deviceMask, VkQueueFlags queueFlags, std::function<void(VkCommandBuffer)>&& fnWork);
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateImageMemoryRequirements(VkDevice device, VkImage image, const VkMemoryRequirements* pMemoryRequirement);
#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateSparseImageMemoryRequirements(VkDevice device, VkImage image, uint32_t sparseImageMemoryRequirementCount, const VkSparseImageMemoryRequirements* pSparseImageMemoryRequirement);
#endif
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateBufferMemoryRequirements(VkDevice device, VkBuffer buffer, const VkMemoryRequirements* pMemoryRequirement);
NV_REPLAY_EXPORT VkResult VulkanHelper_GetCompatiblePhysicalDevice(VkInstance instance, uint32_t deviceIdx, const VkPhysicalDeviceProperties& physicalDeviceProperties, uint32_t queueFamilyCount, const VkQueueFamilyProperties* pQueueFamilyProperties, const VkPhysicalDeviceMemoryProperties& memoryProperties, VkPhysicalDevice* pPhysicalDevice);
NV_REPLAY_EXPORT VkResult VulkanHelper_GetCompatibleDisplay(VkPhysicalDevice physicalDevice, const VkDisplayPropertiesKHR& matchProperty, VkDisplayKHR* pDisplay);
NV_REPLAY_EXPORT VkResult VulkanHelper_GetCompatibleDisplayMode(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModePropertiesKHR& matchProperty, VkDisplayModeKHR* pDisplayMode);
#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateAccelerationStructureNV(VkDevice device, VkAccelerationStructureCreateInfoNV* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkAccelerationStructureNV* pAccelerationStructure);
NV_REPLAY_EXPORT VkResult VulkanHelper_AllocateAndInitializeMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, VkDeviceAddress address, uint32_t bufferBindCount, const VkBindBufferMemoryInfo* pBindBufferMemoryInfo, uint32_t imageBindCount, const VkBindImageMemoryInfo* pBindImageMemoryInfo, uint32_t accelerationStructureBindCount, const VkBindAccelerationStructureMemoryInfoNV* pBindAccelerationStructureMemoryInfoNV, VkDeviceMemory* pDeviceMemory);
NV_REPLAY_EXPORT VkResult VulkanHelper_AllocateAndInitializeMemory2(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, VkDeviceAddress address, uint32_t bufferBindCount, const VkBindBufferMemoryInfo* pBindBufferMemoryInfo, uint32_t imageBindCount, const VkBindImageMemoryInfo* pBindImageMemoryInfo, uint32_t accelerationStructureBindCount, const VkBindAccelerationStructureMemoryInfoNV* pBindAccelerationStructureMemoryInfoNV, VkDeviceMemory* pDeviceMemory, const uint8_t* pData);
#endif
NV_REPLAY_EXPORT VkResult VulkanHelper_AllocateAndInitializeMemory3(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VulkanHelper_InitializeDeviceMemoryInfo* pInitializeInfo, VkDeviceMemory* pDeviceMemory, const uint8_t* pData);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateBuffer(VkDevice device, VkBufferCreateInfo* pCreateInfo, VkDeviceAddress address, VkBuffer* pBuffer);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateBuffer2(VkDevice device, VkBufferCreateInfo* pCreateInfo, const VkMemoryRequirements* pRequirements, const VkDeviceAddress address, VkDeviceAddress opaqueCaptureAddress, VkBuffer* pBuffer);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateBuffer3(VkDevice device, VkBufferCreateInfo* pCreateInfo, const VkMemoryRequirements* pRequirements, const VkDeviceAddress address, VkDeviceAddress opaqueCaptureAddress, size_t opaqueHandleSize, const void* pOpaqueHandle, VkBuffer* pBuffer);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateSampler(VkDevice device, VkSamplerCreateInfo* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkSampler* pSampler);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateImage(VkDevice device, VkImageCreateInfo* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkImage* pImage);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateImageView(VkDevice device, VkImageViewCreateInfo* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkImageView* pImageView);
#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateAccelerationStructureKHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateAccelerationStructure2KHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure, VkBool32 isCompacted);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateAccelerationStructure3KHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure, VkBool32 isCompacted, const VkAccelerationStructureBuildSizesInfoKHR* pCaptureSizeInfo);
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateAccelerationStructure4KHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure, VkBool32 isCompacted, const VkAccelerationStructureBuildSizesInfoKHR* pCaptureSizeInfo, size_t opaqueHandleSize, const void* pOpaqueHandle);
#endif
#if defined(VK_EXT_opacity_micromap)
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateMicromapEXT(VkDevice device, VkMicromapCreateInfoEXT* pCreateInfo, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapEXT* pMicromapEXT, VkBool32 isCompacted, const VkMicromapBuildSizesInfoEXT* pCaptureSizeInfo);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeMicromapEXT(VkDevice device, VkMicromapEXT micromapEXT, const VkMicromapBuildInfoEXT* pBuildInfo, VkDeviceSize dataSize, VkDeviceSize triangleArraySize, VkBool32 isCompacted);
#endif
#if defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanSCHelper_CreateGraphicsPipeline(VkDevice device, const VkGraphicsPipelineCreateInfo* pCreateInfo, size_t size, const void* pData, VkPipeline* pPipeline);
NV_REPLAY_EXPORT VkResult VulkanSCHelper_CreateComputePipeline(VkDevice device, const VkComputePipelineCreateInfo* pCreateInfo, size_t size, const void* pData, VkPipeline* pPipeline);
#endif
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateBuffer(VkDevice device, uint32_t deviceMask, VkBuffer buffer, VkDeviceMemory memory, VkMemoryPropertyFlags memoryFlags, VkDeviceSize offset, VkDeviceSize size, const uint32_t* pBufferData);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateBuffer2(VkDevice device, uint32_t deviceMask, VkBuffer buffer, VkDeviceSize size, const uint32_t* pBufferData);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateBuffer3(VkDevice device, uint32_t deviceMask, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const uint32_t* pBufferData);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateImage(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, VkImageLayout layout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateImage2(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, VkImageLayout layout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData, const VkClearValue* pClearValue);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateImage3(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, uint32_t layoutCount, const VkImageLayout* pLayout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData, const VkClearValue* pClearValue);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateImage4(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, uint32_t layoutCount, const VkImageLayout* pOldLayouts, const VkImageLayout* pNewLayouts, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData, const VkClearValue* pClearValue);
NV_REPLAY_EXPORT VkResult VulkanHelper_PopulateSwapchainImage(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, VkImageLayout layout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData);
NV_REPLAY_EXPORT VkResult VulkanHelper_TransitionImageLayout(VkDevice device, VkImage image, uint32_t layoutCount, const VkImageLayout* pOldLayouts, const VkImageLayout* pNewLayouts, VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, uint32_t rangeCount, const VkImageSubresourceRange* pRanges);
NV_REPLAY_EXPORT VkResult VulkanHelper_UpdateMappedMemory(VkDevice device, VkDeviceMemory memory, void* pMappedPtr, VkDeviceSize offset, VkDeviceSize size, const uint8_t* pData);
NV_REPLAY_EXPORT VkResult VulkanHelper_UpdateMappedMemory2(VkDevice device, VkDeviceMemory memory, void* pMappedPtr, VkDeviceSize offset, VkDeviceSize size, const uint8_t* pData, uint32_t bufferInfoCount, const VkDescriptorBufferInfo* pBufferInfo);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeDescriptorSet(VkDevice device, VkDescriptorSet set, VkDescriptorPool pool, VkDescriptorSetLayout layout, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeCommandBuffer(VkDevice device, VkCommandBuffer commandBuffer, const VkCommandBufferAllocateInfo* pAllocateInfo, PFN_RecordCommandBuffer pFnRecordCommandBuffer);
NV_REPLAY_EXPORT VkResult VulkanHelper_RecordCommandBuffer(VkDevice device, VkCommandBuffer commandBuffer, uint32_t revision, PFN_RecordCommandBuffer pFnRecordCommandBuffer);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeSwapchain(VkDevice device, VkSwapchainKHR swapchain, uint32_t acquiredImageCount);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeQueryPool(VkDevice device, VkQueryPool queryPool);
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetQueryPool(VkDevice device, VkQueryPool queryPool);
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetDeviceMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize offset, VkDeviceSize size, const void* pData);
#if defined(VK_NV_ray_tracing) || defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateAccelerationStructureMemoryRequirementsNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkMemoryRequirements2* pVkMemoryRequirements2);
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateAccelerationStructureMemoryRequirementsKHR(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkMemoryRequirements2* pCaptureMemoryRequirements2);
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateAccelerationStructureScratchMemoryRequirementsNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkMemoryRequirements2* pVkMemoryRequirements2);
#endif
#if defined(VK_KHR_video_queue)
NV_REPLAY_EXPORT VkResult VulkanHelper_ValidateVideoSessionMemoryRequirements(VkDevice device, VkVideoSessionKHR videoSession, uint32_t captureMemoryRequirementsCount, const VkVideoSessionMemoryRequirementsKHR* pCaptureMemoryProperties);
#endif
#if defined(VK_NV_ray_tracing) || defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeAccelerationStructureNV(VkDevice device, const VkAccelerationStructureInfoNV* pInfo, const void* pInstanceData, const VulkanHelper_GeometryDataNV* pGeometryDataNV, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VulkanHelper_InitializeAccelerationStructureInfoKHR* pInitializationInfo, uint32_t geometryCount, const VkAccelerationStructureGeometryKHR* pGeometry, const VkAccelerationStructureBuildRangeInfoKHR* pRangeInfo);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeAccelerationStructureNV2(VkDevice device, const VkAccelerationStructureInfoNV* pInfo, const void* pInstanceData, const VulkanHelper_GeometryDataNV* pGeometryDataNV, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBool32 supportUpdates);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VulkanHelper_InitializeAccelerationStructureInfoKHR* pInitializationInfo, uint32_t geometryCount, const VkAccelerationStructureGeometryKHR* pGeometry, const VkAccelerationStructureBuildRangeInfoKHR* pRangeInfo, VkBool32 supportUpdates);
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeSerializedAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, VkDeviceSize size, const void* pData);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, uint64_t handle);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterAccelerationStructureAddressKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, VkDeviceAddress address);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterRaytracingShaderGroupHandleNV(VkDevice device, VkPipeline pipeline, uint32_t groupNumber, const uint64_t* pHandle);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterRaytracingShaderGroupHandleNV(VkDevice device, VkPipeline pipeline, uint32_t groupNumber, uint32_t shaderGroupHandleSize, const uint8_t* pHandle);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice device, VkPipeline pipeline, uint32_t groupNumber, uint32_t shaderGroupHandleSize, const uint8_t* pHandle);
#endif
#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeSparseBindings(VkDevice device, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo);
#endif
#if defined(VK_KHR_timeline_semaphore)
NV_REPLAY_EXPORT VkResult VulkanHelper_InitializeTimelineSemaphore(VkDevice device, VkSemaphore semaphore, uint64_t startValue, uint64_t endValue);
#endif
NV_REPLAY_EXPORT VkResult VulkanHelper_UpdateExternalMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, const uint8_t* pData);
#if NV_USE_MANAGED_WINSYS
NV_REPLAY_EXPORT VkResult VulkanHelper_CreateWindowSystemSurface(VkInstance instance, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterObject(VkObjectType objectType, uint64_t object, uint64_t id);
NV_REPLAY_EXPORT VkResult VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice device, uint32_t descriptorWriteCount, Serialization::DATABASE_HANDLE handle, VkDeviceSize dataSize, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies);
#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT VkResult VulkanHelper_CmdTraceRaysNV_FromDatabase(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, Serialization::DATABASE_HANDLE raygenShaderBindingTableHandle, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, Serialization::DATABASE_HANDLE missShaderBindingTableHandle, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, Serialization::DATABASE_HANDLE hitShaderBindingTableHandle, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, Serialization::DATABASE_HANDLE callableShaderBindingTableHandle, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth);
NV_REPLAY_EXPORT VkResult VulkanHelper_CmdTraceRaysKHR_FromDatabase(VkCommandBuffer commandBuffer, const VulkanHelper_ShaderBindTable* pRaygen, const VulkanHelper_ShaderBindTable* pMiss, const VulkanHelper_ShaderBindTable* pHit, const VulkanHelper_ShaderBindTable* pCallable, uint32_t width, uint32_t height, uint32_t depth);
NV_REPLAY_EXPORT VkResult VulkanHelper_CmdTraceRaysKHR_FromDatabase2(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth);
NV_REPLAY_EXPORT VkResult VulkanHelper_CmdBuildAccelerationStructuresInstanceKHR(VkCommandBuffer cmdBuffer, VkAccelerationStructureTypeKHR type, VkBuildAccelerationStructureFlagsKHR flags, VkBuildAccelerationStructureModeKHR mode, VkAccelerationStructureKHR srcAccelerationStructure, VkAccelerationStructureKHR dstAccelerationStructure, VkGeometryFlagsKHR geometryFlags, uint32_t instanceCount, const VulkanHelper_AccelerationStructureInstance* pInstances);
NV_REPLAY_EXPORT VkResult VulkanHelper_CmdBuildAccelerationStructuresMotionInstanceKHR(VkCommandBuffer cmdBuffer, VkAccelerationStructureTypeKHR type, VkBuildAccelerationStructureFlagsKHR flags, VkBuildAccelerationStructureModeKHR mode, VkAccelerationStructureKHR srcAccelerationStructure, VkAccelerationStructureKHR dstAccelerationStructure, VkGeometryFlagsKHR geometryFlags, uint32_t instanceCount, const VulkanHelper_AccelerationStructureMotionInstance* pInstances);
#endif
#if defined(VK_EXT_descriptor_buffer)
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterDescriptor_Sampler(VkDevice device, VkDescriptorType type, VkSampler sampler, size_t size, const void* pData);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterDescriptor_Image(VkDevice device, VkDescriptorType type, const VkDescriptorImageInfo* pInfo, size_t size, const void* pData);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterDescriptor_Buffer(VkDevice device, VkDescriptorType type, const VkDescriptorAddressInfoEXT* pAddressInfo, size_t size, const void* pData);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterDescriptor_AccelerationStructure(VkDevice device, VkDescriptorType type, VkDeviceAddress accelerationStructure, size_t size, const void* pData);
#endif

// Cleanup
NV_REPLAY_EXPORT VkResult VulkanHelper_ReleaseDevice(VkDevice device);
NV_REPLAY_EXPORT VkResult VulkanHelper_ReleaseInstance(VkInstance instance);

// External override API
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterOverrideSet(VkInstance instance, uint32_t count, const uint64_t* pOverrides);
NV_REPLAY_EXPORT VkResult VulkanHelper_AssociateImageWithOverrideKey(VkInstance instance, VkImage image, uint64_t key);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterImageOverride(VkInstance instance, uint64_t key, VkImage srcImage, VkImage dstImg);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterSemaphoreOverride(VkInstance instance, uint64_t key, VkSemaphore srcSemaphore, VkSemaphore dstSemaphore);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterFenceOverride(VkInstance instance, uint64_t key, VkFence srcFence, VkFence dstFence);
NV_REPLAY_EXPORT VkResult VulkanHelper_ActivateOverride(VkInstance instance, uint64_t key);
NV_REPLAY_EXPORT VkResult VulkanHelper_DeactivateOverride(VkInstance instance, uint64_t key);
NV_REPLAY_EXPORT VkResult VulkanHelper_SignalSemaphore(VkSemaphore semaphore);
NV_REPLAY_EXPORT VkResult VulkanHelper_WaitSemaphore(VkSemaphore semaphore);
NV_REPLAY_EXPORT VkResult VulkanHelper_SignalFence(VkFence fence);
#if defined(VK_NVX_image_view_handle)
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterImageViewHandleOverrideNVX(VkDevice device, VkImageView imageView, VkDescriptorType descriptorType, VkSampler sampler, uint32_t srcViewHandleNVX);
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterImageViewAddressOverrideNVX(VkDevice device, VkImageView imageView, VkDeviceAddress srcDeviceAddressNVX, VkDeviceSize srcSizeNVX);
NV_REPLAY_EXPORT VkResult VulkanHelper_ActivateImageViewHandleOverrideNVX(void* pData, size_t dataSize);
NV_REPLAY_EXPORT VkResult VulkanHelper_ActivateImageViewAddressOverrideNVX(void* pData, size_t dataSize);
#endif

// Calling context API
NV_REPLAY_EXPORT bool VulkanHelper_IsCallingContextEnabled();
NV_REPLAY_EXPORT VkResult VulkanHelper_SetCallingContext(const VulkanHelper_CallingContext* pContext);
NV_REPLAY_EXPORT VkResult VulkanHelper_GetCallingContext(VulkanHelper_CallingContext* pContext);

// Deprecated
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetBegin(VkInstance instance);
NV_REPLAY_EXPORT VkResult VulkanHelper_ResetEnd(VkInstance instance);

//------------------------------------------------------------------------------
// Vulkan API
//------------------------------------------------------------------------------

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
NV_REPLAY_EXPORT void VulkanReplay_DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
NV_REPLAY_EXPORT PFN_vkVoidFunction VulkanReplay_GetDeviceProcAddr(VkDevice device, const char* pName);
NV_REPLAY_EXPORT PFN_vkVoidFunction VulkanReplay_GetInstanceProcAddr(VkInstance instance, const char* pName);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
NV_REPLAY_EXPORT void VulkanReplay_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumerateInstanceVersion(uint32_t* pApiVersion);
#endif // VK_VERSION_1_1

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
NV_REPLAY_EXPORT VkResult VulkanReplay_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence);
NV_REPLAY_EXPORT VkResult VulkanReplay_QueueWaitIdle(VkQueue queue);
NV_REPLAY_EXPORT VkResult VulkanReplay_DeviceWaitIdle(VkDevice device);
NV_REPLAY_EXPORT VkResult VulkanReplay_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData);
NV_REPLAY_EXPORT void VulkanReplay_UnmapMemory(VkDevice device, VkDeviceMemory memory);
NV_REPLAY_EXPORT VkResult VulkanReplay_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges);
NV_REPLAY_EXPORT VkResult VulkanReplay_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges);
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes);
NV_REPLAY_EXPORT void VulkanReplay_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements);
NV_REPLAY_EXPORT VkResult VulkanReplay_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset);
NV_REPLAY_EXPORT void VulkanReplay_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements);
NV_REPLAY_EXPORT VkResult VulkanReplay_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
NV_REPLAY_EXPORT void VulkanReplay_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetFenceStatus(VkDevice device, VkFence fence);
NV_REPLAY_EXPORT VkResult VulkanReplay_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore);
NV_REPLAY_EXPORT void VulkanReplay_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent);
NV_REPLAY_EXPORT void VulkanReplay_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetEventStatus(VkDevice device, VkEvent event);
NV_REPLAY_EXPORT VkResult VulkanReplay_SetEvent(VkDevice device, VkEvent event);
NV_REPLAY_EXPORT VkResult VulkanReplay_ResetEvent(VkDevice device, VkEvent event);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT void VulkanReplay_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);
#endif // VK_VERSION_1_2

#if defined(VK_EXT_host_query_reset)
NV_REPLAY_EXPORT void VulkanReplay_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);
#endif // VK_EXT_host_query_reset

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer);
NV_REPLAY_EXPORT void VulkanReplay_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView);
NV_REPLAY_EXPORT void VulkanReplay_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage);
NV_REPLAY_EXPORT void VulkanReplay_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView);
NV_REPLAY_EXPORT void VulkanReplay_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule);
NV_REPLAY_EXPORT void VulkanReplay_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache);
NV_REPLAY_EXPORT void VulkanReplay_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
NV_REPLAY_EXPORT void VulkanReplay_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout);
NV_REPLAY_EXPORT void VulkanReplay_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler);
NV_REPLAY_EXPORT void VulkanReplay_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout);
NV_REPLAY_EXPORT void VulkanReplay_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags);
NV_REPLAY_EXPORT VkResult VulkanReplay_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets);
NV_REPLAY_EXPORT VkResult VulkanReplay_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets);
NV_REPLAY_EXPORT void VulkanReplay_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer);
NV_REPLAY_EXPORT void VulkanReplay_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
NV_REPLAY_EXPORT void VulkanReplay_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool);
#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags);
NV_REPLAY_EXPORT VkResult VulkanReplay_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
NV_REPLAY_EXPORT void VulkanReplay_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers);
NV_REPLAY_EXPORT VkResult VulkanReplay_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_EndCommandBuffer(VkCommandBuffer commandBuffer);
NV_REPLAY_EXPORT VkResult VulkanReplay_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
#endif // VK_VERSION_1_0

#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetAttachmentFeedbackLoopEnableEXT(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask);
#endif // VK_EXT_attachment_feedback_loop_dynamic_state

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets);
NV_REPLAY_EXPORT void VulkanReplay_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
#endif // VK_VERSION_1_0

#if defined(VK_EXT_multi_draw)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset);
#endif // VK_EXT_multi_draw

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
NV_REPLAY_EXPORT void VulkanReplay_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
NV_REPLAY_EXPORT void VulkanReplay_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions);
NV_REPLAY_EXPORT void VulkanReplay_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions);
#endif // VK_VERSION_1_0

#if defined(VK_NV_copy_memory_indirect)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources);
#endif // VK_NV_copy_memory_indirect

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData);
NV_REPLAY_EXPORT void VulkanReplay_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data);
NV_REPLAY_EXPORT void VulkanReplay_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges);
NV_REPLAY_EXPORT void VulkanReplay_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges);
NV_REPLAY_EXPORT void VulkanReplay_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects);
NV_REPLAY_EXPORT void VulkanReplay_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask);
NV_REPLAY_EXPORT void VulkanReplay_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask);
NV_REPLAY_EXPORT void VulkanReplay_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers);
NV_REPLAY_EXPORT void VulkanReplay_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers);
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query);
#endif // VK_VERSION_1_0

#if defined(VK_EXT_conditional_rendering)
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer);
#endif // VK_EXT_conditional_rendering

#if defined(VK_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags);
NV_REPLAY_EXPORT void VulkanReplay_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues);
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents);
NV_REPLAY_EXPORT void VulkanReplay_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndRenderPass(VkCommandBuffer commandBuffer);
NV_REPLAY_EXPORT void VulkanReplay_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers);
#endif // VK_VERSION_1_0

#if defined(VK_KHR_android_surface)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_KHR_android_surface

#if defined(VK_KHR_display)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_KHR_display

#if defined(VK_KHR_display_swapchain)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains);
#endif // VK_KHR_display_swapchain

#if defined(VK_KHR_surface)
NV_REPLAY_EXPORT void VulkanReplay_DestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes);
#endif // VK_KHR_surface

#if defined(VK_KHR_swapchain)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain);
#endif // VK_KHR_swapchain

#if defined(VK_KHR_swapchain) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator);
#endif // VK_KHR_swapchain && !VKSC_VERSION_1_0

#if defined(VK_KHR_swapchain)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages);
NV_REPLAY_EXPORT VkResult VulkanReplay_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex);
NV_REPLAY_EXPORT VkResult VulkanReplay_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo);
#endif // VK_KHR_swapchain

#if defined(VK_KHR_wayland_surface)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
NV_REPLAY_EXPORT VkBool32 VulkanReplay_GetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display);
#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_win32_surface)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
NV_REPLAY_EXPORT VkBool32 VulkanReplay_GetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);
#endif // VK_KHR_win32_surface

#if defined(VK_KHR_xlib_surface)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
NV_REPLAY_EXPORT VkBool32 VulkanReplay_GetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID);
#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
NV_REPLAY_EXPORT VkBool32 VulkanReplay_GetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id);
#endif // VK_KHR_xcb_surface

#if defined(VK_EXT_debug_report)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
NV_REPLAY_EXPORT void VulkanReplay_DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_DebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage);
#endif // VK_EXT_debug_report

#if defined(VK_EXT_debug_marker)
NV_REPLAY_EXPORT VkResult VulkanReplay_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer);
NV_REPLAY_EXPORT void VulkanReplay_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);
#endif // VK_EXT_debug_marker

#if defined(VK_NV_external_memory_capabilities)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties);
#endif // VK_NV_external_memory_capabilities

#if defined(VK_NV_external_memory_win32)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);
#endif // VK_NV_external_memory_win32

#if defined(VK_NV_device_generated_commands)
NV_REPLAY_EXPORT void VulkanReplay_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex);
NV_REPLAY_EXPORT void VulkanReplay_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout);
NV_REPLAY_EXPORT void VulkanReplay_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator);
#endif // VK_NV_device_generated_commands

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2KHR* pFeatures);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2KHR* pProperties);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2KHR* pFormatProperties);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2KHR* pImageFormatInfo, VkImageFormatProperties2KHR* pImageFormatProperties);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2KHR* pQueueFamilyProperties);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2KHR* pMemoryProperties);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties);
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_physical_device_properties2)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2KHR* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2KHR* pProperties);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_KHR_push_descriptor)
NV_REPLAY_EXPORT void VulkanReplay_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites);
#endif // VK_KHR_push_descriptor

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags);
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_maintenance1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlagsKHR flags);
#endif // VK_KHR_maintenance1 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_memory_capabilities)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHR* pExternalBufferInfo, VkExternalBufferPropertiesKHR* pExternalBufferProperties);
#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_memory_win32)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);
#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties);
#endif // VK_KHR_external_memory_fd

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_semaphore_capabilities)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHR* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHR* pExternalSemaphoreProperties);
#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_KHR_external_semaphore_win32)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
NV_REPLAY_EXPORT VkResult VulkanReplay_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd);
NV_REPLAY_EXPORT VkResult VulkanReplay_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);
#endif // VK_KHR_external_semaphore_fd

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_fence_capabilities)
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfoKHR* pExternalFenceInfo, VkExternalFencePropertiesKHR* pExternalFenceProperties);
#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_external_fence_win32)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
NV_REPLAY_EXPORT VkResult VulkanReplay_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd);
NV_REPLAY_EXPORT VkResult VulkanReplay_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo);
#endif // VK_KHR_external_fence_fd

#if defined(VK_EXT_direct_mode_display)
NV_REPLAY_EXPORT VkResult VulkanReplay_ReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
NV_REPLAY_EXPORT VkResult VulkanReplay_AcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay);
#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities);
#endif // VK_EXT_display_surface_counter

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group_creation)
NV_REPLAY_EXPORT VkResult VulkanReplay_EnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupPropertiesKHR* pPhysicalDeviceGroupProperties);
#endif // VK_KHR_device_group_creation

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlagsKHR* pPeerMemoryFeatures);
#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT VkResult VulkanReplay_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
NV_REPLAY_EXPORT VkResult VulkanReplay_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfoKHR* pBindInfos);
#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT VkResult VulkanReplay_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
NV_REPLAY_EXPORT VkResult VulkanReplay_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfoKHR* pBindInfos);
#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask);
#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes);
NV_REPLAY_EXPORT VkResult VulkanReplay_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex);
#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
NV_REPLAY_EXPORT void VulkanReplay_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects);
#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplateKHR* pDescriptorUpdateTemplate);
#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
NV_REPLAY_EXPORT void VulkanReplay_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator);
#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData);
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
NV_REPLAY_EXPORT void VulkanReplay_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const void* pData);
#endif // VK_KHR_descriptor_update_template

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
NV_REPLAY_EXPORT void VulkanReplay_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData);
#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

#if defined(VK_EXT_hdr_metadata)
NV_REPLAY_EXPORT void VulkanReplay_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata);
#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_shared_presentable_image)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain);
#endif // VK_KHR_shared_presentable_image

#if defined(VK_NV_clip_space_w_scaling)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings);
#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_discard_rectangles)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles);
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode);
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_sample_locations)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo);
NV_REPLAY_EXPORT void VulkanReplay_GetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties);
#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_surface_capabilities2)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats);
#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities);
#endif // VK_KHR_get_display_properties2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
NV_REPLAY_EXPORT void VulkanReplay_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
NV_REPLAY_EXPORT void VulkanReplay_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);
#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_memory_requirements2)
NV_REPLAY_EXPORT void VulkanReplay_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2KHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements);
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirementsKHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements);
#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversionKHR* pYcbcrConversion);
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
NV_REPLAY_EXPORT void VulkanReplay_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversionKHR ycbcrConversion, const VkAllocationCallbacks* pAllocator);
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue);
#endif // VK_VERSION_1_1

#if defined(VK_EXT_validation_cache)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache);
NV_REPLAY_EXPORT void VulkanReplay_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches);
#endif // VK_EXT_validation_cache

#if defined(VK_VERSION_1_1)
NV_REPLAY_EXPORT void VulkanReplay_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport);
#endif // VK_VERSION_1_1

#if defined(VK_KHR_maintenance3)
NV_REPLAY_EXPORT void VulkanReplay_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupportKHR* pSupport);
#endif // VK_KHR_maintenance3

#if defined(VK_AMD_shader_info)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo);
#endif // VK_AMD_shader_info

#if defined(VK_EXT_calibrated_timestamps)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainEXT* pTimeDomains);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation);
#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
NV_REPLAY_EXPORT VkResult VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo);
NV_REPLAY_EXPORT void VulkanReplay_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo);
NV_REPLAY_EXPORT void VulkanReplay_QueueEndDebugUtilsLabelEXT(VkQueue queue);
NV_REPLAY_EXPORT void VulkanReplay_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer);
NV_REPLAY_EXPORT void VulkanReplay_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger);
NV_REPLAY_EXPORT void VulkanReplay_DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_SubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);
#endif // VK_EXT_debug_utils

#if defined(VK_EXT_external_memory_host)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties);
#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker);
#endif // VK_AMD_buffer_marker

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfo* pSubpassBeginInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfoKHR* pSubpassBeginInfo);
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT void VulkanReplay_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo* pSubpassBeginInfo, const VkSubpassEndInfo* pSubpassEndInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
NV_REPLAY_EXPORT void VulkanReplay_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR* pSubpassBeginInfo, const VkSubpassEndInfoKHR* pSubpassEndInfo);
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT void VulkanReplay_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo* pSubpassEndInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
NV_REPLAY_EXPORT void VulkanReplay_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR* pSubpassEndInfo);
#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue);
#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT VkResult VulkanReplay_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
NV_REPLAY_EXPORT VkResult VulkanReplay_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfoKHR* pWaitInfo, uint64_t timeout);
#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT VkResult VulkanReplay_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
NV_REPLAY_EXPORT VkResult VulkanReplay_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfoKHR* pSignalInfo);
#endif // VK_KHR_timeline_semaphore

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer);
#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif // VK_KHR_draw_indirect_count

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif // VK_KHR_draw_indirect_count

#if defined(VK_NV_device_diagnostic_checkpoints)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker);
NV_REPLAY_EXPORT void VulkanReplay_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData);
#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_EXT_transform_feedback)
NV_REPLAY_EXPORT void VulkanReplay_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes);
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets);
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride);
#endif // VK_EXT_transform_feedback

#if defined(VK_NV_scissor_exclusive)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors);
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
NV_REPLAY_EXPORT void VulkanReplay_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables);
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_shading_rate_image)
NV_REPLAY_EXPORT void VulkanReplay_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders);
#endif // VK_NV_shading_rate_image

#if defined(VK_NV_mesh_shader)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif // VK_NV_mesh_shader

#if defined(VK_EXT_mesh_shader)
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
NV_REPLAY_EXPORT void VulkanReplay_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif // VK_EXT_mesh_shader

#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT VkResult VulkanReplay_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT void VulkanReplay_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator);
#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT void VulkanReplay_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
NV_REPLAY_EXPORT VkResult VulkanReplay_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
NV_REPLAY_EXPORT void VulkanReplay_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT VkResult VulkanReplay_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, size_t dataSize, void* pData, size_t stride);
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT void VulkanReplay_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT void VulkanReplay_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_cooperative_matrix)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties);
#endif // VK_NV_cooperative_matrix

#if defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT void VulkanReplay_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_ray_tracing_maintenance1)
NV_REPLAY_EXPORT void VulkanReplay_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress);
#endif // VK_KHR_ray_tracing_maintenance1

#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility);
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
NV_REPLAY_EXPORT VkDeviceSize VulkanReplay_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NVX_image_view_handle)
NV_REPLAY_EXPORT uint32_t VulkanReplay_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties);
#endif // VK_NVX_image_view_handle

#if defined(VK_EXT_full_screen_exclusive)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes);
NV_REPLAY_EXPORT VkResult VulkanReplay_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain);
NV_REPLAY_EXPORT VkResult VulkanReplay_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain);
#endif // VK_EXT_full_screen_exclusive

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT uint64_t VulkanReplay_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
NV_REPLAY_EXPORT uint64_t VulkanReplay_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfoKHR* pInfo);
#endif // VK_KHR_buffer_device_address

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT VkDeviceAddress VulkanReplay_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
NV_REPLAY_EXPORT VkDeviceAddress VulkanReplay_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfoKHR* pInfo);
#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_buffer_device_address)
NV_REPLAY_EXPORT VkDeviceAddress VulkanReplay_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfoEXT* pInfo);
#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_headless_surface)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateHeadlessSurfaceEXT(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_EXT_headless_surface

#if defined(VK_NV_coverage_reduction_mode)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations);
#endif // VK_NV_coverage_reduction_mode

#if defined(VK_VERSION_1_2)
NV_REPLAY_EXPORT uint64_t VulkanReplay_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);
#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
NV_REPLAY_EXPORT uint64_t VulkanReplay_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfoKHR* pInfo);
#endif // VK_KHR_buffer_device_address

#if defined(VK_KHR_pipeline_executable_properties)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPipelineExecutablePropertiesKHR(VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPipelineExecutableStatisticsKHR(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPipelineExecutableInternalRepresentationsKHR(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations);
#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_EXT_line_rasterization)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern);
#endif // VK_EXT_line_rasterization

#if defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetFaultData(VkDevice device, VkFaultQueryBehavior faultQueryBehavior, VkBool32* pUnrecordedFaults, uint32_t* pFaultCount, VkFaultData* pFaults);
#endif // VKSC_VERSION_1_0

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_tooling_info)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolPropertiesEXT* pToolProperties);
#endif // VK_EXT_tooling_info

#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateAccelerationStructureKHR(VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure);
NV_REPLAY_EXPORT void VulkanReplay_CmdBuildAccelerationStructuresKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
NV_REPLAY_EXPORT void VulkanReplay_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts);
NV_REPLAY_EXPORT VkResult VulkanReplay_BuildAccelerationStructuresKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
NV_REPLAY_EXPORT VkDeviceAddress VulkanReplay_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo);
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_deferred_host_operations)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation);
NV_REPLAY_EXPORT void VulkanReplay_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT uint32_t VulkanReplay_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation);
NV_REPLAY_EXPORT VkResult VulkanReplay_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation);
#endif // VK_KHR_deferred_host_operations

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp);
#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints);
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable);
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp);
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable);
#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state3) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask* pSampleMask);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable);
#endif // VK_EXT_extended_dynamic_state3 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlotEXT* pPrivateDataSlot);
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
NV_REPLAY_EXPORT void VulkanReplay_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlotEXT privateDataSlot, const VkAllocationCallbacks* pAllocator);
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT VkResult VulkanReplay_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
NV_REPLAY_EXPORT VkResult VulkanReplay_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t data);
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData);
#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
NV_REPLAY_EXPORT void VulkanReplay_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t* pData);
#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2KHR* pCopyBufferInfo);
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2KHR* pCopyImageInfo);
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
NV_REPLAY_EXPORT void VulkanReplay_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2KHR* pBlitImageInfo);
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2KHR* pCopyBufferToImageInfo);
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2KHR* pCopyImageToBufferInfo);
#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
NV_REPLAY_EXPORT void VulkanReplay_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2KHR* pResolveImageInfo);
#endif // VK_KHR_copy_commands2

#if defined(VK_KHR_fragment_shading_rate)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetFragmentShadingRateKHR(VkCommandBuffer commandBuffer, const VkExtent2D* pFragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);
#endif // VK_KHR_fragment_shading_rate

#if defined(VK_NV_fragment_shading_rate_enums)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer commandBuffer, VkFragmentShadingRateNV shadingRate, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);
#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_acceleration_structure)
NV_REPLAY_EXPORT void VulkanReplay_GetAccelerationStructureBuildSizesKHR(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);
#endif // VK_KHR_acceleration_structure

#if defined(VK_EXT_vertex_input_dynamic_state) || defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions);
#endif // VK_EXT_vertex_input_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_color_write_enable)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetColorWriteEnableEXT(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkBool32* pColorWriteEnables);
#endif // VK_EXT_color_write_enable

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetEvent2(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo* pDependencyInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
NV_REPLAY_EXPORT void VulkanReplay_CmdSetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfoKHR* pDependencyInfo);
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdResetEvent2(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
NV_REPLAY_EXPORT void VulkanReplay_CmdResetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2KHR stageMask);
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdWaitEvents2(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfo* pDependencyInfos);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
NV_REPLAY_EXPORT void VulkanReplay_CmdWaitEvents2KHR(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfoKHR* pDependencyInfos);
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdPipelineBarrier2(VkCommandBuffer commandBuffer, const VkDependencyInfo* pDependencyInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
NV_REPLAY_EXPORT void VulkanReplay_CmdPipelineBarrier2KHR(VkCommandBuffer commandBuffer, const VkDependencyInfoKHR* pDependencyInfo);
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT VkResult VulkanReplay_QueueSubmit2(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
NV_REPLAY_EXPORT VkResult VulkanReplay_QueueSubmit2KHR(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence);
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteTimestamp2(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteTimestamp2KHR(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkQueryPool queryPool, uint32_t query);
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteBufferMarker2AMD(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker);
NV_REPLAY_EXPORT void VulkanReplay_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData);
#endif // VK_KHR_synchronization2

#if defined(VKSC_VERSION_1_0)
NV_REPLAY_EXPORT void VulkanReplay_GetCommandPoolMemoryConsumption(VkDevice device, VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkCommandPoolMemoryConsumption* pConsumption);
#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_video_queue)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceVideoCapabilitiesKHR(VkPhysicalDevice physicalDevice, const VkVideoProfileInfoKHR* pVideoProfile, VkVideoCapabilitiesKHR* pCapabilities);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceVideoFormatPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoFormatInfoKHR* pVideoFormatInfo, uint32_t* pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR* pVideoFormatProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession);
NV_REPLAY_EXPORT void VulkanReplay_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters);
NV_REPLAY_EXPORT VkResult VulkanReplay_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo);
NV_REPLAY_EXPORT void VulkanReplay_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements);
NV_REPLAY_EXPORT VkResult VulkanReplay_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos);
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
NV_REPLAY_EXPORT void VulkanReplay_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo);
#endif // VK_KHR_video_decode_queue

#if defined(VK_KHR_video_queue)
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo);
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_encode_queue)
NV_REPLAY_EXPORT void VulkanReplay_CmdEncodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo);
#endif // VK_KHR_video_encode_queue

#if defined(VK_NV_memory_decompression)
NV_REPLAY_EXPORT void VulkanReplay_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions);
NV_REPLAY_EXPORT void VulkanReplay_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride);
#endif // VK_NV_memory_decompression

#if defined(VK_NVX_binary_import)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule);
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction);
NV_REPLAY_EXPORT void VulkanReplay_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo);
#endif // VK_NVX_binary_import

#if defined(VK_EXT_descriptor_buffer)
NV_REPLAY_EXPORT void VulkanReplay_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes);
NV_REPLAY_EXPORT void VulkanReplay_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset);
NV_REPLAY_EXPORT void VulkanReplay_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos);
NV_REPLAY_EXPORT void VulkanReplay_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData);
#endif // VK_EXT_descriptor_buffer

#if defined(VK_EXT_pageable_device_local_memory)
NV_REPLAY_EXPORT void VulkanReplay_SetDeviceMemoryPriorityEXT(VkDevice device, VkDeviceMemory memory, float priority);
#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_present_wait)
NV_REPLAY_EXPORT VkResult VulkanReplay_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout);
#endif // VK_KHR_present_wait

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginRendering(VkCommandBuffer commandBuffer, const VkRenderingInfo* pRenderingInfo);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
NV_REPLAY_EXPORT void VulkanReplay_CmdBeginRenderingKHR(VkCommandBuffer commandBuffer, const VkRenderingInfoKHR* pRenderingInfo);
#endif // VK_KHR_dynamic_rendering

#if defined(VK_VERSION_1_3)
NV_REPLAY_EXPORT void VulkanReplay_CmdEndRendering(VkCommandBuffer commandBuffer);
#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
NV_REPLAY_EXPORT void VulkanReplay_CmdEndRenderingKHR(VkCommandBuffer commandBuffer);
#endif // VK_KHR_dynamic_rendering

#if defined(VK_EXT_opacity_micromap)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateMicromapEXT(VkDevice device, const VkMicromapCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkMicromapEXT* pMicromap);
NV_REPLAY_EXPORT void VulkanReplay_CmdBuildMicromapsEXT(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos);
NV_REPLAY_EXPORT VkResult VulkanReplay_BuildMicromapsEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos);
NV_REPLAY_EXPORT void VulkanReplay_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo);
NV_REPLAY_EXPORT VkResult VulkanReplay_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo);
NV_REPLAY_EXPORT void VulkanReplay_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
NV_REPLAY_EXPORT VkResult VulkanReplay_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, size_t dataSize, void* pData, size_t stride);
NV_REPLAY_EXPORT void VulkanReplay_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility);
NV_REPLAY_EXPORT void VulkanReplay_GetMicromapBuildSizesEXT(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapBuildSizesInfoEXT* pSizeInfo);
#endif // VK_EXT_opacity_micromap

#if defined(VK_EXT_shader_module_identifier)
NV_REPLAY_EXPORT void VulkanReplay_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier);
NV_REPLAY_EXPORT void VulkanReplay_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier);
#endif // VK_EXT_shader_module_identifier

#if defined(VK_EXT_image_compression_control)
NV_REPLAY_EXPORT void VulkanReplay_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout);
#endif // VK_EXT_image_compression_control

#if defined(VK_EXT_device_fault)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo);
#endif // VK_EXT_device_fault

#if defined(VK_EXT_swapchain_maintenance1)
NV_REPLAY_EXPORT VkResult VulkanReplay_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo);
#endif // VK_EXT_swapchain_maintenance1

#if defined(VK_KHR_map_memory2)
NV_REPLAY_EXPORT VkResult VulkanReplay_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData);
NV_REPLAY_EXPORT VkResult VulkanReplay_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo);
#endif // VK_KHR_map_memory2

#if defined(VK_EXT_shader_object)
NV_REPLAY_EXPORT VkResult VulkanReplay_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders);
NV_REPLAY_EXPORT void VulkanReplay_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData);
NV_REPLAY_EXPORT void VulkanReplay_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders);
#endif // VK_EXT_shader_object

#if defined(VK_NV_external_memory_sci_buf)
NV_REPLAY_EXPORT VkResult VulkanReplay_GetMemorySciBufNV(VkDevice device, const VkMemoryGetSciBufInfoNV* pGetSciBufInfo, NvSciBufObj* pHandle);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceExternalMemorySciBufPropertiesNV(VkPhysicalDevice physicalDevice, VkExternalMemoryHandleTypeFlagBits handleType, NvSciBufObj handle, VkMemorySciBufPropertiesNV* pMemorySciBufProperties);
NV_REPLAY_EXPORT VkResult VulkanReplay_GetPhysicalDeviceSciBufAttributesNV(VkPhysicalDevice physicalDevice, NvSciBufAttrList pAttributes);
#endif // VK_NV_external_memory_sci_buf
