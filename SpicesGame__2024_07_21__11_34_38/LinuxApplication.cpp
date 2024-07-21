#include "LinuxApplication.h"
#include "Helpers.h"
#include "WindowSystem.h"

//------------------------------------------------------------------------------
// LinuxApplication
//------------------------------------------------------------------------------
LinuxApplication::LinuxApplication()
{
}

//------------------------------------------------------------------------------
// ProcessMessages
//------------------------------------------------------------------------------
bool LinuxApplication::ProcessMessages()
{
    WindowSystemInstance().ProcessEvents();
    const bool shutDown = WindowSystemInstance().ShouldShutdown();

    return !shutDown;
}

//------------------------------------------------------------------------------
// PlatformInstance
//------------------------------------------------------------------------------
Application& Application::PlatformInstance()
{
    static LinuxApplication app;
    return app;
}