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
 *                        J.E.L. Larsson, C.E. Jones                          *
 *                                06.05.25                                    *
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
#include "GermaniumRaw2Cal.h"

/*
Empty constructor for FairRoot.
*/
GermaniumRaw2Cal::GermaniumRaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
funcal_data(new TClonesArray("GermaniumFebexData")),
fcal_data(new TClonesArray("GermaniumCalData")),
ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
GermaniumRaw2Cal::GermaniumRaw2Cal(const TString& name, Int_t verbose) 
    : FairTask(name, verbose),
    fNEvents(0),
    header(nullptr),
    fOnline(kFALSE),
    funcal_data(new TClonesArray("GermaniumFebexData")),
    fcal_data(new TClonesArray("GermaniumCalData")),
    ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumRaw2Cal::~GermaniumRaw2Cal(){
    c4LOG(info, "Deleting GermaniumRaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
    if (ftime_machine_array) delete ftime_machine_array;
}



void GermaniumRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Init - register data to output tree and gets input data.
*/
InitStatus GermaniumRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("GermaniumFebexData");
    c4LOG_IF(fatal, !funcal_data, "Germanium branch of GermaniumFebexData not found.");
 
    // needs to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("GermaniumCalData", "Germanium Cal Data", fcal_data, !fOnline);
    FairRootManager::Instance()->Register("GermaniumTimeMachineData", "Time Machine Data", ftime_machine_array, !fOnline);
    
    fcal_data->Clear();

    return kSUCCESS;
}

/*
Prints detector map to console.
*/
void GermaniumRaw2Cal::PrintDetectorMap(){
    if (germanium_configuration->MappingLoaded()){
        for (const auto& entry : germanium_configuration->Mapping()){
            std::cout << "FEBEXMODULE: " << entry.first.first << " FEBEXCHANNEL " << entry.first.second;
            std::cout << " DETECTORID: " << entry.second.first << " CRYSTALID: " << entry.second.second << " OF N = " << germanium_configuration->CrystalsPerDetector(entry.second.first) << "CRYSTALS" << "\n";
        }
    }
    else{
        c4LOG(info, "Detector map is not load. Cannot print.");
    }
}

/*
Prints calibration coeffs to console.
*/
void GermaniumRaw2Cal::PrintDetectorCal(){
    if (germanium_configuration->CalibrationCoefficientsLoaded()){
        for (const auto& entry : germanium_configuration->CalibrationCoefficients()){
            std::cout << "DETECTORID: " << entry.first.first << " CRYSTALID: " << entry.first.second;
            std::cout << " a0: " << entry.second.at(0) << " a1: " << entry.second.at(1) << " a2:" << entry.second.at(2) << "\n";
        }
    }
    else{
        c4LOG(info, "Cal map is not load. Cannot print.");
    }
}        

/*
Analysis event loop. 
Fatal error if detector map is not set. If calibration coeffs are not written, simply the uncalibrated energies are written.

Picks out the TimeMachine.
*/
void GermaniumRaw2Cal::Exec(Option_t* option)
{
    if (funcal_data && funcal_data->GetEntriesFast() > 0)
    {
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {
            funcal_hit = (GermaniumFebexData*)funcal_data->At(ihit);
            
            //do the detector mapping here:
            if (germanium_configuration->MappingLoaded())
            {
                std::pair<int,int> unmapped_det {funcal_hit->Get_board_id(), funcal_hit->Get_channel_id()};
                
                if (germanium_configuration->Mapping().count(unmapped_det) > 0)
                {
                    detector_id = germanium_configuration->Mapping().at(unmapped_det).first; //.find returns an iterator over the pairs matching key.
                    crystal_id = germanium_configuration->Mapping().at(unmapped_det).second;

                    if (detector_id == -1 || crystal_id == -1) continue; //skip

                }
                else continue;// simply ignore unmapped items.

                //only do calibrations if mapping is functional:
                if (germanium_configuration->CalibrationCoefficientsLoaded())
                {
                    std::pair<int,int> calibdet {detector_id, crystal_id};
                    if (germanium_configuration->CalibrationCoefficients().count(calibdet) > 0){
                    double a0 = germanium_configuration->CalibrationCoefficients().at(calibdet).at(0); //.find returns an iterator over the pairs matching key.
                    double a1 = germanium_configuration->CalibrationCoefficients().at(calibdet).at(1);
                    double a2 = germanium_configuration->CalibrationCoefficients().at(calibdet).at(2);
                    channel_energy_cal = a0 + a1*(double) funcal_hit->Get_channel_energy() + a2*(double) funcal_hit->Get_channel_energy()*(double) funcal_hit->Get_channel_energy();
                    }else{
                        //c4LOG(fatal, "Detector Calibrations not set - please set this using SetCalibrationMap to use the Cal Task.");
                        channel_energy_cal = funcal_hit->Get_channel_energy();
                        //continue;
                    }
                }
            }
            else c4LOG(fatal, "Detector Mapping not set - please set this."); //no map and cal: ->


            if (detector_id == germanium_configuration->TM_Delayed()){
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData(0,funcal_hit->Get_channel_trigger_time(),funcal_hit->Get_wr_subsystem_id(),funcal_hit->Get_wr_t());
                //continue;
            }
            else if (detector_id == germanium_configuration->TM_Undelayed()){
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData(funcal_hit->Get_channel_trigger_time(),0,funcal_hit->Get_wr_subsystem_id(),funcal_hit->Get_wr_t());
                //continue;
            }

            //allow pileups of sci41
            // if (funcal_hit->Get_pileup() == true){
                // if (germanium_configuration->IsDetectorAuxilliary(detector_id) == false || VetoPileupSCI41 == true){
                //     continue;
                // }
            // }

            // std::cout << "wr germanium: " << funcal_hit->Get_wr_t() << std::endl;
            new ((*fcal_data)[fcal_data->GetEntriesFast()]) GermaniumCalData(
                funcal_hit->Get_trigger(),
                funcal_hit->Get_event_trigger_time(),
                funcal_hit->Get_pileup(),
                funcal_hit->Get_overflow(),
                funcal_hit->Get_channel_trigger_time(),
                channel_energy_cal,
                crystal_id,
                detector_id,
                funcal_hit->Get_wr_subsystem_id(),
                funcal_hit->Get_wr_t(),
                ((int64_t)funcal_hit->Get_wr_t() + ((int64_t)funcal_hit->Get_channel_trigger_time() - (int64_t)funcal_hit->Get_event_trigger_time()))
                );
            
            fNEvents++;
        }
    }
}

/*
Very important function - all TClonesArray must be cleared after each event.
*/
void GermaniumRaw2Cal::FinishEvent(){
    funcal_data->Clear();
    fcal_data->Clear();
    ftime_machine_array->Clear();
};



ClassImp(GermaniumRaw2Cal)