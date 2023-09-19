#ifndef GermaniumOnlineSpectra_H
#define GermaniumOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class GermaniumOnlineSpectra : public FairTask
{
    public:
        GermaniumOnlineSpectra();
        GermaniumOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~GermaniumOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TClonesArray* fHitGe;

        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* cSumTime; // channel 1 out of 28 for now?
        TCanvas* cEnergySpectraTest;

        // Histograms
        TH1F* fh1_SumTime;
        TH1F* fh1_EnergySpectraTest;

    public:
        ClassDef(GermaniumOnlineSpectra, 1)
};

#endif