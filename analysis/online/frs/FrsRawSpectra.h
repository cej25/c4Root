#ifndef FrsRawSpectra_H
#define FrsRawSpectra_H

#include "FairTask.h"
#include "TH1.h"
#include "TH2.h"

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

        TClonesArray* fFrsUserArray; // array with hit items
        TClonesArray* fFrsMainArray; // array with hit items
        TClonesArray* fFrsTPCArray; // array with hit items
        TClonesArray* fFrsVFTXArray; // array with hit items

        FrsUserData* fHitFrsUser; // array with hit items
        FrsMainData* fHitFrsMain; // array with hit items
        FrsTPCData* fHitFrsTPC; // array with hit items
        FrsVFTXData* fHitFrsVFTX; // array with hit items

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
        TH2F* h2_v1290_data_vs_chan;
        TH1F* h1_v7x5_tpc_data12[32];
        TH2F* h2_v7x5_tpc_data12_vs_chan;
        TH1F* h1_v7x5_tpc_data13[32];
        TH2F* h2_v7x5_tpc_data13_vs_chan;
        TH1F* h1_v1190_tpc_data[32];
        TH2F* h2_v1190_tpc_data_vs_chan;
        TH2F* h2_v1190_tpc_data_vs_chan_1st_hit;
        TH1F* h1_v7x5_user_data10[32];
        TH2F* h2_v7x5_user_data10_vs_chan;
        TH1F* h1_v7x5_user_data12[32];
        TH2F* h2_v7x5_user_data12_vs_chan;
        TH1I* h1_vftx_vftx_lead_mult[32];
        TH1I* h1_vftx_vftx_trail_mult[32];
        TH1I* h1_vftx_vftx_lead_cc[32];
        TH1I* h1_vftx_vftx_lead_ft[32];
        TH1I* h1_vftx_vftx_lead_time[32];
        TH1I* h1_vftx_vftx_trail_cc[32];
        TH1I* h1_vftx_vftx_trail_ft[32];
        TH1I* h1_vftx_vftx_lead_time_ref_ch0[32];
        TH2I* h2_vftx_vftx_lead_time_ref_ch0_vs_event[32];
        TH2I* h2_vftx_vftx_lead_time_ref_ch8_vs_event[32];
        TH2I* h2_vftx_vftx_lead_time_ch0vs4;
        


        // canvases


}


#endif