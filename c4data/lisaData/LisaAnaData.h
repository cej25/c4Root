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
#include <vector>

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
                    uint8_t b_id,
                    uint64_t ev_time,
                    uint8_t ch_id,
                    uint64_t ch_time,
                    int p,
                    //int p_MWD,
                    int o,
                    //int o_MWD,
                    uint32_t ch_energy,
                    uint32_t ch_energy_MWD,
                    uint8_t ch_id_traces,
                    std::vector<int16_t> tr,
                    std::vector<int16_t> trace_MWD);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        uint8_t Get_board_id() const;
        uint64_t Get_board_event_time() const;
        uint8_t Get_channel_id() const;
        uint64_t Get_channel_time() const;
        int Get_pileup() const;
        //int Get_pileup_MWD() const;
        int Get_overflow() const;
        //int Get_overflow_MWD() const;
        uint32_t Get_channel_energy() const;
        uint32_t Get_channel_energy_MWD() const;
        uint8_t Get_channel_id_traces() const;
        std::vector<int16_t> Get_trace() const;
        std::vector<int16_t> Get_trace_MWD() const;

        // Getters
        ClassDef(LisaAnaItem, 1);
    private:

        uint64_t wr_t;
        uint16_t wr_id;
        uint8_t board_id;
        uint64_t board_event_time;
        uint8_t channel_id;
        uint64_t channel_time;
        int pileup;
        //int pileup_MWD;
        int overflow;
        //int overflow_MWD;
        uint32_t channel_energy;
        uint32_t channel_energy_MWD;
        uint8_t channel_id_traces;
        std::vector<int16_t> trace;
        std::vector<int16_t> trace_MWD;

};

inline uint64_t LisaAnaItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t LisaAnaItem::Get_wr_id() const
{
    return wr_id;
}

inline uint8_t LisaAnaItem::Get_board_id() const
{
    return board_id;
}

inline uint64_t LisaAnaItem::Get_board_event_time() const
{
    return board_event_time;
}

inline uint8_t LisaAnaItem::Get_channel_id() const
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

inline uint32_t LisaAnaItem::Get_channel_energy() const
{
    return channel_energy;
}

inline uint32_t LisaAnaItem::Get_channel_energy_MWD() const
{
    return channel_energy_MWD;
}

inline uint8_t LisaAnaItem::Get_channel_id_traces() const
{
    return channel_id_traces;
}

inline std::vector<int16_t> LisaAnaItem::Get_trace() const
{
    return trace;
}

inline std::vector<int16_t> LisaAnaItem::Get_trace_MWD() const
{
    return trace_MWD;
}

#endif