#ifndef FatimaRaw2Cal_H
#define FatimaRaw2Cal_H

#include "FairTask.h"


class TClonesArray;
class EventHeader;
class FatimaTwinpeaksData;
class FatimaTwinpeaksCalData;
class TimeMachineData;
class TClonesArray;

class FatimaRaw2Cal : public FairTask
{
    public:
        FatimaRaw2Cal();

        FatimaRaw2Cal(const TString& name, Int_t verbose);

        ~FatimaRaw2Cal();

        void PrintDetectorMap();
        void PrintDetectorCal();

        Bool_t SetDetectorMapFile(TString);
        Bool_t SetDetectorCalFile(TString);

        void SetTimeMachineChannels(int ftime_machine_delayed_detector_id, int ftime_machine_undelayed_detector_id);

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void SetParContainers();

        virtual InitStatus Init();


    private:
        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;


        FatimaTwinpeaksData* funcal_hit;
        
        TClonesArray * hits_in_Twinpeaks_channel;
        
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

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;
        double a0,a1,a2,a3;

        int time_machine_delayed_detector_id;
        int time_machine_undelayed_detector_id;

        //maps:
        std::map<std::pair<int,int>,int> detector_mapping; // [board_id][channel_id] -> [detector_id]
        std::map<int,std::vector<double>> calibration_coeffs; // key: [detector id] -> vector[a0 - a3] index is coefficient number 0 = offset +++ expects quadratic.

    public:
        ClassDef(FatimaRaw2Cal, 1);
};

#endif

