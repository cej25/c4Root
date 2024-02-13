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
}

GermaniumRaw2Cal::~GermaniumRaw2Cal(){
    c4LOG(info, "Deleting GermaniumRaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
    if (ftime_machine_array) delete ftime_machine_array;
}


/*
A way to pass the TimeMachineChannels to the class, should be done after the mapping and before Init.
*/
void GermaniumRaw2Cal::SetTimeMachineChannels(int ftime_machine_undelayed_detector_id, int ftime_machine_undelayed_crystal_id, int ftime_machine_delayed_detector_id, int ftime_machine_delayed_crystal_id){
    time_machine_delayed_detector_id=ftime_machine_delayed_detector_id;
    time_machine_undelayed_detector_id=ftime_machine_undelayed_detector_id;
    time_machine_delayed_crystal_id=ftime_machine_delayed_crystal_id;
    time_machine_undelayed_crystal_id=ftime_machine_undelayed_crystal_id;
} 

void GermaniumRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Init - register data to output tree and gets input data.
*/
InitStatus GermaniumRaw2Cal::Init(){
    //grabs instance managers and handles.

    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
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
Reads a file containing the detector mappings. To be called before Init. Assumed structure of the file is:
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (febex module id) (febex channel id) (detector id) (crystal id)

Raises a fatal error if the module and channel numbers are not unique.
*/
Bool_t GermaniumRaw2Cal::SetDetectorMapFile(TString filename){
    c4LOG(info, "Reading Detector map");

    std::ifstream detector_map_file (filename);

    int rfebex_module,rfebex_channel,rdetector_id,rcrystal_id; 
    
    //assumes the first line in the file is num-modules used
    while(!detector_map_file.eof()){
        if(detector_map_file.peek()=='#') detector_map_file.ignore(256,'\n');
        else{
            detector_map_file >> rfebex_module >> rfebex_channel >> rdetector_id >> rcrystal_id;
            std::pair<int,int> febex_mc = {rfebex_module,rfebex_channel};
            std::pair<int,int> ge_cd = {rdetector_id,rcrystal_id};
            
            //fails? check!
            //auto it = detector_mapping.find(febex_mc);
            //if (it != detector_mapping.end()) c4LOG(fatal,Form("Detector mapping not unique. Multiple entries of (febex module id = %i) (febex channel id = %i)",rfebex_module,rfebex_channel));

            detector_mapping.insert(std::pair<std::pair<int,int>,std::pair<int,int>>{febex_mc,ge_cd});
            detector_map_file.ignore(256,'\n');

            auto it = detector_mapping.find(febex_mc);
            if (it != detector_mapping.end()) c4LOG(fatal,Form("Detector mapping not unique. Multiple entries of (febex module id = %i) (febex channel id = %i)",rfebex_module,rfebex_channel));
        }
    }
    DetectorMap_loaded = 1;     
    detector_map_file.close();  
    return 0; 
};


/*
Reads a file containing the detector calibrations. To be called before Init. Assumed structure of the file is:
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (Ge detector id) (Ge crystal id) (a1/slope) (a0/offset)

Raises a fatal error if the detector numbers are not unique.
*/
Bool_t GermaniumRaw2Cal::SetDetectorCalFile(TString filename){

    c4LOG(info, "Reading Calibration coefficients.");


    std::ifstream cal_map_file (filename);

    int rdetector_id,rcrystal_id; // temp read variables
    double a0,a1;
    
    //assumes the first line in the file is num-modules used
    while(!cal_map_file.eof()){
        if(cal_map_file.peek()=='#') cal_map_file.ignore(256,'\n');
        else{
            cal_map_file >> rdetector_id >> rcrystal_id >> a1 >> a0;
            std::pair<int,int> detector_crystal = {rdetector_id,rcrystal_id};
            std::pair<double,double> cals = {a0,a1};
            calibration_coeffs.insert(std::pair<std::pair<int,int>,std::pair<double,double>>{detector_crystal,cals});
            cal_map_file.ignore(256,'\n');

            auto it = calibration_coeffs.find(detector_crystal);
            if (it != calibration_coeffs.end()) c4LOG(fatal,Form("Detector calibration not unique. Multiple entries of (Ge detector id = %i) (Ge crystal id = %i)",rdetector_id,rcrystal_id));

        }
    }
    DetectorCal_loaded = 1;
    cal_map_file.close();
    return 0; 
};

/*
Prints detector map to console.
*/
void GermaniumRaw2Cal::PrintDetectorMap(){
    if (DetectorMap_loaded){
        for (const auto& entry : detector_mapping){
            std::cout << "FEBEXMODULE: " << entry.first.first << " FEBEXCHANNEL " << entry.first.second;
            std::cout << " DETECTORID: " << entry.second.first << " CRYSTALID: " << entry.second.second << "\n";
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
    if (DetectorCal_loaded){
        for (const auto& entry : calibration_coeffs){
            std::cout << "DETECTORID: " << entry.first.first << " CRYSTALID: " << entry.first.second;
            std::cout << " a0: " << entry.second.first << " a1: " << entry.second.second << "\n";
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
void GermaniumRaw2Cal::Exec(Option_t* option){
    if (funcal_data && funcal_data->GetEntriesFast() > 0){
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){
            funcal_hit = (GermaniumFebexData*)funcal_data->At(ihit);
            //do the detector mapping here:
            if (DetectorMap_loaded){
                std::pair<int,int> unmapped_det {funcal_hit->Get_board_id(), funcal_hit->Get_channel_id()};
                
                if (auto result_find = detector_mapping.find(unmapped_det); result_find != detector_mapping.end()){
                detector_id = result_find->second.first; //.find returns an iterator over the pairs matching key.
                crystal_id = result_find->second.second;
                }else{
                    c4LOG(fatal, "Detector mapping not complete - exiting.");
                }

                //only do calibrations if mapping is functional:
                if (DetectorCal_loaded){
                    std::pair<int,int> calibdet {detector_id, crystal_id};
                    if (auto result_find_cal = calibration_coeffs.find(calibdet); result_find_cal != calibration_coeffs.end()){
                    double a0 = result_find_cal->second.first; //.find returns an iterator over the pairs matching key.
                    double a1 = result_find_cal->second.second;
                    channel_energy_cal = a0 + a1*(double) funcal_hit->Get_channel_energy();
                    }else{
                        //c4LOG(fatal, "Detector Calibrations not set - please set this using SetCalibrationMap to use the Cal Task.");
                        channel_energy_cal = funcal_hit->Get_channel_energy();
                        continue;
                    }
                }
            }
            else{ //no map and cal: ->
                c4LOG(fatal, "Detector Mapping not set - please set this using SetDetectorMap to use the Cal Task.");
            }

            if (detector_id == time_machine_delayed_detector_id & crystal_id == time_machine_delayed_crystal_id){
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData(0,funcal_hit->Get_channel_trigger_time(),funcal_hit->Get_wr_subsystem_id(),funcal_hit->Get_wr_t());
                continue;
            }
            else if (detector_id == time_machine_undelayed_detector_id & crystal_id == time_machine_undelayed_crystal_id){
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData(funcal_hit->Get_channel_trigger_time(),0,funcal_hit->Get_wr_subsystem_id(),funcal_hit->Get_wr_t());
                continue;
            }

            new ((*fcal_data)[fcal_data->GetEntriesFast()]) GermaniumCalData(
                funcal_hit->Get_event_trigger_time(),
                funcal_hit->Get_pileup(),
                funcal_hit->Get_overflow(),
                funcal_hit->Get_channel_trigger_time(),
                channel_energy_cal,
                crystal_id,
                detector_id,
                funcal_hit->Get_wr_subsystem_id(),
                funcal_hit->Get_wr_t());
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
