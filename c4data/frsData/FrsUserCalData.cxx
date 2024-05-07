#include "FrsUserCalData.h"

FrsUserCalData::FrsUserCalData()
    :   fScalers_N(0)
    ,   fScalers_Index(0)
    ,   fV830_Scalers(0)
{
}


FrsUserCalData::FrsUserCalData(uint32_t Scalers_N, 
                            std::vector<uint32_t> Scalers_Index, 
                            std::vector<uint32_t> V830_Scalers,
                            uint32_t* dt_array,
                            uint32_t* music_e1,
                            uint32_t* music_e2)
    :   fScalers_N(Scalers_N)
    ,   fScalers_Index(Scalers_Index)
    ,   fV830_Scalers(V830_Scalers)
{   
    for (int i = 0; i < 16; i++) fdt_array[i] = dt_array[i];
    for (int i = 0; i < 8; i++)
    {
        fmusic_e1[i] = music_e1[i];
        fmusic_e2[i] = music_e2[i];
    }
}

FrsUserCalScalerItem::FrsUserCalScalerItem()
{

}

void FrsUserCalScalerItem::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsUserCalScalerItem::Reset()
{
    index = 0;
    scaler = 0;
}

FrsUserCalSciItem::FrsUserCalSciItem()
{

}

void FrsUserCalSciItem::SetAll(uint32_t* dt)
{
    dt_array = dt;
}

FrsUserCalMusicItem::FrsUserCalMusicItem()
{

}

void FrsUserCalMusicItem::SetAll(uint32_t* me1, uint32_t* me2)
{
    music_e1 = me1;
    music_e2 = me2;
}

void FrsUserCalMusicItem::Reset()
{

}




ClassImp(FrsUserCalData)
