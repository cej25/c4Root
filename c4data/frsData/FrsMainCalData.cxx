#include "FrsMainCalData.h"

FrsMainCalScalerItem::FrsMainCalScalerItem()
{

}

void FrsMainCalScalerItem::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsMainCalScalerItem::Reset()
{

}

ClassImp(FrsMainCalScalerItem)

FrsMainCalSciItem::FrsMainCalSciItem()
{

}

void FrsMainCalSciItem::SetdEArray(uint32_t* de)
{
    de_array = de;
}

void FrsMainCalSciItem::SetAll(uint32_t* de, uint32_t** tdc, int * multi)
{
    de_array = de;
    tdc_array = tdc;
    mh_counter = multi;
}

void FrsMainCalSciItem::Reset() //?
{
    de_array = 0;
    tdc_array = 0;
}

ClassImp(FrsMainCalSciItem)

FrsMainCalMusicItem::FrsMainCalMusicItem()
{

}

void FrsMainCalMusicItem::SetAll(uint32_t* mt1, uint32_t* mt2)
{
    music_t1 = mt1;
    music_t2 = mt2;
}

void FrsMainCalMusicItem::Reset()
{
    music_t1 = 0;
    music_t2 = 0;
}

ClassImp(FrsMainCalMusicItem)