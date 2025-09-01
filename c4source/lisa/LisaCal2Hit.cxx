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
 *                              13.08.25                                      *
 ******************************************************************************/
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
#include "c4Logger.h"

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

LisaCal2Hit::LisaCal2Hit()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaAnaArray(nullptr)
    ,   lisaCalArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   multihitArray(nullptr)
    ,   lisaHitArray(new std::vector<LisaHitItem>)

{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();

    frs = frs_config->FRS(); 
    id = frs_config->ID();  
}



LisaCal2Hit::~LisaCal2Hit()
{
    delete lisaArray;
    delete lisaAnaArray;
    delete lisaCalArray;
    delete lisaHitArray;
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

    return kSUCCESS;
}


void LisaCal2Hit::Exec(Option_t* option)
{
    
    //c4LOG(info, " ::: start of event");
    lisaHitArray->clear();
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0 || multihitArray->size() <= 0) return;  

    
    const auto & frsHitItem = frsHitArray->at(0);
    const auto & multihitItem = multihitArray->at(0);

    // For global reaction flag definition
    beta_i = multihitItem.Get_ID_beta_s1s2_mhtdc();
    beta_f = multihitItem.Get_ID_beta_s2s4_mhtdc();
    aoq_i = multihitItem.Get_ID_AoQ_s1s2_mhtdc();
    aoq_f = multihitItem.Get_ID_AoQ_s2s4_mhtdc();
    z_i = multihitItem.Get_ID_z21_mhtdc();
    z_f = multihitItem.Get_ID_z41_mhtdc();
    beta0 = multihitItem.Get_ID_beta_s1s2_selected_mhtdc();

    // For gate on same S2 events in s2 and s4
    sci21l_s1s2_selected = multihitItem.Get_ID_sci21l_s1s2_selected_mhtdc();
    sci21r_s1s2_selected = multihitItem.Get_ID_sci21r_s1s2_selected_mhtdc();
    sci21l_s2s4_selected = multihitItem.Get_ID_sci21l_s2s4_selected_mhtdc();
    sci21r_s2s4_selected = multihitItem.Get_ID_sci21r_s2s4_selected_mhtdc();

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
    
    int tot_multiplicity = lisaCalArray->size();
    //int layer = lisaCalItem.Get_layer_id();
    int multiplicity[layer_number] = {0};

    // Calculate FRS parameters
    if ((sci21l_s1s2_selected == sci21l_s2s4_selected) && (sci21r_s1s2_selected == sci21r_s2s4_selected))
    {
        for(size_t i = 0; i < sci21l_s2s4_selected.size(); i++)
        {

            // Calculate Gamma initial
            gamma = 1.f / sqrt(1.f - TMath::Power(beta_i[i], 2));
            gamma_i.emplace_back(gamma);
            
            // Calculate beta in MeV
            beta_trans = (gamma -1.f)*aoq_i[i]*std::round(z_i[i])*conv_coeff;
            beta_en_i.emplace_back(beta_trans);

            // Get N and A before and after LISA
            N_i = aoq_i[i]*std::round(z_i[i]) - (z_i[i]);
            A_i = aoq_i[i]*std::round(z_i[i]);

            N_f = aoq_f[i]*std::round(z_f[i]) - (z_f[i]);
            A_f = aoq_f[i]*std::round(z_f[i]);

            //c4LOG(info, " Ni : " << N_i << " N_f : " << N_f );
            float z_diff_21_41 = z_i[i] - z_f[i];

            // Remove junk : Zf > Zi or Nf > Ni 
            //               Zi > Zf + 5 regardless from N which might be screwed up by the AoQ*Z(wrong) calculation
            double zDiff = std::round(z_diff_21_41);
            double nDiff = std::round(N_i - N_f);
            if (zDiff < 4 || nDiff < 7) return;
            if (std::abs(zDiff) > 9) return;   // 5 + 4
            if (std::abs(nDiff) > 12) return;  // 5 + 7

            // Global reaction flag
            if ( (zDiff >= 4 && zDiff <= 5) && (nDiff >= 7 && nDiff <= 8) )
            {
                // No Reactions
                globalReactions = 0;
            }
            else if (zDiff > 5 || nDiff > 8)
            {
                // Reactions
                globalReactions = 1;
            }
            else
            {
                globalReactions = -5;
            }
        }
        
    }            

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

            // int xpos_beam = -1;
            // int ypos_beam = -1;

            int x_origin = -14; // TODO move to lisa config
            int y_origin = -6.7;
            int x_step = 6;
            int y_step = 7;

            int xpos_beam = (std::floor((x_lisa_tpc22_23 - x_origin) / x_step));
            int ypos_beam = (std::floor((y_lisa_tpc22_23 - y_origin) / y_step));

            //c4LOG(info, " size of beta: " << beta_i.size() << " size of beta s: " << beta0.size());

            if (lisa_config->ZCalibrationLoaded() && (sci21l_s1s2_selected == sci21l_s2s4_selected) && (sci21r_s1s2_selected == sci21r_s2s4_selected))
            {
                 
                std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> z_calibration_coeffs = lisa_config->ZCalibrationCoefficients();
                if (auto result_find_Zcal = z_calibration_coeffs.find(detector_lxy); result_find_Zcal != z_calibration_coeffs.end()) 
                {
                    std::pair<double,double> z_coeffs = result_find_Zcal->second; 
                    slope_z = z_coeffs.first;
                    intercept_z = z_coeffs.second;

                    for (size_t i = 0; i < sci21l_s2s4_selected.size(); i++)
                    {
         
                        // Gate on lisa position
                        //if (std::abs(xpos_beam - xpos) > 1 || std::abs(ypos_beam - ypos) > 1) c4LOG(info, " x,ylisa : " << xpos << " , " << ypos << " x,y beam :" << xpos_beam << " ," << ypos_beam);
                        if (std::abs(xpos_beam - xpos) > 1 || std::abs(ypos_beam - ypos) > 1) return;
                        if(layer_id ==1)
                        {

                            xpos_1.emplace_back(xpos);
                            ypos_1.emplace_back(ypos);
                            thickness_1.emplace_back(thickness);

                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta0[i] * beta0[i])) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_1_temp.emplace_back(z_val + id->offset_z21); 
                            }
                            
                            // Calculate beta in MeV after passing layer 1
                            beta_trans_after1 = beta_en_i[i] - de_dx*thickness;


                            // Remove impossible values of z lisa or impossible z21 - zlisa - z41 event
                            // Add some tolerance
                            if ( std::abs(z_i[i] - z_lisa_1_temp[i]) > 6) return; //cleans the positive signals
                            if ( z_lisa_1_temp[i] > z_i[i]+ 2 ) return;
                            // TODO Add condition on TPC extrapolated position
                            
                            z_lisa_1.emplace_back(z_lisa_1_temp[i]);
                            z_diff_21_lisa1 = z_i[i] - z_lisa_1[i];
                            z_diff_lisa1_41 = z_lisa_1[i] - z_f[i];

                            // Calculate beta after layer 1
                            //      To calculate beta after layer 1, we need A after layer 1. The question now is: did we have a reaction in layer 1?
                            //      To know this, we compare z_i (21) with z (lisa) and z (41), and Aoq(s1s2)*z(21) with Aoq(s2s4)*z(41)
                            //      If they are the same, no reaction --> A(after layer 1) = A_i
                            //      If z and/or A are different, we calculate the new A
                            //      Now we can calculate the new beta

                            if(globalReactions == 0) 
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_1 = A_i * conv_coeff;
                            } 
                            else if (globalReactions == 1)
                            {
                                // If there is a reaction between s1s2 and s2s4:
                                // Has this reaction happened in this layer?
                                if( z_diff_21_lisa1 < 1 + 1.5) 
                                {
                                    // If no reaction happens, use A and Z from FRS before LISA
                                    A_MeV_1 = A_i * conv_coeff;
                                    lisaReaction = 0;

                                }else if ( z_diff_21_lisa1 >= 1 + 1.5)
                                {
                                    // If the reaction happened in this layer, calculate new A
                                    // TODO : flag for what kind of reaction #p,#n
                                    N_after1 = std::round(aoq_f[i]*std::round(z_f[i])) - std::round(z_f[i]);
                                    A_after1 = z_lisa_1[i] + N_after1;
                                    A_MeV_1 = A_after1 * conv_coeff;
                                    c4LOG(info, " Reaction happened in Layer :" << layer_id << " Z, N, A before :" << std::round(z_i[i]) << "," << N_i << "," << A_i << " Z,N,A after :" << std::round(z_f[i]) << "," << N_after1 << "," << A_after1 );
                                    c4LOG(info, " AoQ before: " << aoq_i[i] << " AoQ after : " << aoq_f[i]);
                                    c4LOG(info, " --- ");
                                    
                                    lisaReaction = 1;
                                }
                            }

                            // Calculate gamma and beta after layer 1 with the A calculate for that event
                            if(A_MeV_1 == 0) {c4LOG(info, " A = 0 ???" << " noReaction : " << noReaction);}
                            if(A_MeV_1 > 0 )
                            {
                                gamma_after1 = 1.f + beta_trans_after1 / A_MeV_1;
                                float inv_g2 = 1.f / (gamma_after1 * gamma_after1);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after1 = std::sqrt(arg);
                                
                                //if(beta_after1 >= 0.9) c4LOG(info, " ::: Beta is 1 ::: ");
                                //if(beta_after1 >= 0.9) c4LOG(info, " gamma before : " << gamma << " gamma after: " << gamma_after1 << " AoQ :" << aoq_i[0] << " A : " << A_MeV/conv_coeff);
                                //if(beta_after1 >= 0.9) c4LOG(info, " z music : " << static_cast<int>(std::round(z_i[i])) << " z lisa: " << static_cast<int>(std::round(z_lisa_1[i])) << " z diff : " << z_diff);

                            } 

                            beta1.emplace_back(beta_after1);
                            gamma1.emplace_back(gamma_after1);
                        
                            //c4LOG(info, " gamma after: " << gamma_after1);
                            //c4LOG( info, " beta before : " << beta << " beta after : " << beta_after1);
                            m_layer1 = 1;

                        }else if(layer_id == 2 && m_layer1 == 1 )
                        {
                            //c4LOG(info, " In layer 2 ");
                            m_layer2 = 1;

                        }else if(layer_id == 3 && m_layer2 == 1 )
                        {
                            //c4LOG(info, " In layer 3 ");
                            m_layer3 = 1;

                        }else if(layer_id == 4 && m_layer3 == 1 )
                        {
                            //c4LOG(info, " In layer 4 ");
                            m_layer4 = 1;
                        }else if(layer_id == 5 && m_layer4 == 1 )
                        {
                            //c4LOG(info, " In layer 5 ");
                            m_layer5 = 1;
                        }

                    }

                }
 
            }
            
            //c4LOG(info, " 11");
            auto & entry = lisaHitArray->emplace_back();
            entry.SetAll(
                lisaCalItem.Get_wr_t(),
                lisaCalItem.Get_wr_id(),
                lisaCalItem.Get_board_id(),
                lisaCalItem.Get_layer_id(),
                lisaCalItem.Get_city(),
                lisaCalItem.Get_xposition(),
                lisaCalItem.Get_yposition(),
                lisaCalItem.Get_thickness(),
                lisaCalItem.Get_energy(),
                lisaCalItem.Get_energy_MWD(),
                lisaCalItem.Get_trace_febex(),
                lisaCalItem.Get_trace_x(),
                lisaCalItem.Get_energy_GM(),
                lisaCalItem.Get_energy_MWD_GM(),
                lisaCalItem.Get_de_dx(),
                lisaCalItem.Get_de_dx_GM(),
                z_lisa_1,
                beta0,
                beta1,
                lisaCalItem.Get_board_event_time(),
                lisaCalItem.Get_channel_event_time(),
                EVTno,
                lisaCalItem.Get_pileup(),
                //lisaCalItem.Get_pileup_MWD(),
                lisaCalItem.Get_overflow(),
                //lisaCalItem.Get_overflow_MWD(),
                globalReactions,
                lisaReaction
            );

            lisaReaction = 0;
            globalReactions = 0;

            z_lisa_1_temp.clear();
            z_lisa_2_temp.clear();
            z_lisa_3_temp.clear();
            z_lisa_4_temp.clear();
            z_lisa_5_temp.clear();

            z_lisa_1.clear();
            z_lisa_2.clear();
            z_lisa_3.clear();
            z_lisa_4.clear();
            z_lisa_5.clear();

            gamma1.clear();
            gamma2.clear();
            gamma3.clear();
            gamma4.clear();
            gamma5.clear();

            beta1.clear();
            beta2.clear();
            beta3.clear();
            beta4.clear();
            beta5.clear();

            beta_en1.clear();
            beta_en2.clear();
            beta_en3.clear();
            beta_en4.clear();
            beta_en5.clear();

            xpos_1.clear();
            ypos_1.clear();
            thickness_1.clear();
            //c4LOG(info, " END of subevent");

        }
    }

    //c4LOG(info, " end of event");
}

void LisaCal2Hit::FinishEvent()
{

    gamma_i.clear();
    gamma_f.clear();
    beta_en_i.clear();
}

void LisaCal2Hit::FinishTask()
{
}