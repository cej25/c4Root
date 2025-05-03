#ifndef StefanRaw2Cal_H
#define StefanRaw2Cal_H

#include "FairTask.h"
#include "StefanFebexData.h"
#include "StefanCalData.h"
#include "TStefanConfiguration.h"

class TClonesArray;
class StefanFebexItem;
class EventHeader;

class StefanRaw2Cal : public FairTask
{
    public:
        StefanRaw2Cal();

        StefanRaw2Cal(const TString& name, Int_t verbose);

        virtual ~StefanRaw2Cal();
        
        void SetOnline(Bool_t set_online){ fOnline = set_online; }

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual InitStatus Init();

        void SetVetoPileupSCI41(bool v){ VetoPileupSCI41 = v; }
        

    private:
        
        const TStefanConfiguration*  stefan_config;
	
	    std::vector<StefanFebexItem> const* StefanArray;
        std::vector<StefanCalItem>* StefanHit;
        int detector_id;
        int strip_id;

        EventHeader * header;
        Bool_t fOnline;
        Int_t fNEvents = 0;
	    int64_t wr_t;

        bool VetoPileupSCI41 = false;

        Int_t nUnmapped = 0;
        Int_t nNothings = 0;
        Int_t nTotalStefan = 0;

        Int_t count_in_event = 0;

        std::map<std::pair<int, int>, std::pair<int, std::pair<int,int>>> detector_mapping;

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;
        //maps:
        

    public:
        ClassDef(StefanRaw2Cal, 1);
};

#endif
