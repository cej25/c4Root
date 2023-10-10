#include "AidaData.h"

AidaUnpackAdcItem::AidaUnpackAdcItem()
{
}

void AidaUnpackAdcItem::Reset()
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

AidaUnpackScalerItem::AidaUnpackScalerItem()
{
}

void AidaUnpackScalerItem::Reset()
{
    time = value = 0;
    fee = 0;
}

void AidaUnpackScalerItem::SetAll(uint64_t t, uint64_t v, int f)
{
    time = t;
    value = v;
    fee = f;
}

AidaUnpackFlowItem::AidaUnpackFlowItem()
{
}

void AidaUnpackFlowItem::Reset()
{
    time = 0;
    fee = 0;
    pause = false;
}

void AidaUnpackFlowItem::SetAll(uint64_t t, int f, bool p)
{
    time = t;
    fee = f;
    pause = p;
}

ClassImp(AidaUnpackAdcItem)
ClassImp(AidaUnpackScalerItem)
ClassImp(AidaUnpackFlowItem)

