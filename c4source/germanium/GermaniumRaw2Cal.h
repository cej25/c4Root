#ifndef GermaniumRaw2Cal_H
#define GermaniumRaw2Cal_H

#include "FairTask.h"
#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class GermaniumFebexData;
class GermaniumCalData;

class GermaniumRaw2Cal : public FairTask
{
    public:
        GermaniumRaw2Cal();

        GermaniumRaw2Cal(const TString& name, Int_t verbose);

        virtual ~GermaniumRaw2Cal();
        
        void SetOnline(Bool_t set_online){fOnline = set_online;}

        void PrintDetectorMap();
        void PrintDetectorCal();

        //Bool_t SetDetectorMapFile(TString);
        //Bool_t SetDetectorCalFile(TString);


        void SetTimeMachineChannels(int ftime_machine_delayed_detector_id, int ftime_machine_delayed_crystal_id, int ftime_machine_undelayed_detector_id, int ftime_machine_undelayed_crystal_id);//AFTER mapping.


        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void SetParContainers();

        virtual InitStatus Init();

        //virtual InitStatus ReInit() {return kSUCCESS;}


    private:
        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;
        
        const TGermaniumConfiguration *  germanium_configuration;

        GermaniumFebexData* funcal_hit;
        GermaniumCalData* fcal_hit;

        int detector_id;
        int crystal_id;
        double channel_energy_cal;


        int time_machine_delayed_detector_id;
        int time_machine_undelayed_detector_id;
        int time_machine_delayed_crystal_id;
        int time_machine_undelayed_crystal_id;


        EventHeader * header;
        Int_t fNEvents;

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;
        //maps:
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping; // [board_id][channel_id] -> [detector_id][crystal_id]
        std::map<std::pair<int,int>,std::pair<double,double>> calibration_coeffs; // key: [detector id][crystal id] -> [a0][a1]

    public:
        ClassDef(GermaniumRaw2Cal, 1);
};

#endif

