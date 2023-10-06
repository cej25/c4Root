#ifndef AidaOnlineSpectra_H
#define AidaOnlineSpectra_H

#include "AidaData.h"
#include "FairTask.h"
#include <array>
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class AidaOnlineSpectra : public FairTask
{
    public:
        AidaOnlineSpectra();
        AidaOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~AidaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        std::vector<AidaUnpackAdcItem> const* adcArray;
        std::vector<AidaUnpackFlowItem> const* flowArray;
        std::vector<AidaUnpackScalerItem> const* scalerArray;

        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        //TCanvas* cSumTime; // channel 1 out of 28 for now?
        //TCanvas* cEnergySpectraTest;

        // Histograms
        //TH1F* fh1_SumTime;
        //TH1F* fh1_EnergySpectraTest;
        std::vector<std::array<std::array<TH1F*, 2>, 64>> fhAdcs;

    public:
        ClassDef(AidaOnlineSpectra, 1)
};

#endif
