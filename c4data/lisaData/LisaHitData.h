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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

#ifndef LisaHitData_H
#define LisaHitData_H

#include "TObject.h"
#include <vector>
#include "TString.h"
#include "TVector.h"


class LisaHitItem : public TObject
{
    public:
        LisaHitItem();

        void SetAll(uint64_t wr,
                    uint16_t w_id,
                    int b_id,
                    int layer,
                    TString c,
                    int xpos,
                    int ypos,
                    float thick,
                    float e, 
                    float e_MWD,
                    std::vector<float> tr,
                    //std::vector<int16_t> tr_MWD,
                    std::vector<int16_t> tr_x,
                    float e_GM,
                    float e_MWD_GM,
                    float dedx,
                    float dedx_GM,
                    std::vector<float> z,
                    std::vector<float> b0,
                    std::vector<float> b_l,
                    std::vector<float> b1,
                    std::vector<float> b2,
                    std::vector<float> b3,
                    std::vector<float> b4,
                    std::vector<float> b5,
                    uint64_t evt_t,
                    uint64_t ch_t,
                    uint64_t evtno,
                    int pu,
                    //int pu_MWD,
                    int ov,
                    int greact,
                    int lreact);
                    //int ov_MWD);

        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        int Get_board_id() const;
        int Get_layer_id() const;
        TString Get_city() const;
        int Get_xposition() const;
        int Get_yposition() const;
        float Get_thickness() const;
        float Get_energy() const;
        float Get_energy_MWD() const;
        std::vector<float> Get_trace_febex() const;
        //std::vector<int16_t> Get_trace_MWD() const;
        std::vector<int16_t> Get_trace_x() const;
        float Get_energy_GM() const;
        float Get_energy_MWD_GM() const;
        float Get_de_dx() const;
        float Get_de_dx_GM() const;
        std::vector<float> Get_Z_lisa() const;
        std::vector<float> Get_beta_s1s2_correlated() const;
        std::vector<float> Get_beta_before_L1() const;
        std::vector<float> Get_beta_after_L1() const;
        std::vector<float> Get_beta_after_L2() const;
        std::vector<float> Get_beta_after_L3() const;
        std::vector<float> Get_beta_after_L4() const;
        std::vector<float> Get_beta_after_L5() const;
        uint64_t Get_board_event_time() const;
        uint64_t Get_channel_event_time() const;
        uint64_t Get_evtno();
        int Get_pileup() const;
        //int Get_pileup_MWD() const;
        int Get_overflow() const;
        //int Get_overflow_MWD() const;
        int Get_Global_Reactions() const;
        int Get_Lisa_Reactions() const;


        // Getters
        ClassDef(LisaHitItem, 1);
    private:
        uint64_t wr_t;
        uint16_t wr_id;
        int board_id;
        int layer_id;
        TString city; // name
        int xposition;
        int yposition;
        float thickness;
        float energy; // double? int?
        float energy_MWD; // double? int?
        std::vector<float> trace_febex;
        //std::vector<int16_t> trace_MWD;
        std::vector<int16_t> trace_x;
        float energy_GM;
        float energy_MWD_GM;
        float de_dx;
        float de_dx_GM;
        std::vector<float> z_lisa;
        std::vector<float> beta0;
        std::vector<float> beta_before_lisa;
        std::vector<float> beta1;
        std::vector<float> beta2;
        std::vector<float> beta3;
        std::vector<float> beta4;
        std::vector<float> beta5;
        uint64_t board_event_time;
        uint64_t ch_event_time;
        uint64_t event_no;
        int pileup;
        //int pileup_MWD;
        int overflow;
        //int overflow_MWD;
        int global_reactions;
        int lisa_reaction;
        // timing info for correlations

};

inline uint64_t LisaHitItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t LisaHitItem::Get_wr_id() const
{
    return wr_id;
}

inline int LisaHitItem::Get_board_id() const
{
    return board_id;
}

inline int LisaHitItem::Get_layer_id() const
{
    return layer_id;
}

inline TString LisaHitItem::Get_city() const
{
    return city;
}

inline int LisaHitItem::Get_xposition() const
{
    return xposition;
}

inline int LisaHitItem::Get_yposition() const
{
    return yposition;
}

inline float LisaHitItem::Get_thickness() const
{
    return thickness;
}

inline float LisaHitItem::Get_energy() const
{
    return energy;
}

inline float LisaHitItem::Get_energy_MWD() const
{
    return energy_MWD;
}

inline std::vector<float> LisaHitItem::Get_trace_febex() const
{
    return trace_febex;
}

// inline std::vector<int16_t> LisaHitItem::Get_trace_MWD() const
// {
//     return trace_MWD;
// }

inline std::vector<int16_t> LisaHitItem::Get_trace_x() const
{
    return trace_x;
}

inline float LisaHitItem::Get_energy_GM() const
{
    return energy_GM;
}

inline float LisaHitItem::Get_energy_MWD_GM() const
{
    return energy_MWD_GM;
}

inline float LisaHitItem::Get_de_dx() const
{
    return de_dx;
}

inline float LisaHitItem::Get_de_dx_GM() const
{
    return de_dx_GM;
}

inline std::vector<float> LisaHitItem::Get_Z_lisa() const
{
    return z_lisa;
}

inline std::vector<float> LisaHitItem::Get_beta_s1s2_correlated() const
{
    return beta0;
}

inline std::vector<float> LisaHitItem::Get_beta_before_L1() const
{
    return beta_before_lisa;
}

inline std::vector<float> LisaHitItem::Get_beta_after_L1() const
{
    return beta1;
}

inline std::vector<float> LisaHitItem::Get_beta_after_L2() const
{
    return beta2;
}

inline std::vector<float> LisaHitItem::Get_beta_after_L3() const
{
    return beta3;
}

inline std::vector<float> LisaHitItem::Get_beta_after_L4() const
{
    return beta4;
}

inline std::vector<float> LisaHitItem::Get_beta_after_L5() const
{
    return beta5;
}

inline uint64_t LisaHitItem::Get_board_event_time() const
{
    return board_event_time;
}

inline uint64_t LisaHitItem::Get_channel_event_time() const
{
    return ch_event_time;
}

inline int LisaHitItem::Get_pileup() const
{
    return pileup;
}

// inline int LisaHitItem::Get_pileupMWD() const
// {
//     return pileup_MWD;
// }

inline int LisaHitItem::Get_overflow() const
{
    return overflow;
}

// inline int LisaHitItem::Get_overflow_MWD() const
// {
//     return overflow_MWD;
// }

inline int LisaHitItem::Get_Global_Reactions() const
{
    return global_reactions;
}

inline int LisaHitItem::Get_Lisa_Reactions() const
{
    return lisa_reaction;
}


#endif