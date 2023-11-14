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


        void CreateHistograms();

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
        TCanvas* cEnergySpectra;
        TCanvas* cCalEnergySpectra;

        // Histograms energy
        TH1F * h1_energy[100];
        TH1F * h1_energy_mult2[100];

        //Histograms time
        TH1F * h1_time[100];

        const int NCrystals = 7; //needs to be changed.
        const int NDetectors = 2; //needs to be changed.


    public:
        ClassDef(GermaniumOnlineSpectra, 1)
};

#endif