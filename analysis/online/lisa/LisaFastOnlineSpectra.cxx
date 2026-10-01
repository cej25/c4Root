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

    number_labr_detectors = lisafast_configuration->NLaBrDetectors();
    number_diamond_detectors = lisafast_configuration->NDiamondDetectors();

    auto const& labr_mapping = lisafast_configuration->LaBr_Mapping();
    auto const& diamond_mapping = lisafast_configuration->Diamond_Mapping();
    //auto const & det_mapping = lisafast_configuration->Mapping();

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_lisafast = new TDirectory("LISA_FAST", "LISA_FAST", "", 0);
    // mgr->Register("LISA_FAST", "LISA_FAST Directory", dir_lisafast, false); // allow other tasks to access directory.
    histograms->Add(dir_lisafast);

    dir_lisafast_LaBr = dir_lisafast->mkdir("LaBr");
    dir_lisafast_Diamond = dir_lisafast->mkdir("Diamond");
    dir_lisafast_dt_LaBr_Diamond = dir_lisafast->mkdir("dt_LaBr_Diamond");

    
    dir_lisafast_slowToT_LaBr = dir_lisafast_LaBr->mkdir("SlowToT");
    dir_lisafast_fastToT_LaBr = dir_lisafast_LaBr->mkdir("FastToT");
    dir_lisafast_hitpattern_LaBr = dir_lisafast_LaBr->mkdir("Hit Pattern");
    dir_lisafast_fast_v_slow_LaBr = dir_lisafast_LaBr->mkdir("Fast Vs. Slow");
    dir_lisafast_energy_spectra_LaBr = dir_lisafast_LaBr->mkdir("Energy Spectra");
    dir_lisafast_time_spectra_LaBr = dir_lisafast_LaBr->mkdir("Time Spectra");

    // int min_detector_id = *min_element(detectors.begin(),detectors.end()); delete this
    // int max_detector_id = *max_element(detectors.begin(), detectors.end()); // this can be read from mapping in TConfig instead, i'm just fixing like this for now.
    //number_detectors = detectors.size();


    int slowToT_bins = lisafast_configuration->slowToT_bin;
    float slowToT_min = lisafast_configuration->slowToT_min;
    float slowToT_max = lisafast_configuration->slowToT_max;

    // ::: Slow ToT (i.e raw energy):
    c_lisafast_slowToT_LaBr  = new TCanvas("c_lisafast_slowToT_LaBr","slow ToT LisaFast spectra",650,350);
    c_lisafast_slowToT_LaBr->Divide(2, (number_labr_detectors+1)/2);
    h1_lisafast_slowToT_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++)
    {
        c_lisafast_slowToT_LaBr->cd(ihist+1);
        h1_lisafast_slowToT_LaBr[ihist] = MakeTH1(dir_lisafast_slowToT_LaBr, "F", Form("h1_lisafast_slowToT_LaBr_%d",ihist), Form("LisaFast slow ToT detector %d",ihist),slowToT_bins,slowToT_min,slowToT_max, "ToT [ns]", kSpring, kBlue+2);
        h1_lisafast_slowToT_LaBr[ihist]->Draw();
    }
    c_lisafast_slowToT_LaBr->cd(0);
    dir_lisafast_slowToT_LaBr->Append(c_lisafast_slowToT_LaBr);

    //fast ToT
    c_lisafast_fastToT_LaBr  = new TCanvas("c_lisafast_fastToT_LaBr","Fast ToT LisaFast spectra",650,350);
    c_lisafast_fastToT_LaBr->Divide(2, (number_labr_detectors+1)/2);
    h1_lisafast_fastToT_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++)
    {
        c_lisafast_fastToT_LaBr->cd(ihist+1);
        h1_lisafast_fastToT_LaBr[ihist] = MakeTH1(dir_lisafast_fastToT_LaBr, "F", Form("h1_lisafast_fastToT_LaBr_%d",ihist+1),Form("LisaFast fast ToT detector %d",ihist+1),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high, "ToT [ns]", kSpring, kBlue+2);
        h1_lisafast_fastToT_LaBr[ihist]->Draw();
        
    }
    c_lisafast_fastToT_LaBr->cd(0);
    dir_lisafast_fastToT_LaBr->Add(c_lisafast_fastToT_LaBr);
    
    //energy spectrum:
    c_lisafast_energy_LaBr  = new TCanvas("c_lisafast_energy_LaBr","LisaFast energy spectra",650,350);
    c_lisafast_energy_LaBr->Divide(2, (number_labr_detectors+1)/2);
    h1_lisafast_energy_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++){
        c_lisafast_energy_LaBr->cd(ihist+1);
        h1_lisafast_energy_LaBr[ihist] = MakeTH1(dir_lisafast_energy_spectra_LaBr, "F", Form("h1_lisafast_energy_LaBr_%d",ihist+1),Form("LisaFast energy detector %d",ihist+1),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
        h1_lisafast_energy_LaBr[ihist]->Draw();
    }
    c_lisafast_energy_LaBr->cd(0);
    dir_lisafast_energy_spectra_LaBr->Append(c_lisafast_energy_LaBr);
    
    // fast vs slow:
    c_lisafast_fast_v_slow_LaBr  = new TCanvas("c_lisafast_fast_v_slow_LaBr","fast vs slow ToT LisaFast spectra",650,350);
    c_lisafast_fast_v_slow_LaBr->Divide((number_labr_detectors<5) ? number_labr_detectors : 5,(number_labr_detectors%5==0) ? (number_labr_detectors/5) : (number_labr_detectors/5 + 1));
    h2_lisafast_fast_v_slow_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++){
        c_lisafast_fast_v_slow_LaBr->cd(ihist+1);
        h2_lisafast_fast_v_slow_LaBr[ihist] = MakeTH2(dir_lisafast_fast_v_slow_LaBr, "F", Form("h2_lisafast_fast_v_slow_ToT_LaBr_%d",ihist+1),Form("LISA_FAST fast vs. slow detector %d",ihist+1),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high,fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high, "Fast ToT [ns]", "Slow ToT [ns]");
        h2_lisafast_fast_v_slow_LaBr[ihist]->Draw();        
    }
    c_lisafast_fast_v_slow_LaBr->cd(0);
    dir_lisafast_fast_v_slow_LaBr->Append(c_lisafast_fast_v_slow_LaBr);
    
    //Time spectra:
    dir_lisafast_time_spectra_LaBr->cd();
    c_lisafast_time_spectra_divided_LaBr  = new TCanvas("c_lisafast_time_spectra_divided_LaBr","LisaFast absolute time spectra",650,350);
    c_lisafast_time_spectra_divided_LaBr->Divide((number_labr_detectors<5) ? number_labr_detectors : 5,(number_labr_detectors%5==0) ? (number_labr_detectors/5) : (number_labr_detectors/5 + 1));
    h1_lisafast_abs_time_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++)
    {
        c_lisafast_time_spectra_divided_LaBr->cd(ihist+1);
        h1_lisafast_abs_time_LaBr[ihist] = MakeTH1(dir_lisafast_time_spectra_LaBr, "F", Form("h1_lisafast_abs_time_LaBr_%d",ihist+1),Form("LisaFast absolute DAQ time detector %d",ihist+1), 1e3, 0, 2.7e12, "Timestamp [ns]");

    }
    c_lisafast_time_spectra_divided_LaBr->cd(0);
    dir_lisafast_time_spectra_LaBr->Append(c_lisafast_time_spectra_divided_LaBr);

    //2D energy spectrum
    c_lisafast_energy_vs_detid_LaBr = new TCanvas("c_lisafast_energy_vs_detid_LaBr","LisaFast energy spectrum",650,350);
    h2_lisafast_energy_vs_detid_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_lisafast_energy_vs_detid_LaBr","LISA_FAST energies",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "Energy [keV]", "Detector");
    h2_lisafast_energy_vs_detid_LaBr->Draw();
    dir_lisafast_energy_spectra_LaBr->Append(c_lisafast_energy_vs_detid_LaBr);

    //2D uncalibrated energy spectrum
    c_lisafast_energy_uncal_LaBr = new TCanvas("c_lisafast_energy_uncal_LaBr","LisaFast energy spectrum",650,350);
    h2_lisafast_energy_uncal_vs_detid_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_lisafast_energy_uncal_vs_detid_LaBr","LISA_FAST uncal energy (arb.)",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "Energy [a.u.]", "Detector");
    h2_lisafast_energy_uncal_vs_detid_LaBr->Draw();
    dir_lisafast_energy_spectra_LaBr->Append(c_lisafast_energy_uncal_LaBr);

    // Hit patterns:
    c_lisafast_hitpatterns_LaBr  = new TCanvas("c_lisafast_hitpatterns_LaBr","LisaFast hit patterns",650,350);
    c_lisafast_hitpatterns_LaBr->Divide(2,1);

    c_lisafast_hitpatterns_LaBr->cd(1);
    h1_lisafast_hitpattern_slow_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_hitpattern_slow_LaBr","LISA_FAST slow hit patterns",number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "Detector", kRed-3, kBlack);
    h1_lisafast_hitpattern_slow_LaBr->Draw();
    
    c_lisafast_hitpatterns_LaBr->cd(2);
    h1_lisafast_hitpattern_fast_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_hitpattern_fast_LaBr","LISA_FAST fast hit patterns",number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "Detector", kRed-3, kBlack);
    h1_lisafast_hitpattern_fast_LaBr->Draw();
    c_lisafast_hitpatterns_LaBr->cd(0);
    dir_lisafast_hitpattern_LaBr->Append(c_lisafast_hitpatterns_LaBr);
    
    c_lisafast_event_multiplicity  = new TCanvas("c_lisafast_event_multiplicity","LisaFast event multiplicities",650,350);
    
    h1_lisafast_multiplicity = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_multiplicity","LISA_FAST event multiplicity",20,0,20, "Event Multiplicity", kRed-3, kBlack);
    h1_lisafast_multiplicity->Draw();
    c_lisafast_event_multiplicity->cd(0);
    dir_lisafast_hitpattern_LaBr->Append(c_lisafast_event_multiplicity);

    //time differences!
    number_reference_detectors = (int) dt_reference_detectors.size();
    dir_lisafast_time_differences_LaBr.resize(number_reference_detectors);

    h1_lisafast_time_differences_LaBr.resize(number_reference_detectors);
    h2_lisafast_time_differences_vs_energy_LaBr.resize(number_reference_detectors);
    for (int ihist = 0; ihist < number_reference_detectors; ihist++)
    {
        std::stringstream name;
        name << "time_differences_rel_" << dt_reference_detectors.at(ihist) << "_energy_gate_" << (int)dt_reference_detectors_energy_gates.at(ihist).first << "_" << (int)dt_reference_detectors_energy_gates.at(ihist).second;
        dir_lisafast_time_differences_LaBr[ihist] = dir_lisafast->mkdir(name.str().c_str());
        dir_lisafast_time_differences_LaBr[ihist]->cd();
    
        c_lisafast_time_differences_LaBr = new TCanvas(Form("c_lisafast_time_differences_rel_det_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"lisafast relative time differences",650,350);
        c_lisafast_time_differences_LaBr->Divide((number_labr_detectors<5) ? number_labr_detectors : 5,(number_labr_detectors%5==0) ? (number_labr_detectors/5) : (number_labr_detectors/5 + 1));
        //h1_lisafast_time_differences[ihist] = new TH1F*[number_detectors];
        h1_lisafast_time_differences_LaBr[ihist].resize(number_labr_detectors);

        for (int detid_idx = 0; detid_idx < number_labr_detectors; detid_idx++)
        {
            c_lisafast_time_differences_LaBr->cd(detid_idx+1);
            
            h1_lisafast_time_differences_LaBr[ihist][detid_idx] = MakeTH1(dir_lisafast_time_differences_LaBr[ihist], "F", Form("h1_lisafast_rel_time_det_%d_to_det_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist),detid_idx+1,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("LISA_FAST dT t(%d) - t(%d) gated %d and %d",detid_idx+1,dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high, Form("dT t(%d) - t(%d) [ns]",detid_idx+1,dt_reference_detectors.at(ihist)), kMagenta, kBlue+2);
            
        }
        c_lisafast_time_differences_LaBr->cd(0);
        dir_lisafast_time_differences_LaBr[ihist]->Append(c_lisafast_time_differences_LaBr);

        c_lisafast_time_differences_vs_energy_LaBr  = new TCanvas(Form("c_lisafast_time_differences_rel_det_%d_vs_energy_energy_gate_%d_%d",dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"lisafast relative time differences vs energy",650,350);
        c_lisafast_time_differences_vs_energy_LaBr->Divide((number_labr_detectors<5) ? number_labr_detectors : 5,(number_labr_detectors%5==0) ? (number_labr_detectors/5) : (number_labr_detectors/5 + 1));
        //h2_lisafast_time_differences_vs_energy[ihist] = new TH2F*[number_labr_detectors];
        h2_lisafast_time_differences_vs_energy_LaBr[ihist].resize(number_labr_detectors);

        for (int detid_idx = 0; detid_idx < number_labr_detectors; detid_idx++)
        {
            c_lisafast_time_differences_vs_energy_LaBr->cd(detid_idx+1);
            h2_lisafast_time_differences_vs_energy_LaBr[ihist][detid_idx] = MakeTH2(dir_lisafast_time_differences_LaBr[ihist], "F", Form("h2_lisafast_rel_time_det_%d_to_det_%d_vs_energy_energy_gate_%d_%d",detid_idx+1,dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("LISA_FAST dT t(%d) - t(%d) vs Energy, energy gate %d, %d",detid_idx+1,dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high, Form("Energy (Detector %d) [keV]",detid_idx+1), Form("dT t(%d) - t(%d) [ns]",detid_idx+1,dt_reference_detectors.at(ihist)));
            // h2_lisafast_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_lisafast_rel_time_det_%d_to_det_%d_vs_energy_energy_gate_%d_%d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("lisafast delta time t(%d) - t(%d) vs energy, energy gate %d, %d",detectors.at(detid_idx),dt_reference_detectors.at(ihist),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high); 
            // h2_lisafast_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%d) - t(%d) (ns)",detectors.at(detid_idx),dt_reference_detectors.at(ihist)));
            // h2_lisafast_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %d (keV)",detectors.at(detid_idx)));
            h2_lisafast_time_differences_vs_energy_LaBr[ihist][detid_idx]->Draw();
            
        }
        c_lisafast_time_differences_vs_energy_LaBr->cd(0);
        dir_lisafast_time_differences_LaBr[ihist]->Append(c_lisafast_time_differences_vs_energy_LaBr);
    }

    dir_lisafast->cd();

      
    run->GetHttpServer()->RegisterCommand("Reset_LISA_Fast_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

void LisaFastOnlineSpectra::Reset_Histo() {
    c4LOG(info, "Resetting LISA Fast histograms.");

    // Assuming dir is a TDirectory pointer containing histograms
    if (dir_lisafast) {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_lisafast);
        c4LOG(info, "LISA Fast histograms reset.");
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
            double run_time = hit->Get_run_time();

            c4LOG(info, "run time: " << run_time << " ns");


            
            int detector_id1 = hit->Get_detector_id();

            //int detector_index1 = GetDetectorIndex(detector_id1);
            //if (detector_index1 >= number_detectors) {continue;} // this implies that the hit corresponds to a detector that is not specified for plotting.

            event_multiplicity ++; // count only "valid events"
            h1_lisafast_slowToT_LaBr[detector_id1]->Fill(slow_ToT1); // all these were indexed by detector_index1, some horrible logic thing may need fixing down the road
            h1_lisafast_energy_LaBr[detector_id1]->Fill(energy1);
            h1_lisafast_fastToT_LaBr[detector_id1]->Fill(fast_ToT1);
            h2_lisafast_fast_v_slow_LaBr[detector_id1]->Fill(fast_ToT1, slow_ToT1);
            h1_lisafast_abs_time_LaBr[detector_id1]->Fill(fast_lead_epoch+fast_lead1);
            
            h2_lisafast_energy_vs_detid_LaBr->Fill(energy1, detector_id1);
            h2_lisafast_energy_uncal_vs_detid_LaBr->Fill(slow_ToT1, detector_id1);
            
            if (fast_ToT1 != 0 ) h1_lisafast_hitpattern_fast_LaBr->Fill(detector_id1);
            if (slow_ToT1 != 0 ) h1_lisafast_hitpattern_slow_LaBr->Fill(detector_id1);
            
            //TWO FOLD COINCIDENCES: ????
            if (nHits >= 2 && number_reference_detectors > 0){
                for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++){
                    if (ihit2 == ihit) {continue;}

                    LisaFastCalData * hit2 = (LisaFastCalData*)fHitLisaFast->At(ihit2); // I want this to be the reference detector for easier code:
                    
                    int detector_id2 = hit2->Get_detector_id();
                    double slow_ToT2 = hit2->Get_slow_ToT();
                    double fast_ToT2 = hit2->Get_fast_ToT();
                    double energy2 = hit2->Get_energy();
                    double fast_lead2 = hit2->Get_fast_lead_time();
                    int64_t fast_lead_epoch2 = hit2->Get_fast_lead_epoch();

                        
                    for (int detector_index2 = 0; detector_index2<number_reference_detectors; detector_index2++){
                    
                    if (detector_id2 == dt_reference_detectors.at(detector_index2)) {
                    
                    double dt = fast_lead1 - fast_lead2;//+ (fast_lead_epoch - fast_lead_epoch2) - lisafast_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1); 
                    //c4LOG(info,Form("det1 = %i, det2 = %i, shift = %f",detector_id1,detector_id2,lisafast_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1)));
                    //c4LOG(info,Form("epoch1 = %i, epoch2 = %i, depoch = %i",fast_lead_epoch,fast_lead_epoch2,fast_lead_epoch-fast_lead_epoch2));
                    //c4LOG(info,Form("time1 = %f, time2 = %f, dtime = %f",fast_lead1,fast_lead2,fast_lead1-fast_lead2));
                    //c4LOG(info,Form("dt = %f",dt));
                    

                    if (dt_reference_detectors_energy_gates.at(detector_index2).first != 0 && dt_reference_detectors_energy_gates.at(detector_index2).second != 0){
                        if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(detector_index2).second) < energygate_width) && (TMath::Abs(energy1 - dt_reference_detectors_energy_gates.at(detector_index2).first) < energygate_width)){
                            h1_lisafast_time_differences_LaBr[detector_index2][detector_id1]->Fill(dt);
                            h2_lisafast_time_differences_vs_energy_LaBr[detector_index2][detector_id1]->Fill(energy1,dt);
                        }
                    }else if(dt_reference_detectors_energy_gates.at(detector_index2).second != 0 && dt_reference_detectors_energy_gates.at(detector_index2).first == 0){
                        if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(detector_index2).second) < energygate_width)){
                            h1_lisafast_time_differences_LaBr[detector_index2][detector_id1]->Fill(dt);
                            h2_lisafast_time_differences_vs_energy_LaBr[detector_index2][detector_id1]->Fill(energy1,dt);
                        }
                    }
                    else{ // no gates
                        h1_lisafast_time_differences_LaBr[detector_index2][detector_id1]->Fill(dt);
                        h2_lisafast_time_differences_vs_energy_LaBr[detector_index2][detector_id1]->Fill(energy1,dt);
                    }
                    }
                    
                    }
                }
            }


            // ::: cross event coincidences ::: //

            // erase hits outside window
            for (auto hit_coin = coin_hits.begin(); hit_coin != coin_hits.end();)
            {
                if ((run_time - hit_coin->Get_run_time()) > coin_window_ns)
                {
                    coin_hits.erase(hit_coin);
                } 
                else hit_coin++;
            }
            
            for (auto hit_coin = coin_hits.begin(); hit_coin != coin_hits.end(); hit_coin++)
            {
                double dt = run_time - hit_coin->Get_run_time();
                double energy2 = hit_coin->Get_energy();
                int detector_id2 = hit_coin->Get_detector_id();

                std::cout << "making coincidences" << std::endl;
            }

            coin_hits.push_back(*hit);


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
