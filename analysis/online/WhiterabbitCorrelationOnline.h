#ifndef FatimaOnlineSpectra_H
#define FatimaOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FatimaOnlineSpectra : public FairTask
{
    public:
        FatimaOnlineSpectra();
        FatimaOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~FatimaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitAida;


        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas

        
        // Histograms 
        



    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif
