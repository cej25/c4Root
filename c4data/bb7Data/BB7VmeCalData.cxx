#include "BB7VmeCalData.h"

BB7VmeCalData::BB7VmeCalData()
{

}


BB7VmeImplantItem::BB7VmeImplantItem()
{

}

void BB7VmeImplantItem::SetAll(uint64_t wr, int det, int si, int st, uint32_t adc)
{
    wr_t = wr;
    detector = det;
    side = si;
    strip = st;
    raw_adc = adc;
}

void BB7VmeImplantItem::Reset()
{
    wr_t = 0;
    detector = 0;
    side = 0;
    strip = 0;
    raw_adc = 0;
}

ClassImp(BB7VmeImplantItem)


BB7VmeDecayItem::BB7VmeDecayItem()
{

}

void BB7VmeDecayItem::SetAll(uint64_t wr, int det, int si, int st, uint32_t adc)
{
    wr_t = wr;
    detector = det;
    side = si;
    strip = st;
    raw_adc = adc;
}

void BB7VmeDecayItem::Reset()
{
    wr_t = 0;
    detector = 0;
    side = 0;
    strip = 0;
    raw_adc = 0;
}

BB7VmeResidualItem::BB7VmeResidualItem()
{

}

void BB7VmeResidualItem::SetAll(uint32_t left, uint32_t right, uint32_t del, uint32_t un)
{
    sc41l = left;
    sc41r = right;
    tm_delayed = del;
    tm_undelayed = un;
}

void BB7VmeResidualItem::Reset()
{
    sc41l = 0;
    sc41r = 0;
    tm_delayed = 0;
    tm_undelayed = 0;
}

ClassImp(BB7VmeResidualItem)
