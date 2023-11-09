// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaTwinpeaksData.h"
#include "FatimaTwinpeaksCalData.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include "FatimaRaw2Cal.h"

FatimaRaw2Cal::FatimaRaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
funcal_data(new TClonesArray("FatimaTwinpeaksData")),
fcal_data(new TClonesArray("FatimaTwinpeaksCalData")),
ftime_machine_array(new TClonesArray("TimeMachineData"))
{
}


FatimaRaw2Cal::FatimaRaw2Cal(const TString& name, Int_t verbose) 
    : FairTask(name, verbose),
    fNEvents(0),
    header(nullptr),
    fOnline(kFALSE),
    funcal_data(new TClonesArray("FatimaTwinpeaksData")),
    fcal_data(new TClonesArray("FatimaTwinpeaksCalData")),
    ftime_machine_array(new TClonesArray("TimeMachineData"))
{
}

FatimaRaw2Cal::~FatimaRaw2Cal(){
    c4LOG(info, "Deleting FatimaRaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
    if(ftime_machine_array) delete ftime_machine_array;
}



void FatimaRaw2Cal::SetTimeMachineChannels(int ftime_machine_undelayed_detector_id, int ftime_machine_delayed_detector_id)
{
time_machine_delayed_detector_id = ftime_machine_delayed_detector_id;
time_machine_undelayed_detector_id = ftime_machine_undelayed_detector_id;
} //AFTER mapping.




void FatimaRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FatimaRaw2Cal::Init(){
    //grab instance managers and handles.

    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    //only needed for communicating with the https server i believe
    //FairRunOnline* run = FairRunOnline::Instance();
    //run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksData");
    c4LOG_IF(fatal, !funcal_data, "Fatima branch of FatimaTwinpeaksData not found.");
    

    FairRootManager::Instance()->Register("FatimaTwinpeaksCalData", "Fatima Cal Data", fcal_data, !fOnline);
    //need to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("FatimaTimeMachineData", "Time Machine Data", ftime_machine_array, !fOnline);
    fcal_data->Clear();
    funcal_data->Clear();

    
    //memset(fcal_data, 0, sizeof *fcal_data);


    return kSUCCESS;
}

Bool_t FatimaRaw2Cal::SetDetectorMapFile(TString filename){
    /*
    TODO: Make the reading fail-safe.

    Assumed structure of detector map is 
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (tamex module id) (tamex channel id) (detector id)
    */
    c4LOG(info, "Reading Detector map");

    //std::cout << "reading detector map \n";

    std::ifstream detector_map_file (filename);

    int rtamex_module,rtamex_channel,rdetector_id; // temp read variables
        

    while(!detector_map_file.eof()){
        if(detector_map_file.peek()=='#') detector_map_file.ignore(256,'\n');
        else{
            detector_map_file >> rtamex_module >> rtamex_channel >> rdetector_id;
            c4LOG(info, Form("Reading %i, %i, %i",rtamex_module,rtamex_channel,rdetector_id));
            std::pair<int,int> tamex_mc = {rtamex_module,rtamex_channel};
            detector_mapping.insert(std::pair<std::pair<int,int>,int>{tamex_mc,rdetector_id});
            detector_map_file.ignore(256,'\n');
            //TODO: implement a check to make sure keys are unique.
        }
    }
    DetectorMap_loaded = 1;
    detector_map_file.close();  
    return 0; 
};

Bool_t FatimaRaw2Cal::SetDetectorCalFile(TString filename){

    //TODO: Make the reading fail-safe.
    //
    //Assumed structure of detector map is 
    //- aribtrary lines of comments starting with #
    //- each entry is a line with four numbers: (tamex module id) (tamex channel id) (detector id) (crystal id)
    //
    c4LOG(info, "Reading Calibration coefficients.");


    std::ifstream cal_map_file (filename);

    int rdetector_id; // temp read variables
    double a0,a1;
    
    //assumes the first line in the file is num-modules used
    while(!cal_map_file.eof()){
        if(cal_map_file.peek()=='#') cal_map_file.ignore(256,'\n');
        else{
            cal_map_file >> rdetector_id >> a1 >> a0;
            std::pair<double,double> cals = {a0,a1};
            calibration_coeffs.insert(std::pair<int,std::pair<double,double>>{rdetector_id,cals});
            cal_map_file.ignore(256,'\n');
            //TODO: implement a check to make sure keys are unique.
        }
    }
    DetectorCal_loaded = 1;
    cal_map_file.close();  
    return 0; 
};

void FatimaRaw2Cal::PrintDetectorMap(){
    if (DetectorMap_loaded){
        for (const auto& entry : detector_mapping){
            std::cout << "tamexMODULE: " << entry.first.first << " tamexCHANNEL " << entry.first.second;
            std::cout << " DETECTORID: " << entry.second << "\n";
        }
    }
    else{
        c4LOG(info, "Detector map is not load. Cannot print.");
    }
}

void FatimaRaw2Cal::PrintDetectorCal(){
    if (DetectorCal_loaded){
        for (const auto& entry : calibration_coeffs){
            std::cout << "DETECTORID: " << entry.first;
            std::cout << " a0: " << entry.second.first << " a1: " << entry.second.second << "\n";
        }
    }
    else{
        c4LOG(info, "Cal map is not load. Cannot print.");
    }
}        


void FatimaRaw2Cal::Exec(Option_t* option){
    if (funcal_data && funcal_data->GetEntriesFast() > 1){ // only get events with two hits.or more
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){

            funcal_hit = (FatimaTwinpeaksData*)funcal_data->At(ihit);

            // under the assumption fast-slow always follows:
            if (funcal_hit->Get_trail_epoch_counter() == 0) {continue;} // missing trail
            if (ihit == event_multiplicity - 1) {fNunmatched++; continue;} //if only one event is left
            if (funcal_hit->Get_ch_ID()%2==0) {fNunmatched++; continue;} //skip slow channels only read them in partner. increment ihit by one extra.
            
            funcal_hit_next = (FatimaTwinpeaksData*)funcal_data->At(ihit+1);
            
            if (funcal_hit_next->Get_ch_ID() != funcal_hit->Get_ch_ID()+1){ // this assumption seems empirically true - no events are filled when reverse order is put.
                fNunmatched++; continue;
            }


            //from here the funcalhitpartner is the slow branch and funcal_hit the fast:

            //do the detector mapping here:
            if (DetectorMap_loaded){
                std::pair<int,int> unmapped_det {funcal_hit->Get_board_id(), (funcal_hit->Get_ch_ID()+1)/2};
                
                if (auto result_find = detector_mapping.find(unmapped_det); result_find != detector_mapping.end()){
                detector_id = result_find->second; //.find returns an iterator over the pairs matching key.
                if (detector_id == -1) {fNunmatched++; continue;} //if only one event is left
                }else{
                    c4LOG(fatal, "Detector mapping not complete - exiting.");
                }
                //only do calibrations if mapping is functional:
                if (DetectorCal_loaded){
                    //TODO implement
                }




            }
            else{ //no map and cal: ->
                detector_id = funcal_hit->Get_board_id()*17 + (int)(funcal_hit_next->Get_ch_ID()+1)/2; // do mapping.                
            }

            if (funcal_hit_next->Get_trail_epoch_counter() == 0) continue; // missing trail in either

            fast_lead_time =  funcal_hit->Get_lead_epoch_counter()*10.24e3 + funcal_hit->Get_lead_coarse_T()*5.0 - funcal_hit->Get_lead_fine_T();
            fast_trail_time = funcal_hit->Get_trail_epoch_counter()*10.24e3 + funcal_hit->Get_trail_coarse_T()*5.0 - funcal_hit->Get_trail_fine_T();
            
            slow_lead_time =  funcal_hit_next->Get_lead_epoch_counter()*10.24e3 + funcal_hit_next->Get_lead_coarse_T()*5.0 - funcal_hit_next->Get_lead_fine_T();
            slow_trail_time = funcal_hit_next->Get_trail_epoch_counter()*10.24e3 + funcal_hit_next->Get_trail_coarse_T()*5.0 - funcal_hit_next->Get_trail_fine_T();
            

            fast_ToT =  fast_trail_time - fast_lead_time;
            slow_ToT =  slow_trail_time - slow_lead_time;

            
            if (((detector_id == time_machine_delayed_detector_id) || (detector_id == time_machine_undelayed_detector_id)) && time_machine_delayed_detector_id!=0 && time_machine_undelayed_detector_id!=0){ // currently only gets the TM if it also matches it slow-fast...
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData((detector_id==time_machine_undelayed_detector_id) ? (fast_lead_time) : (0), (detector_id==time_machine_undelayed_detector_id) ? (0) : (fast_lead_time), funcal_hit->Get_wr_subsystem_id(), funcal_hit->Get_wr_t() );
                continue;
            }

            new ((*fcal_data)[fcal_data->GetEntriesFast()]) FatimaTwinpeaksCalData(
                funcal_hit->Get_board_id(),
                (int)((funcal_hit->Get_ch_ID()+1)/2),
                detector_id,
                slow_lead_time,
                slow_trail_time,
                fast_lead_time,
                fast_trail_time,
                fast_ToT,
                slow_ToT,
                funcal_hit->Get_wr_subsystem_id(),
                funcal_hit->Get_wr_t());
            
            
            fNEvents++;
            ihit++; //increment it by one extra.
        }
    }    
}


void FatimaRaw2Cal::FinishEvent(){
    //THIS FUNCTION IS EXTREMELY IMPORTANT!!!!
    // reset output array
    funcal_data->Clear();
    fcal_data->Clear();
    ftime_machine_array->Clear();
};


    
void FatimaRaw2Cal::FinishTask(){
    c4LOG(info, Form("Wrote %i events.",fNEvents));
    c4LOG(info, Form("%i events are unmatched (not written).",fNunmatched));
}


ClassImp(FatimaRaw2Cal)
