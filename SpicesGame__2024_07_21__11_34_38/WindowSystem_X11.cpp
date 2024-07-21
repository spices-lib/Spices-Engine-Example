//---------------------------------------------------------------------------
// File: WindowSystem_X11.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

#if defined(WINAPI_GLX)
#include "nvglx.h"
#endif

#include "X11/Xatom.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <algorithm>
#include <cstring>
#include <vector>

class X11System : public WindowSystem
{

public:
    X11System()
        : m_XDisplay(nullptr)
        , m_defaultScreen(0)
    {
    }

    virtual void ProcessEvents() override
    {
        XEvent event;

        // The only event that is of interest to us is the close event.
        while (XPending(m_XDisplay))
        {
            XNextEvent(m_XDisplay, &event);
            switch (event.type)
            {
            case ClientMessage:
                // All we have to do when we receive the close event is exit the application loop.
                if ((event.xclient.message_type == XInternAtom(m_XDisplay, "WM_PROTOCOLS", True)) && (static_cast<Atom>(event.xclient.data.l[0]) == XInternAtom(m_XDisplay, "WM_DELETE_WINDOW", True)))
                {
                    Shutdown();
                }
                break;

            case KeyRelease:
                {
                    int dummy = 0;
                    KeySym* pKeySyms = XGetKeyboardMapping(event.xkey.display, event.xkey.keycode, 1, &dummy);
                    if (pKeySyms)
                    {
                        if (pKeySyms[0] == XK_Escape)
                        {
                            Shutdown();
                        }
                        XFree(pKeySyms);
                    }
                }
                break;
            
            default:
                break;
            }
        }
    }

    virtual void CreateDisplay() override
    {
        // Need this for cross-process eglStream capabilities.
        const auto status = XInitThreads();
        NV_THROW_IF(!status, "XInitThreads Failed");

        // Open X display
        m_XDisplay = XOpenDisplay(nullptr);
        NV_THROW_IF(m_XDisplay == nullptr, "X failed to open display.\n");

        m_defaultScreen = DefaultScreen(m_XDisplay);
    }

    virtual void DestroyDisplay() override
    {
        XCloseDisplay(m_XDisplay);
        m_XDisplay = nullptr;
    }

    virtual void SetCreatingFullscreen(bool fullscreen) override
    {
        m_creatingFullscreen = fullscreen;
    }

    void GetScreenSize(int nScreen, int& width, int& height)
    {
        Screen* pScreen = XScreenOfDisplay(m_XDisplay, nScreen);
        NV_ASSERT(pScreen);
        width = XWidthOfScreen(pScreen);
        height = XHeightOfScreen(pScreen);
    }

    virtual void GetScreenSize(int& width, int& height) override
    {
        GetScreenSize(m_defaultScreen, width, height);
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
        WindowEntry entry;

#if defined(WINAPI_GLX)
        using CreationData = std::tuple<GLXFBConfig*, const XColor*, int>;

        if (data) {
            CreationData* winData = reinterpret_cast<CreationData*>(data);
            GLXFBConfig& config = *std::get<0>(*winData);
            XVisualInfo* pVI = glXGetVisualFromFBConfig(m_XDisplay, config);

            NV_THROW_IF(!pVI, "Unable to get XVisual from GLXFBConfig.");

            // Resize to the screen extent when using fullscreen
            if (m_creatingFullscreen) {
                GetScreenSize(pVI->screen, width, height);
            }

            entry.screen = pVI->screen;
            Window rootWindow = RootWindow(m_XDisplay, pVI->screen);

            // For StaticGray, StaticColor, and TrueColor, alloc must be AllocNone, or a BadMatch error results.
            const auto visualType = pVI->c_class;
            const bool writableColormap = (visualType != StaticGray && visualType != StaticColor && visualType != TrueColor);

            XColor* colors = const_cast<XColor*>(std::get<1>(*winData));
            int colormapSize = std::get<2>(*winData);
            if (writableColormap && colors && colormapSize) {
                entry.colormap = XCreateColormap(m_XDisplay, rootWindow, pVI->visual, AllocAll);
                auto ret = XStoreColors(m_XDisplay, entry.colormap, colors, colormapSize);
                NV_THROW_IF(ret == BadAccess || ret == BadColor || ret == BadValue, "Failed to store colors in colormap.");
            } else {
                entry.colormap = XCreateColormap(m_XDisplay, rootWindow, pVI->visual, AllocNone);
            }

            XSetWindowAttributes swa;

            swa.colormap = entry.colormap;
            swa.background_pixmap = None;
            swa.border_pixel = 0;
            swa.event_mask = StructureNotifyMask;

            entry.window = XCreateWindow(
                m_XDisplay,
                rootWindow,
                0,
                0,
                width,
                height,
                0,
                pVI->depth,
                InputOutput,
                pVI->visual,
                CWBorderPixel | CWColormap | CWEventMask,
                &swa);

            NV_THROW_IF(entry.window == None, "Failed to create XWindow.");

            XFree(pVI);
        } else
#endif
        {
            // Resize to the screen extent when using fullscreen
            if (m_creatingFullscreen) {
                GetScreenSize(width, height);
            }

            // Create a native window
            entry.window = XCreateSimpleWindow(m_XDisplay,
                RootWindow(m_XDisplay, m_defaultScreen),
                0,
                0,
                width,
                height,
                0,
                BlackPixel(m_XDisplay, m_defaultScreen),
                WhitePixel(m_XDisplay, m_defaultScreen));
            NV_THROW_IF(!entry.window, "Failed to create native window.\n");

            XSetWindowBackgroundPixmap(m_XDisplay, entry.window, None);
        }

        // Make the window unresizable.
        XSizeHints sizeHints;
        memset(&sizeHints, 0, sizeof(XSizeHints));
        sizeHints.flags = PMaxSize | PMinSize;
        sizeHints.max_width = sizeHints.min_width = width;
        sizeHints.max_height = sizeHints.min_height = height;
        XSetWMNormalHints(m_XDisplay, entry.window, &sizeHints);

        if (m_creatingFullscreen) {
            Atom wm_state = XInternAtom(m_XDisplay, "_NET_WM_STATE", false);
            Atom wm_fullscreen = XInternAtom(m_XDisplay, "_NET_WM_STATE_FULLSCREEN", false);
            XChangeProperty(m_XDisplay, entry.window, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char*)&wm_fullscreen, 1);
        }

        Atom wm_destroy_window = XInternAtom(m_XDisplay, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_XDisplay, entry.window, &wm_destroy_window, 1);

        // Make sure the MapNotify event goes into the queue
        XSelectInput(m_XDisplay, entry.window, StructureNotifyMask | PointerMotionMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask);

        // Window title
        XStoreName(m_XDisplay, entry.window, "SerializedWindow");

        // Show it
        XMapWindow(m_XDisplay, entry.window);

        // Make sure a fix-sized window is shown before graphics operation.
        // A later shown will trigger "resize" event and cause vkQueuePresent
        // receive OUT_OF_DATA error
        XFlush(m_XDisplay);

        // Add to entry list
        m_windows.push_back(entry);

#if defined(WINAPI_EGL)
        m_windows.back().nativeWindow = reinterpret_cast<void*>(&m_windows.back().window);
#endif
    }

    virtual void DestroyAllWindows() override
    {
        for (auto& entry : m_windows) {
            XDestroyWindow(m_XDisplay, entry.window);
        }
        m_windows.clear();
    }

    virtual void DestroyWindow(void* winAddr) override
    {
        NV_THROW_IF(!winAddr, "Failed to destroy X11 window.\n");
        Window win = (*reinterpret_cast<Window*>(winAddr));

        XDestroyWindow(m_XDisplay, win);
        auto pos = std::find_if(m_windows.begin(), m_windows.end(), [win](WindowEntry& entry) {
            return entry.window == win;
        });
        if (pos != m_windows.end()) {
            m_windows.erase(pos);
        }
    }

    virtual void* GetDisplayAddr() override
    {
        return reinterpret_cast<void*>(&m_XDisplay);
    }

    virtual void* GetWindowAddr() override
    {
        NV_THROW_IF(m_windows.empty(), "Failed to get X11 window address.\n");
        return reinterpret_cast<void*>(&m_windows.back().window);
    }

#if defined(WINAPI_EGL)
    virtual void* GetEGLWindowEXTAddr() override
    {
        NV_THROW_IF(m_windows.empty(), "Failed to get X11 pixmap address.\n");
        return reinterpret_cast<void*>(&m_windows.back().nativeWindow);
    }

    virtual void* GetEGLDisplayAddr() override
    {
        m_eglDisplay = eglGetPlatformDisplay(EGL_PLATFORM_X11_EXT, reinterpret_cast<void*>(m_XDisplay), nullptr);
        return reinterpret_cast<void*>(&m_eglDisplay);
    }
#endif

#if defined(WINAPI_GLX)
    virtual void CreatePixmap(int width, int height) override
    {
        m_XPixmap = XCreatePixmap(m_XDisplay,
            RootWindow(m_XDisplay, m_defaultScreen),
            width, height,
            DefaultDepth(m_XDisplay, m_defaultScreen));
    }

    virtual void DestroyPixmap() override
    {
        XFreePixmap(m_XDisplay, m_XPixmap);
    }

    virtual void* GetPixmapAddr() override
    {
        return reinterpret_cast<void*>(&m_XPixmap);
    }
#endif

private:
    struct WindowEntry
    {
        Window      window = None;
        Colormap    colormap = None;
        int         screen = 0;
#if defined(WINAPI_EGL)
        void*       nativeWindow = nullptr;
#endif
    };

    // X11 variables
    Display*                m_XDisplay;
    int                     m_defaultScreen;
    std::vector<WindowEntry>  m_windows;
    bool                    m_creatingFullscreen = false;
#if defined(WINAPI_GLX)
    Pixmap                  m_XPixmap;
#endif
#if defined(WINAPI_EGL)
    EGLDisplay              m_eglDisplay;
#endif
};

WindowSystem& WindowSystemInstance()
{
    static X11System instance;
    return instance;
}
