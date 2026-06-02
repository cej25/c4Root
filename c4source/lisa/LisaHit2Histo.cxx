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
 *                      E.M. Gandolfo, C.E. Jones                             *
 *                              01.06.26                                      *
 ******************************************************************************/
// This task writes on a tree part of the the data coming from the FRS-LISA correlation analysis.
// Future project is to include the full correlation data as well as the nearline analysis from lisa.

// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TString.h"

// c4
#include "LisaCal2Hit.h"
#include "FrsHitData.h"
#include "LisaCalData.h"
#include "c4Logger.h"
#include "THttpServer.h"
#include "TCanvas.h"
#include "EventHeader.h"
#include "AnalysisTools.h"

// atima
#ifdef WITH_ATIMA
    #include "Atima.h"
#endif

// ROOT
#include "TClonesArray.h"
#include "TMath.h"
#include <TMacro.h>
#include <vector>
#include <iostream>
#include <TROOT.h>
#include <chrono>
#include <numeric>
#include "TVector.h"
#include <cmath>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TRandom.h"
#include <string>
#include "TColor.h"
#include "TStyle.h"

LisaHit2Histo::LisaHit2Histo()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaAnaArray(nullptr)
    ,   lisaCalArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   multihitArray(nullptr)
    ,   lisaHistoArray(new std::vector<LisaHistoItem>)

{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();

    frs = frs_config->FRS(); 
    id = frs_config->ID();  
}

LisaHit2Histo::LisaHit2Histo(std::vector<FrsGate*> fg)
    : LisaHit2Histo("LisaHit2Histo")
{
    FrsGates = fg;
}

LisaHit2Histo::LisaHit2Histo(std::vector<LisaGate*> lg)
    : LisaHit2Histo("LisaHit2Histo")
{
    for (auto & gate : lg) 
    {
        if (gate->GetType() == "energy") febex_gates.emplace_back(gate); 
        else if (gate->GetType() == "energy_mwd") mwd_gates.emplace_back(gate);
    }
}

LisaHit2Histo::LisaHit2Histo(std::vector<FrsGate*> fg, std::vector<LisaGate*> lg)
    : LisaHit2Histo("LisaHit2Histo")
{
    FrsGates = fg;
    std::cout << "SIZE OF FRS GATES: " << FrsGates.size() << std::endl;
    for (int i = 0; i < FrsGates.size(); i++)
    {
        std::cout << FrsGates.at(i)->GetName() << std::endl;
    }
    
    std::cout << "SIZE OF LISA FEBEX+MWD GATES: " << lg.size() << std::endl;
    for (int i = 0; i < lg.size(); i++)
    {
        std::cout << lg.at(i)->GetName() << std::endl;
    }

    for (auto & gate : lg) 
    {
        if (gate->GetType() == "energy") febex_gates.emplace_back(gate); 
        else if (gate->GetType() == "energy_mwd") mwd_gates.emplace_back(gate);
    }
}

LisaHit2Histo::~LisaHit2Histo()
{
    delete lisaArray;
    delete lisaAnaArray;
    delete lisaCalArray;
    delete lisaHistoArray;
    delete frsHitArray;
    delete multihitArray;
}

InitStatus LisaCal2Hit::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");

    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");
    
    mgr->RegisterAny("LisaHitData", lisaHitArray, !fOnline);

    layer_number = lisa_config->NLayers();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    auto const & detector_mapping = lisa_config->Mapping();

    gate_number = febex_gates.size();
    mwd_gate_number = mwd_gates.size();

    excluded = lisa_config->GetExcludedChannels();

    // ::: Gates quantities

    // --- FRS gated quantities

    // ::: Gates FRS applied on FRS :::
    if (!FrsGates.empty())
    {
        // S1-S2 gate
        h2_Z21_vs_AoQs1s2_s1s2_correlated.resize(FrsGates.size());
        // S1S2S4 gate (full sequential gate)
        h2_Z21_vs_AoQs1s2_s1s2s4_correlated.resize(FrsGates.size());
        h2_Z41_vs_AoQs2s4_s1s2s4_correlated.resize(FrsGates.size());
        h2_Z42_vs_AoQs2s4_s1s2s4_correlated.resize(FrsGates.size());

        
        for (int gate_frs = 0; gate_frs < FrsGates.size(); gate_frs++)
        {
      
            // S1S2 gated on S1S2
            h2_Z21_vs_AoQs1s2_s1s2_correlated[gate_frs] = new TH2F(Form("h2_Z21_vs_AoQs1s2_s1s2_correlated_gate_%i",gate_frs),
                                                            Form("Z21 vs AoQs1s2 - s1s2 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);


            // S1S2 gated on S1S2S4
            h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate_frs] = new TH2F(Form("h2_Z21_vs_AoQs1s2_s1s2s4_correlated_gate_%i",gate_frs),
                                                            Form("Z21 vs AoQs1s2 - s1s2s4 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);


            // S2S4 gated on S1S2S4
            h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate_frs] = new TH2F(Form("h2_Z41_vs_AoQs2s4_s1s2s4_correlated_gate_%i",gate_frs),
                                                            Form("Z41 vs AoQs2s4 - s1s2s4 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);


            h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate_frs] = new TH2F(Form("h2_Z42_vs_AoQs2s4_s1s2s4_correlated_gate_%i",gate_frs),
                                                            Form("Z42 vs AoQs2s4 - s1s2s4 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);
    
        }
    }


    mh_counter_passed_s1s2_seq = new int*[pair_count];
    mh_counter_passed_s2s4_seq = new int*[pair_count];
    for (int pair = 0; pair < pair_count; pair++)
    {   
        mh_counter_passed_s1s2_seq[pair] = new int[layer_number];
        mh_counter_passed_s2s4_seq[pair] = new int[layer_number];
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq[pair][i] = 0;
            mh_counter_passed_s2s4_seq[pair][i] = 0;
        }
    }

    mh_counter_passed_s1s2_seq_mwd = new int*[pair_count_MWD];
    mh_counter_passed_s2s4_seq_mwd = new int*[pair_count_MWD];
    for (int pair = 0; pair < pair_count; pair++)
    {   
        mh_counter_passed_s1s2_seq_mwd[pair] = new int[layer_number];
        mh_counter_passed_s2s4_seq_mwd[pair] = new int[layer_number];
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq_mwd[pair][i] = 0;
            mh_counter_passed_s2s4_seq_mwd[pair][i] = 0;
        }
    }
    //c4LOG(info, "::::::::::::::::::end of counters ");
   
    energy_layer.resize(layer_number);
    energy_MWD_layer.resize(layer_number);

    energy_xy_gated.resize(gate_number);
    energy_layer_gated.resize(gate_number);
    for (int g = 0; g < gate_number; g++) 
    {   
        energy_layer_gated[g].resize(layer_number);
        energy_xy_gated[g].resize(layer_number);
        for (int l = 0; l < layer_number; l++) 
        {
            energy_xy_gated[g][l].resize(xmax);
            for (int x = 0; x < xmax; x++) 
            {
                energy_xy_gated[g][l][x].resize(ymax);
            }
        }
    }
    //c4LOG(info, "::::::::::::::::::end of energy gated febex ");
   
    energy_MWD_xy_gated.resize(mwd_gate_number);
    energy_MWD_layer_gated.resize(mwd_gate_number);
    for (int g = 0; g < mwd_gate_number; g++) 
    {   
        energy_MWD_layer_gated[g].resize(layer_number);
        energy_MWD_xy_gated[g].resize(layer_number);
        for (int l = 0; l < layer_number; l++) 
        {
            energy_MWD_xy_gated[g][l].resize(xmax);
            for (int x = 0; x < xmax; x++) 
            {
                energy_MWD_xy_gated[g][l][x].resize(ymax);
            }
        }
    }

    z21_passed.resize(FrsGates.size());
    AoQ_s1s2_passed.resize(FrsGates.size());
    z41_passed.resize(FrsGates.size());
    z42_passed.resize(FrsGates.size());
    AoQ_s2s4_passed.resize(FrsGates.size());
    dEdeg_z41_passed.resize(FrsGates.size());

    return kSUCCESS;
}


void LisaCal2Hit::Exec(Option_t* option)
{
    

    lisaHistoArray->clear();
    // -> Reject events without both subsystems <-
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0 || multihitArray->size() <= 0) return;  // frs, lisa and travmus subevent exists
    
    const auto & frsHitItem = frsHitArray->at(0);
    const auto & multihitItem = multihitArray->at(0);

    // ::: FRS WR
    Int_t count_wr = 0;
    wr_FRS = frsHitItem.Get_wr_t();
    wr_travMUSIC = frsHitItem.Get_travmus_wr_t();

    // ::: Total multiplicity of lisa
    int lisa_total_multiplicity = 0;

    // ::: MUSIC energies
    energy_MUSIC_21 = frsHitItem.Get_music21_dE();
    energy_MUSIC_41 = frsHitItem.Get_music41_dE(); 
    energy_MUSIC_42 = frsHitItem.Get_music42_dE();
    // ::: FRS data
    std::vector<Float_t> z21_mhtdc = multihitItem.Get_ID_z21_mhtdc();
    std::vector<Float_t> z41_mhtdc = multihitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> z42_mhtdc = multihitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> z21_sected_mhtdc = multihitItem.Get_ID_z21_selected_mhtdc();
    std::vector<Float_t> z42_sected_mhtdc = multihitItem.Get_ID_z42_selected_mhtdc();
    std::vector<Float_t> AoQ_s1s2_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_mhtdc();
    std::vector<Float_t> AoQ_s1s2_selected_mhtdc = multiHitItem.Get_ID_AoQ_corr_s1s2_selected_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_mhtdc(); // use the selected quantities
    std::vector<Float_t> AoQ_s2s4_selected_mhtdc = multiHitItem.Get_ID_AoQ_corr_s2s4_selected_mhtdc();
    beta_i = multihitItem.Get_ID_beta_s1s2_mhtdc();
    beta_f = multihitItem.Get_ID_beta_s2s4_mhtdc();

    if (AoQ_s2s4_mhtdc.size() > 0) aoq++;
    std::vector<Float_t> dEdeg_z41_mhtdc = multihitItem.Get_ID_dEdeg_z41_mhtdc();
    Float_t x2_position = frsHitItem.Get_ID_x2();
    Float_t x4_position = frsHitItem.Get_ID_x4();
    Float_t sci42e = frsHitItem.Get_sci_e_42();

    // For position calculation
    Float_t a_focs2 = frsHitItem.Get_tpc_angle_x_s2_foc_22_23();
    Float_t b_focs2 = frsHitItem.Get_tpc_angle_y_s2_foc_22_23();
    Float_t x_focs2 = frsHitItem.Get_tpc_x_s2_foc_22_23();
    Float_t y_focs2 = frsHitItem.Get_tpc_y_s2_foc_22_23();
    Float_t dist_focS2_TPC22 = frs->dist_focS2 - frs->dist_TPC22;

    if (beta_i.size()==0) return;
    for (int i = 0; i < beta_i.size(); i++)
    {
        if (beta_i[i] <= 0. || beta_i[i] >= 1.) return;
    }


    // ::: Vectors for FRS gated data
    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
        //if (AoQ_s1s2_mhtdc.size()!=1 || AoQ_s2s4_mhtdc.size() !=1 )break; // this is a quick fix to reject all the events with multihits - redundant
        for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
        {
            
            if (FrsGates[gate]->PassedS1S2(z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
            {
                z21_passed[gate].emplace_back(z21_mhtdc.at(i));
                AoQ_s1s2_passed[gate].emplace_back(AoQ_s1s2_mhtdc.at(i));
            }
        }

        // for (int i = 0; i < AoQ_s1s2_selected_mhtdc.size(); i++)
        // {
            
        //     if (FrsGates[gate]->PassedS1S2(z21_selected_mhtdc.at(i), x2_position, AoQ_s1s2_selected_mhtdc.at(i)))
        //     {
        //         z21_selected_passed[gate].emplace_back(z21_selected_mhtdc.at(i));
        //         AoQ_s1s2_selected_passed[gate].emplace_back(AoQ_s1s2_selected_mhtdc.at(i));
        //     }
        // }

        for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
        {
            if (FrsGates[gate]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
            {
                z41_passed[gate].emplace_back(z41_mhtdc.at(i));
                z42_passed[gate].emplace_back(z42_mhtdc.at(i));
                AoQ_s2s4_passed[gate].emplace_back(AoQ_s2s4_mhtdc.at(i));
                dEdeg_z41_passed[gate].emplace_back(dEdeg_z41_mhtdc.at(i));
                //add _selected quantities
            }
        }

        // for (int i = 0; i < AoQ_s2s4_selected_mhtdc.size(); i++)
        // {
        //     if (FrsGates[gate]->PassedS2S4(z41_selected_mhtdc.at(i), z42_selected_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_selected_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
        //     {
        //         z41_selected_passed[gate].emplace_back(z41_selected_mhtdc.at(i));
        //         z42_selected_passed[gate].emplace_back(z42_selected_mhtdc.at(i));
        //         AoQ_s2s4_selected_passed[gate].emplace_back(AoQ_s2s4_selected_mhtdc.at(i));
        //         dEdeg_z41_passed[gate].emplace_back(dEdeg_z41_mhtdc.at(i));
        //         //add _selected quantities
        //     }
        // }
    }

    // TOTREE: 
    // -- frs quantities for multihitmap
    // AoQ_s1s2_mhtdc
    // AoQ_s2s4_mhtdc
    // AoQ_s1s2_selected_mhtdc
    // AoQ_s2s4_selected_mhtdc
    // 
    // FRS gated quantities
    // AoQs1s2_s1s2_mhtdc  -- //this is theAo!of s1s2 gated on s1s2 gate
    // AoQs1s2_s1s2s4_mhtdc -- //this is the same gated on the sequential gate so s1s2s4
    // AoQs2s4_s1s2s4_mhtdc
    // Z21_s1s2_mhtdc
    // Z21_s1s24_mhtdc
    // Z42_s1s2s4_mhtdc

    // AoQs1s2_selected_s1s2_mhtdc  -- //this is theAo!of s1s2 gated on s1s2 gate
    // AoQs1s2_selected_s1s2s4_mhtdc -- //this is the same gated on the sequential gate so s1s2s4
    // AoQs2s4_selected_s1s2s4_mhtdc
    // Z21_selected_s1s2_mhtdc
    // Z21_selected_s1s24_mhtdc
    // Z42_selected_s1s2s4_mhtdc

    // LISA quantities gated on FRS gate (both for normal and _selected quantites)
    // energy_layer
    // energy_layer_gated
    // energy_MWD_layer
    // energy_MWD_layer_gated

    // LISA quantities gated on FRS+LISA gates (both for normal and _selected quantites)
    // energy_layer
    // energy_layer_gated
    // energy_MWD_layer
    // energy_MWD_layer_gated


    // ::: Histos to make into trees
    // I am here
    // Fill FRS histos applied on FRS
    // FRS on FRS
    if (!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            // Loop S1S2
            if ( z21_passed[gate].size() > 0 )
            {
                for ( int i = 0; i < z21_passed[gate].size(); i++)
                {
                    h2_Z21_vs_AoQs1s2_s1s2_correlated[gate]->Fill(AoQ_s1s2_passed[gate].at(i), z21_passed[gate].at(i));
                }
            }
            // Full seq gate (S1S2S4)
            if ( z21_passed[gate].size() > 0 && z41_passed[gate].size() > 0) 
            {
                for ( int i = 0; i < z21_passed[gate].size(); i++)
                {
                    h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate]->Fill( AoQ_s1s2_passed[gate].at(i), z21_passed[gate].at(i));
                }

                for ( int j = 0; j < z41_passed[gate].size(); j++)
                {
                    h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate]->Fill(AoQ_s2s4_passed[gate].at(j), z41_passed[gate].at(j));
                    h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate]->Fill(AoQ_s2s4_passed[gate].at(j), z42_passed[gate].at(j));

                }
            }
        }
    }
    //....................
    // ::: Now loop over lisa data starts
    for (auto const & lisaCalItem : *lisaCalArray)
    {          

        if (lisa_config->MappingLoaded())
        {

            uint64_t EVTno = header->GetEventno();
            float de_dx = lisaCalItem.Get_de_dx_GM();
            int layer_id = lisaCalItem.Get_layer_id();
            int xpos = lisaCalItem.Get_xposition();
            int ypos = lisaCalItem.Get_yposition();
            float thickness = lisaCalItem.Get_thickness();
            multiplicity[layer_id-1]++;
            std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer_id, std::make_pair(xpos, ypos) );

            // Extrapolate TPC position on LISA
            Float_t dist_LISA_focS2 = 1930 + 153 + (layer_id-1) * 4.8 + dist_focS2_TPC22;
            Float_t x_lisa_tpc22_23 = (a_focs2 / 1000. * dist_LISA_focS2) + x_focs2;
            Float_t y_lisa_tpc22_23 = (b_focs2 / 1000. * dist_LISA_focS2) + y_focs2;

            // ::: Energy data
            float energy_LISA_febex = lisaCalItem.Get_energy_GM();
            float energy_LISA_MWD = lisaCalItem.Get_energy_MWD_GM();

            // Exclude channel before filling layers
            if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

            energy_layer[layer-1].emplace_back(energy_LISA_febex);
            energy_MWD_layer[layer-1].emplace_back(energy_LISA_MWD);

            // LISA gates applied on LISA
            // Loop over gates for LISA FEBEX
            for (int g = 0; g < febex_gates.size(); g++)
            {
                if (febex_gates.at(g)->PassedGate(layer, energy_LISA_febex))
                {
                    energy_layer_gated[g][layer-1].push_back(energy_LISA_febex);
                    energy_xy_gated[g][layer-1][xpos][ypos].push_back(energy_LISA_febex);
                }
            }
            int g = 0;
            // Loop over gates for LISA MWD
            g = 0;
            for (auto & gate : mwd_gates)
            {   
                if (gate->PassedGate(layer, energy_LISA_MWD))
                {
                    energy_MWD_layer_gated[g][layer-1].push_back(energy_LISA_MWD);
                    energy_MWD_xy_gated[g][layer-1][xpos][ypos].push_back(energy_LISA_MWD);
                }
                g++;
            }

            // FRS gates applied to LISA -- replace histos with quantities
            if (!FrsGates.empty())
            {
                for (int gate = 0; gate < FrsGates.size(); gate++)
                {    
                    // S1S2 gated
                    if ( z21_passed[gate].size() > 0 )
                    {
                        // Febex
                        h2_LISA_energy_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_febex);
                        h1_LISA_energy_s1s2_gated[gate][layer-1]->Fill(energy_LISA_febex);
                        // MWD
                        h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_MWD);
                        h1_LISA_energy_MWD_s1s2_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                        
                        //Febex and MWD XY channel
                        if ( xpos == lisa_config->xpos_gate && ypos == lisa_config->ypos_gate)
                        {
                            h2_LISA_energy_xy_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_febex);
                            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_MWD);
                            
                            h1_LISA_energy_xy_s1s2_gated[gate][layer-1]->Fill(energy_LISA_febex);
                            h1_LISA_energy_MWD_xy_s1s2_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                        } 
                    }

                    // Sequential
                    if ( z21_passed[gate].size() > 0 && z41_passed[gate].size() > 0) //all vectors of s1s2 have the same size (same for s2s4)
                    {
                        // Febex
                        h2_LISA_energy_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_febex);
                        h1_LISA_energy_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_febex);
                        // MWD
                        h2_LISA_energy_MWD_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_MWD);
                        h1_LISA_energy_MWD_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                        
                        //Febex and MWD XY channel
                        if ( xpos == lisa_config->xpos_gate && ypos == lisa_config->ypos_gate)
                        {
                            h2_LISA_energy_xy_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_febex);
                            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_MWD);
                            
                            h1_LISA_energy_xy_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_febex);
                            h1_LISA_energy_MWD_xy_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                        } 
                    }
                    
                }            
            } 

            // ::: LISA-FRS gates applied on LISA (LISA_FRS Directory)
            //     Histo with no condition on multiplicity and with condition of multiplicity 5
            // ::: Febex
            //pair_count = std::min(febex_gates.size(), FrsGates.size());
            for (int pair = 0; pair < pair_count; pair++)  
            {
                for (int l = 0; l < layer_number; l++) 
                {
                    // Check condition on Febex Gate
                    if (energy_layer_gated[pair][l].size() == 0) break; 

                    // S1 S2 conditions
                    if ( z21_passed[pair].size() > 0 ) 
                    {
                        for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                        {
                            // Febex with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_LISA_s1s2_gated[pair][l]->Fill(energy_layer_gated[pair][l].at(j)); 

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_LISA_s1s2_gated_M5[pair][l]->Fill(energy_layer_gated[pair][l].at(j)); 
                        
                        }

                        for ( int k = 0; k < energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                        {
                            // Febex XY with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_xy_LISA_s1s2_gated[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_xy_LISA_s1s2_gated_M5[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                        }
                    }

                    // Loop for sequential gate S1S2S4
                    if ( z21_passed[pair].size() > 0 && z41_passed[pair].size() > 0 ) 
                    {
                        for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                        {
                            // Febex with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_LISA_s1s2s4_gated[pair][l]->Fill(energy_layer_gated[pair][l].at(j));   

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_layer_gated[pair][l].at(j));   
                        }

                        for ( int k = 0; k < energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                        {
                            // Febex XY with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_xy_LISA_s1s2s4_gated[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_xy_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));                       
                        
                        }
                    }
                        
                }
            }
            // ::: MWD 
            //int pair_count_MWD = std::min(mwd_gates.size(), FrsGates.size());
            
            for (int pair = 0; pair < pair_count_MWD; pair++)  
            {
                for (int l = 0; l < layer_number; l++) 
                {
                    // Check condition on Febex Gate
                    if (energy_MWD_layer_gated[pair][l].size() == 0) break;

                    // Loop for S1S2
                    if ( z21_passed[pair].size() > 0 ) 
                    {
                        for ( int j = 0; j < energy_MWD_layer_gated[pair][l].size(); j++)
                        {
                            // MWD  with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_LISA_s1s2_gated[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));   

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_LISA_s1s2_gated_M5[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));           
                        }

                        for ( int k = 0; k < energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                        {
                            // MWD XY  with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_xy_LISA_s1s2_gated[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_xy_LISA_s1s2_gated_M5[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                                            
                        }                  
                    }

                    // Loop for sequential gate S1S2S4
                    if ( z21_passed[pair].size() > 0 && z41_passed[pair].size() > 0 ) 
                    {
                        
                        for ( int j = 0; j < energy_MWD_layer_gated[pair][l].size(); j++)
                        {
                            // MWD with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_LISA_s1s2s4_gated[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));   

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));                        
                        
                        }

                        for ( int k = 0; k < energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                        {
                            // MWD XY with condition of trigger on sci41 (TPAT 2)
                            if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));                    
                        }
                                        
                    }
                }
            } 
            //............................
  
            auto & entry = lisaHitArray->emplace_back();
            entry.SetAll(
                lisaCalItem.Get_wr_t(),
                lisaCalItem.Get_wr_id(),
                lisaCalItem.Get_board_id(),
                lisaCalItem.Get_layer_id(),
                lisaCalItem.Get_city(),
                lisaCalItem.Get_xposition(),
                lisaCalItem.Get_yposition(),
                x_lisa_tpc22_23,
                y_lisa_tpc22_23,
                lisaCalItem.Get_thickness(),
                lisaCalItem.Get_energy(),
                lisaCalItem.Get_energy_MWD(),
                lisaCalItem.Get_trace_febex(),
                lisaCalItem.Get_trace_x(),
                lisaCalItem.Get_energy_GM(),
                lisaCalItem.Get_energy_MWD_GM(),
                lisaCalItem.Get_de_dx(),
                lisaCalItem.Get_de_dx_GM(),
                lisaCalItem.Get_board_event_time(),
                lisaCalItem.Get_channel_event_time(),
                EVTno,
                lisaCalItem.Get_pileup(),
                //lisaCalItem.Get_pileup_MWD(),
                lisaCalItem.Get_overflow(),
                //lisaCalItem.Get_overflow_MWD(),
 
            );


            //c4LOG(info, " END of subevent");

        }
    }

    //c4LOG(info, " LISA end of event");
}

void LisaCal2Hit::FinishEvent()
{
    //std::cout << "::::: FE 1 " << std::endl;
    for (int pair = 0; pair < pair_count; pair++)
    {
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq[pair][i] = 0;
            mh_counter_passed_s2s4_seq[pair][i] = 0;
        }
    }
    //std::cout << "::::: FE 2 " << std::endl;
    for (int pair = 0; pair < pair_count_MWD; pair++)
    {
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq_mwd[pair][i] = 0;
            mh_counter_passed_s2s4_seq_mwd[pair][i] = 0;
        }
    }
    //std::cout << "::::: FE 3 " << std::endl;
    for (int l = 0; l < layer_number; l++)
    {
        energy_layer[l].clear();
        energy_MWD_layer[l].clear();
    }
    //std::cout << "::::: FE 4 " << std::endl;
    for (int g = 0; g < energy_layer_gated.size(); g++)
    {
        //std::cout << "::::: FE 5 " << std::endl;
        for (int l = 0; l < energy_layer_gated[g].size(); l++)
        {
            //std::cout << "::::: FE 6 " << std::endl;
            energy_layer_gated[g][l].clear();
            //energy_MWD_layer_gated[g][l].clear();
            for (int x = 0; x < energy_xy_gated[g][l].size(); x++)
            {
                //std::cout << "::::: FE 7 " << std::endl;
                for (int y = 0; y < energy_xy_gated[g][l][x].size(); y++)
                {
                    energy_xy_gated[g][l][x][y].clear();
                    //energy_MWD_xy_gated[g][l][x][y].clear();
                }
            }
        }
    }

    //std::cout << "::::: FE 8 " << std::endl;
    for (int g = 0; g < energy_MWD_layer_gated.size(); g++)
    {
        //std::cout << "::::: FE 9 " << std::endl;
        for (int l = 0; l < energy_MWD_layer_gated[g].size(); l++)
        {
            //std::cout << "::::: FE 10 " << std::endl;
            energy_MWD_layer_gated[g][l].clear();
            for (int x = 0; x < energy_MWD_xy_gated[g][l].size(); x++)
            {
                //std::cout << "::::: FE 11 " << std::endl;
                for (int y = 0; y < energy_MWD_xy_gated[g][l][x].size(); y++)
                {
                    energy_xy_gated[g][l][x][y].clear();
                }
            }
        }
    }
    //std::cout << "::::: before vectors " << std::endl;
    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
        z21_passed[gate].clear();
        AoQ_s1s2_passed[gate].clear();
        z41_passed[gate].clear();
        z42_passed[gate].clear();
        AoQ_s2s4_passed[gate].clear();
        dEdeg_z41_passed[gate].clear(); 
    }
}

void LisaCal2Hit::FinishTask()
{
}