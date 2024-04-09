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
    : c4Reader("BeamMonitorReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("BeamMonitorData"))
{
}

BeamMonitorReader::~BeamMonitorReader() { delete fArray; }

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
    FairRootManager::Instance()->Register("BeamMonitorData", "Beam Monitor Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BeamMonitorReader::Read()
{
    c4LOG(debug2, "Event Data");

    BeamMonitorData* BeamMonitorHit = new BeamMonitorData();

    // CEJ doing S2 now, not sure if identical or small differences
    uint32_t ts_prev_S2 = 0;
    uint32_t ts_curr_S2 = 0;
    uint32_t ts_diff_S2 = 0;
    uint32_t ts_first_S2 = 1;

    std::vector<uint32_t> dtS2;

    for (int hit = 0; hit < fData->beammonitor_dataS2; hit++)
    {   
        ts_curr_S2 = fData->beammonitor_dataS2v[hit];
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
            dtS2.emplace_back(ts_diff_S2);
        }
        
        ts_prev_S2 = ts_curr_S2;
    }

    uint32_t ts_prev_S4 = 0;
    uint32_t ts_curr_S4 = 0;
    uint32_t ts_diff_S4 = 0;
    uint32_t ts_first_S4 = 1;

    std::vector<uint32_t> dtS4;

    for (int hit = 0; hit < fData->beammonitor_dataS4; hit++)
    {   
        ts_curr_S4 = fData->beammonitor_dataS4v[hit];
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
            dtS4.emplace_back(ts_diff_S4);
        }
        
        ts_prev_S4 = ts_curr_S4;
    }
    
    BeamMonitorHit->Set_S2_data(dtS2);
    BeamMonitorHit->Set_S4_data(dtS4);

    new ((*fArray)[fArray->GetEntriesFast()]) BeamMonitorData(*BeamMonitorHit);

    fNEvent += 1;
    return kTRUE;
}

void BeamMonitorReader::Reset()
{
    fArray->Clear();
}

ClassImp(BeamMonitorReader);