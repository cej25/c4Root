#include "FrsMainCalData.h"

FrsMainCalData::FrsMainCalData()
    :   fScalers_N(0)
    ,   fScalers_Index(0)
    ,   fV830_Scalers(0)
{
    for (int i = 0; i < 14; i++) fDe_array[i] = 0;
    for (int i = 0; i < 15; i++) fTdc_array[i] = std::vector<uint32_t>();
    for (int i = 0; i < 8; i++)
    {
        fmusic_t1[i] = 0;
        fmusic_t2[i] = 0;
    }
}

FrsMainCalData::FrsMainCalData( 
            uint32_t Scalers_N, 
            std::vector<uint32_t> Scalers_Index, 
            std::vector<uint32_t> V830_Scalers,
            const uint32_t* de_array,
            const std::vector<uint32_t>* tdc_array,
            const uint32_t* music_t1,
            const uint32_t* music_t2)
    :   fScalers_N(Scalers_N)
    ,   fScalers_Index(Scalers_Index)
    ,   fV830_Scalers(V830_Scalers)
{
    for (int i = 0; i < 14; i++) fDe_array[i] = de_array[i];
    for (int i = 0; i < 15; i++) fTdc_array[i] = tdc_array[i];
    for (int i = 0; i < 8; i++)
    {
        fmusic_t1[i] = music_t1[i];
        fmusic_t2[i] = music_t2[i];
    }
    /*for (int i = 0; i < 32; i++) fIncreaseScalerTemp[i] = increase_scaler_temp[i];*/
}

FrsMainCalData::~FrsMainCalData()
{
}

ClassImp(FrsMainCalData)
