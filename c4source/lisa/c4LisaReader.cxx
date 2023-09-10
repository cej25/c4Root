#include "FairLogger.h"
#include "FairRootManager.h"

#include "c4LisaData.h"
#include "c4LisaTraceData.h"
#include "c4LisaReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_lisa.h"
}

c4LisaReader::c4LisaReader(EXT_STR_h101_LISA_onion* data, size_t offset)
    : c4Reader("c4LisaReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("c4LisaData"))
    , fTraceArray(new TClonesArray("c4LisaTraceData"))
{
}

c4LisaReader::~c4LisaReader() 
{ 
    delete fArray;
    delete fTraceArray;
}

Bool_t c4LisaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_LISA_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_LISA, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // register output array in a tree
    FairRootManager::Instance()->Register("LisaData", "LISA Data", fArray, !fOnline);
    FairRootManager::Instance()->Register("LisaTraceData", "LISA Trace Data", fTraceArray, !fOnline);
    fArray->Clear();
    fTraceArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t c4LisaReader::Read()
{
    c4LOG(debug1, "Event data");

    uint32_t ts_lo, ts_hi;

    // Read 16 channels channels
    for (Int_t t = 0; t < 16; t++)
    {   
        // we should avoid zeros where we can, i.e. only fill from active channels.
        // or borrow some __cool__ ucesb zero_suppression. Otherwise..works..
        // janky until the structure file can be fixed. Mapping?
        if (t == 0)
        {
            ts_lo = fData->trace_data_fts_lo_0[0];
            ts_hi = fData->trace_data_fts_hi_0[0];
        }
        else
        {
            ts_lo = 0;
            ts_hi = 0;
        }

        new ((*fArray)[fArray->GetEntriesFast()]) c4LisaData(fData->trace_data_fboard[0],
                                                         fData->trace_data_fchn[0],
                                                         fData->trace_data_fen_0[0],
                                                         ts_lo,
                                                         ts_hi);

        for (Int_t e = 0; e < fData->trace_trace_ftrace[t]._; e++)
        {
            new ((*fTraceArray)[fTraceArray->GetEntriesFast()]) c4LisaTraceData(fData->trace_trace_ftrace[t].v[e]);
        }
    }
    
    fNEvent += 1;
    return kTRUE;
}

void c4LisaReader::Reset()
{
    fArray->Clear();
    fTraceArray->Clear();
}

ClassImp(c4LisaReader);
