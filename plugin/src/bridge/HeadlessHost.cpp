//
//  HeadlessHost.cpp
//

#include "HeadlessHost.h"

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

    void CHeadlessHost::Init(IObjUpdateSupportContext* /*context*/)
    {
        // Runs at Vectorworks launch. No document exists yet: no document access, no Python,
        // no UI, nothing that blocks. TODO(#6): start the bridge server and accept the
        // application-shutdown notifications to stop it.
        Log("IObjUpdateSupport::Init: vw-mcp loaded (headless scaffold; no server yet)");
    }
}
