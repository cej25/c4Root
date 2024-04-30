#ifndef FatimaRaw2Cal_H
#define FatimaRaw2Cal_H

#include "FairTask.h"
#include "TFatimaTwinpeaksConfiguration.h"

class TClonesArray;
class EventHeader;
class FatimaTwinpeaksData;
class FatimaTwinpeaksCalData;
class TimeMachineData;

class FatimaRaw2Cal : public FairTask
{
    public:
        FatimaRaw2Cal();

        FatimaRaw2Cal(const TString& name, Int_t verbose);

        ~FatimaRaw2Cal();

        void PrintDetectorMap();
        void PrintDetectorCal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void SetParContainers();

        virtual InitStatus Init();


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
        
        double slow_lead_time;
        double slow_trail_time;

        double fast_lead_time;
        double fast_trail_time;

        double fast_ToT;
        double slow_ToT;

        double energy;

        int fNunmatched = 0;

        EventHeader * header;
        Int_t fNEvents = 0;
        Int_t fExecs = 0;
        int total_time_microsecs = 0;

        double a0,a1,a2,a3;

    public:
        ClassDef(FatimaRaw2Cal, 1);
};

#endif

