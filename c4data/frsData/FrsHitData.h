#ifndef FrsHitData_H
#define FrsHitData_H

#include "../../config/setup.h"
#include <vector>
#include "TObject.h"

class FrsHitItem : public TObject
{
    public:
        FrsHitItem();

        void SetAll(uint64_t wr_t,
                    uint16_t tpat,
                    Float_t x2,
                    Float_t y2,
                    Float_t x4,
                    Float_t y4,
                    Float_t a2,
                    Float_t b2,
                    Float_t a4,
                    Float_t b4,
                    Float_t AoQ,
                    Float_t AoQ_driftcorr,
                    Float_t AoQ_corr,
                    Float_t z,
                    Float_t z_driftcorr,
                    Float_t z2,
                    Float_t beta,
                    Float_t dEdeg,
                    Float_t dEdegoQ,
                    Float_t* rho,
                    Float_t* brho,
                    Float_t* music_dE,
                    Float_t* music_dE_cor,
                    Float_t sci_21l,
                    Float_t sci_21r,
                    Float_t sci_22l,
                    Float_t sci_22r,
                    Float_t sci_31l,
                    Float_t sci_31r,
                    Float_t sci_41l,
                    Float_t sci_41r,
                    Float_t sci_42l,
                    Float_t sci_42r,
                    Float_t sci_43l,
                    Float_t sci_43r,
                    Float_t sci_81l,
                    Float_t sci_81r,
                    Float_t sci_e_21,
                    Float_t sci_e_22,
                    Float_t sci_e_31,
                    Float_t sci_e_41,
                    Float_t sci_e_42,
                    Float_t sci_e_43,
                    Float_t sci_e_81,
                    Float_t sci_x_21,
                    Float_t sci_x_22,
                    Float_t sci_x_41,
                    Float_t sci_x_42,
                    Float_t sci_x_43,
                    Float_t sci_x_81,
                    Float_t sci_tof_21_41,
                    Float_t sci_tof_21_41_calib,
                    Float_t sci_tof_21_42,
                    Float_t sci_tof_21_42_calib,
                    Float_t sci_tof_21_81,
                    Float_t sci_tof_21_81_calib,
                    Float_t sci_tof_22_41,
                    Float_t sci_tof_22_41_calib,
                    Float_t sci_tof_22_81,
                    Float_t sci_tof_22_81_calib,
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
                    uint32_t ibin_clean_for_spill);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_tpat() const;
        Float_t Get_ID_x2() const; //
        Float_t Get_ID_y2() const; //
        Float_t Get_ID_x4() const;
        Float_t Get_ID_y4() const;
        Float_t Get_ID_a2() const;
        Float_t Get_ID_b2() const;
        Float_t Get_ID_a4() const;
        Float_t Get_ID_b4() const;
        Float_t Get_ID_AoQ() const;
        Float_t Get_ID_AoQ_driftcorr() const;
        Float_t Get_ID_AoQ_corr() const;
        Float_t Get_ID_z() const; //
        Float_t Get_ID_z_driftcorr() const;
        Float_t Get_ID_z2() const; //
        Float_t Get_ID_beta() const;
        Float_t Get_ID_dEdeg() const;
        Float_t Get_ID_dEdegoQ() const;
        Float_t Get_ID_rho(int index) const;
        Float_t Get_ID_brho(int index) const; 
        Float_t Get_music_dE(int index) const; //index 0 = music 1
        Float_t Get_music_dE_cor(int index) const; 
        Float_t Get_sci_21l() const { return fsci_21l; }
        Float_t Get_sci_21r() const { return fsci_21r; }
        Float_t Get_sci_22l() const { return fsci_22l; }
        Float_t Get_sci_22r() const { return fsci_22r; }
        Float_t Get_sci_31l() const { return fsci_31l; }
        Float_t Get_sci_31r() const { return fsci_31r; }
        Float_t Get_sci_41l() const { return fsci_41l; }
        Float_t Get_sci_41r() const { return fsci_41r; }
        Float_t Get_sci_42l() const { return fsci_42l; }
        Float_t Get_sci_42r() const { return fsci_42r; }
        Float_t Get_sci_43l() const { return fsci_43l; }
        Float_t Get_sci_43r() const { return fsci_43r; }
        Float_t Get_sci_81l() const { return fsci_81l; }
        Float_t Get_sci_81r() const { return fsci_81r; }
        Float_t Get_sci_e_21() const { return fsci_e_21; }
        Float_t Get_sci_e_22() const { return fsci_e_22; }
        Float_t Get_sci_e_31() const { return fsci_e_31; }
        Float_t Get_sci_e_41() const { return fsci_e_41; }
        Float_t Get_sci_e_42() const { return fsci_e_42; }
        Float_t Get_sci_e_43() const { return fsci_e_43; }
        Float_t Get_sci_e_81() const { return fsci_e_81; }
        Float_t Get_sci_x_21() const { return fsci_x_21; }
        Float_t Get_sci_x_22() const { return fsci_x_22; }
        Float_t Get_sci_x_41() const { return fsci_x_41; }
        Float_t Get_sci_x_42() const { return fsci_x_42; }
        Float_t Get_sci_x_43() const { return fsci_x_43; }
        Float_t Get_sci_x_81() const { return fsci_x_81; }
        Float_t Get_sci_tof_21_41() const { return fsci_tof_21_41; }
        Float_t Get_sci_tof_21_41_calib() const { return fsci_tof_21_41_calib; }
        Float_t Get_sci_tof_21_42() const { return fsci_tof_21_42; }
        Float_t Get_sci_tof_21_42_calib() const { return fsci_tof_21_42_calib; }
        Float_t Get_sci_tof_21_81() const { return fsci_tof_21_81; }
        Float_t Get_sci_tof_21_81_calib() const { return fsci_tof_21_81_calib; }
        Float_t Get_sci_tof_22_41() const { return fsci_tof_22_41; }
        Float_t Get_sci_tof_22_41_calib() const { return fsci_tof_22_41_calib; }
        Float_t Get_sci_tof_22_81() const { return fsci_tof_22_81; }
        Float_t Get_sci_tof_22_81_calib() const { return fsci_tof_22_81_calib; }
        uint32_t Get_time_in_ms() const;
        uint32_t Get_ibin_for_s() const;
        uint32_t Get_ibin_for_100ms() const;
        uint32_t Get_ibin_for_spill() const;
        uint32_t Get_increase_sc_temp_main(int index) const;
        uint32_t Get_increase_sc_temp_user(int index) const;
        uint32_t Get_increase_sc_temp2() const;
        uint32_t Get_increase_sc_temp3() const;
        uint32_t Get_extraction_time_ms() const;
        uint32_t Get_ibin_clean_for_s() const;
        uint32_t Get_ibin_clean_for_100ms() const;
        uint32_t Get_ibin_clean_for_spill() const;

        ClassDefNV(FrsHitItem, 1);

    private:

        uint64_t fwr_t;
        uint16_t ftpat;

        // ids
        Float_t fID_x2;
        Float_t fID_y2;
        Float_t fID_x4;
        Float_t fID_y4;
        Float_t fID_a2;
        Float_t fID_b2;
        Float_t fID_a4;
        Float_t fID_b4;
        Float_t fID_AoQ;
        Float_t fID_AoQ_driftcorr;
        Float_t fID_AoQ_corr;
        Float_t fID_z;
        Float_t fID_z_driftcorr;
        Float_t fID_z2;
        Float_t fID_beta;
        Float_t fID_dEdeg;
        Float_t fID_dEdegoQ;
        Float_t fID_rho[2]; // [2]
        Float_t fID_brho[2]; // [2]

        // scitillators / energy loss
        // we can't store this stuff in a tree as a pointer.....
        Float_t fmusic_dE[2]; // [2] // CEJ: 2? 3 for more musics?
        Float_t fmusic_dE_cor[2]; // [2]
        Float_t fsci_21l;
        Float_t fsci_21r;
        Float_t fsci_22l;
        Float_t fsci_22r;
        Float_t fsci_31l;
        Float_t fsci_31r;
        Float_t fsci_41l;
        Float_t fsci_41r;
        Float_t fsci_42l;
        Float_t fsci_42r;
        Float_t fsci_43l;
        Float_t fsci_43r;
        Float_t fsci_81l;
        Float_t fsci_81r;
        Float_t fsci_e_21;
        Float_t fsci_e_22;
        Float_t fsci_e_31;
        Float_t fsci_e_41;
        Float_t fsci_e_42;
        Float_t fsci_e_43;
        Float_t fsci_e_81;
        Float_t fsci_x_21;
        Float_t fsci_x_22;
        Float_t fsci_x_41;
        Float_t fsci_x_42;
        Float_t fsci_x_43;
        Float_t fsci_x_81;
        Float_t fsci_tof_21_41; // should we look at passing all the tof calcs?
        Float_t fsci_tof_21_41_calib;
        Float_t fsci_tof_21_42;
        Float_t fsci_tof_21_42_calib;
        Float_t fsci_tof_21_81;
        Float_t fsci_tof_21_81_calib;
        Float_t fsci_tof_22_41;
        Float_t fsci_tof_22_41_calib;
        Float_t fsci_tof_22_81;
        Float_t fsci_tof_22_81_calib;
        
        // scalers
        uint32_t ftime_in_ms;
        uint32_t fibin_for_s;
        uint32_t fibin_for_100ms;
        uint32_t fibin_for_spill;
        uint32_t fincrease_sc_temp_main[32]; // [32]
        uint32_t fincrease_sc_temp_user[32]; // [32]
        uint32_t fincrease_sc_temp2;
        uint32_t fincrease_sc_temp3;
        uint32_t fextraction_time_ms;
        uint32_t fibin_clean_for_s;
        uint32_t fibin_clean_for_100ms;
        uint32_t fibin_clean_for_spill;

};

class FrsMultiHitItem : public TObject
{
    public: 
        FrsMultiHitItem();

        void SetAll(
                    Float_t s2x,
                    Float_t s2a,
                    Float_t s4x,
                    Float_t s4a,
                    Float_t tof,
                    Float_t beta, 
                    Float_t AoQ, 
                    Float_t AoQ_corr, 
                    Float_t z,
                    Float_t z2,
                    Float_t dEdeg,
                    Float_t dEdegoQ);
        void Reset();

        Float_t Get_ID_s2x_mhtdc() const;
        Float_t Get_ID_s4x_mhtdc() const;
        Float_t Get_ID_s2a_mhtdc() const;
        Float_t Get_ID_s4a_mhtdc() const;
        Float_t Get_ID_tof_mhtdc() const;
        Float_t Get_ID_beta_mhtdc() const;
        Float_t Get_ID_AoQ_mhtdc() const;
        Float_t Get_ID_AoQ_corr_mhtdc() const;
        Float_t Get_ID_z_mhtdc() const;
        Float_t Get_ID_z2_mhtdc() const;
        Float_t Get_ID_dEdeg_mhtdc() const;
        Float_t Get_ID_dEdegoQ_mhtdc() const;

        ClassDefNV(FrsMultiHitItem, 1);

    private:

        Float_t fID_s2x_mhtdc;
        Float_t fID_s4x_mhtdc;
        Float_t fID_s2a_mhtdc;
        Float_t fID_s4a_mhtdc;
        Float_t fID_tof_mhtdc;
        Float_t fID_beta_mhtdc;
        Float_t fID_AoQ_mhtdc;
        Float_t fID_AoQ_corr_mhtdc;
        Float_t fID_z_mhtdc;
        Float_t fID_z2_mhtdc;
        Float_t fID_dEdeg_mhtdc;
        Float_t fID_dEdegoQ_mhtdc;

};


inline uint64_t FrsHitItem::Get_wr_t() const
{
    return fwr_t;
}

inline uint16_t FrsHitItem::Get_tpat() const
{
    return ftpat;
}

inline Float_t FrsHitItem::Get_ID_x2() const
{
    return fID_x2;
}

inline Float_t FrsHitItem::Get_ID_y2() const
{
    return fID_y2;
}

inline Float_t FrsHitItem::Get_ID_x4() const
{
    return fID_x4;
}

inline Float_t FrsHitItem::Get_ID_y4() const
{
    return fID_y4;
}

inline Float_t FrsHitItem::Get_ID_a2() const
{
    return fID_a2;
}

inline Float_t FrsHitItem::Get_ID_b2() const
{
    return fID_b2;
}

inline Float_t FrsHitItem::Get_ID_a4() const
{
    return fID_a4;
}

inline Float_t FrsHitItem::Get_ID_b4() const
{
    return fID_b4;
}

inline Float_t FrsHitItem::Get_ID_AoQ() const
{
    return fID_AoQ;
}

inline Float_t FrsHitItem::Get_ID_AoQ_driftcorr() const
{
    return fID_AoQ_driftcorr;
}

inline Float_t FrsHitItem::Get_ID_AoQ_corr() const
{
    return fID_AoQ_corr;
}

inline Float_t FrsHitItem::Get_ID_z() const
{
    return fID_z;
}

inline Float_t FrsHitItem::Get_ID_z_driftcorr() const
{
    return fID_z_driftcorr;
}

inline Float_t FrsHitItem::Get_ID_z2() const
{
    return fID_z2;
}

inline Float_t FrsHitItem::Get_ID_beta() const
{
    return fID_beta;
}

inline Float_t FrsHitItem::Get_ID_dEdeg() const
{
    return fID_dEdeg;
}

inline Float_t FrsHitItem::Get_ID_dEdegoQ() const
{
    return fID_dEdegoQ;
}

inline Float_t FrsHitItem::Get_ID_rho(int index) const
{
    return fID_rho[index];
}

inline Float_t FrsHitItem::Get_ID_brho(int index) const
{
    return fID_brho[index];
}

inline Float_t FrsHitItem::Get_music_dE(int index) const
{
    return fmusic_dE[index];
}

inline Float_t FrsHitItem::Get_music_dE_cor(int index) const
{
    return fmusic_dE_cor[index];
}

inline uint32_t FrsHitItem::Get_time_in_ms() const
{
    return ftime_in_ms;
}

inline uint32_t FrsHitItem::Get_ibin_for_s() const
{
    return fibin_for_s;
}

inline uint32_t FrsHitItem::Get_ibin_for_100ms() const
{
    return fibin_for_100ms;
}

inline uint32_t FrsHitItem::Get_ibin_for_spill() const
{
    return fibin_for_spill;
}

inline uint32_t FrsHitItem::Get_increase_sc_temp_main(int index) const
{
    return fincrease_sc_temp_main[index];
}

inline uint32_t FrsHitItem::Get_increase_sc_temp_user(int index) const
{
    return fincrease_sc_temp_user[index];
}

inline uint32_t FrsHitItem::Get_increase_sc_temp2() const
{
    return fincrease_sc_temp2;
}

inline uint32_t FrsHitItem::Get_increase_sc_temp3() const
{
    return fincrease_sc_temp3;
}

inline uint32_t FrsHitItem::Get_extraction_time_ms() const
{
    return fextraction_time_ms;
}
inline uint32_t FrsHitItem::Get_ibin_clean_for_s() const
{
    return fibin_clean_for_s;
}

inline uint32_t FrsHitItem::Get_ibin_clean_for_100ms() const
{
    return fibin_clean_for_100ms;
}

inline uint32_t FrsHitItem::Get_ibin_clean_for_spill() const
{
    return fibin_clean_for_spill;
}

inline Float_t FrsMultiHitItem::Get_ID_s2x_mhtdc() const
{
    return fID_s2x_mhtdc;
}
inline Float_t FrsMultiHitItem::Get_ID_s4x_mhtdc() const
{
    return fID_s4x_mhtdc;
}
inline Float_t FrsMultiHitItem::Get_ID_beta_mhtdc() const
{
    return fID_beta_mhtdc;
}

inline Float_t FrsMultiHitItem::Get_ID_AoQ_mhtdc() const
{
    return fID_AoQ_mhtdc;
}

inline Float_t FrsMultiHitItem::Get_ID_AoQ_corr_mhtdc() const
{
    return fID_AoQ_corr_mhtdc;
}

inline Float_t FrsMultiHitItem::Get_ID_z_mhtdc() const
{
    return fID_z_mhtdc;
}

inline Float_t FrsMultiHitItem::Get_ID_z2_mhtdc() const
{
    return fID_z2_mhtdc;
}

inline Float_t FrsMultiHitItem::Get_ID_dEdeg_mhtdc() const
{
    return fID_dEdeg_mhtdc;
}

inline Float_t FrsMultiHitItem::Get_ID_dEdegoQ_mhtdc() const
{
    return fID_dEdegoQ_mhtdc;
}


#endif
