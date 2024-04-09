#include "AidaReader.h"

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "AidaData.h"
#include "c4Logger.h"

#include <chrono>

// ucesb
#include "ext_data_struct_info.hh"
extern "C"
{
#include "ext_h101_aida.h"
#include "ext_data_client.h"
}

AidaReader::AidaReader(EXT_STR_h101_aida_onion* data, size_t offset)
    : c4Reader("AidaReader"),
      fNEvent(0),
      fData(data),
      fOffset(offset),
      fAdcOnline(false),
      fFlowScalerOnline(false),
      adcArray(new std::vector<AidaUnpackAdcItem>),
      flowArray(new std::vector<AidaUnpackFlowItem>),
      scalerArray(new std::vector<AidaUnpackScalerItem>)
{
}

AidaReader::~AidaReader()
{
    delete adcArray;
    delete flowArray;
    delete scalerArray;
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvent << " microseconds.");
}

Bool_t AidaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_aida_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_aida, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register vector(?) of data here
    FairRootManager::Instance()->RegisterAny("AidaAdcData", adcArray, !fAdcOnline);
    FairRootManager::Instance()->RegisterAny("AidaFlowData", flowArray, !fFlowScalerOnline);
    FairRootManager::Instance()->RegisterAny("AidaScalerData", scalerArray, !fFlowScalerOnline);

    return kTRUE;
}

Bool_t AidaReader::Read()
{
    auto start = std::chrono::high_resolution_clock::now();
    // fData is valid here, shove it into the vector
    // Clean vectors
    adcArray->clear();
    flowArray->clear();
    scalerArray->clear();
    
    if (!fData) return kTRUE;

    // ADC items
    for (size_t i = 0; i < fData->aida_data_adc; i++)
    {
        auto& entry = adcArray->emplace_back();
        uint64_t rt = fData->aida_data_adc_timestamp_raw_lo[i] | ((uint64_t)fData->aida_data_adc_timestamp_raw_hi[i] << 32);
        uint64_t st = fData->aida_data_adc_timestamp_slow_lo[i] | ((uint64_t)fData->aida_data_adc_timestamp_slow_hi[i] << 32);
        uint64_t ft = fData->aida_data_adc_timestamp_fast_lo[i] | ((uint64_t)fData->aida_data_adc_timestamp_fast_hi[i] << 32);
        entry.SetAll(rt, st, ft, fData->aida_data_adc_fee[i], fData->aida_data_adc_channel[i], fData->aida_data_adc_range[i], fData->aida_data_adcv[i]);
    }

    // Flow items
    for (size_t i = 0; i < fData->aida_data_flow; i++)
    {
        auto& entry = flowArray->emplace_back();
        uint64_t t = fData->aida_data_flow_timestamp_lo[i] | ((uint64_t)fData->aida_data_flow_timestamp_hi[i] << 32);
        int f = fData->aida_data_flow_fee[i];
        bool p = fData->aida_data_flow_paused[i] != 0;
        entry.SetAll(t, f, p);
    }

    // Scaler items
    for (size_t i = 0; i < fData->aida_data_scaler; i++)
    {
        auto& entry = scalerArray->emplace_back();
        uint64_t t = fData->aida_data_scaler_timestamp_lo[i] | ((uint64_t)fData->aida_data_scaler_timestamp_hi[i] << 32);
        uint64_t v = fData->aida_data_scaler_value_lo[i] | ((uint64_t)fData->aida_data_scaler_value_hi[i] << 32);
        int f = fData->aida_data_scaler_fee[i];
        entry.SetAll(t, v, f);
    }

    fNEvent++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    return kTRUE;
}

void AidaReader::Reset()
{
    // Clear the vector
    adcArray->clear();
    flowArray->clear();
    scalerArray->clear();
}

ClassImp(AidaReader);

