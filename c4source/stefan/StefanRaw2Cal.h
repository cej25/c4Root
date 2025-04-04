#ifndef StefanRaw2Cal_H
#define StefanRaw2Cal_H

#include "FairTask.h"
#include "TStefanConfiguration.h"

class TClonesArray;
class EventHeader;

class StefanRaw2Cal : public FairTask
{
    public:
        StefanRaw2Cal();

        StefanRaw2Cal(const TString& name, Int_t verbose);

        virtual ~StefanRaw2Cal();
        
        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void SetParContainers();

        virtual InitStatus Init();

        void SetVetoPileupSCI41(bool v){VetoPileupSCI41 = v;}
        

    private:
        Bool_t fOnline;
        
        const TStefanConfiguration*  stefan_config;

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
        

    public:
        ClassDef(StefanRaw2Cal, 1);
};

#endif
