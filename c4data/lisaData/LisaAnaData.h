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

#ifndef LisaAnaData_H
#define LisaAnaData_H

#include "TObject.h"
#include "TVector.h"
#include <vector>
#include <ROOT/RVec.hxx>

// This is the adjustment to use TVectors instead of std::vector
//This was to try to read vectors of vectors form external macro without sourcing c4. It does not work.
//template <typename T>
//using StdVector = std::vector<T>;

//Not in use.
// class LisaAnaData : public TObject
// {
//     public:
//         LisaAnaData();

//         // Destructor
//         virtual ~LisaAnaData() {}
       
//     protected:


//     public:
//         ClassDef(LisaAnaData, 1)
// };

class LisaAnaItem : public TObject
{
    public:
        LisaAnaItem();

        void SetAll(uint64_t wr,
                    uint16_t id,
                    int b_id,
                    uint64_t ev_time,
                    int ch_id,
                    uint64_t ch_time,
                    int p,
                    //int p_MWD,
                    int o,
                    //int o_MWD,
                    float ch_energy,
                    float ch_energy_MWD,
                    int ch_id_traces,
                    std::vector<float> tr,
                    std::vector<float> tr_0,
                    std::vector<float> tr_MWD,
                    std::vector<int16_t> tr_x);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        int Get_board_id() const;
        uint64_t Get_board_event_time() const;
        int Get_channel_id() const;
        uint64_t Get_channel_time() const;
        int Get_pileup() const;
        //int Get_pileup_MWD() const;
        int Get_overflow() const;
        //int Get_overflow_MWD() const;
        float Get_channel_energy() const;
        float Get_channel_energy_MWD() const;
        int Get_channel_id_traces() const;
        std::vector<float> Get_trace_febex() const;
        std::vector<float> Get_trace_febex_0() const;
        std::vector<float> Get_trace_MWD() const;
        std::vector<int16_t> Get_trace_x() const;

        // Getters
        ClassDef(LisaAnaItem, 1);
    private:

        uint64_t wr_t;
        uint16_t wr_id;
        int board_id;
        uint64_t board_event_time;
        int channel_id;
        uint64_t channel_time;
        int pileup;
        //int pileup_MWD;
        int overflow;
        //int overflow_MWD;
        float channel_energy;
        float channel_energy_MWD;
        int channel_id_traces;
        std::vector<float> trace_febex;
        std::vector<float> trace_febex_0;
        std::vector<float> trace_MWD;
        std::vector<int16_t> trace_x;

};

inline uint64_t LisaAnaItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t LisaAnaItem::Get_wr_id() const
{
    return wr_id;
}

inline int LisaAnaItem::Get_board_id() const
{
    return board_id;
}

inline uint64_t LisaAnaItem::Get_board_event_time() const
{
    return board_event_time;
}

inline int LisaAnaItem::Get_channel_id() const
{
    return channel_id;
}

inline uint64_t LisaAnaItem::Get_channel_time() const
{
    return channel_time;
}

inline int LisaAnaItem::Get_pileup() const
{
    return pileup;
}

// inline int LisaAnaItem::Get_pileup_MWD() const
// {
//     return pileup_MWD;
// }

inline int LisaAnaItem::Get_overflow() const
{
    return overflow;
}

// inline int LisaAnaItem::Get_overflow_MWD() const
// {
//     return overflow_MWD;
// }

inline float LisaAnaItem::Get_channel_energy() const
{
    return channel_energy;
}

inline float LisaAnaItem::Get_channel_energy_MWD() const
{
    return channel_energy_MWD;
}

inline int LisaAnaItem::Get_channel_id_traces() const
{
    return channel_id_traces;
}

inline std::vector<float> LisaAnaItem::Get_trace_febex() const
{
    return trace_febex;
}

inline std::vector<float> LisaAnaItem::Get_trace_febex_0() const
{
    return trace_febex_0;
}

inline std::vector<float> LisaAnaItem::Get_trace_MWD() const
{
    return trace_MWD;
}

inline std::vector<int16_t> LisaAnaItem::Get_trace_x() const
{
    return trace_x;
}

#endif
