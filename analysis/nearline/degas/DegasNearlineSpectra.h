#ifndef DegasNearlineSpectra_H
#define DegasNearlineSpectra_H

#include "FairTask.h"
#include "TDegasConfiguration.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TH1;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class DegasNearlineSpectra : public FairTask
{
    public:
        void SetSpectraDirectory(const TString& name) { fSpectraDirectory = name; }
        void FillEvent();

        DegasNearlineSpectra();
        DegasNearlineSpectra(const TString& name, Int_t verbose = 1);

        void CreateHistograms();

        virtual ~DegasNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();


        void SetBinningEnergy(int nbins, float binlow, float binhigh)
        {
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh;
        };

        void AddReferenceDetector(int detector_id, int crystal_id)
        {
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, 0.0));
        }

        void AddReferenceDetectorWithEnergyGates(int detector_id, int crystal_id, double energy_in_other, double energy_in_ref_det)
        {
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(energy_in_other,energy_in_ref_det));
        }

        void AddReferenceDetectorWithEnergyGates(int detector_id, int crystal_id, double energy_in_ref_det)
        {
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, energy_in_ref_det));
        }

        void SetEnergyGateWidth(double width)
        {
            energygate_width = width;
        }


    private:
        TString fSpectraDirectory; //! Alternate directory for gated spectra
        TClonesArray* fHitGe;

        const TDegasConfiguration * degas_configuration;

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

        TH1* h1_degas_energy_summed_vs_tsci41_cut;
        TH2* h2_degas_energy_energy_vetosci41;
        TH2* h2_degas_energy_energy_sci41_cut;

        char** detector_labels;

        // Folder and files
        TDirectory* dir_degas;
        TDirectory* dir_degas_energy;
        TDirectory* dir_degas_drift;
        TDirectory* dir_degas_time;
        TDirectory* dir_degas_hitpattern;
        TDirectory* dir_degas_multiplicity;
        TDirectory* dir_degas_sci41;
        TDirectory* dir_degas_rates;
        std::vector<TDirectory*> dir_degas_time_differences;

        // Histograms energy
        std::vector<TH1*> h1_degas_energy;
        std::vector<TH2*> h2_degas_energy_vs_t;
        TH2* h2_degas_energy_vs_detidx;

        std::vector<std::vector<TH1*>> h1_degas_time_differences; // [reference_dector][detector index]
        std::vector<std::vector<TH2*>> h2_degas_time_differences_vs_energy; // [reference_dector][detector index]

        TH1* h1_degas_energy_summed;
        TH1* h1_degas_energy_summed_vetosci41;
        TH2* h2_degas_energy_summed_vs_tsci41;

        TH1* h1_degas_multiplicity;
        TH1* h1_degas_hitpattern;

        // Histograms time
        std::vector<TH1*> h1_degas_time;

        TH1** h1_degas_rates;

        // rates
        int64_t saved_degas_wr = 0;
        int* detector_counters;
        int* detector_rates;
        int rate_running_count = 0;

    public:
        ClassDef(DegasNearlineSpectra, 1)
};

#endif
