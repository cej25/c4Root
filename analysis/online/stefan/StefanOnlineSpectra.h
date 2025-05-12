#ifndef StefanOnlineSpectra_H
#define StefanOnlineSpectra_H

// FairRoot
#include "FairTask.h"

// c4
#include "StefanHitData.h"
#include "TStefanConfiguration.h"

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
class StefanHitItem;
class TStefanConfiguration;

class StefanOnlineSpectra : public FairTask
{
    public:
        StefanOnlineSpectra();
        StefanOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~StefanOnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // HTTP Commands
        virtual void Reset_Histo();

        // range setters


    private:

        TStefanConfiguration const* stefan_config;

        std::vector<StefanHitItem> const* StefanHit; 
        
        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        int nDets = 0;

        // Folders and Files
        TFolder* histograms;
        TDirectory* dir_stefan;
        TDirectory** dir_dssd;
        TDirectory** dir_hits;
        std::vector<std::vector<TDirectory*>> dir_raw;
        std::vector<TDirectory*> dir_pixel;
	
	
        TDirectory** dir_stats;
        
        
	
	
	
        std::vector<TH2*> h2_hit_strip_xy; // Hit pattern
        std::vector< std::vector<std::vector<TH1*>>> h1_raw_energy; // raw energy spectra
        std::vector< std::vector<TH1*>> h1_pixel_energy; // energy per pixel spectra



        // Counters
        std::set<int>** implant_strips_fired;
        int** implant_side_x_mult;
        int** implant_side_y_mult;
        std::set<int>** decay_strips_fired;
        int** decay_side_x_mult;
        int** decay_side_y_mult;


    public:
        ClassDef(StefanOnlineSpectra, 1)
};

#endif
