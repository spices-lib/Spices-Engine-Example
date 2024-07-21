//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: Resources02.cpp
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
// CreateResources02
//-----------------------------------------------------------------------------
void CreateResources02()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Create VkPipeline_uid_5228
    {
        BEGIN_DATA_SCOPE();

        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_9[2] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_VERTEX_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5226,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_FRAGMENT_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5227,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkVertexInputBindingDescription VkVertexInputBindingDescription_pVertexBindingDescriptions_8[1] = { VkVertexInputBindingDescription{
        /* binding = */ 0u,
        /* stride = */ 44u,
        /* inputRate = */ VK_VERTEX_INPUT_RATE_VERTEX} };
        static VkVertexInputAttributeDescription VkVertexInputAttributeDescription_pVertexAttributeDescriptions_8[4] = { VkVertexInputAttributeDescription{
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
        static VkPipelineVertexInputStateCreateInfo VkPipelineVertexInputStateCreateInfo_pVertexInputState_8[1] = { VkPipelineVertexInputStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineVertexInputStateCreateFlags(0),
        /* vertexBindingDescriptionCount = */ 1u,
        /* pVertexBindingDescriptions = */ VkVertexInputBindingDescription_pVertexBindingDescriptions_8,
        /* vertexAttributeDescriptionCount = */ 4u,
        /* pVertexAttributeDescriptions = */ VkVertexInputAttributeDescription_pVertexAttributeDescriptions_8} };
        static VkPipelineInputAssemblyStateCreateInfo VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_8[1] = { VkPipelineInputAssemblyStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineInputAssemblyStateCreateFlags(0),
        /* topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        /* primitiveRestartEnable = */ 0u} };
        static VkPipelineViewportStateCreateInfo VkPipelineViewportStateCreateInfo_pViewportState_8[1] = { VkPipelineViewportStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineViewportStateCreateFlags(0),
        /* viewportCount = */ 1u,
        /* pViewports = */ nullptr,
        /* scissorCount = */ 1u,
        /* pScissors = */ nullptr} };
        static VkPipelineRasterizationStateCreateInfo VkPipelineRasterizationStateCreateInfo_pRasterizationState_8[1] = { VkPipelineRasterizationStateCreateInfo{
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
        static VkPipelineMultisampleStateCreateInfo VkPipelineMultisampleStateCreateInfo_pMultisampleState_8[1] = { VkPipelineMultisampleStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineMultisampleStateCreateFlags(0),
        /* rasterizationSamples = */ VK_SAMPLE_COUNT_1_BIT,
        /* sampleShadingEnable = */ 0u,
        /* minSampleShading = */ HexToFloat(0x3F800000/*1.0f*/),
        /* pSampleMask = */ nullptr,
        /* alphaToCoverageEnable = */ 0u,
        /* alphaToOneEnable = */ 0u} };
        static VkPipelineDepthStencilStateCreateInfo VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_8[1] = { VkPipelineDepthStencilStateCreateInfo{
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
        static VkPipelineColorBlendAttachmentState VkPipelineColorBlendAttachmentState_pAttachments_8[1] = { VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 0u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* colorBlendOp = */ VK_BLEND_OP_ADD,
        /* srcAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstAlphaBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* alphaBlendOp = */ VK_BLEND_OP_ADD,
        /* colorWriteMask = */ VkColorComponentFlags(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)} };
        static VkPipelineColorBlendStateCreateInfo VkPipelineColorBlendStateCreateInfo_pColorBlendState_8[1] = { VkPipelineColorBlendStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineColorBlendStateCreateFlags(0),
        /* logicOpEnable = */ 0u,
        /* logicOp = */ VK_LOGIC_OP_COPY,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkPipelineColorBlendAttachmentState_pAttachments_8,
        /* blendConstants = */ NV_TO_ARRAY(0.0f, 0.0f, 0.0f, 0.0f)} };
        static VkDynamicState VkDynamicState_pDynamicStates_8[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        static VkPipelineDynamicStateCreateInfo VkPipelineDynamicStateCreateInfo_pDynamicState_9[1] = { VkPipelineDynamicStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDynamicStateCreateFlags(0),
        /* dynamicStateCount = */ 2u,
        /* pDynamicStates = */ VkDynamicState_pDynamicStates_8} };
        static VkGraphicsPipelineCreateInfo VkGraphicsPipelineCreateInfo_temp_8[1] = { VkGraphicsPipelineCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 2u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_9,
        /* pVertexInputState = */ VkPipelineVertexInputStateCreateInfo_pVertexInputState_8,
        /* pInputAssemblyState = */ VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_8,
        /* pTessellationState = */ nullptr,
        /* pViewportState = */ VkPipelineViewportStateCreateInfo_pViewportState_8,
        /* pRasterizationState = */ VkPipelineRasterizationStateCreateInfo_pRasterizationState_8,
        /* pMultisampleState = */ VkPipelineMultisampleStateCreateInfo_pMultisampleState_8,
        /* pDepthStencilState = */ VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_8,
        /* pColorBlendState = */ VkPipelineColorBlendStateCreateInfo_pColorBlendState_8,
        /* pDynamicState = */ VkPipelineDynamicStateCreateInfo_pDynamicState_9,
        /* layout = */ VkPipelineLayout_uid_5225,
        /* renderPass = */ VkRenderPass_uid_5222,
        /* subpass = */ 0u,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ -1} };
        NV_VK_REPLAY(VulkanReplay_CreateGraphicsPipelines(VkDevice_uid_4, VkPipelineCache(VK_NULL_HANDLE), 1u, VkGraphicsPipelineCreateInfo_temp_8, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_5228)));
    }

    // Create VkPipeline_uid_5249
    {
        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_10[2] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_VERTEX_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5247,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_FRAGMENT_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5248,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkVertexInputBindingDescription VkVertexInputBindingDescription_pVertexBindingDescriptions_9[1] = { VkVertexInputBindingDescription{
        /* binding = */ 0u,
        /* stride = */ 44u,
        /* inputRate = */ VK_VERTEX_INPUT_RATE_VERTEX} };
        static VkVertexInputAttributeDescription VkVertexInputAttributeDescription_pVertexAttributeDescriptions_9[4] = { VkVertexInputAttributeDescription{
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
        static VkPipelineVertexInputStateCreateInfo VkPipelineVertexInputStateCreateInfo_pVertexInputState_9[1] = { VkPipelineVertexInputStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineVertexInputStateCreateFlags(0),
        /* vertexBindingDescriptionCount = */ 1u,
        /* pVertexBindingDescriptions = */ VkVertexInputBindingDescription_pVertexBindingDescriptions_9,
        /* vertexAttributeDescriptionCount = */ 4u,
        /* pVertexAttributeDescriptions = */ VkVertexInputAttributeDescription_pVertexAttributeDescriptions_9} };
        static VkPipelineInputAssemblyStateCreateInfo VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_9[1] = { VkPipelineInputAssemblyStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineInputAssemblyStateCreateFlags(0),
        /* topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        /* primitiveRestartEnable = */ 0u} };
        static VkPipelineViewportStateCreateInfo VkPipelineViewportStateCreateInfo_pViewportState_9[1] = { VkPipelineViewportStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineViewportStateCreateFlags(0),
        /* viewportCount = */ 1u,
        /* pViewports = */ nullptr,
        /* scissorCount = */ 1u,
        /* pScissors = */ nullptr} };
        static VkPipelineRasterizationStateCreateInfo VkPipelineRasterizationStateCreateInfo_pRasterizationState_9[1] = { VkPipelineRasterizationStateCreateInfo{
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
        static VkPipelineMultisampleStateCreateInfo VkPipelineMultisampleStateCreateInfo_pMultisampleState_9[1] = { VkPipelineMultisampleStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineMultisampleStateCreateFlags(0),
        /* rasterizationSamples = */ VK_SAMPLE_COUNT_1_BIT,
        /* sampleShadingEnable = */ 0u,
        /* minSampleShading = */ HexToFloat(0x3F800000/*1.0f*/),
        /* pSampleMask = */ nullptr,
        /* alphaToCoverageEnable = */ 0u,
        /* alphaToOneEnable = */ 0u} };
        static VkPipelineDepthStencilStateCreateInfo VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_9[1] = { VkPipelineDepthStencilStateCreateInfo{
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
        static VkPipelineColorBlendAttachmentState VkPipelineColorBlendAttachmentState_pAttachments_9[1] = { VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 0u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* colorBlendOp = */ VK_BLEND_OP_ADD,
        /* srcAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstAlphaBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* alphaBlendOp = */ VK_BLEND_OP_ADD,
        /* colorWriteMask = */ VkColorComponentFlags(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)} };
        static VkPipelineColorBlendStateCreateInfo VkPipelineColorBlendStateCreateInfo_pColorBlendState_9[1] = { VkPipelineColorBlendStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineColorBlendStateCreateFlags(0),
        /* logicOpEnable = */ 0u,
        /* logicOp = */ VK_LOGIC_OP_COPY,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkPipelineColorBlendAttachmentState_pAttachments_9,
        /* blendConstants = */ NV_TO_ARRAY(0.0f, 0.0f, 0.0f, 0.0f)} };
        static VkDynamicState VkDynamicState_pDynamicStates_9[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        static VkPipelineDynamicStateCreateInfo VkPipelineDynamicStateCreateInfo_pDynamicState_10[1] = { VkPipelineDynamicStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDynamicStateCreateFlags(0),
        /* dynamicStateCount = */ 2u,
        /* pDynamicStates = */ VkDynamicState_pDynamicStates_9} };
        static VkGraphicsPipelineCreateInfo VkGraphicsPipelineCreateInfo_temp_9[1] = { VkGraphicsPipelineCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 2u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_10,
        /* pVertexInputState = */ VkPipelineVertexInputStateCreateInfo_pVertexInputState_9,
        /* pInputAssemblyState = */ VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_9,
        /* pTessellationState = */ nullptr,
        /* pViewportState = */ VkPipelineViewportStateCreateInfo_pViewportState_9,
        /* pRasterizationState = */ VkPipelineRasterizationStateCreateInfo_pRasterizationState_9,
        /* pMultisampleState = */ VkPipelineMultisampleStateCreateInfo_pMultisampleState_9,
        /* pDepthStencilState = */ VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_9,
        /* pColorBlendState = */ VkPipelineColorBlendStateCreateInfo_pColorBlendState_9,
        /* pDynamicState = */ VkPipelineDynamicStateCreateInfo_pDynamicState_10,
        /* layout = */ VkPipelineLayout_uid_5246,
        /* renderPass = */ VkRenderPass_uid_5241,
        /* subpass = */ 0u,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ -1} };
        NV_VK_REPLAY(VulkanReplay_CreateGraphicsPipelines(VkDevice_uid_4, VkPipelineCache(VK_NULL_HANDLE), 1u, VkGraphicsPipelineCreateInfo_temp_9, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_5249)));
    }

    // Create VkPipeline_uid_5273
    {
        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_11[3] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_VERTEX_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5270,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_FRAGMENT_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5271,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_GEOMETRY_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5272,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkVertexInputBindingDescription VkVertexInputBindingDescription_pVertexBindingDescriptions_10[1] = { VkVertexInputBindingDescription{
        /* binding = */ 0u,
        /* stride = */ 44u,
        /* inputRate = */ VK_VERTEX_INPUT_RATE_VERTEX} };
        static VkVertexInputAttributeDescription VkVertexInputAttributeDescription_pVertexAttributeDescriptions_10[4] = { VkVertexInputAttributeDescription{
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
        static VkPipelineVertexInputStateCreateInfo VkPipelineVertexInputStateCreateInfo_pVertexInputState_10[1] = { VkPipelineVertexInputStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineVertexInputStateCreateFlags(0),
        /* vertexBindingDescriptionCount = */ 1u,
        /* pVertexBindingDescriptions = */ VkVertexInputBindingDescription_pVertexBindingDescriptions_10,
        /* vertexAttributeDescriptionCount = */ 4u,
        /* pVertexAttributeDescriptions = */ VkVertexInputAttributeDescription_pVertexAttributeDescriptions_10} };
        static VkPipelineInputAssemblyStateCreateInfo VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_10[1] = { VkPipelineInputAssemblyStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineInputAssemblyStateCreateFlags(0),
        /* topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        /* primitiveRestartEnable = */ 0u} };
        static VkPipelineViewportStateCreateInfo VkPipelineViewportStateCreateInfo_pViewportState_10[1] = { VkPipelineViewportStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineViewportStateCreateFlags(0),
        /* viewportCount = */ 1u,
        /* pViewports = */ nullptr,
        /* scissorCount = */ 1u,
        /* pScissors = */ nullptr} };
        static VkPipelineRasterizationStateCreateInfo VkPipelineRasterizationStateCreateInfo_pRasterizationState_10[1] = { VkPipelineRasterizationStateCreateInfo{
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
        static VkPipelineMultisampleStateCreateInfo VkPipelineMultisampleStateCreateInfo_pMultisampleState_10[1] = { VkPipelineMultisampleStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineMultisampleStateCreateFlags(0),
        /* rasterizationSamples = */ VK_SAMPLE_COUNT_1_BIT,
        /* sampleShadingEnable = */ 0u,
        /* minSampleShading = */ HexToFloat(0x3F800000/*1.0f*/),
        /* pSampleMask = */ nullptr,
        /* alphaToCoverageEnable = */ 0u,
        /* alphaToOneEnable = */ 0u} };
        static VkPipelineDepthStencilStateCreateInfo VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_10[1] = { VkPipelineDepthStencilStateCreateInfo{
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
        static VkPipelineColorBlendAttachmentState VkPipelineColorBlendAttachmentState_pAttachments_10[1] = { VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 0u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* colorBlendOp = */ VK_BLEND_OP_ADD,
        /* srcAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstAlphaBlendFactor = */ VK_BLEND_FACTOR_ZERO,
        /* alphaBlendOp = */ VK_BLEND_OP_ADD,
        /* colorWriteMask = */ VkColorComponentFlags(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)} };
        static VkPipelineColorBlendStateCreateInfo VkPipelineColorBlendStateCreateInfo_pColorBlendState_10[1] = { VkPipelineColorBlendStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineColorBlendStateCreateFlags(0),
        /* logicOpEnable = */ 0u,
        /* logicOp = */ VK_LOGIC_OP_COPY,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkPipelineColorBlendAttachmentState_pAttachments_10,
        /* blendConstants = */ NV_TO_ARRAY(0.0f, 0.0f, 0.0f, 0.0f)} };
        static VkDynamicState VkDynamicState_pDynamicStates_10[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        static VkPipelineDynamicStateCreateInfo VkPipelineDynamicStateCreateInfo_pDynamicState_11[1] = { VkPipelineDynamicStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDynamicStateCreateFlags(0),
        /* dynamicStateCount = */ 2u,
        /* pDynamicStates = */ VkDynamicState_pDynamicStates_10} };
        static VkGraphicsPipelineCreateInfo VkGraphicsPipelineCreateInfo_temp_10[1] = { VkGraphicsPipelineCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 3u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_11,
        /* pVertexInputState = */ VkPipelineVertexInputStateCreateInfo_pVertexInputState_10,
        /* pInputAssemblyState = */ VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_10,
        /* pTessellationState = */ nullptr,
        /* pViewportState = */ VkPipelineViewportStateCreateInfo_pViewportState_10,
        /* pRasterizationState = */ VkPipelineRasterizationStateCreateInfo_pRasterizationState_10,
        /* pMultisampleState = */ VkPipelineMultisampleStateCreateInfo_pMultisampleState_10,
        /* pDepthStencilState = */ VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_10,
        /* pColorBlendState = */ VkPipelineColorBlendStateCreateInfo_pColorBlendState_10,
        /* pDynamicState = */ VkPipelineDynamicStateCreateInfo_pDynamicState_11,
        /* layout = */ VkPipelineLayout_uid_5269,
        /* renderPass = */ VkRenderPass_uid_5266,
        /* subpass = */ 0u,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ -1} };
        NV_VK_REPLAY(VulkanReplay_CreateGraphicsPipelines(VkDevice_uid_4, VkPipelineCache(VK_NULL_HANDLE), 1u, VkGraphicsPipelineCreateInfo_temp_10, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_5273)));
    }

    // Create VkPipeline_uid_5285
    {
        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_12[2] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_VERTEX_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5283,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_FRAGMENT_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_5284,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkVertexInputBindingDescription VkVertexInputBindingDescription_pVertexBindingDescriptions_11[1] = { VkVertexInputBindingDescription{
        /* binding = */ 0u,
        /* stride = */ 20u,
        /* inputRate = */ VK_VERTEX_INPUT_RATE_VERTEX} };
        static VkVertexInputAttributeDescription VkVertexInputAttributeDescription_pVertexAttributeDescriptions_11[3] = { VkVertexInputAttributeDescription{
        /* location = */ 0u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R32G32_SFLOAT,
        /* offset = */ 0u}, VkVertexInputAttributeDescription{
        /* location = */ 1u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R32G32_SFLOAT,
        /* offset = */ 8u}, VkVertexInputAttributeDescription{
        /* location = */ 2u,
        /* binding = */ 0u,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* offset = */ 16u} };
        static VkPipelineVertexInputStateCreateInfo VkPipelineVertexInputStateCreateInfo_pVertexInputState_11[1] = { VkPipelineVertexInputStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineVertexInputStateCreateFlags(0),
        /* vertexBindingDescriptionCount = */ 1u,
        /* pVertexBindingDescriptions = */ VkVertexInputBindingDescription_pVertexBindingDescriptions_11,
        /* vertexAttributeDescriptionCount = */ 3u,
        /* pVertexAttributeDescriptions = */ VkVertexInputAttributeDescription_pVertexAttributeDescriptions_11} };
        static VkPipelineInputAssemblyStateCreateInfo VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_11[1] = { VkPipelineInputAssemblyStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineInputAssemblyStateCreateFlags(0),
        /* topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        /* primitiveRestartEnable = */ 0u} };
        static VkPipelineViewportStateCreateInfo VkPipelineViewportStateCreateInfo_pViewportState_11[1] = { VkPipelineViewportStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineViewportStateCreateFlags(0),
        /* viewportCount = */ 1u,
        /* pViewports = */ nullptr,
        /* scissorCount = */ 1u,
        /* pScissors = */ nullptr} };
        static VkPipelineRasterizationStateCreateInfo VkPipelineRasterizationStateCreateInfo_pRasterizationState_11[1] = { VkPipelineRasterizationStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineRasterizationStateCreateFlags(0),
        /* depthClampEnable = */ 0u,
        /* rasterizerDiscardEnable = */ 0u,
        /* polygonMode = */ VK_POLYGON_MODE_FILL,
        /* cullMode = */ VkCullModeFlags(0),
        /* frontFace = */ VK_FRONT_FACE_COUNTER_CLOCKWISE,
        /* depthBiasEnable = */ 0u,
        /* depthBiasConstantFactor = */ 0.0f,
        /* depthBiasClamp = */ 0.0f,
        /* depthBiasSlopeFactor = */ 0.0f,
        /* lineWidth = */ HexToFloat(0x3F800000/*1.0f*/)} };
        static VkPipelineMultisampleStateCreateInfo VkPipelineMultisampleStateCreateInfo_pMultisampleState_11[1] = { VkPipelineMultisampleStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineMultisampleStateCreateFlags(0),
        /* rasterizationSamples = */ VK_SAMPLE_COUNT_1_BIT,
        /* sampleShadingEnable = */ 0u,
        /* minSampleShading = */ 0.0f,
        /* pSampleMask = */ nullptr,
        /* alphaToCoverageEnable = */ 0u,
        /* alphaToOneEnable = */ 0u} };
        static VkPipelineDepthStencilStateCreateInfo VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_11[1] = { VkPipelineDepthStencilStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDepthStencilStateCreateFlags(0),
        /* depthTestEnable = */ 0u,
        /* depthWriteEnable = */ 0u,
        /* depthCompareOp = */ VK_COMPARE_OP_NEVER,
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
        /* maxDepthBounds = */ 0.0f} };
        static VkPipelineColorBlendAttachmentState VkPipelineColorBlendAttachmentState_pAttachments_11[1] = { VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 1u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_SRC_ALPHA,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        /* colorBlendOp = */ VK_BLEND_OP_ADD,
        /* srcAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE,
        /* dstAlphaBlendFactor = */ VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        /* alphaBlendOp = */ VK_BLEND_OP_ADD,
        /* colorWriteMask = */ VkColorComponentFlags(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)} };
        static VkPipelineColorBlendStateCreateInfo VkPipelineColorBlendStateCreateInfo_pColorBlendState_11[1] = { VkPipelineColorBlendStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineColorBlendStateCreateFlags(0),
        /* logicOpEnable = */ 0u,
        /* logicOp = */ VK_LOGIC_OP_CLEAR,
        /* attachmentCount = */ 1u,
        /* pAttachments = */ VkPipelineColorBlendAttachmentState_pAttachments_11,
        /* blendConstants = */ NV_TO_ARRAY(0.0f, 0.0f, 0.0f, 0.0f)} };
        static VkDynamicState VkDynamicState_pDynamicStates_11[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        static VkPipelineDynamicStateCreateInfo VkPipelineDynamicStateCreateInfo_pDynamicState_12[1] = { VkPipelineDynamicStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDynamicStateCreateFlags(0),
        /* dynamicStateCount = */ 2u,
        /* pDynamicStates = */ VkDynamicState_pDynamicStates_11} };
        static VkGraphicsPipelineCreateInfo VkGraphicsPipelineCreateInfo_temp_11[1] = { VkGraphicsPipelineCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 2u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_12,
        /* pVertexInputState = */ VkPipelineVertexInputStateCreateInfo_pVertexInputState_11,
        /* pInputAssemblyState = */ VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_11,
        /* pTessellationState = */ nullptr,
        /* pViewportState = */ VkPipelineViewportStateCreateInfo_pViewportState_11,
        /* pRasterizationState = */ VkPipelineRasterizationStateCreateInfo_pRasterizationState_11,
        /* pMultisampleState = */ VkPipelineMultisampleStateCreateInfo_pMultisampleState_11,
        /* pDepthStencilState = */ VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_11,
        /* pColorBlendState = */ VkPipelineColorBlendStateCreateInfo_pColorBlendState_11,
        /* pDynamicState = */ VkPipelineDynamicStateCreateInfo_pDynamicState_12,
        /* layout = */ VkPipelineLayout_uid_5282,
        /* renderPass = */ VkRenderPass_uid_5277,
        /* subpass = */ 0u,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ 0} };
        NV_VK_REPLAY(VulkanReplay_CreateGraphicsPipelines(VkDevice_uid_4, VkPipelineCache(VK_NULL_HANDLE), 1u, VkGraphicsPipelineCreateInfo_temp_11, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_5285)));
    }

    // Create VkPipeline_uid_6415
    {
        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_13[2] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_VERTEX_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_6413,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_FRAGMENT_BIT,
        /* module = */ /* module = */ VkShaderModule_uid_6414,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkVertexInputBindingDescription VkVertexInputBindingDescription_pVertexBindingDescriptions_12[1] = { VkVertexInputBindingDescription{
        /* binding = */ 0u,
        /* stride = */ 44u,
        /* inputRate = */ VK_VERTEX_INPUT_RATE_VERTEX} };
        static VkVertexInputAttributeDescription VkVertexInputAttributeDescription_pVertexAttributeDescriptions_12[4] = { VkVertexInputAttributeDescription{
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
        static VkPipelineVertexInputStateCreateInfo VkPipelineVertexInputStateCreateInfo_pVertexInputState_12[1] = { VkPipelineVertexInputStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineVertexInputStateCreateFlags(0),
        /* vertexBindingDescriptionCount = */ 1u,
        /* pVertexBindingDescriptions = */ VkVertexInputBindingDescription_pVertexBindingDescriptions_12,
        /* vertexAttributeDescriptionCount = */ 4u,
        /* pVertexAttributeDescriptions = */ VkVertexInputAttributeDescription_pVertexAttributeDescriptions_12} };
        static VkPipelineInputAssemblyStateCreateInfo VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_12[1] = { VkPipelineInputAssemblyStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineInputAssemblyStateCreateFlags(0),
        /* topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        /* primitiveRestartEnable = */ 0u} };
        static VkPipelineViewportStateCreateInfo VkPipelineViewportStateCreateInfo_pViewportState_12[1] = { VkPipelineViewportStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineViewportStateCreateFlags(0),
        /* viewportCount = */ 1u,
        /* pViewports = */ nullptr,
        /* scissorCount = */ 1u,
        /* pScissors = */ nullptr} };
        static VkPipelineRasterizationStateCreateInfo VkPipelineRasterizationStateCreateInfo_pRasterizationState_12[1] = { VkPipelineRasterizationStateCreateInfo{
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
        static VkPipelineMultisampleStateCreateInfo VkPipelineMultisampleStateCreateInfo_pMultisampleState_12[1] = { VkPipelineMultisampleStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineMultisampleStateCreateFlags(0),
        /* rasterizationSamples = */ VK_SAMPLE_COUNT_1_BIT,
        /* sampleShadingEnable = */ 0u,
        /* minSampleShading = */ HexToFloat(0x3F800000/*1.0f*/),
        /* pSampleMask = */ nullptr,
        /* alphaToCoverageEnable = */ 0u,
        /* alphaToOneEnable = */ 0u} };
        static VkPipelineDepthStencilStateCreateInfo VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_12[1] = { VkPipelineDepthStencilStateCreateInfo{
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
        static VkPipelineColorBlendAttachmentState VkPipelineColorBlendAttachmentState_pAttachments_12[2] = { VkPipelineColorBlendAttachmentState{
        /* blendEnable = */ 1u,
        /* srcColorBlendFactor = */ VK_BLEND_FACTOR_SRC_ALPHA,
        /* dstColorBlendFactor = */ VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
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
        static VkPipelineColorBlendStateCreateInfo VkPipelineColorBlendStateCreateInfo_pColorBlendState_12[1] = { VkPipelineColorBlendStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineColorBlendStateCreateFlags(0),
        /* logicOpEnable = */ 0u,
        /* logicOp = */ VK_LOGIC_OP_COPY,
        /* attachmentCount = */ 2u,
        /* pAttachments = */ VkPipelineColorBlendAttachmentState_pAttachments_12,
        /* blendConstants = */ NV_TO_ARRAY(0.0f, 0.0f, 0.0f, 0.0f)} };
        static VkDynamicState VkDynamicState_pDynamicStates_12[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        static VkPipelineDynamicStateCreateInfo VkPipelineDynamicStateCreateInfo_pDynamicState_13[1] = { VkPipelineDynamicStateCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineDynamicStateCreateFlags(0),
        /* dynamicStateCount = */ 2u,
        /* pDynamicStates = */ VkDynamicState_pDynamicStates_12} };
        static VkGraphicsPipelineCreateInfo VkGraphicsPipelineCreateInfo_temp_12[1] = { VkGraphicsPipelineCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 2u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_13,
        /* pVertexInputState = */ VkPipelineVertexInputStateCreateInfo_pVertexInputState_12,
        /* pInputAssemblyState = */ VkPipelineInputAssemblyStateCreateInfo_pInputAssemblyState_12,
        /* pTessellationState = */ nullptr,
        /* pViewportState = */ VkPipelineViewportStateCreateInfo_pViewportState_12,
        /* pRasterizationState = */ VkPipelineRasterizationStateCreateInfo_pRasterizationState_12,
        /* pMultisampleState = */ VkPipelineMultisampleStateCreateInfo_pMultisampleState_12,
        /* pDepthStencilState = */ VkPipelineDepthStencilStateCreateInfo_pDepthStencilState_12,
        /* pColorBlendState = */ VkPipelineColorBlendStateCreateInfo_pColorBlendState_12,
        /* pDynamicState = */ VkPipelineDynamicStateCreateInfo_pDynamicState_13,
        /* layout = */ VkPipelineLayout_uid_6412,
        /* renderPass = */ VkRenderPass_uid_5208,
        /* subpass = */ 0u,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ -1} };
        NV_VK_REPLAY(VulkanReplay_CreateGraphicsPipelines(VkDevice_uid_4, VkPipelineCache(VK_NULL_HANDLE), 1u, VkGraphicsPipelineCreateInfo_temp_12, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_6415)));
    }

    // Create VkPipeline_uid_6756
    {
        static VkPipelineShaderStageCreateInfo VkPipelineShaderStageCreateInfo_pStages_14[5] = { VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_RAYGEN_BIT_KHR,
        /* module = */ /* module = */ VkShaderModule_uid_6751,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_MISS_BIT_KHR,
        /* module = */ /* module = */ VkShaderModule_uid_6752,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_MISS_BIT_KHR,
        /* module = */ /* module = */ VkShaderModule_uid_6753,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
        /* module = */ /* module = */ VkShaderModule_uid_6754,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr}, VkPipelineShaderStageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineShaderStageCreateFlags(0),
        /* stage = */ VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
        /* module = */ /* module = */ VkShaderModule_uid_6755,
        /* pName = */ "main",
        /* pSpecializationInfo = */ nullptr} };
        static VkRayTracingShaderGroupCreateInfoKHR VkRayTracingShaderGroupCreateInfoKHR_pGroups_2[5] = { VkRayTracingShaderGroupCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR,
        /* generalShader = */ 0u,
        /* closestHitShader = */ 4294967295u,
        /* anyHitShader = */ 4294967295u,
        /* intersectionShader = */ 4294967295u,
        /* pShaderGroupCaptureReplayHandle = */ NV_VK_USER_PTR}, VkRayTracingShaderGroupCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR,
        /* generalShader = */ 1u,
        /* closestHitShader = */ 4294967295u,
        /* anyHitShader = */ 4294967295u,
        /* intersectionShader = */ 4294967295u,
        /* pShaderGroupCaptureReplayHandle = */ NV_VK_USER_PTR}, VkRayTracingShaderGroupCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR,
        /* generalShader = */ 2u,
        /* closestHitShader = */ 4294967295u,
        /* anyHitShader = */ 4294967295u,
        /* intersectionShader = */ 4294967295u,
        /* pShaderGroupCaptureReplayHandle = */ NV_VK_USER_PTR}, VkRayTracingShaderGroupCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR,
        /* generalShader = */ 4294967295u,
        /* closestHitShader = */ 3u,
        /* anyHitShader = */ 4294967295u,
        /* intersectionShader = */ 4294967295u,
        /* pShaderGroupCaptureReplayHandle = */ NV_VK_USER_PTR}, VkRayTracingShaderGroupCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* type = */ VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR,
        /* generalShader = */ 4294967295u,
        /* closestHitShader = */ 4u,
        /* anyHitShader = */ 4294967295u,
        /* intersectionShader = */ 4294967295u,
        /* pShaderGroupCaptureReplayHandle = */ NV_VK_USER_PTR} };
        static VkRayTracingPipelineCreateInfoKHR VkRayTracingPipelineCreateInfoKHR_temp_2[1] = { VkRayTracingPipelineCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* flags = */ VkPipelineCreateFlags(0),
        /* stageCount = */ 5u,
        /* pStages = */ VkPipelineShaderStageCreateInfo_pStages_14,
        /* groupCount = */ 5u,
        /* pGroups = */ VkRayTracingShaderGroupCreateInfoKHR_pGroups_2,
        /* maxPipelineRayRecursionDepth = */ 2u,
        /* pLibraryInfo = */ nullptr,
        /* pLibraryInterface = */ nullptr,
        /* pDynamicState = */ nullptr,
        /* layout = */ VkPipelineLayout_uid_6750,
        /* basePipelineHandle = */ VkPipeline(VK_NULL_HANDLE),
        /* basePipelineIndex = */ 0} };
        NV_VK_REPLAY(VulkanReplay_CreateRayTracingPipelinesKHR(VkDevice_uid_4, VkDeferredOperationKHR(VK_NULL_HANDLE), VkPipelineCache(VK_NULL_HANDLE), 1u, VkRayTracingPipelineCreateInfoKHR_temp_2, nullptr, NV_TO_OUTPUT_ARRAY(&VkPipeline_uid_6756)));

        NV_VK_REPLAY(VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice_uid_4, VkPipeline_uid_6756, 0u, 32u, NV_TO_STACK_PTR(uint8_t(0x0e), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x7c), uint8_t(0x03), uint8_t(0xff), uint8_t(0xff), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00))));
        NV_VK_REPLAY(VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice_uid_4, VkPipeline_uid_6756, 1u, 32u, NV_TO_STACK_PTR(uint8_t(0x11), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0xbc), uint8_t(0x03), uint8_t(0xff), uint8_t(0xff), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00))));
        NV_VK_REPLAY(VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice_uid_4, VkPipeline_uid_6756, 2u, 32u, NV_TO_STACK_PTR(uint8_t(0x12), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0xbc), uint8_t(0x03), uint8_t(0xff), uint8_t(0xff), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00))));
        NV_VK_REPLAY(VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice_uid_4, VkPipeline_uid_6756, 3u, 32u, NV_TO_STACK_PTR(uint8_t(0x13), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0xdc), uint8_t(0x03), uint8_t(0xff), uint8_t(0xff), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00))));
        NV_VK_REPLAY(VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice_uid_4, VkPipeline_uid_6756, 4u, 32u, NV_TO_STACK_PTR(uint8_t(0x16), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0xdc), uint8_t(0x03), uint8_t(0xff), uint8_t(0xff), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00), uint8_t(0x00))));
    }

    // Create VkFence_uid_25
    {
        BEGIN_DATA_SCOPE();

        static VkFenceCreateInfo VkFenceCreateInfo_temp_2[1] = { VkFenceCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkFenceCreateFlags(VK_FENCE_CREATE_SIGNALED_BIT)} };
        NV_VK_REPLAY(VulkanReplay_CreateFence(VkDevice_uid_4, VkFenceCreateInfo_temp_2, nullptr, &VkFence_uid_25));
    }

    // Create VkSemaphore_uid_23
    {
        static VkSemaphoreCreateInfo VkSemaphoreCreateInfo_temp_3[1] = { VkSemaphoreCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSemaphoreCreateFlags(0)} };
        NV_VK_REPLAY(VulkanReplay_CreateSemaphore(VkDevice_uid_4, VkSemaphoreCreateInfo_temp_3, nullptr, &VkSemaphore_uid_23));
    }

    // Create VkSemaphore_uid_24
    {
        static VkSemaphoreCreateInfo VkSemaphoreCreateInfo_temp_4[1] = { VkSemaphoreCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSemaphoreCreateFlags(0)} };
        NV_VK_REPLAY(VulkanReplay_CreateSemaphore(VkDevice_uid_4, VkSemaphoreCreateInfo_temp_4, nullptr, &VkSemaphore_uid_24));
    }

    // Create VkCommandBuffer_uid_9
    {
        static VkCommandBufferAllocateInfo VkCommandBufferAllocateInfo_temp_2[1] = { VkCommandBufferAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* commandPool = */ VkCommandPool_uid_7,
        /* level = */ VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        /* commandBufferCount = */ 1u} };
        NV_VK_REPLAY(VulkanReplay_AllocateCommandBuffers(VkDevice_uid_4, VkCommandBufferAllocateInfo_temp_2, NV_TO_OUTPUT_ARRAY(&VkCommandBuffer_uid_9)));
    }
}

//-----------------------------------------------------------------------------
// OnBeforeWinResourcesInit00
//-----------------------------------------------------------------------------
void OnBeforeWinResourcesInit00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

}

//-----------------------------------------------------------------------------
// CreateWinResources00
//-----------------------------------------------------------------------------
void CreateWinResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    #if !NV_USE_MANAGED_WINSYS
        // Create hwnd_00000000002F0AAC
        {
            BEGIN_DATA_SCOPE();

            NV_THROW_IF(!RegisterReplayerWindowClass(currentInstance, CS_HREDRAW | CS_OWNDC | CS_VREDRAW), "Failed to register window class");
            const uint32_t x = 0u;
            const uint32_t y = 0u;
            const uint32_t Width = 2200u;
            const uint32_t Height = 1300u;
            const DWORD Style = WS_BORDER | WS_DLGFRAME | WS_SYSMENU | WS_VISIBLE;
            const DWORD ExtendedStyle = WS_EX_LEFT;
            PROCESS_DPI_AWARENESS DpiAwareness = PROCESS_PER_MONITOR_DPI_AWARE;
            hwnd_00000000002F0AAC = CreateReplayerWindow(currentInstance, nullptr, x, y, Width, Height, Style, ExtendedStyle, DpiAwareness);
            NV_THROW_IF(!hwnd_00000000002F0AAC, "Failed to create replayer window");
        }
        #endif
}

//-----------------------------------------------------------------------------
// OnAfterWinResourcesInit00
//-----------------------------------------------------------------------------
void OnAfterWinResourcesInit00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

}

//-----------------------------------------------------------------------------
// ReleaseResources00
//-----------------------------------------------------------------------------
void ReleaseResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    NV_VK_REPLAY(VulkanHelper_ReleaseDevice(VkDevice_uid_4));
    NV_VK_REPLAY(VulkanHelper_ReleaseInstance(VkInstance_uid_1));
}

//-----------------------------------------------------------------------------
// ReleaseWinResources00
//-----------------------------------------------------------------------------
void ReleaseWinResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    #if !NV_USE_MANAGED_WINSYS
        // Release hwnd_00000000002F0AAC
        DestroyWindow(hwnd_00000000002F0AAC);
        #endif
}

//-----------------------------------------------------------------------------
// OnAfterWinResourcesReleased00
//-----------------------------------------------------------------------------
void OnAfterWinResourcesReleased00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

}

//-----------------------------------------------------------------------------
// Captured Resources
//-----------------------------------------------------------------------------
VkInstance VkInstance_uid_1;
VkPhysicalDevice VkPhysicalDevice_uid_2;
VkSurfaceKHR VkSurfaceKHR_uid_3;
VkDevice VkDevice_uid_4;
VkQueue VkQueue_uid_6;
VkCommandPool VkCommandPool_uid_7;
VkCommandBuffer VkCommandBuffer_uid_9;
VkSwapchainKHR VkSwapchainKHR_uid_13;
VkImage VkImage_uid_14;
VkImage VkImage_uid_15;
VkImageView VkImageView_uid_18;
VkSemaphore VkSemaphore_uid_23;
VkSemaphore VkSemaphore_uid_24;
VkFence VkFence_uid_25;
VkDescriptorPool VkDescriptorPool_uid_26;
VkDescriptorSet VkDescriptorSet_uid_40;
VkDescriptorSet VkDescriptorSet_uid_94;
VkDescriptorSet VkDescriptorSet_uid_109;
VkDescriptorSet VkDescriptorSet_uid_110;
VkDescriptorSet VkDescriptorSet_uid_111;
VkDescriptorSet VkDescriptorSet_uid_112;
VkDescriptorSet VkDescriptorSet_uid_113;
VkDescriptorSet VkDescriptorSet_uid_118;
VkDescriptorSet VkDescriptorSet_uid_119;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_5034;
VkImage VkImage_uid_5056;
VkDeviceMemory VkDeviceMemory_uid_5057;
VkImageView VkImageView_uid_5061;
VkSampler VkSampler_uid_5062;
VkBuffer VkBuffer_uid_5076;
VkDeviceMemory VkDeviceMemory_uid_5077;
VkBuffer VkBuffer_uid_5081;
VkDeviceMemory VkDeviceMemory_uid_5082;
VkRenderPass VkRenderPass_uid_5092;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_5095;
VkPipelineLayout VkPipelineLayout_uid_5096;
VkShaderModule VkShaderModule_uid_5097;
VkShaderModule VkShaderModule_uid_5098;
VkPipeline VkPipeline_uid_5099;
VkBuffer VkBuffer_uid_5155;
VkDeviceMemory VkDeviceMemory_uid_5156;
VkBuffer VkBuffer_uid_5157;
VkDeviceMemory VkDeviceMemory_uid_5158;
VkBuffer VkBuffer_uid_5185;
VkDeviceMemory VkDeviceMemory_uid_5186;
VkBuffer VkBuffer_uid_5190;
VkDeviceMemory VkDeviceMemory_uid_5191;
VkRenderPass VkRenderPass_uid_5208;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_5211;
VkPipelineLayout VkPipelineLayout_uid_5212;
VkRenderPass VkRenderPass_uid_5222;
VkPipelineLayout VkPipelineLayout_uid_5225;
VkShaderModule VkShaderModule_uid_5226;
VkShaderModule VkShaderModule_uid_5227;
VkPipeline VkPipeline_uid_5228;
VkBuffer VkBuffer_uid_5233;
VkDeviceMemory VkDeviceMemory_uid_5234;
VkBuffer VkBuffer_uid_5238;
VkDeviceMemory VkDeviceMemory_uid_5239;
VkRenderPass VkRenderPass_uid_5241;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_5245;
VkPipelineLayout VkPipelineLayout_uid_5246;
VkShaderModule VkShaderModule_uid_5247;
VkShaderModule VkShaderModule_uid_5248;
VkPipeline VkPipeline_uid_5249;
VkBuffer VkBuffer_uid_5254;
VkDeviceMemory VkDeviceMemory_uid_5255;
VkBuffer VkBuffer_uid_5259;
VkDeviceMemory VkDeviceMemory_uid_5260;
VkRenderPass VkRenderPass_uid_5266;
VkPipelineLayout VkPipelineLayout_uid_5269;
VkShaderModule VkShaderModule_uid_5270;
VkShaderModule VkShaderModule_uid_5271;
VkShaderModule VkShaderModule_uid_5272;
VkPipeline VkPipeline_uid_5273;
VkRenderPass VkRenderPass_uid_5277;
VkSampler VkSampler_uid_5280;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_5281;
VkPipelineLayout VkPipelineLayout_uid_5282;
VkShaderModule VkShaderModule_uid_5283;
VkShaderModule VkShaderModule_uid_5284;
VkPipeline VkPipeline_uid_5285;
VkImage VkImage_uid_5290;
VkDeviceMemory VkDeviceMemory_uid_5291;
VkImageView VkImageView_uid_5292;
VkBuffer VkBuffer_uid_5304;
VkDeviceMemory VkDeviceMemory_uid_5305;
VkBuffer VkBuffer_uid_5309;
VkDeviceMemory VkDeviceMemory_uid_5310;
VkBuffer VkBuffer_uid_5383;
VkDeviceMemory VkDeviceMemory_uid_5384;
VkBuffer VkBuffer_uid_5385;
VkDeviceMemory VkDeviceMemory_uid_5386;
VkBuffer VkBuffer_uid_5396;
VkDeviceMemory VkDeviceMemory_uid_5397;
VkBuffer VkBuffer_uid_5401;
VkDeviceMemory VkDeviceMemory_uid_5402;
VkBuffer VkBuffer_uid_5406;
VkDeviceMemory VkDeviceMemory_uid_5407;
VkBuffer VkBuffer_uid_5411;
VkDeviceMemory VkDeviceMemory_uid_5412;
VkBuffer VkBuffer_uid_5416;
VkDeviceMemory VkDeviceMemory_uid_5417;
VkBuffer VkBuffer_uid_5421;
VkDeviceMemory VkDeviceMemory_uid_5422;
VkBuffer VkBuffer_uid_5426;
VkDeviceMemory VkDeviceMemory_uid_5427;
VkBuffer VkBuffer_uid_5431;
VkDeviceMemory VkDeviceMemory_uid_5432;
VkBuffer VkBuffer_uid_5436;
VkDeviceMemory VkDeviceMemory_uid_5437;
VkBuffer VkBuffer_uid_5441;
VkDeviceMemory VkDeviceMemory_uid_5442;
VkBuffer VkBuffer_uid_5444;
VkDeviceMemory VkDeviceMemory_uid_5445;
VkBuffer VkBuffer_uid_5446;
VkDeviceMemory VkDeviceMemory_uid_5447;
VkBuffer VkBuffer_uid_5457;
VkDeviceMemory VkDeviceMemory_uid_5458;
VkBuffer VkBuffer_uid_5462;
VkDeviceMemory VkDeviceMemory_uid_5463;
VkBuffer VkBuffer_uid_5465;
VkDeviceMemory VkDeviceMemory_uid_5466;
VkBuffer VkBuffer_uid_5467;
VkDeviceMemory VkDeviceMemory_uid_5468;
VkBuffer VkBuffer_uid_5478;
VkDeviceMemory VkDeviceMemory_uid_5479;
VkBuffer VkBuffer_uid_5483;
VkDeviceMemory VkDeviceMemory_uid_5484;
VkBuffer VkBuffer_uid_5486;
VkDeviceMemory VkDeviceMemory_uid_5487;
VkBuffer VkBuffer_uid_5488;
VkDeviceMemory VkDeviceMemory_uid_5489;
VkBuffer VkBuffer_uid_5499;
VkDeviceMemory VkDeviceMemory_uid_5500;
VkBuffer VkBuffer_uid_5504;
VkDeviceMemory VkDeviceMemory_uid_5505;
VkBuffer VkBuffer_uid_5507;
VkDeviceMemory VkDeviceMemory_uid_5508;
VkBuffer VkBuffer_uid_5509;
VkDeviceMemory VkDeviceMemory_uid_5510;
VkBuffer VkBuffer_uid_5520;
VkDeviceMemory VkDeviceMemory_uid_5521;
VkBuffer VkBuffer_uid_5525;
VkDeviceMemory VkDeviceMemory_uid_5526;
VkBuffer VkBuffer_uid_5528;
VkDeviceMemory VkDeviceMemory_uid_5529;
VkBuffer VkBuffer_uid_5530;
VkDeviceMemory VkDeviceMemory_uid_5531;
VkBuffer VkBuffer_uid_5541;
VkDeviceMemory VkDeviceMemory_uid_5542;
VkBuffer VkBuffer_uid_5546;
VkDeviceMemory VkDeviceMemory_uid_5547;
VkBuffer VkBuffer_uid_5549;
VkDeviceMemory VkDeviceMemory_uid_5550;
VkBuffer VkBuffer_uid_5551;
VkDeviceMemory VkDeviceMemory_uid_5552;
VkBuffer VkBuffer_uid_5562;
VkDeviceMemory VkDeviceMemory_uid_5563;
VkBuffer VkBuffer_uid_5567;
VkDeviceMemory VkDeviceMemory_uid_5568;
VkBuffer VkBuffer_uid_5570;
VkDeviceMemory VkDeviceMemory_uid_5571;
VkBuffer VkBuffer_uid_5572;
VkDeviceMemory VkDeviceMemory_uid_5573;
VkBuffer VkBuffer_uid_5583;
VkDeviceMemory VkDeviceMemory_uid_5584;
VkBuffer VkBuffer_uid_5588;
VkDeviceMemory VkDeviceMemory_uid_5589;
VkBuffer VkBuffer_uid_5591;
VkDeviceMemory VkDeviceMemory_uid_5592;
VkBuffer VkBuffer_uid_5593;
VkDeviceMemory VkDeviceMemory_uid_5594;
VkBuffer VkBuffer_uid_5604;
VkDeviceMemory VkDeviceMemory_uid_5605;
VkBuffer VkBuffer_uid_5609;
VkDeviceMemory VkDeviceMemory_uid_5610;
VkBuffer VkBuffer_uid_5612;
VkDeviceMemory VkDeviceMemory_uid_5613;
VkBuffer VkBuffer_uid_5614;
VkDeviceMemory VkDeviceMemory_uid_5615;
VkBuffer VkBuffer_uid_5625;
VkDeviceMemory VkDeviceMemory_uid_5626;
VkBuffer VkBuffer_uid_5630;
VkDeviceMemory VkDeviceMemory_uid_5631;
VkBuffer VkBuffer_uid_5633;
VkDeviceMemory VkDeviceMemory_uid_5634;
VkBuffer VkBuffer_uid_5635;
VkDeviceMemory VkDeviceMemory_uid_5636;
VkBuffer VkBuffer_uid_5646;
VkDeviceMemory VkDeviceMemory_uid_5647;
VkBuffer VkBuffer_uid_5651;
VkDeviceMemory VkDeviceMemory_uid_5652;
VkBuffer VkBuffer_uid_5654;
VkDeviceMemory VkDeviceMemory_uid_5655;
VkBuffer VkBuffer_uid_5656;
VkDeviceMemory VkDeviceMemory_uid_5657;
VkBuffer VkBuffer_uid_5667;
VkDeviceMemory VkDeviceMemory_uid_5668;
VkBuffer VkBuffer_uid_5672;
VkDeviceMemory VkDeviceMemory_uid_5673;
VkBuffer VkBuffer_uid_5675;
VkDeviceMemory VkDeviceMemory_uid_5676;
VkBuffer VkBuffer_uid_5677;
VkDeviceMemory VkDeviceMemory_uid_5678;
VkBuffer VkBuffer_uid_5688;
VkDeviceMemory VkDeviceMemory_uid_5689;
VkBuffer VkBuffer_uid_5693;
VkDeviceMemory VkDeviceMemory_uid_5694;
VkBuffer VkBuffer_uid_5696;
VkDeviceMemory VkDeviceMemory_uid_5697;
VkBuffer VkBuffer_uid_5698;
VkDeviceMemory VkDeviceMemory_uid_5699;
VkBuffer VkBuffer_uid_5709;
VkDeviceMemory VkDeviceMemory_uid_5710;
VkBuffer VkBuffer_uid_5714;
VkDeviceMemory VkDeviceMemory_uid_5715;
VkBuffer VkBuffer_uid_5717;
VkDeviceMemory VkDeviceMemory_uid_5718;
VkBuffer VkBuffer_uid_5719;
VkDeviceMemory VkDeviceMemory_uid_5720;
VkBuffer VkBuffer_uid_5730;
VkDeviceMemory VkDeviceMemory_uid_5731;
VkBuffer VkBuffer_uid_5735;
VkDeviceMemory VkDeviceMemory_uid_5736;
VkBuffer VkBuffer_uid_5738;
VkDeviceMemory VkDeviceMemory_uid_5739;
VkBuffer VkBuffer_uid_5740;
VkDeviceMemory VkDeviceMemory_uid_5741;
VkBuffer VkBuffer_uid_5751;
VkDeviceMemory VkDeviceMemory_uid_5752;
VkBuffer VkBuffer_uid_5756;
VkDeviceMemory VkDeviceMemory_uid_5757;
VkBuffer VkBuffer_uid_5759;
VkDeviceMemory VkDeviceMemory_uid_5760;
VkBuffer VkBuffer_uid_5761;
VkDeviceMemory VkDeviceMemory_uid_5762;
VkBuffer VkBuffer_uid_5772;
VkDeviceMemory VkDeviceMemory_uid_5773;
VkBuffer VkBuffer_uid_5777;
VkDeviceMemory VkDeviceMemory_uid_5778;
VkBuffer VkBuffer_uid_5780;
VkDeviceMemory VkDeviceMemory_uid_5781;
VkBuffer VkBuffer_uid_5782;
VkDeviceMemory VkDeviceMemory_uid_5783;
VkBuffer VkBuffer_uid_5793;
VkDeviceMemory VkDeviceMemory_uid_5794;
VkBuffer VkBuffer_uid_5798;
VkDeviceMemory VkDeviceMemory_uid_5799;
VkBuffer VkBuffer_uid_5801;
VkDeviceMemory VkDeviceMemory_uid_5802;
VkBuffer VkBuffer_uid_5803;
VkDeviceMemory VkDeviceMemory_uid_5804;
VkBuffer VkBuffer_uid_5814;
VkDeviceMemory VkDeviceMemory_uid_5815;
VkBuffer VkBuffer_uid_5819;
VkDeviceMemory VkDeviceMemory_uid_5820;
VkBuffer VkBuffer_uid_5822;
VkDeviceMemory VkDeviceMemory_uid_5823;
VkBuffer VkBuffer_uid_5824;
VkDeviceMemory VkDeviceMemory_uid_5825;
VkBuffer VkBuffer_uid_5835;
VkDeviceMemory VkDeviceMemory_uid_5836;
VkBuffer VkBuffer_uid_5840;
VkDeviceMemory VkDeviceMemory_uid_5841;
VkBuffer VkBuffer_uid_5843;
VkDeviceMemory VkDeviceMemory_uid_5844;
VkBuffer VkBuffer_uid_5845;
VkDeviceMemory VkDeviceMemory_uid_5846;
VkBuffer VkBuffer_uid_5856;
VkDeviceMemory VkDeviceMemory_uid_5857;
VkBuffer VkBuffer_uid_5861;
VkDeviceMemory VkDeviceMemory_uid_5862;
VkBuffer VkBuffer_uid_5864;
VkDeviceMemory VkDeviceMemory_uid_5865;
VkBuffer VkBuffer_uid_5866;
VkDeviceMemory VkDeviceMemory_uid_5867;
VkBuffer VkBuffer_uid_5877;
VkDeviceMemory VkDeviceMemory_uid_5878;
VkBuffer VkBuffer_uid_5882;
VkDeviceMemory VkDeviceMemory_uid_5883;
VkBuffer VkBuffer_uid_5885;
VkDeviceMemory VkDeviceMemory_uid_5886;
VkBuffer VkBuffer_uid_5887;
VkDeviceMemory VkDeviceMemory_uid_5888;
VkBuffer VkBuffer_uid_5898;
VkDeviceMemory VkDeviceMemory_uid_5899;
VkBuffer VkBuffer_uid_5903;
VkDeviceMemory VkDeviceMemory_uid_5904;
VkBuffer VkBuffer_uid_5906;
VkDeviceMemory VkDeviceMemory_uid_5907;
VkBuffer VkBuffer_uid_5908;
VkDeviceMemory VkDeviceMemory_uid_5909;
VkBuffer VkBuffer_uid_5919;
VkDeviceMemory VkDeviceMemory_uid_5920;
VkBuffer VkBuffer_uid_5924;
VkDeviceMemory VkDeviceMemory_uid_5925;
VkBuffer VkBuffer_uid_5927;
VkDeviceMemory VkDeviceMemory_uid_5928;
VkBuffer VkBuffer_uid_5929;
VkDeviceMemory VkDeviceMemory_uid_5930;
VkBuffer VkBuffer_uid_5940;
VkDeviceMemory VkDeviceMemory_uid_5941;
VkBuffer VkBuffer_uid_5945;
VkDeviceMemory VkDeviceMemory_uid_5946;
VkBuffer VkBuffer_uid_5948;
VkDeviceMemory VkDeviceMemory_uid_5949;
VkBuffer VkBuffer_uid_5950;
VkDeviceMemory VkDeviceMemory_uid_5951;
VkBuffer VkBuffer_uid_5961;
VkDeviceMemory VkDeviceMemory_uid_5962;
VkBuffer VkBuffer_uid_5966;
VkDeviceMemory VkDeviceMemory_uid_5967;
VkBuffer VkBuffer_uid_5969;
VkDeviceMemory VkDeviceMemory_uid_5970;
VkBuffer VkBuffer_uid_5971;
VkDeviceMemory VkDeviceMemory_uid_5972;
VkBuffer VkBuffer_uid_5982;
VkDeviceMemory VkDeviceMemory_uid_5983;
VkBuffer VkBuffer_uid_5987;
VkDeviceMemory VkDeviceMemory_uid_5988;
VkBuffer VkBuffer_uid_5990;
VkDeviceMemory VkDeviceMemory_uid_5991;
VkBuffer VkBuffer_uid_5992;
VkDeviceMemory VkDeviceMemory_uid_5993;
VkBuffer VkBuffer_uid_6003;
VkDeviceMemory VkDeviceMemory_uid_6004;
VkBuffer VkBuffer_uid_6008;
VkDeviceMemory VkDeviceMemory_uid_6009;
VkBuffer VkBuffer_uid_6011;
VkDeviceMemory VkDeviceMemory_uid_6012;
VkBuffer VkBuffer_uid_6013;
VkDeviceMemory VkDeviceMemory_uid_6014;
VkBuffer VkBuffer_uid_6024;
VkDeviceMemory VkDeviceMemory_uid_6025;
VkBuffer VkBuffer_uid_6029;
VkDeviceMemory VkDeviceMemory_uid_6030;
VkBuffer VkBuffer_uid_6032;
VkDeviceMemory VkDeviceMemory_uid_6033;
VkBuffer VkBuffer_uid_6034;
VkDeviceMemory VkDeviceMemory_uid_6035;
VkBuffer VkBuffer_uid_6045;
VkDeviceMemory VkDeviceMemory_uid_6046;
VkBuffer VkBuffer_uid_6050;
VkDeviceMemory VkDeviceMemory_uid_6051;
VkBuffer VkBuffer_uid_6053;
VkDeviceMemory VkDeviceMemory_uid_6054;
VkBuffer VkBuffer_uid_6055;
VkDeviceMemory VkDeviceMemory_uid_6056;
VkBuffer VkBuffer_uid_6066;
VkDeviceMemory VkDeviceMemory_uid_6067;
VkBuffer VkBuffer_uid_6071;
VkDeviceMemory VkDeviceMemory_uid_6072;
VkBuffer VkBuffer_uid_6074;
VkDeviceMemory VkDeviceMemory_uid_6075;
VkBuffer VkBuffer_uid_6076;
VkDeviceMemory VkDeviceMemory_uid_6077;
VkBuffer VkBuffer_uid_6087;
VkDeviceMemory VkDeviceMemory_uid_6088;
VkBuffer VkBuffer_uid_6092;
VkDeviceMemory VkDeviceMemory_uid_6093;
VkBuffer VkBuffer_uid_6095;
VkDeviceMemory VkDeviceMemory_uid_6096;
VkBuffer VkBuffer_uid_6097;
VkDeviceMemory VkDeviceMemory_uid_6098;
VkBuffer VkBuffer_uid_6108;
VkDeviceMemory VkDeviceMemory_uid_6109;
VkBuffer VkBuffer_uid_6113;
VkDeviceMemory VkDeviceMemory_uid_6114;
VkBuffer VkBuffer_uid_6116;
VkDeviceMemory VkDeviceMemory_uid_6117;
VkBuffer VkBuffer_uid_6118;
VkDeviceMemory VkDeviceMemory_uid_6119;
VkBuffer VkBuffer_uid_6129;
VkDeviceMemory VkDeviceMemory_uid_6130;
VkBuffer VkBuffer_uid_6134;
VkDeviceMemory VkDeviceMemory_uid_6135;
VkBuffer VkBuffer_uid_6137;
VkDeviceMemory VkDeviceMemory_uid_6138;
VkBuffer VkBuffer_uid_6139;
VkDeviceMemory VkDeviceMemory_uid_6140;
VkBuffer VkBuffer_uid_6150;
VkDeviceMemory VkDeviceMemory_uid_6151;
VkBuffer VkBuffer_uid_6155;
VkDeviceMemory VkDeviceMemory_uid_6156;
VkBuffer VkBuffer_uid_6158;
VkDeviceMemory VkDeviceMemory_uid_6159;
VkBuffer VkBuffer_uid_6160;
VkDeviceMemory VkDeviceMemory_uid_6161;
VkBuffer VkBuffer_uid_6171;
VkDeviceMemory VkDeviceMemory_uid_6172;
VkBuffer VkBuffer_uid_6176;
VkDeviceMemory VkDeviceMemory_uid_6177;
VkBuffer VkBuffer_uid_6179;
VkDeviceMemory VkDeviceMemory_uid_6180;
VkBuffer VkBuffer_uid_6181;
VkDeviceMemory VkDeviceMemory_uid_6182;
VkBuffer VkBuffer_uid_6192;
VkDeviceMemory VkDeviceMemory_uid_6193;
VkBuffer VkBuffer_uid_6197;
VkDeviceMemory VkDeviceMemory_uid_6198;
VkBuffer VkBuffer_uid_6200;
VkDeviceMemory VkDeviceMemory_uid_6201;
VkBuffer VkBuffer_uid_6202;
VkDeviceMemory VkDeviceMemory_uid_6203;
VkBuffer VkBuffer_uid_6213;
VkDeviceMemory VkDeviceMemory_uid_6214;
VkBuffer VkBuffer_uid_6218;
VkDeviceMemory VkDeviceMemory_uid_6219;
VkBuffer VkBuffer_uid_6221;
VkDeviceMemory VkDeviceMemory_uid_6222;
VkBuffer VkBuffer_uid_6223;
VkDeviceMemory VkDeviceMemory_uid_6224;
VkBuffer VkBuffer_uid_6234;
VkDeviceMemory VkDeviceMemory_uid_6235;
VkBuffer VkBuffer_uid_6239;
VkDeviceMemory VkDeviceMemory_uid_6240;
VkBuffer VkBuffer_uid_6242;
VkDeviceMemory VkDeviceMemory_uid_6243;
VkBuffer VkBuffer_uid_6244;
VkDeviceMemory VkDeviceMemory_uid_6245;
VkBuffer VkBuffer_uid_6255;
VkDeviceMemory VkDeviceMemory_uid_6256;
VkBuffer VkBuffer_uid_6260;
VkDeviceMemory VkDeviceMemory_uid_6261;
VkBuffer VkBuffer_uid_6263;
VkDeviceMemory VkDeviceMemory_uid_6264;
VkBuffer VkBuffer_uid_6265;
VkDeviceMemory VkDeviceMemory_uid_6266;
VkBuffer VkBuffer_uid_6276;
VkDeviceMemory VkDeviceMemory_uid_6277;
VkBuffer VkBuffer_uid_6281;
VkDeviceMemory VkDeviceMemory_uid_6282;
VkBuffer VkBuffer_uid_6284;
VkDeviceMemory VkDeviceMemory_uid_6285;
VkBuffer VkBuffer_uid_6286;
VkDeviceMemory VkDeviceMemory_uid_6287;
VkBuffer VkBuffer_uid_6297;
VkDeviceMemory VkDeviceMemory_uid_6298;
VkBuffer VkBuffer_uid_6302;
VkDeviceMemory VkDeviceMemory_uid_6303;
VkBuffer VkBuffer_uid_6305;
VkDeviceMemory VkDeviceMemory_uid_6306;
VkBuffer VkBuffer_uid_6307;
VkDeviceMemory VkDeviceMemory_uid_6308;
VkBuffer VkBuffer_uid_6318;
VkDeviceMemory VkDeviceMemory_uid_6319;
VkBuffer VkBuffer_uid_6323;
VkDeviceMemory VkDeviceMemory_uid_6324;
VkBuffer VkBuffer_uid_6326;
VkDeviceMemory VkDeviceMemory_uid_6327;
VkBuffer VkBuffer_uid_6328;
VkDeviceMemory VkDeviceMemory_uid_6329;
VkBuffer VkBuffer_uid_6339;
VkDeviceMemory VkDeviceMemory_uid_6340;
VkBuffer VkBuffer_uid_6344;
VkDeviceMemory VkDeviceMemory_uid_6345;
VkBuffer VkBuffer_uid_6347;
VkDeviceMemory VkDeviceMemory_uid_6348;
VkBuffer VkBuffer_uid_6349;
VkDeviceMemory VkDeviceMemory_uid_6350;
VkBuffer VkBuffer_uid_6360;
VkDeviceMemory VkDeviceMemory_uid_6361;
VkBuffer VkBuffer_uid_6365;
VkDeviceMemory VkDeviceMemory_uid_6366;
VkImage VkImage_uid_6370;
VkDeviceMemory VkDeviceMemory_uid_6371;
VkImageView VkImageView_uid_6375;
VkSampler VkSampler_uid_6376;
VkBuffer VkBuffer_uid_6386;
VkDeviceMemory VkDeviceMemory_uid_6387;
VkBuffer VkBuffer_uid_6391;
VkDeviceMemory VkDeviceMemory_uid_6392;
VkBuffer VkBuffer_uid_6403;
VkDeviceMemory VkDeviceMemory_uid_6404;
VkBuffer VkBuffer_uid_6408;
VkDeviceMemory VkDeviceMemory_uid_6409;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6411;
VkPipelineLayout VkPipelineLayout_uid_6412;
VkShaderModule VkShaderModule_uid_6413;
VkShaderModule VkShaderModule_uid_6414;
VkPipeline VkPipeline_uid_6415;
VkBuffer VkBuffer_uid_6420;
VkDeviceMemory VkDeviceMemory_uid_6421;
VkBuffer VkBuffer_uid_6425;
VkDeviceMemory VkDeviceMemory_uid_6426;
VkBuffer VkBuffer_uid_6580;
VkDeviceMemory VkDeviceMemory_uid_6581;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6582;
VkBuffer VkBuffer_uid_6583;
VkDeviceMemory VkDeviceMemory_uid_6584;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6585;
VkBuffer VkBuffer_uid_6586;
VkDeviceMemory VkDeviceMemory_uid_6587;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6588;
VkBuffer VkBuffer_uid_6589;
VkDeviceMemory VkDeviceMemory_uid_6590;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6591;
VkBuffer VkBuffer_uid_6592;
VkDeviceMemory VkDeviceMemory_uid_6593;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6594;
VkBuffer VkBuffer_uid_6595;
VkDeviceMemory VkDeviceMemory_uid_6596;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6597;
VkBuffer VkBuffer_uid_6598;
VkDeviceMemory VkDeviceMemory_uid_6599;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6600;
VkBuffer VkBuffer_uid_6601;
VkDeviceMemory VkDeviceMemory_uid_6602;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6603;
VkBuffer VkBuffer_uid_6604;
VkDeviceMemory VkDeviceMemory_uid_6605;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6606;
VkBuffer VkBuffer_uid_6607;
VkDeviceMemory VkDeviceMemory_uid_6608;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6609;
VkBuffer VkBuffer_uid_6610;
VkDeviceMemory VkDeviceMemory_uid_6611;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6612;
VkBuffer VkBuffer_uid_6613;
VkDeviceMemory VkDeviceMemory_uid_6614;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6615;
VkBuffer VkBuffer_uid_6616;
VkDeviceMemory VkDeviceMemory_uid_6617;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6618;
VkBuffer VkBuffer_uid_6619;
VkDeviceMemory VkDeviceMemory_uid_6620;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6621;
VkBuffer VkBuffer_uid_6622;
VkDeviceMemory VkDeviceMemory_uid_6623;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6624;
VkBuffer VkBuffer_uid_6625;
VkDeviceMemory VkDeviceMemory_uid_6626;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6627;
VkBuffer VkBuffer_uid_6628;
VkDeviceMemory VkDeviceMemory_uid_6629;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6630;
VkBuffer VkBuffer_uid_6631;
VkDeviceMemory VkDeviceMemory_uid_6632;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6633;
VkBuffer VkBuffer_uid_6634;
VkDeviceMemory VkDeviceMemory_uid_6635;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6636;
VkBuffer VkBuffer_uid_6637;
VkDeviceMemory VkDeviceMemory_uid_6638;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6639;
VkBuffer VkBuffer_uid_6640;
VkDeviceMemory VkDeviceMemory_uid_6641;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6642;
VkBuffer VkBuffer_uid_6643;
VkDeviceMemory VkDeviceMemory_uid_6644;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6645;
VkBuffer VkBuffer_uid_6646;
VkDeviceMemory VkDeviceMemory_uid_6647;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6648;
VkBuffer VkBuffer_uid_6649;
VkDeviceMemory VkDeviceMemory_uid_6650;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6651;
VkBuffer VkBuffer_uid_6652;
VkDeviceMemory VkDeviceMemory_uid_6653;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6654;
VkBuffer VkBuffer_uid_6655;
VkDeviceMemory VkDeviceMemory_uid_6656;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6657;
VkBuffer VkBuffer_uid_6658;
VkDeviceMemory VkDeviceMemory_uid_6659;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6660;
VkBuffer VkBuffer_uid_6661;
VkDeviceMemory VkDeviceMemory_uid_6662;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6663;
VkBuffer VkBuffer_uid_6664;
VkDeviceMemory VkDeviceMemory_uid_6665;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6666;
VkBuffer VkBuffer_uid_6667;
VkDeviceMemory VkDeviceMemory_uid_6668;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6669;
VkBuffer VkBuffer_uid_6670;
VkDeviceMemory VkDeviceMemory_uid_6671;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6672;
VkBuffer VkBuffer_uid_6673;
VkDeviceMemory VkDeviceMemory_uid_6674;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6675;
VkBuffer VkBuffer_uid_6676;
VkDeviceMemory VkDeviceMemory_uid_6677;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6678;
VkBuffer VkBuffer_uid_6679;
VkDeviceMemory VkDeviceMemory_uid_6680;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6681;
VkBuffer VkBuffer_uid_6682;
VkDeviceMemory VkDeviceMemory_uid_6683;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6684;
VkBuffer VkBuffer_uid_6685;
VkDeviceMemory VkDeviceMemory_uid_6686;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6687;
VkBuffer VkBuffer_uid_6688;
VkDeviceMemory VkDeviceMemory_uid_6689;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6690;
VkBuffer VkBuffer_uid_6691;
VkDeviceMemory VkDeviceMemory_uid_6692;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6693;
VkBuffer VkBuffer_uid_6694;
VkDeviceMemory VkDeviceMemory_uid_6695;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6696;
VkBuffer VkBuffer_uid_6697;
VkDeviceMemory VkDeviceMemory_uid_6698;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6699;
VkBuffer VkBuffer_uid_6700;
VkDeviceMemory VkDeviceMemory_uid_6701;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6702;
VkBuffer VkBuffer_uid_6703;
VkDeviceMemory VkDeviceMemory_uid_6704;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6705;
VkBuffer VkBuffer_uid_6706;
VkDeviceMemory VkDeviceMemory_uid_6707;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6708;
VkBuffer VkBuffer_uid_6709;
VkDeviceMemory VkDeviceMemory_uid_6710;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6711;
VkBuffer VkBuffer_uid_6712;
VkDeviceMemory VkDeviceMemory_uid_6713;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6714;
VkBuffer VkBuffer_uid_6715;
VkDeviceMemory VkDeviceMemory_uid_6716;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6717;
VkBuffer VkBuffer_uid_6718;
VkDeviceMemory VkDeviceMemory_uid_6719;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6720;
VkBuffer VkBuffer_uid_6721;
VkDeviceMemory VkDeviceMemory_uid_6722;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6723;
VkBuffer VkBuffer_uid_6724;
VkDeviceMemory VkDeviceMemory_uid_6725;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6726;
VkBuffer VkBuffer_uid_6733;
VkDeviceMemory VkDeviceMemory_uid_6734;
VkAccelerationStructureKHR VkAccelerationStructureKHR_uid_6735;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6747;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6748;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6749;
VkPipelineLayout VkPipelineLayout_uid_6750;
VkShaderModule VkShaderModule_uid_6751;
VkShaderModule VkShaderModule_uid_6752;
VkShaderModule VkShaderModule_uid_6753;
VkShaderModule VkShaderModule_uid_6754;
VkShaderModule VkShaderModule_uid_6755;
VkPipeline VkPipeline_uid_6756;
VkBuffer VkBuffer_uid_6762;
VkDeviceMemory VkDeviceMemory_uid_6763;
VkImage VkImage_uid_6887;
VkDeviceMemory VkDeviceMemory_uid_6888;
VkImageView VkImageView_uid_6889;
VkImage VkImage_uid_6892;
VkDeviceMemory VkDeviceMemory_uid_6893;
VkImageView VkImageView_uid_6894;
VkSampler VkSampler_uid_6895;
VkImage VkImage_uid_6909;
VkDeviceMemory VkDeviceMemory_uid_6910;
VkImageView VkImageView_uid_6911;
VkImage VkImage_uid_6918;
VkDeviceMemory VkDeviceMemory_uid_6919;
VkImageView VkImageView_uid_6920;
VkImage VkImage_uid_6922;
VkDeviceMemory VkDeviceMemory_uid_6923;
VkImageView VkImageView_uid_6924;
VkImage VkImage_uid_6939;
VkDeviceMemory VkDeviceMemory_uid_6940;
VkImageView VkImageView_uid_6941;
VkSampler VkSampler_uid_6942;
VkRenderPass VkRenderPass_uid_6943;
VkFramebuffer VkFramebuffer_uid_6945;
VkBuffer VkBuffer_uid_6946;
VkDeviceMemory VkDeviceMemory_uid_6947;
VkBuffer VkBuffer_uid_6948;
VkDeviceMemory VkDeviceMemory_uid_6949;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6950;
VkBuffer VkBuffer_uid_6954;
VkDeviceMemory VkDeviceMemory_uid_6955;
VkBuffer VkBuffer_uid_6956;
VkDeviceMemory VkDeviceMemory_uid_6957;
VkBuffer VkBuffer_uid_6958;
VkDeviceMemory VkDeviceMemory_uid_6959;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6960;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6961;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6962;
VkRenderPass VkRenderPass_uid_6963;
VkFramebuffer VkFramebuffer_uid_6965;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6966;
VkBuffer VkBuffer_uid_6973;
VkDeviceMemory VkDeviceMemory_uid_6974;
VkBuffer VkBuffer_uid_6979;
VkDeviceMemory VkDeviceMemory_uid_6980;
VkBuffer VkBuffer_uid_6981;
VkDeviceMemory VkDeviceMemory_uid_6982;
VkRenderPass VkRenderPass_uid_6985;
VkFramebuffer VkFramebuffer_uid_6987;
VkRenderPass VkRenderPass_uid_6988;
VkFramebuffer VkFramebuffer_uid_6990;
VkRenderPass VkRenderPass_uid_6991;
VkFramebuffer VkFramebuffer_uid_6993;
VkDescriptorSetLayout VkDescriptorSetLayout_uid_6995;
VkRenderPass VkRenderPass_uid_6996;
VkFramebuffer VkFramebuffer_uid_6998;
VkRenderPass VkRenderPass_uid_6999;
VkFramebuffer VkFramebuffer_uid_7001;
VkBuffer VkBuffer_uid_7268;
VkDeviceMemory VkDeviceMemory_uid_7269;
VkBuffer VkBuffer_uid_7289;
VkDeviceMemory VkDeviceMemory_uid_7290;
#if !NV_USE_MANAGED_WINSYS

HWND hwnd_00000000002F0AAC;
#endif

void* VkDeviceMemory_uid_5156_MappedPointer = NULL;
void* VkDeviceMemory_uid_5158_MappedPointer = NULL;
void* VkDeviceMemory_uid_5384_MappedPointer = NULL;
void* VkDeviceMemory_uid_5386_MappedPointer = NULL;
void* VkDeviceMemory_uid_5445_MappedPointer = NULL;
void* VkDeviceMemory_uid_5447_MappedPointer = NULL;
void* VkDeviceMemory_uid_5466_MappedPointer = NULL;
void* VkDeviceMemory_uid_5468_MappedPointer = NULL;
void* VkDeviceMemory_uid_5487_MappedPointer = NULL;
void* VkDeviceMemory_uid_5489_MappedPointer = NULL;
void* VkDeviceMemory_uid_5508_MappedPointer = NULL;
void* VkDeviceMemory_uid_5510_MappedPointer = NULL;
void* VkDeviceMemory_uid_5529_MappedPointer = NULL;
void* VkDeviceMemory_uid_5531_MappedPointer = NULL;
void* VkDeviceMemory_uid_5550_MappedPointer = NULL;
void* VkDeviceMemory_uid_5552_MappedPointer = NULL;
void* VkDeviceMemory_uid_5571_MappedPointer = NULL;
void* VkDeviceMemory_uid_5573_MappedPointer = NULL;
void* VkDeviceMemory_uid_5592_MappedPointer = NULL;
void* VkDeviceMemory_uid_5594_MappedPointer = NULL;
void* VkDeviceMemory_uid_5613_MappedPointer = NULL;
void* VkDeviceMemory_uid_5615_MappedPointer = NULL;
void* VkDeviceMemory_uid_5634_MappedPointer = NULL;
void* VkDeviceMemory_uid_5636_MappedPointer = NULL;
void* VkDeviceMemory_uid_5655_MappedPointer = NULL;
void* VkDeviceMemory_uid_5657_MappedPointer = NULL;
void* VkDeviceMemory_uid_5676_MappedPointer = NULL;
void* VkDeviceMemory_uid_5678_MappedPointer = NULL;
void* VkDeviceMemory_uid_5697_MappedPointer = NULL;
void* VkDeviceMemory_uid_5699_MappedPointer = NULL;
void* VkDeviceMemory_uid_5718_MappedPointer = NULL;
void* VkDeviceMemory_uid_5720_MappedPointer = NULL;
void* VkDeviceMemory_uid_5739_MappedPointer = NULL;
void* VkDeviceMemory_uid_5741_MappedPointer = NULL;
void* VkDeviceMemory_uid_5760_MappedPointer = NULL;
void* VkDeviceMemory_uid_5762_MappedPointer = NULL;
void* VkDeviceMemory_uid_5781_MappedPointer = NULL;
void* VkDeviceMemory_uid_5783_MappedPointer = NULL;
void* VkDeviceMemory_uid_5802_MappedPointer = NULL;
void* VkDeviceMemory_uid_5804_MappedPointer = NULL;
void* VkDeviceMemory_uid_5823_MappedPointer = NULL;
void* VkDeviceMemory_uid_5825_MappedPointer = NULL;
void* VkDeviceMemory_uid_5844_MappedPointer = NULL;
void* VkDeviceMemory_uid_5846_MappedPointer = NULL;
void* VkDeviceMemory_uid_5865_MappedPointer = NULL;
void* VkDeviceMemory_uid_5867_MappedPointer = NULL;
void* VkDeviceMemory_uid_5886_MappedPointer = NULL;
void* VkDeviceMemory_uid_5888_MappedPointer = NULL;
void* VkDeviceMemory_uid_5907_MappedPointer = NULL;
void* VkDeviceMemory_uid_5909_MappedPointer = NULL;
void* VkDeviceMemory_uid_5928_MappedPointer = NULL;
void* VkDeviceMemory_uid_5930_MappedPointer = NULL;
void* VkDeviceMemory_uid_5949_MappedPointer = NULL;
void* VkDeviceMemory_uid_5951_MappedPointer = NULL;
void* VkDeviceMemory_uid_5970_MappedPointer = NULL;
void* VkDeviceMemory_uid_5972_MappedPointer = NULL;
void* VkDeviceMemory_uid_5991_MappedPointer = NULL;
void* VkDeviceMemory_uid_5993_MappedPointer = NULL;
void* VkDeviceMemory_uid_6012_MappedPointer = NULL;
void* VkDeviceMemory_uid_6014_MappedPointer = NULL;
void* VkDeviceMemory_uid_6033_MappedPointer = NULL;
void* VkDeviceMemory_uid_6035_MappedPointer = NULL;
void* VkDeviceMemory_uid_6054_MappedPointer = NULL;
void* VkDeviceMemory_uid_6056_MappedPointer = NULL;
void* VkDeviceMemory_uid_6075_MappedPointer = NULL;
void* VkDeviceMemory_uid_6077_MappedPointer = NULL;
void* VkDeviceMemory_uid_6096_MappedPointer = NULL;
void* VkDeviceMemory_uid_6098_MappedPointer = NULL;
void* VkDeviceMemory_uid_6117_MappedPointer = NULL;
void* VkDeviceMemory_uid_6119_MappedPointer = NULL;
void* VkDeviceMemory_uid_6138_MappedPointer = NULL;
void* VkDeviceMemory_uid_6140_MappedPointer = NULL;
void* VkDeviceMemory_uid_6159_MappedPointer = NULL;
void* VkDeviceMemory_uid_6161_MappedPointer = NULL;
void* VkDeviceMemory_uid_6180_MappedPointer = NULL;
void* VkDeviceMemory_uid_6182_MappedPointer = NULL;
void* VkDeviceMemory_uid_6201_MappedPointer = NULL;
void* VkDeviceMemory_uid_6203_MappedPointer = NULL;
void* VkDeviceMemory_uid_6222_MappedPointer = NULL;
void* VkDeviceMemory_uid_6224_MappedPointer = NULL;
void* VkDeviceMemory_uid_6243_MappedPointer = NULL;
void* VkDeviceMemory_uid_6245_MappedPointer = NULL;
void* VkDeviceMemory_uid_6264_MappedPointer = NULL;
void* VkDeviceMemory_uid_6266_MappedPointer = NULL;
void* VkDeviceMemory_uid_6285_MappedPointer = NULL;
void* VkDeviceMemory_uid_6287_MappedPointer = NULL;
void* VkDeviceMemory_uid_6306_MappedPointer = NULL;
void* VkDeviceMemory_uid_6308_MappedPointer = NULL;
void* VkDeviceMemory_uid_6327_MappedPointer = NULL;
void* VkDeviceMemory_uid_6329_MappedPointer = NULL;
void* VkDeviceMemory_uid_6348_MappedPointer = NULL;
void* VkDeviceMemory_uid_6350_MappedPointer = NULL;
void* VkDeviceMemory_uid_6947_MappedPointer = NULL;
void* VkDeviceMemory_uid_6949_MappedPointer = NULL;
void* VkDeviceMemory_uid_6955_MappedPointer = NULL;
void* VkDeviceMemory_uid_6957_MappedPointer = NULL;
void* VkDeviceMemory_uid_6959_MappedPointer = NULL;
void* VkDeviceMemory_uid_6974_MappedPointer = NULL;
void* VkDeviceMemory_uid_6980_MappedPointer = NULL;
void* VkDeviceMemory_uid_6982_MappedPointer = NULL;
void* VkDeviceMemory_uid_7269_MappedPointer = NULL;
void* VkDeviceMemory_uid_7290_MappedPointer = NULL;
NV_REPLAY_END_RESOURCE_INIT()
