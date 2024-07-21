//---------------------------------------------------------------------------
// File: WindowSystem_D2d.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

#include "Application.h"

#include <vector>

#ifndef DPI_ENUMS_DECLARED

typedef enum MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

#define DPI_ENUMS_DECLARED
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
#pragma comment(lib, "Shcore.lib")
#include <ShellScalingApi.h>
#endif

static HWND s_ReplayWindow = NULL;

//-----------------------------------------------------------------------------
// TrySetProcessDpiAwareness
//-----------------------------------------------------------------------------
static HRESULT Win32Replay_TrySetProcessDpiAwareness(PROCESS_DPI_AWARENESS value)
{
    // Load up DLL responsible for DPI management (requires Win8.1 and above)
    HMODULE hShcore = LoadLibraryA("Shcore.dll");
    if (hShcore == NULL) {
        return S_OK;
    }

    // Find up SetProcessDpiAwareness
    typedef HRESULT(STDAPICALLTYPE * PFN_SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS value);
    PFN_SetProcessDpiAwareness fnSetProcessDpiAwareness = reinterpret_cast<PFN_SetProcessDpiAwareness>(GetProcAddress(hShcore, "SetProcessDpiAwareness"));
    if (fnSetProcessDpiAwareness == NULL) {
        return S_OK;
    }

    // Set value if the function exists
    return fnSetProcessDpiAwareness(value);
}

//------------------------------------------------------------------------------
// CreateWindowEx_Win32 (static)
//------------------------------------------------------------------------------
static HWND Win32Replay_CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    // Force style for a borderless window if requested
    if (Application::HasForceBorderlessWindow()) {
        dwStyle = WS_POPUP | WS_OVERLAPPED | WS_TILED | WS_VISIBLE;
    }

    // Adjust the window rect based on style
    RECT WindowRect;
    WindowRect.left = x;
    WindowRect.right = x + nWidth;
    WindowRect.top = y;
    WindowRect.bottom = y + nHeight;
    AdjustWindowRectEx(&WindowRect, dwStyle, NULL, dwExStyle);
    nWidth = WindowRect.right - WindowRect.left;
    nHeight = WindowRect.bottom - WindowRect.top;

    // Create window
    return CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

//-----------------------------------------------------------------------------
// ReplayerWndProc
//-----------------------------------------------------------------------------
static LRESULT CALLBACK ReplayerWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Handle messages we care about
    switch (uMsg)
    {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
            {
                BEGIN_DATA_SCOPE();

                PostQuitMessage(0);
                return 0;
            }

            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// Window Specification
//-----------------------------------------------------------------------------
const wchar_t REPLAYER_WINDOW_CLASS_NAME[] = L"NV Replayer WndClass";
const wchar_t REPLAYER_WINDOW_TITLE_NAME[] = L"Nvda.Replayer";
const wchar_t REPLAYER_WINDOW_MENU_NAME[] = L"";

//-----------------------------------------------------------------------------
// RegisterReplayerWindowClass
//-----------------------------------------------------------------------------
BOOL RegisterReplayerWindowClass(HINSTANCE hInstance, UINT style)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Populate the struct
    WNDCLASS wc;
    wc.style = style;
    wc.lpfnWndProc = (WNDPROC)ReplayerWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = REPLAYER_WINDOW_MENU_NAME;
    wc.lpszClassName = REPLAYER_WINDOW_CLASS_NAME;
    BOOL ret = RegisterClass(&wc);
    if (!ret && GetLastError() == ERROR_CLASS_ALREADY_EXISTS)
    {
        BEGIN_DATA_SCOPE();

        return TRUE;
    }

    return ret;
}

//-----------------------------------------------------------------------------
// CreateReplayerWindow
//-----------------------------------------------------------------------------
HWND CreateReplayerWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, uint32_t x, uint32_t y, uint32_t Width, uint32_t Height, DWORD Style, DWORD ExtendedStyle, PROCESS_DPI_AWARENESS DpiAwareness)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Respect captured process's DPI awareness
    Win32Replay_TrySetProcessDpiAwareness(DpiAwareness);

    // Respect captured process's DPI awareness
    s_ReplayWindow = Win32Replay_CreateWindowEx(ExtendedStyle, REPLAYER_WINDOW_CLASS_NAME, REPLAYER_WINDOW_TITLE_NAME, Style, x, y, Width, Height, NULL, NULL, hInstance, NULL);
    return s_ReplayWindow;
}

//-----------------------------------------------------------------------------
// GetReplayerMonitor
//-----------------------------------------------------------------------------
HMONITOR GetReplayerMonitor()
{
    return MonitorFromWindow(s_ReplayWindow, MONITOR_DEFAULTTOPRIMARY);
}

class Win32System : public WindowSystem
{
public:

    virtual void CreateDisplay() override
    {
        m_hInstance = GetModuleHandle(NULL);
        RegisterReplayerWindowClass(m_hInstance, CS_HREDRAW | CS_VREDRAW);
    }

    virtual void DestroyDisplay() override
    {
        // Nothing to do.
    }

    virtual void SetCreatingFullscreen(bool fullscreen) override
    {
        m_fullscreen = fullscreen;
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
        if (m_fullscreen) {
            GetScreenSize(width, height);
        }

        const DWORD Style = WS_POPUP | WS_OVERLAPPED | WS_TILED | WS_VISIBLE;
        auto hWnd = CreateReplayerWindow(m_hInstance, NULL, 0, 0, width, height, Style, 0, PROCESS_SYSTEM_DPI_AWARE);
        m_hWnds.push_back(hWnd);
    }

    virtual void GetScreenSize(int& width, int& height) override
    {
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
    }

    virtual void DestroyAllWindows() override
    {
        for (auto& hWnd : m_hWnds) {
            ::DestroyWindow(hWnd);
        }
        m_hWnds.clear();
    }

    virtual void DestroyWindow(void* winAddr) override
    {
        auto hWnd = reinterpret_cast<HWND>(winAddr);
        auto itr = std::find_if(m_hWnds.begin(), m_hWnds.end(), [&](HWND& _hWnd) {
            return _hWnd == hWnd;
        });
        if (itr != m_hWnds.end()) {
            ::DestroyWindow(*itr);
            m_hWnds.erase(itr);
        }
    }

    virtual void* GetDisplayAddr() override
    {
        return &m_hInstance;
    }

    virtual void* GetWindowAddr() override
    {
        return reinterpret_cast<void*>(&m_hWnds.back());
    }

    Win32System() = default;

private:
    HINSTANCE m_hInstance;
    std::vector<HWND> m_hWnds;
    bool m_fullscreen = false;
};

WindowSystem& WindowSystemInstance()
{
    static Win32System instance;
    return instance;
}