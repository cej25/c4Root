// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "GermaniumFebexData.h"
#include "GermaniumReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_ge_febex.h"
}

GermaniumReader::GermaniumReader(EXT_STR_h101_GE_FEBEX_onion* data, size_t offset)
    : c4Reader("GermaniumReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("GermaniumFebexData"))
{
}

GermaniumReader::~GermaniumReader() { delete fArray; }

Bool_t GermaniumReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_GE_FEBEX_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_GE_FEBEX, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("GermaniumFebexData", "Germanium Febex Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t GermaniumReader::Read()
{
    c4LOG(debug1, "Event Data");

    // GE_MAX_HITS
    // not entirely sure this is going to work. really need to work it all out....
    for (int det = 0; det < 28; det++)
    {
        new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(det,
                                                                       fData->Sum_Time_lo[det],
                                                                       fData->Sum_Time_hi[det],
                                                                       fData->Hit_Pattern[det],
                                                                       fData->Chan_Energy[det],
                                                                       fData->Chan_Time_lo[det],
                                                                       fData->Chan_Time_hi[det],
                                                                       fData->Chan_CF_lo[det],
                                                                       fData->Chan_CF_hi[det],
                                                                       fData->Pileup[det],
                                                                       fData->Overflow[det],
                                                                       fData->det_ids[det],
                                                                       fData->crystal_ids[det]);
    }


    fNEvent += 1;
    return kTRUE;
}

void GermaniumReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(GermaniumReader);
