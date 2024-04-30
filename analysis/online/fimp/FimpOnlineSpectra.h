#ifndef FimpOnlineSpectra_H
#define FimpOnlineSpectra_H

#include "FairTask.h"
#include "TFimpConfiguration.h"
#include "FimpData.h"
#include "FimpCalData.h"
#include <vector>
#include <memory>
#include "TDirectory.h"
#include "TFolder.h"

class FimpCalItem;
class TFimpConfiguration;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TFolder;
class TDirectory;


class FimpOnlineSpectra : public FairTask
{
    public:
        FimpOnlineSpectra();
        FimpOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FimpOnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();
    
    private:
        TFimpConfiguration const* fimp_config;

        std::vector<FimpCalItem> const* fimpCalArray;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_fimp;
        TDirectory* dir_stats;
        
    public:
        ClassDef(FimpOnlineSpectra, 1)
};

#endif
