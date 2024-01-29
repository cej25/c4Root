// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsUserRaw2Cal.h"
#include "FrsUserData.h"
#include "FrsUserCalData.h"
#include "TFRSParameter.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsUserRaw2Cal::FrsUserRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsUserData"))
    ,   fCalArray(new TClonesArray("FrsUserCalData"))
{
}

FrsUserRaw2Cal::FrsUserRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsUserData"))
    ,   fCalArray(new TClonesArray("FrsUserCalData"))
{
}

FrsUserRaw2Cal::~FrsUserRaw2Cal()
{
    c4LOG(info, "Deleting FrsUserRaw2Cal task");
    if (fRawArray) delete fRawArray;
    if (fCalArray) delete fCalArray;
}



InitStatus FrsUserRaw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsUserData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of UserData not found");

    FairRootManager::Instance()->Register("FrsUserCalData", "FRS User Cal Data", fCalArray, !fOnline);

    fRawArray->Clear();
    fCalArray->Clear();

    return kSUCCESS;
}

void FrsUserRaw2Cal::Exec(Option_t* option)
{

    // check there is actual data from module(s)
    int mult = fRawArray->GetEntriesFast();
    if (!mult) return;

    // do we have to sort out the scalers here? seems weird. do we have to merge user and frs somehow??

    fRawHit = (FrsUserData*)fRawArray->At(mult-1);

    v7x5_geo = fRawHit->Get_v7x5_geo();
    v7x5_channel = fRawHit->Get_v7x5_channel();
    v7x5_data = fRawHit->Get_v7x5_data();

    // dt_array time - geo12
    for (int m = 0; m < 4; m++) // loop over 4x v7x5
    {
        for (int i = 0; v7x5_data[m].size(); i++)
        {
            switch (v7x5_channel[m][i])
            {
                case 0:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[0] = v7x5_data[m][i]; // dt_21l_21r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[0] = v7x5_data[m][i]; 
                    }
                    break;
                case 1:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[1] = v7x5_data[m][i]; // dt_41l_41r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[1] = v7x5_data[m][i]; 
                    }
                    break;
                case 2:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[2] = v7x5_data[m][i]; // dt_42l_42r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[2] = v7x5_data[m][i]; 
                    }
                    break;
                case 3:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[3] = v7x5_data[m][i]; // dt_43l_43r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[3] = v7x5_data[m][i]; 
                    }
                    break;
                case 4:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[4] = v7x5_data[m][i]; // dt_81l_81r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[4] = v7x5_data[m][i]; 
                    }
                    break;
                case 5:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[5] = v7x5_data[m][i]; // dt_21l_41l
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[5] = v7x5_data[m][i]; 
                    }
                    break;
                case 6:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[6] = v7x5_data[m][i]; // dt_21r_41r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[6] = v7x5_data[m][i]; 
                    }
                    break;
                case 7:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[7] = v7x5_data[m][i]; // dt_42r_21r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e1[7] = v7x5_data[m][i]; 
                    }
                    break;
                case 8:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[8] = v7x5_data[m][i]; // dt_42l_21l
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[0] = v7x5_data[m][i]; 
                    }
                    break;
                case 9:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[9] = v7x5_data[m][i]; // dt_21l_81l
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[1] = v7x5_data[m][i]; 
                    }
                    break;
                case 10:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[10] = v7x5_data[m][i]; // dt_21r_81r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[2] = v7x5_data[m][i]; 
                    }
                    break;
                case 11:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[11] = v7x5_data[m][i]; // dt_22l_22r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[3] = v7x5_data[m][i]; 
                    }
                    break;
                case 12:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[12] = v7x5_data[m][i]; // dt_22l_41l
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[4] = v7x5_data[m][i]; 
                    }
                    break;
                case 13:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[13] = v7x5_data[m][i]; // dt_22r_41r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[5] = v7x5_data[m][i]; 
                    }
                    break;
                case 14:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[14] = v7x5_data[m][i]; // dt_22l_81l
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[6] = v7x5_data[m][i]; 
                    }
                    break;
                case 15:
                    if (v7x5_geo[m][i] == 12)
                    {
                        dt_array[15] = v7x5_data[m][i]; // dt_22r_81r
                    }
                    else if (v7x5_geo[m][i] == 10)
                    {
                        music_e2[7] = v7x5_data[m][i]; 
                    }
                    break;
            }
        }
    }
    
    new ((*fCalArray)[fCalArray->GetEntriesFast()]) FrsUserCalData(
        // v830 scaler stuff?
        dt_array,
        music_e1,
        music_e2
    );

    fNEvents++;

}

void FrsUserRaw2Cal::FinishEvent()
{
    // clears
}

void FrsUserRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.", fNEvents));
}

ClassImp(FrsUserRaw2Cal)