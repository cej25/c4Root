#ifndef H10MCPRaw2Cal_H
#define H10MCPRaw2Cal_H

#include "FairTask.h"
#include "H10MCPTwinpeaksData.h"
#include "H10MCPTwinpeaksCalData.h"
#include "TH10MCPConfiguration.h"
#include "TimeMachineData.h"
#include "TClonesArray.h"

class TClonesArray;
class EventHeader;
class TimeMachineData;

class H10MCPRaw2Cal : public FairTask
{
    public:
        H10MCPRaw2Cal();

        H10MCPRaw2Cal(const TString& name, Int_t verbose);

        ~H10MCPRaw2Cal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual InitStatus Init();


    private:

        TH10MCPConfiguration const* mcp_config;

        H10MCPTwinpeaksData* funcal_hit;
                
        H10MCPTwinpeaksData* funcal_hit_next;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;

        Bool_t fOnline;

        uint16_t detector_id;
        Int_t mcp_id;
        Int_t type;
        Int_t number;
        
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

