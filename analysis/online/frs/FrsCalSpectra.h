#ifndef FrsCalSpectra_H
#define FrsCalSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TFolder;
class TCanvas;
class TH1F;
class TH2F;
class TH1D;
class FrsCalData;

class FrsCalSpectra : public FairTask
{
    public:
        FrsCalSpectra();

        FrsCalSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsCalSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // ResetHisto

    private:

        TClonesArray* fCalMainArray;
        FrsCalData* fCalMainHit;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* frs_cal_hists;
}


#endif