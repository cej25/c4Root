#ifndef FatimaGermaniumCorrelations_H
#define FatimaGermaniumCorrelations_H

#include "FairTask.h"

#include "TFatimaTwinpeaksConfiguration.h"
#include "TGermaniumConfiguration.h"
#include "TFrsConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class FatimaGermaniumCorrelations : public FairTask
{
    public:
        FatimaGermaniumCorrelations();
        FatimaGermaniumCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~FatimaGermaniumCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        void AddGammaEnergyOfInterestGermanium(double energy, double gate_width){
            gamma_energies_of_interest_germanium.emplace_back(energy);
            gate_width_gamma_energies_of_interest_germanium.emplace_back(gate_width);
        }
        
        void AddGammaEnergyOfInterestFatima(double energy, double gate_width){
            gamma_energies_of_interest_fatima.emplace_back(energy);
            gate_width_gamma_energies_of_interest_fatima.emplace_back(gate_width);
        }


        void SetBinningEnergyFatima(int nbins, float binlow, float binhigh){
            ffatima_energy_nbins = nbins;
            ffatima_energy_bin_low = binlow;
            ffatima_energy_bin_high = binhigh; 
        };
        
        void SetBinningEnergyGermanium(int nbins, float binlow, float binhigh){
            fgermanium_energy_nbins = nbins;
            fgermanium_energy_bin_low = binlow;
            fgermanium_energy_bin_high = binhigh; 
        };


        void SetBinningCoincidences(int nbins, float binlow, float binhigh){
            ftime_coincidence_nbins = nbins;
            ftime_coincidence_low = binlow;
            ftime_coincidence_high = binhigh;
        }
        
        
    private:
        TClonesArray* fHitFatima;
        TClonesArray* fHitGermanium;

        const TFatimaTwinpeaksConfiguration * fatima_configuration;
        const TGermaniumConfiguration * germanium_configuration;


        int ffatima_energy_nbins = 1500;
        int ffatima_energy_bin_low = 0;
        int ffatima_energy_bin_high = 1500;
        
        int fgermanium_energy_nbins = 1500;
        int fgermanium_energy_bin_low = 0;
        int fgermanium_energy_bin_high = 1500;
        
        
        int ftime_coincidence_nbins = 1000;
        int ftime_coincidence_low = 0;
        int ftime_coincidence_high = 1000;

        int fatima_coincidence_gate = 500; //ns
        int germanium_coincidence_gate = 500; //ns
        int fatima_germanium_coincidence_gate = 500; //ns

        std::vector<double> gamma_energies_of_interest_fatima;
        std::vector<double> gate_width_gamma_energies_of_interest_fatima;

        std::vector<double> gamma_energies_of_interest_germanium;
        std::vector<double> gate_width_gamma_energies_of_interest_germanium;

        EventHeader* header;
        Int_t fNEvents;


        // Folder and files
        TDirectory* dir_fatima_germanium;
        TDirectory ** folder_energy_gated;




    public:
        ClassDef(FatimaGermaniumCorrelations, 1)
};

#endif