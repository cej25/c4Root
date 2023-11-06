// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaOnlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AidaData.h"
#include "TAidaConfiguration.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

AidaOnlineSpectra::AidaOnlineSpectra()
{
}

AidaOnlineSpectra::AidaOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , adcArray(nullptr)
    , flowArray(nullptr)
    , scalerArray(nullptr)
    , implantHitArray(nullptr)
    , header(nullptr)
    , fNEvents(0)
    // ranges
{
}

AidaOnlineSpectra::~AidaOnlineSpectra()
{
    c4LOG(info, "");
    // do we delete pointers? we didn't create them
}

void AidaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    adcArray = mgr->InitObjectAs<decltype(adcArray)>("AidaAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaAdcData not found!");
    //flowArray = (flowArray))mgr->GetObject("AidaFlowData");
    //c4LOG_IF(fatal, !adcArray, "Branch AidaFlowData not found!");
    //scalerArray = (decltype(scalerArray))mgr->GetObject("AidaScalerData");
    //c4LOG_IF(fatal, !adcArray, "Branch AidaScalerData not found!");

    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");

    TFolder *aidaFold = new TFolder("Aida", "Aida");
    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
    hit1 = new TH2F("dssd1", "dssd1", 386, 0, 386, 128, 0, 128);

    run->AddObject(aidaFold);

    run->GetHttpServer()->RegisterCommand("Reset_Aida_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void AidaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
}

void AidaOnlineSpectra::Exec(Option_t* option)
{
    //for (auto const& entry : *adcArray)
    //{
        //int fee = entry.Fee();
        //bool implant = entry.Range();
        //int channel = entry.Channel();
        //uint16_t value = entry.Value();

        //int implantIdx = implant ? 1 : 0;

        //if (!implant)
            //fhAdcs[fee - 1][channel][implantIdx]->Fill(value);
    //}
    //
    for (auto const& hit : *implantHitArray)
    {
        if (hit.DSSD == 1) {
            hit1->Fill(hit.StripX, hit.StripY);
        }
    }
    fNEvents += 1;
}

void AidaOnlineSpectra::FinishEvent()
{
}

void AidaOnlineSpectra::FinishTask()
{
}

ClassImp(AidaOnlineSpectra)
