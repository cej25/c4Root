#ifndef FrsGermaniumCorrelations_H
#define FrsGermaniumCorrelations_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"
#include "FrsHitData.h"
#include "TFrsConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class FrsGate;
class FrsHitItem;
class FrsMultiHitItem;

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

        void AddGammaEnergyOfInterest(double energy, double gate_width){
            gamma_energies_of_interest.emplace_back(energy);
            gate_width_gamma_energies_of_interest.emplace_back(gate_width);
        }


        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };

        void SetShortLifetimeCollectionWindow(int stop){
            stop_short_lifetime_collection = stop;
        }

        void SetLongLifetimeCollectionWindow(int start, int stop) // cut the WR on the start!!
        {
            start_long_lifetime_collection = start;
            stop_long_lifetime_collection = stop;
        }
        void SetLongLifetimePlottingWindow(int start, int stop) // cut the WR on the start!!
        {
            long_lifetime_binlow = start;
            long_lifetime_binhigh = stop;
        }
        
        
    
    private:
        TClonesArray* fHitGe;
        TClonesArray* fHitFrs;

        std::vector<FrsHitItem> const* hitArrayFrs;
        std::vector<FrsMultiHitItem> const* multihitArray;

        const TGermaniumConfiguration * germanium_configuration;
        const TFrsConfiguration * frs_configuration;
        
        FrsGate * frsgate;

        int64_t wr_t_last_frs_hit = 0;
        int64_t wr_t_first_frs_hit = 0;
        bool positive_PID = false;
        bool positive_PID_mhtdc = false;

        Double_t ID_x2 = 0.;
        Double_t ID_y2 = 0.;
        Double_t ID_x4 = 0.;
        Double_t ID_AoQ_mhtdc = 0.;
        Double_t ID_z41_mhtdc = 0.;
        Double_t ID_z42_mhtdc = 0.;
        Double_t ID_dEdegZ41_mhtdc = 0.;

        
        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;


        int start_long_lifetime_collection = 1e3; // must cut the prompt flash
        int stop_long_lifetime_collection = 1e3; // for how long to collect? 
        int long_lifetime_binlow = -10e3;
        int long_lifetime_binhigh = 100e3;

        int stop_short_lifetime_collection = 0;

        int germanium_coincidence_gate = 500; //ns

        std::vector<double> gamma_energies_of_interest;
        std::vector<double> gate_width_gamma_energies_of_interest;

        EventHeader* header;
        Int_t fNEvents;

        // Histograms:
        //FRS - for verification of gates:
        TCanvas * c_frs_Z_vs_AoQ_gated;
        TH2F * h2_frs_Z_vs_AoQ_gated;

        TCanvas * c_frs_Z_vs_Z2_gated;
        TH2F * h2_frs_Z_vs_Z2_gated;

        TCanvas * c_frs_x2_vs_AoQ_gated;
        TH2F * h2_frs_x2_vs_AoQ_gated;
        
        TCanvas * c_frs_x4_vs_AoQ_gated;
        TH2F * h2_frs_x4_vs_AoQ_gated;
        
        //Implant rate
        TCanvas * c_frs_rate;
        TGraph * g_frs_rate;
        int64_t frs_rate_time = 0;
        int frs_rate_implanted = 0;
        
        TCanvas * c_frs_total;
        TGraph * g_frs_total;
        uint64_t frs_total_implanted = 0;

        //short lifetimes:
        TCanvas * c_germanium_energy_vs_tsci41;
        TH2F * h2_germanium_energy_vs_tsci41;

        TCanvas * c_germanium_energy_promptflash_cut;
        TCanvas* c_germanium_energy_promptflash_cut_mhtdc_gated;
        TH1F * h1_germanium_energy_promptflash_cut;
        TH1F* h1_germanium_energy_promptflash_cut_mhtdc_gated;

        TCanvas * c_germanium_energy_energy_promptflash_cut;
        TH2F * h2_germanium_energy_energy_promptflash_cut;

        //long lifetimes:
        TCanvas * c_germanium_energy_vs_sci41_wr_long;
        TH2F * h2_germanium_energy_vs_sci41_wr_long;
        
        TCanvas * c_germanium_energy_promptflash_cut_long;
        TH1F * h1_germanium_energy_promptflash_cut_long;


        TCanvas * c_germanium_energy_energy_promptflash_cut_long; 
        TH2F * h2_germanium_energy_energy_promptflash_cut_long;



        // Energy-gated histograms:
        //short:
        TCanvas ** c_germanium_tsci41_energy_gated;
        TH1F ** h1_germanium_tsci41_energy_gated;

        TCanvas ** c_germanium_energy_promptflash_cut_energy_gated;
        TH1F ** h1_germanium_energy_promptflash_cut_energy_gated;
        
        //long:
        TCanvas ** c_germanium_energy_promptflash_cut_long_energy_gated;
        TH1F ** h1_germanium_energy_promptflash_cut_long_energy_gated;
        
        TCanvas ** c_germanium_twr_sci41_energy_gated;
        TH1F ** h1_germanium_twr_sci41_energy_gated;
        

        int number_of_detectors_to_plot;
        std::vector<std::pair<int,int>> crystals_to_plot;
        TH1** h1_ge_time_ref_frs_wr;



        // Folder and files
        TFolder* histograms;
        TFolder* folder_germanium;
        TFolder ** folder_energy_gated;

        TDirectory* dir_frs;
        TDirectory* dir_frs_ge_corr;
        TDirectory* dir_frs_ge_gate;
        // other




    public:
        ClassDef(FrsGermaniumCorrelations, 1)
};

#endif