#include "c4AidaReader.h"

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "AidaData.h"
#include "c4Logger.h"

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
      fOnline(false),
      adcArray(new std::vector<AidaUnpackAdcItem>)
{
}

AidaReader::~AidaReader()
{
    delete adcArray;
}

Bool_t AidaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    EXT_STR_h101_AIDA_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_aida, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register vector(?) of data here
    FairRootManager::Instance()->RegisterAny("AidaAdcData", adcArray, !fOnline);
    
    return kTRUE;
}

Bool_t AidaReader::Read()
{
    // fData is valid here, shove it into the vector
    //
    for (size_t i = 0; i < fData->aida_data_adc; i++)
    {
        auto& entry = adcArray->emplace_back();
        uint64_t rt = fData->aida_data_adc_timestamp_raw_lo[i] | ((uint64_t)fData->aida_data_adc_timestamp_raw_hi[i] << 32);
        uint64_t st = fData->aida_data_adc_timestamp_slow_lo[i] | ((uint64_t)fData->aida_data_adc_timestamp_slow_hi[i] << 32);
        uint64_t ft = fData->aida_data_adc_timestamp_fast_lo[i] | ((uint64_t)fData->aida_data_adc_timestamp_fast_hi[i] << 32);
        entry.SetAll(rt, st, ft, fData->aida_data_adc_fee[i], fData->aida_data_adc_channel[i], fData->aida_data_adc_range[i], fData->aida_data_adcv[i]);
    }
    return kTRUE;
}

void AidaReader::Reset()
{
    // Clear the vector
    adcArray->clear();
}

ClassImp(AidaReader);

