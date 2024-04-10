#ifndef GermaniumResolution_H
#define GermaniumResolution_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class GermaniumResolution : public FairTask
{
    public:
        GermaniumResolution();
        GermaniumResolution(const TString& name, Int_t verbose = 1);

        virtual ~GermaniumResolution();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };


        void SetPeakOfInterest(double energy, double fitwidth){
            peak_interest_energy = energy;
            peak_interest_fitwidth = fitwidth;
        };

        // range setters

    
    private:
        TClonesArray* fHitGe;

        const TGermaniumConfiguration * germanium_configuration;

        // ranges
        int number_of_detectors_to_plot;
        int number_reference_detectors; 
        std::vector<std::pair<int,int>> crystals_to_plot;

        int fenergy_nbins = 3000;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        double peak_interest_energy;
        double peak_interest_fitwidth;

        EventHeader* header;
        Int_t fNEvents;

        uint64_t last_wr = 0;
        uint64_t current_wr = 0;
        uint64_t first_wr = 0;

        // Canvas
        TCanvas* c_germanium_energy;
        TH1F ** h1_germanium_energy;
        TH1F ** h1_germanium_energy_clear;


        std::vector<double> * resoltutions;
        std::vector<double> * resoltutions_err;
        std::vector<uint64_t> * time;
        



    public:
        ClassDef(GermaniumResolution, 1)
};

#endif