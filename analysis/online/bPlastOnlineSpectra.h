#ifndef bPlastOnlineSpectra_H
#define bPlastOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

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

        // range setters

    
    private:
        TClonesArray* fHit_bPlast;

        EventHeader* header;
        
        Int_t fNEvent;

        // Canvas
        TCanvas* cLeadTime;

        // Histograms
        TH1F* fh1_LeadTime;

    public:
        ClassDef(bPlastOnlineSpectra, 1)
};

#endif