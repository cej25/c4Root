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

FrsTPCRaw2Cal::FrsTPCRaw2Cal(TFRSParameter* ffrs,
                            TMWParameter* fmw,
                            TTPCParameter* ftpc,
                            TMUSICParameter* fmusic,
                            TLABRParameter* flabr,
                            TSCIParameter* fsci,
                            TIDParameter* fid,
                            TSIParameter* fsi,
                            TMRTOFMSParameter* fmrtof,
                            TRangeParameter* frange)
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsTPCData"))
    ,   fCalArray(new TClonesArray("FrsTPCCalData"))
{
    frs = ffrs;
    mw = fmw;
    tpc = ftpc;
    music = fmusic;
    labr = flabr;
    sci = fsci;
    id = fid;
    si = fsi;
    mrtof = fmrtof;
    range = frange;
}

FrsTPCRaw2Cal::FrsTPCRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsTPCData"))
    ,   fCalArray(new TClonesArray("FrsTPCCalData"))
{

}

FrsTPCRaw2Cal::~FrsTPCRaw2Cal()
{
    c4LOG(info, "Deleting FrsTPCRaw2Cal task");
    if (fRawArray) delete fRawArray;
    if (fCalArray) delete fCalArray;
}

void FrsTPCRaw2Cal::SetParameters()
{
    v1190_channel_dt[0][0] = 0+1; //TPC21-A11
    v1190_channel_dt[0][1] = 1+1; //TPC21-A12
    v1190_channel_dt[0][2] = 2+1; //TPC21-A21
    v1190_channel_dt[0][3] = 3+1; //TPC21-A22
    v1190_channel_lt[0][0] = 4+1; //TPC21-DL1
    v1190_channel_rt[0][0] = 5+1; //TPC21-DR1
    // 6, 7 empty
    v1190_channel_lt[0][1] = 8+1; //TPC21-DL2
    v1190_channel_rt[0][1] = 9+1; //TPC21-DR2
    v1190_channel_dt[1][0] = 10+1; //TPC22-A11
    v1190_channel_dt[1][1] = 11+1; //TPC22-A12
    v1190_channel_dt[1][2] = 12+1; //TPC22-A21
    v1190_channel_dt[1][3] = 13+1; //TPC22-A22
    // 14, 15 empty
    //17(top channel of 3rd module is dead)
    //18(skip)
    v1190_channel_lt[1][0] = 18+1; //TPC22-DL1
    v1190_channel_rt[1][0] = 19+1; //TPC22-DR1
    v1190_channel_lt[1][1] = 20+1; //TPC22-DL2
    v1190_channel_rt[1][1] = 21+1; //TPC22-DR2
    // 22,23 empty

    // ======= middle NIM crate (TPC23+24)=========
    v1190_channel_dt[2][0] = 24+1; //TPC23-A11
    v1190_channel_dt[2][1] = 25+1; //TPC23-A12
    v1190_channel_dt[2][2] = 26+1; //TPC23-A21
    v1190_channel_dt[2][3] = 27+1; //TPC23-A22
    v1190_channel_lt[2][0] = 28+1; //TPC23-DL1
    v1190_channel_rt[2][0] = 29+1; //TPC23-DR1
    //30,31 empty
    v1190_channel_lt[2][1] = 32+1; //TPC23-DL2
    v1190_channel_rt[2][1] = 33+1; //TPC23-DR2
    v1190_channel_dt[3][0] = 34+1; //TPC24-A11
    v1190_channel_dt[3][1] = 35+1; //TPC24-A12
    v1190_channel_dt[3][2] = 36+1; //TPC24-A21
    v1190_channel_dt[3][3] = 37+1; //TPC24-A22
    //38,39 empty
    v1190_channel_lt[3][0] = 40+1; //TPC24-DL1
    v1190_channel_rt[3][0] = 41+1; //TPC24-DR1
    v1190_channel_lt[3][1] = 42+1; //TPC24-DL2
    v1190_channel_rt[3][1] = 43+1; //TPC24-DR2
    //46,47 empty

    // ======= bottom NIM crate (TPC41+42+31)=========
    v1190_channel_dt[4][0] = 64+1; //TPC41-A11
    v1190_channel_dt[4][1] = 65+1; //TPC41-A12
    v1190_channel_dt[4][2] = 66+1; //TPC41-A21
    v1190_channel_dt[4][3] = 67+1; //TPC41-A22
    v1190_channel_lt[4][0] = 68+1; //TPC41-DL1
    v1190_channel_rt[4][0] = 69+1; //TPC41-DR1
    //70,71 empty
    v1190_channel_lt[4][1] = 72+1; //TPC41-DL2
    v1190_channel_rt[4][1] = 73+1; //TPC41-DR2
    v1190_channel_dt[5][0] = 74+1; //TPC42-A11
    v1190_channel_dt[5][1] = 75+1; //TPC42-A12
    v1190_channel_dt[5][2] = 76+1; //TPC42-A21
    v1190_channel_dt[5][3] = 77+1; //TPC42-A22
    //78,79 empty
    v1190_channel_lt[5][0] = 80+1; //TPC42-DL1
    v1190_channel_rt[5][0] = 81+1; //TPC42-DR1
    v1190_channel_lt[5][1] = 82+1; //TPC42-DL2
    v1190_channel_rt[5][1] = 83+1; //TPC42-DR2
    v1190_channel_dt[6][0] = 84+1; //TPC31-A11
    v1190_channel_dt[6][1] = 85+1; //TPC31-A12
    //86,87 empty
    v1190_channel_dt[6][2] = 88+1; //TPC31-A21
    v1190_channel_dt[6][3] = 89+1; //TPC31-A22
    v1190_channel_lt[6][0] = 90+1; //TPC31-DL1
    v1190_channel_rt[6][0] = 91+1; //TPC31-DR1
    v1190_channel_lt[6][1] = 92+1; //TPC31-DL2
    v1190_channel_rt[6][1] = 93+1; //TPC31-DR2
    //94,95 empty

    //time reference signal
    v1190_channel_timeref[0] = 96+1; //accept trig
    v1190_channel_timeref[1] = 97+1; //sc21
    v1190_channel_timeref[2] = 98+1; //sc22
    v1190_channel_timeref[3] = 99+1; //sc31
    v1190_channel_timeref[4] =100+1; //sc41
    v1190_channel_timeref[5] =101+1; //
    v1190_channel_timeref[6] =102+1; //
    v1190_channel_timeref[7] =103+1; //

    v1190_channel_calibgrid[0] = 104+1;//tpc21grid
    v1190_channel_calibgrid[1] = 105+1;//tpc22grid
    v1190_channel_calibgrid[2] = 106+1;//tpc23grid
    v1190_channel_calibgrid[3] = 107+1;//tpc24grid
    v1190_channel_calibgrid[4] = 108+1;//tpc41grid
    v1190_channel_calibgrid[5] = 109+1;//tpc42grid
    v1190_channel_calibgrid[6] = 110+1;//tpc31grid //to be checked maybe 111

}

InitStatus FrsTPCRaw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsTPCData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of TPCData not found");

    FairRootManager::Instance()->Register("FrsTPCCalData", "FRS TPC Cal Data", fCalArray, !fOnline);

    fRawArray->Clear();
    fCalArray->Clear();

    SetParameters();

    return kSUCCESS;
}

void FrsTPCRaw2Cal::Exec(Option_t* option)
{

    // check there is actual data from module(s)
    int mult = fRawArray->GetEntriesFast();
    if (!mult) return;

    fRawHit = (FrsTPCData*)fRawArray->At(mult-1);

    v7x5_geo = fRawHit->Get_v7x5_geo();
    v7x5_channel = fRawHit->Get_v7x5_channel();
    v7x5_data = fRawHit->Get_v7x5_data();
    
    for (int m = 0; m < 2; m++)
    {
       for (int i = 0; i < v7x5_data[m].size(); i++)
        {
            switch (v7x5_channel[m][i])
            {
                case 0:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[0][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[4][0] = v7x5_data[m][i];
                    }
                    break;
                case 1:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[0][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[4][1] = v7x5_data[m][i];
                    }
                    break;
                case 2:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[0][2] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[4][2] = v7x5_data[m][i];
                    }
                    break;
                case 3:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[0][3] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[4][3] = v7x5_data[m][i];
                    }
                    break;
                case 4:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[0][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_l[4][0] = v7x5_data[m][i];
                    }
                    break;
                case 5:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[0][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_r[4][0] = v7x5_data[m][i];
                    }
                    break;
                case 6:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[0][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_l[4][1] = v7x5_data[m][i];
                    }
                    break;
                case 7:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[0][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_r[4][1] = v7x5_data[m][i];
                    }
                    break;
                case 8:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[1][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[5][0] = v7x5_data[m][i];
                    }
                    break;
                case 9:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[1][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[5][1] = v7x5_data[m][i];
                    }
                    break;
                case 10:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[1][2] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[5][2] = v7x5_data[m][i];
                    }
                    break;
                case 11:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[1][3] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[5][3] = v7x5_data[m][i];
                    }
                    break;
                case 12:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[1][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_l[5][0] = v7x5_data[m][i];
                    }
                    break;
                case 13:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[1][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_r[5][0] = v7x5_data[m][i];
                    }
                    break;
                case 14:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[1][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_l[5][1] = v7x5_data[m][i];
                    }
                    break;
                case 15:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[1][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_r[5][1] = v7x5_data[m][i];
                    }
                    break;
                case 16:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[2][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[6][0] = v7x5_data[m][i];
                    }
                    break;
                case 17:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[2][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[6][1] = v7x5_data[m][i];
                    }
                    break;
                case 18:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[2][2] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[6][2] = v7x5_data[m][i];
                    }
                    break;
                case 19:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[2][3] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_a[6][3] = v7x5_data[m][i];
                    }
                    break;
                case 20:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[2][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_l[6][0] = v7x5_data[m][i];
                    }
                    break;
                case 21:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[2][0] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_r[6][0] = v7x5_data[m][i];
                    }
                    break;
                case 22:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[2][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_l[6][1] = v7x5_data[m][i];
                    }
                    break;
                case 23:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[2][1] = v7x5_data[m][i];
                    }
                    else if (v7x5_geo[m][i] == 8)
                    {
                        tpc_r[6][1] = v7x5_data[m][i];
                    }
                    break;
                case 24:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[3][0] = v7x5_data[m][i];
                    }
                    break;
                case 25:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[3][1] = v7x5_data[m][i];
                    }
                    break;
                case 26:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[3][2] = v7x5_data[m][i];
                    }
                    break;
                case 27:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_a[3][3] = v7x5_data[m][i];
                    }
                    break;
                case 28:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[3][0] = v7x5_data[m][i];
                    }
                    break;
                case 29:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[3][0] = v7x5_data[m][i];
                    }
                    break;
                case 30:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_l[3][1] = v7x5_data[m][i];
                    }
                    break;
                case 31:
                    if (v7x5_geo[m][i] == 12)
                    {
                        tpc_r[3][1] = v7x5_data[m][i];
                    }
                    break;
            }
        }
    }
 
    v1190_channel = fRawHit->Get_V1190_Channel();
    v1190_data = fRawHit->Get_V1190_Data();
    v1190_lot = fRawHit->Get_V1190_LoT();

    for (int i = 0; i < v1190_data.size(); i++)
    {   
        // select leads
        if (v1190_lot[i] == 0) // leads 0, trails 1
        {   
            if (v1190_lead_hits[v1190_channel[i]].size() < 64) v1190_lead_hits[v1190_channel[i]].emplace_back(v1190_data[i]);
        }
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

    bool checkrange1 = 0;
    bool checkrange2 = 0;
    bool checkrange3 = 0;
    bool checkrange4 = 0;
    bool checkrange5 = 0;

    // CEJ: the loops I built here are different to Go4 so I'm sure I caused some issue
    // I'm just not sure what yet...
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < tpc_lt[i][0].size(); j++)
        {
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
            else if (tpc_lt_s[i][1] > 0 && tpc_rt_s[i][1] > 0 && tpc_dt_s[i][j] > 0)
            {
                tpc_csum[i][j] = (tpc_lt_s[i][1] + tpc_rt_s[i][1] - 2 * tpc_dt_s[i][j]);
            }
            else
            {
                tpc_csum[i][j] = -9999999;
            }

            //all csums are currently -9999999 
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

    new ((*fCalArray)[fCalArray->GetEntriesFast()]) FrsTPCCalData(
        b_tpc_de,
        tpc_x,
        tpc_y,
        tpc_csum,
        b_tpc_xy,
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
        tpc_music43_x
    );

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
    memset(tpc_csum, 0, sizeof(tpc_csum));
    memset(b_tpc_csum, 0, sizeof(b_tpc_csum));
    memset(tpc_x, 0, sizeof(tpc_x));
    memset(tpc_y, 0, sizeof(tpc_y));
    memset(tpc_xraw, 0, sizeof(tpc_xraw));
    memset(tpc_yraw, 0, sizeof(tpc_yraw));
    memset(tpc_dx12, 0, sizeof(tpc_dx12));
    memset(b_tpc_xy, 0, sizeof(b_tpc_xy));
    fCalArray->Clear();
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
    for (int i = 0; i < 128; i++)
    {
        v1190_lead_hits[i].clear();
    }
    
    
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