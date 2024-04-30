#ifndef bPlastNearlineSpectra_H
#define bPlastNearlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TbPlastConfiguration.h"
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
        std::map<std::pair<int, int>, std::pair<int, std::pair<char, char>>> bplast_map;

        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        int nDetectors;
        int nTamexBoards;

        //Folders and files
        TDirectory* dir_bplast;
        TDirectory* dir_bplast_slowToT;
        TDirectory* dir_bplast_fastToT;
        TDirectory* dir_bplast_hitpattern;
        TDirectory* dir_bplast_fast_vs_slow;
        TDirectory* dir_bplast_time_spectra;

        // Histograms
        std::vector<TH1F*> h1_bplast_slowToT;
        std::vector<TH1F*> h1_bplast_fastToT;
        std::vector<TH1F*> h1_bplast_hitpatterns;
        std::vector<TH1F*> h1_bplast_tamex_card_hitpattern;

        std::vector<TH2F*> h2_bplast_fastToT_vs_slowToT;
        std::vector<TH1F*> h1_bplast_time_spectra;

        // Scaler spectra TBA

        // Detector Multiplicity
        TH1F* h1_bplast_multiplicity;

        int event_multiplicity;

    public:
        ClassDef(bPlastNearlineSpectra, 1)
};

#endif
