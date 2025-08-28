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

    beta0 = multihitItem.Get_ID_beta_s1s2_mhtdc();
    aoq0 = multihitItem.Get_ID_AoQ_s1s2_mhtdc();
    z0 = multihitItem.Get_ID_z21_mhtdc();

    if (beta0.size()==0) return;
    //c4LOG(info, " beta : " << beta1);

    int tot_multiplicity = lisaCalArray->size();
    //int layer = lisaCalItem.Get_layer_id();
    int multiplicity[layer_number] = {0};

    //c4LOG(info, " TOT multiplicity = " << tot_multiplicity);

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

            float z_val = 0;
            float beta_trans = 0;
            float beta_trans_after1 = 0;
            float beta_after1 = -999.;

            multiplicity[layer_id-1]++;
            
            std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer_id, std::make_pair(xpos, ypos) );
            //if (beta0.size() != 1) {c4LOG(info, " size of beta s1s2 : " << beta0.size());}

            if (lisa_config->ZCalibrationLoaded())
            {
                
                std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> z_calibration_coeffs = lisa_config->ZCalibrationCoefficients();
                if (auto result_find_Zcal = z_calibration_coeffs.find(detector_lxy); result_find_Zcal != z_calibration_coeffs.end()) 
                {
                    std::pair<double,double> z_coeffs = result_find_Zcal->second; 
                    slope_z = z_coeffs.first;
                    intercept_z = z_coeffs.second;

                    if (layer_id == 1)
                    {
                        xpos_1.emplace_back(xpos);
                        ypos_1.emplace_back(ypos);
                        thickness_1.emplace_back(thickness);

                        for (size_t i = 0; i < beta0.size(); i++)
                        {
                            float beta = beta0.at(i);
                            if (beta <= 0. || beta > 1.)
                            {
                                z_lisa.emplace_back(-999.);
                                beta1.emplace_back(-999.);
                                gamma0.emplace_back(-999);
                                gamma1.emplace_back(-999);
                                continue;
                            }

                            float gamma = 1.f / sqrt(1.f - TMath::Power(beta0.at(i), 2));
                            gamma0.emplace_back(gamma);

                            //  Z calibration
                            de_dx_corr = slope_z * (1.f / (beta * beta)) + intercept_z;
                            float zL = -999.;
                            if (de_dx_corr > 0.f)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa.emplace_back(z_val + id->offset_z21); 
                            }

                            beta_trans = (gamma -1.f)*aoq0[i]*z0[i]*conv_coeff;
                            beta_en0.emplace_back(beta_trans);

                            beta_trans_after1 = beta_trans - de_dx*thickness;
                            //c4LOG(info, " z music : " << static_cast<int>(std::round(z0[i])) << " z lisa: " << static_cast<int>(std::round(z_lisa[i])));
                            //c4LOG(info, " z music : " << z0[i] << " z lisa: " << z_lisa[i]);

                            float z_diff = z_lisa[i] - z0[i];
                            //c4LOG(info, " z lisa: " << z_lisa[i] << " z music: " << z0[i] << " z diff : " << z_diff);
                            float A_MeV = -999.;
                            bool sameZ = false;

                            if(std::abs(z_diff) <= 1.5)
                            {
                                A_MeV = ((aoq0[i] * z_lisa[i]) - z0[i] + z_lisa[i]) * conv_coeff;
                                //c4LOG(info, " A for z same : " << A_MeV/conv_coeff );
                                sameZ = true;
                            } 
                            // else if (std::abs(z_diff) > 1.5)
                            // {
                            //     A_MeV = ((aoq0[i] * z0[i]) - z0[i] + z_lisa[i])* conv_coeff;
                            //     c4LOG(info, " A for Z different : " << (aoq0[i] * z0[i]) - z0[i] + zL);
                            // }
                            //c4LOG(info, "5");
                            if(A_MeV != 0 && A_MeV > 0)
                            {
                                gamma_after1 = 1.f + beta_trans_after1 / A_MeV;
                                //c4LOG(info, " gamma before : " << gamma0[i] << " gamma after : " << gamma_after1);
                                float inv_g2 = 1.f / (gamma_after1 * gamma_after1);
                                float arg = 1.f - inv_g2;
                                if (arg >= 0.f) beta_after1 = std::sqrt(arg);
                                //c4LOG(info, " beta before : " << beta0[i] << " beta after : " << beta_after1);
                                //c4LOG(info, " ::: ");

                            } else
                            {
                                gamma_after1 = -999.;
                            }
                            if(!sameZ)
                            {
                                //c4LOG(info, " :::::::: Different Z  in layer " << layer_id);
                                //c4LOG(info, " A : " << std::round((aoq0[i] * z0[i]) + (zL - z0[i])));
                            }

                            beta1.emplace_back(beta_after1);
                            gamma1.emplace_back(gamma_after1);
                        
                            // if (z_lisa[i] - z0[i] <= 1.5) // if z lisa and z music are the same
                            // {
                            //     gamma_after1 = 1.f + beta_trans_after1/((aoq0[i] *z0[i]) * conv_coeff); 
                            //     beta_after1 = sqrt(1.f - 1.f/TMath::Power(gamma_after1, 2));
                            //     beta1.emplace_back(beta_after1);
                            //     //c4LOG(info, " A : " << (aoq0[i]*z_lisa[i])-z0[i] + z_lisa[i]);
                            //     //c4LOG(info, " gamma before : " << gamma0[i] << " gamma after : " << gamma_after1);
                            // }

                            // if(std::abs(z_diff) >= 1.5) // if z lisa and z musics are different
                            // {
                            //     gamma_after1 = 1. + beta_trans_after1/(((aoq0[i] * z_lisa[i]) - z0[i] + z_lisa[i])*conv_coeff);
                            //     beta_after1 = sqrt(1. - 1./TMath::Power(gamma_after1, 2));
                            //     beta1.emplace_back(beta_after1);
                            //     c4LOG(info, " DIFFERENT Z in " << layer_id);
                            //     c4LOG(info, " A : " << std::round((aoq0[i]*z_lisa[i]) + (z_lisa[i] - z0[i])));
                            // }
                
                            // gamma1.emplace_back(gamma_after1);

                            //c4LOG(info, " gamma after: " << gamma_after1);
                            //c4LOG( info, " beta before : " << beta << " beta after : " << beta_after1);
                        
                        } 
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
                else
                {
                    z_lisa.emplace_back(-999.);
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

    z_lisa.clear();
    xpos_1.clear();
    ypos_1.clear();
    thickness_1.clear();

    gamma0.clear();
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

    beta_en0.clear();
    beta_en1.clear();
    beta_en2.clear();
    beta_en3.clear();
    beta_en4.clear();
    beta_en5.clear();
}

void LisaCal2Hit::FinishTask()
{
}