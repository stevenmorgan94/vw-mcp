//
//  HeadlessHost.cpp
//

#include "HeadlessHost.h"
#include "Bridge.h"

#if GS_MAC
#include <os/log.h>
#elif _WINDOWS
#include <Windows.h>
#endif

using namespace VectorWorks::Extension;

namespace VwMcp
{
    void Log(const char* message)
    {
#if GS_MAC
        static os_log_t sLog = os_log_create("vw-mcp", "plugin");
        os_log(sLog, "%{public}s", message);
#elif _WINDOWS
        ::OutputDebugStringA("[vw-mcp] ");
        ::OutputDebugStringA(message);
        ::OutputDebugStringA("\n");
#endif
    }

    CHeadlessHost::CHeadlessHost(CallBackPtr)
    {
    }

    CHeadlessHost::~CHeadlessHost()
    {
    }

    void CHeadlessHost::Init(IObjUpdateSupportContext* context)
    {
        // Runs at Vectorworks launch, on the main thread, before any document exists. Only starts the
        // bridge (a background server thread plus main-loop timers); no document access, no Python.
        Log("IObjUpdateSupport::Init: starting the bridge");
        if (context)
        {
            context->AcceptNotification(kNotifyBeforeApplicationQuit);
            context->AcceptNotification(kNotifyApplicationShutdown);
        }
        Bridge::Start();
    }

    void CHeadlessHost::OnNotification(IObjUpdateSupportContext* context)
    {
        if (!context) return;
        StatusID which = 0;
        StatusData data = 0;
        context->GetNotification(which, data);
        if (which == kNotifyBeforeApplicationQuit || which == kNotifyApplicationShutdown)
            Bridge::Stop();
    }
}
