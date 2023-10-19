// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastTwinpeaksData.h"
#include "bPlastCalData.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include "bPlastRaw2Cal.h"

bPlastRaw2Cal::bPlastRaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
funcal_data(new TClonesArray("bPlastTwinpeaksData")),
fcal_data(new TClonesArray("bPlastCalData"))
{
}


bPlastRaw2Cal::bPlastRaw2Cal(const TString& name, Int_t verbose) 
    : FairTask(name, verbose),
    fNEvents(0),
    header(nullptr),
    fOnline(kFALSE),
    funcal_data(new TClonesArray("bPlastTwinpeaksData")),
    fcal_data(new TClonesArray("bPlastCalData"))
{
}

bPlastRaw2Cal::~bPlastRaw2Cal(){
    c4LOG(info, "Deleting bPlastRaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
}


void bPlastRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastRaw2Cal::Init(){
    //grab instance managers and handles.

    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    //only needed for communicating with the https server i believe
    //FairRunOnline* run = FairRunOnline::Instance();
    //run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksData");
    c4LOG_IF(fatal, !funcal_data, "bPlast branch of bPlastTwinpeaksData not found.");
    
    /*fcal_data = (TClonesArray*)mgr->GetObject("bPlastCalData");
    c4LOG_IF(fatal, !fcal_data, "bPlast branch of bPlastCalData not found.");
    */

    FairRootManager::Instance()->Register("bPlastCalData", "bPlast Cal Data", fcal_data, !fOnline);
    
    fcal_data->Clear();
    
    //memset(funcal_data, 0, sizeof *funcal_data);


    return kSUCCESS;
}

Bool_t bPlastRaw2Cal::SetDetectorMapFile(TString filename){
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
    
    //assumes the first line in the file is num-modules used
    while(!detector_map_file.eof()){
        if(detector_map_file.peek()=='#') detector_map_file.ignore(256,'\n');
        else{
            detector_map_file >> rtamex_module >> rtamex_channel >> rdetector_id;
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

Bool_t bPlastRaw2Cal::SetDetectorCalFile(TString filename){

    //TODO: Make the reading fail-safe.
    //
    //Assumed structure of detector map is 
    //- aribtrary lines of comments starting with #
    //- each entry is a line with four number: (tamex module id) (tamex channel id) (detector id) (crystal id)
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

void bPlastRaw2Cal::PrintDetectorMap(){
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

void bPlastRaw2Cal::PrintDetectorCal(){
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


void bPlastRaw2Cal::Exec(Option_t* option){
    if (funcal_data && funcal_data->GetEntriesFast() > 0){
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){

            funcal_hit = (bPlastTwinpeaksData*)funcal_data->At(ihit);

            //do the detector mapping here:
            if (DetectorMap_loaded){
                std::pair<int,int> unmapped_det {funcal_hit->Get_board_id(), funcal_hit->Get_ch_ID()};
                
                if (auto result_find = detector_mapping.find(unmapped_det); result_find != detector_mapping.end()){
                detector_id = result_find->second; //.find returns an iterator over the pairs matching key.
                }else{
                    c4LOG(fatal, "Detector mapping not complete - exiting.");
                }
                //only do calibrations if mapping is functional:
                if (DetectorCal_loaded){
                    //TODO implement
                }
            }
            else{ //no map and cal: ->
                c4LOG(fatal, "Detector Mapping not set - please set this using SetDetectorMap to use the Cal Task.");
            }


            //match slow and fast entries.

            //get ToT

            //write long time

            //


            new ((*fcal_data)[fcal_data->GetEntriesFast()]) bPlastCalData(
                //
                funcal_hit->Get_wr_subsystem_id(),
                funcal_hit->Get_wr_t());
        }
    }    
}


void bPlastRaw2Cal::Reset(){
    // reset output array
    funcal_data->Clear();
    fcal_data->Clear();
};



ClassImp(bPlastRaw2Cal)