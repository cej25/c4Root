#ifndef BGOOnlineSpectra_H
#define BGOOnlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

#include "TGermaniumConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

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

        void SetCoincidenceWindow(int window)
        {
            BGO_Germanium_wr_coincidence_window = window;
        };

        void SetCoincidenceOffset(int offset)
        {
            BGO_Germanium_wr_coincidence_window_offset = offset;
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
        int BGO_Germanium_wr_coincidence_window_offset = 0;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_bgo_time;
        TCanvas* c_bgo_energy;
        
        TCanvas* c_germanium_bgo_veto_energy;
        TCanvas* c_germanium_bgo_vetotrue_energy;
        TCanvas* c_germanium_bgo_veto_timedifferences;

        TCanvas* c_bgo_snapshot;
        
        // Folder and files
        TFolder* histograms;
        TDirectory* dir_bgo;
        TDirectory* dir_bgo_energy;
        TDirectory* dir_bgo_time;
        TDirectory* dir_bgo_germanium_veto_energy;
        TDirectory* dir_bgo_germanium_vetotrue_energy;
        TDirectory* dir_bgo_germanium_veto_timedifferences;

        TFile* file_bgo_snapshot;

        //TFile* file_germanium_snapshot;

        // Histograms energy
        std::vector<TH1F*> h1_bgo_energy;
        std::vector<TH1F*> h1_bgo_time;
        std::vector<TH1F*> h1_germanium_bgo_veto_energy;
        std::vector<TH1F*> h1_germanium_bgo_vetotrue_energy; // plot what we're vetoing
        std::vector<TH1F*> h1_germanium_bgo_veto_timedifferences;

    public:
        ClassDef(BGOOnlineSpectra, 1)
};

#endif