#ifndef FrsRawSpectra_H
#define FrsRawSpectra_H

#include "FairTask.h"
#include "TH1.h"
#include "TH2.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsMainData;
class FrsUserData;
class FrsTPCData;
class FrsVFTXData;
class TCanvas;
class TH1F;
class TH2F;
class TFolder;


class FrsRawSpectra : public FairTask
{
    public:
        FrsRawSpectra();

        FrsRawSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsRawSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // ResetHisto

    private:

        TClonesArray* fFrsUserArray; // array with hit items
        TClonesArray* fFrsMainArray; // array with hit items
        TClonesArray* fFrsTPCArray; // array with hit items
        TClonesArray* fFrsVFTXArray; // array with hit items

        FrsUserData* fHitFrsUser; // array with hit items
        FrsMainData* fHitFrsMain; // array with hit items
        FrsTPCData* fHitFrsTPC; // array with hit items
        FrsVFTXData* fHitFrsVFTX; // array with hit items

        EventHeader* header;
        Int_t fNEvents;

        // folders
        TFolder* folder_frs_hists;
        TFolder* folder_frs_raw_hists;

        // histograms
        


        // canvases


}


#endif