#include "AidaHitData.h"

void AidaHit::Reset()
{
    DSSD = -1;
    StripX = StripY = PosX = PosY = -1;
    Energy = EnergyX = EnergyY = 0;
    StripXMin = StripXMax = StripYMin = StripYMax = -1;
    ClusterSizeX = ClusterSizeY = 0;
    Time = TimeX = TimeY = 0;
    FastTime = FastTimeX = FastTimeY = 0;
    Stopped = false;
}

ClassImp(AidaHit)

