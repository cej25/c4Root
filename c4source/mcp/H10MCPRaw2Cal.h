#ifndef H10MCPRaw2Cal_H
#define H10MCPRaw2Cal_H

#include "FairTask.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TClonesArray.h"

class TClonesArray;
class EventHeader;
class FatimaTwinpeaksData;
class FatimaTwinpeaksCalData;
class TimeMachineData;

class H10MCPRaw2Cal : public FairTask
{
    public:
        H10MCPRaw2Cal();

        H10MCPRaw2Cal(const TString& name, Int_t verbose);

        ~H10MCPRaw2Cal();

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

        TFatimaTwinpeaksConfiguration const* fatima_configuration;

        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;


        FatimaTwinpeaksData* funcal_hit;
                
        FatimaTwinpeaksData* funcal_hit_next;
        FatimaTwinpeaksCalData* fcal_hit;

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
        ClassDef(H10MCPRaw2Cal, 1);
};

#endif

