#ifndef LisaAnaData_H
#define LisaAnaData_H

#include "TObject.h"
#include <vector>

//Not in use.
class LisaAnaData : public TObject
{
    public:
        LisaAnaData();

        // Destructor
        virtual ~LisaAnaData() {}
       
    protected:


    public:
        ClassDef(LisaAnaData, 1)
};

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
                    bool p,
                    bool o,
                    uint32_t ch_energy,
                    uint32_t ch_energy_ana,
                    uint8_t ch_id_traces,
                    std::vector<uint16_t> tr);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        uint8_t Get_board_id() const;
        uint64_t Get_board_event_time() const;
        uint8_t Get_channel_id() const;
        uint64_t Get_channel_time() const;
        bool Get_pileup() const;
        bool Get_overflow() const;
        uint32_t Get_channel_energy() const;
        uint32_t Get_channel_energy_ana() const;
        uint8_t Get_channel_id_traces() const;
        std::vector<uint16_t> Get_trace() const;

        // Getters
        ClassDefNV(LisaAnaItem, 2);
    private:

        uint64_t wr_t;
        uint16_t wr_id;
        uint8_t board_id;
        uint64_t board_event_time;
        uint8_t channel_id;
        uint64_t channel_time;
        bool pileup;
        bool overflow;
        uint32_t channel_energy;
        uint32_t channel_energy_ana;
        uint8_t channel_id_traces;
        std::vector<uint16_t> trace;

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

inline bool LisaAnaItem::Get_pileup() const
{
    return pileup;
}

inline bool LisaAnaItem::Get_overflow() const
{
    return overflow;
}

inline uint32_t LisaAnaItem::Get_channel_energy() const
{
    return channel_energy;
}

inline uint32_t LisaAnaItem::Get_channel_energy_ana() const
{
    return channel_energy_ana;
}

inline uint8_t LisaAnaItem::Get_channel_id_traces() const
{
    return channel_id_traces;
}

inline std::vector<uint16_t> LisaAnaItem::Get_trace() const
{
    return trace;
}

#endif