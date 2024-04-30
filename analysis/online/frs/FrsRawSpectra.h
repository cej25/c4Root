#ifndef FrsRawSpectra_H
#define FrsRawSpectra_H

#include "FairTask.h"
#include "FrsMainData.h"
#include "FrsTPCData.h"
#include "FrsUserData.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include "../../../config/setup.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsMainData;
class FrsUserData;
class FrsTPCData;
class FrsVFTXData;
class TFolder;
class TDirectory;
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

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // ResetHisto

    private:

        std::vector<FrsMainV792Item> const* v792arrayMain;
        std::vector<FrsMainV1290Item> const* v1290arrayMain;
        std::vector<FrsTPCV7X5Item> const* v7x5arrayTPC;
        std::vector<FrsTPCV1190Item> const* v1190arrayTPC;
        std::vector<FrsUserV7X5Item> const* v7x5arrayUser;


        EventHeader* header;
        Int_t fNEvents;

        // folders
        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_frs_raw;
        TDirectory* dir_frs_raw_main;
        TDirectory* dir_frs_raw_tpc;
        TDirectory* dir_frs_raw_user;
        //TDirectory* dir_frs_raw_vftx;
        TDirectory* dir_raw_v792_main;
        TDirectory* dir_raw_v1290_main;
        TDirectory* dir_raw_v7x5_tpc;
        TDirectory* dir_raw_v1190_tpc;
        TDirectory* dir_raw_v7x5_user;
        //TDirectory* dir_raw_vftx_vftx;

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

        // Canvases
        TCanvas* c_v792_main;
        TCanvas* c_v1290_main_mult;
        TCanvas* c_v1290_main_leads;
        TCanvas* c_v7x5_tpc_geo12;
        TCanvas* c_v7x5_tpc_geo8;
        TCanvas* c_v1190_tpc;
        TCanvas* c_v7x5_user_geo10;
        TCanvas* c_v7x5_user_geo12;
        /*TCanvas* c_vftx_lead_mult;
        TCanvas* c_vftx_trail_mult;
        TCanvas* c_vftx_lead_cc;
        TCanvas* c_vftx_lead_ft;
        TCanvas* c_vftx_lead_time;
        TCanvas* c_vftx_trail_cc;
        TCanvas* c_vftx_trail_ft;
        TCanvas* c_vftx_trail_time;
        TCanvas* c_vftx_lead_refch0;
        TCanvas* c_vftx_lead_refch0_vs_event;
        TCanvas* c_vftx_lead_refch8_vs_event;*/

        // variables
        int v1290_mult[32] = {0};
    
    public:
        ClassDef(FrsRawSpectra, 1)

};

#endif