#ifndef BB7OnlineSpectra_H
#define BB7OnlineSpectra_H

#include "FairTask.h"

#include "EventHeader.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TH1.h"
#include <vector>

class TH1D;
class TH1F;
class TH1I;

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

        TClonesArray* fHitBB7;
        EventHeader* header;

        // folders
        // TFolder* folder_bb7_hists;
        // TFolder* folder_raw_e;
        // TFolder* folder_stats;
        TFolder* histograms;
        TDirectory* dir_bb7;
        TDirectory* dir_raw_e;
        TDirectory* dir_stats;

        // canvases
        TCanvas* c_raw_e; // per side?
        TCanvas* c_hitpatterns;


        // histograms
        TH1D* h1_bb7_RawE[2][32]; // 64 strips? use config later
        TH1I* h1_bb7_hitpattern[2];

    public:
        ClassDef(BB7OnlineSpectra, 1)


};


#endif