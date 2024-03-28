#ifndef FrsGermaniumCorrelations_H
#define FrsGermaniumCorrelations_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class FrsGate;

class FrsGermaniumCorrelations : public FairTask
{
    public:
        FrsGermaniumCorrelations();
        FrsGermaniumCorrelations(FrsGate * frsgate);
        FrsGermaniumCorrelations(const TString& name, Int_t verbose = 1);



        virtual ~FrsGermaniumCorrelations();

        //virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        //virtual void Reset_Ge_Histo();

        //virtual void Snapshot_Ge_Histo();


        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };
    
    private:
        TClonesArray* fHitGe;
        TClonesArray* fHitFrs;

        const TGermaniumConfiguration * germanium_configuration;
        
        FrsGate * frsgate;

        uint64_t wr_t_last_frs_hit = 0;
        bool positive_PID = false;

        
        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        EventHeader* header;
        Int_t fNEvents;

        // Canvases and histograms
        TCanvas * c_germanium_energy_vs_tsci41;
        TH2F * h2_germanium_summed_vs_tsci41;
        TCanvas * c_germanium_energy_promptflash_cut;
        TH1F * h1_germanium_energy_promptflash_cut;
        TCanvas * c_germanium_energy_vs_wr_long;
        TH2F * h2_germanium_summed_vs_wr_long;
        TCanvas * c_germanium_energy_promptflash_cut_long;
        TH1F * h1_germanium_energy_promptflash_cut_long;


        // Folder and files
        TFolder* folder_germanium;




    public:
        ClassDef(FrsGermaniumCorrelations, 1)
};

#endif