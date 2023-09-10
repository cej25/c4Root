// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumOnlineSpectra.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "c4Logger.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

GermaniumOnlineSpectra::GermaniumOnlineSpectra()
{
}

GermaniumOnlineSpectra::GermaniumOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
}

GermaniumOnlineSpectra::~GermaniumOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void GermaniumOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus GermaniumOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumFebexData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumData not found!");

    // Create histograms
    TString Name1;
    TString Name2; 

    cSumTime = new TCanvas("SumTime1", "Sum Time 1", 10, 10, 800, 700);

    Name1 = "fh1_SumTime";
    Name2 = "Ge: Sum Time 1";

    fh1_SumTime = new TH1F(Name1, Name2, 1000, 1.5141e13, 1.5153e13); // no idea
    fh1_SumTime->GetXaxis()->SetTitle("Time");
    fh1_SumTime->GetYaxis()->SetTitle("Counts"); // necessary?
    fh1_SumTime->GetYaxis()->SetTitleOffset(1.15);
    fh1_SumTime->GetXaxis()->CenterTitle(true);
    fh1_SumTime->GetYaxis()->CenterTitle(true);
    fh1_SumTime->GetXaxis()->SetLabelSize(0.045);
    fh1_SumTime->GetXaxis()->SetTitleSize(0.045);
    fh1_SumTime->GetYaxis()->SetLabelSize(0.045);
    fh1_SumTime->GetYaxis()->SetTitleSize(0.045);
    //fh1_SumTime->SetFillColor(2);
    fh1_SumTime->SetLineColor(1);
    fh1_SumTime->Draw("");

    TFolder *geFold = new TFolder("Germanium", "Germanium");
    geFold->Add(cSumTime);
    run->AddObject(geFold);

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    fh1_SumTime->Reset();
}

void GermaniumOnlineSpectra::Exec(Option_t* option)
{   

    ULong64_t SumTime;
    uint8_t GeFired;
    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitGe->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            GermaniumFebexData* hit = (GermaniumFebexData*)fHitGe->At(ihit);
            if (!hit)
                continue;

            GeFired = hit->GetGeFired();
            if (GeFired == 0)
            {
                SumTime = hit->GetSumTimeLo() + ((ULong64_t)(hit->GetSumTimeHi()) << 32);
                fh1_SumTime->Fill(SumTime);
            }

        }
    }

    fNEvents += 1;
}

void GermaniumOnlineSpectra::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
}

void GermaniumOnlineSpectra::FinishTask()
{
    if (fHitGe)
    {
        cSumTime->Write();
    }
}

ClassImp(GermaniumOnlineSpectra)