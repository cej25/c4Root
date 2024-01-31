#ifndef FrsHitData_H
#define FrsHitData_H

#include <vector>
#include "TObject.h"

class FrsHitData : public TObject
{
    public:
        FrsHitData();

        FrsHitData(uint64_t WR_TS);

        ~FrsHitData();

        inline const uint64_t Get_WR() const { return fWR_TS; }

    protected:

        uint64_t fWR_TS;
    
    public:
        ClassDef(FrsHitData, 1)

};


#endif