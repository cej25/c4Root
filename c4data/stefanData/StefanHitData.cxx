#include "StefanHitData.h"

void StefanHitItem::Reset()
{
    DSSD = -1;
    StripX = StripY = PosX = PosY = -1;
    Energy = EnergyX = EnergyY = 0;
    StripXMin = StripXMax = StripYMin = StripYMax = -1;
    ClusterSizeX = ClusterSizeY = 0;
    Time = TimeX = TimeY = 0;
    Stopped = false;
}

ClassImp(StefanHitItem)

