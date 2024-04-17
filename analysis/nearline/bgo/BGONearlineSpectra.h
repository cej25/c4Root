#ifndef BGONearlineSpectra_H
#define BGONearlineSpectra_H

#include "FairTask.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

#include "TGermaniumConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"

class TClonesArray;
class EventHeader;
class TH1F;
class TH2F;
class TFile;
class TDirectory;

class BGONearlineSpectra : public FairTask
{
    public:
        BGONearlineSpectra();
        BGONearlineSpectra(const TString& name, Int_t verbose = 1);

        void CreateHistograms();

        virtual ~BGONearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

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
 
        // Folder and files
        TDirectory* dir_bgo;
        TDirectory* dir_bgo_energy;
        TDirectory* dir_bgo_time;
        TDirectory* dir_bgo_germanium_veto_energy;
        TDirectory* dir_bgo_germanium_veto_timedifferences;


        // Histograms energy
        std::vector<TH1F*> h1_bgo_energy;
        std::vector<TH1F*> h1_bgo_time;
        std::vector<TH1F*> h1_germanium_bgo_veto_energy;
        std::vector<TH1F*> h1_germanium_bgo_veto_timedifferences;

    public:
        ClassDef(BGONearlineSpectra, 1)
};

#endif