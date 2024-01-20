#ifndef FatimaTimingAnalysis_H
#define FatimaTimingAnalysis_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FatimaTimingAnalysis : public FairTask
{
    public:
        FatimaTimingAnalysis();
        FatimaTimingAnalysis(const TString& name, Int_t verbose = 1);

        void SetDetectorToAnalyze(std::vector<int> * detectors_analyze){detector_id_analyze = detectors_analyze;};
        void SetEnergies(double fE1, double fE2, double fgatewidth){E1 = fE1; E2 = fE2; Egatewidth = fgatewidth;}
        void SetdTHistoBinSize(int fNbins, double flowBin, double fhighBin){Nbins = fNbins; lowBin = flowBin; highBin = fhighBin;};

        virtual ~FatimaTimingAnalysis();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;

        std::vector<int> * detector_id_analyze;


        EventHeader* header;
        Int_t fNEvents;     


        //Histograms to create:
        TH2F * h_slow_ToT_vs_detector_id;
        TH2F * h_energy_vs_detector_id;
        TH2F * h_energy_energy;


        int Nbins = 1000;
        double lowBin = -100;
        double highBin = 100;


        double E1;
        double E2;
        double Egatewidth;

        TH1F *** h_energy_E1_E2_dt;

        


        



    public:
        ClassDef(FatimaTimingAnalysis, 1)
};

#endif
