
// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"

#include "c4Logger.h"

// c4
#include "GermaniumFebexData.h"
#include "AgataSuperTraceData.h"
#include "TAgataConfiguration.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "AgataTraceRaw2Cal.h"

/*
Empty constructor for FairRoot.
*/
AgataTraceRaw2Cal::AgataTraceRaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
funcal_data(new TClonesArray("GermaniumFebexTraceData")),
fcal_data(new TClonesArray("AgataSuperTraceData"))
{
    agata_configuration = TAgataConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
AgataTraceRaw2Cal::AgataTraceRaw2Cal(const TString& name, Int_t verbose) 
    : FairTask(name, verbose),
    fNEvents(0),
    header(nullptr),
    fOnline(kFALSE),
    funcal_data(new TClonesArray("GermaniumFebexTraceData")),
    fcal_data(new TClonesArray("AgataSuperTraceData"))
{
    agata_configuration = TAgataConfiguration::GetInstance();
}

AgataTraceRaw2Cal::~AgataTraceRaw2Cal(){
    c4LOG(info, "Deleting AgataTraceRaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
}



void AgataTraceRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Init - register data to output tree and gets input data.
*/
InitStatus AgataTraceRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("GermaniumFebexTraceData");
    c4LOG_IF(fatal, !funcal_data, "Germanium branch of GermaniumFebexTraceData not found.");
 
    // needs to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("AgataSuperTraceData", "Agata Cal Data", fcal_data, !fOnline);
    
    fcal_data->Clear();

    return kSUCCESS;
}


/*
Analysis event loop. 
Fatal error if detector map is not set. If calibration coeffs are not written, simply the uncalibrated energies are written.

Picks out the TimeMachine.
*/
void AgataTraceRaw2Cal::Exec(Option_t* option)
{
    if (funcal_data && funcal_data->GetEntriesFast() > 0)
    {
        AgataSuperTraceData * event = new AgataSuperTraceData();
        
        int nfired_segments = 0;
        int64_t fevent_trigger_time = 0;
        int64_t fhit_pattern = 0;
        double seg_energies[36];
        double seg_times[36];
        int segid = -1;

        double supertrace[18500];

        int normsamples = 50;
        double normalization[36];


        for (int i=0; i<36; i++) seg_energies[i] = 0;
        for (int i=0; i<36; i++) seg_times[i] = 0;
        for (int i=0; i<18500; i++) supertrace[i] = 0;


        Int_t event_multiplicity = funcal_data->GetEntriesFast();

        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {
            funcal_hit = (GermaniumFebexTraceData*)funcal_data->At(ihit);

            int board_id = funcal_hit->Get_board_id();
            int channel_id = funcal_hit->Get_channel_id();
            int64_t event_trigger_time = funcal_hit->Get_event_trigger_time();
            int64_t channel_trigger_time = funcal_hit->Get_channel_trigger_time();
            int32_t uncal_energy = funcal_hit->Get_channel_energy();

            if (uncal_energy < 0) uncal_energy = 0;

            char sector = agata_configuration->GetDetectorID(board_id,channel_id).first;
            int layer = agata_configuration->GetDetectorID(board_id,channel_id).second;
            
            if (layer == -1) continue;
            if (agata_configuration->GetCalibrationCoeff(board_id,channel_id).size() <= 1) c4LOG(fatal,"Failed to read the coeffs");

            double a0 = agata_configuration->GetCalibrationCoeff(board_id,channel_id).at(0);
            double a1 = agata_configuration->GetCalibrationCoeff(board_id,channel_id).at(1);


            //c4LOG(info, Form("bid = %i, chid = %i, un = %i, en = %f, a0 = %f, a1 = %f, sec = %c, layer = %i",board_id,channel_id,uncal_energy,(double)(uncal_energy)*a1+a0, a0, a1,sector,layer));

            if (layer == 1 && sector == 'S'){
                fhit_pattern |= (int64_t(1) << 0);  
                
                event->Set_event_trigger_time(event_trigger_time);
                event->Set_core_trigger_time(channel_trigger_time);
                event->Set_core_energy((double)(uncal_energy)*a1 + a0);

                double baseline_corr = 0;
                int nsamples = 30;

                for (int i = 0; i<nsamples; i++) baseline_corr += funcal_hit->Get_trace_value(i);
                baseline_corr/=nsamples;

                for (int i = 0; i<500; i++) supertrace[i] = funcal_hit->Get_trace_value(i) - baseline_corr;

            }else{
                segid = ((int)sector-65)*6 + layer - 1;
                if (uncal_energy != 0){
                    fhit_pattern |= (int64_t(1) << segid+1);
                    seg_energies[segid] = (double)(uncal_energy)*a1 + a0;
                    seg_times[segid] = channel_trigger_time;
                }


                double baseline_corr = 0;
                int nsamples = 30;

                for (int i = 0; i<nsamples; i++) baseline_corr += funcal_hit->Get_trace_value(i);
                baseline_corr/=nsamples;

                int max_amp_i = 0;
                for (int i = 0; i<500; i++) {
                    supertrace[i + 500*(segid+1)] = funcal_hit->Get_trace_value(i) - baseline_corr; 

                    if (supertrace[i + 500*(segid+1)] > supertrace[max_amp_i + 500*(segid+1)]) max_amp_i = i;
                }

                for (int i = max_amp_i; i<max_amp_i+normsamples; i++) normalization[segid] += supertrace[i + 500*(segid+1)];
                normalization[segid]/=normsamples;
            }
        }

        event->Set_all_segment_energy(seg_energies);
        event->Set_all_segment_trigger_time(seg_times);


        //normalization:
        double max_segment = 0;
        for (int i = 0;i<36;i++){
            if (normalization[i] > max_segment) max_segment = normalization[i];
        }

        for (int i = 0; i<18500;i++) supertrace[i] = supertrace[i]*1000/max_segment;


        event->Set_supertrace(supertrace);
        //time alignment:
        
        
        new ((*fcal_data)[fcal_data->GetEntriesFast()]) AgataSuperTraceData(*event);  
    }
}

/*
Very important function - all TClonesArray must be cleared after each event.
*/
void AgataTraceRaw2Cal::FinishEvent(){
    funcal_data->Clear();
    fcal_data->Clear();
};



ClassImp(AgataTraceRaw2Cal)