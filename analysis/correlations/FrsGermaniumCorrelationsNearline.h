#ifndef FrsGermaniumCorrelationsNearline_H
#define FrsGermaniumCorrelationsNearline_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"
#include "TFrsConfiguration.h"
#include "FrsHitData.h"
#include "EventHeader.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class FrsGate;

class FrsGermaniumCorrelationsNearline : public FairTask
{
    public:
        FrsGermaniumCorrelationsNearline();
        FrsGermaniumCorrelationsNearline(FrsGate * frsgate);
        FrsGermaniumCorrelationsNearline(const TString& name, Int_t verbose = 1);

        void SetMultiHit(bool v) {use_multi = v;};


        virtual ~FrsGermaniumCorrelationsNearline();

        //virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        //virtual void Reset_Ge_Histo();

        //virtual void Snapshot_Ge_Histo();

        void SetAnlOrCalInput(TString AnlOrCal){
            input_anl_or_cal = AnlOrCal;
        }

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
        
        void SetControlOutput(bool a){fControlOutput = a;} // writes the events that passes the fatima and frs gates to a tree
        void SetWriteOutput(bool a){fWriteOutput = a;} // writes the events that passes the fatima and frs gates to a tree
    
    private:
        TClonesArray* fHitGe;
        TClonesArray* fHitFrs;
        TClonesArray* fMultiHitFrs;

        std::vector<FrsHitItem> const* hitArrayFrs;
        std::vector<FrsMultiHitItem> const* multihitArrayFrs;



        bool fWriteOutput = true;
        bool fControlOutput = false;
        TString input_anl_or_cal = "Cal";
        FairRunAna * run;

        

        const TGermaniumConfiguration * germanium_configuration;
        const TFrsConfiguration * frs_configuration;
        
        FrsGate * frsgate;

        int64_t wr_t = 0;

        bool use_multi = false;


        int64_t wr_t_last_frs_hit = 0;
        int64_t wr_t_first_frs_hit = 0;
        bool positive_PID = false;

        
        int fenergy_nbins = 3000;
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

        EventHeader const* header;
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

        TCanvas * c_frs_Z_vs_dEdeg_gated;
        TH2F * h2_frs_Z_vs_dEdeg_gated;
        
        TCanvas * c_frs_Z_vs_sci42E_gated;
        TH2F * h2_frs_Z_vs_sci42E_gated;
        
        //reverse energy-gated
        TCanvas ** c_frs_Z_vs_AoQ_reverse_gated;
        TH2F ** h2_frs_Z_vs_AoQ_reverse_gated;

        TCanvas ** c_frs_Z_vs_Z2_reverse_gated;
        TH2F ** h2_frs_Z_vs_Z2_reverse_gated;

        TCanvas ** c_frs_x2_vs_AoQ_reverse_gated;
        TH2F ** h2_frs_x2_vs_AoQ_reverse_gated;
        
        TCanvas ** c_frs_x4_vs_AoQ_reverse_gated;
        TH2F ** h2_frs_x4_vs_AoQ_reverse_gated;
        
        //on wr:
        TCanvas ** c_frs_Z_vs_AoQ_reverse_wr_gated;
        TH2F ** h2_frs_Z_vs_AoQ_reverse_wr_gated;

        TCanvas ** c_frs_Z_vs_Z2_reverse_wr_gated;
        TH2F ** h2_frs_Z_vs_Z2_reverse_wr_gated;

        TCanvas ** c_frs_x2_vs_AoQ_reverse_wr_gated;
        TH2F ** h2_frs_x2_vs_AoQ_reverse_wr_gated;
        
        TCanvas ** c_frs_x4_vs_AoQ_reverse_wr_gated;
        TH2F ** h2_frs_x4_vs_AoQ_reverse_wr_gated;
        
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

        TCanvas * c_germanium_energy_vs_log_tsci41;
        TH2F * h2_germanium_energy_vs_log_tsci41;

        TCanvas * c_germanium_energy_promptflash_cut;
        TH1F * h1_germanium_energy_promptflash_cut;

        TCanvas * c_germanium_energy_energy_promptflash_cut;
        TH2F * h2_germanium_energy_energy_promptflash_cut;

        //long lifetimes:
        TCanvas * c_germanium_energy_vs_sci41_wr_long;
        TH2F * h2_germanium_energy_vs_sci41_wr_long;
        
        TCanvas * c_germanium_energy_promptflash_cut_long;
        TH1F * h1_germanium_energy_promptflash_cut_long;


        TCanvas * c_germanium_energy_energy_promptflash_cut_long; 
        TH2F * h2_germanium_energy_energy_promptflash_cut_long;

        int number_of_detectors_to_plot;
        std::vector<std::pair<int,int>> crystals_to_plot;
        char** detector_labels;
        TH1* h1_germanium_hitpattern_post6us;


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
        
        // Folder and files
        bool found_dir_corr = true;
        TDirectory* dir_corr;
        TDirectory* dir_germanium;
        TDirectory ** folder_energy_gated;




    public:
        ClassDef(FrsGermaniumCorrelationsNearline, 1)
};

#endif