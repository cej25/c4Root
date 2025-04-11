#ifndef FrsData_H
#define FrsData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

typedef UInt_t UInt_t;
typedef Int_t Int_t;

class FrsTpatItem : public TObject
{
    public:
        FrsTpatItem();
        
        void SetAll(Long64_t wr, Short_t tp, Long64_t tmwr);
        void Reset();

        Long64_t Get_wr_t() const { return wr_t; }
        Short_t Get_tpat() const { return tpat; }
        Long64_t Get_travmus_wr_t() const { return travmus_wr_t; }

        ClassDef(FrsTpatItem, 1);

    private:

        Long64_t wr_t;
        Short_t tpat;
        Long64_t travmus_wr_t;
};

class FrsScalerItem : public TObject
{
    public:
        FrsScalerItem();

        void SetAll(Int_t i, UInt_t sc);
        void Reset();

        Int_t Get_index() const { return index; }
        UInt_t Get_scaler() const { return scaler; }
        
        ClassDef(FrsScalerItem, 1);

    private:

        Int_t index;
        UInt_t scaler;

};

class FrsSciItem : public TObject
{
    public:
        FrsSciItem();

        void SetAll(UInt_t de[18], UInt_t dt[19], std::vector<Int_t> mhtdc[24]);
        void Reset();

        // Getters
        const UInt_t (&Get_de_array() const) [32] { return sciDE; }
        const UInt_t (&Get_dt_array() const) [32] { return sciDT; }
        const std::vector<Int_t> (&Get_mhtdc_array() const) [32] { return sciMHTDC; }

        ClassDef(FrsSciItem, 1);
    
    private:

        // these should all probably just be set to 32...
        UInt_t sciDE[32]; // 16 --> 18 2025
        UInt_t sciDT[32]; // 16 --> 19 2025
        std::vector<Int_t> sciMHTDC[32]; // 15 --> 24 2025


};

class FrsMusicItem : public TObject
{
    public:
        FrsMusicItem();

        void SetAll(UInt_t e[5][8], UInt_t t[5][8]);
        void Reset();

        const UInt_t (&Get_music_e() const) [5][8] { return musicE; }
        const UInt_t (&Get_music_t() const) [5][8] { return musicT; }

        
        ClassDef(FrsMusicItem, 1);

    private:

        UInt_t musicE[5][8]; // 2 -> 5 2025
        UInt_t musicT[5][8];

};

class FrsTpcItem : public TObject
{
    public:
        FrsTpcItem();

        void SetAll(UInt_t adc[7][8], std::vector<UInt_t> tdc[128]);
        void Reset();

        const UInt_t (&Get_adc_data() const) [7][8] { return adcData; }
        const std::vector<UInt_t> (&Get_tdc_data() const) [128] { return tdcData; }

        ClassDef(FrsTpcItem, 1);

    private:

        // 7 tpcs, 8 channels each
        UInt_t adcData[7][8];

        // 128 channels, *up to* 64 hits (anl/software limit)
        std::vector<UInt_t> tdcData[128];
        

};

#endif 