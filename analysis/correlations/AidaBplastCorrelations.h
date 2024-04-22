#ifndef AidaBplastCorrelations_H
#define AidaBplastCorrelations_H

#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "FairTask.h"
#include <array>
#include <vector>

class TClonesArray;
class EventHeader;
class EventData;
class TCanvas;
class TH1F;
class TH2F;

class AidaBplastCorrelations : public FairTask
{
    public:
        AidaBplastCorrelations();
        AidaBplastCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~AidaBplastCorrelations();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TClonesArray* fHitbPlastTwinpeaks;

        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;
        // ranges
        //Double_t

        EventHeader* fEventHeader;
        EventData* fEventData;
        Int_t fNEvents;

        // TDirectories
        TDirectory* dir_bplast;
        TDirectory* dir_slow_ToT;

        // Canvas -- we can think about adding lead and trail spectra for each channel/detector
        TCanvas* c_bplast_slowToT;
        TCanvas* c_bplast_fastToT;
        TCanvas* c_bplast_hitpatterns;
        TCanvas* c_bplast_fast_v_slow;

        TCanvas* c_bplast_time_spectra;
        TCanvas* c_bplast_rel_time_spectra;

        static const int NDetectors = 128;

        // Histograms ToT

        TH1F * h1_bplast_slowToT[NDetectors];
        TH1F * h1_bplast_fastToT[NDetectors];
        TH1F * h1_bplast_fast_hitpatterns;
        TH1F * h1_bplast_slow_hitpatterns;

        TH2F * h2_bplast_slowToT_vs_fastToT[NDetectors];

        //Time spectra
        TH1F * h1_bplast_abs_time[NDetectors];
        TH1F * h1_bplast_rel_time[NDetectors];



    public:
        ClassDef(AidaBplastCorrelations, 1)
};

#endif
