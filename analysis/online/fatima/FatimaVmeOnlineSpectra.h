#ifndef FatimaVmeOnlineSpectra_H
#define FatimaVmeOnlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TCanvas.h"
#include <vector>
#include "TH1.h"
#include "TFile.h"
#include "TFatimaVmeConfiguration.h"

class EventHeader;

class TH1I;
class TH1D;
class TH2D;

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
        TFatimaVmeConfiguration const* fatima_vme_config;

        TClonesArray* fHitFatimaVme;

        EventHeader* header;
        Int_t fNEvents;

        TFile* file_fatima_vme_snapshot;


        // Folders
        TFolder* folder_fatima_vme;
        TFolder* folder_stats_vme;
        TFolder* folder_raw_vme;
        TFolder* folder_cal_vme;
        TFolder* folder_raw_energy;
        TFolder* folder_raw_time;
        TFolder* folder_cal_energy;
        TFolder* folder_cal_time;
        TFolder* folder_tdc_dt;
        TFolder* folder_dt_ch1;
        TFolder* folder_dt_sc41;

        // Canvases
        TCanvas* c_FatVME_E;
        TCanvas* c_FatVME_RawE;
        TCanvas* c_FatVME_RawT;
        TCanvas* c_FatVME_T;
        TCanvas* c_FatVME_dTrefCh1;
        TCanvas* c_FatVME_dTrefSC41;
        TCanvas* c_fatima_vme_snapshot;

        // Histograms
        // these should be vectors based on detector config. 
        TH1D* h1_FatVME_RawE[36];
        TH1D* h1_FatVME_RawT[36];
        TH1D* h1_FatVME_E[36];
        TH1D* h1_FatVME_TDC_dt_refCh1[36];
        TH1D* h1_FatVME_TDC_dT_refSC41L[36];
        TH1D* h1_FatVME_E_Sum;
        TH1D* h1_FatVME_E_Sum_Large; // large range
        TH1I* h1_FatVME_QDC_HitPattern;
        TH1I* h1_FatVME_TDC_HitPattern;
        TH1I* h1_FatVME_QDCMult;
        TH1I* h1_FatVME_TDCMult;
        TH2D* h1_FatVME_EvsT;
        TH1D* h1_FatVME_Time;
        
        TH1D* h1_FatVME_time_machine_undelayed;
        TH1D* h1_FatVME_time_machine_delayed;
        
        TH1D* h1_FatVME_sc41l_time;
        TH1D* h1_FatVME_sc41r_time;
        TH1D* h1_FatVME_sc41l;
        TH1D* h1_FatVME_sc41r;

        int num_detectors;


    public:
        ClassDef(FatimaVmeOnlineSpectra, 1);
};



#endif
