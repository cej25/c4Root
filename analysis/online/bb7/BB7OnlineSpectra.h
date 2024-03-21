#ifndef BB7OnlineSpectra_H
#define BB7OnlineSpectra_H

#include "FairTask.h"

#include "EventHeader.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include "TCanvas.h"
#include "TH1.h"
#include <vector>

class TH1D;
class TH1F;

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
        TFolder* folder_bb7_hists;
        TFolder* folder_raw_e;

        // canvases


        // histograms
        TH1D* h1_bb7_RawE[64]; // 64 strips? use config later

    public:
        ClassDef(BB7OnlineSpectra, 1)


};


#endif