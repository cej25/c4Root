#ifndef bPlastNearlineSpectra_H
#define bPlastNearlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TbPlastConfiguration.h"
#include "TExperimentConfiguration.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class bPlastNearlineSpectra : public FairTask
{
    public:
        bPlastNearlineSpectra();
        bPlastNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~bPlastNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();
    
    private:
        TClonesArray* fHitbPlastTwinpeaks;

        TbPlastConfiguration const* bplast_conf;
        TExperimentConfiguration const * exp_conf;
        
        std::map<std::pair<int, int>, std::pair<int, std::pair<char, char>>> bplast_map;

        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        int nDetectors;
        int nTamexBoards;
        // int time_duration = 24;

        //Folders and files
        TDirectory* dir_bplast;
        TDirectory* dir_bplast_slowToT;
        TDirectory* dir_bplast_fastToT;
        TDirectory* dir_bplast_hitpattern;
        TDirectory* dir_bplast_fast_vs_slow;
        TDirectory* dir_bplast_time_spectra;
        TDirectory* dir_bplast_rates;

        // Histograms
        std::vector<TH1*> h1_bplast_slowToT;
        std::vector<TH1*> h1_bplast_fastToT;
        std::vector<TH1*> h1_bplast_hitpatterns;
        std::vector<TH1*> h1_bplast_tamex_card_hitpattern;

        std::vector<TH2*> h2_bplast_fastToT_vs_slowToT;
        std::vector<TH1*> h1_bplast_time_spectra;
        std::vector<TH1*> h1_bplast_rates;

        // Scaler spectra TBA

        // Detector Multiplicity
        TH1* h1_bplast_multiplicity;

        int event_multiplicity;
        int64_t wr_t = 0;
        int64_t wr_prev = 0;
        int64_t wr_prev1s = 0;
        int* detector_counters;
        int* detector_rates;
        int rate_running_count = 0;

    public:
        ClassDef(bPlastNearlineSpectra, 1)
};

#endif
