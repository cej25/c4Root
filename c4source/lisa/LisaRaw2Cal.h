#ifndef LisaRaw2Cal_H
#define LisaRaw2Cal_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include <map>
#include "TClonesArray.h"

class EventHeader;
class LisaData;
class LisaCalData;
class TClonesArray;

class LisaRaw2Cal : public FairTask
{
    public:
        LisaRaw2Cal();

        virtual ~LisaRaw2Cal();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TLisaConfiguration const* lisa_config;

        TClonesArray* fLisaArray;
        TClonesArray* fLisaCalArray;
        //TClonesArray* fTimeMachineArray;

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;

        std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> detector_mapping;


    public:
        ClassDef(LisaRaw2Cal, 1)

};



#endif