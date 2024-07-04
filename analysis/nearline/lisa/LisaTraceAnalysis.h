#ifndef LisaTraceAnalysis_H
#define LisaTraceAnalysis_H

#include "FairTask.h"
#include "TLisaConfiguration.h"
#include "LisaData.h" // do we need raw?
#include "LisaCalData.h"
#include <vector>
#include <memory>
#include "TDirectory.h"
#include "TFolder.h"
#include "TPad.h"
#include "TH2I.h"
#include "TGraph.h"


class LisaCalItem;
class TLisaConfiguration;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;
class TFolder;
class TDirectory;


class LisaTraceAnalysis : public FairTask
{
    public:
        LisaTraceAnalysis();
        LisaTraceAnalysis(const TString& name, Int_t verbose = 1);

        virtual ~LisaTraceAnalysis();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TLisaConfiguration const* lisa_config;
        // TClonesArray* fHitLisa;

        std::vector<LisaCalItem> const* lisaCalArray;

        // common variables
        int layer_number;
        int det_number;
        int xmax;
        int ymax;
        int num_layers;
        std::string city = "";
        

        EventHeader* header;
        Int_t fNEvents;

        TDirectory* dir_lisa;
        TDirectory* dir_crosstalk;
        std::vector<TCanvas*> c_energies;
        std::vector<TCanvas*> c_traces_cross;
        std::vector<TH2F*> h2_traces_hit;
        std::vector<TH1F*> h1_energies_hit;
        std::vector< std::vector<TH2F*> > h2_traces_nothit;
        Int_t layer;
        uint64_t wr_time;
 
        

    public:
        ClassDef(LisaTraceAnalysis, 1)
};

#endif
