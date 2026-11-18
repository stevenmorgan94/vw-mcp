//
//  StatusPalette.cpp
//

#include "StatusPalette.h"
#include "bridge/Bridge.h"
#include "bridge/ScriptRunner.h"
#include "bridge/HeadlessHost.h"

#include <filesystem>
#include <fstream>

#if GS_MAC
#include <CoreFoundation/CoreFoundation.h>
#include <objc/message.h>
#include <objc/runtime.h>
#endif

#include "PaletteHtml.generated.inc"   // kPaletteHtml, from tools/embed_palette.py

namespace VwMcp
{
    // ---- JS bridge --------------------------------------------------------------------
    BEGIN_WebPalette_DISPATCH_MAP(CStatusJSProvider)
    ADD_WebPalette_FUNCTION("status", OnStatus)
    ADD_WebPalette_FUNCTION("copy", OnCopy)
    ADD_WebPalette_FUNCTION("code", OnCode)
    ADD_WebPalette_FUNCTION("setPaused", OnSetPaused)
    ADD_WebPalette_FUNCTION("setSaveFirst", OnSetSaveFirst)
    ADD_WebPalette_FUNCTION("saveScript", OnSaveScript)
    ADD_WebPalette_FUNCTION("saveResult", OnSaveResult)
    END_WebPalette_DISPATCH_MAP

    CStatusJSProvider::CStatusJSProvider(IVWUnknown* parent) : VWExtensionPaletteJSProvider(parent) {}
    CStatusJSProvider::~CStatusJSProvider() {}

    void CStatusJSProvider::OnInit(IInitContext* context)
    {
        fWebFrame = context->GetWebFrame();
        context->AddFunctionPromiseSync("vwmcp.status");
        context->AddFunctionPromiseSync("vwmcp.copy");
        for (const char* f : { "vwmcp.code", "vwmcp.setPaused", "vwmcp.setSaveFirst", "vwmcp.saveScript", "vwmcp.saveResult" })
            context->AddFunctionPromiseSync(f);
    }

    void CStatusJSProvider::OnStatus(const TXString&, const TXString&, const std::vector<nlohmann::json>&, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        context->Resolve(Bridge::StatusJson());
    }

#if GS_MAC
    // [[NSPasteboard generalPasteboard] clearContents]; [... setString:text forType:NSPasteboardTypeString]
    static bool CopyToClipboard(const std::string& text)
    {
        using MsgId = id (*)(Class, SEL);
        using MsgLong = long (*)(id, SEL);
        using MsgSet = bool (*)(id, SEL, id, id);
        Class pbClass = objc_getClass("NSPasteboard");
        if (!pbClass) return false;
        id pb = ((MsgId)objc_msgSend)(pbClass, sel_registerName("generalPasteboard"));
        if (!pb) return false;
        ((MsgLong)objc_msgSend)(pb, sel_registerName("clearContents"));
        CFStringRef s = CFStringCreateWithBytes(kCFAllocatorDefault, (const UInt8*)text.data(), (CFIndex)text.size(), kCFStringEncodingUTF8, false);
        if (!s) return false;
        bool ok = ((MsgSet)objc_msgSend)(pb, sel_registerName("setString:forType:"), (__bridge id)s, (__bridge id)CFSTR("public.utf8-plain-text"));
        CFRelease(s);
        return ok;
    }
#endif

    void CStatusJSProvider::OnCopy(const TXString&, const TXString&, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        bool ok = false;
#if GS_MAC
        if (!args.empty() && args[0].is_string())
            ok = CopyToClipboard(args[0].get<std::string>());
#endif
        // TODO(#9): Windows clipboard.
        context->Resolve(nlohmann::json { { "ok", ok } });
    }

    static int  ArgInt(const std::vector<nlohmann::json>& a, size_t i)  { return i < a.size() && a[i].is_number() ? a[i].get<int>() : 0; }
    static bool ArgBool(const std::vector<nlohmann::json>& a, size_t i) { return i < a.size() && a[i].is_boolean() && a[i].get<bool>(); }

    void CStatusJSProvider::OnCode(const TXString&, const TXString&, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        context->Resolve(Bridge::JobCode(ArgInt(args, 0)));
    }

    void CStatusJSProvider::OnSetPaused(const TXString&, const TXString&, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        Bridge::SetPaused(ArgBool(args, 0));
        context->Resolve(nlohmann::json { { "ok", true } });
    }

    void CStatusJSProvider::OnSetSaveFirst(const TXString&, const TXString&, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        Bridge::SetSaveFirst(ArgBool(args, 0));
        context->Resolve(nlohmann::json { { "ok", true } });
    }

    void CStatusJSProvider::OnSaveScript(const TXString&, const TXString&, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        std::string name = args.size() > 1 && args[1].is_string() ? args[1].get<std::string>() : "";
        context->Resolve(Bridge::QueueSaveScript(ArgInt(args, 0), name));
    }

    void CStatusJSProvider::OnSaveResult(const TXString&, const TXString&, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
    {
        context->Resolve(Bridge::TakeInternalResult(ArgInt(args, 0)));
    }

    // ---- palette ----------------------------------------------------------------------
    CExtStatusPalette::CExtStatusPalette(CallBackPtr) {}
    CExtStatusPalette::~CExtStatusPalette() {}

    void CExtStatusPalette::DefineSinks()
    {
        this->DefineSink<CStatusJSProvider>(IID_WebJavaScriptProvider);
    }

    TXString CExtStatusPalette::GetTitle() { return TXResStr("ExtVwMcpStatus", "paletteName"); }

    bool CExtStatusPalette::GetInitialSize(ViewCoord& outCX, ViewCoord& outCY) { outCX = 360; outCY = 480; return true; }
    bool CExtStatusPalette::GetMinimalSize(ViewCoord& outCX, ViewCoord& outCY) { outCX = 280; outCY = 300; return true; }

    // The page is embedded in the binary and written to <data folder>/palette/index.html. This avoids
    // enumerating bundle resources (that enumeration has escaped the bundle before) and needs no build tooling.
    TXString CExtStatusPalette::GetInitialURL()
    {
        std::filesystem::path dir = std::filesystem::path(DataFolder()) / "palette";
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        std::filesystem::path f = dir / "index.html";
        {
            std::ofstream out(f, std::ios::trunc | std::ios::binary);
            out << kPaletteHtml;
        }
        return TXString(("file://" + f.string()).c_str());
    }

    // ---- menu -------------------------------------------------------------------------
    static SMenuDef gShowStatusMenuDef = {
        /*Needs*/           EMenuEnableFlags::None,
        /*NeedsNot*/        EMenuEnableFlags::None,
        /*Title*/           { "ExtMenuShowVwMcpStatus", "menu_title" },
        /*Category*/        { "ExtMenuShowVwMcpStatus", "menu_category" },
        /*HelpText*/        { "ExtMenuShowVwMcpStatus", "menu_helptext" },
        /*VersionCreated*/  32,
        /*VersionModified*/ 0,
        /*VersionRetired*/  0,
        /*OverrideHelpID*/  " "
    };

    CExtMenuShowStatus::CExtMenuShowStatus(CallBackPtr cbp) : VWExtensionMenu(cbp, gShowStatusMenuDef) {}
    CExtMenuShowStatus::~CExtMenuShowStatus() {}
    CExtMenuShowStatus_EventSink::CExtMenuShowStatus_EventSink(IVWUnknown* parent) : VWMenu_EventSink(parent) {}
    CExtMenuShowStatus_EventSink::~CExtMenuShowStatus_EventSink() {}

    void CExtMenuShowStatus_EventSink::DoInterface()
    {
        gSDK->SetWebPaletteVisibility(CExtStatusPalette::_GetIID(), true);
    }

    static int gHelpMenuErr = -1;     // -1 = not attempted / IWorkspaces not available yet
    static int gHelpMenuTries = 0;
    int HelpMenuItemResult() { return gHelpMenuErr; }

    void InstallHelpMenuItem()
    {
        using namespace VectorWorks::Workspaces;
        if (gHelpMenuErr != -1 || gHelpMenuTries > 1000) return;
        ++gHelpMenuTries;
        VCOMPtr<IWorkspaces> ws(IID_Workspaces);
        if (!ws) return;
        IWorkspaces::ESpecialMenuItemLocation loc[IWorkspaces::kSpecialMenuOS_OSCount] = {
            IWorkspaces::eSpecialMenuItemLocation_Help, IWorkspaces::eSpecialMenuItemLocation_Help };
        VCOMError err = ws->AddSpecialMenuItem(loc, CExtMenuShowStatus::_GetIID(), 910,
                                               IWorkspaces::eSpecialMenuItemInsert_Last,
                                               IWorkspaces::eSpecialMenuItemDivider_BeforeItem);
        gHelpMenuErr = (int)err;
    }
}

// {CD211A42-6E81-4338-A3A0-71B276603F68}
IMPLEMENT_VWPaletteExtension(
    /*Extension class*/ VwMcp::CExtStatusPalette,
    /*Universal name*/  "VwMcpStatus",
    /*Version*/         1,
    /*UUID*/            0xcd211a42, 0x6e81, 0x4338, 0xa3, 0xa0, 0x71, 0xb2, 0x76, 0x60, 0x3f, 0x68);

// {5749BFDF-30EC-460A-8A62-8A276C7D9252}
IMPLEMENT_VWMenuExtension(
    /*Extension class*/ VwMcp::CExtMenuShowStatus,
    /*Event sink*/      VwMcp::CExtMenuShowStatus_EventSink,
    /*Universal name*/  "ExtMenuShowVwMcpStatus",
    /*Version*/         1,
    /*UUID*/            0x5749bfdf, 0x30ec, 0x460a, 0x8a, 0x62, 0x8a, 0x27, 0x6c, 0x7d, 0x92, 0x52);
