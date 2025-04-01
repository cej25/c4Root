#ifndef BB7VmeCalData_H
#define BB7VmeCalData_H

#include "TObject.h"
#include <vector>

class BB7VmeImplantItem : public TObject
{
    public:
        BB7VmeImplantItem();

        void SetAll(Long64_t wr, Int_t det, Int_t si, Int_t st, UInt_t adc);
        void Reset();

        Long64_t Get_wr_t() const { return wr_t; }
        Int_t Get_detector() const { return detector; }
        Int_t Get_side() const { return side; }
        Int_t Get_strip() const { return strip; }
        UInt_t Get_raw_adc() const { return raw_adc; }

        ClassDefNV(BB7VmeImplantItem, 1);
    
    private:

        Long64_t wr_t;
        Int_t detector;
        Int_t side;
        Int_t strip;
        UInt_t raw_adc;

};

class BB7VmeDecayItem : public TObject
{
    public:
        BB7VmeDecayItem();

        void SetAll(Long64_t wr, Int_t det, Int_t si, Int_t st, UInt_t adc);
        void Reset();

        Long64_t Get_wr_t() const { return wr_t; }
        Int_t Get_detector() const { return detector; }
        Int_t Get_side() const { return side; }
        Int_t Get_strip() const { return strip; }
        UInt_t Get_raw_adc() const { return raw_adc; }

        ClassDefNV(BB7VmeDecayItem, 1);
    
    private:

        Long64_t wr_t;
        Int_t detector;
        Int_t side;
        Int_t strip;
        UInt_t raw_adc;
};

class BB7VmeResidualItem : public TObject
{
    public:
        BB7VmeResidualItem();

        void Reset();
        void SetAll(UInt_t left, UInt_t right, UInt_t tmd, UInt_t tmu);

        UInt_t Get_SC41L() const { return sc41l; }
        UInt_t Get_SC41R() const { return sc41r; }
        UInt_t Get_TM_Delayed() const { return tm_delayed; }
        UInt_t Get_TM_Undelayed() const { return tm_undelayed; }

        ClassDefNV(BB7VmeResidualItem, 1);

    private:
        UInt_t sc41l;
        UInt_t sc41r;
        UInt_t tm_delayed;
        UInt_t tm_undelayed;
};

#endif