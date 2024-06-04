#include "BB7VmeCalData.h"

BB7VmeCalData::BB7VmeCalData()
{

}


BB7VmeImplantItem::BB7VmeImplantItem()
{

}

void BB7VmeImplantItem::SetAll(uint64_t wr, int si, int st, uint32_t adc)
{
    wr_t = wr;
    side = si;
    strip = st;
    raw_adc = adc;
}

void BB7VmeImplantItem::Reset()
{
    wr_t = 0;
    side = 0;
    strip = 0;
    raw_adc = 0;
}

ClassImp(BB7VmeImplantItem)


BB7VmeDecayItem::BB7VmeDecayItem()
{

}

void BB7VmeDecayItem::SetAll(uint64_t wr, int si, int st, uint32_t adc)
{
    wr_t = wr;
    side = si;
    strip = st;
    raw_adc = adc;
}

void BB7VmeDecayItem::Reset()
{
    wr_t = 0;
    side = 0;
    strip = 0;
    raw_adc = 0;
}

ClassImp(BB7VmeDecayItem)
