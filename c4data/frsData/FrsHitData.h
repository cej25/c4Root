#ifndef FrsHitData_H
#define FrsHitData_H

#include <vector>
#include "TObject.h"

class FrsHitData : public TObject
{
    public:
        FrsHitData();

        // I think some of this spill stuff should be floats
        FrsHitData(uint64_t WR_TS,
                uint32_t time_in_ms, 
                uint32_t ibin_for_s, 
                uint32_t ibin_for_100ms,
                uint32_t ibin_for_spill,
                uint32_t* increase_sc_temp_main,
                uint32_t* increase_sc_temp_user, 
                uint32_t increase_sc_temp2,
                uint32_t increase_sc_temp3,
                uint32_t extraction_time_ms, 
                uint32_t ibin_clean_for_s, 
                uint32_t ibin_clean_for_100ms,
                uint32_t ibin_clean_for_spill,
                Float_t id_x2,
                Float_t id_x4,
                Float_t id_AoQ,
                Float_t id_AoQ_corr,
                Float_t id_z,
                Float_t id_z2,
                Float_t id_beta);

        ~FrsHitData();

        inline const uint64_t Get_WR() const { return fWR_TS; }
        inline const Float_t Get_ID_AoQ() const {return fID_AoQ; }
        inline const Float_t Get_ID_AoQ_corr() const {return fID_AoQ_corr; }
        inline const Float_t Get_ID_z() const {return fID_z; }
        inline const Float_t Get_ID_z2() const {return fID_z2; }
        inline const Float_t Get_ID_x4() const {return fID_x4; }
        inline const Float_t Get_ID_beta() const {return fID_beta;}

        inline uint32_t Get_time_in_ms() { return ftime_in_ms; }
        inline uint32_t Get_ibin_for_s() { return fibin_for_s; }
        inline uint32_t Get_ibin_for_100ms() { return fibin_for_100ms; }
        inline uint32_t Get_ibin_for_spill() { return fibin_for_spill; }
        inline uint32_t* Get_increase_sc_temp_main() { return fincrease_sc_temp_main; }
        inline uint32_t* Get_increase_sc_temp_user() { return fincrease_sc_temp_user; }
        inline uint32_t Get_increase_sc_temp2() { return fincrease_sc_temp2; }
        inline uint32_t Get_increase_sc_temp3() { return fincrease_sc_temp3; }
        inline uint32_t Get_extraction_time_ms() { return fextraction_time_ms; }
        inline uint32_t Get_ibin_clean_for_s() { return fibin_clean_for_s; }
        inline uint32_t Get_ibin_clean_for_100ms() { return fibin_clean_for_100ms; }
        inline uint32_t Get_ibin_clean_for_spill() { return fibin_clean_for_spill; }

    protected:

        uint64_t fWR_TS;
        Float_t fID_x2;
        Float_t fID_x4;
        Float_t fID_AoQ;
        Float_t fID_AoQ_corr;
        Float_t fID_z;
        Float_t fID_z2;
        Float_t fID_beta;
        
        uint32_t ftime_in_ms;
        uint32_t fibin_for_s;
        uint32_t fibin_for_100ms;
        uint32_t fibin_for_spill;
        uint32_t fincrease_sc_temp_main[32];
        uint32_t fincrease_sc_temp_user[32];
        uint32_t fincrease_sc_temp2;
        uint32_t fincrease_sc_temp3;
        uint32_t fextraction_time_ms;
        uint32_t fibin_clean_for_s;
        uint32_t fibin_clean_for_100ms;
        uint32_t fibin_clean_for_spill;
    
    public:
        ClassDef(FrsHitData, 1)

};


#endif