//
//  HeadlessHost.h
//  The launch hook: an IObjUpdateSupport provider registered in GROUPID_ObjUpdateSupport.
//  Vectorworks calls Init() at startup, with no UI and before any document exists.
//
//  Scaffold only (#5): Init() logs and does nothing else. Ticket #6 starts the local HTTP server
//  here (background thread, never calls the SDK) and stops it on application shutdown.
//
#pragma once

namespace VwMcp
{
    // {21EB8AB0-4B54-429D-B8AA-1AD871E8A8A9}
    static const VWIID IID_HeadlessHost = { 0x21eb8ab0, 0x4b54, 0x429d, { 0xb8, 0xaa, 0x1a, 0xd8, 0x71, 0xe8, 0xa8, 0xa9 } };

    class CHeadlessHost : public VCOMImmediateImpl<VectorWorks::Extension::IObjUpdateSupport>
    {
    public:
                                CHeadlessHost(CallBackPtr);
        virtual                 ~CHeadlessHost();

        // IObjUpdateSupport
        virtual void VCOM_CALLTYPE Init(VectorWorks::Extension::IObjUpdateSupportContext* context);
    };

    // Writes one line to the system log (macOS: unified logging, subsystem "vw-mcp";
    // read it with `log stream --predicate 'subsystem == "vw-mcp"'`). Never calls the SDK,
    // so it is safe from any thread.
    void Log(const char* message);
}
