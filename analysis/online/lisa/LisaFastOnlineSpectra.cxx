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
#include <algorithm>
#include <set>
#include <tuple>
#include <cmath>

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

    int max_layer = lisafast_configuration->NDiamondLayers();
    int max_x = lisafast_configuration->XMax();
    int max_y = lisafast_configuration->YMax();

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
    dir_lisafast_hitpattern_LaBr = dir_lisafast_LaBr->mkdir("Hit_Pattern");
    dir_lisafast_fast_v_slow_LaBr = dir_lisafast_LaBr->mkdir("Fast_Vs_Slow");
    dir_lisafast_energy_spectra_LaBr = dir_lisafast_LaBr->mkdir("Energy_Spectra");
    dir_lisafast_time_spectra_LaBr = dir_lisafast_LaBr->mkdir("Time_Spectra");
    dir_lisafast_dTw_coin_LaBr = dir_lisafast_LaBr->mkdir("dT_window_Coincidences");

    // === Diamond directories ===
    dir_lisafast_slowToT_Diamond = dir_lisafast_Diamond->mkdir("SlowToT");
    dir_lisafast_fastToT_Diamond = dir_lisafast_Diamond->mkdir("FastToT");
    dir_lisafast_hitpattern_Diamond = dir_lisafast_Diamond->mkdir("Hit_Pattern");
    dir_lisafast_fast_v_slow_Diamond = dir_lisafast_Diamond->mkdir("Fast_Vs_Slow");
    dir_lisafast_energy_spectra_Diamond = dir_lisafast_Diamond->mkdir("Energy_Spectra");
    dir_lisafast_time_spectra_Diamond = dir_lisafast_Diamond->mkdir("Time_Spectra");

    // ================================================
    // Diamond-Diamond coincidences

    dir_lisafast_Diamond_Coincidences =dir_lisafast_Diamond->mkdir("Coincidences");
    dir_lisafast_Diamond_dT_event = dir_lisafast_Diamond_Coincidences->mkdir("dT_event_Coincidences");
    dir_lisafast_Diamond_dT_window = dir_lisafast_Diamond_Coincidences->mkdir("dT_window_Coincidences");
    dir_lisafast_Diamond_dT_event_single = dir_lisafast_Diamond_dT_event->mkdir("Single_Diamond");
    dir_lisafast_Diamond_dTw_single = dir_lisafast_Diamond_dT_window->mkdir("Single_Diamond");

    // Prepare one subdirectory per Diamond layer
    dir_lisafast_slowToT_Diamond_layer.resize(max_layer, nullptr);
    dir_lisafast_energy_spectra_Diamond_layer.resize(max_layer, nullptr);
    dir_lisafast_fastToT_Diamond_layer.resize(max_layer, nullptr);
    dir_lisafast_fast_v_slow_Diamond_layer.resize(max_layer, nullptr);
    dir_lisafast_time_spectra_Diamond_layer.resize(max_layer, nullptr);

    for (int layer = 0; layer < max_layer; layer++)
    {
        dir_lisafast_slowToT_Diamond_layer[layer] = dir_lisafast_slowToT_Diamond->mkdir(Form("Layer_%d", layer + 1));
        dir_lisafast_energy_spectra_Diamond_layer[layer] = dir_lisafast_energy_spectra_Diamond->mkdir(Form("Layer_%d", layer + 1));
        dir_lisafast_fastToT_Diamond_layer[layer] = dir_lisafast_fastToT_Diamond->mkdir(Form("Layer_%d", layer + 1));
        dir_lisafast_fast_v_slow_Diamond_layer[layer] = dir_lisafast_fast_v_slow_Diamond->mkdir(Form("Layer_%d", layer + 1));
        dir_lisafast_time_spectra_Diamond_layer[layer] = dir_lisafast_time_spectra_Diamond->mkdir(Form("Layer_%d", layer + 1));
    }

    if (number_labr_detectors > 0)
    {
    

        // ===:::::::: LABR :::::::::::===
        // ::: Slow ToT (i.e. raw energy):
        c_lisafast_slowToT_LaBr  = new TCanvas("c_lisafast_slowToT_LaBr","slow ToT LaBr spectra",650,350);
        c_lisafast_slowToT_LaBr->Divide(2, (number_labr_detectors+1)/2);
        h1_lisafast_slowToT_LaBr.resize(number_labr_detectors);
        for (int ihist = 0; ihist < number_labr_detectors; ihist++)
        {
            c_lisafast_slowToT_LaBr->cd(ihist+1);
            h1_lisafast_slowToT_LaBr[ihist] = MakeTH1(dir_lisafast_slowToT_LaBr, "F", Form("h1_lisafast_slowToT_LaBr_%d",ihist), Form("LaBr slow ToT detector %d",ihist),lisafast_configuration->slowToT_bin,lisafast_configuration->slowToT_min,lisafast_configuration->slowToT_max, "ToT [ns]", kSpring, kBlue+2);
            h1_lisafast_slowToT_LaBr[ihist]->Draw();
        }
        c_lisafast_slowToT_LaBr->cd(0);
        dir_lisafast_slowToT_LaBr->Append(c_lisafast_slowToT_LaBr);

        // ::: Fast ToT
        c_lisafast_fastToT_LaBr  = new TCanvas("c_lisafast_fastToT_LaBr","Fast ToT LaBr spectra",650,350);
        c_lisafast_fastToT_LaBr->Divide(2, (number_labr_detectors+1)/2);
        h1_lisafast_fastToT_LaBr.resize(number_labr_detectors);
        for (int ihist = 0; ihist < number_labr_detectors; ihist++)
        {
            c_lisafast_fastToT_LaBr->cd(ihist+1);
            h1_lisafast_fastToT_LaBr[ihist] = MakeTH1(dir_lisafast_fastToT_LaBr, "F", Form("h1_lisafast_fastToT_LaBr_%d",ihist+1),Form("LaBr fast ToT detector %d",ihist+1),lisafast_configuration->fastToT_bin,lisafast_configuration->fastToT_min,lisafast_configuration->fastToT_max, "ToT [ns]", kSpring, kBlue+2);
            h1_lisafast_fastToT_LaBr[ihist]->Draw();
            
        }
        c_lisafast_fastToT_LaBr->cd(0);
        dir_lisafast_fastToT_LaBr->Add(c_lisafast_fastToT_LaBr);
        
        // ::: Energy spectrum (calibrated slowToT):::
        c_lisafast_energy_LaBr  = new TCanvas("c_lisafast_energy_LaBr","LaBr energy spectra",650,350);
        c_lisafast_energy_LaBr->Divide(2, (number_labr_detectors+1)/2);
        h1_lisafast_energy_LaBr.resize(number_labr_detectors);
        for (int ihist = 0; ihist < number_labr_detectors; ihist++){
            c_lisafast_energy_LaBr->cd(ihist+1);
            h1_lisafast_energy_LaBr[ihist] = MakeTH1(dir_lisafast_energy_spectra_LaBr, "F", Form("h1_lisafast_energy_LaBr_%d",ihist+1),Form("LisaFast energy detector %d",ihist+1),lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max, "Energy [keV]", kOrange-3, kBlue+2);
            h1_lisafast_energy_LaBr[ihist]->Draw();
        }
        c_lisafast_energy_LaBr->cd(0);
        dir_lisafast_energy_spectra_LaBr->Append(c_lisafast_energy_LaBr);

        h2_E1_vs_E2_all_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_E1_vs_E2_all_LaBr","LaBr all coincidence energy correlations",lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max,lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max, "Energy 1 [keV]", "Energy 2 [keV]");
        //h3_E1_vs_E2_vs_dt_all_LaBr = MakeTH3(dir_lisafast_energy_spectra_LaBr, "F", "h3_E1_vs_E2_vs_dt_all_LaBr","LaBr all coincidence energy correlations vs. time difference",lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max,lisafast_configuration->energy_bin,lisafast_configuration->energy_min,lisafast_configuration->energy_max, lisafast_configuration->dt_bin,lisafast_configuration->dt_min,lisafast_configuration->dt_max, "Energy 1 [keV]", "Energy 2 [keV]", "dT [ns]");


        // ::: Fast vs Slow:
        c_lisafast_fast_v_slow_LaBr  = new TCanvas("c_lisafast_fast_v_slow_LaBr","LaBr fast vs slow ToT spectra",650,350);
        c_lisafast_fast_v_slow_LaBr->Divide(std::min(number_labr_detectors, 5), (number_labr_detectors + 4) / 5); //organize in rows of maximum 5
        h2_lisafast_fast_v_slow_LaBr.resize(number_labr_detectors);
        for (int ihist = 0; ihist < number_labr_detectors; ihist++){
            c_lisafast_fast_v_slow_LaBr->cd(ihist+1);
            h2_lisafast_fast_v_slow_LaBr[ihist] = MakeTH2(dir_lisafast_fast_v_slow_LaBr, "F", Form("h2_lisafast_fast_v_slow_ToT_LaBr_%d",ihist+1),Form("LISA_FAST fast vs. slow detector %d",ihist+1),lisafast_configuration->slowToT_bin,lisafast_configuration->slowToT_min,lisafast_configuration->slowToT_max, lisafast_configuration->fastToT_bin,lisafast_configuration->fastToT_min,lisafast_configuration->fastToT_max, "Slow ToT [ns]","Fast ToT [ns]");
            h2_lisafast_fast_v_slow_LaBr[ihist]->Draw();        
        }
        c_lisafast_fast_v_slow_LaBr->cd(0);
        dir_lisafast_fast_v_slow_LaBr->Append(c_lisafast_fast_v_slow_LaBr);
        
        // ::: Time spectra:
        dir_lisafast_time_spectra_LaBr->cd();
        c_lisafast_time_spectra_divided_LaBr  = new TCanvas("c_lisafast_time_spectra_divided_LaBr","LaBr Absolute time spectra",650,350);
        c_lisafast_time_spectra_divided_LaBr->Divide(std::min(number_labr_detectors, 5), (number_labr_detectors + 4) / 5);
        h1_lisafast_abs_time_LaBr.resize(number_labr_detectors);
        for (int ihist = 0; ihist < number_labr_detectors; ihist++)
        {
            c_lisafast_time_spectra_divided_LaBr->cd(ihist+1);
            h1_lisafast_abs_time_LaBr[ihist] = MakeTH1(dir_lisafast_time_spectra_LaBr, "F", Form("h1_lisafast_abs_time_LaBr_%d",ihist+1),Form("LaBr absolute DAQ time detector %d",ihist+1), 1e3, 0, 2.7e12, "Timestamp [ns]");
            h1_lisafast_abs_time_LaBr[ihist]->Draw();
        }
        c_lisafast_time_spectra_divided_LaBr->cd(0);
        dir_lisafast_time_spectra_LaBr->Append(c_lisafast_time_spectra_divided_LaBr);

        // ::: 2D energy spectrum
        //c4LOG(info," number of LaBr : " << number_labr_detectors);

        c_lisafast_energy_vs_detid_LaBr = new TCanvas("c_lisafast_energy_vs_detid_LaBr","LaBr energy vs ID",650,350);
        h2_lisafast_energy_vs_detid_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_lisafast_energy_vs_detid_LaBr",
            "LaBr energies vs ID", number_labr_detectors, 0.5, number_labr_detectors+0.5,
            lisafast_configuration->energy_bin,
            lisafast_configuration->energy_min,
            lisafast_configuration->energy_max,
            "LaBr", "Energy [keV]");
        h2_lisafast_energy_vs_detid_LaBr->Draw();
        dir_lisafast_energy_spectra_LaBr->Append(c_lisafast_energy_vs_detid_LaBr);

        // ::: 2D uncalibrated energy spectrum
        c_lisafast_energy_uncal_LaBr = new TCanvas("c_lisafast_energy_uncal_LaBr","LaBr raw energy vs ID",650,350);
        h2_lisafast_energy_uncal_vs_detid_LaBr = MakeTH2(dir_lisafast_energy_spectra_LaBr, "F", "h2_lisafast_energy_uncal_vs_detid_LaBr",
            "LaBr raw energy vs ID", number_labr_detectors,0.5,number_labr_detectors+0.5, 
            lisafast_configuration->slowToT_bin,
            lisafast_configuration->slowToT_min,
            lisafast_configuration->slowToT_max,
            "LaBr","Energy [a.u.]");
        h2_lisafast_energy_uncal_vs_detid_LaBr->Draw();
        dir_lisafast_energy_spectra_LaBr->Append(c_lisafast_energy_uncal_LaBr);

        //:::  Hit patterns
        c_lisafast_hitpatterns_LaBr  = new TCanvas("c_lisafast_hitpatterns_LaBr","LaBr hit patterns",650,350);
        c_lisafast_hitpatterns_LaBr->Divide(2,1);

        // Fast hit pattern
        c_lisafast_hitpatterns_LaBr->cd(1);
        h1_lisafast_hitpattern_slow_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_hitpattern_slow_LaBr","LaBr slow hit patterns",number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "LaBr", kRed-3, kBlack);
        h1_lisafast_hitpattern_slow_LaBr->Draw();
        
        // Slow hit pattern
        c_lisafast_hitpatterns_LaBr->cd(2);
        h1_lisafast_hitpattern_fast_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I", "h1_lisafast_hitpattern_fast_LaBr","LaBr fast hit patterns",number_labr_detectors+1,0-0.5,number_labr_detectors+0.5, "LaBr", kRed-3, kBlack);
        h1_lisafast_hitpattern_fast_LaBr->Draw();
        c_lisafast_hitpatterns_LaBr->cd(0);
        dir_lisafast_hitpattern_LaBr->Append(c_lisafast_hitpatterns_LaBr);
        
        // ::: Multiplicity

        c_lisafast_event_multiplicity = new TCanvas("c_lisafast_event_multiplicity","LaBr event multiplicities", 650, 350);
        c_lisafast_event_multiplicity->Divide(2, 1);

        // Event multiplicity
        c_lisafast_event_multiplicity->cd(1);

        h1_lisafast_event_multiplicity_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I",
            "h1_lisafast_event_multiplicity_LaBr","LaBr event multiplicity",
            20, 0, 20,"Number of LaBr hits per event", kRed-3, kBlack);

        h1_lisafast_event_multiplicity_LaBr->Draw();

        // Detector multiplicity
        c_lisafast_event_multiplicity->cd(2);
        h1_lisafast_detector_multiplicity_LaBr = MakeTH1(dir_lisafast_hitpattern_LaBr, "I",
            "h1_lisafast_detector_multiplicity_LaBr","LaBr detector multiplicity",
            20, 0, 20,"Number of distinct LaBr detectors per event", kBlue, kBlack);

        h1_lisafast_detector_multiplicity_LaBr->Draw();

        c_lisafast_event_multiplicity->cd(0);
        dir_lisafast_hitpattern_LaBr->Append(c_lisafast_event_multiplicity);

        // ::: Time differences - event based

        // Ungated dT
        dir_lisafast_dT_event_coin_LaBr = dir_lisafast_LaBr->mkdir("dT_event_Coincidences");
        dir_lisafast_dT_event_coin_LaBr->cd();

        c_lisafast_deltaT_LaBr = new TCanvas("c_lisafast_deltaT_LaBr","LaBr relative time differences",650, 350);
        c_lisafast_deltaT_LaBr->Divide(std::min(number_labr_detectors, 5),(number_labr_detectors + 4) / 5);
        
        c4LOG(info," number of ref detector " << dt_reference_labr);
        h1_lisafast_deltaT_LaBr.resize(number_labr_detectors);

        for (int detid_idx = 0;detid_idx < number_labr_detectors;detid_idx++)
        {
            c_lisafast_deltaT_LaBr->cd(detid_idx + 1);
            h1_lisafast_deltaT_LaBr[detid_idx] =
                MakeTH1(dir_lisafast_dT_event_coin_LaBr,"F",
                    Form("h1_lisafast_dT_%d_to_%d_LaBr",detid_idx + 1, dt_reference_labr),
                    Form("LaBr dT t(%d) - t(%d)", detid_idx + 1, dt_reference_labr),
                    lisafast_configuration->dt_bin,
                    lisafast_configuration->dt_min,
                    lisafast_configuration->dt_max,
                    Form("dT t(%d) - t(%d) [ns]", detid_idx + 1, dt_reference_labr),
                    kMagenta,kBlue + 2);

            h1_lisafast_deltaT_LaBr[detid_idx]->Draw();
        }
        c_lisafast_deltaT_LaBr->cd(0);
        dir_lisafast_dT_event_coin_LaBr->Append(c_lisafast_deltaT_LaBr);
        
        // Ungated dT vs energy
        c_lisafast_deltaT_vs_energy_LaBr = new TCanvas("c_lisafast_deltaT_vs_energy_LaBr", "LaBr relative time differences vs energy",650, 350);
        c_lisafast_deltaT_vs_energy_LaBr->Divide(std::min(number_labr_detectors, 5),(number_labr_detectors + 4) / 5);

        h2_lisafast_deltaT_vs_energy_LaBr.resize(number_labr_detectors);
        for (int detid_idx = 0;detid_idx < number_labr_detectors;detid_idx++)
        {
            c_lisafast_deltaT_vs_energy_LaBr->cd(detid_idx + 1);

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

            h2_lisafast_deltaT_vs_energy_LaBr[detid_idx]->Draw();
        }

        c_lisafast_deltaT_vs_energy_LaBr->cd(0);
        dir_lisafast_dT_event_coin_LaBr->Append(c_lisafast_deltaT_vs_energy_LaBr);

        // ::: Energy gated event-based coincidences
        dir_lisafast_dT_event_Gates_LaBr = dir_lisafast_dT_event_coin_LaBr->mkdir("dT_event_Gates");
        h1_lisafast_deltaT_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
        h2_lisafast_deltaT_vs_energy_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
        
        c_lisafast_deltaT_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
        c_lisafast_deltaT_vs_energy_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());

        // ::: Energy gated on dT window coincidences
        dir_lisafast_dT_window_Gates_LaBr = dir_lisafast_dTw_coin_LaBr->mkdir("dTw_event_Gates_LaBr");
        h1_lisafast_dTw_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
        h2_lisafast_dTw_vs_energy_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());

        c_lisafast_dTw_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());
        c_lisafast_dTw_vs_energy_LaBr_gated.resize(dt_reference_detectors_energy_gates.size());

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
            TDirectory* dir_dTw_gate = dir_lisafast_dT_window_Gates_LaBr->mkdir(name_dTw.str().c_str());
            
            dir_gate->cd();
            h1_lisafast_deltaT_LaBr_gated[igate].resize(number_labr_detectors);
            h2_lisafast_deltaT_vs_energy_LaBr_gated[igate].resize(number_labr_detectors);       
            
            c_lisafast_deltaT_LaBr_gated[igate] =
                new TCanvas(Form("c_lisafast_deltaT_LaBr_gated_ref%d_gate%d_%d",
                        dt_reference_labr,(int)gate_other,(int)gate_ref),
                    "LaBr gated relative time differences",650,350);
            c_lisafast_deltaT_LaBr_gated[igate]->Divide(std::min(number_labr_detectors, 5),(number_labr_detectors + 4) / 5);

            c_lisafast_deltaT_vs_energy_LaBr_gated[igate] =
                new TCanvas(Form("c_lisafast_deltaT_vs_energy_LaBr_gated_ref%d_gate%d_%d",
                        dt_reference_labr,(int)gate_other,(int)gate_ref),
                    "LaBr gated relative time differences vs energy",650,350);
            c_lisafast_deltaT_vs_energy_LaBr_gated[igate]->Divide(
                std::min(number_labr_detectors, 5),
                (number_labr_detectors + 4) / 5);

            dir_dTw_gate->cd();
            h1_lisafast_dTw_LaBr_gated[igate].resize(number_labr_detectors);
            h2_lisafast_dTw_vs_energy_LaBr_gated[igate].resize(number_labr_detectors);

            c_lisafast_dTw_LaBr_gated[igate] =
                new TCanvas(Form("c_lisafast_dTw_LaBr_gated_ref%d_gate%d_%d",
                        dt_reference_labr,(int)gate_other,(int)gate_ref),
                    "LaBr_gated_dTw",650, 350);

            c_lisafast_dTw_LaBr_gated[igate]->Divide(std::min(number_labr_detectors, 5),(number_labr_detectors + 4) / 5);

            c_lisafast_dTw_vs_energy_LaBr_gated[igate] =
                new TCanvas(Form("c_lisafast_dTw_vs_energy_LaBr_gated_ref%d_gate%d_%d",
                        dt_reference_labr,(int)gate_other,(int)gate_ref),
                    "LaBr gated dTw vs energy",650, 350);

            c_lisafast_dTw_vs_energy_LaBr_gated[igate]->Divide(std::min(number_labr_detectors, 5),(number_labr_detectors + 4) / 5);
            
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
                    c_lisafast_deltaT_LaBr_gated[igate]->cd(detid_idx + 1);
                    h1_lisafast_deltaT_LaBr_gated[igate][detid_idx]->Draw();

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
                c_lisafast_deltaT_vs_energy_LaBr_gated[igate]->cd(detid_idx + 1);
                h2_lisafast_deltaT_vs_energy_LaBr_gated[igate][detid_idx]->Draw("COLZ");

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

                c_lisafast_dTw_LaBr_gated[igate]->cd(detid_idx + 1);
                h1_lisafast_dTw_LaBr_gated[igate][detid_idx]->Draw();  

                c_lisafast_dTw_vs_energy_LaBr_gated[igate]->cd(detid_idx + 1);
                h2_lisafast_dTw_vs_energy_LaBr_gated[igate][detid_idx]->Draw("COLZ");
            
            }
            c_lisafast_deltaT_LaBr_gated[igate]->cd(0);
            dir_gate->Append(c_lisafast_deltaT_LaBr_gated[igate]);

            c_lisafast_deltaT_vs_energy_LaBr_gated[igate]->cd(0);
            dir_gate->Append(c_lisafast_deltaT_vs_energy_LaBr_gated[igate]);

            c_lisafast_dTw_LaBr_gated[igate]->cd(0);
            dir_dTw_gate->Append(c_lisafast_dTw_LaBr_gated[igate]);

            c_lisafast_dTw_vs_energy_LaBr_gated[igate]->cd(0);
            dir_dTw_gate->Append(c_lisafast_dTw_vs_energy_LaBr_gated[igate]);
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
        
        c_lisafast_dTw_coin_LaBr = new TCanvas("c_lisafast_dTw_coin_LaBr","LaBr dT window coincidence",650, 350);
        h1_lisafast_dTw_coin_LaBr->Draw();

        c_lisafast_dTw_coin_LaBr->cd(0);
        dir_lisafast_dTw_coin_LaBr->Append(c_lisafast_dTw_coin_LaBr);
        c_lisafast_dTw_vs_energy_coin_LaBr = new TCanvas("c_lisafast_dTw_vs_energy_coin_LaBr","LaBr dTw vs energy",650, 350);

        h2_lisafast_dTw_vs_energy_coin_LaBr->Draw("COLZ");

        c_lisafast_dTw_vs_energy_coin_LaBr->cd(0);
        dir_lisafast_dTw_coin_LaBr->Append(c_lisafast_dTw_vs_energy_coin_LaBr);
    }

    dir_lisafast->cd();

    // ================================================
    // Diamond raw spectra
    // ================================================


    if (number_diamond_detectors > 0)
    {

        // ================================================
        // Diamond Hit Pattern - Grid
        // ================================================

        c_lisafast_hitpattern_grid_Diamond = new TCanvas("c_lisafast_hitpattern_grid_Diamond","Diamond Hit Pattern Grid",900, 700);
        c_lisafast_hitpattern_grid_Diamond->Divide(2, (max_layer + 1) / 2, 0.05, 0.05);
        h2_lisafast_hitpattern_grid_Diamond.resize(max_layer);
        
        // ::: Diamond multiplicity

        c_lisafast_event_multiplicity_Diamond = new TCanvas("c_lisafast_event_multiplicity_Diamond","Diamond event multiplicities", 650, 350);
        c_lisafast_event_multiplicity_Diamond->Divide(2, 1);

        // Event multiplicity
        c_lisafast_event_multiplicity_Diamond->cd(1);

        h1_lisafast_event_multiplicity_Diamond = MakeTH1(dir_lisafast_hitpattern_Diamond, "I",
            "h1_lisafast_event_multiplicity_Diamond","Diamond event multiplicity",
            100, 0, 100,"Number of Diamond hits per event", kRed-3, kBlack);

        h1_lisafast_event_multiplicity_Diamond->Draw();

        // Detector multiplicity
        c_lisafast_event_multiplicity_Diamond->cd(2);

        h1_lisafast_detector_multiplicity_Diamond = MakeTH1(dir_lisafast_hitpattern_Diamond, "I",
            "h1_lisafast_detector_multiplicity_Diamond",
            "Diamond detector multiplicity",
            100, 0, 100,"Number of distinct Diamond pixels per event", kBlue, kBlack);

        h1_lisafast_detector_multiplicity_Diamond->Draw();

        c_lisafast_event_multiplicity_Diamond->cd(0);
        dir_lisafast_hitpattern_Diamond->Append(c_lisafast_event_multiplicity_Diamond);

        // ================================================
        // Diamond-Diamond coincidences
        // ================================================

        int ref_layer = std::get<0>(dt_reference_diamond);
        int ref_x = std::get<1>(dt_reference_diamond);
        int ref_y = std::get<2>(dt_reference_diamond);

        TString ref_tag;

        if (ref_layer > 0)
            ref_tag = Form("ref_%d%d%d", ref_layer, ref_x, ref_y);
        else
            ref_tag = "ref_-1";

        // Event-based coincidences
        h1_lisafast_deltaT_Diamond.resize(max_layer);
        h2_lisafast_deltaT_vs_energy_Diamond.resize(max_layer);

        // Time-window coincidences
        h1_lisafast_dTw_Diamond.resize(max_layer);
        h2_lisafast_dTw_vs_energy_Diamond.resize(max_layer);


        // Resize layer-level histogram vectors
        h1_lisafast_slowToT_Diamond_layer.resize(max_layer, nullptr);
        h1_lisafast_energy_Diamond_layer.resize(max_layer, nullptr);
        h1_lisafast_fastToT_Diamond_layer.resize(max_layer, nullptr);

        // Resize per-pixel histogram arrays
        h1_lisafast_slowToT_Diamond.resize(max_layer);
        h1_lisafast_energy_Diamond.resize(max_layer);
        h1_lisafast_fastToT_Diamond.resize(max_layer);
        h2_lisafast_fast_v_slow_Diamond.resize(max_layer);
        h1_lisafast_abs_time_Diamond.resize(max_layer);

        c_lisafast_slowToT_Diamond.resize(max_layer, nullptr);
        c_lisafast_fastToT_Diamond.resize(max_layer, nullptr);
        c_lisafast_energy_Diamond.resize(max_layer, nullptr);
        c_lisafast_fast_v_slow_Diamond.resize(max_layer, nullptr);

        for (int layer = 0; layer < max_layer; layer++)
        {
            
            // Diamond hit pattern for this layer
            c_lisafast_hitpattern_grid_Diamond->cd(layer + 1);

            h2_lisafast_hitpattern_grid_Diamond[layer] = MakeTH2(dir_lisafast_hitpattern_Diamond, "F",
                Form("h2_lisafast_hitpattern_grid_Diamond_layer_%d", layer + 1),
                Form("Diamond Hit Pattern - Layer %d", layer + 1),
                max_x, 0, max_x,max_y, 0, max_y,"X position", "Y position");

            h2_lisafast_hitpattern_grid_Diamond[layer]->SetStats(0);
            h2_lisafast_hitpattern_grid_Diamond[layer]->Draw("COLZ");
            
            // Canvas for individual Diamond SlowToT histograms in this layer
            c_lisafast_slowToT_Diamond[layer] = new TCanvas(Form("c_lisafast_slowToT_Diamond_layer_%d", layer + 1),Form("Diamond SlowToT - Layer %d", layer + 1),900, 700);
            c_lisafast_slowToT_Diamond[layer]->Divide(max_x, max_y);
            
            h1_lisafast_slowToT_Diamond[layer].resize(max_x, std::vector<TH1*>(max_y, nullptr));
            h1_lisafast_energy_Diamond[layer].resize(max_x, std::vector<TH1*>(max_y, nullptr));
            h1_lisafast_fastToT_Diamond[layer].resize(max_x, std::vector<TH1*>(max_y, nullptr));
            h2_lisafast_fast_v_slow_Diamond[layer].resize(max_x, std::vector<TH2*>(max_y, nullptr));
            h1_lisafast_abs_time_Diamond[layer].resize(max_x, std::vector<TH1*>(max_y, nullptr));

            h1_lisafast_deltaT_Diamond[layer].resize(max_x, std::vector<TH1*>(max_y, nullptr));
            h2_lisafast_deltaT_vs_energy_Diamond[layer].resize(max_x, std::vector<TH2*>(max_y, nullptr));
            h1_lisafast_dTw_Diamond[layer].resize(max_x, std::vector<TH1*>(max_y, nullptr));
            h2_lisafast_dTw_vs_energy_Diamond[layer].resize(max_x, std::vector<TH2*>(max_y, nullptr));
            
            // Canvas for individual Diamond Fast vs Slow ToT histograms
            c_lisafast_fast_v_slow_Diamond[layer] = new TCanvas(Form("c_lisafast_fast_v_slow_Diamond_layer_%d", layer + 1),Form("Diamond Fast vs Slow ToT - Layer %d", layer + 1),900, 700);
            c_lisafast_fast_v_slow_Diamond[layer]->Divide(max_x, max_y);

            // Layer-level SlowToT
            h1_lisafast_slowToT_Diamond_layer[layer] = MakeTH1(dir_lisafast_slowToT_Diamond, "F",
                Form("h1_lisafast_slowToT_Diamond_layer_%d", layer + 1),
                Form("Diamond SlowToT - Layer %d", layer + 1),
                lisafast_configuration->slowToT_bin,
                lisafast_configuration->slowToT_min,
                lisafast_configuration->slowToT_max,
                "Slow ToT [ns]", kSpring, kBlue + 2);

            // Layer-level energy
            h1_lisafast_energy_Diamond_layer[layer] = MakeTH1(dir_lisafast_energy_spectra_Diamond, "F",
                Form("h1_lisafast_energy_Diamond_layer_%d", layer + 1),
                Form("Diamond Energy - Layer %d", layer + 1),
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                "Energy [keV]", kOrange - 3, kBlue + 2);

            // Canvas for individual Diamond Energy histograms in this layer
            c_lisafast_energy_Diamond[layer] = new TCanvas(
                Form("c_lisafast_energy_Diamond_layer_%d", layer + 1),
                Form("Diamond Energy - Layer %d", layer + 1),900, 700);
            c_lisafast_energy_Diamond[layer]->Divide(max_x, max_y);

            // Layer-level FastToT
            h1_lisafast_fastToT_Diamond_layer[layer] = MakeTH1(dir_lisafast_fastToT_Diamond, "F",
                Form("h1_lisafast_fastToT_Diamond_layer_%d", layer + 1),
                Form("Diamond FastToT - Layer %d", layer + 1),
                lisafast_configuration->fastToT_bin,
                lisafast_configuration->fastToT_min,
                lisafast_configuration->fastToT_max,
                "Fast ToT [ns]", kSpring, kBlue + 2);

            // Canvas for individual Diamond FastToT histograms in this layer
            c_lisafast_fastToT_Diamond[layer] = new TCanvas(
                Form("c_lisafast_fastToT_Diamond_layer_%d", layer + 1),
                Form("Diamond FastToT - Layer %d", layer + 1),900, 700);
            c_lisafast_fastToT_Diamond[layer]->Divide(max_x, max_y);


            // Per-diamond histograms
            for (int x = 0; x < max_x; x++)
            {
                for (int y = 0; y < max_y; y++)
                {
                    TString city = "";
                    TString sn = "";

                    // Retrieve detector information from mapping
                    for (const auto& [tamex_bc, info] : diamond_mapping)
                    {
                        int mapped_layer = info.first.first;
                        int mapped_x = info.first.second.first;
                        int mapped_y = info.first.second.second;

                        if (mapped_layer == layer + 1 &&
                            mapped_x == x &&
                            mapped_y == y)
                        {
                            city = info.second.second.first;
                            sn = info.second.second.second;
                            break;
                        }
                    }

                    // SlowToT
                    h1_lisafast_slowToT_Diamond[layer][x][y] = MakeTH1(dir_lisafast_slowToT_Diamond_layer[layer], "F",
                        Form("h1_lisafast_slowToT_Diamond_%s_%s_%d%d%d",city.Data(), sn.Data(), layer + 1, x, y),
                        Form("Diamond SlowToT %s - Layer %d (%d,%d)",city.Data(), layer + 1, x, y),
                        lisafast_configuration->slowToT_bin,
                        lisafast_configuration->slowToT_min,
                        lisafast_configuration->slowToT_max,
                        "Slow ToT [ns]", kSpring, kBlue + 2);

                    // Draw in the corresponding position of the Diamond grid
                    int pad = (max_y - (y + 1)) * max_x + x + 1;

                    c_lisafast_slowToT_Diamond[layer]->cd(pad);
                    h1_lisafast_slowToT_Diamond[layer][x][y]->Draw();
                    

                    // Energy
                    h1_lisafast_energy_Diamond[layer][x][y] = MakeTH1(dir_lisafast_energy_spectra_Diamond_layer[layer], "F",
                        Form("h1_lisafast_energy_Diamond_%s_%s_%d%d%d",city.Data(), sn.Data(), layer + 1, x, y),
                        Form("Diamond Energy %s - Layer %d (%d,%d)",city.Data(), layer + 1, x, y),
                        lisafast_configuration->energy_bin,
                        lisafast_configuration->energy_min,
                        lisafast_configuration->energy_max,
                        "Energy [keV]", kOrange - 3, kBlue + 2);
                    
                    // Draw in the corresponding position of the Diamond grid
                    c_lisafast_energy_Diamond[layer]->cd(pad);
                    h1_lisafast_energy_Diamond[layer][x][y]->Draw();

                    // FastToT
                    h1_lisafast_fastToT_Diamond[layer][x][y] = MakeTH1(dir_lisafast_fastToT_Diamond_layer[layer], "F",
                        Form("h1_lisafast_fastToT_Diamond_%s_%s_%d%d%d",city.Data(), sn.Data(), layer + 1, x, y),
                        Form("Diamond FastToT %s - Layer %d (%d,%d)",city.Data(), layer + 1, x, y),
                        lisafast_configuration->fastToT_bin,
                        lisafast_configuration->fastToT_min,
                        lisafast_configuration->fastToT_max,
                        "Fast ToT [ns]", kSpring, kBlue + 2);

                    // Draw in the corresponding position of the Diamond grid
                    c_lisafast_fastToT_Diamond[layer]->cd(pad);
                    h1_lisafast_fastToT_Diamond[layer][x][y]->Draw();

                    // Fast versus Slow ToT
                    h2_lisafast_fast_v_slow_Diamond[layer][x][y] = MakeTH2(dir_lisafast_fast_v_slow_Diamond_layer[layer], "F",
                        Form("h2_lisafast_fast_v_slow_Diamond_%s_%s_%d%d%d",city.Data(), sn.Data(), layer + 1, x, y),
                        Form("Diamond Fast vs. Slow ToT %s - Layer %d (%d,%d)",city.Data(), layer + 1, x, y),
                        lisafast_configuration->slowToT_bin,
                        lisafast_configuration->slowToT_min,
                        lisafast_configuration->slowToT_max,
                        lisafast_configuration->fastToT_bin,
                        lisafast_configuration->fastToT_min,
                        lisafast_configuration->fastToT_max,
                        "Slow ToT [ns]", "Fast ToT [ns]");
                    
                    c_lisafast_fast_v_slow_Diamond[layer]->cd(pad);
                    h2_lisafast_fast_v_slow_Diamond[layer][x][y]->Draw("COLZ");

                    // Absolute time
                    h1_lisafast_abs_time_Diamond[layer][x][y] = MakeTH1(dir_lisafast_time_spectra_Diamond_layer[layer], "F",
                        Form("h1_lisafast_abs_time_Diamond_%s_%s_%d%d%d",city.Data(), sn.Data(), layer + 1, x, y),
                        Form("Diamond absolute DAQ time %s - Layer %d (%d,%d)",city.Data(), layer + 1, x, y),
                        1e3, 0, 2.7e12, "Timestamp [ns]");


                    // ========================================
                    // Event-based dT
                    // ========================================

                    h1_lisafast_deltaT_Diamond[layer][x][y] = MakeTH1(dir_lisafast_Diamond_dT_event_single, "F",
                            Form("h1_lisafast_deltaT_Diamond_%s_%s_%s_%d%d%d",city.Data(), sn.Data(), ref_tag.Data(),layer + 1, x, y),
                            Form("Diamond dT %s - Layer %d (%d,%d) - %s",city.Data(), layer + 1, x, y, ref_tag.Data()),
                            lisafast_configuration->dt_bin,
                            lisafast_configuration->dt_min,
                            lisafast_configuration->dt_max,
                            "dT [ns]", kMagenta, kBlue + 2);

                    h2_lisafast_deltaT_vs_energy_Diamond[layer][x][y] =MakeTH2(dir_lisafast_Diamond_dT_event_single, "F",
                            Form("h2_lisafast_deltaT_vs_energy_Diamond_%s_%s_%s_%d%d%d",city.Data(), sn.Data(), ref_tag.Data(),layer + 1, x, y),
                            Form("Diamond dT vs Energy - Layer %d (%d,%d) - %s",layer + 1, x, y, ref_tag.Data()),
                            lisafast_configuration->energy_bin,
                            lisafast_configuration->energy_min,
                            lisafast_configuration->energy_max,
                            lisafast_configuration->dt_bin,
                            lisafast_configuration->dt_min,
                            lisafast_configuration->dt_max,
                            "Energy [keV]", "dT [ns]");

                    // ========================================
                    // Time-window dTw
                    // ========================================

                    h1_lisafast_dTw_Diamond[layer][x][y] = MakeTH1(dir_lisafast_Diamond_dTw_single, "F",
                            Form("h1_lisafast_dTw_Diamond_%s_%s_%s_%d%d%d",city.Data(), sn.Data(), ref_tag.Data(),layer + 1, x, y),
                            Form("Diamond dTw %s - Layer %d (%d,%d) - %s",city.Data(), layer + 1, x, y, ref_tag.Data()),
                            lisafast_configuration->dt_bin,
                            lisafast_configuration->dt_min,
                            lisafast_configuration->dt_max,
                            "dTw [ns]", kMagenta, kBlue + 2);

                    h2_lisafast_dTw_vs_energy_Diamond[layer][x][y] = MakeTH2(dir_lisafast_Diamond_dTw_single, "F",
                            Form("h2_lisafast_dTw_vs_energy_Diamond_%s_%s_%s_%d%d%d",city.Data(), sn.Data(), ref_tag.Data(),layer + 1, x, y),
                            Form("Diamond dTw vs Energy - Layer %d (%d,%d) - %s",layer + 1, x, y, ref_tag.Data()),
                            lisafast_configuration->energy_bin,
                            lisafast_configuration->energy_min,
                            lisafast_configuration->energy_max,
                            lisafast_configuration->dt_bin,
                            lisafast_configuration->dt_min,
                            lisafast_configuration->dt_max,
                            "Energy [keV]", "dTw [ns]");
                }
            }

            c_lisafast_slowToT_Diamond[layer]->cd(0);
            dir_lisafast_slowToT_Diamond_layer[layer]->Append(c_lisafast_slowToT_Diamond[layer]);
            c_lisafast_fastToT_Diamond[layer]->cd(0);
            dir_lisafast_fastToT_Diamond_layer[layer]->Append(c_lisafast_fastToT_Diamond[layer]); 
            c_lisafast_energy_Diamond[layer]->cd(0);
            dir_lisafast_energy_spectra_Diamond_layer[layer]->Append(c_lisafast_energy_Diamond[layer]);
            c_lisafast_fast_v_slow_Diamond[layer]->cd(0);
            dir_lisafast_fast_v_slow_Diamond_layer[layer]->Append(c_lisafast_fast_v_slow_Diamond[layer]);
        }

        c_lisafast_hitpattern_grid_Diamond->cd(0);
        dir_lisafast_hitpattern_Diamond->Append(c_lisafast_hitpattern_grid_Diamond);
        // Canvas for layer-level Diamond SlowToT histograms
        c_lisafast_slowToT_Diamond_layers = new TCanvas("c_lisafast_slowToT_Diamond_layers","Diamond SlowToT - All Layers",900, 700);
        c_lisafast_slowToT_Diamond_layers->Divide(2, (max_layer + 1) / 2);

        for (int layer = 0; layer < max_layer; layer++)
        {
            c_lisafast_slowToT_Diamond_layers->cd(layer + 1);
            h1_lisafast_slowToT_Diamond_layer[layer]->Draw();
        }

        c_lisafast_slowToT_Diamond_layers->cd(0);
        dir_lisafast_slowToT_Diamond->Append(c_lisafast_slowToT_Diamond_layers);

        // Canvas for layer-level Diamond FastToT histograms
        c_lisafast_fastToT_Diamond_layers = new TCanvas("c_lisafast_fastToT_Diamond_layers","Diamond FastToT - All Layers",900, 700);
        c_lisafast_fastToT_Diamond_layers->Divide(2, (max_layer + 1) / 2);

        for (int layer = 0; layer < max_layer; layer++)
        {
            c_lisafast_fastToT_Diamond_layers->cd(layer + 1);
            h1_lisafast_fastToT_Diamond_layer[layer]->Draw();
        }

        c_lisafast_fastToT_Diamond_layers->cd(0);
        dir_lisafast_fastToT_Diamond->Append(c_lisafast_fastToT_Diamond_layers);

        // Canvas for layer-level Diamond Energy histograms
        c_lisafast_energy_Diamond_layers = new TCanvas("c_lisafast_energy_Diamond_layers","Diamond Energy - All Layers",900, 700);
        c_lisafast_energy_Diamond_layers->Divide(2, (max_layer + 1) / 2);

        for (int layer = 0; layer < max_layer; layer++)
        {
            c_lisafast_energy_Diamond_layers->cd(layer + 1);
            h1_lisafast_energy_Diamond_layer[layer]->Draw();
        }

        c_lisafast_energy_Diamond_layers->cd(0);
        dir_lisafast_energy_spectra_Diamond->Append(c_lisafast_energy_Diamond_layers);

        // ================================================
        // Global event-based histograms
        // ================================================

        h1_lisafast_deltaT_coin_Diamond = MakeTH1(dir_lisafast_Diamond_dT_event, "F",
                Form("h1_lisafast_deltaT_coin_Diamond_%s", ref_tag.Data()),
                "Global Diamond event-based coincidence dT",
                lisafast_configuration->dt_bin,
                lisafast_configuration->dt_min,
                lisafast_configuration->dt_max,
                "dT [ns]", kMagenta, kBlue + 2);

        h2_lisafast_deltaT_vs_energy_coin_Diamond = MakeTH2(dir_lisafast_Diamond_dT_event, "F",
                Form("h2_lisafast_deltaT_vs_energy_coin_Diamond_%s", ref_tag.Data()),
                "Global Diamond event-based dT vs Energy",
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                lisafast_configuration->dt_bin,
                lisafast_configuration->dt_min,
                lisafast_configuration->dt_max,
                "Energy [keV]", "dT [ns]");

        h2_E1_vs_E2_deltaT_coin_Diamond = MakeTH2(dir_lisafast_Diamond_dT_event, "F",
                Form("h2_E1_vs_E2_deltaT_coin_Diamond_%s", ref_tag.Data()),
                "Global Diamond event-based E1 vs E2",
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                "Energy 1 [keV]", "Energy 2 [keV]");

        // ================================================
        // Global time-window histograms
        // ================================================

        h1_lisafast_dTw_coin_Diamond = MakeTH1(dir_lisafast_Diamond_dT_window, "F",
                Form("h1_lisafast_dTw_coin_Diamond_%s", ref_tag.Data()),
                "Global Diamond time-window coincidence dTw",
                lisafast_configuration->dt_bin,
                lisafast_configuration->dt_min,
                lisafast_configuration->dt_max,
                "dTw [ns]", kMagenta, kBlue + 2);

        h2_lisafast_dTw_vs_energy_coin_Diamond = MakeTH2(dir_lisafast_Diamond_dT_window, "F",
                Form("h2_lisafast_dTw_vs_energy_coin_Diamond_%s", ref_tag.Data()),
                "Global Diamond time-window dTw vs Energy",
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                lisafast_configuration->dt_bin,
                lisafast_configuration->dt_min,
                lisafast_configuration->dt_max,
                "Energy [keV]", "dTw [ns]");

        h2_E1_vs_E2_dTw_coin_Diamond = MakeTH2(dir_lisafast_Diamond_dT_window, "F",
                Form("h2_E1_vs_E2_dTw_coin_Diamond_%s", ref_tag.Data()),
                "Global Diamond time-window E1 vs E2",
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                lisafast_configuration->energy_bin,
                lisafast_configuration->energy_min,
                lisafast_configuration->energy_max,
                "Energy 1 [keV]", "Energy 2 [keV]");

    }
      
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
    int event_multiplicity_LaBr = 0;
    int event_multiplicity_Diamond = 0;

    std::set<int> fired_LaBr_detectors;
    std::set<std::tuple<int, int, int>> fired_Diamond_detectors;

    if (fHitLisaFast && fHitLisaFast->GetEntriesFast() > 0)
    {   
        event_multiplicity = 0;
        Int_t nHits = fHitLisaFast->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            LisaFastCalData* hit = (LisaFastCalData*)fHitLisaFast->At(ihit);
            if (!hit) continue;

            // ================================================
            // Diamond hits
            // ================================================
            if (hit->Get_detector_type() == 1)
            {
                int layer = hit->Get_layer() - 1; // Convert to zero-based index
                int x = hit->Get_x();
                int y = hit->Get_y();
                event_multiplicity_Diamond++;
                fired_Diamond_detectors.insert({hit->Get_layer(), x, y});

                // Check that the coordinates are within the booked histogram arrays
                if (layer < 0 || layer >= (int)h1_lisafast_slowToT_Diamond.size())
                    continue;

                if (x < 0 || x >= (int)h1_lisafast_slowToT_Diamond[layer].size())
                    continue;

                if (y < 0 || y >= (int)h1_lisafast_slowToT_Diamond[layer][x].size())
                    continue;
                // Diamond hit pattern
                if (h2_lisafast_hitpattern_grid_Diamond[layer])h2_lisafast_hitpattern_grid_Diamond[layer]->Fill(x, y);

                double slow_ToT = hit->Get_slow_ToT();
                double fast_ToT = hit->Get_fast_ToT();
                double energy = hit->Get_energy();
                double fast_lead = hit->Get_fast_lead_time();
                int64_t fast_lead_epoch = hit->Get_fast_lead_epoch();

                // Per-diamond histograms
                if (h1_lisafast_slowToT_Diamond[layer][x][y])
                    h1_lisafast_slowToT_Diamond[layer][x][y]->Fill(slow_ToT);

                if (h1_lisafast_fastToT_Diamond[layer][x][y])
                    h1_lisafast_fastToT_Diamond[layer][x][y]->Fill(fast_ToT);

                if (h1_lisafast_energy_Diamond[layer][x][y])
                    h1_lisafast_energy_Diamond[layer][x][y]->Fill(energy);

                if (h2_lisafast_fast_v_slow_Diamond[layer][x][y])
                    h2_lisafast_fast_v_slow_Diamond[layer][x][y]->Fill(slow_ToT, fast_ToT);

                if (h1_lisafast_abs_time_Diamond[layer][x][y])
                    h1_lisafast_abs_time_Diamond[layer][x][y]->Fill(fast_lead_epoch + fast_lead);

                // Layer-summed histograms
                if (h1_lisafast_slowToT_Diamond_layer[layer])
                    h1_lisafast_slowToT_Diamond_layer[layer]->Fill(slow_ToT);

                if (h1_lisafast_fastToT_Diamond_layer[layer])
                    h1_lisafast_fastToT_Diamond_layer[layer]->Fill(fast_ToT);

                if (h1_lisafast_energy_Diamond_layer[layer])
                    h1_lisafast_energy_Diamond_layer[layer]->Fill(energy);

                // ================================================
                // Event-based Diamond-Diamond coincidences
                // ================================================
                int ref_layer = std::get<0>(dt_reference_diamond);
                int ref_x = std::get<1>(dt_reference_diamond);
                int ref_y = std::get<2>(dt_reference_diamond);

                // Do not process coincidences if no reference diamond is configured
                bool current_is_reference = (hit->Get_layer() == ref_layer && x == ref_x && y == ref_y);

                if (nHits >= 2 && ref_layer > 0 && !current_is_reference)
                {
                    for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++)
                    {
                        if (ihit2 == ihit) continue;

                        LisaFastCalData* hit2 = (LisaFastCalData*)fHitLisaFast->At(ihit2);

                        if (!hit2 || hit2->Get_detector_type() != 1) continue;

                        // Check whether hit2 is the reference Diamond
                        if (hit2->Get_layer() != ref_layer ||
                            hit2->Get_x() != ref_x ||
                            hit2->Get_y() != ref_y)
                            continue;

                        double fast_lead_ref = hit2->Get_fast_lead_time();
                        double energy_ref = hit2->Get_energy();

                        double dt = fast_lead - fast_lead_ref;

                        // Per-diamond histograms
                        if (h1_lisafast_deltaT_Diamond[layer][x][y]) h1_lisafast_deltaT_Diamond[layer][x][y]->Fill(dt);

                        if (h2_lisafast_deltaT_vs_energy_Diamond[layer][x][y]) h2_lisafast_deltaT_vs_energy_Diamond[layer][x][y]->Fill(energy, dt);

                        // Global histograms
                        h1_lisafast_deltaT_coin_Diamond->Fill(dt);
                        h2_lisafast_deltaT_vs_energy_coin_Diamond->Fill(energy, dt);
                        h2_E1_vs_E2_deltaT_coin_Diamond->Fill(energy, energy_ref);
                    }
                }

                // ================================================
                // Diamond-Diamond time-window coincidences
                // ================================================

                double run_time = hit->Get_run_time();

                bool has_reference = (ref_layer > 0);

                for (auto hit_coin = coin_hits_Diamond.begin();
                    hit_coin != coin_hits_Diamond.end(); )
                {
                    // Remove hits outside the coincidence window
                    if ((run_time - hit_coin->Get_run_time()) > coin_window_ns)
                    {
                        hit_coin = coin_hits_Diamond.erase(hit_coin);
                        continue;
                    }

                    int layer_coin = hit_coin->Get_layer();
                    int x_coin = hit_coin->Get_x();
                    int y_coin = hit_coin->Get_y();

                    int layer_coin_idx = layer_coin - 1;

                    // Check previous hit coordinates
                    if (layer_coin_idx < 0 ||
                        layer_coin_idx >= (int)h1_lisafast_dTw_Diamond.size() ||
                        x_coin < 0 || x_coin >= (int)h1_lisafast_dTw_Diamond[layer_coin_idx].size() ||
                        y_coin < 0 || y_coin >= (int)h1_lisafast_dTw_Diamond[layer_coin_idx][x_coin].size())
                    {
                        ++hit_coin;
                        continue;
                    }

                    double time_coin = hit_coin->Get_run_time();
                    double energy_coin = hit_coin->Get_energy();

                    bool same_diamond = (layer == layer_coin && x == x_coin && y == y_coin);
                    bool previous_is_reference = (layer_coin == ref_layer && x_coin == ref_x && y_coin == ref_y);
                    bool is_coincidence = false;

                    double dt = 0.;
                    double energy_other = 0.;
                    double energy_ref = 0.;

                    int other_layer = -1;
                    int other_x = -1;
                    int other_y = -1;

                    if (has_reference)
                    {
                        if (current_is_reference && !previous_is_reference)
                        {
                            is_coincidence = true;
                            dt = time_coin - run_time;

                            energy_ref = energy;
                            energy_other = energy_coin;

                            other_layer = layer_coin_idx;
                            other_x = x_coin;
                            other_y = y_coin;
                        }
                        else if (previous_is_reference && !current_is_reference)
                        {
                            is_coincidence = true;
                            dt = run_time - time_coin;

                            energy_other = energy;
                            energy_ref = energy_coin;

                            other_layer = layer;
                            other_x = x;
                            other_y = y;
                        }
                    }
                    else if (!same_diamond)
                    {
                        is_coincidence = true;
                        dt = run_time - time_coin;

                        energy_other = energy;
                        energy_ref = energy_coin;

                        other_layer = layer;
                        other_x = x;
                        other_y = y;
                    }

                    if (is_coincidence && std::abs(dt) < coin_window_ns)
                    {
                        // Global histograms
                        h1_lisafast_dTw_coin_Diamond->Fill(dt);
                        h2_lisafast_dTw_vs_energy_coin_Diamond->Fill(energy_other, dt);
                        h2_E1_vs_E2_dTw_coin_Diamond->Fill(energy_other, energy_ref);

                        // Individual histogram of the non-reference pixel
                        if (h1_lisafast_dTw_Diamond[other_layer][other_x][other_y]) h1_lisafast_dTw_Diamond[other_layer][other_x][other_y]->Fill(dt);

                        if (h2_lisafast_dTw_vs_energy_Diamond[other_layer][other_x][other_y]) h2_lisafast_dTw_vs_energy_Diamond[other_layer][other_x][other_y]->Fill(energy_other, dt);

                        // Without a reference, also fill the previous diamond
                        // with the opposite time difference
                        if (!has_reference)
                        {
                            if (h1_lisafast_dTw_Diamond[layer_coin_idx][x_coin][y_coin])h1_lisafast_dTw_Diamond[layer_coin_idx][x_coin][y_coin]->Fill(-dt);

                            if (h2_lisafast_dTw_vs_energy_Diamond[layer_coin_idx][x_coin][y_coin])h2_lisafast_dTw_vs_energy_Diamond[layer_coin_idx][x_coin][y_coin]->Fill(energy_coin, -dt);
                        }
                    }

                    ++hit_coin;
                }

                // Store current hit for future cross-event coincidences
                coin_hits_Diamond.push_back(*hit);

                continue;
            }

            // ================================================
            // LaBr hits
            // ================================================
            if (hit->Get_detector_type() != 0 || number_labr_detectors <= 0) continue;           
            //c4LOG(info, "Slow down");
            double slow_ToT1 = hit->Get_slow_ToT();
            double fast_ToT1 = hit->Get_fast_ToT();
            double energy1 = hit->Get_energy();
            double fast_lead1 = hit->Get_fast_lead_time();
            int64_t fast_lead_epoch = hit->Get_fast_lead_epoch();
            double run_time = hit->Get_run_time();

            int detector_id1 = hit->Get_detector_id();
            event_multiplicity_LaBr++;
            fired_LaBr_detectors.insert(detector_id1);

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
                    if (!hit2 || hit2->Get_detector_type() != 0)continue;
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
        if (number_labr_detectors > 0)
        {
            h1_lisafast_event_multiplicity_LaBr->Fill(event_multiplicity_LaBr);
            h1_lisafast_detector_multiplicity_LaBr->Fill(fired_LaBr_detectors.size());
        }

        if (number_diamond_detectors > 0)
        {
            h1_lisafast_event_multiplicity_Diamond->Fill(event_multiplicity_Diamond);
            h1_lisafast_detector_multiplicity_Diamond->Fill(fired_Diamond_detectors.size());
        }

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
