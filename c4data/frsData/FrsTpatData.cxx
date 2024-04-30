#include "FrsTpatData.h"

FrsTpatData::FrsTpatData()
{
}

FrsTpatData::~FrsTpatData()
{
}


FrsTpatItem::FrsTpatItem()
{

}

void FrsTpatItem::SetAll(uint64_t wr, uint16_t tp)
{
    wr_t = wr;
    tpat = tp;
}

void FrsTpatItem::Reset()
{
    wr_t = 0;
    tpat = 0;
}

ClassImp(FrsTpatData)