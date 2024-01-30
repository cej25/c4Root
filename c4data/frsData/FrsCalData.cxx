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
    //,   fDe_array(new uint32_t[14])
   //,   fTdc_array(0)
   // ,   fMusicT1(0)
   // ,   fMusicT2(0)
{
    //fDe_array = new uint32_t[15];
}

FrsCalData::FrsCalData(uint64_t WR_TS, uint32_t time_in_ms, uint32_t ibin_for_s, 
            uint32_t ibin_for_100ms, 
            const uint32_t* increase_scaler_temp,
            uint32_t extraction_time_ms, 
            uint32_t ibin_clean_for_s, 
            uint32_t ibin_clean_for_100ms,
            // V792
            // mapped array?
            const uint32_t* de_array,
            // V1290
            const std::vector<uint32_t>* tdc_array,
            const uint32_t* music_t1,
            const uint32_t* music_t2)
    :   fWR_TS(WR_TS)
    ,   fTimeMs(time_in_ms)
    ,   fIBinS(ibin_for_s)
    ,   fIBin100Ms(ibin_for_100ms)
    //,   fIncreaseScalerTemp(increase_scaler_temp)
    ,   fExtractionTime(extraction_time_ms)
    ,   fIBinSClean(ibin_clean_for_s)
    ,   fIBin100MsClean(ibin_clean_for_100ms)
    //,   fDe_array(de_array)
   // ,   fTdc_array(tdc_array)
    //,   fMusicT1(music_t1)
    //,   fMusicT2(music_t2)
{
    //fDe_array = new uint32_t[15];
    for (int i = 0; i < 14; i++) fDe_array[i] = de_array[i];
    for (int i = 0; i < 15; i++) fTdc_array[i] = tdc_array[i];
    for (int i = 0; i < 8; i++)
    {
        fMusicT1[i] = music_t1[i];
        fMusicT2[i] = music_t2[i];
    }
    for (int i = 0; i < 32; i++) fIncreaseScalerTemp[i] = increase_scaler_temp[i];
    //fDe_array = de_array;
}

FrsCalData::~FrsCalData()
{
    /*delete fIncreaseScalerTemp;
    delete fDe_array;
    delete fMusicT1;
    delete fMusicT2;*/
}

ClassImp(FrsCalData)
