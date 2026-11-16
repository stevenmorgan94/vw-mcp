//
//  ModuleMain.cpp
//  Entry point of the vw-mcp Vectorworks module (vw-mcp.vwlibrary).
//
//  The plug-in is headless: it registers one IObjUpdateSupport provider, which Vectorworks
//  initialises at launch with no user action (see docs/research, issue #2). No menus, tools
//  or palettes are registered here yet.
//

#include "bridge/HeadlessHost.h"
#include "palette/StatusPalette.h"

const char* DefaultPluginVWRIdentifier() { return "vw-mcp"; }

// The SDK version this module was compiled for. Vectorworks rejects a module built for another year.
extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_ver() { return SDK_VERSION; }

extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_main(Sint32 action, void* moduleInfo, const VWIID& iid,
                                                        IVWUnknown*& inOutInterface, CallBackPtr cbp)
{
    ::GS_InitializeVCOM(cbp);

    Sint32 reply = 0L;

    using namespace VWFC::PluginSupport;

    // Group registration. Use REGISTER_Interface (group overload), NOT REGISTER_Interface_NoCache:
    // the SDK 2027 group overload of REGISTER_Interface_NoCache calls GS_VWRegisterInterface without
    // the group id (VWExtensions.h), so the provider would never be found in GROUPID_ObjUpdateSupport.
    REGISTER_Interface<VwMcp::CHeadlessHost>(GROUPID_ObjUpdateSupport, VwMcp::IID_HeadlessHost,
                                             action, moduleInfo, iid, inOutInterface, cbp, reply);

    VwMcp::InstallHelpMenuItem();

    // The status palette and the menu command that shows it (also put in the Help menu at launch).
    REGISTER_Extension<VwMcp::CExtStatusPalette>(GROUPID_ExtensionWebPalettes, action, moduleInfo, iid, inOutInterface, cbp, reply);
    REGISTER_Extension<VwMcp::CExtMenuShowStatus>(GROUPID_ExtensionMenu, action, moduleInfo, iid, inOutInterface, cbp, reply);

    return reply;
}
