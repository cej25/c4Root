#ifndef FrsFatimaCorrelations_H
#define FrsFatimaCorrelations_H

#include "FairTask.h"

#include "TFatimaTwinpeaksConfiguration.h"

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



        virtual ~FrsFatimaCorrelations();

        //virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

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
        
        
    
    private:
        TClonesArray* fHitFatima;
        TClonesArray* fHitFrs;

        const TFatimaTwinpeaksConfiguration * fatima_configuration;
        
        FrsGate * frsgate;

        int64_t wr_t_last_frs_hit = 0;
        bool positive_PID = false;

        
        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;


        int start_long_lifetime_collection = 1e3; // must cut the prompt flash
        int stop_long_lifetime_collection = 1e3; // for how long to collect? 

        int stop_short_lifetime_collection = 0;

        int fatima_coincidence_gate = 100; //ns

        std::vector<double> gamma_energies_of_interest;
        std::vector<double> gate_width_gamma_energies_of_interest;

        EventHeader* header;
        Int_t fNEvents;

        // Histograms:
        //FRS
        TCanvas * c_frs_Z_vs_AoQ_gated;
        TH2F * h2_frs_Z_vs_AoQ_gated;

        //short lifetimes:
        TCanvas * c_fatima_energy_vs_tsci41;
        TH2F * h2_fatima_summed_vs_tsci41;
        TCanvas * c_fatima_energy_promptflash_cut;
        TH1F * h1_fatima_energy_promptflash_cut;
        TCanvas * c_fatima_energy_energy_promptflash_cut;
        TH2F * h2_fatima_energy_energy_promptflash_cut;

        //long lifetimes:
        TCanvas * c_fatima_energy_vs_wr_long;
        TH2F * h2_fatima_summed_vs_wr_long;
        TCanvas * c_fatima_energy_promptflash_cut_long;
        TH1F * h1_fatima_energy_promptflash_cut_long;


        //Implant rate
        TCanvas * c_frs_rate;
        TGraph * g_frs_rate;
        int64_t frs_rate_time = 0;
        int frs_rate_implanted = 0;

        // Energy-gated histograms:
        //short:
        TCanvas ** c_fatima_tsci41_energy_gated;
        TH1F ** h1_fatima_tsci41_energy_gated;

        TCanvas ** c_fatima_energy_promptflash_cut_energy_gated;
        TH1F ** h1_fatima_energy_promptflash_cut_energy_gated;
        
        //long:
        TCanvas ** c_fatima_energy_promptflash_cut_long_energy_gated;
        TH1F ** h1_fatima_energy_promptflash_cut_long_energy_gated;
        
        TCanvas ** c_fatima_twr_sci41_energy_gated;
        TH1F ** h1_fatima_twr_sci41_energy_gated;
        




        // Folder and files
        TFolder* folder_fatima;
        TFolder ** folder_energy_gated;




    public:
        ClassDef(FrsFatimaCorrelations, 1)
};

#endif