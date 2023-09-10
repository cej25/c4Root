#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FrsOnlineSpectra : public FairTask
{
    public:
        FrsOnlineSpectra();

        FrsOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        void SetRangeZ(Double_t min, Double_t max)
        {
            fMin_Z = min;
            fMax_Z = max;
        }

        void SetRangeAq(Double_t min, Double_t max)
        {
            fMin_AoQ = min;
            fMax_AoQ = max;
        }

        void SetRangeX4(Double_t min, Double_t max)
        {
            fMin_x4 = min;
            fMax_x4 = max;
        }

        void SetIsoGate(Double_t minz, Double_t maxz, Double_t minaq, Double_t maxaq)
        {
            fMin_Z_gate = minz;
            fMax_Z_gate = maxz;
            fMin_AoQ_gate = minaq;
            fMax_AoQ_gate = maxaq;
        }

    private:
        TClonesArray* fHitFrs; // array with hit items

        // Ranges for histograms
        Double_t fMin_Z, fMax_Z, fMin_AoQ, fMax_AoQ, fMin_x4, fMax_x4;
        Double_t fMin_Z_gate, fMax_Z_gate, fMin_AoQ_gate, fMax_AoQ_gate;

        // check for trigger should be done globally, somewhere else
        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* cZvsAoQ;
        TCanvas* cX4vsAoQ;
        TCanvas* cZvsAoQCorr;
        TCanvas* cX4vsAoQCorr;

        // Histograms for Hit data
        TH2F* fh2_ZvsAoQ;
        TH2F* fh2_x4vsAoQ;
        TH2F* fh2_ZvsAoQCorr;
        TH2F* fh2_x4vsAoQCorr;
    
    public:
        ClassDef(FrsOnlineSpectra, 1)

};

#endif