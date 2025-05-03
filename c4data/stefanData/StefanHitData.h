#ifndef StefanHitData_H
#define StefanHitData_H

#include "TObject.h"

class StefanHitItem : public TObject
{
    public:
        StefanHitItem() { Reset(); }

        void Reset();

        Int_t DSSD;
        Double_t StripX, StripY;
        Double_t PosX, PosY;

        Double_t Energy, EnergyX, EnergyY;

        Int_t StripXMin, StripXMax, StripYMin, StripYMax;
        Int_t ClusterSizeX, ClusterSizeY;

        Long64_t Time, TimeX, TimeY;

        Bool_t Stopped;

        ClassDefNV(StefanHitItem, 1)

};


#endif /* StefanHitData_H */

