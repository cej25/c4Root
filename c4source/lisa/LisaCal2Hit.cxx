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

    beta_i = multihitItem.Get_ID_beta_s1s2_mhtdc();
    beta_f = multihitItem.Get_ID_beta_s2s4_mhtdc();
    aoq_i = multihitItem.Get_ID_AoQ_s1s2_mhtdc();
    aoq_f = multihitItem.Get_ID_AoQ_s2s4_mhtdc();
    z_i = multihitItem.Get_ID_z21_mhtdc();
    z_f = multihitItem.Get_ID_z41_mhtdc();
    sci21l_s1s2_selected = multihitItem.Get_ID_sci21l_s1s2_selected_mhtdc();
    sci21r_s1s2_selected = multihitItem.Get_ID_sci21r_s1s2_selected_mhtdc();
    sci21l_s2s4_selected = multihitItem.Get_ID_sci21l_s2s4_selected_mhtdc();
    sci21r_s2s4_selected = multihitItem.Get_ID_sci21r_s2s4_selected_mhtdc();

    if (beta_i.size()==0) return;

    int tot_multiplicity = lisaCalArray->size();
    //int layer = lisaCalItem.Get_layer_id();
    int multiplicity[layer_number] = {0};

    for(size_t i = 0; i < sci21l_s2s4_selected.size(); i++)
    {

        //c4LOG(info, " 1");
        if (beta_i[i] <= 0. || beta_i[i] >= 1.) return;
        beta = beta_i.at(i);
        beta0.emplace_back(beta);
        //c4LOG(info, " 2");

        // Calculate Gamma initial
        gamma = 1.f / sqrt(1.f - TMath::Power(beta0.at(i), 2));
        gamma_i.emplace_back(gamma);
        
        // Calculate beta in MeV
        beta_trans = (gamma -1.f)*aoq_i[i]*std::round(z_i[i])*conv_coeff;
        beta_en_i.emplace_back(beta_trans);

        // Get N and A before and after LISA
        N_i = aoq_i[i]*std::round(z_i[i]) - (z_i[i]);
        A_i = aoq_i[i]*std::round(z_i[i]);

        N_f = aoq_f[i]*std::round(z_f[i]) - (z_f[i]);
        A_f = aoq_f[i]*std::round(z_f[i]);
        //c4LOG(info, " 3");
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

            // !TODO the calculation only if the extrapoleted position of the beam matches LISA!!!
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

                        //c4LOG(info, "4");
                        float z_diff_21_41 = z_i[i] - z_f[i];
                        bool noReaction = true;

                        // Remove junk : Zf > Zi or Nf > Ni 
                        //               Zi > Zf + 5 regardless from N which might be screwed up by the AoQ*Z(wrong) calculation
                        if( std::round(z_diff_21_41) > 5 || std::round(N_f) > std::round(N_i)) return; //this is 5 because of the current fucked up calibration of musics. Should be 0.
                        if( std::round(z_diff_21_41) > 5) return; //this is 5 because of the current fucked up calibration of musics. Should be 0.

                        // Set Flag for global reactions
                        // If zi = zf and ni = nf -> NoReaction Flag true
                        // If zf < zi or nf < ni -> NoReaction Flag false
                        if ( std::round(z_diff_21_41) == 4 && (std::round(N_i) == std::round(N_f))) noReaction = true; //this is 4 becuase of calibration. Should be 0-1
                        if ( std::round(z_diff_21_41) < 3 && (std::round(N_i) < std::round(N_f))) noReaction = false;
                        //c4LOG(info, " 5");
                        if(layer_id ==1)
                        {

                            //c4LOG(info, " 6");
                            xpos_1.emplace_back(xpos);
                            ypos_1.emplace_back(ypos);
                            thickness_1.emplace_back(thickness);
                            float A_MeV_1 = 0;

                            //c4LOG(info, " 7");
                            //  Calibrate LISA in Z
                            de_dx_corr = slope_z * (1.f / (beta0[i] * beta0[i])) + intercept_z;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa_1_temp.emplace_back(z_val + id->offset_z21); 
                            }
                            // Calculate beta in MeV after passing layer 1
                            //c4LOG(info, " 8");
                            beta_trans_after1 = beta_en_i[i] - de_dx*thickness;

                            // NB: ATM the calibration of zeta is a bit wrong, we can't really compare z lisa (accurate) and z music. 
                            float z_diff_lisa_21 = z_i[i] - z_lisa_1_temp[i];
                            float z_diff_41_lisa1 = z_f[i] - z_lisa_1_temp[i];
                            //  TODO Throw away junk events in Z21
                            // If Zlisa > Z21 Junk
                            // If Z lisa - Z 21 > 6 Junk (probable coming from low positive signals we have or noise in music)
                            // If Z lisa > Z f --> Junk (not possible that Z in lisa is less than Z in 41)
                            // Fill a new Zlisa1 vector cleaned of all of this junk

                            if( std::abs(z_diff_lisa_21) >= (1+6) || std::abs(z_diff_21_41) >= (4+4)) 
                            {
                                //c4LOG(info, " Junk.  Z21 : " << z_i[i] << " ZLISA : " << z_lisa_1_temp[i] << " Z41 : " << z_f[i]);
                                return;
                            }

                            // Calculate beta after layer 1

                            //      To calculate beta after layer 1, we need A after layer 1. The question now is: did we have a reaction in layer 1?
                            //      To know this, we compare z_i (21) with z (lisa) and z (41), and Aoq(s1s2)*z(21) with Aoq(s2s4)*z(41)
                            //      If they are the same, no reaction --> A(after layer 1) = A_i
                            //      If z and/or A are different, we calculate the new A
                            //      Now we can calculate the new beta

                            // Is there a reaction between S1S2 and S2S4?
                            //c4LOG(info, " 9");
                            if(std::abs(z_diff_21_41) < 4 + 2) //atm Z is not well calibrate and the av difference for no reaction is 4
                            {
                                // If no reaction, use A and Z from FRS before LISA
                                A_MeV_1 = A_i * conv_coeff;
                                noReaction = true;
                            } 
                            else if (std::abs(z_diff_21_41) >= 4 + 2)
                            {
                                // If there is a reaction between s1s2 and s2s4:
                                // Has this reaction happened in this layer?
                                if( std::abs(z_diff_lisa_21) < 1 + 1.5) //atm z21 is not well calibrate and the av difference for no reaction is 1.5
                                {
                                    // If no reaction happens, use A and Z from FRS before LISA
                                    A_MeV_1 = A_i * conv_coeff;
                                    noReaction = true;

                                }else if (std::abs(z_diff_lisa_21) >= 1 + 1.5)
                                {
                                    // If the reaction happened in this layer, calculate new A
                                    // A_after1 = Z (calculated in LISA 1) + N (calculated from s2s4 (AoQ*Z41)-Z41)
                                    N_after1 = std::round(aoq_f[i]*std::round(z_f[i])) - std::round(z_f[i]);
                                    A_after1 = z_lisa_1[i] + N_after1;
                                    A_MeV_1 = A_after1 * conv_coeff;
                                    c4LOG(info, " Reaction happened in Layer :" << layer_id << " Z, N, A before :" << std::round(z_i[i]) << "," << N_i << "," << A_i << " Z,N,A after :" << std::round(z_f[i]) << "," << N_after1 << "," << A_after1 );
                                    c4LOG(info, " Z lisa: " << z_lisa_1[i]);
                                    c4LOG(info, " AoQ before: " << aoq_i[i] << " AoQ after : " << aoq_f[i]);
                                    c4LOG(info, " --- ");
                                    noReaction = false;
                                    // !!!Flag for reaction identification in layer
                                
                                }
                            }
                            //c4LOG(info, " 10");
                            // Calculate gamma and beta after layer 1 with the A calculate for that event
                            if(A_MeV_1 == 0) {c4LOG(info, " A = 0 ???");}
                            if(A_MeV_1 > 0 && std::abs(z_diff_lisa_21) <=5)
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
                        
                            // if (z_lisa_1[i] - z_i[i] <= 1.5) // if z lisa and z music are the same
                            // {
                            //     gamma_after1 = 1.f + beta_trans_after1/((aoq_i[i] *z_i[i]) * conv_coeff); 
                            //     beta_after1 = sqrt(1.f - 1.f/TMath::Power(gamma_after1, 2));
                            //     beta1.emplace_back(beta_after1);
                            //     //c4LOG(info, " A : " << (aoq_i[i]*z_lisa_1[i])-z_i[i] + z_lisa_1[i]);
                            //     //c4LOG(info, " gamma before : " << gamma_i[i] << " gamma after : " << gamma_after1);
                            // }

                            // if(std::abs(z_diff) >= 1.5) // if z lisa and z musics are different
                            // {
                            //     gamma_after1 = 1. + beta_trans_after1/(((aoq_i[i] * z_lisa_1[i]) - z_i[i] + z_lisa_1[i])*conv_coeff);
                            //     beta_after1 = sqrt(1. - 1./TMath::Power(gamma_after1, 2));
                            //     beta1.emplace_back(beta_after1);
                            //     c4LOG(info, " DIFFERENT Z in " << layer_id);
                            //     c4LOG(info, " A : " << std::round((aoq_i[i]*z_lisa_1[i]) + (z_lisa_1[i] - z_i[i])));
                            // }
                
                            // gamma1.emplace_back(gamma_after1);

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
                lisaCalItem.Get_overflow()
                //lisaCalItem.Get_overflow_MWD()
            );

            

        }
    }

    //c4LOG(info, " end of event");
}

void LisaCal2Hit::FinishEvent()
{
    c4LOG(info, " 12");
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

    xpos_1.clear();
    ypos_1.clear();
    thickness_1.clear();

    gamma_i.clear();
    gamma_f.clear();

    gamma1.clear();
    gamma2.clear();
    gamma3.clear();
    gamma4.clear();
    gamma5.clear();

    beta0.clear();
    beta1.clear();
    beta2.clear();
    beta3.clear();
    beta4.clear();
    beta5.clear();

    beta_en_i.clear();
    beta_en1.clear();
    beta_en2.clear();
    beta_en3.clear();
    beta_en4.clear();
    beta_en5.clear();

    c4LOG(info, " 13");
}

void LisaCal2Hit::FinishTask()
{
}