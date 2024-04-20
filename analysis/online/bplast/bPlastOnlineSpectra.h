#ifndef bPlastOnlineSpectra_H
#define bPlastOnlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TbPlastConfiguration.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class bPlastOnlineSpectra : public FairTask
{
    public:
        bPlastOnlineSpectra();
        bPlastOnlineSpectra(const TString& name, Int_t verbose = 1);
        
        virtual ~bPlastOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TClonesArray* fHitbPlastTwinpeaks;

        TbPlastConfiguration const* bplast_conf;
        std::map<std::pair<int, int>, std::pair<int, std::pair<char, char>>> bplast_map;

        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        int nDetectors;
        int nTamexBoards;

        TString screenshot_path = "/u/jbormans/screenshots/";

        // Canvases
        TCanvas* c_bplast_slowToT;
        TCanvas* c_bplast_fastToT;
        TCanvas* c_bplast_hitpatterns;
        TCanvas* c_bplast_tamex_card_hitpattern;
        TCanvas* c_bplast_fast_v_slow;
        TCanvas* c_bplast_time_spectra;
        TCanvas* c_bplast_multiplicity;
        TCanvas* c_bplast_channel_multiplicity;
        TCanvas* c_bplast_wr_time_diff;
        TCanvas* c_bplast_snapshot;

        //Folders and files
        TFolder* histograms;
        TDirectory* dir_bplast;
        TDirectory* dir_bplast_slowToT;
        TDirectory* dir_bplast_fastToT;
        TDirectory* dir_bplast_hitpattern;
        TDirectory* dir_bplast_fast_vs_slow;

        TFile* file_bplast_snapshot;

        // Histograms
        std::vector<TH1F*> h1_bplast_slowToT;
        std::vector<TH1F*> h1_bplast_fastToT;
        std::vector<TH1F*> h1_bplast_hitpatterns;
        std::vector<TH1F*> h1_bplast_tamex_card_hitpattern;

        std::vector<TH2F*> h2_bplast_fastToT_vs_slowToT;
        std::vector<TH1F*> h1_bplast_time_spectra;
        TH1F* h1_bplast_wr_time_diff;


        // Detector Multiplicity
        std::vector<TH1F*> h1_bplast_multiplicity;

        int event_multiplicity_upstream;
        int event_multiplicity_downstream;
        int wr_t;
        int wr_prev;

    public:
        ClassDef(bPlastOnlineSpectra, 1)
};

#endif
