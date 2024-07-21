#include "QnxApplication.h"
#include "Helpers.h"
#include "CommonReplay.h"

#include <signal.h>

//------------------------------------------------------------------------------
// QnxApplication
//------------------------------------------------------------------------------
QnxApplication::QnxApplication()
{
    // Handle Ctrl+C. On QNX the resources (eglStream, OpenWFD, etc) need to be destoied otherwise the system state will corrupt
    struct sigaction sigint;
    sigint.sa_handler = [](int signum){
        NV_MESSAGE("Shuting down...");
        PlatformInstance().Shutdown();
    };
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &sigint, NULL);
}

//------------------------------------------------------------------------------
// ProcessMessages
//------------------------------------------------------------------------------
bool QnxApplication::ProcessMessages()
{
#if defined(__QNX_USE_DIRECT_TO_DISPLAY)
    // Nothing to do.
    return true;
#else
    bool shutdown = false;
    static int val = 1;

    // The only event that is of interest to us is the close event.
    while (!screen_get_event(appState.screen_ctx, appState.screen_ev, 0ull)) {
        // Get QNX CAR 2.1 event property
        int rc = screen_get_event_property_iv(appState.screen_ev, SCREEN_PROPERTY_TYPE, &val);
        if (rc || (val == SCREEN_EVENT_NONE)) {
            break;
        }

        switch (val) {
        case SCREEN_EVENT_CLOSE:
            // All we have to do when we receive the close event is exit the application loop.
            shutdown = true;
            break;

        default:
            break;
        }
    }

    return !shutdown;
#endif
}

//------------------------------------------------------------------------------
// PlatformInstance
//------------------------------------------------------------------------------
Application& Application::PlatformInstance()
{
    static QnxApplication app;
    return app;
}