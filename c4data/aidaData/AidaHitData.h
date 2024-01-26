#ifndef AidaHitData_H
#define AidaHitData_H

#include "TObject.h"

class AidaHit : public TObject
{
public:
    AidaHit() { Reset(); }

    void Reset();

    int DSSD;
    double StripX, StripY;
    double PosX, PosY;

    double Energy, EnergyX, EnergyY;

    int StripXMin, StripXMax, StripYMin, StripYMax;
    int ClusterSizeX, ClusterSizeY;

    int64_t Time, TimeX, TimeY;
    int64_t FastTime, FastTimeX, FastTimeY;

    bool Stopped;

    ClassDefNV(AidaHit, 2)

private:
};


#endif /* AidaHitData_H */

