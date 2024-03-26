// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsMainData.h"
#include "FrsMainReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frsmain.h"
}

FrsMainReader::FrsMainReader(EXT_STR_h101_frsmain_onion* data, size_t offset)
    : c4Reader("FrsMainReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FrsMainData"))
{
}

FrsMainReader::~FrsMainReader() 
{ 
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsMainReader properly.");
}

Bool_t FrsMainReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");
    
    EXT_STR_h101_frsmain_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsmain, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    FairRootManager::Instance()->Register("FrsMainData", "FRS Main Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FrsMainReader init complete.");

    return kTRUE;
}

Bool_t FrsMainReader::Read()
{
    c4LOG(debug1, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    // get spill on and spill off
    int spill_on = fData->frsmain_spill_on_spillon;
    int spill_off = fData->frsmain_spill_off_spilloff;

    if (spill_on == 1) spill_flag = true;
    if (spill_off == 1) spill_flag = false;

    std::cout << "spill_flag: " << spill_flag << std::endl;

    header->SetSpillFlag(spill_flag);

    // V830
    scalers_n = fData->frsmain_data_v830_n;
    for (uint32_t i = 0; i < scalers_n; i++)
    {   
        scalers_index.emplace_back(fData->frsmain_data_v830_nI[i]);
        scalers_main.emplace_back(fData->frsmain_data_v830_data[i]);
    }

    // V792
    v792_geo = fData->frsmain_data_v792_geo;
    int hit_index_v792 = 0;
    for (uint32_t channel_index = 0; channel_index < fData->frsmain_data_v792_nM; channel_index++){
        int current_channel_v792 = fData->frsmain_data_v792_nMI[channel_index];
        int next_channel_start_v792 = fData->frsmain_data_v792_nME[channel_index];
        for (uint32_t j = hit_index_v792; j<next_channel_start_v792; j++){
            v792_channel.emplace_back(current_channel_v792);
            v792_data.emplace_back(fData->frsmain_data_v792_data[j]);
        }
        hit_index_v792 = next_channel_start_v792;
    }

    // V1290
    int hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->frsmain_data_v1290_nM; channel_index++)
    {   
        int current_channel = fData->frsmain_data_v1290_nMI[channel_index]; // channel to read now!
        int next_channel_start = fData->frsmain_data_v1290_nME[channel_index]; // we read this channel until we hit this index
        
        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {
            //c4LOG(info,Form("current channel = %i, next channel start = %i, channels fired = %i, data = %i",fData->frsmain_data_v1290_leadOrTrailMI[channel_index], fData->frsmain_data_v1290_leadOrTrailME[channel_index], fData->frsmain_data_v1290_nM, fData->frsmain_data_v1290_leadOrTrailv[j]));
            //c4LOG(info,Form("current channel = %i, next channel start = %i, channels fired = %i, data = %i",current_channel, next_channel_start, fData->frsmain_data_v1290_nM, fData->frsmain_data_v1290_data[j]));
            v1290_channel.emplace_back(current_channel);
            v1290_data.emplace_back(fData->frsmain_data_v1290_data[j]);
            v1290_lot.emplace_back(fData->frsmain_data_v1290_leadOrTrailv[j]);
        }
        hit_index = next_channel_start;
    }

    // CEJ: should scalers not write regardless of this?
    if (v1290_channel.size() > 0 || v792_channel.size() > 0)
    {
        new ((*fArray)[fArray->GetEntriesFast()]) FrsMainData(
            //wr_t,
            scalers_n,
            scalers_index,
            scalers_main,
            v792_geo,
            v792_channel,
            v792_data,
            v1290_channel,
            v1290_data,
            v1290_lot);
        
        fNEvent += 1;
    }
    return kTRUE;

}

void FrsMainReader::ZeroArrays()
{
    fArray->Clear();
}

void FrsMainReader::ClearVectors()
{
    scalers_index.clear();
    scalers_main.clear();
    v792_channel.clear();
    v792_data.clear();
    v1290_channel.clear();
    v1290_data.clear();
    v1290_lot.clear();
}

void FrsMainReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsMainReader);