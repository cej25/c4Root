// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "TravMusData.h"
#include "TravMusReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_travmus.h"
}

TravMusReader::TravMusReader(EXT_STR_h101_travmus_onion* data, size_t offset)
    : c4Reader("TravMusReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , adcArray(new std::vector<TravMusAdcItem>)
    , tdcArray(new std::vector<TravMusTdcItem>)
{
}

TravMusReader::~TravMusReader() 
{ 
    c4LOG(info, "Destroyed TravMusReader properly.");
}

Bool_t TravMusReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    
    EXT_STR_h101_travmus_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_travmus, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    mgr->RegisterAny("TravMusAdcData", adcArray, !fOnline);
    mgr->RegisterAny("TravMusTdcData", tdcArray, !fOnline);
    
    adcArray->clear();
    tdcArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t TravMusReader::Read()
{
    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    uint64_t wr_t = (((uint64_t)fData->travmus_ts_t[3]) << 48) + (((uint64_t)fData->travmus_ts_t[2]) << 32) + (((uint64_t)fData->travmus_ts_t[1]) << 16) + (uint64_t)(fData->travmus_ts_t[0]);
    //c4LOG(info, " wr travMUS : " << wr_t);

    // loop through ADC or whatever
    int adc_hit_index = 0;
    for (uint32_t adc_chan_index = 0; adc_chan_index < fData->travmus_data_adcM; adc_chan_index++)
    {
        int current_adc_chan = fData->travmus_data_adcMI[adc_chan_index];
        int next_chan_start = fData->travmus_data_adcME[adc_chan_index];

        for (uint32_t j = adc_hit_index; j < next_chan_start; j++)
        {
            uint32_t channel = current_adc_chan;
            uint32_t adc_data = fData->travmus_data_adcv[j];

            auto & entry = adcArray->emplace_back();
            entry.SetAll(wr_t, channel-1, adc_data); // channel offset by 1 with ZSM
        }
        adc_hit_index = next_chan_start;
    }

    int tdc_hit_index = 0;
    for (uint32_t tdc_chan_index = 0; tdc_chan_index < fData->travmus_data_tdcM; tdc_chan_index++)
    {
        int current_tdc_chan = fData->travmus_data_tdcMI[tdc_chan_index];
        int next_chan_start = fData->travmus_data_tdcME[tdc_chan_index];

        for (uint32_t j = tdc_hit_index; j < next_chan_start; j++)
        {
            uint32_t channel = current_tdc_chan;
            uint32_t tdc_data = fData->travmus_data_tdcv[j];

            auto & entry = tdcArray->emplace_back();
            entry.SetAll(channel-1, tdc_data); // channel offset by 1 with ZSM
        }
        tdc_hit_index = next_chan_start;
    }

    return kTRUE;

}

void TravMusReader::ZeroArrays()
{

}

void TravMusReader::ClearVectors()
{
    adcArray->clear();
    tdcArray->clear();
}

void TravMusReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(TravMusReader);
