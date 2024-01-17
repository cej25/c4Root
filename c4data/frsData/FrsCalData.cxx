// FairRoot
#include "FrsCalData.h"

FrsCalData::FrsCalData()
    :   fWR_TS(0)
    ,   fTimeMs(0)
    ,   fIBinS(0)
    ,   fIBin100Ms(0)
    //,   fIncreaseScalerTemp(0)
    ,   fExtractionTime(0)
    ,   fIBinSClean(0)
    ,   fIBin100MsClean(0)
    //,   fDe_array(0)
    //,   fTdc_array(0)
    //,   fMusicT1(0)
    //,   fMusicT2(0)
{
}

FrsCalData::FrsCalData(uint64_t WR_TS, uint32_t time_in_ms, uint32_t ibin_for_s, 
            uint32_t ibin_for_100ms, 
           // uint32_t increase_scaler_temp[32], 
            uint32_t extraction_time_ms, 
            uint32_t ibin_clean_for_s, 
            uint32_t ibin_clean_for_100ms)//,
            // V792
            // mapped array?
           // uint32_t de_array[14],
            // V1290
            //std::vector<uint32_t> tdc_array[15])//,
            //uint32_t music_t1[8],
            //uint32_t music_t2[8])
    :   fWR_TS(WR_TS)
    ,   fTimeMs(time_in_ms)
    ,   fIBinS(ibin_for_s)
    ,   fIBin100Ms(ibin_for_100ms)
    //,   fIncreaseScalerTemp(increase_scaler_temp)
    ,   fExtractionTime(extraction_time_ms)
    ,   fIBinSClean(ibin_clean_for_s)
    ,   fIBin100MsClean(ibin_clean_for_100ms)
    //,   fDe_array(de_array)
    //,   fTdc_array(tdc_array)
    //,   fMusicT1(music_t1)
    //,   fMusicT2(music_t2)
{
}

ClassImp(FrsCalData)
