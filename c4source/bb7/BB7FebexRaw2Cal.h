#ifndef BB7FebexRaw2Cal_H
#define BB7FebexRaw2Cal_H

#include "FairTask.h"
#include "EventHeader.h"
#include "TBB7FebexConfiguration.h"
#include "BB7FebexCalData.h"
#include <map>
#include <vector>

class EventHeader;
struct BB7FebexRawCrate;
class BB7FebexRawData;
class BB7FebexCalItem;

class BB7FebexRaw2Cal : public FairTask
{
    public:
        BB7FebexRaw2Cal();

        virtual ~BB7FebexRaw2Cal();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();


    private:

        TBB7FebexConfiguration const* bb7_config;
    
        void CalibrateCrate(const BB7FebexRawCrate& crate, int crateId);

        const BB7FebexRawData* fRaw = nullptr; //! Borrowed input
        std::vector<BB7FebexCalItem>* bb7calImplants;
        std::vector<BB7FebexCalItem>* bb7calDecays;

        EventHeader* header;
        Bool_t fOnline;

        int32_t implantThreshold = 10000;
        int32_t decayThreshold = 100;

        Int_t nUnmapped = 0;
        Int_t nNothings = 0;


        Int_t count_in_event = 0;

        std::map<std::pair<int, std::pair<int, int>>, std::pair<int, std::pair<int,int>>> detector_mapping;

        



    public:
        ClassDef(BB7FebexRaw2Cal, 2)

};



#endif