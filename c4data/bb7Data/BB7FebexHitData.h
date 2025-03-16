#ifndef BB7FebexHitData_H
#define BB7FebexHitData_H

#include "TObject.h"

class BB7FebexHitItem : public TObject
{
    public:
        BB7FebexHitItem() { Reset(); }

        void Reset();

        Int_t DSSD;
        Double_t StripX, StripY;
        Double_t PosX, PosY;

        Double_t Energy, EnergyX, EnergyY;

        Int_t StripXMin, StripXMax, StripYMin, StripYMax;
        Int_t ClusterSizeX, ClusterSizeY;

        Long64_t Time, TimeX, TimeY;

        Bool_t Stopped;

        ClassDefNV(BB7FebexHitItem, 1)

};


#endif /* BB7FebexHitData_H */

