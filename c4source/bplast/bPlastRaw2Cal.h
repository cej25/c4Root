#ifndef bPlastRaw2Cal_H
#define bPlastRaw2Cal_H

#include "FairTask.h"


class TClonesArray;
class EventHeader;
class bPlastTwinpeaksData;
class bPlastCalData;

class bPlastRaw2Cal : public FairTask
{
    public:
        bPlastRaw2Cal();

        bPlastRaw2Cal(const TString& name, Int_t verbose);

        virtual ~bPlastRaw2Cal();

        void PrintDetectorMap();
        void PrintDetectorCal();

        Bool_t SetDetectorMapFile(TString);
        Bool_t SetDetectorCalFile(TString);


        virtual void Exec(Option_t* option);

        virtual void Reset();

        virtual void SetParContainers();

        virtual InitStatus Init();

        //virtual InitStatus ReInit() {return kSUCCESS;}


    private:
        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;


        bPlastTwinpeaksData* funcal_hit;
        bPlastCalData* fcal_hit;

        uint16_t detector_id;
        double channel_energy_cal;


        EventHeader * header;
        Int_t fNEvents;

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;
        //maps:
        std::map<std::pair<int,int>,int> detector_mapping; // [board_id][channel_id] -> [detector_id]
        std::map<int,std::pair<double,double>> calibration_coeffs; // key: [detector id] -> [a0][a1]

    public:
        ClassDef(bPlastRaw2Cal, 1);
};

#endif
