#ifndef BB7FebexOnlineSpectra_H
#define BB7FebexOnlineSpectra_H

// FairRoot
#include "FairTask.h"

// c4
#include "BB7FebexCalData.h"
#include "BB7FebexHitData.h"
#include "TBB7FebexConfiguration.h"

// ROOT
#include "TDirectory.h"
#include "TFolder.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TClonesArray.h"
#include <array>
#include <deque>
#include <map>
#include <vector>

class EventHeader;

class TClonesArray;
class TDirectory;
class TFolder;
class TGraph;
class TCanvas;
class TH1F;
class TH2F;

class BB7FebexOnlineSpectra : public FairTask
{
    public:
        BB7FebexOnlineSpectra();
        BB7FebexOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~BB7FebexOnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // HTTP Commands
        virtual void Reset_Histo();

        // range setters


    private:
        std::vector<BB7FebexCalItem> const* bb7calImplants;
        std::vector<BB7FebexCalItem> const* bb7calDecays;
        std::vector<BB7FebexHitItem> const* implantHitArray;
        std::vector<BB7FebexHitItem> const* decayHitArray;

        // AIDA Config
        TBB7FebexConfiguration const* bb7_config;

        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        int nDets = 0;

        // Folders and Files
        TFolder* histograms;
        TDirectory* dir_bb7;
        std::vector<TDirectory*> dir_dssd;
        std::vector<TDirectory*> dir_stats;
        std::vector<TDirectory*> dir_implants;
        std::vector<TDirectory*> dir_decays;

        // Histograms
        std::vector<TH1*> h1_implant_side_x_mult;
        std::vector<TH1*> h1_implant_side_y_mult;
        std::vector<TH2*> h2_implant_strip_mult; 
        std::vector<TH1*> h1_implant_side_x_hitpattern;
        std::vector<TH1*> h1_implant_side_y_hitpattern;
        std::vector<TH2*> h2_implant_strip_xy;
        std::vector<TH1*> h1_implant_e;
        std::vector<TH2*> h2_implant_e_xy;
        std::vector<TH2*> h2_implant_strip_1d_e;

        std::vector<TH1*> h1_decay_side_x_mult;
        std::vector<TH1*> h1_decay_side_y_mult;
        std::vector<TH2*> h2_decay_strip_mult; 
        std::vector<TH1*> h1_decay_side_x_hitpattern;
        std::vector<TH1*> h1_decay_side_y_hitpattern;
        std::vector<TH2*> h2_decay_strip_xy;
        std::vector<TH1*> h1_decay_e;
        std::vector<TH2*> h2_decay_e_xy;
        std::vector<TH2*> h2_decay_strip_1d_e; 

        // Counters
        std::set<int>** implant_strips_fired;
        int** implant_side_x_mult;
        int** implant_side_y_mult;
        std::set<int>** decay_strips_fired;
        int** decay_side_x_mult;
        int** decay_side_y_mult;

        // std::vector<std::set<int>> implant_strips_fired[2];
        // std::vector<int> implant_side_x_mult[32];
        // std::vector<int> implant_side_y_mult[32];
        // std::vector<std::set<int>> decay_strips_fired[2];
        // std::vector<int> decay_side_x_mult[32];
        // std::vector<int> decay_side_y_mult[32];

    public:
        ClassDef(BB7FebexOnlineSpectra, 1)
};

#endif
