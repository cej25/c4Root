#ifndef StefanRaw2Cal_H
#define StefanRaw2Cal_H

#include "FairTask.h"
#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class GermaniumFebexData;
class GermaniumCalData;

class StefanRaw2Cal : public FairTask
{
    public:
        StefanRaw2Cal();

        StefanRaw2Cal(const TString& name, Int_t verbose);

        virtual ~StefanRaw2Cal();
        
        void SetOnline(Bool_t set_online){fOnline = set_online;}

        void PrintDetectorMap();
        void PrintDetectorCal();


        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void SetParContainers();

        virtual InitStatus Init();

        void SetVetoPileupSCI41(bool v){VetoPileupSCI41 = v;}
        

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

        bool VetoPileupSCI41 = true;


        EventHeader * header;
        Int_t fNEvents = 0;

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;
        //maps:
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping; // [board_id][channel_id] -> [detector_id][crystal_id]
        std::map<std::pair<int,int>,std::vector<double>> calibration_coeffs; // key: [detector id][crystal id] -> [a0][a1]

    public:
        ClassDef(StefanRaw2Cal, 1);
};

#endif
