#ifndef BB7Raw2Cal_H
#define BB7Raw2Cal_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "BB7VmeData.h"
#include "BB7VmeCalData.h"
#include "TBB7VmeConfiguration.h"

#include <map>

class TBB7VmeConfiguration;
class BB7V7x5Item;
class BB7VmeImplantItem;
class BB7VmeDecayItem;

class BB7Raw2Cal : public FairTask
{
    public:
        BB7Raw2Cal();

        virtual ~BB7Raw2Cal();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TBB7VmeConfiguration const* bb7_config;

        TClonesArray* fBB7VmeArray;
        TClonesArray* fBB7VmeCalArray;
        TClonesArray* fTimeMachineArray;
        std::vector<BB7V7x5Item> const* v7x5array;
        std::vector<BB7VmeImplantItem>* implantArray;
        std::vector<BB7VmeDecayItem>* decayArray;

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        //uint64_t wr_t;

        std::map<std::pair<int, int>, std::pair<int, int>> detector_mapping;

        std::vector<uint32_t> v7x5_geo;
        std::vector<uint32_t> v7x5_channel;
        std::vector<uint32_t> v7x5_data;
    
    public:
        ClassDef(BB7Raw2Cal, 1)

};



#endif