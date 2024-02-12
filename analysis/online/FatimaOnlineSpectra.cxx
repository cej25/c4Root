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
#include "TFile.h"
#include "TRandom.h"

FatimaOnlineSpectra::FatimaOnlineSpectra() : FatimaOnlineSpectra("FatimaOnlineSpectra")
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
    c4LOG(info, "HERE");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");

    //create folders
    folder_fatima = new TFolder("FATIMA", "FATIMA");


    run->AddObject(folder_fatima);

    folder_fatima_slowToT = new TFolder("slowToT", "slowToT");
    folder_fatima_fastToT = new TFolder("fastToT", "fastToT");
    folder_fatima_hitpattern = new TFolder("hitpattern", "hitpattern");
    folder_fatima_fast_v_slow = new TFolder("fast_v_slow", "fast_v_slow");
    folder_fatima_time_spectra = new TFolder("time_spectra", "time_spectra");
    folder_fatima_energy_spectra = new TFolder("Energy", "energy");
    folder_fatima_time_differences = new TFolder("time_differences", "time_differences");
    folder_fatima->Add(folder_fatima_slowToT);
    folder_fatima->Add(folder_fatima_fastToT);
    folder_fatima->Add(folder_fatima_hitpattern);
    folder_fatima->Add(folder_fatima_fast_v_slow);
    folder_fatima->Add(folder_fatima_time_spectra);
    folder_fatima->Add(folder_fatima_energy_spectra);
    folder_fatima->Add(folder_fatima_time_differences);


    // energy spectra:
    c_fatima_slowToT  = new TCanvas("c_fatima_slowToT","slow ToT Fatima spectra",650,350);
    c_fatima_slowToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_slowToT->cd(ihist+1);
        h1_fatima_slowToT[ihist] = new TH1F(Form("h1_fatima_slowToT_%d",ihist),Form("Fatima slow ToT detector %d",ihist),fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h1_fatima_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        if (h1_fatima_slowToT[ihist]->GetEntries() != 0 || true){
            h1_fatima_slowToT[ihist]->Draw();
            folder_fatima_slowToT->Add(h1_fatima_slowToT[ihist]);
        }
    }
    c_fatima_slowToT->cd(0);

    folder_fatima->Add(c_fatima_slowToT);
    
    // energy spectra:
    c_fatima_fastToT  = new TCanvas("c_fatima_fastToT","fast ToT Fatima spectra",650,350);
    c_fatima_fastToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_fastToT->cd(ihist+1);
        h1_fatima_fastToT[ihist] = new TH1F(Form("h1_fatima_fastToT_%d",ihist),Form("Fatima fast ToT detector %d",ihist),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high);
        h1_fatima_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        if (h1_fatima_fastToT[ihist]->GetEntries() != 0 || true){
            h1_fatima_fastToT[ihist]->Draw();
            folder_fatima_fastToT->Add(h1_fatima_fastToT[ihist]);
        }
    }
    c_fatima_fastToT->cd(0);

    folder_fatima->Add(c_fatima_fastToT);
    
    
    // energy spectra:
    c_fatima_energies  = new TCanvas("c_fatima_energies","Fatima Energy spectra",650,350);
    c_fatima_energies->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_energies->cd(ihist+1);
        h1_fatima_energies[ihist] = new TH1F(Form("h1_fatima_energies_%d",ihist),Form("Fatima detector %d energy",ihist),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energies[ihist]->GetXaxis()->SetTitle("Energy (keV)");
        if (h1_fatima_energies[ihist]->GetEntries() != 0 || true){
            h1_fatima_energies[ihist]->Draw();
            folder_fatima_energy_spectra->Add(h1_fatima_energies[ihist]);
        }
    }
    c_fatima_energies->cd(0);

    folder_fatima->Add(c_fatima_energies);
    
    // energy spectra:
    c_fatima_fast_v_slow  = new TCanvas("c_fatima_fast_v_slow","fast vs slow ToT Fatima spectra",650,350);
    c_fatima_fast_v_slow->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_fast_v_slow->cd(ihist+1);
        h2_fatima_fast_v_slow[ihist] = new TH2F(Form("h2_fatima_fast_v_slow_ToT_%d",ihist),Form("FATIMA fast vs. slow detector %d",ihist),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high,fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h2_fatima_fast_v_slow[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        if (h2_fatima_fast_v_slow[ihist]->GetEntries() != 0 || true){
            h2_fatima_fast_v_slow[ihist]->Draw("COLZ");
            folder_fatima_fast_v_slow->Add(h2_fatima_fast_v_slow[ihist]);
        }
    }
    c_fatima_fast_v_slow->cd(0);

    folder_fatima->Add(c_fatima_fast_v_slow);
    
    // Time spectra:
    c_fatima_time_spectra_divided  = new TCanvas("c_fatima_time_spectra_divided","Fatima time spectra",650,350);
    c_fatima_time_spectra_divided->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_spectra_divided->cd(ihist+1);
        h1_fatima_abs_time[ihist] = new TH1F(Form("h1_fatima_abs_time_%d",ihist),Form("FATIMA time spectrum detectors %d",ihist),100,0,2.7e12);
        h1_fatima_abs_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        if (h1_fatima_abs_time[ihist]->GetEntries() != 0 || true){
            h1_fatima_abs_time[ihist]->Draw();
            folder_fatima_time_spectra->Add(h1_fatima_abs_time[ihist]);
        }
    }
    c_fatima_time_spectra_divided->cd(0);

    folder_fatima->Add(c_fatima_time_spectra_divided);

    c_fatima_energy = new TCanvas("c_fatima_energy","Fatima energy spectrum",650,350);
    h2_fatima_energy = new TH2F("h2_fatima_energy","FATIMA energy (keV)",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,NDetectors,0,NDetectors);
    h2_fatima_energy->GetXaxis()->SetTitle("Energy (keV)");
    h2_fatima_energy->GetYaxis()->SetTitle("Detector nr.");
    if (h2_fatima_energy->GetEntries() != 0 || true) h2_fatima_energy->Draw("COLZ");
    folder_fatima_energy_spectra->Add(c_fatima_energy);

    c_fatima_energy_uncal = new TCanvas("c_fatima_energy_uncal","Fatima energy spectrum",650,350);
    h2_fatima_energy_uncal = new TH2F("h2_fatima_energy_uncal","FATIMA energy (keV)",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,NDetectors,0,NDetectors);
    h2_fatima_energy_uncal->GetXaxis()->SetTitle("Energy (binnr)");
    h2_fatima_energy_uncal->GetYaxis()->SetTitle("Detector nr.");
    if (h2_fatima_energy_uncal->GetEntries() != 0 || true) h2_fatima_energy_uncal->Draw("COLZ");
    folder_fatima_energy_spectra->Add(c_fatima_energy_uncal);

    // Hit patterns:
    c_fatima_hitpatterns  = new TCanvas("c_fatima_hitpatterns","Fatima hit patterns",650,350);
    c_fatima_hitpatterns->Divide(2,1);

    c_fatima_hitpatterns->cd(1);
    h1_fatima_hitpattern_slow = new TH1F("h1_fatima_hitpattern_slow","FATIMA slow hit patterns",NDetectors,0,NDetectors);
    h1_fatima_hitpattern_slow->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_slow->GetYaxis()->SetTitle("Hits");
    h1_fatima_hitpattern_slow->Draw();
    folder_fatima_hitpattern->Add(h1_fatima_hitpattern_slow);
    
    c_fatima_hitpatterns->cd(2);
    h1_fatima_hitpattern_fast = new TH1F("h1_fatima_hitpattern_fast","FATIMA fast hit patterns",NDetectors,0,NDetectors);
    h1_fatima_hitpattern_fast->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_fast->GetYaxis()->SetTitle("Hits");
    if (h1_fatima_hitpattern_fast->GetEntries() != 0 || true) h1_fatima_hitpattern_fast->Draw();
    folder_fatima_hitpattern->Add(h1_fatima_hitpattern_slow);
    c_fatima_hitpatterns->cd(0);
    
    folder_fatima->Add(c_fatima_hitpatterns);
    
    
    c_fatima_time_differences = new TCanvas("c_fatima_time_differences","Time coincidences to detector 0",650,350);
    c_fatima_time_differences->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_differences->cd(ihist+1);
        h1_fatima_time_differences[ihist] = new TH1F(Form("h1_fatima_time_differences_%d",ihist),Form("FATIMA time spectrum t_%d - t_0",ihist),1000,-500,500);
        h1_fatima_time_differences[ihist]->GetXaxis()->SetTitle("Time (ns)");
        if (h1_fatima_time_differences[ihist]->GetEntries() != 0 || true) h1_fatima_time_differences[ihist]->Draw();
        folder_fatima_time_differences->Add(h1_fatima_time_differences[ihist]);
    }
    c_fatima_time_differences->cd(0);

    folder_fatima->Add(c_fatima_time_differences);
    
    c_fatima_energy_energy = new TCanvas("c_fatima_energy_energy","Fatima energy-energy, det 0 vs det 1 dt < 1000 ns",650,350);
    h2_fatima_energy_energy= new TH2F("h2_fatima_energy_energy","FATIMA energy-energy det0 vs det1 dt < 1000 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_energy->GetXaxis()->SetTitle("Energy (keV)");
    h2_fatima_energy_energy->GetYaxis()->SetTitle("Energy (keV)");
    c_fatima_energy_energy->SetLogz();
    if (h2_fatima_energy_energy->GetEntries() != 0 || true) h2_fatima_energy_energy->Draw("COLZ");
    folder_fatima_energy_spectra->Add(c_fatima_energy_energy);
    
    
    c_fatima_time_differences_SCI41 = new TCanvas("c_fatima_time_differences_SCI41","Time coincidences to detector SCI41",650,350);
    c_fatima_time_differences_SCI41->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_differences_SCI41->cd(ihist+1);
        h1_fatima_time_differences_SCI41[ihist] = new TH1F(Form("h1_fatima_time_differences_%d_SCI41",ihist),Form("FATIMA time spectrum t_%d - t(SCI41)",ihist),1000,-500,500);
        h1_fatima_time_differences_SCI41[ihist]->GetXaxis()->SetTitle("Time (ns)");
        if (h1_fatima_time_differences_SCI41[ihist]->GetEntries() != 0 || true) h1_fatima_time_differences_SCI41[ihist]->Draw();
    }
    c_fatima_time_differences_SCI41->cd(0);
    folder_fatima->Add(c_fatima_time_differences_SCI41);

    
    
    
    c_fatima_time_differences_energy_SCI41 = new TCanvas("c_fatima_time_differences_energy_SCI41","energy vs dt to detector 0 vs SCI41",650,350);
    c_fatima_time_differences_energy_SCI41->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_differences_energy_SCI41->cd(ihist+1);
        h1_fatima_time_differences_energy_SCI41[ihist] = new TH2F(Form("h1_fatima_time_differences_energy_%d_SCI41",ihist),Form("FATIMA t_%d - t(SCI41) vs energy",ihist),1000,-500,500,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_time_differences_energy_SCI41[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_fatima_time_differences_energy_SCI41[ihist]->GetYaxis()->SetTitle("Energy (keV)");
        h1_fatima_time_differences_energy_SCI41[ihist]->Draw();
    }
    c_fatima_time_differences_energy_SCI41->cd(0);
    folder_fatima->Add(c_fatima_time_differences_energy_SCI41);

    
    c_fatima_time_differences_energy_SCI41_sum = new TCanvas("c_fatima_time_differences_energy_SCI41_sum","energy vs dt(t_any - SCI41)",650,350);
    h1_fatima_time_differences_energy_SCI41_sum = new TH2F("h1_fatima_time_differences_energy_SCI41_sum","FATIMA t_any - t(SCI41) vs energy",1000,-500,1000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_time_differences_energy_SCI41_sum->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_time_differences_energy_SCI41_sum->GetYaxis()->SetTitle("Energy (keV)");
    h1_fatima_time_differences_energy_SCI41_sum->Draw();
    folder_fatima->Add(c_fatima_time_differences_energy_SCI41_sum);

    c_fatima_time_differences_energy_SCI41_gated = new TCanvas("c_fatima_time_differences_energy_SCI41_gated","energy vs dt(t_any - SCI41)",650,350);
    h1_fatima_time_differences_energy_SCI41_gated = new TH1F("h1_fatima_time_differences_energy_SCI41_gated","FATIMA t_any - t(SCI41) vs energy",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_time_differences_energy_SCI41_gated->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_time_differences_energy_SCI41_gated->GetYaxis()->SetTitle("Energy (keV)");
    h1_fatima_time_differences_energy_SCI41_gated->Draw();
    folder_fatima->Add(c_fatima_time_differences_energy_SCI41_gated);

    
    run->GetHttpServer()->RegisterCommand("Reset_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

    return kSUCCESS;
    
}

void FatimaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting histograms!");
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_slowToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_fastToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_abs_time[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_energies[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_time_differences[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h2_fatima_fast_v_slow[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_time_differences_SCI41[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_time_differences_energy_SCI41[ihist]->Reset();
    
    h1_fatima_time_differences_energy_SCI41_gated->Reset();
    h1_fatima_hitpattern_fast->Reset();
    h1_fatima_hitpattern_slow->Reset();
    h1_fatima_time_differences_energy_SCI41_sum->Reset();
    h2_fatima_energy->Reset();
    h2_fatima_energy_uncal->Reset();
    h2_fatima_energy_energy->Reset();
}

// not complete maybe different spectra need to be added here, but anyway correlations between Sc41 and are something for later analysis (?)
void FatimaOnlineSpectra::Snapshot_Histo()
{
    // date and time stamp
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // make folder with date and time
    TString snapshot_dir = Form("FATIMA_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);

    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    c_fatima_snapshot = new TCanvas("c_fatima_snapshot","Fatima snapshot",650,350);

    for (int ihist = 0; ihist<NDetectors; ihist++)
    {
        if(h1_fatima_slowToT[ihist]->GetEntries() != 0 || true)
        {
            h1_fatima_slowToT[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_slowTot_%d.png",ihist));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_fastToT[ihist]->GetEntries() != 0 || true)
        {
            h1_fatima_fastToT[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_fastTot_%d.png",ihist));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_abs_time[ihist]->GetEntries() != 0 || true)
        {
            h1_fatima_abs_time[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_abs_time_%d.png",ihist));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_energies[ihist]->GetEntries() != 0 || true)
        {
            h1_fatima_energies[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_energies_%d.png",ihist));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_time_differences[ihist]->GetEntries() != 0 || true)
        {
            h1_fatima_time_differences[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_time_differences_%d.png",ihist));
            c_fatima_snapshot->Clear();
        }
        if(h2_fatima_fast_v_slow[ihist]->GetEntries() != 0 || true)
        {
            h2_fatima_fast_v_slow[ihist]->Draw("COLZ");
            c_fatima_snapshot->SaveAs(Form("h2_fatima_fast_v_slow_%d.png",ihist));
            c_fatima_snapshot->Clear();
        }
    }
    delete c_fatima_snapshot;
    // save the snapshot of .root file with data and time stamp
    file_fatima_snapshot = new TFile(Form("FATIMA_snapshot_%d_%d_%d_%d_%d_%d.root",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec),"RECREATE"); 
    file_fatima_snapshot->cd();
    folder_fatima->Write();
    file_fatima_snapshot->Close();
    delete file_fatima_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshots saved in: " << snapshot_dir);
}


void FatimaOnlineSpectra::Exec(Option_t* option)
{   
    //suspects that the lead and trail flags are	
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);
            if (!hit) continue;
            
            if (hit->Get_detector_id() > NDetectors || hit->Get_detector_id() < 0) continue;

            h1_fatima_slowToT[hit->Get_detector_id()]->Fill(hit->Get_slow_ToT());
            h1_fatima_energies[hit->Get_detector_id()]->Fill(hit->Get_energy());
            h1_fatima_fastToT[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT());
            h2_fatima_fast_v_slow[hit->Get_detector_id()]->Fill(hit->Get_fast_ToT(), hit->Get_slow_ToT());
            h1_fatima_abs_time[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time());
            h2_fatima_energy->Fill(hit->Get_energy(), hit->Get_detector_id());
            h2_fatima_energy_uncal->Fill(hit->Get_slow_ToT(), hit->Get_detector_id());
            if (hit->Get_fast_ToT() != 0 ) h1_fatima_hitpattern_fast->Fill(hit->Get_detector_id());
            if (hit->Get_slow_ToT() != 0 ) h1_fatima_hitpattern_slow->Fill(hit->Get_detector_id());
            
            //COINCIDENCES:
            if (nHits > 1){
                for (Int_t ihit2 = ihit+1; ihit2 < nHits; ihit2++){
                    FatimaTwinpeaksCalData * hit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit2);
                    if (!(TMath::Abs(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time())<100e3)) continue;
                    if (hit->Get_detector_id() == 1 && hit2->Get_detector_id() == 2){
                        h2_fatima_energy_energy->Fill(hit->Get_energy(),hit2->Get_energy());
                    }else if (hit->Get_detector_id() == 1 && hit2->Get_detector_id() == 0){
                        h2_fatima_energy_energy->Fill(hit2->Get_energy(),hit->Get_energy());
                    }
                    
                    h1_fatima_time_differences[hit->Get_detector_id()]->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time());
                    
                    if (hit->Get_detector_id() == 18){
                        h1_fatima_time_differences_SCI41[hit2->Get_detector_id()]->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time());
                        h1_fatima_time_differences_energy_SCI41[hit2->Get_detector_id()]->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time(),hit2->Get_energy());
                        if (hit2->Get_detector_id() < 10 ) {
                            h1_fatima_time_differences_energy_SCI41_sum->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time(),hit2->Get_energy());
                            if (hit2->Get_fast_lead_time() - hit->Get_fast_lead_time() > - 305) h1_fatima_time_differences_energy_SCI41_gated->Fill(hit2->Get_energy());
                        }
                    }else if (hit2->Get_detector_id() == 18){
                        h1_fatima_time_differences_SCI41[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time());
                        h1_fatima_time_differences_energy_SCI41[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time(),hit->Get_energy());
                        if (hit->Get_detector_id() < 10 ) {
                            h1_fatima_time_differences_energy_SCI41_sum->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time(),hit->Get_energy());
                            if (hit->Get_fast_lead_time() - hit2->Get_fast_lead_time() > - 305) h1_fatima_time_differences_energy_SCI41_gated->Fill(hit->Get_energy());
                        }
                    }
                    
                    
                    
                }
            }

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
    if(fNEvents == 0){
        c4LOG(warning, "No events processed, histograms will not be saved!");
        return;
    }
    if (fHitFatimaTwinpeaks)
    {
        folder_fatima->Write();
        c4LOG(info, "FATIMA histograms written to file");
    }
}

ClassImp(FatimaOnlineSpectra)
