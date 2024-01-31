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

bPlastOnlineSpectra::bPlastOnlineSpectra() : bPlastOnlineSpectra("bPlastOnlineSpectra")
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
    TFolder * bPlast_snapshot_folder = new TFolder("bPlast_Snapshots", "bPlast_Snapshots");

    run->AddObject(bPlast_spectra_folder);
    run->AddObject(bPlast_snapshot_folder);

    // energy spectra:
    c_bplast_slowToT  = new TCanvas("c_bplast_slowToT","slow ToT bPlast spectra",650,350);
    c_bplast_slowToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_slowToT->cd(ihist+1);
        h1_bplast_slowToT[ihist] = new TH1F(Form("c_bplast_slowToT_%d",ihist),Form("bPlastic slow ToT %d",ihist),10000,0,5e3);
        h1_bplast_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_bplast_slowToT[ihist]->Draw();
    }
    c_bplast_slowToT->cd(0);

    bPlast_spectra_folder->Add(c_bplast_slowToT);
    
    // energy spectra:
    c_bplast_fastToT  = new TCanvas("c_bplast_fastToT","fast ToT bPlast spectra",650,350);
    c_bplast_fastToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_fastToT->cd(ihist+1);
        h1_bplast_fastToT[ihist] = new TH1F(Form("c_bplast_fastToT_%d",ihist),Form("bPlastic fast ToT %d",ihist),10000,0,5e3);
        h1_bplast_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_bplast_fastToT[ihist]->Draw();
    }
    c_bplast_fastToT->cd(0);

    bPlast_spectra_folder->Add(c_bplast_fastToT);

    // hit pattern:

    c_bplast_hitpatterns  = new TCanvas("c_bplast_hitpatterns","fast HitPatt bPlast spectra",650,350);
    c_bplast_hitpatterns->Divide(2,1);

    c_bplast_hitpatterns->cd(1);
    h1_bplast_fast_hitpatterns = new TH1F("h1_bplast_fast_hitpatterns","Fast ToT detector hit patterns",NDetectors,0,NDetectors);
    h1_bplast_fast_hitpatterns->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_fast_hitpatterns->GetYaxis()->SetTitle("Counts");
    h1_bplast_fast_hitpatterns->Draw();
    c_bplast_hitpatterns->cd(2);
    h1_bplast_slow_hitpatterns = new TH1F("h1_bplast_slow_hitpatterns","Slow ToT detector hit patterns",NDetectors,0,NDetectors);
    h1_bplast_slow_hitpatterns->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_slow_hitpatterns->GetYaxis()->SetTitle("Counts");
    h1_bplast_slow_hitpatterns->Draw();
    c_bplast_hitpatterns->cd(0);


    bPlast_spectra_folder->Add(c_bplast_hitpatterns);
    
    
    // Time spectra:
    c_bplast_time_spectra  = new TCanvas("c_bplast_time_spectra","bPlast time spectra",650,350);
    c_bplast_time_spectra->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_time_spectra->cd(ihist+1);
        h1_bplast_abs_time[ihist] = new TH1F(Form("bPlast_Time_spectrum_%d",ihist),Form("bPlast Time spectrum detector %d",ihist),10000,0,2.7e12);
        h1_bplast_abs_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_bplast_abs_time[ihist]->Draw();
    }
    c_bplast_time_spectra->cd(0);


    c_bplast_fast_v_slow  = new TCanvas("c_bplast_fast_v_slow","fast vs slow ToT bplast spectra",650,350);
    c_bplast_fast_v_slow->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_fast_v_slow->cd(ihist+1);
        h2_bplast_slowToT_vs_fastToT[ihist] = new TH2F(Form("h2_bplast_slowToT_vs_fastToT_ToT_%d",ihist),Form("bplast fast vs. slow detector %d",ihist),1000,0,2.5e3,1000,0,2.5e3);
        h2_bplast_slowToT_vs_fastToT[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        h2_bplast_slowToT_vs_fastToT[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        h2_bplast_slowToT_vs_fastToT[ihist]->Draw("COLZ");
    }
    c_bplast_fast_v_slow->cd(0);

    bPlast_spectra_folder->Add(c_bplast_fast_v_slow);


    bPlast_spectra_folder->Add(c_bplast_time_spectra);

    run->GetHttpServer()->RegisterCommand("Reset_bPlast_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_bPlast_Hist", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

    return kSUCCESS;
    
}

void bPlastOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_slowToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_fastToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h2_bplast_slowToT_vs_fastToT[ihist]->Reset();
    h1_bplast_fast_hitpatterns->Reset();
    h1_bplast_slow_hitpatterns->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_abs_time[ihist]->Reset();

    c4LOG(info, "Histograms reset.");
   
}

// make a date and time stamped folder with pngs of the histograms and .root file and save them
void bPlastOnlineSpectra::Snapshot_Histo()
{
    c4LOG(info, "");
    // get the date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    TString snapshot_dir = Form("bPlast_Snapshots_%d_%d_%d_%d_%d_%d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    c_bplast_slowToT->SaveAs("c_bplast_slowToT.png");
    c_bplast_fastToT->SaveAs("c_bplast_fastToT.png");
    c_bplast_hitpatterns->SaveAs("c_bplast_hitpatterns.png");
    c_bplast_time_spectra->SaveAs("c_bplast_time_spectra.png");
    c_bplast_fast_v_slow->SaveAs("c_bplast_fast_v_slow.png");

    // TFile * snapshot_file = new TFile("bPlast_Snapshots.root","RECREATE");
    // bPlast_snapshot_folder->cd(0)
    // for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_slowToT[ihist]->Write();
    // for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_fastToT[ihist]->Write();
    // h1_bplast_fast_hitpatterns->Write();
    // h1_bplast_slow_hitpatterns->Write();
    // for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_abs_time[ihist]->Write();
    // for (int ihist = 0; ihist<NDetectors; ihist++) h2_bplast_slowToT_vs_fastToT[ihist]->Write();
    // snapshot_file->Close();

    gSystem->cd("..");
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
            if (hit->Get_slow_ToT() != 0) h1_bplast_slowToT[hit->Get_detector_id()]->Fill(hit->Get_slow_ToT());
            if (hit->Get_fast_ToT() != 0) h1_bplast_fastToT[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT());


            if ( (hit->Get_fast_ToT() != 0) && (hit->Get_slow_ToT() != 0) ) h2_bplast_slowToT_vs_fastToT[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT(),hit->Get_slow_ToT());

            if (hit->Get_fast_ToT() !=0 ) h1_bplast_abs_time[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time());

            // Hit pattern spectra
            // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit

            if (hit->Get_fast_ToT() != 0) h1_bplast_fast_hitpatterns->Fill(hit->Get_detector_id());
            if (hit->Get_slow_ToT() != 0) h1_bplast_slow_hitpatterns->Fill(hit->Get_detector_id());
            
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
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_slowToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_fastToT[ihist]->Write();
        h1_bplast_fast_hitpatterns->Write();
        h1_bplast_slow_hitpatterns->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_abs_time[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h2_bplast_slowToT_vs_fastToT[ihist]->Write();
    }
}

ClassImp(bPlastOnlineSpectra)
