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
 *                        E.G. Gandolfo, C.E. Jones                          *
 *                                09.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "LisaFastNearlineSpectra.h"
#include "EventHeader.h"
#include "LisaFastCalData.h"

#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>
#include <sstream>

LisaFastNearlineSpectra::LisaFastNearlineSpectra() : LisaFastNearlineSpectra("LisaFastNearlineSpectra")
{
    lisafast_configuration = TLisaFastConfiguration::GetInstance();
}

LisaFastNearlineSpectra::LisaFastNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitLisaFast(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    lisafast_configuration = TLisaFastConfiguration::GetInstance();
}

LisaFastNearlineSpectra::~LisaFastNearlineSpectra()
{
    c4LOG(info, "");
    if (fHitLisaFast)
        delete fHitLisaFast;
}

InitStatus LisaFastNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitLisaFast = (TClonesArray*)mgr->GetObject("LisaFastCalData");
    c4LOG_IF(fatal, !fHitLisaFast, "Branch LisaFastCalData not found!");

    number_labr_detectors = lisafast_configuration->NLaBrDetectors();
    number_diamond_detectors = lisafast_configuration->NDiamondDetectors();

    auto const& labr_mapping = lisafast_configuration->LaBr_Mapping();
    auto const& diamond_mapping = lisafast_configuration->Diamond_Mapping();
    //auto const & det_mapping = lisafast_configuration->Mapping();

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisafast = gDirectory->mkdir("LISA_FAST");
    gDirectory->cd("LISA_FAST");

    dir_lisafast_LaBr = dir_lisafast->mkdir("LaBr");
    dir_lisafast_Diamond = dir_lisafast->mkdir("Diamond");
    dir_lisafast_dt_LaBr_Diamond = dir_lisafast->mkdir("dt_LaBr_Diamond");
    
    dir_lisafast_slowToT_LaBr = dir_lisafast_LaBr->mkdir("SlowToT");
    dir_lisafast_fastToT_LaBr = dir_lisafast_LaBr->mkdir("FastToT");
    dir_lisafast_hitpattern_LaBr = dir_lisafast_LaBr->mkdir("Hit_Pattern");
    dir_lisafast_fast_v_slow_LaBr = dir_lisafast_LaBr->mkdir("Fast_Vs_Slow");
    dir_lisafast_energy_spectra_LaBr = dir_lisafast_LaBr->mkdir("Energy_Spectra");
    dir_lisafast_time_spectra_LaBr = dir_lisafast_LaBr->mkdir("Time_Spectra");
    dir_lisafast_dTw_coin_LaBr = dir_lisafast_LaBr->mkdir("dT_window_Coincidences");

    // ===:::::::: LABR :::::::::::===

    // ::: Slow ToT (i.e. raw energy):
    h1_lisafast_slowToT_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++)
    {
        h1_lisafast_slowToT_LaBr[ihist] = MakeTH1(dir_lisafast_slowToT_LaBr, "F", Form("h1_lisafast_slowToT_LaBr_%d",ihist), Form("LaBr slow ToT detector %d",ihist),lisafast_configuration->slowToT_bin,lisafast_configuration->slowToT_min,lisafast_configuration->slowToT_max, "ToT [ns]", kSpring, kBlue+2);
    }

    // ::: Fast ToT
    h1_lisafast_fastToT_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++)
    {
        h1_lisafast_fastToT_LaBr[ihist] = MakeTH1(dir_lisafast_fastToT_LaBr, "F", Form("h1_lisafast_fastToT_LaBr_%d",ihist+1),Form("LaBr fast ToT detector %d",ihist+1),lisafast_configuration->fastToT_bin,lisafast_configuration->fastToT_min,lisafast_configuration->fastToT_max, "ToT [ns]", kSpring, kBlue+2);
    }

    // ::: Energy spectrum (calibrated slowToT):::
    h1_lisafast_energy_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++){
        h1_lisafast_energy_LaBr[ihist] = MakeTH1(dir_lisafast_energy_spectra_LaBr, "F", Form("h1_lisafast_energy_LaBr_%d",ihist+1),Form("LisaFast energy detector %d",ihist+1),lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max, "Energy [keV]", kOrange-3, kBlue+2);
    }
    h2_E1_vs_E2_all_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_E1_vs_E2_all_LaBr","LaBr all coincidence energy correlations",lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max,lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max, "Energy 1 [keV]", "Energy 2 [keV]");

    // ::: Fast vs Slow:
    h2_lisafast_fast_v_slow_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++){
        h2_lisafast_fast_v_slow_LaBr[ihist] = MakeTH2(dir_lisafast_fast_v_slow_LaBr, "F", Form("h2_lisafast_fast_v_slow_ToT_LaBr_%d",ihist+1),Form("LISA_FAST fast vs. slow detector %d",ihist+1),lisafast_configuration->slowToT_bin,lisafast_configuration->slowToT_min,lisafast_configuration->slowToT_max, lisafast_configuration->fastToT_bin,lisafast_configuration->fastToT_min,lisafast_configuration->fastToT_max, "Slow ToT [ns]","Fast ToT [ns]");
    }

    // ::: Time spectra:
    dir_lisafast_time_spectra_LaBr->cd();
    h1_lisafast_abs_time_LaBr.resize(number_labr_detectors);
    for (int ihist = 0; ihist < number_labr_detectors; ihist++)
    {
        h1_lisafast_abs_time_LaBr[ihist] = MakeTH1(dir_lisafast_time_spectra_LaBr, "F", Form("h1_lisafast_abs_time_LaBr_%d",ihist+1),Form("LaBr absolute DAQ time detector %d",ihist+1), 1e3, 0, 2.7e12, "Timestamp [ns]");
    }

    // ::: 2D energy spectrum
    h2_lisafast_energy_vs_detid_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_lisafast_energy_vs_detid_LaBr",
        "LaBr energies vs ID", number_labr_detectors, 0.5, number_labr_detectors+0.5,
        lisafast_configuration->energy_bin,
        lisafast_configuration->energy_min,
        lisafast_configuration->energy_max,
        "LaBr", "Energy [keV]");

    // ::: 2D uncalibrated energy spectrum
    h2_lisafast_energy_uncal_vs_detid_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_lisafast_energy_uncal_vs_detid_LaBr",
        "LaBr raw energy vs ID", number_labr_detectors,0.5,number_labr_detectors+0.5, 
        lisafast_configuration->slowToT_bin,
        lisafast_configuration->slowToT_min,
        lisafast_configuration->slowToT_max,
        "LaBr","Energy [a.u.]");

    //:::  Hit patterns
    // Fast hit pattern
    h1_lisafast_hitpattern_slow_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_hitpattern_slow_LaBr","LaBr slow hit patterns",number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "LaBr", kRed-3, kBlack);
    
    // Slow hit pattern
    h1_lisafast_hitpattern_fast_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_hitpattern_fast_LaBr","LaBr fast hit patterns",number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "LaBr", kRed-3, kBlack);

    // ::: Multiplicity    
    h1_lisafast_multiplicity = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_multiplicity","LaBr event multiplicity",20,0,20, "Event Multiplicity", kRed-3, kBlack);

    // ::: Time differences - event based

    // Ungated dT
    dir_lisafast_dT_event_coin_LaBr = dir_lisafast_LaBr->mkdir("dT_event_Coincidences");
    dir_lisafast_dT_event_coin_LaBr->cd();

    c4LOG(info," number of ref detector " << dt_reference_labr);
    h1_lisafast_deltaT_LaBr.resize(number_labr_detectors);

    for (int detid_idx = 0;detid_idx < number_labr_detectors;detid_idx++)
    {
        h1_lisafast_deltaT_LaBr[detid_idx] =
            MakeTH1(dir_lisafast_dT_event_coin_LaBr,"F",
                Form("h1_lisafast_dT_%d_to_%d_LaBr",detid_idx + 1, dt_reference_labr),
                Form("LaBr dT t(%d) - t(%d)", detid_idx + 1, dt_reference_labr),
                lisafast_configuration->dt_bin,
                lisafast_configuration->dt_min,
                lisafast_configuration->dt_max,
                Form("dT t(%d) - t(%d) [ns]", detid_idx + 1, dt_reference_labr),
                kMagenta,kBlue + 2);
    }

    // Ungated dT vs energy
    h2_lisafast_deltaT_vs_energy_LaBr.resize(number_labr_detectors);
    for (int detid_idx = 0;detid_idx < number_labr_detectors;detid_idx++)
    {
        h2_lisafast_deltaT_vs_energy_LaBr[detid_idx] =
            MakeTH2(dir_lisafast_dT_event_coin_LaBr,"F",
                Form("h2_lisafast_deltaT_det_%d_to_refdet_%d_vs_en_LaBr", detid_idx + 1, dt_reference_labr),
                Form("LaBr dT t(%d) - t(%d) vs Energy", detid_idx + 1, dt_reference_labr),
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                lisafast_configuration->dt_bin,
                lisafast_configuration->dt_min,
                lisafast_configuration->dt_max,
                Form("Energy (LaBr ID %d) [keV]",detid_idx + 1),
                Form("dT t(%d) - t(%d) [ns]",detid_idx + 1,dt_reference_labr));
    }

    // ::: Energy gated event-based coincidences
    dir_lisafast_dT_event_Gates_LaBr = dir_lisafast_dT_event_coin_LaBr->mkdir("dT_event_Gates");
    h1_lisafast_deltaT_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
    h2_lisafast_deltaT_vs_energy_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
    
    // ::: Energy gated on dT window coincidences
    dir_lisafast_dTw_Gates_LaBr = dir_lisafast_dTw_coin_LaBr->mkdir("dTw_event_Gates_LaBr");
    h1_lisafast_dTw_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
    h2_lisafast_dTw_vs_energy_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());

    // Loop over gates
    for (size_t igate = 0; igate < dt_reference_detectors_energy_gates.size(); igate++)
    {
        double gate_other = dt_reference_detectors_energy_gates[igate].first;
        double gate_ref = dt_reference_detectors_energy_gates[igate].second;

        std::stringstream name;
        std::stringstream name_dTw;

        name << "deltaT_rel_"<< dt_reference_labr<< "_energy_gate_"
        << (int)gate_other<< "_"<< (int)gate_ref;

        name_dTw << "dTw_rel_" << dt_reference_labr
        << "_energy_gate_"<< (int)gate_other << "_"<< (int)gate_ref;

        TDirectory* dir_gate = dir_lisafast_dT_event_Gates_LaBr->mkdir(name.str().c_str());
        TDirectory* dir_dTw_gate = dir_lisafast_dTw_Gates_LaBr->mkdir(name_dTw.str().c_str());
        
        dir_gate->cd();
        h1_lisafast_deltaT_LaBr_gated[igate].resize(number_labr_detectors);
        h2_lisafast_deltaT_vs_energy_LaBr_gated[igate].resize(number_labr_detectors);       
        
        dir_dTw_gate->cd();
        h1_lisafast_dTw_LaBr_gated[igate].resize(number_labr_detectors);
        h2_lisafast_dTw_vs_energy_LaBr_gated[igate].resize(number_labr_detectors);

        for (int detid_idx = 0;detid_idx < number_labr_detectors;detid_idx++)
        {
            int detid = detid_idx + 1;

            // ----------------------------------------------------
            // Gated dT spectrum
            // ----------------------------------------------------

            h1_lisafast_deltaT_LaBr_gated[igate][detid_idx] =
                MakeTH1(dir_gate,"F",
                    Form("h1_lisafast_dT_%d_to_%d_energy_gate_%d_%d_LaBr",
                        detid, dt_reference_labr, (int)gate_other, (int)gate_ref),
                    Form("LaBr dT t(%d) - t(%d) gated %d and %d(ref)",
                        detid, dt_reference_labr, (int)gate_other,(int)gate_ref),
                    lisafast_configuration->dt_bin,
                    lisafast_configuration->dt_min,
                    lisafast_configuration->dt_max,
                    Form("dT t(%d) - t(%d) [ns]",
                        detid,dt_reference_labr),kMagenta,kBlue + 2);

            // ----------------------------------------------------
            // Gated dT vs energy
            // ----------------------------------------------------

            h2_lisafast_deltaT_vs_energy_LaBr_gated[igate][detid_idx] =
                MakeTH2(dir_gate,"F",
                    Form("h2_lisafast_deltaT_det_%d_to_refdet_%d_vs_en_energy_gate_%d_%d_LaBr",
                        detid,dt_reference_labr,(int)gate_other,(int)gate_ref),
                    Form("LaBr dT t(%d) - t(%d) vs Energy, energy gate %d, %d",
                        detid,dt_reference_labr,(int)gate_other,(int)gate_ref),
                        lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max,
                    lisafast_configuration->dt_bin,lisafast_configuration->dt_min,lisafast_configuration->dt_max,
                    Form("Energy (LaBr ID %d) [keV]",detid),
                    Form("dT t(%d) - t(%d) [ns]",detid,dt_reference_labr));
            // ----------------------------------------------------
            // Gated dTw spectrum
            // ----------------------------------------------------

            h1_lisafast_dTw_LaBr_gated[igate][detid_idx] =
                MakeTH1(dir_dTw_gate,"F",
                    Form("h1_lisafast_dTw_%d_to_%d_energy_gate_%d_%d_LaBr",
                        detid,dt_reference_labr,
                        (int)gate_other,(int)gate_ref),
                    Form("LaBr dTw t(%d) - t(%d) gated %d and %d(ref)",
                        detid,dt_reference_labr,
                        (int)gate_other,(int)gate_ref),
                    lisafast_configuration->dt_bin,
                    lisafast_configuration->dt_min,
                    lisafast_configuration->dt_max,
                    Form("dTw t(%d) - t(%d) [ns]",
                        detid,dt_reference_labr),
                    kMagenta,kBlue + 2);
            // ----------------------------------------------------
            // Gated dTw vs energy
            // ----------------------------------------------------

            h2_lisafast_dTw_vs_energy_LaBr_gated[igate][detid_idx] =
                MakeTH2(dir_dTw_gate,"F",
                    Form("h2_lisafast_dTw_det_%d_to_refdet_%d_vs_en_energy_gate_%d_%d_LaBr",
                        detid,dt_reference_labr,
                        (int)gate_other,(int)gate_ref),
                    Form("LaBr dTw t(%d) - t(%d) vs Energy, energy gate %d, %d",
                        detid,dt_reference_labr,
                        (int)gate_other,(int)gate_ref),
                    lisafast_configuration->energy_bin,
                    lisafast_configuration->energy_min,
                    lisafast_configuration->energy_max,
                    lisafast_configuration->dt_bin,
                    lisafast_configuration->dt_min,
                    lisafast_configuration->dt_max,
                    Form("Energy (LaBr ID %d) [keV]", detid),
                    Form("dTw t(%d) - t(%d) [ns]",
                        detid,dt_reference_labr));   
        }

    }
    
    h1_lisafast_dTw_coin_LaBr = MakeTH1(dir_lisafast_dTw_coin_LaBr, "F", "h1_lisafast_dTw_coin_labr","LaBr dTwindow coincidence",lisafast_configuration->dt_bin,lisafast_configuration->dt_min,lisafast_configuration->dt_max, "dT [ns]", kMagenta,kBlue + 2);
    h2_lisafast_dTw_vs_energy_coin_LaBr =
        MakeTH2(dir_lisafast_dTw_coin_LaBr,"F","h2_lisafast_dTw_vs_energy_coin_LaBr","LaBr dTw t(other) - t(ref) vs Energy",
            lisafast_configuration->energy_bin,
            lisafast_configuration->energy_min,
            lisafast_configuration->energy_max,
            lisafast_configuration->dt_bin,
            lisafast_configuration->dt_min,
            lisafast_configuration->dt_max,
            "Energy (LaBr other) [keV]","dTw [ns]");
    
    h2_E1_vs_E2_dTw_coin_all_LaBr = MakeTH2(dir_lisafast_dTw_coin_LaBr, "F", "h2_E1_vs_E2_dTw_coin_all_labr","LaBr dTWindow coincidence energy",lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max,lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max, "Energy 1 [keV]", "Energy 2 [keV]");
    
    h2_lisafast_dTw_vs_energy_coin_LaBr->Draw("COLZ");


    dir_lisafast->cd();
    gDirectory = tmp;
    
    return kSUCCESS;
    
}


void LisaFastNearlineSpectra::Exec(Option_t* option)
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

            //c4LOG(info, "Slow down");
            double slow_ToT1 = hit->Get_slow_ToT();
            double fast_ToT1 = hit->Get_fast_ToT();
            double energy1 = hit->Get_energy();
            double fast_lead1 = hit->Get_fast_lead_time();
            int64_t fast_lead_epoch = hit->Get_fast_lead_epoch();
            double run_time = hit->Get_run_time();

            int detector_id1 = hit->Get_detector_id();

            event_multiplicity ++;

            // ::: Slow/Fast Time
            h1_lisafast_slowToT_LaBr[detector_id1-1]->Fill(slow_ToT1); // all these were indexed by detector_index1, some horrible logic thing may need fixing down the road
            h1_lisafast_fastToT_LaBr[detector_id1-1]->Fill(fast_ToT1);
            h2_lisafast_fast_v_slow_LaBr[detector_id1-1]->Fill(slow_ToT1,fast_ToT1);        
    
            // ::: Abs time
            h1_lisafast_abs_time_LaBr[detector_id1-1]->Fill(fast_lead_epoch+fast_lead1);

            // ::: Energy
            h1_lisafast_energy_LaBr[detector_id1-1]->Fill(energy1);

            //c4LOG(info," detector_id1 = " << detector_id1);
            h2_lisafast_energy_vs_detid_LaBr->Fill(detector_id1-0.5, energy1);
            h2_lisafast_energy_uncal_vs_detid_LaBr->Fill(detector_id1-0.5, slow_ToT1);
            
            // ::: Hit Pattern
            if (fast_ToT1 != 0 ) h1_lisafast_hitpattern_fast_LaBr->Fill(detector_id1);
            if (slow_ToT1 != 0 ) h1_lisafast_hitpattern_slow_LaBr->Fill(detector_id1);
            
            // ::: Event-based coincidences: 
            // If multiple hits in one event -> those hits are in coincidence

            if (nHits >= 2)
            {
                for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++)
                {
                    if (ihit2 == ihit) {continue;}

                    LisaFastCalData* hit2 = (LisaFastCalData*)fHitLisaFast->At(ihit2); // I want this to be the reference detector for easier code:
                    
                    int detector_id2 = hit2->Get_detector_id();
                    double slow_ToT2 = hit2->Get_slow_ToT();
                    double fast_ToT2 = hit2->Get_fast_ToT();
                    double energy2 = hit2->Get_energy();
                    double fast_lead2 = hit2->Get_fast_lead_time();
                    int64_t fast_lead_epoch2 = hit2->Get_fast_lead_epoch();

                    double dt = fast_lead1 - fast_lead2;//+ (fast_lead_epoch - fast_lead_epoch2) - lisafast_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1); 

                    h2_E1_vs_E2_all_LaBr->Fill(energy1, energy2);
                    //h3_E1_vs_E2_vs_dt_all_LaBr->Fill(energy1, energy2, dt);

                    if (dt_reference_labr > 0 && detector_id2 == dt_reference_labr)
                    {
                        
                        // Non-gated
                        h1_lisafast_deltaT_LaBr[detector_id1 - 1]->Fill(dt);
                        h2_lisafast_deltaT_vs_energy_LaBr[detector_id1 - 1]->Fill(energy1, dt);
                        
                        // Gated
                        for (size_t igate = 0;
                            igate < dt_reference_detectors_energy_gates.size();
                            ++igate)
                        {
                            double gate_other = dt_reference_detectors_energy_gates[igate].first;
                            double gate_ref = dt_reference_detectors_energy_gates[igate].second;
                            bool gate_passed = false;

                            // Gate on both detectors
                            if (gate_other != 0 &&
                                gate_ref != 0)
                            {
                                gate_passed =
                                    (TMath::Abs(energy1 - gate_other) < lisafast_configuration->en_gate_width)
                                    &&
                                    (TMath::Abs(energy2 - gate_ref) < lisafast_configuration->en_gate_width);
                            }

                            // Gate only on reference detector
                            else if (gate_other == 0 &&
                                    gate_ref != 0)
                            {
                                gate_passed =(TMath::Abs(energy2 - gate_ref) < lisafast_configuration->en_gate_width);
                            }

                            if (gate_passed)
                            {
                                h1_lisafast_deltaT_LaBr_gated[igate][detector_id1 - 1]->Fill(dt);
                                h2_lisafast_deltaT_vs_energy_LaBr_gated[igate][detector_id1 - 1]->Fill(energy1, dt);
                            }
                        }
                        
                        //c4LOG(info, "Slow down");
                    }

                }
            }

            // ::: Cross-event coincidences :::
            // If the dT between hits is smaller than the given dT window,
            // AND one of the two detectors is the reference detector,
            // the hits are considered to be in coincidence.
            //
            // Convention:
            //     dt = t_other - t_reference
            for (auto hit_coin = coin_hits.begin(); hit_coin != coin_hits.end(); )
            {
                // erase hits outside of dT window
                if ((run_time - hit_coin->Get_run_time()) > coin_window_ns)
                {
                    hit_coin = coin_hits.erase(hit_coin);
                    continue;
                }

                int detector_id_coin = hit_coin->Get_detector_id();
                double time_coin = hit_coin->Get_run_time();
                double energy_coin = hit_coin->Get_energy();

                double energy_other;
                double energy_ref;
                int detector_id_other;

                bool current_is_reference =
                    (detector_id1 == dt_reference_labr);

                bool previous_is_reference =
                    (detector_id_coin == dt_reference_labr);

                // Only consider coincidences if ref detector is in
                if (current_is_reference || previous_is_reference)
                {
                    double dt = 0.0;

                    if (current_is_reference)
                    {
                        // Current hit is the reference
                        // dt = t_other - t_reference
                        dt = time_coin - run_time;
                        energy_ref = energy1;
                        energy_other = energy_coin;
                        detector_id_other = detector_id_coin;
                    }
                    else
                    {
                        // Previous hit is the reference
                        // dt = t_other - t_reference
                        dt = run_time - time_coin;
                        energy_other = energy1;
                        energy_ref = energy_coin;
                        detector_id_other = detector_id1;
                    }

                    if (std::abs(dt) < coin_window_ns)
                    {
                        h1_lisafast_dTw_coin_LaBr->Fill(dt);
                        h2_lisafast_dTw_vs_energy_coin_LaBr->Fill(energy_other, dt);
                        
                        h2_E1_vs_E2_dTw_coin_all_LaBr->Fill(energy1,hit_coin->Get_energy());

                        for (size_t igate = 0;igate < dt_reference_detectors_energy_gates.size();++igate)
                        {
                            double gate_other =dt_reference_detectors_energy_gates[igate].first;
                            double gate_ref =dt_reference_detectors_energy_gates[igate].second;
                            bool gate_passed = false;

                            // Gate on both detectors
                            if (gate_other != 0 && gate_ref != 0)
                            {
                                gate_passed =
                                    (TMath::Abs(energy_other - gate_other)
                                    < lisafast_configuration->en_gate_width)
                                    &&
                                    (TMath::Abs(energy_ref - gate_ref)
                                    < lisafast_configuration->en_gate_width);
                            }
                            // Gate only on reference detector
                            else if (gate_other == 0 && gate_ref != 0)
                            {
                                gate_passed =(TMath::Abs(energy_ref - gate_ref)< lisafast_configuration->en_gate_width);
                            }
                            
                            if (gate_passed)
                            {
                                h1_lisafast_dTw_LaBr_gated[igate][detector_id_other - 1]->Fill(dt);
                                h2_lisafast_dTw_vs_energy_LaBr_gated[igate][detector_id_other - 1]->Fill(energy_other, dt);
                            }
                        }

                    }
                }

                ++hit_coin;
            }
            // Store current hit for future cross-event coincidences
            coin_hits.push_back(*hit);

        }
        
        h1_lisafast_multiplicity->Fill(event_multiplicity);

    }
    
    fNEvents += 1;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void LisaFastNearlineSpectra::FinishEvent()
{
    if (fHitLisaFast)
    {
        fHitLisaFast->Clear();
    }
}

void LisaFastNearlineSpectra::FinishTask()
{
    if(fNEvents == 0){
        c4LOG(warning, "No events processed, histograms will not be saved!");
        return;
    }
   
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisafast->Write();
    gDirectory = tmp;

    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(LisaFastNearlineSpectra)
