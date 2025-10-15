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
#include "Atima.h"

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
    Atima atima;
    //c4LOG(info, " ::: LISA start of event");
    lisaHitArray->clear();
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0 || multihitArray->size() <= 0) return;  

    const auto & frsHitItem = frsHitArray->at(0);
    const auto & multihitItem = multihitArray->at(0);

    // For global reaction flag definition
    beta_i = multihitItem.Get_ID_beta_s1s2_mhtdc();
    beta_f = multihitItem.Get_ID_beta_s2s4_mhtdc();
    aoq_i = multihitItem.Get_ID_AoQ_s1s2_mhtdc();
    aoq_f = multihitItem.Get_ID_AoQ_s2s4_mhtdc();
    aoq_i_s = multihitItem.Get_ID_AoQ_corr_s1s2_selected_mhtdc();
    aoq_f_s = multihitItem.Get_ID_AoQ_corr_s2s4_selected_mhtdc();
    z_i = multihitItem.Get_ID_z21_mhtdc();
    z_f = multihitItem.Get_ID_z41_mhtdc();
    beta0 = multihitItem.Get_ID_beta_s1s2_selected_mhtdc();
    copy_beta0 = multihitItem.Get_ID_beta_s1s2_selected_mhtdc();

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

            // Temporary parameters waiting to include **ATIMA**
            //beta_before_lisa_temp = beta0[i]*1.09105309 - 0.07362279; // For primary - run6
            beta_before_lisa_temp = beta0[i]*1.05614604 - 0.04864503; // For primary - run18
            //beta_before_lisa_temp = beta0[i]*1.08374666 - 0.06858425; // For primary - run19

            catima::Projectile carbon(12, 6);
            Double_t Ein = 0.5;

            Double_t dE = atima.CalculateEnergyLossShiyan(carbon,Ein);
            std::cout << "Total ΔE = " << dE << " MeV/u" << std::endl;

            beta_before_lisa.emplace_back(beta_before_lisa_temp);
            copy_beta_before_lisa.emplace_back(beta_before_lisa_temp);
            
            // Calculate Gamma initial
            gamma = 1.f / sqrt(1.f - TMath::Power(beta_before_lisa[i], 2));
            gamma_i.emplace_back(gamma);
            
            // Calculate beta in MeV
            beta_trans = (gamma -1.f)*(aoq_i[i]*std::round(z_i[i]))*conv_coeff;
            beta_en_i.emplace_back(beta_trans);

            // Get N and A before and after LISA
            N_i = aoq_i[i]*std::round(z_i[i]) - (z_i[i]);
            A_i = aoq_i[i]*std::round(z_i[i]);

            N_f = aoq_f[i]*std::round(z_f[i]) - (z_f[i]);
            A_f = aoq_f[i]*std::round(z_f[i]);

            //c4LOG(info, " Ni : " << N_i << " N_f : " << N_f );
            float z_diff_21_41 = z_i[i] - z_f[i];

            // Remove junk : Zf > Zi or Nf > Ni 
            //               Zi > Zf + 7
            float nDiff = N_i - N_f;
            if (z_diff_21_41 < -0.2 || nDiff < -0.2) return;
            if (std::abs(z_diff_21_41) > 7) return;   
            if (std::abs(nDiff) > 7 ) return; 

            // Global reaction flag
            if ( (std::abs(z_diff_21_41) >= 0 && std::abs(z_diff_21_41) < 1.2) && (std::abs(nDiff) >= 0 && std::abs(nDiff) < 1.2))
            {
                // No Reactions
                globalReactions = 0;
                c_globalReactions = 0;
            }
            else if (std::abs(z_diff_21_41) >= 1.2 || std::abs(nDiff) >= 1.2)
            {
                // Reactions
                globalReactions = 1;
                c_globalReactions = 1;
            }
            else
            {
                globalReactions = -5;
                c_globalReactions = -5;
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

            float x_origin = -14; // TODO move to lisa config
            float y_origin = -6.7;
            float x_step = 6;
            float y_step = 7;

            int xpos_beam = (std::floor((x_lisa_tpc22_23 - x_origin) / x_step));
            int ypos_beam = (std::floor((y_lisa_tpc22_23 - y_origin) / y_step));
            // Gate on lisa position
            if (std::abs(xpos_beam - xpos) > 1 || std::abs(ypos_beam - ypos) > 1) return;

            // Add reaction definition with dedx here

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
                        
                        // global lisa constrained reaction flag
                        float z_diff_21_41 = z_i[i] - z_f[i];
                        float nDiff = N_i - N_f;
                        if ( (std::abs(z_diff_21_41) >= 0 && std::abs(z_diff_21_41) < 1.2) && (std::abs(nDiff) >= 0 && std::abs(nDiff) < 1.2))
                        {
                            // No Reactions
                            globalReactions_on_lisa_z = 0;
                            c_globalReactions_on_lisa_z = 0;
                        }
                        else if (std::abs(z_diff_21_41) >= 1.2 || std::abs(nDiff) >= 1.2)
                        {
                            // Reactions
                            globalReactions_on_lisa_z = 1;
                            c_globalReactions_on_lisa_z = 1;
                        }
                        else
                        {
                            globalReactions_on_lisa_z = -5;
                            c_globalReactions_on_lisa_z = -5;
                        }

                        if(layer_id ==1)
                        {

                            xpos_1.emplace_back(xpos);
                            ypos_1.emplace_back(ypos);
                            thickness_1.emplace_back(thickness);

                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta_before_lisa[i] * beta_before_lisa[i])) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_1_temp.emplace_back(z_val + id->offset_z21); 
                            }
                            
                            // Calculate beta in MeV after passing layer 1
                            beta_trans_after1 = beta_en_i[i] - de_dx*thickness;


                            // Remove impossible values of z lisa or impossible z21 - zlisa - z41 event
                            // Add some tolerance
                            if ( std::abs(z_i[i] - z_lisa_1_temp[i]) > 6) return;   // cleans the positive signals
                            if ( z_lisa_1_temp[i] > z_i[i]+ 0.5 ) return;           // z lisa can't be greater than z21

                            z_lisa_1.emplace_back(z_lisa_1_temp[i]);
                            z_lisa.emplace_back(z_lisa_1_temp[i]);
                            z_diff_21_lisa1 = z_i[i] - z_lisa[i];

                            if(c_globalReactions_on_lisa_z == 0) 
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_1 = A_i * conv_coeff;
                                lisaReactions_z = 0;
                                layer1_reaction = 0;
                            } 
                            else if (c_globalReactions_on_lisa_z == 1)
                            {
                                // If there is a reaction between s1s2 and s2s4:
                                // Has this reaction happened BEFORE this layer? 
                                if( std::abs(z_diff_21_lisa1) < 1) // 
                                {
                                    // If no reaction happened, use A and Z from FRS before LISA
                                    A_MeV_1 = A_i * conv_coeff;
                                    lisaReactions_z = 0;
                                    layer1_reaction = 0;

                                }else if ( std::abs(z_diff_21_lisa1) >= 1 )
                                {
                                    // If a reaction happened before this layer, calculate new A
                                    A_1 = z_lisa_1[i] + N_f;
                                    A_MeV_1 = A_1 * conv_coeff;
                                    //c4LOG(info, "11");
                                    lisaReactions_z = 1; // this is enabled if a reaction happened BEFORE current layer
                                    layer1_reaction = 1;
                                }
                            }

                            // Calculate gamma and beta after layer 1 with the A calculated for that event
                            if(A_MeV_1 == 0) {c4LOG(info, " A = 0 ???" << " noReaction : " << noReaction);}
                            if(A_MeV_1 > 0 )
                            {
                                gamma_after1 = 1.f + beta_trans_after1 / A_MeV_1;
                                float inv_g2 = 1.f / (gamma_after1 * gamma_after1);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after1 = std::sqrt(arg);
                            } 

                            beta1.emplace_back(beta_after1);
                            gamma1.emplace_back(gamma_after1);
                        
                            m_layer1 = 1;

                        }else if(layer_id == 2 && m_layer1 == 1 ) // this selects LISA events with multiplicity 5
                        {
                            // Calibrate for Z
                            //if(c_globalReactions_on_lisa==1)c4LOG(info,"22");
                            xpos_2.emplace_back(xpos);
                            ypos_2.emplace_back(ypos);
                            thickness_2.emplace_back(thickness);
                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta_after1 * beta_after1)) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_2_temp.emplace_back(z_val + id->offset_z21); 
                            }
                            // Calculate beta in MeV after passing layer 2
                            beta_trans_after2 = beta_trans_after1 - de_dx*thickness;

                            // Remove impossible values of z lisa or impossible z21 - zlisa - z41 event
                            // Add some tolerance
                            if ( std::abs(z_i[i] - z_lisa_2_temp[i]) > 6) return; //cleans the positive signals
                            if ( z_lisa_2_temp[i] > z_i[i] + 1 ) return;
                            if ( z_lisa_2_temp[i] > z_lisa_1[i] + 0.5) return;

                            z_lisa_2.emplace_back(z_lisa_2_temp[i]);
                            z_lisa.emplace_back(z_lisa_2[i]);
                            
                            z_diff_lisa1_lisa2 = z_lisa_1[i] - z_lisa_2[i];
                            z_diff_lisa2_41 = z_lisa_2[i] - z_f[i];
                            // Check if there is reaction
                            if(c_globalReactions_on_lisa_z == 0) 
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_2 = A_i * conv_coeff;
                            } 
                            else if (c_globalReactions_on_lisa_z == 1)
                            {
                                // Check if it happened before this layer
                                if( std::abs(z_diff_lisa1_lisa2) < 1 ) // zlisa1 - zlisa2 < 1
                                {
                                    // If no reaction happens, use A and Z from FRS before LISA
                                    A_MeV_2 = A_i * conv_coeff;
                                    lisaReactions_z = 0;
                                    layer2_reaction = 0;

                                }else if ( std::abs(z_diff_lisa1_lisa2) >= 1)
                                {
                                    // If the reaction happened before this layer, calculate new A
                                    A_2 = z_lisa_2[i] + N_f;
                                    A_MeV_2 = A_2 * conv_coeff;
                                    
                                    lisaReactions_z = 1;
                                    layer2_reaction = 1;
                                }
                            }
                            // Calculate beta after layer2
                            if(A_MeV_2 == 0) {c4LOG(info, " A = 0 ???" << " noReaction : " << noReaction);}
                            if(A_MeV_2 > 0 )
                            {
                                gamma_after2 = 1.f + beta_trans_after2 / A_MeV_2;
                                float inv_g2 = 1.f / (gamma_after2 * gamma_after2);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after2 = std::sqrt(arg);
                            } 
                            beta2.emplace_back(beta_after2);
                            gamma2.emplace_back(gamma_after2);

                            m_layer2 = 1;

                        }else if(layer_id == 3 && m_layer2 == 1 )
                        {
                            //  Calibrate for Z
                            xpos_3.emplace_back(xpos);
                            ypos_3.emplace_back(ypos);
                            thickness_3.emplace_back(thickness);
                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta_after2 * beta_after2)) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_3_temp.emplace_back(z_val + id->offset_z21); 
                            }

                            // Calculate beta in MeV after passing layer 3
                            beta_trans_after3 = beta_trans_after2 - de_dx*thickness;

                            // Remove impossible values of z lisa or impossible z21 - zlisa - z41 event
                            // Add some tolerance
                            if ( std::abs(z_i[i] - z_lisa_3_temp[i]) > 6) return; //cleans the positive signals
                            if ( z_lisa_3_temp[i] > z_i[i] + 1 ) return;
                            if(layer2_reaction == 1) // if there is a reaction in the prev layer, the z in the following layer should not be greater than z41
                            {
                                if (z_lisa_3_temp[i] > z_f[i] ) return; //!!this exclude reactions between lisa5 and s4
                            }
                            if ( z_lisa_3_temp[i] > z_lisa_2[i] + 0.5) return;

                            z_lisa_3.emplace_back(z_lisa_3_temp[i]);
                            z_lisa.emplace_back(z_lisa_3[i]);

                            z_diff_lisa2_lisa3 = z_lisa_2[i] - z_lisa_3[i];
                            z_diff_lisa3_41 = z_lisa_3[i] - z_f[i];
                            // Check if there is reaction
                            if(c_globalReactions_on_lisa_z == 0) 
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_3 = A_i * conv_coeff;
                            } 
                            else if (c_globalReactions_on_lisa_z == 1 && ( layer2_reaction == 1 ))
                            {
                                // If there is a reaction between s1s2 and s2s4, but it happened in the prev layers
                                // Use A_MeV calculated in the layer1 step
                                A_MeV_3 = A_MeV_2;

                                // TODO if z2 != z1 add some flag or do something to see if any problem

                            }
                            else if (c_globalReactions_on_lisa_z == 1 && ( layer2_reaction == 0 ))
                            {
                                // If the reaction did not happened earlier
                                // Check if it happened before this layer

                                if( z_diff_lisa2_lisa3 < 1 ) // zlisa2 - zlisa3 < 1.5 (for some tolerance)
                                {
                                    // If no reaction happens, use A and Z from FRS before LISA
                                    A_MeV_3 = A_i * conv_coeff;
                                    lisaReactions_z = 0;
                                    layer3_reaction = 0;

                                }else if ( z_diff_lisa2_lisa3 >= 1)
                                {
                                    // If the reaction happened in this layer, calculate new A
                                    A_3 = z_lisa_3[i] + N_f;
                                    A_MeV_3 = A_3 * conv_coeff;
                                    
                                    lisaReactions_z = 1;
                                }
                            }
                            // Calculate beta after layer3
                            if(A_MeV_3 == 0) {c4LOG(info, " A = 0 ???" << " noReaction : " << noReaction);}
                            if(A_MeV_3 > 0 )
                            {
                                gamma_after3 = 1.f + beta_trans_after3 / A_MeV_3;
                                float inv_g2 = 1.f / (gamma_after3 * gamma_after3);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after3 = std::sqrt(arg);
                            } 
                            beta3.emplace_back(beta_after3);
                            gamma3.emplace_back(gamma_after3);
                            
                            m_layer3 = 1;

                        }else if(layer_id == 4 && m_layer3 == 1 )
                        {
                            // Calibrate for Z
                            xpos_4.emplace_back(xpos);
                            ypos_4.emplace_back(ypos);
                            thickness_4.emplace_back(thickness);
                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta_after3 * beta_after3)) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_4_temp.emplace_back(z_val + id->offset_z21); 
                            }
                            // Calculate beta in MeV after passing layer 4
                            beta_trans_after4 = beta_trans_after3 - de_dx*thickness;


                            // Remove impossible values of z lisa or impossible z21 - zlisa - z41 event
                            // Add some tolerance
                            if ( std::abs(z_i[i] - z_lisa_4_temp[i]) > 6) return; //cleans the positive signals
                            if ( z_lisa_4_temp[i] > z_i[i] + 1 ) return;
                            if(layer2_reaction == 1 || layer3_reaction == 1) // if there is a reaction in the prev layer, the z in the following layer should not be greater than z41
                            {
                                if (z_lisa_4_temp[i] > z_f[i] ) return; //!!this exclude reactions between lisa5 and s4
                            }
                            if ( z_lisa_4_temp[i] > z_lisa_3[i] + 0.5) return;

                            z_lisa_4.emplace_back(z_lisa_4_temp[i]);
                            z_lisa.emplace_back(z_lisa_4[i]);

                            z_diff_lisa3_lisa4 = z_lisa_3[i] - z_lisa_4[i];
                            z_diff_lisa4_41 = z_lisa_4[i] - z_f[i];

                            // Check if there is reaction
                            if(c_globalReactions_on_lisa_z == 0) 
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_4 = A_i * conv_coeff;
                            } 
                            else if (c_globalReactions_on_lisa_z == 1 && ( layer2_reaction == 1 || layer3_reaction == 1))
                            {
                                // If there is a reaction between s1s2 and s2s4, but it happened in the prev layers
                                // Use A_MeV calculated in the layer1 step
                                A_MeV_4 = A_MeV_3;

                                // TODO if z2 != z1 add some flag or do something to see if any problem

                            }
                            else if (c_globalReactions_on_lisa_z == 1 && ( layer2_reaction == 0 && layer3_reaction == 0))
                            {
                                // If the reaction did not happened earlier
                                // Check if it happened before this layer

                                if( z_diff_lisa3_lisa4 < 1 ) // zlisa2 - zlisa3 < 1.5 (for some tolerance)
                                {
                                    // If no reaction happens, use A and Z from FRS before LISA
                                    A_MeV_4 = A_i * conv_coeff;
                                    lisaReactions_z = 0;
                                    layer4_reaction = 0;

                                }else if ( z_diff_lisa3_lisa4 >= 1)
                                {
                                    // If the reaction happened in this layer, calculate new A
                                    A_4 = z_lisa_4[i] + N_f;
                                    A_MeV_4 = A_4 * conv_coeff;
                                    
                                    lisaReactions_z = 1;
                                }
                            }
                            // Calculate beta after layer4
                            if(A_MeV_4 == 0) {c4LOG(info, " A = 0 ???" << " noReaction : " << noReaction);}
                            if(A_MeV_4 > 0 )
                            {
                                gamma_after4 = 1.f + beta_trans_after4 / A_MeV_4;
                                float inv_g2 = 1.f / (gamma_after4 * gamma_after4);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after4 = std::sqrt(arg);
                            } 
                            beta4.emplace_back(beta_after4);
                            gamma4.emplace_back(gamma_after4);

                            m_layer4 = 1;

                        }else if(layer_id == 5 && m_layer4 == 1 )
                        {
                            // Calibrate for Z
                            xpos_5.emplace_back(xpos);
                            ypos_5.emplace_back(ypos);
                            thickness_5.emplace_back(thickness);
                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta_after4 * beta_after4)) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_5_temp.emplace_back(z_val + id->offset_z21); 
                            }
                            // Calculate beta in MeV after passing layer 5
                            beta_trans_after5 = beta_trans_after4 - de_dx*thickness;

                            // Remove impossible values of z lisa or impossible z21 - zlisa - z41 event
                            // Add some tolerance
                            if ( std::abs(z_i[i] - z_lisa_5_temp[i]) > 6) return; //cleans the positive signals
                            if ( z_lisa_5_temp[i] > z_i[i] + 1 ) return;
                            if(layer2_reaction == 1 || layer3_reaction == 1 || layer4_reaction == 1) // if there is a reaction in the prev layer, the z in the following layer should not be greater than z41
                            {
                                if (z_lisa_5_temp[i] > z_f[i] ) return; //!!this exclude reactions between lisa5 and s4
                            }
                            if ( z_lisa_5_temp[i] > z_lisa_4[i] + 0.5) return;

                            z_lisa_5.emplace_back(z_lisa_5_temp[i]);
                            z_lisa.emplace_back(z_lisa_5[i]);

                            z_diff_lisa4_lisa5 = z_lisa_4[i] - z_lisa_5[i];
                            z_diff_lisa5_41 = z_lisa_5[i] - z_f[i];

                            // Check if there is reaction
                            if(c_globalReactions_on_lisa_z == 0) 
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_5 = A_i * conv_coeff;
                            } 
                            else if (c_globalReactions_on_lisa_z == 1 && ( layer2_reaction == 1 || layer3_reaction == 1 || layer4_reaction == 1))
                            {
                                // If there is a reaction between s1s2 and s2s4, but it happened in the prev layers
                                // Use A_MeV calculated in the layer1 step
                                A_MeV_5 = A_MeV_4;

                                // TODO if z2 != z1 add some flag or do something to see if any problem

                            }
                            else if (c_globalReactions_on_lisa_z == 1 && ( layer2_reaction == 0 && layer3_reaction == 0 && layer4_reaction == 0))
                            {
                                // If the reaction did not happened earlier
                                // Check if it happened before this layer

                                if( z_diff_lisa4_lisa5 < 1 ) // zlisa2 - zlisa3 < 1.5 (for some tolerance)
                                {
                                    // If no reaction happens, use A and Z from FRS before LISA
                                    A_MeV_5 = A_i * conv_coeff;
                                    lisaReactions_z = 0;
                                    layer5_reaction = 0;

                                }else if ( z_diff_lisa4_lisa5 >= 1)
                                {
                                    // If the reaction happened in this layer, calculate new A
                                    A_5 = z_lisa_5[i] + N_f;
                                    A_MeV_5 = A_5 * conv_coeff;
                                    
                                    lisaReactions_z = 1;
                                    layer5_reaction = 1;
                                }
                            }
                            // Calculate beta after layer4
                            if(A_MeV_5 == 0) {c4LOG(info, " A = 0 ???" << " noReaction : " << noReaction);}
                            if(A_MeV_5 > 0 )
                            {
                                gamma_after5 = 1.f + beta_trans_after5 / A_MeV_5;
                                float inv_g2 = 1.f / (gamma_after5 * gamma_after5);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after5 = std::sqrt(arg);
                            } 
                            beta5.emplace_back(beta_after5);
                            gamma5.emplace_back(gamma_after5);

                            m_layer5 = 1;
                        }

                        // Calculate reactions after lisa
                        if(m_layer5 == 1 && c_globalReactions_on_lisa_z == 1 && layer1_reaction == 0 && layer2_reaction == 0 && layer3_reaction == 0 && layer4_reaction == 0 && layer5_reaction == 0)
                        {
                            //c4LOG(info, "after lisa reactions");
                            if(z_f[i] <= (z_lisa_5[i] - 1) ) 
                            {
                                after_lisa_reactions_z = 1;
                            }else if (z_f[i] > (z_lisa_5[i] - 1) )
                            {
                                after_lisa_reactions_z = 0;
                            }
                        }

                    }

                }
 
            }
            
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
                z_lisa,
                copy_beta0,
                copy_beta_before_lisa,
                beta1,
                beta2,
                beta3,
                beta4,
                beta5,
                lisaCalItem.Get_board_event_time(),
                lisaCalItem.Get_channel_event_time(),
                EVTno,
                lisaCalItem.Get_pileup(),
                //lisaCalItem.Get_pileup_MWD(),
                lisaCalItem.Get_overflow(),
                //lisaCalItem.Get_overflow_MWD(),
                globalReactions,
                globalReactions_on_lisa_z,
                lisaReactions_z,
                after_lisa_reactions_z
            );

            lisaReactions_z = 0;
            globalReactions = 0;
            globalReactions_on_lisa_z = 0;
            after_lisa_reactions_z = 0;

            gamma1.clear();
            gamma2.clear();
            gamma3.clear();
            gamma4.clear();
            gamma5.clear();

            z_lisa.clear();
            copy_beta0.clear();
            copy_beta_before_lisa.clear();
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
            xpos_2.clear();
            ypos_2.clear();
            thickness_2.clear();
            xpos_3.clear();
            ypos_3.clear();
            thickness_3.clear();
            xpos_4.clear();
            ypos_4.clear();
            thickness_4.clear();
            xpos_5.clear();
            ypos_5.clear();
            thickness_5.clear();

            //c4LOG(info, " END of subevent");

        }
    }

    //c4LOG(info, " LISA end of event");
}

void LisaCal2Hit::FinishEvent()
{
    m_layer1 = 0;
    m_layer2 = 0;
    m_layer3 = 0;
    m_layer4 = 0;
    m_layer5 = 0;
    layer1_reaction = 0;
    layer2_reaction = 0;
    layer3_reaction = 0;
    layer4_reaction = 0;
    layer5_reaction = 0;

    c_globalReactions = 0;
    c_globalReactions_on_lisa_z = 0;

    copy_beta_before_lisa.clear();
    //copy_beta0.clear();
    beta_before_lisa.clear();
    gamma_i.clear();
    gamma_f.clear();
    beta_en_i.clear();

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
}

void LisaCal2Hit::FinishTask()
{
}