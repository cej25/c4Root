#include "FrsTPCCalData.h"

FrsTPCCalItem::FrsTPCCalItem()
{

}

void FrsTPCCalItem::SetAll(Float_t* tpc_x, // [7]
                    Bool_t* b_tpc_xy, // [7]
                    Int_t** tpc_csum, // [7][4]
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
    ftpc_x = tpc_x;
    fb_tpc_xy = b_tpc_xy;
    ftpc_csum = tpc_csum;
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

void FrsTPCCalItem::Reset()
{   
    ftpc_x = {0};
    fb_tpc_xy = {0};
    ftpc_csum = {0};
    ftpc_angle_x_s2_foc_21_22 = 0;
    ftpc_angle_y_s2_foc_21_22 = 0;
    ftpc_x_s2_foc_21_22 = 0;
    ftpc_y_s2_foc_21_22 = 0;
    ftpc21_22_sc21_x = 0;
    ftpc21_22_sc22_x = 0;
    ftpc_angle_x_s2_foc_23_24 = 0;
    ftpc_angle_y_s2_foc_23_24 = 0;
    ftpc_x_s2_foc_23_24 = 0;
    ftpc_y_s2_foc_23_24 = 0;
    ftpc23_24_sc21_x = 0;
    ftpc23_24_sc21_y = 0;
    ftpc23_24_sc22_x = 0;
    ftpc23_24_sc22_y = 0;
    ftpc_angle_x_s2_foc_22_24 = 0;
    ftpc_angle_y_s2_foc_22_24 = 0;
    ftpc_x_s2_foc_22_24 = 0;
    ftpc_y_s2_foc_22_24 = 0;
    ftpc_angle_x_s4 = 0;
    ftpc_angle_y_s4 = 0;
    ftpc_x_s4 = 0;
    ftpc_y_s4 = 0;
    ftpc_sc41_x = 0;
    ftpc_sc41_y = 0;
    ftpc_sc42_x = 0;
    ftpc_sc42_y = 0;
    ftpc_sc43_x = 0;
    ftpc_music41_x = 0;
    ftpc_music42_x = 0;
    ftpc_music43_x = 0;
}


ClassImp(FrsTPCCalItem)