#ifndef DegasBGOOnlineSpectra_H
#define DegasBGOOnlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

#include "TDegasConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class DegasBGOOnlineSpectra : public FairTask
{
    public:
        DegasBGOOnlineSpectra();
        DegasBGOOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~DegasBGOOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();


        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh;
        };

        void SetCoincidenceWindow(int window)
        {
        };

        void SetCoincidenceOffset(int offset)
        {
        };



    private:
        TClonesArray* fHitGe;
        TClonesArray* fHitBGO;

        const TDegasConfiguration * degas_configuration;
        const TBGOTwinpeaksConfiguration * BGO_configuration;

        // ranges
        int number_of_detectors_to_plot;
        std::vector<std::pair<int,int>> crystals_to_plot;


        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;


        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_bgo_time;
        TCanvas* c_bgo_energy;

        TCanvas* c_degas_bgo_veto_energy;
        TCanvas* c_degas_bgo_vetotrue_energy;
        TCanvas* c_degas_bgo_veto_timedifferences;

        // Folder and files
        TFolder* histograms;
        TDirectory* dir_bgo;
        TDirectory* dir_bgo_energy;
        TDirectory* dir_bgo_time;
        TDirectory* dir_bgo_degas_veto_energy;
        TDirectory* dir_bgo_degas_vetotrue_energy;
        TDirectory* dir_bgo_degas_veto_time_differences;

        TFile* file_bgo_snapshot;

        //TFile* file_degas_snapshot;

        // Histograms energy
        std::vector<TH1*> h1_bgo_energy;
        std::vector<TH1*> h1_bgo_time;
        std::vector<TH1*> h1_degas_bgo_veto_energy;
        std::vector<TH1*> h1_degas_bgo_vetotrue_energy; // plot what we're vetoing
        std::vector<TH1*> h1_degas_bgo_veto_timedifferences;

    public:
        ClassDef(DegasBGOOnlineSpectra, 1)
};

#endif
