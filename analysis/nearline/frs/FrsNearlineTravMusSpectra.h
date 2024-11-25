#ifndef FrsNearlineTravMusSpectra_H
#define FrsNearlineTravMusSpectra_H 1

#include "TFrsConfiguration.h"
#include "FrsTravMusCalData.h"
#include "TExperimentConfiguration.h"

#include "FairTask.h"
#include "TH1.h"
#include "TDirectory.h"
#include <vector>

class TExperimentConfiguration;
class EventHeader;
class TFolder;
class TDirectory;
class TCanvas;
class FrsTravMusCalItem;
class TH1I;
class TH2I;
class TH1D;
class TH2D;
class TH1F;
class TH2F;
class TH2;

class FrsNearlineTravMusSpectra : public FairTask
{
    public:
        FrsNearlineTravMusSpectra();

        FrsNearlineTravMusSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsNearlineTravMusSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

    private:
        TFrsConfiguration const* frs_config;
        TExperimentConfiguration const* exp_config;

        std::vector<FrsTravMusCalItem> const* travMusicArray;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_travmus;
        TDirectory* dir_raw_adc;
        TDirectory* dir_raw_adc_drift;

        // Canvas
        TCanvas* c_raw_adc;
        TCanvas* c_raw_adc_drift;

        // Histograms
        TH1I* h1_travmus_raw_adc[8];
        TH2* h2_travmus_raw_adc_drift[8];

    public:
        ClassDef(FrsNearlineTravMusSpectra, 1)

};

#endif