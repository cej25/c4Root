#include "FairLogger.h"
#include "FairRootManager.h"

#include "LisaData.h"
#include "LisaTraceData.h"
#include "LisaReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_lisa.h"
}

// maybe no longer needed to define
#define TRACE_CHANNELS 16

LisaReader::LisaReader(EXT_STR_h101_lisa_onion* data, size_t offset)
    : c4Reader("LisaReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("LisaData"))
    , fTraceArray(new TClonesArray("LisaTraceData"))
{
}

LisaReader::~LisaReader() 
{ 
    delete fArray;
    delete fTraceArray;
}

Bool_t LisaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_lisa_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_lisa, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // register output array in a tree
    // CALUM: I set this up originally having two branches
    // 1. one for energy, channel ids etc
    // 2. one for trace data
    // you don't need to do that, necessarily. 
    FairRootManager::Instance()->Register("LisaData", "LISA Data", fArray, !fOnline);
    FairRootManager::Instance()->Register("LisaTraceData", "LISA Trace Data", fTraceArray, !fOnline);
    fArray->Clear();
    fTraceArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t LisaReader::Read()
{
    // Reading is done in here on a per-event basis!
    
    return kTRUE;
}

// You must clear any arrays and vectors you use or things will get weird
void LisaReader::ZeroArrays()
{   

}

void LisaReader::ClearVectors()
{

}

void LisaReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(LisaReader);
