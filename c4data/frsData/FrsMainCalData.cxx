#include "FrsMainCalData.h"

FrsMainCalData::FrsMainCalData()
    :   fWR_TS(0)
    ,   fTimeMs(0)
    ,   fIBinS(0)
    ,   fIBin100Ms(0)
    ,   fExtractionTime(0)
    ,   fIBinSClean(0)
    ,   fIBin100MsClean(0)
{
    for (int i = 0; i < 14; i++) fDe_array[i] = 0;
    for (int i = 0; i < 15; i++) fTdc_array[i] = std::vector<uint32_t>();
    for (int i = 0; i < 8; i++)
    {
        fmusic_t1[i] = 0;
        fmusic_t2[i] = 0;
    }
}

FrsMainCalData::FrsMainCalData(uint64_t WR_TS, uint32_t time_in_ms, uint32_t ibin_for_s, 
            uint32_t ibin_for_100ms, 
            const uint32_t* increase_scaler_temp,
            uint32_t extraction_time_ms, 
            uint32_t ibin_clean_for_s, 
            uint32_t ibin_clean_for_100ms,
            const uint32_t* de_array,
            const std::vector<uint32_t>* tdc_array,
            const uint32_t* music_t1,
            const uint32_t* music_t2)
    :   fWR_TS(WR_TS)
    ,   fTimeMs(time_in_ms)
    ,   fIBinS(ibin_for_s)
    ,   fIBin100Ms(ibin_for_100ms)
    ,   fExtractionTime(extraction_time_ms)
    ,   fIBinSClean(ibin_clean_for_s)
    ,   fIBin100MsClean(ibin_clean_for_100ms)
{
    for (int i = 0; i < 14; i++) fDe_array[i] = de_array[i];
    for (int i = 0; i < 15; i++) fTdc_array[i] = tdc_array[i];
    for (int i = 0; i < 8; i++)
    {
        fmusic_t1[i] = music_t1[i];
        fmusic_t2[i] = music_t2[i];
    }
    for (int i = 0; i < 32; i++) fIncreaseScalerTemp[i] = increase_scaler_temp[i];
}

FrsMainCalData::~FrsMainCalData()
{
}

ClassImp(FrsMainCalData)
