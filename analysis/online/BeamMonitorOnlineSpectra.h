#ifndef BeamMonitorOnlineSpectra_H
#define BeamMonitorOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class BeamMonitorOnlineSpectra : public FairTask
{
    public:
        BeamMonitorOnlineSpectra();
        BeamMonitorOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~BeamMonitorOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TClonesArray* fHitBM;

        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* cSpills; // channel 1 out of 28 for now?

        // Histograms
        TH1F* fh1_Spills;

    public:
        ClassDef(BeamMonitorOnlineSpectra, 1)
};

#endif