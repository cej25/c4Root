#ifndef FrsCalData_H
#define FrsCalData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class FrsCalSciItem : public TObject
{
    public:
        FrsCalSciItem();

        void SetAll(uint32_t de21l,
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
                    std::vector<uint32_t> sci81r_hits);

        // Getters

        ClassDef(FrsCalSciItem, 1);

    private:

        // TAC dE
        uint32_t de_21l;
        uint32_t de_21r;
        uint32_t de_22l;
        uint32_t de_22r;
        uint32_t de_31l;
        uint32_t de_31r;
        uint32_t de_41l;
        uint32_t de_41r;
        uint32_t de_42l;
        uint32_t de_42r;
        uint32_t de_43l;
        uint32_t de_43r;
        uint32_t de_81l;
        uint32_t de_81r;

        // TAC dT
        uint32_t dt_21l_21r;
        uint32_t dt_22l_22r;
        uint32_t dt_41l_41r;
        uint32_t dt_42l_42r;
        uint32_t dt_43l_43r;
        uint32_t dt_81l_81r;
        uint32_t dt_21l_41l;
        uint32_t dt_21r_41r;
        uint32_t dt_42r_21r;
        uint32_t dt_42l_21l;
        uint32_t dt_21l_81l;
        uint32_t dt_21r_81r;
        uint32_t dt_22l_41l;
        uint32_t dt_22r_41r;
        uint32_t dt_22l_81l;
        uint32_t dt_22r_81r;

        // MHTDC
        std::vector<uint32_t> mhtdc_sci11_hits;
        std::vector<uint32_t> mhtdc_sci21l_hits;
        std::vector<uint32_t> mhtdc_sci21r_hits;
        std::vector<uint32_t> mhtdc_sci22l_hits;
        std::vector<uint32_t> mhtdc_sci22r_hits;
        std::vector<uint32_t> mhtdc_sci31l_hits;
        std::vector<uint32_t> mhtdc_sci31r_hits;
        std::vector<uint32_t> mhtdc_sci41l_hits;
        std::vector<uint32_t> mhtdc_sci41r_hits;
        std::vector<uint32_t> mhtdc_sci42l_hits;
        std::vector<uint32_t> mhtdc_sci42r_hits;
        std::vector<uint32_t> mhtdc_sci43l_hits;
        std::vector<uint32_t> mhtdc_sci43r_hits;
        std::vector<uint32_t> mhtdc_sci81l_hits;
        std::vector<uint32_t> mhtdc_sci81r_hits;
   
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
                    Float_t tpc_music41_x,
                    Float_t tpc_music42_x,
                    Float_t tpc_music43_x);

        // Getters..

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
        Float_t ftpc_music41_x;
        Float_t ftpc_music42_x;
        Float_t ftpc_music43_x;

};



#endif 