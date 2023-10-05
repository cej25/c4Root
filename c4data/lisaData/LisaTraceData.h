#ifndef LisaTraceData_H
#define LisaTraceData_H
#include "TObject.h"

class LisaTraceData : public TObject
{
    public:
        LisaTraceData();

        LisaTraceData(uint32_t trSample);

        virtual ~LisaTraceData() {}

        // Getters
        inline const uint32_t GetTrSample() const { return fTrSample; }

        // Setters
        void SetTrSample(uint32_t v) { fTrSample = v; }

    protected:
        // somethin
        uint32_t fTrSample;

    public:
        ClassDef(LisaTraceData, 1)
};

#endif