#ifndef TravMusNearlineSpectra_H
#define TravMusNearlineSpectra_H 1

#include "TFrsConfiguration.h"
#include "TravMusCalData.h"
#include "TravMusAnaData.h"

#include "FairTask.h"
#include "TH1.h"
#include "TDirectory.h"
#include <vector>

class EventHeader;
class TFolder;
class TDirectory;
class TCanvas;
class TravMusCalItem;
class TH1F;
class TH2F;
class TH1D;
class TH1I;
class TH2D;
class TH2I;

class TravMusNearlineSpectra : public FairTask
{
    public:
        TravMusNearlineSpectra();

        TravMusNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~TravMusNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

    private:
        TFrsConfiguration const* frs_config;

        std::vector<TravMusCalItem> const* travMusCalArray;
        std::vector<TravMusAnaItem> const* travMusAnaArray;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_travmus;
        // TDirectory* dir_travmus_tac;
        // TDirectory* dir_travmus_mhtdc;
        TDirectory* dir_raw_adc;

        // Canvas
        TCanvas* c_raw_adc;

        // Histograms
        TH1I* h1_travmus_raw_adc[8];
        TH2* h2_travmus_vs_Z;

        TH1* h1_Z_travmus;
        TH1* h1_travmus_dE;

        TH2* h2_travmus_vs_Z_mhtdc;

        TH1* h1_z_travmus_mhtdc;

    public:
        ClassDef(TravMusNearlineSpectra, 1)

};

#endif