#ifndef FrsCalSpectra_H
#define FrsCalSpectra_H

#include "FairTask.h"
#include "TH1.h"
#include "TH2.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsMainCalData;
class FrsUserCalData;
class FrsTPCData;
class FrsTPCCalData;
class FrsVFTXCalData;
class TCanvas;
class TH1F;
class TH2F;
class TFolder;


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

        TClonesArray* fFrsUserCalArray; // array with hit items
        TClonesArray* fFrsMainCalArray; // array with hit items
        TClonesArray* fFrsTPCArray; // array with hit items
        TClonesArray* fFrsTPCCalArray; // array with hit items
        TClonesArray* fFrsVFTXCalArray; // array with hit items

        FrsUserCalData* fHitFrsUserCal; // array with hit items
        FrsMainCalData* fHitFrsMainCal; // array with hit items
        FrsTPCData* fHitFrsTPC; // array with hit items
        FrsTPCCalData* fHitFrsTPCCal; // array with hit items
        FrsVFTXCalData* fHitFrsVFTXCal; // array with hit items

        EventHeader* header;
        Int_t fNEvents;

        TFolder* frs_hists;
        TFolder* frs_cal_hists;
}


#endif