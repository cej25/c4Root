#ifndef BB7FebexRaw2Cal_H
#define BB7FebexRaw2Cal_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TBB7FebexConfiguration.h"
#include "BB7FebexData.h"
#include "BB7FebexCalData.h"
#include <map>
#include <vector>

class EventHeader;
class BB7FebexItem;
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
    
        std::vector<BB7FebexItem> const* bb7array;
        std::vector<BB7FebexCalItem>* bb7calImplants;
        std::vector<BB7FebexCalItem>* bb7calDecays;

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        int64_t wr_t;

        uint32_t implantThreshold = 1500;
        uint32_t decayThreshold = 100;

        std::map<std::pair<int,int>, std::pair<int, std::pair<int, int>>> detector_mapping;

        



    public:
        ClassDef(BB7FebexRaw2Cal, 1)

};



#endif