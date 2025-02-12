#ifndef FrsCalData_H
#define FrsCalData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

typedef Float_t Float_t;
typedef Int_t Int_t;
typedef Bool_t Bool_t;
typedef UInt_t UInt_t;

class FrsCalSciItem : public TObject
{
    public:
        FrsCalSciItem();

        void SetAll(UInt_t de11l,
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
                    UInt_t dt_11l_11r,
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
                    std::vector<Int_t> sci81r_hits);

        // Getters
        UInt_t Get_dE_11l() const { return de_11l; }
        UInt_t Get_dE_11r() const { return de_11r; }
        UInt_t Get_dE_21l() const { return de_21l; }
        UInt_t Get_dE_21r() const { return de_21r; }
        UInt_t Get_dE_22l() const { return de_22l; }
        UInt_t Get_dE_22r() const { return de_22r; }
        UInt_t Get_dE_31l() const { return de_31l; }
        UInt_t Get_dE_31r() const { return de_31r; }
        UInt_t Get_dE_41l() const { return de_41l; }
        UInt_t Get_dE_41r() const { return de_41r; }
        UInt_t Get_dE_42l() const { return de_42l; }
        UInt_t Get_dE_42r() const { return de_42r; }
        UInt_t Get_dE_43l() const { return de_43l; }
        UInt_t Get_dE_43r() const { return de_43r; }
        UInt_t Get_dE_81l() const { return de_81l; }
        UInt_t Get_dE_81r() const { return de_81r; }

        UInt_t Get_dT_11l_11r() const { return dt_11l_11r; }
        UInt_t Get_dT_21l_21r() const { return dt_21l_21r; }
        UInt_t Get_dT_22l_22r() const { return dt_22l_22r; }
        UInt_t Get_dT_41l_41r() const { return dt_41l_41r; }
        UInt_t Get_dT_42l_42r() const { return dt_42l_42r; } 
        UInt_t Get_dT_43l_43r() const { return dt_43l_43r; }
        UInt_t Get_dT_81l_81r() const { return dt_81l_81r; }
        UInt_t Get_dT_11l_21l() const { return dt_11l_21l; }
        UInt_t Get_dT_11r_21r() const { return dt_11r_21r; }
        UInt_t Get_dT_21l_41l() const { return dt_21l_41l; }
        UInt_t Get_dT_21r_41r() const { return dt_21r_41r; }
        UInt_t Get_dT_42l_21l() const { return dt_42l_21l; }
        UInt_t Get_dT_42r_21r() const { return dt_42r_21r; }
        UInt_t Get_dT_21l_81l() const { return dt_21l_81l; }
        UInt_t Get_dT_21r_81r() const { return dt_21r_81r; }
        UInt_t Get_dT_22l_41l() const { return dt_22l_41l; }
        UInt_t Get_dT_22r_41r() const { return dt_22r_41r; }
        UInt_t Get_dT_22l_81l() const { return dt_22l_81l; }
        UInt_t Get_dT_22r_81r() const { return dt_22r_81r; }

        std::vector<Int_t> Get_mhtdc_sci11la_hits() const { return mhtdc_sci11la_hits; }
        std::vector<Int_t> Get_mhtdc_sci11lb_hits() const { return mhtdc_sci11lb_hits; }
        std::vector<Int_t> Get_mhtdc_sci11lc_hits() const { return mhtdc_sci11lc_hits; }
        std::vector<Int_t> Get_mhtdc_sci11ld_hits() const { return mhtdc_sci11ld_hits; }
        std::vector<Int_t> Get_mhtdc_sci11ra_hits() const { return mhtdc_sci11ra_hits; }
        std::vector<Int_t> Get_mhtdc_sci11rb_hits() const { return mhtdc_sci11rb_hits; }
        std::vector<Int_t> Get_mhtdc_sci11rc_hits() const { return mhtdc_sci11rc_hits; }
        std::vector<Int_t> Get_mhtdc_sci11rd_hits() const { return mhtdc_sci11rd_hits; }
        std::vector<Int_t> Get_mhtdc_sci21l_hits() const { return mhtdc_sci21l_hits; }
        std::vector<Int_t> Get_mhtdc_sci21r_hits() const { return mhtdc_sci21r_hits; }
        std::vector<Int_t> Get_mhtdc_sci22l_hits() const { return mhtdc_sci22l_hits; }
        std::vector<Int_t> Get_mhtdc_sci22r_hits() const { return mhtdc_sci22r_hits; }
        std::vector<Int_t> Get_mhtdc_sci31l_hits() const { return mhtdc_sci31l_hits; }
        std::vector<Int_t> Get_mhtdc_sci31r_hits() const { return mhtdc_sci31r_hits; }
        std::vector<Int_t> Get_mhtdc_sci41l_hits() const { return mhtdc_sci41l_hits; }
        std::vector<Int_t> Get_mhtdc_sci41r_hits() const { return mhtdc_sci41r_hits; }
        std::vector<Int_t> Get_mhtdc_sci42l_hits() const { return mhtdc_sci42l_hits; }
        std::vector<Int_t> Get_mhtdc_sci42r_hits() const { return mhtdc_sci42r_hits; }
        std::vector<Int_t> Get_mhtdc_sci43l_hits() const { return mhtdc_sci43l_hits; }
        std::vector<Int_t> Get_mhtdc_sci43r_hits() const { return mhtdc_sci43r_hits; }
        std::vector<Int_t> Get_mhtdc_sci81l_hits() const { return mhtdc_sci81l_hits; }
        std::vector<Int_t> Get_mhtdc_sci81r_hits() const { return mhtdc_sci81r_hits; }

        ClassDef(FrsCalSciItem, 1);

    private:

        // TAC dE
        UInt_t de_11l;
        UInt_t de_11r;
        UInt_t de_21l;
        UInt_t de_21r;
        UInt_t de_22l;
        UInt_t de_22r;
        UInt_t de_31l;
        UInt_t de_31r;
        UInt_t de_41l;
        UInt_t de_41r;
        UInt_t de_42l;
        UInt_t de_42r;
        UInt_t de_43l;
        UInt_t de_43r;
        UInt_t de_81l;
        UInt_t de_81r;

        // TAC dT
        UInt_t dt_11l_11r;
        UInt_t dt_21l_21r;
        UInt_t dt_22l_22r;
        UInt_t dt_41l_41r;
        UInt_t dt_42l_42r;
        UInt_t dt_43l_43r;
        UInt_t dt_81l_81r;
        UInt_t dt_11l_21l;
        UInt_t dt_11r_21r;
        UInt_t dt_21l_41l;
        UInt_t dt_21r_41r;
        UInt_t dt_42l_21l;
        UInt_t dt_42r_21r;
        UInt_t dt_21l_81l;
        UInt_t dt_21r_81r;
        UInt_t dt_22l_41l;
        UInt_t dt_22r_41r;
        UInt_t dt_22l_81l;
        UInt_t dt_22r_81r;

        // MHTDC
        std::vector<Int_t> mhtdc_sci11la_hits;
        std::vector<Int_t> mhtdc_sci11lb_hits;
        std::vector<Int_t> mhtdc_sci11lc_hits;
        std::vector<Int_t> mhtdc_sci11ld_hits;
        std::vector<Int_t> mhtdc_sci11ra_hits;
        std::vector<Int_t> mhtdc_sci11rb_hits;
        std::vector<Int_t> mhtdc_sci11rc_hits;
        std::vector<Int_t> mhtdc_sci11rd_hits;
        std::vector<Int_t> mhtdc_sci21l_hits;
        std::vector<Int_t> mhtdc_sci21r_hits;
        std::vector<Int_t> mhtdc_sci22l_hits;
        std::vector<Int_t> mhtdc_sci22r_hits;
        std::vector<Int_t> mhtdc_sci31l_hits;
        std::vector<Int_t> mhtdc_sci31r_hits;
        std::vector<Int_t> mhtdc_sci41l_hits;
        std::vector<Int_t> mhtdc_sci41r_hits;
        std::vector<Int_t> mhtdc_sci42l_hits;
        std::vector<Int_t> mhtdc_sci42r_hits;
        std::vector<Int_t> mhtdc_sci43l_hits;
        std::vector<Int_t> mhtdc_sci43r_hits;
        std::vector<Int_t> mhtdc_sci81l_hits;
        std::vector<Int_t> mhtdc_sci81r_hits;
   
};

class FrsCalMusicItem : public TObject
{
    public:
        FrsCalMusicItem();

        void SetAll(UInt_t music21_e[8],
                    UInt_t music22_e[8],
                    UInt_t music41_e[8],
                    UInt_t music42_e[8],
                    UInt_t music43_e[8]);

        const UInt_t (&Get_music21_e() const) [8] { return fmusic21_e; }
        const UInt_t (&Get_music22_e() const) [8] { return fmusic22_e; }
        const UInt_t (&Get_music41_e() const) [8] { return fmusic41_e; }
        const UInt_t (&Get_music42_e() const) [8] { return fmusic42_e; }
        const UInt_t (&Get_music43_e() const) [8] { return fmusic43_e; }

        ClassDef(FrsCalMusicItem, 1);
    
    private:

        UInt_t fmusic21_e[8];
        UInt_t fmusic22_e[8];
        UInt_t fmusic41_e[8];
        UInt_t fmusic42_e[8];
        UInt_t fmusic43_e[8];

};

class FrsCalTpcItem : public TObject
{
    public:
        FrsCalTpcItem();

        void SetAll(Float_t tpc_x[7],
                    Bool_t b_tpc_xy[7],
                    Int_t tpc_csum[7][4], // [7][4]
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
                    Float_t tpc_music43_x);

        // Getters..
        const Float_t (&Get_tpc_x() const) [7] { return ftpc_x; }
        const Bool_t (&Get_b_tpc_xy() const) [7] { return fb_tpc_xy; }
        const Int_t (&Get_tpc_csum() const) [7][4] { return ftpc_csum; }
        Float_t Get_tpc_x_s2_foc_21_22() const { return ftpc_x_s2_foc_21_22; }
        Float_t Get_tpc_y_s2_foc_21_22() const { return ftpc_y_s2_foc_21_22; }
        Float_t Get_tpc_angle_x_s2_foc_21_22() const { return ftpc_angle_x_s2_foc_21_22; }
        Float_t Get_tpc_angle_y_s2_foc_21_22() const { return ftpc_angle_y_s2_foc_21_22; }
        Float_t Get_tpc_x_s2_foc_22_24() const { return ftpc_x_s2_foc_22_24; }
        Float_t Get_tpc_y_s2_foc_22_24() const { return ftpc_y_s2_foc_22_24; }
        Float_t Get_tpc_angle_x_s2_foc_22_24() const { return ftpc_angle_x_s2_foc_22_24; }
        Float_t Get_tpc_angle_y_s2_foc_22_24() const { return ftpc_angle_y_s2_foc_22_24; }
        Float_t Get_tpc_x_s2_foc_23_24() const { return ftpc_x_s2_foc_23_24; }
        Float_t Get_tpc_y_s2_foc_23_24() const { return ftpc_y_s2_foc_23_24; }
        Float_t Get_tpc_angle_x_s2_foc_23_24() const { return ftpc_angle_x_s2_foc_23_24; }
        Float_t Get_tpc_angle_y_s2_foc_23_24() const { return ftpc_angle_y_s2_foc_23_24; }
        Float_t Get_tpc_angle_x_s4() const { return ftpc_angle_x_s4; }
        Float_t Get_tpc_angle_y_s4() const { return ftpc_angle_y_s4; }
        Float_t Get_tpc_x_s4() const { return ftpc_x_s4; }
        Float_t Get_tpc_y_s4() const { return ftpc_y_s4; }
        Float_t Get_tpc23_24_sc21_y() const { return ftpc23_24_sc21_y; }
        Float_t Get_tpc23_24_sc22_y() const { return ftpc23_24_sc22_y; }
        Float_t Get_tpc_sc41_x() const { return ftpc_sc41_x; }
        Float_t Get_tpc_sc41_y() const { return ftpc_sc41_y; }
        Float_t Get_tpc_sc42_x() const { return ftpc_sc42_x; }
        Float_t Get_tpc_sc42_y() const { return ftpc_sc42_y; }
        Float_t Get_tpc_sc43_x() const { return ftpc_sc43_x; }
        Float_t Get_tpc21_22_sc21_x() const { return ftpc21_22_sc21_x; }
        Float_t Get_tpc23_24_sc21_x() const { return ftpc23_24_sc21_x; }
        Float_t Get_tpc21_22_sc22_x() const { return ftpc21_22_sc22_x; }
        Float_t Get_tpc23_24_sc22_x() const { return ftpc23_24_sc22_x; }
        Float_t Get_tpc21_22_music21_x() const { return ftpc21_22_music21_x; }
        Float_t Get_tpc21_22_music21_y() const { return ftpc21_22_music21_y; }
        Float_t Get_tpc21_22_music22_x() const { return ftpc21_22_music22_x; }
        Float_t Get_tpc21_22_music22_y() const { return ftpc21_22_music22_y; }
        Float_t Get_tpc23_24_music21_x() const { return ftpc23_24_music21_x; }
        Float_t Get_tpc23_24_music21_y() const { return ftpc23_24_music21_y; }
        Float_t Get_tpc23_24_music22_x() const { return ftpc23_24_music22_x; }
        Float_t Get_tpc23_24_music22_y() const { return ftpc23_24_music22_y; }
        Float_t Get_tpc22_24_music21_x() const { return ftpc22_24_music21_x; }
        Float_t Get_tpc22_24_music21_y() const { return ftpc22_24_music21_y; }
        Float_t Get_tpc22_24_music22_x() const { return ftpc22_24_music22_x; }
        Float_t Get_tpc22_24_music22_y() const { return ftpc22_24_music22_y; }
        Float_t Get_tpc_music41_x() const { return ftpc_music41_x; }
        Float_t Get_tpc_music42_x() const { return ftpc_music42_x; }
        Float_t Get_tpc_music43_x() const { return ftpc_music43_x; }


        ClassDef(FrsCalTpcItem, 1);

    private:

        Bool_t fb_tpc_de[7]; // not used yet, tpc_de not even passed along
        Float_t ftpc_x[7]; // [7]; // used by frs for plotting and sc31
        Float_t ftpc_y[7]; // used by frs for plotting and sc31
        Bool_t fb_tpc_xy[7]; // [7]
        Int_t ftpc_csum[7][4]; //[7][4]
        Float_t ftpc_angle_x_s2_foc_21_22;
        Float_t ftpc_angle_y_s2_foc_21_22;
        Float_t ftpc_x_s2_foc_21_22;
        Float_t ftpc_y_s2_foc_21_22;
        Float_t ftpc21_22_sc21_x;
        Float_t ftpc21_22_sc22_x;
        Float_t ftpc_angle_x_s2_foc_23_24;
        Float_t ftpc_angle_y_s2_foc_23_24;
        Float_t ftpc_x_s2_foc_23_24;
        Float_t ftpc_y_s2_foc_23_24;
        Float_t ftpc23_24_sc21_x;
        Float_t ftpc23_24_sc21_y;
        Float_t ftpc23_24_sc22_x;
        Float_t ftpc23_24_sc22_y;
        Float_t ftpc_angle_x_s2_foc_22_24;
        Float_t ftpc_angle_y_s2_foc_22_24;
        Float_t ftpc_x_s2_foc_22_24;
        Float_t ftpc_y_s2_foc_22_24;
        Float_t ftpc_angle_x_s4;
        Float_t ftpc_angle_y_s4;
        Float_t ftpc_x_s4;
        Float_t ftpc_y_s4;
        Float_t ftpc_sc41_x;
        Float_t ftpc_sc41_y;
        Float_t ftpc_sc42_x;
        Float_t ftpc_sc42_y;
        Float_t ftpc_sc43_x;
        Float_t ftpc21_22_music21_x;
        Float_t ftpc21_22_music21_y;
        Float_t ftpc21_22_music22_x;
        Float_t ftpc21_22_music22_y;
        Float_t ftpc23_24_music21_x;
        Float_t ftpc23_24_music21_y;
        Float_t ftpc23_24_music22_x;
        Float_t ftpc23_24_music22_y;
        Float_t ftpc22_24_music21_x;
        Float_t ftpc22_24_music21_y;
        Float_t ftpc22_24_music22_x;
        Float_t ftpc22_24_music22_y;
        Float_t ftpc_music41_x;
        Float_t ftpc_music42_x;
        Float_t ftpc_music43_x;

};



#endif 