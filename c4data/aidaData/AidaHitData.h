#ifndef AidaHitData_H
#define AidaHitData_H

#include "TObject.h"

class AidaHit : public TObject
{
    public:
        AidaHit() { Reset(); }

        void Reset();

        Int_t DSSD;
        Double_t StripX, StripY;
        Double_t PosX, PosY;

        Double_t Energy, EnergyX, EnergyY;

        Int_t StripXMin, StripXMax, StripYMin, StripYMax;
        Int_t ClusterSizeX, ClusterSizeY;

        Long64_t Time, TimeX, TimeY;
        Long64_t FastTime, FastTimeX, FastTimeY;

        Bool_t Stopped;

        ClassDefNV(AidaHit, 2)

    private:
};


#endif /* AidaHitData_H */

