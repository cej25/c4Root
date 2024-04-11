// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaNearlineSpectra.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>
#include <sstream>

FatimaNearlineSpectra::FatimaNearlineSpectra() 
    : FatimaNearlineSpectra("FatimaNearlineSpectra")
    {
    }

FatimaNearlineSpectra::FatimaNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

FatimaNearlineSpectra::~FatimaNearlineSpectra()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
}

InitStatus FatimaNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fatima = gDirectory->mkdir("FATIMA");
    gDirectory->cd("FATIMA");

    dir_fatima_slowToT = gDirectory->mkdir("SlowToT"); // do these just exist in bplast already lol
    dir_fatima_fastToT = gDirectory->mkdir("FastToT");
    dir_fatima_hitpattern = gDirectory->mkdir("Hit Pattern");
    dir_fatima_fast_v_slow = gDirectory->mkdir("Fast Vs. Slow");
    dir_fatima_energy_spectra = gDirectory->mkdir("Energy Spectra");
    dir_fatima_time_spectra = gDirectory->mkdir("Time Spectra");

    int min_detector_id = *min_element(detectors.begin(),detectors.end());
    int max_detector_id = *max_element(detectors.begin(), detectors.end());
    number_detectors = detectors.size();

    // Slow ToT:
    dir_fatima_slowToT->cd();
    h1_fatima_slowToT.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        h1_fatima_slowToT[ihist] = new TH1F(Form("h1_fatima_slowToT_%d",detectors.at(ihist)),Form("Fatima slow ToT detector %d",detectors.at(ihist)),fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h1_fatima_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
    }

    //fast ToT
    dir_fatima_fastToT->cd();
    h1_fatima_fastToT.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        h1_fatima_fastToT[ihist] = new TH1F(Form("h1_fatima_fastToT_%d",detectors.at(ihist)),Form("Fatima fast ToT detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high);
        h1_fatima_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");        
    }
    
    //energy spectrum:
    dir_fatima_energy_spectra->cd();
    h1_fatima_energy.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        h1_fatima_energy[ihist] = new TH1F(Form("h1_fatima_energy_%d",detectors.at(ihist)),Form("Fatima energy detector %d",detectors.at(ihist)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
    }
    
    // fast vs slow:
    dir_fatima_fast_v_slow->cd();
    h2_fatima_fast_v_slow.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        h2_fatima_fast_v_slow[ihist] = new TH2F(Form("h2_fatima_fast_v_slow_ToT_%d",detectors.at(ihist)),Form("FATIMA fast vs. slow detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high,fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h2_fatima_fast_v_slow[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        h2_fatima_fast_v_slow[ihist]->SetOption("COLZ");        
    }
    
    // Time spectra:
    dir_fatima_time_spectra->cd();
    h1_fatima_abs_time.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        h1_fatima_abs_time[ihist] = new TH1F(Form("h1_fatima_abs_time_%d",detectors.at(ihist)),Form("Fatima absolute DAQ time detector %d",detectors.at(ihist)),1000,0,2.7e12); // up to 45 mins in ns :)
        h1_fatima_abs_time[ihist]->GetXaxis()->SetTitle("Timestamp (ns)");
    }

    //2D energy spectrum
    dir_fatima_energy_spectra->cd();
    h2_fatima_energy_vs_detid = new TH2F("h2_fatima_energy_vs_detid","FATIMA energies",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5); //such that the y-axis is the detector id and not the index
    h2_fatima_energy_vs_detid->GetXaxis()->SetTitle("Energy (keV)");
    h2_fatima_energy_vs_detid->GetYaxis()->SetTitle("Detector nr.");
    h2_fatima_energy_vs_detid->SetOption("COLZ");

    //2D uncalibrated energy spectrum
    h2_fatima_energy_uncal_vs_detid = new TH2F("h2_fatima_energy_uncal_vs_detid","FATIMA uncal energy (arb.)",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5);
    h2_fatima_energy_uncal_vs_detid->GetXaxis()->SetTitle("Energy (arb.)");
    h2_fatima_energy_uncal_vs_detid->GetYaxis()->SetTitle("Detector nr.");
    h2_fatima_energy_uncal_vs_detid->SetOption("COLZ");

    // Hit patterns:
    dir_fatima_hitpattern->cd();

    h1_fatima_hitpattern_slow = new TH1F("h1_fatima_hitpattern_slow","FATIMA slow hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5);
    h1_fatima_hitpattern_slow->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_slow->GetYaxis()->SetTitle("Hits");
    
    h1_fatima_hitpattern_fast = new TH1F("h1_fatima_hitpattern_fast","FATIMA fast hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5);
    h1_fatima_hitpattern_fast->GetXaxis()->SetTitle("Detector nr.");
    h1_fatima_hitpattern_fast->GetYaxis()->SetTitle("Hits");
    
    h1_fatima_multiplicity = new TH1F("h1_fatima_multiplicity","FATIMA event multiplicity",20,0,20);
    h1_fatima_multiplicity->GetXaxis()->SetTitle("Event multiplicity");
    h1_fatima_multiplicity->GetYaxis()->SetTitle("Counts");
    
    dir_fatima_time_differences.resize(number_reference_detectors);
    h1_fatima_time_differences.resize(number_reference_detectors);
    h2_fatima_time_differences_vs_energy.resize(number_reference_detectors);
    for (int ihist = 0; ihist < number_reference_detectors; ihist++)
    {
        std::stringstream name;
        name << "time_differences_rel_det_" << dt_reference_detectors.at(ihist);
        dir_fatima_time_differences[ihist] = dir_fatima->mkdir(name.str().c_str());
        dir_fatima_time_differences[ihist]->cd();

        h1_fatima_time_differences[ihist].resize(number_detectors);

        for (int detid_idx = 0; detid_idx < number_detectors; detid_idx++)
        {
            h1_fatima_time_differences[ihist][detid_idx] = new TH1F(Form("h1_fatima_rel_time_det_%i_det_%i",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),Form("Fatima delta time t(%i) - t(%i)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),1000,-100,100); 
            h1_fatima_time_differences[ihist][detid_idx]->GetXaxis()->SetTitle(Form("dt t(%i) - t(%i) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
        }

        h2_fatima_time_differences_vs_energy[ihist].resize(number_detectors);

        for (int detid_idx = 0; detid_idx < number_detectors; detid_idx++)
        {
            h2_fatima_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_fatima_rel_time_det_%i_det_%i_vs_energy",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),Form("Fatima delta time t(%i) - t(%i) vs energy",detectors.at(detid_idx),dt_reference_detectors.at(ihist)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,1000,-100,100); 
            h2_fatima_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%i) - t(%i) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            h2_fatima_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %i (keV)",detectors.at(detid_idx)));
            h2_fatima_time_differences_vs_energy[ihist][detid_idx]->SetOption("COLZ");
        }
    }

    dir_fatima->cd();
    gDirectory = tmp;
 
    return kSUCCESS;
    
}


void FatimaNearlineSpectra::Exec(Option_t* option)
{   
    
    auto start = std::chrono::high_resolution_clock::now();
    
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
        // ++events should go here, no?
    }
    
    fNEvents += 1;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}


void FatimaNearlineSpectra::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
}

void FatimaNearlineSpectra::FinishTask()
{
    if(fNEvents == 0){
        c4LOG(warning, "No events processed, histograms will not be saved!");
        return;
    }
   
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fatima->Write();
    gDirectory = tmp;

    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(FatimaNearlineSpectra)
