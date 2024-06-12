#ifndef FatimaVmeNearlineSpectra_H
#define FatimaVmeNearlineSpectra_H

#include "FairTask.h"
#include "TCanvas.h"
#include <vector>
#include "TH1.h"
#include "TFile.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFatimaVmeConfiguration.h"
#include "FatimaVmeCalData.h"

class EventHeader;
class TFolder;
class TDirectory;
class TFile;
class TH1I;
class TH1D;
class TH2D;

class FatimaVmeNearlineSpectra : public FairTask
{
    public:
        FatimaVmeNearlineSpectra();
        FatimaVmeNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FatimaVmeNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

    private:
        TFatimaVmeConfiguration const* fatima_vme_config;

        TClonesArray* fHitFatimaVme;

        std::vector<FatimaVmeQDCCalItem> const* qdcCalArray;
        std::vector<FatimaVmeTDCCalItem> const* tdcCalArray;
        std::vector<FatimaVmeResiduals> const* residualArray;

        EventHeader* header;
        Int_t fNEvents;

        int nDetectors;

        TFile* file_fatima_vme_snapshot;

        // Folders
        TDirectory* dir_fatima_vme;
        TDirectory* dir_stats_vme;
        TDirectory* dir_raw_vme;
        TDirectory* dir_cal_vme;
        TDirectory* dir_raw_energy;
        TDirectory* dir_raw_time;
        TDirectory* dir_cal_energy;
        TDirectory* dir_residuals;
        TDirectory* dir_cal_time;
        TDirectory* dir_tdc_dt;
        TDirectory* dir_dt_ch1;
        TDirectory* dir_dt_sc41;



        // Histograms
        std::vector<TH1D*> h1_FatVME_RawE;
        std::vector<TH1D*> h1_FatVME_RawT;
        std::vector<TH1D*> h1_FatVME_E;
        std::vector<TH1D*> h1_FatVME_TDC_dt_refCh1;
        std::vector<TH1D*> h1_FatVME_TDC_dT_refSC41L;
        std::vector<TH2D*> h2_FatVME_EvsdTsc41;
        TH1D* h1_FatVME_E_Sum;
        TH1I* h1_FatVME_QDC_HitPattern;
        TH1I* h1_FatVME_TDC_HitPattern;
        TH1I* h1_FatVME_QDCMult;
        TH1I* h1_FatVME_TDCMult;
        TH2D* h2_FatVME_EvsdTsc41_summed;
        
        TH1D* h1_FatVME_time_machine_undelayed;
        TH1D* h1_FatVME_time_machine_delayed;
        
        TH1D* h1_FatVME_sc41l_time;
        TH1D* h1_FatVME_sc41r_time;

    public:
        ClassDef(FatimaVmeNearlineSpectra, 1);
};



#endif
