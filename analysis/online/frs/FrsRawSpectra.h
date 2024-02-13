#ifndef FrsRawSpectra_H
#define FrsRawSpectra_H

#include "FairTask.h"
#include "TH1.h"
#include "TH2.h"
#include "../../../config/frs_config.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsMainData;
class FrsUserData;
class FrsTPCData;
class FrsVFTXData;
class TFolder;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;


class FrsRawSpectra : public FairTask
{
    public:
        FrsRawSpectra();

        FrsRawSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsRawSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // ResetHisto

    private:

        TClonesArray* fFrsMainArray; // array with hit items
        TClonesArray* fFrsTPCArray; // array with hit items
        TClonesArray* fFrsUserArray; // array with hit items
        TClonesArray* fFrsVFTXArray; // array with hit items

        FrsMainData* fHitFrsMainRaw; // array with hit items
        FrsTPCData* fHitFrsTPCRaw; // array with hit items
        FrsUserData* fHitFrsUserRaw; // array with hit items
        FrsVFTXData* fHitFrsVFTXRaw; // array with hit items

        EventHeader* header;
        Int_t fNEvents;

        // folders
        TFolder* folder_frs_hists;
        TFolder* folder_frs_raw_hists;
        TFolder* folder_frs_raw_main_hists;
        TFolder* folder_frs_raw_tpc_hists;
        TFolder* folder_frs_raw_user_hists;
        TFolder* folder_frs_raw_vftx_hists;
        TFolder* folder_raw_v792_main_hists;
        TFolder* folder_raw_v1290_main_hists;
        TFolder* folder_raw_v7x5_tpc_hists;
        TFolder* folder_raw_v1190_tpc_hists;
        TFolder* folder_raw_v7x5_user_hists;
        TFolder* folder_raw_vftx_vftx_hists;

        // histograms
        TH1F* h1_v792_main_data[32];
        TH2F* h2_v792_main_data_vs_chan;
        TH1F* h1_v1290_main_mult[32]; 
        TH1F* h1_v1290_main_leads[32];
        TH2F* h2_v1290_main_data_vs_chan;
        TH1F* h1_v7x5_tpc_data12[32];
        TH2F* h2_v7x5_tpc_data12_vs_chan;
        TH1F* h1_v7x5_tpc_data8[32];
        TH2F* h2_v7x5_tpc_data8_vs_chan;
        TH1F* h1_v1190_tpc_data[128];
        TH2F* h2_v1190_tpc_data_vs_chan;
        TH2F* h2_v1190_tpc_data_vs_chan_1st_hit;
        TH1F* h1_v7x5_user_data10[32];
        TH2F* h2_v7x5_user_data10_vs_chan;
        TH1F* h1_v7x5_user_data12[32];
        TH2F* h2_v7x5_user_data12_vs_chan;
        TH1I* h1_vftx_vftx_lead_mult[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_trail_mult[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_lead_cc[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_lead_ft[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_lead_time[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_trail_cc[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_trail_ft[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_trail_time[VFTX_MAX_CHN];
        TH1I* h1_vftx_vftx_lead_time_ref_ch0[VFTX_MAX_CHN];
        TH2I* h2_vftx_vftx_lead_time_ref_ch0_vs_event[VFTX_MAX_CHN];
        TH2I* h2_vftx_vftx_lead_time_ref_ch8_vs_event[VFTX_MAX_CHN];
        TH2I* h2_vftx_vftx_lead_time_ch0vs4;


        // variables
        int v1290_mult[32] = {0};
    
    public:
        ClassDef(FrsRawSpectra, 1)

};

#endif