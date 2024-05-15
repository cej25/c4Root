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
    dt_array = dt;
}

ClassImp(FrsUserCalSciItem)


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

ClassImp(FrsUserCalMusicItem)
