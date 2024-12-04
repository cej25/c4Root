// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsTPCRaw2Cal.h"
#include "FrsTPCData.h"
#include "FrsTPCCalData.h"
#include "TFRSParameter.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsTPCRaw2Cal::FrsTPCRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   v1190array(nullptr)
    ,   v7x5array(nullptr)
    ,   adcArray(nullptr)
    ,   tpcCalArray(new std::vector<FrsTPCCalItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
}

FrsTPCRaw2Cal::FrsTPCRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   v1190array(nullptr)
    ,   v7x5array(nullptr)
    ,   adcArray(nullptr)
    ,   tpcCalArray(new std::vector<FrsTPCCalItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
}

FrsTPCRaw2Cal::~FrsTPCRaw2Cal()
{
    c4LOG(info, "Deleting FrsTPCRaw2Cal task");
}

void FrsTPCRaw2Cal::SetParameters()
{
    v1190_channel_dt[0][0] = 0; //TPC21-A11
    v1190_channel_dt[0][1] = 1; //TPC21-A12
    v1190_channel_dt[0][2] = 2; //TPC21-A21
    v1190_channel_dt[0][3] = 3; //TPC21-A22
    v1190_channel_lt[0][0] = 4; //TPC21-DL1
    v1190_channel_rt[0][0] = 5; //TPC21-DR1
    // 6, 7 empty
    v1190_channel_lt[0][1] = 8; //TPC21-DL2
    v1190_channel_rt[0][1] = 9; //TPC21-DR2
    v1190_channel_dt[1][0] = 10; //TPC22-A11
    v1190_channel_dt[1][1] = 11; //TPC22-A12
    v1190_channel_dt[1][2] = 12; //TPC22-A21
    v1190_channel_dt[1][3] = 13; //TPC22-A22
    // 14, 15 empty
    //17(top channel of 3rd module is dead)
    //18(skip)
    v1190_channel_lt[1][0] = 18; //TPC22-DL1
    v1190_channel_rt[1][0] = 19; //TPC22-DR1
    v1190_channel_lt[1][1] = 20; //TPC22-DL2
    v1190_channel_rt[1][1] = 21; //TPC22-DR2
    // 22,23 empty

    // ======= middle NIM crate (TPC23+24)=========
    v1190_channel_dt[2][0] = 24; //TPC23-A11
    v1190_channel_dt[2][1] = 25; //TPC23-A12
    v1190_channel_dt[2][2] = 26; //TPC23-A21
    v1190_channel_dt[2][3] = 27; //TPC23-A22
    v1190_channel_lt[2][0] = 28; //TPC23-DL1
    v1190_channel_rt[2][0] = 29; //TPC23-DR1
    //30,31 empty
    v1190_channel_lt[2][1] = 32; //TPC23-DL2
    v1190_channel_rt[2][1] = 33; //TPC23-DR2
    v1190_channel_dt[3][0] = 34; //TPC24-A11
    v1190_channel_dt[3][1] = 35; //TPC24-A12
    v1190_channel_dt[3][2] = 36; //TPC24-A21
    v1190_channel_dt[3][3] = 37; //TPC24-A22
    //38,39 empty
    v1190_channel_lt[3][0] = 40; //TPC24-DL1
    v1190_channel_rt[3][0] = 41; //TPC24-DR1
    v1190_channel_lt[3][1] = 42; //TPC24-DL2
    v1190_channel_rt[3][1] = 43; //TPC24-DR2
    //46,47 empty

    // ======= bottom NIM crate (TPC41+42+31)=========
    v1190_channel_dt[4][0] = 64; //TPC41-A11
    v1190_channel_dt[4][1] = 65; //TPC41-A12
    v1190_channel_dt[4][2] = 66; //TPC41-A21
    v1190_channel_dt[4][3] = 67; //TPC41-A22
    v1190_channel_lt[4][0] = 68; //TPC41-DL1
    v1190_channel_rt[4][0] = 69; //TPC41-DR1
    //70,71 empty
    v1190_channel_lt[4][1] = 72; //TPC41-DL2
    v1190_channel_rt[4][1] = 73; //TPC41-DR2
    v1190_channel_dt[5][0] = 74; //TPC42-A11
    v1190_channel_dt[5][1] = 75; //TPC42-A12
    v1190_channel_dt[5][2] = 76; //TPC42-A21
    v1190_channel_dt[5][3] = 77; //TPC42-A22
    //78,79 empty
    v1190_channel_lt[5][0] = 80; //TPC42-DL1
    v1190_channel_rt[5][0] = 81; //TPC42-DR1
    v1190_channel_lt[5][1] = 82; //TPC42-DL2
    v1190_channel_rt[5][1] = 83; //TPC42-DR2
    v1190_channel_dt[6][0] = 84; //TPC31-A11
    v1190_channel_dt[6][1] = 85; //TPC31-A12
    //86,87 empty
    v1190_channel_dt[6][2] = 88; //TPC31-A21
    v1190_channel_dt[6][3] = 89; //TPC31-A22
    v1190_channel_lt[6][0] = 90; //TPC31-DL1
    v1190_channel_rt[6][0] = 91; //TPC31-DR1
    v1190_channel_lt[6][1] = 92; //TPC31-DL2
    v1190_channel_rt[6][1] = 93; //TPC31-DR2
    //94,95 empty

    //time reference signal
    v1190_channel_timeref[0] = 96; //accept trig
    v1190_channel_timeref[1] = 97; //sc21
    v1190_channel_timeref[2] = 98; //sc22
    v1190_channel_timeref[3] = 99; //sc31
    v1190_channel_timeref[4] =100; //sc41
    v1190_channel_timeref[5] =101; //
    v1190_channel_timeref[6] =102; //
    v1190_channel_timeref[7] =103; //

    v1190_channel_calibgrid[0] = 104;//tpc21grid
    v1190_channel_calibgrid[1] = 105;//tpc22grid
    v1190_channel_calibgrid[2] = 106;//tpc23grid
    v1190_channel_calibgrid[3] = 107;//tpc24grid
    v1190_channel_calibgrid[4] = 108;//tpc41grid
    v1190_channel_calibgrid[5] = 109;//tpc42grid
    v1190_channel_calibgrid[6] = 110;//tpc31grid //to be checked maybe 111+1

}

InitStatus FrsTPCRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    v7x5array = mgr->InitObjectAs<decltype(v7x5array)>("FrsTPCV7X5Data");
    c4LOG_IF(fatal, !v7x5array, "Branch v7x5array not found!");
    v1190array = mgr->InitObjectAs<decltype(v1190array)>("FrsTPCV1190Data");
    c4LOG_IF(fatal, !v1190array, "Branch v1190array not found!");

    adcArray = mgr->InitObjectAs<decltype(adcArray)>("tpcAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch tpcAdcData not found!");
    tdcArray = mgr->InitObjectAs<decltype(tdcArray)>("tpcTdcData");
    C4LOG_IF(fatal, !tdcArray, "Branch tpcTdcData not found!");

    mgr->RegisterAny("FrsTPCCalData", tpcCalArray, !fOnline);
    tpcCalArray->clear();

    b_tpc_xy = new Bool_t[7];
    tpc_csum = new Int_t*[7];
    for (int i = 0; i < 7; i++) tpc_csum[i] = new Int_t[4];

    SetParameters();

    return kSUCCESS;
}

void FrsTPCRaw2Cal::Exec(Option_t* option)
{
    tpcCalArray->clear();

    // reset
    std::vector<Int_t> v1190_lead_hits[128];
    for (int i = 0; i < 7; i++)
    {
        b_tpc_xy[i] = false;
        for (int j = 0; j < 4; j++) tpc_csum[i][j] = -9999999;
    }

    for (const auto & adcItem : *adcArray)
    {
        // std::cout << "TPC: " << adcItem.Get_tpc() << " - Channel: " << adcItem.Get_channel() << " - Data: " << adcItem.Get_adc_data() << std::endl; 
        uint32_t itpc = adcItem.Get_tpc();
        uint32_t channel = adcItem.Get_channel();
        uint32_t data = adcItem.Get_adc_data();

        // mapping ...........
        if (channel >= 0 && channel < 4) tpc_a[itpc][channel] = data;
        else if (channel == 4) tpc_l[itpc][0] = data;
        else if (channel == 5) tpc_r[itpc][0] = data;
        else if (channel == 6) tpc_l[itpc][1] = data;
        else if (channel == 7) tpc_r[itpc][1] = data;
    
    }



    // for (const auto & v7x5item : *v7x5array)
    // {
    //     uint32_t channel = v7x5item.Get_channel();
    //     uint32_t geo = v7x5item.Get_geo();
    //     uint32_t data = v7x5item.Get_v7x5_data();
    //     int tpc_s2_geo = 12;
    //     int tpc_s3_geo = 8; // lol
    //     int tpc_s4_geo = 8; // for NOW!! MAYBE 13????
    //     switch (channel)
    //     {   
    //         case 0:
    //             if (geo == tpc_s2_geo) tpc_a[0][0] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_a[4][0] = data; // 41
    //             break;
    //         case 1:
    //             if (geo == tpc_s2_geo) tpc_a[0][1] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_a[4][1] = data; // 41
    //             break;
    //         case 2:
    //             if (geo == tpc_s2_geo) tpc_a[0][2] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_a[4][2] = data; // 41
    //             break;
    //         case 3:
    //             if (geo == tpc_s2_geo) tpc_a[0][3] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_a[4][3] = data; // 41
    //             break;
    //         case 4:
    //             if (geo == tpc_s2_geo) tpc_l[0][0] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_l[4][0] = data; // 41
    //             break;
    //         case 5:
    //             if (geo == tpc_s2_geo) tpc_r[0][0] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_r[4][0] = data; // 41
    //             break;
    //         case 6:
    //             if (geo == tpc_s2_geo) tpc_l[0][1] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_l[4][1] = data; // 41
    //             break;
    //         case 7:
    //             if (geo == tpc_s2_geo) tpc_r[0][1] = data; // 21
    //             if (geo == tpc_s4_geo) tpc_r[4][1] = data; // 41
    //             break;
    //         case 8:
    //             if (geo == tpc_s2_geo) tpc_a[1][0] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_a[5][0] = data; // 42
    //             break;
    //         case 9:
    //             if (geo == tpc_s2_geo) tpc_a[1][1] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_a[5][1] = data; // 42
    //             break;
    //         case 10:
    //             if (geo == tpc_s2_geo) tpc_a[1][2] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_a[5][2] = data; // 42
    //             break;
    //         case 11:
    //             if (geo == tpc_s2_geo) tpc_a[1][3] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_a[5][3] = data; // 42
    //             break;
    //         case 12:
    //             if (geo == tpc_s2_geo) tpc_l[1][0] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_l[5][0] = data; // 42
    //             break;
    //         case 13:
    //             if (geo == tpc_s2_geo) tpc_r[1][0] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_r[5][0] = data; // 42
    //             break;
    //         case 14:
    //             if (geo == tpc_s2_geo) tpc_l[1][1] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_l[5][1] = data; // 42
    //             break;
    //         case 15:
    //             if (geo == tpc_s2_geo) tpc_r[1][1] = data; // 22
    //             if (geo == tpc_s4_geo) tpc_r[5][1] = data; // 42
    //             break;
    //         case 16:
    //             if (geo == tpc_s2_geo) tpc_a[2][0] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_a[6][0] = data; // 31
    //             break;
    //         case 17:
    //             if (geo == tpc_s2_geo) tpc_a[2][1] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_a[6][1] = data; // 31
    //             break;
    //         case 18:
    //             if (geo == tpc_s2_geo) tpc_a[2][2] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_a[6][2] = data; // 31
    //             break;
    //         case 19:
    //             if (geo == tpc_s2_geo) tpc_a[2][3] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_a[6][3] = data; // 31
    //             break;
    //         case 20:
    //             if (geo == tpc_s2_geo) tpc_l[2][0] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_l[6][0] = data; // 31
    //             break;
    //         case 21:
    //             if (geo == tpc_s2_geo) tpc_r[2][0] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_r[6][0] = data; // 31
    //             break;
    //         case 22:
    //             if (geo == tpc_s2_geo) tpc_l[2][1] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_l[6][1] = data; // 31
    //             break;
    //         case 23:
    //             if (geo == tpc_s2_geo) tpc_r[2][1] = data; // 23
    //             if (geo == tpc_s3_geo) tpc_r[6][1] = data; // 31
    //             break;
    //         case 24:
    //             if (geo == tpc_s2_geo) tpc_a[3][0] = data; // 24
    //             break;
    //         case 25:
    //             if (geo == tpc_s2_geo) tpc_a[3][1] = data; // 24
    //             break;
    //         case 26:
    //             if (geo == tpc_s2_geo) tpc_a[3][2] = data; // 24
    //             break;
    //         case 27:
    //             if (geo == tpc_s2_geo) tpc_a[3][3] = data; // 24
    //             break;
    //         case 28:
    //             if (geo == tpc_s2_geo) tpc_l[3][0] = data; // 24
    //             break;
    //         case 29:
    //             if (geo == tpc_s2_geo) tpc_r[3][0] = data; // 24
    //             break;
    //         case 30:
    //             if (geo == tpc_s2_geo) tpc_l[3][1] = data; // 24
    //             break;
    //         case 31:
    //             if (geo == tpc_s2_geo) tpc_r[3][1] = data; // 24
    //             break;

    //     }
    // }


    std::cout << "tpc_a[5][2] ::: " << tpc_a[5][2] << std::endl;

    int v1190_count[128] = {0};
    for (const auto & v1190item : *v1190array)
    {
        uint32_t channel = v1190item.Get_channel();
        uint32_t data = v1190item.Get_v1190_data();
        uint32_t lot = v1190item.Get_leadOrTrail();

        // leads 0, trails 1  
        if (lot == 0 && v1190_count[channel] < 64) v1190_lead_hits[channel].emplace_back(data);

        v1190_count[channel]++;
    }

   
    for (int i = 0; i < 7; i++)
    {
        double temp_de = 1.0;
        int temp_count = 0;

        // anode
        for (int j = 0; j < 4; j++)
        {
            // each element a vector
            tpc_dt[i][j] = v1190_lead_hits[v1190_channel_dt[i][j]];
            

            if (tpc_a[i][j] - tpc->a_offset[i][j] > 5.0)
            {
                temp_de *= (tpc_a[i][j] - tpc->a_offset[i][j]);
                temp_count++;
            }
            if (temp_count == 4)
            {
                tpc_de[i] = sqrt(sqrt(temp_de));
                b_tpc_de[i] = kTRUE; // here we go to Anl with both
                // CEJ: we never passed these along, its used for another Z calc
                // we can add this if desired, but later down the line? not urgent I guess
            }
        }

        // delay line
        for (int j = 0; j < 2; j++)
        {
            tpc_lt[i][j] = v1190_lead_hits[v1190_channel_lt[i][j]];
            tpc_rt[i][j] = v1190_lead_hits[v1190_channel_rt[i][j]];
        }

        // calibgrid
        tpc_calibgrid[i] = v1190_lead_hits[v1190_channel_calibgrid[i]];

    }

    // timeref
    for (int i = 0; i < 8; i++)
    {
        tpc_timeref[i] = v1190_lead_hits[v1190_channel_timeref[i]];
    }


    // CALIB 
    for (int i = 0; i < 8; i++)
    {   
        // weird condition in go4, ignore for now loop through vector size
        for (int j = 0; j < tpc_timeref[i].size(); j++)
        {   
            if (tpc_timeref[i][j] > tpc->lim_timeref[i][0] && tpc_timeref[i][j] < tpc->lim_timeref[i][1])
            {
                b_tpc_timeref[i] = true;
            }

            if (b_tpc_timeref[i])
            {
                if (tpc_timeref_s[i] <= 0 || (tpc_timeref_s[i] > 0 && tpc_timeref[i][j] < tpc_timeref_s[i]))
                {
                    tpc_timeref_s[i] = tpc_timeref[i][j];
                }
            }
        }
    }


    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < tpc_lt[i][0].size(); j++)
        {
            bool checkrange1 = 0;
            Int_t thisdata = tpc_lt[i][0][j];

            Int_t currently_selected = tpc_lt_s[i][0];

            if (thisdata > tpc->lim_lt[i][0][0] && thisdata < tpc->lim_lt[i][0][1])
            {
                checkrange1 = true;

            }

            if (checkrange1 && (currently_selected <= 0 || (currently_selected > 0 && thisdata  < currently_selected)))
            {
                tpc_lt_s[i][0] = thisdata;
            }
        }

        for (int j = 0; j < tpc_rt[i][0].size(); j++)
        {
            bool checkrange2 = 0;
            Int_t thisdata = tpc_rt[i][0][j];

            Int_t currently_selected = tpc_rt_s[i][0];

            if (thisdata > tpc->lim_rt[i][0][0] && thisdata < tpc->lim_rt[i][0][1])
            {
                checkrange2 = true;
            }

            if (checkrange2 && (currently_selected <= 0 || (currently_selected > 0 && thisdata  < currently_selected)))
            {
                tpc_rt_s[i][0] = thisdata;
            }
        }

        for (int j = 0; j < tpc_lt[i][1].size(); j++)
        {
            bool checkrange3 = 0;
            Int_t thisdata = tpc_lt[i][1][j];

            Int_t currently_selected = tpc_lt_s[i][1];

            if (thisdata > tpc->lim_lt[i][1][0] && thisdata < tpc->lim_lt[i][1][1])
            {
                checkrange3 = true;
            }

            if (checkrange3 && (currently_selected <= 0 || (currently_selected > 0 && thisdata  < currently_selected)))
            {
                tpc_lt_s[i][1] = thisdata;
            }
        }

        for (int j = 0; j < tpc_rt[i][1].size(); j++)
        {
            bool checkrange4 = 0;
            Int_t thisdata = tpc_rt[i][1][j];

            Int_t currently_selected = tpc_rt_s[i][1];

            if (thisdata > tpc->lim_rt[i][1][0] && thisdata < tpc->lim_rt[i][1][1])
            {
                checkrange4 = true;
            }

            if (checkrange4 && (currently_selected <= 0 || (currently_selected > 0 && thisdata  < currently_selected)))
            {
                tpc_rt_s[i][1] = thisdata;
            }
        }

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < tpc_dt[i][j].size(); k++)
            {
                bool checkrange5 = 0;
                Int_t thisdata = tpc_dt[i][j][k];

                Int_t currently_selected = tpc_dt_s[i][j];

                if (thisdata > tpc->lim_dt[i][j][0] && thisdata < tpc->lim_dt[i][j][1])
                {
                    checkrange5 = true;
                } 

                if (checkrange5 && (currently_selected <= 0 || (currently_selected > 0 && thisdata < currently_selected)))
                {
                    tpc_dt_s[i][j] = thisdata;
                }
            }
        }
        
        for (int j = 0; j < 4; j++)
        {
            // calculate control sums
            if (j < 2 && tpc_lt_s[i][0] > 0 && tpc_rt_s[i][0] > 0 && tpc_dt_s[i][j] > 0)
            {
                tpc_csum[i][j] = (tpc_lt_s[i][0] + tpc_rt_s[i][0] - 2 * tpc_dt_s[i][j]);
            }
            else if (2 <= j && j < 4 && tpc_lt_s[i][1] > 0 && tpc_rt_s[i][1] > 0 && tpc_dt_s[i][j] > 0)
            {
                tpc_csum[i][j] = (tpc_lt_s[i][1] + tpc_rt_s[i][1] - 2 * tpc_dt_s[i][j]);
            }
            else
            {
                tpc_csum[i][j] = -9999999;
            }

            if (tpc_csum[i][0] > tpc->lim_csum1[i][0] && tpc_csum[i][0] < tpc->lim_csum1[i][1])
            {   
                b_tpc_csum[i][0] = true;
            }
            if (tpc_csum[i][1] > tpc->lim_csum2[i][0] && tpc_csum[i][1] < tpc->lim_csum2[i][1])
            {   
                b_tpc_csum[i][1] = true;
            }
            if (tpc_csum[i][2] > tpc->lim_csum3[i][0] && tpc_csum[i][2] < tpc->lim_csum3[i][1])
            {   
                b_tpc_csum[i][2] = true;
            }
            if (tpc_csum[i][3] > tpc->lim_csum4[i][0] && tpc_csum[i][3] < tpc->lim_csum4[i][1])
            {   
                b_tpc_csum[i][3] = true;
            }
        }

        int countx = 0;
        float sumx = 0.0;
        float tmp_tpc_x0 = -99999.;
        float tmp_tpc_x1 = -99999.;

        if (b_tpc_csum[i][0] || b_tpc_csum[i][1])
        {
            tpc_xraw[i][0] = tpc_lt_s[i][0] - tpc_rt_s[i][0];
            tmp_tpc_x0 = (tpc_xraw[i][0]) * (tpc->x_factor[i][0]) + (tpc->x_offset[i][0]);
            sumx += tmp_tpc_x0;
            countx++;
        }
        if (b_tpc_csum[i][2] || b_tpc_csum[i][3])
        {
            tpc_xraw[i][1] = tpc_lt_s[i][1] - tpc_rt_s[i][1];
            tmp_tpc_x1 = (tpc_xraw[i][1]) * (tpc->x_factor[i][1]) + (tpc->x_offset[i][1]);
            sumx += tmp_tpc_x1;
            countx++;
        }

        if (countx > 0)
        {   
            tpc_x[i] = sumx / ((float)countx);
        }
        if (countx == 2)
        {
            tpc_dx12[i] = tmp_tpc_x1 - tmp_tpc_x0;
        }

        int county = 0;
        float sumy = 0.0;
        float tmp_tpc_y[4] = {-99999., -99999., -99999., -99999.};
        int index_timeref = tpc->id_tpc_timeref[i];
        for (int j = 0; j < 4; j++)
        {       
            if (b_tpc_csum[i][j] && b_tpc_timeref[index_timeref])
            {
                tpc_yraw[i][j] = tpc_dt_s[i][j] - tpc_timeref_s[index_timeref];
                tmp_tpc_y[j] = (tpc_yraw[i][j]) * (tpc->y_factor[i][j]) + (tpc->y_offset[i][j]);
                sumy += tmp_tpc_y[j];
                county++;
            }
        }

        if (county > 0)
        {
            tpc_y[i] = sumy / ((double)county);
        }

        if (countx > 0 && county > 0)
        {
            b_tpc_xy[i] = kTRUE;
        }
        else
        {
            b_tpc_xy[i] = kFALSE;
        }

    }

    Float_t dist_TPC21_TPC22 = frs->dist_TPC22 - frs->dist_TPC21;
    Float_t dist_TPC23_TPC24 = frs->dist_TPC24 - frs->dist_TPC23;
    Float_t dist_TPC22_TPC24 = frs->dist_TPC24 - frs->dist_TPC22;
    Float_t dist_TPC21_focS2 = frs->dist_TPC21 - frs->dist_focS2;
    Float_t dist_TPC22_focS2 = frs->dist_TPC22 - frs->dist_focS2;
    Float_t dist_TPC23_focS2 = frs->dist_TPC23 - frs->dist_focS2;
    Float_t dist_TPC41_TPC42 = frs->dist_TPC42 - frs->dist_TPC41;
    Float_t dist_TPC42_focS4 = frs->dist_focS4 - frs->dist_TPC42;
    
    //=================================
    // Tracking with TPC 21 and TPC 22
    //=================================
    if (b_tpc_xy[0] && b_tpc_xy[1])
    {
        tpc_angle_x_s2_foc_21_22 = (tpc_x[1] - tpc_x[0])/dist_TPC21_TPC22*1000.;
        tpc_angle_y_s2_foc_21_22 = (tpc_y[1] - tpc_y[0])/dist_TPC21_TPC22*1000.;
        tpc_x_s2_foc_21_22 = -tpc_angle_x_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_x[0]; //check
        tpc_y_s2_foc_21_22 = -tpc_angle_y_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_y[0]; //check
        Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
        tpc21_22_sc21_x = (tpc_angle_x_s2_foc_21_22/1000.*dist_SC21_focS2)+tpc_x_s2_foc_21_22;
        tpc21_22_sc21_y = (tpc_angle_y_s2_foc_21_22/1000.*dist_SC21_focS2)+tpc_y_s2_foc_21_22;
        Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
        tpc21_22_sc22_x = (tpc_angle_x_s2_foc_21_22/1000.*dist_SC22_focS2)+tpc_x_s2_foc_21_22;
        tpc21_22_sc22_y = (tpc_angle_y_s2_foc_21_22/1000.*dist_SC22_focS2)+tpc_y_s2_foc_21_22;
        Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;
        tpc21_22_s2target_x = (tpc_angle_x_s2_foc_21_22/1000.*dist_S2target_focS2)+tpc_x_s2_foc_21_22;
        tpc21_22_s2target_y = (tpc_angle_y_s2_foc_21_22/1000.*dist_S2target_focS2)+tpc_y_s2_foc_21_22;
    }

    //=================================
    // Tracking with TPC 23 and TPC 24
    //=================================
    if (b_tpc_xy[2] && b_tpc_xy[3])
    {
        // Angle X at S2 focus
        tpc_angle_x_s2_foc_23_24 = (tpc_x[3] - tpc_x[2])/dist_TPC23_TPC24*1000.;
        // Angle Y at S2 focus
        tpc_angle_y_s2_foc_23_24 = (tpc_y[3] - tpc_y[2])/dist_TPC23_TPC24*1000.;
        // X position at S2 focus
        tpc_x_s2_foc_23_24 = -tpc_angle_x_s2_foc_23_24 * dist_TPC23_focS2/1000. + tpc_x[2]; //check
        // Y position at S2 focus
        tpc_y_s2_foc_23_24 = -tpc_angle_y_s2_foc_23_24 * dist_TPC23_focS2/1000. + tpc_y[2]; //check
        /// TPC 23 24 X at SC21 focus 
        Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
        tpc23_24_sc21_x = (tpc_angle_x_s2_foc_23_24/1000.*dist_SC21_focS2)+tpc_x_s2_foc_23_24;
        tpc23_24_sc21_y = (tpc_angle_y_s2_foc_23_24/1000.*dist_SC21_focS2)+tpc_y_s2_foc_23_24;
        /// TPC 23 24 X at SC22 focus ??
        Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
        tpc23_24_sc22_x = (tpc_angle_x_s2_foc_23_24/1000.*dist_SC22_focS2)+tpc_x_s2_foc_23_24;
        tpc23_24_sc22_y = (tpc_angle_y_s2_foc_23_24/1000.*dist_SC22_focS2)+tpc_y_s2_foc_23_24;
        // TPC 23 24 X at target focus ??
        Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;
        tpc23_24_s2target_x = (tpc_angle_x_s2_foc_23_24/1000.*dist_S2target_focS2)+tpc_x_s2_foc_23_24;
        tpc23_24_s2target_y = (tpc_angle_y_s2_foc_23_24/1000.*dist_S2target_focS2)+tpc_y_s2_foc_23_24;
    }
    else  
    {
        tpc_x_s2_foc_23_24= -999;
        tpc_x_s2_foc_23_24= -999;
        tpc_y_s2_foc_23_24 =-999;
        tpc_angle_x_s2_foc_23_24 =-999;
        tpc_angle_y_s2_foc_23_24 =-999;
        tpc23_24_sc21_x =-999;
        tpc23_24_sc21_y =-999;
        tpc23_24_sc22_x =-999;
        tpc23_24_sc22_y =-999;   
    }

    //=================================
    // Tracking with TPC 22 and TPC 24
    //=================================
    if (b_tpc_xy[1] && b_tpc_xy[3])
    {
        tpc_angle_x_s2_foc_22_24 = (tpc_x[3] - tpc_x[1])/dist_TPC22_TPC24*1000.;
        tpc_angle_y_s2_foc_22_24 = (tpc_y[3] - tpc_y[1])/dist_TPC22_TPC24*1000.;
        tpc_x_s2_foc_22_24 = -tpc_angle_x_s2_foc_22_24 * dist_TPC22_focS2/1000. + tpc_x[1]; //check
        tpc_y_s2_foc_22_24 = -tpc_angle_y_s2_foc_22_24 * dist_TPC22_focS2/1000. + tpc_y[1]; //check
        Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
        tpc22_24_sc21_x = (tpc_angle_x_s2_foc_22_24/1000.*dist_SC21_focS2)+tpc_x_s2_foc_22_24;
        tpc22_24_sc21_y = (tpc_angle_y_s2_foc_22_24/1000.*dist_SC21_focS2)+tpc_y_s2_foc_22_24;
        Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
        tpc22_24_sc22_x = (tpc_angle_x_s2_foc_22_24/1000.*dist_SC22_focS2)+tpc_x_s2_foc_22_24;
        tpc22_24_sc22_y = (tpc_angle_y_s2_foc_22_24/1000.*dist_SC22_focS2)+tpc_y_s2_foc_22_24;
        Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;
        tpc22_24_s2target_x = (tpc_angle_x_s2_foc_22_24/1000.*dist_S2target_focS2)+tpc_x_s2_foc_22_24;
        tpc22_24_s2target_y = (tpc_angle_y_s2_foc_22_24/1000.*dist_S2target_focS2)+tpc_y_s2_foc_22_24;

    }
    else 
    {
        tpc_x_s2_foc_22_24= -999 ;
        tpc_y_s2_foc_22_24 =-999;
        tpc_angle_x_s2_foc_22_24 =-999;
        tpc_angle_y_s2_foc_22_24 =-999;
        tpc22_24_sc21_x =-999;
        tpc22_24_sc21_y =-999;
        tpc22_24_sc22_x =-999;
        tpc22_24_sc22_y =-999;
    }

    //=====================================================
    // Tracking with TPC 41 and TPC 42 (TPC 5 and 6) at S4
    //=====================================================
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {   
        tpc_angle_x_s4 = (tpc_x[5] - tpc_x[4])/dist_TPC41_TPC42*1000.;
        tpc_angle_y_s4 = (tpc_y[5] - tpc_y[4])/dist_TPC41_TPC42*1000.;
        tpc_x_s4 = tpc_angle_x_s4 * dist_TPC42_focS4/1000. + tpc_x[5];
        tpc_y_s4 = tpc_angle_y_s4 * dist_TPC42_focS4/1000. + tpc_y[5];

        Float_t dist_SC41_focS4 = frs->dist_SC41 - frs->dist_focS4;
        tpc_sc41_x = (tpc_angle_x_s4/1000.*dist_SC41_focS4)+tpc_x_s4;
        tpc_sc41_y = (tpc_angle_y_s4/1000.*dist_SC41_focS4)+tpc_y_s4;

        Float_t dist_SC42_focS4 = frs->dist_SC42 - frs->dist_focS4;
        tpc_sc42_x = (tpc_angle_x_s4/1000.*dist_SC42_focS4)+tpc_x_s4;
        tpc_sc42_y = (tpc_angle_y_s4/1000.*dist_SC42_focS4)+tpc_y_s4;

        Float_t dist_SC43_focS4 = frs->dist_SC43 - frs->dist_focS4;
        tpc_sc43_x = (tpc_angle_x_s4/1000.*dist_SC43_focS4)+tpc_x_s4;
        tpc_sc43_y = (tpc_angle_y_s4/1000.*dist_SC43_focS4)+tpc_y_s4;

        Float_t dist_MUSIC41_focS4 = frs->dist_MUSIC41 - frs->dist_focS4;
        tpc_music41_x = (tpc_angle_x_s4/1000.*dist_MUSIC41_focS4)+tpc_x_s4;
        tpc_music41_y = (tpc_angle_y_s4/1000.*dist_MUSIC41_focS4)+tpc_y_s4;

        Float_t dist_MUSIC42_focS4 = frs->dist_MUSIC42 - frs->dist_focS4;
        tpc_music42_x = (tpc_angle_x_s4/1000.*dist_MUSIC42_focS4)+tpc_x_s4;
        tpc_music42_y = (tpc_angle_y_s4/1000.*dist_MUSIC42_focS4)+tpc_y_s4;

        Float_t dist_MUSIC43_focS4 = frs->dist_MUSIC43 - frs->dist_focS4;
        tpc_music43_x = (tpc_angle_x_s4/1000.*dist_MUSIC43_focS4)+tpc_x_s4;
        tpc_music43_y = (tpc_angle_y_s4/1000.*dist_MUSIC43_focS4)+tpc_y_s4;

        Float_t dist_S4target_focS4 = frs->dist_S4target - frs->dist_focS4;
        tpc_s4target_x = (tpc_angle_x_s4/1000.* dist_S4target_focS4)+tpc_x_s4;
        tpc_s4target_y = (tpc_angle_y_s4/1000.* dist_S4target_focS4)+tpc_y_s4;
    }
    else  
    {
        tpc_angle_x_s4= -999;
        tpc_angle_y_s4= -999;
        tpc_x_s4 =-999;
        tpc_y_s4 =-999;
        tpc_sc42_x =-999;
        tpc_sc42_y =-999;  
    }

    auto & tpcEntry = tpcCalArray->emplace_back();
    tpcEntry.SetAll(tpc_x,
        b_tpc_xy,
        tpc_csum,
        tpc_angle_x_s2_foc_21_22,
        tpc_angle_y_s2_foc_21_22,
        tpc_x_s2_foc_21_22,
        tpc_y_s2_foc_21_22,
        tpc21_22_sc21_x,
        tpc21_22_sc22_x,
        tpc_angle_x_s2_foc_23_24,
        tpc_angle_y_s2_foc_23_24,
        tpc_x_s2_foc_23_24,
        tpc_y_s2_foc_23_24,
        tpc23_24_sc21_x,
        tpc23_24_sc21_y,
        tpc23_24_sc22_x,
        tpc23_24_sc22_y,
        tpc_angle_x_s2_foc_22_24,
        tpc_angle_y_s2_foc_22_24,
        tpc_x_s2_foc_22_24,
        tpc_y_s2_foc_22_24,
        tpc_angle_x_s4,
        tpc_angle_y_s4,
        tpc_x_s4,
        tpc_y_s4,
        tpc_sc41_x,
        tpc_sc41_y,
        tpc_sc42_x,
        tpc_sc42_y,
        tpc_sc43_x,
        tpc_music41_x,
        tpc_music42_x,
        tpc_music43_x);

    fNEvents += 1;


}


void FrsTPCRaw2Cal::ZeroArrays()
{   
    memset(tpc_a, 0, sizeof(tpc_a));
    memset(tpc_l, 0, sizeof(tpc_l));
    memset(tpc_r, 0, sizeof(tpc_r));
    memset(b_tpc_timeref, 0, sizeof(b_tpc_timeref));
    memset(tpc_timeref_s, 0, sizeof(tpc_timeref_s));
    memset(tpc_dt_s, 0, sizeof(tpc_dt_s));
    memset(tpc_lt_s, 0, sizeof(tpc_lt_s));
    memset(tpc_rt_s, 0, sizeof(tpc_rt_s));
    memset(tpc_de, 0, sizeof(tpc_de));
    memset(b_tpc_de, 0, sizeof(b_tpc_de));
    memset(b_tpc_csum, 0, sizeof(b_tpc_csum));
    memset(tpc_x, 0, sizeof(tpc_x));
    memset(tpc_y, 0, sizeof(tpc_y));
    memset(tpc_xraw, 0, sizeof(tpc_xraw));
    memset(tpc_yraw, 0, sizeof(tpc_yraw));
    memset(tpc_dx12, 0, sizeof(tpc_dx12));
}

void FrsTPCRaw2Cal::ZeroVariables()
{
    tpc_x_s2_foc_21_22 = -999;
    tpc_y_s2_foc_21_22 = -999;
    tpc_angle_x_s2_foc_21_22 = -999;
    tpc_angle_y_s2_foc_21_22 = -999;
    tpc_x_s2_foc_23_24 = -999;
    tpc_y_s2_foc_23_24 = -999;
    tpc_angle_x_s2_foc_23_24 = -999;
    tpc_angle_y_s2_foc_23_24 = -999;
    tpc_x_s2_foc_22_24 = -999;
    tpc_y_s2_foc_22_24 = -999;
    tpc_angle_x_s2_foc_22_24 = -999;
    tpc_angle_y_s2_foc_22_24 = -999;
    tpc_x_s2_foc = -999;
    tpc_y_s2_foc = -999;
    tpc_angle_x_s2_foc = -999;
    tpc_angle_y_s2_foc = -999;
    tpc_x_s4 = -999;
    tpc_y_s4 = -999;
    tpc_angle_x_s4 = -999;
    tpc_angle_y_s4 = -999;
    tpc_x_s4_target2 = -999;
    tpc_y_s4_target2 = -999;
    tpc21_22_sc21_x = -999;
    tpc21_22_sc21_y = -999;
    tpc23_24_sc21_x = -999;
    tpc23_24_sc21_y = -999;
    tpc22_24_sc21_x = -999;
    tpc22_24_sc21_y = -999;
    tpc21_22_sc22_x = -999;
    tpc21_22_sc22_y = -999;
    tpc23_24_sc22_x = -999;
    tpc23_24_sc22_y = -999;
    tpc22_24_sc22_x = -999;
    tpc22_24_sc22_y = -999;
    tpc21_22_s2target_x = -999;
    tpc21_22_s2target_y = -999;
    tpc23_24_s2target_x = -999;
    tpc23_24_s2target_y = -999;
    tpc22_24_s2target_x = -999;
    tpc22_24_s2target_y = -999;
    tpc_x_s2_target1 = -999;
    tpc_y_s2_target1 = -999;
    tpc_sc41_x = -999;
    tpc_sc41_y = -999;
    tpc_sc42_x = -999;
    tpc_sc42_y = -999;
    tpc_sc43_x = -999;
    tpc_sc43_y = -999;
    tpc_music41_x = -999;
    tpc_music41_y = -999;
    tpc_music42_x = -999;
    tpc_music42_y = -999;
    tpc_music43_x = -999;
    tpc_music43_y = -999;
    tpc_s4target_x = -999;
    tpc_s4target_y = -999;
    music1_x1 = -999;
    music1_x2 = -999;
    music1_x3 = -999;
    music1_x4 = -999;
    music1_y1 = -999;
    music1_y2 = -999;
    music1_y3 = -999;
    music1_y4 = -999;
    music2_x = -999;
}

void FrsTPCRaw2Cal::ClearVectors()
{
    for (int i = 0; i < 7; i++)
    {
        tpc_calibgrid[i].clear();
        for (int j = 0; j < 2; j++)
        {
            tpc_lt[i][j].clear();
            tpc_rt[i][j].clear();
        }
        for (int j = 0; j < 4; j++)
        {
            tpc_dt[i][j].clear();
        }

    }
    for (int i = 0; i < 8; i++)
    {
        tpc_timeref[i].clear();
    }
    /*for (int i = 0; i < 128; i++)
    {
        v1190_lead_hits[i].clear();
    }*/
    
    
    /*
    v1190_channel.clear();
    v1190_data.clear();
    v1190_lot.clear();
    for (int i = 0; i < 2; i++)
    {
        v7x5_geo[i].clear();
        v7x5_channel[i].clear();
        v7x5_data[i].clear();
    }
    */

}

void FrsTPCRaw2Cal::FinishEvent()
{
    ZeroArrays();
    ZeroVariables();
    ClearVectors();
}

void FrsTPCRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.", fNEvents));
}

ClassImp(FrsTPCRaw2Cal)