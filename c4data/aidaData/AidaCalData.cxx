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

void AidaCalAdcItem::SetAll(ULong64_t st, ULong64_t ft, Int_t f, Int_t c, Int_t d, Int_t si, Int_t str, Bool_t r, Double_t i, Double_t e)
{
    slowTime = st;
    fastTime = ft;
    fee = f;
    channel = c;
    dssd = d;
    side = si;
    strip = str;
    range = r;
    intensity = i;
    energy = e;
}

ClassImp(AidaCalAdcItem)
