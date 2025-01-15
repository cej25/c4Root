#ifndef AidaPulserWalkthrough_H
#define AidaPulserWalkthrough_H

// FairRoot
#include "FairTask.h"

// c4
#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"

// ROOT
#include "TDirectory.h"
#include "TFolder.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TClonesArray.h"
#include <array>
#include <deque>
#include <map>
#include <vector>

class EventHeader;

class TClonesArray;
class TDirectory;
class TFolder;
class TGraph;
class TCanvas;
class TH1F;
class TH2F;

struct AidaPulserParameters
{
    // These parameters go to TSpectrum::SearchHighRes
    double Sigma;
    double Threshold;
    bool RemoveBG;
    double Deconv;
    bool Markov;
    double Average;
};

class AidaPulserWalkthrough : public FairTask
{
    public:
        AidaPulserWalkthrough();
        AidaPulserWalkthrough(const TString& name, Int_t verbose = 1);

        virtual ~AidaPulserWalkthrough();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        void SetParameters(AidaPulserParameters p) { params = p; }
        void FindOffsets();

        // HTTP Commands

        // range setters


    private:
        // Data from AIDA Classes
        std::vector<AidaUnpackAdcItem> const* adcArray;
        std::vector<AidaUnpackFlowItem> const* flowArray;
        std::vector<AidaUnpackScalerItem> const* scalerArray;
        std::vector<AidaCalAdcItem> const* implantCalArray;
        std::vector<AidaCalAdcItem> const* decayCalArray;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;

        // AIDA Config
        TAidaConfiguration const* conf;

        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        // Folders and Files
        TFile* histos;

        // Histograms
        // Implant Histograms
        std::vector<TH1F*> h_aida_adc;

        // Algorithm stuff
        AidaPulserParameters params;



    public:
        ClassDef(AidaPulserWalkthrough, 1)
};

#endif
