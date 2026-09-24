/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                  E. Gandolfo (og fatima), C.E. Jones                       *
 *                                  08.25                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "LisaFastOnlineSpectra.h"
#include "EventHeader.h"
#include "LisaFastCalData.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>
#include <sstream>

LisaFastOnlineSpectra::LisaFastOnlineSpectra() : LisaFastOnlineSpectra("LisaFastOnlineSpectra")
{
    lisafast_configuration = TLisaFastConfiguration::GetInstance();
}

LisaFastOnlineSpectra::LisaFastOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitLisaFast(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    lisafast_configuration = TLisaFastConfiguration::GetInstance();
}

LisaFastOnlineSpectra::~LisaFastOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitLisaFast)
        delete fHitLisaFast;
}

void LisaFastOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}



InitStatus LisaFastOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitLisaFast = (TClonesArray*)mgr->GetObject("LisaFastCalData");
    c4LOG_IF(fatal, !fHitLisaFast, "Branch LisaFastCalData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_lisafast = new TDirectory("FATIMA", "FATIMA", "", 0);
    // mgr->Register("FATIMA", "FATIMA Directory", dir_lisafast, false); // allow other tasks to access directory.
    histograms->Add(dir_lisafast);

    dir_lisafast_slowToT = dir_lisafast->mkdir("SlowToT");
    dir_lisafast_fastToT = dir_lisafast->mkdir("FastToT");
    dir_lisafast_hitpattern = dir_lisafast->mkdir("Hit Pattern");
    dir_lisafast_fast_v_slow = dir_lisafast->mkdir("Fast Vs. Slow");
    dir_lisafast_energy_spectra = dir_lisafast->mkdir("Energy Spectra");
    dir_lisafast_time_spectra = dir_lisafast->mkdir("Time Spectra");

    int min_detector_id = *min_element(detectors.begin(),detectors.end());
    int max_detector_id = *max_element(detectors.begin(), detectors.end());
    number_detectors = detectors.size();

    // Slow ToT:
    c_lisafast_slowToT  = new TCanvas("c_lisafast_slowToT","slow ToT LisaFast spectra",650,350);
    c_lisafast_slowToT->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_lisafast_slowToT.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        c_lisafast_slowToT->cd(ihist+1);
        h1_lisafast_slowToT[ihist] = MakeTH1(dir_lisafast_slowToT, "F", Form("h1_lisafast_slowToT_%d",detectors.at(ihist)), Form("LisaFast slow ToT detector %d",detectors.at(ihist)),fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high, "ToT [ns]", kSpring, kBlue+2);
        h1_lisafast_slowToT[ihist]->Draw();
    }
    c_lisafast_slowToT->cd(0);
    dir_lisafast_slowToT->Append(c_lisafast_slowToT);

    //fast ToT
    // dir_lisafast_fastToT->cd();
    c_lisafast_fastToT  = new TCanvas("c_lisafast_fastToT","Fast ToT LisaFast spectra",650,350);
    c_lisafast_fastToT->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_lisafast_fastToT.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++)
    {
        c_lisafast_fastToT->cd(ihist+1);
        h1_lisafast_fastToT[ihist] = MakeTH1(dir_lisafast_fastToT, "F", Form("h1_lisafast_fastToT_%d",detectors.at(ihist)),Form("LisaFast fast ToT detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high, "ToT [ns]", kSpring, kBlue+2);
        // h1_lisafast_fastToT[ihist] = new TH1F(Form("h1_lisafast_fastToT_%d",detectors.at(ihist)),Form("LisaFast fast ToT detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high);
        // h1_lisafast_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_lisafast_fastToT[ihist]->Draw();
        
    }
    c_lisafast_fastToT->cd(0);
    dir_lisafast_fastToT->Add(c_lisafast_fastToT);
    
    //energy spectrum:
    // dir_lisafast_energy_spectra->cd();
    c_lisafast_energy  = new TCanvas("c_lisafast_energy","LisaFast energy spectra",650,350);
    c_lisafast_energy->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h1_lisafast_energy.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_lisafast_energy->cd(ihist+1);
        h1_lisafast_energy[ihist] = MakeTH1(dir_lisafast_energy_spectra, "F", Form("h1_lisafast_energy_%d",detectors.at(ihist)),Form("LisaFast energy detector %d",detectors.at(ihist)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
        // h1_lisafast_energy[ihist] = new TH1F(Form("h1_lisafast_energy_%d",detectors.at(ihist)),Form("LisaFast energy detector %d",detectors.at(ihist)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        // h1_lisafast_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_lisafast_energy[ihist]->Draw();
    }
    c_lisafast_energy->cd(0);
    dir_lisafast_energy_spectra->Append(c_lisafast_energy);
    
    // fast vs slow:
    // dir_lisafast_fast_v_slow->cd();
    c_lisafast_fast_v_slow  = new TCanvas("c_lisafast_fast_v_slow","fast vs slow ToT LisaFast spectra",650,350);
    c_lisafast_fast_v_slow->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    h2_lisafast_fast_v_slow.resize(number_detectors);
    for (int ihist = 0; ihist < number_detectors; ihist++){
        c_lisafast_fast_v_slow->cd(ihist+1);
        h2_lisafast_fast_v_slow[ihist] = MakeTH2(dir_lisafast_fast_v_slow, "F", Form("h2_lisafast_fast_v_slow_ToT_%d",detectors.at(ihist)),Form("FATIMA fast vs. slow detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high,fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high, "Fast ToT [ns]", "Slow ToT [ns]");
        // h2_lisafast_fast_v_slow[ihist] = new TH2F(Form("h2_lisafast_fast_v_slow_ToT_%d",detectors.at(ihist)),Form("FATIMA fast vs. slow detector %d",detectors.at(ihist)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high,fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        // h2_lisafast_fast_v_slow[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        // h2_lisafast_fast_v_slow[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        h2_lisafast_fast_v_slow[ihist]->Draw();        
    }
    c_lisafast_fast_v_slow->cd(0);
    dir_lisafast_fast_v_slow->Append(c_lisafast_fast_v_slow);
    
    // Time spectra:
    // dir_lisafast_time_spectra->cd();
    // c_lisafast_time_spectra_divided  = new TCanvas("c_lisafast_time_spectra_divided","LisaFast absolute time spectra",650,350);
    // c_lisafast_time_spectra_divided->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
    // h1_lisafast_abs_time.resize(number_detectors);
    // for (int ihist = 0; ihist < number_detectors; ihist++)
    // {
    //     c_lisafast_time_spectra_divided->cd(ihist+1);
    //     h1_lisafast_abs_time[ihist] = MakeTH1(dir_lisafast_time_spectra, "F", Form("h1_lisafast_abs_time_%d",detectors.at(ihist)),Form("LisaFast absolute DAQ time detector %d",detectors.at(ihist)), 1e3, 0, 2.7e12, "Timestamp [ns]");
    //     // h1_lisafast_abs_time[ihist] = new TH1F(Form("h1_lisafast_abs_time_%d",detectors.at(ihist)),Form("LisaFast absolute DAQ time detector %d",detectors.at(ihist)),1000,0,2.7e12); // up to 45 mins in ns :)
    //     // h1_lisafast_abs_time[ihist]->GetXaxis()->SetTitle("Timestamp (ns)");
    //     h1_lisafast_abs_time[ihist]->Draw();
    // }
    // c_lisafast_time_spectra_divided->cd(0);
    // dir_lisafast_time_spectra->Append(c_lisafast_time_spectra_divided);

    //2D energy spectrum
    // dir_lisafast_energy_spectra->cd();
    c_lisafast_energy_vs_detid = new TCanvas("c_lisafast_energy_vs_detid","LisaFast energy spectrum",650,350);
    h2_lisafast_energy_vs_detid = MakeTH2(dir_lisafast_energy_spectra, "F", "h2_lisafast_energy_vs_detid","FATIMA energies",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5, "Energy [keV]", "Detector");
    // h2_lisafast_energy_vs_detid = new TH2F("h2_lisafast_energy_vs_detid","FATIMA energies",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5); //such that the y-axis is the detector id and not the index
    // h2_lisafast_energy_vs_detid->GetXaxis()->SetTitle("Energy (keV)");
    // h2_lisafast_energy_vs_detid->GetYaxis()->SetTitle("Detector nr.");
    h2_lisafast_energy_vs_detid->Draw();
    dir_lisafast_energy_spectra->Append(c_lisafast_energy_vs_detid);

    //2D uncalibrated energy spectrum
    c_lisafast_energy_uncal = new TCanvas("c_lisafast_energy_uncal","LisaFast energy spectrum",650,350);
    h2_lisafast_energy_uncal_vs_detid = MakeTH2(dir_lisafast_energy_spectra, "F", "h2_lisafast_energy_uncal_vs_detid","FATIMA uncal energy (arb.)",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5, "Energy [a.u.]", "Detector");
    // h2_lisafast_energy_uncal_vs_detid = new TH2F("h2_lisafast_energy_uncal_vs_detid","FATIMA uncal energy (arb.)",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,max_detector_id+1,0-0.5,max_detector_id+0.5);
    // h2_lisafast_energy_uncal_vs_detid->GetXaxis()->SetTitle("Energy (arb.)");
    // h2_lisafast_energy_uncal_vs_detid->GetYaxis()->SetTitle("Detector nr.");
    h2_lisafast_energy_uncal_vs_detid->Draw();
    dir_lisafast_energy_spectra->Append(c_lisafast_energy_uncal);

    // Hit patterns:
    // dir_lisafast_hitpattern->cd();
    c_lisafast_hitpatterns  = new TCanvas("c_lisafast_hitpatterns","LisaFast hit patterns",650,350);
    c_lisafast_hitpatterns->Divide(2,1);

    c_lisafast_hitpatterns->cd(1);
    h1_lisafast_hitpattern_slow = MakeTH1(dir_lisafast_hitpattern, "I", "h1_lisafast_hitpattern_slow","FATIMA slow hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5, "Detector", kRed-3, kBlack);
    // h1_lisafast_hitpattern_slow = new TH1F("h1_lisafast_hitpattern_slow","FATIMA slow hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5);
    // h1_lisafast_hitpattern_slow->GetXaxis()->SetTitle("Detector nr.");
    // h1_lisafast_hitpattern_slow->GetYaxis()->SetTitle("Hits");
    h1_lisafast_hitpattern_slow->Draw();
    
    c_lisafast_hitpatterns->cd(2);
    h1_lisafast_hitpattern_fast = MakeTH1(dir_lisafast_hitpattern, "I", "h1_lisafast_hitpattern_fast","FATIMA fast hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5, "Detector", kRed-3, kBlack);
    // h1_lisafast_hitpattern_fast = new TH1F("h1_lisafast_hitpattern_fast","FATIMA fast hit patterns",max_detector_id+1,0-0.5,max_detector_id+0.5);
    // h1_lisafast_hitpattern_fast->GetXaxis()->SetTitle("Detector nr.");
    // h1_lisafast_hitpattern_fast->GetYaxis()->SetTitle("Hits");
    h1_lisafast_hitpattern_fast->Draw();
    c_lisafast_hitpatterns->cd(0);
    dir_lisafast_hitpattern->Append(c_lisafast_hitpatterns);
    
    c_lisafast_event_multiplicity  = new TCanvas("c_lisafast_event_multiplicity","LisaFast event multiplicities",650,350);
    
    h1_lisafast_multiplicity = MakeTH1(dir_lisafast_hitpattern, "I", "h1_lisafast_multiplicity","FATIMA event multiplicity",20,0,20, "Event Multiplicity", kRed-3, kBlack);
    // h1_lisafast_multiplicity = new TH1F("h1_lisafast_multiplicity","FATIMA event multiplicity",20,0,20);
    // h1_lisafast_multiplicity->GetXaxis()->SetTitle("Event multiplicity");
    // h1_lisafast_multiplicity->GetYaxis()->SetTitle("Counts");
    h1_lisafast_multiplicity->Draw();
    c_lisafast_event_multiplicity->cd(0);
    dir_lisafast_hitpattern->Append(c_lisafast_event_multiplicity);
    
    //time differences!
    number_reference_detectors = (int) dt_reference_detectors.size();
    dir_lisafast_time_differences.resize(number_reference_detectors);

    h1_lisafast_time_differences.resize(number_reference_detectors);
    h2_lisafast_time_differences_vs_energy.resize(number_reference_detectors);
    for (int ihist = 0; ihist < number_reference_detectors; ihist++)
    {
        std::stringstream name;
        name << "time_differences_rel_" << dt_reference_detectors.at(ihist) << "_energy_gate_" << (int)dt_reference_detectors_energy_gates.at(ihist).first << "_" << (int)dt_reference_detectors_energy_gates.at(ihist).second;
        dir_lisafast_time_differences[ihist] = dir_lisafast->mkdir(name.str().c_str());
        dir_lisafast_time_differences[ihist]->cd();
    
        c_lisafast_time_differences = new TCanvas(Form("c_lisafast_time_differences_rel_det_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"lisafast relative time differences",650,350);
        c_lisafast_time_differences->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
        //h1_lisafast_time_differences[ihist] = new TH1F*[number_detectors];
        h1_lisafast_time_differences[ihist].resize(number_detectors);

        for (int detid_idx = 0; detid_idx < number_detectors; detid_idx++)
        {
            c_lisafast_time_differences->cd(detid_idx+1);
            
            h1_lisafast_time_differences[ihist][detid_idx] = MakeTH1(dir_lisafast_time_differences[ihist], "F", Form("h1_lisafast_rel_time_det_%d_to_det_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist),detectors.at(detid_idx),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("FATIMA dT t(%d) - t(%d) gated %d and %d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high, Form("dT t(%d) - t(%d) [ns]",detectors.at(detid_idx),dt_reference_detectors.at(ihist)), kMagenta, kBlue+2);

            // h1_lisafast_time_differences[ihist][detid_idx] = new TH1F(Form("h1_lisafast_rel_time_det_%d_to_det_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist),detectors.at(detid_idx),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("lisafast delta time t(%d) - t(%d) gated %d and %d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high); 
            // h1_lisafast_time_differences[ihist][detid_idx]->GetXaxis()->SetTitle(Form("dt t(%d) - t(%d) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            h1_lisafast_time_differences[ihist][detid_idx]->Draw();
            
        }
        c_lisafast_time_differences->cd(0);
        dir_lisafast_time_differences[ihist]->Append(c_lisafast_time_differences);

        c_lisafast_time_differences_vs_energy  = new TCanvas(Form("c_lisafast_time_differences_rel_det_%d_vs_energy_energy_gate_%d_%d",dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"lisafast relative time differences vs energy",650,350);
        c_lisafast_time_differences_vs_energy->Divide((number_detectors<5) ? number_detectors : 5,(number_detectors%5==0) ? (number_detectors/5) : (number_detectors/5 + 1));
        //h2_lisafast_time_differences_vs_energy[ihist] = new TH2F*[number_detectors];
        h2_lisafast_time_differences_vs_energy[ihist].resize(number_detectors);

        for (int detid_idx = 0; detid_idx < number_detectors; detid_idx++)
        {
            c_lisafast_time_differences_vs_energy->cd(detid_idx+1);
            h2_lisafast_time_differences_vs_energy[ihist][detid_idx] = MakeTH2(dir_lisafast_time_differences[ihist], "F", Form("h1_lisafast_rel_time_det_%d_to_det_%d_vs_energy_energy_gate_%d_%d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("FATIMA dT t(%d) - t(%d) vs Energy, energy gate %d, %d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high, Form("Energy (Detector %d) [keV]",detectors.at(detid_idx)), Form("dT t(%d) - t(%d) [ns]",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            // h2_lisafast_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_lisafast_rel_time_det_%d_to_det_%d_vs_energy_energy_gate_%d_%d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("lisafast delta time t(%d) - t(%d) vs energy, energy gate %d, %d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high); 
            // h2_lisafast_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%d) - t(%d) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            // h2_lisafast_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %d (keV)",detectors.at(detid_idx)));
            h2_lisafast_time_differences_vs_energy[ihist][detid_idx]->Draw();
            
        }
        c_lisafast_time_differences_vs_energy->cd(0);
        dir_lisafast_time_differences[ihist]->Append(c_lisafast_time_differences_vs_energy);
    }

    dir_lisafast->cd();

    
    // ::: Rates :::: //
    // h1_lisafast_rates = new TH1*[number_detectors];
    // detector_counters = new int[number_detectors];
    // detector_rates = new int[number_detectors];
    // for (int i = 0; i < number_detectors; i++) h1_lisafast_rates[i] = MakeTH1(dir_lisafast_rates, "I", Form("h1_lisafast_rates_det_%i", i), Form("Rate in FATIMA detector %i", i), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
    
    run->GetHttpServer()->RegisterCommand("Reset_FATIMA_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

void LisaFastOnlineSpectra::Reset_Histo() {
    c4LOG(info, "Resetting FATIMA histograms.");

    // Assuming dir is a TDirectory pointer containing histograms
    if (dir_lisafast) {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_lisafast);
        c4LOG(info, "FATIMA histograms reset.");
    } else {
        c4LOG(error, "Failed to get list of histograms from directory.");
    }
}


void LisaFastOnlineSpectra::Exec(Option_t* option)
{   
    
    auto start = std::chrono::high_resolution_clock::now();
    

    if (fHitLisaFast && fHitLisaFast->GetEntriesFast() > 0)
    {   
        event_multiplicity = 0;
        Int_t nHits = fHitLisaFast->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            LisaFastCalData* hit = (LisaFastCalData*)fHitLisaFast->At(ihit);
            if (!hit) continue;


            double slow_ToT1 = hit->Get_slow_ToT();
            double fast_ToT1 = hit->Get_fast_ToT();
            double energy1 = hit->Get_energy();
            double fast_lead1 = hit->Get_fast_lead_time();
            int64_t fast_lead_epoch = hit->Get_fast_lead_epoch();
            
            int detector_id1 = hit->Get_detector_id();

            int detector_index1 = GetDetectorIndex(detector_id1);
            if (detector_index1 >= number_detectors) {continue;} // this implies that the hit corresponds to a detector that is not specified for plotting.

            event_multiplicity ++; // count only "valid events"
            h1_lisafast_slowToT[detector_index1]->Fill(slow_ToT1);
            h1_lisafast_energy[detector_index1]->Fill(energy1);
            h1_lisafast_fastToT[detector_index1]->Fill(fast_ToT1);
            h2_lisafast_fast_v_slow[detector_index1]->Fill(fast_ToT1, slow_ToT1);
            //h1_lisafast_abs_time[detector_index1]->Fill(fast_lead_epoch+fast_lead1);
            
            h2_lisafast_energy_vs_detid->Fill(energy1, detector_id1);
            h2_lisafast_energy_uncal_vs_detid->Fill(slow_ToT1, detector_id1);
            
            if (fast_ToT1 != 0 ) h1_lisafast_hitpattern_fast->Fill(detector_id1);
            if (slow_ToT1 != 0 ) h1_lisafast_hitpattern_slow->Fill(detector_id1);
            
            // //TWO FOLD COINCIDENCES: ????
            // if (nHits >= 2 && number_reference_detectors > 0){
            //     for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++){
            //         if (ihit2 == ihit) {continue;}

            //         LisaFastCalData * hit2 = (LisaFastCalData*)fHitLisaFast->At(ihit2); // I want this to be the reference detector for easier code:
                    
            //         int detector_id2 = hit2->Get_detector_id();
            //         double slow_ToT2 = hit2->Get_slow_ToT();
            //         double fast_ToT2 = hit2->Get_fast_ToT();
            //         double energy2 = hit2->Get_energy();
            //         double fast_lead2 = hit2->Get_fast_lead_time();
            //         int64_t fast_lead_epoch2 = hit2->Get_fast_lead_epoch();

                        
            //         for (int detector_index2 = 0; detector_index2<number_reference_detectors; detector_index2++){
                    
            //         if (detector_id2 == dt_reference_detectors.at(detector_index2)) {
                    
            //         double dt = fast_lead1 - fast_lead2 + (fast_lead_epoch - fast_lead_epoch2) - lisafast_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1); 
            //         //c4LOG(info,Form("det1 = %i, det2 = %i, shift = %f",detector_id1,detector_id2,lisafast_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1)));
            //         //c4LOG(info,Form("epoch1 = %i, epoch2 = %i, depoch = %i",fast_lead_epoch,fast_lead_epoch2,fast_lead_epoch-fast_lead_epoch2));
            //         //c4LOG(info,Form("time1 = %f, time2 = %f, dtime = %f",fast_lead1,fast_lead2,fast_lead1-fast_lead2));
            //         //c4LOG(info,Form("dt = %f",dt));
                    

            //         if (dt_reference_detectors_energy_gates.at(detector_index2).first != 0 && dt_reference_detectors_energy_gates.at(detector_index2).second != 0){
            //             if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(detector_index2).second) < energygate_width) && (TMath::Abs(energy1 - dt_reference_detectors_energy_gates.at(detector_index2).first) < energygate_width)){
            //                 h1_lisafast_time_differences[detector_index2][detector_index1]->Fill(dt);
            //                 h2_lisafast_time_differences_vs_energy[detector_index2][detector_index1]->Fill(energy1,dt);
            //             }
            //         }else if(dt_reference_detectors_energy_gates.at(detector_index2).second != 0 && dt_reference_detectors_energy_gates.at(detector_index2).first == 0){
            //             if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(detector_index2).second) < energygate_width)){
            //                 h1_lisafast_time_differences[detector_index2][detector_index1]->Fill(dt);
            //                 h2_lisafast_time_differences_vs_energy[detector_index2][detector_index1]->Fill(energy1,dt);
            //             }
            //         }
            //         else{ // no gates
            //             h1_lisafast_time_differences[detector_index2][detector_index1]->Fill(dt);
            //             h2_lisafast_time_differences_vs_energy[detector_index2][detector_index1]->Fill(energy1,dt);
            //         }
            //         }
                    
            //         }
            //     }
            // }
        }


        h1_lisafast_multiplicity->Fill(event_multiplicity);


    }
    
    fNEvents += 1;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void LisaFastOnlineSpectra::FinishEvent()
{
    if (fHitLisaFast)
    {
        fHitLisaFast->Clear();
    }
}

void LisaFastOnlineSpectra::FinishTask()
{
    if(fNEvents == 0){
        c4LOG(warning, "No events processed, histograms will not be saved!");
        return;
    }
    if (fHitLisaFast)
    {
        c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    }
}

ClassImp(LisaFastOnlineSpectra)
