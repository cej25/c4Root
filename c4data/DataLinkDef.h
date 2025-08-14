// clang-format off

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Aida
#pragma link C++ class AidaUnpackAdcItem+;
#pragma link C++ class AidaUnpackFlowItem+;
#pragma link C++ class AidaUnpackScalerItem+;
#pragma link C++ class std::vector<AidaUnpackAdcItem>+;
#pragma link C++ class std::vector<AidaUnpackFlowItem>+;
#pragma link C++ class std::vector<AidaUnpackScalerItem>+;
#pragma link C++ class AidaCalAdcItem+;
#pragma link C++ class std::vector<AidaCalAdcItem>+;
#pragma link C++ class AidaHit+;
#pragma link C++ class std::vector<AidaHit>+;

// BB7
#pragma link C++ class BB7FebexItem+;
#pragma link C++ class BB7EmptyItem+;
#pragma link C++ class BB7FebexCalItem+;
#pragma link C++ class BB7FebexHitItem+;

#pragma link C++ class BB7V7x5Item+;
#pragma link C++ class BB7V1290Item+;
#pragma link C++ class BB7VmeImplantItem+;
#pragma link C++ class BB7VmeDecayItem+;
#pragma link C++ class BB7VmeResidualItem+;

// BeamMonitor
#pragma link C++ class BeamMonitorItem+;

// BGO
#pragma link C++ class BGOTwinpeaksData+;
#pragma link C++ class BGOTwinpeaksCalData+;

// bPlast
#pragma link C++ class bPlastTwinpeaksData+;
#pragma link C++ class bPlastTwinpeaksCalData+;

// Fatima
#pragma link C++ class FatimaTwinpeaksData+;
#pragma link C++ class FatimaTwinpeaksCalData+;

#pragma link C++ class FatimaVmeQDCItem+;
#pragma link C++ class FatimaVmeTDCItem+;
#pragma link C++ class FatimaVmeQDCCalItem+;
#pragma link C++ class FatimaVmeTDCCalItem+;
#pragma link C++ class FatimaVmeResiduals+;

// FIMP
#pragma link C++ class FimpItem+;
#pragma link C++ class FimpCalItem+;

// FRS
#pragma link C++ class FrsTpatItem+;
#pragma link C++ class FrsScalerItem+;
#pragma link C++ class FrsSciItem+;
#pragma link C++ class FrsMusicItem+;
#pragma link C++ class FrsTpcItem+;
#pragma link C++ class FrsCalSciItem+;
#pragma link C++ class FrsCalMusicItem+;
#pragma link C++ class FrsCalTpcItem+;
#pragma link C++ class FrsHitItem+;
#pragma link C++ class FrsMultiHitItem+;

// FRS parameter classes
#pragma link C++ class TFRSParameter+;
#pragma link C++ class TMWParameter+;
#pragma link C++ class TTPCParameter+;
#pragma link C++ class TMUSICParameter+;
#pragma link C++ class TSCIParameter+;
#pragma link C++ class TIDParameter+;
#pragma link C++ class TSIParameter+;
#pragma link C++ class TRangeParameter+;
#pragma link C++ class TLABRParameter+;
#pragma link C++ class TMRTOFMSParameter+;
#pragma link C++ class FrsGate+;

// Germanium
#pragma link C++ class GermaniumFebexData+;
#pragma link C++ class GermaniumCalData+;
#pragma link C++ class GermaniumFebexTraceData+;

// HISPEC10 MCP
#pragma link C++ class H10MCPTwinpeaksData+;
#pragma link C++ class H10MCPTwinpeaksCalData+;
#pragma link C++ class H10MCPTwinpeaksAnaData+;

// LISA
#pragma link C++ class LisaItem+;
#pragma link C++ class LisaCalItem+;
#pragma link C++ class LisaAnaItem+;
#pragma link C++ class LisaHitItem+;
#pragma link C++ class LisaTraceData+;
#pragma link C++ class LisaGate+;

// STEFAN
#pragma link C++ class StefanFebexItem+;
#pragma link C++ class StefanCalItem+;

// TimeMachine
#pragma link C++ class TimeMachineData+;

// Configuration Classes
#pragma link C++ class TFrsConfiguration+;
#pragma link C++ class TAidaConfiguration+;
#pragma link C++ class TGermaniumConfiguration+;
#pragma link C++ class TFatimaTwinpeaksConfiguration+;
#pragma link C++ class TFatimaVmeConfiguration+;
#pragma link C++ class TBGOTwinpeaksConfiguration+;
#pragma link C++ class TbPlastConfiguration+;
#pragma link C++ class TCorrelationsConfiguration+;
#pragma link C++ class TExperimentConfiguration+;
#pragma link C++ class TBB7VmeConfiguration+;
#pragma link C++ class TBB7FebexConfiguration+;
#pragma link C++ class TLisaConfiguration+;
#pragma link C++ class TFimpConfiguration+;
#pragma link C++ class TH10MCPConfiguration+;
#pragma link C++ class TStefanConfiguration+;


#endif
