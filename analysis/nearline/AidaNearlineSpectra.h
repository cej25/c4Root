#ifndef AidaNearlineSpectra_H
#define AidaNearlineSpectra_H

#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "FairTask.h"
#include <array>
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TFolder;
class TH1F;
class TH2F;

class AidaNearlineSpectra : public FairTask
{
    public:
        AidaNearlineSpectra();
        AidaNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~AidaNearlineSpectra();

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
        std::vector<AidaCalAdcItem> const* implantCalArray;
        std::vector<AidaCalAdcItem> const* decayCalArray;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;

        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        //TCanvas* cSumTime; // channel 1 out of 28 for now?
        //TCanvas* cEnergySpectraTest;
        
        // Folders
        TFolder* aidaFolder;
        TFolder* implantFolder;
        TFolder* stoppedImplantFolder;
        TFolder* decayFolder;
        std::vector<TFolder*> implantDssdFolder;
        std::vector<TFolder*> stoppedImplantDssdFolder;
        std::vector<TFolder*> decayDssdFolder;

        // Histograms
        //TH1F* fh1_SumTime;
        //TH1F* fh1_EnergySpectraTest;
        //std::vector<std::array<std::array<TH1F*, 2>, 64>> fhAdcs;
        std::vector<TH2F*> h2_implant_strip_xy;
        std::vector<TH2F*> h2_implant_pos_xy;
        std::vector<TH1F*> h1_implant_e;
        std::vector<TH2F*> h2_implant_e_xy;
        std::vector<TH2F*> h2_implant_strip_1d_energy;
        std::vector<TH2F*> h2_implant_strip_1d;
        std::vector<TH2F*> h2_implant_x_ex;
        std::vector<TH2F*> h2_implant_y_ey;
        std::vector<TH2F*> h2_implant_strip_xy_stopped;

    public:
        ClassDef(AidaNearlineSpectra, 1)
};

#endif
