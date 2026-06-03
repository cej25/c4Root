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

LisaHit2Histo::LisaHit2Histo(const TString& name, Int_t verbose)
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
    delete lisaHitArray;
    // delete lisaHistoArray;
    delete frsHitArray;
    delete multihitArray;

    //and do I need this?
    //for (auto* v : lisaHistoArray) delete v;
}

InitStatus LisaHit2Histo::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    //lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    //c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");

    lisaHitArray = mgr->InitObjectAs<decltype(lisaHitArray)>("LisaHitData");
    c4LOG_IF(fatal, !lisaHitArray, "Branch LisaHitData not found!");

    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    //c4LOG(info,"A");
    lisaHistoArray.resize(1 + std::min(febex_gates.size(), FrsGates.size()));
    // Do I need this???
    // for (int i = 0; i < (int)lisaHistoArray.size(); i++)
    // {
    //     lisaHistoArray.at(i) = new std::vector<LisaHistoItem>();
    // }


    //c4LOG(info,"AA");
    // if (lisaHistoArray.size() > 0)
    // {
    //     mgr->RegisterAny("LisaHistoData_NoGate", lisaHistoArray.at(0), !fOnline);

    //     for (int i = 0; i < lisaHistoArray.size(); i++)
    //     {
    //         std::string branchName = "LisaHistoData_" + FrsGates.at(i)->GetName();
    //         mgr->RegisterAny(branchName.c_str(), lisaHistoArray.at(i+1), !fOnline);
    //     }
    // }
    //c4LOG(info,"B");

    if (lisaHistoArray.size() > 0)
    {
        mgr->RegisterAny("LisaHistoData_NoGate", lisaHistoArray.at(0), !fOnline);

        for (int i = 0; i < (int)FrsGates.size(); i++)  //  was lisaHistoArray.size()
        {
            std::string branchName = "LisaHistoData_" + FrsGates.at(i)->GetName();
            mgr->RegisterAny(branchName.c_str(), lisaHistoArray.at(i+1), !fOnline); 
        }
    }
    
    //mgr->RegisterAny("LisaHitData", lisaHitArray, !fOnline);

    layer_number = lisa_config->NLayers();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();

    gate_number = febex_gates.size();
    mwd_gate_number = mwd_gates.size();

    excluded = lisa_config->GetExcludedChannels();
    //c4LOG(info,"C");

    // LISA energy
    // energy_layer1.resize(layer_number);
    // energy_MWD_layer.resize(layer_number);

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
    AoQ_s2s4_selected_passed.resize(FrsGates.size());   

    Z41_s1s2s4_passed.resize(FrsGates.size());
    Z21_s1s2s4_selected_passed.resize(FrsGates.size());
    AoQs1s2_s1s2s4_passed.resize(FrsGates.size());
    AoQs2s4_s1s2s4_passed.resize(FrsGates.size());
    Z21_s1s2s4_passed.resize(FrsGates.size());
    Z42_s1s2s4_passed.resize(FrsGates.size());
    AoQ_s1s2_selected_passed.resize(FrsGates.size());
    AoQs1s2_s1s2s4_selected_passed.resize(FrsGates.size());
    AoQs2s4_s1s2s4_selected_passed.resize(FrsGates.size());
    Z42_s1s2s4_selected_passed.resize(FrsGates.size());

    // --- LISA - febex
    // energy_layer_gated.resize(gate_number);
    energy_layer1_gated.resize(gate_number);
    energy_layer2_gated.resize(gate_number);
    energy_layer3_gated.resize(gate_number);
    energy_layer4_gated.resize(gate_number);
    energy_layer5_gated.resize(gate_number);
    
    // for (int g = 0; g < gate_number; g++) 
    // {   
    //     energy_layer_gated[g].resize(layer_number);
    // }
    // --- LISA - MWD
    energy_MWD_layer1_gated.resize(gate_number);
    energy_MWD_layer2_gated.resize(gate_number);
    energy_MWD_layer3_gated.resize(gate_number);
    energy_MWD_layer4_gated.resize(gate_number);
    energy_MWD_layer5_gated.resize(gate_number);

    // for (int g = 0; g < gate_number; g++) 
    // {   
    //     energy_MWD_layer_gated[g].resize(layer_number);
    // }

    int pair_count_init = (int)std::min(febex_gates.size(), FrsGates.size());
    layers_event_gated.resize(pair_count_init);
    xpos_event_gated.resize(pair_count_init);
    ypos_event_gated.resize(pair_count_init);

    
    //c4LOG(info,"D - end of init");

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
    //c4LOG(info,"E - start of exec");

    // ::: MUSIC energies
    energy_MUSIC_21 = frsHitItem.Get_music21_dE();
    energy_MUSIC_41 = frsHitItem.Get_music41_dE(); 
    energy_MUSIC_42 = frsHitItem.Get_music42_dE();

    // ::: FRS data
    std::vector<Float_t> Z21_mhtdc = multihitItem.Get_ID_z21_mhtdc();
    std::vector<Float_t> Z41_mhtdc = multihitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> Z42_mhtdc = multihitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> Z21_selected_mhtdc = multihitItem.Get_ID_z21_selected_mhtdc();
    std::vector<Float_t> Z41_selected_mhtdc = multihitItem.Get_ID_z41_selected_mhtdc();
    std::vector<Float_t> Z42_selected_mhtdc = multihitItem.Get_ID_z42_selected_mhtdc();
    std::vector<Float_t> AoQ_s1s2_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_mhtdc();
    std::vector<Float_t> AoQ_s1s2_selected_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_selected_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_mhtdc(); // use the selected quantities
    std::vector<Float_t> AoQ_s2s4_selected_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_selected_mhtdc();
    std::vector<Float_t> beta_i = multihitItem.Get_ID_beta_s1s2_mhtdc();
    std::vector<Float_t> beta_f = multihitItem.Get_ID_beta_s2s4_mhtdc();

    if (AoQ_s2s4_mhtdc.size() > 0) aoq++;
    std::vector<Float_t> dEdeg_z41_mhtdc = multihitItem.Get_ID_dEdeg_z41_mhtdc();
    //std::vector<Float_t> dEdeg_z41_selected_mhtdc = multihitItem.Get_ID_dEdeg_z41_selected_mhtdc();
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

    //c4LOG(info,"F");

    // --- FRS gated on FRS quantities
    if (!FrsGates.empty())
    {
        //c4LOG(info,"F1");
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            // Z21 and AoQs1s2 with s1s2 gates
            //c4LOG(info,"F2");
            for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
            {
                
                if (FrsGates[gate]->PassedS1S2(Z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
                {
                    Z21_passed[gate].emplace_back(Z21_mhtdc.at(i));
                    AoQ_s1s2_passed[gate].emplace_back(AoQ_s1s2_mhtdc.at(i));
                }
            }
            //c4LOG(info,"F3");
            // z21 and AoQ selected with s1s2 gates
            for (int i = 0; i < AoQ_s1s2_selected_mhtdc.size(); i++)
            {
                
                if (FrsGates[gate]->PassedS1S2(Z21_selected_mhtdc.at(i), x2_position, AoQ_s1s2_selected_mhtdc.at(i)))
                {
                    Z21_selected_passed[gate].emplace_back(Z21_selected_mhtdc.at(i));
                    AoQ_s1s2_selected_passed[gate].emplace_back(AoQ_s1s2_selected_mhtdc.at(i));
                }
            }
            //c4LOG(info,"F4");
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
            //c4LOG(info,"F5");
            //c4LOG(info,"size of aoqs2s4 passed: " << AoQ_s2s4_selected_mhtdc.size());
            // z42, aoqs2s4 selected with s12s4 gates
            for (int i = 0; i < AoQ_s2s4_selected_mhtdc.size(); i++)
            {
                //c4LOG(info,"size of Z41_selected_mhtdc: " << Z41_selected_mhtdc.size());
                //c4LOG(info,"size of Z42_selected_mhtdc: " << Z42_selected_mhtdc.size());
                //c4LOG(info,"size of dEdeg_z41_mhtdc: " << dEdeg_z41_mhtdc.size());
                if (FrsGates[gate]->PassedS2S4(Z41_selected_mhtdc.at(i), Z42_selected_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_selected_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
                    //c4LOG(info,"inner loop");
                    //c4LOG(info,"size of Z41_selected_mhtdc: " << Z41_selected_mhtdc.size());
                    //c4LOG(info,"size of Z42_selected_mhtdc: " << Z42_selected_mhtdc.size());
                    //c4LOG(info,"size of dEdeg_z41_mhtdc: " << dEdeg_z41_mhtdc.size());
                    Z42_selected_passed[gate].emplace_back(Z42_selected_mhtdc.at(i));
                    //c4LOG(info,"z42 filled");

                    AoQ_s2s4_selected_passed[gate].emplace_back(AoQ_s2s4_selected_mhtdc.at(i));
                    //c4LOG(info,"end emplace_back");
                }
            }
            //c4LOG(info,"F6");
            // Full seq gate (S1S2S4)
            if ( Z21_passed[gate].size() > 0 && Z41_passed[gate].size() > 0) 
            {

                for ( int i = 0; i < Z21_passed[gate].size(); i++)
                {
                    Z21_s1s2s4_passed[gate].emplace_back(Z21_mhtdc.at(i));
                    AoQs1s2_s1s2s4_passed[gate].emplace_back(AoQ_s1s2_mhtdc.at(i));

                }

                for ( int j = 0; j < Z42_passed[gate].size(); j++)
                {
                    
                    Z41_s1s2s4_passed[gate].emplace_back(Z41_mhtdc.at(j));
                    Z42_s1s2s4_passed[gate].emplace_back(Z42_mhtdc.at(j));
                    AoQs2s4_s1s2s4_passed[gate].emplace_back(AoQ_s2s4_mhtdc.at(j));

                }
            }
            //c4LOG(info,"F7");
            if ( Z21_selected_passed[gate].size() > 0 && Z42_selected_passed[gate].size() > 0) 
            {
                
                //c4LOG(info,"F8");
                for ( int i = 0; i < Z21_selected_passed[gate].size(); i++)
                {
                    AoQs1s2_s1s2s4_selected_passed[gate].emplace_back(AoQ_s1s2_selected_mhtdc.at(i));
                    Z21_s1s2s4_selected_passed[gate].emplace_back(Z21_selected_mhtdc.at(i));

                }
                //c4LOG(info,"F9");
                //c4LOG(info," size of Z42_selected_passed: " << Z42_selected_passed[gate].size());
                //c4LOG(info," size of Z42_selected_mhtdc: " << Z42_selected_mhtdc.size());

                for ( int j = 0; j < Z42_selected_passed[gate].size(); j++)
                {
                    
                    //c4LOG(info,"F91");
                    Z42_s1s2s4_selected_passed[gate].emplace_back(Z42_selected_mhtdc.at(j));
                    //c4LOG(info,"F92");
                    AoQs2s4_s1s2s4_selected_passed[gate].emplace_back(AoQ_s2s4_selected_mhtdc.at(j));
                    //c4LOG(info,"F93");

                }
            }
        }
    }

    //c4LOG(info,"G");

    //....................
    // ::: Now loop over lisa data starts
    for (auto const & lisaCalItem : *lisaCalArray)
    {          

        if (lisa_config->MappingLoaded())
        {

            uint64_t EVTno = header->GetEventno();
            float de_dx = lisaCalItem.Get_de_dx_GM();
            layer = lisaCalItem.Get_layer_id();
            xpos = lisaCalItem.Get_xposition();
            ypos = lisaCalItem.Get_yposition();

            layers_event.emplace_back(layer);
            xpos_event.emplace_back(xpos);
            ypos_event.emplace_back(ypos);

            float thickness = lisaCalItem.Get_thickness();
            std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer, std::make_pair(xpos, ypos) );

            // Extrapolate TPC position on LISA
            Float_t dist_LISA_focS2 = 1930 + 153 + (layer-1) * 4.8 + dist_focS2_TPC22;
            Float_t x_lisa_tpc22_23 = (a_focs2 / 1000. * dist_LISA_focS2) + x_focs2;
            Float_t y_lisa_tpc22_23 = (b_focs2 / 1000. * dist_LISA_focS2) + y_focs2;

            lisa_total_multiplicity++;
            // ::: Energy data
            float energy_LISA_febex = lisaCalItem.Get_energy_GM();
            float energy_LISA_MWD = lisaCalItem.Get_energy_MWD_GM();

            // Exclude channel before filling layers
            if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

            if (layer == 1) energy_layer1.emplace_back(energy_LISA_febex);
            if (layer == 2) energy_layer2.emplace_back(energy_LISA_febex);
            if (layer == 3) energy_layer3.emplace_back(energy_LISA_febex);
            if (layer == 4) energy_layer4.emplace_back(energy_LISA_febex);
            if (layer == 5) energy_layer5.emplace_back(energy_LISA_febex);
            if (layer == 1) energy_MWD_layer1.emplace_back(energy_LISA_MWD);
            if (layer == 2) energy_MWD_layer2.emplace_back(energy_LISA_MWD);
            if (layer == 3) energy_MWD_layer3.emplace_back(energy_LISA_MWD);
            if (layer == 4) energy_MWD_layer4.emplace_back(energy_LISA_MWD);
            if (layer == 5) energy_MWD_layer5.emplace_back(energy_LISA_MWD);
            

            //...........................
            //c4LOG(info, " END of subevent");

        }

    }
   
    // ::: LISA-FRS gates applied on LISA 
    // ::: Febex
    pair_count = std::min(febex_gates.size(), FrsGates.size());
    
    for (int pair = 0; pair < pair_count; pair++)  
    {
        for (int l = 0; l < layer_number; l++) // CEJ remove at some point, pointless
        {
            // Check condition on Febex Gate
            //if (energy_layer_gated[pair][l].size() == 0) break; 

            // Loop for sequential gate S1S2S4
            if ( Z21_passed[pair].size() > 0 && Z42_passed[pair].size() > 0 ) 
            {
                // Febex with condition of trigger on sci41 (TPAT 2)
                if ((frsHitItem.Get_tpat() & 0b10) && (int)lisaCalArray->size() == 5) 
                {
                    if (l == 0) for (size_t j = 0; j < energy_layer1.size(); j++) energy_layer1_gated[pair].emplace_back(energy_layer1.at(j));
                    if (l == 1) for (size_t j = 0; j < energy_layer2.size(); j++) energy_layer2_gated[pair].emplace_back(energy_layer2.at(j));
                    if (l == 2) for (size_t j = 0; j < energy_layer3.size(); j++) energy_layer3_gated[pair].emplace_back(energy_layer3.at(j));
                    if (l == 3) for (size_t j = 0; j < energy_layer4.size(); j++) energy_layer4_gated[pair].emplace_back(energy_layer4.at(j));
                    if (l == 4) for (size_t j = 0; j < energy_layer5.size(); j++) energy_layer5_gated[pair].emplace_back(energy_layer5.at(j));
                }

                // cej still valid? hope so
                for (size_t j = 0; j < layers_event.size(); j++)
                {
                    layers_event_gated[pair].emplace_back(layers_event.at(j));
                    xpos_event_gated[pair].emplace_back(xpos_event.at(j));
                    ypos_event_gated[pair].emplace_back(ypos_event.at(j));
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
            //if (energy_MWD_layer_gated[pair][l].size() == 0) break;

            // Loop for sequential gate S1S2S4
            if ( Z21_passed[pair].size() > 0 && Z42_passed[pair].size() > 0 ) 
            {
                // MWD with condition of trigger on sci41 (TPAT 2)
                if ((frsHitItem.Get_tpat() & 0b10) && (int)lisaCalArray->size() == 5) 
                {
                    if (l == 0) for (size_t j = 0; j < energy_MWD_layer1.size(); j++) energy_MWD_layer1_gated[pair].emplace_back(energy_MWD_layer1.at(j));
                    if (l == 0) for (size_t j = 0; j < energy_MWD_layer2.size(); j++) energy_MWD_layer2_gated[pair].emplace_back(energy_MWD_layer2.at(j));
                    if (l == 0) for (size_t j = 0; j < energy_MWD_layer3.size(); j++) energy_MWD_layer3_gated[pair].emplace_back(energy_MWD_layer3.at(j));
                    if (l == 0) for (size_t j = 0; j < energy_MWD_layer4.size(); j++) energy_MWD_layer4_gated[pair].emplace_back(energy_MWD_layer4.at(j));
                    if (l == 0) for (size_t j = 0; j < energy_MWD_layer5.size(); j++) energy_MWD_layer5_gated[pair].emplace_back(energy_MWD_layer5.at(j));
                
                }                                
            }
        }
    } 
    auto & nongated_entry = lisaHistoArray.at(0)->emplace_back();
    // nongated_entry.SetNonGated(
    //     layers_event,
    //     xpos_event,
    //     ypos_event,
    //     AoQ_s1s2_mhtdc,
    //     AoQ_s2s4_mhtdc,
    //     AoQ_s1s2_selected_mhtdc,
    //     AoQ_s2s4_selected_mhtdc,
    //     Z21_mhtdc,
    //     Z41_mhtdc,
    //     Z42_mhtdc ,
    //     Z21_selected_mhtdc, 
    //     Z42_selected_mhtdc,
    //     energy_layer,
    //     energy_MWD_layer
    //     );

    // individual entry
    nongated_entry.layers = layers_event;
    nongated_entry.xpositions = xpos_event;
    nongated_entry.ypositions = ypos_event;
    nongated_entry.AoQ_s1s2_mhtdc = AoQ_s1s2_mhtdc;
    nongated_entry.AoQ_s2s4_mhtdc = AoQ_s2s4_mhtdc;
    nongated_entry.AoQ_s1s2_selected_mhtdc = AoQ_s1s2_selected_mhtdc;
    nongated_entry.AoQ_s2s4_selected_mhtdc = AoQ_s2s4_selected_mhtdc;
    nongated_entry.Z21_mhtdc = Z21_mhtdc;
    nongated_entry.Z41_mhtdc = Z41_mhtdc;
    nongated_entry.Z42_mhtdc = Z42_mhtdc;
    nongated_entry.Z21_selected_mhtdc = Z21_selected_mhtdc;
    nongated_entry.Z42_selected_mhtdc = Z42_selected_mhtdc;
    nongated_entry.energy_layer1 = energy_layer1;
    nongated_entry.energy_layer1 = energy_layer2;
    nongated_entry.energy_layer1 = energy_layer3;
    nongated_entry.energy_layer1 = energy_layer4;
    nongated_entry.energy_layer1 = energy_layer5;
    nongated_entry.energy_MWD_layer1 = energy_MWD_layer1;
    nongated_entry.energy_MWD_layer2 = energy_MWD_layer2;
    nongated_entry.energy_MWD_layer3 = energy_MWD_layer3;
    nongated_entry.energy_MWD_layer4 = energy_MWD_layer4;
    nongated_entry.energy_MWD_layer5 = energy_MWD_layer5;



//c4LOG(info,"H2");
    // for (int gate = 0; gate < FrsGates.size(); gate++)
    // {
    //     auto & gated_entry = lisaHistoArray.at(gate)->emplace_back();
    //     gated_entry.SetGated(
    //         AoQ_s1s2_passed[gate],
    //         AoQs1s2_s1s2s4_passed[gate],
    //         AoQs2s4_s1s2s4_passed[gate],
    //         Z21_passed[gate],
    //         Z21_s1s2s4_passed[gate],
    //         Z42_s1s2s4_passed[gate],
    //         AoQ_s1s2_selected_passed[gate],
    //         AoQs1s2_s1s2s4_selected_passed[gate],
    //         AoQs2s4_s1s2s4_selected_passed[gate],
    //         Z21_selected_passed[gate],
    //         Z21_s1s2s4_selected_passed[gate],
    //         Z42_s1s2s4_selected_passed[gate],
    //         energy_layer_gated[gate],
    //         energy_MWD_layer_gated[gate]
    //         );
    // }
    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
        //c4LOG(info,"H3");
        auto & gated_entry = lisaHistoArray.at(gate+1)->emplace_back();
        
        gated_entry.AoQs1s2_s1s2_mhtdc = AoQ_s1s2_passed[gate];
        gated_entry.AoQs1s2_s1s2s4_mhtdc = AoQs1s2_s1s2s4_passed[gate];
        gated_entry.AoQs2s4_s1s2s4_mhtdc = AoQs2s4_s1s2s4_passed[gate];
        gated_entry.Z21_s1s2_mhtdc = Z21_passed[gate];
        gated_entry.Z21_s1s2s4_mhtdc = Z21_s1s2s4_passed[gate];
        gated_entry.Z42_s1s2s4_mhtdc = Z42_s1s2s4_passed[gate];
        gated_entry.AoQs1s2_selected_s1s2_mhtdc = AoQ_s1s2_selected_passed[gate];
        gated_entry.AoQs1s2_selected_s1s2s4_mhtdc = AoQs1s2_s1s2s4_selected_passed[gate];
        gated_entry.AoQs2s4_selected_s1s2s4_mhtdc = AoQs2s4_s1s2s4_selected_passed[gate];
        gated_entry.Z21_selected_s1s2_mhtdc = Z21_selected_passed[gate];
        gated_entry.Z21_selected_s1s2s4_mhtdc = Z21_s1s2s4_selected_passed[gate];
        gated_entry.Z42_selected_s1s2s4_mhtdc = Z42_s1s2s4_selected_passed[gate];
        gated_entry.energy_layer1_gated = energy_layer1_gated[gate];
        gated_entry.energy_layer2_gated = energy_layer2_gated[gate];
        gated_entry.energy_layer3_gated = energy_layer3_gated[gate];
        gated_entry.energy_layer4_gated = energy_layer4_gated[gate];
        gated_entry.energy_layer5_gated = energy_layer5_gated[gate];
        gated_entry.energy_MWD_layer1_gated = energy_MWD_layer1_gated[gate];
        gated_entry.energy_MWD_layer2_gated = energy_MWD_layer2_gated[gate];
        gated_entry.energy_MWD_layer3_gated = energy_MWD_layer3_gated[gate];
        gated_entry.energy_MWD_layer4_gated = energy_MWD_layer4_gated[gate];
        gated_entry.energy_MWD_layer5_gated = energy_MWD_layer5_gated[gate];
        gated_entry.layers_gated     = layers_event_gated[gate];
        gated_entry.xpositions_gated = xpos_event_gated[gate];
        gated_entry.ypositions_gated = ypos_event_gated[gate];

    }


    //c4LOG(info, " LISA end of event");
}

void LisaHit2Histo::FinishEvent()
{
    //c4LOG(info,"I");
   
        energy_layer1.clear();
        energy_layer2.clear();
        energy_layer3.clear();
        energy_layer4.clear();
        energy_layer5.clear();
        energy_MWD_layer1.clear();
        energy_MWD_layer2.clear();
        energy_MWD_layer3.clear();
        energy_MWD_layer4.clear();
        energy_MWD_layer5.clear();
    

    // for (int g = 0; g < energy_layer_gated.size(); g++)
    // {
    //     for (int l = 0; l < energy_layer_gated[g].size(); l++)
    //     {
    //         energy_layer_gated[g][l].clear();
    //     }
    // }

     for (int g = 0; g < FrsGates.size(); g++)
    {
        // for (int l = 0; l < 10; l++)
        // {
        //     energy_layer_gated[g][l].clear();
        // }

        energy_layer1_gated[g].clear();
        energy_layer2_gated[g].clear();
        energy_layer3_gated[g].clear();
        energy_layer4_gated[g].clear();
        energy_layer5_gated[g].clear();
        energy_MWD_layer1_gated[g].clear();
        energy_MWD_layer2_gated[g].clear();
        energy_MWD_layer3_gated[g].clear();
        energy_MWD_layer4_gated[g].clear();
        energy_MWD_layer5_gated[g].clear();
    }

    // for (int g = 0; g < energy_MWD_layer_gated.size(); g++)
    // {
    //     for (int l = 0; l < energy_MWD_layer_gated[g].size(); l++)
    //     {
    //         energy_MWD_layer_gated[g][l].clear();
    //     }
    // }

    layers_event.clear();
    xpos_event.clear();
    ypos_event.clear();

    //c4LOG(info,"L");
    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
 
        AoQ_s1s2_passed[gate].clear();
        Z41_s1s2s4_passed[gate].clear();
        Z21_s1s2s4_selected_passed[gate].clear();
        AoQ_s2s4_passed[gate].clear();
        dEdeg_z41_passed[gate].clear(); 
        AoQs1s2_s1s2s4_passed[gate].clear();
        AoQs2s4_s1s2s4_passed[gate].clear();
        Z21_passed[gate].clear();
        Z41_passed[gate].clear();
        Z42_passed[gate].clear();
        Z42_selected_passed[gate].clear();
        Z21_s1s2s4_passed[gate].clear();
        Z42_s1s2s4_passed[gate].clear();
        AoQ_s1s2_selected_passed[gate].clear();
        AoQs1s2_s1s2s4_selected_passed[gate].clear();
        AoQs2s4_s1s2s4_selected_passed[gate].clear();
        Z21_selected_passed[gate].clear();
        Z42_s1s2s4_selected_passed[gate].clear();
        layers_event_gated[gate].clear();
        xpos_event_gated[gate].clear();
        ypos_event_gated[gate].clear();
    }



    
}

void LisaHit2Histo::FinishTask()
{
}