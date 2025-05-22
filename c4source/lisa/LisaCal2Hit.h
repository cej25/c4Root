#ifndef LisaCal2Hit_H
#define LisaCal2Hit_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include "LisaAnaData.h"
#include "LisaHitData.h"
#include <map>
#include <vector>
#include "TVector.h"

class EventHeader;
class LisaItem;
class LisaCalItem;
class LisaAnaItem;
class LisaHitItem;

class LisaCal2Hit : public FairTask
{
    public:
        LisaCal2Hit();

        virtual ~LisaCal2Hit();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TLisaConfiguration const* lisa_config;
    
        std::vector<LisaItem> const* lisaArray;
        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<LisaHitItem>* lisaHitArray;
      

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;


    public:
        ClassDef(LisaCal2Hit, 1)

};



#endif