#ifndef FimpRaw2Cal_H
#define FimpRaw2Cal_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TFimpConfiguration.h"
#include "FimpData.h"
#include "FimpCalData.h"
#include <map>
#include <vector>

class EventHeader;
class FimpItem;
class FimpCalItem;

class FimpRaw2Cal : public FairTask
{
    public:
        FimpRaw2Cal();

        virtual ~FimpRaw2Cal();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TFimpConfiguration const* fimp_config;
    
        std::vector<FimpItem> const* fimpArray;
        std::vector<FimpCalItem>* fimpCalArray;

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;

        //std::map<int, std::pair<std::pair<int, int>, std::string>> detector_mapping;


    public:
        ClassDef(FimpRaw2Cal, 1)

};



#endif