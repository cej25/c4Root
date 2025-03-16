#ifndef AidaCalData_H
#define AidaCalData_H

#include "TObject.h"

class AidaCalAdcItem : public TObject
{
    public:
        AidaCalAdcItem();

        void Reset();
        void SetAll(ULong64_t st, ULong64_t ft, Int_t f, Int_t c, Int_t d, Int_t si, Int_t str, Bool_t r, Double_t i, Double_t e);
    
        ULong64_t SlowTime() const { return slowTime; }
        ULong64_t FastTime() const { return fastTime; }
        Int_t Fee() const { return fee; }
        Int_t Channel() const { return channel; }
        Int_t DSSD() const { return dssd; }
        Int_t Side() const { return side; }
        Int_t Strip() const { return strip; }
        Bool_t Range() const { return range; }
        Double_t Intensity() const { return intensity; }
        Double_t Energy() const { return energy; }

        ClassDefNV(AidaCalAdcItem, 2)

    private:
        ULong64_t slowTime;
        ULong64_t fastTime;
        Int_t fee;
        Int_t channel;
        Int_t dssd;
        Int_t side;
        Int_t strip;
        Bool_t range;
        Double_t intensity; // only for gain matching code?
        Double_t energy;
};

#endif /* AidaCalData_H */

