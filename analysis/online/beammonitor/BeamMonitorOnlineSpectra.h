#ifndef BeamMonitorOnlineSpectra_H
#define BeamMonitorOnlineSpectra_H

#include "FairTask.h"
#include "BeamMonitorData.h"
#include "TGraph.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TGraph;
class TH1D;

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

        EventHeader* header;
        Int_t fNEvents;

        Int_t BM_NTimeMax = 10000;
        Double_t BM_CR_Tlimit = pow(10,6);
        Double_t BM_CountRate;
        Double_t BM_Tdiff_integral;
        Int_t BM_MaxTimeDiff = 100000;
        Int_t BM_S4_MaxTdiffs = 100000;
        Int_t BM_dc_MinBin;
        Double_t BM_dc_MinValue;
        Double_t BM_Tmean;
        Double_t BM_QF;
        Double_t BM_CR_timesum;
        Int_t BM_CR_relevanthits;

        TH1D* hG_BM_s4h_norm_tdiff;
        TH1D* hG_BM_s4h_tdiff;
        TH1D* hG_BM_s4h_t1;
        TH1D* hG_BM_s4h_n;
        TH1D* hG_BM_s4h_poisson;
        TH1D* hG_BM_s4h_c;
        TH1D* hG_BM_s4h_dc;
        TH1D* hG_BM_s4h_cp;

        TGraph* hG_BM_s4gr_dt_avg;
        TGraph* hG_BM_s4gr_qf;
        TGraph* hG_BM_s4gr_dcmin;
        TGraph* hG_BM_s4gr_dctime;

        TH1D* hG_BM_s2h_norm_tdiff;
        TH1D* hG_BM_s2h_tdiff;
        TH1D* hG_BM_s2h_t1;
        TH1D* hG_BM_s2h_n;
        TH1D* hG_BM_s2h_poisson;
        TH1D* hG_BM_s2h_c;
        TH1D* hG_BM_s2h_dc;
        TH1D* hG_BM_s2h_cp;

        TGraph* hG_BM_s2gr_dt_avg;
        TGraph* hG_BM_s2gr_qf;
        TGraph* hG_BM_s2gr_dcmin;
        TGraph* hG_BM_s2gr_dctime;

        // // Canvas
        // TCanvas* cS4tdiff; // channel 1 out of 28 for now?
        // //temporary!!       
        // TCanvas* ct1;
        // TCanvas* cQF;
        // TCanvas* cNormDiff;
        // TCanvas* cPoisson;
        // TCanvas* cCum;
        // TCanvas* cCumPoisson;
        // TCanvas* cDev; 


    public:
        ClassDef(BeamMonitorOnlineSpectra, 1)
};

#endif