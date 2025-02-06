#ifndef BB7FebexCalData_H
#define BB7FebexCalData_H

#include "TObject.h"
#include <vector>
#include "TString.h"

class BB7FebexCalItem : public TObject
{
    public:
        BB7FebexCalItem();

        void SetAll(int64_t wr,
                    int si,
                    int st,
                    int e, // probably uint32_t e
                    std::vector<uint16_t> tr,
                    double e_cal,
                    uint64_t evt_t,
                    uint64_t ch_t,
                    int pu,
                    int ov); 
        void Reset();

        int64_t Get_wr_t() const;
        int Get_side() const;
        int Get_strip() const;
        uint32_t Get_energy() const;
        std::vector<uint16_t> Get_trace() const;
        double Get_energy_cal() const;
        uint64_t Get_board_event_time() const;
        uint64_t Get_channel_event_time() const;
        int Get_pileup() const;
        int Get_overflow() const;

        // Getters
        ClassDefNV(BB7FebexCalItem, 1);
    private:
        int64_t wr_t;
        int side;
        int strip;
        uint32_t energy; // double? maybe. e_cal is double.
        std::vector<uint16_t> trace;
        double energy_cal;
        uint64_t board_event_time;
        uint64_t ch_event_time;
        int pileup;
        int overflow;

};

inline int64_t BB7FebexCalItem::Get_wr_t() const
{
    return wr_t;
}

inline int BB7FebexCalItem::Get_side() const
{
    return side;
}

inline int BB7FebexCalItem::Get_strip() const
{
    return strip;
}

inline uint32_t BB7FebexCalItem::Get_energy() const
{
    return energy;
}

inline std::vector<uint16_t> BB7FebexCalItem::Get_trace() const
{
    return trace;
}

inline double BB7FebexCalItem::Get_energy_cal() const
{
    return energy_cal;
}

inline uint64_t BB7FebexCalItem::Get_board_event_time() const
{
    return board_event_time;
}

inline uint64_t BB7FebexCalItem::Get_channel_event_time() const
{
    return ch_event_time;
}

inline int BB7FebexCalItem::Get_pileup() const
{
    return pileup;
}

inline int BB7FebexCalItem::Get_overflow() const
{
    return overflow;
}


#endif