#ifndef FimpOnlineSpectra_H
#define FimpOnlineSpectra_H

#include "FairTask.h"
#include "TFimpConfiguration.h"
#include "FimpData.h"
#include "FimpCalData.h"
#include <map>
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
class TH1D;
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

        std::vector<FimpItem> const* fimpRawArray;
        std::vector<FimpCalItem> const* fimpCalArray;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_fimp;
        TDirectory* dir_stats;
        TDirectory* dir_tot;
        TDirectory* dir_leads;
        TDirectory* dir_trails;
        TDirectory* dir_time_lead;
        TDirectory* dir_coarse_clock_lead;
        TDirectory* dir_fine_lead;
        TDirectory* dir_time_trail;
        TDirectory* dir_coarse_clock_trail;
        TDirectory* dir_fine_trail;
        TDirectory* dir_sc41;

        TH1* h1_fimp_whiterabbit;
        TH1* h1_fimp_wr_dt;
        TH1* h1_fimp_multiplicity;
        TH1* h1_fimp_hitpattern;
        std::vector<TH1*> h1_fimp_tot;
        std::vector<TH1*> h1_fimp_lead_times;
        std::vector<TH1*> h1_fimp_trail_times;
        std::vector<TH1*> h1_fimp_sc41l_dT;
        std::vector<TH1*> h1_fimp_sc41r_dT;
        std::vector<TH1*> h1_fimp_coarse_clock_lead;
        std::vector<TH1*> h1_fimp_coarse_clock_trail;
        std::vector<TH1*> h1_fimp_fine_bin_lead;
        std::vector<TH1*> h1_fimp_fine_bin_trail;

        //int64_t wr_t = 0;
        int64_t prev_wr_t = 0;

        std::map<int, std::pair<std::pair<int, int>, std::string>> detector_mapping;
        
    public:
        ClassDef(FimpOnlineSpectra, 1)
};

#endif
