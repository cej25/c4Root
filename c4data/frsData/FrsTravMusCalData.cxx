#include "FrsTravMusCalData.h"

FrsTravMusCalItem::FrsTravMusCalItem()
{
}

void FrsTravMusCalItem::SetAll(uint64_t wr, uint16_t* e, uint16_t* t)
{
    wr_t = wr;
    for (int i = 0; i < 8; i++)
    {
        energy[i] = e[i];
        time[i] = t[i];
    }
}

void FrsTravMusCalItem::Reset()
{
    wr_t = 0;
    for (int i = 0; i < 8; i++)
    {
        energy[i] = 0;
        time[i] = 0;
    }
}

ClassImp(FrsTravMusCalItem)