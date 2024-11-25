#include "TravMusAnaData.h"

TravMusAnaItem::TravMusAnaItem()
{
}

void TravMusAnaItem::SetAll(int64_t wr, double de)
{
    wr_t = wr;
    de_travmus = de;
}

void TravMusAnaItem::Reset()
{
    
}

ClassImp(TravMusAnaItem)