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
#include "TFatimaTwinpeaksConfiguration.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <chrono>

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
   fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
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
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
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


void FatimaRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Initializer called by the FairRoot manager. Gets the required FairRootManager objects to read and register the data to be written to the tree.
*/
InitStatus FatimaRaw2Cal::Init()
{  
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksData");
    c4LOG_IF(fatal, !funcal_data, "Fatima branch of FatimaTwinpeaksData not found.");
    
    //need to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("FatimaTwinpeaksCalData", "FatimaTwinpeaksCalDataFolder", fcal_data, !fOnline);
    FairRootManager::Instance()->Register("FatimaTimeMachineData", "FatimaTimeMachineDataFolder", ftime_machine_array, !fOnline);

    fcal_data->Clear();
    funcal_data->Clear();

    return kSUCCESS;
};

/*
Dump detector map to console.
*/
void FatimaRaw2Cal::PrintDetectorMap()
{
    if (fatima_configuration->MappingLoaded())
    {
        for (const auto& entry : fatima_configuration->Mapping())
        {
            std::cout << "tamexMODULE: " << entry.first.first << " tamexCHANNEL " << entry.first.second;
            std::cout << " DETECTORID: " << entry.second << "\n";
        }
    }
    else
    {
        c4LOG(info, "Detector map is not load. Cannot print.");
    }
}

/*
Dump detector calibrations to console.
*/
void FatimaRaw2Cal::PrintDetectorCal()
{
    if (fatima_configuration->CalibrationCoefficientsLoaded())
    {
        for (const auto& entry : fatima_configuration->CalibrationCoefficients())
        {
            std::cout << "DETECTORID: " << entry.first;
            std::cout << " a0: " << entry.second.at(0) << " a1: " << entry.second.at(1) << " a2: " << entry.second.at(2) << " a3: " << entry.second.at(3) << "\n";
        }
    }
    else
    {
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
void FatimaRaw2Cal::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    if (funcal_data && funcal_data->GetEntriesFast() > 1)
    { // only get events with two hits or more
        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {

            FatimaTwinpeaksData* first_hit_in_fast_channel = (FatimaTwinpeaksData*)funcal_data->At(ihit);

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
                ihit = hits_in_fast_channel + hits_in_slow_channel + ihit - 1; // -1 cus it adds one when restarting the for-loop 
                continue;
            }


            for (int hitnr = 0; hitnr<hits_in_fast_channel; hitnr++)
            {

                funcal_hit = (FatimaTwinpeaksData*)funcal_data->At(ihit+hitnr);
                funcal_hit_next = (FatimaTwinpeaksData*)funcal_data->At(ihit+hitnr+hits_in_fast_channel);
            
            if (funcal_hit_next->Get_ch_ID() != funcal_hit->Get_ch_ID()+1)
            {
                fNunmatched++;
                continue;
            }

            if (funcal_hit_next->Get_board_id() != funcal_hit->Get_board_id())
            {
                continue;
            }


            //from here the funcalhitpartner is the slow branch and funcal_hit the fast:
            
            if (fatima_configuration->MappingLoaded())
            {
                std::map<std::pair<int,int>,int> fmap;
                fmap = fatima_configuration->Mapping();
                std::pair<int, int> unmapped_det { funcal_hit->Get_board_id(), (funcal_hit->Get_ch_ID()+1)/2};
                if (auto result_find = fmap.find(unmapped_det); result_find != fmap.end())
                {
                    detector_id = result_find->second; // .find returns an iterator over the pairs matching key
                    //c4LOG(info,Form("board = %i, ch = %i, det = %i",funcal_hit->Get_board_id(), (funcal_hit->Get_ch_ID()+1)/2,result_find->second));
                    if (detector_id == -1) { fNunmatched++; continue; }
                }
            }
            


            if (funcal_hit_next->Get_trail_epoch_counter() == 0 || funcal_hit_next->Get_lead_epoch_counter() == 0) continue; // missing trail in either
            if (funcal_hit->Get_trail_epoch_counter() == 0 || funcal_hit->Get_lead_epoch_counter() == 0) continue; // missing trail in either
            //if (funcal_hit_next->Get_trail_coarse_T() == 0 || funcal_hit_next->Get_lead_coarse_T() == 0) continue; // missing trail in either
            //if (funcal_hit->Get_trail_fine_T() == 0 || funcal_hit->Get_lead_fine_T() == 0) continue; // missing trail in either

            // Round-off error safe:
            fast_lead_epoch = (int64_t)(funcal_hit->Get_lead_epoch_counter()) * 10240;

            fast_lead_time = (double)(funcal_hit->Get_lead_coarse_T()) * 5.0
                           - (double)(funcal_hit->Get_lead_fine_T());

            fast_trail_epoch = (int64_t)(funcal_hit->Get_trail_epoch_counter()) * 10240;

            fast_trail_time = (double)(funcal_hit->Get_trail_coarse_T()) * 5.0
                            - (double)(funcal_hit->Get_trail_fine_T());

            slow_lead_epoch = (int64_t)(funcal_hit_next->Get_lead_epoch_counter()) * 10240;

            slow_lead_time = (double)(funcal_hit_next->Get_lead_coarse_T()) * 5.0
                            -(double)(funcal_hit_next->Get_lead_fine_T());

            slow_trail_epoch = (int64_t)(funcal_hit_next->Get_trail_epoch_counter()) * 10240;

            slow_trail_time = (double)(funcal_hit_next->Get_trail_coarse_T()) * 5.0
                            - (double)(funcal_hit_next->Get_trail_fine_T());

            
            fast_ToT =  (double)(funcal_hit->Get_trail_epoch_counter() - funcal_hit->Get_lead_epoch_counter())*10.24e3 +  (double)((int32_t)funcal_hit->Get_trail_coarse_T() - (int32_t)funcal_hit->Get_lead_coarse_T())*5.0 - (funcal_hit->Get_trail_fine_T() - funcal_hit->Get_lead_fine_T());
            // find the slow ToT without encountering round-off errors:
            slow_ToT =  (double)(funcal_hit_next->Get_trail_epoch_counter() - funcal_hit_next->Get_lead_epoch_counter())*10.24e3 +  (double)((int32_t)funcal_hit_next->Get_trail_coarse_T() - (int32_t)funcal_hit_next->Get_lead_coarse_T())*5.0 - (funcal_hit_next->Get_trail_fine_T() - funcal_hit_next->Get_lead_fine_T());
            
            absolute_event_time = (uint64_t)(funcal_hit->Get_wr_t() + (int64_t)(((int32_t)funcal_hit->Get_lead_epoch_counter() - (int32_t)funcal_hit->Get_accepted_lead_epoch_counter()) * 10.24e3 + ((int32_t)funcal_hit->Get_lead_coarse_T() - (int32_t)funcal_hit->Get_accepted_lead_coarse_T()) * 5.0 - (int32_t)(funcal_hit->Get_lead_fine_T() - funcal_hit->Get_accepted_lead_fine_T())));
            //if (detector_id == 0 || detector_id == 1) c4LOG(info,Form("id = %i, fast lead = %f, fast trail = %f, fast ToT = %f",detector_id,fast_lead_time,fast_trail_time,fast_ToT));

            if (fatima_configuration->MappingLoaded()){
                if (fatima_configuration->CalibrationCoefficientsLoaded()){ // check
                    std::map<int,std::vector<double>> calibration_coeffs = fatima_configuration->CalibrationCoefficients();
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

            if (fatima_configuration->GainShiftsLoaded() && !(fatima_configuration->IsDetectorAuxilliary(detector_id))){
                energy = energy*fatima_configuration->GetGainShift(detector_id,funcal_hit->Get_wr_t());
            }
            

            if (((detector_id == fatima_configuration->TM_Delayed()) || (detector_id == fatima_configuration->TM_Undelayed())) && fatima_configuration->TM_Delayed() != 0 && fatima_configuration->TM_Undelayed() != 0)
            {
                new ((*ftime_machine_array)[ftime_machine_array->GetEntriesFast()]) TimeMachineData((detector_id == fatima_configuration->TM_Undelayed()) ? (fast_lead_time) : (0), (detector_id == fatima_configuration->TM_Undelayed()) ? (0) : (fast_lead_time), funcal_hit->Get_wr_subsystem_id(), funcal_hit->Get_wr_t());
            }
            
            //c4LOG(info,Form("board = %i, ch = %i, det = %i",funcal_hit->Get_board_id(),(int)((funcal_hit->Get_ch_ID()+1)/2), detector_id));
            
            new ((*fcal_data)[fcal_data->GetEntriesFast()]) FatimaTwinpeaksCalData(
                funcal_hit->Get_board_id(),
                (int)((funcal_hit->Get_ch_ID()+1)/2),
                detector_id,
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
            //ihit++; //increment it by one extra.
            }
        }
        fExecs++; // count once every time we do something with fatima
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();



    if (ApplyMultiplicityCondition && fcal_data){
        FairRunOnline * run = FairRunOnline::Instance();
        run->MarkFill(false);
        int mult = CountMultiplicity(fcal_data);
        if (mult >= MultiplicityGate) run->MarkFill(true);
    }
}

int FatimaRaw2Cal::CountMultiplicity(TClonesArray * fcal){
    //finds the maximum multiplicity hit in the data structure
    int max_multiplicty = 0;
    for (int i = 0; i<fcal->GetEntries(); i++){
        FatimaTwinpeaksCalData * f = (FatimaTwinpeaksCalData*)fcal->At(i);
        if (fatima_configuration->IsDetectorAuxilliary(f->Get_detector_id())) continue;

        int multiplicty = 1;
        for (int j = 0; j<fcal->GetEntries(); j++){
            if (j == i) continue;
            FatimaTwinpeaksCalData * g = (FatimaTwinpeaksCalData*)fcal->At(j);
            if (fatima_configuration->IsDetectorAuxilliary(g->Get_detector_id())) continue;             

            if (TMath::Abs((double)((int64_t)f->Get_fast_lead_epoch() - (int64_t)g->Get_fast_lead_epoch()) + (f->Get_fast_lead_time() - g->Get_fast_lead_time()))<1e3){
                multiplicty ++;
            }
        }
        if (multiplicty > max_multiplicty) max_multiplicty = multiplicty;
    }
    return max_multiplicty;
}

/*
THIS FUNCTION IS EXTREMELY IMPORTANT!!!!

Clears the TClonesArray used in the function. If they are not cleared after each event they will eat all your RAM.

*/
void FatimaRaw2Cal::FinishEvent()
{
    // reset output array
    funcal_data->Clear();
    fcal_data->Clear();
    ftime_machine_array->Clear();
};

/*
Some stats are written when finishing.
*/
void FatimaRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
    c4LOG(info, Form("%i events are unmatched (not written).",fNunmatched));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}


ClassImp(FatimaRaw2Cal)
