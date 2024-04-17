#ifndef GermaniumOnlineSpectra_H
#define GermaniumOnlineSpectra_H

#include "FairTask.h"
#include "TGermaniumConfiguration.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class GermaniumOnlineSpectra : public FairTask
{
    public:
        GermaniumOnlineSpectra();
        GermaniumOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~GermaniumOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Ge_Histo();

        virtual void Snapshot_Ge_Histo();


        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };

        void AddReferenceDetector(int detector_id, int crystal_id){
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, 0.0));
        }

        void AddReferenceDetectorWithEnergyGates(int detector_id, int crystal_id, double energy_in_other, double energy_in_ref_det){
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(energy_in_other,energy_in_ref_det));
        }

        void AddReferenceDetectorWithEnergyGates(int detector_id, int crystal_id, double energy_in_ref_det){
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, energy_in_ref_det));
        }

        
        void SetEnergyGateWidth(double width){
            energygate_width = width;
        }

        // range setters

    
    private:
        TClonesArray* fHitGe;

        const TGermaniumConfiguration * germanium_configuration;

        // ranges
        int number_of_detectors_to_plot;
        int number_reference_detectors; 
        std::vector<std::pair<int,int>> crystals_to_plot;

        std::vector<std::pair<int,int>> dt_reference_detectors;
        std::vector<std::pair<double,double>> dt_reference_detectors_energy_gates;
        double energygate_width = 5;

        
        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_germanium_time;
        TCanvas* c_germanium_energy;
        TCanvas* c_germanium_energy_vs_detidx;

        TCanvas* c_germanium_hitpattern;
        TCanvas* c_germanium_multiplicity;
        TCanvas* c_germanium_time_differences;
        TCanvas* c_germanium_time_differences_vs_energy;
        TCanvas* c_germanium_rates;
        TCanvas* c_germanium_energy_summed;
        TCanvas* c_germanium_energy_summed_vetosci41;
        TCanvas* c_germanium_energy_summed_vs_tsci41;
        
        TCanvas* c_germanium_energy_summed_vs_tsci41_cut;
        TH1F* h1_germanium_energy_summed_vs_tsci41_cut;

        TCanvas* c_germanium_energy_energy_vetosci41;
        TH2F* h2_germanium_energy_energy_vetosci41;

        TCanvas* c_germanium_energy_energy_sci41_cut;
        TH2F* h2_germanium_energy_energy_sci41_cut;

        TCanvas* c_germanium_snapshot;

        char ** detector_labels;

        // Folder and files
        TFolder* histograms;
        TDirectory* dir_germanium;
        TDirectory* dir_germanium_energy;
        TDirectory* dir_germanium_time;
        TDirectory* dir_germanium_hitpattern;
        TDirectory* dir_germanium_multiplicity;
        TDirectory* dir_germanium_sci41;
        std::vector<TDirectory*> dir_germanium_time_differences;

        TFile* file_germanium_snapshot;

        // Histograms energy
        std::vector<TH1F*> h1_germanium_energy;
        TH2F* h2_germanium_energy_vs_detidx;

        std::vector<std::vector<TH1F*>> h1_germanium_time_differences; // [reference_dector][detector index]
        std::vector<std::vector<TH2F*>> h2_germanium_time_differences_vs_energy; // [reference_dector][detector index]

        TH1F* h1_germanium_energy_summed;
        TH1F* h1_germanium_energy_summed_vetosci41;
        TH2F* h2_germanium_energy_summed_vs_tsci41;

        TH1F* h1_germanium_multiplicity;
        TH1F* h1_germanium_hitpattern;

        // Histograms time
        std::vector<TH1F*> h1_germanium_time;

    public:
        ClassDef(GermaniumOnlineSpectra, 1)
};

#endif