/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                             C.E. Jones                                     *
 *                              06.05.25                                      *
 ******************************************************************************/

#include "FrsCalData.h"

FrsCalSciItem::FrsCalSciItem() {}

void FrsCalSciItem::SetMetaData(int64_t wr, TString setup)
{
    fwr_t = wr;
    setup_file = setup;
}

void FrsCalSciItem::SetAll(UInt_t de11l,
                        UInt_t de11r,
                        UInt_t de21l,
                        UInt_t de21r,
                        UInt_t de22l,
                        UInt_t de22r,
                        UInt_t de31l,
                        UInt_t de31r,
                        UInt_t de41l,
                        UInt_t de41r,
                        UInt_t de42l,
                        UInt_t de42r,
                        UInt_t de43l,
                        UInt_t de43r,
                        UInt_t de81l,
                        UInt_t de81r,
                        UInt_t dt11l_11r,
                        UInt_t dt21l_21r,
                        UInt_t dt22l_22r,
                        UInt_t dt41l_41r,
                        UInt_t dt42l_42r,
                        UInt_t dt43l_43r,
                        UInt_t dt81l_81r,
                        UInt_t dt11l_21l,
                        UInt_t dt11r_21r,
                        UInt_t dt21l_41l,
                        UInt_t dt21r_41r,
                        UInt_t dt42r_21r,
                        UInt_t dt42l_21l,
                        UInt_t dt21l_81l,
                        UInt_t dt21r_81r,
                        UInt_t dt22l_41l,
                        UInt_t dt22r_41r,
                        UInt_t dt22l_81l,
                        UInt_t dt22r_81r,
                        std::vector<Int_t> sci11la_hits,
                        std::vector<Int_t> sci11lb_hits,
                        std::vector<Int_t> sci11lc_hits,
                        std::vector<Int_t> sci11ld_hits,
                        std::vector<Int_t> sci11ra_hits,
                        std::vector<Int_t> sci11rb_hits,
                        std::vector<Int_t> sci11rc_hits,
                        std::vector<Int_t> sci11rd_hits,
                        std::vector<Int_t> sci21l_hits,
                        std::vector<Int_t> sci21r_hits,
                        std::vector<Int_t> sci22l_hits,
                        std::vector<Int_t> sci22r_hits,
                        std::vector<Int_t> sci31l_hits,
                        std::vector<Int_t> sci31r_hits,
                        std::vector<Int_t> sci41l_hits,
                        std::vector<Int_t> sci41r_hits,
                        std::vector<Int_t> sci42l_hits,
                        std::vector<Int_t> sci42r_hits,
                        std::vector<Int_t> sci43l_hits,
                        std::vector<Int_t> sci43r_hits,
                        std::vector<Int_t> sci81l_hits,
                        std::vector<Int_t> sci81r_hits)
{
    de_11l = de11l;
    de_11r = de11r;
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
    dt_11l_11r = dt11l_11r;
    dt_21l_21r = dt21l_21r;
    dt_22l_22r = dt22l_22r;
    dt_41l_41r = dt41l_41r;
    dt_42l_42r = dt42l_42r;
    dt_43l_43r = dt43l_43r;
    dt_81l_81r = dt81l_81r;
    dt_11l_21l = dt11l_21l;
    dt_11r_21r = dt11r_21r;
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
    mhtdc_sci11la_hits = sci11la_hits;
    mhtdc_sci11lb_hits = sci11lb_hits;
    mhtdc_sci11lc_hits = sci11lc_hits;
    mhtdc_sci11ld_hits = sci11ld_hits;
    mhtdc_sci11ra_hits = sci11ra_hits;
    mhtdc_sci11rb_hits = sci11rb_hits;
    mhtdc_sci11rc_hits = sci11rc_hits;
    mhtdc_sci11rd_hits = sci11rd_hits;
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

FrsCalMusicItem::FrsCalMusicItem() {}

void FrsCalMusicItem::SetMetaData(int64_t wr, TString setup)
{
    fwr_t = wr;
    setup_file = setup;
}

void FrsCalMusicItem::SetAll(UInt_t music21_e[8],
                            UInt_t music22_e[8],
                            UInt_t music41_e[8],
                            UInt_t music42_e[8],
                            UInt_t music43_e[8])
{
    for (int i = 0; i < 8; i++)
    {
        fmusic21_e[i] = music21_e[i];
        fmusic22_e[i] = music22_e[i];
        fmusic41_e[i] = music41_e[i];
        fmusic42_e[i] = music42_e[i];
        fmusic43_e[i] = music43_e[i];
    }
}


FrsCalTpcItem::FrsCalTpcItem() {}

void FrsCalTpcItem::SetMetaData(int64_t wr, TString setup)
{
    fwr_t = wr;
    setup_file = setup;
}

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
                    Float_t tpc21_22_music21_x,
                    Float_t tpc21_22_music21_y,
                    Float_t tpc21_22_music22_x,
                    Float_t tpc21_22_music22_y,
                    Float_t tpc23_24_music21_x,
                    Float_t tpc23_24_music21_y,
                    Float_t tpc23_24_music22_x,
                    Float_t tpc23_24_music22_y,
                    Float_t tpc22_24_music21_x,
                    Float_t tpc22_24_music21_y,
                    Float_t tpc22_24_music22_x,
                    Float_t tpc22_24_music22_y,
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
    ftpc21_22_music21_x = tpc21_22_music21_x;
    ftpc21_22_music21_y = tpc21_22_music21_y;
    ftpc21_22_music22_x = tpc21_22_music22_x;
    ftpc21_22_music22_y = tpc21_22_music22_y;
    ftpc23_24_music21_x = tpc23_24_music21_x;
    ftpc23_24_music21_y = tpc23_24_music21_y;
    ftpc23_24_music22_x = tpc23_24_music22_x;
    ftpc23_24_music22_y = tpc23_24_music22_y;
    ftpc22_24_music21_x = tpc22_24_music21_x;
    ftpc22_24_music21_y = tpc22_24_music21_y;
    ftpc22_24_music22_x = tpc22_24_music22_x;
    ftpc22_24_music22_y = tpc22_24_music22_y;
    ftpc_music41_x = tpc_music41_x;
    ftpc_music42_x = tpc_music42_x;
    ftpc_music43_x = tpc_music43_x;
}

ClassImp(FrsCalTpcItem)