#ifndef LisaOnlineSpectra_H
#define LisaOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;

class LisaOnlineSpectra : public FairTask
{
    public:
        LisaOnlineSpectra();
        LisaOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~LisaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TClonesArray* fHitLisa;

        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        // TCanvas*

        // Histograms
        TH1I* h1_hitpattern;
        TH1F* h1_energy;
        TH2F* h2_traces;

    public:
        ClassDef(LisaOnlineSpectra, 1)
};

#endif
