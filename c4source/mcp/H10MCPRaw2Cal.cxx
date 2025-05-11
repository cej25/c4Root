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
 *                              C.E. Jones                                    *
 *                               06.05.25                                     *
 ******************************************************************************/

// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "c4Logger.h"
#include "TClonesArray.h"
#include <chrono>

#include "H10MCPRaw2Cal.h"

/*
empty constructor required for FairRoot.
*/
H10MCPRaw2Cal::H10MCPRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   funcal_data(new TClonesArray("H10MCPTwinpeaksData"))
    ,   fcal_data(new TClonesArray("H10MCPTwinpeaksCalData"))
    ,   ftime_machine_array(new TClonesArray("TimeMachineData"))
{
   mcp_config = TH10MCPConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
H10MCPRaw2Cal::H10MCPRaw2Cal(const TString& name, Int_t verbose) 
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE) 
    ,   funcal_data(new TClonesArray("H10MCPTwinpeaksData"))
    ,   fcal_data(new TClonesArray("H10MCPTwinpeaksCalData"))
    ,   ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}
/*
Clearing old constructed objects.
*/
H10MCPRaw2Cal::~H10MCPRaw2Cal()
{
    c4LOG(info, "Deleting H10MCPRaw2Cal task");
}


/*
Initializer called by the FairRoot manager. Gets the required FairRootManager objects to read and register the data to be written to the tree.
*/
InitStatus H10MCPRaw2Cal::Init()
{  
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksData");
    c4LOG_IF(fatal, !funcal_data, "Fatima branch of H10MCPTwinpeaksData not found.");
    
    //need to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("H10MCPTwinpeaksCalData", "H10MCPTwinpeaksCalDataFolder", fcal_data, !fOnline);
    FairRootManager::Instance()->Register("H10MCPTimeMachineData", "H10MCPTimeMachineDataFolder", ftime_machine_array, !fOnline);

    fcal_data->Clear();
    funcal_data->Clear();


    return kSUCCESS;
};
       

/*
The event loop executable. This is where the events are analyzed. Only used implicitly by FairRoot during Run().

Further the hits are matched slow + fast and assigned from the internal Twinpeaks channnel number to the detector number if DetectorMap is loaded.
Assumes that fast hits always preceedes slow hits. 

If no detector map is set then be careful with how the mapping happens: tamex module id * number of tamex modules + channel id.

Writes the times in ns!
*/
void H10MCPRaw2Cal::Exec(Option_t* option)
{
 

    // std::cout << "EVENT :: " << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    if (funcal_data && funcal_data->GetEntriesFast() > 1)
    { // only get events with two hits or more
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
 	    for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {

            H10MCPTwinpeaksData* first_hit_in_fast_channel = (H10MCPTwinpeaksData*)funcal_data->At(ihit);
             
            // under the assumption fast-slow always follows:
            //assume that only matched lead-trail hits are written.
            if (first_hit_in_fast_channel->Get_ch_ID()%2==0) {continue;} //get the first odd numbered channel

            int hits_in_fast_channel = 1;
            int hits_in_slow_channel = 0;

            int look_ahead_counter = 1;
            bool all_hits_in_fast_slow_found = false;
            while (!all_hits_in_fast_slow_found)
            {
                if (ihit+look_ahead_counter >= event_multiplicity) break;
                H10MCPTwinpeaksData* this_hit = (H10MCPTwinpeaksData*)funcal_data->At(ihit + look_ahead_counter);

                if (this_hit->Get_ch_ID() == first_hit_in_fast_channel->Get_ch_ID() && this_hit->Get_board_id() == first_hit_in_fast_channel->Get_board_id()) hits_in_fast_channel++;
                else if (this_hit->Get_ch_ID() == first_hit_in_fast_channel->Get_ch_ID()+1 && this_hit->Get_board_id() == first_hit_in_fast_channel->Get_board_id()) hits_in_slow_channel++;
                else all_hits_in_fast_slow_found = true;
                look_ahead_counter++;
            }


            // if (hits_in_fast_channel != hits_in_slow_channel) 
            // {
            //     //break condition - cant recover.
            //     ihit = hits_in_fast_channel + hits_in_slow_channel + ihit - 1; // -1 cus it adds one when restarting the for-loop
            //     // continue;
            // }

            // CEJ:: need to add logic for when missing slow hits. After which ^continue; can be removed.

            // TAMEX working normally
            if (hits_in_fast_channel == hits_in_slow_channel)
            {
                for (int hitnr = 0; hitnr<hits_in_fast_channel; hitnr++)
                {

                    funcal_hit = (H10MCPTwinpeaksData*)funcal_data->At(ihit+hitnr);
                    funcal_hit_next = (H10MCPTwinpeaksData*)funcal_data->At(ihit+hitnr+hits_in_fast_channel);
                    
                    if (funcal_hit_next->Get_ch_ID() != funcal_hit->Get_ch_ID()+1)
                    {
                        fNunmatched++;
                        continue;
                    }

                    if (funcal_hit_next->Get_board_id() != funcal_hit->Get_board_id())
                    {
                        continue;
                    }

                    if (mcp_config->MappingLoaded())
                    {
                        std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> fmap;
                        fmap = mcp_config->Mapping();
                        std::pair<int, int> unmapped_det { funcal_hit->Get_board_id(), (funcal_hit->Get_ch_ID()+1)/2};
                        std::cout << "board:: " << funcal_hit->Get_board_id() << " ::  channel::  " << (funcal_hit->Get_ch_ID()+1)/2 << std::endl;
                        if (auto result_find = fmap.find(unmapped_det); result_find != fmap.end())
                        {
                            mcp_id = result_find->second.first; // 0/1 [1/2]
                            type = result_find->second.second.first; // 0/1/2 [T/X/Y]
                            number = result_find->second.second.second; // 0/1 [1/2]
                                    
                            // std::cout << "MCP: " <<mcp_id << " - TYPE :: " << type << " - NUMBER:: " << number << std::endl;

                            if (mcp_id == -1) { fNunmatched++; continue; }
                        }
                        else
                        {
                            mcp_id = -1;
                            type = -1;
                            number = -1;
                        }
                    }
                    else
                    {
                        mcp_id = -1;
                        type = -1;
                        number = -1;
                    }
                    
                    if (funcal_hit_next->Get_trail_epoch_counter() == 0 || funcal_hit_next->Get_lead_epoch_counter() == 0) continue; // missing trail in either
                    if (funcal_hit->Get_trail_epoch_counter() == 0 || funcal_hit->Get_lead_epoch_counter() == 0) continue; // missing trail in either
                    //if (funcal_hit_next->Get_trail_coarse_T() == 0 || funcal_hit_next->Get_lead_coarse_T() == 0) continue; // missing trail in either
                    //if (funcal_hit->Get_trail_fine_T() == 0 || funcal_hit->Get_lead_fine_T() == 0) continue; // missing trail in either

                    // Round-off error safe:
                    fast_lead_epoch = (Long64_t)(funcal_hit->Get_lead_epoch_counter()) * 10240;

                    fast_lead_time = (Double_t)(funcal_hit->Get_lead_coarse_T()) * 5.0
                                - (Double_t)(funcal_hit->Get_lead_fine_T());

                    fast_trail_epoch = (Long64_t)(funcal_hit->Get_trail_epoch_counter()) * 10240;

                    fast_trail_time = (Double_t)(funcal_hit->Get_trail_coarse_T()) * 5.0
                                    - (Double_t)(funcal_hit->Get_trail_fine_T());

                    slow_lead_epoch = (Long64_t)(funcal_hit_next->Get_lead_epoch_counter()) * 10240;

                    slow_lead_time = (Double_t)(funcal_hit_next->Get_lead_coarse_T()) * 5.0
                                    -(Double_t)(funcal_hit_next->Get_lead_fine_T());

                    slow_trail_epoch = (Long64_t)(funcal_hit_next->Get_trail_epoch_counter()) * 10240;

                    slow_trail_time = (Double_t)(funcal_hit_next->Get_trail_coarse_T()) * 5.0
                                    - (Double_t)(funcal_hit_next->Get_trail_fine_T());

                    
                    fast_ToT =  (Double_t)(funcal_hit->Get_trail_epoch_counter() - funcal_hit->Get_lead_epoch_counter()) * 10.24e3 +  (Double_t)((Int_t)funcal_hit->Get_trail_coarse_T() - (Int_t)funcal_hit->Get_lead_coarse_T()) * 5.0 - (funcal_hit->Get_trail_fine_T() - funcal_hit->Get_lead_fine_T());
                    // find the slow ToT without encountering round-off errors:
                    slow_ToT =  (Double_t)(funcal_hit_next->Get_trail_epoch_counter() - funcal_hit_next->Get_lead_epoch_counter()) * 10.24e3 +  (Double_t)((Int_t)funcal_hit_next->Get_trail_coarse_T() - (Int_t)funcal_hit_next->Get_lead_coarse_T()) * 5.0 - (funcal_hit_next->Get_trail_fine_T() - funcal_hit_next->Get_lead_fine_T());
                    
                    absolute_event_time = (Long64_t)(funcal_hit->Get_wr_t() + (Long64_t)(((Int_t)funcal_hit->Get_lead_epoch_counter() - (Int_t)funcal_hit->Get_accepted_lead_epoch_counter()) * 10.24e3 + ((Int_t)funcal_hit->Get_lead_coarse_T() - (Int_t)funcal_hit->Get_accepted_lead_coarse_T()) * 5.0 - (Int_t)(funcal_hit->Get_lead_fine_T() - funcal_hit->Get_accepted_lead_fine_T())));

                    if (mcp_config->MappingLoaded())
                    {
                        if (mcp_config->CalibrationCoefficientsLoaded())
                        { // check
                            std::map<int,std::vector<double>> calibration_coeffs = mcp_config->CalibrationCoefficients();
                            if (auto result_find_cal = calibration_coeffs.find(detector_id); result_find_cal != calibration_coeffs.end()){
                                std::vector<double> coeffs = result_find_cal->second; //.find returns an iterator over the pairs matching key.
                                a0 = coeffs.at(0);
                                a1 = coeffs.at(1);
                                a2 = coeffs.at(2);
                                a3 = coeffs.at(3);
                                
                                energy = a0 + a1*slow_ToT + a2*slow_ToT*slow_ToT + a3*slow_ToT*slow_ToT*slow_ToT; 
                            }else{
                                energy = slow_ToT;
                            }
                        
                        }
                        else
                        {
                            energy = slow_ToT;
                        }
                    }

                    // if (mcp_config->GainShiftsLoaded() && !(mcp_config->IsDetectorAuxilliary(detector_id)))
                    // {
                    //     energy = energy * mcp_config->GetGainShift(detector_id,funcal_hit->Get_wr_t());
                    // } 

                    if (((detector_id == mcp_config->TM_Delayed()) || (detector_id == mcp_config->TM_Undelayed())) && mcp_config->TM_Delayed() != 0 && mcp_config->TM_Undelayed() != 0)
                    {
                        new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData((detector_id == mcp_config->TM_Undelayed()) ? (fast_lead_time) : (0), (detector_id == mcp_config->TM_Undelayed()) ? (0) : (fast_lead_time), funcal_hit->Get_wr_subsystem_id(), funcal_hit->Get_wr_t());
                    }
                    
                    //std::cout << "setting event.. ??" << std::endl;

                    new ((*fcal_data)[fcal_data->GetEntriesFast()]) H10MCPTwinpeaksCalData(
                                    funcal_hit->Get_trigger(),
                                    funcal_hit->Get_board_id(),
                                    (int)((funcal_hit->Get_ch_ID()+1)/2),
                                    mcp_id,
                                    type,
                                    number,
                                    slow_lead_epoch,
                                    slow_lead_time,
                                    slow_trail_epoch,
                                    slow_trail_time,
                                    fast_lead_epoch,
                                    fast_lead_time,
                                    fast_trail_epoch,
                                    fast_trail_time,
                                    fast_ToT,
                                    slow_ToT,
                                    energy,
                                    funcal_hit->Get_wr_subsystem_id(),
                                    funcal_hit->Get_wr_t(),
                                    absolute_event_time);

                                fNEvents++;
        
                }
            }
            // TAMEX dropping slow trails
            else
            {
                for (int hitnr = 0; hitnr < hits_in_fast_channel; hitnr++)
                {
                    funcal_hit = (H10MCPTwinpeaksData*)funcal_data->At(ihit + hitnr); // fast
                    
                    // do something with slow???? naahh

                    if (mcp_config->MappingLoaded())
                    {
                        std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> fmap;
                        fmap = mcp_config->Mapping();
                        std::pair<int, int> unmapped_det { funcal_hit->Get_board_id(), (funcal_hit->Get_ch_ID()+1)/2};
                        std::cout << "board:: " << funcal_hit->Get_board_id() << " ::  channel::  " << (funcal_hit->Get_ch_ID()+1)/2 << std::endl;
                        if (auto result_find = fmap.find(unmapped_det); result_find != fmap.end())
                        {
                            mcp_id = result_find->second.first; // 0/1 [1/2]
                            type = result_find->second.second.first; // 0/1/2 [T/X/Y]
                            number = result_find->second.second.second; // 0/1 [1/2]
                                    
                            // std::cout << "MCP: " <<mcp_id << " - TYPE :: " << type << " - NUMBER:: " << number << std::endl;

                            if (mcp_id == -1) { fNunmatched++; continue; }
                        }
                        else
                        {
                            mcp_id = -1;
                            type = -1;
                            number = -1;
                        }
                    }
                    else
                    {
                        mcp_id = -1;
                        type = -1;
                        number = -1;
                    }
                    
                    if (funcal_hit->Get_trail_epoch_counter() == 0 || funcal_hit->Get_lead_epoch_counter() == 0) continue; // missing trail in either


                    // Round-off error safe:
                    fast_lead_epoch = (Long64_t)(funcal_hit->Get_lead_epoch_counter()) * 10240;

                    fast_lead_time = (Double_t)(funcal_hit->Get_lead_coarse_T()) * 5.0
                                - (Double_t)(funcal_hit->Get_lead_fine_T());

                    fast_trail_epoch = (Long64_t)(funcal_hit->Get_trail_epoch_counter()) * 10240;

                    fast_trail_time = (Double_t)(funcal_hit->Get_trail_coarse_T()) * 5.0
                                    - (Double_t)(funcal_hit->Get_trail_fine_T());

                    slow_lead_epoch = 0;

                    slow_lead_time = 0;

                    slow_trail_epoch = 0;

                    slow_trail_time = 0;

                    
                    fast_ToT =  (Double_t)(funcal_hit->Get_trail_epoch_counter() - funcal_hit->Get_lead_epoch_counter()) * 10.24e3 +  (Double_t)((Int_t)funcal_hit->Get_trail_coarse_T() - (Int_t)funcal_hit->Get_lead_coarse_T()) * 5.0 - (funcal_hit->Get_trail_fine_T() - funcal_hit->Get_lead_fine_T());
                    // find the slow ToT without encountering round-off errors:
                    slow_ToT =  0;
                    
                    absolute_event_time = (Long64_t)(funcal_hit->Get_wr_t() + (Long64_t)(((Int_t)funcal_hit->Get_lead_epoch_counter() - (Int_t)funcal_hit->Get_accepted_lead_epoch_counter()) * 10.24e3 + ((Int_t)funcal_hit->Get_lead_coarse_T() - (Int_t)funcal_hit->Get_accepted_lead_coarse_T()) * 5.0 - (Int_t)(funcal_hit->Get_lead_fine_T() - funcal_hit->Get_accepted_lead_fine_T())));

                    if (mcp_config->MappingLoaded())
                    {
                        if (mcp_config->CalibrationCoefficientsLoaded())
                        { // check
                            std::map<int,std::vector<double>> calibration_coeffs = mcp_config->CalibrationCoefficients();
                            if (auto result_find_cal = calibration_coeffs.find(detector_id); result_find_cal != calibration_coeffs.end()){
                                std::vector<double> coeffs = result_find_cal->second; //.find returns an iterator over the pairs matching key.
                                a0 = coeffs.at(0);
                                a1 = coeffs.at(1);
                                a2 = coeffs.at(2);
                                a3 = coeffs.at(3);
                                
                                energy = a0 + a1*slow_ToT + a2*slow_ToT*slow_ToT + a3*slow_ToT*slow_ToT*slow_ToT; 
                            }else{
                                energy = slow_ToT;
                            }
                        
                        }
                        else
                        {
                            energy = slow_ToT;
                        }
                    }

                    // if (mcp_config->GainShiftsLoaded() && !(mcp_config->IsDetectorAuxilliary(detector_id)))
                    // {
                    //     energy = energy * mcp_config->GetGainShift(detector_id,funcal_hit->Get_wr_t());
                    // } 

                    if (((detector_id == mcp_config->TM_Delayed()) || (detector_id == mcp_config->TM_Undelayed())) && mcp_config->TM_Delayed() != 0 && mcp_config->TM_Undelayed() != 0)
                    {
                        new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData((detector_id == mcp_config->TM_Undelayed()) ? (fast_lead_time) : (0), (detector_id == mcp_config->TM_Undelayed()) ? (0) : (fast_lead_time), funcal_hit->Get_wr_subsystem_id(), funcal_hit->Get_wr_t());
                    }
                    
                    //std::cout << "setting event.. ??" << std::endl;

                    new ((*fcal_data)[fcal_data->GetEntriesFast()]) H10MCPTwinpeaksCalData(
                                    funcal_hit->Get_trigger(),
                                    funcal_hit->Get_board_id(),
                                    (int)((funcal_hit->Get_ch_ID()+1)/2),
                                    mcp_id,
                                    type,
                                    number,
                                    slow_lead_epoch,
                                    slow_lead_time,
                                    slow_trail_epoch,
                                    slow_trail_time,
                                    fast_lead_epoch,
                                    fast_lead_time,
                                    fast_trail_epoch,
                                    fast_trail_time,
                                    fast_ToT,
                                    slow_ToT,
                                    energy,
                                    funcal_hit->Get_wr_subsystem_id(),
                                    funcal_hit->Get_wr_t(),
                                    absolute_event_time);

                                fNEvents++;
        
                }
            }
        }
        fExecs++;
    }



    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();

}


void H10MCPRaw2Cal::FinishEvent()
{
    // reset output array
    fcal_data->Clear();
};

/*
Some stats are written when finishing.
*/
void H10MCPRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
    c4LOG(info, Form("%i events are unmatched (not written).",fNunmatched));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}


ClassImp(H10MCPRaw2Cal)
