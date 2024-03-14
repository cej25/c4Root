#ifndef FatimaVmeOnlineSpectra_H
#define FatimaVmeOnlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include <vector>
#include "TH1.h"

class EventHeader;

class FatimaVmeOnlineSpectra : public FairTask
{
    public:
        FatimaVmeOnlineSpectra();
        FatimaVmeOnlineSpectra(TString& name, Int_t verbose = 1);

        virtual ~FatimaVmeOnlineSpectra();

        void Reset_Hist();
        void Snapshot_Histo();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();
        virtual void Reset_Histo();

    private:
        TClonesArray* fHitFatimaVme;

        EventHeader* header;
        Int_t fNEvents;

        // Folders
        TFolder* folder_fatima_vme;
        TFolder* folder_raw_vme;
        TFolder* folder_raw_energy;
        TFolder* folder_raw_time;

        // Canvases

        // Histograms
        TH1I* h1_FatVME_QDCMult;
        TH1I* h1_FatVME_TDCMult;
        // these should be vectors based on detector config.
        TH1D* h1_FatVME_RawE[36];
        TH1D* h1_FatVME_RawT[36];
    
    public:
        ClassDef(FatimaVmeOnlineSpectra, 1);
};



#endif