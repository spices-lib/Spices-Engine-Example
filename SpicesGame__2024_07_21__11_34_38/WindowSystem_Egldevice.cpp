//---------------------------------------------------------------------------
// File: WindowSystem_Egldevice.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <dlfcn.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <map>
#include <vector>

// QNX currently uses OpenWFD device
#if defined(__QNX__)
#define USE_DRM_DEVICE 0
#define USE_OPENWFD_DEVICE 1
#else
#define USE_DRM_DEVICE 1
#define USE_OPENWFD_DEVICE 0
#endif

#if USE_DRM_DEVICE
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm_fourcc.h>

// In case eglext.h does not yet have EGL_DRM_MASTER_FD_EXT
#ifndef EGL_DRM_MASTER_FD_EXT
#define EGL_DRM_MASTER_FD_EXT 0x333C
#endif
#endif // USE_DRM_DEVICE

#if USE_OPENWFD_DEVICE
#include <WF/wfd.h>
#include <WF/wfdext.h>

// eglext.h does not yet have EGL_OPENWF_DEVICE_EXT
#ifndef EGL_OPENWF_DEVICE_EXT
#define EGL_OPENWF_DEVICE_EXT 0x333D
#endif
#endif // USE_OPENWFD_DEVICE

namespace // unnamed
{

#if USE_DRM_DEVICE

using PFNDRMOPEN = int (*)(const char*, const char*);
using PFNDRMMODEGETRESOURCES = drmModeResPtr (*)(int);
using PFNDRMMODEFREERESOURCES = void (*)(drmModeResPtr);
using PFNDRMMODEGETPLANERESOURCES = drmModePlaneResPtr (*)(int);
using PFNDRMMODEFREEPLANERESOURCES = void (*)(drmModePlaneResPtr);
using PFNDRMMODEGETCONNECTOR = drmModeConnectorPtr (*)(int, uint32_t);
using PFNDRMMODEFREECONNECTOR = void (*)(drmModeConnectorPtr);
using PFNDRMMODEGETENCODER = drmModeEncoderPtr (*)(int, uint32_t);
using PFNDRMMODEFREEENCODER = void (*)(drmModeEncoderPtr);
using PFNDRMMODEGETPLANE = drmModePlanePtr (*)(int, uint32_t);
using PFNDRMMODEFREEPLANE = void (*)(drmModePlanePtr);
using PFNDRMMODESETCRTC = int (*)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t*, int, drmModeModeInfoPtr);
using PFNDRMMODEGETCRTC = drmModeCrtcPtr (*)(int, uint32_t);
using PFNDRMMODESETPLANE = int (*)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
using PFNDRMMODEFREECRTC = void (*)(drmModeCrtcPtr);
using PFNDRMSETCLIENTCAP = int (*)(int, uint64_t, uint64_t);
using PFNDRMIOCTL = int (*)(int, unsigned long, void*);
using PFNDRMMODEADDFB2 = int (*)(int, uint32_t, uint32_t, uint32_t, const uint32_t*, const uint32_t*, const uint32_t*, uint32_t*, uint32_t);
using PFNDRMMODECREATEPROPERTYBLOB = int (*)(int, const void*, size_t, uint32_t*);
using PFNDRMMODEGETPROPERTY = drmModePropertyPtr (*)(int, uint32_t);
using PFNDRMMODEFREEPROPERTY = void (*)(drmModePropertyPtr);
using PFNDRMMODEOBJECTGETPROPERTIES = drmModeObjectPropertiesPtr (*)(int, uint32_t, uint32_t);
using PFNDRMMODEFREEOBJECTPROPERTIES = void (*)(drmModeObjectPropertiesPtr);
using PFNDRMMODEATOMICADDPROPERTY = int (*)(drmModeAtomicReqPtr, uint32_t, uint32_t, uint64_t);
using PFNDRMMODEATOMICFREE = void (*)(drmModeAtomicReqPtr);
using PFNDRMMODEATOMICALLOC = drmModeAtomicReqPtr (*)(void);
using PFNDRMMODEATOMICCOMMIT = int (*)(int, drmModeAtomicReqPtr, uint32_t, void*);
using PFNDRMGETVERSION = drmVersionPtr (*)(int);
using PFNDRMFREEVERSION = void (*)(drmVersionPtr);

PFNDRMOPEN FP_drmOpen = nullptr;
PFNDRMMODEGETRESOURCES FP_drmModeGetResources = nullptr;
PFNDRMMODEFREERESOURCES FP_drmModeFreeResources = nullptr;
PFNDRMMODEGETPLANERESOURCES FP_drmModeGetPlaneResources = nullptr;
PFNDRMMODEFREEPLANERESOURCES FP_drmModeFreePlaneResources = nullptr;
PFNDRMMODEGETCONNECTOR FP_drmModeGetConnector = nullptr;
PFNDRMMODEFREECONNECTOR FP_drmModeFreeConnector = nullptr;
PFNDRMMODEGETENCODER FP_drmModeGetEncoder = nullptr;
PFNDRMMODEFREEENCODER FP_drmModeFreeEncoder = nullptr;
PFNDRMMODEGETPLANE FP_drmModeGetPlane = nullptr;
PFNDRMMODEFREEPLANE FP_drmModeFreePlane = nullptr;
PFNDRMMODESETCRTC FP_drmModeSetCrtc = nullptr;
PFNDRMMODEGETCRTC FP_drmModeGetCrtc = nullptr;
PFNDRMMODESETPLANE FP_drmModeSetPlane = nullptr;
PFNDRMMODEFREECRTC FP_drmModeFreeCrtc = nullptr;
PFNDRMSETCLIENTCAP FP_drmSetClientCap = nullptr;
PFNDRMIOCTL FP_drmIoctl = nullptr;
PFNDRMMODEADDFB2 FP_drmModeAddFB2 = nullptr;
PFNDRMMODECREATEPROPERTYBLOB FP_drmModeCreatePropertyBlob = nullptr;
PFNDRMMODEGETPROPERTY FP_drmModeGetProperty = nullptr;
PFNDRMMODEFREEPROPERTY FP_drmModeFreeProperty = nullptr;
PFNDRMMODEFREEOBJECTPROPERTIES FP_drmModeFreeObjectProperties = nullptr;
PFNDRMMODEOBJECTGETPROPERTIES FP_drmModeObjectGetProperties = nullptr;
PFNDRMMODEATOMICFREE FP_drmModeAtomicFree = nullptr;
PFNDRMMODEATOMICADDPROPERTY FP_drmModeAtomicAddProperty = nullptr;
PFNDRMMODEATOMICALLOC FP_drmModeAtomicAlloc = nullptr;
PFNDRMMODEATOMICCOMMIT FP_drmModeAtomicCommit = nullptr;
PFNDRMGETVERSION FP_drmGetVersion = nullptr;
PFNDRMFREEVERSION FP_drmFreeVersion = nullptr;

struct DRMPlaneInfo
{
    EGLint layerIndex = -1;
    unsigned int crtcMask = 0;
    int planeType = DRM_PLANE_TYPE_OVERLAY;
};

struct DRMFramebuffer
{
    uint32_t handle = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t pitch = 0;
    uint8_t* pData = nullptr;
    size_t size = 0;
};

#endif // USE_DRM_DEVICE

#if USE_OPENWFD_DEVICE

using PFNWFDBINDPIPELINETOPORT = void (*)(WFDDevice device, WFDPort port, WFDPipeline pipeline);
using PFNWFDBINDSOURCETOPIPELINE = void (*)(WFDDevice device, WFDPipeline pipeline, WFDSource source, WFDTransition transition, const WFDRect* region);
using PFNWFDCREATEDEVICE = WFDDevice (*)(WFDint deviceId, const WFDint* attribList);
using PFNWFDCREATEPIPELINE = WFDPipeline (*)(WFDDevice device, WFDint pipelineId, const WFDint* attribList);
using PFNWFDCREATEPORT = WFDPort (*)(WFDDevice device, WFDint portId, const WFDint* attribList);
using PFNWFDDESTROYDEVICE = WFDErrorCode (*)(WFDDevice device);
using PFNWFDDESTROYPIPELINE = void (*)(WFDDevice device, WFDPipeline pipeline);
using PFNWFDDESTROYPORT = void (*)(WFDDevice device, WFDPort port);
using PFNWFDDEVICECOMMIT = void (*)(WFDDevice device, WFDCommitType type, WFDHandle handle);
using PFNWFDENUMERATEDEVICES = WFDint (*)(WFDint* const deviceIds, const WFDint deviceIdsCount, const WFDint* const filterList);
using PFNWFDENUMERATEPIPELINES = WFDint (*)(WFDDevice device, WFDint* pipelineIds, WFDint pipelineIdsCount, const WFDint* filterList);
using PFNWFDENUMERATEPORTS = WFDint (*)(WFDDevice device, WFDint* portIds, WFDint portIdsCount, const WFDint* filterList);
using PFNWFDGETCURRENTPORTMODE = WFDPortMode (*)(WFDDevice device, WFDPort port);
using PFNWFDGETERROR = WFDErrorCode (*)(WFDDevice device);
using PFNWFDGETPORTMODEATTRIBI = WFDint (*)(WFDDevice device, WFDPort port, WFDPortMode mode, WFDPortModeAttrib attrib);
using PFNWFDGETPORTMODES = WFDint (*)(WFDDevice device, WFDPort port, WFDPortMode* modes, WFDint modesCount);
using PFNWFDSETPIPELINEATTRIBF = void (*)(WFDDevice device, WFDPipeline pipeline, WFDPipelineConfigAttrib attrib, WFDfloat value);
using PFNWFDSETPIPELINEATTRIBIV = void (*)(WFDDevice device, WFDPipeline pipeline, WFDPipelineConfigAttrib attrib, WFDint count, const WFDint* value);
using PFNWFDSETPORTMODE = void (*)(WFDDevice device, WFDPort port, WFDPortMode mode);

PFNWFDBINDPIPELINETOPORT FP_wfdBindPipelineToPort = nullptr;
PFNWFDBINDSOURCETOPIPELINE FP_wfdBindSourceToPipeline = nullptr;
PFNWFDCREATEDEVICE FP_wfdCreateDevice = nullptr;
PFNWFDCREATEPIPELINE FP_wfdCreatePipeline = nullptr;
PFNWFDCREATEPORT FP_wfdCreatePort = nullptr;
PFNWFDDESTROYDEVICE FP_wfdDestroyDevice = nullptr;
PFNWFDDESTROYPIPELINE FP_wfdDestroyPipeline = nullptr;
PFNWFDDESTROYPORT FP_wfdDestroyPort = nullptr;
PFNWFDDEVICECOMMIT FP_wfdDeviceCommit = nullptr;
PFNWFDENUMERATEDEVICES FP_wfdEnumerateDevices = nullptr;
PFNWFDENUMERATEPIPELINES FP_wfdEnumeratePipelines = nullptr;
PFNWFDENUMERATEPORTS FP_wfdEnumeratePorts = nullptr;
PFNWFDGETCURRENTPORTMODE FP_wfdGetCurrentPortMode = nullptr;
PFNWFDGETERROR FP_wfdGetError = nullptr;
PFNWFDGETPORTMODEATTRIBI FP_wfdGetPortModeAttribi = nullptr;
PFNWFDGETPORTMODES FP_wfdGetPortModes = nullptr;
PFNWFDSETPIPELINEATTRIBF FP_wfdSetPipelineAttribf = nullptr;
PFNWFDSETPIPELINEATTRIBIV FP_wfdSetPipelineAttribiv = nullptr;
PFNWFDSETPORTMODE FP_wfdSetPortMode = nullptr;

struct OpenWfdPortInfo
{
    WFDint id = -1;
    WFDint handle = -1;
    std::vector<WFDPortMode> allModes;
};

struct OpenWfdPipelineInfo
{
    WFDint id = -1;
    WFDint handle = -1;
    WFDint layerIdx = -1;
};

#endif // USE_OPENWFD_DEVICE

typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT* devices, EGLint* num_devices);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, const EGLAttrib* attrib_list, EGLOutputLayerEXT* layers, EGLint max_layers, EGLint* num_layers);
typedef const char* (EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib* value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value);

PFNEGLSTREAMCONSUMEROUTPUTEXTPROC FP_eglStreamConsumerOutputEXT = nullptr;
PFNEGLQUERYDEVICESEXTPROC FP_eglQueryDevicesEXT = nullptr;
PFNEGLGETOUTPUTLAYERSEXTPROC FP_eglGetOutputLayersEXT = nullptr;
PFNEGLQUERYDEVICESTRINGEXTPROC FP_eglQueryDeviceStringEXT = nullptr;
PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC FP_eglQueryOutputLayerAttribEXT = nullptr;
PFNEGLOUTPUTLAYERATTRIBEXTPROC FP_eglOutputLayerAttribEXT = nullptr;

} // unnamed

class EglDeviceSystem : public WindowSystem
{

public:
    virtual void CreateDisplay() override
    {
        // Initialize function pointers
        DoInitEglDeviceFunctionPointers();
#if USE_DRM_DEVICE
        DoInitDrmDeviceFunctionPointers();
#elif USE_OPENWFD_DEVICE
        DoInitOpenWfdDeviceFunctionPointers();
#endif

        // Create device
        DoCreateEglDevice();
#if USE_DRM_DEVICE
        DoCreateDrmDevice();
#elif USE_OPENWFD_DEVICE
        DoCreateOpenWfdDevice();
#endif

        // Get platform/native display
        DoGetPlatformDisplay();
    }

    virtual void DestroyDisplay() override
    {
#if USE_DRM_DEVICE

        if (m_pDrmRes)
        {
            FP_drmModeFreeResources(m_pDrmRes);
        }

        if (m_pDrmPlaneRes)
        {
            FP_drmModeFreePlaneResources(m_pDrmPlaneRes);
        }

        if (m_libDrmHandle)
        {
            dlclose(m_libDrmHandle);
        }

#elif USE_OPENWFD_DEVICE

        if (m_wfdDeviceHandle && (m_currWfdPipelineIdx >= 0))
        {
            const OpenWfdPipelineInfo& pipelineInfo = m_allWfdPipelines[m_currWfdPipelineIdx];
            FP_wfdBindSourceToPipeline(m_wfdDeviceHandle, pipelineInfo.handle, WFDSource(0), WFD_TRANSITION_AT_VSYNC, nullptr);
            FP_wfdDeviceCommit(m_wfdDeviceHandle, WFD_COMMIT_PIPELINE, pipelineInfo.handle);
        }
        for (const OpenWfdPipelineInfo& pipelineInfo : m_allWfdPipelines)
        {
            FP_wfdDestroyPipeline(m_wfdDeviceHandle, pipelineInfo.handle);
        }
        for (const OpenWfdPortInfo& portInfo : m_allWfdPorts)
        {
            FP_wfdDestroyPort(m_wfdDeviceHandle, portInfo.handle);
        }
        FP_wfdDestroyDevice(m_wfdDeviceHandle);

        if (m_libWfdHandle)
        {
            dlclose(m_libWfdHandle);
        }

#endif
    }

    virtual void SetCreatingFullscreen(bool /*fullscreen*/) override
    {
    }

    virtual void GetScreenSize(int& /*width*/, int& /*height*/) override
    {
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
        if (width > 0)
        {
            m_width = width;
        }
        if (height > 0)
        {
            m_height = height;
        }

        // Populate device resources and set output mode
        DoPopulateEglDeviceResources();
#if USE_DRM_DEVICE
        DoPopulateDrmDeviceResources();
        DoSetDrmOutputMode();
#elif USE_OPENWFD_DEVICE
        DoPopulateOpenWfdDeviceResources();
        DoSetOpenWfdOutputMode();
#endif
        NV_MESSAGE("Created native window");
    }

    virtual void DestroyAllWindows() override
    {
        // Nothing to do.
    }

    virtual void DestroyWindow(void* winAddr) override
    {
        // Nothing to do.
    }

    virtual void* GetDisplayAddr() override
    {
        if ((m_currDevIndex != -1) && (m_currDevIndex < int(m_vecDevices.size())))
        {
            return reinterpret_cast<void*>(&m_vecDevices[m_currDevIndex]);
        }

        return reinterpret_cast<void*>(&m_null_display);
    }

    virtual void* GetWindowAddr() override
    {
        return reinterpret_cast<void*>(&m_null_window);
    }

#if defined(WINAPI_EGL)
#ifdef EGL_KHR_stream
    virtual void ConnectConsumerToStream(EGLStreamKHR stream) override
    {
        if (m_currLayerIndex == -1)
        {
            return;
        }

        // Connect the output layer to the stream
        EGLBoolean result = FP_eglStreamConsumerOutputEXT(m_display, stream, m_vecLayers[m_currLayerIndex]);
        NV_THROW_IF(!result, "Failed to connect the output layer to the stream.");

        // Set swap interval for the output layer
        result = FP_eglOutputLayerAttribEXT(m_display, m_vecLayers[m_currLayerIndex], EGL_SWAP_INTERVAL_EXT, 1);
        NV_THROW_IF(!result, "Failed to set swap interval for the output layer");
    }
#endif

    virtual void* GetEGLDisplayAddr() override
    {
        return reinterpret_cast<void*>(&m_display);
    }
#endif

    EglDeviceSystem()
    {
    }

private:

    void DoInitEglDeviceFunctionPointers()
    {
        // Macro to load egl ext function pointers
#define NV_LOAD_EGLEXT_PTR(name, type)                                   \
    FP_##name = reinterpret_cast<type>(eglGetProcAddress(#name)); \
    NV_THROW_IF(!FP_##name, "Failed to load symbol from libEGL.so.1.");

        // Get EGL ext functions
        NV_LOAD_EGLEXT_PTR(eglStreamConsumerOutputEXT, PFNEGLSTREAMCONSUMEROUTPUTEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglQueryDevicesEXT, PFNEGLQUERYDEVICESEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglGetOutputLayersEXT, PFNEGLGETOUTPUTLAYERSEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglQueryDeviceStringEXT, PFNEGLQUERYDEVICESTRINGEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglQueryOutputLayerAttribEXT, PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglOutputLayerAttribEXT, PFNEGLOUTPUTLAYERATTRIBEXTPROC);

#undef NV_LOAD_EGLEXT_PTR
    }

    void DoCreateEglDevice()
    {
        // Get the extension string.
        const char* pExtensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        NV_THROW_IF(!pExtensions, "Failed to query EGL extensions.");

        // Check extensions for EGL device.
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_device_base"), "EGL device platform extension is not there.");
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_platform_base"), "EGL device platform extension is not there.");
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_platform_device"), "EGL device platform extension is not there.");

        // Query the number of all supported devices in the system.
        EGLint num = 0;
        EGLBoolean result = FP_eglQueryDevicesEXT(0, nullptr, &num);
        NV_THROW_IF(!result || (num == 0), "Failed to query EGL devices.");

        // Load devices.
        m_vecDevices.resize(num);
        EGLint deviceCount = 0;
        result = FP_eglQueryDevicesEXT(num, m_vecDevices.data(), &deviceCount);
        NV_THROW_IF(!result || (deviceCount == 0), "Failed to load EGL device.");

        // Use device 0 as default
        m_currDevIndex = 0;
        NV_MESSAGE("Try using device %d", m_currDevIndex);
    }

    void DoGetPlatformDisplay()
    {
        // Display attributes
        std::vector<EGLAttrib> vecDisplayAttribs;
#if USE_DRM_DEVICE
        vecDisplayAttribs.push_back(EGL_DRM_MASTER_FD_EXT);
        vecDisplayAttribs.push_back(m_drmDescriptor);
#elif USE_OPENWFD_DEVICE
        vecDisplayAttribs.push_back(EGL_OPENWF_DEVICE_EXT);
        vecDisplayAttribs.push_back(m_wfdDeviceHandle);
#endif
        vecDisplayAttribs.push_back(EGL_NONE);

        m_display = eglGetPlatformDisplay(EGL_PLATFORM_DEVICE_EXT, static_cast<NativeDisplayType>(m_vecDevices[m_currDevIndex]), vecDisplayAttribs.data());
    }

    void DoPopulateEglDeviceResources()
    {
        // Get extension string
        const char* pExtensions = eglQueryString(m_display, EGL_EXTENSIONS);
        NV_THROW_IF(!pExtensions, "Failed to query EGL extensions.");

        // Check extensions for EGL stream
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_output_base"), "EGL stream extension is not there..");
        NV_THROW_IF(!strstr(pExtensions, "EGL_KHR_stream"), "EGL stream extension is not there..");
        NV_THROW_IF(!strstr(pExtensions, "EGL_KHR_stream_producer_eglsurface"), "EGL stream extension is not there..");
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_stream_consumer_egloutput"), "EGL stream extension is not there..");

        // Query the number of all supported layers in the system.
        EGLint num = 0;
        EGLBoolean result = FP_eglGetOutputLayersEXT(m_display, nullptr, nullptr, 0, &num);
        NV_THROW_IF(!result || (num == 0), "Failed to query EGL layers.");

        // Obtain layers.
        m_vecLayers.resize(num);
        EGLint layerCount = 0;
        result = FP_eglGetOutputLayersEXT(m_display, nullptr, m_vecLayers.data(), num, &layerCount);
        NV_THROW_IF(!result || (layerCount == 0), "Failed to obtain EGL layer.");
    }

#if USE_DRM_DEVICE

    void DoInitDrmDeviceFunctionPointers()
    {
        // Open DRM library
        void* m_libDrmHandle = dlopen("libdrm.so.2", RTLD_LAZY);
        NV_THROW_IF(!m_libDrmHandle, "Failed to open libdrm.so.2");

        // Macro to load function pointers
#define NV_LOAD_DRM_PTR(name, type)                                   \
    FP_##name = reinterpret_cast<type>(dlsym(m_libDrmHandle, #name)); \
    NV_THROW_IF(!FP_##name, "Failed to load symbol from libdrm.so.2.");

        // Get DRM functions
        NV_LOAD_DRM_PTR(drmOpen, PFNDRMOPEN);
        NV_LOAD_DRM_PTR(drmModeGetResources, PFNDRMMODEGETRESOURCES);
        NV_LOAD_DRM_PTR(drmModeFreeResources, PFNDRMMODEFREERESOURCES);
        NV_LOAD_DRM_PTR(drmModeGetPlaneResources, PFNDRMMODEGETPLANERESOURCES);
        NV_LOAD_DRM_PTR(drmModeFreePlaneResources, PFNDRMMODEFREEPLANERESOURCES);
        NV_LOAD_DRM_PTR(drmModeGetConnector, PFNDRMMODEGETCONNECTOR);
        NV_LOAD_DRM_PTR(drmModeFreeConnector, PFNDRMMODEFREECONNECTOR);
        NV_LOAD_DRM_PTR(drmModeGetEncoder, PFNDRMMODEGETENCODER);
        NV_LOAD_DRM_PTR(drmModeFreeEncoder, PFNDRMMODEFREEENCODER);
        NV_LOAD_DRM_PTR(drmModeGetPlane, PFNDRMMODEGETPLANE);
        NV_LOAD_DRM_PTR(drmModeFreePlane, PFNDRMMODEFREEPLANE);
        NV_LOAD_DRM_PTR(drmModeSetCrtc, PFNDRMMODESETCRTC);
        NV_LOAD_DRM_PTR(drmModeGetCrtc, PFNDRMMODEGETCRTC);
        NV_LOAD_DRM_PTR(drmModeSetPlane, PFNDRMMODESETPLANE);
        NV_LOAD_DRM_PTR(drmModeFreeCrtc, PFNDRMMODEFREECRTC);
        NV_LOAD_DRM_PTR(drmSetClientCap, PFNDRMSETCLIENTCAP);
        NV_LOAD_DRM_PTR(drmIoctl, PFNDRMIOCTL);
        NV_LOAD_DRM_PTR(drmModeAddFB2, PFNDRMMODEADDFB2);
        NV_LOAD_DRM_PTR(drmModeCreatePropertyBlob, PFNDRMMODECREATEPROPERTYBLOB);
        NV_LOAD_DRM_PTR(drmModeGetProperty, PFNDRMMODEGETPROPERTY);
        NV_LOAD_DRM_PTR(drmModeFreeProperty, PFNDRMMODEFREEPROPERTY);
        NV_LOAD_DRM_PTR(drmModeObjectGetProperties, PFNDRMMODEOBJECTGETPROPERTIES);
        NV_LOAD_DRM_PTR(drmModeFreeObjectProperties, PFNDRMMODEFREEOBJECTPROPERTIES);
        NV_LOAD_DRM_PTR(drmModeAtomicFree, PFNDRMMODEATOMICFREE);
        NV_LOAD_DRM_PTR(drmModeAtomicAddProperty, PFNDRMMODEATOMICADDPROPERTY);
        NV_LOAD_DRM_PTR(drmModeAtomicAlloc, PFNDRMMODEATOMICALLOC);
        NV_LOAD_DRM_PTR(drmModeAtomicCommit, PFNDRMMODEATOMICCOMMIT);
        NV_LOAD_DRM_PTR(drmGetVersion, PFNDRMGETVERSION);
        NV_LOAD_DRM_PTR(drmFreeVersion, PFNDRMFREEVERSION);

#undef NV_LOAD_DRM_PTR
    }

    // Create DRM desktop
    void DoCreateDrmDevice()
    {
        // Open DRM file and query resources
        const char* devStr = FP_eglQueryDeviceStringEXT(m_vecDevices[m_currDevIndex], EGL_DRM_DEVICE_FILE_EXT);
        NV_THROW_IF(!devStr, "Failed to query EGL_DRM_DEVICE_FILE_EXT.");

        if (strcmp(devStr, "drm-nvdc") == 0)
        {
            m_drmDescriptor = FP_drmOpen(devStr, nullptr);
            m_isDrmNvdc = true;
        }
        else
        {
            m_drmDescriptor = open(devStr, O_RDWR | O_CLOEXEC);
        }
        NV_THROW_IF(m_drmDescriptor == -1, "Failed to open DRM");
        NV_MESSAGE("Opened device: %s", devStr);

        // Set isDrmNvdc based on drm version string
        drmVersionPtr version = FP_drmGetVersion(m_drmDescriptor);
        NV_MESSAGE("DRM version: %s", version->name);
        if (!strcmp(version->name, "drm-nvdc") ||
            !strcmp(version->name, "tegra-udrm") ||
            !strcmp(version->name, "tegra")) {
            m_isDrmNvdc = true;
        }
        FP_drmFreeVersion(version);

        int result = FP_drmSetClientCap(m_drmDescriptor, DRM_CLIENT_CAP_ATOMIC, 1);
        NV_THROW_IF(result != 0, "Failed to set client capability DRM_CLIENT_CAP_ATOMIC");

        result = FP_drmSetClientCap(m_drmDescriptor, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
        NV_THROW_IF(result != 0, "Failed to set client capability DRM_CLIENT_CAP_UNIVERSAL_PLANES");
    }

    // Populate DRM resources
    void DoPopulateDrmDeviceResources()
    {
        m_pDrmRes = FP_drmModeGetResources(m_drmDescriptor);
        NV_THROW_IF(!m_pDrmRes, "Failed to get DRM resources.");

        m_pDrmPlaneRes = FP_drmModeGetPlaneResources(m_drmDescriptor);
        NV_THROW_IF(!m_pDrmPlaneRes, "Failed to get DRM plane resources.");

        // Find connector index and CRTC index
        for (int connIndex = 0; connIndex < m_pDrmRes->count_connectors; ++connIndex)
        {
            drmModeConnector* pConnector = FP_drmModeGetConnector(m_drmDescriptor, m_pDrmRes->connectors[connIndex]);
            if (!pConnector || (pConnector->connection != DRM_MODE_CONNECTED) || (pConnector->count_modes <= 0))
            {
                if (pConnector)
                {
                    FP_drmModeFreeConnector(pConnector);
                }
                // Try the next connector.
                continue;
            }

            // Record the connector we try to use.
            m_currConnIndex = connIndex;
            NV_MESSAGE("Use connector %d", m_currConnIndex);

            // Find a usable CRTC associated with the selected connector
            drmModeEncoder* pEncoder = FP_drmModeGetEncoder(m_drmDescriptor, pConnector->encoder_id);
            if (pEncoder)
            {
                for (int crtcIndex = 0; crtcIndex < m_pDrmRes->count_crtcs; ++crtcIndex)
                {
                    if (m_pDrmRes->crtcs[crtcIndex] == pEncoder->crtc_id)
                    {
                        m_currCrtcIndex = crtcIndex;
                        NV_MESSAGE("Use CRTC %d", m_currCrtcIndex);
                    }
                }

                FP_drmModeFreeEncoder(pEncoder);
            }
            else if (pConnector->count_encoders > 0)
            {
                // If the connector doesn't have an encoder attached, use the first one
                pEncoder = FP_drmModeGetEncoder(m_drmDescriptor, pConnector->encoders[0]);
                if (pEncoder)
                {
                    m_currCrtcIndex = pEncoder->crtc_id;
                    NV_MESSAGE("Use CRTC %d", m_currCrtcIndex);
                    FP_drmModeFreeEncoder(pEncoder);
                }
                else
                {
                    NV_THROW_IF(true, "Failed to get an encoder");
                }
            }
            else
            {
                NV_THROW_IF(true, "Failed to get an encoder");
            }

            FP_drmModeFreeConnector(pConnector);

            break;
        }

        // Parse plane info
        m_planeInfos.resize(m_pDrmPlaneRes->count_planes);
        for (int i = 0; i < (int)m_pDrmPlaneRes->count_planes; ++i)
        {
            drmModePlane* pPlane = FP_drmModeGetPlane(m_drmDescriptor, m_pDrmPlaneRes->planes[i]);
            NV_THROW_IF(!pPlane, "Failed to get plane");
            m_planeInfos[i].layerIndex = -1;
            m_planeInfos[i].crtcMask = pPlane->possible_crtcs;
            FP_drmModeFreePlane(pPlane);
            m_planeInfos[i].planeType = GetDrmPlaneType(m_drmDescriptor, m_pDrmPlaneRes->planes[i]);
        }

        // Map layers to planes
        int n = 0;
        int layerIndex = 0;        
        for (int i = 0; i < (int)m_pDrmPlaneRes->count_planes; ++i)
        {
            const EGLAttrib layerAttrib[3] = { EGL_DRM_PLANE_EXT, m_pDrmPlaneRes->planes[i], EGL_NONE };
            EGLOutputLayerEXT tempLayer;
            if (FP_eglGetOutputLayersEXT(m_display, layerAttrib, &tempLayer, 1, &n) && n > 0)
            {
                m_vecLayers[layerIndex] = tempLayer;
                m_planeInfos[i].layerIndex = layerIndex++;
            }
        }
        NV_THROW_IF(layerIndex == 0, "Can't find an output layer");

        m_currLayerIndex = m_planeInfos[m_renderingPlaneIndex].layerIndex;
        NV_THROW_IF(m_currLayerIndex == -1, "Failed to find available connector/CRTC/output layer.");

        NV_MESSAGE("Try using layer index %d", m_currLayerIndex);
    }

    // Set DRM output mode
    void DoSetDrmOutputMode()
    {
        if ((m_currConnIndex == -1) || (m_currCrtcIndex == -1))
        {
            return;
        }

        // Get the current state of the connector
        drmModeConnector* pConnector = FP_drmModeGetConnector(m_drmDescriptor, m_pDrmRes->connectors[m_currConnIndex]);
        NV_THROW_IF(!pConnector, "Failed to get DRM connector");

        // Returns the default layer to be drawn onto for the current CRTC
        m_renderingPlaneIndex = [&]() {
            for (uint32_t planeIndex = 0; planeIndex < m_pDrmPlaneRes->count_planes; ++planeIndex)
            {
                if (m_planeInfos[planeIndex].crtcMask & (1 << m_currCrtcIndex))
                {
                    return int(planeIndex);
                }
            }
            return -1;
        }();
        NV_THROW_IF(m_renderingPlaneIndex == -1, "Failed to find available rendering plane.");
        NV_MESSAGE("Render plane: %d", m_renderingPlaneIndex);

        // Returns the plane index of the primary plane for the current CRTC
        m_primaryPlaneIndex = [&]() {
            for (uint32_t planeIndex = 0; planeIndex < m_pDrmPlaneRes->count_planes; ++planeIndex)
            {
                if (m_planeInfos[planeIndex].planeType == DRM_PLANE_TYPE_PRIMARY
                    && (m_planeInfos[planeIndex].crtcMask & (1 << m_currCrtcIndex)))
                {
                    return int(planeIndex);
                }
            }
            return -1;
        }();
        NV_THROW_IF(m_primaryPlaneIndex == -1, "Failed to find primary plane.");
        NV_MESSAGE("Primary plane: %d", m_renderingPlaneIndex);

        // Set the output mode
        {
            drmModeModeInfoPtr newMode = nullptr;
            unsigned int modeX = 0;
            unsigned int modeY = 0;

            // Choose the preferred mode if it's set, or else choose the largest supported mode
            unsigned int modeSize = 0;
            for (int i = 0; i < pConnector->count_modes; ++i)
            {
                drmModeModeInfoPtr mode = pConnector->modes + i;
                if (mode->type & DRM_MODE_TYPE_PREFERRED) {
                    newMode = mode;
                    modeX = (unsigned int)mode->hdisplay;
                    modeY = (unsigned int)mode->vdisplay;
                    break;
                }

                const unsigned int size = (unsigned int)mode->hdisplay * (unsigned int)mode->vdisplay;
                if (size > modeSize) {
                    newMode = mode;
                    modeSize = size;
                    modeX = (unsigned int)mode->hdisplay;
                    modeY = (unsigned int)mode->vdisplay;
                }
            }
            NV_MESSAGE("Selected mode: %d x %d", modeX, modeY);
            NV_THROW_IF(!modeX || !modeY || !newMode, "Failed to find a valid mode");

            // Firstly, we will try to allocate large framebuffer and use drmModeSetCrtc to set output mode
            // If this fail, we still want to allocate 1x1 framebuffer and perform a modeset via atomic requests for resizing
            bool result = [&](){
                uint32_t initialFbId = 0;

                NV_MESSAGE("Trying to allocate large framebuffer and using drmModeSetCrtc to set output mode");

                if (!m_isDrmNvdc)
                {
                    DRMFramebuffer drmFb = {};
                    if (!CreateDRMFramebuffer(modeX, modeY, 32, drmFb))
                    {
                        NV_MESSAGE("Faield to to create drm framebuffer");
                        return false;
                    }
                    const uint32_t colorFormat = DRM_FORMAT_ARGB8888;
                    const uint32_t offset = 0;
                    if (FP_drmModeAddFB2(m_drmDescriptor, modeX, modeY, colorFormat, &drmFb.handle, &drmFb.pitch, &offset, &initialFbId, 0) < 0)
                    {
                        NV_MESSAGE("Failed to add framebuffer");
                        return false;
                    }
                }
                else
                {
                    initialFbId = -1;
                }

                if (FP_drmModeSetCrtc(m_drmDescriptor,
                    m_pDrmRes->crtcs[m_currCrtcIndex],
                    initialFbId,
                    0,
                    0,
                    &m_pDrmRes->connectors[m_currConnIndex],
                    1,
                    newMode))
                {
                    NV_MESSAGE("Trying to set CRTC failed");
                    return false;
                }

                drmModeCrtcPtr currCrtc = (drmModeCrtcPtr)FP_drmModeGetCrtc(m_drmDescriptor, m_pDrmRes->crtcs[m_currCrtcIndex]);
                if (currCrtc != nullptr)
                {
                    NV_MESSAGE("DRM Mode: %d x %d @ %d", currCrtc->mode.hdisplay, currCrtc->mode.vdisplay, currCrtc->mode.vrefresh);
                }
                else
                {
                    NV_MESSAGE("Failed to get current mode");
                }

                // Set the alpha and the plane configuration here if not sending atomic info to EGL
                if (m_renderingPlaneIndex != m_primaryPlaneIndex && !m_isDrmNvdc)
                {
                    NV_MESSAGE("Rendering plane doesn't match primary plane, need some more configrations...");
                }

                drmModeAtomicReqPtr pAtomic = FP_drmModeAtomicAlloc();
                NV_THROW_IF(pAtomic == nullptr, "Failed to allocate the property set");

                // Set the alpha property of the plane
                const unsigned int alpha = (m_isDrmNvdc ? 0xff : 0xffff);
                if (!AtomicSetAlpha(m_drmDescriptor, pAtomic, m_pDrmPlaneRes->planes[m_renderingPlaneIndex], alpha))
                {
                    // This is not a fatal error, fallback to commit an alpha property
                    NV_MESSAGE("Could not set the alpha property");
                    NV_THROW_IF(FP_drmModeAtomicCommit(m_drmDescriptor, pAtomic, 0, nullptr/* user_data */), "Failed to commit alpha property");
                }

                FP_drmModeAtomicFree(pAtomic);

                const uint32_t planeFbId = initialFbId;
                bool ret = FP_drmModeSetPlane(m_drmDescriptor,
                                     m_pDrmPlaneRes->planes[m_renderingPlaneIndex],
                                     m_pDrmRes->crtcs[m_currCrtcIndex], planeFbId, 0,
                                     0 /* offsetX */, 0 /* offsetY */,
                                     m_width, m_height,
                                     0, 0, m_width << 16, m_height << 16);
                NV_THROW_IF(ret, "drmModeSetPlane-fail");

                return true;
            }();

            if (!result) {
                result = [&](){
                    NV_MESSAGE("Trying to allocate 1x1 framebuffer and perform a modeset via atomic requests for resizing");

                    DRMFramebuffer drmFb = {};
                    if (!CreateDRMFramebuffer(1, 1, 32, drmFb))
                    {
                        NV_MESSAGE("Trying to create drm framebuffer failed");
                        return false;
                    }

                    uint32_t offset = 0;
                    uint32_t fbId = 0;
                    int res = FP_drmModeAddFB2(m_drmDescriptor, 1, 1, DRM_FORMAT_ARGB8888, &drmFb.handle, &drmFb.pitch, &offset, &fbId, 0);
                    if (res < 0)
                    {
                        NV_MESSAGE("Trying to add framebuffer failed");
                        return false;
                    }

                    drmModeAtomicReqPtr req = FP_drmModeAtomicAlloc();
                    if (!req)
                    {
                        NV_MESSAGE("Trying to allocate drm atomics request structure failed");
                        return false;
                    }

                    uint32_t connId = m_pDrmRes->connectors[m_currConnIndex];
                    uint32_t crtcId = m_pDrmRes->crtcs[m_currCrtcIndex];
                    uint32_t primaryPlaneId = m_pDrmPlaneRes->planes[m_primaryPlaneIndex];
                    uint32_t renderingPlaneId = m_pDrmPlaneRes->planes[m_renderingPlaneIndex];
                    uint32_t srcX = 0, srcY = 0, srcW = 1, srcH = 1;
                    uint32_t crtcX = 0, crtcY = 0, crtcW = 1, crtcH = 1;
                    if (!AtomicAddFrameBuffer(m_drmDescriptor, req, connId, crtcId, primaryPlaneId, fbId))
                    {
                        NV_MESSAGE("Trying to set the atomic frame buffer property failed");
                        return false;
                    }
                    if (!AtomicPlaneResize(m_drmDescriptor, req, primaryPlaneId,
                                              crtcId, crtcX, crtcY, crtcW, crtcH,
                                              srcX << 16, srcY << 16,
                                              srcW << 16, srcH << 16))
                    {
                        NV_MESSAGE("Trying to resize the atomic plane properties failed");
                        return false;
                    }

                    if (newMode)
                    {
                        uint32_t modeId = 0;
                        res = FP_drmModeCreatePropertyBlob(m_drmDescriptor, newMode, sizeof(*newMode), &modeId);
                        if (res != 0 || modeId == 0)
                        {
                            NV_MESSAGE("Trying to create mode property blob failed");
                            return false;
                        }
                        if (!AtomicAddMode(m_drmDescriptor, req, modeId, connId, crtcId))
                        {
                            NV_MESSAGE("Trying to set the atomic mode properties failed");
                            return false;
                        }
                    }

                    if (!AtomicPlaneResize(m_drmDescriptor, req, renderingPlaneId,
                                          crtcId, crtcX, crtcY, crtcW, crtcH,
                                          srcX << 16, srcY << 16, srcW << 16,
                                          srcH << 16))
                    {
                        NV_MESSAGE("Trying to resize the atomic plane properties failed");
                        return false;
                    }
                    res = FP_drmModeAtomicCommit(m_drmDescriptor, req, DRM_MODE_ATOMIC_ALLOW_MODESET, nullptr);
                    if (res != 0)
                    {
                        NV_MESSAGE("Trying to commit atomic modeset request failed");
                        return false;
                    }
                    return true;
                }();
                NV_THROW_IF(!result, "Failed to set DRM output mode");
            }
        }
    }

    bool AtomicSetAlpha(int fd, drmModeAtomicReqPtr req, uint32_t planeId, uint32_t alpha)
    {
        drmModeObjectPropertiesPtr planeProps = FP_drmModeObjectGetProperties(fd, planeId, DRM_MODE_OBJECT_PLANE);
        if (!planeProps)
        {
            NV_MESSAGE("Failed to get property DRM_MODE_OBJECT_PLANE");
            return false;
        }

        auto SetProp = [=](const char* propName, drmModeObjectPropertiesPtr properties, uint32_t setProp, uint32_t propValue) {
            uint32_t propId = GetPropertyId(fd, properties, propName);
            if (propId == 0)
            {
                NV_MESSAGE("Failed to get property ID: %s", propName);
                return false;
            }
            if (FP_drmModeAtomicAddProperty(req, setProp, propId, propValue) <= 0)
            {
                NV_MESSAGE("Failed to add property: %s, with value: %u", propName, propValue);
                return false;
            }
            return true;
        };

        if (!SetProp("alpha", planeProps, planeId, alpha))
        {
            FP_drmModeFreeObjectProperties(planeProps);
            return false;
        }

        FP_drmModeFreeObjectProperties(planeProps);
        return true;
    }

    bool CreateDRMFramebuffer(uint32_t width, uint32_t height, uint32_t bitDepth, DRMFramebuffer& fb)
    {
        // Set a dumb frame buffer to the primary plane (CRTC)
        drm_mode_create_dumb creq;
        drm_mode_map_dumb mreq;
        memset(&creq, 0, sizeof(creq));
        creq.width = width;
        creq.height = height;
        creq.bpp = bitDepth;
        uint8_t* pData = NULL;    

        // Create the dumb buffer
        int result = FP_drmIoctl(m_drmDescriptor, DRM_IOCTL_MODE_CREATE_DUMB, &creq);
        if (result < 0) {
            NV_MESSAGE("Trying to create dumb buffer failed");
            return false;
        }

        // Map the frame buffer
        memset(&mreq, 0, sizeof(mreq));
        mreq.handle = creq.handle;
        result = FP_drmIoctl(m_drmDescriptor, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
        if (result) {
            NV_MESSAGE("Trying to map dumb buffer failed");
            return false;
        }

        // Map and clear the FB
        pData = (uint8_t*)mmap(0, creq.size, PROT_READ | PROT_WRITE, MAP_SHARED, m_drmDescriptor, mreq.offset);
        if (pData == MAP_FAILED) {
            NV_MESSAGE("Trying to mmap dumb buffer failed");
            return false;
        }

        // Clear the frame buffer
        memset(pData, 0x00, creq.size);
        fb.handle = creq.handle;
        fb.width = width;
        fb.height = height;
        fb.pitch = creq.pitch;
        fb.pData = pData;
        fb.size = creq.size;

        return true;
    };

    uint32_t GetPropertyId(int fd, drmModeObjectPropertiesPtr properties, const char *propName)
    {
        uint32_t propertyId = 0;
        for (uint32_t i = 0; i < properties->count_props; i++) {
            drmModePropertyPtr p = FP_drmModeGetProperty(fd, properties->props[i]);

            if (!p) {
                NV_MESSAGE("Trying to query property failed");
                return 0;
            }
            if (strcmp(propName, p->name) == 0) {
                propertyId = p->prop_id;
            }
            FP_drmModeFreeProperty(p);    

            if (propertyId) {
                break;
            }
        }
        return propertyId;
    }

    int GetDrmPlaneType(int drmFd, uint32_t objectID)
    {
        bool found = false;
        int planeType = DRM_PLANE_TYPE_OVERLAY;
        drmModeObjectPropertiesPtr pModeObjectProperties = FP_drmModeObjectGetProperties(drmFd, objectID, DRM_MODE_OBJECT_PLANE);
        for (uint32_t i = 0; i < pModeObjectProperties->count_props; i++) {
            drmModePropertyPtr pProperty = FP_drmModeGetProperty(drmFd, pModeObjectProperties->props[i]);    
            if (!pProperty) {
               continue;
            }

            if(strcmp("type", pProperty->name) == 0) {
                uint64_t value = pModeObjectProperties->prop_values[i];
                found = true;
                for (int j = 0; j < pProperty->count_enums; j++) {
                    if (value == (pProperty->enums[j]).value) {
                        if (strcmp( "Primary", (pProperty->enums[j]).name) == 0) {
                            planeType = DRM_PLANE_TYPE_PRIMARY;
                        } else if (strcmp( "Overlay", (pProperty->enums[j]).name) == 0) {
                            planeType = DRM_PLANE_TYPE_OVERLAY;
                        } else {
                            planeType = DRM_PLANE_TYPE_CURSOR;
                        }
                    }
                }
            }
            FP_drmModeFreeProperty(pProperty);
            if (found)
                break;
        }
        if (!found) {
           NV_MESSAGE("Trying to find value for property type failed");
        }
        return planeType;
    }

#define SET_PROP(propName, properties, setProp, propValue)                   \
    propId = GetPropertyId(fd, properties, propName);                        \
    if (propId == 0) {                                                       \
        return false;                                                        \
    }                                                                        \
    if (FP_drmModeAtomicAddProperty(req, setProp, propId, propValue) <= 0) { \
        return false;                                                        \
    }

    bool AtomicAddMode(int fd, drmModeAtomicReqPtr req, uint32_t modeId, uint32_t connId, uint32_t crtcId)
    {
        uint32_t propId;
        drmModeObjectPropertiesPtr crtcProps = NULL;
        crtcProps = FP_drmModeObjectGetProperties(fd, crtcId, DRM_MODE_OBJECT_CRTC);
        if (!crtcProps) {
            return false;
        }
        drmModeObjectPropertiesPtr connProps = NULL;
        connProps = FP_drmModeObjectGetProperties(fd, connId, DRM_MODE_OBJECT_CONNECTOR);
        if (!connProps) {
            return false;
        }  

        SET_PROP("CRTC_ID", connProps, connId, crtcId);
        SET_PROP("MODE_ID", crtcProps, crtcId, modeId);
        SET_PROP("ACTIVE", crtcProps, crtcId, 1);
        return true;
    }

    bool AtomicPlaneResize(int fd, drmModeAtomicReqPtr req,
                                     uint32_t planeId, uint32_t crtcId,
                                     uint32_t crtcX, uint32_t crtcY,
                                     uint32_t crtcW, uint32_t crtcH,
                                     uint32_t srcX, uint32_t srcY,
                                     uint32_t srcW, uint32_t srcH)
    {
        uint32_t propId;
        drmModeObjectPropertiesPtr planeProps;
        planeProps = FP_drmModeObjectGetProperties(fd, planeId, DRM_MODE_OBJECT_PLANE);
        if (!planeProps) {
            return false;
        }

        SET_PROP("CRTC_X", planeProps, planeId, crtcX);
        SET_PROP("CRTC_Y", planeProps, planeId, crtcY);
        SET_PROP("CRTC_W", planeProps, planeId, crtcW);
        SET_PROP("CRTC_H", planeProps, planeId, crtcH);
        SET_PROP("SRC_X", planeProps, planeId, srcX);
        SET_PROP("SRC_Y", planeProps, planeId, srcY);
        SET_PROP("SRC_W", planeProps, planeId, srcW);
        SET_PROP("SRC_H", planeProps, planeId, srcH);
        SET_PROP("CRTC_ID", planeProps, planeId, crtcId);
        return true;
    }

    bool AtomicAddFrameBuffer(int fd, drmModeAtomicReqPtr req, uint32_t connId, uint32_t crtcId, uint32_t planeId, uint32_t fbId)
    {
        uint32_t propId;
        drmModeObjectPropertiesPtr connProps = nullptr, planeProps = nullptr;
        connProps = FP_drmModeObjectGetProperties(fd, connId, DRM_MODE_OBJECT_CONNECTOR);
        if (!connProps) {
            return false;
        }
        planeProps = FP_drmModeObjectGetProperties(fd, planeId, DRM_MODE_OBJECT_PLANE);
        if (!planeProps) {
            return false;
        }

        SET_PROP("CRTC_ID",  connProps, connId, crtcId);
        SET_PROP("FB_ID",  planeProps, planeId, fbId);
        return true;
    }

#endif // USE_DRM_DEVICE

#if USE_OPENWFD_DEVICE

    // Initialize OpenWFD
    void DoInitOpenWfdDeviceFunctionPointers()
    {
        // Open OpenWFD library
        m_libWfdHandle = dlopen("libtegrawfd.so", RTLD_LAZY);
        NV_THROW_IF(!m_libWfdHandle, "Failed to open libtegrawfd.so");

        // Macro to load function pointers
#define NV_LOAD_OPENWFD_PTR(name, type)                                   \
    FP_##name = reinterpret_cast<type>(dlsym(m_libWfdHandle, #name));     \
    NV_THROW_IF(!FP_##name, "Failed to load symbol from libtegrawfd.so");

        NV_LOAD_OPENWFD_PTR(wfdBindPipelineToPort, PFNWFDBINDPIPELINETOPORT);
        NV_LOAD_OPENWFD_PTR(wfdBindSourceToPipeline, PFNWFDBINDSOURCETOPIPELINE);
        NV_LOAD_OPENWFD_PTR(wfdCreateDevice, PFNWFDCREATEDEVICE);
        NV_LOAD_OPENWFD_PTR(wfdCreatePipeline, PFNWFDCREATEPIPELINE);
        NV_LOAD_OPENWFD_PTR(wfdCreatePort, PFNWFDCREATEPORT);
        NV_LOAD_OPENWFD_PTR(wfdDestroyDevice, PFNWFDDESTROYDEVICE);
        NV_LOAD_OPENWFD_PTR(wfdDestroyPipeline, PFNWFDDESTROYPIPELINE);
        NV_LOAD_OPENWFD_PTR(wfdDestroyPort, PFNWFDDESTROYPORT);
        NV_LOAD_OPENWFD_PTR(wfdDeviceCommit, PFNWFDDEVICECOMMIT);
        NV_LOAD_OPENWFD_PTR(wfdEnumerateDevices, PFNWFDENUMERATEDEVICES);
        NV_LOAD_OPENWFD_PTR(wfdEnumeratePipelines, PFNWFDENUMERATEPIPELINES);
        NV_LOAD_OPENWFD_PTR(wfdEnumeratePorts, PFNWFDENUMERATEPORTS);
        NV_LOAD_OPENWFD_PTR(wfdGetCurrentPortMode, PFNWFDGETCURRENTPORTMODE);
        NV_LOAD_OPENWFD_PTR(wfdGetError, PFNWFDGETERROR);
        NV_LOAD_OPENWFD_PTR(wfdGetPortModeAttribi, PFNWFDGETPORTMODEATTRIBI);
        NV_LOAD_OPENWFD_PTR(wfdGetPortModes, PFNWFDGETPORTMODES);
        NV_LOAD_OPENWFD_PTR(wfdSetPipelineAttribf, PFNWFDSETPIPELINEATTRIBF);
        NV_LOAD_OPENWFD_PTR(wfdSetPipelineAttribiv, PFNWFDSETPIPELINEATTRIBIV);
        NV_LOAD_OPENWFD_PTR(wfdSetPortMode, PFNWFDSETPORTMODE);

#undef NV_LOAD_OPENWFD_PTR
    }

    // Create OpenWFD desktop
    void DoCreateOpenWfdDevice()
    {
        // Create device
        m_wfdDeviceHandle = FP_wfdCreateDevice(WFD_DEFAULT_DEVICE_ID, nullptr);
        NV_THROW_IF(!m_wfdDeviceHandle, "Failed to create OpenWFD device");
    }

    // Populate OpenWFD resources
    void DoPopulateOpenWfdDeviceResources()
    {
        // Enumerate ports
        const WFDint numPorts = FP_wfdEnumeratePorts(m_wfdDeviceHandle, nullptr, 0, nullptr);
        NV_THROW_IF(!numPorts, "Failed to enumerate OpenWFD ports");

        // Query port IDs
        std::vector<WFDint> allPortIds(numPorts);
        const WFDint queriedNumPorts = FP_wfdEnumeratePorts(m_wfdDeviceHandle, allPortIds.data(), numPorts, nullptr);
        NV_THROW_IF(queriedNumPorts != numPorts, "Failed to query OpenWFD port IDs");

        // Query port info
        m_allWfdPorts.resize(numPorts);
        for (WFDint portIdx = 0; portIdx < numPorts; ++portIdx)
        {
            OpenWfdPortInfo& portInfo = m_allWfdPorts[portIdx];

            portInfo.id = allPortIds[portIdx];
            portInfo.handle = FP_wfdCreatePort(m_wfdDeviceHandle, portInfo.id, nullptr);
            NV_THROW_IF(!portInfo.handle, "Failed to create OpenWFD port");

            const WFDint numPortModes = FP_wfdGetPortModes(m_wfdDeviceHandle, portInfo.handle, nullptr, 0);
            NV_THROW_IF(!numPortModes, "Failed to query OpenWFD port modes");

            portInfo.allModes.resize(numPortModes);
            const WFDint queriedNumPortModes = FP_wfdGetPortModes(m_wfdDeviceHandle, portInfo.handle, portInfo.allModes.data(), numPortModes);
            NV_THROW_IF(queriedNumPortModes != numPortModes, "Failed to query OpenWFD port modes");
        }

        // Enumerate pipelines
        const WFDint numPipelines = FP_wfdEnumeratePipelines(m_wfdDeviceHandle, nullptr, 0, nullptr);
        NV_THROW_IF(!numPipelines, "Failed to enumerate OpenWFD pipelines");

        // Query pipeline IDs
        std::vector<WFDint> allPipelineIds(numPipelines);
        const WFDint queriedNumPipelines = FP_wfdEnumeratePipelines(m_wfdDeviceHandle, allPipelineIds.data(), numPipelines, nullptr);
        NV_THROW_IF(queriedNumPipelines != numPipelines, "Failed to query OpenWFD pipeline IDs");

        // Query pipeline info
        m_allWfdPipelines.resize(numPipelines);
        for (WFDint pipelineIdx = 0; pipelineIdx < numPipelines; ++pipelineIdx)
        {
            OpenWfdPipelineInfo& pipelineInfo = m_allWfdPipelines[pipelineIdx];

            pipelineInfo.id = allPipelineIds[pipelineIdx];
            pipelineInfo.handle = FP_wfdCreatePipeline(m_wfdDeviceHandle, pipelineInfo.id, nullptr);
            NV_THROW_IF(!pipelineInfo.handle, "Failed to create OpenWFD pipeline");

            // Associated layer index (if any)
            EGLint numLayers = 0;
            EGLOutputLayerEXT associatedLayer = nullptr;
            const EGLAttrib layerAttrib[3] = { EGL_OPENWF_PIPELINE_ID_EXT, pipelineInfo.id , EGL_NONE };
            const EGLBoolean result = FP_eglGetOutputLayersEXT(m_display, layerAttrib, &associatedLayer, 1, &numLayers);
            if (!result || !numLayers)
            {
                NV_MESSAGE("WRN: Failed to get output layer for pipeline %d", pipelineInfo.id);
                continue;
            }
            for (int layerIdx = 0; layerIdx < int(m_vecLayers.size()); ++layerIdx)
            {
                if (m_vecLayers[layerIdx] == associatedLayer)
                {
                    pipelineInfo.layerIdx = layerIdx;
                    break;
                }
            }
            if (pipelineInfo.layerIdx == -1)
            {
                NV_MESSAGE("WRN: Can not find layer for pipeline %d", pipelineInfo.id);
            }
        }
    }

    // Set OpenWFD output mode
    void DoSetOpenWfdOutputMode()
    {
        // Simply use the first port
        m_currWfdPortIdx = 0;
        NV_MESSAGE("Try using port %d", m_currWfdPortIdx);

        // Current port info
        const OpenWfdPortInfo& portInfo = m_allWfdPorts[m_currWfdPortIdx];

        // Choose the largest supported mode
        int currModeIdx = -1;
        uint32_t maxModeSize = 0;
        for (int modeIdx = 0; modeIdx < int(portInfo.allModes.size()); ++modeIdx)
        {
            const WFDint modeWidth = FP_wfdGetPortModeAttribi(m_wfdDeviceHandle, portInfo.handle, portInfo.allModes[modeIdx], WFD_PORT_MODE_WIDTH);
            const WFDint modeHeight = FP_wfdGetPortModeAttribi(m_wfdDeviceHandle, portInfo.handle, portInfo.allModes[modeIdx], WFD_PORT_MODE_HEIGHT);
            const WFDint refreshRate = FP_wfdGetPortModeAttribi(m_wfdDeviceHandle, portInfo.handle, portInfo.allModes[modeIdx], WFD_PORT_MODE_REFRESH_RATE);
            NV_MESSAGE("Found port mode: %d x %d, refresh rate: %d", modeWidth, modeHeight, refreshRate);

            const uint32_t modeSize = (modeWidth * modeHeight);
            if (modeSize > maxModeSize)
            {
                currModeIdx = modeIdx;
                maxModeSize = modeSize;
            }
        }
        NV_THROW_IF(currModeIdx == -1, "Failed to find supported port mode");

        FP_wfdSetPortMode(m_wfdDeviceHandle, portInfo.handle, portInfo.allModes[currModeIdx]);
        WFDErrorCode errCode = FP_wfdGetError(m_wfdDeviceHandle);
        NV_THROW_IF(errCode != WFD_ERROR_NONE, "Failed to set OpenWFD port mode");

        // Simply use the first pipeline that has been associated with a layer
        for (int pipelineIdx = 0; pipelineIdx < int(m_allWfdPipelines.size()); ++pipelineIdx)
        {
            const OpenWfdPipelineInfo& pipelineInfo = m_allWfdPipelines[pipelineIdx];
            if (pipelineInfo.layerIdx != -1)
            {
                m_currWfdPipelineIdx = pipelineIdx;
                m_currLayerIndex = pipelineInfo.layerIdx;
                break;
            }
        }
        NV_THROW_IF(m_currWfdPipelineIdx == -1, "OpenWFD pipeline is not available");
        NV_MESSAGE("Try using pipeline %d, layer idx %d", m_currWfdPipelineIdx, m_currLayerIndex);

        // Current pipeline info
        const OpenWfdPipelineInfo& pipelineInfo = m_allWfdPipelines[m_currWfdPipelineIdx];

        // Set pipeline alpha
        FP_wfdSetPipelineAttribf(m_wfdDeviceHandle, pipelineInfo.handle, WFD_PIPELINE_GLOBAL_ALPHA, 1.0);
        errCode = FP_wfdGetError(m_wfdDeviceHandle);
        NV_THROW_IF(errCode != WFD_ERROR_NONE, "Failed to set OpenWFD pipeline alpha");

        // Set pipeline source rectangle
        const WFDint srcRect[4] = { 0, 0, m_width, m_height };
        FP_wfdSetPipelineAttribiv(m_wfdDeviceHandle, pipelineInfo.handle, WFD_PIPELINE_SOURCE_RECTANGLE, 4, srcRect);
        errCode = FP_wfdGetError(m_wfdDeviceHandle);
        NV_THROW_IF(errCode != WFD_ERROR_NONE, "Failed to set OpenWFD pipeline source rectangle");

        // Set pipeline destination rectangle
        const WFDint dstRect[4] = { 0, 0, m_width, m_height };
        FP_wfdSetPipelineAttribiv(m_wfdDeviceHandle, pipelineInfo.handle, WFD_PIPELINE_DESTINATION_RECTANGLE, 4, dstRect);
        errCode = FP_wfdGetError(m_wfdDeviceHandle);
        NV_THROW_IF(errCode != WFD_ERROR_NONE, "Failed to set OpenWFD pipeline destination rectangle");

        // Bind the chosen port and pipeline
        FP_wfdBindPipelineToPort(m_wfdDeviceHandle, portInfo.handle, pipelineInfo.handle);
        errCode = FP_wfdGetError(m_wfdDeviceHandle);
        NV_THROW_IF(errCode != WFD_ERROR_NONE, "Failed to bind OpenWFD port and pipeline");

        // Commit changes
        FP_wfdDeviceCommit(m_wfdDeviceHandle, WFD_COMMIT_ENTIRE_DEVICE, WFD_INVALID_HANDLE);
        errCode = FP_wfdGetError(m_wfdDeviceHandle);
        NV_THROW_IF(errCode != WFD_ERROR_NONE, "Failed to commit OpenWFD changes");
    }

#endif // USE_OPENWFD_DEVICE

private:

    // EGL variables
    EGLDisplay m_display = 0;
    std::vector<EGLDeviceEXT> m_vecDevices;
    std::vector<EGLOutputLayerEXT> m_vecLayers;
    NativeDisplayType m_null_display = 0;
    NativeWindowType m_null_window = 0;

    // DRM variables
#if USE_DRM_DEVICE
    bool m_isDrmNvdc = false;
    void* m_libDrmHandle = nullptr;
    int m_drmDescriptor = 0;
    drmModeRes* m_pDrmRes = nullptr;
    drmModePlaneRes* m_pDrmPlaneRes = nullptr;

    std::vector<DRMPlaneInfo> m_planeInfos;
    int m_currCrtcIndex = -1;
    int m_currConnIndex = -1;
    int m_renderingPlaneIndex = -1;
    int m_primaryPlaneIndex = -1;
#endif // USE_DRM_DEVICE

    // OpenWFD variables
#if USE_OPENWFD_DEVICE
    void* m_libWfdHandle = nullptr;
    WFDDevice m_wfdDeviceHandle = 0;
    std::vector<OpenWfdPortInfo> m_allWfdPorts;
    std::vector<OpenWfdPipelineInfo> m_allWfdPipelines;
    int m_currWfdPortIdx = -1;
    int m_currWfdPipelineIdx = -1;
#endif // USE_OPENWFD_DEVICE

    // Indices records
    int m_currDevIndex = -1;
    int m_currLayerIndex = -1;

    // Dimensions
    int m_width = 800;
    int m_height = 600;
};

WindowSystem& WindowSystemInstance()
{
    static EglDeviceSystem instance;
    return instance;
}
