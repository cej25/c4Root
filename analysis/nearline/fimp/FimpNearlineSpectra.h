#ifndef FimpNearlineSpectra_H
#define FimpNearlineSpectra_H

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


class FimpNearlineSpectra : public FairTask
{
    public:
        FimpNearlineSpectra();
        FimpNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FimpNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();
    
    private:
        TFimpConfiguration const* fimp_config;

        std::vector<FimpCalItem> const* fimpCalArray;

        EventHeader* header;
        Int_t fNEvents;

        TDirectory* dir_fimp;
        TDirectory* dir_stats;
        
    public:
        ClassDef(FimpNearlineSpectra, 1)
};

#endif
