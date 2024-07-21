//---------------------------------------------------------------------------
// File: WindowSystem_Xcb.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

#include <dlfcn.h>
#include <mutex>
#include <vector>
#include <xcb/xcb.h>
#include <xcb/xcb_icccm.h>
#include <X11/keysym.h>

// libxcb-keysyms dynamic load
typedef struct _XCBKeySymbols xcb_key_symbols_t;

typedef xcb_key_symbols_t* (*xcb_key_symbols_alloc_pfn)(xcb_connection_t *c);
typedef void (*xcb_key_symbols_free_pfn)(xcb_key_symbols_t *syms);
typedef xcb_keysym_t (*xcb_key_symbols_get_keysym_pfn)(xcb_key_symbols_t *syms, xcb_keycode_t keycode, int col);

class XCBKeySyms
{
private:
    XCBKeySyms()
    {
        m_libXcbKeysyms = dlopen("libxcb-keysyms.so.1", RTLD_NOW);

        if (m_libXcbKeysyms) {
            m_keySymbolsAlloc = reinterpret_cast<xcb_key_symbols_alloc_pfn>(dlsym(m_libXcbKeysyms, "xcb_key_symbols_alloc"));
            m_keySymbolsFree = reinterpret_cast<xcb_key_symbols_free_pfn>(dlsym(m_libXcbKeysyms, "xcb_key_symbols_free"));
            m_keySymbolsGetKeysym = reinterpret_cast<xcb_key_symbols_get_keysym_pfn>(dlsym(m_libXcbKeysyms, "xcb_key_symbols_get_keysym"));
        } else {
            printf("Failed to load libxcb-keysyms.so.1. It's better to have libxcb-keysyms installed.\n");
        }
    }

public:
    ~XCBKeySyms()
    {
        if (m_libXcbKeysyms) {
            dlclose(m_libXcbKeysyms);
            m_libXcbKeysyms = nullptr;
        }

        m_keySymbolsAlloc = nullptr;
        m_keySymbolsFree = nullptr;
        m_keySymbolsGetKeysym = nullptr;
    }

    static XCBKeySyms& Instance()
    {
        static std::unique_ptr<XCBKeySyms> s_pInstance;

        static std::once_flag s_onceFlag;
        std::call_once(s_onceFlag, [](){
            s_pInstance.reset(new XCBKeySyms);
        });

        return *s_pInstance;
    }

    xcb_key_symbols_t* AllocKeySymbols(xcb_connection_t* connection)
    {
        return m_keySymbolsAlloc ? m_keySymbolsAlloc(connection) : nullptr;
    }

    void FreeKeySymbols(xcb_key_symbols_t*& keySymbols)
    {
        if (m_keySymbolsFree) {
            m_keySymbolsFree(keySymbols);
            keySymbols = nullptr;
        }
    }

    bool IsEscape(xcb_key_symbols_t* keySymbols, xcb_keycode_t keyCode)
    {
        if (m_keySymbolsGetKeysym) {
            // Return if keysymbol is XK_Escape
            return m_keySymbolsGetKeysym(keySymbols, keyCode, 0) == XK_Escape;
        }

        // Default key code of "Escape" on Linux is 0x9
        return keyCode == 0x9;
    }

private:
    // Xcb-keysyms library handle
    void* m_libXcbKeysyms = nullptr;

    // Xcb-keysyms raw functions
    xcb_key_symbols_alloc_pfn      m_keySymbolsAlloc = nullptr;
    xcb_key_symbols_free_pfn       m_keySymbolsFree = nullptr;
    xcb_key_symbols_get_keysym_pfn m_keySymbolsGetKeysym = nullptr;
};

class XcbSystem : public WindowSystem
{
public:
    void handleEvent(const xcb_generic_event_t *event)
    {
        switch (event->response_type & 0x7f)
        {
        case XCB_CLIENT_MESSAGE:
            if ((*(xcb_client_message_event_t*)event).data.data32[0] ==
                (*atom_wm_delete_window).atom) {
                Shutdown();
            }
            break;
        case XCB_KEY_RELEASE:
            {
                const xcb_key_release_event_t *keyEvent = (const xcb_key_release_event_t *)event;
                if (XCBKeySyms::Instance().IsEscape(key_symbols, keyEvent->detail)) {
                    Shutdown();
                } 
            }
            break;
        case XCB_DESTROY_NOTIFY:
            Shutdown();
            break;
        default:
            break;
        }
    }

    virtual void ProcessEvents() override
    {
        xcb_flush(connection);
        xcb_generic_event_t *event;
        while ((event = xcb_poll_for_event(connection)))
        {
            handleEvent(event);
            free(event);
        }
    }

    virtual void CreateDisplay() override
    {
        // For Xcb, display means connection.
        const xcb_setup_t *setup;
        xcb_screen_iterator_t iter;
        int scr;

        connection = xcb_connect(NULL, &scr);
        NV_THROW_IF(!connection, "Could not build an xcb connection!");

        setup = xcb_get_setup(connection);
        iter = xcb_setup_roots_iterator(setup);
        while (scr-- > 0)
            xcb_screen_next(&iter);
        screen = iter.data;

        key_symbols = XCBKeySyms::Instance().AllocKeySymbols(connection);
    }

    virtual void DestroyDisplay() override
    {
        XCBKeySyms::Instance().FreeKeySymbols(key_symbols);

        xcb_disconnect(connection);
        connection = nullptr;
    }

    static xcb_intern_atom_reply_t* intern_atom_helper(xcb_connection_t *conn, bool only_if_exists, const char *str)
    {
        xcb_intern_atom_cookie_t cookie = xcb_intern_atom(conn, only_if_exists, strlen(str), str);
        return xcb_intern_atom_reply(conn, cookie, NULL);
    }

    virtual void SetCreatingFullscreen(bool fullscreen) override
    {
        creatingFullscreen = fullscreen;
    }

    virtual void GetScreenSize(int& width, int& height) override
    {
        width = screen->width_in_pixels;
        height = screen->height_in_pixels;
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
        uint32_t value_mask, value_list[32];

        xcb_window_t window = xcb_generate_id(connection);

        value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        value_list[0] = screen->black_pixel;
        value_list[1] =
            XCB_EVENT_MASK_KEY_RELEASE |
            XCB_EVENT_MASK_KEY_PRESS |
            XCB_EVENT_MASK_EXPOSURE |
            XCB_EVENT_MASK_STRUCTURE_NOTIFY |
            XCB_EVENT_MASK_POINTER_MOTION |
            XCB_EVENT_MASK_BUTTON_PRESS |
            XCB_EVENT_MASK_BUTTON_RELEASE;

        // Resize to the screen extent when using fullscreen
        if (creatingFullscreen) {
            GetScreenSize(width, height);
        }

        // Create window
        xcb_create_window(connection,
            XCB_COPY_FROM_PARENT,
            window, screen->root,
            0, 0, width, height, 0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            screen->root_visual,
            value_mask, value_list);

        // Make the window unresizable
        xcb_size_hints_t hints;
        memset(&hints, 0, sizeof(xcb_size_hints_t));
        xcb_icccm_size_hints_set_min_size(&hints, width, height);
        xcb_icccm_size_hints_set_max_size(&hints, width, height);
        xcb_icccm_set_wm_size_hints(connection, window, XCB_ATOM_WM_NORMAL_HINTS, &hints);

        if (creatingFullscreen) {
            xcb_intern_atom_reply_t *atom_wm_state = intern_atom_helper(connection, false, "_NET_WM_STATE");
            xcb_intern_atom_reply_t *atom_wm_fullscreen = intern_atom_helper(connection, false, "_NET_WM_STATE_FULLSCREEN");
            xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, atom_wm_state->atom, XCB_ATOM_ATOM, 32, 1, &(atom_wm_fullscreen->atom));
            free(atom_wm_fullscreen);
            free(atom_wm_state);
        }

        // Magic code that will send notification when window is destroyed
        xcb_intern_atom_reply_t* reply = intern_atom_helper(connection, true, "WM_PROTOCOLS");
        atom_wm_delete_window = intern_atom_helper(connection, false, "WM_DELETE_WINDOW");

        xcb_change_property(connection, XCB_PROP_MODE_REPLACE,
            window, (*reply).atom, 4, 32, 1,
            &(*atom_wm_delete_window).atom);

        free(reply);

        // Make window visible
        xcb_void_cookie_t cookie = xcb_map_window_checked(connection, window);
        xcb_generic_error_t* error = xcb_request_check(connection, cookie);
        NV_THROW_IF(error, "Failed to map xcb window");
        free(error);

        // Make sure a fix-sized window is shown before graphics operations.
        // A later shown will trigger "resize" event and cause vkQueuePresent
        // receive OUT_OF_DATE error.
        xcb_flush(connection);

        // Add to window list
        windows.push_back(window);
    }

    virtual void DestroyAllWindows() override
    {
        for (auto win : windows) {
            // Make window invisible
            xcb_unmap_window(connection, win);
            // Destroy window
            xcb_destroy_window(connection, win);
        }
        windows.clear();
    }

    virtual void DestroyWindow(void* winAddr) override
    {
        NV_THROW_IF(!winAddr, "Failed to destroy XCB window.\n");
        xcb_window_t win = (*reinterpret_cast<xcb_window_t*>(winAddr));

        // Make window invisible
        xcb_unmap_window(connection, win);
        // Destroy window
        xcb_destroy_window(connection, win);

        auto pos = std::find(windows.begin(), windows.end(), win);
        if (pos != windows.end()) {
            windows.erase(pos);
        }
    }

    virtual void* GetDisplayAddr() override
    {
        return reinterpret_cast<void*>(&connection);
    }

    virtual void* GetWindowAddr() override
    {
        NV_THROW_IF(windows.empty(), "Failed to get XCB window address.\n");
        return reinterpret_cast<void*>(&windows.back());
    }

#if defined(WINAPI_GLX)
    virtual void CreatePixmap(int width, int height) override
    {
        m_pixmap = xcb_generate_id(connection);
        
        auto cookie = xcb_create_pixmap_checked(connection,
            screen->root_depth,
            m_pixmap,
            screen->root,
            width, height);

        auto error = xcb_request_check(connection, cookie);
        NV_THROW_IF(error, "Failed to create pixmap.\n");
    }

    virtual void DestroyPixmap() override
    {
        if (m_pixmap) {
            xcb_free_pixmap(connection, m_pixmap);
            m_pixmap = 0;
        }
    }

    virtual void* GetPixmapAddr() override
    {
        return reinterpret_cast<void*>(&m_pixmap);
    }
#endif

    XcbSystem()
        : connection(nullptr)
        , screen(nullptr)
        , atom_wm_delete_window(nullptr)
        , key_symbols(nullptr)
    {
    }

private:
    xcb_connection_t *connection;
    xcb_screen_t *screen;
    std::vector<xcb_window_t> windows;
    xcb_intern_atom_reply_t *atom_wm_delete_window;
    xcb_key_symbols_t* key_symbols;
    bool creatingFullscreen = false;

#if defined(WINAPI_GLX)
    xcb_pixmap_t m_pixmap;
#endif
};

WindowSystem& WindowSystemInstance()
{
    static XcbSystem instance;
    return instance;
}
