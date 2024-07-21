//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: CommandList00.cpp
// 
//-----------------------------------------------------------------------------

#include "Resources.h"
#include "Helpers.h"
#include "CommonReplay.h"

NV_REPLAY_BEGIN_COMMAND_LIST()

//-----------------------------------------------------------------------------
// Record_VkCommandBuffer_uid_9_r1_Part00
//-----------------------------------------------------------------------------
void Record_VkCommandBuffer_uid_9_r1_Part00(VkCommandBuffer cmdBuffer)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    static VkCommandBufferBeginInfo VkCommandBufferBeginInfo_temp_2[1] = { VkCommandBufferBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* flags = */ VkCommandBufferUsageFlags(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT),
    /* pInheritanceInfo = */ nullptr} };
    NV_VK_REPLAY(VulkanReplay_BeginCommandBuffer(cmdBuffer, VkCommandBufferBeginInfo_temp_2)); // Event #22 (Begin Recording #0)

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_16[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "PreRenderer",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_16)); // Event #23

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_17[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "PreRenderer",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_17)); // Event #24

    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_8[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6943,
    /* framebuffer = */ VkFramebuffer_uid_6945,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 1631u,
    /* height = */ 892u}},
    /* clearValueCount = */ 0u,
    /* pClearValues = */ nullptr} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_8, VK_SUBPASS_CONTENTS_INLINE)); // Event #25

    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #26
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #27
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #28

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_18[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "RayTracing",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_18)); // Event #29

    static uint32_t uint32_t_temp_179;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, VkPipelineLayout_uid_6750, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_109), 0u, nullptr)); // Event #30

    static uint32_t uint32_t_temp_180;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, VkPipelineLayout_uid_6750, 1u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_110), 0u, nullptr)); // Event #31

    static uint32_t uint32_t_temp_181;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, VkPipelineLayout_uid_6750, 2u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_111), 0u, nullptr)); // Event #32

    static uint32_t uint32_t_temp_182;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, VkPipelineLayout_uid_6750, 3u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_112), 0u, nullptr)); // Event #33

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, VkPipeline_uid_6756)); // Event #34
    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_6750, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000), 0u, 4u, NV_GET_RESOURCE_STATIC(void*, 342, 4ull))); // Event #35

    static VkStridedDeviceAddressRegionKHR VkStridedDeviceAddressRegionKHR_temp_5[1] = { VkStridedDeviceAddressRegionKHR{
    /* deviceAddress = */ 343ull,
    /* stride = */ 64ull,
    /* size = */ 64ull} };
    static VkStridedDeviceAddressRegionKHR VkStridedDeviceAddressRegionKHR_temp_6[1] = { VkStridedDeviceAddressRegionKHR{
    /* deviceAddress = */ 344ull,
    /* stride = */ 32ull,
    /* size = */ 192ull} };
    static VkStridedDeviceAddressRegionKHR VkStridedDeviceAddressRegionKHR_temp_7[1] = { VkStridedDeviceAddressRegionKHR{
    /* deviceAddress = */ 345ull,
    /* stride = */ 32ull,
    /* size = */ 128ull} };
    static VkStridedDeviceAddressRegionKHR VkStridedDeviceAddressRegionKHR_temp_8[1] = { VkStridedDeviceAddressRegionKHR{
    /* deviceAddress = */ 18446744073709551615ull,
    /* stride = */ 0ull,
    /* size = */ 0ull} };
    NV_VK_REPLAY(VulkanHelper_CmdTraceRaysKHR_FromDatabase2(cmdBuffer, VkStridedDeviceAddressRegionKHR_temp_5, VkStridedDeviceAddressRegionKHR_temp_6, VkStridedDeviceAddressRegionKHR_temp_7, VkStridedDeviceAddressRegionKHR_temp_8, 1631u, 892u, 1u)); // Event #36 (Trace Rays #0)

    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #37

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_19[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "RayTracingCompose",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_19)); // Event #38

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_20[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "RayTracingCompose",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_20)); // Event #39

    static union VkClearValue unionVkClearValue_pClearValues_36[2] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F), NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_9[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6963,
    /* framebuffer = */ VkFramebuffer_uid_6965,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 1631u,
    /* height = */ 892u}},
    /* clearValueCount = */ 2u,
    /* pClearValues = */ unionVkClearValue_pClearValues_36} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_9, VK_SUBPASS_CONTENTS_INLINE)); // Event #40

    static VkViewport VkViewport_temp_3[1] = { VkViewport{
    /* x = */ 0.0f,
    /* y = */ HexToFloat(0x445F0000/*892.0f*/),
    /* width = */ HexToFloat(0x44CBE000/*1631.0f*/),
    /* height = */ HexToFloat(0xC45F0000/*-892.0f*/),
    /* minDepth = */ 0.0f,
    /* maxDepth = */ HexToFloat(0x3F800000/*1.0f*/)} };
    NV_VK_REPLAY(VulkanReplay_CmdSetViewport(cmdBuffer, 0u, 1u, VkViewport_temp_3)); // Event #41

    static VkRect2D VkRect2D_temp_81[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 2200u,
    /* height = */ 1300u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_81)); // Event #42

    static uint32_t uint32_t_temp_183;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5096, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_109), 0u, nullptr)); // Event #43

    static uint32_t uint32_t_temp_184;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5096, 1u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_113), 0u, nullptr)); // Event #44

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_5099)); // Event #45

    static uint64_t uint64_t_temp_9[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_5076), uint64_t_temp_9)); // Event #46

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_5081, 0ull, VK_INDEX_TYPE_UINT32)); // Event #47
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #48 (Draw #0)
    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #49
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #50
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #51

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_21[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "Sprite",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_21)); // Event #52

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_22[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "Sprite",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_22)); // Event #53

    static union VkClearValue unionVkClearValue_pClearValues_37[2] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F), NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_10[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6985,
    /* framebuffer = */ VkFramebuffer_uid_6987,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 1631u,
    /* height = */ 892u}},
    /* clearValueCount = */ 2u,
    /* pClearValues = */ unionVkClearValue_pClearValues_37} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_10, VK_SUBPASS_CONTENTS_INLINE)); // Event #54

    static uint32_t uint32_t_temp_185;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5212, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_109), 0u, nullptr)); // Event #55

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_6415)); // Event #56
    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_5212, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000), 0u, 68u, NV_GET_RESOURCE_STATIC(void*, 346, 68ull))); // Event #57

    static uint32_t uint32_t_temp_186;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5212, 1u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_94), 0u, nullptr)); // Event #58

    static uint64_t uint64_t_temp_10[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_6420), uint64_t_temp_10)); // Event #59

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_6425, 0ull, VK_INDEX_TYPE_UINT32)); // Event #60
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #61 (Draw #1)
    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_6415)); // Event #62
    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_5212, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000), 0u, 68u, NV_GET_RESOURCE_STATIC(void*, 347, 68ull))); // Event #63

    static uint32_t uint32_t_temp_187;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5212, 1u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_94), 0u, nullptr)); // Event #64

    static uint64_t uint64_t_temp_11[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_6386), uint64_t_temp_11)); // Event #65

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_6391, 0ull, VK_INDEX_TYPE_UINT32)); // Event #66
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #67 (Draw #2)
    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_6415)); // Event #68
    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_5212, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000), 0u, 68u, NV_GET_RESOURCE_STATIC(void*, 348, 68ull))); // Event #69

    static uint32_t uint32_t_temp_188;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5212, 1u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_94), 0u, nullptr)); // Event #70

    static uint64_t uint64_t_temp_12[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_6403), uint64_t_temp_12)); // Event #71

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_6408, 0ull, VK_INDEX_TYPE_UINT32)); // Event #72
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #73 (Draw #3)
    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #74
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #75
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #76

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_23[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "WorldPick",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_23)); // Event #77

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_24[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "WorldPick",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_24)); // Event #78

    static union VkClearValue unionVkClearValue_pClearValues_38[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_11[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6988,
    /* framebuffer = */ VkFramebuffer_uid_6990,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 1631u,
    /* height = */ 892u}},
    /* clearValueCount = */ 1u,
    /* pClearValues = */ unionVkClearValue_pClearValues_38} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_11, VK_SUBPASS_CONTENTS_INLINE)); // Event #79

    static uint32_t uint32_t_temp_189;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5225, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_109), 0u, nullptr)); // Event #80

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_5228)); // Event #81
    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_5225, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR | VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | 0x7fffc000), 0u, 68u, NV_GET_RESOURCE_STATIC(void*, 349, 68ull))); // Event #82

    static uint64_t uint64_t_temp_13[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_6360), uint64_t_temp_13)); // Event #83

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_6365, 0ull, VK_INDEX_TYPE_UINT32)); // Event #84
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #85 (Draw #4)
    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #86
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #87
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #88

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_25[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "WorldPickStage2",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_25)); // Event #89

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_26[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "WorldPickStage2",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_26)); // Event #90

    static union VkClearValue unionVkClearValue_pClearValues_39[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_12[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6991,
    /* framebuffer = */ VkFramebuffer_uid_6993,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 1631u,
    /* height = */ 892u}},
    /* clearValueCount = */ 1u,
    /* pClearValues = */ unionVkClearValue_pClearValues_39} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_12, VK_SUBPASS_CONTENTS_INLINE)); // Event #91

    static uint32_t uint32_t_temp_190;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5246, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_109), 0u, nullptr)); // Event #92

    static uint32_t uint32_t_temp_191;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5246, 1u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_118), 0u, nullptr)); // Event #93

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_5249)); // Event #94

    static uint64_t uint64_t_temp_14[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_5233), uint64_t_temp_14)); // Event #95

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_5238, 0ull, VK_INDEX_TYPE_UINT32)); // Event #96
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #97 (Draw #5)
    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #98
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #99
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #100

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_27[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "TestPass",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_27)); // Event #101

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_28[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "Test",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_28)); // Event #102

    static union VkClearValue unionVkClearValue_pClearValues_40[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_13[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6996,
    /* framebuffer = */ VkFramebuffer_uid_6998,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 1631u,
    /* height = */ 892u}},
    /* clearValueCount = */ 1u,
    /* pClearValues = */ unionVkClearValue_pClearValues_40} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_13, VK_SUBPASS_CONTENTS_INLINE)); // Event #103

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_5273)); // Event #104

    static uint64_t uint64_t_temp_15[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_5254), uint64_t_temp_15)); // Event #105

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_5259, 0ull, VK_INDEX_TYPE_UINT32)); // Event #106
    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 0u, 0, 0u)); // Event #107 (Draw #6)
    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #108
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #109
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #110

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_29[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "Slate",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_29)); // Event #111

    static VkDebugUtilsLabelEXT VkDebugUtilsLabelEXT_temp_30[1] = { VkDebugUtilsLabelEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
    /* pNext = */ nullptr,
    /* pLabelName = */ "Slate",
    /* color = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/))} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginDebugUtilsLabelEXT(cmdBuffer, VkDebugUtilsLabelEXT_temp_30)); // Event #112

    static union VkClearValue unionVkClearValue_pClearValues_41[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
    static VkRenderPassBeginInfo VkRenderPassBeginInfo_temp_14[1] = { VkRenderPassBeginInfo{
    /* sType = */ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    /* pNext = */ nullptr,
    /* renderPass = */ VkRenderPass_uid_6999,
    /* framebuffer = */ VkFramebuffer_uid_7001,
    /* renderArea = */ VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 2200u,
    /* height = */ 1300u}},
    /* clearValueCount = */ 1u,
    /* pClearValues = */ unionVkClearValue_pClearValues_41} };
    NV_VK_REPLAY(VulkanReplay_CmdBeginRenderPass(cmdBuffer, VkRenderPassBeginInfo_temp_14, VK_SUBPASS_CONTENTS_INLINE)); // Event #113

    NV_VK_REPLAY(VulkanReplay_CmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipeline_uid_5285)); // Event #114

    static uint64_t uint64_t_temp_16[1] = { 0ull };
    NV_VK_REPLAY(VulkanReplay_CmdBindVertexBuffers(cmdBuffer, 0u, 1u, NV_TO_STACK_PTR(VkBuffer_uid_7268), uint64_t_temp_16)); // Event #115

    NV_VK_REPLAY(VulkanReplay_CmdBindIndexBuffer(cmdBuffer, VkBuffer_uid_7289, 0ull, VK_INDEX_TYPE_UINT16)); // Event #116

    static VkViewport VkViewport_temp_4[1] = { VkViewport{
    /* x = */ 0.0f,
    /* y = */ 0.0f,
    /* width = */ HexToFloat(0x45098000/*2200.0f*/),
    /* height = */ HexToFloat(0x44A28000/*1300.0f*/),
    /* minDepth = */ 0.0f,
    /* maxDepth = */ HexToFloat(0x3F800000/*1.0f*/)} };
    NV_VK_REPLAY(VulkanReplay_CmdSetViewport(cmdBuffer, 0u, 1u, VkViewport_temp_4)); // Event #117

    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_5282, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT), 0u, 8u, NV_GET_RESOURCE_STATIC(void*, 350, 8ull))); // Event #118
    NV_VK_REPLAY(VulkanReplay_CmdPushConstants(cmdBuffer, VkPipelineLayout_uid_5282, VkShaderStageFlags(VK_SHADER_STAGE_VERTEX_BIT), 8u, 8u, NV_GET_RESOURCE_STATIC(void*, 351, 8ull))); // Event #119

    static VkRect2D VkRect2D_temp_82[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1,
    /* y = */ 24},
    /* extent = */ VkExtent2D{
    /* width = */ 2198u,
    /* height = */ 1276u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_82)); // Event #120

    static uint32_t uint32_t_temp_192;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #121

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 777u, 1u, 0u, 0, 0u)); // Event #122 (Draw #7)

    static VkRect2D VkRect2D_temp_83[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 38,
    /* y = */ 27},
    /* extent = */ VkExtent2D{
    /* width = */ 1635u,
    /* height = */ 898u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_83)); // Event #123

    static uint32_t uint32_t_temp_193;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_119), 0u, nullptr)); // Event #124

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 777u, 330, 0u)); // Event #125 (Draw #8)

    static VkRect2D VkRect2D_temp_84[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 38,
    /* y = */ 27},
    /* extent = */ VkExtent2D{
    /* width = */ 1635u,
    /* height = */ 898u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_84)); // Event #126

    static uint32_t uint32_t_temp_194;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #127

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 546u, 1u, 783u, 330, 0u)); // Event #128 (Draw #9)

    static VkRect2D VkRect2D_temp_85[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 4,
    /* y = */ 927},
    /* extent = */ VkExtent2D{
    /* width = */ 1641u,
    /* height = */ 336u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_85)); // Event #129

    static uint32_t uint32_t_temp_195;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #130

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 1536u, 1u, 1329u, 482, 0u)); // Event #131 (Draw #10)

    static VkRect2D VkRect2D_temp_86[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 6,
    /* y = */ 960},
    /* extent = */ VkExtent2D{
    /* width = */ 1633u,
    /* height = */ 298u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_86)); // Event #132

    static uint32_t uint32_t_temp_196;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #133

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 7158u, 1u, 2865u, 894, 0u)); // Event #134 (Draw #11)

    static VkRect2D VkRect2D_temp_87[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_87)); // Event #135

    static uint32_t uint32_t_temp_197;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #136

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 180u, 1u, 10023u, 5666, 0u)); // Event #137 (Draw #12)

    static VkRect2D VkRect2D_temp_88[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 79u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_88)); // Event #138

    static uint32_t uint32_t_temp_198;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #139

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 162u, 1u, 10203u, 5666, 0u)); // Event #140 (Draw #13)

    static VkRect2D VkRect2D_temp_89[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1757,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 433u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_89)); // Event #141

    static uint32_t uint32_t_temp_199;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #142

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 174u, 1u, 10365u, 5666, 0u)); // Event #143 (Draw #14)

    static VkRect2D VkRect2D_temp_90[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 79u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_90)); // Event #144

    static uint32_t uint32_t_temp_200;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #145

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 48u, 1u, 10539u, 5666, 0u)); // Event #146 (Draw #15)

    static VkRect2D VkRect2D_temp_91[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1757,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 433u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_91)); // Event #147

    static uint32_t uint32_t_temp_201;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #148

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 180u, 1u, 10587u, 5666, 0u)); // Event #149 (Draw #16)

    static VkRect2D VkRect2D_temp_92[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 79u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_92)); // Event #150

    static uint32_t uint32_t_temp_202;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #151

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 72u, 1u, 10767u, 5666, 0u)); // Event #152 (Draw #17)

    static VkRect2D VkRect2D_temp_93[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1757,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 433u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_93)); // Event #153

    static uint32_t uint32_t_temp_203;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #154

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 144u, 1u, 10839u, 5666, 0u)); // Event #155 (Draw #18)

    static VkRect2D VkRect2D_temp_94[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_94)); // Event #156

    static uint32_t uint32_t_temp_204;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #157

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 357u, 1u, 10983u, 5666, 0u)); // Event #158 (Draw #19)

    static VkRect2D VkRect2D_temp_95[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1691,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 99u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_95)); // Event #159

    static uint32_t uint32_t_temp_205;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #160

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 54u, 1u, 11340u, 5666, 0u)); // Event #161 (Draw #20)

    static VkRect2D VkRect2D_temp_96[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1791,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 398u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_96)); // Event #162

    static uint32_t uint32_t_temp_206;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #163

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 1362u, 1u, 11394u, 5666, 0u)); // Event #164 (Draw #21)

    static VkRect2D VkRect2D_temp_97[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1691,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 99u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_97)); // Event #165

    static uint32_t uint32_t_temp_207;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #166

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 36u, 1u, 12756u, 5666, 0u)); // Event #167 (Draw #22)

    static VkRect2D VkRect2D_temp_98[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1791,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 398u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_98)); // Event #168

    static uint32_t uint32_t_temp_208;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #169

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 1362u, 1u, 12792u, 5666, 0u)); // Event #170 (Draw #23)

    static VkRect2D VkRect2D_temp_99[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1691,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 99u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_99)); // Event #171

    static uint32_t uint32_t_temp_209;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #172

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 174u, 1u, 14154u, 5666, 0u)); // Event #173 (Draw #24)

    static VkRect2D VkRect2D_temp_100[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1791,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 398u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_100)); // Event #174

    static uint32_t uint32_t_temp_210;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #175

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 1368u, 1u, 14328u, 5666, 0u)); // Event #176 (Draw #25)

    static VkRect2D VkRect2D_temp_101[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_101)); // Event #177

    static uint32_t uint32_t_temp_211;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #178

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 816u, 1u, 15696u, 5666, 0u)); // Event #179 (Draw #26)

    static VkRect2D VkRect2D_temp_102[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1713,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 139u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_102)); // Event #180

    static uint32_t uint32_t_temp_212;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #181

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 234u, 1u, 16512u, 5666, 0u)); // Event #182 (Draw #27)

    static VkRect2D VkRect2D_temp_103[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1853,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 337u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_103)); // Event #183

    static uint32_t uint32_t_temp_213;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #184

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 936u, 1u, 16746u, 5666, 0u)); // Event #185 (Draw #28)

    static VkRect2D VkRect2D_temp_104[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_104)); // Event #186

    static uint32_t uint32_t_temp_214;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #187

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 17682u, 5666, 0u)); // Event #188 (Draw #29)

    static VkRect2D VkRect2D_temp_105[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1713,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 139u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_105)); // Event #189

    static uint32_t uint32_t_temp_215;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #190

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 66u, 1u, 17688u, 5666, 0u)); // Event #191 (Draw #30)

    static VkRect2D VkRect2D_temp_106[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1853,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 337u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_106)); // Event #192

    static uint32_t uint32_t_temp_216;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #193

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 294u, 1u, 17754u, 5666, 0u)); // Event #194 (Draw #31)

    static VkRect2D VkRect2D_temp_107[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1713,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 139u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_107)); // Event #195

    static uint32_t uint32_t_temp_217;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #196

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 42u, 1u, 18048u, 5666, 0u)); // Event #197 (Draw #32)

    static VkRect2D VkRect2D_temp_108[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1853,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 337u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_108)); // Event #198

    static uint32_t uint32_t_temp_218;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #199

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 294u, 1u, 18090u, 5666, 0u)); // Event #200 (Draw #33)

    static VkRect2D VkRect2D_temp_109[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_109)); // Event #201

    static uint32_t uint32_t_temp_219;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #202

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 489u, 1u, 18384u, 5666, 0u)); // Event #203 (Draw #34)

    static VkRect2D VkRect2D_temp_110[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1713,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 139u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_110)); // Event #204

    static uint32_t uint32_t_temp_220;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #205

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 234u, 1u, 18873u, 5666, 0u)); // Event #206 (Draw #35)

    static VkRect2D VkRect2D_temp_111[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1853,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 337u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_111)); // Event #207

    static uint32_t uint32_t_temp_221;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #208

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 972u, 1u, 19107u, 5666, 0u)); // Event #209 (Draw #36)

    static VkRect2D VkRect2D_temp_112[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_112)); // Event #210

    static uint32_t uint32_t_temp_222;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #211

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 321u, 1u, 20079u, 5666, 0u)); // Event #212 (Draw #37)

    static VkRect2D VkRect2D_temp_113[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1691,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_113)); // Event #213

    static uint32_t uint32_t_temp_223;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #214

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 36u, 1u, 20400u, 5666, 0u)); // Event #215 (Draw #38)

    static VkRect2D VkRect2D_temp_114[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1821,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 368u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_114)); // Event #216

    static uint32_t uint32_t_temp_224;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #217

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 318u, 1u, 20436u, 5666, 0u)); // Event #218 (Draw #39)

    static VkRect2D VkRect2D_temp_115[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 578},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 685u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_115)); // Event #219

    static uint32_t uint32_t_temp_225;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #220

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 327u, 1u, 20754u, 5666, 0u)); // Event #221 (Draw #40)

    static VkRect2D VkRect2D_temp_116[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 4,
    /* y = */ 27},
    /* extent = */ VkExtent2D{
    /* width = */ 30u,
    /* height = */ 898u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_116)); // Event #222

    static uint32_t uint32_t_temp_226;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #223

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 1602u, 1u, 21081u, 9330, 0u)); // Event #224 (Draw #41)

    static VkRect2D VkRect2D_temp_117[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 4,
    /* y = */ 1265},
    /* extent = */ VkExtent2D{
    /* width = */ 2192u,
    /* height = */ 32u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_117)); // Event #225

    static uint32_t uint32_t_temp_227;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #226

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 12u, 1u, 22683u, 9738, 0u)); // Event #227 (Draw #42)

    static VkRect2D VkRect2D_temp_118[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_118)); // Event #228

    static uint32_t uint32_t_temp_228;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #229

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 180u, 1u, 22695u, 9746, 0u)); // Event #230 (Draw #43)

    static VkRect2D VkRect2D_temp_119[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 79u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_119)); // Event #231

    static uint32_t uint32_t_temp_229;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #232

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 162u, 1u, 22875u, 9746, 0u)); // Event #233 (Draw #44)

    static VkRect2D VkRect2D_temp_120[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1757,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 433u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_120)); // Event #234

    static uint32_t uint32_t_temp_230;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #235

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 306u, 1u, 23037u, 9746, 0u)); // Event #236 (Draw #45)

    static VkRect2D VkRect2D_temp_121[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 79u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_121)); // Event #237

    static uint32_t uint32_t_temp_231;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #238

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 48u, 1u, 23343u, 9746, 0u)); // Event #239 (Draw #46)

    static VkRect2D VkRect2D_temp_122[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1757,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 433u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_122)); // Event #240

    static uint32_t uint32_t_temp_232;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #241

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 312u, 1u, 23391u, 9746, 0u)); // Event #242 (Draw #47)

    static VkRect2D VkRect2D_temp_123[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 79u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_123)); // Event #243

    static uint32_t uint32_t_temp_233;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #244

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 72u, 1u, 23703u, 9746, 0u)); // Event #245 (Draw #48)

    static VkRect2D VkRect2D_temp_124[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1757,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 433u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_124)); // Event #246

    static uint32_t uint32_t_temp_234;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #247

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 144u, 1u, 23775u, 9746, 0u)); // Event #248 (Draw #49)

    static VkRect2D VkRect2D_temp_125[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_125)); // Event #249

    static uint32_t uint32_t_temp_235;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #250

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 339u, 1u, 23919u, 9746, 0u)); // Event #251 (Draw #50)

    static VkRect2D VkRect2D_temp_126[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_126)); // Event #252

    static uint32_t uint32_t_temp_236;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #253

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 24u, 1u, 24258u, 9746, 0u)); // Event #254 (Draw #51)

    static VkRect2D VkRect2D_temp_127[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_127)); // Event #255

    static uint32_t uint32_t_temp_237;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #256

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 456u, 1u, 24282u, 9746, 0u)); // Event #257 (Draw #52)

    static VkRect2D VkRect2D_temp_128[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_128)); // Event #258

    static uint32_t uint32_t_temp_238;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #259

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 24u, 1u, 24738u, 9746, 0u)); // Event #260 (Draw #53)

    static VkRect2D VkRect2D_temp_129[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_129)); // Event #261

    static uint32_t uint32_t_temp_239;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #262

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 456u, 1u, 24762u, 9746, 0u)); // Event #263 (Draw #54)

    static VkRect2D VkRect2D_temp_130[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_130)); // Event #264

    static uint32_t uint32_t_temp_240;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #265

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 30u, 1u, 25218u, 9746, 0u)); // Event #266 (Draw #55)

    static VkRect2D VkRect2D_temp_131[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_131)); // Event #267

    static uint32_t uint32_t_temp_241;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #268

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 456u, 1u, 25248u, 9746, 0u)); // Event #269 (Draw #56)

    static VkRect2D VkRect2D_temp_132[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_132)); // Event #270

    static uint32_t uint32_t_temp_242;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #271

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 345u, 1u, 25704u, 9746, 0u)); // Event #272 (Draw #57)

    static VkRect2D VkRect2D_temp_133[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_133)); // Event #273

    static uint32_t uint32_t_temp_243;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #274

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 48u, 1u, 26049u, 9746, 0u)); // Event #275 (Draw #58)

    static VkRect2D VkRect2D_temp_134[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_134)); // Event #276

    static uint32_t uint32_t_temp_244;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #277

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 348u, 1u, 26097u, 9746, 0u)); // Event #278 (Draw #59)

    static VkRect2D VkRect2D_temp_135[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_135)); // Event #279

    static uint32_t uint32_t_temp_245;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #280

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 36u, 1u, 26445u, 9746, 0u)); // Event #281 (Draw #60)

    static VkRect2D VkRect2D_temp_136[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_136)); // Event #282

    static uint32_t uint32_t_temp_246;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #283

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 348u, 1u, 26481u, 9746, 0u)); // Event #284 (Draw #61)

    static VkRect2D VkRect2D_temp_137[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_137)); // Event #285

    static uint32_t uint32_t_temp_247;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #286

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 36u, 1u, 26829u, 9746, 0u)); // Event #287 (Draw #62)

    static VkRect2D VkRect2D_temp_138[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_138)); // Event #288

    static uint32_t uint32_t_temp_248;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #289

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 348u, 1u, 26865u, 9746, 0u)); // Event #290 (Draw #63)

    static VkRect2D VkRect2D_temp_139[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_139)); // Event #291

    static uint32_t uint32_t_temp_249;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #292

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 54u, 1u, 27213u, 9746, 0u)); // Event #293 (Draw #64)

    static VkRect2D VkRect2D_temp_140[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_140)); // Event #294

    static uint32_t uint32_t_temp_250;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #295

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 348u, 1u, 27267u, 9746, 0u)); // Event #296 (Draw #65)

    static VkRect2D VkRect2D_temp_141[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1677,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 515u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_141)); // Event #297

    static uint32_t uint32_t_temp_251;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #298

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 357u, 1u, 27615u, 9746, 0u)); // Event #299 (Draw #66)

    static VkRect2D VkRect2D_temp_142[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_142)); // Event #300

    static uint32_t uint32_t_temp_252;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #301

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 36u, 1u, 27972u, 9746, 0u)); // Event #302 (Draw #67)

    static VkRect2D VkRect2D_temp_143[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_143)); // Event #303

    static uint32_t uint32_t_temp_253;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #304

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 630u, 1u, 28008u, 9746, 0u)); // Event #305 (Draw #68)

    static VkRect2D VkRect2D_temp_144[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_144)); // Event #306

    static uint32_t uint32_t_temp_254;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #307

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 54u, 1u, 28638u, 9746, 0u)); // Event #308 (Draw #69)

    static VkRect2D VkRect2D_temp_145[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_145)); // Event #309

    static uint32_t uint32_t_temp_255;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #310

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 306u, 1u, 28692u, 9746, 0u)); // Event #311 (Draw #70)

    static VkRect2D VkRect2D_temp_146[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_146)); // Event #312

    static uint32_t uint32_t_temp_256;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #313

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 48u, 1u, 28998u, 9746, 0u)); // Event #314 (Draw #71)

    static VkRect2D VkRect2D_temp_147[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_147)); // Event #315

    static uint32_t uint32_t_temp_257;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #316

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 306u, 1u, 29046u, 9746, 0u)); // Event #317 (Draw #72)

    static VkRect2D VkRect2D_temp_148[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_148)); // Event #318

    static uint32_t uint32_t_temp_258;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #319

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 66u, 1u, 29352u, 9746, 0u)); // Event #320 (Draw #73)

    static VkRect2D VkRect2D_temp_149[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_149)); // Event #321

    static uint32_t uint32_t_temp_259;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #322

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 288u, 1u, 29418u, 9746, 0u)); // Event #323 (Draw #74)

    static VkRect2D VkRect2D_temp_150[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_150)); // Event #324

    static uint32_t uint32_t_temp_260;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #325

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 78u, 1u, 29706u, 9746, 0u)); // Event #326 (Draw #75)

    static VkRect2D VkRect2D_temp_151[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_151)); // Event #327

    static uint32_t uint32_t_temp_261;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #328

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 288u, 1u, 29784u, 9746, 0u)); // Event #329 (Draw #76)

    static VkRect2D VkRect2D_temp_152[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1689,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 129u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_152)); // Event #330

    static uint32_t uint32_t_temp_262;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #331

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 84u, 1u, 30072u, 9746, 0u)); // Event #332 (Draw #77)

    static VkRect2D VkRect2D_temp_153[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1819,
    /* y = */ 47},
    /* extent = */ VkExtent2D{
    /* width = */ 371u,
    /* height = */ 509u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_153)); // Event #333

    static uint32_t uint32_t_temp_263;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #334

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 288u, 1u, 30156u, 9746, 0u)); // Event #335 (Draw #78)

    static VkRect2D VkRect2D_temp_154[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 43,
    /* y = */ 32},
    /* extent = */ VkExtent2D{
    /* width = */ 327u,
    /* height = */ 36u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_154)); // Event #336

    static uint32_t uint32_t_temp_264;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #337

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 876u, 1u, 30444u, 12548, 0u)); // Event #338 (Draw #79)

    static VkRect2D VkRect2D_temp_155[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1514,
    /* y = */ 32},
    /* extent = */ VkExtent2D{
    /* width = */ 156u,
    /* height = */ 36u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_155)); // Event #339

    static uint32_t uint32_t_temp_265;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #340

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 354u, 1u, 31320u, 12832, 0u)); // Event #341 (Draw #80)

    static VkRect2D VkRect2D_temp_156[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 2200u,
    /* height = */ 1300u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_156)); // Event #342

    static uint32_t uint32_t_temp_266;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #343

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 6u, 1u, 31674u, 12948, 0u)); // Event #344 (Draw #81)

    static VkRect2D VkRect2D_temp_157[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 1482,
    /* y = */ 67},
    /* extent = */ VkExtent2D{
    /* width = */ 180u,
    /* height = */ 78u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_157)); // Event #345

    static uint32_t uint32_t_temp_267;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #346

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 552u, 1u, 31680u, 12948, 0u)); // Event #347 (Draw #82)

    static VkRect2D VkRect2D_temp_158[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 2200u,
    /* height = */ 1300u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_158)); // Event #348

    static uint32_t uint32_t_temp_268;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #349

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 12u, 1u, 32232u, 13320, 0u)); // Event #350 (Draw #83)

    static VkRect2D VkRect2D_temp_159[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 2200u,
    /* height = */ 24u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_159)); // Event #351

    static uint32_t uint32_t_temp_269;
    NV_VK_REPLAY(VulkanReplay_CmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout_uid_5282, 0u, 1u, NV_TO_STACK_PTR(VkDescriptorSet_uid_40), 0u, nullptr)); // Event #352

    NV_VK_REPLAY(VulkanReplay_CmdDrawIndexed(cmdBuffer, 432u, 1u, 32244u, 13320, 0u)); // Event #353 (Draw #84)

    static VkRect2D VkRect2D_temp_160[1] = { VkRect2D{
    /* offset = */ VkOffset2D{
    /* x = */ 0,
    /* y = */ 0},
    /* extent = */ VkExtent2D{
    /* width = */ 2200u,
    /* height = */ 1300u}} };
    NV_VK_REPLAY(VulkanReplay_CmdSetScissor(cmdBuffer, 0u, 1u, VkRect2D_temp_160)); // Event #354

    NV_VK_REPLAY(VulkanReplay_CmdEndRenderPass(cmdBuffer)); // Event #355
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #356
    NV_VK_REPLAY(VulkanReplay_CmdEndDebugUtilsLabelEXT(cmdBuffer)); // Event #357
    NV_VK_REPLAY(VulkanReplay_EndCommandBuffer(cmdBuffer)); // Event #358 (End Recording #0)
}

//-----------------------------------------------------------------------------
// Record_VkCommandBuffer_uid_9_r1
//-----------------------------------------------------------------------------
void Record_VkCommandBuffer_uid_9_r1(VkCommandBuffer cmdBuffer)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    Record_VkCommandBuffer_uid_9_r1_Part00(cmdBuffer);
}

NV_REPLAY_END_COMMAND_LIST()
