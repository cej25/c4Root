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
#ifndef LisaData_H
#define LisaData_H
#include "TObject.h"
#include <vector>
#include "TVector.h"

// This is the adjustment to use TVectors instead of std::vector
//This was to try to read vectors of vectors form external macro without sourcing c4. It does not work.
//template <typename T>
//using StdVector = std::vector<T>;

class LisaItem : public TObject
{
    public:
        LisaItem();

        void SetAll(uint64_t wr,
                    uint16_t id,
                    int b_id,
                    uint64_t ev_time,
                    int ch_id,
                    uint64_t ch_time,
                    bool p,
                    bool o,
                    float ch_energy,
                    int ch_id_traces,
                    std::vector<float> tr,
                    std::vector<int16_t> tr_x);

        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        int Get_board_id() const;
        uint64_t Get_board_event_time() const;
        int Get_channel_id() const;
        uint64_t Get_channel_time() const;
        bool Get_pileup() const;
        bool Get_overflow() const;
        float Get_channel_energy() const;
        int Get_channel_id_traces() const;
        std::vector<float> Get_trace() const;
        std::vector<int16_t> Get_trace_x() const;

        // Getters
        ClassDefNV(LisaItem, 2);
    private:
    
        uint64_t wr_t;
        uint16_t wr_id;
        int board_id;
        uint64_t board_event_time;
        int channel_id;
        uint64_t channel_time;
        bool pileup;
        bool overflow;
        float channel_energy;
        int channel_id_traces;
        std::vector<float> trace; 
        std::vector<int16_t> trace_x; 

};

inline uint64_t LisaItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t LisaItem::Get_wr_id() const
{
    return wr_id;
}

inline int LisaItem::Get_board_id() const
{
    return board_id;
}

inline uint64_t LisaItem::Get_board_event_time() const
{
    return board_event_time;
}

inline int LisaItem::Get_channel_id() const
{
    return channel_id;
}

inline uint64_t LisaItem::Get_channel_time() const
{
    return channel_time;
}

inline bool LisaItem::Get_pileup() const
{
    return pileup;
}

inline bool LisaItem::Get_overflow() const
{
    return overflow;
}

inline float LisaItem::Get_channel_energy() const
{
    return channel_energy;
}

inline int LisaItem::Get_channel_id_traces() const
{
    return channel_id_traces;
}

inline std::vector<float> LisaItem::Get_trace() const
{
    return trace;
}

inline std::vector<int16_t> LisaItem::Get_trace_x() const
{
    return trace_x;
}

#endif