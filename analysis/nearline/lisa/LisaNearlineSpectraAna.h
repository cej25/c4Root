#ifndef LisaNearlineSpectraAna_H
#define LisaNearlineSpectraAna_H

#include "FairTask.h"
#include "TLisaConfiguration.h"
#include "LisaData.h" // do we need raw?
#include "LisaAnaData.h"
#include <vector>
#include <memory>
#include "TDirectory.h"
#include "TFolder.h"
#include "TPad.h"
#include "TH2I.h"
#include "TGraph.h"
#include "TString.h"
#include "TExperimentConfiguration.h"


//Debugging. Replaced std::string with TString 8nov24



class LisaAnaItem;
class TLisaConfiguration;
class TExperimentConfiguration;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;
class TFolder;
class TDirectory;
class TH2;


class LisaNearlineSpectraAna : public FairTask
{
    public:
        LisaNearlineSpectraAna();
        LisaNearlineSpectraAna(const TString& name, Int_t verbose = 1);

        virtual ~LisaNearlineSpectraAna();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TLisaConfiguration const* lisa_config;
        TExperimentConfiguration const* exp_config;

        // TClonesArray* fHitLisa;

        std::vector<LisaAnaItem> const* lisaAnaArray;
        
        EventHeader* header;
        Int_t fNEvents;

        TDirectory* dir_lisa;
        TDirectory* dir_energy;
        TDirectory* dir_traces;
        TDirectory* dir_energy_MWD;
        TDirectory* dir_traces_MWD;


        int64_t prev_wr = 0;
        int64_t wr_diff;
    
        // ::: Histograms

        // energy
        std::vector<TH1F*> h1_energy;
        std::vector<TH1F*> h1_energy_MWD;
        std::vector<TH2F*> h2_traces;
        std::vector<TH2F*> h2_traces_MWD;


        // ::: Temporary mapping for histo displaying and filling
        //int ch_number = 16;
        int mapping[16];
        
        

    public:
        ClassDef(LisaNearlineSpectraAna, 1)
};

#endif