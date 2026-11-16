// ===== AUTO-GENERATED from ISDK.h — DO NOT EDIT BY HAND =====
// Provides DispatchIsdkCall(). Generated from the VW 2026 ISDK.h; the 5 entries removed from ISDK in
// VW 2027 (DeleteAllComponents, Get/SetCurtainWallCutPlane, Get/SetLayerEnableCutPlane) were deleted by hand.
// TODO: regenerate from the 2027 ISDK.h with tools/gen_isdk_dispatch.py (docs: native-ops-split research, #8).
#include <unordered_map>

static std::unordered_map<int, MCObjectHandle> gHandleReg;
static int gNextHandleId = 1;

static MCObjectHandle ResolveHandle(const nlohmann::json& a){
    if (a.is_object()){
        if (a.contains("$h") && a["$h"].is_number_integer()){ auto it=gHandleReg.find(a["$h"].get<int>()); return it!=gHandleReg.end()?it->second:nullptr; }
        if (a.contains("$name") && a["$name"].is_string()) return gSDK->GetNamedObject(TXString(a["$name"].get<std::string>().c_str()));
        if (a.contains("$layer") && a["$layer"].is_string()) return gSDK->GetNamedLayer(TXString(a["$layer"].get<std::string>().c_str()));
    }
    return nullptr;
}
static long long      JInt (const nlohmann::json& a, size_t& i){ return a.at(i++).get<long long>(); }
static double         JReal(const nlohmann::json& a, size_t& i){ return a.at(i++).get<double>(); }
static bool           JBool(const nlohmann::json& a, size_t& i){ return a.at(i++).get<bool>(); }
static TXString       JStr (const nlohmann::json& a, size_t& i){ return TXString(a.at(i++).get<std::string>().c_str()); }
static MCObjectHandle JHandle(const nlohmann::json& a, size_t& i){ return ResolveHandle(a.at(i++)); }
static WorldPt   JWpt (const nlohmann::json& a, size_t& i){ const auto& p=a.at(i++); return WorldPt(p.at(0).get<double>(), p.at(1).get<double>()); }
static WorldPt3  JWpt3(const nlohmann::json& a, size_t& i){ const auto& p=a.at(i++); return WorldPt3(p.at(0).get<double>(), p.at(1).get<double>(), p.at(2).get<double>()); }
static WorldRect JWrect(const nlohmann::json& a, size_t& i){ const auto& p=a.at(i++); WorldRect r; r.Set(WorldPt(p.at(0).get<double>(),p.at(1).get<double>()), WorldPt(p.at(2).get<double>(),p.at(3).get<double>())); return r; }
static nlohmann::json MWpt (const WorldPt& p){ return nlohmann::json::array({p.x,p.y}); }
static nlohmann::json MWpt3(const WorldPt3& p){ return nlohmann::json::array({p.x,p.y,p.z}); }
static nlohmann::json MWrect(const WorldRect& r){ return nlohmann::json{{"l",r.left},{"t",r.top},{"r",r.right},{"b",r.bottom}}; }
static std::string MStr(const TXString& s){ return std::string(s.operator const char*()); }

typedef void (*IsdkShim)(const nlohmann::json& a, int asId, nlohmann::json& r);

static const std::unordered_map<std::string, IsdkShim>& IsdkShimTable(){
  static const std::unordered_map<std::string, IsdkShim> t = {
  { "GetClFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetClFillPat(p0));
  } },
  { "GetClLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetClLineWeight(p0));
  } },
  { "GetClUseGraphic", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetClUseGraphic(p0));
  } },
  { "GetClVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetClVisibility(p0));
  } },
  { "GetVPClassFillStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetVPClassFillStyle(p0, p1));
  } },
  { "SetClFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetClFillPat(p0, p1); r["ret"]=nullptr;
  } },
  { "SetClLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetClLineWeight(p0, p1); r["ret"]=nullptr;
  } },
  { "SetClUseGraphic", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetClUseGraphic(p0, p1); r["ret"]=nullptr;
  } },
  { "SetClVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetClVisibility(p0, p1); r["ret"]=nullptr;
  } },
  { "VPClassHasOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->VPClassHasOverride(p0, p1));
  } },
  { "DeleteAllDLComponents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->DeleteAllDLComponents());
  } },
  { "DeleteDLComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteDLComponent(p0));
  } },
  { "GetDefaultArrowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultArrowByClass());
  } },
  { "GetDefaultClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDefaultClass());
  } },
  { "GetDefaultFColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultFColorsByClass());
  } },
  { "GetDefaultFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDefaultFillPat());
  } },
  { "GetDefaultFPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultFPatByClass());
  } },
  { "GetDefaultHatch", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetDefaultHatch();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDefaultLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDefaultLineWeight());
  } },
  { "GetDefaultLWByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultLWByClass());
  } },
  { "GetDefaultPColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultPColorsByClass());
  } },
  { "GetDefaultPPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultPPatByClass());
  } },
  { "GetDLComponentClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    Sint32 p1 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentClass(p0, p1));
    r["out"]["componentClass"] = (long long)p1;
  } },
  { "GetDLComponentFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    Sint32 p1 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentFill(p0, p1));
    r["out"]["fill"] = (long long)p1;
  } },
  { "GetDLComponentFillColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    ColorRef p1 = 0;
    ColorRef p2 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentFillColors(p0, p1, p2));
    r["out"]["fillForeColor"] = (long long)p1;
    r["out"]["fillBackColor"] = (long long)p2;
  } },
  { "GetDLComponentName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetDLComponentName(p0, p1));
    r["out"]["outComponentName"] = MStr(p1);
  } },
  { "GetDLComponentPenColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    ColorRef p1 = 0;
    ColorRef p2 = 0;
    ColorRef p3 = 0;
    ColorRef p4 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentPenColors(p0, p1, p2, p3, p4));
    r["out"]["leftPenForeColor"] = (long long)p1;
    r["out"]["leftPenBackColor"] = (long long)p2;
    r["out"]["rightPenForeColor"] = (long long)p3;
    r["out"]["rightPenBackColor"] = (long long)p4;
  } },
  { "GetDLComponentPenWeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    Uint8 p1 = 0;
    Uint8 p2 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentPenWeights(p0, p1, p2));
    r["out"]["penWeightLeft"] = (long long)p1;
    r["out"]["penWeightRight"] = (long long)p2;
  } },
  { "GetDLComponentUseFillClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    Boolean p1 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentUseFillClassAttr(p0, p1));
    r["out"]["useClassAttr"] = (bool)(p1!=0);
  } },
  { "GetDLComponentUsePenClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    Boolean p1 = 0;
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentUsePenClassAttr(p0, p1, p2));
    r["out"]["leftPenUseClassAttr"] = (bool)(p1!=0);
    r["out"]["rightPenUseClassAttr"] = (bool)(p2!=0);
  } },
  { "GetDLComponentWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldCoord p1 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentWidth(p0, p1));
    r["out"]["width"] = (double)p1;
  } },
  { "GetDLControlOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (double)(gSDK->GetDLControlOffset());
  } },
  { "GetDLOptions", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDLOptions());
  } },
  { "GetDLSeparation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (double)(gSDK->GetDLSeparation());
  } },
  { "GetDocumentDefaultSketchStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDocumentDefaultSketchStyle());
  } },
  { "GetNumberOfDLComponents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    short p0 = 0;
    r["ret"] = (bool)(gSDK->GetNumberOfDLComponents(p0));
    r["out"]["numComponents"] = (long long)p0;
  } },
  { "GetObjectInternalIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetObjectInternalIndex(p0));
  } },
  { "GetWallPrefStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    InternalIndex p0 = 0;
    r["ret"] = (bool)(gSDK->GetWallPrefStyle(p0));
    r["out"]["wallStyleNum"] = (long long)p0;
  } },
  { "GetWallStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    InternalIndex p1 = 0;
    r["ret"] = (bool)(gSDK->GetWallStyle(p0, p1));
    r["out"]["wallStyle"] = (long long)p1;
  } },
  { "SetDefaultArrowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultArrowByClass(); r["ret"]=nullptr;
  } },
  { "SetDefaultClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetDefaultClass(p0); r["ret"]=nullptr;
  } },
  { "SetDefaultFColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultFColorsByClass(); r["ret"]=nullptr;
  } },
  { "SetDefaultFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetDefaultFillPat(p0); r["ret"]=nullptr;
  } },
  { "SetDefaultFPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultFPatByClass(); r["ret"]=nullptr;
  } },
  { "SetDefaultHatch", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetDefaultHatch(p0));
  } },
  { "SetDefaultLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetDefaultLineWeight(p0); r["ret"]=nullptr;
  } },
  { "SetDefaultLWByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultLWByClass(); r["ret"]=nullptr;
  } },
  { "SetDefaultPColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultPColorsByClass(); r["ret"]=nullptr;
  } },
  { "SetDefaultPPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultPPatByClass(); r["ret"]=nullptr;
  } },
  { "SetDefaultWallThickness", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    gSDK->SetDefaultWallThickness(p0); r["ret"]=nullptr;
  } },
  { "SetDLComponentClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentClass(p0, p1));
  } },
  { "SetDLComponentFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentFill(p0, p1));
  } },
  { "SetDLComponentFillColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentFillColors(p0, p1, p2));
  } },
  { "SetDLComponentName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentName(p0, p1));
  } },
  { "SetDLComponentPenColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentPenColors(p0, p1, p2, p3, p4));
  } },
  { "SetDLComponentPenWeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentPenWeights(p0, p1, p2));
  } },
  { "SetDLComponentUseFillClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentUseFillClassAttr(p0, p1));
  } },
  { "SetDLComponentUsePenClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentUsePenClassAttr(p0, p1, p2));
  } },
  { "SetDLComponentWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    double p1 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentWidth(p0, p1));
  } },
  { "SetDLControlOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    gSDK->SetDLControlOffset(p0); r["ret"]=nullptr;
  } },
  { "SetDLOptions", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetDLOptions(p0); r["ret"]=nullptr;
  } },
  { "SetDLSeparation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    gSDK->SetDLSeparation(p0); r["ret"]=nullptr;
  } },
  { "SetDocumentDefaultSketchStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDocumentDefaultSketchStyle(p0));
  } },
  { "SetWallPrefStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetWallPrefStyle(p0));
  } },
  { "WrapGetDefaultWallThickness", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double_gs p0 = 0;
    gSDK->WrapGetDefaultWallThickness(p0); r["ret"]=nullptr;
    r["out"]["outCoordLen"] = (double)p0;
  } },
  { "Add3DVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    bool p2 = JBool(a,i);
    gSDK->Add3DVertex(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CalcAreaN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    gSDK->CalcAreaN(p0, p1); r["ret"]=nullptr;
    r["out"]["area"] = (double)p1;
  } },
  { "CalcPerimN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    gSDK->CalcPerimN(p0, p1); r["ret"]=nullptr;
    r["out"]["perim"] = (double)p1;
  } },
  { "CalcSurfaceArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->CalcSurfaceArea(p0));
  } },
  { "CalcVolume", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->CalcVolume(p0));
  } },
  { "Centroid3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    double_gs p2 = 0;
    double_gs p3 = 0;
    r["ret"] = (bool)(gSDK->Centroid3D(p0, p1, p2, p3));
    r["out"]["xCG"] = (double)p1;
    r["out"]["yCG"] = (double)p2;
    r["out"]["zCG"] = (double)p3;
  } },
  { "CountVertices", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CountVertices(p0));
  } },
  { "CreateSkylight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CreateSkylight(p0));
  } },
  { "DeleteVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeleteVertex(p0, p1); r["ret"]=nullptr;
  } },
  { "Get3DVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2;
    gSDK->Get3DVertex(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["vertex"] = MWpt3(p2);
  } },
  { "GetArcInfoN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    double_gs p2 = 0;
    WorldPt p3;
    WorldCoord p4 = 0;
    WorldCoord p5 = 0;
    gSDK->GetArcInfoN(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
    r["out"]["startAngle"] = (double)p1;
    r["out"]["sweepAngle"] = (double)p2;
    r["out"]["center"] = MWpt(p3);
    r["out"]["radiusX"] = (double)p4;
    r["out"]["radiusY"] = (double)p5;
  } },
  { "GetBatAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    WorldCoord p5 = 0;
    WorldCoord p6 = 0;
    double_gs p7 = 0;
    WorldCoord p8 = 0;
    r["ret"] = (bool)(gSDK->GetBatAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8));
    r["out"]["useHeight"] = (bool)(p2!=0);
    r["out"]["heightDepthValue"] = (double)p3;
    r["out"]["bottomWidth"] = (double)p4;
    r["out"]["topWidth"] = (double)p5;
    r["out"]["baseHeight"] = (double)p6;
    r["out"]["topSlope"] = (double)p7;
    r["out"]["controlPoint"] = (double)p8;
  } },
  { "GetDormerAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    WorldCoord p3 = 0;
    Boolean p4 = 0;
    WorldCoord p5 = 0;
    InternalIndex p6 = 0;
    Boolean p7 = 0;
    WorldCoord p8 = 0;
    r["ret"] = (bool)(gSDK->GetDormerAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8));
    r["out"]["edgeIndex"] = (long long)p2;
    r["out"]["cornerOffset"] = (double)p3;
    r["out"]["isPerpOffset"] = (bool)(p4!=0);
    r["out"]["perpOrHeightOffset"] = (double)p5;
    r["out"]["symName"] = (long long)p6;
    r["out"]["centerSymbol"] = (bool)(p7!=0);
    r["out"]["symOffset"] = (double)p8;
  } },
  { "GetEndPoints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    WorldPt p2;
    gSDK->GetEndPoints(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["startPt"] = MWpt(p1);
    r["out"]["endPt"] = MWpt(p2);
  } },
  { "GetExtrudeValues", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    WorldCoord p2 = 0;
    gSDK->GetExtrudeValues(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["bottom"] = (double)p1;
    r["out"]["top"] = (double)p2;
  } },
  { "GetGableAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    double_gs p5 = 0;
    double_gs p6 = 0;
    WorldCoord p7 = 0;
    r["ret"] = (bool)(gSDK->GetGableAttributes(p0, p1, p2, p3, p4, p5, p6, p7));
    r["out"]["useHeight"] = (bool)(p2!=0);
    r["out"]["heightDepthValue"] = (double)p3;
    r["out"]["bottomWidth"] = (double)p4;
    r["out"]["leftSlope"] = (double)p5;
    r["out"]["rightSlope"] = (double)p6;
    r["out"]["overhang"] = (double)p7;
  } },
  { "GetHipAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    double_gs p5 = 0;
    double_gs p6 = 0;
    double_gs p7 = 0;
    WorldCoord p8 = 0;
    r["ret"] = (bool)(gSDK->GetHipAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8));
    r["out"]["useHeight"] = (bool)(p2!=0);
    r["out"]["heightDepthValue"] = (double)p3;
    r["out"]["bottomWidth"] = (double)p4;
    r["out"]["leftSlope"] = (double)p5;
    r["out"]["rightSlope"] = (double)p6;
    r["out"]["frontSlope"] = (double)p7;
    r["out"]["overhang"] = (double)p8;
  } },
  { "GetLocus3DPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1;
    gSDK->GetLocus3DPosition(p0, p1); r["ret"]=nullptr;
    r["out"]["locPos"] = MWpt3(p1);
  } },
  { "GetLocusPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    gSDK->GetLocusPosition(p0, p1); r["ret"]=nullptr;
    r["out"]["locPos"] = MWpt(p1);
  } },
  { "GetNumRoofElements", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumRoofElements(p0));
  } },
  { "GetObjectBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldRect p1;
    r["ret"] = (bool)(gSDK->GetObjectBounds(p0, p1));
    r["out"]["bounds"] = MWrect(p1);
  } },
  { "GetPolyDirection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetPolyDirection(p0));
  } },
  { "GetPolyShapeClose", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetPolyShapeClose(p0));
  } },
  { "GetQArcQuadrant", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetQArcQuadrant(p0));
  } },
  { "GetRoofAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    Boolean p1 = 0;
    WorldCoord p2 = 0;
    WorldCoord p3 = 0;
    short p4 = 0;
    WorldCoord p5 = 0;
    r["ret"] = (bool)(gSDK->GetRoofAttributes(p0, p1, p2, p3, p4, p5));
    r["out"]["genGableWall"] = (bool)(p1!=0);
    r["out"]["bearingInset"] = (double)p2;
    r["out"]["roofThick"] = (double)p3;
    r["out"]["miterType"] = (long long)p4;
    r["out"]["vertMiter"] = (double)p5;
  } },
  { "GetRoofElementType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    Boolean p3 = 0;
    short p4 = 0;
    r["ret"] = (bool)(gSDK->GetRoofElementType(p0, p1, p2, p3, p4));
    r["out"]["edgeIndex"] = (long long)p2;
    r["out"]["isDormer"] = (bool)(p3!=0);
    r["out"]["dormerType"] = (long long)p4;
  } },
  { "GetRRectDiameters", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    WorldCoord p2 = 0;
    gSDK->GetRRectDiameters(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["xDiam"] = (double)p1;
    r["out"]["yDiam"] = (double)p2;
  } },
  { "GetShedAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    double_gs p5 = 0;
    WorldCoord p6 = 0;
    r["ret"] = (bool)(gSDK->GetShedAttributes(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["useHeight"] = (bool)(p2!=0);
    r["out"]["heightDepthValue"] = (double)p3;
    r["out"]["bottomWidth"] = (double)p4;
    r["out"]["topSlope"] = (double)p5;
    r["out"]["overhang"] = (double)p6;
  } },
  { "GetSkylight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    InternalIndex p5 = 0;
    r["ret"] = (bool)(gSDK->GetSkylight(p0, p1, p2, p3, p4, p5));
    r["out"]["edgeIndex"] = (long long)p2;
    r["out"]["cornerOffset"] = (double)p3;
    r["out"]["perpOffset"] = (double)p4;
    r["out"]["symName"] = (long long)p5;
  } },
  { "GetSweepAnglesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    double_gs p2 = 0;
    double_gs p3 = 0;
    gSDK->GetSweepAnglesN(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["startAngle"] = (double)p1;
    r["out"]["arcAngle"] = (double)p2;
    r["out"]["incrAngle"] = (double)p3;
  } },
  { "GetTrapeziumAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    Boolean p5 = 0;
    WorldCoord p6 = 0;
    double_gs p7 = 0;
    double_gs p8 = 0;
    double_gs p9 = 0;
    r["ret"] = (bool)(gSDK->GetTrapeziumAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9));
    r["out"]["useHeight"] = (bool)(p2!=0);
    r["out"]["heightDepthValue"] = (double)p3;
    r["out"]["bottomWidth"] = (double)p4;
    r["out"]["useTopWidth"] = (bool)(p5!=0);
    r["out"]["topWidth"] = (double)p6;
    r["out"]["leftSlope"] = (double)p7;
    r["out"]["rightSlope"] = (double)p8;
    r["out"]["topSlope"] = (double)p9;
  } },
  { "Insert3DVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->Insert3DVertex(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "Moments3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    double_gs p2 = 0;
    double_gs p3 = 0;
    r["ret"] = (bool)(gSDK->Moments3D(p0, p1, p2, p3));
    r["out"]["Ixx"] = (double)p1;
    r["out"]["Iyy"] = (double)p2;
    r["out"]["Izz"] = (double)p3;
  } },
  { "NurbsCurveEvaluatePoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    WorldPt3 p3;
    r["ret"] = (bool)(gSDK->NurbsCurveEvaluatePoint(p0, p1, p2, p3));
    r["out"]["pt"] = MWpt3(p3);
  } },
  { "NurbsCurveGetNumPieces", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->NurbsCurveGetNumPieces(p0));
  } },
  { "NurbsCurveType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = 0;
    r["ret"] = (bool)(gSDK->NurbsCurveType(p0, p1, p2));
    r["out"]["isByWeight"] = (bool)(p2!=0);
  } },
  { "NurbsDegree", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->NurbsDegree(p0, p1));
  } },
  { "NurbsDelVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->NurbsDelVertex(p0, p1, p2));
  } },
  { "NurbsGetNumPts", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->NurbsGetNumPts(p0, p1));
  } },
  { "NurbsGetPt3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    WorldPt3 p3;
    r["ret"] = (bool)(gSDK->NurbsGetPt3D(p0, p1, p2, p3));
    r["out"]["pt"] = MWpt3(p3);
  } },
  { "NurbsGetWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = 0;
    r["ret"] = (bool)(gSDK->NurbsGetWeight(p0, p1, p2, p3));
    r["out"]["weight"] = (double)p3;
  } },
  { "NurbsKnot", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = 0;
    r["ret"] = (bool)(gSDK->NurbsKnot(p0, p1, p2, p3));
    r["out"]["knot"] = (double)p3;
  } },
  { "NurbsNumKnots", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->NurbsNumKnots(p0, p1));
  } },
  { "NurbsSetKnot", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (bool)(gSDK->NurbsSetKnot(p0, p1, p2, p3));
  } },
  { "NurbsSetPt3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    WorldPt3 p3 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->NurbsSetPt3D(p0, p1, p2, p3));
  } },
  { "NurbsSetWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (bool)(gSDK->NurbsSetWeight(p0, p1, p2, p3));
  } },
  { "NurbsSurfaceEvaluatePoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    WorldPt3 p3;
    r["ret"] = (bool)(gSDK->NurbsSurfaceEvaluatePoint(p0, p1, p2, p3));
    r["out"]["pt"] = MWpt3(p3);
  } },
  { "ObjArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->ObjArea(p0));
  } },
  { "ObjSurfaceArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->ObjSurfaceArea(p0));
  } },
  { "ObjVolume", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->ObjVolume(p0));
  } },
  { "Products3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    double_gs p2 = 0;
    double_gs p3 = 0;
    r["ret"] = (bool)(gSDK->Products3D(p0, p1, p2, p3));
    r["out"]["Ixy"] = (double)p1;
    r["out"]["Iyz"] = (double)p2;
    r["out"]["Izx"] = (double)p3;
  } },
  { "RemoveRoofElement", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->RemoveRoofElement(p0, p1); r["ret"]=nullptr;
  } },
  { "Set3DVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    bool p3 = JBool(a,i);
    gSDK->Set3DVertex(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetArcAnglesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->SetArcAnglesN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetBatAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    double p6 = JReal(a,i);
    double p7 = JReal(a,i);
    double p8 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetBatAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8));
  } },
  { "SetDormerAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    bool p4 = JBool(a,i);
    double p5 = JReal(a,i);
    long long p6 = JInt(a,i);
    bool p7 = JBool(a,i);
    double p8 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetDormerAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8));
  } },
  { "SetDormerThick", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->SetDormerThick(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetEndPoints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2 = JWpt(a,i);
    gSDK->SetEndPoints(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetExtrudeValues", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->SetExtrudeValues(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetGableAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    double p6 = JReal(a,i);
    double p7 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetGableAttributes(p0, p1, p2, p3, p4, p5, p6, p7));
  } },
  { "SetHipAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    double p6 = JReal(a,i);
    double p7 = JReal(a,i);
    double p8 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetHipAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8));
  } },
  { "SetLocus3DPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    gSDK->SetLocus3DPosition(p0, p1); r["ret"]=nullptr;
  } },
  { "SetLocusPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    gSDK->SetLocusPosition(p0, p1); r["ret"]=nullptr;
  } },
  { "SetObjectBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldRect p1 = JWrect(a,i);
    gSDK->SetObjectBounds(p0, p1); r["ret"]=nullptr;
  } },
  { "SetPolyShapeClose", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetPolyShapeClose(p0, p1); r["ret"]=nullptr;
  } },
  { "SetQArcQuadrant", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetQArcQuadrant(p0, p1); r["ret"]=nullptr;
  } },
  { "SetRoofAccessoriesParameters", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    double p6 = JReal(a,i);
    double p7 = JReal(a,i);
    double p8 = JReal(a,i);
    double p9 = JReal(a,i);
    gSDK->SetRoofAccessoriesParameters(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); r["ret"]=nullptr;
  } },
  { "SetRoofAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    long long p4 = JInt(a,i);
    double p5 = JReal(a,i);
    gSDK->SetRoofAttributes(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "SetRRectDiameters", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->SetRRectDiameters(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetShedAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    double p6 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetShedAttributes(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "SetSkylight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetSkylight(p0, p1, p2, p3, p4, p5));
  } },
  { "SetSweepAnglesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    gSDK->SetSweepAnglesN(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetSweepScrew", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetSweepScrew(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTrapeziumAttributes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    bool p5 = JBool(a,i);
    double p6 = JReal(a,i);
    double p7 = JReal(a,i);
    double p8 = JReal(a,i);
    double p9 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetTrapeziumAttributes(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9));
  } },
  { "WrapGetSweepScrew", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    gSDK->WrapGetSweepScrew(p0, p1); r["ret"]=nullptr;
    r["out"]["outCoordLen"] = (double)p1;
  } },
  { "CreateCircularDimension", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    WorldRect p4 = JWrect(a,i);
    bool p5 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateCircularDimension(p0, p1, p2, p3, p4, p5);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetArrowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetArrowByClass(p0));
  } },
  { "GetDefaultOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetDefaultOpacityByClass());
  } },
  { "GetFColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetFColorsByClass(p0));
  } },
  { "GetFillIAxisEndPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->GetFillIAxisEndPoint(p0, p1));
    r["out"]["iAxisEndPoint"] = MWpt(p1);
  } },
  { "GetFillJAxisEndPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->GetFillJAxisEndPoint(p0, p1));
    r["out"]["jAxisEndPoint"] = MWpt(p1);
  } },
  { "GetFillOriginPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->GetFillOriginPoint(p0, p1));
    r["out"]["originPoint"] = MWpt(p1);
  } },
  { "GetFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetFillPat(p0));
  } },
  { "GetFillPoints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    WorldPt p2;
    WorldPt p3;
    r["ret"] = (bool)(gSDK->GetFillPoints(p0, p1, p2, p3));
    r["out"]["originPoint"] = MWpt(p1);
    r["out"]["iAxisEndPoint"] = MWpt(p2);
    r["out"]["jAxisEndPoint"] = MWpt(p3);
  } },
  { "GetFPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetFPatByClass(p0));
  } },
  { "GetLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetLineWeight(p0));
  } },
  { "GetLineWeightDisplayMM", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetLineWeightDisplayMM(p0));
  } },
  { "GetLineWeightDisplayPt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetLineWeightDisplayPt(p0));
  } },
  { "GetLWByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetLWByClass(p0));
  } },
  { "GetOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetOpacityByClass(p0));
  } },
  { "GetPColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetPColorsByClass(p0));
  } },
  { "GetPPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetPPatByClass(p0));
  } },
  { "GetVertexVis", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    gSDK->GetVertexVis(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["vis"] = (bool)(p2!=0);
  } },
  { "SetArrowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetArrowByClass(p0); r["ret"]=nullptr;
  } },
  { "SetDefaultOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetDefaultOpacityByClass(); r["ret"]=nullptr;
  } },
  { "SetFColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetFColorsByClass(p0); r["ret"]=nullptr;
  } },
  { "SetFillIAxisEndPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetFillIAxisEndPoint(p0, p1));
  } },
  { "SetFillJAxisEndPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetFillJAxisEndPoint(p0, p1));
  } },
  { "SetFillOriginPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetFillOriginPoint(p0, p1));
  } },
  { "SetFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetFillPat(p0, p1); r["ret"]=nullptr;
  } },
  { "SetFPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetFPatByClass(p0); r["ret"]=nullptr;
  } },
  { "SetLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetLineWeight(p0, p1); r["ret"]=nullptr;
  } },
  { "SetLineWeightDisplayMM", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetLineWeightDisplayMM(p0));
  } },
  { "SetLineWeightDisplayPt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetLineWeightDisplayPt(p0));
  } },
  { "SetLWByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetLWByClass(p0); r["ret"]=nullptr;
  } },
  { "SetOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetOpacityByClass(p0); r["ret"]=nullptr;
  } },
  { "SetPColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetPColorsByClass(p0); r["ret"]=nullptr;
  } },
  { "SetPPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetPPatByClass(p0); r["ret"]=nullptr;
  } },
  { "SetVertexVis", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetVertexVis(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetDefinition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetDefinition(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDXFColorToLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetDXFColorToLineWeight(p0));
  } },
  { "GetNamedObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->GetNamedObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetObjectClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetObjectClass(p0));
  } },
  { "GetObjectName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    gSDK->GetObjectName(p0, p1); r["ret"]=nullptr;
    r["out"]["outName"] = MStr(p1);
  } },
  { "GetSymbolDefinitionType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetSymbolDefinitionType(p0));
  } },
  { "IsLocked", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsLocked(p0));
  } },
  { "IsSelected", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsSelected(p0));
  } },
  { "LockObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->LockObject(p0, p1); r["ret"]=nullptr;
  } },
  { "SelectObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SelectObject(p0, p1); r["ret"]=nullptr;
  } },
  { "SetDXFColorToLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetDXFColorToLineWeight(p0, p1); r["ret"]=nullptr;
  } },
  { "SetObjectClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetObjectClass(p0, p1); r["ret"]=nullptr;
  } },
  { "SetVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetVisibility(p0, p1); r["ret"]=nullptr;
  } },
  { "AttachAuxObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->AttachAuxObject(p0, p1); r["ret"]=nullptr;
  } },
  { "DeleteAuxObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->DeleteAuxObject(p0, p1); r["ret"]=nullptr;
  } },
  { "FindAuxObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->FindAuxObject(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "FirstAuxObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->FirstAuxObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsPluginFormat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsPluginFormat(p0));
  } },
  { "NextAuxObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->NextAuxObject(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "RemoveAuxObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->RemoveAuxObject(p0, p1); r["ret"]=nullptr;
  } },
  { "CoordLengthToPageLengthN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    r["ret"] = (double)(gSDK->CoordLengthToPageLengthN(p0));
  } },
  { "CoordLengthToPagePoints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    r["ret"] = (double)(gSDK->CoordLengthToPagePoints(p0));
  } },
  { "CoordLengthToPixelLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    short p1 = 0;
    r["ret"] = (bool)(gSDK->CoordLengthToPixelLength(p0, p1));
    r["out"]["numPixels"] = (long long)p1;
  } },
  { "CoordLengthToUnitsLengthN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    r["ret"] = (double)(gSDK->CoordLengthToUnitsLengthN(p0));
  } },
  { "DimStringToCoord", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    WorldCoord p1 = 0;
    r["ret"] = (bool)(gSDK->DimStringToCoord(p0, p1));
    r["out"]["c"] = (double)p1;
  } },
  { "FPCoordLengthToPageLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double_gs p1 = 0;
    gSDK->FPCoordLengthToPageLength(p0, p1); r["ret"]=nullptr;
    r["out"]["pageLen"] = (double)p1;
  } },
  { "FPCoordLengthToUnitsLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double_gs p1 = 0;
    gSDK->FPCoordLengthToUnitsLength(p0, p1); r["ret"]=nullptr;
    r["out"]["unitsLen"] = (double)p1;
  } },
  { "ModelPt2DToScreenPt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    gSDK->ModelPt2DToScreenPt(p0); r["ret"]=nullptr;
    r["out"]["vertex"] = MWpt(p0);
  } },
  { "ModelVecToScreenVec", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    gSDK->ModelVecToScreenVec(p0); r["ret"]=nullptr;
    r["out"]["vertex"] = MWpt(p0);
  } },
  { "PageLengthToFPCoordLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double_gs p1 = 0;
    gSDK->PageLengthToFPCoordLength(p0, p1); r["ret"]=nullptr;
    r["out"]["coordLen"] = (double)p1;
  } },
  { "PagePointsToCoordLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double_gs p0 = 0;
    r["ret"] = (double)(gSDK->PagePointsToCoordLength(p0));
    r["out"]["points"] = (double)p0;
  } },
  { "PixelLengthToCoordLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldCoord p1 = 0;
    gSDK->PixelLengthToCoordLength(p0, p1); r["ret"]=nullptr;
    r["out"]["numCoords"] = (double)p1;
  } },
  { "ScreenPtToModelPt2D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    gSDK->ScreenPtToModelPt2D(p0); r["ret"]=nullptr;
    r["out"]["vertex"] = MWpt(p0);
  } },
  { "ScreenVecToModelVec", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    gSDK->ScreenVecToModelVec(p0); r["ret"]=nullptr;
    r["out"]["vertex"] = MWpt(p0);
  } },
  { "UnitsLengthToFPCoordLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double_gs p1 = 0;
    gSDK->UnitsLengthToFPCoordLength(p0, p1); r["ret"]=nullptr;
    r["out"]["coordLen"] = (double)p1;
  } },
  { "WorldCoordsPerDrawingUnit", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (double)(gSDK->WorldCoordsPerDrawingUnit());
  } },
  { "WrapPageLengthToCoordLengthN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double_gs p1 = 0;
    gSDK->WrapPageLengthToCoordLengthN(p0, p1); r["ret"]=nullptr;
    r["out"]["outCoordLen"] = (double)p1;
  } },
  { "WrapUnitsLengthToCoordLengthN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double_gs p1 = 0;
    gSDK->WrapUnitsLengthToCoordLengthN(p0, p1); r["ret"]=nullptr;
    r["out"]["outCoordLen"] = (double)p1;
  } },
  { "AppendRoofEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    r["ret"] = (bool)(gSDK->AppendRoofEdge(p0, p1, p2, p3, p4));
  } },
  { "Create3DPoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->Create3DPoly();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateAngleDimension", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateAngleDimension(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateArcN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateArcN(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateBatDormer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CreateBatDormer(p0));
  } },
  { "CreateChainDimension", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateChainDimension(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateCombineIntoSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    MCObjectHandle rh = gSDK->CreateCombineIntoSurface(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateCone", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateCone(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateContourCurves", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    WorldPt3 p3 = JWpt3(a,i);
    MCObjectHandle rh = gSDK->CreateContourCurves(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateCustomDimensionStandard", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateCustomDimensionStandard(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateCustomObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    bool p3 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateCustomObject(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateCustomObjectDoubleClick", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateCustomObjectDoubleClick(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateCustomObjectPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    bool p3 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateCustomObjectPath(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateExtrude", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateExtrude(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateExtrudeAlongPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateExtrudeAlongPath(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateGableDormer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CreateGableDormer(p0));
  } },
  { "CreateGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateHemisphere", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    MCObjectHandle rh = gSDK->CreateHemisphere(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateHipDormer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CreateHipDormer(p0));
  } },
  { "CreateImageProp", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    bool p6 = JBool(a,i);
    bool p7 = JBool(a,i);
    bool p8 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateImageProp(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
    r["out"]["propName"] = MStr(p0);
  } },
  { "CreateInterpolatedSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateInterpolatedSurface(p0, p1, p2, p3, p4);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateLayer(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLayerN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    double p1 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateLayerN(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLightN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    WorldPt3 p4 = JWpt3(a,i);
    bool p5 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateLightN(p0, p1, p2, p3, p4, p5);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLine", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    MCObjectHandle rh = gSDK->CreateLine(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLocus", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateLocus(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLocus3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    MCObjectHandle rh = gSDK->CreateLocus3D(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateLoftSurfaces", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateLoftSurfaces(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateNurbsCurve", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    bool p1 = JBool(a,i);
    long long p2 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateNurbsCurve(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateNurbsSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateNurbsSurface(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateOval", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    MCObjectHandle rh = gSDK->CreateOval(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreatePolyshape", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->CreatePolyshape();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateQArc", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateQArc(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateRectangle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    MCObjectHandle rh = gSDK->CreateRectangle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateRoof", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    long long p3 = JInt(a,i);
    double p4 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateRoof(p0, p1, p2, p3, p4);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateRoundWall", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateRoundWall(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateRRectangle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateRRectangle(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateShedDormer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CreateShedDormer(p0));
  } },
  { "CreateBasicSlab", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateBasicSlab(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateSphere", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    double p1 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateSphere(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateStaticHatch", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateStaticHatch(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateStaticHatchFromObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateStaticHatchFromObject(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateSurfacefromCurvesNetwork", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->CreateSurfacefromCurvesNetwork());
  } },
  { "CreateSweepN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateSweepN(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateSymbolDefinition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    MCObjectHandle rh = gSDK->CreateSymbolDefinition(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
    r["out"]["inoutName"] = MStr(p0);
  } },
  { "CreateSymbolFolder", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateSymbolFolder(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateTaperedExtrude", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateTaperedExtrude(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateTrapeziumDormer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CreateTrapeziumDormer(p0));
  } },
  { "CreateViewport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateViewport(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateWall", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateWall(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DuplicateSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    gSDK->DuplicateSelection(p0, p1); r["ret"]=nullptr;
  } },
  { "ExtendNurbsCurve", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    MCObjectHandle rh = gSDK->ExtendNurbsCurve(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ExtendNurbsSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    MCObjectHandle rh = gSDK->ExtendNurbsSurface(p0, p1, p2, p3, p4);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GroupSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GroupSelection();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PlaceSymbolByNameN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->PlaceSymbolByNameN(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PlaceSymbolN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->PlaceSymbolN(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "RevolveWithRail", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    MCObjectHandle rh = gSDK->RevolveWithRail(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    gSDK->AddChoice(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "AddListBoxTabStop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->AddListBoxTabStop(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "AdjustComponentPixelPos", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->AdjustComponentPixelPos(p0, p1, p2, p3, p4));
  } },
  { "AlertCritical", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    gSDK->AlertCritical(p0, p1); r["ret"]=nullptr;
  } },
  { "AlertInform", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    bool p2 = JBool(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    gSDK->AlertInform(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "AlertQuestion", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    TXString p6 = JStr(a,i);
    TXString p7 = JStr(a,i);
    TXString p8 = JStr(a,i);
    TXString p9 = JStr(a,i);
    r["ret"] = (long long)(gSDK->AlertQuestion(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9));
  } },
  { "AlignBottomEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AlignBottomEdge(p0, p1, p2, p3));
  } },
  { "AlignLeftEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AlignLeftEdge(p0, p1, p2, p3));
  } },
  { "AlignRightEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AlignRightEdge(p0, p1, p2, p3));
  } },
  { "AreListBrowserColumnLinesEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AreListBrowserColumnLinesEnabled(p0, p1));
  } },
  { "AreListBrowserRadioColumnLinesEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AreListBrowserRadioColumnLinesEnabled(p0, p1, p2));
  } },
  { "ClearGradientSliderSegments", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->ClearGradientSliderSegments(p0, p1));
  } },
  { "Confirm", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->Confirm(p0, p1));
  } },
  { "CreateCenteredStaticText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateCenteredStaticText(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateCheckBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->CreateCheckBox(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateCheckBoxGroupBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    bool p3 = JBool(a,i);
    gSDK->CreateCheckBoxGroupBox(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateClassPullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateClassPullDownMenu(p0, p1, p2));
  } },
  { "CreateCMYKColorSwatch", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateCMYKColorSwatch(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateColorPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->CreateColorPopup(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateCustomControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateCustomControl(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateDesignLayerPullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateDesignLayerPullDownMenu(p0, p1, p2));
  } },
  { "CreateEditInteger", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateEditInteger(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateEditReal", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    long long p4 = JInt(a,i);
    gSDK->CreateEditReal(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "CreateEditText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    gSDK->CreateEditText(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "CreateEnhancedPullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateEnhancedPullDownMenu(p0, p1, p2, p3));
  } },
  { "CreateGroupBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    bool p3 = JBool(a,i);
    gSDK->CreateGroupBox(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateIconPushButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateIconPushButton(p0, p1, p2, p3));
  } },
  { "CreateImageControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    MCObjectHandle p4 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->CreateImageControl(p0, p1, p2, p3, p4));
  } },
  { "CreateLayout", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (long long)(gSDK->CreateLayout(p0, p1, p2, p3));
  } },
  { "CreateLineAttributePopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateLineAttributePopup(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateLineStylePopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateLineStylePopup(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateLineWeightPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateLineWeightPopup(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateListBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateListBox(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateListBoxN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    gSDK->CreateListBoxN(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "CreateListBrowser", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateListBrowser(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateMarkerPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateMarkerPopup(p0, p1); r["ret"]=nullptr;
  } },
  { "CreatePatternPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreatePatternPopup(p0, p1); r["ret"]=nullptr;
  } },
  { "CreatePullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->CreatePullDownMenu(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreatePullDownMenuGroupBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreatePullDownMenuGroupBox(p0, p1, p2, p3, p4));
  } },
  { "CreatePushButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->CreatePushButton(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateRadioButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->CreateRadioButton(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateRadioButtonGroupBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    bool p3 = JBool(a,i);
    gSDK->CreateRadioButtonGroupBox(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateResizableLayout", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    r["ret"] = (long long)(gSDK->CreateResizableLayout(p0, p1, p2, p3, p4, p5));
  } },
  { "CreateRightStaticText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateRightStaticText(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateSeparator", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateSeparator(p0, p1, p2));
  } },
  { "CreateSheetLayerPullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateSheetLayerPullDownMenu(p0, p1, p2));
  } },
  { "CreateStandardIconControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->CreateStandardIconControl(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateStaticText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateStaticText(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateSwapControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateSwapControl(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateSwapPane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->CreateSwapPane(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateTabControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CreateTabControl(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateTabPane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->CreateTabPane(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateThreeStateCheckBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->CreateThreeStateCheckBox(p0, p1, p2));
  } },
  { "CreateTreeControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateTreeControl(p0, p1, p2, p3));
  } },
  { "DeleteAllItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeleteAllItems(p0, p1); r["ret"]=nullptr;
  } },
  { "DeleteAllListBrowserItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteAllListBrowserItems(p0, p1));
  } },
  { "DeleteListBrowserColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteListBrowserColumn(p0, p1, p2));
  } },
  { "DeleteListBrowserItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteListBrowserItem(p0, p1, p2));
  } },
  { "DeselectEditText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeselectEditText(p0, p1); r["ret"]=nullptr;
  } },
  { "DisplaySwapPane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->DisplaySwapPane(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "DisplayTabPane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->DisplayTabPane(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "EnableItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->EnableItem(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "EnableListBrowser", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableListBrowser(p0, p1, p2));
  } },
  { "EnableListBrowserClickAllDataChange", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableListBrowserClickAllDataChange(p0, p1, p2));
  } },
  { "EnableListBrowserColumnLines", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->EnableListBrowserColumnLines(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "EnableListBrowserColumnTracking", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->EnableListBrowserColumnTracking(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "EnableListBrowserDragAndDrop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableListBrowserDragAndDrop(p0, p1, p2));
  } },
  { "EnableListBrowserDropOnIndices", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableListBrowserDropOnIndices(p0, p1, p2, p3, p4));
  } },
  { "EnableListBrowserRadioColumnLines", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->EnableListBrowserRadioColumnLines(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "EnableListBrowserSingleLineSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableListBrowserSingleLineSelection(p0, p1, p2));
  } },
  { "EnableListBrowserSorting", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->EnableListBrowserSorting(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "EnableListBrowserUpdates", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableListBrowserUpdates(p0, p1, p2));
  } },
  { "EnsureListBrowserItemIsVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->EnsureListBrowserItemIsVisible(p0, p1, p2));
  } },
  { "ExpandTreeControlItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ExpandTreeControlItem(p0, p1, p2, p3));
  } },
  { "FindListBrowserColumnDataItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    short p4 = 0;
    r["ret"] = (bool)(gSDK->FindListBrowserColumnDataItem(p0, p1, p2, p3, p4));
    r["out"]["columnDataItemIndex"] = (long long)p4;
  } },
  { "FindListBrowserColumnItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    short p4 = 0;
    r["ret"] = (bool)(gSDK->FindListBrowserColumnItem(p0, p1, p2, p3, p4));
    r["out"]["itemIndex"] = (long long)p4;
  } },
  { "GetActiveEditItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetActiveEditItem(p0));
  } },
  { "GetActivePane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetActivePane(p0, p1));
  } },
  { "GetBooleanItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    gSDK->GetBooleanItem(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["state"] = (bool)(p2!=0);
  } },
  { "GetChoiceCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetChoiceCount(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["numItems"] = (long long)p2;
  } },
  { "GetChoiceIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    short p3 = 0;
    gSDK->GetChoiceIndex(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["nItemIndex"] = (long long)p3;
  } },
  { "GetChoiceText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3;
    gSDK->GetChoiceText(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["outItemText"] = MStr(p3);
  } },
  { "GetColorChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetColorChoice(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["colorIndex"] = (long long)p2;
  } },
  { "GetComponentTextWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentTextWidth(p0, p1, p2));
    r["out"]["nWidthInLMUnits"] = (long long)p2;
  } },
  { "GetEditInteger", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetEditInteger(p0, p1, p2));
    r["out"]["value"] = (long long)p2;
  } },
  { "GetEditReal", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = 0;
    r["ret"] = (bool)(gSDK->GetEditReal(p0, p1, p2, p3));
    r["out"]["value"] = (double)p3;
  } },
  { "GetGradientSliderData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = 0;
    double p4 = 0;
    WorldPt3 p5;
    r["ret"] = (bool)(gSDK->GetGradientSliderData(p0, p1, p2, p3, p4, p5));
    r["out"]["spotPosition"] = (double)p3;
    r["out"]["midpointPosition"] = (double)p4;
    r["out"]["color"] = MWpt3(p5);
  } },
  { "GetGradientSliderSelectedMarker", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    short p3 = 0;
    r["ret"] = (bool)(gSDK->GetGradientSliderSelectedMarker(p0, p1, p2, p3));
    r["out"]["segmentIndex"] = (long long)p2;
    r["out"]["markerType"] = (long long)p3;
  } },
  { "GetIconPushButtonState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetIconPushButtonState(p0, p1, p2));
    r["out"]["bPressed"] = (bool)(p2!=0);
  } },
  { "GetImagePopupObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetImagePopupObject(p0, p1, p2));
  } },
  { "GetImagePopupObjectItemIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetImagePopupObjectItemIndex(p0, p1, p2));
  } },
  { "GetImagePopupSelectedItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetImagePopupSelectedItem(p0, p1));
  } },
  { "GetItemText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2;
    gSDK->GetItemText(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["outCurrentText"] = MStr(p2);
  } },
  { "GetLayoutDialogPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    short p1 = 0;
    short p2 = 0;
    short p3 = 0;
    short p4 = 0;
    r["ret"] = (bool)(gSDK->GetLayoutDialogPosition(p0, p1, p2, p3, p4));
    r["out"]["left"] = (long long)p1;
    r["out"]["top"] = (long long)p2;
    r["out"]["right"] = (long long)p3;
    r["out"]["bottom"] = (long long)p4;
  } },
  { "GetLayoutDialogSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    short p1 = 0;
    short p2 = 0;
    gSDK->GetLayoutDialogSize(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["width"] = (long long)p1;
    r["out"]["height"] = (long long)p2;
  } },
  { "GetLineWeightChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetLineWeightChoice(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["lineWeight"] = (long long)p2;
  } },
  { "GetListBrowserColumnWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    short p3 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserColumnWidth(p0, p1, p2, p3));
    r["out"]["width"] = (long long)p3;
  } },
  { "GetListBrowserColumnDataItemInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4;
    short p5 = 0;
    short p6 = 0;
    Sint32 p7 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserColumnDataItemInfo(p0, p1, p2, p3, p4, p5, p6, p7));
    r["out"]["itemString"] = MStr(p4);
    r["out"]["imageOn"] = (long long)p5;
    r["out"]["imageOff"] = (long long)p6;
    r["out"]["itemData"] = (long long)p7;
  } },
  { "GetListBrowserColumnSortState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetListBrowserColumnSortState(p0, p1, p2));
  } },
  { "GetListBrowserColumnOwnerDrawnType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserColumnOwnerDrawnType(p0, p1, p2, p3, p4));
    r["out"]["iOwnerDrawnType"] = (long long)p4;
  } },
  { "GetListBrowserColumnHeaderToolTip", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3;
    TXString p4;
    r["ret"] = (bool)(gSDK->GetListBrowserColumnHeaderToolTip(p0, p1, p2, p3, p4));
    r["out"]["strToolTipPrimaryText"] = MStr(p3);
    r["out"]["strToolTipSubText"] = MStr(p4);
  } },
  { "GetListBrowserColumnHeaderJust", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    Sint32 p3 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserColumnHeaderJust(p0, p1, p2, p3));
    r["out"]["iJustification"] = (long long)p3;
  } },
  { "GetListBrowserControlType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetListBrowserControlType(p0, p1, p2));
  } },
  { "GetListBrowserEditDisplayType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetListBrowserEditDisplayType(p0, p1, p2));
  } },
  { "GetListBrowserEventInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    Sint32 p3 = 0;
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserEventInfo(p0, p1, p2, p3, p4));
    r["out"]["iEventType"] = (long long)p2;
    r["out"]["iRowIndex"] = (long long)p3;
    r["out"]["iColumnIndex"] = (long long)p4;
  } },
  { "GetListBrowserItemData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemData(p0, p1, p2, p3, p4));
    r["out"]["nUserData"] = (long long)p4;
  } },
  { "GetListBrowserItemDisplayType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetListBrowserItemDisplayType(p0, p1, p2));
  } },
  { "HasListBrowserItemFillForeColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->HasListBrowserItemFillForeColor(p0, p1, p2, p3, p4));
    r["out"]["hasColor"] = (bool)(p4!=0);
  } },
  { "GetListBrowserItemFillForeColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    Sint32 p5 = 0;
    Sint32 p6 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemFillForeColor(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["iRedIndex"] = (long long)p4;
    r["out"]["iGreenIndex"] = (long long)p5;
    r["out"]["iBlueIndex"] = (long long)p6;
  } },
  { "HasListBrowserItemFillBackColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->HasListBrowserItemFillBackColor(p0, p1, p2, p3, p4));
    r["out"]["hasColor"] = (bool)(p4!=0);
  } },
  { "GetListBrowserItemFillBackColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    Sint32 p5 = 0;
    Sint32 p6 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemFillBackColor(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["iRedIndex"] = (long long)p4;
    r["out"]["iGreenIndex"] = (long long)p5;
    r["out"]["iBlueIndex"] = (long long)p6;
  } },
  { "GetListBrowserItemGradientOrImageRefNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemGradientOrImageRefNumber(p0, p1, p2, p3, p4));
    r["out"]["liRefNumber"] = (long long)p4;
  } },
  { "GetListBrowserItemInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4;
    short p5 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemInfo(p0, p1, p2, p3, p4, p5));
    r["out"]["itemString"] = MStr(p4);
    r["out"]["imageIndex"] = (long long)p5;
  } },
  { "HasListBrowserItemPenForeColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->HasListBrowserItemPenForeColor(p0, p1, p2, p3, p4));
    r["out"]["hasColor"] = (bool)(p4!=0);
  } },
  { "GetListBrowserItemPenForeColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    Sint32 p5 = 0;
    Sint32 p6 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemPenForeColor(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["iRedIndex"] = (long long)p4;
    r["out"]["iGreenIndex"] = (long long)p5;
    r["out"]["iBlueIndex"] = (long long)p6;
  } },
  { "HasListBrowserItemPenBackColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->HasListBrowserItemPenBackColor(p0, p1, p2, p3, p4));
    r["out"]["hasColor"] = (bool)(p4!=0);
  } },
  { "GetListBrowserItemPenBackColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    Sint32 p5 = 0;
    Sint32 p6 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemPenBackColor(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["iRedIndex"] = (long long)p4;
    r["out"]["iGreenIndex"] = (long long)p5;
    r["out"]["iBlueIndex"] = (long long)p6;
  } },
  { "GetListBrowserItemTextJust", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemTextJust(p0, p1, p2, p3, p4));
    r["out"]["justification"] = (long long)p4;
  } },
  { "HasListBrowserItemTextColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->HasListBrowserItemTextColor(p0, p1, p2, p3, p4));
    r["out"]["hasColor"] = (bool)(p4!=0);
  } },
  { "GetListBrowserItemTextColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    Sint32 p5 = 0;
    Sint32 p6 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemTextColor(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["redIndex"] = (long long)p4;
    r["out"]["greenIndex"] = (long long)p5;
    r["out"]["blueIndex"] = (long long)p6;
  } },
  { "GetListBrowserSortColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetListBrowserSortColumn(p0, p1));
  } },
  { "GetNumGradientSliderSegments", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumGradientSliderSegments(p0, p1));
  } },
  { "GetNumImagePopupItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumImagePopupItems(p0, p1));
  } },
  { "GetNumListBrowserColumns", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumListBrowserColumns(p0, p1));
  } },
  { "GetNumListBrowserColumnDataItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumListBrowserColumnDataItems(p0, p1, p2));
  } },
  { "GetNumListBrowserItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumListBrowserItems(p0, p1));
  } },
  { "GetNumSelectedListBrowserItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumSelectedListBrowserItems(p0, p1));
  } },
  { "GetPatternData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    short p3 = 0;
    short p4 = 0;
    gSDK->GetPatternData(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["patternIndex"] = (long long)p2;
    r["out"]["foreColor"] = (long long)p3;
    r["out"]["backColor"] = (long long)p4;
  } },
  { "GetSelChoiceIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    short p3 = 0;
    gSDK->GetSelChoiceIndex(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["outSelectedIndex"] = (long long)p3;
  } },
  { "GetSelectedChoiceIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetSelectedChoiceIndex(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["nItemIndex"] = (long long)p2;
  } },
  { "GetSelectionRange", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    Sint32 p3 = 0;
    gSDK->GetSelectionRange(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["startPos"] = (long long)p2;
    r["out"]["endPos"] = (long long)p3;
  } },
  { "GetThreeStateCheckBoxState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetThreeStateCheckBoxState(p0, p1, p2));
    r["out"]["iState"] = (long long)p2;
  } },
  { "GetTreeControlSelectedItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetTreeControlSelectedItem(p0, p1, p2));
    r["out"]["nItemID"] = (long long)p2;
  } },
  { "InsertGradientSliderSegment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    WorldPt3 p3 = JWpt3(a,i);
    r["ret"] = (long long)(gSDK->InsertGradientSliderSegment(p0, p1, p2, p3));
  } },
  { "InsertImagePopupObjectItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->InsertImagePopupObjectItem(p0, p1, p2));
  } },
  { "InsertImagePopupResource", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (long long)(gSDK->InsertImagePopupResource(p0, p1, p2, p3));
  } },
  { "InsertImagePopupSeparator", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (long long)(gSDK->InsertImagePopupSeparator(p0, p1, p2));
  } },
  { "InsertListBrowserColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (long long)(gSDK->InsertListBrowserColumn(p0, p1, p2, p3, p4));
  } },
  { "InsertListBrowserColumnDataItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (long long)(gSDK->InsertListBrowserColumnDataItem(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "InsertListBrowserItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (long long)(gSDK->InsertListBrowserItem(p0, p1, p2, p3));
  } },
  { "InsertTreeControlItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (long long)(gSDK->InsertTreeControlItem(p0, p1, p2, p3, p4));
  } },
  { "IsItemEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsItemEnabled(p0, p1));
  } },
  { "IsItemVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsItemVisible(p0, p1));
  } },
  { "IsListBrowserColumnTrackingEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserColumnTrackingEnabled(p0, p1, p2));
  } },
  { "IsListBrowserItemSelected", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserItemSelected(p0, p1, p2));
  } },
  { "IsListBrowserSortingEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserSortingEnabled(p0, p1));
  } },
  { "GetListBrowserItemCheckState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    int p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemCheckState(p0, p1, p2, p3, p4));
    r["out"]["iState"] = (long long)p4;
  } },
  { "SetListBrowserItemCheckState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemCheckState(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserReadOnly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetListBrowserReadOnly(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "IsListBrowserReadOnly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserReadOnly(p0, p1));
  } },
  { "SetListBrowserItemReadOnly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    gSDK->SetListBrowserItemReadOnly(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "IsListBrowserItemReadOnly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserItemReadOnly(p0, p1, p2, p3));
  } },
  { "NotifyPullDownClicked", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->NotifyPullDownClicked(p0, p1));
  } },
  { "PostMinorNoteAlert", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->PostMinorNoteAlert(p0); r["ret"]=nullptr;
  } },
  { "PostMinorStopAlert", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->PostMinorStopAlert(p0); r["ret"]=nullptr;
  } },
  { "PostNoteAlert", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->PostNoteAlert(p0); r["ret"]=nullptr;
  } },
  { "PostStopAlert", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->PostStopAlert(p0); r["ret"]=nullptr;
  } },
  { "RefreshItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RefreshItem(p0, p1));
  } },
  { "RefreshListBrowser", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RefreshListBrowser(p0, p1));
  } },
  { "RemoveAllImagePopupItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveAllImagePopupItems(p0, p1));
  } },
  { "RemoveAllListBrowserColumnDataItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->RemoveAllListBrowserColumnDataItems(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "RemoveChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->RemoveChoice(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "RemoveEnhancedPullDownMenuItemRange", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveEnhancedPullDownMenuItemRange(p0, p1, p2, p3));
  } },
  { "RemoveGradientSliderSegment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveGradientSliderSegment(p0, p1, p2));
  } },
  { "RemoveImagePopupItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveImagePopupItem(p0, p1, p2));
  } },
  { "RemoveListBoxTabStop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->RemoveListBoxTabStop(p0, p1); r["ret"]=nullptr;
  } },
  { "RemoveListBrowserColumnDataItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveListBrowserColumnDataItem(p0, p1, p2, p3));
  } },
  { "RemoveTreeControlItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveTreeControlItem(p0, p1, p2));
  } },
  { "SelectChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->SelectChoice(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SelectEditText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SelectEditText(p0, p1); r["ret"]=nullptr;
  } },
  { "SelectTreeControlItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SelectTreeControlItem(p0, p1, p2));
  } },
  { "SetBelowItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetBelowItem(p0, p1, p2, p3, p4));
  } },
  { "SetBooleanItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetBooleanItem(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetColorChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetColorChoice(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetComponentIndeterminate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentIndeterminate(p0, p1, p2));
  } },
  { "SetComponentSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentSize(p0, p1, p2, p3));
  } },
  { "SetEdgeBinding", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    gSDK->SetEdgeBinding(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "SetEditInteger", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetEditInteger(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetEditReal", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    gSDK->SetEditReal(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetFirstGroupItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetFirstGroupItem(p0, p1, p2));
  } },
  { "SetFirstLayoutItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetFirstLayoutItem(p0, p1));
  } },
  { "SetFocusOnItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetFocusOnItem(p0, p1));
  } },
  { "SetFocusOnListBrowser", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetFocusOnListBrowser(p0, p1));
  } },
  { "SetGradientSliderData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    WorldPt3 p5 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->SetGradientSliderData(p0, p1, p2, p3, p4, p5));
    r["out"]["segmentIndex"] = (long long)p2;
  } },
  { "SetGradientSliderSelectedMarker", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetGradientSliderSelectedMarker(p0, p1, p2, p3));
  } },
  { "SetHelpText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->SetHelpText(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetIconPushButtonState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetIconPushButtonState(p0, p1, p2));
  } },
  { "SetImageControlHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetImageControlHandle(p0, p1, p2));
  } },
  { "SetImageControlPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetImageControlPath(p0, p1, p2));
  } },
  { "SetImagePopupSelectedItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetImagePopupSelectedItem(p0, p1, p2));
  } },
  { "SetItemText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->SetItemText(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetItemToolTipText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetItemToolTipText(p0, p1, p2, p3, p4, p5));
  } },
  { "SetLayoutDialogPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetLayoutDialogPosition(p0, p1, p2));
  } },
  { "SetLayoutDialogSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetLayoutDialogSize(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetLayoutOption", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetLayoutOption(p0, p1, p2));
  } },
  { "SetLineWeightChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetLineWeightChoice(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetListBrowserColumnWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserColumnWidth(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserColumnOwnerDrawnType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserColumnOwnerDrawnType(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserColumnHeaderToolTip", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserColumnHeaderToolTip(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserColumnHeaderJust", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserColumnHeaderJust(p0, p1, p2, p3));
  } },
  { "SetListBrowserColumnImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserColumnImage(p0, p1, p2, p3));
  } },
  { "SetListBrowserControlType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserControlType(p0, p1, p2, p3));
  } },
  { "SetListBrowserDragAndDropColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserDragAndDropColumn(p0, p1, p2));
  } },
  { "SetListBrowserEditDisplayType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserEditDisplayType(p0, p1, p2, p3));
  } },
  { "SetListBrowserItemData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemData(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserItemDisplayType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemDisplayType(p0, p1, p2, p3));
  } },
  { "SetListBrowserItemFillForeColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemFillForeColor(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "SetListBrowserItemFillBackColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemFillBackColor(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "SetListBrowserItemGradientOrImageRefNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemGradientOrImageRefNumber(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserItemInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4 = JStr(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemInfo(p0, p1, p2, p3, p4, p5));
  } },
  { "SetListBrowserItemPenForeColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemPenForeColor(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "SetListBrowserItemPenBackColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemPenBackColor(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "SetListBrowserItemTextJust", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemTextJust(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserItemTextColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemTextColor(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "SetListBrowserItemUsingColumnDataItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemUsingColumnDataItem(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserSelection(p0, p1, p2, p3, p4));
  } },
  { "SetListBrowserSortColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->SetListBrowserSortColumn(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetPatternData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    gSDK->SetPatternData(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "SetProportionalBinding", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    gSDK->SetProportionalBinding(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "SetRightItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetRightItem(p0, p1, p2, p3, p4));
  } },
  { "SetSelectionRange", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetSelectionRange(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetTextEditable", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetTextEditable(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetThreeStateCheckBoxState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetThreeStateCheckBoxState(p0, p1, p2));
  } },
  { "SetTreeControlItemData2", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetTreeControlItemData2(p0, p1, p2, p3));
  } },
  { "ShowEnhancedPullDownMenuGroupIcon", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ShowEnhancedPullDownMenuGroupIcon(p0, p1, p2));
  } },
  { "ShowItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->ShowItem(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "UpdateCustomControlScrollArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    bool p7 = JBool(a,i);
    bool p8 = JBool(a,i);
    bool p9 = JBool(a,i);
    gSDK->UpdateCustomControlScrollArea(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); r["ret"]=nullptr;
  } },
  { "VerifyLayout", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->VerifyLayout(p0));
  } },
  { "AddClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (long long)(gSDK->AddClass(p0));
  } },
  { "AddGuidesClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->AddGuidesClass());
  } },
  { "ColorIndexToName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    gSDK->ColorIndexToName(p0, p1); r["ret"]=nullptr;
    r["out"]["outColorName"] = MStr(p1);
  } },
  { "CopySymbol", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->CopySymbol(p0, p1));
  } },
  { "CreateGradient", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateGradient(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateHatch", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    long long p5 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateHatch(p0, p1, p2, p3, p4, p5);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateImageFromPaint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateImageFromPaint(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreatePaintFromImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreatePaintFromImage(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateWallStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateWallStyle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->DeleteClass(p0); r["ret"]=nullptr;
  } },
  { "DeselectAll", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->DeselectAll(); r["ret"]=nullptr;
  } },
  { "GetActiveSymbolDef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetActiveSymbolDef();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetClassVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetClassVisibility(p0));
  } },
  { "GetCurrentLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetCurrentLayer();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetCurrentView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetCurrentView());
  } },
  { "GetDimensionClassID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDimensionClassID());
  } },
  { "GetGradientData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = 0;
    double p3 = 0;
    WorldPt3 p4;
    r["ret"] = (bool)(gSDK->GetGradientData(p0, p1, p2, p3, p4));
    r["out"]["spotPosition"] = (double)p2;
    r["out"]["midpointPosition"] = (double)p3;
    r["out"]["color"] = MWpt3(p4);
  } },
  { "GetGradientMidpointPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = 0;
    r["ret"] = (bool)(gSDK->GetGradientMidpointPosition(p0, p1, p2));
    r["out"]["position"] = (double)p2;
  } },
  { "GetGradientSpotColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2;
    gSDK->GetGradientSpotColor(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["color"] = MWpt3(p2);
  } },
  { "GetGradientSpotPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = 0;
    r["ret"] = (bool)(gSDK->GetGradientSpotPosition(p0, p1, p2));
    r["out"]["position"] = (double)p2;
  } },
  { "GetGridUnits", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldCoord p0 = 0;
    WorldCoord p1 = 0;
    gSDK->GetGridUnits(p0, p1); r["ret"]=nullptr;
    r["out"]["x"] = (double)p0;
    r["out"]["y"] = (double)p1;
  } },
  { "GetHatchLevel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2;
    WorldPt p3;
    double p4 = 0;
    WorldPt p5;
    ColorRef p6 = 0;
    short p7 = 0;
    r["ret"] = (bool)(gSDK->GetHatchLevel(p0, p1, p2, p3, p4, p5, p6, p7));
    r["out"]["outStartPt"] = MWpt(p2);
    r["out"]["outRepeatVec"] = MWpt(p3);
    r["out"]["outDashFactor"] = (double)p4;
    r["out"]["outOffsetVec"] = MWpt(p5);
    r["out"]["outColorIndex"] = (long long)p6;
    r["out"]["outMilsLineWeight"] = (long long)p7;
  } },
  { "GetLayerScaleN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    gSDK->GetLayerScaleN(p0, p1); r["ret"]=nullptr;
    r["out"]["scale"] = (double)p1;
  } },
  { "GetNamedLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->GetNamedLayer(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetNoneClassID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNoneClassID());
  } },
  { "GetNumGradientSegments", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumGradientSegments(p0));
  } },
  { "GetPageBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0;
    gSDK->GetPageBounds(p0); r["ret"]=nullptr;
    r["out"]["bounds"] = MWrect(p0);
  } },
  { "GetSheetLayerUserOrigin", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->GetSheetLayerUserOrigin(p0, p1));
    r["out"]["origin"] = MWpt(p1);
  } },
  { "GetUserOrigin", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    gSDK->GetUserOrigin(p0); r["ret"]=nullptr;
    r["out"]["origin"] = MWpt(p0);
  } },
  { "GetUserOriginFP", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    r["ret"] = (bool)(gSDK->GetUserOriginFP(p0));
    r["out"]["outOrigin"] = MWpt(p0);
  } },
  { "InsertGradientSegment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    WorldPt3 p3 = JWpt3(a,i);
    r["ret"] = (long long)(gSDK->InsertGradientSegment(p0, p1, p2, p3));
  } },
  { "MarkCurrentDocChanged", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->MarkCurrentDocChanged(); r["ret"]=nullptr;
  } },
  { "NumSelectedObjects", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->NumSelectedObjects());
  } },
  { "RemoveGradientSegment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveGradientSegment(p0, p1));
  } },
  { "ResetAllObjectsVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ResetAllObjectsVisibility(); r["ret"]=nullptr;
  } },
  { "SelectAll", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SelectAll(); r["ret"]=nullptr;
  } },
  { "SetActiveSymbolDef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetActiveSymbolDef(p0); r["ret"]=nullptr;
  } },
  { "SetClassVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetClassVisibility(p0, p1); r["ret"]=nullptr;
  } },
  { "SetCurrentLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetCurrentLayer(p0); r["ret"]=nullptr;
  } },
  { "SetGradientData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    WorldPt3 p4 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->SetGradientData(p0, p1, p2, p3, p4));
    r["out"]["segmentIndex"] = (long long)p1;
  } },
  { "SetGradientMidpointPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetGradientMidpointPosition(p0, p1, p2));
  } },
  { "SetGradientSpotColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->SetGradientSpotColor(p0, p1, p2));
  } },
  { "SetGradientSpotPosition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetGradientSpotPosition(p0, p1, p2));
    r["out"]["segmentIndex"] = (long long)p1;
  } },
  { "SetHatchLevel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2 = JWpt(a,i);
    WorldPt p3 = JWpt(a,i);
    double p4 = JReal(a,i);
    WorldPt p5 = JWpt(a,i);
    long long p6 = JInt(a,i);
    long long p7 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetHatchLevel(p0, p1, p2, p3, p4, p5, p6, p7));
  } },
  { "SetLayerScaleN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetLayerScaleN(p0, p1); r["ret"]=nullptr;
  } },
  { "SetProjection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    gSDK->SetProjection(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetRenderMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetRenderMode(p0, p1, p2, p3));
  } },
  { "SetSheetLayerUserOrigin", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetSheetLayerUserOrigin(p0, p1));
  } },
  { "SetUserOrigin", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    gSDK->SetUserOrigin(p0); r["ret"]=nullptr;
  } },
  { "SetUserOriginFP", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetUserOriginFP(p0));
  } },
  { "ShowCreateImageDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->ShowCreateImageDialog();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ValidClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->ValidClass(p0));
  } },
  { "UpdateThumbnailPreview", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->UpdateThumbnailPreview(p0));
  } },
  { "CloseXCode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->CloseXCode(p0); r["ret"]=nullptr;
  } },
  { "AddResourceToList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->AddResourceToList(p0, p1));
  } },
  { "DeleteResourceFromList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeleteResourceFromList(p0, p1); r["ret"]=nullptr;
  } },
  { "DisposeResourceList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->DisposeResourceList(p0); r["ret"]=nullptr;
  } },
  { "GetActualNameFromResourceList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2;
    gSDK->GetActualNameFromResourceList(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["name"] = MStr(p2);
  } },
  { "GetMyMenuCommandIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetMyMenuCommandIndex());
  } },
  { "GetNameFromResourceList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2;
    gSDK->GetNameFromResourceList(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["name"] = MStr(p2);
  } },
  { "GetResourceFromList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetResourceFromList(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ImportResourceToCurrentFile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->ImportResourceToCurrentFile(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ResourceListSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->ResourceListSize(p0));
  } },
  { "AddPullDownMenuItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->AddPullDownMenuItem(p0, p1); r["ret"]=nullptr;
  } },
  { "AddPullDownMenuMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->AddPullDownMenuMode(p0); r["ret"]=nullptr;
  } },
  { "EnableMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    gSDK->EnableMode(p0, p1); r["ret"]=nullptr;
  } },
  { "GetModeValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetModeValue(p0));
  } },
  { "SetHelpString", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->SetHelpString(p0); r["ret"]=nullptr;
  } },
  { "SetModeValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetModeValue(p0, p1); r["ret"]=nullptr;
  } },
  { "SetPullDownMenuSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetPullDownMenuSelection(p0, p1); r["ret"]=nullptr;
  } },
  { "ClassIDToName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    gSDK->ClassIDToName(p0, p1); r["ret"]=nullptr;
    r["out"]["outClassName"] = MStr(p1);
  } },
  { "ClassNameToID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (long long)(gSDK->ClassNameToID(p0));
  } },
  { "InternalIndexToHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle rh = gSDK->InternalIndexToHandle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "InternalIndexToNameN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    gSDK->InternalIndexToNameN(p0, p1); r["ret"]=nullptr;
    r["out"]["outName"] = MStr(p1);
  } },
  { "MaxClassID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->MaxClassID());
  } },
  { "NameToInternalIndexN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    InternalIndex p1 = 0;
    r["ret"] = (bool)(gSDK->NameToInternalIndexN(p0, p1));
    r["out"]["index"] = (long long)p1;
  } },
  { "AddToConstraintModel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->AddToConstraintModel(p0); r["ret"]=nullptr;
  } },
  { "AddViewportAnnotationObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddViewportAnnotationObject(p0, p1));
  } },
  { "AppendParameterWidget", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AppendParameterWidget(p0, p1, p2, p3));
  } },
  { "AppendWidget", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AppendWidget(p0, p1, p2, p3, p4));
  } },
  { "ConvertTo3DPolygons", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->ConvertTo3DPolygons(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ConvertToNURBS", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->ConvertToNURBS(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ConvertToPolygon", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->ConvertToPolygon(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ConvertToPolygonN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    long long p2 = JInt(a,i);
    MCObjectHandle rh = gSDK->ConvertToPolygonN(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ConvertToPolyline", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->ConvertToPolyline(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ConvertToUnstyledWall", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->ConvertToUnstyledWall(p0));
  } },
  { "CreateConstraintModel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->CreateConstraintModel(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateOffsetNurbsObjectHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateOffsetNurbsObjectHandle(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CustomObjectControlPtsRemove", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->CustomObjectControlPtsRemove(p0));
  } },
  { "CustomObjectControlPtSet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CustomObjectControlPtSet(p0, p1, p2, p3, p4, p5));
  } },
  { "CustomObjectGetSurfaceProxy", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CustomObjectGetSurfaceProxy(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CustomObjectReplacePath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->CustomObjectReplacePath(p0, p1));
  } },
  { "DeleteComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteComponent(p0, p1));
  } },
  { "DeleteConstraint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->DeleteConstraint(p0, p1); r["ret"]=nullptr;
  } },
  { "DuplicateObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->DuplicateObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "EnableParameter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->EnableParameter(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "EvaluateNurbsSurfacePointAndNormal", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    WorldPt3 p3;
    WorldPt3 p4;
    r["ret"] = (bool)(gSDK->EvaluateNurbsSurfacePointAndNormal(p0, p1, p2, p3, p4));
    r["out"]["point"] = MWpt3(p3);
    r["out"]["normal"] = MWpt3(p4);
  } },
  { "Get2DPt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2;
    gSDK->Get2DPt(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["loc"] = MWpt(p2);
  } },
  { "GetBinaryConstraint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    long long p7 = JInt(a,i);
    long long p8 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetBinaryConstraint(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetClosestSide", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    short p2 = 0;
    short p3 = 0;
    gSDK->GetClosestSide(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["indexA"] = (long long)p2;
    r["out"]["indexB"] = (long long)p3;
  } },
  { "GetComponentClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentClass(p0, p1, p2));
    r["out"]["componentClass"] = (long long)p2;
  } },
  { "GetComponentFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentFill(p0, p1, p2));
    r["out"]["fill"] = (long long)p2;
  } },
  { "GetComponentFillColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    ColorRef p2 = 0;
    ColorRef p3 = 0;
    r["ret"] = (bool)(gSDK->GetComponentFillColors(p0, p1, p2, p3));
    r["out"]["fillForeColor"] = (long long)p2;
    r["out"]["fillBackColor"] = (long long)p3;
  } },
  { "GetComponentName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    TXString p2;
    r["ret"] = (bool)(gSDK->GetComponentName(p0, p1, p2));
    r["out"]["componentName"] = MStr(p2);
  } },
  { "GetComponentPenColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    ColorRef p2 = 0;
    ColorRef p3 = 0;
    ColorRef p4 = 0;
    ColorRef p5 = 0;
    r["ret"] = (bool)(gSDK->GetComponentPenColors(p0, p1, p2, p3, p4, p5));
    r["out"]["leftPenForeColor"] = (long long)p2;
    r["out"]["leftPenBackColor"] = (long long)p3;
    r["out"]["rightPenForeColor"] = (long long)p4;
    r["out"]["rightPenBackColor"] = (long long)p5;
  } },
  { "GetComponentPenWeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Uint8 p2 = 0;
    Uint8 p3 = 0;
    r["ret"] = (bool)(gSDK->GetComponentPenWeights(p0, p1, p2, p3));
    r["out"]["leftPenWeight"] = (long long)p2;
    r["out"]["rightPenWeight"] = (long long)p3;
  } },
  { "GetComponentUseFillClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseFillClassAttr(p0, p1, p2));
    r["out"]["useFillClassAttributes"] = (bool)(p2!=0);
  } },
  { "GetComponentUsePenClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    Boolean p3 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUsePenClassAttr(p0, p1, p2, p3));
    r["out"]["useLeftPenClassAttributes"] = (bool)(p2!=0);
    r["out"]["useRightPenClassAttributes"] = (bool)(p3!=0);
  } },
  { "GetComponentWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentWidth(p0, p1, p2));
    r["out"]["width"] = (double)p2;
  } },
  { "GetCustomObjectColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    ColorRef p2 = 0;
    r["ret"] = (bool)(gSDK->GetCustomObjectColor(p0, p1, p2));
    r["out"]["ioColorRef"] = (long long)p2;
  } },
  { "GetCustomObjectPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomObjectPath(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetCustomObjectProfileGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomObjectProfileGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDistanceAlongNurbsCurve", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    long long p4 = JInt(a,i);
    double_gs p5 = 0;
    r["ret"] = (bool)(gSDK->GetDistanceAlongNurbsCurve(p0, p1, p2, p3, p4, p5));
    r["out"]["outDistance"] = (double)p5;
  } },
  { "GetLocalizedPluginChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    TXString p3;
    r["ret"] = (bool)(gSDK->GetLocalizedPluginChoice(p0, p1, p2, p3));
    r["out"]["localizedChoice"] = MStr(p3);
  } },
  { "GetLocalizedPluginName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetLocalizedPluginName(p0, p1));
    r["out"]["outLocalizedName"] = MStr(p1);
  } },
  { "GetLocalizedPluginParameter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2;
    r["ret"] = (bool)(gSDK->GetLocalizedPluginParameter(p0, p1, p2));
    r["out"]["localizedParameterName"] = MStr(p2);
  } },
  { "GetNumberOfComponents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    r["ret"] = (bool)(gSDK->GetNumberOfComponents(p0, p1));
    r["out"]["numComponents"] = (long long)p1;
  } },
  { "GetNurbsObjectDistanceFromPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = 0;
    r["ret"] = (bool)(gSDK->GetNurbsObjectDistanceFromPoint(p0, p1, p2));
    r["out"]["distance"] = (double)p2;
  } },
  { "GetObjectProperty", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetObjectProperty(p0, p1, p2));
    r["out"]["outValue"] = (bool)(p2!=0);
  } },
  { "GetParameterOnNurbsCurve", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    double p2 = 0;
    Sint32 p3 = 0;
    r["ret"] = (bool)(gSDK->GetParameterOnNurbsCurve(p0, p1, p2, p3));
    r["out"]["parameter"] = (double)p2;
    r["out"]["index"] = (long long)p3;
  } },
  { "GetPointAndParameterOnNurbsCurveAtGivenLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    WorldPt3 p2;
    double_gs p3 = 0;
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetPointAndParameterOnNurbsCurveAtGivenLength(p0, p1, p2, p3, p4));
    r["out"]["outPointOnCurve"] = MWpt3(p2);
    r["out"]["outParametricParameter"] = (double)p3;
    r["out"]["outPiecewiseCurveIndex"] = (long long)p4;
  } },
  { "GetRoofEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2;
    double_gs p3 = 0;
    WorldCoord p4 = 0;
    WorldCoord p5 = 0;
    r["ret"] = (bool)(gSDK->GetRoofEdge(p0, p1, p2, p3, p4, p5));
    r["out"]["vertexPt"] = MWpt(p2);
    r["out"]["slope"] = (double)p3;
    r["out"]["projection"] = (double)p4;
    r["out"]["eaveHeight"] = (double)p5;
  } },
  { "GetSingularConstraint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetSingularConstraint(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetViewportClassVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    r["ret"] = (bool)(gSDK->GetViewportClassVisibility(p0, p1, p2));
    r["out"]["visibilityType"] = (long long)p2;
  } },
  { "GetViewportCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetViewportCropObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetViewportGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetViewportGroup(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetViewportGroupParent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetViewportGroupParent(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetViewportLayerVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    short p2 = 0;
    r["ret"] = (bool)(gSDK->GetViewportLayerVisibility(p0, p1, p2));
    r["out"]["visibilityType"] = (long long)p2;
  } },
  { "HasConstraint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->HasConstraint(p0));
  } },
  { "InsertAllParametersAsWidgets", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->InsertAllParametersAsWidgets(p0));
  } },
  { "InsertParameterWidget", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->InsertParameterWidget(p0, p1, p2, p3, p4));
  } },
  { "InsertWidget", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4 = JStr(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->InsertWidget(p0, p1, p2, p3, p4, p5));
  } },
  { "IsObjectFromReferencedFile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsObjectFromReferencedFile(p0));
  } },
  { "IsViewportGroupContainedObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsViewportGroupContainedObject(p0, p1));
  } },
  { "MakePolyshapeValid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->MakePolyshapeValid(p0); r["ret"]=nullptr;
  } },
  { "MoveObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->MoveObject(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "MoveObject3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    bool p4 = JBool(a,i);
    gSDK->MoveObject3D(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "RemoveCustomObjectColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveCustomObjectColor(p0, p1));
  } },
  { "RemoveRoofEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveRoofEdge(p0, p1));
  } },
  { "ResetObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->ResetObject(p0));
  } },
  { "ScaleObjectN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    gSDK->ScaleObjectN(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetBinaryConstraint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    long long p7 = JInt(a,i);
    long long p8 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetBinaryConstraint(p0, p1, p2, p3, p4, p5, p6, p7, p8));
  } },
  { "SetComponentClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentClass(p0, p1, p2));
  } },
  { "SetComponentFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentFill(p0, p1, p2));
  } },
  { "SetComponentFillColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentFillColors(p0, p1, p2, p3));
  } },
  { "SetComponentName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetComponentName(p0, p1, p2));
  } },
  { "SetComponentPenColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentPenColors(p0, p1, p2, p3, p4, p5));
  } },
  { "SetComponentPenWeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentPenWeights(p0, p1, p2, p3));
  } },
  { "SetComponentUseFillClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseFillClassAttr(p0, p1, p2));
  } },
  { "SetComponentUsePenClassAttr", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUsePenClassAttr(p0, p1, p2, p3));
  } },
  { "SetComponentWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComponentWidth(p0, p1, p2));
  } },
  { "SetConstraintValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetConstraintValue(p0, p1); r["ret"]=nullptr;
  } },
  { "SetCustomObjectColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectColor(p0, p1, p2));
  } },
  { "SetCustomObjectControlPointVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectControlPointVisibility(p0, p1, p2));
  } },
  { "SetCustomObjectPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectPath(p0, p1));
  } },
  { "SetCustomObjectProfileGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectProfileGroup(p0, p1));
  } },
  { "SetDefinition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->SetDefinition(p0, p1); r["ret"]=nullptr;
  } },
  { "SetObjectProperty", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetObjectProperty(p0, p1, p2));
  } },
  { "SetParameterVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetParameterVisibility(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetRoofEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    gSDK->SetRoofEdge(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "SetSingularConstraint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetSingularConstraint(p0, p1, p2, p3));
  } },
  { "SetViewportClassVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetViewportClassVisibility(p0, p1, p2));
  } },
  { "SetViewportCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetViewportCropObject(p0, p1));
  } },
  { "SetViewportLayerVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetViewportLayerVisibility(p0, p1, p2));
  } },
  { "UpdateConstraintModel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->UpdateConstraintModel());
  } },
  { "UpdateViewport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->UpdateViewport(p0); r["ret"]=nullptr;
  } },
  { "ViewportHasCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->ViewportHasCropObject(p0));
  } },
  { "FirstSelectedObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->FirstSelectedObject();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "MoveSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    gSDK->MoveSelection(p0, p1); r["ret"]=nullptr;
  } },
  { "MoveSelection3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->MoveSelection3D(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "RotateSelectionN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    double p1 = JReal(a,i);
    gSDK->RotateSelectionN(p0, p1); r["ret"]=nullptr;
  } },
  { "ScaleSelectionN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->ScaleSelectionN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateTextBlock", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    WorldPt p1 = JWpt(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateTextBlock(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->DeleteText(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetCharNumFromPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (long long)(gSDK->GetCharNumFromPoint(p0, p1));
  } },
  { "GetTextChars", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString rs = gSDK->GetTextChars(p0); r["ret"] = MStr(rs);
  } },
  { "GetTextColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    ColorRef p2 = 0;
    gSDK->GetTextColor(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["charColor"] = (long long)p2;
  } },
  { "GetTextFontIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetTextFontIndex(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["fontIndex"] = (long long)p2;
  } },
  { "GetTextJustification", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    gSDK->GetTextJustification(p0, p1); r["ret"]=nullptr;
    r["out"]["justification"] = (long long)p1;
  } },
  { "GetTextLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetTextLength(p0));
  } },
  { "GetTextLineHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    gSDK->GetTextLineHeight(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["height"] = (double)p2;
  } },
  { "GetTextOrientationN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    short p2 = 0;
    gSDK->GetTextOrientationN(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["angle"] = (double)p1;
    r["out"]["flipState"] = (long long)p2;
  } },
  { "GetTextSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    gSDK->GetTextSize(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["charSize"] = (double)p2;
  } },
  { "GetTextVerticalAlignment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    gSDK->GetTextVerticalAlignment(p0, p1); r["ret"]=nullptr;
    r["out"]["verticalAlignment"] = (long long)p1;
  } },
  { "GetTextVerticalSpacing", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    WorldCoord p2 = 0;
    gSDK->GetTextVerticalSpacing(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["spacing"] = (long long)p1;
    r["out"]["height"] = (double)p2;
  } },
  { "GetTextWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    r["ret"] = (bool)(gSDK->GetTextWidth(p0, p1));
    r["out"]["width"] = (double)p1;
  } },
  { "GetTextWrap", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    Boolean p1 = 0;
    r["ret"] = (bool)(gSDK->GetTextWrap(p0, p1));
    r["out"]["wrapped"] = (bool)(p1!=0);
  } },
  { "SetTextColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetTextColor(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetTextFontIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetTextFontIndex(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetTextJustification", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetTextJustification(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTextOrientationN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetTextOrientationN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetTextSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    gSDK->SetTextSize(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetTextVerticalAlignment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetTextVerticalAlignment(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTextVerticalSpacing", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    gSDK->SetTextVerticalSpacing(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetTextWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetTextWidth(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTextWrap", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetTextWrap(p0, p1); r["ret"]=nullptr;
  } },
  { "AttachDefaultTextureSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->AttachDefaultTextureSpace(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateShaderRecord", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateShaderRecord(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->CreateTexture();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateTextureBitmap", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->CreateTextureBitmap();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateTextureBitmapFromPaintNode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateTextureBitmapFromPaintNode(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteTextureSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeleteTextureSpace(p0, p1); r["ret"]=nullptr;
  } },
  { "EditShaderRecord", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->EditShaderRecord(p0));
  } },
  { "EditTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->EditTexture(p0));
  } },
  { "EditTextureSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->EditTextureSpace(p0, p1));
  } },
  { "GetClGenTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetClGenTexture(p0));
  } },
  { "GetClRoofTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    InternalIndex p1 = 0;
    InternalIndex p2 = 0;
    InternalIndex p3 = 0;
    gSDK->GetClRoofTextures(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["top"] = (long long)p1;
    r["out"]["edge"] = (long long)p2;
    r["out"]["dormer"] = (long long)p3;
  } },
  { "GetClUseTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetClUseTexture(p0));
  } },
  { "GetClWallTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    InternalIndex p1 = 0;
    InternalIndex p2 = 0;
    InternalIndex p3 = 0;
    gSDK->GetClWallTextures(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["right"] = (long long)p1;
    r["out"]["left"] = (long long)p2;
    r["out"]["center"] = (long long)p3;
  } },
  { "GetShaderRecord", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetShaderRecord(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetTextureRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (long long)(gSDK->GetTextureRef(p0, p1, p2));
  } },
  { "GetTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    InternalIndex p1 = 0;
    InternalIndex p2 = 0;
    InternalIndex p3 = 0;
    gSDK->GetTextures(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["primaryTexture"] = (long long)p1;
    r["out"]["secondaryTexture"] = (long long)p2;
    r["out"]["tertiaryTexture"] = (long long)p3;
  } },
  { "GetTextureSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetTextureSpace(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetVPClassGenTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetVPClassGenTexture(p0, p1));
  } },
  { "GetVPClassRoofTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    InternalIndex p2 = 0;
    InternalIndex p3 = 0;
    InternalIndex p4 = 0;
    gSDK->GetVPClassRoofTextures(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["top"] = (long long)p2;
    r["out"]["edge"] = (long long)p3;
    r["out"]["dormer"] = (long long)p4;
  } },
  { "GetVPClassWallTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    InternalIndex p2 = 0;
    InternalIndex p3 = 0;
    InternalIndex p4 = 0;
    gSDK->GetVPClassWallTextures(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["right"] = (long long)p2;
    r["out"]["left"] = (long long)p3;
    r["out"]["center"] = (long long)p4;
  } },
  { "SetClGenTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetClGenTexture(p0, p1); r["ret"]=nullptr;
  } },
  { "SetClRoofTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetClRoofTextures(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetClUseTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetClUseTexture(p0, p1); r["ret"]=nullptr;
  } },
  { "SetClWallTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetClWallTextures(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetDefaultTextureSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetDefaultTextureSpace(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetTextureRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetTextureRef(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "BoxToolDraw", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->BoxToolDraw(); r["ret"]=nullptr;
  } },
  { "ClearAllToolPts", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->ClearAllToolPts());
  } },
  { "ClearDataDisplayBar", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ClearDataDisplayBar(); r["ret"]=nullptr;
  } },
  { "ClickDragToolStatus", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->ClickDragToolStatus());
  } },
  { "Default2DToolDraw", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->Default2DToolDraw(); r["ret"]=nullptr;
  } },
  { "Default3DToolDraw", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->Default3DToolDraw(); r["ret"]=nullptr;
  } },
  { "DrawCoordArcN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    gSDK->DrawCoordArcN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "DrawCoordEllipse", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0;
    gSDK->DrawCoordEllipse(p0); r["ret"]=nullptr;
    r["out"]["theBox"] = MWrect(p0);
  } },
  { "DrawCoordLine", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    gSDK->DrawCoordLine(p0, p1); r["ret"]=nullptr;
  } },
  { "DrawCoordLine3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    gSDK->DrawCoordLine3D(p0, p1); r["ret"]=nullptr;
  } },
  { "DrawCoordRect", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    gSDK->DrawCoordRect(p0); r["ret"]=nullptr;
  } },
  { "DrawDataDisplayBar", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->DrawDataDisplayBar(p0); r["ret"]=nullptr;
  } },
  { "DrawNurbsObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->DrawNurbsObject(p0); r["ret"]=nullptr;
  } },
  { "DrawObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->DrawObject(p0, p1); r["ret"]=nullptr;
  } },
  { "GetNumToolPts", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumToolPts());
  } },
  { "GetToolPt2D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->GetToolPt2D(p0, p1));
    r["out"]["outToolPoint"] = MWpt(p1);
  } },
  { "GetToolPt3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldPt3 p1;
    r["ret"] = (bool)(gSDK->GetToolPt3D(p0, p1));
    r["out"]["outToolPoint"] = MWpt3(p1);
  } },
  { "GetToolPtCurrent2D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    r["ret"] = (bool)(gSDK->GetToolPtCurrent2D(p0));
    r["out"]["outToolPoint"] = MWpt(p0);
  } },
  { "GetToolPtCurrent3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0;
    r["ret"] = (bool)(gSDK->GetToolPtCurrent3D(p0));
    r["out"]["outToolPt"] = MWpt3(p0);
  } },
  { "GetToolPtCurrentWorkingPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0;
    r["ret"] = (bool)(gSDK->GetToolPtCurrentWorkingPlane(p0));
    r["out"]["outToolPt"] = MWpt3(p0);
  } },
  { "GetToolPtWorkingPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldPt3 p1;
    r["ret"] = (bool)(gSDK->GetToolPtWorkingPlane(p0, p1));
    r["out"]["outToolPoint"] = MWpt3(p1);
  } },
  { "OnePointToolStatus", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->OnePointToolStatus());
  } },
  { "PolyToolStatus", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->PolyToolStatus());
  } },
  { "PopLastToolPt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->PopLastToolPt());
  } },
  { "SetCursorMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetCursorMode(); r["ret"]=nullptr;
  } },
  { "SetDimUserBarValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    double p1 = JReal(a,i);
    gSDK->SetDimUserBarValue(p0, p1); r["ret"]=nullptr;
  } },
  { "SetFloatUserBarValueN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    double p1 = JReal(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetFloatUserBarValueN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetTextUserBarValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->SetTextUserBarValue(p0, p1); r["ret"]=nullptr;
  } },
  { "SetToolProperty", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetToolProperty(p0, p1, p2));
  } },
  { "ThreePointToolStatus", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->ThreePointToolStatus());
  } },
  { "TwoPointToolStatus", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->TwoPointToolStatus());
  } },
  { "AddObjectToContainer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddObjectToContainer(p0, p1));
  } },
  { "AuxOwner", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->AuxOwner(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->DeleteObject(p0, p1); r["ret"]=nullptr;
  } },
  { "FirstMemberObj", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->FirstMemberObj(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDefaultContainer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetDefaultContainer();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDrawingHeader", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetDrawingHeader();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetHatchListHeader", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetHatchListHeader();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetSymbolLibraryHeader", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetSymbolLibraryHeader();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "InsertObjectAfter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->InsertObjectAfter(p0, p1));
  } },
  { "InsertObjectBefore", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->InsertObjectBefore(p0, p1));
  } },
  { "LastMemberObj", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->LastMemberObj(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "NextObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->NextObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ParentObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->ParentObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PrevObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->PrevObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SearchForAncestorType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle rh = gSDK->SearchForAncestorType(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetPageBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    gSDK->SetPageBounds(p0); r["ret"]=nullptr;
  } },
  { "AcquireExportPDFSettingsAndLocation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    r["ret"] = (bool)(gSDK->AcquireExportPDFSettingsAndLocation(p0));
  } },
  { "ClosePDFDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ClosePDFDocument(); r["ret"]=nullptr;
  } },
  { "ExportPDFPages", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (long long)(gSDK->ExportPDFPages(p0));
  } },
  { "OpenPDFDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (bool)(gSDK->OpenPDFDocument(p0));
  } },
  { "AddAfterMoveObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddAfterMoveObject(p0));
  } },
  { "AddAfterSwapObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddAfterSwapObject(p0));
  } },
  { "AddBeforeMoveObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddBeforeMoveObject(p0));
  } },
  { "AddBeforeSwapObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddBeforeSwapObject(p0));
  } },
  { "AddBothSwapObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddBothSwapObject(p0));
  } },
  { "AddCoordMoveObject2D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->AddCoordMoveObject2D(p0, p1, p2));
  } },
  { "AddCoordMoveObject3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (bool)(gSDK->AddCoordMoveObject3D(p0, p1, p2, p3));
  } },
  { "EndUndoEvent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->EndUndoEvent());
  } },
  { "NameUndoEvent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->NameUndoEvent(p0); r["ret"]=nullptr;
  } },
  { "NonUndoableActionOK", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->NonUndoableActionOK());
  } },
  { "SetUndoMethod", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetUndoMethod(p0); r["ret"]=nullptr;
  } },
  { "SupportUndoAndRemove", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SupportUndoAndRemove(); r["ret"]=nullptr;
  } },
  { "UndoAndRemove", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->UndoAndRemove(); r["ret"]=nullptr;
  } },
  { "AngleToStringN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    TXString p1;
    gSDK->AngleToStringN(p0, p1); r["ret"]=nullptr;
    r["out"]["s"] = MStr(p1);
  } },
  { "AssociateLinearDimension", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->AssociateLinearDimension(p0, p1); r["ret"]=nullptr;
  } },
  { "ClipSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->ClipSurface(p0, p1); r["ret"]=nullptr;
  } },
  { "CombineIntoSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    MCObjectHandle rh = gSDK->CombineIntoSurface(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CoordToDimString", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    TXString p1;
    gSDK->CoordToDimString(p0, p1); r["ret"]=nullptr;
    r["out"]["s"] = MStr(p1);
  } },
  { "DisableModules", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->DisableModules(p0); r["ret"]=nullptr;
  } },
  { "DisplayContextHelpOfCurrentPlugin", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->DisplayContextHelpOfCurrentPlugin(); r["ret"]=nullptr;
  } },
  { "DisplayContextualHelp", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (bool)(gSDK->DisplayContextualHelp(p0));
  } },
  { "DisplayOrganizationDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->DisplayOrganizationDialog(p0); r["ret"]=nullptr;
  } },
  { "DoMenuName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->DoMenuName(p0, p1));
  } },
  { "ExternalNameToID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (long long)(gSDK->ExternalNameToID(p0));
  } },
  { "FontIndexFromName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (long long)(gSDK->FontIndexFromName(p0));
  } },
  { "FontNameFromIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    bool p2 = JBool(a,i);
    gSDK->FontNameFromIndex(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["fontName"] = MStr(p1);
  } },
  { "GetActiveSerialNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    gSDK->GetActiveSerialNumber(p0); r["ret"]=nullptr;
    r["out"]["outSerialNumber"] = MStr(p0);
  } },
  { "GetCallBackInval", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetCallBackInval());
  } },
  { "GetCurrentMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetCurrentMode());
  } },
  { "GetDataBarCursorVisState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDataBarCursorVisState());
  } },
  { "GetEnabledModules", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetEnabledModules());
  } },
  { "GetModifierFlags", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    Boolean p0 = 0;
    Boolean p1 = 0;
    Boolean p2 = 0;
    gSDK->GetModifierFlags(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["optionFlag"] = (bool)(p0!=0);
    r["out"]["cmdFlag"] = (bool)(p1!=0);
    r["out"]["shiftFlag"] = (bool)(p2!=0);
  } },
  { "GetProduct", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    short p0 = 0;
    Sint32 p1 = 0;
    gSDK->GetProduct(p0, p1); r["ret"]=nullptr;
    r["out"]["product"] = (long long)p0;
    r["out"]["modules"] = (long long)p1;
  } },
  { "GetSavedSetting", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2;
    r["ret"] = (bool)(gSDK->GetSavedSetting(p0, p1, p2));
    r["out"]["value"] = MStr(p2);
  } },
  { "HandlePendingUpdatesAndActivates", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->HandlePendingUpdatesAndActivates(); r["ret"]=nullptr;
  } },
  { "HilitePalettesAndTopDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->HilitePalettesAndTopDocument(p0); r["ret"]=nullptr;
  } },
  { "IntersectObjects", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle rh = gSDK->IntersectObjects(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "LineLineIntersect", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2 = JWpt(a,i);
    WorldPt p3 = JWpt(a,i);
    Boolean p4 = 0;
    Boolean p5 = 0;
    WorldPt p6;
    gSDK->LineLineIntersect(p0, p1, p2, p3, p4, p5, p6); r["ret"]=nullptr;
    r["out"]["parallel"] = (bool)(p4!=0);
    r["out"]["intOnLines"] = (bool)(p5!=0);
    r["out"]["sect"] = MWpt(p6);
  } },
  { "ObjectNearCoordPt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    MCObjectHandle rh = gSDK->ObjectNearCoordPt(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PointInsidePoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->PointInsidePoly(p0, p1));
  } },
  { "PointOnPolyEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->PointOnPolyEdge(p0, p1, p2));
  } },
  { "SetCallBackInval", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->SetCallBackInval(p0); r["ret"]=nullptr;
  } },
  { "SetPersistentHighlight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetPersistentHighlight(p0, p1); r["ret"]=nullptr;
  } },
  { "SetSavedSetting", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    gSDK->SetSavedSetting(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "StringToAngleN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    double_gs p1 = 0;
    r["ret"] = (bool)(gSDK->StringToAngleN(p0, p1));
    r["out"]["angle"] = (double)p1;
  } },
  { "SymbolContainsLight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SymbolContainsLight(p0));
  } },
  { "ToggleObjectHighlight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ToggleObjectHighlight(p0); r["ret"]=nullptr;
  } },
  { "VerifyPluginLibrary", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (bool)(gSDK->VerifyPluginLibrary(p0));
  } },
  { "GetPerspectiveInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    WorldCoord p2 = 0;
    WorldRect p3;
    gSDK->GetPerspectiveInfo(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["perspectiveDistance"] = (double)p1;
    r["out"]["clipDistance"] = (double)p2;
    r["out"]["clipRect"] = MWrect(p3);
  } },
  { "GetProjection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetProjection(p0));
  } },
  { "GetPerspectiveType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetPerspectiveType(p0));
  } },
  { "GetRenderMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetRenderMode(p0));
  } },
  { "GetScreenDPI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetScreenDPI());
  } },
  { "GetViewCenter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    gSDK->GetViewCenter(p0); r["ret"]=nullptr;
    r["out"]["center"] = MWpt(p0);
  } },
  { "RedrawRect", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldRect p0 = JWrect(a,i);
    gSDK->RedrawRect(p0); r["ret"]=nullptr;
  } },
  { "SetViewCenter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    gSDK->SetViewCenter(p0); r["ret"]=nullptr;
  } },
  { "SetWorkingPlaneVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    gSDK->SetWorkingPlaneVertex(p0); r["ret"]=nullptr;
  } },
  { "SetZoomFactorN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    gSDK->SetZoomFactorN(p0); r["ret"]=nullptr;
  } },
  { "ViewRotWorldZN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    bool p1 = JBool(a,i);
    gSDK->ViewRotWorldZN(p0, p1); r["ret"]=nullptr;
  } },
  { "DeleteBreak", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeleteBreak(p0, p1); r["ret"]=nullptr;
  } },
  { "GetWallCaps", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    Boolean p1 = 0;
    Boolean p2 = 0;
    Boolean p3 = 0;
    gSDK->GetWallCaps(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["leftCap"] = (bool)(p1!=0);
    r["out"]["rightCap"] = (bool)(p2!=0);
    r["out"]["round"] = (bool)(p3!=0);
  } },
  { "GetWallCapsOffsets", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    WorldCoord p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    gSDK->GetWallCapsOffsets(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["leftCapLeftOffset"] = (double)p1;
    r["out"]["leftCapRightOffset"] = (double)p2;
    r["out"]["rightCapLeftOffset"] = (double)p3;
    r["out"]["rightCapRightOffset"] = (double)p4;
  } },
  { "GetWallCornerHeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    WorldCoord p2 = 0;
    WorldCoord p3 = 0;
    WorldCoord p4 = 0;
    gSDK->GetWallCornerHeights(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["startHeightTop"] = (double)p1;
    r["out"]["startHeightBottom"] = (double)p2;
    r["out"]["endHeightTop"] = (double)p3;
    r["out"]["endHeightBottom"] = (double)p4;
  } },
  { "MoveWallByOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    gSDK->MoveWallByOffset(p0, p1); r["ret"]=nullptr;
    r["out"]["offset"] = (double)p1;
  } },
  { "ReverseWallSides", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ReverseWallSides(p0); r["ret"]=nullptr;
  } },
  { "SetWallCaps", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetWallCaps(p0, p1, p2, p3));
  } },
  { "SetWallCapsOffsets", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetWallCapsOffsets(p0, p1, p2, p3, p4));
  } },
  { "SetWallCornerHeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetWallCornerHeights(p0, p1, p2, p3, p4));
  } },
  { "SetWallStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetWallStyle(p0, p1, p2, p3));
  } },
  { "SetWallWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetWallWidth(p0, p1));
  } },
  { "WrapGetWallWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double_gs p1 = 0;
    gSDK->WrapGetWallWidth(p0, p1); r["ret"]=nullptr;
    r["out"]["outCoordLen"] = (double)p1;
  } },
  { "AutoFitWorksheetRowHeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->AutoFitWorksheetRowHeights(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateWorksheet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateWorksheet(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateWorksheetImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    MCObjectHandle rh = gSDK->CreateWorksheetImage(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteWorksheetColumns", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->DeleteWorksheetColumns(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "DeleteWorksheetRows", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->DeleteWorksheetRows(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetTopVisibleWorksheet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetTopVisibleWorksheet();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWorksheetColumnOperators", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    short p3 = 0;
    short p4 = 0;
    short p5 = 0;
    short p6 = 0;
    short p7 = 0;
    gSDK->GetWorksheetColumnOperators(p0, p1, p2, p3, p4, p5, p6, p7); r["ret"]=nullptr;
    r["out"]["sort1"] = (long long)p2;
    r["out"]["sort2"] = (long long)p3;
    r["out"]["sort3"] = (long long)p4;
    r["out"]["sum1"] = (long long)p5;
    r["out"]["sum2"] = (long long)p6;
    r["out"]["sum3"] = (long long)p7;
  } },
  { "GetWorksheetColumnWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetWorksheetColumnWidth(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["width"] = (long long)p2;
  } },
  { "GetWorksheetFromImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWorksheetFromImage(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWorksheetImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWorksheetImage(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWorksheetRowColumnCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    short p1 = 0;
    short p2 = 0;
    gSDK->GetWorksheetRowColumnCount(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["numRows"] = (long long)p1;
    r["out"]["numColumns"] = (long long)p2;
  } },
  { "GetWorksheetRowHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetWorksheetRowHeight(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["height"] = (long long)p2;
  } },
  { "GetWorksheetRowHLockState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    gSDK->GetWorksheetRowHLockState(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["lockState"] = (bool)(p2!=0);
  } },
  { "GetWorksheetSubrowCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    gSDK->GetWorksheetSubrowCount(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["numSubrows"] = (long long)p2;
  } },
  { "InsertWorksheetColumns", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->InsertWorksheetColumns(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "InsertWorksheetRows", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->InsertWorksheetRows(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "IsWorksheetDatabaseRow", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsWorksheetDatabaseRow(p0, p1));
  } },
  { "IsWorksheetVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsWorksheetVisible(p0));
  } },
  { "RecalculateWorksheet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->RecalculateWorksheet(p0); r["ret"]=nullptr;
  } },
  { "SetTopVisibleWorksheet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetTopVisibleWorksheet(p0); r["ret"]=nullptr;
  } },
  { "SetWorksheetColumnOperators", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    long long p7 = JInt(a,i);
    gSDK->SetWorksheetColumnOperators(p0, p1, p2, p3, p4, p5, p6, p7); r["ret"]=nullptr;
  } },
  { "SetWorksheetColumnWidth", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetWorksheetColumnWidth(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetWorksheetRowsHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    gSDK->SetWorksheetRowsHeight(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "ShowWorksheet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->ShowWorksheet(p0, p1); r["ret"]=nullptr;
  } },
  { "ShowWorksheetDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->ShowWorksheetDialog(p0); r["ret"]=nullptr;
  } },
  { "GetCurrentWorkspaceFileName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    gSDK->GetCurrentWorkspaceFileName(p0); r["ret"]=nullptr;
    r["out"]["outFileName"] = MStr(p0);
  } },
  { "SetWorkspaceFileToReload", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->SetWorkspaceFileToReload(p0); r["ret"]=nullptr;
  } },
  { "WSAddMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->WSAddMenu(p0, p1, p2));
  } },
  { "WSAddToolPalette", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->WSAddToolPalette(p0, p1));
  } },
  { "WSMenuAddMenuItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->WSMenuAddMenuItem(p0, p1, p2));
  } },
  { "WSMenuBarAddMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->WSMenuBarAddMenu(p0, p1));
  } },
  { "WSPaletteSetHomeCorner", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->WSPaletteSetHomeCorner(p0, p1, p2));
  } },
  { "WSSetVersion", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->WSSetVersion(p0, p1));
  } },
  { "WSToolPaletteAddToolSet", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->WSToolPaletteAddToolSet(p0, p1, p2));
  } },
  { "WSToolSetAddToolChildToTool", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->WSToolSetAddToolChildToTool(p0, p1, p2, p3));
  } },
  { "EnableComponentInstance", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableComponentInstance(p0, p1));
  } },
  { "IsEnabledComponentInstance", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsEnabledComponentInstance(p0));
  } },
  { "SetComponentInstanceName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetComponentInstanceName(p0, p1));
  } },
  { "GetComponentInstanceName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetComponentInstanceName(p0, p1));
    r["out"]["outLocalizedName"] = MStr(p1);
  } },
  { "EmptyToolHighlightingList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->EmptyToolHighlightingList());
  } },
  { "AddToolHighlightingObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddToolHighlightingObject(p0));
  } },
  { "AddToolHighlightingSegment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->AddToolHighlightingSegment(p0, p1));
  } },
  { "AddToolHighlightingPolyCreate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->AddToolHighlightingPolyCreate();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddToolHighlightingPoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->AddToolHighlightingPoly(p0, p1));
  } },
  { "AddToolHighlightingSegment3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->AddToolHighlightingSegment3D(p0, p1));
  } },
  { "AddToolHighlightingPoly3DCreate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->AddToolHighlightingPoly3DCreate();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddToolHighlightingPoly3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->AddToolHighlightingPoly3D(p0, p1));
  } },
  { "AddToolHighlightingPoly3DAddVertex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->AddToolHighlightingPoly3DAddVertex(p0, p1));
  } },
  { "OpenURL", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (bool)(gSDK->OpenURL(p0));
  } },
  { "ConvertNurbsToPolylineArcs", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle rh = gSDK->ConvertNurbsToPolylineArcs(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateOffsetObjectHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateOffsetObjectHandle(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "UnfoldSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->UnfoldSurface(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateWallHoleGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateWallHoleGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWallHoleGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWallHoleGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PerformMultipleUnion", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle rh = gSDK->PerformMultipleUnion(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWorksheetSubrowHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    short p3 = 0;
    gSDK->GetWorksheetSubrowHeight(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["height"] = (long long)p3;
  } },
  { "SetCustomObjectWallHoleGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectWallHoleGroup(p0, p1));
  } },
  { "GetCustomObjectSelectionGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomObjectSelectionGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetCustomObjectSelectionGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectSelectionGroup(p0, p1));
  } },
  { "CreateWallFootPrint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateWallFootPrint(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "EnableDrawingWorksheetPalette", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->EnableDrawingWorksheetPalette(p0, p1); r["ret"]=nullptr;
  } },
  { "GetWorksheetAutoRecalcState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetWorksheetAutoRecalcState(p0));
  } },
  { "SetWorksheetAutoRecalcState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetWorksheetAutoRecalcState(p0, p1); r["ret"]=nullptr;
  } },
  { "RestoreWPHybridTool", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->RestoreWPHybridTool(p0); r["ret"]=nullptr;
  } },
  { "ClearWPHybridTool", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ClearWPHybridTool(); r["ret"]=nullptr;
  } },
  { "SetCursorByView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetCursorByView(); r["ret"]=nullptr;
  } },
  { "AddUndoDeselectObj", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddUndoDeselectObj(p0));
  } },
  { "AddUndoSelectObj", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddUndoSelectObj(p0));
  } },
  { "SetStaticTextStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetStaticTextStyle(p0, p1, p2));
  } },
  { "SetStaticTextColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetStaticTextColor(p0, p1, p2, p3, p4));
  } },
  { "SetItemClickable", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetItemClickable(p0, p1, p2));
  } },
  { "SetSliderLiveUpdate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetSliderLiveUpdate(p0, p1, p2));
  } },
  { "RegisterDialogForTimerEvents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RegisterDialogForTimerEvents(p0, p1));
  } },
  { "DeregisterDialogFromTimerEvents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->DeregisterDialogFromTimerEvents(p0); r["ret"]=nullptr;
  } },
  { "SetListItemEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->SetListItemEnabled(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "SetObjectAsCornerBreak", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetObjectAsCornerBreak(p0, p1, p2));
  } },
  { "SetObjectWallOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetObjectWallOffset(p0, p1, p2));
  } },
  { "GetCoreWallComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetCoreWallComponent(p0));
  } },
  { "SetCoreWallComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetCoreWallComponent(p0, p1); r["ret"]=nullptr;
  } },
  { "GetActiveLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetActiveLayer();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetHighlightedHelpString", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->SetHighlightedHelpString(p0); r["ret"]=nullptr;
  } },
  { "GetCurrentLocalization", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    TXString p1;
    gSDK->GetCurrentLocalization(p0, p1); r["ret"]=nullptr;
    r["out"]["outLanguage"] = MStr(p0);
    r["out"]["outSubLanguage"] = MStr(p1);
  } },
  { "RefreshRenderingForSelectedObjects", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->RefreshRenderingForSelectedObjects(); r["ret"]=nullptr;
  } },
  { "RefreshResourceBrowserResourcesList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->RefreshResourceBrowserResourcesList(p0); r["ret"]=nullptr;
  } },
  { "PointInsideAnEnclosedRegionOfTheGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->PointInsideAnEnclosedRegionOfTheGroup(p0, p1));
    r["out"]["pickPt"] = MWpt(p1);
  } },
  { "CreateArcLengthDimension", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    bool p6 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateArcLengthDimension(p0, p1, p2, p3, p4, p5, p6);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetRoofRunRise", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    double p2 = 0;
    double p3 = 0;
    double p4 = 0;
    r["ret"] = (bool)(gSDK->GetRoofRunRise(p0, p1, p2, p3, p4));
    r["out"]["run"] = (double)p2;
    r["out"]["rise"] = (double)p3;
    r["out"]["value"] = (double)p4;
  } },
  { "AlignColumnEdge", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AlignColumnEdge(p0, p1, p2, p3));
  } },
  { "DeleteSymbolDefinition", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    gSDK->DeleteSymbolDefinition(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetTilePopupObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetTilePopupObject(p0, p1, p2));
  } },
  { "GetTilePopupObjectItemIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetTilePopupObjectItemIndex(p0, p1, p2));
  } },
  { "GetTilePopupSelectedItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetTilePopupSelectedItem(p0, p1));
  } },
  { "GetHatchPopupObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetHatchPopupObject(p0, p1, p2));
  } },
  { "GetHatchPopupObjectItemIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetHatchPopupObjectItemIndex(p0, p1, p2));
  } },
  { "GetHatchPopupSelectedItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetHatchPopupSelectedItem(p0, p1));
  } },
  { "CreateTile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateTile(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ShowNewTileDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->ShowNewTileDialog();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetTileBackgroundColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    ColorRef p1 = 0;
    r["ret"] = (bool)(gSDK->GetTileBackgroundColor(p0, p1));
    r["out"]["backgroundColor"] = (long long)p1;
  } },
  { "SetTileBackgroundColor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetTileBackgroundColor(p0, p1));
  } },
  { "GetTileGeometryGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetTileGeometryGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetListBrowserItemTileRefNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemTileRefNumber(p0, p1, p2, p3, p4));
    r["out"]["liRefNumber"] = (long long)p4;
  } },
  { "SetListBrowserItemTileRefNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemTileRefNumber(p0, p1, p2, p3, p4));
  } },
  { "AddToolEditTextMethod", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    gSDK->AddToolEditTextMethod(p0, p1); r["ret"]=nullptr;
  } },
  { "SetToolEditTextMethodValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->SetToolEditTextMethodValue(p0, p1); r["ret"]=nullptr;
  } },
  { "GetToolEditTextMethodValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetToolEditTextMethodValue(p0); r["ret"] = MStr(rs);
  } },
  { "EditRealConvertToStringUtility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    double p1 = JReal(a,i);
    TXString p2;
    gSDK->EditRealConvertToStringUtility(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["valueText"] = MStr(p2);
  } },
  { "GSNewObjectHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle rh = gSDK->GSNewObjectHandle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "InvalObj", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->InvalObj(p0); r["ret"]=nullptr;
  } },
  { "SetTextAdorner", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    WorldPt p2 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetTextAdorner(p0, p1, p2));
  } },
  { "GetTreeControlItemText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3;
    r["ret"] = (bool)(gSDK->GetTreeControlItemText(p0, p1, p2, p3));
    r["out"]["itemText"] = MStr(p3);
  } },
  { "GetTreeControlSelectedItemText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2;
    r["ret"] = (bool)(gSDK->GetTreeControlSelectedItemText(p0, p1, p2));
    r["out"]["itemText"] = MStr(p2);
  } },
  { "AddTileGeometryObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddTileGeometryObject(p0, p1));
  } },
  { "GetTileGroupParent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetTileGroupParent(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsTileGroupContainedObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsTileGroupContainedObject(p0));
  } },
  { "IsPlanarObjectIn3DView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsPlanarObjectIn3DView(p0));
  } },
  { "SetPlanarRefIDToGround", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetPlanarRefIDToGround(p0); r["ret"]=nullptr;
  } },
  { "ResizeSelectedDims", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    gSDK->ResizeSelectedDims(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "GetImageFileName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    long long p1 = JInt(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    TXString rs = gSDK->GetImageFileName(p0, p1, p2); r["ret"] = MStr(rs);
    r["out"]["resourceFileName"] = MStr(p0);
  } },
  { "CompressTextureImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->CompressTextureImage(p0); r["ret"]=nullptr;
  } },
  { "CreateTextureBitmapNoDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateTextureBitmapNoDialog(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ShowListBrowserRadioToolTips", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->ShowListBrowserRadioToolTips(p0, p1));
  } },
  { "SetTextStyleRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetTextStyleRef(p0, p1); r["ret"]=nullptr;
  } },
  { "GetTextStyleRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetTextStyleRef(p0));
  } },
  { "AlertQuestionDefault", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    TXString p6 = JStr(a,i);
    TXString p7 = JStr(a,i);
    TXString p8 = JStr(a,i);
    TXString p9 = JStr(a,i);
    long long p10 = JInt(a,i);
    r["ret"] = (long long)(gSDK->AlertQuestionDefault(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10));
  } },
  { "SetColorName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetColorName(p0, p1));
  } },
  { "GetColorName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetColorName(p0); r["ret"] = MStr(rs);
  } },
  { "IsScreenObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsScreenObject(p0));
  } },
  { "PieceWiseNurbsCurveReverseInPlace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->PieceWiseNurbsCurveReverseInPlace(p0));
  } },
  { "CreatePieceWiseNurbsCurveReverse", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreatePieceWiseNurbsCurveReverse(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateSlab", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateSlab(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ModifySlab", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->ModifySlab(p0, p1, p2, p3));
  } },
  { "GetSlabStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetSlabStyle(p0));
  } },
  { "SetSlabStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetSlabStyle(p0, p1); r["ret"]=nullptr;
  } },
  { "ConvertToUnstyledSlab", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ConvertToUnstyledSlab(p0); r["ret"]=nullptr;
  } },
  { "GetSlabPreferencesStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetSlabPreferencesStyle());
  } },
  { "SetSlabPreferencesStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetSlabPreferencesStyle(p0); r["ret"]=nullptr;
  } },
  { "BeginMultipleDuplicate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->BeginMultipleDuplicate(); r["ret"]=nullptr;
  } },
  { "EndMultipleDuplicate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->EndMultipleDuplicate(); r["ret"]=nullptr;
  } },
  { "BuildConstraintModelForObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->BuildConstraintModelForObject(p0, p1); r["ret"]=nullptr;
  } },
  { "RecordModifiedObjectInConstraintModel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->RecordModifiedObjectInConstraintModel(p0, p1); r["ret"]=nullptr;
  } },
  { "GetCurveEndsAndTangents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1;
    WorldPt3 p2;
    WorldPt3 p3;
    WorldPt3 p4;
    r["ret"] = (bool)(gSDK->GetCurveEndsAndTangents(p0, p1, p2, p3, p4));
    r["out"]["startPt"] = MWpt3(p1);
    r["out"]["endPt"] = MWpt3(p2);
    r["out"]["startTangent"] = MWpt3(p3);
    r["out"]["endTangent"] = MWpt3(p4);
  } },
  { "AreWorksheetGridLinesVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AreWorksheetGridLinesVisible(p0));
  } },
  { "SetWorksheetGridLinesVisibility", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetWorksheetGridLinesVisibility(p0, p1); r["ret"]=nullptr;
  } },
  { "AreUpdateChecksEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->AreUpdateChecksEnabled());
  } },
  { "CheckForUpdates", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->CheckForUpdates(); r["ret"]=nullptr;
  } },
  { "CreateCustomObjectPathNoOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateCustomObjectPathNoOffset(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "NumberCustomDimensionStandards", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->NumberCustomDimensionStandards());
  } },
  { "FindClosestPointOnNURBSObjectFrom3DPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    WorldPt3 p2;
    r["ret"] = (bool)(gSDK->FindClosestPointOnNURBSObjectFrom3DPoint(p0, p1, p2));
    r["out"]["outClosestPoint"] = MWpt3(p2);
  } },
  { "GetSlabHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetSlabHeight(p0));
  } },
  { "SetSlabHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetSlabHeight(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateSlabStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateSlabStyle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWallPreferences", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetWallPreferences();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetSlabPreferences", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetSlabPreferences();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDatumSlabComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetDatumSlabComponent(p0));
  } },
  { "SetDatumSlabComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetDatumSlabComponent(p0, p1); r["ret"]=nullptr;
  } },
  { "GetComponentOffsetFromWallTop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentOffsetFromWallTop(p0, p1, p2));
    r["out"]["offsetFromWallTop"] = (double)p2;
  } },
  { "SetComponentOffsetFromWallTop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComponentOffsetFromWallTop(p0, p1, p2));
  } },
  { "GetComponentOffsetFromWallBottom", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentOffsetFromWallBottom(p0, p1, p2));
    r["out"]["offsetFromWallBottom"] = (double)p2;
  } },
  { "SetComponentOffsetFromWallBottom", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComponentOffsetFromWallBottom(p0, p1, p2));
  } },
  { "GetComponentFollowTopWallPeaks", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentFollowTopWallPeaks(p0, p1, p2));
    r["out"]["followTopWallPeaks"] = (bool)(p2!=0);
  } },
  { "SetComponentFollowTopWallPeaks", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentFollowTopWallPeaks(p0, p1, p2));
  } },
  { "GetComponentFollowBottomWallPeaks", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentFollowBottomWallPeaks(p0, p1, p2));
    r["out"]["followBottomWallPeaks"] = (bool)(p2!=0);
  } },
  { "SetComponentFollowBottomWallPeaks", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentFollowBottomWallPeaks(p0, p1, p2));
  } },
  { "GetComponentManualEdgeOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentManualEdgeOffset(p0, p1, p2));
    r["out"]["manualEdgeOffset"] = (double)p2;
  } },
  { "SetComponentManualEdgeOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComponentManualEdgeOffset(p0, p1, p2));
  } },
  { "GetComponentTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    InternalIndex p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentTexture(p0, p1, p2));
    r["out"]["texture"] = (long long)p2;
  } },
  { "SetComponentTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentTexture(p0, p1, p2));
  } },
  { "GetComponentNetArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (double)(gSDK->GetComponentNetArea(p0, p1));
  } },
  { "GetComponentNetVolume", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (double)(gSDK->GetComponentNetVolume(p0, p1));
  } },
  { "FontMapGetReplacement", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1;
    gSDK->FontMapGetReplacement(p0, p1); r["ret"]=nullptr;
    r["out"]["outReplFont"] = MStr(p1);
  } },
  { "ConvertFontIDToIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->ConvertFontIDToIndex(p0));
  } },
  { "ConvertIndexToFontID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->ConvertIndexToFontID(p0));
  } },
  { "Get2DPolyAreaAndPerimeter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = 0;
    double p2 = 0;
    gSDK->Get2DPolyAreaAndPerimeter(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["area"] = (double)p1;
    r["out"]["perimeter"] = (double)p2;
  } },
  { "IFC_ResetGUID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->IFC_ResetGUID(p0); r["ret"]=nullptr;
  } },
  { "IFC_IsIFCRecord", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IFC_IsIFCRecord(p0));
  } },
  { "GetWallComponentPoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetWallComponentPoly(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetObjectHiddenLine", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle rh = gSDK->GetObjectHiddenLine(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddBeforeModifyWorkingPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->AddBeforeModifyWorkingPlane());
  } },
  { "CoordToPrimaryDimensionString", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    TXString rs = gSDK->CoordToPrimaryDimensionString(p0); r["ret"] = MStr(rs);
  } },
  { "CoordToSecondaryDimensionString", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    TXString rs = gSDK->CoordToSecondaryDimensionString(p0); r["ret"] = MStr(rs);
  } },
  { "GetWallOverallHeights", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldCoord p1 = 0;
    WorldCoord p2 = 0;
    gSDK->GetWallOverallHeights(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["overallHeightTop"] = (double)p1;
    r["out"]["overallHeightBottom"] = (double)p2;
  } },
  { "CheckParametricNameConflictWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (bool)(gSDK->CheckParametricNameConflictWithUI(p0));
  } },
  { "ShowByClassChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->ShowByClassChoice(p0, p1); r["ret"]=nullptr;
  } },
  { "IsClassChoiceSelected", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsClassChoiceSelected(p0, p1));
  } },
  { "SelectClassChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SelectClassChoice(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetMeshVertexCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetMeshVertexCount(p0));
  } },
  { "GetMeshVertexAt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 rp = gSDK->GetMeshVertexAt(p0, p1); r["ret"] = MWpt3(rp);
  } },
  { "SetMeshVertexAt", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    gSDK->SetMeshVertexAt(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "NewCreateCombineIntoSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle p3 = JHandle(a,i);
    MCObjectHandle rh = gSDK->NewCreateCombineIntoSurface(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PushPullPlanarAddObjectID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->PushPullPlanarAddObjectID(p0); r["ret"]=nullptr;
  } },
  { "PushPullPlanarEnd", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->PushPullPlanarEnd(); r["ret"]=nullptr;
  } },
  { "PushPullPlanarIsEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->PushPullPlanarIsEnabled());
  } },
  { "PushPullPlanarSetEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->PushPullPlanarSetEnabled(p0); r["ret"]=nullptr;
  } },
  { "PushPullPlanarNeedsPickLoop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->PushPullPlanarNeedsPickLoop());
  } },
  { "PushPullPlanarAddPrefButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->PushPullPlanarAddPrefButton(); r["ret"]=nullptr;
  } },
  { "CreateProxyObjOnLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateProxyObjOnLayer(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetProxyParent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetProxyParent(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddClassWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (long long)(gSDK->AddClassWithUI(p0));
    r["out"]["inOutName"] = MStr(p0);
  } },
  { "EditClassWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->EditClassWithUI(p0));
  } },
  { "CloseDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->CloseDocument());
  } },
  { "GetNumStories", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumStories());
  } },
  { "GetNumLayerLevelTypes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumLayerLevelTypes());
  } },
  { "GetNumStoryLayerTemplates", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumStoryLayerTemplates());
  } },
  { "GetLayerLevelType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString rs = gSDK->GetLayerLevelType(p0); r["ret"] = MStr(rs);
  } },
  { "SetLayerLevelType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->SetLayerLevelType(p0, p1));
    r["out"]["layerLevelType"] = MStr(p1);
  } },
  { "GetStoryLayerTemplateName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetStoryLayerTemplateName(p0); r["ret"] = MStr(rs);
  } },
  { "GetStoryOfLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetStoryOfLayer(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetLayerForStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    MCObjectHandle rh = gSDK->GetLayerForStory(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    TXString p1;
    r["ret"] = (bool)(gSDK->CreateStory(p0, p1));
    r["out"]["name"] = MStr(p0);
    r["out"]["suffix"] = MStr(p1);
  } },
  { "CreateLayerLevelType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->CreateLayerLevelType(p0));
    r["out"]["name"] = MStr(p0);
  } },
  { "CreateStoryLayerTemplate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    double p1 = JReal(a,i);
    TXString p2;
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    short p5 = 0;
    r["ret"] = (bool)(gSDK->CreateStoryLayerTemplate(p0, p1, p2, p3, p4, p5));
    r["out"]["name"] = MStr(p0);
    r["out"]["layerLevelType"] = MStr(p2);
    r["out"]["index"] = (long long)p5;
  } },
  { "DeleteStoryLayerTemplate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteStoryLayerTemplate(p0));
  } },
  { "AssociateLayerWithStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AssociateLayerWithStory(p0, p1));
  } },
  { "GetStoryAbove", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetStoryAbove(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetStoryBelow", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetStoryBelow(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetStoryElevation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetStoryElevation(p0));
  } },
  { "SetStoryElevation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetStoryElevation(p0, p1));
  } },
  { "GetStorySuffix", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString rs = gSDK->GetStorySuffix(p0); r["ret"] = MStr(rs);
  } },
  { "SetStorySuffix", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetStorySuffix(p0, p1));
  } },
  { "HasObjectStoryBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->HasObjectStoryBounds(p0));
  } },
  { "DelObjectStoryBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->DelObjectStoryBounds(p0));
  } },
  { "GetObjectStoryBoundsCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetObjectStoryBoundsCount(p0));
  } },
  { "ConvertToPolylineWithTangentVertices", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->ConvertToPolylineWithTangentVertices(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateImageControl2", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4 = JStr(a,i);
    r["ret"] = (bool)(gSDK->CreateImageControl2(p0, p1, p2, p3, p4));
  } },
  { "UpdateImageControl2", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->UpdateImageControl2(p0, p1, p2));
  } },
  { "CreateImageButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->CreateImageButton(p0, p1, p2, p3));
  } },
  { "UpdateImageButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->UpdateImageButton(p0, p1, p2));
  } },
  { "CreateThumbnailPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateThumbnailPopup(p0, p1));
  } },
  { "AddButtonMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->AddButtonMode(p0); r["ret"]=nullptr;
  } },
  { "AddCheckMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->AddCheckMode(p0, p1); r["ret"]=nullptr;
  } },
  { "AddListBrowserImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (long long)(gSDK->AddListBrowserImage(p0, p1, p2));
  } },
  { "GetListBrowserMultImageIndexes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4;
    TXString p5;
    TXString p6;
    r["ret"] = (bool)(gSDK->GetListBrowserMultImageIndexes(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["imageSpec0"] = MStr(p4);
    r["out"]["imageSpec1"] = MStr(p5);
    r["out"]["imageSpec2"] = MStr(p6);
  } },
  { "SetListBrowserMultImageIndexes", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    TXString p6 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserMultImageIndexes(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "InsertEnhancedPullDownMenuItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (long long)(gSDK->InsertEnhancedPullDownMenuItem(p0, p1, p2, p3));
  } },
  { "InsertProposedClassOrLayerItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->InsertProposedClassOrLayerItem(p0, p1, p2, p3));
  } },
  { "AreAlertsAllowed", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->AreAlertsAllowed());
  } },
  { "GetWorksheetColumnSortPrecedence", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetWorksheetColumnSortPrecedence(p0, p1, p2));
  } },
  { "CreateRenderworksStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->CreateRenderworksStyle();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetStoryLayerTemplateInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    double p2 = 0;
    TXString p3;
    double p4 = 0;
    double p5 = 0;
    r["ret"] = (bool)(gSDK->GetStoryLayerTemplateInfo(p0, p1, p2, p3, p4, p5));
    r["out"]["name"] = MStr(p1);
    r["out"]["scaleFactor"] = (double)p2;
    r["out"]["layerLevelType"] = MStr(p3);
    r["out"]["elevationOffset"] = (double)p4;
    r["out"]["defaultWallHeight"] = (double)p5;
  } },
  { "GetObjectGeneratingAutoPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetObjectGeneratingAutoPlane();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetVertexMaxRadius", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (double)(gSDK->GetVertexMaxRadius(p0, p1));
  } },
  { "AlertSetAlwaysDoValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    gSDK->AlertSetAlwaysDoValue(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetCSGAction", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetCSGAction(p0));
  } },
  { "SupportCustomControlKeyEvents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SupportCustomControlKeyEvents(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTextJustificationN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetTextJustificationN(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTextVerticalAlignmentN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetTextVerticalAlignmentN(p0, p1); r["ret"]=nullptr;
  } },
  { "GetLayerLevelTypeName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetLayerLevelTypeName(p0); r["ret"] = MStr(rs);
  } },
  { "SetLayerLevelTypeName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetLayerLevelTypeName(p0, p1));
  } },
  { "SetStoryLayerTemplateName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetStoryLayerTemplateName(p0, p1));
  } },
  { "GetUserOriginGlobal", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0;
    r["ret"] = (bool)(gSDK->GetUserOriginGlobal(p0));
    r["out"]["outOrigin"] = MWpt(p0);
  } },
  { "GetVectorworksSessionID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString rs = gSDK->GetVectorworksSessionID(); r["ret"] = MStr(rs);
  } },
  { "EnableListBrowserHierarchicalDisplay", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->EnableListBrowserHierarchicalDisplay(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetListBrowserHierarchicalDisplayColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetListBrowserHierarchicalDisplayColumn(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetListBrowserNumericItemInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4 = JStr(a,i);
    double p5 = JReal(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserNumericItemInfo(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "StringToArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    double p1 = 0;
    r["ret"] = (bool)(gSDK->StringToArea(p0, p1));
    r["out"]["outArea"] = (double)p1;
  } },
  { "StringToVolume", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    double p1 = 0;
    r["ret"] = (bool)(gSDK->StringToVolume(p0, p1));
    r["out"]["outVolume"] = (double)p1;
  } },
  { "IsListBrowserDisplayHierarchical", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserDisplayHierarchical(p0, p1));
  } },
  { "HierarchicalListBrowserItemOpened", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    short p4 = 0;
    gSDK->HierarchicalListBrowserItemOpened(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["outNumbRedisplayedItems"] = (long long)p4;
  } },
  { "HierarchicalListBrowserItemClosed", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->HierarchicalListBrowserItemClosed(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "HierarchicalListBrowserItemIsClosed", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->HierarchicalListBrowserItemIsClosed(p0, p1, p2));
  } },
  { "HierarchicalListBrowserItemIsContainer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->HierarchicalListBrowserItemIsContainer(p0, p1, p2));
  } },
  { "GetDisplayedItemsCountInHierarchicalContainer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    short p3 = 0;
    gSDK->GetDisplayedItemsCountInHierarchicalContainer(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["outDisplayedItemsCount"] = (long long)p3;
  } },
  { "GetListBrowserItemOriginalName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString rs = gSDK->GetListBrowserItemOriginalName(p0, p1, p2); r["ret"] = MStr(rs);
  } },
  { "AddListBrowserOriginalName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->AddListBrowserOriginalName(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetListBrowserOriginalNameCloseLevels", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    Boolean p3 = 0;
    Boolean p4 = 0;
    Boolean p5 = 0;
    gSDK->GetListBrowserOriginalNameCloseLevels(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
    r["out"]["outLeve1Closed"] = (bool)(p3!=0);
    r["out"]["outLevel2Closed"] = (bool)(p4!=0);
    r["out"]["outLevel3Closed"] = (bool)(p5!=0);
  } },
  { "SetListBrowserOriginalNameCloseLevels", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    gSDK->SetListBrowserOriginalNameCloseLevels(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "CollapseAllListBrowserItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->CollapseAllListBrowserItems(p0, p1); r["ret"]=nullptr;
  } },
  { "ExpandAllListBrowserItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->ExpandAllListBrowserItems(p0, p1); r["ret"]=nullptr;
  } },
  { "SetToolHelpMessage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetToolHelpMessage(p0, p1));
  } },
  { "FindWallsSurroundingPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    long long p2 = JInt(a,i);
    MCObjectHandle p3 = JHandle(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    MCObjectHandle rh = gSDK->FindWallsSurroundingPoint(p0, p1, p2, p3, p4, p5);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetNumAssociations", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumAssociations(p0));
  } },
  { "GetAssociation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Sint16 p2 = 0;
    Sint16 p3 = 0;
    MCObjectHandle rh = gSDK->GetAssociation(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
    r["out"]["associationKind"] = (long long)p2;
    r["out"]["value"] = (long long)p3;
  } },
  { "AdjustPathForWrapping", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    long long p1 = JInt(a,i);
    gSDK->AdjustPathForWrapping(p0, p1); r["ret"]=nullptr;
    r["out"]["path"] = MStr(p0);
  } },
  { "DoBatchPrintOrExport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->DoBatchPrintOrExport(p0); r["ret"]=nullptr;
  } },
  { "DeleteObjectNoNotify", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->DeleteObjectNoNotify(p0); r["ret"]=nullptr;
  } },
  { "GetNumSavedViews", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumSavedViews());
  } },
  { "GetSavedView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetSavedView(p0, p1));
    r["out"]["view"] = MStr(p1);
  } },
  { "RestoreSavedView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->RestoreSavedView(p0); r["ret"]=nullptr;
  } },
  { "GetClPenPatN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetClPenPatN(p0));
  } },
  { "SetClPenPatN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetClPenPatN(p0, p1); r["ret"]=nullptr;
  } },
  { "GetDefaultPenPatN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetDefaultPenPatN());
  } },
  { "SetDefaultPenPatN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetDefaultPenPatN(p0); r["ret"]=nullptr;
  } },
  { "GetPenPatN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetPenPatN(p0));
  } },
  { "SetPenPatN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetPenPatN(p0, p1); r["ret"]=nullptr;
  } },
  { "GetLineTypeAttributeData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    InternalIndex p2 = 0;
    short p3 = 0;
    gSDK->GetLineTypeAttributeData(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["lineStyle"] = (long long)p2;
    r["out"]["lineWeight"] = (long long)p3;
  } },
  { "SetLineTypeAttributeData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetLineTypeAttributeData(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "GetLineTypeChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    gSDK->GetLineTypeChoice(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["lineTypeRefNumber"] = (long long)p2;
  } },
  { "SetLineTypeChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetLineTypeChoice(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "ShowComplexLineTypesInLineAttributePopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->ShowComplexLineTypesInLineAttributePopup(p0, p1); r["ret"]=nullptr;
  } },
  { "GetListBrowserItemLineTypeRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    Sint32 p4 = 0;
    Sint32 p5 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemLineTypeRef(p0, p1, p2, p3, p4, p5));
    r["out"]["iLineRef"] = (long long)p4;
    r["out"]["iLineWeight"] = (long long)p5;
  } },
  { "SetListBrowserItemLineTypeRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemLineTypeRef(p0, p1, p2, p3, p4, p5));
  } },
  { "IsWorksheetCellImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsWorksheetCellImage(p0, p1, p2, p3));
  } },
  { "GetWorksheetCellImageType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    short p3 = 0;
    gSDK->GetWorksheetCellImageType(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["type"] = (long long)p3;
  } },
  { "GetWorksheetCellImageSizeType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetWorksheetCellImageSizeType(p0, p1, p2));
  } },
  { "GetWorksheetCellImageSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    short p3 = 0;
    short p4 = 0;
    gSDK->GetWorksheetCellImageSize(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["height"] = (long long)p3;
    r["out"]["width"] = (long long)p4;
  } },
  { "GetWorksheetCellImageAngle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = 0;
    gSDK->GetWorksheetCellImageAngle(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["angle"] = (double)p3;
  } },
  { "GetWorksheetCellImageView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TStandardView p3 = 0;
    gSDK->GetWorksheetCellImageView(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["view"] = (long long)p3;
  } },
  { "GetWorksheetCellImageRenderMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TRenderMode p3 = 0;
    gSDK->GetWorksheetCellImageRenderMode(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["renderMode"] = (long long)p3;
  } },
  { "GetWorksheetCellImageUseLayerScale", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetWorksheetCellImageUseLayerScale(p0, p1, p2));
  } },
  { "GetWorksheetCellImageScale", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = 0;
    gSDK->GetWorksheetCellImageScale(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["scale"] = (double)p3;
  } },
  { "GetWorksheetCellImageUseObjectImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetWorksheetCellImageUseObjectImage(p0, p1, p2));
  } },
  { "DoPolylineRadiusSmoothing", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->DoPolylineRadiusSmoothing(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "TrimNurbsSurface", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->TrimNurbsSurface(p0, p1));
  } },
  { "InteractiveViewOperation_End", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->InteractiveViewOperation_End(); r["ret"]=nullptr;
  } },
  { "SetToolByIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetToolByIndex(p0); r["ret"]=nullptr;
  } },
  { "CreateLayerWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    MCObjectHandle rh = gSDK->CreateLayerWithUI(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
    r["out"]["name"] = MStr(p0);
  } },
  { "EditLayerWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->EditLayerWithUI(p0));
  } },
  { "CreateSavedViewWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->CreateSavedViewWithUI(p0));
    r["out"]["outName"] = MStr(p0);
  } },
  { "EditSavedViewWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->EditSavedViewWithUI(p0));
    r["out"]["inOutName"] = MStr(p0);
  } },
  { "CreateExtrudeAlongPath2", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    double p3 = JReal(a,i);
    bool p4 = JBool(a,i);
    bool p5 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateExtrudeAlongPath2(p0, p1, p2, p3, p4, p5);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsGBXMLExportAllowed", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsGBXMLExportAllowed());
  } },
  { "ConvertToGenericSolid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->ConvertToGenericSolid(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddWallToContainer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->AddWallToContainer(p0, p1); r["ret"]=nullptr;
  } },
  { "DeleteAssociations", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->DeleteAssociations(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateTaperedExtrude2", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateTaperedExtrude2(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "EnableTreeControlDragAndDrop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->EnableTreeControlDragAndDrop(p0, p1, p2));
  } },
  { "EnableDragBetweenControls", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->EnableDragBetweenControls(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetTreeControlItemParent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    Sint32 p3 = 0;
    r["ret"] = (bool)(gSDK->GetTreeControlItemParent(p0, p1, p2, p3));
    r["out"]["parentID"] = (long long)p3;
  } },
  { "CopyTreeControlSubtree", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    r["ret"] = (long long)(gSDK->CopyTreeControlSubtree(p0, p1, p2, p3, p4, p5));
  } },
  { "SetTreeControlItemImage", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetTreeControlItemImage(p0, p1, p2, p3));
  } },
  { "CreateComplexLineType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateComplexLineType(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetComplexLineTypeGeometryGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetComplexLineTypeGeometryGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddComplexLineTypeGeometryObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddComplexLineTypeGeometryObject(p0, p1));
  } },
  { "GetComplexLineTypeGroupParent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetComplexLineTypeGroupParent(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsComplexLineTypeGroupContainedObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsComplexLineTypeGroupContainedObject(p0));
  } },
  { "SetComplexLineTypePageSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComplexLineTypePageSpace(p0, p1));
  } },
  { "IsComplexLineTypeInPageSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsComplexLineTypeInPageSpace(p0));
  } },
  { "SetComplexLineTypeGapSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComplexLineTypeGapSize(p0, p1));
  } },
  { "GetComplexLineTypeGapSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetComplexLineTypeGapSize(p0));
  } },
  { "RemoveAllTreeControlItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->RemoveAllTreeControlItems(p0, p1); r["ret"]=nullptr;
  } },
  { "CreateGroupOutline", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateGroupOutline(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetNumberOfLineTypesItems", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumberOfLineTypesItems(p0, p1));
  } },
  { "GetLineTypeAtIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    InternalIndex p3 = 0;
    gSDK->GetLineTypeAtIndex(p0, p1, p2, p3); r["ret"]=nullptr;
    r["out"]["outLineTypeRefNumber"] = (long long)p3;
  } },
  { "Create2DObjectShadow", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    MCObjectHandle rh = gSDK->Create2DObjectShadow(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetToolPtCurrentIsSnapped", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetToolPtCurrentIsSnapped());
  } },
  { "Project3DModelPtToScreen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->Project3DModelPtToScreen(p0, p1));
    r["out"]["outwptScreen"] = MWpt(p1);
  } },
  { "GetImageCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetImageCropObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsImageCropped", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsImageCropped(p0));
  } },
  { "IsImageCropVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsImageCropVisible(p0));
  } },
  { "SetImageCropVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetImageCropVisible(p0, p1); r["ret"]=nullptr;
  } },
  { "SetImageCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetImageCropObject(p0, p1));
  } },
  { "GetNumViewportClassOverrides", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumViewportClassOverrides(p0));
  } },
  { "GetViewportClassOverrideClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetViewportClassOverrideClass(p0, p1));
  } },
  { "CreateViewportClassOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateViewportClassOverride(p0, p1));
  } },
  { "RemoveViewportClassOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveViewportClassOverride(p0, p1));
  } },
  { "GetNumViewportLightOverrides", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumViewportLightOverrides(p0));
  } },
  { "GetViewportLightOverrideLight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetViewportLightOverrideLight(p0, p1));
  } },
  { "CreateViewportLightOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateViewportLightOverride(p0, p1));
  } },
  { "RemoveViewportLightOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveViewportLightOverride(p0, p1));
  } },
  { "GetNumViewportLayerOverrides", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumViewportLayerOverrides(p0));
  } },
  { "GetViewportLayerOverrideLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetViewportLayerOverrideLayer(p0, p1));
  } },
  { "CreateViewportLayerOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateViewportLayerOverride(p0, p1));
  } },
  { "RemoveViewportLayerOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveViewportLayerOverride(p0, p1));
  } },
  { "GetNumViewportLayerPropertiesOverrides", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumViewportLayerPropertiesOverrides(p0));
  } },
  { "GetViewportLayerPropertiesOverrideLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetViewportLayerPropertiesOverrideLayer(p0, p1));
  } },
  { "CreateViewportLayerPropertiesOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateViewportLayerPropertiesOverride(p0, p1));
  } },
  { "RemoveViewportLayerPropertiesOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveViewportLayerPropertiesOverride(p0, p1));
  } },
  { "GetNumViewportLayerStackingOverrides", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumViewportLayerStackingOverrides(p0));
  } },
  { "GetViewportLayerStackingOverrideLayer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetViewportLayerStackingOverrideLayer(p0, p1));
  } },
  { "GetViewportLayerStackingOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetViewportLayerStackingOverride(p0, p1, p2));
    r["out"]["outStackingPosition"] = (long long)p2;
  } },
  { "SetViewportLayerStackingOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetViewportLayerStackingOverride(p0, p1, p2));
  } },
  { "RemoveViewportLayerStackingOverride", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveViewportLayerStackingOverride(p0, p1));
  } },
  { "IsDesignLayerViewport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsDesignLayerViewport(p0));
  } },
  { "TrackToolViewport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    MCObjectHandle rh = gSDK->TrackToolViewport(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateScriptResource", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    bool p2 = JBool(a,i);
    TXString p3 = JStr(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateScriptResource(p0, p1, p2, p3, p4));
  } },
  { "GetScriptResource", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1;
    bool p2 = 0;
    r["ret"] = (bool)(gSDK->GetScriptResource(p0, p1, p2));
    r["out"]["outScript"] = MStr(p1);
    r["out"]["outPython"] = (bool)(p2!=0);
  } },
  { "SetScriptResource", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetScriptResource(p0, p1, p2));
  } },
  { "OpenScriptResPalette", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->OpenScriptResPalette(p0, p1));
  } },
  { "GetWallHoleGroupDeep", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWallHoleGroupDeep(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateTextStyleResource", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateTextStyleResource(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DuplicateWorkingPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->DuplicateWorkingPlane(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteWorkingPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->DeleteWorkingPlane(p0); r["ret"]=nullptr;
  } },
  { "SysBeep", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SysBeep(p0); r["ret"]=nullptr;
  } },
  { "TickCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->TickCount());
  } },
  { "IsCurtainWall", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsCurtainWall(p0));
  } },
  { "GetCurtainWallPanelInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    bool p2 = JBool(a,i);
    WorldPt p3;
    WorldCoord p4 = 0;
    WorldCoord p5 = 0;
    r["ret"] = (bool)(gSDK->GetCurtainWallPanelInfo(p0, p1, p2, p3, p4, p5));
    r["out"]["outCenterPt"] = MWpt(p3);
    r["out"]["outWidth"] = (double)p4;
    r["out"]["outHeight"] = (double)p5;
  } },
  { "IsFontAvailable", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsFontAvailable(p0));
  } },
  { "ResetVisibilityForSymbol", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ResetVisibilityForSymbol(p0); r["ret"]=nullptr;
  } },
  { "CanSymbolBeAddedLegal", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->CanSymbolBeAddedLegal(p0, p1));
  } },
  { "CreateMesh", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->CreateMesh();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetPointInsidePoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1;
    r["ret"] = (bool)(gSDK->GetPointInsidePoly(p0, p1));
    r["out"]["insideWorldPt"] = MWpt(p1);
  } },
  { "GetStandardFontListSize", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetStandardFontListSize());
  } },
  { "SetTreeControlItemAsDivider", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->SetTreeControlItemAsDivider(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "GetTreeControlItemNumberOfChildren", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetTreeControlItemNumberOfChildren(p0, p1, p2));
  } },
  { "GetTreeControlItemChildID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetTreeControlItemChildID(p0, p1, p2, p3));
  } },
  { "SetTreeControlItemSelectionState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    gSDK->SetTreeControlItemSelectionState(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "GetVerticesFromSolid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetVerticesFromSolid(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetNurbsCurvesFromSolid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetNurbsCurvesFromSolid(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetNurbsSurfacesFromSolid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetNurbsSurfacesFromSolid(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetNurbsCurvesOnCuttingPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    MCObjectHandle rh = gSDK->GetNurbsCurvesOnCuttingPlane(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateImageMaskFromAlphaChannel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateImageMaskFromAlphaChannel(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ConvertPolylineToPolylineWithOnlyArcVertices", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->ConvertPolylineToPolylineWithOnlyArcVertices(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetTextTabStopCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    Sint32 p1 = 0;
    r["ret"] = (bool)(gSDK->GetTextTabStopCount(p0, p1));
    r["out"]["count"] = (long long)p1;
  } },
  { "GetTextTabStopLocation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetTextTabStopLocation(p0, p1, p2));
    r["out"]["location"] = (double)p2;
  } },
  { "MoveTextTabStopLocation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->MoveTextTabStopLocation(p0, p1, p2));
  } },
  { "AddTextTabStop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    r["ret"] = (bool)(gSDK->AddTextTabStop(p0, p1));
  } },
  { "RemoveTextTabStop", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RemoveTextTabStop(p0, p1));
  } },
  { "GetTextStyleByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetTextStyleByClass(p0));
  } },
  { "SetTextStyleByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SetTextStyleByClass(p0); r["ret"]=nullptr;
  } },
  { "GetClUseTextStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetClUseTextStyle(p0));
  } },
  { "SetClUseTextStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetClUseTextStyle(p0, p1); r["ret"]=nullptr;
  } },
  { "GetClTextStyleRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetClTextStyleRef(p0));
  } },
  { "SetClTextStyleRef", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetClTextStyleRef(p0, p1); r["ret"]=nullptr;
  } },
  { "GetObjectWallOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetObjectWallOffset(p0, p1, p2));
    r["out"]["offset"] = (double)p2;
  } },
  { "SetObjectWallHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetObjectWallHeight(p0, p1, p2));
  } },
  { "GetObjectWallHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetObjectWallHeight(p0, p1, p2));
    r["out"]["height"] = (double)p2;
  } },
  { "ClearHatchReferenceForMaterialNode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ClearHatchReferenceForMaterialNode(p0); r["ret"]=nullptr;
  } },
  { "GetDescriptionText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString rs = gSDK->GetDescriptionText(p0); r["ret"] = MStr(rs);
  } },
  { "SetDescriptionText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetDescriptionText(p0, p1));
  } },
  { "RefreshModeBar", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->RefreshModeBar(); r["ret"]=nullptr;
  } },
  { "ClearClearPullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->ClearClearPullDownMenu(p0); r["ret"]=nullptr;
  } },
  { "RefreshClassPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RefreshClassPopup(p0, p1));
  } },
  { "SetPerspectiveInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    WorldPt p3 = JWpt(a,i);
    WorldPt p4 = JWpt(a,i);
    long long p5 = JInt(a,i);
    gSDK->SetPerspectiveInfo(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "GetListBrowserHierarchicalDisplayColumn", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetListBrowserHierarchicalDisplayColumn(p0, p1));
  } },
  { "GetPDFPageCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetPDFPageCropObject(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsPDFPageCropped", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsPDFPageCropped(p0));
  } },
  { "IsPDFPageCropVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsPDFPageCropVisible(p0));
  } },
  { "SetPDFPageCropVisible", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetPDFPageCropVisible(p0, p1); r["ret"]=nullptr;
  } },
  { "SetPDFPageCropObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetPDFPageCropObject(p0, p1));
  } },
  { "SetPDFPageWidthAndHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetPDFPageWidthAndHeight(p0, p1, p2));
  } },
  { "SetCurrentView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetCurrentView(p0, p1); r["ret"]=nullptr;
  } },
  { "IsCurrentlyBuildingAnUndoEvent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsCurrentlyBuildingAnUndoEvent());
  } },
  { "ShowCustomDimensionStandardsDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->ShowCustomDimensionStandardsDialog());
  } },
  { "SetTextStyleRefN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetTextStyleRefN(p0, p1, p2, p3));
  } },
  { "GetTextStyleRefN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetTextStyleRefN(p0, p1));
  } },
  { "SetTextStyleByClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetTextStyleByClassN(p0, p1, p2));
  } },
  { "GetTextStyleByClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->GetTextStyleByClassN(p0, p1));
  } },
  { "GetNumStoryLevelTemplates", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumStoryLevelTemplates());
  } },
  { "GetStoryLevelTemplateName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetStoryLevelTemplateName(p0); r["ret"] = MStr(rs);
  } },
  { "SetStoryLevelTemplateName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetStoryLevelTemplateName(p0, p1));
  } },
  { "CreateStoryLevelTemplate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    double p1 = JReal(a,i);
    TXString p2;
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    short p5 = 0;
    r["ret"] = (bool)(gSDK->CreateStoryLevelTemplate(p0, p1, p2, p3, p4, p5));
    r["out"]["name"] = MStr(p0);
    r["out"]["layerLevelType"] = MStr(p2);
    r["out"]["index"] = (long long)p5;
  } },
  { "DeleteStoryLevelTemplate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteStoryLevelTemplate(p0));
  } },
  { "GetStoryLevelTemplateInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    double p2 = 0;
    TXString p3;
    double p4 = 0;
    double p5 = 0;
    r["ret"] = (bool)(gSDK->GetStoryLevelTemplateInfo(p0, p1, p2, p3, p4, p5));
    r["out"]["name"] = MStr(p1);
    r["out"]["scaleFactor"] = (double)p2;
    r["out"]["layerLevelType"] = MStr(p3);
    r["out"]["elevationOffset"] = (double)p4;
    r["out"]["defaultWallHeight"] = (double)p5;
  } },
  { "AddStoryLevel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    double p2 = JReal(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->AddStoryLevel(p0, p1, p2, p3));
  } },
  { "AddStoryLevelFromTemplate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->AddStoryLevelFromTemplate(p0, p1));
  } },
  { "RemoveStoryLevel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->RemoveStoryLevel(p0, p1, p2));
  } },
  { "SetStoryLevelElevation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetStoryLevelElevation(p0, p1, p2));
  } },
  { "GetStoryLevelElevation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (double)(gSDK->GetStoryLevelElevation(p0, p1));
  } },
  { "ResetDefaultStoryLevels", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ResetDefaultStoryLevels(p0));
  } },
  { "GetComponentTopIsRelativeToStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentTopIsRelativeToStory(p0, p1, p2));
    r["out"]["topIsRelativeToStory"] = (bool)(p2!=0);
  } },
  { "SetComponentTopIsRelativeToStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentTopIsRelativeToStory(p0, p1, p2));
  } },
  { "GetComponentBottomIsRelativeToStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentBottomIsRelativeToStory(p0, p1, p2));
    r["out"]["bottomIsRelativeToStory"] = (bool)(p2!=0);
  } },
  { "SetComponentBottomIsRelativeToStory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentBottomIsRelativeToStory(p0, p1, p2));
  } },
  { "ShowListBrowserHeader", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->ShowListBrowserHeader(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetListBrowserNumericItemInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    TXString p4;
    double p5 = 0;
    short p6 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserNumericItemInfo(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["itemString"] = MStr(p4);
    r["out"]["itemVal"] = (double)p5;
    r["out"]["imageIndex"] = (long long)p6;
  } },
  { "AddPullDownResourceMethod", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    gSDK->AddPullDownResourceMethod(p0, p1); r["ret"]=nullptr;
  } },
  { "SetPullDownResourceValue", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->SetPullDownResourceValue(p0, p1); r["ret"]=nullptr;
  } },
  { "SetImagePopupResourceAdvanced", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetImagePopupResourceAdvanced(p0, p1); r["ret"]=nullptr;
  } },
  { "GetClassSharedAndUpdateReference", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = 0;
    bool p3 = 0;
    r["ret"] = (bool)(gSDK->GetClassSharedAndUpdateReference(p0, p1, p2, p3));
    r["out"]["outSharedRef"] = (bool)(p2!=0);
    r["out"]["outUpdateRef"] = (bool)(p3!=0);
  } },
  { "SetObjectAsSpanWallBreak", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetObjectAsSpanWallBreak(p0, p1, p2));
  } },
  { "GetTreeControlItemCheckBoxState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    Sint32 p3 = 0;
    r["ret"] = (bool)(gSDK->GetTreeControlItemCheckBoxState(p0, p1, p2, p3));
    r["out"]["outState"] = (long long)p3;
  } },
  { "SetTreeControlItemCheckBoxState", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetTreeControlItemCheckBoxState(p0, p1, p2, p3, p4));
  } },
  { "CreateShellSolid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateShellSolid(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateSlabModifier", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateSlabModifier(p0, p1, p2, p3, p4));
  } },
  { "GetParentFolderNameFromResourceList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2;
    gSDK->GetParentFolderNameFromResourceList(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["name"] = MStr(p2);
  } },
  { "GetRoofStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetRoofStyle(p0));
  } },
  { "SetRoofStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetRoofStyle(p0, p1); r["ret"]=nullptr;
  } },
  { "ConvertToUnstyledRoof", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ConvertToUnstyledRoof(p0); r["ret"]=nullptr;
  } },
  { "GetRoofPreferencesStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetRoofPreferencesStyle());
  } },
  { "SetRoofPreferencesStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->SetRoofPreferencesStyle(p0); r["ret"]=nullptr;
  } },
  { "CreateRoofStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->CreateRoofStyle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetRoofPreferences", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetRoofPreferences();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetDatumRoofComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetDatumRoofComponent(p0));
  } },
  { "SetDatumRoofComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetDatumRoofComponent(p0, p1); r["ret"]=nullptr;
  } },
  { "BuildResourceListFromOpenFile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (long long)(gSDK->BuildResourceListFromOpenFile(p0, p1, p2));
    r["out"]["numItems"] = (long long)p2;
  } },
  { "SwitchToOpenFile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SwitchToOpenFile(p0));
  } },
  { "CalcRoofTopArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = 0;
    gSDK->CalcRoofTopArea(p0, p1); r["ret"]=nullptr;
    r["out"]["outArea"] = (double)p1;
  } },
  { "SwitchFromPlanTo3DView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SwitchFromPlanTo3DView(); r["ret"]=nullptr;
  } },
  { "UngroupObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->UngroupObject(p0); r["ret"]=nullptr;
  } },
  { "ConvertToGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->ConvertToGroup(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SymbolsInGroupToGroups", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->SymbolsInGroupToGroups(p0); r["ret"]=nullptr;
  } },
  { "GetCheckoutsComment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->GetCheckoutsComment(p0));
    r["out"]["comment"] = MStr(p0);
  } },
  { "SetCheckoutsComment", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetCheckoutsComment(p0));
  } },
  { "GetCurrentUserId", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->GetCurrentUserId(p0));
    r["out"]["userid"] = MStr(p0);
  } },
  { "GetProjectFullPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->GetProjectFullPath(p0));
    r["out"]["outFilePath"] = MStr(p0);
  } },
  { "GetWorkingFileId", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->GetWorkingFileId(p0));
    r["out"]["uuid"] = MStr(p0);
  } },
  { "IsAWorkingFile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsAWorkingFile());
  } },
  { "IsProjectOffline", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsProjectOffline());
  } },
  { "GetCustomScreenFeedbackGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomScreenFeedbackGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetCustomScreenFeedbackGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomScreenFeedbackGroup(p0, p1));
  } },
  { "SetCurrentLayerN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetCurrentLayerN(p0, p1); r["ret"]=nullptr;
  } },
  { "GetViewFromAndToPoints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0;
    WorldPt3 p1;
    r["ret"] = (bool)(gSDK->GetViewFromAndToPoints(p0, p1));
    r["out"]["fromPt"] = MWpt3(p0);
    r["out"]["toPt"] = MWpt3(p1);
  } },
  { "GetComponentDatumIsTopOfComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentDatumIsTopOfComponent(p0, p1, p2));
    r["out"]["datumIsTopOfComponent"] = (bool)(p2!=0);
  } },
  { "SetComponentDatumIsTopOfComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentDatumIsTopOfComponent(p0, p1, p2));
  } },
  { "GetComponentBoundOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentBoundOffset(p0, p1, p2));
    r["out"]["boundOffset"] = (double)p2;
  } },
  { "SetComponentBoundOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComponentBoundOffset(p0, p1, p2));
  } },
  { "GetComponentAlwaysAutoJoinInCappedJoinMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentAlwaysAutoJoinInCappedJoinMode(p0, p1, p2));
    r["out"]["alwaysAutoJoinInCappedJoinMode"] = (bool)(p2!=0);
  } },
  { "SetComponentAlwaysAutoJoinInCappedJoinMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentAlwaysAutoJoinInCappedJoinMode(p0, p1, p2));
  } },
  { "GetComponentAlternateSectionFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Sint32 p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentAlternateSectionFill(p0, p1, p2));
    r["out"]["alternateSectionFill"] = (long long)p2;
  } },
  { "SetComponentAlternateSectionFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentAlternateSectionFill(p0, p1, p2));
  } },
  { "GetComponentPenStylesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    InternalIndex p2 = 0;
    InternalIndex p3 = 0;
    r["ret"] = (bool)(gSDK->GetComponentPenStylesN(p0, p1, p2, p3));
    r["out"]["leftPenStyle"] = (long long)p2;
    r["out"]["rightPenStyle"] = (long long)p3;
  } },
  { "SetComponentPenStylesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentPenStylesN(p0, p1, p2, p3));
  } },
  { "GetComponentAlternateSectionFillColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    ColorRef p2 = 0;
    ColorRef p3 = 0;
    r["ret"] = (bool)(gSDK->GetComponentAlternateSectionFillColors(p0, p1, p2, p3));
    r["out"]["alternateSectionFillForeColor"] = (long long)p2;
    r["out"]["alternateSectionFillBackColor"] = (long long)p3;
  } },
  { "SetComponentAlternateSectionFillColors", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentAlternateSectionFillColors(p0, p1, p2, p3));
  } },
  { "GetComponentUseClassFillStyleForFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassFillStyleForFill(p0, p1, p2));
    r["out"]["useClassFillStyleForFill"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassFillStyleForFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassFillStyleForFill(p0, p1, p2));
  } },
  { "GetComponentUseClassFillColorsForFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassFillColorsForFill(p0, p1, p2));
    r["out"]["useClassFillColorsForFill"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassFillColorsForFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassFillColorsForFill(p0, p1, p2));
  } },
  { "GetComponentUseClassFillStyleForAlternateSectionFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassFillStyleForAlternateSectionFill(p0, p1, p2));
    r["out"]["useClassFillStyleForAlternateSectionFill"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassFillStyleForAlternateSectionFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassFillStyleForAlternateSectionFill(p0, p1, p2));
  } },
  { "GetComponentUseClassFillColorsForAlternateSectionFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassFillColorsForAlternateSectionFill(p0, p1, p2));
    r["out"]["useClassFillColorsForAlternateSectionFill"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassFillColorsForAlternateSectionFill", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassFillColorsForAlternateSectionFill(p0, p1, p2));
  } },
  { "GetComponentUseClassPenStyleForLeftPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassPenStyleForLeftPen(p0, p1, p2));
    r["out"]["useClassPenStyleForLeftPen"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassPenStyleForLeftPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassPenStyleForLeftPen(p0, p1, p2));
  } },
  { "GetComponentUseClassPenWeightForLeftPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassPenWeightForLeftPen(p0, p1, p2));
    r["out"]["useClassPenWeightForLeftPen"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassPenWeightForLeftPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassPenWeightForLeftPen(p0, p1, p2));
  } },
  { "GetComponentUseClassPenColorsForLeftPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassPenColorsForLeftPen(p0, p1, p2));
    r["out"]["useClassPenColorsForLeftPen"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassPenColorsForLeftPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassPenColorsForLeftPen(p0, p1, p2));
  } },
  { "GetComponentUseClassPenStyleForRightPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassPenStyleForRightPen(p0, p1, p2));
    r["out"]["useClassPenStyleForRightPen"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassPenStyleForRightPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassPenStyleForRightPen(p0, p1, p2));
  } },
  { "GetComponentUseClassPenWeightForRightPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassPenWeightForRightPen(p0, p1, p2));
    r["out"]["useClassPenWeightForRightPen"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassPenWeightForRightPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassPenWeightForRightPen(p0, p1, p2));
  } },
  { "GetComponentUseClassPenColorsForRightPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentUseClassPenColorsForRightPen(p0, p1, p2));
    r["out"]["useClassPenColorsForRightPen"] = (bool)(p2!=0);
  } },
  { "SetComponentUseClassPenColorsForRightPen", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentUseClassPenColorsForRightPen(p0, p1, p2));
  } },
  { "SetIsCurtainWall", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetIsCurtainWall(p0, p1); r["ret"]=nullptr;
  } },
  { "MirrorObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    WorldPt p2 = JWpt(a,i);
    WorldPt p3 = JWpt(a,i);
    MCObjectHandle rh = gSDK->MirrorObject(p0, p1, p2, p3);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ResetNurbsCurve", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    bool p2 = JBool(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->ResetNurbsCurve(p0, p1, p2, p3));
  } },
  { "SetArc", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetArc(p0, p1, p2, p3, p4));
  } },
  { "SetOpacityByClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetOpacityByClassN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetOpacityByClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    Boolean p1 = 0;
    Boolean p2 = 0;
    gSDK->GetOpacityByClassN(p0, p1, p2); r["ret"]=nullptr;
    r["out"]["outPenOpacityByClass"] = (bool)(p1!=0);
    r["out"]["outFillOpacityByClass"] = (bool)(p2!=0);
  } },
  { "GetDefaultOpacityByClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    Boolean p0 = 0;
    Boolean p1 = 0;
    gSDK->GetDefaultOpacityByClassN(p0, p1); r["ret"]=nullptr;
    r["out"]["outPenOpacityByClass"] = (bool)(p0!=0);
    r["out"]["outFillOpacityByClass"] = (bool)(p1!=0);
  } },
  { "SetDefaultOpacityByClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetDefaultOpacityByClassN(p0, p1); r["ret"]=nullptr;
  } },
  { "MarqueeEmptyList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->MarqueeEmptyList());
  } },
  { "MarqueeAddObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->MarqueeAddObject(p0));
  } },
  { "GetFreehandInteractivePoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->GetFreehandInteractivePoly();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "BeginFreehandInteractive", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->BeginFreehandInteractive(); r["ret"]=nullptr;
  } },
  { "UpdateFreehandInteractive", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->UpdateFreehandInteractive(); r["ret"]=nullptr;
  } },
  { "EndFreehandInteractive", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->EndFreehandInteractive();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsPlanRotationView", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsPlanRotationView());
  } },
  { "CreateHelicalAlongCurve", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    double p4 = 0;
    double p5 = 0;
    bool p6 = JBool(a,i);
    bool p7 = JBool(a,i);
    bool p8 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateHelicalAlongCurve(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
    r["out"]["pitch"] = (double)p4;
    r["out"]["numTurns"] = (double)p5;
  } },
  { "ViewRestoreN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->ViewRestoreN(p0, p1); r["ret"]=nullptr;
  } },
  { "RestoreSavedViewN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    gSDK->RestoreSavedViewN(p0, p1); r["ret"]=nullptr;
  } },
  { "RemoveCustomTextureParts", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->RemoveCustomTextureParts(p0, p1); r["ret"]=nullptr;
  } },
  { "AddCustomTexturePart", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    gSDK->AddCustomTexturePart(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CustomTexturePartExists", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CustomTexturePartExists(p0, p1, p2));
  } },
  { "ApplyCustomTexturePart", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->ApplyCustomTexturePart(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "GetObjectByUuid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    MCObjectHandle rh = gSDK->GetObjectByUuid(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetObjectUuid", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetObjectUuid(p0, p1));
    r["out"]["uuid"] = MStr(p1);
  } },
  { "IsDropShadowEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsDropShadowEnabled(p0));
  } },
  { "EnableDropShadow", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->EnableDropShadow(p0, p1); r["ret"]=nullptr;
  } },
  { "DeleteDropShadowData", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->DeleteDropShadowData(p0); r["ret"]=nullptr;
  } },
  { "IsDropShadowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsDropShadowByClass(p0));
  } },
  { "SetDropShadowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetDropShadowByClass(p0, p1); r["ret"]=nullptr;
  } },
  { "IsDropShadowEnabledInDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsDropShadowEnabledInDocument());
  } },
  { "SetDropShadowByClassInDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->SetDropShadowByClassInDocument(p0); r["ret"]=nullptr;
  } },
  { "AddDrain", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (long long)(gSDK->AddDrain(p0, p1, p2, p3));
  } },
  { "ConnectDrains", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    r["ret"] = (long long)(gSDK->ConnectDrains(p0, p1, p2, p3, p4, p5));
  } },
  { "AddSlopeValley", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    r["ret"] = (long long)(gSDK->AddSlopeValley(p0, p1, p2, p3, p4));
  } },
  { "GetNumDrains", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetNumDrains(p0));
  } },
  { "SetDrainHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetDrainHeight(p0, p1, p2));
  } },
  { "GetDrainHeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (double)(gSDK->GetDrainHeight(p0, p1));
  } },
  { "GetDrainLocation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt rp = gSDK->GetDrainLocation(p0, p1); r["ret"] = MWpt(rp);
  } },
  { "SetDrainLocation", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt p2 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetDrainLocation(p0, p1, p2));
  } },
  { "RotateDrain", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    gSDK->RotateDrain(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetDrainDrainageArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (double)(gSDK->GetDrainDrainageArea(p0, p1));
  } },
  { "GetDrainSymbol", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetDrainSymbol(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetDrainSymbol", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetDrainSymbol(p0, p1, p2));
  } },
  { "GetNumDrainSlopeValleys", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetNumDrainSlopeValleys(p0, p1));
  } },
  { "GetDrainSlopeValley", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    WorldPt p3;
    double p4 = 0;
    double p5 = 0;
    bool p6 = 0;
    r["ret"] = (bool)(gSDK->GetDrainSlopeValley(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["controlPt"] = MWpt(p3);
    r["out"]["slope"] = (double)p4;
    r["out"]["edgeHeight"] = (double)p5;
    r["out"]["heightLocked"] = (bool)(p6!=0);
  } },
  { "SetDrainSlopeValley", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    WorldPt p3 = JWpt(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    bool p6 = JBool(a,i);
    gSDK->SetDrainSlopeValley(p0, p1, p2, p3, p4, p5, p6); r["ret"]=nullptr;
  } },
  { "GetDrainConnectionIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetDrainConnectionIndex(p0, p1, p2));
  } },
  { "GetDrainConnection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    short p2 = 0;
    short p3 = 0;
    short p4 = 0;
    double p5 = 0;
    double p6 = 0;
    r["ret"] = (bool)(gSDK->GetDrainConnection(p0, p1, p2, p3, p4, p5, p6));
    r["out"]["drain1"] = (long long)p2;
    r["out"]["drain2"] = (long long)p3;
    r["out"]["style"] = (long long)p4;
    r["out"]["angle1"] = (double)p5;
    r["out"]["angle2"] = (double)p6;
  } },
  { "SetDrainConnection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetDrainConnection(p0, p1, p2, p3, p4));
  } },
  { "DeleteDrainConnection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteDrainConnection(p0, p1));
  } },
  { "DeleteSlopeValley", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->DeleteSlopeValley(p0, p1, p2, p3));
  } },
  { "DeleteDrain", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->DeleteDrain(p0, p1));
  } },
  { "ChoosePluginStyleForReplace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ChoosePluginStyleForReplace(p0); r["ret"]=nullptr;
  } },
  { "GetSymbolDefSubType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetSymbolDefSubType(p0));
  } },
  { "SetSymbolDefSubType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetSymbolDefSubType(p0, p1); r["ret"]=nullptr;
  } },
  { "GetLayerCutPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetLayerCutPlane(p0));
  } },
  { "SetLayerCutPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetLayerCutPlane(p0, p1); r["ret"]=nullptr;
  } },
  { "GetWallBelowCutPlaneClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetWallBelowCutPlaneClass(p0));
  } },
  { "SetWallBelowCutPlaneClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetWallBelowCutPlaneClass(p0, p1); r["ret"]=nullptr;
  } },
  { "GetTaperedComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetTaperedComponent(p0));
  } },
  { "SetTaperedComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetTaperedComponent(p0, p1); r["ret"]=nullptr;
  } },
  { "GetComponentAutoBoundEdgeOffsetOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentAutoBoundEdgeOffsetOffset(p0, p1, p2));
    r["out"]["autoBoundEdgeOffsetOffset"] = (double)p2;
  } },
  { "SetComponentAutoBoundEdgeOffsetOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetComponentAutoBoundEdgeOffsetOffset(p0, p1, p2));
  } },
  { "GetComponentMasterSnaps", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    Boolean p2 = 0;
    Boolean p3 = 0;
    r["ret"] = (bool)(gSDK->GetComponentMasterSnaps(p0, p1, p2, p3));
    r["out"]["masterSnapOnLeft"] = (bool)(p2!=0);
    r["out"]["masterSnapOnRight"] = (bool)(p3!=0);
  } },
  { "SetComponentMasterSnaps", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetComponentMasterSnaps(p0, p1, p2, p3));
  } },
  { "PullDownResourceGetSelectedResourceName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->PullDownResourceGetSelectedResourceName(p0); r["ret"] = MStr(rs);
  } },
  { "PullDownResourceSetSelectedResourceName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->PullDownResourceSetSelectedResourceName(p0, p1); r["ret"]=nullptr;
  } },
  { "PullDownResourceLayoutGetSelectedResourceName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString rs = gSDK->PullDownResourceLayoutGetSelectedResourceName(p0, p1); r["ret"] = MStr(rs);
  } },
  { "PullDownResourceLayoutSetSelectedResourceName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->PullDownResourceLayoutSetSelectedResourceName(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetWorksheetImageScaleFactor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetWorksheetImageScaleFactor(p0));
  } },
  { "SetWorksheetImageScaleFactor", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetWorksheetImageScaleFactor(p0, p1, p2));
  } },
  { "SetWorksheetCellsImageResolution", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetWorksheetCellsImageResolution(p0, p1); r["ret"]=nullptr;
  } },
  { "GetWorksheetCellsImageResolution", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetWorksheetCellsImageResolution(p0));
  } },
  { "CreateResourceFolder", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateResourceFolder(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetToolHelpMessageAndTitle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetToolHelpMessageAndTitle(p0, p1, p2));
  } },
  { "IsPluginStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsPluginStyle(p0));
  } },
  { "IsActiveSymbolInCurrentDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsActiveSymbolInCurrentDocument());
  } },
  { "RemoveItemFromPluginStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->RemoveItemFromPluginStyle(p0, p1));
  } },
  { "AddResourceToListUnsorted", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->AddResourceToListUnsorted(p0, p1));
  } },
  { "RemoveItemFromPluginStyleEditList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->RemoveItemFromPluginStyleEditList(p0, p1));
  } },
  { "OffsetPolyClosed", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    bool p2 = JBool(a,i);
    MCObjectHandle rh = gSDK->OffsetPolyClosed(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateFillSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateFillSpace(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CountFillSpaces", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->CountFillSpaces(p0));
  } },
  { "GetFillSpace", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    MCObjectHandle rh = gSDK->GetFillSpace(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetCurlProxyInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    TXString p1;
    Sint32 p2 = 0;
    TXString p3;
    TXString p4;
    r["ret"] = (bool)(gSDK->GetCurlProxyInfo(p0, p1, p2, p3, p4));
    r["out"]["outProxyType"] = MStr(p0);
    r["out"]["outAddress"] = MStr(p1);
    r["out"]["outPort"] = (long long)p2;
    r["out"]["outUsername"] = MStr(p3);
    r["out"]["outPassword"] = MStr(p4);
  } },
  { "DrawHotSpots", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->DrawHotSpots(); r["ret"]=nullptr;
  } },
  { "IsSymDefUsedInEditContext", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsSymDefUsedInEditContext(p0));
  } },
  { "SelectPluginCatalog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SelectPluginCatalog(p0));
  } },
  { "AplyFirstCatalogItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->AplyFirstCatalogItem(p0, p1));
  } },
  { "IsCatalogParameter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->IsCatalogParameter(p0, p1));
  } },
  { "SetUseCatalogItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetUseCatalogItem(p0, p1); r["ret"]=nullptr;
  } },
  { "GetUseCatalogItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetUseCatalogItem(p0));
  } },
  { "SetCatalogItemByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetCatalogItemByStyle(p0, p1); r["ret"]=nullptr;
  } },
  { "GetCatalogItemByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetCatalogItemByStyle(p0));
  } },
  { "GetWallEndCapFootPrint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->GetWallEndCapFootPrint(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetToolPt2D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldPt p1 = JWpt(a,i);
    r["ret"] = (bool)(gSDK->SetToolPt2D(p0, p1));
  } },
  { "SetToolPt3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    r["ret"] = (bool)(gSDK->SetToolPt3D(p0, p1));
  } },
  { "GetObjTypeProperties", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (long long)(gSDK->GetObjTypeProperties(p0));
  } },
  { "GetWorksheetImageShowDBHeaders", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetWorksheetImageShowDBHeaders(p0));
  } },
  { "SetWorksheetImageShowDBHeaders", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetWorksheetImageShowDBHeaders(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "SetFocusOnSelectedViewPane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetFocusOnSelectedViewPane(p0, p1); r["ret"]=nullptr;
  } },
  { "GetPageBoundsN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldRect p1;
    gSDK->GetPageBoundsN(p0, p1); r["ret"]=nullptr;
    r["out"]["bounds"] = MWrect(p1);
  } },
  { "GetDlgCtrlWidthStdChar", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    r["ret"] = (long long)(gSDK->GetDlgCtrlWidthStdChar(p0));
  } },
  { "GetHierarchicalListBrowserRowContainerPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    TXString rs = gSDK->GetHierarchicalListBrowserRowContainerPath(p0, p1, p2); r["ret"] = MStr(rs);
  } },
  { "SelectInResourceManager", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SelectInResourceManager(p0));
  } },
  { "BeginMultipleMove", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->BeginMultipleMove());
  } },
  { "EndMultipleMove", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->EndMultipleMove());
  } },
  { "GetWallAngleVector", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2;
    r["ret"] = (bool)(gSDK->GetWallAngleVector(p0, p1, p2));
    r["out"]["wallVector"] = MWpt(p2);
  } },
  { "GetPDFAnnotationsCount", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetPDFAnnotationsCount(p0));
  } },
  { "SetDashLineTypeName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetDashLineTypeName(p0, p1));
  } },
  { "GetDashLineTypeName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetDashLineTypeName(p0); r["ret"] = MStr(rs);
  } },
  { "GetDLComponentPenStylesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    InternalIndex p1 = 0;
    InternalIndex p2 = 0;
    r["ret"] = (bool)(gSDK->GetDLComponentPenStylesN(p0, p1, p2));
    r["out"]["outPenStyleLeft"] = (long long)p1;
    r["out"]["outPenStyleRight"] = (long long)p2;
  } },
  { "SetDLComponentPenStylesN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetDLComponentPenStylesN(p0, p1, p2));
  } },
  { "InsertNewDLComponentN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    double p1 = JReal(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    r["ret"] = (bool)(gSDK->InsertNewDLComponentN(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "InsertNewComponentN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    double p2 = JReal(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    long long p7 = JInt(a,i);
    r["ret"] = (bool)(gSDK->InsertNewComponentN(p0, p1, p2, p3, p4, p5, p6, p7));
  } },
  { "IsDashLineStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsDashLineStyle(p0));
  } },
  { "GetPseudoDashIndexFromDashLineType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    Sint16 p1 = 0;
    r["ret"] = (bool)(gSDK->GetPseudoDashIndexFromDashLineType(p0, p1));
    r["out"]["pseudoIndex"] = (long long)p1;
  } },
  { "GetDashLineTypeFromPseudoDashIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    InternalIndex p1 = 0;
    r["ret"] = (bool)(gSDK->GetDashLineTypeFromPseudoDashIndex(p0, p1));
    r["out"]["lineStyle"] = (long long)p1;
  } },
  { "BeginMultiplePseudoDashIndexConvert", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->BeginMultiplePseudoDashIndexConvert(); r["ret"]=nullptr;
  } },
  { "EndMultiplePseudoDashIndexConvert", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->EndMultiplePseudoDashIndexConvert(); r["ret"]=nullptr;
  } },
  { "CreateSearchEditBox", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateSearchEditBox(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateSymbolDefinitionForDisplayControl", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    MCObjectHandle rh = gSDK->CreateSymbolDefinitionForDisplayControl(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
    r["out"]["inoutName"] = MStr(p0);
  } },
  { "SetMirrorEmpty2DComponents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetMirrorEmpty2DComponents(p0, p1));
  } },
  { "GetMirrorEmpty2DComponents", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetMirrorEmpty2DComponents(p0));
  } },
  { "GetActiveSymbolName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString rs = gSDK->GetActiveSymbolName(); r["ret"] = MStr(rs);
  } },
  { "CreateEditPassword", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->CreateEditPassword(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CreateTemporaryCustomObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateTemporaryCustomObject(p0, p1, p2);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "UpdatePIOFromStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->UpdatePIOFromStyle(p0); r["ret"]=nullptr;
  } },
  { "GetPageMargins", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = 0;
    double p2 = 0;
    double p3 = 0;
    double p4 = 0;
    gSDK->GetPageMargins(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["left"] = (double)p1;
    r["out"]["right"] = (double)p2;
    r["out"]["bottom"] = (double)p3;
    r["out"]["top"] = (double)p4;
  } },
  { "CreateLayerPullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateLayerPullDownMenu(p0, p1, p2));
  } },
  { "Project3DPointOnPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0 = JWpt3(a,i);
    WorldPt3 p1 = JWpt3(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    WorldPt3 p3 = JWpt3(a,i);
    WorldPt3 rp = gSDK->Project3DPointOnPlane(p0, p1, p2, p3); r["ret"] = MWpt3(rp);
  } },
  { "ShowDetailedMemoryInfoDlg", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ShowDetailedMemoryInfoDlg(); r["ret"]=nullptr;
  } },
  { "GetCustomObjectProfileGroupInAux", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomObjectProfileGroupInAux(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "EditSymbolMarkersDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2;
    TXString p3;
    r["ret"] = (bool)(gSDK->EditSymbolMarkersDialog(p0, p1, p2, p3));
    r["out"]["inOutStartMarkerSymName"] = MStr(p2);
    r["out"]["inOutEndMarkerSymName"] = MStr(p3);
  } },
  { "CreateSearchablePulldownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateSearchablePulldownMenu(p0, p1, p2));
  } },
  { "InsertStaticItemInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    bool p6 = JBool(a,i);
    r["ret"] = (bool)(gSDK->InsertStaticItemInSearchablePulldown(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "InsertItemInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    bool p6 = JBool(a,i);
    r["ret"] = (bool)(gSDK->InsertItemInSearchablePulldown(p0, p1, p2, p3, p4, p5, p6));
  } },
  { "InsertChildItemInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    TXString p6 = JStr(a,i);
    bool p7 = JBool(a,i);
    r["ret"] = (bool)(gSDK->InsertChildItemInSearchablePulldown(p0, p1, p2, p3, p4, p5, p6, p7));
  } },
  { "ClearChoicesFromSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->ClearChoicesFromSearchablePulldown(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetActiveIDStrFromSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString rs = gSDK->GetActiveIDStrFromSearchablePulldown(p0, p1); r["ret"] = MStr(rs);
  } },
  { "SetActiveIDStrInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetActiveIDStrInSearchablePulldown(p0, p1, p2));
  } },
  { "GetDisplayNameFromIDStrInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3;
    r["ret"] = (bool)(gSDK->GetDisplayNameFromIDStrInSearchablePulldown(p0, p1, p2, p3));
    r["out"]["outName"] = MStr(p3);
  } },
  { "GetIDStrFromDisplayNameInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3;
    r["ret"] = (bool)(gSDK->GetIDStrFromDisplayNameInSearchablePulldown(p0, p1, p2, p3));
    r["out"]["outIDStr"] = MStr(p3);
  } },
  { "GetWallRecessGeometryGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWallRecessGeometryGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetWallRecessGeometryGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetWallRecessGeometryGroup(p0, p1));
  } },
  { "IsListBrowserItem3StateCheckBoxEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserItem3StateCheckBoxEnabled(p0, p1, p2, p3));
  } },
  { "EndAndRemoveUndoEvent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->EndAndRemoveUndoEvent());
  } },
  { "ClearUndoTableDueToUnsupportedAction", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ClearUndoTableDueToUnsupportedAction(); r["ret"]=nullptr;
  } },
  { "AlertDialogWithHyperlink", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    gSDK->AlertDialogWithHyperlink(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "IsListBrowserExternalSortEnabled", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserExternalSortEnabled(p0, p1));
  } },
  { "Get2DComponentsByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->Get2DComponentsByStyle(p0));
  } },
  { "Set2DComponentsByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->Set2DComponentsByStyle(p0, p1));
  } },
  { "GetMirrorEmpty2DComponentsByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetMirrorEmpty2DComponentsByStyle(p0));
  } },
  { "SetMirrorEmpty2DComponentsByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetMirrorEmpty2DComponentsByStyle(p0, p1));
  } },
  { "GetTopPlan2DComponentByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetTopPlan2DComponentByStyle(p0));
  } },
  { "SetTopPlan2DComponentByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetTopPlan2DComponentByStyle(p0, p1));
  } },
  { "GetHorizontalSectionCutPlaneByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetHorizontalSectionCutPlaneByStyle(p0));
  } },
  { "SetHorizontalSectionCutPlaneByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetHorizontalSectionCutPlaneByStyle(p0, p1));
  } },
  { "GetVerticalSectionCutPlaneByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetVerticalSectionCutPlaneByStyle(p0));
  } },
  { "SetVerticalSectionCutPlaneByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetVerticalSectionCutPlaneByStyle(p0, p1));
  } },
  { "SetLayerName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetLayerName(p0, p1, p2));
  } },
  { "SetSheetLayerTitle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetSheetLayerTitle(p0, p1));
  } },
  { "AlertCriticalWithHyperlink", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    gSDK->AlertCriticalWithHyperlink(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "AlertInformWithHyperlink", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    bool p5 = JBool(a,i);
    TXString p6 = JStr(a,i);
    TXString p7 = JStr(a,i);
    TXString p8 = JStr(a,i);
    gSDK->AlertInformWithHyperlink(p0, p1, p2, p3, p4, p5, p6, p7, p8); r["ret"]=nullptr;
  } },
  { "DuplicateObjectWithNotification", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->DuplicateObjectWithNotification(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "DeleteDimensionConstraints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->DeleteDimensionConstraints(p0));
  } },
  { "EnableItemInSearchablePulldown", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    bool p3 = JBool(a,i);
    gSDK->EnableItemInSearchablePulldown(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateClassPullDownMenuN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateClassPullDownMenuN(p0, p1, p2, p3));
  } },
  { "CreateLayerPullDownMenuN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateLayerPullDownMenuN(p0, p1, p2, p3));
  } },
  { "CreateSheetLayerPullDownMenuN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateSheetLayerPullDownMenuN(p0, p1, p2, p3));
  } },
  { "CreateDesignLayerPullDownMenuN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->CreateDesignLayerPullDownMenuN(p0, p1, p2, p3));
  } },
  { "PixelLengthToLineWeight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    short p1 = 0;
    gSDK->PixelLengthToLineWeight(p0, p1); r["ret"]=nullptr;
    r["out"]["outLineWeightMils"] = (long long)p1;
  } },
  { "LineWeightToPixelLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    short p1 = 0;
    gSDK->LineWeightToPixelLength(p0, p1); r["ret"]=nullptr;
    r["out"]["outPixels"] = (long long)p1;
  } },
  { "ShowFloatingDataBar", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ShowFloatingDataBar(p0));
  } },
  { "IsDesignLayerSectionViewport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsDesignLayerSectionViewport(p0));
  } },
  { "UpdateSLVPForOnlyAnnotationsChange", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldRect p1 = JWrect(a,i);
    WorldRect p2 = JWrect(a,i);
    gSDK->UpdateSLVPForOnlyAnnotationsChange(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "CoordLenToPageLenScale", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (double)(gSDK->CoordLenToPageLenScale(p0, p1, p2));
  } },
  { "CoordLenToPagePtsScale", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (double)(gSDK->CoordLenToPagePtsScale(p0, p1, p2));
  } },
  { "PageLenToCoordLenScale", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (double)(gSDK->PageLenToCoordLenScale(p0, p1, p2));
  } },
  { "PagePtsToCoordLenScale", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    double p1 = JReal(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (double)(gSDK->PagePtsToCoordLenScale(p0, p1, p2));
  } },
  { "CreateMaterial", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    bool p1 = JBool(a,i);
    MCObjectHandle rh = gSDK->CreateMaterial(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetObjectMaterialName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetObjectMaterialName(p0, p1));
    r["out"]["outMaterialName"] = MStr(p1);
  } },
  { "GetObjectMaterialHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetObjectMaterialHandle(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetObjectMaterialHandle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetObjectMaterialHandle(p0, p1));
  } },
  { "IsMaterialSimple", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsMaterialSimple(p0));
  } },
  { "GetMaterialTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetMaterialTexture(p0));
  } },
  { "SetMaterialTexture", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetMaterialTexture(p0, p1));
  } },
  { "GetMaterialFillStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetMaterialFillStyle(p0));
  } },
  { "SetMaterialFillStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetMaterialFillStyle(p0, p1));
  } },
  { "IsMaterialFillStyleByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsMaterialFillStyleByClass(p0));
  } },
  { "SetMaterialFillStyleByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetMaterialFillStyleByClass(p0, p1));
  } },
  { "AddSubmaterialToMaterial", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    double p2 = JReal(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->AddSubmaterialToMaterial(p0, p1, p2, p3));
  } },
  { "RemoveSubmaterialFromMaterial", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->RemoveSubmaterialFromMaterial(p0, p1));
  } },
  { "UpdateSubmaterialInMaterial", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    double p2 = JReal(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (bool)(gSDK->UpdateSubmaterialInMaterial(p0, p1, p2, p3));
  } },
  { "SetExcludeObjectFromDataVisualization", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetExcludeObjectFromDataVisualization(p0, p1); r["ret"]=nullptr;
  } },
  { "DeleteRegenerableSubObjects", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->DeleteRegenerableSubObjects(p0); r["ret"]=nullptr;
  } },
  { "GetComponentMaterial", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    InternalIndex p2 = 0;
    r["ret"] = (bool)(gSDK->GetComponentMaterial(p0, p1, p2));
    r["out"]["material"] = (long long)p2;
  } },
  { "SetComponentMaterial", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetComponentMaterial(p0, p1, p2));
  } },
  { "EditPluginStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->EditPluginStyle(p0); r["ret"]=nullptr;
  } },
  { "CreateResourceTextPopup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->CreateResourceTextPopup(p0, p1, p2));
  } },
  { "AddBothSwapLayerProperties", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddBothSwapLayerProperties(p0));
  } },
  { "GetClassByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetClassByStyle(p0));
  } },
  { "SetClassByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetClassByStyle(p0, p1));
  } },
  { "GetMaterialArea", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (double)(gSDK->GetMaterialArea(p0, p1));
  } },
  { "GetMaterialVolume", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (double)(gSDK->GetMaterialVolume(p0, p1));
  } },
  { "GetProjectName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    r["ret"] = (bool)(gSDK->GetProjectName(p0));
    r["out"]["outName"] = MStr(p0);
  } },
  { "DuplicateObjectIgnoreConstraints", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->DuplicateObjectIgnoreConstraints(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "CreateEditColorText", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->CreateEditColorText(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "AddToolEditTextMethodN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    gSDK->AddToolEditTextMethodN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "TagSubObjectAsPart", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    long long p2 = JInt(a,i);
    TXString p3 = JStr(a,i);
    r["ret"] = (bool)(gSDK->TagSubObjectAsPart(p0, p1, p2, p3));
  } },
  { "SetPartInstanceUniqueName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetPartInstanceUniqueName(p0, p1));
  } },
  { "SetPartDataID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetPartDataID(p0, p1));
  } },
  { "RemovePartTag", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->RemovePartTag(p0));
  } },
  { "IsSubObjectTaggedAsPart", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->IsSubObjectTaggedAsPart(p0));
  } },
  { "GetPartTypeName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetPartTypeName(p0, p1));
    r["out"]["partTypeName"] = MStr(p1);
  } },
  { "GetPartInstanceUniqueName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetPartInstanceUniqueName(p0, p1));
    r["out"]["instanceUniqueName"] = MStr(p1);
  } },
  { "GetPartDataID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    Sint32 p1 = 0;
    r["ret"] = (bool)(gSDK->GetPartDataID(p0, p1));
    r["out"]["dataID"] = (long long)p1;
  } },
  { "GetPartInfo", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1;
    Sint32 p2 = 0;
    TXString p3;
    r["ret"] = (bool)(gSDK->GetPartInfo(p0, p1, p2, p3));
    r["out"]["partTypeName"] = MStr(p1);
    r["out"]["dataID"] = (long long)p2;
    r["out"]["uniqueInstanceName"] = MStr(p3);
  } },
  { "AppendNurbsCurves", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    gSDK->AppendNurbsCurves(p0, p1); r["ret"]=nullptr;
  } },
  { "GetCustomObjectSecondProfileGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomObjectSecondProfileGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SetCustomObjectSecondProfileGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectSecondProfileGroup(p0, p1));
  } },
  { "AddToolFaceHighlightingPoly3D", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddToolFaceHighlightingPoly3D(p0));
  } },
  { "SetCustomObjectWallClosureGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->SetCustomObjectWallClosureGroup(p0, p1));
  } },
  { "GetWallClosureGroup", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWallClosureGroup(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWallClosureGroupDeep", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetWallClosureGroupDeep(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddCustomTexturePartCategory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    gSDK->AddCustomTexturePartCategory(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "HasCustomTexturePartCategory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->HasCustomTexturePartCategory(p0, p1));
  } },
  { "RemoveCustomTexturePartCategory", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->RemoveCustomTexturePartCategory(p0, p1); r["ret"]=nullptr;
  } },
  { "SetTextureRefN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    gSDK->SetTextureRefN(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "GetTextureRefN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    bool p3 = JBool(a,i);
    r["ret"] = (long long)(gSDK->GetTextureRefN(p0, p1, p2, p3));
  } },
  { "SetDefaultTextureMappingN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SetDefaultTextureMappingN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "IsPartTexturedFromOveral", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsPartTexturedFromOveral(p0, p1, p2));
  } },
  { "RevertPartTextureToOveral", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->RevertPartTextureToOveral(p0, p1, p2));
  } },
  { "CreatePluginStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->CreatePluginStyle(p0); r["ret"]=nullptr;
  } },
  { "ClearLinkedTextBounds", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    gSDK->ClearLinkedTextBounds(p0); r["ret"]=nullptr;
  } },
  { "GetListBrowserItemHatchRefNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    InternalIndex p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemHatchRefNumber(p0, p1, p2, p3, p4));
    r["out"]["liRefNumber"] = (long long)p4;
  } },
  { "SetListBrowserItemHatchRefNumber", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemHatchRefNumber(p0, p1, p2, p3, p4));
  } },
  { "GetListBrowserItemMarkerByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemMarkerByClass(p0, p1, p2, p3, p4));
    r["out"]["bByClass"] = (bool)(p4!=0);
  } },
  { "SetListBrowserItemMarkerByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemMarkerByClass(p0, p1, p2, p3, p4));
  } },
  { "CanFreelyTransformObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->CanFreelyTransformObject(p0));
  } },
  { "SetListBrowserItemResourceOnlyCurrentDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    gSDK->SetListBrowserItemResourceOnlyCurrentDocument(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "IsListBrowserItemResourceOnlyCurrentDocument", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsListBrowserItemResourceOnlyCurrentDocument(p0, p1, p2, p3));
  } },
  { "ChangeNurbsPointType", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->ChangeNurbsPointType(p0, p1); r["ret"]=nullptr;
  } },
  { "NurbsInsertPtAtIndex", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    WorldPt3 p2 = JWpt3(a,i);
    gSDK->NurbsInsertPtAtIndex(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetNurbsLength", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetNurbsLength(p0));
  } },
  { "GetShowListBrowserItemMarkerByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->GetShowListBrowserItemMarkerByClass(p0, p1, p2, p3, p4));
    r["out"]["bShowByClass"] = (bool)(p4!=0);
  } },
  { "ShowListBrowserItemMarkerByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ShowListBrowserItemMarkerByClass(p0, p1, p2, p3, p4));
  } },
  { "GetShowListBrowserItemMarkerEditList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->GetShowListBrowserItemMarkerEditList(p0, p1, p2, p3, p4));
    r["out"]["bShowEditList"] = (bool)(p4!=0);
  } },
  { "ShowListBrowserItemMarkerEditList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ShowListBrowserItemMarkerEditList(p0, p1, p2, p3, p4));
  } },
  { "GetWallAtPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    MCObjectHandle rh = gSDK->GetWallAtPoint(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetWallInsertLocationOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetWallInsertLocationOffset(p0));
  } },
  { "SetWallInsertLocationOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetWallInsertLocationOffset(p0, p1));
  } },
  { "GetUseWallClosure", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetUseWallClosure(p0));
  } },
  { "SetUseWallClosure", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetUseWallClosure(p0, p1));
  } },
  { "GetWallInsertLocationByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetWallInsertLocationByStyle(p0));
  } },
  { "SetWallInsertLocationByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetWallInsertLocationByStyle(p0, p1));
  } },
  { "GetWallInsertLocationOffsetByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetWallInsertLocationOffsetByStyle(p0));
  } },
  { "SetWallInsertLocationOffsetByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetWallInsertLocationOffsetByStyle(p0, p1));
  } },
  { "GetUseWallClosureByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetUseWallClosureByStyle(p0));
  } },
  { "SetUseWallClosureByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetUseWallClosureByStyle(p0, p1));
  } },
  { "GetObjectWallInsertLocationOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetObjectWallInsertLocationOffset(p0, p1, p2));
    r["out"]["insertLocationOffset"] = (double)p2;
  } },
  { "SetObjectWallInsertLocationOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    double p2 = JReal(a,i);
    r["ret"] = (bool)(gSDK->SetObjectWallInsertLocationOffset(p0, p1, p2));
  } },
  { "GetWallHoleObjectIgnoreClosure", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetWallHoleObjectIgnoreClosure(p0));
  } },
  { "SetWallHoleObjectIgnoreClosure", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetWallHoleObjectIgnoreClosure(p0, p1); r["ret"]=nullptr;
  } },
  { "SetObjectClassN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->SetObjectClassN(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "ShowCriteriaDialog", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ShowCriteriaDialog(p0, p1));
    r["out"]["inOutCriteria"] = MStr(p0);
  } },
  { "BuildResourceListFromOpenFileN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    Sint32 p3 = 0;
    r["ret"] = (long long)(gSDK->BuildResourceListFromOpenFileN(p0, p1, p2, p3));
    r["out"]["numItems"] = (long long)p3;
  } },
  { "CreateCheckBoxWithIcon", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    gSDK->CreateCheckBoxWithIcon(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "CreateRadioButtonWithIcon", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    gSDK->CreateRadioButtonWithIcon(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "MirrorObjectN", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    WorldPt p2 = JWpt(a,i);
    WorldPt p3 = JWpt(a,i);
    bool p4 = JBool(a,i);
    MCObjectHandle rh = gSDK->MirrorObjectN(p0, p1, p2, p3, p4);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "AddToolSearchablePullDownMenuMethod", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    gSDK->AddToolSearchablePullDownMenuMethod(p0); r["ret"]=nullptr;
  } },
  { "AddSearchablePullDownMenuStaticChoice", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    gSDK->AddSearchablePullDownMenuStaticChoice(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "AddSearchablePullDownMenuItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    gSDK->AddSearchablePullDownMenuItem(p0, p1, p2, p3, p4); r["ret"]=nullptr;
  } },
  { "AddSearchablePullDownMenuChildItem", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    TXString p5 = JStr(a,i);
    gSDK->AddSearchablePullDownMenuChildItem(p0, p1, p2, p3, p4, p5); r["ret"]=nullptr;
  } },
  { "SetSearchablePullDownMenuSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->SetSearchablePullDownMenuSelection(p0, p1); r["ret"]=nullptr;
  } },
  { "GetSearchablePullDownMenuSelectedID", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString rs = gSDK->GetSearchablePullDownMenuSelectedID(p0); r["ret"] = MStr(rs);
  } },
  { "ClearSearchablePullDownMenu", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->ClearSearchablePullDownMenu(p0); r["ret"]=nullptr;
  } },
  { "ClearSearchablePullDownMenuStaticChoices", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    gSDK->ClearSearchablePullDownMenuStaticChoices(p0); r["ret"]=nullptr;
  } },
  { "CoordToSIAString", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    double p0 = JReal(a,i);
    bool p1 = JBool(a,i);
    TXString p2;
    TXString p3;
    r["ret"] = (bool)(gSDK->CoordToSIAString(p0, p1, p2, p3));
    r["out"]["outCentimeters"] = MStr(p2);
    r["out"]["outMillimeters"] = MStr(p3);
  } },
  { "FormatTextObjectInSIA", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (bool)(gSDK->FormatTextObjectInSIA(p0, p1, p2, p3));
  } },
  { "FormatTextObjectSegmentInSIA", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    double p3 = JReal(a,i);
    r["ret"] = (bool)(gSDK->FormatTextObjectSegmentInSIA(p0, p1, p2, p3));
  } },
  { "SetIsRunningLongActivity", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->SetIsRunningLongActivity(p0); r["ret"]=nullptr;
  } },
  { "CreateStoryWithUI", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->CreateStoryWithUI();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SelectWorksheetSubrow", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    gSDK->SelectWorksheetSubrow(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetInsertLocationComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (long long)(gSDK->GetInsertLocationComponent(p0));
  } },
  { "SetInsertLocationComponent", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    gSDK->SetInsertLocationComponent(p0, p1); r["ret"]=nullptr;
  } },
  { "GetComponentInsertLocationOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->GetComponentInsertLocationOffset(p0));
  } },
  { "SetComponentInsertLocationOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    gSDK->SetComponentInsertLocationOffset(p0, p1); r["ret"]=nullptr;
  } },
  { "GetObjectWallPerpendicularOffset", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    WorldCoord p2 = 0;
    r["ret"] = (bool)(gSDK->GetObjectWallPerpendicularOffset(p0, p1, p2));
    r["out"]["perpendicularOffset"] = (double)p2;
  } },
  { "GetExcludeWallClosureFromSettings", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = 0;
    bool p2 = 0;
    bool p3 = 0;
    bool p4 = 0;
    gSDK->GetExcludeWallClosureFromSettings(p0, p1, p2, p3, p4); r["ret"]=nullptr;
    r["out"]["left"] = (bool)(p1!=0);
    r["out"]["right"] = (bool)(p2!=0);
    r["out"]["top"] = (bool)(p3!=0);
    r["out"]["bottom"] = (bool)(p4!=0);
  } },
  { "SetExcludeWallClosureFromSettings", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetExcludeWallClosureFromSettings(p0, p1, p2, p3, p4));
  } },
  { "GetExcludeWallClosureFromSettingsByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetExcludeWallClosureFromSettingsByStyle(p0));
  } },
  { "SetExcludeWallClosureFromSettingsByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetExcludeWallClosureFromSettingsByStyle(p0, p1));
  } },
  { "ResetOldTextures", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->ResetOldTextures(p0, p1); r["ret"]=nullptr;
  } },
  { "SetIsObjectGimbalLocked", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    gSDK->SetIsObjectGimbalLocked(p0, p1); r["ret"]=nullptr;
  } },
  { "CreatePolylineWithCornerVerticesAddedToArcCurves", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreatePolylineWithCornerVerticesAddedToArcCurves(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "ObjSurfaceAreaInWorldCoords", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->ObjSurfaceAreaInWorldCoords(p0));
  } },
  { "GetCustomObjectSecondPath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->GetCustomObjectSecondPath(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetCurrentWorldSpaceToolPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt3 p0;
    r["ret"] = (bool)(gSDK->GetCurrentWorldSpaceToolPoint(p0));
    r["out"]["locPos"] = MWpt3(p0);
  } },
  { "TrackNodeChange", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    gSDK->TrackNodeChange(p0, p1); r["ret"]=nullptr;
  } },
  { "EnableTreeControlMultiSelection", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    gSDK->EnableTreeControlMultiSelection(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetViewportStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    InternalIndex p1 = 0;
    r["ret"] = (bool)(gSDK->GetViewportStyle(p0, p1));
    r["out"]["viewportStyle"] = (long long)p1;
  } },
  { "SetViewportStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetViewportStyle(p0, p1));
  } },
  { "CreateBorderlessMenuButton", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    gSDK->CreateBorderlessMenuButton(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "ShowAndSelectObject", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->ShowAndSelectObject(p0));
  } },
  { "GetListBrowserItemIndentLevel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    short p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemIndentLevel(p0, p1, p2, p3, p4));
    r["out"]["indentLevel"] = (long long)p4;
  } },
  { "SetListBrowserItemIndentLevel", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    long long p4 = JInt(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemIndentLevel(p0, p1, p2, p3, p4));
  } },
  { "GetActiveClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetActiveClass());
  } },
  { "GetActiveFillPat", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetActiveFillPat());
  } },
  { "GetActiveArrowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveArrowByClass());
  } },
  { "GetActiveFColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveFColorsByClass());
  } },
  { "GetActiveFPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveFPatByClass());
  } },
  { "GetActiveLWByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveLWByClass());
  } },
  { "GetActivePColorsByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActivePColorsByClass());
  } },
  { "GetActivePPatByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActivePPatByClass());
  } },
  { "GetActiveOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveOpacityByClass());
  } },
  { "GetActiveDropShadowByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveDropShadowByClass());
  } },
  { "GetActivePenOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActivePenOpacityByClass());
  } },
  { "GetActiveFillOpacityByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->GetActiveFillOpacityByClass());
  } },
  { "CreateSectionViewport", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    WorldPt p0 = JWpt(a,i);
    WorldPt p1 = JWpt(a,i);
    WorldPt p2 = JWpt(a,i);
    double p3 = JReal(a,i);
    double p4 = JReal(a,i);
    double p5 = JReal(a,i);
    MCObjectHandle p6 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateSectionViewport(p0, p1, p2, p3, p4, p5, p6);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "GetAppParameter", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1;
    r["ret"] = (bool)(gSDK->GetAppParameter(p0, p1));
    r["out"]["outValue"] = MStr(p1);
  } },
  { "CreateSingleOffsetPoly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    double p1 = JReal(a,i);
    MCObjectHandle rh = gSDK->CreateSingleOffsetPoly(p0, p1);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "SaveActiveFile", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->SaveActiveFile());
  } },
  { "RenameDataVisualization", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->RenameDataVisualization(p0, p1));
  } },
  { "RotateObjectPlanar", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    WorldPt p1 = JWpt(a,i);
    double p2 = JReal(a,i);
    gSDK->RotateObjectPlanar(p0, p1, p2); r["ret"]=nullptr;
  } },
  { "GetWallClosureName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString rs = gSDK->GetWallClosureName(p0); r["ret"] = MStr(rs);
  } },
  { "SetWallClosureName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    TXString p1 = JStr(a,i);
    r["ret"] = (bool)(gSDK->SetWallClosureName(p0, p1));
  } },
  { "GetWallClosureNameByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->GetWallClosureNameByStyle(p0));
  } },
  { "SetWallClosureNameByStyle", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetWallClosureNameByStyle(p0, p1));
  } },
  { "IsDocumentReady", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsDocumentReady());
  } },
  { "IsNurbsCornerPoint", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsNurbsCornerPoint(p0, p1));
  } },
  { "GetListBrowserItemIndeterminate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemIndeterminate(p0, p1, p2, p3, p4));
    r["out"]["indeterminate"] = (bool)(p4!=0);
  } },
  { "SetListBrowserItemIndeterminate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemIndeterminate(p0, p1, p2, p3, p4));
  } },
  { "CreateFormattedUnlinkedTextCopy", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->CreateFormattedUnlinkedTextCopy(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsVisibleByLayerAndClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    bool p1 = JBool(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->IsVisibleByLayerAndClass(p0, p1, p2));
  } },
  { "IsTreeControlItemExpanded", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (bool)(gSDK->IsTreeControlItemExpanded(p0, p1, p2));
  } },
  { "GetCurrentWorkspaceFilePath", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0;
    gSDK->GetCurrentWorkspaceFilePath(p0); r["ret"]=nullptr;
    r["out"]["outFilePath"] = MStr(p0);
  } },
  { "InitHandingWidgets", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->InitHandingWidgets(); r["ret"]=nullptr;
  } },
  { "UpdateHandingWidgets", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    bool p0 = JBool(a,i);
    gSDK->UpdateHandingWidgets(p0); r["ret"]=nullptr;
  } },
  { "ClearHandingWidgets", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ClearHandingWidgets(); r["ret"]=nullptr;
  } },
  { "IsAssemblyEditModeActive", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle rh = gSDK->IsAssemblyEditModeActive();
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "IsObjectInsertedInAssembly", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle rh = gSDK->IsObjectInsertedInAssembly(p0);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "PolylineCurveCountBetweenTwoCornerVertices", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    r["ret"] = (long long)(gSDK->PolylineCurveCountBetweenTwoCornerVertices(p0, p1, p2));
  } },
  { "SetActivePlaneToLayerPlane", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->SetActivePlaneToLayerPlane(); r["ret"]=nullptr;
  } },
  { "TransferAuxList", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    bool p2 = JBool(a,i);
    bool p3 = JBool(a,i);
    gSDK->TransferAuxList(p0, p1, p2, p3); r["ret"]=nullptr;
  } },
  { "GetListBrowserItemByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->GetListBrowserItemByClass(p0, p1, p2, p3, p4));
    r["out"]["bByClass"] = (bool)(p4!=0);
  } },
  { "SetListBrowserItemByClass", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetListBrowserItemByClass(p0, p1, p2, p3, p4));
  } },
  { "GetShowListBrowserItemByClassOption", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = 0;
    r["ret"] = (bool)(gSDK->GetShowListBrowserItemByClassOption(p0, p1, p2, p3, p4));
    r["out"]["bShowByClass"] = (bool)(p4!=0);
  } },
  { "ShowListBrowserItemByClassOption", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    long long p2 = JInt(a,i);
    long long p3 = JInt(a,i);
    bool p4 = JBool(a,i);
    r["ret"] = (bool)(gSDK->ShowListBrowserItemByClassOption(p0, p1, p2, p3, p4));
  } },
  { "CreateNewSolidForWDAssemblyCuttingHole", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    MCObjectHandle p1 = JHandle(a,i);
    MCObjectHandle p2 = JHandle(a,i);
    MCObjectHandle p3 = JHandle(a,i);
    bool p4 = JBool(a,i);
    long long p5 = JInt(a,i);
    long long p6 = JInt(a,i);
    MCObjectHandle rh = gSDK->CreateNewSolidForWDAssemblyCuttingHole(p0, p1, p2, p3, p4, p5, p6);
    int id = (asId>=0)? asId : gNextHandleId++;
    if (rh) { gHandleReg[id]=rh; r["as"]=id; }
    r["ret"] = (rh!=nullptr);
  } },
  { "InitInteractivePIOResizer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->InitInteractivePIOResizer());
  } },
  { "IsInteractivePIOResizerActive", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->IsInteractivePIOResizerActive());
  } },
  { "MouseMoveInteractivePIOResizer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->MouseMoveInteractivePIOResizer());
  } },
  { "CompleteInteractivePIOResizer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (bool)(gSDK->CompleteInteractivePIOResizer());
  } },
  { "CancelInteractivePIOResizer", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->CancelInteractivePIOResizer(); r["ret"]=nullptr;
  } },
  { "AlertQuestionWithHyperlink", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    TXString p0 = JStr(a,i);
    TXString p1 = JStr(a,i);
    TXString p2 = JStr(a,i);
    TXString p3 = JStr(a,i);
    TXString p4 = JStr(a,i);
    long long p5 = JInt(a,i);
    TXString p6 = JStr(a,i);
    TXString p7 = JStr(a,i);
    TXString p8 = JStr(a,i);
    TXString p9 = JStr(a,i);
    TXString p10 = JStr(a,i);
    TXString p11 = JStr(a,i);
    TXString p12 = JStr(a,i);
    r["ret"] = (long long)(gSDK->AlertQuestionWithHyperlink(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12));
  } },
  { "SetGradientSliderFaderMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetGradientSliderFaderMode(p0, p1, p2));
  } },
  { "GetGradientSliderFaderMode", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = 0;
    r["ret"] = (bool)(gSDK->GetGradientSliderFaderMode(p0, p1, p2));
    r["out"]["faderMode"] = (bool)(p2!=0);
  } },
  { "SetGradientSliderLiveUpdate", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    long long p1 = JInt(a,i);
    bool p2 = JBool(a,i);
    r["ret"] = (bool)(gSDK->SetGradientSliderLiveUpdate(p0, p1, p2));
  } },
  { "AddObjectActionHighlight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->AddObjectActionHighlight(p0));
  } },
  { "RemoveObjectActionHighlight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (bool)(gSDK->RemoveObjectActionHighlight(p0));
  } },
  { "ClearActionHighlight", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    gSDK->ClearActionHighlight(); r["ret"]=nullptr;
  } },
  { "GetNumPhases", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    r["ret"] = (long long)(gSDK->GetNumPhases());
  } },
  { "SetPhaseName", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->SetPhaseName(p0, p1); r["ret"]=nullptr;
  } },
  { "SetPhaseDescription", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    long long p0 = JInt(a,i);
    TXString p1 = JStr(a,i);
    gSDK->SetPhaseDescription(p0, p1); r["ret"]=nullptr;
  } },
  { "ObjVolumeInWorldCoords", [](const nlohmann::json& a, int asId, nlohmann::json& r){
    size_t i=0; (void)asId;
    MCObjectHandle p0 = JHandle(a,i);
    r["ret"] = (double)(gSDK->ObjVolumeInWorldCoords(p0));
  } },
  };
  return t;
}

static nlohmann::json DispatchIsdkCall(const std::string& fn, const nlohmann::json& args, int asId){
    nlohmann::json r; r["op"]="call"; r["fn"]=fn;
    const auto& tbl = IsdkShimTable();
    auto it = tbl.find(fn);
    if (it == tbl.end()){ r["ok"]=false; r["error"]="unknown or unsupported fn (not in generated table)"; return r; }
    try { nlohmann::json args2 = args.is_array()? args : nlohmann::json::array(); it->second(args2, asId, r); if(!r.contains("ok")) r["ok"]=true; }
    catch (const std::exception& e){ r["ok"]=false; r["error"]=std::string("arg/marshal error: ")+e.what(); }
    return r;
}
