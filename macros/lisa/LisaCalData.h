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

#ifndef LisaCalData_H
#define LisaCalData_H

#include "TObject.h"
#include <vector>
#include "TString.h"
#include <ROOT/RVec.hxx>
#include "TVector.h"

//Debugging. Replaced std::string with TString 8nov24

class LisaCalItem : public TObject
{
    public:
        LisaCalItem();

        void SetAll(uint64_t wr,
                    uint16_t w_id,
                    uint8_t b_id,
                    int layer,
                    TString c,
                    int xpos,
                    int ypos,
                    double e, // uint32_t e?
                    double e_MWD,
                    std::vector<int16_t> tr,
                    std::vector<int16_t> tr_MWD,
                    std::vector<int16_t> tr_x,
                    double e_GM,
                    double e_MWD_GM,
                    uint64_t evt_t,
                    uint64_t ch_t,
                    uint64_t evtno,
                    int pu,
                    //int pu_MWD,
                    int ov);
                    //int ov_MWD);

        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        uint8_t Get_board_id() const;
        int Get_layer_id() const;
        TString Get_city() const;
        int Get_xposition() const;
        int Get_yposition() const;
        double Get_energy() const;
        double Get_energy_MWD() const;
        std::vector<int16_t> Get_trace_febex() const;
        std::vector<int16_t> Get_trace_MWD() const;
        std::vector<int16_t> Get_trace_x() const;
        double Get_energy_GM() const;
        double Get_energy_MWD_GM() const;
        uint64_t Get_board_event_time() const;
        uint64_t Get_channel_event_time() const;
        uint64_t Get_evtno();
        int Get_pileup() const;
        //int Get_pileup_MWD() const;
        int Get_overflow() const;
        //int Get_overflow_MWD() const;


        // Getters
        ClassDef(LisaCalItem, 1);
    private:
        uint64_t wr_t;
        uint16_t wr_id;
        uint8_t board_id;
        int layer_id;
        TString city; // name
        int xposition;
        int yposition;
        double energy; // double? int?
        double energy_MWD; // double? int?
        std::vector<int16_t> trace_febex;
        std::vector<int16_t> trace_MWD;
        std::vector<int16_t> trace_x;
        double energy_GM;
        double energy_MWD_GM;
        uint64_t board_event_time;
        uint64_t ch_event_time;
        uint64_t event_no;
        int pileup;
        //int pileup_MWD;
        int overflow;
        //int overflow_MWD;
        // timing info for correlations

};

inline uint64_t LisaCalItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t LisaCalItem::Get_wr_id() const
{
    return wr_id;
}

inline uint8_t LisaCalItem::Get_board_id() const
{
    return board_id;
}

inline int LisaCalItem::Get_layer_id() const
{
    return layer_id;
}

inline TString LisaCalItem::Get_city() const
{
    return city;
}

inline int LisaCalItem::Get_xposition() const
{
    return xposition;
}

inline int LisaCalItem::Get_yposition() const
{
    return yposition;
}

inline double LisaCalItem::Get_energy() const
{
    return energy;
}

inline double LisaCalItem::Get_energy_MWD() const
{
    return energy_MWD;
}

inline std::vector<int16_t> LisaCalItem::Get_trace_febex() const
{
    return trace_febex;
}

inline std::vector<int16_t> LisaCalItem::Get_trace_MWD() const
{
    return trace_MWD;
}

inline std::vector<int16_t> LisaCalItem::Get_trace_x() const
{
    return trace_x;
}

inline double LisaCalItem::Get_energy_GM() const
{
    return energy_GM;
}

inline double LisaCalItem::Get_energy_MWD_GM() const
{
    return energy_MWD_GM;
}

inline uint64_t LisaCalItem::Get_board_event_time() const
{
    return board_event_time;
}

inline uint64_t LisaCalItem::Get_channel_event_time() const
{
    return ch_event_time;
}

inline int LisaCalItem::Get_pileup() const
{
    return pileup;
}

// inline int LisaCalItem::Get_pileupMWD() const
// {
//     return pileup_MWD;
// }

inline int LisaCalItem::Get_overflow() const
{
    return overflow;
}

// inline int LisaCalItem::Get_overflow_MWD() const
// {
//     return overflow_MWD;
// }


#endif