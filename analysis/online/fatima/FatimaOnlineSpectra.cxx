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

    folder_fatima_slowToT = new TFolder("SlowToT", "slowToT");
    folder_fatima_fastToT = new TFolder("FastToT", "fastToT");
    folder_fatima_hitpattern = new TFolder("Hitpattern", "hitpattern");
    folder_fatima_fast_v_slow = new TFolder("Fast_v_Slow", "fast_v_slow");
    folder_fatima_time_spectra = new TFolder("Time_Spectra", "time_spectra");
    folder_fatima_energy_spectra = new TFolder("Energy", "energy");
    folder_fatima->Add(folder_fatima_slowToT);
    folder_fatima->Add(folder_fatima_fastToT);
    folder_fatima->Add(folder_fatima_hitpattern);
    folder_fatima->Add(folder_fatima_fast_v_slow);
    folder_fatima->Add(folder_fatima_time_spectra);
    folder_fatima->Add(folder_fatima_energy_spectra);


    int min_detector_id = *min_element(detectors.begin(),detectors.end());
    int max_detector_id = *max_element(detectors.begin(), detectors.end());
    number_detectors = detectors.size();


    // Slow ToT:
    c_fatima_slowToT  = new TCanvas("c_fatima_slowToT","slow ToT Fatima spectra",650,350);
    c_fatima_slowToT->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_fatima_slowToT = new TH1F*[number_detectors];
    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_fatima_slowToT->cd(ihist+1);
        h1_fatima_slowToT[ihist] = new TH1F(Form("h1_fatima_slowToT_%d",detectors.at(ihist)),Form("Fatima slow ToT detector %d",detectors.at(ihist)),fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h1_fatima_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_fatima_slowToT[ihist]->Draw();
        folder_fatima_slowToT->Add(h1_fatima_slowToT[ihist]);
        
    }
    c_fatima_slowToT->cd(0);
    folder_fatima_slowToT->Add(c_fatima_slowToT);


    //fast ToT

    c_fatima_fastToT  = new TCanvas("c_fatima_fastToT","Fast ToT Fatima spectra",650,350);
    c_fatima_fastToT->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_fatima_fastToT = new TH1F*[number_detectors];

    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_fatima_fastToT->cd(ihist+1);
        h1_fatima_fastToT[ihist] = new TH1F(Form("h1_fatima_fastToT_%d",detectors.at(ihist)),Form("Fatima fast ToT detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high);
        h1_fatima_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_fatima_fastToT[ihist]->Draw();
        folder_fatima_fastToT->Add(h1_fatima_fastToT[ihist]);
        
    }
    c_fatima_fastToT->cd(0);
    folder_fatima_fastToT->Add(c_fatima_fastToT);
    
    //energy spectrum:
    
    c_fatima_energy  = new TCanvas("c_fatima_energy","Fatima energy spectra",650,350);
    c_fatima_energy->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_fatima_energy = new TH1F*[number_detectors];

    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_fatima_energy->cd(ihist+1);
        h1_fatima_energy[ihist] = new TH1F(Form("h1_fatima_energy_%d",detectors.at(ihist)),Form("Fatima energy detector %d",detectors.at(ihist)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_fatima_energy[ihist]->Draw();
        folder_fatima_energy_spectra->Add(h1_fatima_energy[ihist]);
        
    }
    c_fatima_energy->cd(0);
    folder_fatima_energy_spectra->Add(c_fatima_energy);
    
    
    // fast vs slow:
    c_fatima_fast_v_slow  = new TCanvas("c_fatima_fast_v_slow","fast vs slow ToT Fatima spectra",650,350);
    c_fatima_fast_v_slow->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));

    h2_fatima_fast_v_slow = new TH2F * [number_detectors];

    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_fatima_fast_v_slow->cd(ihist+1);
        h2_fatima_fast_v_slow[ihist] = new TH2F(Form("h2_fatima_fast_v_slow_ToT_%d",detectors.at(ihist)),Form("FATIMA fast vs. slow detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high,fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h2_fatima_fast_v_slow[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->Draw("COLZ");
        folder_fatima_fast_v_slow->Add(h2_fatima_fast_v_slow[ihist]);
        
    }
    c_fatima_fast_v_slow->cd(0);
    folder_fatima_fast_v_slow->Add(c_fatima_fast_v_slow);
    
    // Time spectra:
    
    c_fatima_time_spectra_divided  = new TCanvas("c_fatima_time_spectra_divided","Fatima absolute time spectra",650,350);
    c_fatima_time_spectra_divided->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_fatima_abs_time = new TH1F*[number_detectors];

    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_fatima_time_spectra_divided->cd(ihist+1);
        h1_fatima_abs_time[ihist] = new TH1F(Form("h1_fatima_abs_time_%d",detectors.at(ihist)),Form("Fatima absolute DAQ time detector %d",detectors.at(ihist)),1000,0,2.7e12); // up to 45 mins in ns :)
        h1_fatima_abs_time[ihist]->GetXaxis()->SetTitle("Timestamp (ns)");
        h1_fatima_abs_time[ihist]->Draw();
        folder_fatima_fastToT->Add(h1_fatima_abs_time[ihist]);
        
    }
    c_fatima_time_spectra_divided->cd(0);
    folder_fatima_time_spectra->Add(c_fatima_time_spectra_divided);


    //2D energy spectrum
    c_fatima_energy_vs_detid = new TCanvas("c_fatima_energy_vs_detid","Fatima energy spectrum",650,350);
    h2_fatima_energy_vs_detid = new TH2F("h2_fatima_energy_vs_detid","FATIMA energies",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5); //such that the y-axis is the detector id and not the index
    h2_fatima_energy_vs_detid->GetXaxis()->SetTitle("Energy (keV)");
    h2_fatima_energy_vs_detid->GetYaxis()->SetTitle("Detector nr.");
    h2_fatima_energy_vs_detid->Draw("COLZ");
    folder_fatima_energy_spectra->Add(c_fatima_energy_vs_detid);

    //2D uncalibrated energy spectrum
    c_fatima_energy_uncal = new TCanvas("c_fatima_energy_uncal","Fatima energy spectrum",650,350);
    h2_fatima_energy_uncal_vs_detid = new TH2F("h2_fatima_energy_uncal_vs_detid","FATIMA uncal energy (arb.)",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5);
    h2_fatima_energy_uncal_vs_detid->GetXaxis()->SetTitle("Energy (arb.)");
    h2_fatima_energy_uncal_vs_detid->GetYaxis()->SetTitle("Detector nr.");
    h2_fatima_energy_uncal_vs_detid->Draw("COLZ");
    folder_fatima_energy_spectra->Add(c_fatima_energy_uncal);

    // Hit patterns:
    c_fatima_hitpatterns  = new TCanvas("c_fatima_hitpatterns","Fatima hit patterns",650,350);
    c_fatima_hitpatterns->Divide(2,1);

    c_fatima_hitpatterns->cd(1);
    h1_fatima_hitpattern_slow = new TH1F("h1_fatima_hitpattern_slow","FATIMA slow hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5);
    h1_fatima_hitpattern_slow->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_slow->GetYaxis()->SetTitle("Hits");
    h1_fatima_hitpattern_slow->Draw();
    folder_fatima_hitpattern->Add(h1_fatima_hitpattern_slow);
    
    c_fatima_hitpatterns->cd(2);
    h1_fatima_hitpattern_fast = new TH1F("h1_fatima_hitpattern_fast","FATIMA fast hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5);
    h1_fatima_hitpattern_fast->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_fast->GetYaxis()->SetTitle("Hits");
    h1_fatima_hitpattern_fast->Draw();
    folder_fatima_hitpattern->Add(h1_fatima_hitpattern_fast);
    c_fatima_hitpatterns->cd(0);
    
    folder_fatima_hitpattern->Add(c_fatima_hitpatterns);


    // Hit patterns:
    c_fatima_event_multiplicity  = new TCanvas("c_fatima_event_multiplicity","Fatima event multiplicities",650,350);
    
    h1_fatima_multiplicity = new TH1F("h1_fatima_multiplicity","FATIMA event multiplicity",50,0,50);
    h1_fatima_multiplicity->GetXaxis()->SetTitle("Event multiplicity");
    h1_fatima_multiplicity->Draw();
    folder_fatima_hitpattern->Add(h1_fatima_multiplicity);
    c_fatima_event_multiplicity->cd(0);
    
    folder_fatima_hitpattern->Add(c_fatima_event_multiplicity);
    
    //
    h1_fatima_time_differences = new TH1F ** [number_reference_detectors];
    h2_fatima_time_differences_vs_energy = new TH2F ** [number_reference_detectors];
    for (int ihist = 0; ihist < number_reference_detectors; ihist++){
        folder_fatima_time_differences = new TFolder(Form("time_differences_rel_det_%i",dt_reference_detectors.at(ihist)), Form("time_differences_rel_det_%i",dt_reference_detectors.at(ihist)));
        folder_fatima->Add(folder_fatima_time_differences);

        c_fatima_time_differences  = new TCanvas(Form("c_fatima_time_differences_rel_det_%i",dt_reference_detectors.at(ihist)),"Fatima relative time differences",650,350);
        c_fatima_time_differences->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
        h1_fatima_time_differences[ihist] = new TH1F*[number_detectors];

        for (int detid_idx = 0; detid_idx < number_detectors; detid_idx++){
            c_fatima_time_differences->cd(detid_idx+1);
            h1_fatima_time_differences[ihist][detid_idx] = new TH1F(Form("h1_fatima_rel_time_det_%i_det_%i",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),Form("Fatima delta time t(%i) - t(%i)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),1000,-100,100); 
            h1_fatima_time_differences[ihist][detid_idx]->GetXaxis()->SetTitle(Form("dt t(%i) - t(%i) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            h1_fatima_time_differences[ihist][detid_idx]->Draw();
            folder_fatima_fastToT->Add(h1_fatima_time_differences[ihist][detid_idx]);
            
        }
        c_fatima_time_differences->cd(0);
        folder_fatima_time_differences->Add(c_fatima_time_differences);



        c_fatima_time_differences_vs_energy  = new TCanvas(Form("c_fatima_time_differences_rel_det_%i_vs_energy",dt_reference_detectors.at(ihist)),"Fatima relative time differences vs energy",650,350);
        c_fatima_time_differences_vs_energy->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
        h2_fatima_time_differences_vs_energy[ihist] = new TH2F*[number_detectors];

        for (int detid_idx = 0; detid_idx < number_detectors; detid_idx++){
            c_fatima_time_differences_vs_energy->cd(detid_idx+1);
            h2_fatima_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_fatima_rel_time_det_%i_det_%i_vs_energy",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),Form("Fatima delta time t(%i) - t(%i) vs energy",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,1000,-100,100); 
            h2_fatima_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%i) - t(%i) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            h2_fatima_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %i (keV)",detectors.at(detid_idx)));
            h2_fatima_time_differences_vs_energy[ihist][detid_idx]->Draw("COLZ");
            folder_fatima_fastToT->Add(h2_fatima_time_differences_vs_energy[ihist][detid_idx]);
            
        }
        c_fatima_time_differences_vs_energy->cd(0);
        folder_fatima_time_differences->Add(c_fatima_time_differences_vs_energy);
    }

    
    run->GetHttpServer()->RegisterCommand("Reset_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

    return kSUCCESS;
    
}

void FatimaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting histograms!");
    for (int ihist = 0; ihist<number_detectors; ihist++) h1_fatima_slowToT[ihist]->Reset();
    for (int ihist = 0; ihist<number_detectors; ihist++) h1_fatima_fastToT[ihist]->Reset();
    for (int ihist = 0; ihist<number_detectors; ihist++) h1_fatima_abs_time[ihist]->Reset();
    for (int ihist = 0; ihist<number_detectors; ihist++) h1_fatima_energy[ihist]->Reset();
    for (int ihist = 0; ihist<number_detectors; ihist++) h2_fatima_fast_v_slow[ihist]->Reset();
    
    h1_fatima_hitpattern_fast->Reset();
    h1_fatima_hitpattern_slow->Reset();
    h2_fatima_energy_vs_detid->Reset();

    h2_fatima_energy_uncal_vs_detid->Reset();
    //for (int ihist = 0; ihist<number_detectors; ihist++) h1_fatima_time_differences[ihist]->Reset();
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

    for (int ihist = 0; ihist<number_detectors; ihist++)
    {
        if(h1_fatima_slowToT[ihist]->GetEntries() != 0)
        {
            h1_fatima_slowToT[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_slowTot_%d.png",detectors.at(ihist)));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_fastToT[ihist]->GetEntries() != 0)
        {
            h1_fatima_fastToT[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_fastTot_%d.png",detectors.at(ihist)));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_abs_time[ihist]->GetEntries() != 0)
        {
            h1_fatima_abs_time[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_abs_time_%d.png",detectors.at(ihist)));
            c_fatima_snapshot->Clear();
        }
        if(h1_fatima_energy[ihist]->GetEntries() != 0)
        {
            h1_fatima_energy[ihist]->Draw();
            c_fatima_snapshot->SaveAs(Form("h1_fatima_energy_%d.png",detectors.at(ihist)));
            c_fatima_snapshot->Clear();
        }

        if(h2_fatima_fast_v_slow[ihist]->GetEntries() != 0)
        {
            h2_fatima_fast_v_slow[ihist]->Draw("COLZ");
            c_fatima_snapshot->SaveAs(Form("h2_fatima_fast_v_slow_%d.png",detectors.at(ihist)));
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
        event_multiplicity = 0;
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);
            if (!hit) continue;


            double slow_ToT1 = hit->Get_slow_ToT();
            double fast_ToT1 = hit->Get_fast_ToT();
            double energy1 = hit->Get_energy();
            double fast_lead1 = hit->Get_fast_lead_time();
            
            int detector_id1 = hit->Get_detector_id();
            int detector_index1 = GetDetectorIndex(detector_id1);
            if (detector_index1 >= number_detectors) {continue;} // this implies that the hit corresponds to a detector that is not specified for plotting.

            event_multiplicity ++; // count only "valid events"
            h1_fatima_slowToT[detector_index1]->Fill(slow_ToT1);
            h1_fatima_energy[detector_index1]->Fill(energy1);
            h1_fatima_fastToT[detector_index1]->Fill(fast_ToT1);
            h2_fatima_fast_v_slow[detector_index1]->Fill(fast_ToT1, slow_ToT1);
            h1_fatima_abs_time[detector_index1]->Fill(fast_lead1);
            
            h2_fatima_energy_vs_detid->Fill(energy1, detector_id1);
            h2_fatima_energy_uncal_vs_detid->Fill(slow_ToT1, detector_id1);
            
            if (fast_ToT1 != 0 ) h1_fatima_hitpattern_fast->Fill(detector_id1);
            if (slow_ToT1 != 0 ) h1_fatima_hitpattern_slow->Fill(detector_id1);
            
            //TWO FOLD COINCIDENCES:
            if (nHits > 1 && number_reference_detectors > 0){
                for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++){
                    if (ihit2 == ihit) {continue;}

                    FatimaTwinpeaksCalData * hit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit2); // I want this to be the reference detector for easier code:
                    if (!(TMath::Abs(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time())<100)) continue;
                    
                    int detector_id2 = hit2->Get_detector_id();
                    int detector_index2 = GetReferenceDetectorIndex(detector_id2);
                    if (detector_index2 >= number_reference_detectors) {continue;} // this implies that the hit corresponds to a detector that is not specified as a reference detector.

                    double slow_ToT2 = hit2->Get_slow_ToT();
                    double fast_ToT2 = hit2->Get_fast_ToT();
                    double energy2 = hit2->Get_energy();
                    double fast_lead2 = hit2->Get_fast_lead_time();

                    h1_fatima_time_differences[detector_index2][detector_index1]->Fill(fast_lead1 - fast_lead2);
                    h2_fatima_time_differences_vs_energy[detector_index2][detector_index1]->Fill(energy1,fast_lead1-fast_lead2);



                }
            }
        }
        h1_fatima_multiplicity->Fill(event_multiplicity);
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
        if(folder_fatima) folder_fatima->Write();
        c4LOG(info, "FATIMA histograms written to file");
    }
}

ClassImp(FatimaOnlineSpectra)
