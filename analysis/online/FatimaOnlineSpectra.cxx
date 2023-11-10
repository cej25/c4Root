// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaOnlineSpectra.h"
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

FatimaOnlineSpectra::FatimaOnlineSpectra()
{
}

FatimaOnlineSpectra::FatimaOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

FatimaOnlineSpectra::~FatimaOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
}

void FatimaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FatimaOnlineSpectra::Init()
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

    // energy spectra:
    cslowToT  = new TCanvas("cslowToT","slow ToT Fatima spectra",650,350);
    cslowToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        cslowToT->cd(ihist+1);
        h1_slowToT[ihist] = new TH1F(Form("slow_ToT_%d",ihist),Form("slow_ToT_%d",ihist),2000,0,2.5e3);
        h1_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_slowToT[ihist]->Draw();
    }
    cslowToT->cd(0);

    fatima_spectra_folder->Add(cslowToT);
    
    // energy spectra:
    cfastToT  = new TCanvas("cfastToT","fast ToT Fatima spectra",650,350);
    cfastToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        cfastToT->cd(ihist+1);
        h1_fastToT[ihist] = new TH1F(Form("fast_ToT_%d",ihist),Form("fast_ToT_%d",ihist),2000,0,2.5e3);
        h1_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_fastToT[ihist]->Draw();
    }
    cfastToT->cd(0);

    fatima_spectra_folder->Add(cfastToT);
    
    // energy spectra:
    cfast_v_slow  = new TCanvas("cfast_v_slow","fast vs slow ToT Fatima spectra",650,350);
    cfast_v_slow->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        cfast_v_slow->cd(ihist+1);
        h2_fast_v_slow[ihist] = new TH2F(Form("fast_v_slow_ToT_%d",ihist),Form("fast_v_slow_ToT_%d",ihist),1000,0,2.5e3,1000,0,2.5e3);
        h2_fast_v_slow[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h2_fast_v_slow[ihist]->GetYaxis()->SetTitle("ToT (ns)");
        h2_fast_v_slow[ihist]->Draw("COLZ");
    }
    cfast_v_slow->cd(0);

    fatima_spectra_folder->Add(cfast_v_slow);
    
    // Time spectra:
    time_spectra_divided  = new TCanvas("time_spectra_divided","Fatima time spectra",650,350);
    time_spectra_divided->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        time_spectra_divided->cd(ihist+1);
        h1_abs_time[ihist] = new TH1F(Form("Time_spectrum_%d",ihist),Form("Time_spectrum_%d",ihist),100,1.5218e14,1.5225e14);
        h1_abs_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_abs_time[ihist]->Draw();
    }
    time_spectra_divided->cd(0);

    fatima_spectra_folder->Add(time_spectra_divided);

    run->GetHttpServer()->RegisterCommand("Reset_Fatima_Hist", Form("/Objects/%s->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

void FatimaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_slowToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fastToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_abs_time[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h2_fast_v_slow[ihist]->Reset();
   
}

void FatimaOnlineSpectra::Exec(Option_t* option)
{   
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);
            if (!hit) continue;
            
            if (hit->Get_detector_id() > NDetectors || hit->Get_detector_id() < 0) continue;

            h1_slowToT[hit->Get_detector_id()]->Fill(hit->Get_slow_ToT());
            //h1_abs_time[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time());
            h1_fastToT[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT());
            h2_fast_v_slow[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT(), hit->Get_slow_ToT());

            }
        }
    fNEvents += 1;
}



void FatimaOnlineSpectra::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
}

void FatimaOnlineSpectra::FinishTask()
{
    if (fHitFatimaTwinpeaks)
    {
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_slowToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fastToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_abs_time[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h2_fast_v_slow[ihist]->Write();
    }
}

ClassImp(FatimaOnlineSpectra)