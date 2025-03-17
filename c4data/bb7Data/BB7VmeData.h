#ifndef BB7VmeData_H
#define BB7VmeData_H

#include "TObject.h"
#include <vector>

class BB7V7x5Item : public TObject
{
    public:
        BB7V7x5Item();

        void SetAll(Long64_t wr, UInt_t g, UInt_t data, UInt_t ch);
        void Reset();

        Long64_t Get_wr_t() const { return wr_t; }
        UInt_t Get_geo() const { return geo; }
        UInt_t Get_v7x5_data() const { return v7x5_data; }
        UInt_t Get_channel() const { return channel; }

        ClassDefNV(BB7V7x5Item, 1);

    private:
        Long64_t wr_t;
        UInt_t geo;
        UInt_t v7x5_data;
        UInt_t channel;
};

class BB7V1290Item : public TObject
{
    public:
        BB7V1290Item();

        void SetAll(UInt_t ch, UInt_t data, UInt_t lot);
        void Reset();

        UInt_t Get_channel() const { return channel; }
        UInt_t Get_v1290_data() const { return v1290_data; }
        UInt_t Get_leadOrTrail() const { return leadOrTrail; }

        ClassDefNV(BB7V1290Item, 1);

    private:
        UInt_t channel;
        UInt_t v1290_data;
        UInt_t leadOrTrail;
};

#endif