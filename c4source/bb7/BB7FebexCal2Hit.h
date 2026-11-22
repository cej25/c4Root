#ifndef BB7FebexCal2Hit_H
#define BB7FebexCal2Hit_H

#include "BB7FebexCalData.h"
#include "BB7FebexHitData.h"
#include "FairTask.h"
#include "TBB7FebexConfiguration.h"
#include <vector>
#include "EventHeader.h"

class BB7FebexCal2Hit : public FairTask
{
    public:
        BB7FebexCal2Hit();
        virtual ~BB7FebexCal2Hit();
        virtual void Exec(Option_t* option);
        virtual InitStatus Init();
        void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishTask();

    private:
        std::vector<BB7FebexCalItem> const* bb7calImplants;
        std::vector<BB7FebexCalItem> const* bb7calDecays;
        std::vector<BB7FebexHitItem>* implantHitArray;
        std::vector<BB7FebexHitItem>* decayHitArray;

        EventHeader* header;

        void SetParameter();

        TBB7FebexConfiguration const* bb7_config;

        Int_t fExecs = 0;
        Bool_t fOnline;
        int total_time_microsecs = 0;

        Int_t ncalImplantEvents = 0;
        Int_t ncalDecayEvents = 0;

    public:
        ClassDef(BB7FebexCal2Hit, 1)
};

#endif /* BB7FebexCal2Hit_H */
