//---------------------------------------------------------------------------
// File: function_overrides.cpp
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#include "function_overrides.h"

//
// Example override usage:
//
// function_overrides.h
//
//     #define VKCREATEINSTANCE_PRE(...)  OVERRIDE_VkCreateInstance_Pre(__VA_ARGS__)
//     #define VKCREATEINSTANCE_POST(...) OVERRIDE_VkCreateInstance_Post(__VA_ARGS__)
//
//     void OVERRIDE_VkCreateInstance_Pre(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
//     void OVERRIDE_VkCreateInstance_Post(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
//
// function_overrides.cpp
//
//     void OVERRIDE_VkCreateInstance_Pre(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
//     {
//     }
//
//     void OVERRIDE_VkCreateInstance_Post(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
//     {
//     }
//
