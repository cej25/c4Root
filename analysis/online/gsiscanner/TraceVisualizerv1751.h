#ifndef TraceVisualizerv1751_H
#define TraceVisualizerv1751_H

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

class TraceVisualizerv1751 : public FairTask
{
    public:
        TraceVisualizerv1751();
        TraceVisualizerv1751(const TString& name, Int_t verbose = 1);

        virtual ~TraceVisualizerv1751();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();
        virtual void ResetAllHistos();

        virtual void SetTraceLength(int v){trace_length_plot = v;}
        virtual void SetPlotFrequency(int v){plot_every_ntrace = v;}
        


    private:
        TClonesArray* fHitUncal;


        // ranges
        int number_of_boards = 1;
        int number_of_channels_per_board = 8;
        int number_of_channels = number_of_boards * number_of_channels_per_board;
        
        
        int funcal_nbins = 2e4;
        int funcal_bin_low = 0;
        int funcal_bin_high = 2e6;

        int trace_length_plot = 1000; //unit 1 ns
        int plot_every_ntrace = 300;
        int skip_counter = 0;

        EventHeader* header;
        Int_t fNEvents;

        
        // Folder and files
        TFolder* histograms;
        TDirectory* dir_v1751;
        TDirectory** dir_v1751_board;


        TCanvas ** c_energy_board;
        TCanvas *** c_energy;
        TH1F *** h1_energy;
    
        TCanvas ** c_trace_board;
        TCanvas *** c_trace;
        TH1F *** h1_trace;




    public:
        ClassDef(TraceVisualizerv1751, 1)
};

#endif