//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: Resources01.cpp
// 
//-----------------------------------------------------------------------------

#include <vector>
#include <vulkan/vulkan.h>

#include "VulkanHelpers.h"
#include "VulkanReplay.h"
#include "Helpers.h"
#include "CommonReplay.h"
#include "Resources.h"
#include "WindowSystem.h"

NV_REPLAY_BEGIN_RESOURCE_INIT()

//-----------------------------------------------------------------------------
// CreateResources01
//-----------------------------------------------------------------------------
void CreateResources01()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Create VkDeviceMemory_uid_5904
    {
        BEGIN_DATA_SCOPE();

        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_375[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_390[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_375,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_390[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5903,
        /* memory = */ VkDeviceMemory_uid_5904,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_390[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962559803392ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_390,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_390, VulkanHelper_InitializeDeviceMemoryInfo_temp_390, &VkDeviceMemory_uid_5904, nullptr));
    }

    // Create VkDeviceMemory_uid_5907
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_376[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_391[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_376,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_391[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5906,
        /* memory = */ VkDeviceMemory_uid_5907,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_391[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962554626048ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_391,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_391, VulkanHelper_InitializeDeviceMemoryInfo_temp_391, &VkDeviceMemory_uid_5907, nullptr));
    }

    // Create VkDeviceMemory_uid_5909
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_377[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_392[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_377,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_392[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5908,
        /* memory = */ VkDeviceMemory_uid_5909,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_392[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962554691584ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_392,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_392, VulkanHelper_InitializeDeviceMemoryInfo_temp_392, &VkDeviceMemory_uid_5909, nullptr));
    }

    // Create VkDeviceMemory_uid_5920
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_378[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_393[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_378,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_393[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5919,
        /* memory = */ VkDeviceMemory_uid_5920,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_393[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962561179648ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_393,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_393, VulkanHelper_InitializeDeviceMemoryInfo_temp_393, &VkDeviceMemory_uid_5920, nullptr));
    }

    // Create VkDeviceMemory_uid_5925
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_379[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_394[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_379,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_394[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5924,
        /* memory = */ VkDeviceMemory_uid_5925,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_394[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962560720896ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_394,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_394, VulkanHelper_InitializeDeviceMemoryInfo_temp_394, &VkDeviceMemory_uid_5925, nullptr));
    }

    // Create VkDeviceMemory_uid_5928
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_380[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_395[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_380,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_395[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5927,
        /* memory = */ VkDeviceMemory_uid_5928,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_395[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962555478016ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_395,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_395, VulkanHelper_InitializeDeviceMemoryInfo_temp_395, &VkDeviceMemory_uid_5928, nullptr));
    }

    // Create VkDeviceMemory_uid_5930
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_381[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_396[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_381,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_396[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5929,
        /* memory = */ VkDeviceMemory_uid_5930,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_396[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962555543552ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_396,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_396, VulkanHelper_InitializeDeviceMemoryInfo_temp_396, &VkDeviceMemory_uid_5930, nullptr));
    }

    // Create VkDeviceMemory_uid_5941
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_382[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_397[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_382,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_397[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5940,
        /* memory = */ VkDeviceMemory_uid_5941,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_397[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962562097152ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_397,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_397, VulkanHelper_InitializeDeviceMemoryInfo_temp_397, &VkDeviceMemory_uid_5941, nullptr));
    }

    // Create VkDeviceMemory_uid_5946
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_383[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_398[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_383,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_398[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5945,
        /* memory = */ VkDeviceMemory_uid_5946,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_398[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962561638400ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_398,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_398, VulkanHelper_InitializeDeviceMemoryInfo_temp_398, &VkDeviceMemory_uid_5946, nullptr));
    }

    // Create VkDeviceMemory_uid_5949
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_384[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_399[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_384,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_399[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5948,
        /* memory = */ VkDeviceMemory_uid_5949,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_399[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962555609088ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_399,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_399, VulkanHelper_InitializeDeviceMemoryInfo_temp_399, &VkDeviceMemory_uid_5949, nullptr));
    }

    // Create VkDeviceMemory_uid_5951
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_385[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_400[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_385,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_400[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5950,
        /* memory = */ VkDeviceMemory_uid_5951,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_400[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962556395520ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_400,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_400, VulkanHelper_InitializeDeviceMemoryInfo_temp_400, &VkDeviceMemory_uid_5951, nullptr));
    }

    // Create VkDeviceMemory_uid_5962
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_386[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_401[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_386,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_401[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5961,
        /* memory = */ VkDeviceMemory_uid_5962,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_401[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962563014656ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_401,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_401, VulkanHelper_InitializeDeviceMemoryInfo_temp_401, &VkDeviceMemory_uid_5962, nullptr));
    }

    // Create VkDeviceMemory_uid_5967
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_387[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_402[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_387,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_402[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5966,
        /* memory = */ VkDeviceMemory_uid_5967,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_402[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962562555904ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_402,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_402, VulkanHelper_InitializeDeviceMemoryInfo_temp_402, &VkDeviceMemory_uid_5967, nullptr));
    }

    // Create VkDeviceMemory_uid_5970
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_388[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_403[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_388,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_403[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5969,
        /* memory = */ VkDeviceMemory_uid_5970,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_403[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962556461056ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_403,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_403, VulkanHelper_InitializeDeviceMemoryInfo_temp_403, &VkDeviceMemory_uid_5970, nullptr));
    }

    // Create VkDeviceMemory_uid_5972
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_389[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_404[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_389,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_404[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5971,
        /* memory = */ VkDeviceMemory_uid_5972,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_404[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962556526592ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_404,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_404, VulkanHelper_InitializeDeviceMemoryInfo_temp_404, &VkDeviceMemory_uid_5972, nullptr));
    }

    // Create VkDeviceMemory_uid_5983
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_390[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_405[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_390,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_405[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5982,
        /* memory = */ VkDeviceMemory_uid_5983,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_405[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962563932160ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_405,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_405, VulkanHelper_InitializeDeviceMemoryInfo_temp_405, &VkDeviceMemory_uid_5983, nullptr));
    }

    // Create VkDeviceMemory_uid_5988
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_391[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_406[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_391,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_406[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5987,
        /* memory = */ VkDeviceMemory_uid_5988,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_406[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962563473408ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_406,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_406, VulkanHelper_InitializeDeviceMemoryInfo_temp_406, &VkDeviceMemory_uid_5988, nullptr));
    }

    // Create VkDeviceMemory_uid_5991
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_392[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_407[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_392,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_407[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5990,
        /* memory = */ VkDeviceMemory_uid_5991,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_407[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962557313024ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_407,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_407, VulkanHelper_InitializeDeviceMemoryInfo_temp_407, &VkDeviceMemory_uid_5991, nullptr));
    }

    // Create VkDeviceMemory_uid_5993
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_393[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_408[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_393,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_408[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5992,
        /* memory = */ VkDeviceMemory_uid_5993,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_408[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962557378560ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_408,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_408, VulkanHelper_InitializeDeviceMemoryInfo_temp_408, &VkDeviceMemory_uid_5993, nullptr));
    }

    // Create VkDeviceMemory_uid_6004
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_394[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_409[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_394,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_409[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6003,
        /* memory = */ VkDeviceMemory_uid_6004,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_409[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962564849664ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_409,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_409, VulkanHelper_InitializeDeviceMemoryInfo_temp_409, &VkDeviceMemory_uid_6004, nullptr));
    }

    // Create VkDeviceMemory_uid_6009
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_395[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_410[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_395,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_410[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6008,
        /* memory = */ VkDeviceMemory_uid_6009,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_410[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962564390912ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_410,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_410, VulkanHelper_InitializeDeviceMemoryInfo_temp_410, &VkDeviceMemory_uid_6009, nullptr));
    }

    // Create VkDeviceMemory_uid_6012
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_396[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_411[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_396,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_411[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6011,
        /* memory = */ VkDeviceMemory_uid_6012,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_411[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962557444096ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_411,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_411, VulkanHelper_InitializeDeviceMemoryInfo_temp_411, &VkDeviceMemory_uid_6012, nullptr));
    }

    // Create VkDeviceMemory_uid_6014
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_397[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_412[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_397,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_412[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6013,
        /* memory = */ VkDeviceMemory_uid_6014,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_412[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962558230528ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_412,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_412, VulkanHelper_InitializeDeviceMemoryInfo_temp_412, &VkDeviceMemory_uid_6014, nullptr));
    }

    // Create VkDeviceMemory_uid_6025
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_398[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_413[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_398,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_413[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6024,
        /* memory = */ VkDeviceMemory_uid_6025,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_413[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962565767168ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_413,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_413, VulkanHelper_InitializeDeviceMemoryInfo_temp_413, &VkDeviceMemory_uid_6025, nullptr));
    }

    // Create VkDeviceMemory_uid_6030
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_399[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_414[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_399,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_414[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6029,
        /* memory = */ VkDeviceMemory_uid_6030,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_414[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962565308416ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_414,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_414, VulkanHelper_InitializeDeviceMemoryInfo_temp_414, &VkDeviceMemory_uid_6030, nullptr));
    }

    // Create VkDeviceMemory_uid_6033
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_400[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_415[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_400,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_415[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6032,
        /* memory = */ VkDeviceMemory_uid_6033,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_415[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962558296064ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_415,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_415, VulkanHelper_InitializeDeviceMemoryInfo_temp_415, &VkDeviceMemory_uid_6033, nullptr));
    }

    // Create VkDeviceMemory_uid_6035
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_401[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_416[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_401,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_416[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6034,
        /* memory = */ VkDeviceMemory_uid_6035,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_416[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962558361600ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_416,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_416, VulkanHelper_InitializeDeviceMemoryInfo_temp_416, &VkDeviceMemory_uid_6035, nullptr));
    }

    // Create VkDeviceMemory_uid_6046
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_402[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_417[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_402,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_417[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6045,
        /* memory = */ VkDeviceMemory_uid_6046,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_417[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962566684672ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_417,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_417, VulkanHelper_InitializeDeviceMemoryInfo_temp_417, &VkDeviceMemory_uid_6046, nullptr));
    }

    // Create VkDeviceMemory_uid_6051
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_403[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_418[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_403,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_418[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6050,
        /* memory = */ VkDeviceMemory_uid_6051,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_418[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962566225920ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_418,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_418, VulkanHelper_InitializeDeviceMemoryInfo_temp_418, &VkDeviceMemory_uid_6051, nullptr));
    }

    // Create VkDeviceMemory_uid_6054
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_404[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_419[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_404,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_419[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6053,
        /* memory = */ VkDeviceMemory_uid_6054,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_419[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962559148032ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_419,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_419, VulkanHelper_InitializeDeviceMemoryInfo_temp_419, &VkDeviceMemory_uid_6054, nullptr));
    }

    // Create VkDeviceMemory_uid_6056
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_405[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_420[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_405,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_420[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6055,
        /* memory = */ VkDeviceMemory_uid_6056,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_420[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962559213568ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_420,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_420, VulkanHelper_InitializeDeviceMemoryInfo_temp_420, &VkDeviceMemory_uid_6056, nullptr));
    }

    // Create VkDeviceMemory_uid_6067
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_406[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_421[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_406,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_421[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6066,
        /* memory = */ VkDeviceMemory_uid_6067,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_421[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962567602176ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_421,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_421, VulkanHelper_InitializeDeviceMemoryInfo_temp_421, &VkDeviceMemory_uid_6067, nullptr));
    }

    // Create VkDeviceMemory_uid_6072
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_407[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_422[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_407,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_422[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6071,
        /* memory = */ VkDeviceMemory_uid_6072,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_422[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962567143424ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_422,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_422, VulkanHelper_InitializeDeviceMemoryInfo_temp_422, &VkDeviceMemory_uid_6072, nullptr));
    }

    // Create VkDeviceMemory_uid_6075
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_408[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_423[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_408,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_423[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6074,
        /* memory = */ VkDeviceMemory_uid_6075,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_423[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962559279104ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_423,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_423, VulkanHelper_InitializeDeviceMemoryInfo_temp_423, &VkDeviceMemory_uid_6075, nullptr));
    }

    // Create VkDeviceMemory_uid_6077
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_409[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_424[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_409,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_424[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6076,
        /* memory = */ VkDeviceMemory_uid_6077,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_424[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962560065536ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_424,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_424, VulkanHelper_InitializeDeviceMemoryInfo_temp_424, &VkDeviceMemory_uid_6077, nullptr));
    }

    // Create VkDeviceMemory_uid_6088
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_410[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_425[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_410,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_425[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6087,
        /* memory = */ VkDeviceMemory_uid_6088,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_425[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962568519680ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_425,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_425, VulkanHelper_InitializeDeviceMemoryInfo_temp_425, &VkDeviceMemory_uid_6088, nullptr));
    }

    // Create VkDeviceMemory_uid_6093
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_411[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_426[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_411,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_426[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6092,
        /* memory = */ VkDeviceMemory_uid_6093,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_426[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962568060928ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_426,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_426, VulkanHelper_InitializeDeviceMemoryInfo_temp_426, &VkDeviceMemory_uid_6093, nullptr));
    }

    // Create VkDeviceMemory_uid_6096
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_412[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_427[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_412,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_427[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6095,
        /* memory = */ VkDeviceMemory_uid_6096,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_427[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962560131072ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_427,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_427, VulkanHelper_InitializeDeviceMemoryInfo_temp_427, &VkDeviceMemory_uid_6096, nullptr));
    }

    // Create VkDeviceMemory_uid_6098
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_413[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_428[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_413,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_428[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6097,
        /* memory = */ VkDeviceMemory_uid_6098,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_428[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962560196608ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_428,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_428, VulkanHelper_InitializeDeviceMemoryInfo_temp_428, &VkDeviceMemory_uid_6098, nullptr));
    }

    // Create VkDeviceMemory_uid_6109
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_414[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_429[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_414,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_429[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6108,
        /* memory = */ VkDeviceMemory_uid_6109,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_429[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962569437184ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_429,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_429, VulkanHelper_InitializeDeviceMemoryInfo_temp_429, &VkDeviceMemory_uid_6109, nullptr));
    }

    // Create VkDeviceMemory_uid_6114
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_415[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_430[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_415,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_430[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6113,
        /* memory = */ VkDeviceMemory_uid_6114,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_430[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962568978432ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_430,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_430, VulkanHelper_InitializeDeviceMemoryInfo_temp_430, &VkDeviceMemory_uid_6114, nullptr));
    }

    // Create VkDeviceMemory_uid_6117
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_416[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_431[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_416,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_431[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6116,
        /* memory = */ VkDeviceMemory_uid_6117,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_431[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962560983040ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_431,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_431, VulkanHelper_InitializeDeviceMemoryInfo_temp_431, &VkDeviceMemory_uid_6117, nullptr));
    }

    // Create VkDeviceMemory_uid_6119
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_417[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_432[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_417,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_432[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6118,
        /* memory = */ VkDeviceMemory_uid_6119,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_432[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962561048576ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_432,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_432, VulkanHelper_InitializeDeviceMemoryInfo_temp_432, &VkDeviceMemory_uid_6119, nullptr));
    }

    // Create VkDeviceMemory_uid_6130
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_418[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_433[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_418,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_433[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6129,
        /* memory = */ VkDeviceMemory_uid_6130,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_433[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962570354688ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_433,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_433, VulkanHelper_InitializeDeviceMemoryInfo_temp_433, &VkDeviceMemory_uid_6130, nullptr));
    }

    // Create VkDeviceMemory_uid_6135
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_419[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_434[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_419,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_434[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6134,
        /* memory = */ VkDeviceMemory_uid_6135,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_434[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962569895936ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_434,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_434, VulkanHelper_InitializeDeviceMemoryInfo_temp_434, &VkDeviceMemory_uid_6135, nullptr));
    }

    // Create VkDeviceMemory_uid_6138
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_420[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_435[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_420,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_435[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6137,
        /* memory = */ VkDeviceMemory_uid_6138,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_435[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962561114112ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_435,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_435, VulkanHelper_InitializeDeviceMemoryInfo_temp_435, &VkDeviceMemory_uid_6138, nullptr));
    }

    // Create VkDeviceMemory_uid_6140
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_421[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_436[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_421,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_436[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6139,
        /* memory = */ VkDeviceMemory_uid_6140,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_436[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962561900544ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_436,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_436, VulkanHelper_InitializeDeviceMemoryInfo_temp_436, &VkDeviceMemory_uid_6140, nullptr));
    }

    // Create VkDeviceMemory_uid_6151
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_422[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_437[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_422,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_437[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6150,
        /* memory = */ VkDeviceMemory_uid_6151,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_437[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962571272192ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_437,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_437, VulkanHelper_InitializeDeviceMemoryInfo_temp_437, &VkDeviceMemory_uid_6151, nullptr));
    }

    // Create VkDeviceMemory_uid_6156
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_423[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_438[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_423,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_438[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6155,
        /* memory = */ VkDeviceMemory_uid_6156,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_438[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962570813440ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_438,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_438, VulkanHelper_InitializeDeviceMemoryInfo_temp_438, &VkDeviceMemory_uid_6156, nullptr));
    }

    // Create VkDeviceMemory_uid_6159
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_424[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_439[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_424,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_439[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6158,
        /* memory = */ VkDeviceMemory_uid_6159,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_439[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962561966080ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_439,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_439, VulkanHelper_InitializeDeviceMemoryInfo_temp_439, &VkDeviceMemory_uid_6159, nullptr));
    }

    // Create VkDeviceMemory_uid_6161
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_425[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_440[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_425,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_440[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6160,
        /* memory = */ VkDeviceMemory_uid_6161,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_440[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962562031616ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_440,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_440, VulkanHelper_InitializeDeviceMemoryInfo_temp_440, &VkDeviceMemory_uid_6161, nullptr));
    }

    // Create VkDeviceMemory_uid_6172
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_426[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_441[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_426,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_441[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6171,
        /* memory = */ VkDeviceMemory_uid_6172,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_441[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962572189696ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_441,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_441, VulkanHelper_InitializeDeviceMemoryInfo_temp_441, &VkDeviceMemory_uid_6172, nullptr));
    }

    // Create VkDeviceMemory_uid_6177
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_427[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_442[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_427,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_442[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6176,
        /* memory = */ VkDeviceMemory_uid_6177,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_442[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962571730944ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_442,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_442, VulkanHelper_InitializeDeviceMemoryInfo_temp_442, &VkDeviceMemory_uid_6177, nullptr));
    }

    // Create VkDeviceMemory_uid_6180
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_428[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_443[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_428,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_443[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6179,
        /* memory = */ VkDeviceMemory_uid_6180,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_443[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962562818048ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_443,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_443, VulkanHelper_InitializeDeviceMemoryInfo_temp_443, &VkDeviceMemory_uid_6180, nullptr));
    }

    // Create VkDeviceMemory_uid_6182
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_429[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_444[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_429,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_444[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6181,
        /* memory = */ VkDeviceMemory_uid_6182,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_444[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962562883584ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_444,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_444, VulkanHelper_InitializeDeviceMemoryInfo_temp_444, &VkDeviceMemory_uid_6182, nullptr));
    }

    // Create VkDeviceMemory_uid_6193
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_430[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_445[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_430,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_445[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6192,
        /* memory = */ VkDeviceMemory_uid_6193,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_445[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962573107200ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_445,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_445, VulkanHelper_InitializeDeviceMemoryInfo_temp_445, &VkDeviceMemory_uid_6193, nullptr));
    }

    // Create VkDeviceMemory_uid_6198
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_431[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_446[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_431,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_446[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6197,
        /* memory = */ VkDeviceMemory_uid_6198,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_446[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962572648448ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_446,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_446, VulkanHelper_InitializeDeviceMemoryInfo_temp_446, &VkDeviceMemory_uid_6198, nullptr));
    }

    // Create VkDeviceMemory_uid_6201
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_432[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_447[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_432,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_447[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6200,
        /* memory = */ VkDeviceMemory_uid_6201,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_447[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962562949120ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_447,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_447, VulkanHelper_InitializeDeviceMemoryInfo_temp_447, &VkDeviceMemory_uid_6201, nullptr));
    }

    // Create VkDeviceMemory_uid_6203
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_433[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_448[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_433,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_448[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6202,
        /* memory = */ VkDeviceMemory_uid_6203,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_448[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962563735552ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_448,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_448, VulkanHelper_InitializeDeviceMemoryInfo_temp_448, &VkDeviceMemory_uid_6203, nullptr));
    }

    // Create VkDeviceMemory_uid_6214
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_434[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_449[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_434,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_449[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6213,
        /* memory = */ VkDeviceMemory_uid_6214,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_449[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962574024704ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_449,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_449, VulkanHelper_InitializeDeviceMemoryInfo_temp_449, &VkDeviceMemory_uid_6214, nullptr));
    }

    // Create VkDeviceMemory_uid_6219
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_435[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_450[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_435,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_450[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6218,
        /* memory = */ VkDeviceMemory_uid_6219,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_450[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962573565952ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_450,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_450, VulkanHelper_InitializeDeviceMemoryInfo_temp_450, &VkDeviceMemory_uid_6219, nullptr));
    }

    // Create VkDeviceMemory_uid_6222
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_436[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_451[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_436,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_451[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6221,
        /* memory = */ VkDeviceMemory_uid_6222,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_451[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962563801088ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_451,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_451, VulkanHelper_InitializeDeviceMemoryInfo_temp_451, &VkDeviceMemory_uid_6222, nullptr));
    }

    // Create VkDeviceMemory_uid_6224
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_437[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_452[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_437,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_452[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6223,
        /* memory = */ VkDeviceMemory_uid_6224,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_452[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962563866624ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_452,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_452, VulkanHelper_InitializeDeviceMemoryInfo_temp_452, &VkDeviceMemory_uid_6224, nullptr));
    }

    // Create VkDeviceMemory_uid_6235
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_438[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_453[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_438,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_453[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6234,
        /* memory = */ VkDeviceMemory_uid_6235,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_453[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962574942208ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_453,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_453, VulkanHelper_InitializeDeviceMemoryInfo_temp_453, &VkDeviceMemory_uid_6235, nullptr));
    }

    // Create VkDeviceMemory_uid_6240
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_439[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_454[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_439,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_454[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6239,
        /* memory = */ VkDeviceMemory_uid_6240,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_454[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962574483456ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_454,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_454, VulkanHelper_InitializeDeviceMemoryInfo_temp_454, &VkDeviceMemory_uid_6240, nullptr));
    }

    // Create VkDeviceMemory_uid_6243
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_440[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_455[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_440,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_455[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6242,
        /* memory = */ VkDeviceMemory_uid_6243,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_455[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962564653056ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_455,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_455, VulkanHelper_InitializeDeviceMemoryInfo_temp_455, &VkDeviceMemory_uid_6243, nullptr));
    }

    // Create VkDeviceMemory_uid_6245
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_441[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_456[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_441,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_456[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6244,
        /* memory = */ VkDeviceMemory_uid_6245,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_456[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962564718592ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_456,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_456, VulkanHelper_InitializeDeviceMemoryInfo_temp_456, &VkDeviceMemory_uid_6245, nullptr));
    }

    // Create VkDeviceMemory_uid_6256
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_442[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_457[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_442,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_457[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6255,
        /* memory = */ VkDeviceMemory_uid_6256,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_457[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962575859712ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_457,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_457, VulkanHelper_InitializeDeviceMemoryInfo_temp_457, &VkDeviceMemory_uid_6256, nullptr));
    }

    // Create VkDeviceMemory_uid_6261
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_443[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_458[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_443,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_458[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6260,
        /* memory = */ VkDeviceMemory_uid_6261,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_458[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962575400960ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_458,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_458, VulkanHelper_InitializeDeviceMemoryInfo_temp_458, &VkDeviceMemory_uid_6261, nullptr));
    }

    // Create VkDeviceMemory_uid_6264
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_444[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_459[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_444,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_459[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6263,
        /* memory = */ VkDeviceMemory_uid_6264,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_459[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962564784128ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_459,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_459, VulkanHelper_InitializeDeviceMemoryInfo_temp_459, &VkDeviceMemory_uid_6264, nullptr));
    }

    // Create VkDeviceMemory_uid_6266
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_445[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_460[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_445,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_460[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6265,
        /* memory = */ VkDeviceMemory_uid_6266,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_460[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962565570560ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_460,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_460, VulkanHelper_InitializeDeviceMemoryInfo_temp_460, &VkDeviceMemory_uid_6266, nullptr));
    }

    // Create VkDeviceMemory_uid_6277
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_446[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_461[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_446,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_461[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6276,
        /* memory = */ VkDeviceMemory_uid_6277,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_461[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962576777216ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_461,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_461, VulkanHelper_InitializeDeviceMemoryInfo_temp_461, &VkDeviceMemory_uid_6277, nullptr));
    }

    // Create VkDeviceMemory_uid_6282
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_447[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_462[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_447,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_462[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6281,
        /* memory = */ VkDeviceMemory_uid_6282,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_462[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962576318464ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_462,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_462, VulkanHelper_InitializeDeviceMemoryInfo_temp_462, &VkDeviceMemory_uid_6282, nullptr));
    }

    // Create VkDeviceMemory_uid_6285
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_448[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_463[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_448,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_463[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6284,
        /* memory = */ VkDeviceMemory_uid_6285,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_463[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962565636096ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_463,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_463, VulkanHelper_InitializeDeviceMemoryInfo_temp_463, &VkDeviceMemory_uid_6285, nullptr));
    }

    // Create VkDeviceMemory_uid_6287
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_449[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_464[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_449,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_464[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6286,
        /* memory = */ VkDeviceMemory_uid_6287,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_464[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962565701632ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_464,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_464, VulkanHelper_InitializeDeviceMemoryInfo_temp_464, &VkDeviceMemory_uid_6287, nullptr));
    }

    // Create VkDeviceMemory_uid_6298
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_450[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_465[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_450,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_465[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6297,
        /* memory = */ VkDeviceMemory_uid_6298,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_465[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962577694720ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_465,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_465, VulkanHelper_InitializeDeviceMemoryInfo_temp_465, &VkDeviceMemory_uid_6298, nullptr));
    }

    // Create VkDeviceMemory_uid_6303
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_451[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_466[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_451,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_466[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6302,
        /* memory = */ VkDeviceMemory_uid_6303,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_466[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962577235968ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_466,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_466, VulkanHelper_InitializeDeviceMemoryInfo_temp_466, &VkDeviceMemory_uid_6303, nullptr));
    }

    // Create VkDeviceMemory_uid_6306
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_452[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_467[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_452,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_467[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6305,
        /* memory = */ VkDeviceMemory_uid_6306,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_467[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962566488064ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_467,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_467, VulkanHelper_InitializeDeviceMemoryInfo_temp_467, &VkDeviceMemory_uid_6306, nullptr));
    }

    // Create VkDeviceMemory_uid_6308
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_453[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_468[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_453,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_468[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6307,
        /* memory = */ VkDeviceMemory_uid_6308,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_468[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962566553600ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_468,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_468, VulkanHelper_InitializeDeviceMemoryInfo_temp_468, &VkDeviceMemory_uid_6308, nullptr));
    }

    // Create VkDeviceMemory_uid_6319
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_454[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_469[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_454,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_469[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6318,
        /* memory = */ VkDeviceMemory_uid_6319,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_469[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962578612224ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_469,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_469, VulkanHelper_InitializeDeviceMemoryInfo_temp_469, &VkDeviceMemory_uid_6319, nullptr));
    }

    // Create VkDeviceMemory_uid_6324
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_455[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_470[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_455,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_470[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6323,
        /* memory = */ VkDeviceMemory_uid_6324,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_470[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962578153472ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_470,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_470, VulkanHelper_InitializeDeviceMemoryInfo_temp_470, &VkDeviceMemory_uid_6324, nullptr));
    }

    // Create VkDeviceMemory_uid_6327
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_456[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_471[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_456,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_471[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6326,
        /* memory = */ VkDeviceMemory_uid_6327,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_471[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962566619136ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_471,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_471, VulkanHelper_InitializeDeviceMemoryInfo_temp_471, &VkDeviceMemory_uid_6327, nullptr));
    }

    // Create VkDeviceMemory_uid_6329
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_457[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_472[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_457,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_472[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6328,
        /* memory = */ VkDeviceMemory_uid_6329,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_472[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962567405568ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_472,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_472, VulkanHelper_InitializeDeviceMemoryInfo_temp_472, &VkDeviceMemory_uid_6329, nullptr));
    }

    // Create VkDeviceMemory_uid_6340
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_458[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_473[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_458,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_473[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6339,
        /* memory = */ VkDeviceMemory_uid_6340,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_473[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962579529728ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_473,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_473, VulkanHelper_InitializeDeviceMemoryInfo_temp_473, &VkDeviceMemory_uid_6340, nullptr));
    }

    // Create VkDeviceMemory_uid_6345
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_459[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_474[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_459,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_474[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6344,
        /* memory = */ VkDeviceMemory_uid_6345,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_474[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962579070976ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_474,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_474, VulkanHelper_InitializeDeviceMemoryInfo_temp_474, &VkDeviceMemory_uid_6345, nullptr));
    }

    // Create VkDeviceMemory_uid_6348
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_460[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_475[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_460,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_475[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6347,
        /* memory = */ VkDeviceMemory_uid_6348,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_475[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962567471104ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_475,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_475, VulkanHelper_InitializeDeviceMemoryInfo_temp_475, &VkDeviceMemory_uid_6348, nullptr));
    }

    // Create VkDeviceMemory_uid_6350
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_461[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_476[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_461,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_476[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6349,
        /* memory = */ VkDeviceMemory_uid_6350,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_476[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962567536640ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_476,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_476, VulkanHelper_InitializeDeviceMemoryInfo_temp_476, &VkDeviceMemory_uid_6350, nullptr));
    }

    // Create VkDeviceMemory_uid_6361
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_462[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_477[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_462,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_477[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6360,
        /* memory = */ VkDeviceMemory_uid_6361,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_477[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962568388608ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_477,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_477, VulkanHelper_InitializeDeviceMemoryInfo_temp_477, &VkDeviceMemory_uid_6361, nullptr));
    }

    // Create VkDeviceMemory_uid_6366
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_463[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_478[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_463,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_478[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6365,
        /* memory = */ VkDeviceMemory_uid_6366,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_478[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962568323072ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_478,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_478, VulkanHelper_InitializeDeviceMemoryInfo_temp_478, &VkDeviceMemory_uid_6366, nullptr));
    }

    // Create VkDeviceMemory_uid_6371
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_479[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 351232ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_479[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6370,
        /* memory = */ VkDeviceMemory_uid_6371,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_479[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962579988480ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_479,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_479, VulkanHelper_InitializeDeviceMemoryInfo_temp_479, &VkDeviceMemory_uid_6371, nullptr));
    }

    // Create VkDeviceMemory_uid_6387
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_464[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_480[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_464,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_480[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6386,
        /* memory = */ VkDeviceMemory_uid_6387,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_480[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962569240576ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_480,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_480, VulkanHelper_InitializeDeviceMemoryInfo_temp_480, &VkDeviceMemory_uid_6387, nullptr));
    }

    // Create VkDeviceMemory_uid_6392
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_465[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_481[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_465,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_481[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6391,
        /* memory = */ VkDeviceMemory_uid_6392,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_481[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962569306112ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_481,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_481, VulkanHelper_InitializeDeviceMemoryInfo_temp_481, &VkDeviceMemory_uid_6392, nullptr));
    }

    // Create VkDeviceMemory_uid_6404
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_466[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_482[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_466,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_482[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6403,
        /* memory = */ VkDeviceMemory_uid_6404,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_482[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962568454144ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_482,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_482, VulkanHelper_InitializeDeviceMemoryInfo_temp_482, &VkDeviceMemory_uid_6404, nullptr));
    }

    // Create VkDeviceMemory_uid_6409
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_467[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_483[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_467,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_483[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6408,
        /* memory = */ VkDeviceMemory_uid_6409,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_483[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962570158080ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_483,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_483, VulkanHelper_InitializeDeviceMemoryInfo_temp_483, &VkDeviceMemory_uid_6409, nullptr));
    }

    // Create VkDeviceMemory_uid_6421
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_468[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_484[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_468,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_484[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6420,
        /* memory = */ VkDeviceMemory_uid_6421,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_484[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962570223616ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_484,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_484, VulkanHelper_InitializeDeviceMemoryInfo_temp_484, &VkDeviceMemory_uid_6421, nullptr));
    }

    // Create VkDeviceMemory_uid_6426
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_469[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_485[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_469,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_485[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6425,
        /* memory = */ VkDeviceMemory_uid_6426,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_485[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962569371648ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_485,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_485, VulkanHelper_InitializeDeviceMemoryInfo_temp_485, &VkDeviceMemory_uid_6426, nullptr));
    }

    // Create VkDeviceMemory_uid_6581
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_470[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_486[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_470,
        /* allocationSize = */ 3072ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_486[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6580,
        /* memory = */ VkDeviceMemory_uid_6581,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_486[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962572124160ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_486,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_486, VulkanHelper_InitializeDeviceMemoryInfo_temp_486, &VkDeviceMemory_uid_6581, nullptr));
    }

    // Create VkDeviceMemory_uid_6584
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_471[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_487[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_471,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_487[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6583,
        /* memory = */ VkDeviceMemory_uid_6584,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_487[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962610528256ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_487,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_487, VulkanHelper_InitializeDeviceMemoryInfo_temp_487, &VkDeviceMemory_uid_6584, nullptr));
    }

    // Create VkDeviceMemory_uid_6587
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_472[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_488[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_472,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_488[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6586,
        /* memory = */ VkDeviceMemory_uid_6587,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_488[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962912256000ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_488,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_488, VulkanHelper_InitializeDeviceMemoryInfo_temp_488, &VkDeviceMemory_uid_6587, nullptr));
    }

    // Create VkDeviceMemory_uid_6590
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_473[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_489[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_473,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_489[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6589,
        /* memory = */ VkDeviceMemory_uid_6590,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_489[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962913370112ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_489,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_489, VulkanHelper_InitializeDeviceMemoryInfo_temp_489, &VkDeviceMemory_uid_6590, nullptr));
    }

    // Create VkDeviceMemory_uid_6593
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_474[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_490[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_474,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_490[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6592,
        /* memory = */ VkDeviceMemory_uid_6593,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_490[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962914484224ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_490,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_490, VulkanHelper_InitializeDeviceMemoryInfo_temp_490, &VkDeviceMemory_uid_6593, nullptr));
    }

    // Create VkDeviceMemory_uid_6596
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_475[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_491[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_475,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_491[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6595,
        /* memory = */ VkDeviceMemory_uid_6596,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_491[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962915598336ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_491,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_491, VulkanHelper_InitializeDeviceMemoryInfo_temp_491, &VkDeviceMemory_uid_6596, nullptr));
    }

    // Create VkDeviceMemory_uid_6599
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_476[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_492[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_476,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_492[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6598,
        /* memory = */ VkDeviceMemory_uid_6599,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_492[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962916712448ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_492,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_492, VulkanHelper_InitializeDeviceMemoryInfo_temp_492, &VkDeviceMemory_uid_6599, nullptr));
    }

    // Create VkDeviceMemory_uid_6602
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_477[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_493[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_477,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_493[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6601,
        /* memory = */ VkDeviceMemory_uid_6602,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_493[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962917826560ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_493,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_493, VulkanHelper_InitializeDeviceMemoryInfo_temp_493, &VkDeviceMemory_uid_6602, nullptr));
    }

    // Create VkDeviceMemory_uid_6605
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_478[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_494[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_478,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_494[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6604,
        /* memory = */ VkDeviceMemory_uid_6605,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_494[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962918940672ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_494,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_494, VulkanHelper_InitializeDeviceMemoryInfo_temp_494, &VkDeviceMemory_uid_6605, nullptr));
    }

    // Create VkDeviceMemory_uid_6608
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_479[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_495[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_479,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_495[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6607,
        /* memory = */ VkDeviceMemory_uid_6608,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_495[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962920054784ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_495,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_495, VulkanHelper_InitializeDeviceMemoryInfo_temp_495, &VkDeviceMemory_uid_6608, nullptr));
    }

    // Create VkDeviceMemory_uid_6611
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_480[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_496[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_480,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_496[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6610,
        /* memory = */ VkDeviceMemory_uid_6611,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_496[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962921168896ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_496,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_496, VulkanHelper_InitializeDeviceMemoryInfo_temp_496, &VkDeviceMemory_uid_6611, nullptr));
    }

    // Create VkDeviceMemory_uid_6614
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_481[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_497[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_481,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_497[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6613,
        /* memory = */ VkDeviceMemory_uid_6614,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_497[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962922283008ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_497,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_497, VulkanHelper_InitializeDeviceMemoryInfo_temp_497, &VkDeviceMemory_uid_6614, nullptr));
    }

    // Create VkDeviceMemory_uid_6617
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_482[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_498[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_482,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_498[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6616,
        /* memory = */ VkDeviceMemory_uid_6617,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_498[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962923397120ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_498,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_498, VulkanHelper_InitializeDeviceMemoryInfo_temp_498, &VkDeviceMemory_uid_6617, nullptr));
    }

    // Create VkDeviceMemory_uid_6620
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_483[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_499[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_483,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_499[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6619,
        /* memory = */ VkDeviceMemory_uid_6620,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_499[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962924511232ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_499,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_499, VulkanHelper_InitializeDeviceMemoryInfo_temp_499, &VkDeviceMemory_uid_6620, nullptr));
    }

    // Create VkDeviceMemory_uid_6623
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_484[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_500[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_484,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_500[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6622,
        /* memory = */ VkDeviceMemory_uid_6623,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_500[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962925625344ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_500,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_500, VulkanHelper_InitializeDeviceMemoryInfo_temp_500, &VkDeviceMemory_uid_6623, nullptr));
    }

    // Create VkDeviceMemory_uid_6626
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_485[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_501[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_485,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_501[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6625,
        /* memory = */ VkDeviceMemory_uid_6626,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_501[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962926739456ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_501,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_501, VulkanHelper_InitializeDeviceMemoryInfo_temp_501, &VkDeviceMemory_uid_6626, nullptr));
    }

    // Create VkDeviceMemory_uid_6629
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_486[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_502[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_486,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_502[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6628,
        /* memory = */ VkDeviceMemory_uid_6629,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_502[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962927853568ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_502,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_502, VulkanHelper_InitializeDeviceMemoryInfo_temp_502, &VkDeviceMemory_uid_6629, nullptr));
    }

    // Create VkDeviceMemory_uid_6632
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_487[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_503[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_487,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_503[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6631,
        /* memory = */ VkDeviceMemory_uid_6632,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_503[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962928967680ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_503,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_503, VulkanHelper_InitializeDeviceMemoryInfo_temp_503, &VkDeviceMemory_uid_6632, nullptr));
    }

    // Create VkDeviceMemory_uid_6635
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_488[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_504[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_488,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_504[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6634,
        /* memory = */ VkDeviceMemory_uid_6635,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_504[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962930081792ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_504,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_504, VulkanHelper_InitializeDeviceMemoryInfo_temp_504, &VkDeviceMemory_uid_6635, nullptr));
    }

    // Create VkDeviceMemory_uid_6638
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_489[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_505[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_489,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_505[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6637,
        /* memory = */ VkDeviceMemory_uid_6638,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_505[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962931195904ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_505,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_505, VulkanHelper_InitializeDeviceMemoryInfo_temp_505, &VkDeviceMemory_uid_6638, nullptr));
    }

    // Create VkDeviceMemory_uid_6641
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_490[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_506[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_490,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_506[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6640,
        /* memory = */ VkDeviceMemory_uid_6641,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_506[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962932310016ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_506,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_506, VulkanHelper_InitializeDeviceMemoryInfo_temp_506, &VkDeviceMemory_uid_6641, nullptr));
    }

    // Create VkDeviceMemory_uid_6644
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_491[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_507[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_491,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_507[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6643,
        /* memory = */ VkDeviceMemory_uid_6644,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_507[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962933424128ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_507,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_507, VulkanHelper_InitializeDeviceMemoryInfo_temp_507, &VkDeviceMemory_uid_6644, nullptr));
    }

    // Create VkDeviceMemory_uid_6647
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_492[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_508[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_492,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_508[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6646,
        /* memory = */ VkDeviceMemory_uid_6647,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_508[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962934538240ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_508,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_508, VulkanHelper_InitializeDeviceMemoryInfo_temp_508, &VkDeviceMemory_uid_6647, nullptr));
    }

    // Create VkDeviceMemory_uid_6650
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_493[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_509[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_493,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_509[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6649,
        /* memory = */ VkDeviceMemory_uid_6650,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_509[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962935652352ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_509,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_509, VulkanHelper_InitializeDeviceMemoryInfo_temp_509, &VkDeviceMemory_uid_6650, nullptr));
    }

    // Create VkDeviceMemory_uid_6653
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_494[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_510[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_494,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_510[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6652,
        /* memory = */ VkDeviceMemory_uid_6653,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_510[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962936766464ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_510,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_510, VulkanHelper_InitializeDeviceMemoryInfo_temp_510, &VkDeviceMemory_uid_6653, nullptr));
    }

    // Create VkDeviceMemory_uid_6656
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_495[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_511[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_495,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_511[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6655,
        /* memory = */ VkDeviceMemory_uid_6656,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_511[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962937880576ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_511,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_511, VulkanHelper_InitializeDeviceMemoryInfo_temp_511, &VkDeviceMemory_uid_6656, nullptr));
    }

    // Create VkDeviceMemory_uid_6659
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_496[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_512[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_496,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_512[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6658,
        /* memory = */ VkDeviceMemory_uid_6659,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_512[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962938994688ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_512,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_512, VulkanHelper_InitializeDeviceMemoryInfo_temp_512, &VkDeviceMemory_uid_6659, nullptr));
    }

    // Create VkDeviceMemory_uid_6662
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_497[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_513[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_497,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_513[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6661,
        /* memory = */ VkDeviceMemory_uid_6662,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_513[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962940108800ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_513,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_513, VulkanHelper_InitializeDeviceMemoryInfo_temp_513, &VkDeviceMemory_uid_6662, nullptr));
    }

    // Create VkDeviceMemory_uid_6665
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_498[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_514[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_498,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_514[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6664,
        /* memory = */ VkDeviceMemory_uid_6665,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_514[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962941222912ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_514,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_514, VulkanHelper_InitializeDeviceMemoryInfo_temp_514, &VkDeviceMemory_uid_6665, nullptr));
    }

    // Create VkDeviceMemory_uid_6668
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_499[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_515[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_499,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_515[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6667,
        /* memory = */ VkDeviceMemory_uid_6668,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_515[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962942337024ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_515,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_515, VulkanHelper_InitializeDeviceMemoryInfo_temp_515, &VkDeviceMemory_uid_6668, nullptr));
    }

    // Create VkDeviceMemory_uid_6671
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_500[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_516[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_500,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_516[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6670,
        /* memory = */ VkDeviceMemory_uid_6671,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_516[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962943451136ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_516,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_516, VulkanHelper_InitializeDeviceMemoryInfo_temp_516, &VkDeviceMemory_uid_6671, nullptr));
    }

    // Create VkDeviceMemory_uid_6674
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_501[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_517[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_501,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_517[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6673,
        /* memory = */ VkDeviceMemory_uid_6674,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_517[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962944565248ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_517,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_517, VulkanHelper_InitializeDeviceMemoryInfo_temp_517, &VkDeviceMemory_uid_6674, nullptr));
    }

    // Create VkDeviceMemory_uid_6677
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_502[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_518[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_502,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_518[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6676,
        /* memory = */ VkDeviceMemory_uid_6677,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_518[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962945679360ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_518,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_518, VulkanHelper_InitializeDeviceMemoryInfo_temp_518, &VkDeviceMemory_uid_6677, nullptr));
    }

    // Create VkDeviceMemory_uid_6680
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_503[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_519[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_503,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_519[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6679,
        /* memory = */ VkDeviceMemory_uid_6680,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_519[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962946793472ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_519,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_519, VulkanHelper_InitializeDeviceMemoryInfo_temp_519, &VkDeviceMemory_uid_6680, nullptr));
    }

    // Create VkDeviceMemory_uid_6683
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_504[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_520[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_504,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_520[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6682,
        /* memory = */ VkDeviceMemory_uid_6683,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_520[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962947907584ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_520,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_520, VulkanHelper_InitializeDeviceMemoryInfo_temp_520, &VkDeviceMemory_uid_6683, nullptr));
    }

    // Create VkDeviceMemory_uid_6686
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_505[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_521[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_505,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_521[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6685,
        /* memory = */ VkDeviceMemory_uid_6686,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_521[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962949021696ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_521,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_521, VulkanHelper_InitializeDeviceMemoryInfo_temp_521, &VkDeviceMemory_uid_6686, nullptr));
    }

    // Create VkDeviceMemory_uid_6689
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_506[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_522[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_506,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_522[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6688,
        /* memory = */ VkDeviceMemory_uid_6689,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_522[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962950135808ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_522,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_522, VulkanHelper_InitializeDeviceMemoryInfo_temp_522, &VkDeviceMemory_uid_6689, nullptr));
    }

    // Create VkDeviceMemory_uid_6692
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_507[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_523[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_507,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_523[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6691,
        /* memory = */ VkDeviceMemory_uid_6692,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_523[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962951249920ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_523,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_523, VulkanHelper_InitializeDeviceMemoryInfo_temp_523, &VkDeviceMemory_uid_6692, nullptr));
    }

    // Create VkDeviceMemory_uid_6695
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_508[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_524[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_508,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_524[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6694,
        /* memory = */ VkDeviceMemory_uid_6695,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_524[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962952364032ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_524,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_524, VulkanHelper_InitializeDeviceMemoryInfo_temp_524, &VkDeviceMemory_uid_6695, nullptr));
    }

    // Create VkDeviceMemory_uid_6698
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_509[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_525[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_509,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_525[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6697,
        /* memory = */ VkDeviceMemory_uid_6698,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_525[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962953478144ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_525,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_525, VulkanHelper_InitializeDeviceMemoryInfo_temp_525, &VkDeviceMemory_uid_6698, nullptr));
    }

    // Create VkDeviceMemory_uid_6701
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_510[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_526[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_510,
        /* allocationSize = */ 1092864ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_526[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6700,
        /* memory = */ VkDeviceMemory_uid_6701,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_526[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962954592256ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_526,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_526, VulkanHelper_InitializeDeviceMemoryInfo_temp_526, &VkDeviceMemory_uid_6701, nullptr));
    }

    // Create VkDeviceMemory_uid_6704
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_511[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_527[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_511,
        /* allocationSize = */ 64256ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_527[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6703,
        /* memory = */ VkDeviceMemory_uid_6704,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_527[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962573041664ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_527,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_527, VulkanHelper_InitializeDeviceMemoryInfo_temp_527, &VkDeviceMemory_uid_6704, nullptr));
    }

    // Create VkDeviceMemory_uid_6707
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_512[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_528[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_512,
        /* allocationSize = */ 64256ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_528[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6706,
        /* memory = */ VkDeviceMemory_uid_6707,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_528[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962573959168ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_528,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_528, VulkanHelper_InitializeDeviceMemoryInfo_temp_528, &VkDeviceMemory_uid_6707, nullptr));
    }

    // Create VkDeviceMemory_uid_6710
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_513[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_529[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_513,
        /* allocationSize = */ 64256ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_529[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6709,
        /* memory = */ VkDeviceMemory_uid_6710,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_529[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962574745600ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_529,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_529, VulkanHelper_InitializeDeviceMemoryInfo_temp_529, &VkDeviceMemory_uid_6710, nullptr));
    }

    // Create VkDeviceMemory_uid_6713
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_514[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_530[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_514,
        /* allocationSize = */ 1150720ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_530[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6712,
        /* memory = */ VkDeviceMemory_uid_6713,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_530[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962955706368ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_530,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_530, VulkanHelper_InitializeDeviceMemoryInfo_temp_530, &VkDeviceMemory_uid_6713, nullptr));
    }

    // Create VkDeviceMemory_uid_6716
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_515[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_531[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_515,
        /* allocationSize = */ 1125632ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_531[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6715,
        /* memory = */ VkDeviceMemory_uid_6716,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_531[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962956886016ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_531,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_531, VulkanHelper_InitializeDeviceMemoryInfo_temp_531, &VkDeviceMemory_uid_6716, nullptr));
    }

    // Create VkDeviceMemory_uid_6719
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_516[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_532[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_516,
        /* allocationSize = */ 2096384ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_532[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6718,
        /* memory = */ VkDeviceMemory_uid_6719,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_532[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962959769600ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_532,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_532, VulkanHelper_InitializeDeviceMemoryInfo_temp_532, &VkDeviceMemory_uid_6719, nullptr));
    }

    // Create VkDeviceMemory_uid_6722
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_517[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_533[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_517,
        /* allocationSize = */ 1724416ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_533[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6721,
        /* memory = */ VkDeviceMemory_uid_6722,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_533[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962961866752ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_533,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_533, VulkanHelper_InitializeDeviceMemoryInfo_temp_533, &VkDeviceMemory_uid_6722, nullptr));
    }

    // Create VkDeviceMemory_uid_6725
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_518[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_534[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_518,
        /* allocationSize = */ 2572288ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_534[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6724,
        /* memory = */ VkDeviceMemory_uid_6725,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_534[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962963636224ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_534,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_534, VulkanHelper_InitializeDeviceMemoryInfo_temp_534, &VkDeviceMemory_uid_6725, nullptr));
    }

    // Create VkDeviceMemory_uid_6734
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_519[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_535[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_519,
        /* allocationSize = */ 18688ull,
        /* memoryTypeIndex = */ 0u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_535[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6733,
        /* memory = */ VkDeviceMemory_uid_6734,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_535[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962574876672ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_535,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_535, VulkanHelper_InitializeDeviceMemoryInfo_temp_535, &VkDeviceMemory_uid_6734, nullptr));
    }

    // Create VkDeviceMemory_uid_6763
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_520[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_536[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_520,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_536[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6762,
        /* memory = */ VkDeviceMemory_uid_6763,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_536[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962570289152ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_536,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_536, VulkanHelper_InitializeDeviceMemoryInfo_temp_536, &VkDeviceMemory_uid_6763, nullptr));
    }

    // Create VkDeviceMemory_uid_6888
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_537[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 23396352ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_537[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6887,
        /* memory = */ VkDeviceMemory_uid_6888,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_537[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962335604736ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_537,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_537, VulkanHelper_InitializeDeviceMemoryInfo_temp_537, &VkDeviceMemory_uid_6888, nullptr));
    }

    // Create VkDeviceMemory_uid_6893
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_538[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 5849088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_538[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6892,
        /* memory = */ VkDeviceMemory_uid_6893,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_538[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962892595200ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_538,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_538, VulkanHelper_InitializeDeviceMemoryInfo_temp_538, &VkDeviceMemory_uid_6893, nullptr));
    }

    // Create VkDeviceMemory_uid_6910
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_539[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 5849088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_539[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6909,
        /* memory = */ VkDeviceMemory_uid_6910,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_539[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962138800128ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_539,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_539, VulkanHelper_InitializeDeviceMemoryInfo_temp_539, &VkDeviceMemory_uid_6910, nullptr));
    }

    // Create VkDeviceMemory_uid_6919
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_540[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 65175552ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_540[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6918,
        /* memory = */ VkDeviceMemory_uid_6919,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_540[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962408939520ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_540,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_540, VulkanHelper_InitializeDeviceMemoryInfo_temp_540, &VkDeviceMemory_uid_6919, nullptr));
    }

    // Create VkDeviceMemory_uid_6923
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_541[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 5849088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_541[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6922,
        /* memory = */ VkDeviceMemory_uid_6923,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_541[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962898493440ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_541,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_541, VulkanHelper_InitializeDeviceMemoryInfo_temp_541, &VkDeviceMemory_uid_6923, nullptr));
    }

    // Create VkDeviceMemory_uid_6940
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_542[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 5849088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_542[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_6939,
        /* memory = */ VkDeviceMemory_uid_6940,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_542[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962886107136ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_542,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_542, VulkanHelper_InitializeDeviceMemoryInfo_temp_542, &VkDeviceMemory_uid_6940, nullptr));
    }

    // Create VkDeviceMemory_uid_6947
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_543[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 320ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_543[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6946,
        /* memory = */ VkDeviceMemory_uid_6947,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_543[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962572976128ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_543,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_543, VulkanHelper_InitializeDeviceMemoryInfo_temp_543, &VkDeviceMemory_uid_6947, nullptr));
    }

    // Create VkDeviceMemory_uid_6949
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_544[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_544[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6948,
        /* memory = */ VkDeviceMemory_uid_6949,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_544[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962573828096ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_544,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_544, VulkanHelper_InitializeDeviceMemoryInfo_temp_544, &VkDeviceMemory_uid_6949, nullptr));
    }

    // Create VkDeviceMemory_uid_6955
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_521[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_545[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_521,
        /* allocationSize = */ 3200000ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_545[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6954,
        /* memory = */ VkDeviceMemory_uid_6955,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_545[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962592178176ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_545,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_545, VulkanHelper_InitializeDeviceMemoryInfo_temp_545, &VkDeviceMemory_uid_6955, nullptr));
    }

    // Create VkDeviceMemory_uid_6957
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_522[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_546[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_522,
        /* allocationSize = */ 8000ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_546[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6956,
        /* memory = */ VkDeviceMemory_uid_6957,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_546[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962573893632ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_546,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_546, VulkanHelper_InitializeDeviceMemoryInfo_temp_546, &VkDeviceMemory_uid_6957, nullptr));
    }

    // Create VkDeviceMemory_uid_6959
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_523[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_547[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_523,
        /* allocationSize = */ 400000ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_547[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6958,
        /* memory = */ VkDeviceMemory_uid_6959,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_547[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962892005376ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_547,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_547, VulkanHelper_InitializeDeviceMemoryInfo_temp_547, &VkDeviceMemory_uid_6959, nullptr));
    }

    // Create VkDeviceMemory_uid_6974
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_524[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_548[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_524,
        /* allocationSize = */ 640ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_548[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6973,
        /* memory = */ VkDeviceMemory_uid_6974,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_548[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962574811136ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_548,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_548, VulkanHelper_InitializeDeviceMemoryInfo_temp_548, &VkDeviceMemory_uid_6974, nullptr));
    }

    // Create VkDeviceMemory_uid_6980
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_525[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_549[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_525,
        /* allocationSize = */ 8000ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_549[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6979,
        /* memory = */ VkDeviceMemory_uid_6980,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_549[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962571993088ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_549,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_549, VulkanHelper_InitializeDeviceMemoryInfo_temp_549, &VkDeviceMemory_uid_6980, nullptr));
    }

    // Create VkDeviceMemory_uid_6982
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_526[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_550[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_526,
        /* allocationSize = */ 400000ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_550[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_6981,
        /* memory = */ VkDeviceMemory_uid_6982,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_550[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962360770560ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_550,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_550, VulkanHelper_InitializeDeviceMemoryInfo_temp_550, &VkDeviceMemory_uid_6982, nullptr));
    }

    // Create VkDeviceMemory_uid_7269
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_551[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 274688ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_551[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_7268,
        /* memory = */ VkDeviceMemory_uid_7269,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_551[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962173009920ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_551,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_551, VulkanHelper_InitializeDeviceMemoryInfo_temp_551, &VkDeviceMemory_uid_7269, nullptr));
    }

    // Create VkDeviceMemory_uid_7290
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_552[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 66560ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_552[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_7289,
        /* memory = */ VkDeviceMemory_uid_7290,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_552[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962576580608ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_552,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_552, VulkanHelper_InitializeDeviceMemoryInfo_temp_552, &VkDeviceMemory_uid_7290, nullptr));
    }

    // Create VkAccelerationStructureKHR_uid_6582
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_51[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6580,
        /* offset = */ 0ull,
        /* size = */ 2944ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_151[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x8C, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 3u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x8B, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_51[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_151,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_271[1] = { 2u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_51[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 2944ull,
        /* updateScratchSize = */ 1664ull,
        /* buildScratchSize = */ 1664ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_51, 0x000000e01dc50000, VkAccelerationStructureBuildGeometryInfoKHR_temp_51, uint32_t_temp_271, &VkAccelerationStructureKHR_uid_6582, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_51, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6582), 6582ull));
    }

    // Create VkAccelerationStructureKHR_uid_6585
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_52[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6583,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_152[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x36, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x2F, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_52[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_152,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_272[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_52[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_52, 0x000000e0200f0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_52, uint32_t_temp_272, &VkAccelerationStructureKHR_uid_6585, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_52, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6585), 6585ull));
    }

    // Create VkAccelerationStructureKHR_uid_6588
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_53[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6586,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_153[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x28, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x21, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_53[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_153,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_273[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_53[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_53, 0x000000e0320b0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_53, uint32_t_temp_273, &VkAccelerationStructureKHR_uid_6588, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_53, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6588), 6588ull));
    }

    // Create VkAccelerationStructureKHR_uid_6591
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_54[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6589,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_154[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x1A, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x13, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_54[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_154,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_274[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_54[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_54, 0x000000e0321c0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_54, uint32_t_temp_274, &VkAccelerationStructureKHR_uid_6591, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_54, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6591), 6591ull));
    }

    // Create VkAccelerationStructureKHR_uid_6594
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_55[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6592,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_155[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x0C, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x05, 0x1E, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_55[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_155,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_275[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_55[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_55, 0x000000e0322d0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_55, uint32_t_temp_275, &VkAccelerationStructureKHR_uid_6594, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_55, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6594), 6594ull));
    }

    // Create VkAccelerationStructureKHR_uid_6597
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_56[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6595,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_156[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xFE, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xF7, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_56[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_156,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_276[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_56[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_56, 0x000000e0323e0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_56, uint32_t_temp_276, &VkAccelerationStructureKHR_uid_6597, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_56, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6597), 6597ull));
    }

    // Create VkAccelerationStructureKHR_uid_6600
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_57[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6598,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_157[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xF0, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xE9, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_57[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_157,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_277[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_57[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_57, 0x000000e0324f0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_57, uint32_t_temp_277, &VkAccelerationStructureKHR_uid_6600, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_57, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6600), 6600ull));
    }

    // Create VkAccelerationStructureKHR_uid_6603
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_58[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6601,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_158[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xE2, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xDB, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_58[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_158,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_278[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_58[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_58, 0x000000e032600000, VkAccelerationStructureBuildGeometryInfoKHR_temp_58, uint32_t_temp_278, &VkAccelerationStructureKHR_uid_6603, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_58, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6603), 6603ull));
    }

    // Create VkAccelerationStructureKHR_uid_6606
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_59[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6604,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_159[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xD4, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xCD, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_59[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_159,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_279[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_59[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_59, 0x000000e032710000, VkAccelerationStructureBuildGeometryInfoKHR_temp_59, uint32_t_temp_279, &VkAccelerationStructureKHR_uid_6606, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_59, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6606), 6606ull));
    }

    // Create VkAccelerationStructureKHR_uid_6609
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_60[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6607,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_160[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xC6, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xBF, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_60[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_160,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_280[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_60[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_60, 0x000000e032820000, VkAccelerationStructureBuildGeometryInfoKHR_temp_60, uint32_t_temp_280, &VkAccelerationStructureKHR_uid_6609, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_60, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6609), 6609ull));
    }

    // Create VkAccelerationStructureKHR_uid_6612
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_61[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6610,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_161[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xB8, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xB1, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_61[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_161,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_281[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_61[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_61, 0x000000e032930000, VkAccelerationStructureBuildGeometryInfoKHR_temp_61, uint32_t_temp_281, &VkAccelerationStructureKHR_uid_6612, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_61, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6612), 6612ull));
    }

    // Create VkAccelerationStructureKHR_uid_6615
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_62[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6613,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_162[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xAA, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xA3, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_62[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_162,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_282[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_62[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_62, 0x000000e032a40000, VkAccelerationStructureBuildGeometryInfoKHR_temp_62, uint32_t_temp_282, &VkAccelerationStructureKHR_uid_6615, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_62, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6615), 6615ull));
    }

    // Create VkAccelerationStructureKHR_uid_6618
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_63[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6616,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_163[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x9C, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x95, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_63[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_163,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_283[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_63[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_63, 0x000000e032b50000, VkAccelerationStructureBuildGeometryInfoKHR_temp_63, uint32_t_temp_283, &VkAccelerationStructureKHR_uid_6618, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_63, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6618), 6618ull));
    }

    // Create VkAccelerationStructureKHR_uid_6621
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_64[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6619,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_164[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x8E, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x87, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_64[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_164,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_284[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_64[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_64, 0x000000e032c60000, VkAccelerationStructureBuildGeometryInfoKHR_temp_64, uint32_t_temp_284, &VkAccelerationStructureKHR_uid_6621, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_64, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6621), 6621ull));
    }

    // Create VkAccelerationStructureKHR_uid_6624
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_65[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6622,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_165[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x80, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x79, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_65[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_165,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_285[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_65[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_65, 0x000000e032d70000, VkAccelerationStructureBuildGeometryInfoKHR_temp_65, uint32_t_temp_285, &VkAccelerationStructureKHR_uid_6624, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_65, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6624), 6624ull));
    }

    // Create VkAccelerationStructureKHR_uid_6627
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_66[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6625,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_166[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x72, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x6B, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_66[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_166,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_286[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_66[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_66, 0x000000e032e80000, VkAccelerationStructureBuildGeometryInfoKHR_temp_66, uint32_t_temp_286, &VkAccelerationStructureKHR_uid_6627, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_66, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6627), 6627ull));
    }

    // Create VkAccelerationStructureKHR_uid_6630
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_67[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6628,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_167[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x64, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x5D, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_67[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_167,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_287[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_67[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_67, 0x000000e032f90000, VkAccelerationStructureBuildGeometryInfoKHR_temp_67, uint32_t_temp_287, &VkAccelerationStructureKHR_uid_6630, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_67, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6630), 6630ull));
    }

    // Create VkAccelerationStructureKHR_uid_6633
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_68[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6631,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_168[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x56, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x4F, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_68[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_168,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_288[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_68[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_68, 0x000000e0330a0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_68, uint32_t_temp_288, &VkAccelerationStructureKHR_uid_6633, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_68, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6633), 6633ull));
    }

    // Create VkAccelerationStructureKHR_uid_6636
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_69[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6634,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_169[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x48, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x41, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_69[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_169,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_289[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_69[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_69, 0x000000e0331b0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_69, uint32_t_temp_289, &VkAccelerationStructureKHR_uid_6636, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_69, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6636), 6636ull));
    }

    // Create VkAccelerationStructureKHR_uid_6639
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_70[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6637,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_170[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x3A, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x33, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_70[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_170,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_290[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_70[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_70, 0x000000e0332c0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_70, uint32_t_temp_290, &VkAccelerationStructureKHR_uid_6639, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_70, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6639), 6639ull));
    }

    // Create VkAccelerationStructureKHR_uid_6642
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_71[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6640,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_171[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x2C, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x25, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_71[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_171,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_291[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_71[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_71, 0x000000e0333d0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_71, uint32_t_temp_291, &VkAccelerationStructureKHR_uid_6642, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_71, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6642), 6642ull));
    }

    // Create VkAccelerationStructureKHR_uid_6645
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_72[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6643,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_172[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x1E, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x17, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_72[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_172,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_292[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_72[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_72, 0x000000e0334e0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_72, uint32_t_temp_292, &VkAccelerationStructureKHR_uid_6645, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_72, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6645), 6645ull));
    }

    // Create VkAccelerationStructureKHR_uid_6648
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_73[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6646,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_173[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x10, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x09, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_73[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_173,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_293[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_73[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_73, 0x000000e0335f0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_73, uint32_t_temp_293, &VkAccelerationStructureKHR_uid_6648, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_73, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6648), 6648ull));
    }

    // Create VkAccelerationStructureKHR_uid_6651
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_74[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6649,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_174[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x02, 0x1D, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xFB, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_74[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_174,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_294[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_74[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_74, 0x000000e033700000, VkAccelerationStructureBuildGeometryInfoKHR_temp_74, uint32_t_temp_294, &VkAccelerationStructureKHR_uid_6651, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_74, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6651), 6651ull));
    }

    // Create VkAccelerationStructureKHR_uid_6654
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_75[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6652,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_175[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xF4, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xED, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_75[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_175,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_295[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_75[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_75, 0x000000e033810000, VkAccelerationStructureBuildGeometryInfoKHR_temp_75, uint32_t_temp_295, &VkAccelerationStructureKHR_uid_6654, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_75, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6654), 6654ull));
    }

    // Create VkAccelerationStructureKHR_uid_6657
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_76[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6655,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_176[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xE6, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xDF, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_76[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_176,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_296[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_76[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_76, 0x000000e033920000, VkAccelerationStructureBuildGeometryInfoKHR_temp_76, uint32_t_temp_296, &VkAccelerationStructureKHR_uid_6657, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_76, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6657), 6657ull));
    }

    // Create VkAccelerationStructureKHR_uid_6660
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_77[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6658,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_177[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xD8, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xD1, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_77[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_177,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_297[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_77[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_77, 0x000000e033a30000, VkAccelerationStructureBuildGeometryInfoKHR_temp_77, uint32_t_temp_297, &VkAccelerationStructureKHR_uid_6660, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_77, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6660), 6660ull));
    }

    // Create VkAccelerationStructureKHR_uid_6663
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_78[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6661,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_178[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xCA, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xC3, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_78[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_178,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_298[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_78[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_78, 0x000000e033b40000, VkAccelerationStructureBuildGeometryInfoKHR_temp_78, uint32_t_temp_298, &VkAccelerationStructureKHR_uid_6663, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_78, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6663), 6663ull));
    }

    // Create VkAccelerationStructureKHR_uid_6666
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_79[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6664,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_179[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xBC, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xB5, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_79[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_179,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_299[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_79[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_79, 0x000000e033c50000, VkAccelerationStructureBuildGeometryInfoKHR_temp_79, uint32_t_temp_299, &VkAccelerationStructureKHR_uid_6666, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_79, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6666), 6666ull));
    }

    // Create VkAccelerationStructureKHR_uid_6669
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_80[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6667,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_180[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xAE, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xA7, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_80[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_180,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_300[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_80[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_80, 0x000000e033d60000, VkAccelerationStructureBuildGeometryInfoKHR_temp_80, uint32_t_temp_300, &VkAccelerationStructureKHR_uid_6669, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_80, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6669), 6669ull));
    }

    // Create VkAccelerationStructureKHR_uid_6672
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_81[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6670,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_181[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xA0, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x99, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_81[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_181,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_301[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_81[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_81, 0x000000e033e70000, VkAccelerationStructureBuildGeometryInfoKHR_temp_81, uint32_t_temp_301, &VkAccelerationStructureKHR_uid_6672, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_81, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6672), 6672ull));
    }

    // Create VkAccelerationStructureKHR_uid_6675
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_82[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6673,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_182[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x92, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x8B, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_82[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_182,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_302[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_82[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_82, 0x000000e033f80000, VkAccelerationStructureBuildGeometryInfoKHR_temp_82, uint32_t_temp_302, &VkAccelerationStructureKHR_uid_6675, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_82, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6675), 6675ull));
    }

    // Create VkAccelerationStructureKHR_uid_6678
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_83[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6676,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_183[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x84, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x7D, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_83[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_183,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_303[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_83[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_83, 0x000000e034090000, VkAccelerationStructureBuildGeometryInfoKHR_temp_83, uint32_t_temp_303, &VkAccelerationStructureKHR_uid_6678, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_83, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6678), 6678ull));
    }

    // Create VkAccelerationStructureKHR_uid_6681
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_84[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6679,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_184[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x76, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x6F, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_84[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_184,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_304[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_84[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_84, 0x000000e0341a0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_84, uint32_t_temp_304, &VkAccelerationStructureKHR_uid_6681, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_84, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6681), 6681ull));
    }

    // Create VkAccelerationStructureKHR_uid_6684
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_85[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6682,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_185[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x68, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x61, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_85[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_185,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_305[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_85[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_85, 0x000000e0342b0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_85, uint32_t_temp_305, &VkAccelerationStructureKHR_uid_6684, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_85, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6684), 6684ull));
    }

    // Create VkAccelerationStructureKHR_uid_6687
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_86[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6685,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_186[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x5A, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x53, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_86[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_186,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_306[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_86[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_86, 0x000000e0343c0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_86, uint32_t_temp_306, &VkAccelerationStructureKHR_uid_6687, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_86, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6687), 6687ull));
    }

    // Create VkAccelerationStructureKHR_uid_6690
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_87[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6688,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_187[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x4C, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x45, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_87[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_187,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_307[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_87[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_87, 0x000000e0344d0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_87, uint32_t_temp_307, &VkAccelerationStructureKHR_uid_6690, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_87, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6690), 6690ull));
    }

    // Create VkAccelerationStructureKHR_uid_6693
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_88[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6691,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_188[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x3E, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x37, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_88[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_188,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_308[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_88[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_88, 0x000000e0345e0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_88, uint32_t_temp_308, &VkAccelerationStructureKHR_uid_6693, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_88, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6693), 6693ull));
    }

    // Create VkAccelerationStructureKHR_uid_6696
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_89[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6694,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_189[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x30, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x22, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_89[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_189,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_309[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_89[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_89, 0x000000e0346f0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_89, uint32_t_temp_309, &VkAccelerationStructureKHR_uid_6696, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_89, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6696), 6696ull));
    }

    // Create VkAccelerationStructureKHR_uid_6699
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_90[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6697,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_190[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x29, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xCA, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_90[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_190,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_310[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_90[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_90, 0x000000e034800000, VkAccelerationStructureBuildGeometryInfoKHR_temp_90, uint32_t_temp_310, &VkAccelerationStructureKHR_uid_6699, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_90, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6699), 6699ull));
    }

    // Create VkAccelerationStructureKHR_uid_6702
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_91[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6700,
        /* offset = */ 0ull,
        /* size = */ 1092736ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_191[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xF4, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xC6, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_91[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_191,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_311[1] = { 19602u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_91[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1245440ull,
        /* updateScratchSize = */ 80000ull,
        /* buildScratchSize = */ 80000ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_91, 0x000000e034910000, VkAccelerationStructureBuildGeometryInfoKHR_temp_91, uint32_t_temp_311, &VkAccelerationStructureKHR_uid_6702, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_91, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6702), 6702ull));
    }

    // Create VkAccelerationStructureKHR_uid_6705
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_92[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6703,
        /* offset = */ 0ull,
        /* size = */ 64128ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_192[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x49, 0x11, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 567u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x4A, 0x11, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_92[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_192,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_312[1] = { 1062u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_92[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 72576ull,
        /* updateScratchSize = */ 5888ull,
        /* buildScratchSize = */ 5888ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_92, 0x000000e01dd30000, VkAccelerationStructureBuildGeometryInfoKHR_temp_92, uint32_t_temp_312, &VkAccelerationStructureKHR_uid_6705, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_92, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6705), 6705ull));
    }

    // Create VkAccelerationStructureKHR_uid_6708
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_93[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6706,
        /* offset = */ 0ull,
        /* size = */ 64128ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_193[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x73, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 567u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x72, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_93[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_193,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_313[1] = { 1062u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_93[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 72576ull,
        /* updateScratchSize = */ 5888ull,
        /* buildScratchSize = */ 5888ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_93, 0x000000e01de10000, VkAccelerationStructureBuildGeometryInfoKHR_temp_93, uint32_t_temp_313, &VkAccelerationStructureKHR_uid_6708, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_93, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6708), 6708ull));
    }

    // Create VkAccelerationStructureKHR_uid_6711
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_94[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6709,
        /* offset = */ 0ull,
        /* size = */ 64128ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_194[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x7E, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 567u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x7D, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_94[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_194,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_314[1] = { 1062u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_94[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 72576ull,
        /* updateScratchSize = */ 5888ull,
        /* buildScratchSize = */ 5888ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_94, 0x000000e01ded0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_94, uint32_t_temp_314, &VkAccelerationStructureKHR_uid_6711, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_94, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6711), 6711ull));
    }

    // Create VkAccelerationStructureKHR_uid_6714
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_95[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6712,
        /* offset = */ 0ull,
        /* size = */ 1150592ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_195[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x38, 0x11, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 21263u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x75, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_95[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_195,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_315[1] = { 19907u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_95[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1262592ull,
        /* updateScratchSize = */ 81280ull,
        /* buildScratchSize = */ 81280ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_95, 0x000000e034a20000, VkAccelerationStructureBuildGeometryInfoKHR_temp_95, uint32_t_temp_315, &VkAccelerationStructureKHR_uid_6714, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_95, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6714), 6714ull));
    }

    // Create VkAccelerationStructureKHR_uid_6717
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_96[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6715,
        /* offset = */ 0ull,
        /* size = */ 1125632ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_196[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x4F, 0x11, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 11412u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x79, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_96[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_196,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_316[1] = { 19522u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_96[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1238400ull,
        /* updateScratchSize = */ 79744ull,
        /* buildScratchSize = */ 79744ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_96, 0x000000e034b40000, VkAccelerationStructureBuildGeometryInfoKHR_temp_96, uint32_t_temp_316, &VkAccelerationStructureKHR_uid_6717, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_96, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6717), 6717ull));
    }

    // Create VkAccelerationStructureKHR_uid_6720
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_97[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6718,
        /* offset = */ 0ull,
        /* size = */ 2096256ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_197[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xD0, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 22498u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x57, 0x11, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_97[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_197,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_317[1] = { 36212u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_97[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 2296960ull,
        /* updateScratchSize = */ 146432ull,
        /* buildScratchSize = */ 146432ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_97, 0x000000e034e00000, VkAccelerationStructureBuildGeometryInfoKHR_temp_97, uint32_t_temp_317, &VkAccelerationStructureKHR_uid_6720, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_97, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6720), 6720ull));
    }

    // Create VkAccelerationStructureKHR_uid_6723
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_98[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6721,
        /* offset = */ 0ull,
        /* size = */ 1724416ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_198[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xE0, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 16152u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xC0, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_98[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_198,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_318[1] = { 30027u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_98[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 1904256ull,
        /* updateScratchSize = */ 121728ull,
        /* buildScratchSize = */ 121728ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_98, 0x000000e035000000, VkAccelerationStructureBuildGeometryInfoKHR_temp_98, uint32_t_temp_318, &VkAccelerationStructureKHR_uid_6723, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_98, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6723), 6723ull));
    }

    // Create VkAccelerationStructureKHR_uid_6726
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_99[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6724,
        /* offset = */ 0ull,
        /* size = */ 2572288ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_199[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x10, 0x1C, 0xE0, 0x00, 0x00, 0x00),
        /* vertexStride = */ 44ull,
        /* maxVertex = */ 26639u,
        /* indexType = */ VK_INDEX_TYPE_UINT32,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xEB, 0x05, 0xE0, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_99[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_199,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_319[1] = { 44820u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_99[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 2836992ull,
        /* updateScratchSize = */ 180864ull,
        /* buildScratchSize = */ 180864ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_99, 0x000000e0351b0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_99, uint32_t_temp_319, &VkAccelerationStructureKHR_uid_6726, VK_TRUE, VkAccelerationStructureBuildSizesInfoKHR_temp_99, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6726), 6726ull));
    }

    // Create VkAccelerationStructureKHR_uid_6735
    {
        BEGIN_DATA_SCOPE();

        static VkAccelerationStructureCreateInfoKHR VkAccelerationStructureCreateInfoKHR_temp_100[1] = { VkAccelerationStructureCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* createFlags = */ VkAccelerationStructureCreateFlagsKHR(0),
        /* buffer = */ VkBuffer_uid_6733,
        /* offset = */ 0ull,
        /* size = */ 18560ull,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
        /* deviceAddress = */ 0ull} };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_pGeometries_200[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_INSTANCES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryInstancesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR,
        /* pNext = */ nullptr,
        /* arrayOfPointers = */ 0u,
        /* data = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0xA9, 0x1D, 0xE0, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(0)} };
        static VkAccelerationStructureBuildGeometryInfoKHR VkAccelerationStructureBuildGeometryInfoKHR_temp_100[1] = { VkAccelerationStructureBuildGeometryInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
        /* flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
        /* mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        /* srcAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* dstAccelerationStructure = */ VkAccelerationStructureKHR(VK_NULL_HANDLE),
        /* geometryCount = */ 1u,
        /* pGeometries = */ VkAccelerationStructureGeometryKHR_pGeometries_200,
        /* ppGeometries = */ nullptr,
        /* scratchData = */ NV_TO_UNION(VkDeviceOrHostAddressKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} };
        static uint32_t uint32_t_temp_320[1] = { 49u };
        static VkAccelerationStructureBuildSizesInfoKHR VkAccelerationStructureBuildSizesInfoKHR_temp_100[1] = { VkAccelerationStructureBuildSizesInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
        /* pNext = */ nullptr,
        /* accelerationStructureSize = */ 18560ull,
        /* updateScratchSize = */ 3200ull,
        /* buildScratchSize = */ 5888ull} };
        NV_VK_REPLAY(VulkanHelper_CreateAccelerationStructure4KHR(VkDevice_uid_4, VkAccelerationStructureCreateInfoKHR_temp_100, 0x000000e01def0000, VkAccelerationStructureBuildGeometryInfoKHR_temp_100, uint32_t_temp_320, &VkAccelerationStructureKHR_uid_6735, VK_FALSE, VkAccelerationStructureBuildSizesInfoKHR_temp_100, 0ull, nullptr));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, uint64_t(VkAccelerationStructureKHR_uid_6735), 6735ull));
    }

    // Create VkDescriptorPool_uid_26
    {
        static VkDescriptorPoolSize VkDescriptorPoolSize_pPoolSizes_2[4] = { VkDescriptorPoolSize{
        /* type = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1000u}, VkDescriptorPoolSize{
        /* type = */ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        /* descriptorCount = */ 1000u}, VkDescriptorPoolSize{
        /* type = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1000u}, VkDescriptorPoolSize{
        /* type = */ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
        /* descriptorCount = */ 1000u} };
        static VkDescriptorPoolCreateInfo VkDescriptorPoolCreateInfo_temp_2[1] = { VkDescriptorPoolCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkDescriptorPoolCreateFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT | VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT),
        /* maxSets = */ 5000u,
        /* poolSizeCount = */ 4u,
        /* pPoolSizes = */ VkDescriptorPoolSize_pPoolSizes_2} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorPool(VkDevice_uid_4, VkDescriptorPoolCreateInfo_temp_2, nullptr, &VkDescriptorPool_uid_26));
    }

    // Create VkCommandPool_uid_7
    {
        static VkCommandPoolCreateInfo VkCommandPoolCreateInfo_temp_2[1] = { VkCommandPoolCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkCommandPoolCreateFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT),
        /* queueFamilyIndex = */ 0u} };
        NV_VK_REPLAY(VulkanReplay_CreateCommandPool(VkDevice_uid_4, VkCommandPoolCreateInfo_temp_2, nullptr, &VkCommandPool_uid_7));
    }

    // Create VkImageView_uid_18
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_11[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_15,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_11, 0ull, nullptr, &VkImageView_uid_18));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_18), 18ull));
    }

    // Create VkImageView_uid_5061
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_12[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_5056,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 13u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_12, 0ull, nullptr, &VkImageView_uid_5061));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_5061), 5061ull));
    }

    // Create VkImageView_uid_5292
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_13[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_5290,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_13, 0ull, nullptr, &VkImageView_uid_5292));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_5292), 5292ull));
    }

    // Create VkImageView_uid_6375
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_14[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6370,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 9u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_14, 0ull, nullptr, &VkImageView_uid_6375));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6375), 6375ull));
    }

    // Create VkImageView_uid_6889
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_15[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6887,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R32G32B32A32_SFLOAT,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_15, 0ull, nullptr, &VkImageView_uid_6889));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6889), 6889ull));
    }

    // Create VkImageView_uid_6894
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_16[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6892,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_16, 0ull, nullptr, &VkImageView_uid_6894));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6894), 6894ull));
    }

    // Create VkImageView_uid_6911
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_17[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6909,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_17, 0ull, nullptr, &VkImageView_uid_6911));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6911), 6911ull));
    }

    // Create VkImageView_uid_6920
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_18[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6918,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_CUBE,
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 6u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_18, 0ull, nullptr, &VkImageView_uid_6920));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6920), 6920ull));
    }

    // Create VkImageView_uid_6924
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_19[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6922,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_19, 0ull, nullptr, &VkImageView_uid_6924));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6924), 6924ull));
    }

    // Create VkImageView_uid_6941
    {
        static VkImageViewCreateInfo VkImageViewCreateInfo_temp_20[1] = { VkImageViewCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageViewCreateFlags(0),
        /* image = */ VkImage_uid_6939,
        /* viewType = */ VK_IMAGE_VIEW_TYPE_2D,
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* components = */ VkComponentMapping{
        /* r = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* g = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* b = */ VK_COMPONENT_SWIZZLE_IDENTITY,
        /* a = */ VK_COMPONENT_SWIZZLE_IDENTITY},
        /* subresourceRange = */ VkImageSubresourceRange{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* baseMipLevel = */ 0u,
        /* levelCount = */ 1u,
        /* baseArrayLayer = */ 0u,
        /* layerCount = */ 1u}} };
        NV_VK_REPLAY(VulkanHelper_CreateImageView(VkDevice_uid_4, VkImageViewCreateInfo_temp_20, 0ull, nullptr, &VkImageView_uid_6941));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE_VIEW, uint64_t(VkImageView_uid_6941), 6941ull));
    }

    // Create VkDescriptorSetLayout_uid_5034
    {
        static uint32_t uint32_t_pBindingFlags_321[2] = { 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_15[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 2u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_321} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_16[2] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_16[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_15,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 2u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_16} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_16, nullptr, &VkDescriptorSetLayout_uid_5034));
    }

    // Create VkDescriptorSetLayout_uid_5095
    {
        static uint32_t uint32_t_pBindingFlags_322[2] = { 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_16[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 2u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_322} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_17[2] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_17[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_16,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 2u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_17} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_17, nullptr, &VkDescriptorSetLayout_uid_5095));
    }

    // Create VkDescriptorSetLayout_uid_5211
    {
        static uint32_t uint32_t_pBindingFlags_323[1] = { 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_17[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 1u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_323} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_18[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_18[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_17,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_18} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_18, nullptr, &VkDescriptorSetLayout_uid_5211));
    }

    // Create VkDescriptorSetLayout_uid_5245
    {
        static uint32_t uint32_t_pBindingFlags_324[1] = { 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_18[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 1u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_324} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_19[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_19[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_18,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_19} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_19, nullptr, &VkDescriptorSetLayout_uid_5245));
    }

    // Create VkDescriptorSetLayout_uid_5281
    {
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_20[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_20[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(0),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_20} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_20, nullptr, &VkDescriptorSetLayout_uid_5281));
    }

    // Create VkDescriptorSetLayout_uid_6411
    {
        static uint32_t uint32_t_pBindingFlags_325[1] = { 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_19[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 1u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_325} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_21[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_21[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_19,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_21} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_21, nullptr, &VkDescriptorSetLayout_uid_6411));
    }

    // Create VkDescriptorSetLayout_uid_6747
    {
        static uint32_t uint32_t_pBindingFlags_326[3] = { 5u, 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_20[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 3u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_326} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_22[3] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_RAYGEN_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 2u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_RAYGEN_BIT_KHR),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_22[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_20,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 3u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_22} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_22, nullptr, &VkDescriptorSetLayout_uid_6747));
    }

    // Create VkDescriptorSetLayout_uid_6748
    {
        static uint32_t uint32_t_pBindingFlags_327[3] = { 5u, 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_21[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 3u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_327} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_23[3] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 2u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_23[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_21,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 3u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_23} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_23, nullptr, &VkDescriptorSetLayout_uid_6748));
    }

    // Create VkDescriptorSetLayout_uid_6749
    {
        static uint32_t uint32_t_pBindingFlags_328[1] = { 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_22[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 1u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_328} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_24[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_MISS_BIT_KHR),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_24[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_22,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_24} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_24, nullptr, &VkDescriptorSetLayout_uid_6749));
    }

    // Create VkDescriptorSetLayout_uid_6950
    {
        static uint32_t uint32_t_pBindingFlags_329[2] = { 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_23[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 2u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_329} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_25[2] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_25[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_23,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 2u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_25} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_25, nullptr, &VkDescriptorSetLayout_uid_6950));
    }

    // Create VkDescriptorSetLayout_uid_6960
    {
        static uint32_t uint32_t_pBindingFlags_330[3] = { 5u, 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_24[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 3u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_330} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_26[3] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_RAYGEN_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 2u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_RAYGEN_BIT_KHR),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_26[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_24,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 3u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_26} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_26, nullptr, &VkDescriptorSetLayout_uid_6960));
    }

    // Create VkDescriptorSetLayout_uid_6961
    {
        static uint32_t uint32_t_pBindingFlags_331[3] = { 5u, 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_25[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 3u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_331} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_27[3] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 2u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_27[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_25,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 3u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_27} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_27, nullptr, &VkDescriptorSetLayout_uid_6961));
    }

    // Create VkDescriptorSetLayout_uid_6962
    {
        static uint32_t uint32_t_pBindingFlags_332[1] = { 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_26[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 1u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_332} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_28[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_MISS_BIT_KHR),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_28[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_26,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_28} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_28, nullptr, &VkDescriptorSetLayout_uid_6962));
    }

    // Create VkDescriptorSetLayout_uid_6966
    {
        static uint32_t uint32_t_pBindingFlags_333[2] = { 5u, 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_27[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 2u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_333} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_29[2] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr}, VkDescriptorSetLayoutBinding{
        /* binding = */ 1u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_29[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_27,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 2u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_29} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_29, nullptr, &VkDescriptorSetLayout_uid_6966));
    }

    // Create VkDescriptorSetLayout_uid_6995
    {
        static uint32_t uint32_t_pBindingFlags_334[1] = { 5u };
        static VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_28[1] = { VkDescriptorSetLayoutBindingFlagsCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* bindingCount = */ 1u,
        /* pBindingFlags = */ uint32_t_pBindingFlags_334} };
        static VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBinding_pBindings_30[1] = { VkDescriptorSetLayoutBinding{
        /* binding = */ 0u,
        /* descriptorType = */ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        /* descriptorCount = */ 1u,
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT),
        /* pImmutableSamplers = */ nullptr} };
        static VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfo_temp_30[1] = { VkDescriptorSetLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        /* pNext = */ VkDescriptorSetLayoutBindingFlagsCreateInfo_pNext_28,
        /* flags = */ VkDescriptorSetLayoutCreateFlags(VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT),
        /* bindingCount = */ 1u,
        /* pBindings = */ VkDescriptorSetLayoutBinding_pBindings_30} };
        NV_VK_REPLAY(VulkanReplay_CreateDescriptorSetLayout(VkDevice_uid_4, VkDescriptorSetLayoutCreateInfo_temp_30, nullptr, &VkDescriptorSetLayout_uid_6995));
    }

    // Create VkPipelineLayout_uid_5096
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_18[2] = { VkDescriptorSetLayout_uid_5034, VkDescriptorSetLayout_uid_5095 };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_9[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 2u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_18,
        /* pushConstantRangeCount = */ 0u,
        /* pPushConstantRanges = */ nullptr} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_9, nullptr, &VkPipelineLayout_uid_5096));
    }

    // Create VkPipelineLayout_uid_5212
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_19[2] = { VkDescriptorSetLayout_uid_5034, VkDescriptorSetLayout_uid_5211 };
        static VkPushConstantRange VkPushConstantRange_pPushConstantRanges_10[1] = { VkPushConstantRange{
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* offset = */ 0u,
        /* size = */ 68u} };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_10[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 2u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_19,
        /* pushConstantRangeCount = */ 1u,
        /* pPushConstantRanges = */ VkPushConstantRange_pPushConstantRanges_10} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_10, nullptr, &VkPipelineLayout_uid_5212));
    }

    // Create VkPipelineLayout_uid_5225
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_20[1] = { VkDescriptorSetLayout_uid_5034 };
        static VkPushConstantRange VkPushConstantRange_pPushConstantRanges_11[1] = { VkPushConstantRange{
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* offset = */ 0u,
        /* size = */ 68u} };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_11[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_20,
        /* pushConstantRangeCount = */ 1u,
        /* pPushConstantRanges = */ VkPushConstantRange_pPushConstantRanges_11} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_11, nullptr, &VkPipelineLayout_uid_5225));
    }

    // Create VkPipelineLayout_uid_5246
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_21[2] = { VkDescriptorSetLayout_uid_5034, VkDescriptorSetLayout_uid_5245 };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_12[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 2u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_21,
        /* pushConstantRangeCount = */ 0u,
        /* pPushConstantRanges = */ nullptr} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_12, nullptr, &VkPipelineLayout_uid_5246));
    }

    // Create VkPipelineLayout_uid_5269
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_22[1] = { VkDescriptorSetLayout_uid_5034 };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_13[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_22,
        /* pushConstantRangeCount = */ 0u,
        /* pPushConstantRanges = */ nullptr} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_13, nullptr, &VkPipelineLayout_uid_5269));
    }

    // Create VkPipelineLayout_uid_5282
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_23[1] = { VkDescriptorSetLayout_uid_5281 };
        static VkPushConstantRange VkPushConstantRange_pPushConstantRanges_14[1] = { VkPushConstantRange{
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT),
        /* offset = */ 0u,
        /* size = */ 16u} };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_14[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_23,
        /* pushConstantRangeCount = */ 1u,
        /* pPushConstantRanges = */ VkPushConstantRange_pPushConstantRanges_14} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_14, nullptr, &VkPipelineLayout_uid_5282));
    }

    // Create VkPipelineLayout_uid_6412
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_24[2] = { VkDescriptorSetLayout_uid_5034, VkDescriptorSetLayout_uid_6411 };
        static VkPushConstantRange VkPushConstantRange_pPushConstantRanges_15[1] = { VkPushConstantRange{
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* offset = */ 0u,
        /* size = */ 68u} };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_15[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 2u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_24,
        /* pushConstantRangeCount = */ 1u,
        /* pPushConstantRanges = */ VkPushConstantRange_pPushConstantRanges_15} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_15, nullptr, &VkPipelineLayout_uid_6412));
    }

    // Create VkPipelineLayout_uid_6750
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_25[4] = { VkDescriptorSetLayout_uid_5034, VkDescriptorSetLayout_uid_6747, VkDescriptorSetLayout_uid_6748, VkDescriptorSetLayout_uid_6749 };
        static VkPushConstantRange VkPushConstantRange_pPushConstantRanges_16[1] = { VkPushConstantRange{
        /* stageFlags = */ VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000),
        /* offset = */ 0u,
        /* size = */ 4u} };
        static VkPipelineLayoutCreateInfo VkPipelineLayoutCreateInfo_temp_16[1] = { VkPipelineLayoutCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineLayoutCreateFlags(0),
        /* setLayoutCount = */ 4u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_25,
        /* pushConstantRangeCount = */ 1u,
        /* pPushConstantRanges = */ VkPushConstantRange_pPushConstantRanges_16} };
        NV_VK_REPLAY(VulkanReplay_CreatePipelineLayout(VkDevice_uid_4, VkPipelineLayoutCreateInfo_temp_16, nullptr, &VkPipelineLayout_uid_6750));
    }

    // Create VkDescriptorSet_uid_40
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_26[1] = { VkDescriptorSetLayout_uid_5281 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_10[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_26} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_10, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_40)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_40), 40ull));
    }

    // Create VkDescriptorSet_uid_94
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_27[1] = { VkDescriptorSetLayout_uid_6411 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_11[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_27} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_11, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_94)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_94), 94ull));
    }

    // Create VkDescriptorSet_uid_109
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_28[1] = { VkDescriptorSetLayout_uid_6950 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_12[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_28} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_12, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_109)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_109), 109ull));
    }

    // Create VkDescriptorSet_uid_110
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_29[1] = { VkDescriptorSetLayout_uid_6960 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_13[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_29} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_13, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_110)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_110), 110ull));
    }

    // Create VkDescriptorSet_uid_111
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_30[1] = { VkDescriptorSetLayout_uid_6961 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_14[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_30} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_14, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_111)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_111), 111ull));
    }

    // Create VkDescriptorSet_uid_112
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_31[1] = { VkDescriptorSetLayout_uid_6962 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_15[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_31} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_15, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_112)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_112), 112ull));
    }

    // Create VkDescriptorSet_uid_113
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_32[1] = { VkDescriptorSetLayout_uid_6966 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_16[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_32} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_16, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_113)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_113), 113ull));
    }

    // Create VkDescriptorSet_uid_118
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_33[1] = { VkDescriptorSetLayout_uid_6995 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_17[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_33} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_17, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_118)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_118), 118ull));
    }

    // Create VkDescriptorSet_uid_119
    {
        static VkDescriptorSetLayout VkDescriptorSetLayout_pSetLayouts_34[1] = { VkDescriptorSetLayout_uid_5281 };
        static VkDescriptorSetAllocateInfo VkDescriptorSetAllocateInfo_temp_18[1] = { VkDescriptorSetAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* descriptorPool = */ VkDescriptorPool_uid_26,
        /* descriptorSetCount = */ 1u,
        /* pSetLayouts = */ VkDescriptorSetLayout_pSetLayouts_34} };
        NV_VK_REPLAY(VulkanReplay_AllocateDescriptorSets(VkDevice_uid_4, VkDescriptorSetAllocateInfo_temp_18, NV_TO_OUTPUT_ARRAY(&VkDescriptorSet_uid_119)));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_DESCRIPTOR_SET, uint64_t(VkDescriptorSet_uid_119), 119ull));
    }

    // Create VkShaderModule_uid_5097
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_19[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 2416ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 364, 2416ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_19, nullptr, &VkShaderModule_uid_5097));
    }

    // Create VkShaderModule_uid_5098
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_20[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 2372ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 365, 2372ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_20, nullptr, &VkShaderModule_uid_5098));
    }

    // Create VkShaderModule_uid_5226
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_21[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 2896ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 366, 2896ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_21, nullptr, &VkShaderModule_uid_5226));
    }

    // Create VkShaderModule_uid_5227
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_22[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 1012ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 367, 1012ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_22, nullptr, &VkShaderModule_uid_5227));
    }

    // Create VkShaderModule_uid_5247
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_23[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 2416ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 368, 2416ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_23, nullptr, &VkShaderModule_uid_5247));
    }

    // Create VkShaderModule_uid_5248
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_24[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 6212ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 369, 6212ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_24, nullptr, &VkShaderModule_uid_5248));
    }

    // Create VkShaderModule_uid_5270
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_25[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 1128ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 370, 1128ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_25, nullptr, &VkShaderModule_uid_5270));
    }

    // Create VkShaderModule_uid_5271
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_26[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 568ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 371, 568ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_26, nullptr, &VkShaderModule_uid_5271));
    }

    // Create VkShaderModule_uid_5272
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_27[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 1968ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 372, 1968ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_27, nullptr, &VkShaderModule_uid_5272));
    }

    // Create VkShaderModule_uid_5283
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_28[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 1296ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 373, 1296ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_28, nullptr, &VkShaderModule_uid_5283));
    }

    // Create VkShaderModule_uid_5284
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_29[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 772ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 374, 772ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_29, nullptr, &VkShaderModule_uid_5284));
    }

    // Create VkShaderModule_uid_6413
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_30[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 3240ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 375, 3240ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_30, nullptr, &VkShaderModule_uid_6413));
    }

    // Create VkShaderModule_uid_6414
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_31[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 1576ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 376, 1576ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_31, nullptr, &VkShaderModule_uid_6414));
    }

    // Create VkShaderModule_uid_6751
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_32[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 8352ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 377, 8352ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_32, nullptr, &VkShaderModule_uid_6751));
    }

    // Create VkShaderModule_uid_6752
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_33[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 2408ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 378, 2408ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_33, nullptr, &VkShaderModule_uid_6752));
    }

    // Create VkShaderModule_uid_6753
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_34[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 380ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 379, 380ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_34, nullptr, &VkShaderModule_uid_6753));
    }

    // Create VkShaderModule_uid_6754
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_35[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 30116ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 380, 30116ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_35, nullptr, &VkShaderModule_uid_6754));
    }

    // Create VkShaderModule_uid_6755
    {
        BEGIN_DATA_SCOPE();

        static VkShaderModuleCreateInfo VkShaderModuleCreateInfo_temp_36[1] = { VkShaderModuleCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkShaderModuleCreateFlags(0),
        /* codeSize = */ 30516ull,
        /* pCode = */NV_GET_RESOURCE_CHECKED(const uint32_t*, 381, 30516ull)} };
        NV_VK_REPLAY(VulkanReplay_CreateShaderModule(VkDevice_uid_4, VkShaderModuleCreateInfo_temp_36, nullptr, &VkShaderModule_uid_6755));
    }

    // Create VkRenderPass_uid_5092
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_14[2] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_54[2] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentReference{
        /* attachment = */ 1u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_14[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 2u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_54,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_14[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_14[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_14,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_14,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_14} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_14, nullptr, &VkRenderPass_uid_5092));
    }

    // Create VkRenderPass_uid_5208
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_15[2] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_LOAD,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        /* finalLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_LOAD,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_58[2] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentReference{
        /* attachment = */ 1u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_15[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 2u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_58,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_15[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_15[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_15,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_15,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_15} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_15, nullptr, &VkRenderPass_uid_5208));
    }

    // Create VkRenderPass_uid_5222
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_16[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_62[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_16[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_62,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_16[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_16[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_16,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_16,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_16} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_16, nullptr, &VkRenderPass_uid_5222));
    }

    // Create VkRenderPass_uid_5241
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_17[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_LOAD,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_66[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_17[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_66,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_17[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_17[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_17,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_17,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_17} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_17, nullptr, &VkRenderPass_uid_5241));
    }

    // Create VkRenderPass_uid_5266
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_18[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_70[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_18[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_70,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_18[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_18[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_18,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_18,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_18} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_18, nullptr, &VkRenderPass_uid_5266));
    }

    // Create VkRenderPass_uid_5277
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_19[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_PRESENT_SRC_KHR} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_74[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_19[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_74,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_19[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_19[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_19,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_19,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_19} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_19, nullptr, &VkRenderPass_uid_5277));
    }

    // Create VkRenderPass_uid_6943
    {
        static VkSubpassDescription VkSubpassDescription_pSubpasses_20[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 0u,
        /* pColorAttachments = */ nullptr,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_20[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_20[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 0u,
        /* pAttachments = */ nullptr,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_20,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_20} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_20, nullptr, &VkRenderPass_uid_6943));
    }

    // Create VkRenderPass_uid_6963
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_21[2] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_82[2] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentReference{
        /* attachment = */ 1u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_21[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 2u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_82,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_21[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_21[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_21,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_21,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_21} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_21, nullptr, &VkRenderPass_uid_6963));
    }

    // Create VkRenderPass_uid_6985
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_22[2] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_LOAD,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        /* finalLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_LOAD,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_86[2] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL}, VkAttachmentReference{
        /* attachment = */ 1u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_22[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 2u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_86,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_22[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_22[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_22,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_22,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_22} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_22, nullptr, &VkRenderPass_uid_6985));
    }

    // Create VkRenderPass_uid_6988
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_23[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_90[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_23[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_90,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_23[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_23[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_23,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_23,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_23} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_23, nullptr, &VkRenderPass_uid_6988));
    }

    // Create VkRenderPass_uid_6991
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_24[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_LOAD,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_94[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_24[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_94,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_24[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_24[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_24,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_24,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_24} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_24, nullptr, &VkRenderPass_uid_6991));
    }

    // Create VkRenderPass_uid_6996
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_25[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_98[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_25[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_98,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_25[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_25[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_25,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_25,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_25} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_25, nullptr, &VkRenderPass_uid_6996));
    }

    // Create VkRenderPass_uid_6999
    {
        static VkAttachmentDescription VkAttachmentDescription_pAttachments_26[1] = { VkAttachmentDescription{
        /* flags = */ VkAttachmentDescriptionFlags(0),
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* loadOp = */ VK_ATTACHMENT_LOAD_OP_CLEAR,
        /* storeOp = */ VK_ATTACHMENT_STORE_OP_STORE,
        /* stencilLoadOp = */ VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        /* stencilStoreOp = */ VK_ATTACHMENT_STORE_OP_DONT_CARE,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED,
        /* finalLayout = */ VK_IMAGE_LAYOUT_PRESENT_SRC_KHR} };
        static VkAttachmentReference VkAttachmentReference_pColorAttachments_102[1] = { VkAttachmentReference{
        /* attachment = */ 0u,
        /* layout = */ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL} };
        static VkSubpassDescription VkSubpassDescription_pSubpasses_26[1] = { VkSubpassDescription{
        /* flags = */ VkSubpassDescriptionFlags(0),
        /* pipelineBindPoint = */ VK_PIPELINE_BIND_POINT_GRAPHICS,
        /* inputAttachmentCount = */ 0u,
        /* pInputAttachments = */ nullptr,
        /* colorAttachmentCount = */ 1u,
        /* pColorAttachments = */ VkAttachmentReference_pColorAttachments_102,
        /* pResolveAttachments = */ nullptr,
        /* pDepthStencilAttachment = */ nullptr,
        /* preserveAttachmentCount = */ 0u,
        /* pPreserveAttachments = */ nullptr} };
        static VkSubpassDependency VkSubpassDependency_pDependencies_26[2] = { VkSubpassDependency{
        /* srcSubpass = */ 4294967295u,
        /* dstSubpass = */ 0u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* srcAccessMask = */ VkAccessFlags(0),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT),
        /* dependencyFlags = */ VkDependencyFlags(0)}, VkSubpassDependency{
        /* srcSubpass = */ 0u,
        /* dstSubpass = */ 4294967295u,
        /* srcStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT),
        /* dstStageMask = */ VkPipelineStageFlags(VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT),
        /* srcAccessMask = */ VkAccessFlags(VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT),
        /* dstAccessMask = */ VkAccessFlags(VK_ACCESS_MEMORY_READ_BIT),
        /* dependencyFlags = */ VkDependencyFlags(VK_DEPENDENCY_BY_REGION_BIT)} };
        static VkRenderPassCreateInfo VkRenderPassCreateInfo_temp_26[1] = { VkRenderPassCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkRenderPassCreateFlags(0),
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkAttachmentDescription_pAttachments_26,
        /* subpassCount = */ 1u,
        /* pSubpasses = */ VkSubpassDescription_pSubpasses_26,
        /* dependencyCount = */ 2u,
        /* pDependencies = */ VkSubpassDependency_pDependencies_26} };
        NV_VK_REPLAY(VulkanReplay_CreateRenderPass(VkDevice_uid_4, VkRenderPassCreateInfo_temp_26, nullptr, &VkRenderPass_uid_6999));
    }

    // Create VkFramebuffer_uid_6945
    {
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_8[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6943,
        /* attachmentCount = */ 0u,
        /* pAttachments = */ nullptr,
        /* width = */ 1631u,
        /* height = */ 892u,
        /* layers = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_8, nullptr, &VkFramebuffer_uid_6945));
    }

    // Create VkFramebuffer_uid_6965
    {
        static VkImageView VkImageView_pAttachments_9[2] = { VkImageView_uid_6894, VkImageView_uid_6924 };
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_9[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6963,
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkImageView_pAttachments_9,
        /* width = */ 1631u,
        /* height = */ 892u,
        /* layers = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_9, nullptr, &VkFramebuffer_uid_6965));
    }

    // Create VkFramebuffer_uid_6987
    {
        static VkImageView VkImageView_pAttachments_10[2] = { VkImageView_uid_6894, VkImageView_uid_6924 };
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_10[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6985,
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkImageView_pAttachments_10,
        /* width = */ 1631u,
        /* height = */ 892u,
        /* layers = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_10, nullptr, &VkFramebuffer_uid_6987));
    }

    // Create VkFramebuffer_uid_6990
    {
        static VkImageView VkImageView_pAttachments_11[1] = { VkImageView_uid_6941 };
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_11[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6988,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkImageView_pAttachments_11,
        /* width = */ 1631u,
        /* height = */ 892u,
        /* layers = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_11, nullptr, &VkFramebuffer_uid_6990));
    }

    // Create VkFramebuffer_uid_6993
    {
        static VkImageView VkImageView_pAttachments_12[1] = { VkImageView_uid_6894 };
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_12[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6991,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkImageView_pAttachments_12,
        /* width = */ 1631u,
        /* height = */ 892u,
        /* layers = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_12, nullptr, &VkFramebuffer_uid_6993));
    }

    // Create VkFramebuffer_uid_6998
    {
        static VkImageView VkImageView_pAttachments_13[1] = { VkImageView_uid_6920 };
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_13[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6996,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkImageView_pAttachments_13,
        /* width = */ 1631u,
        /* height = */ 892u,
        /* layers = */ 6u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_13, nullptr, &VkFramebuffer_uid_6998));
    }

    // Create VkFramebuffer_uid_7001
    {
        static VkImageView VkImageView_pAttachments_14[1] = { VkImageView_uid_18 };
        static VkFramebufferCreateInfo VkFramebufferCreateInfo_temp_14[1] = { VkFramebufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFramebufferCreateFlags(0),
        /* renderPass = */ VkRenderPass_uid_6999,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkImageView_pAttachments_14,
        /* width = */ 2200u,
        /* height = */ 1300u,
        /* layers = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_CreateFramebuffer(VkDevice_uid_4, VkFramebufferCreateInfo_temp_14, nullptr, &VkFramebuffer_uid_7001));
    }

    // Create VkPipeline_uid_5099
    {
        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_8[2] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_VERTEX_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5097,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_FRAGMENT_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5098,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkVertexInputBindingDescription VkVertexInputBindingDescription_pVertexBindingDescriptions_7[1] = { VkVertexInputBindingDescription{
        /* binding = */ 0u,
        /* stride = */ 44u,
        /* inputRate = */ VK_VERTEX_INPUT_RATE_VERTEX} };
        static VkVertexInputAttributeDescription VkVertexInputAttributeDescription_pVertexAttributeDescriptions_7[4] = { VkVertexInputAttributeDescription{
        /* location = */ 0u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* offset = */ 0u}, VkVertexInputAttributeDescription{
        /* location = */ 1u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* offset = */ 12u}, VkVertexInputAttributeDescription{
        /* location = */ 2u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* offset = */ 24u}, VkVertexInputAttributeDescription{
        /* location = */ 3u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R32G32_SFLOAT,
        /* offset = */ 36u} };
        static VkPipelineVertexInputStateCreateInfo VkPipelineVertexInputStateCreateInfo_pVertexInputState_7[1] = { VkPipelineVertexInputStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineVertexInputStateCreateFlags(0),
        /* vertexBindingDescriptionCount = */ 1u,
        /* pVertexBindingDescriptions = */ VkVertexInputBindingDescription_pVertexBindingDescriptions_7,
        /* vertexAttributeDescriptionCount = */ 4u,
        /* pVertexAttributeDescriptions = */ VkVertexInputAttributeDescription_pVertexAttributeDescriptions_7} };
        static VkPipelineInputAssemblyStateCreateInfo VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_7[1] = { VkPipelineInputAssemblyStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineInputAssemblyStateCreateFlags(0),
        /* topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        /* primitiveRestartEnable = */ 0u} };
        static VkPipelineViewportStateCreateInfo VkPipelineViewportStateCreateInfo_pViewportState_7[1] = { VkPipelineViewportStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineViewportStateCreateFlags(0),
        /* viewportCount = */ 1u,
        /* pViewports = */ nullptr,
        /* scissorCount = */ 1u,
        /* pScissors = */ nullptr} };
        static VkPipelineRasterizationStateCreateInfo VkPipelineRasterizationStateCreateInfo_pRasterizationState_7[1] = { VkPipelineRasterizationStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineRasterizationStateCreateFlags(0),
        /* depthClampEnable = */ 0u,
        /* rasterizerDiscardEnable = */ 0u,
        /* polygonMode = */ VK_POLYGON_MODE_FILL,
        /* cullMode = */ VkCullModeFlags(VK_CULL_MODE_BACK_BIT),
        /* frontFace = */ VK_FRONT_FACE_COUNTER_CLOCKWISE,
        /* depthBiasEnable = */ 0u,
        /* depthBiasConstantFactor = */ 0.0f,
        /* depthBiasClamp = */ 0.0f,
        /* depthBiasSlopeFactor = */ 0.0f,
        /* lineWidth = */ HexToFloat(0x3F800000/*1.0f*/)} };
        static VkPipelineMultisampleStateCreateInfo VkPipelineMultisampleStateCreateInfo_pMultisampleState_7[1] = { VkPipelineMultisampleStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineMultisampleStateCreateFlags(0),
        /* rasterizationSamples = */ VK_SAMPLE_COUNT_1_BIT,
        /* sampleShadingEnable = */ 0u,
        /* minSampleShading = */ HexToFloat(0x3F800000/*1.0f*/),
        /* pSampleMask = */ nullptr,
        /* alphaToCoverageEnable = */ 0u,
        /* alphaToOneEnable = */ 0u} };
        static VkPipelineDepthStencilStateCreateInfo VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_7[1] = { VkPipelineDepthStencilStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDepthStencilStateCreateFlags(0),
        /* depthTestEnable = */ 1u,
        /* depthWriteEnable = */ 1u,
        /* depthCompareOp = */ VK_COMPARE_OP_LESS,
        /* depthBoundsTestEnable = */ 0u,
        /* stencilTestEnable = */ 0u,
        /* front = */ VkStencilOpState{
        /* failOp = */ VK_STENCIL_OP_KEEP,
        /* passOp = */ VK_STENCIL_OP_KEEP,
        /* depthFailOp = */ VK_STENCIL_OP_KEEP,
        /* compareOp = */ VK_COMPARE_OP_NEVER,
        /* compareMask = */ 0u,
        /* writeMask = */ 0u,
        /* reference = */ 0u},
        /* back = */ VkStencilOpState{
        /* failOp = */ VK_STENCIL_OP_KEEP,
        /* passOp = */ VK_STENCIL_OP_KEEP,
        /* depthFailOp = */ VK_STENCIL_OP_KEEP,
        /* compareOp = */ VK_COMPARE_OP_NEVER,
        /* compareMask = */ 0u,
        /* writeMask = */ 0u,
        /* reference = */ 0u},
        /* minDepthBounds = */ 0.0f,
        /* maxDepthBounds = */ HexToFloat(0x3F800000/*1.0f*/)} };
        static VkPipelineColorBlendAttachmentState VkPipelineColorBlendAttachmentState_pAttachments_7[2] = { VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 0u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* colorBlendOp = */ VK_BLEND_OP_ADD,
        /* srcAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstAlphaBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* alphaBlendOp = */ VK_BLEND_OP_ADD,
        /* colorWriteMask = */ VkColorComponentFlags(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)}, VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 0u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* colorBlendOp = */ VK_BLEND_OP_ADD,
        /* srcAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstAlphaBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* alphaBlendOp = */ VK_BLEND_OP_ADD,
        /* colorWriteMask = */ VkColorComponentFlags(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)} };
        static VkPipelineColorBlendStateCreateInfo VkPipelineColorBlendStateCreateInfo_pColorBlendState_7[1] = { VkPipelineColorBlendStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineColorBlendStateCreateFlags(0),
        /* logicOpEnable = */ 0u,
        /* logicOp = */ VK_LOGIC_OP_COPY,
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkPipelineColorBlendAttachmentState_pAttachments_7,
        /* blendConstants = */ NV_TO_ARRAY(0.0f, 0.0f, 0.0f, 0.0f)} };
        static VkDynamicState VkDynamicState_pDynamicStates_7[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        static VkPipelineDynamicStateCreateInfo VkPipelineDynamicStateCreateInfo_pDynamicState_8[1] = { VkPipelineDynamicStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDynamicStateCreateFlags(0),
        /* dynamicStateCount = */ 2u,
        /* pDynamicStates = */ VkDynamicState_pDynamicStates_7} };
        static VkGraphicsPipelineCreateInfo VkGraphicsPipelineCreateInfo_temp_7[1] = { VkGraphicsPipelineCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 2u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_8,
        /* pVertexInputState = */ VkPipelineVertexInputStateCreateInfo_pVertexInputState_7,
        /* pInputAssemblyState = */ VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_7,
        /* pTessellationState = */ nullptr,
        /* pViewportState = */ VkPipelineViewportStateCreateInfo_pViewportState_7,
        /* pRasterizationState = */ VkPipelineRasterizationStateCreateInfo_pRasterizationState_7,
        /* pMultisampleState = */ VkPipelineMultisampleStateCreateInfo_pMultisampleState_7,
        /* pDepthStencilState = */ VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_7,
        /* pColorBlendState = */ VkPipelineColorBlendStateCreateInfo_pColorBlendState_7,
        /* pDynamicState = */ VkPipelineDynamicStateCreateInfo_pDynamicState_8,
        /* layout = */ VkPipelineLayout_uid_5096,
        /* renderPass = */ VkRenderPass_uid_5092,
        /* subpass = */ 0u,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ -1} };
        NV_VK_REPLAY(VulkanReplay_CreateGraphicsPipelines(VkDevice_uid_4, VkPipelineCache(VK_NULL_HANDLE), 1u, VkGraphicsPipelineCreateInfo_temp_7, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_5099)));
    }
}

NV_REPLAY_END_RESOURCE_INIT()
