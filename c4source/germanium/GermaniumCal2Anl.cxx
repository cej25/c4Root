// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumCalData.h"
#include "BGOTwinpeaksCalData.h"
#include "TGermaniumConfiguration.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "GermaniumCal2Anl.h"

/*
*/
GermaniumCal2Anl::GermaniumCal2Anl()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
fcal_ge_data(new TClonesArray("GermaniumCalData")),
fanl_ge_data(new TClonesArray("GermaniumCalData")),
fcal_bgo_data(new TClonesArray("BGOTwinpeaksCalData"))
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
GermaniumCal2Anl::GermaniumCal2Anl(const TString& name, Int_t verbose) 
    : FairTask(name, verbose),
    fNEvents(0),
    header(nullptr),
    fOnline(kFALSE),
    fcal_ge_data(new TClonesArray("GermaniumCalData")),
    fanl_ge_data(new TClonesArray("GermaniumCalData")),
    fcal_bgo_data(new TClonesArray("BGOTwinpeaksCalData"))
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumCal2Anl::~GermaniumCal2Anl(){
    c4LOG(info, "Deleting GermaniumCal2Anl task");
    if (fcal_ge_data) delete fcal_ge_data;
    if (fanl_ge_data) delete fanl_ge_data;
    if (fcal_bgo_data) delete fcal_bgo_data;
}



void GermaniumCal2Anl::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Init - register data to output tree and gets input data.
*/
InitStatus GermaniumCal2Anl::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fcal_ge_data = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fcal_ge_data, "Germanium branch of GermaniumCalData not found.");

    fcal_bgo_data = (TClonesArray*)mgr->GetObject("BGOTwinpeaksCalData");
    c4LOG_IF(fatal, !fcal_bgo_data, "BGO data not found.");
 
    // needs to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("GermaniumAnlData", "Germanium Anl Data", fanl_ge_data, !fOnline);
    
    fanl_ge_data->Clear();

    return kSUCCESS;
}

/*
Analysis event loop. 
Fatal error if detector map is not set. If calibration coeffs are not written, simply the uncalibrated energies are written.

Picks out the TimeMachine.
*/
void GermaniumCal2Anl::Exec(Option_t* option){

    std::vector<int> skip_events = {};

    int event_multiplicity_bgo = 0;
    if (fcal_bgo_data){
        event_multiplicity_bgo = fcal_bgo_data->GetEntriesFast();
    }

    if (fcal_ge_data && fcal_ge_data->GetEntriesFast() > 0){
        Int_t event_multiplicity = fcal_ge_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){
            
            if (count(skip_events.begin(), skip_events.end(), ihit) != 0) continue; //add-backed hit.

            fcal_ge_hit = (GermaniumCalData*)fcal_ge_data->At(ihit);

            double energy1 = fcal_ge_hit->Get_channel_energy();
            int detector_id1 = fcal_ge_hit->Get_detector_id();
            int crystal_id1 = fcal_ge_hit->Get_crystal_id();
            double time1 = fcal_ge_hit->Get_channel_trigger_time();
            int64_t time_wr1 = fcal_ge_hit->Get_absolute_event_time();


            if (energy1 < 25) continue;
            
            //BGO veto:
            if (detector_id1 <= 12) 
            {
                

            bool BGO_veto_this_event = false;

            if (BGO_veto == true && event_multiplicity_bgo > 0){
                
                int64_t fast_lead_epoch_trigger = 0;
                double fast_lead_time_trigger = 0;
                for (int ihit_bgo = 0; ihit_bgo < event_multiplicity_bgo; ihit_bgo++){
                    fcal_bgo_hit = (BGOTwinpeaksCalData*)fcal_bgo_data->At(ihit_bgo);
                    if (fcal_bgo_hit->Get_detector_id() <= 12){
                        fast_lead_epoch_trigger =  fcal_bgo_hit->Get_fast_lead_epoch();
                        fast_lead_time_trigger = fcal_bgo_hit->Get_fast_lead_time();
                        break;
                    }
                }
                
                for (int ihit_bgo = 0; ihit_bgo < event_multiplicity_bgo; ihit_bgo++){
                    fcal_bgo_hit = (BGOTwinpeaksCalData*)fcal_bgo_data->At(ihit_bgo);

                    if (fcal_bgo_hit->Get_detector_id() == detector_id1){
                        int64_t bgo_wr_abs_time = fcal_bgo_hit->Get_wr_t();
                        
                        if (time_wr1 - bgo_wr_abs_time < 500 &&  time_wr1 - bgo_wr_abs_time > 0){
                            // veto this event
                            BGO_veto_this_event = true;
                        }
                    }

                }

            }

            if (BGO_veto_this_event) continue;




            //Add-back:

            if (AddBack_veto == true){
                double time_gate = 200; //ns
                
                //intra-detector addback: detector_id = detector_id'
                if (event_multiplicity > 1){
                    for (Int_t ihit2 = ihit+1; ihit2 < event_multiplicity; ihit2++){

                        fcal_ge_hit2 = (GermaniumCalData*)fcal_ge_data->At(ihit2);

                        double energy2 = fcal_ge_hit2->Get_channel_energy();
                        int detector_id2 = fcal_ge_hit2->Get_detector_id();
                        int crystal_id2 = fcal_ge_hit2->Get_crystal_id();
                        double time2 = fcal_ge_hit2->Get_channel_trigger_time();

                        if (detector_id2 > 12) continue;


                        //c4LOG(info,Form("detector_id1 = %i, detector_id2 = %i, dt = %f, energy1 = %f, energy2 = %f",detector_id1, detector_id2, TMath::Abs(time2 - time1), energy1, energy2));

                        if (detector_id1 == detector_id2 && TMath::Abs(time2 - time1) < time_gate && energy1 > addback_energy_threshold && energy2 > addback_energy_threshold){
                            //Do addback!
                            if (energy1 > energy2){
                                energy1 = energy1 + energy2;
                            
                            }else if (energy2 > energy1){
                                energy1 = energy1 + energy2;
                                time1 = time2;
                                crystal_id1 = crystal_id2;

                            }

                            skip_events.push_back(ihit2);
                        }
                    }
                }
            }
            }

            new ((*fanl_ge_data)[fanl_ge_data->GetEntriesFast()]) GermaniumCalData(
                    fcal_ge_hit->Get_trigger(),
                    fcal_ge_hit->Get_event_trigger_time(),
                    fcal_ge_hit->Get_pileup(),
                    fcal_ge_hit->Get_overflow(),
                    time1,
                    energy1,
                    crystal_id1,
                    detector_id1,
                    fcal_ge_hit->Get_wr_subsystem_id(),
                    fcal_ge_hit->Get_wr_t(),
                    fcal_ge_hit->Get_absolute_event_time()
                );
            fNEvents++;
        }
    }
}

/*
Very important function - all TClonesArray must be cleared after each event.
*/
void GermaniumCal2Anl::FinishEvent(){
    //fcal_bgo_data->Clear();
    //fcal_ge_data->Clear();
    fanl_ge_data->Clear();
};



ClassImp(GermaniumCal2Anl)