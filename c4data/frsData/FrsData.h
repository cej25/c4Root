#ifndef FrsData_H
#define FrsData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class FrsTpatItem : public TObject
{
    public:
        FrsTpatItem();
        
        void SetAll(int64_t wr, int16_t tp);
        void Reset();

        int64_t Get_wr_t() const { return wr_t; }
        int16_t Get_tpat() const { return tpat; }

        ClassDef(FrsTpatItem, 1);

    private:

        int64_t wr_t;
        int16_t tpat;
};

class FrsScalerItem : public TObject
{
    public:
        FrsScalerItem();

        void SetAll(int i, uint32_t sc);
        void Reset();

        int Get_index() const { return index; }
        int Get_scaler() const { return scaler; }
        
        ClassDef(FrsScalerItem, 1);

    private:

        int index;
        uint32_t scaler;

};

class FrsSciItem : public TObject
{
    public:
        FrsSciItem();

        void SetAll(uint32_t de[16], uint32_t dt[16], std::vector<uint32_t> mhtdc[16]);

        // Getters
        const uint32_t (&Get_de_array() const) [16] { return sciDE; }
        const uint32_t (&Get_dt_array() const) [16] { return sciDT; }
        const std::vector<uint32_t> (&Get_mhtdc_array() const) [16] { return sciMHTDC; }

        ClassDef(FrsSciItem, 1);
    
    private:

        uint32_t sciDE[16];
        uint32_t sciDT[16];
        std::vector<uint32_t> sciMHTDC[16];


};

class FrsMusicItem : public TObject
{
    public:
        FrsMusicItem();

        void SetAll(uint32_t e[2][8], uint32_t t[2][8]);

        const uint32_t (&Get_music_e() const) [2][8] { return musicE; }
        const uint32_t (&Get_music_t() const) [2][8] { return musicT; }

        
        ClassDef(FrsMusicItem, 1);

    private:

        uint32_t musicE[2][8];
        uint32_t musicT[2][8];

};

class FrsTpcItem : public TObject
{
    public:
        FrsTpcItem();

        void SetAll(uint32_t adc[7][8], std::vector<uint32_t> tdc[128]);

        const uint32_t (&Get_adc_data() const) [7][8] { return adcData; }
        const std::vector<uint32_t> (&Get_tdc_data() const) [128] { return tdcData; }

        ClassDef(FrsTpcItem, 1);

    private:

        // 7 tpcs, 8 channels each
        uint32_t adcData[7][8];

        // 128 channels, *up to* 64 hits (anl/software limit)
        std::vector<uint32_t> tdcData[128];
        

};

#endif 