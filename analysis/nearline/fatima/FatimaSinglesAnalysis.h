#ifndef FatimaSinglesAnalysis_H
#define FatimaSinglesAnalysis_H

#include "FairTask.h"
#include "FairRootManager.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FatimaSinglesAnalysis : public FairTask
{
    public:
        FatimaSinglesAnalysis();
        FatimaSinglesAnalysis(const TString& name, Int_t verbose = 1);
        
        void SetDetectorToAnalyze(std::vector<int> * detectors_analyze){detector_id_analyze = detectors_analyze;};

        virtual ~FatimaSinglesAnalysis();

        virtual void SetParContainers();

        void SetBinningFastToT(int nbins, float binlow, float binhigh){
            ffast_tot_nbins = nbins;
            ffast_tot_bin_low = binlow;
            ffast_tot_bin_high = binhigh;
        };

        void SetBinningSlowToT(int nbins, float binlow, float binhigh){
            fslow_tot_nbins = nbins;
            fslow_tot_bin_low = binlow;
            fslow_tot_bin_high = binhigh;
        };
        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;

        FairRootManager* mgr;

        std::vector<int> * detector_id_analyze;


        EventHeader* header;
        Int_t fNEvents;     


        //Histograms to create:
        TH1F ** h_slow_ToT;
        TH1F ** h_fast_ToT;
        TH1F ** h_energy;
        

        int ffast_tot_nbins = 500;
        float ffast_tot_bin_low = 0;
        float ffast_tot_bin_high = 2500; 
        int fslow_tot_nbins = 500;
        float fslow_tot_bin_low = 0;
        float fslow_tot_bin_high = 2500;
        int fenergy_nbins = 500;
        float fenergy_bin_low = 0;
        float fenergy_bin_high = 1500;




    public:
        ClassDef(FatimaSinglesAnalysis, 1)
};

#endif
