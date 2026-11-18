//
//  StatusPalette.h
//  The vw-mcp status palette (ticket #7): a web palette showing bridge state, how to connect an AI
//  app, and recent jobs. Opened from "vw-mcp Status…" in the Help menu (added with
//  IWorkspaces::AddSpecialMenuItem, so no workspace edit is needed) or from the same menu command
//  placed in a workspace.
//
#pragma once

namespace VwMcp
{
    using namespace VectorWorks::Extension;
    using namespace VWFC::PluginSupport;

    // JS bridge object `vwmcp`: status(), copy(text), and for the Utility tab (#27) code(jobId),
    // setPaused(on), setSaveFirst(on), saveScript(jobId, name) -> {ticket}, saveResult(ticket).
    class CStatusJSProvider : public VWExtensionPaletteJSProvider
    {
    public:
                        CStatusJSProvider(IVWUnknown* parent);
        virtual         ~CStatusJSProvider();
        virtual void    OnInit(IInitContext* context);

        DEFINE_WebPalette_DISPATCH_MAP;

    private:
        void OnStatus(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
        void OnCopy(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
        void OnCode(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
        void OnSetPaused(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
        void OnSetSaveFirst(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
        void OnSaveScript(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
        void OnSaveResult(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
    };

    class CExtStatusPalette : public VWExtensionWebPalette
    {
        DEFINE_VWPaletteExtension;
    public:
                            CExtStatusPalette(CallBackPtr);
        virtual             ~CExtStatusPalette();
        virtual void        DefineSinks() override;
        virtual TXString    GetTitle() override;
        virtual bool        GetInitialSize(ViewCoord& outCX, ViewCoord& outCY) override;
        virtual bool        GetMinimalSize(ViewCoord& outCX, ViewCoord& outCY) override;
        virtual TXString    VCOM_CALLTYPE GetInitialURL() override;
    };

    class CExtMenuShowStatus_EventSink : public VWMenu_EventSink
    {
    public:
                        CExtMenuShowStatus_EventSink(IVWUnknown* parent);
        virtual         ~CExtMenuShowStatus_EventSink();
        virtual void    DoInterface();
    };

    class CExtMenuShowStatus : public VWExtensionMenu
    {
        DEFINE_VWMenuExtension;
    public:
                        CExtMenuShowStatus(CallBackPtr cbp);
        virtual         ~CExtMenuShowStatus();
    };

    // Puts "vw-mcp Status…" in the Help menu. Main thread; safe to call repeatedly (acts once).
    // Called on every plugin_module_main entry until IWorkspaces is available (the menus are built
    // early), as the context probe did; adding it later only takes effect after a workspace reload.
    void InstallHelpMenuItem();
    int  HelpMenuItemResult();   // the AddSpecialMenuItem VCOMError, or -1 if not attempted yet
}
