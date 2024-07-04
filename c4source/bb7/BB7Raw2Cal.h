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
class BB7VmeResidualItem;
class TClonesArray;
class TimeMachineData;

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

        std::vector<BB7V7x5Item> const* v7x5array;
        std::vector<BB7V1290Item> const* v1290array;
        std::vector<BB7VmeImplantItem>* implantArray;
        std::vector<BB7VmeDecayItem>* decayArray;
        std::vector<BB7VmeResidualItem>* residualArray;
        TClonesArray* fTimeMachineArray;

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        std::map<std::pair<int,int>, std::pair<int, std::pair<int, int>>> detector_mapping;

    public:
        ClassDef(BB7Raw2Cal, 1)

};

#endif