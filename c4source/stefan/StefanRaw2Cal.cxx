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
 *                         C.E. Jones, G. Kosir                               *
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
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "StefanRaw2Cal.h"

/*
Empty constructor for FairRoot.
*/
StefanRaw2Cal::StefanRaw2Cal()
    :   FairTask() 
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   StefanHit(new std::vector<StefanCalItem>)
    // OTHER STUFF 
    // ,   ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    stefan_config = TStefanConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
StefanRaw2Cal::StefanRaw2Cal(const TString& name, Int_t verbose) 
    :   FairTask() 
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   StefanHit(new std::vector<StefanCalItem>)
    // OTHER STUFF 
    // ,   ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    stefan_config = TStefanConfiguration::GetInstance();
}

StefanRaw2Cal::~StefanRaw2Cal()
{
    c4LOG(info, "Deleting StefanRaw2Cal task");
}


/*
Init - register data to output tree and gets input data.
*/
InitStatus StefanRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
    
    
    StefanArray = mgr->InitObjectAs<decltype(StefanArray)>("StefanFebexData");
    c4LOG_IF(fatal, !StefanArray, "Branch StefanFebexData not found!");
 	
 	
    mgr->RegisterAny("StefanCalData", StefanHit, !fOnline);

    detector_mapping = stefan_config->Mapping();
    calibration_coeffs = stefan_config->CalibrationCoefficients();
    // needs to have the name of the detector subsystem here:
    // register stefan etc
    // FairRootManager::Instance()->Register("StefanTimeMachineData", "Time Machine Data", ftime_machine_array, !fOnline);

    // do we need TM for stefan lol
    
    // fcal_data->Clear();

    return kSUCCESS;
}


/*
Analysis event loop. 
Fatal error if detector map is not set. If calibration coeffs are not written, simply the uncalibrated energies are written.

Picks out the TimeMachine.
*/
void StefanRaw2Cal::Exec(Option_t* option)
{
    // process stuff, we can re-steal from germ or bb7 but...better to leave blank rn


    if (StefanArray->size() > 0) nTotalStefan++;

    // std::cout << "EVENT :: " << std::endl;
    for (auto const & StefanItem : *StefanArray)
    {
        std::pair<int, int> unmapped_channel = {StefanItem.Get_board_id(), StefanItem.Get_channel_id()};
        //Get_channel_id_traces() when taking the id information from the trace header
        //Get_channel_id() when taking the id information from the header

        if (stefan_config->MappingLoaded())
        {
            if (detector_mapping.count(unmapped_channel) > 0)
            {   
                int dssd = detector_mapping.at(unmapped_channel).first;
                int side = detector_mapping.at(unmapped_channel).second.first;
                int strip = detector_mapping.at(unmapped_channel).second.second;

                // std::cout << "dssd:: " << dssd << std::endl;
                // std::cout << "side:: " << side << std::endl;
                // std::cout << "strip:: " << strip << std::endl;

                uint32_t energy = StefanItem.Get_channel_energy();
                double energy_calib = energy;

                if (stefan_config->CalibrationLoaded())
                {
                    std::pair<int, std::pair<int, int>> mapped_det = std::make_pair(dssd, std::make_pair(side, strip));
                    if (calibration_coeffs.count(mapped_det) > 0)
                    {   
                        energy_calib = energy * calibration_coeffs.at(mapped_det);
                    }
                }

               
                Long64_t absolute_time = StefanItem.Get_wr_t() + StefanItem.Get_channel_time() - StefanItem.Get_board_event_time();


                // implant 
                auto & entry = StefanHit->emplace_back();
                entry.SetAll(
                    StefanItem.Get_wr_t(),
                    dssd,
                    side,
                    strip,
                    StefanItem.Get_channel_energy(),
                    //StefanItem.Get_trace(),
                    energy_calib,
                    StefanItem.Get_board_event_time(),
                    StefanItem.Get_channel_time(),
                    absolute_time,
                    StefanItem.Get_pileup(),
                    StefanItem.Get_overflow()
                );
            
                
            }
            
            // else c4LOG(warn, "Unmapped data? Board: "  << unmapped_channel.second.first << " Channel: " << unmapped_channel.second.second);

            // possibly stuff with residuals

        }
    }
}


/*
Very important function - all TClonesArray must be cleared after each event.
*/
void StefanRaw2Cal::FinishEvent()
{
    // clear
    count_in_event = 0;
    StefanHit->clear();
};


ClassImp(StefanRaw2Cal)