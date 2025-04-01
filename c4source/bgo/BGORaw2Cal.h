#ifndef BGORaw2Cal_H
#define BGORaw2Cal_H

#include "FairTask.h"
#include "TBGOTwinpeaksConfiguration.h"

class TClonesArray;
class EventHeader;
class BGOTwinpeaksData;
class BGOTwinpeaksCalData;
class TimeMachineData;

class BGORaw2Cal : public FairTask
{
    public:
        BGORaw2Cal();

        BGORaw2Cal(const TString& name, Int_t verbose);

        ~BGORaw2Cal();

        void PrintDetectorMap();
        void PrintDetectorCal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void SetParContainers();

        virtual InitStatus Init();


    private:

        TBGOTwinpeaksConfiguration const* BGO_configuration;

        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;

        BGOTwinpeaksData* funcal_hit;
        BGOTwinpeaksData* funcal_hit_next;
        BGOTwinpeaksCalData* fcal_hit;

        Int_t detector_id;
        Int_t crystal_id;
        
        Long64_t slow_lead_epoch;
        Double_t slow_lead_time;
        Long64_t slow_trail_epoch;
        Double_t slow_trail_time;

        Long64_t fast_lead_epoch;
        Double_t fast_lead_time;
        Long64_t fast_trail_epoch;
        Double_t fast_trail_time;

        Double_t fast_ToT;
        Double_t slow_ToT;

        Long64_t absolute_event_time;

        Double_t energy;

        int fNunmatched = 0;

        EventHeader* header;
        Int_t fNEvents = 0;
        Int_t fExecs = 0;
        int total_time_microsecs = 0;

        double a0,a1,a2,a3;


    public:
        ClassDef(BGORaw2Cal, 1);
};

#endif

