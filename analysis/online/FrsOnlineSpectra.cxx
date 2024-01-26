// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsOnlineSpectra.h"
#include "FrsMainData.h"
#include "EventHeader.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

FrsOnlineSpectra::FrsOnlineSpectra()
    : FrsOnlineSpectra("FrsOnlineSpectra", 1)
{
}

FrsOnlineSpectra::FrsOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fHitFrs(NULL)
    , fNEvents(0)
    , fMin_Z(30.)
    , fMax_Z(80.)
    , fMin_AoQ(1.6)
    , fMax_AoQ(3.0)
    , fMin_x4(-100.) // no idea
    , fMax_x4(100.0) // no idea
    , fMin_Z_gate(30.)
    , fMax_Z_gate(80.)
    , fMin_AoQ_gate(1.6)
    , fMax_AoQ_gate(3.0)
    , header(nullptr)
{
}

FrsOnlineSpectra::~FrsOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitFrs)
        delete fHitFrs;
}

// Public Method SetParContainers
void FrsOnlineSpectra::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance(); // infuriating lack of consistency with capitalisation...
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFrs = (TClonesArray*)mgr->GetObject("FrsMainData");
    c4LOG_IF(fatal, !fHitFrs, "Branch FrsMainData not found");

    // Create histograms for detectors
    TString Name1;
    TString Name2;

    /*
    cTdcRaw = new TCanvas("TdcRaw", "TDC Raw Data", 10, 10, 800, 700);
    fh1_TdcRaw = new TH1F("fh1_TdcRaw", "TDC Raw Data", 20, 0, 1e5);
    fh1_TdcRaw->GetXaxis()->SetTitle("TDC Raw");
    fh1_TdcRaw->Draw();
    
    cTdcChan = new TCanvas("TdcChan", "TDC Channel", 10, 10, 800, 700);
    fh1_TdcChan = new TH1F("fh1_TdcChan", "TDC Channel", 32, 0, 32);
    fh1_TdcChan->GetXaxis()->SetTitle("Channel");
    fh1_TdcChan->Draw();

    */

    /*
    cZvsAoQ = new TCanvas("ZvsAoQ", "Z vs. AoQ", 10, 10, 800, 700);

    Name1 = "fh2_ZvsAoQ";
    Name2 = "FRS: Z vs AoQ";

    fh2_ZvsAoQ = new TH2F(Name1, Name2, 1000, fMin_AoQ, fMax_AoQ, 1000, fMin_Z, fMax_Z);
    fh2_ZvsAoQ->GetXaxis()->SetTitle("AoQ");
    fh2_ZvsAoQ->GetYaxis()->SetTitle("Z");
    fh2_ZvsAoQ->GetYaxis()->SetTitleOffset(1.1);
    fh2_ZvsAoQ->GetXaxis()->CenterTitle(true);
    fh2_ZvsAoQ->GetYaxis()->CenterTitle(true);
    fh2_ZvsAoQ->GetXaxis()->SetLabelSize(0.045);
    fh2_ZvsAoQ->GetXaxis()->SetTitleSize(0.045);
    fh2_ZvsAoQ->GetYaxis()->SetLabelSize(0.045);
    fh2_ZvsAoQ->GetYaxis()->SetTitleSize(0.045);
    fh2_ZvsAoQ->Draw("colz")
    */

   

    
    // MAIN FOLDER-INCOMINGID
   /* TFolder* frsfol = new TFolder("FRS-IncomingID", "FRS incomingID info");
    frsfol->Add(cTdcRaw);
    frsfol->Add(cTdcChan);
    run->AddObject(frsfol);*/

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
   // fh1_TdcRaw->Clear();
   // fh1_TdcChan->Clear();
}

void FrsOnlineSpectra::Exec(Option_t* option)
{
   // Float_t a2AoQCorr = 0.0012;
   // Float_t AoQCorr; // CEJ: handle in calData or hitData !! 
 
    // Fill hit data
    if (fHitFrs && fHitFrs->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFrs->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FrsMainData* hit = (FrsMainData*)fHitFrs->At(ihit);
            if (!hit)
                continue;

         //   fh1_TdcRaw->Fill(hit->GetTdcData());
         //   fh1_TdcChan->Fill(hit->GetChan());

            /*fh2_ZvsAoQ->Fill(hit->GetAoQ(), hit->GetZ());
            fh2_x4vsAoQ->Fill(hit->GetAoQ(), hit->GetX4());
            
            AoQCorr = hit->GetAoQ() - a2AoQCorr * hit->GetA2();
            fh2_ZvsAoQCorr->Fill(AoQCorr, hit->GetZ());
            fh2_x4vsAoQCorr->Fill(AoQCorr, hit->GetX4());*/
        }
    }

    fNEvents += 1;
}

void FrsOnlineSpectra::FinishEvent()
{
    if (fHitFrs)
    {
        fHitFrs->Clear();
    }
}

void FrsOnlineSpectra::FinishTask()
{
    if (fHitFrs)
    {   
      //  cTdcRaw->Write();
      //  cTdcChan->Write();
        /*cZvsAoQ->Write();
        cX4vsAoQ->Write();
        cZvsAoQCorr->Write();
        cX4vsAoQCorr->Write();*/
    }
}

ClassImp(FrsOnlineSpectra)