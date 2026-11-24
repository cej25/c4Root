#ifndef AidaDegasCorrelations_H
#define AidaDegasCorrelations_H

#include "FairTask.h"

#include "TDegasConfiguration.h"
#include "AidaHitData.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class AidaDegasCorrelations : public FairTask
{
    public:
        AidaDegasCorrelations();
        AidaDegasCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~AidaDegasCorrelations();

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

        const TDegasConfiguration * degas_configuration;

        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        uint64_t aida_hit_time = 0;
        double aida_hit_energy = 0;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TFolder* folder_spectra;
        TCanvas * c_degas_energy_time;
        TH2F * h1_aida_degas_energy_time;
        TCanvas * c_degas_energy;
        TH1F * h1_aida_degas_energy;

    public:
        ClassDef(AidaDegasCorrelations, 1)
};

#endif
