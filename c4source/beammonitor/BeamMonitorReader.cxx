/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "BeamMonitorData.h"
#include "BeamMonitorReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_beammonitor.h"
}

#define UINT_MAX 4294967295

BeamMonitorReader::BeamMonitorReader(EXT_STR_h101_beammonitor_onion* data, size_t offset)
    :   c4Reader("BeamMonitorReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   s2array(new std::vector<BeamMonitorItem>)
    ,   s4array(new std::vector<BeamMonitorItem>)
{
}

BeamMonitorReader::~BeamMonitorReader() 
{ 
    delete s2array;
    delete s4array;
}

Bool_t BeamMonitorReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_beammonitor_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_beammonitor, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->RegisterAny("BeamMonitorS2Data", s2array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BeamMonitorS4Data", s4array, !fOnline);
    s2array->clear();
    s4array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BeamMonitorReader::Read()
{
    c4LOG(debug2, "Event Data");

    uint32_t ts_prev_S2 = 0;
    uint32_t ts_curr_S2 = 0;
    uint32_t ts_diff_S2 = 0;
    uint32_t ts_first_S2 = 1;

    for (int hit = 0; hit < fData->beammonitor_s2_dataS2; hit++)
    {   
        ts_curr_S2 = fData->beammonitor_s2_dataS2v[hit];
        ts_diff_S2 = ts_curr_S2 - ts_prev_S2;
        if (ts_diff_S2 < 0)
        {
            ts_diff_S2 = ts_diff_S2 + UINT_MAX;

            if (ts_diff_S2 > pow(10,8))
            {
                ts_diff_S2 = 0;
            }
        }
        if (ts_first_S2 == 1)
        {
            ts_first_S2 = 0;
        }
        else
        {
            auto & entry = s2array->emplace_back();
            entry.SetAll(ts_diff_S2);

        }
        
        ts_prev_S2 = ts_curr_S2;
    }

    uint32_t ts_prev_S4 = 0;
    uint32_t ts_curr_S4 = 0;
    uint32_t ts_diff_S4 = 0;
    uint32_t ts_first_S4 = 1;

    for (int hit = 0; hit < fData->beammonitor_s4_dataS4; hit++)
    {   
        ts_curr_S4 = fData->beammonitor_s4_dataS4v[hit];
        ts_diff_S4 = ts_curr_S4 - ts_prev_S4;
        if (ts_diff_S4 < 0)
        {
            ts_diff_S4 = ts_diff_S4 + UINT_MAX;

            if (ts_diff_S4 > pow(10,8))
            {
                ts_diff_S4 = 0;
            }
        }
        if (ts_first_S4 == 1)
        {
            ts_first_S4 = 0;
        }
        else
        {
            auto & entry = s4array->emplace_back();
            entry.SetAll(ts_diff_S4);
        }
        
        ts_prev_S4 = ts_curr_S4;
    }

    fNEvent += 1;
    return kTRUE;
}

void BeamMonitorReader::Reset()
{
    s2array->clear();
    s4array->clear();
}

ClassImp(BeamMonitorReader);
