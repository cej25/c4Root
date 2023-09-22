#include "AidaData.h"

AidaUnpackAdcItem::AidaUnpackAdcItem()
{
}

void AidaUnpackAdcItem::Clear()
{
    rawTime = slowTime = fastTime = 0;
    fee = channel = 0;
    range = false;
    value = 0;
}

void AidaUnpackAdcItem::SetAll(uint64_t rt, uint64_t st, uint64_t ft, int f, int c, bool r, uint16_t v)
{
    rawTime = rt;
    slowTime = st;
    fastTime = ft;
    fee = f;
    channel = c;
    range = r;
    value = v;
}

ClassImp(AidaUnpackAdcItem)

