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
#include "LisaHit2Histo.h"
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
    // ,   lisaHistoArray(new  std::vector<std::vector<LisaHistoItem>>)
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
    // delete lisaHistoArray;
    delete frsHitArray;
    delete multihitArray;
}

InitStatus LisaHit2Histo::Init()
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

    lisaHistoArray.resize(1 + std::min(febex_gates.size(), FrsGates.size()));

    if (lisaHistoArray.size() > 0)
    {
        mgr->RegisterAny("LisaHistoData_NoGate", lisaHistoArray.at(0), !fOnline);

        for (int i = 0; i < lisaHistoArray.size(); i++)
        {
            std::string branchName = "LisaHistoData_" + FrsGates.at(i)->GetName();
            mgr->RegisterAny(branchName.c_str(), lisaHistoArray.at(i+1), !fOnline);
        }
    }
    
    mgr->RegisterAny("LisaHitData", lisaHitArray, !fOnline);

    layer_number = lisa_config->NLayers();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();

    gate_number = febex_gates.size();
    mwd_gate_number = mwd_gates.size();

    excluded = lisa_config->GetExcludedChannels();

    // LISA energy
    energy_layer.resize(layer_number);
    energy_MWD_layer.resize(layer_number);

    // ::: GATED QUANTITIES

    // --- FRS gated on FRS quantities
    Z21_passed.resize(FrsGates.size());
    Z41_passed.resize(FrsGates.size());
    Z42_passed.resize(FrsGates.size());
    AoQ_s1s2_passed.resize(FrsGates.size());
    AoQ_s2s4_passed.resize(FrsGates.size());
    dEdeg_z41_passed.resize(FrsGates.size());

    Z21_selected_passed.resize(FrsGates.size());
    Z42_selected_passed.resize(FrsGates.size());
    AoQ_s1s2_passed.resize(FrsGates.size());
    AoQ_s2s4_passed.resize(FrsGates.size());

    // --- LISA - febex
    energy_layer_gated.resize(gate_number);
    for (int g = 0; g < gate_number; g++) 
    {   
        energy_layer_gated[g].resize(layer_number);
    }
    // --- LISA - MWD
    energy_MWD_layer_gated.resize(mwd_gate_number);
    for (int g = 0; g < mwd_gate_number; g++) 
    {   
        energy_MWD_layer_gated[g].resize(layer_number);
    }


    // cej:: commented all this out to stop errors
    

    return kSUCCESS;
}


void LisaHit2Histo::Exec(Option_t* option)
{
    
    // cej commenting all this out to prevent errors 
    for (int i = 0; i < lisaHistoArray.size(); i++) lisaHistoArray.at(i)->clear();
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
    std::vector<Float_t> Z21_mhtdc = multihitItem.Get_ID_z21_mhtdc();
    std::vector<Float_t> Z41_mhtdc = multihitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> Z42_mhtdc = multihitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> Z21_selected_mhtdc = multihitItem.Get_ID_z21_selected_mhtdc();
    std::vector<Float_t> Z42_selected_mhtdc = multihitItem.Get_ID_z42_selected_mhtdc();
    std::vector<Float_t> AoQ_s1s2_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_mhtdc();
    std::vector<Float_t> AoQ_s1s2_selected_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_selected_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_mhtdc(); // use the selected quantities
    std::vector<Float_t> AoQ_s2s4_selected_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_selected_mhtdc();
    std::vector<Float_t> beta_i = multihitItem.Get_ID_beta_s1s2_mhtdc();
    std::vector<Float_t> beta_f = multihitItem.Get_ID_beta_s2s4_mhtdc();

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

    
    // --- FRS gated on FRS quantities
    if (!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            // Z21 and AoQs1s2 with s1s2 gates
            for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
            {
                
                if (FrsGates[gate]->PassedS1S2(Z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
                {
                    Z21_passed[gate].emplace_back(Z21_mhtdc.at(i));
                    AoQ_s1s2_passed[gate].emplace_back(AoQ_s1s2_mhtdc.at(i));
                }
            }

            // z21 and AoQ selected with s1s2 gates
            for (int i = 0; i < AoQ_s1s2_selected_mhtdc.size(); i++)
            {
                
                if (FrsGates[gate]->PassedS1S2(Z21_selected_mhtdc.at(i), x2_position, AoQ_s1s2_selected_mhtdc.at(i)))
                {
                    Z21_selected_passed[gate].emplace_back(Z21_selected_mhtdc.at(i));
                    AoQ_s1s2_selected_passed[gate].emplace_back(AoQ_s1s2_selected_mhtdc.at(i));
                }
            }

            // z41, z42, aoqs2s4 and dEg with s2s4 gates
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {
                if (FrsGates[gate]->PassedS2S4(Z41_mhtdc.at(i), Z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
                    Z41_passed[gate].emplace_back(Z41_mhtdc.at(i));
                    Z42_passed[gate].emplace_back(Z42_mhtdc.at(i));
                    AoQ_s2s4_passed[gate].emplace_back(AoQ_s2s4_mhtdc.at(i));
                    dEdeg_z41_passed[gate].emplace_back(dEdeg_z41_mhtdc.at(i));
                }
            }

            // z42, aoqs2s4 selected with s12s4 gates
            for (int i = 0; i < AoQ_s2s4_selected_mhtdc.size(); i++)
            {
                if (FrsGates[gate]->PassedS2S4(Z41_mhtdc.at(i), Z42_selected_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_selected_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
                    Z42_selected_passed[gate].emplace_back(Z42_selected_mhtdc.at(i));
                    AoQ_s2s4_selected_passed[gate].emplace_back(AoQ_s2s4_selected_mhtdc.at(i));
                }
            }

            // Full seq gate (S1S2S4)
            if ( Z21_passed[gate].size() > 0 && Z41_passed[gate].size() > 0) 
            {

                for ( int i = 0; i < Z21_passed[gate].size(); i++)
                {
                    Z21_s1s2s4_passed[gate].emplace_back(Z21_mhtdc.at(i));
                    AoQs1s2_s1s2s4_passed[gate].emplace_back(AoQ_s1s2_mhtdc.at(i));

                }

                for ( int j = 0; j < Z41_passed[gate].size(); j++)
                {
                    
                    Z41_s1s2s4_passed[gate].emplace_back(Z41_mhtdc.at(j));
                    Z42_s1s2s4_passed[gate].emplace_back(Z42_mhtdc.at(j));
                    AoQs2s4_s1s2s4_passed[gate].emplace_back(AoQ_s2s4_mhtdc.at(j));

                }
            }

            if ( Z21_selected_passed[gate].size() > 0 && Z42_selected_passed[gate].size() > 0) 
            {
                
                for ( int i = 0; i < Z21_selected_passed[gate].size(); i++)
                {
                    AoQs1s2_s1s2s4_selected_passed[gate].emplace_back(AoQ_s1s2_selected_mhtdc.at(i));
                    Z21_s1s2s4_selected_passed[gate].emplace_back(Z21_selected_mhtdc.at(i));

                }

                for ( int j = 0; j < Z42_selected_passed[gate].size(); j++)
                {
                    
                    Z42_s1s2s4_selected_passed[gate].emplace_back(Z42_selected_mhtdc.at(j));
                    AoQs2s4_s1s2s4_selected_passed[gate].emplace_back(AoQ_s2s4_selected_mhtdc.at(j));

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
            int layer = lisaCalItem.Get_layer_id();
            int xpos = lisaCalItem.Get_xposition();
            int ypos = lisaCalItem.Get_yposition();
            float thickness = lisaCalItem.Get_thickness();
            std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer, std::make_pair(xpos, ypos) );

            // Extrapolate TPC position on LISA
            Float_t dist_LISA_focS2 = 1930 + 153 + (layer-1) * 4.8 + dist_focS2_TPC22;
            Float_t x_lisa_tpc22_23 = (a_focs2 / 1000. * dist_LISA_focS2) + x_focs2;
            Float_t y_lisa_tpc22_23 = (b_focs2 / 1000. * dist_LISA_focS2) + y_focs2;

            // ::: Energy data
            float energy_LISA_febex = lisaCalItem.Get_energy_GM();
            float energy_LISA_MWD = lisaCalItem.Get_energy_MWD_GM();

            // Exclude channel before filling layers
            if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

            energy_layer[layer-1].emplace_back(energy_LISA_febex);
            energy_MWD_layer[layer-1].emplace_back(energy_LISA_MWD);

   
            // ::: LISA-FRS gates applied on LISA 
            // ::: Febex
            pair_count = std::min(febex_gates.size(), FrsGates.size());
            for (int pair = 0; pair < pair_count; pair++)  
            {
                for (int l = 0; l < layer_number; l++) 
                {
                    // Check condition on Febex Gate
                    if (energy_layer_gated[pair][l].size() == 0) break; 

                    // Loop for sequential gate S1S2S4
                    if ( Z21_passed[pair].size() > 0 && Z41_passed[pair].size() > 0 ) 
                    {
                        for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                        {
                            // Febex with condition of trigger on sci41 (TPAT 2)
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) energy_layer_gated[pair][l].emplace_back(energy_layer.at(j));   
                        }

                    }
                        
                }
            }
            // ::: MWD 
            int pair_count_MWD = std::min(mwd_gates.size(), FrsGates.size());
            for (int pair = 0; pair < pair_count_MWD; pair++)  
            {
                for (int l = 0; l < layer_number; l++) 
                {
                    // Check condition
                    if (energy_MWD_layer_gated[pair][l].size() == 0) break;

                    // Loop for sequential gate S1S2S4
                    if ( Z21_passed[pair].size() > 0 && Z41_passed[pair].size() > 0 ) 
                    {
                        
                        for ( int j = 0; j < energy_MWD_layer_gated[pair][l].size(); j++)
                        {
                            // MWD with condition of trigger on sci41 (TPAT 2)
                            if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) energy_MWD_layer_gated[pair][l].emplace_back(energy_MWD_layer.at(j));   
                        
                        }
                                        
                    }
                }
            } 
            //............................
  

            auto & nongated_entry = lisaHistoArray.at(0)->emplace_back();
            nongated_entry.SetNonGated(
                AoQ_s1s2_mhtdc,
                AoQ_s2s4_mhtdc,
                AoQ_s1s2_selected_mhtdc,
                AoQ_s2s4_selected_mhtdc,
                Z21_mhtdc,
                Z41_mhtdc,
                Z42_mhtdc ,
                Z21_selected_mhtdc, 
                Z42_selected_mhtdc,
                energy_layer,
                energy_MWD_layer
                );

            for (int gate = 0; gate < FrsGates.size(); gate++)
            {
                auto & gated_entry = lisaHistoArray.at(gate)->emplace_back();
                gated_entry.SetGated(
                    AoQ_s1s2_passed[gate],
                    AoQs1s2_s1s2s4_passed[gate],
                    AoQs2s4_s1s2s4_passed[gate],
                    Z21_passed[gate],
                    Z21_s1s2s4_passed[gate],
                    Z42_s1s2s4_passed[gate],
                    AoQ_s1s2_selected_passed[gate],
                    AoQs1s2_s1s2s4_selected_passed[gate],
                    AoQs2s4_s1s2s4_selected_passed[gate],
                    Z21_selected_passed[gate],
                    Z21_s1s2s4_selected_passed[gate],
                    Z42_s1s2s4_selected_passed[gate],
                    energy_layer_gated[gate],
                    energy_MWD_layer_gated[gate]
                    );
            }



            //c4LOG(info, " END of subevent");

        }
    }


    //c4LOG(info, " LISA end of event");
}

void LisaHit2Histo::FinishEvent()
{
    
    for (int l = 0; l < layer_number; l++)
    {
        energy_layer[l].clear();
        energy_MWD_layer[l].clear();
    }

    for (int g = 0; g < energy_layer_gated.size(); g++)
    {
        for (int l = 0; l < energy_layer_gated[g].size(); l++)
        {
            energy_layer_gated[g][l].clear();
        }
    }

    for (int g = 0; g < energy_MWD_layer_gated.size(); g++)
    {
        for (int l = 0; l < energy_MWD_layer_gated[g].size(); l++)
        {
            energy_MWD_layer_gated[g][l].clear();
        }
    }

    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
 
        AoQ_s2s4_passed[gate].clear();
        dEdeg_z41_passed[gate].clear(); 
        AoQs1s2_s1s2s4_passed[gate].clear();
        AoQs2s4_s1s2s4_passed[gate].clear();
        Z21_passed[gate].clear();
        Z41_passed[gate].clear();
        Z42_passed[gate].clear();
        Z21_s1s2s4_passed[gate].clear();
        Z42_s1s2s4_passed[gate].clear();
        AoQ_s1s2_selected_passed[gate].clear();
        AoQs1s2_s1s2s4_selected_passed[gate].clear();
        AoQs2s4_s1s2s4_selected_passed[gate].clear();
        Z21_selected_passed[gate].clear();
        Z42_s1s2s4_selected_passed[gate].clear();
    }



    
}

void LisaHit2Histo::FinishTask()
{
}