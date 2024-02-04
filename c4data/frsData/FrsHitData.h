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
                Float_t id_x4,
                Float_t fID_AoQ,
                Float_t fID_AoQ_corr,
                Float_t fID_z,
                Float_t fID_z2,
                Float_t fID_beta);

        ~FrsHitData();

        inline const uint64_t Get_WR() const { return fWR_TS; }
        inline const Float_t Get_ID_AoQ() const {return fID_AoQ; }
        inline const Float_t Get_ID_AoQ_corr() const {return fID_AoQ_corr; }
        inline const Float_t Get_ID_z() const {return fID_z; }
        inline const Float_t Get_ID_z2() const {return fID_z2; }
        inline const Float_t Get_ID_x4() const {return fID_x4; }
        inline const Float_t Get_ID_beta() const {return fID_beta;}

    protected:

        uint64_t fWR_TS;
        Float_t fID_x2;
        Float_t fID_x4;
        Float_t fID_AoQ;
        Float_t fID_AoQ_corr;
        Float_t fID_z;
        Float_t fID_z2;
        Float_t fID_beta;
    
    public:
        ClassDef(FrsHitData, 1)

};


#endif