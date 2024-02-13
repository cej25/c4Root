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

/*
empty constructor required for FairRoot.
*/
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

/*
Named constructor with verbosity level.
*/
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
/*
Clearing old constructed objects.
*/
FatimaRaw2Cal::~FatimaRaw2Cal(){
    c4LOG(info, "Deleting FatimaRaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
    if(ftime_machine_array) delete ftime_machine_array;
}


/*
This is called AFTER the detector mapping. This picks out the two timemachine channels and writes them to the TimeMachine structure.
*/
void FatimaRaw2Cal::SetTimeMachineChannels(int ftime_machine_undelayed_detector_id, int ftime_machine_delayed_detector_id)
{
time_machine_delayed_detector_id = ftime_machine_delayed_detector_id;
time_machine_undelayed_detector_id = ftime_machine_undelayed_detector_id;
}




void FatimaRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Initializer called by the FairRoot manager. Gets the required FairRootManager objects to read and register the data to be written to the tree.
*/
InitStatus FatimaRaw2Cal::Init(){
    //grabs instance managers and handles.

    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksData");
    c4LOG_IF(fatal, !funcal_data, "Fatima branch of FatimaTwinpeaksData not found.");
    

    FairRootManager::Instance()->Register("FatimaTwinpeaksCalData", "FatimaTwinpeaksCalDataFolder", fcal_data, !fOnline);
    //need to have the name of the detector subsystem here:

    FairRootManager::Instance()->Register("FatimaTimeMachineData", "FatimaTimeMachineDataFolder", ftime_machine_array, !fOnline);

    fcal_data->Clear();
    funcal_data->Clear();

    hits_in_Twinpeaks_channel = new TClonesArray("FatimaTwinpeaksCalData");
    hits_in_Twinpeaks_channel->Clear();

    return kSUCCESS;
};


/*
Reads a file containing the detector mappings. To be called before Init. Assumed structure of the file is:
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (tamex module id) (tamex channel id) (detector id)

Raises a fatal error if the module and channel numbers are not unique.
*/
Bool_t FatimaRaw2Cal::SetDetectorMapFile(TString filename){
    c4LOG(info, "Reading Detector map");

    //std::cout << "reading detector map \n";

    std::ifstream detector_map_file (filename);

    if (!detector_map_file.is_open()) {c4LOG(fatal,Form("File '%s' does not exist",filename.Data()));}

    int rtamex_module,rtamex_channel,rdetector_id; // temp read variables
        
    while(!detector_map_file.eof()){
        if(detector_map_file.peek()=='#') detector_map_file.ignore(256,'\n');
        else{
            detector_map_file >> rtamex_module >> rtamex_channel >> rdetector_id;
            c4LOG(info, Form("Reading %i, %i, %i",rtamex_module,rtamex_channel,rdetector_id));
            std::pair<int,int> tamex_mc = {rtamex_module,rtamex_channel};

            //auto it = detector_mapping.find(tamex_mc);
            //if (it != detector_mapping.end()) c4LOG(fatal,Form("Detector mapping not unique. Multiple entries of (tamex module id = %i) (tamex channel id = %i)",rtamex_module,rtamex_channel));

            detector_mapping.insert(std::pair<std::pair<int,int>,int>{tamex_mc,rdetector_id});
            detector_map_file.ignore(256,'\n');
        }
    }
    DetectorMap_loaded = 1;
    detector_map_file.close();  
    return 0; 
};


/*
Reads a file containing the detector calibrations. NEEDS to be a quadratic poly (just set a2=a3=0 if not desired..) To be called before Init. Assumed structure of the file is:
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (fatima detector id) (a0/offset) (a1/slope) (a2) (a3)

Raises a fatal error if the detector numbers are not unique.
*/
Bool_t FatimaRaw2Cal::SetDetectorCalFile(TString filename){
    c4LOG(info, "Reading Calibration coefficients.");
    c4LOG(info, "File reading");
    c4LOG(info, filename);

    std::ifstream cal_map_file (filename);

    int rdetector_id; // temp read variables
    
    //assumes the first line in the file is num-modules used
    while(!cal_map_file.eof()){
        if(cal_map_file.peek()=='#') cal_map_file.ignore(256,'\n');
        else{
            cal_map_file >> rdetector_id >> a0 >> a1 >> a2 >> a3;
            std::vector<double> cals = {a0,a1,a2,a3};

            //auto it = calibration_coeffs.find(rdetector_id);
            //if (it != calibration_coeffs.end()){ c4LOG(fatal,Form("Detector calibration not unique. Multiple entries of (detector id = %i)",rdetector_id));} // TODO: this is somehow throwing errors figure out why.

            calibration_coeffs.insert(std::pair<int,std::vector<double>>{rdetector_id,cals});
            cal_map_file.ignore(256,'\n');
        }
    }
    DetectorCal_loaded = 1;
    cal_map_file.close();
    return 0; 
};

/*
Dump detector map to console.
*/
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

/*
Dump detector calibrations to console.
*/
void FatimaRaw2Cal::PrintDetectorCal(){
    if (DetectorCal_loaded){
        for (const auto& entry : calibration_coeffs){
            std::cout << "DETECTORID: " << entry.first;
            std::cout << " a0: " << entry.second.at(0) << " a1: " << entry.second.at(1) << " a2: " << entry.second.at(2) << " a3: " << entry.second.at(3) << "\n";
        }
    }
    else{
        c4LOG(info, "Cal map is not load. Cannot print.");
    }
}        

/*
The event loop executable. This is where the events are analyzed. Only used implicitly by FairRoot during Run().

Further the hits are matched slow + fast and assigned from the internal Twinpeaks channnel number to the detector number if DetectorMap is loaded.
Assumes that fast hits always preceedes slow hits. 

If no detector map is set then be careful with how the mapping happens: tamex module id * number of tamex modules + channel id.

Writes the times in ns!
*/
void FatimaRaw2Cal::Exec(Option_t* option){
    if (funcal_data && funcal_data->GetEntriesFast() > 1){ // only get events with two hits or more
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){

            FatimaTwinpeaksData * first_hit_in_fast_channel = (FatimaTwinpeaksData*)funcal_data->At(ihit);

            // under the assumption fast-slow always follows:
            //assume that only matched lead-trail hits are written.
            if (first_hit_in_fast_channel->Get_ch_ID()%2==0) {continue;} //get the first odd numbered channel

            int hits_in_fast_channel = 1;
            int hits_in_slow_channel = 0;

            int look_ahead_counter = 1;
            bool all_hits_in_fast_slow_found = false;
            while (!all_hits_in_fast_slow_found){
                if (ihit+look_ahead_counter >= event_multiplicity) break;
                FatimaTwinpeaksData * this_hit = (FatimaTwinpeaksData*)funcal_data->At(ihit+look_ahead_counter);

                //c4LOG(info,this_hit->Get_ch_ID());

                if (this_hit->Get_ch_ID() == first_hit_in_fast_channel->Get_ch_ID() && this_hit->Get_board_id() == first_hit_in_fast_channel->Get_board_id()) hits_in_fast_channel++;
                else if (this_hit->Get_ch_ID() == first_hit_in_fast_channel->Get_ch_ID()+1 && this_hit->Get_board_id() == first_hit_in_fast_channel->Get_board_id()) hits_in_slow_channel++;
                else all_hits_in_fast_slow_found = true;
                look_ahead_counter++;
            }


            //c4LOG(info,Form("fast hits = %i, slow hits = %i, look ahead counter = %i",hits_in_fast_channel,hits_in_slow_channel,look_ahead_counter));
            if (hits_in_fast_channel != hits_in_slow_channel) {
                //break condition - cant recover.
                ihit = hits_in_fast_channel + hits_in_slow_channel - 1 + ihit;
                continue;
            }


            for (int hitnr = 0; hitnr<hits_in_fast_channel; hitnr++){

            funcal_hit = (FatimaTwinpeaksData*)funcal_data->At(ihit+hitnr);
            funcal_hit_next = (FatimaTwinpeaksData*)funcal_data->At(ihit+hitnr+hits_in_fast_channel);
            
            if (funcal_hit_next->Get_ch_ID() != funcal_hit->Get_ch_ID()+1){ // this assumption seems empirically true - no events are filled when reverse order is put.
                fNunmatched++; continue;
            }

            if (funcal_hit_next->Get_board_id() != funcal_hit->Get_board_id()){
                continue;
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
            else{ //no map and cal: ->
                detector_id = funcal_hit->Get_board_id()*17 + (int)(funcal_hit_next->Get_ch_ID()+1)/2; // do mapping.
            }

            if (funcal_hit_next->Get_trail_epoch_counter() == 0) continue; // missing trail in either

            // I am slightly worried about round-off errors by this method (but as far as i can see the maximum epoch counter values is not so large that the digits are suppressed but it is something to keep in mind). However constructing the times like this makes it very easy to use.
            fast_lead_time = static_cast<double>(funcal_hit->Get_lead_epoch_counter()) * 10.24e3
                           + static_cast<double>(funcal_hit->Get_lead_coarse_T()) * 5.0
                           - static_cast<double>(funcal_hit->Get_lead_fine_T());

            fast_trail_time = static_cast<double>(funcal_hit->Get_trail_epoch_counter()) * 10.24e3
                            + static_cast<double>(funcal_hit->Get_trail_coarse_T()) * 5.0
                            - static_cast<double>(funcal_hit->Get_trail_fine_T());

            slow_lead_time = static_cast<double>(funcal_hit_next->Get_lead_epoch_counter()) * 10.24e3
                            + static_cast<double>(funcal_hit_next->Get_lead_coarse_T()) * 5.0
                            - static_cast<double>(funcal_hit_next->Get_lead_fine_T());

            slow_trail_time = static_cast<double>(funcal_hit_next->Get_trail_epoch_counter()) * 10.24e3
                            + static_cast<double>(funcal_hit_next->Get_trail_coarse_T()) * 5.0
                            - static_cast<double>(funcal_hit_next->Get_trail_fine_T());

            fast_ToT =  fast_trail_time - fast_lead_time;
            slow_ToT =  slow_trail_time - slow_lead_time;

            //if (detector_id == 0 || detector_id == 1) c4LOG(info,Form("id = %i, fast lead = %f, fast trail = %f, fast ToT = %f",detector_id,fast_lead_time,fast_trail_time,fast_ToT));

            if (DetectorMap_loaded){
                if (DetectorCal_loaded){ // check
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
                }else{
                    energy = slow_ToT;
                }
            }

            
            if (((detector_id == time_machine_delayed_detector_id) || (detector_id == time_machine_undelayed_detector_id)) && time_machine_delayed_detector_id!=0 && time_machine_undelayed_detector_id!=0){ // currently only gets the TM if it also matches it slow-fast...
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData((detector_id==time_machine_undelayed_detector_id) ? (fast_lead_time) : (0), (detector_id==time_machine_undelayed_detector_id) ? (0) : (fast_lead_time), funcal_hit->Get_wr_subsystem_id(), funcal_hit->Get_wr_t() );
                //continue; //cej: i think this line skips everything if it finds TM - jel: yes :)
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
                energy,
                funcal_hit->Get_wr_subsystem_id(),
                funcal_hit->Get_wr_t());
            
            
            fNEvents++;
            //ihit++; //increment it by one extra.
            }
        }
    }    
}

/*
THIS FUNCTION IS EXTREMELY IMPORTANT!!!!

Clears the TClonesArray used in the function. If they are not cleared after each event they will eat all your RAM.

*/
void FatimaRaw2Cal::FinishEvent(){
    // reset output array
    funcal_data->Clear();
    fcal_data->Clear();
    ftime_machine_array->Clear();
};

/*
Some stats are written when finishing.
*/
void FatimaRaw2Cal::FinishTask(){
    c4LOG(info, Form("Wrote %i events.",fNEvents));
    c4LOG(info, Form("%i events are unmatched (not written).",fNunmatched));

    
}


ClassImp(FatimaRaw2Cal)
