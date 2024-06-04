#ifndef BB7OnlineSpectra_H
#define BB7OnlineSpectra_H

#include "FairTask.h"

#include "EventHeader.h"
#include "BB7VmeCalData.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TH1.h"
#include <vector>

class TH1D;
class TH1F;
class TH1I;
class TH1;
class TFolder;
class TDirectory;
class BB7VmeImplantItem;
class BB7VmeDecayItem;

class BB7OnlineSpectra : public FairTask
{
    public:
        BB7OnlineSpectra();
        
        virtual ~BB7OnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

    private:

        std::vector<BB7VmeImplantItem> const* implantArray;
        std::vector<BB7VmeDecayItem> const* decayArray;

        TClonesArray* fHitBB7;
        EventHeader* header;

        // folders
        TFolder* histograms;
        TDirectory* dir_bb7;
        TDirectory* dir_raw_e;
        TDirectory* dir_stats;
        TDirectory* dir_rates;
        TDirectory* dir_implants;
        TDirectory* dir_implant_raw_e;
        TDirectory* dir_implant_stats;
        TDirectory* dir_implant_rates;
        TDirectory* dir_decays;
        TDirectory* dir_decay_raw_e;
        TDirectory* dir_decay_stats;
        TDirectory* dir_decay_rates;

        // canvases
        TCanvas* c_raw_e; // per side?
        TCanvas* c_hitpatterns;


        // histograms
        TH1* h1_bb7_RawE[2][32]; // 64 strips? use config later
        TH1* h1_bb7_hitpattern[2];
        TH1*** h1_implant_RawE;
        TH1*** h1_decay_RawE;
        TH1** h1_implant_hitpattern;
        TH1** h1_decay_hitpattern;
        TH1*** h1_implant_rates;
        TH1*** h1_decay_rates;

        int64_t saved_bb7_wr = 0;
        int rate_running_count = 0;
        int** implant_counters;
        int** decay_counters;
        float** implant_rates;
        float** decay_rates;

    public:
        ClassDef(BB7OnlineSpectra, 1)


};


#endif