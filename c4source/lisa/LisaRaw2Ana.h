#ifndef LisaRaw2Ana_H
#define LisaRaw2Ana_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "LisaData.h"
#include "LisaAnaData.h"
#include <map>
#include <vector>

class EventHeader;
class LisaItem;
class LisaAnaItem;

class LisaRaw2Ana : public FairTask
{
    public:
        LisaRaw2Ana();

        virtual ~LisaRaw2Ana();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

        //void PrintMWDParameter();

    private:
        TLisaConfiguration const* lisa_config;
    
        std::vector<LisaItem> const* lisaArray;
        std::vector<LisaAnaItem>* lisaAnaArray;
        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

    public:
        ClassDef(LisaRaw2Ana, 1)

};



#endif