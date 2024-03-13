#ifndef FatimaVmeOnlineSpectra_H
#define FatimaVmeOnlineSpectra_H

#include "FairTask.h"


class FatimaVmeOnlineSpectra : public FairTask
{
    public:
        FatimaVmeOnlineSpectra();
        FatimaVmeOnlineSpectra(TString& name, Int_t verbose = 1);

        virtual ~FatimaVmeOnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();
        virtual void Reset_Histo();

    private:
        TClonesArray* fHitFatimaVme;

        EventHeader* header;
        Int_t fNEvents;

        //Folders

        // Canvases

        // Histograms
}



#endif