#ifndef GermaniumLabTest_H
#define GermaniumLabTest_H

#include "FairTask.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TText.h"
#include <vector>
#include <chrono>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;
class TH1;

class GermaniumLabTest : public FairTask
{
    public:
        GermaniumLabTest();
        GermaniumLabTest(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~GermaniumLabTest();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        int GetVectorIndex(int, int);

        void AddNewMeasurement(int, int, int, int, int, int, int);

        TF1 * MakeFitFunc(TString, int);
        double GetFWxM(TF1 *, double, double, double);
        double GetFWxMHistogram(TH1 * histo, TF1 * fitgaus, double ylim, double xrangemin, double xrangemax);
        void FitPeak(int);

        virtual void ResetAllHisto();
        virtual void ResetOneHisto(int vector_index);

        void SetFitLimits1173(int vector_index, int xlow, int xhigh);
        void SetFitLimits1332(int vector_index, int xlow, int xhigh);


        void StartMeasurement(int vector_index);
        void PauseMeasurement(int vector_index);
        void StopMeasurementCompleted(int vector_index);
        void WriteTestResults(int vector_index);
        void SetLog(int vector_index);
        void SetTraceLengthPlot(int v){trace_length_plot = v;}


    
    private:
        TClonesArray* fHitGeUncal;

        std::string base_path_str = "/u/jlarsson/Documents/DEGAStest/database";

        // ranges
        int number_of_boards = 4;
        int number_of_channels_per_board = 16;
        int number_of_channels = number_of_boards * number_of_channels_per_board;
        int number_of_detectors = number_of_channels;

        //per detector:
        std::vector<int> active_channels_indexes;
        std::vector<int> eb_crystal_id;
        std::vector<int> voltages;
        std::vector<int> degas_detector_id;
        std::vector<char> degas_detector_channel; //a,b,c
        std::vector<int> board_ids;
        std::vector<int> ch_ids;

        std::vector<int> fit_low_limit_1173;
        std::vector<int> fit_high_limit_1173;
        std::vector<int> fit_low_limit_1332;
        std::vector<int> fit_high_limit_1332;

        std::vector<TF1*> fitfunc_1173;
        std::vector<TF1*> fitfunc_1332;

        std::vector<double> gain_coeff;
        std::vector<double> offset_coeff;

        std::vector<std::chrono::time_point<std::chrono::steady_clock>> timers;
        std::vector<bool> test_running;
        std::vector<bool> test_paused;
        std::vector<bool> test_finished;


        std::chrono::time_point<std::chrono::steady_clock> last_trace_plotted;
        
        
        
        int fenergy_nbins = 3000;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        int funcal_nbins = 2e4;
        int funcal_bin_low = 0;
        int funcal_bin_high = 2e6;

        int trace_length_plot = 2000; //unit 10 ns

        EventHeader* header;
        Int_t fNEvents;


        // Canvas
        TCanvas ** c_germanium_time;
        TH1F ** h1_germanium_time;
        
        TCanvas ** c_germanium_uncal;
        TCanvas * c_germanium_raw_all;
        TCanvas * c_germanium_trace;
        TCanvas ** c_germanium_uncal_1173;
        TCanvas ** c_germanium_uncal_1332;
        
        TText ** tp_measurement;

        TH1F ** h1_germanium_uncal;
        TH1F ** h1_germanium_trace;
        TH1F ** h1_germanium_raw;
        TH1F ** h1_germanium_uncal_1173;
        TH1F ** h1_germanium_uncal_1332;

        TCanvas ** c_germanium_rates;
        TH1F ** h1_germanium_rates;


        TString fit_function = "gaus"; // "gaus with tail, crystal ball etc"

        float measurements_duration = 600; //s


        // Folder and files
        TFolder* histograms;
        TDirectory* dir_germanium;


        TCanvas ** c_germanium_energy;
        TH1F ** h1_germanium_energy;




    public:
        ClassDef(GermaniumLabTest, 1)
};

#endif