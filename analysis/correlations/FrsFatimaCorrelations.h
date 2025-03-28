#ifndef FrsFatimaCorrelations_H
#define FrsFatimaCorrelations_H

#include "FairTask.h"

#include "TFatimaTwinpeaksConfiguration.h"
#include "TFrsConfiguration.h"
#include "FrsHitData.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class FrsGate;

class FrsFatimaCorrelations : public FairTask
{
    public:
        FrsFatimaCorrelations();
        FrsFatimaCorrelations(FrsGate * frsgate);
        FrsFatimaCorrelations(const TString& name, Int_t verbose = 1);

        void SetMultiHit(bool v) {use_multi = v;};


        virtual ~FrsFatimaCorrelations();

        //virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        int CountMultiplicity(TClonesArray *, int);
        int CountMultiplicityOutsidePromptFlashSCI41(TClonesArray*, int , double , int64_t );
        int CountMultiplicityOutsidePromptFlashWR(TClonesArray*, int, int64_t);
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


        void SetBinningCoincidences(int nbins, float binlow, float binhigh){
            ftime_coincidence_nbins = nbins;
            ftime_coincidence_low = binlow;
            ftime_coincidence_high = binhigh;
        }

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
        TClonesArray* fHitFatima;
        // no idea what these are for
        TClonesArray* fHitFrs;
        TClonesArray* fMultiHitFrs;


        std::vector<FrsHitItem> const* hitArrayFrs;
        std::vector<FrsMultiHitItem> const* multihitArrayFrs;


        const TFatimaTwinpeaksConfiguration * fatima_configuration;
        const TFrsConfiguration * frs_configuration;
        
        FrsGate * frsgate;

        bool use_multi = false;

        int64_t wr_t_last_frs_hit = 0;
        int64_t wr_t_first_frs_hit = 0;
        bool positive_PID = false;

        
        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;
        int ftime_coincidence_nbins = 1000;
        int ftime_coincidence_low = -1000;
        int ftime_coincidence_high = 1000;


        int start_long_lifetime_collection = 1e3; // must cut the prompt flash
        int stop_long_lifetime_collection = 1e3; // for how long to collect? 
        int long_lifetime_binlow = -10e3;
        int long_lifetime_binhigh = 100e3;

        int stop_short_lifetime_collection = 0;

        int fatima_coincidence_gate = 10; //ns

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


        TCanvas * c_frs_Z_vs_dEdeg_gated;
        TH2F * h2_frs_Z_vs_dEdeg_gated;
        
        TCanvas * c_frs_Z_vs_sci42E_gated;
        TH2F * h2_frs_Z_vs_sci42E_gated;
        
        //Implant rate
        TCanvas * c_frs_rate;
        TGraph * g_frs_rate;
        int64_t frs_rate_time = 0;
        int frs_rate_implanted = 0;
        
        TCanvas * c_frs_total;
        TGraph * g_frs_total;
        uint64_t frs_total_implanted = 0;

        //short lifetimes:
        TCanvas * c_fatima_energy_vs_tsci41;
        TH2F * h2_fatima_energy_vs_tsci41;

        TCanvas * c_fatima_multiplicity_vs_tsci41;
        TH2F * h2_fatima_multiplicity_vs_tsci41;

        TCanvas * c_fatima_energy_promptflash_cut;
        TH1F * h1_fatima_energy_promptflash_cut;

        TCanvas * c_fatima_energy_vs_sci41_mult1;
        TH2F * h2_fatima_energy_vs_sci41_mult1;

        TCanvas * c_fatima_energy_promptflash_cut_mult1;
        TH1F * h1_fatima_energy_promptflash_cut_mult1;

        TCanvas * c_fatima_energy_vs_sci41_mult2;
        TH2F * h2_fatima_energy_vs_sci41_mult2;

        TCanvas * c_fatima_energy_promptflash_cut_mult2;
        TH1F * h1_fatima_energy_promptflash_cut_mult2;

        TCanvas * c_fatima_energy_vs_sci41_mult3;
        TH2F * h2_fatima_energy_vs_sci41_mult3;

        TCanvas * c_fatima_energy_promptflash_cut_mult3;
        TH1F * h1_fatima_energy_promptflash_cut_mult3;

        TCanvas * c_fatima_energy_vs_sci41_mult4p;
        TH2F * h2_fatima_energy_vs_sci41_mult4p;

        TCanvas * c_fatima_energy_promptflash_cut_mult4p;
        TH1F * h1_fatima_energy_promptflash_cut_mult4p;



        TCanvas * c_fatima_energy_energy_promptflash_cut;
        TH2F * h2_fatima_energy_energy_promptflash_cut;

        //long lifetimes:
        TCanvas * c_fatima_energy_vs_sci41_wr_long;
        TH2F * h2_fatima_energy_vs_sci41_wr_long;

        TCanvas * c_fatima_multiplicity_vs_sci41_wr_long;
        TH2F * h2_fatima_multiplicity_vs_sci41_wr_long;
        
        TCanvas * c_fatima_energy_promptflash_cut_long;
        TH1F * h1_fatima_energy_promptflash_cut_long;


        TCanvas * c_fatima_energy_energy_promptflash_cut_long;
        TH2F * h2_fatima_energy_energy_promptflash_cut_long;

        TCanvas * c_fatima_energy_vs_sci41_wr_long_mult1;
        TH2F * h2_fatima_energy_vs_sci41_wr_long_mult1;

        TCanvas * c_fatima_energy_promptflash_cut_long_mult1;
        TH1F * h1_fatima_energy_promptflash_cut_long_mult1;

        TCanvas * c_fatima_energy_vs_sci41_wr_long_mult2;
        TH2F * h2_fatima_energy_vs_sci41_wr_long_mult2;

        TCanvas * c_fatima_energy_promptflash_cut_long_mult2;
        TH1F * h1_fatima_energy_promptflash_cut_long_mult2;

        TCanvas * c_fatima_energy_vs_sci41_wr_long_mult3;
        TH2F * h2_fatima_energy_vs_sci41_wr_long_mult3;

        TCanvas * c_fatima_energy_promptflash_cut_long_mult3;
        TH1F * h1_fatima_energy_promptflash_cut_long_mult3;

        TCanvas * c_fatima_energy_vs_sci41_wr_long_mult4p;
        TH2F * h2_fatima_energy_vs_sci41_wr_long_mult4p;

        TCanvas * c_fatima_energy_promptflash_cut_long_mult4p;
        TH1F * h1_fatima_energy_promptflash_cut_long_mult4p;



        // Energy-gated histograms:
        //short:
        TCanvas ** c_fatima_tsci41_energy_gated;
        TH1F ** h1_fatima_tsci41_energy_gated;

        TCanvas ** c_fatima_energy_promptflash_cut_energy_gated;
        TH1F ** h1_fatima_energy_promptflash_cut_energy_gated;

        TCanvas ** c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut;
        TH2F ** h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut;
        
        //long:
        TCanvas ** c_fatima_energy_promptflash_cut_long_energy_gated;
        TH1F ** h1_fatima_energy_promptflash_cut_long_energy_gated;
        
        TCanvas ** c_fatima_twr_sci41_energy_gated;
        TH1F ** h1_fatima_twr_sci41_energy_gated;

        TCanvas ** c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long;
        TH2F ** h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long;
        
        TCanvas * c_fatima_sci41_hits;
        TH1F * h1_fatima_sci41_hits;

        
        TCanvas * c_fatima_sci41_energy;
        TH1F * h1_fatima_sci41_energy;



        // Folder and files
        TFolder* histograms;
        TDirectory* dir_corr;
        TDirectory* dir_fatima;
        TDirectory** dir_energy_gated;


    public:
        ClassDef(FrsFatimaCorrelations, 1)
};

#endif