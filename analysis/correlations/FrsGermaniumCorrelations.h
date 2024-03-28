#ifndef FrsGermaniumCorrelations_H
#define FrsGermaniumCorrelations_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class FrsGate;

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

        void SetShortLifetimeCollectionWindow(int start, int stop){
            start_short_lifetime_collection = start;
            stop_short_lifetime_collection = stop;
        }

        void SetLongLifetimeCollectionWindow(int start, int stop)
        {
            start_long_lifetime_collection = start;
            stop_long_lifetime_collection = stop;
            start_long_lifetime_collection_background = stop;
            stop_long_lifetime_collection_background = stop;
        }
        
        void SetLongLifetimeCollectionWindow(int start, int stop, int bgstart, int bgstop)
        {
            start_long_lifetime_collection = start;
            stop_long_lifetime_collection = stop;
            start_long_lifetime_collection_background = bgstart;
            stop_long_lifetime_collection_background = bgstop;
        }
        
    
    private:
        TClonesArray* fHitGe;
        TClonesArray* fHitFrs;

        const TGermaniumConfiguration * germanium_configuration;
        
        FrsGate * frsgate;

        uint64_t wr_t_last_frs_hit = 0;
        bool positive_PID = false;

        
        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;


        int start_long_lifetime_collection = 0;
        int stop_long_lifetime_collection = 0;
        int start_long_lifetime_collection_background = 0;
        int stop_long_lifetime_collection_background = 0;

        int start_short_lifetime_collection = 0;
        int stop_short_lifetime_collection = 0;

        int germanium_coincidence_gate = 200; //ns

        std::vector<double> gamma_energies_of_interest;
        std::vector<double> gate_width_gamma_energies_of_interest;

        EventHeader* header;
        Int_t fNEvents;

        // Histograms:
        //FRS
        TCanvas * c_frs_Z_vs_AoQ_gated;
        TH2F * h2_frs_Z_vs_AoQ_gated;

        //short lifetimes:
        TCanvas * c_germanium_energy_vs_tsci41;
        TH2F * h2_germanium_summed_vs_tsci41;
        TCanvas * c_germanium_energy_promptflash_cut;
        TH1F * h1_germanium_energy_promptflash_cut;
        TCanvas * c_germanium_energy_energy_promptflash_cut;
        TH2F * h2_germanium_energy_energy_promptflash_cut;

        //long lifetimes:
        TCanvas * c_germanium_energy_vs_wr_long;
        TH2F * h2_germanium_summed_vs_wr_long;
        TCanvas * c_germanium_energy_promptflash_cut_long;
        TH1F * h1_germanium_energy_promptflash_cut_long;


        //Implant rate
        TCanvas * c_frs_rate;
        TGraph * g_frs_rate;
        uint64_t frs_rate_time = 0;
        int frs_rate_implanted = 0;

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
        TFolder* folder_germanium;
        TFolder ** folder_energy_gated;




    public:
        ClassDef(FrsGermaniumCorrelations, 1)
};

#endif