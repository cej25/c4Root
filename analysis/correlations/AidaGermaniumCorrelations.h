#ifndef AidaGermaniumCorrelations_H
#define AidaGermaniumCorrelations_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"
#include "AidaHitData.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class AidaGermaniumCorrelations : public FairTask
{
    public:
        AidaGermaniumCorrelations();
        AidaGermaniumCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~AidaGermaniumCorrelations();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };

        // range setters

    
    private:
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* implantHitArray;

        const TGermaniumConfiguration * germanium_configuration;

        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        uint64_t aida_hit_time = 0;
        double aida_hit_energy = 0;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TFolder* folder_spectra;
        TCanvas * c_germanium_energy_time;
        TH2F * h1_aida_germanium_energy_time;
        TCanvas * c_germanium_energy;
        TH1F * h1_aida_germanium_energy;

    public:
        ClassDef(AidaGermaniumCorrelations, 1)
};

#endif