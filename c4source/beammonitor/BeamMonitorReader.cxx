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
    #include "ext_h101_bm.h"
}

#define UINT_MAX 4294967295

BeamMonitorReader::BeamMonitorReader(EXT_STR_h101_BM_onion* data, size_t offset)
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

    EXT_STR_h101_BM_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_BM, 0);

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
    c4LOG(debug1, "Event Data");

    // read / manipulate data.
    // S4 for now -- deal with S2 later.
    UInt_t ts_prev_S4 = 0;
    UInt_t ts_curr_S4 = 0;
    UInt_t ts_diff_S4 = 0;
    UInt_t ts_first_S4 = 1;
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
            new ((*fArray)[fArray->GetEntriesFast()]) BeamMonitorData(0, ts_diff_S4);
        }

        ts_prev_S4 = ts_curr_S4;

    }

    fNEvent += 1;
    return kTRUE;
}

void BeamMonitorReader::Reset()
{
    fArray->Clear();
}

ClassImp(BeamMonitorReader);