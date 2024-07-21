//---------------------------------------------------------------------------
// File: WindowSystem_Wayland.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

#include "wayland-client.h"
#if defined(WINAPI_EGL)
#include "wayland-egl.h"
#endif
#include <linux/input.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <vector>

namespace // unnamed
{

struct RegistryInfo
{
    wl_compositor** ppWlCompositor;
    wl_shell** ppWlShell;
    wl_seat** ppWlSeat;
};
RegistryInfo registryInfo;

void seat_handle_capabilities(void* data, wl_seat* seat, uint32_t caps)
{
    // No operation.
}

const wl_seat_listener seat_listener = {
    seat_handle_capabilities,
};

void registry_handle_global(void* data, wl_registry* registry, uint32_t name, const char* interface, uint32_t version)
{
    RegistryInfo* pRegistryInfo = reinterpret_cast<RegistryInfo*>(data);

    if (strcmp(interface, "wl_compositor") == 0)
    {
        *pRegistryInfo->ppWlCompositor = reinterpret_cast<wl_compositor*>(wl_registry_bind(registry, name, &wl_compositor_interface, 1));
    }
    else if (strcmp(interface, "wl_shell") == 0)
    {
        *pRegistryInfo->ppWlShell = reinterpret_cast<wl_shell*>(wl_registry_bind(registry, name, &wl_shell_interface, 1));
    }
    else if (strcmp(interface, "wl_seat") == 0)
    {
        wl_seat* pWlSeat = reinterpret_cast<wl_seat*>(wl_registry_bind(registry, name, &wl_seat_interface, 1));
        *pRegistryInfo->ppWlSeat = pWlSeat;
        wl_seat_add_listener(pWlSeat, &seat_listener, nullptr);
    }
}

void registry_handle_global_remove(void* data, wl_registry* registry, uint32_t name)
{
}

const wl_registry_listener registry_listener = {
    registry_handle_global,
    registry_handle_global_remove
};

void handle_ping(void* data, wl_shell_surface* wlShellSurface, uint32_t serial)
{
    wl_shell_surface_pong(wlShellSurface, serial);
}

void handle_configure(void* data, wl_shell_surface* shell_surface, uint32_t edges, int32_t width, int32_t height)
{
    // No operation.
}

const wl_shell_surface_listener shell_surface_listener = {
    handle_ping,
    handle_configure,
};

void configure_callback(void* data, wl_callback* callback, uint32_t time)
{
    wl_callback_destroy(callback);
}

const wl_callback_listener configure_callback_listener = {
    configure_callback,
};

} // end of unnamed namespace

class WaylandSystem : public WindowSystem
{
    struct SurfaceEntry
    {
#if defined(WINAPI_EGL)
        wl_egl_window* m_wlEGLNativeWindow = nullptr;
#endif
        wl_surface* m_wlSurface = nullptr;
        wl_shell_surface* m_wlShellSurface = nullptr;
        wl_callback* m_callback = nullptr;
    };

public:
    virtual void CreateDisplay() override
    {
        // Open WAYLAND display
        m_wlDisplay = wl_display_connect(nullptr);
        NV_THROW_IF(m_wlDisplay == nullptr, "Failed to connect to a wayland socket.");

        m_wlRegistry = wl_display_get_registry(m_wlDisplay);
        NV_THROW_IF(m_wlRegistry == nullptr, "Failed to get registry.");

        wl_registry_add_listener(m_wlRegistry, &registry_listener, &registryInfo);

        wl_display_dispatch(m_wlDisplay);
    }

    virtual void DestroyDisplay() override
    {
        if (m_wlRegistry)
        {
            wl_registry_destroy(m_wlRegistry);
            m_wlRegistry = nullptr;
        }

        if (m_wlSeat)
        {
            wl_seat_destroy(m_wlSeat);
            m_wlSeat = nullptr;
        }

        if (m_wlShell)
        {
            wl_shell_destroy(m_wlShell);
            m_wlShell = nullptr;
        }

        if (m_wlCompositor)
        {
            wl_compositor_destroy(m_wlCompositor);
            m_wlCompositor = nullptr;
        }

        if (m_pointer)
        {
            wl_pointer_destroy(m_pointer);
            m_pointer = nullptr;
        }

        if (m_keyboard)
        {
            wl_keyboard_destroy(m_keyboard);
            m_keyboard = nullptr;
        }

        if (m_wlDisplay)
        {
            wl_display_flush(m_wlDisplay);
            wl_display_disconnect(m_wlDisplay);
            m_wlDisplay = nullptr;
        }
    }

    virtual void SetCreatingFullscreen(bool /*fullscreen*/) override
    {
    }

    virtual void GetScreenSize(int& /*width*/, int& /*height*/) override
    {
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
        SurfaceEntry entry;

        entry.m_wlSurface = wl_compositor_create_surface(m_wlCompositor);
        NV_THROW_IF(entry.m_wlSurface == nullptr, "Failed to create wayland surface.");

        entry.m_wlShellSurface = wl_shell_get_shell_surface(m_wlShell, entry.m_wlSurface);
        NV_THROW_IF(entry.m_wlShellSurface == nullptr, "Failed to create wayland shell surface.");

        wl_shell_surface_add_listener(entry.m_wlShellSurface, &shell_surface_listener, nullptr);

#if defined(WINAPI_EGL)
        entry.m_wlEGLNativeWindow = wl_egl_window_create(entry.m_wlSurface, width, height);
        NV_THROW_IF(entry.m_wlEGLNativeWindow == nullptr, "Failed to create wayland EGL window.");
#endif

        toggle_fullscreen(entry, m_fullscreen, width, height);

        m_surfaceEntries.push_back(entry);
    }

    virtual void DestroyAllWindows() override
    {
        for (auto& entry : m_surfaceEntries) {
            DestroySurface(entry);
        }
        m_surfaceEntries.clear();
    }

    virtual void DestroyWindow(void* winAddr) override
    {
        NV_THROW_IF(!winAddr, "Failed to destroy Wayland window.\n");

        auto pos = std::find_if(m_surfaceEntries.begin(), m_surfaceEntries.end(), [winAddr](SurfaceEntry const& entry){
            return entry.m_wlSurface == *reinterpret_cast<wl_surface**>(winAddr);
        });
        if (pos != m_surfaceEntries.end()) {
            DestroySurface(*pos);
            m_surfaceEntries.erase(pos);
        }
    }

    virtual void ProcessEvents() override
    {
        if (m_wlDisplay)
        {
            wl_display_dispatch_pending(m_wlDisplay);
        }
    }

    virtual void* GetDisplayAddr() override
    {
        return reinterpret_cast<void*>(&m_wlDisplay);
    }

    virtual void* GetWindowAddr() override
    {
        return m_surfaceEntries.empty() ? nullptr : reinterpret_cast<void*>(&m_surfaceEntries.back().m_wlSurface);
    }

#if defined(WINAPI_EGL)
    virtual void* GetEGLWindowAddr() override
    {
        return m_surfaceEntries.empty() ? nullptr : reinterpret_cast<void*>(&m_surfaceEntries.back().m_wlEGLNativeWindow);
    }

    virtual void* GetEGLDisplayAddr() override
    {
        m_eglDisplay = eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT, reinterpret_cast<void*>(m_wlDisplay), nullptr);
        return reinterpret_cast<void*>(&m_eglDisplay);
    }
#endif

    WaylandSystem()
        : m_wlDisplay(nullptr)
        , m_wlRegistry(nullptr)
        , m_wlCompositor(nullptr)
        , m_wlShell(nullptr)
        , m_wlSeat(nullptr)
        , m_pointer(nullptr)
        , m_keyboard(nullptr)
        , m_fullscreen(false)
    {
        registryInfo.ppWlCompositor = &m_wlCompositor;
        registryInfo.ppWlShell = &m_wlShell;
        registryInfo.ppWlSeat = &m_wlSeat;
    }

private:
    void toggle_fullscreen(SurfaceEntry& entry, bool fullscreen, int width, int height)
    {
        if (fullscreen)
        {
            wl_shell_surface_set_fullscreen(entry.m_wlShellSurface, WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT, 0, nullptr);
        }
        else
        {
            wl_shell_surface_set_toplevel(entry.m_wlShellSurface);
            handle_configure(nullptr, entry.m_wlShellSurface, 0, width, height);
        }

        wl_callback* callback = wl_display_sync(m_wlDisplay);
        wl_callback_add_listener(callback, &configure_callback_listener, nullptr);
    }

    void DestroySurface(SurfaceEntry& entry)
    {
#if defined(WINAPI_EGL)
        // Close the native window
        if (entry.m_wlEGLNativeWindow)
        {
            wl_egl_window_destroy(entry.m_wlEGLNativeWindow);
            entry.m_wlEGLNativeWindow = nullptr;
        }
#endif

        if (entry.m_wlShellSurface)
        {
            wl_shell_surface_destroy(entry.m_wlShellSurface);
            entry.m_wlShellSurface = nullptr;
        }

        if (entry.m_wlSurface)
        {
            wl_surface_destroy(entry.m_wlSurface);
            entry.m_wlSurface = nullptr;
        }

        if (entry.m_callback)
        {
            wl_callback_destroy(entry.m_callback);
            entry.m_callback = nullptr;
        }
    }

    // Wayland variables
    wl_display* m_wlDisplay;
    wl_registry* m_wlRegistry;
    wl_compositor* m_wlCompositor;
    wl_shell* m_wlShell;
    wl_seat* m_wlSeat;
    wl_pointer* m_pointer;
    wl_keyboard* m_keyboard;
    bool m_fullscreen;
    std::vector<SurfaceEntry> m_surfaceEntries;

#if defined(WINAPI_EGL)
    EGLDisplay m_eglDisplay;
#endif
};

WindowSystem& WindowSystemInstance()
{
    static WaylandSystem instance;
    return instance;
}
