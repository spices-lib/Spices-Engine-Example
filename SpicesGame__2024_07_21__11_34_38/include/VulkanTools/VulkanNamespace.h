#if !defined(VK_NAMESPACE)
#if defined(NV_VULKAN_SC_SUPPORT)
#define VK_NAMESPACE VKSC
#else
#define VK_NAMESPACE VK
#endif
#endif

#if !defined(VK_NAMESPACE_NON_INLINE)
#if defined(NV_VULKAN_SC_SUPPORT)
#define VK_NAMESPACE_NON_INLINE VKSC_NON_INLINE
#else
#define VK_NAMESPACE_NON_INLINE VK_NON_INLINE
#endif
#endif