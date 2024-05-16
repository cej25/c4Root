#ifndef FrsTravMusSpectra_H
#define FrsTravMusSpectra_H 1

#include "TFrsConfiguration.h"
#include "FrsTravMusCalData.h"

#include "FairTask.h"
#include "TH1.h"
#include "TDirectory.h"
#include <vector>

class EventHeader;
class TFolder;
class TDirectory;
class TCanvas;
class FrsTravMusCalItem;
class TH1F;
class TH2F;
class TH1D;
class TH1I;
class TH2D;
class TH2I;

class FrsTravMusSpectra : public FairTask
{
    public:
        FrsTravMusSpectra();

        FrsTravMusSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsTravMusSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

    private:
        TFrsConfiguration const* frs_config;

        std::vector<FrsTravMusCalItem> const* travMusicArray;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_travmus;
        TDirectory* dir_raw_adc;

        // Canvas
        TCanvas* c_raw_adc;

        // Histograms
        TH1I* h1_travmus_raw_adc[8];

    public:
        ClassDef(FrsTravMusSpectra, 1)

};

#endif