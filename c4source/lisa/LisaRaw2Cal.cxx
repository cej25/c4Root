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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
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
#include "LisaRaw2Cal.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>

LisaRaw2Cal::LisaRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaCalArray(new std::vector<LisaCalItem>)
{
    lisa_config = TLisaConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();   
}



LisaRaw2Cal::~LisaRaw2Cal()
{
    delete lisaArray;
    delete lisaCalArray;
}

InitStatus LisaRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");
    
    mgr->RegisterAny("LisaCalData", lisaCalArray, !fOnline);

    return kSUCCESS;
}


//:::
void LisaRaw2Cal::PrintDetectorGainM()
{
    if (lisa_config->GainMatchingLoaded())
    {
        for (const auto& entry : lisa_config->GainMatchingCoefficients())
        {
            std::cout << "Detector (#layer,#x,#y): " << entry.first.first << " " << entry.first.second.first << " " << entry.first.second.second << "\n";
            std::cout << " slope : " << entry.second.first << " intercept : " << entry.second.second << "\n";
        }
    }
    else
    {
        c4LOG(info, "Gain matching parameters are not loaded");
    }
}   
//:::



void LisaRaw2Cal::Exec(Option_t* option)
{
    lisaCalArray->clear();

    for (auto const & lisaItem : *lisaArray)
    {          
        std::pair<int, int> unmapped_channel = {lisaItem.Get_board_id(), lisaItem.Get_channel_id_traces()};
        //Get_channel_id_traces() when taking the id information from the trace header
        //Get_channel_id() when taking the id information from the header

        if (lisa_config->MappingLoaded())
        {
            if (detector_mapping.count(unmapped_channel) > 0)
            {
                int layer_id = detector_mapping.at(unmapped_channel).first.first;
                TString city = detector_mapping.at(unmapped_channel).first.second; //Debugging. std::string to Tstring 
                int xpos = detector_mapping.at(unmapped_channel).second.first;
                int ypos = detector_mapping.at(unmapped_channel).second.second;
                uint64_t EVTno = header->GetEventno();

                //std::cout << "Layer, x , y: (" << layer_id << ", (" << xpos << ", " << ypos << "))"<< std::endl;


                if (lisa_config->GainMatchingLoaded())
                {
                    //std::cout<< " Hello 1 " << "\n";
                    energy_GM = 0;
                    std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> GM_coeffs = lisa_config->GainMatchingCoefficients();
                    std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer_id, std::make_pair(xpos, ypos) );
                    //std::cout<< " Hello 2 " << "\n";

                    /*
                    std::cout << "Contents of GM_coeffs:" << std::endl;
                    for (const auto& entry : GM_coeffs) 
                    {
                        std::cout << "Key: (" << entry.first.first << ", (" << entry.first.second.first << ", " << entry.first.second.second << "))";
                        std::cout << " Value: (" << entry.second.first << ", " << entry.second.second << ")" << std::endl;
                    }
                    */

                    /*
                    //loop through key and read coeff
                    bool found = false; 
                    for (const auto& entry : GM_coeffs )
                    {
                        if (entry.first == detector_lxy)
                        {
                            std::pair<double,double> coeffs = entry.second;
                            slope = coeffs.first;
                            intercept = coeffs.second;

                            energy_GM = intercept + slope*lisaItem.Get_channel_energy();
                            found = true;
                            std::cout << " Energy GM - in loop " << "\n";
                            std::cout << " slope in loop " << slope << " intercepts in loop " << intercept << "\n";
                            break;

                        }
                    }
                    */
                    
                    if (auto result_find_GM = GM_coeffs.find(detector_lxy); result_find_GM != GM_coeffs.end()) 
                    {
                        std::pair<double,double> coeffs = result_find_GM->second; //find returns an iterator over the pairs matching key
                        slope = coeffs.first;
                        intercept = coeffs.second;
                        
                        energy_GM = intercept + slope*lisaItem.Get_channel_energy(); 

                        //std::cout<< " Energy GM - in loop " << "\n";
                    }
                    
                }
                        
                auto & entry = lisaCalArray->emplace_back();

                entry.SetAll(
                    lisaItem.Get_wr_t(),
                    layer_id,
                    city,
                    xpos,
                    ypos,
                    lisaItem.Get_channel_energy(),
                    lisaItem.Get_trace(),
                    energy_GM,
                    lisaItem.Get_board_event_time(),
                    lisaItem.Get_channel_time(),
                    EVTno,
                    lisaItem.Get_pileup(),
                    lisaItem.Get_overflow()
                );
                //c4LOG(info,"event num: "<< EVTno);

            }
            else c4LOG(warn, "Unmapped data? Board: "  << unmapped_channel.first << " Channel: " << unmapped_channel.second);

        }


    }
}

void LisaRaw2Cal::FinishEvent()
{

}

void LisaRaw2Cal::FinishTask()
{
}