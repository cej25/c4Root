#ifndef LisaFastRaw2Cal_H
#define LisaFastRaw2Cal_H

#include "FairTask.h"
#include "TLisaFastConfiguration.h"
#include "TClonesArray.h"

class TClonesArray;
class EventHeader;
class LisaFastData;
class LisaFastCalData;

class LisaFastRaw2Cal : public FairTask
{
    public:
        LisaFastRaw2Cal();

        LisaFastRaw2Cal(const TString& name, Int_t verbose);

        ~LisaFastRaw2Cal();

        void PrintDetectorMap();
        void PrintDetectorCal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void SetParContainers();

        virtual InitStatus Init();

        void SetMultiplicityFilter(bool v, int s){ApplyMultiplicityCondition = v; MultiplicityGate = s;}

        int CountMultiplicity(TClonesArray *);


    private:

        TLisaFastConfiguration const* lisafast_configuration;

        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;


        LisaFastData* funcal_hit;
                
        LisaFastData* funcal_hit_next;
        LisaFastCalData* fcal_hit;

        uint16_t detector_id;
        
        int64_t slow_lead_epoch;
        double slow_lead_time;
        int64_t slow_trail_epoch;
        double slow_trail_time;

        int64_t fast_lead_epoch;
        double fast_lead_time;
        int64_t fast_trail_epoch;
        double fast_trail_time;

        double fast_ToT;
        double slow_ToT;

        uint64_t absolute_event_time;

        double energy;

        bool ApplyMultiplicityCondition = false;
        int MultiplicityGate = 2;

        int fNunmatched = 0;

        EventHeader * header;
        Int_t fNEvents = 0;
        Int_t fExecs = 0;
        int total_time_microsecs = 0;

        double a0,a1,a2,a3;

    public:
        ClassDef(LisaFastRaw2Cal, 1);
};

#endif

