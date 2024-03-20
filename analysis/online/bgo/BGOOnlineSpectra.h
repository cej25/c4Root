#ifndef BGOOnlineSpectra_H
#define BGOOnlineSpectra_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class BGOOnlineSpectra : public FairTask
{
    public:
        BGOOnlineSpectra();
        BGOOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~BGOOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_BGO_Histo();

        virtual void Snapshot_BGO_Histo();


        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };
        
    
    private:
        TClonesArray* fHitGe;
        TClonesArray* fHitBGO;

        const TGermaniumConfiguration * germanium_configuration;
        const TBGOTwinpeaksConfiguration * BGO_configuration;

        // ranges
        int number_of_detectors_to_plot;
        std::vector<std::pair<int,int>> crystals_to_plot;


        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        int BGO_Germanium_wr_coincidence_window = 2000;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_bgo_time;
        TCanvas* c_bgo_energy;
        
        TCanvas* c_germanium_bgo_veto_energy;
        TCanvas* c_germanium_bgo_veto_timedifferences;
        
        // Folder and files
        TFolder* folder_bgo;
        TFolder* folder_bgo_energy;
        TFolder* folder_bgo_time;
        TFolder* folder_bgo_germanim_veto_energy;
        TFolder* folder_bgo_germanim_veto_timedifferences;

        //TFile* file_germanium_snapshot;

        // Histograms energy
        TH1F ** h1_bgo_energy;
        TH1F ** h1_bgo_time;
        
        TH1F ** h1_germanium_bgo_veto_energy;
        TH1F ** h1_germanium_bgo_veto_timedifferences;

    public:
        ClassDef(BGOOnlineSpectra, 1)
};

#endif