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
    z_lisa.clear();
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0 || multihitArray->size() <= 0) return;  

    
    const auto & frsHitItem = frsHitArray->at(0);
    const auto & multihitItem = multihitArray->at(0);

    beta1 = multihitItem.Get_ID_beta_s1s2_mhtdc();
    //if (beta1.size()==0) return;
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
            float z_val = 0;

            if (layer_id == 1)
            {
                m_layer1 ++;
            }
            //c4LOG(info, " multiplicity layer 1 : " << m_layer1);
            multiplicity[layer_id-1]++;
            
            std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer_id, std::make_pair(xpos, ypos) );
            //c4LOG(info, " size of beta s1s2 : " << beta1.size());
            //c4LOG(info, " layer : " << layer_id << " xpos : " << xpos << " ypos: "<< ypos);

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
                        for (size_t i = 0; i < beta1.size(); i++)
                        {
                            float beta = beta1.at(i);
                            if (beta <= 0 || beta > 1)
                            {
                                z_lisa.emplace_back(-999.);
                                continue;
                            }
                        
                            de_dx_corr = slope_z * (1.0 / (beta * beta)) + intercept_z;
                            if (de_dx_corr > 0)
                            {
                                z_val = frs->primary_z * std::sqrt(de_dx / de_dx_corr);
                                z_lisa.emplace_back(z_val + id->offset_z21); 
                                //c4LOG(info, " beta : " << beta << " de_dx : " << de_dx << " de_dx_corr : " << de_dx_corr << " z val : " << z_val );
                                //c4LOG(info, " slope : " << slope_z << " layer : " << layer_id << " intercept : " << intercept_z );
                            }
                            else
                            {
                                z_lisa.emplace_back(-999.); 
                            }
                        } 
                    }
                    //c4LOG(info, " end mhit");                                   
                }
                else
                {
                    z_lisa.emplace_back(-999.);
                }


                                // Calculate beta after each layer
                // - Define hits of layers and xy position of each hit
                // - Get the dedx for that hit
                // - Get beta before that hit

                // Take beta0, if layer 1 hit then:
                //      Translate beta in energy
                //      Decrease beta(energy) by de/dx*diamond thickness
                //      Calculate back again beta from new energy
            }

            int layers_fired = 0;
            for (int i = 0; i < layer_number; i++)
            {
                if(multiplicity[i] != 0) layers_fired++;
            }
            //c4LOG(info, " multiplicity L1 : " << multiplicity[0]);
            // c4LOG(info, " multiplicity L2 : " << multiplicity[1]);
            // c4LOG(info, " multiplicity L3 : " << multiplicity[2]);
            // c4LOG(info, " multiplicity L4 : " << multiplicity[3]);
            // c4LOG(info, " multiplicity L5 : " << multiplicity[4]);

            auto & entry = lisaHitArray->emplace_back();
            entry.SetAll(
                lisaCalItem.Get_wr_t(),
                lisaCalItem.Get_wr_id(),
                lisaCalItem.Get_board_id(),
                lisaCalItem.Get_layer_id(),
                lisaCalItem.Get_city(),
                lisaCalItem.Get_xposition(),
                lisaCalItem.Get_yposition(),
                lisaCalItem.Get_energy(),
                lisaCalItem.Get_energy_MWD(),
                lisaCalItem.Get_trace_febex(),
                lisaCalItem.Get_trace_x(),
                lisaCalItem.Get_energy_GM(),
                lisaCalItem.Get_energy_MWD_GM(),
                lisaCalItem.Get_de_dx(),
                lisaCalItem.Get_de_dx_GM(),
                z_lisa,
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

}

void LisaCal2Hit::FinishTask()
{
}