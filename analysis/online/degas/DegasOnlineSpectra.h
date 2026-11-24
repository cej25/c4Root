#ifndef DegasOnlineSpectra_H
#define DegasOnlineSpectra_H

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
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;
class TH1;

class DegasOnlineSpectra : public FairTask
{
    public:
        void SetSpectraDirectory(const TString& name) { fSpectraDirectory = name; }
        void FillEvent();

        DegasOnlineSpectra();
        DegasOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~DegasOnlineSpectra();

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


        void SetResolutionMeasurementParameters(double centr, double width, int64_t time_to_collect_for){
            centroid_resolution = centr;
            width_resolution = width;
            seconds_to_collect_resolution = time_to_collect_for;
        }

        // range setters



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

        // Canvas
        TCanvas* c_degas_time;
        TCanvas* c_degas_energy;
        TCanvas* c_degas_energy_vs_detidx;

        TCanvas* c_degas_hitpattern;
        TCanvas* c_degas_multiplicity;
        TCanvas* c_degas_time_differences;
        TCanvas* c_degas_time_differences_vs_energy;
        TCanvas* c_degas_rates;
        TCanvas* c_degas_energy_summed;
        TCanvas* c_degas_energy_summed_vetosci41;
        TCanvas* c_degas_energy_summed_vs_tsci41;

        TCanvas* c_degas_energy_summed_vs_tsci41_cut;
        TH1* h1_degas_energy_summed_vs_tsci41_cut;

        TCanvas* c_degas_energy_energy_vetosci41;
        TH2* h2_degas_energy_energy_vetosci41;

        TCanvas* c_degas_energy_energy_sci41_cut;
        TH2* h2_degas_energy_energy_sci41_cut;

        const char ** detector_labels;

        // Folder and files
        TFolder* histograms;
        TDirectory* dir_degas;
        TDirectory* dir_degas_energy;
        TDirectory* dir_degas_time;
        TDirectory* dir_degas_hitpattern;
        TDirectory* dir_degas_multiplicity;
        TDirectory* dir_degas_sci41;
        TDirectory* dir_degas_resolution;
        TDirectory* dir_degas_rates;
        std::vector<TDirectory*> dir_degas_time_differences;

        // Histograms energy
        TH1** h1_degas_energy;
        TH2* h2_degas_energy_vs_detidx;

        TH1*** h1_degas_time_differences; // [reference_dector][detector index]
        TH2*** h2_degas_time_differences_vs_energy; // [reference_dector][detector index]

        TH1* h1_degas_energy_summed;
        TH1* h1_degas_energy_summed_vetosci41;
        TH2* h2_degas_energy_summed_vs_tsci41;

        TH1* h1_degas_multiplicity;
        TH1* h1_degas_hitpattern;

        // Histograms time
        TH1** h1_degas_time;


        double centroid_resolution = 1332;
        double width_resolution = 10;


        TF1* f1_gaussian;

        TCanvas* c_last_resolutions_FWHM;

        TH1* h1_last_resolutions_FWHM;
        TH1* h1_last_resolutions_FWTM;
        TH1* h1_last_resolutions_gratio;


        TGraph** g1_resolutions_FWHM;
        TCanvas* c_resolutions_FWHM;

        TGraph** g1_resolutions_FWTM;
        TCanvas* c_resolutions_FWTM;

        TGraph** g1_resolutions_gratio;
        TCanvas* c_resolutions_gratio;

        uint64_t last_time_resolution_was_measured = 0;
        uint64_t current_wr = 0;
        uint64_t first_time = 0;
        int64_t seconds_to_collect_resolution = 10;

        TCanvas * c1_degas_energy_last_fitted;
        TH1** h1_degas_energy_last_fitted;

        TCanvas * c1_degas_energy_last;
        TH1** h1_degas_energy_last;


        TH1** h1_degas_rates;

        // rates
        int64_t saved_degas_wr = 0;
        int* detector_counters;
        int* detector_rates;
        int rate_running_count = 0;

    public:
        ClassDef(DegasOnlineSpectra, 1)
};

#endif
