#ifndef c4LisaTraceData_H
#define c4LisaTraceData_H
#include "TObject.h"

class c4LisaTraceData : public TObject
{
    public:
        c4LisaTraceData();

        c4LisaTraceData(uint32_t trEl);

        virtual ~c4LisaTraceData() {}

        // Getters
        inline const uint32_t GetTrSample() const { return fTrEl; }

        // Setters
        void SetTrEl(uint32_t v) { fTrEl = v; }

    protected:
        // somethin
        uint32_t fTrEl;

    public:
        ClassDef(c4LisaTraceData, 1)
};

#endif