#include "AidaCalData.h"

AidaCalAdcItem::AidaCalAdcItem()
{
}

void AidaCalAdcItem::Reset()
{
    slowTime = fastTime = 0;
    dssd = side = strip = 0;
    range = false;
    intensity = energy = 0.;
}

void AidaCalAdcItem::SetAll(uint64_t st, uint64_t ft, int d, int si, int str, bool r, double i, double e)
{
    slowTime = st;
    fastTime = ft;
    dssd = d;
    side = si;
    strip = str;
    range = r;
    intensity = i;
    energy = e;
}

ClassImp(AidaCalAdcItem)
