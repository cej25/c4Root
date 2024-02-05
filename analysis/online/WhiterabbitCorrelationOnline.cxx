// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "WhiterabbitCorrelationOnline.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline() : WhiterabbitCorrelationOnline("WhiterabbitCorrelationOnline")
{
}

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fHitbPlastTwinpeaks(NULL)
    , fHitAida(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

WhiterabbitCorrelationOnline::~WhiterabbitCorrelationOnline()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
}

void WhiterabbitCorrelationOnline::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus WhiterabbitCorrelationOnline::Init()
{

    // number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");

    TFolder * fatima_spectra_folder = new TFolder("Fatima", "Fatima");

    run->AddObject(fatima_spectra_folder);
    
    
    run->GetHttpServer()->RegisterCommand("Reset_Fatima_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

// work in progress
void WhiterabbitCorrelationOnline::Reset_Histo()
{
    c4LOG(info, "Resetting histograms!");


}

void WhiterabbitCorrelationOnline::Snapshot_Histo()
{
    c4LOG(info, "Snapshotting histograms!");
}



void WhiterabbitCorrelationOnline::Exec(Option_t* option)
{   
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);
            if (!hit) continue;
            
        }
    }
    fNEvents += 1;
}



void WhiterabbitCorrelationOnline::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
}

void WhiterabbitCorrelationOnline::FinishTask()
{
    if (fHitFatimaTwinpeaks)
    {   
    
    }
}

ClassImp(WhiterabbitCorrelationOnline)
