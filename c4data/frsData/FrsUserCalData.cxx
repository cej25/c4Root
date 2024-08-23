#include "FrsUserCalData.h"


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

ClassImp(FrsUserCalScalerItem)


FrsUserCalSciItem::FrsUserCalSciItem()
{

}

void FrsUserCalSciItem::SetAll(uint32_t* dt)
{
    for (int i = 0; i<16; i ++) dt_array[i] = dt[i];
}

ClassImp(FrsUserCalSciItem)


FrsUserCalMusicItem::FrsUserCalMusicItem()
{

}

void FrsUserCalMusicItem::SetAll(uint32_t* me1, uint32_t* me2)
{
    for(int i = 0; i<8; i++){
        music_e1[i] = me1[i];
        music_e2[i] = me2[i];
    }
}

void FrsUserCalMusicItem::Reset()
{

}

ClassImp(FrsUserCalMusicItem)
