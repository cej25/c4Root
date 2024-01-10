// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsData.h"
#include "FrsReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frs.h"
}

// we'll go with FRS for FRSMAIN for now
FrsReader::FrsReader(EXT_STR_h101_FRS_onion* data, size_t offset)
    : c4Reader("FrsReader") // "MainReader" ?
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FrsData"))
   // , v830Array(new std::vector<FrsUnpackV830>)
   // , v7X5Array(new std::vector<FrsUnpackV7X5>)
{
}

FrsReader::~FrsReader() 
{ 
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsReader properly.");
}

Bool_t FrsReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");
    
    EXT_STR_h101_FRS_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_FRS, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("FrsData", "FRS Main Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FrsReader init complete.");

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    // whiterabbit timestamp - includes 20202020 events...
    wr_t = (((uint64_t)fData->frsmain_wr_t[3]) << 48) + (((uint64_t)fData->frsmain_wr_t[2]) << 32) + (((uint64_t)fData->frsmain_wr_t[1]) << 16) + (uint64_t)(fData->frsmain_wr_t[0]);

    // V830
    scalers_n = fData->frsmain_data_v830_n;
    for (uint32_t i = 0; i < scalers_n; i++)
    {   
        scalers_index.emplace_back(fData->frsmain_data_v830_nI[i]);
        scalers_main.emplace_back(fData->frsmain_data_v830_data[fData->frsmain_data_v830_nI[i]]);
    }

    // V792
    v792_geo = fData->frsmain_data_v792_geo;

    uint32_t chn_first_hit = 0;
    uint32_t next_chn_first_hit, hits;

    // loop through number of channels with hits
    for (uint32_t i = 0; i < fData->frsmain_data_v792_nM; i++)
    {   
        next_chn_first_hit = fData->frsmain_data_v792_nME[i];
        hits = next_chn_first_hit - chn_first_hit;
        for (uint32_t j = 0; j < hits; j++)
        {   
            // 32 depends on array size in .spec
            v792_channel.emplace_back(fData->frsmain_data_v792_nMI[i]);
            v792_data.emplace_back(fData->frsmain_data_v792_data[i * 32 + j]);
        }

        chn_first_hit = next_chn_first_hit;

    }

    chn_first_hit = 0;

    // V1290
    for (uint32_t i = 0; i < fData->frsmain_data_v1290_nM; i++)
    {   
        next_chn_first_hit = fData->frsmain_data_v1290_nME[i];
        hits = next_chn_first_hit - chn_first_hit;

        for (uint32_t j = 0; j < hits; j++)
        {
            // 128 depends on size of array in .spec file
            v1290_channel.emplace_back(fData->frsmain_data_v1290_nMI[i]);
            v1290_data.emplace_back(fData->frsmain_data_v1290_data[i * 128 + j]);
            v1290_lot.emplace_back(fData->frsmain_data_v1290_leadOrTrailv[i * 128 + j]);
        }

        chn_first_hit = next_chn_first_hit;
    }

    new ((*fArray)[fArray->GetEntriesFast()]) FrsData(
        wr_t,
        scalers_n,
        &scalers_index,
        &scalers_main,
        v792_geo,
        &v792_channel,
        &v792_data,
        &v1290_channel,
        &v1290_data,
        &v1290_lot);
    

    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    scalers_index.clear();
    scalers_main.clear();
    v792_channel.clear();
    v792_data.clear();
    v1290_channel.clear();
    v1290_data.clear();
    v1290_lot.clear();
    fArray->Clear();
}

ClassImp(FrsReader);