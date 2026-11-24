#ifndef StefanCal2Hit_H
#define StefanCal2Hit_H

#include "StefanCalData.h"
#include "StefanHitData.h"
#include "FairTask.h"
#include "TStefanConfiguration.h"
#include <vector>
#include "EventHeader.h"

class StefanCal2Hit : public FairTask
{
    public:
        StefanCal2Hit();
        virtual ~StefanCal2Hit();
        virtual void Exec(Option_t* option);
        virtual InitStatus Init();
        void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        // implants vs decays or all hits? separate later perhaps
        std::vector<StefanCalItem> const* calArray;
        std::vector<StefanHitItem>* hitArray;

        EventHeader* header;

        void SetParameter();

        TStefanConfiguration const* stefan_config;

        Int_t fExecs = 0;
        Bool_t fOnline;
        int total_time_microsecs = 0;

        Int_t calEvents = 0;

    public:
        ClassDef(StefanCal2Hit, 1)
};

#endif /* StefanCal2Hit_H */
