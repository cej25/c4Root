#ifndef FatimaAidaSpectra_H
#define FatimaAidaSpectra_H

#include "FairTask.h"

#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FatimaAidaSpectra : public FairTask
{
    public:
        FatimaAidaSpectra();
        FatimaAidaSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~FatimaAidaSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;


        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        static const int NDetectors = 24; //change this

        bool veto_sci41;


        //histograms:
        TH1F * h1_fatima_time_differences_energy_SCI41_gated;
        TH1F * h1_fatima_energy_anticoincidence_SCI41;
        TH2F * h1_fatima_energy_decay_gated;
        TH2F * h1_fatima_energy_decay_gated_mult2;
        TH2F * h1_fatima_time_differences_energy_SCI41_dt;
        TH2F * h1_fatima_time_differences_SCI41_dt_detector;
        TH2F * h1_fatima_energy_decay_a_vary;
        
        TH1F * h1_implant_e;
        TH1F * h1_decay_e;
        
        


        



    public:
        ClassDef(FatimaAidaSpectra, 1)
};

#endif
