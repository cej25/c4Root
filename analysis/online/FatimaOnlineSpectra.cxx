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

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");

    TFolder * fatima_spectra_folder = new TFolder("Fatima", "Fatima");

    run->AddObject(fatima_spectra_folder);

    // energy spectra:
    c_fatima_slowToT  = new TCanvas("c_fatima_slowToT","slow ToT Fatima spectra",650,350);
    c_fatima_slowToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_slowToT->cd(ihist+1);
        h1_fatima_slowToT[ihist] = new TH1F(Form("h1_fatima_slowToT_%d",ihist),Form("Fatima slow ToT detector %d",ihist),4000,0,2.5e3);
        h1_fatima_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_fatima_slowToT[ihist]->Draw();
    }
    c_fatima_slowToT->cd(0);

    fatima_spectra_folder->Add(c_fatima_slowToT);
    
    // energy spectra:
    c_fatima_fastToT  = new TCanvas("c_fatima_fastToT","fast ToT Fatima spectra",650,350);
    c_fatima_fastToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_fastToT->cd(ihist+1);
        h1_fatima_fastToT[ihist] = new TH1F(Form("h1_fatima_fastToT_%d",ihist),Form("Fatima fast ToT detector %d",ihist),4000,0,2.5e3);
        h1_fatima_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_fatima_fastToT[ihist]->Draw();
    }
    c_fatima_fastToT->cd(0);

    fatima_spectra_folder->Add(c_fatima_fastToT);
    
    
    // energy spectra:
    c_fatima_energies  = new TCanvas("c_fatima_energies","Fatima Energy spectra",650,350);
    c_fatima_energies->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_energies->cd(ihist+1);
        h1_fatima_energies[ihist] = new TH1F(Form("h1_fatima_energies_%d",ihist),Form("Fatima detector %d energy",ihist),4000,0,10e3);
        h1_fatima_energies[ihist]->GetXaxis()->SetTitle("Energy (keV)");
        h1_fatima_energies[ihist]->Draw();
    }
    c_fatima_energies->cd(0);

    fatima_spectra_folder->Add(c_fatima_energies);
    
    // energy spectra:
    c_fatima_fast_v_slow  = new TCanvas("c_fatima_fast_v_slow","fast vs slow ToT Fatima spectra",650,350);
    c_fatima_fast_v_slow->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_fast_v_slow->cd(ihist+1);
        h2_fatima_fast_v_slow[ihist] = new TH2F(Form("h2_fatima_fast_v_slow_ToT_%d",ihist),Form("FATIMA fast vs. slow detector %d",ihist),1000,0,2.5e3,1000,0,2.5e3);
        h2_fatima_fast_v_slow[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->Draw("COLZ");
    }
    c_fatima_fast_v_slow->cd(0);

    fatima_spectra_folder->Add(c_fatima_fast_v_slow);
    
    // Time spectra:
    c_fatima_time_spectra_divided  = new TCanvas("c_fatima_time_spectra_divided","Fatima time spectra",650,350);
    c_fatima_time_spectra_divided->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_spectra_divided->cd(ihist+1);
        h1_fatima_abs_time[ihist] = new TH1F(Form("h1_fatima_abs_time_%d",ihist),Form("FATIMA time spectrum detectors %d",ihist),100,0,2.7e12);
        h1_fatima_abs_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_fatima_abs_time[ihist]->Draw();
    }
    c_fatima_time_spectra_divided->cd(0);

    fatima_spectra_folder->Add(c_fatima_time_spectra_divided);

    c_fatima_energy = new TCanvas("c_fatima_energy","Fatima energy spectrum",650,350);
    h2_fatima_energy = new TH2F("h2_fatima_energy","FATIMA energy (keV)",5000,0,10e3,NDetectors,0,NDetectors);
    h2_fatima_energy->GetXaxis()->SetTitle("Energy (keV)");
    h2_fatima_energy->GetYaxis()->SetTitle("Detector nr.");
    h2_fatima_energy->Draw("COLZ");
    fatima_spectra_folder->Add(c_fatima_energy);

    c_fatima_energy_uncal = new TCanvas("c_fatima_energy_uncal","Fatima energy spectrum",650,350);
    h2_fatima_energy_uncal = new TH2F("h2_fatima_energy_uncal","FATIMA energy (keV)",5000,0,10e3,NDetectors,0,NDetectors);
    h2_fatima_energy_uncal->GetXaxis()->SetTitle("Energy (binnr)");
    h2_fatima_energy_uncal->GetYaxis()->SetTitle("Detector nr.");
    h2_fatima_energy_uncal->Draw("COLZ");
    fatima_spectra_folder->Add(c_fatima_energy_uncal);

    // Hit patterns:
    c_fatima_hitpatterns  = new TCanvas("c_fatima_hitpatterns","Fatima hit patterns",650,350);
    c_fatima_hitpatterns->Divide(2,1);

    c_fatima_hitpatterns->cd(1);
    h1_fatima_hitpattern_slow = new TH1F("h1_fatima_hitpattern_slow","FATIMA slow hit patterns",NDetectors,0,NDetectors);
    h1_fatima_hitpattern_slow->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_slow->GetYaxis()->SetTitle("Hits");
    h1_fatima_hitpattern_slow->Draw();
    
    c_fatima_hitpatterns->cd(2);
    h1_fatima_hitpattern_fast = new TH1F("h1_fatima_hitpattern_fast","FATIMA fast hit patterns",NDetectors,0,NDetectors);
    h1_fatima_hitpattern_fast->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_fast->GetYaxis()->SetTitle("Hits");
    h1_fatima_hitpattern_fast->Draw();
    c_fatima_hitpatterns->cd(0);
    
    fatima_spectra_folder->Add(c_fatima_hitpatterns);
    
    
    c_fatima_time_differences = new TCanvas("c_fatima_time_differences","Time coincidences to detector 0",650,350);
    c_fatima_time_differences->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_differences->cd(ihist+1);
        h1_fatima_time_differences[ihist] = new TH1F(Form("h1_fatima_time_differences_%d",ihist),Form("FATIMA time spectrum t_%d - t_0",ihist),1000,-500,500);
        h1_fatima_time_differences[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_fatima_time_differences[ihist]->Draw();
    }
    c_fatima_time_differences->cd(0);

    fatima_spectra_folder->Add(c_fatima_time_differences);
    
    c_fatima_energy_energy = new TCanvas("c_fatima_energy_energy","Fatima energy-energy, det 0 vs det 1 dt < 1000 ns",650,350);
    h2_fatima_energy_energy= new TH2F("h2_fatima_energy_energy","FATIMA energy-energy det0 vs det1 dt < 1000 ns",500,0,1.5e3,500,0,1.5e3);
    h2_fatima_energy_energy->GetXaxis()->SetTitle("Energy (keV)");
    h2_fatima_energy_energy->GetYaxis()->SetTitle("Energy (keV)");
    c_fatima_energy_energy->SetLogz();
    h2_fatima_energy_energy->Draw("COLZ");
    fatima_spectra_folder->Add(c_fatima_energy_energy);
    
    
    c_fatima_time_differences_SCI41 = new TCanvas("c_fatima_time_differences_SCI41","Time coincidences to detector SCI41",650,350);
    c_fatima_time_differences_SCI41->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_differences_SCI41->cd(ihist+1);
        h1_fatima_time_differences_SCI41[ihist] = new TH1F(Form("h1_fatima_time_differences_%d_SCI41",ihist),Form("FATIMA time spectrum t_%d - t(SCI41)",ihist),1000,-500,500);
        h1_fatima_time_differences_SCI41[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_fatima_time_differences_SCI41[ihist]->Draw();
    }
    c_fatima_time_differences_SCI41->cd(0);
    fatima_spectra_folder->Add(c_fatima_time_differences_SCI41);

    
    
    
    c_fatima_time_differences_energy_SCI41 = new TCanvas("c_fatima_time_differences_energy_SCI41","energy vs dt to detector 0 vs SCI41",650,350);
    c_fatima_time_differences_energy_SCI41->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_fatima_time_differences_energy_SCI41->cd(ihist+1);
        h1_fatima_time_differences_energy_SCI41[ihist] = new TH2F(Form("h1_fatima_time_differences_energy_%d_SCI41",ihist),Form("FATIMA t_%d - t(SCI41) vs energy",ihist),1000,-500,500,500,0,1.5e3);
        h1_fatima_time_differences_energy_SCI41[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_fatima_time_differences_energy_SCI41[ihist]->GetYaxis()->SetTitle("Energy (keV)");
        h1_fatima_time_differences_energy_SCI41[ihist]->Draw();
    }
    c_fatima_time_differences_energy_SCI41->cd(0);
    fatima_spectra_folder->Add(c_fatima_time_differences_energy_SCI41);

    
    c_fatima_time_differences_energy_SCI41_sum = new TCanvas("c_fatima_time_differences_energy_SCI41_sum","energy vs dt(t_any - SCI41)",650,350);
    h1_fatima_time_differences_energy_SCI41_sum = new TH2F("h1_fatima_time_differences_energy_SCI41_sum","FATIMA t_any - t(SCI41) vs energy",1000,-500,1000,500,0,1.5e3);
    h1_fatima_time_differences_energy_SCI41_sum->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_time_differences_energy_SCI41_sum->GetYaxis()->SetTitle("Energy (keV)");
    h1_fatima_time_differences_energy_SCI41_sum->Draw();
    fatima_spectra_folder->Add(c_fatima_time_differences_energy_SCI41_sum);

    
    
    

    
    
    run->GetHttpServer()->RegisterCommand("Reset_Fatima_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

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

    h1_fatima_hitpattern_fast->Reset();
    h1_fatima_hitpattern_slow->Reset();
    h1_fatima_time_differences_energy_SCI41_sum->Reset();
    h2_fatima_energy->Reset();
    h2_fatima_energy_uncal->Reset();
    h2_fatima_energy_energy->Reset();
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
                    if (!(TMath::Abs(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time())<1000)) continue;
                    if (hit->Get_detector_id() == 0 && hit2->Get_detector_id() == 1){
                        h2_fatima_energy_energy->Fill(hit->Get_energy(),hit2->Get_energy());
                    }else if (hit->Get_detector_id() == 1 && hit2->Get_detector_id() == 0){
                        h2_fatima_energy_energy->Fill(hit2->Get_energy(),hit->Get_energy());
                    }
                    
                    h1_fatima_time_differences[hit->Get_detector_id()]->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time());
                    
                    if (hit->Get_detector_id() == 18){
                        h1_fatima_time_differences_SCI41[hit2->Get_detector_id()]->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time());
                        h1_fatima_time_differences_energy_SCI41[hit2->Get_detector_id()]->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time(),hit2->Get_energy());
                        if (hit2->Get_detector_id() < 10 ) h1_fatima_time_differences_energy_SCI41_sum->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time(),hit2->Get_energy());
                    }else if (hit2->Get_detector_id() == 18){
                        h1_fatima_time_differences_SCI41[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time());
                        h1_fatima_time_differences_energy_SCI41[hit->Get_detector_id()]->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time(),hit->Get_energy());
                        if (hit->Get_detector_id() < 10 ) h1_fatima_time_differences_energy_SCI41_sum->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time(),hit->Get_energy());
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
    if (fHitFatimaTwinpeaks)
    {
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_slowToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_fastToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_energies[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_abs_time[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_time_differences[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h2_fatima_fast_v_slow[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_time_differences_SCI41[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_fatima_time_differences_energy_SCI41[ihist]->Write();
        
        h1_fatima_hitpattern_fast->Write();
        h1_fatima_hitpattern_slow->Write();
        h2_fatima_energy_energy->Write();
        h2_fatima_energy->Write();
        h2_fatima_energy_uncal->Write();
        h1_fatima_time_differences_energy_SCI41_sum->Write();
        

    
    }
}

ClassImp(FatimaOnlineSpectra)
