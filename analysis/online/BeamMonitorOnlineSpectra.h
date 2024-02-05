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

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TClonesArray* fHitBM;

        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* cS4tdiff; // channel 1 out of 28 for now?
        //temporary!!       
        TCanvas* ct1;
        TCanvas* cQF;
        TCanvas* cNormDiff;
        TCanvas* cPoisson;
        TCanvas* cCum;
        TCanvas* cCumPoisson;
        TCanvas* cDev; 

        // Histograms
        TH1F* fh1_S4tdiff;
        // temporary!!!!!!
        TH1F* hbm_s4h_t1;
        TH1F* fh1_S4_QF;
        TH1F* hBM_s4h_c;
        TH1F* hBM_s4h_cp;
        TH1F* hBM_s4h_dc;
        TH1F* hBM_s4h_poisson;
        TH1F* hBM_s4h_norm_tdiff;


    public:
        ClassDef(BeamMonitorOnlineSpectra, 1)
};

#endif