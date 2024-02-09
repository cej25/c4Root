#ifndef bPlastRaw2Cal_H
#define bPlastRaw2Cal_H

#include "FairTask.h"


class TClonesArray;
class EventHeader;
class bPlastTwinpeaksData;
class bPlastTwinpeaksCalData;

class bPlastRaw2Cal : public FairTask
{
    public:
        bPlastRaw2Cal();

        bPlastRaw2Cal(const TString& name, Int_t verbose);

        ~bPlastRaw2Cal();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        void PrintDetectorMap();
        void PrintDetectorCal();
        
        Bool_t SetDetectorMapFile(TString);
        Bool_t SetDetectorCalFile(TString);

        void SetTimeMachineChannels(int ftime_machine_delayed_detector_id, int ftime_machine_undelayed_detector_id);

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        virtual void SetParContainers();

        virtual InitStatus Init();

    private:
        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;

        bPlastTwinpeaksData* funcal_hit;
        bPlastTwinpeaksData* funcal_hit_next; // this is the slow or fast hit corresponding to the fast or slow hit :)
        bPlastTwinpeaksCalData* fcal_hit;

        uint16_t detector_id;
        
        double slow_lead_time;
        double slow_trail_time;

        double fast_lead_time;
        double fast_trail_time;

        double fast_ToT;
        double slow_ToT;

        int fNunmatched = 0;

        EventHeader * header;
        Int_t fNEvents = 0;

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;

        // time machine variables:
        int time_machine_delayed_detector_id;
        int time_machine_undelayed_detector_id;
        //maps:
        std::map<std::pair<int, int>, std::pair<int, std::pair<char, char>>> detector_mapping; // [board_id][channel_id] -> [detector_id][detector_stream][detector_position]
        std::map<int,std::pair<double,double>> calibration_coeffs; // key: [detector id] -> [a0][a1]

    public:
        ClassDef(bPlastRaw2Cal, 1);
};

#endif
