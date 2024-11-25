#include "TravMusAnaData.h"

TravMusAnaItem::TravMusAnaItem()
{
}

void TravMusAnaItem::SetAll(int64_t wr, double de, double de_dc)
{
    wr_t = wr;
    de_travmus = de;
    de_travmus_driftcorr = de_dc;
}

void TravMusAnaItem::Reset()
{
    wr_t = 0;
    de_travmus = 0;
    de_travmus_driftcorr = 0;
}

ClassImp(TravMusAnaItem)