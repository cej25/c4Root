#ifndef FrsTPCCalData_H
#define FrsTPCCalData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsTPCCalData : public TObject
{
    public:
        FrsTPCCalData();

        FrsTPCCalData(Bool_t* b_tpc_de,
                    Float_t* tpc_x,
                    Float_t* tpc_y,
                    Bool_t* b_tpc_xy,
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

        virtual ~FrsTPCCalData() {}

        inline const Bool_t* Get_b_tpc_xy() const { return fb_tpc_xy; }
        inline const Float_t Get_tpc_x_s2_foc_21_22() const { return ftpc_x_s2_foc_21_22; }
        inline const Float_t Get_tpc_y_s2_foc_21_22() const { return ftpc_y_s2_foc_21_22; }
        inline const Float_t Get_tpc_angle_x_s2_foc_21_22() const { return ftpc_angle_x_s2_foc_21_22; }
        inline const Float_t Get_tpc_angle_y_s2_foc_21_22() const { return ftpc_angle_y_s2_foc_21_22; }
        inline const Float_t Get_tpc_x_s2_foc_22_24() const { return ftpc_x_s2_foc_22_24; }
        inline const Float_t Get_tpc_y_s2_foc_22_24() const { return ftpc_y_s2_foc_22_24; }
        inline const Float_t Get_tpc_angle_x_s2_foc_22_24() const { return ftpc_angle_x_s2_foc_22_24; }
        inline const Float_t Get_tpc_angle_y_s2_foc_22_24() const { return ftpc_angle_y_s2_foc_22_24; }
        inline const Float_t Get_tpc_x_s2_foc_23_24() const { return ftpc_x_s2_foc_23_24; }
        inline const Float_t Get_tpc_y_s2_foc_23_24() const { return ftpc_y_s2_foc_23_24; }
        inline const Float_t Get_tpc_angle_x_s2_foc_23_24() const { return ftpc_angle_x_s2_foc_23_24; }
        inline const Float_t Get_tpc_angle_y_s2_foc_23_24() const { return ftpc_angle_y_s2_foc_23_24; }
        inline const Float_t Get_tpc_angle_x_s4() const { return ftpc_angle_x_s4; }
        inline const Float_t Get_tpc_angle_y_s4() const { return ftpc_angle_y_s4; }
        inline const Float_t Get_tpc_x_s4() const { return ftpc_x_s4; }
        inline const Float_t Get_tpc_y_s4() const { return ftpc_y_s4; }

        inline const Float_t Get_tpc21_22_sc21_x() const { return ftpc21_22_sc21_x; }
        inline const Float_t Get_tpc23_24_sc21_x() const { return ftpc23_24_sc21_x; }
        inline const Float_t Get_tpc21_22_sc22_x() const { return ftpc21_22_sc22_x; }
        inline const Float_t Get_tpc23_24_sc22_x() const { return ftpc23_24_sc22_x; }

        inline const Float_t Get_tpc_music41_x() const { return ftpc_music41_x; }
        inline const Float_t Get_tpc_music42_x() const { return ftpc_music42_x; }

    private:
        Bool_t fb_tpc_de[7];
        Float_t ftpc_x[7];
        Float_t ftpc_y[7];
        Bool_t fb_tpc_xy[7];
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
    
    public:
        ClassDef(FrsTPCCalData, 1)
};

#endif