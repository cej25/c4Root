// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastOnlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

bPlastOnlineSpectra::bPlastOnlineSpectra()
{
}

bPlastOnlineSpectra::bPlastOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

bPlastOnlineSpectra::~bPlastOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
}

void bPlastOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastOnlineSpectra::Init()
{

    // number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");

    TFolder * bPlast_spectra_folder = new TFolder("bPlast", "bPlast");

    run->AddObject(bPlast_spectra_folder);

    // energy spectra:
    cSlowToT  = new TCanvas("cbPlastSlowToT","slow ToT bPlast spectra",650,350);
    cSlowToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        cSlowToT->cd(ihist+1);
        h1_SlowToT[ihist] = new TH1F(Form("bPlast_slow_ToT_%d",ihist),Form("slow_ToT_%d",ihist),10000,0,5e3);
        h1_SlowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_SlowToT[ihist]->Draw();
    }
    cSlowToT->cd(0);

    bPlast_spectra_folder->Add(cSlowToT);
    
    // energy spectra:
    cFastToT  = new TCanvas("cbPlastfastToT","fast ToT bPlast spectra",650,350);
    cFastToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        cFastToT->cd(ihist+1);
        h1_FastToT[ihist] = new TH1F(Form("bPlast_fast_ToT_%d",ihist),Form("fast_ToT_%d",ihist),10000,0,5e3);
        h1_FastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_FastToT[ihist]->Draw();
    }
    cFastToT->cd(0);

    bPlast_spectra_folder->Add(cFastToT);

    // hit pattern:

    cFastHitPatt  = new TCanvas("cfastHitPatt","fast HitPatt bPlast spectra",650,350);

    h1_FastHitPatt = new TH1F("fast_HitPatt","fast_HitPatt",NDetectors,0,NDetectors);
    h1_FastHitPatt->GetXaxis()->SetTitle("Detector ID");
    h1_FastHitPatt->GetYaxis()->SetTitle("Counts");
    h1_FastHitPatt->Draw();

    cSlowHitPatt  = new TCanvas("cslowHitPatt","slow HitPatt bPlast spectra",650,350);

    h1_SlowHitPatt = new TH1F("slow_HitPatt","slow_HitPatt",NDetectors,0,NDetectors);
    h1_SlowHitPatt->GetXaxis()->SetTitle("Detector ID");
    h1_SlowHitPatt->GetYaxis()->SetTitle("Counts");
    h1_SlowHitPatt->Draw();
    
    // Time spectra:
    time_spectra_divided  = new TCanvas("bPlast_time_spectra_divided","bPlast time spectra",650,350);
    time_spectra_divided->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        time_spectra_divided->cd(ihist+1);
        h1_abs_time[ihist] = new TH1F(Form("bPlast_Time_spectrum_%d",ihist),Form("Time_spectrum_%d",ihist),10000,1.5218e14,1.5225e14);
        h1_abs_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_abs_time[ihist]->Draw();
    }
    time_spectra_divided->cd(0);

    bPlast_spectra_folder->Add(time_spectra_divided);

    run->GetHttpServer()->RegisterCommand("Reset_bPlast_Hist", Form("/Objects/%s->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

void bPlastOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_SlowToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_FastToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_SlowToT_vs_FastToT[ihist]->Reset();
    h1_FastHitPatt->Reset();
    h1_SlowHitPatt->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_abs_time[ihist]->Reset();

    c4LOG(info, "Histograms reset.");
   
}

void bPlastOnlineSpectra::Exec(Option_t* option)
{   
    if (fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitbPlastTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            bPlastTwinpeaksCalData* hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
            if (!hit) continue;
            
            if (hit->Get_detector_id() > NDetectors || hit->Get_detector_id() < 0) continue;

            // Lead and Trail spectra -- empty for now

            // Fast and Slow Tot spectra
            
            h1_SlowToT[hit->Get_detector_id()]->Fill(hit->Get_slow_ToT());
            h1_FastToT[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT());

            // Hit pattern spectra
            // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit

            h1_FastHitPatt->Fill(hit->Get_detector_id());
            h1_SlowHitPatt->Fill(hit->Get_detector_id());
            
            // Fast Vs Slow ToT

            

            }
        }
    fNEvents += 1;
}

void bPlastOnlineSpectra::FinishEvent()
{
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
}

void bPlastOnlineSpectra::FinishTask()
{
    if (fHitbPlastTwinpeaks)
    {
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_SlowToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_FastToT[ihist]->Write();
        h1_FastHitPatt->Write();
        h1_SlowHitPatt->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_abs_time[ihist]->Write();
    }
}

ClassImp(bPlastOnlineSpectra)
