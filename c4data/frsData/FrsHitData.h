#ifndef FrsHitData_H
#define FrsHitData_H

#include <vector>
#include "TObject.h"

class FrsHitData : public TObject
{
    public:
        FrsHitData();

        FrsHitData(uint64_t WR_TS,
                Float_t id_x2,
                Float_t id_x4);

        ~FrsHitData();

        inline const uint64_t Get_WR() const { return fWR_TS; }

    protected:

        uint64_t fWR_TS;
        Float_t fID_x2;
        Float_t fID_x4;
    
    public:
        ClassDef(FrsHitData, 1)

};


#endif