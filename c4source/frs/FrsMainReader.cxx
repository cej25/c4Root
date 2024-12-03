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
    , v830array(new std::vector<FrsMainV830Item>)
    , v792array(new std::vector<FrsMainV792Item>)
    , v1290array(new std::vector<FrsMainV1290Item>)
{
}

FrsMainReader::~FrsMainReader() 
{ 
    c4LOG(info, "Destroyed FrsMainReader properly.");
}

Bool_t FrsMainReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    
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

    FairRootManager::Instance()->RegisterAny("FrsMainV830Data", v830array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsMainV792Data", v792array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsMainV1290Data", v1290array, !fOnline);

    v1290array->clear();
    v792array->clear();
    v830array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsMainReader::Read()
{
    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    // get spill on and spill off
    int spill_on = fData->frsmain_spill_on_spillon;
    int spill_off = fData->frsmain_spill_off_spilloff;

    if (spill_on == 1) spill_flag = true;
    if (spill_off == 1) spill_flag = false;

    header->SetSpillFlag(spill_flag);

    // V830
    for (uint32_t i = 0; i < fData->frsmain_data_v830_n; i++)
    {       
        uint32_t index = fData->frsmain_data_v830_nI[i];
        uint32_t scaler = fData->frsmain_data_v830_data[i];
        auto & entry = v830array->emplace_back();
        entry.SetAll(index, scaler);
    }

    // V792
    uint32_t geo = fData->frsmain_data_v792_geo;
    int hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->frsmain_data_v792_nM; channel_index++)
    {
        int current_channel = fData->frsmain_data_v792_nMI[channel_index];
        int next_channel_start = fData->frsmain_data_v792_nME[channel_index];

        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {
            uint32_t channel = current_channel - 1; // also needs a -1 as below.
            uint32_t data = fData->frsmain_data_v792_data[j];

            auto & entry = v792array->emplace_back();
            entry.SetAll(channel, data, geo);
        }
        hit_index = next_channel_start;
    }

    // V1290
    hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->frsmain_data_v1290_nM; channel_index++)
    {   
        int current_channel = fData->frsmain_data_v1290_nMI[channel_index];
        int next_channel_start = fData->frsmain_data_v1290_nME[channel_index];
        
        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {
            uint32_t channel = current_channel - 1;
            uint32_t data = fData->frsmain_data_v1290_data[j];
            uint32_t lot = fData->frsmain_data_v1290_leadOrTrailv[j];
            
            auto & entry = v1290array->emplace_back();
            entry.SetAll(channel, data, lot);
        }
        hit_index = next_channel_start;
    }

    return kTRUE;

}

void FrsMainReader::ZeroArrays()
{
    
}

void FrsMainReader::ClearVectors()
{
    v830array->clear();
    v792array->clear();
    v1290array->clear();
}

void FrsMainReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsMainReader);
