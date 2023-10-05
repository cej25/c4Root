// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BeamMonitorOnlineSpectra.h"
#include "EventHeader.h"
#include "BeamMonitorData.h"
#include "c4Logger.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

BeamMonitorOnlineSpectra::BeamMonitorOnlineSpectra()
{
}

BeamMonitorOnlineSpectra::BeamMonitorOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitBM(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
}

BeamMonitorOnlineSpectra::~BeamMonitorOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitBM)
        delete fHitBM;
}

void BeamMonitorOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus BeamMonitorOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitBM = (TClonesArray*)mgr->GetObject("BeamMonitorData");
    c4LOG_IF(fatal, !fHitBM, "Branch BeamMonitorData not found!");

    // Create histograms
    TString Name1;
    TString Name2; 

    cSpills = new TCanvas("cSpills", "Spills", 10, 10, 800, 700);


    Name1 = "fh1_Spills";
    Name2 = "Beam Monitor: Spills";

    cSpills = new TCanvas("cSpills","Spills",10,10,800,700);
    fh1_Spills = new TH1F("fh1_Spills","Spills", 1000, 0, 1e8);
    fh1_Spills->Draw("");

    TFolder *bmFold = new TFolder("Germanium", "Germanium");
    bmFold->Add(cSpills);

    run->AddObject(bmFold);

    run->GetHttpServer()->RegisterCommand("Reset_BM_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void BeamMonitorOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    fh1_Spills->Reset();
}

void BeamMonitorOnlineSpectra::Exec(Option_t* option)
{   

    if (fHitBM && fHitBM->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitBM->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            BeamMonitorData* hit = (BeamMonitorData*)fHitBM->At(ihit);
            if (!hit)
                continue;

        }
    }

    fNEvents += 1;
}

void BeamMonitorOnlineSpectra::FinishEvent()
{
    if (fHitBM)
    {
        fHitBM->Clear();
    }
}

void BeamMonitorOnlineSpectra::FinishTask()
{
    if (fHitBM)
    {
        cSpills->Write();
    }
}

ClassImp(BeamMonitorOnlineSpectra)