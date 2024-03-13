#ifndef BeamMonitorOnlineSpectra_H
#define BeamMonitorOnlineSpectra_H

#include "FairTask.h"
#include "BeamMonitorData.h"
#include "TGraph.h"
#include "TFolder.h"

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

        TFolder* folder_beammonitor;

        // S2
        Int_t BM_S2_count = 0;
        const Int_t BM_S2_DoAnalysisEvery = 100000;
        Long64_t BM_S2_QFcount;
        Long64_t BM_S2_SumTdiff;
        const Int_t BM_S2_MaxTdiffs = 300000;
        

        // S4
        Int_t BM_S4_count = 0;
        const Int_t BM_S4_DoAnalysisEvery = 30000;
        Long64_t BM_S4_QFcount;
        Long64_t BM_S4_SumTdiff;
        const Int_t BM_S4_MaxTdiffs = 100000;

        // Both
        const Int_t BM_NBinsMax = 100000;
        const Int_t BM_NTimeMax = 10000; // time axis displays for HitTimes [ms]
        const Int_t BM_MaxTimeDiff = 100000; // [100ns units]


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

    public:
        ClassDef(BeamMonitorOnlineSpectra, 1)
};

#endif