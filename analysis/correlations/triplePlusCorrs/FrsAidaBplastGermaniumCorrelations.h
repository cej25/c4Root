#ifndef FrsAidaBplastGermaniumCorrelations_H
#define FrsAidaBplastGermaniumCorrelations_H

#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "FairTask.h"
#include <array>
#include <vector>

class TClonesArray;
class EventHeader;
class EventData;
class TCanvas;
class TH1F;
class TH2F;

class FrsAidaBplastGermaniumCorrelations : public FairTask
{
    public:
        FrsAidaBplastGermaniumCorrelations();
        FrsAidaBplastGermaniumCorrelations(FrsGate * frsgate);
        FrsAidaBplastGermaniumCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~FrsAidaBplastGermaniumCorrelations();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        void AddGammaEnergyOfInterest(double energy, double gate_width){
            gamma_energies_of_interest.emplace_back(energy);
            gate_width_gamma_energies_of_interest.emplace_back(gate_width);
        }

    
    private:
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitFrs;
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;

        const TGermaniumConfiguration* germanium_config;
        const TFrsConfiguration* frs_config;
        const TbPlastConfiguration* bplast_config;
        const TAidaConfigurations* aida_config;

        FrsGate* frsgate;
        std::map<std::pair<int, int>, std::pair<int, std::pair<char, char>>> bplast_map;

        int64_t wr_t_last_frs_hit = 0;
        int64_t wr_t_last_frs_hit = 0;

        bool positive_PID = false;

        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        std::vector<double> gamma_energies_of_interest;
        std::vector<double> gate_width_gamma_energies_of_interest;

        EventHeader* fEventHeader;
        Int_t fNEvents;

        // Canvases

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

        // AIDA - for verification of gates:

        // Implants
        TCanvas * c_aida_implants_dssd1_frs_gated;
        TH2F * h2_aida_implants_dssd1_frs_gated;

        TCanvas * c_aida_implants_dssd2_frs_gated;
        TH2F * h2_aida_implants_dssd2_frs_gated;

        //Decays

        TCanvas * c_aida_decays_dssd1_frs_gated;
        TH2F * h2_aida_decays_dssd1_frs_gated;

        TCanvas * c_aida_decays_dssd2_frs_gated;
        TH2F * h2_aida_decays_dssd2_frs_gated;

        // bPlast fast vs. slow spectra on double gate

        TCanvas * c_bplast_fast_vs_slow_gated;
        TH2F * h2_bplast_fast_vs_slow_gated;

        // Germanium spectra after triple gate

        TCanvas * c_ge_gated;
        TH1F * h1_ge_gated;

        // Energy gated histograms

        TCanvas ** c_germanium_offspill_energy_gated;
        TH1F ** h1_germanium_offspill_energy_gated;

        // TDirectories
        TFolder* folder_germanium;
        TFolder ** folder_energy_gated;



    public:
        ClassDef(FrsAidaBplastGermaniumCorrelations, 1)
};

#endif
