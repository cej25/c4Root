#ifndef BB7FebexHitData_H
#define BB7FebexHitData_H

#include "TObject.h"

class BB7FebexHitItem : public TObject
{
    public:
        BB7FebexHitItem() { Reset(); }

        void Reset();

        int DSSD;
        double StripX, StripY;
        double PosX, PosY;

        double Energy, EnergyX, EnergyY;

        int StripXMin, StripXMax, StripYMin, StripYMax;
        int ClusterSizeX, ClusterSizeY;

        int64_t Time, TimeX, TimeY;

        bool Stopped;

        ClassDefNV(BB7FebexHitItem, 1)

};


#endif /* BB7FebexHitData_H */

