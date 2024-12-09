#include "FrsCalData.h"

FrsCalSciItem::FrsCalSciItem() {}

void FrsCalSciItem::SetAll(uint32_t de21l,
                        uint32_t de21r,
                        uint32_t de22l,
                        uint32_t de22r,
                        uint32_t de31l,
                        uint32_t de31r,
                        uint32_t de41l,
                        uint32_t de41r,
                        uint32_t de42l,
                        uint32_t de42r,
                        uint32_t de43l,
                        uint32_t de43r,
                        uint32_t de81l,
                        uint32_t de81r,
                        uint32_t dt21l_21r,
                        uint32_t dt22l_22r,
                        uint32_t dt41l_41r,
                        uint32_t dt42l_42r,
                        uint32_t dt43l_43r,
                        uint32_t dt81l_81r,
                        uint32_t dt21l_41l,
                        uint32_t dt21r_41r,
                        uint32_t dt42r_21r,
                        uint32_t dt42l_21l,
                        uint32_t dt21l_81l,
                        uint32_t dt21r_81r,
                        uint32_t dt22l_41l,
                        uint32_t dt22r_41r,
                        uint32_t dt22l_81l,
                        uint32_t dt22r_81r,
                        std::vector<uint32_t> sci11_hits,
                        std::vector<uint32_t> sci21l_hits,
                        std::vector<uint32_t> sci21r_hits,
                        std::vector<uint32_t> sci22l_hits,
                        std::vector<uint32_t> sci22r_hits,
                        std::vector<uint32_t> sci31l_hits,
                        std::vector<uint32_t> sci31r_hits,
                        std::vector<uint32_t> sci41l_hits,
                        std::vector<uint32_t> sci41r_hits,
                        std::vector<uint32_t> sci42l_hits,
                        std::vector<uint32_t> sci42r_hits,
                        std::vector<uint32_t> sci43l_hits,
                        std::vector<uint32_t> sci43r_hits,
                        std::vector<uint32_t> sci81l_hits,
                        std::vector<uint32_t> sci81r_hits)
{
    de_21l = de21l;
    de_21r = de21r;
    de_22l = de22l;
    de_22r = de22r;
    de_31l = de31l;
    de_31r = de31r;
    de_41l = de41l;
    de_41r = de41r;
    de_42l = de42l;
    de_42r = de42r;
    de_43l = de43l;
    de_43r = de43r;
    de_81l = de81l;
    de_81r = de81r;
    dt_21l_21r = dt21l_21r;
    dt_22l_22r = dt22l_22r;
    dt_41l_41r = dt41l_41r;
    dt_42l_42r = dt42l_42r;
    dt_43l_43r = dt43l_43r;
    dt_81l_81r = dt81l_81r;
    dt_21l_41l = dt21l_41l;
    dt_21r_41r = dt21r_41r;
    dt_42r_21r = dt42r_21r;
    dt_42l_21l = dt42l_21l;
    dt_21l_81l = dt21l_81l;
    dt_21r_81r = dt21r_81r;
    dt_22l_41l = dt22l_41l;
    dt_22r_41r = dt22r_41r;
    dt_22l_81l = dt22l_81l;
    dt_22r_81r = dt22r_81r;
    mhtdc_sci11_hits  = sci11_hits;
    mhtdc_sci21l_hits = sci21l_hits;
    mhtdc_sci21r_hits = sci21r_hits;
    mhtdc_sci22l_hits = sci22l_hits;
    mhtdc_sci22r_hits = sci22r_hits;
    mhtdc_sci31l_hits = sci31l_hits;
    mhtdc_sci31r_hits = sci31r_hits;
    mhtdc_sci41l_hits = sci41l_hits;
    mhtdc_sci41r_hits = sci41r_hits;
    mhtdc_sci42l_hits = sci42l_hits;
    mhtdc_sci42r_hits = sci42r_hits;
    mhtdc_sci43l_hits = sci43l_hits;
    mhtdc_sci43r_hits = sci43r_hits;
    mhtdc_sci81l_hits = sci81l_hits;
    mhtdc_sci81r_hits = sci81r_hits;
}

ClassImp(FrsCalSciItem)


FrsCalTpcItem::FrsCalTpcItem() {}

void FrsCalTpcItem::SetAll(Float_t tpc_x[7],
                    Bool_t b_tpc_xy[7],
                    Int_t tpc_csum[7][4],
                    Float_t tpc_angle_x_s2_foc_21_22,
                    Float_t tpc_angle_y_s2_foc_21_22,
                    Float_t tpc_x_s2_foc_21_22,
                    Float_t tpc_y_s2_foc_21_22,
                    Float_t tpc21_22_sc21_x,
                    Float_t tpc21_22_sc22_x,
                    Float_t tpc_angle_x_s2_foc_23_24,
                    Float_t tpc_angle_y_s2_foc_23_24,
                    Float_t tpc_x_s2_foc_23_24,
                    Float_t tpc_y_s2_foc_23_24,
                    Float_t tpc23_24_sc21_x,
                    Float_t tpc23_24_sc21_y,
                    Float_t tpc23_24_sc22_x,
                    Float_t tpc23_24_sc22_y,
                    Float_t tpc_angle_x_s2_foc_22_24,
                    Float_t tpc_angle_y_s2_foc_22_24,
                    Float_t tpc_x_s2_foc_22_24,
                    Float_t tpc_y_s2_foc_22_24,
                    Float_t tpc_angle_x_s4,
                    Float_t tpc_angle_y_s4,
                    Float_t tpc_x_s4,
                    Float_t tpc_y_s4,
                    Float_t tpc_sc41_x,
                    Float_t tpc_sc41_y,
                    Float_t tpc_sc42_x,
                    Float_t tpc_sc42_y,
                    Float_t tpc_sc43_x,
                    Float_t tpc_music41_x,
                    Float_t tpc_music42_x,
                    Float_t tpc_music43_x)
{
    for (int i = 0; i < 7; i++) ftpc_x[i] = tpc_x[i];
    for (int i = 0; i < 7; i++) fb_tpc_xy[i] = b_tpc_xy[i];
    for (int i = 0; i < 7; i++) for (int j = 0; j < 4; j++) ftpc_csum[i][j] = tpc_csum[i][j];
    ftpc_angle_x_s2_foc_21_22 = tpc_angle_x_s2_foc_21_22;
    ftpc_angle_y_s2_foc_21_22 = tpc_angle_y_s2_foc_21_22;
    ftpc_x_s2_foc_21_22 = tpc_x_s2_foc_21_22;
    ftpc_y_s2_foc_21_22 = tpc_y_s2_foc_21_22;
    ftpc21_22_sc21_x = tpc21_22_sc21_x;
    ftpc21_22_sc22_x = tpc21_22_sc22_x;
    ftpc_angle_x_s2_foc_23_24 = tpc_angle_x_s2_foc_23_24;
    ftpc_angle_y_s2_foc_23_24 = tpc_angle_y_s2_foc_23_24;
    ftpc_x_s2_foc_23_24 = tpc_x_s2_foc_23_24;
    ftpc_y_s2_foc_23_24 = tpc_y_s2_foc_23_24;
    ftpc23_24_sc21_x = tpc23_24_sc21_x;
    ftpc23_24_sc21_y = tpc23_24_sc21_y;
    ftpc23_24_sc22_x = tpc23_24_sc22_x;
    ftpc23_24_sc22_y = tpc23_24_sc22_y;
    ftpc_angle_x_s2_foc_22_24 = tpc_angle_x_s2_foc_22_24;
    ftpc_angle_y_s2_foc_22_24 = tpc_angle_y_s2_foc_22_24;
    ftpc_x_s2_foc_22_24 = tpc_x_s2_foc_22_24;
    ftpc_y_s2_foc_22_24 = tpc_y_s2_foc_22_24;
    ftpc_angle_x_s4 = tpc_angle_x_s4;
    ftpc_angle_y_s4 = tpc_angle_y_s4;
    ftpc_x_s4 = tpc_x_s4;
    ftpc_y_s4 = tpc_y_s4;
    ftpc_sc41_x = tpc_sc41_x;
    ftpc_sc41_y = tpc_sc41_y;
    ftpc_sc42_x = tpc_sc42_x;
    ftpc_sc42_y = tpc_sc42_y;
    ftpc_sc43_x = tpc_sc43_x;
    ftpc_music41_x = tpc_music41_x;
    ftpc_music42_x = tpc_music42_x;
    ftpc_music43_x = tpc_music43_x;
}

ClassImp(FrsCalTpcItem)