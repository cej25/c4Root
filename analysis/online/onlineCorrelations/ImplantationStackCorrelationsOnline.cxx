#include "ImplantationStackCorrelationsOnline.h"

// FairROOT
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "ImplantationStackCorrelationsOnline.h"
#include "EventHeader.h"
#include "c4Logger.h"

#include <map>

ImplantationStackCorrelationsOnline::ImplantationStackCorrelationsOnline()
    : FairTask()
    , header(nullptr)
    , adcArray(nullptr)
    , flowArray(nullptr)
    , scalerArray(nullptr)
    , implantHitArray(nullptr)
    , fHitbPlastTwinpeaks(NULL)
    , fHitBGO(NULL)
    ,   fNEvents(0)
{
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();
    bgo_conf = TBGOTwinpeaksConfiguration::GetInstance();
}

ImplantationStackCorrelationsOnline::ImplantationStackCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   fNEvents(0)
{
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();
    bgo_conf = TBGOTwinpeaksConfiguration::GetInstance();
}

ImplantationStackCorrelationsOnline::~ImplantationStackCorrelationsOnline()
{
    delete fHitbPlastTwinpeaks;
    delete fHitBGO;
}

InitStatus ImplantationStackCorrelationsOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
    // bPlast
    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");
    // BGO
    fHitBGO = (TClonesArray*)mgr->GetObject("BGOTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitBGO, "Branch BGOTwinpeaksCalData not found!");

    // Raw data
    adcArray = mgr->InitObjectAs<decltype(adcArray)>("AidaAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaAdcData not found!");
    flowArray = mgr->InitObjectAs<decltype(flowArray)>("AidaFlowData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaFlowData not found!");
    scalerArray = mgr->InitObjectAs<decltype(scalerArray)>("AidaScalerData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaScalerData not found!");

    // Calibrated data
    implantCalArray = mgr->InitObjectAs<decltype(implantCalArray)>("AidaImplantCalAdcData");
    c4LOG_IF(fatal, !implantCalArray, "Branch AidaImplantCalAdcData not found!");
    decayCalArray = mgr->InitObjectAs<decltype(decayCalArray)>("AidaDecayCalAdcData");
    c4LOG_IF(fatal, !decayCalArray, "Branch AidaDecayCalAdcData not found!");

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_implantationstack_corrs = new TDirectory("ImplantationStack", "ImplantationStack", "", 0);
    mgr->Register("ImplantationStack", "ImplantationStack Directory", dir_implantationstack_corrs, false);
    histograms->Add(dir_implantationstack_corrs);

    // Load configs and mappings
    aida_config = TAidaConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();



    dir_implantationstack_corrs->cd();



    return kSUCCESS;

}

void ImplantationStackCorrelationsOnline::Exec(Option_t* option)
{

}

void ImplantationStackCorrelationsOnline::FinishEvent()
{

}

void ImplantationStackCorrelationsOnline::FinishTask()
{
}