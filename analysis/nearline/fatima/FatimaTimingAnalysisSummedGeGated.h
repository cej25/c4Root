#ifndef FatimaTimingAnalysisSummedGeGated_H
#define FatimaTimingAnalysisSummedGeGated_H

#include "FairTask.h"
#include "FairRootManager.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TGermaniumConfiguration.h"


class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FatimaTimingAnalysisSummedGeGated : public FairTask
{
    public:
        FatimaTimingAnalysisSummedGeGated();
        FatimaTimingAnalysisSummedGeGated(const TString& name, Int_t verbose = 1);
        
        
        Bool_t SetDetectorTimeshifts(TString filename);

        void SetEnergies(double fE1, double fE2, double fgatewidth){E1 = fE1; E2 = fE2; Egatewidth = fgatewidth;}
        void SetEnergiesGe(double fE1, double fgatewidth){ge_E1 = fE1; ge_Egatewidth = fgatewidth;}

        virtual ~FatimaTimingAnalysisSummedGeGated();

        virtual void SetParContainers();

        void SetBinning_dT(int fNbins, double flowBin, double fhighBin){Nbins = fNbins; lowBin = flowBin; highBin = fhighBin;};

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

        /*
        double SoftwareTimewalk(double energy){
            //in energy in keV, out software walk:
            double a = 2223.77;
            double b = 1423.68;
            double c = -1.23853;
            return a/(energy+b) + c;
        };
        */



        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        const TFatimaTwinpeaksConfiguration * fatima_configuration;
        const TGermaniumConfiguration * germanium_configuration;
        TClonesArray* fHitFatima;
        TClonesArray* fHitGe;



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

        double ge_E1;
        double ge_Egatewidth;

        TH1F * h_energy_E1_E2_dt;
        TH2F * h_energy_E1_dt_vs_E;

        

        int ffast_tot_nbins = 500;
        float ffast_tot_bin_low = 0;
        float ffast_tot_bin_high = 2500; 
        int fslow_tot_nbins = 500;
        float fslow_tot_bin_low = 0;
        float fslow_tot_bin_high = 2500;
        int fenergy_nbins = 500;
        float fenergy_bin_low = 0;
        float fenergy_bin_high = 1500;



        // Folder and files
        TFolder * histograms;
        TDirectory* dir_fatima;


    public:
        ClassDef(FatimaTimingAnalysisSummedGeGated, 1)
};

#endif
