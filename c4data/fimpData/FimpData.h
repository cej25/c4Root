#ifndef FimpData_H
#define FimpData_H

#include "TObject.h"
#include <vector>

class FimpItem : public TObject
{
    public:
        FimpItem();

        virtual ~FimpItem() {}

        void SetAll(uint64_t wr, 
                    uint16_t id,
                    uint64_t trig_t, 
                    uint16_t chan, 
                    std::vector<uint16_t> lead_ct, 
                    std::vector<double> lead_ft, 
                    std::vector<uint16_t> trail_ct, 
                    std::vector<double> trail_ft,
                    std::vector<uint16_t> raw_lead_ft,
                    std::vector<uint16_t> raw_trail_ft);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        uint64_t Get_trig_time_long() const;
        uint16_t Get_channel() const;
        std::vector<uint16_t> Get_lead_coarse_time() const;
        std::vector<double> Get_lead_fine_time() const;
        std::vector<uint16_t> Get_trail_coarse_time() const;
        std::vector<double> Get_trail_fine_time() const;
        std::vector<uint16_t> Get_raw_lead_fine_time() const;
        std::vector<uint16_t> Get_raw_trail_fine_time() const;

        ClassDef(FimpItem, 2);
    
    private:
        // members
        uint64_t wr_t;
        uint16_t wr_id;
        uint64_t trig_time_long; 
        uint16_t channel;
        std::vector<uint16_t> lead_coarse_time;
        std::vector<double> lead_fine_time;
        std::vector<uint16_t> trail_coarse_time;
        std::vector<double> trail_fine_time;
        std::vector<uint16_t> raw_lead_fine_time;
        std::vector<uint16_t> raw_trail_fine_time;
};

inline uint64_t FimpItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t FimpItem::Get_wr_id() const
{
    return wr_id;
}

inline uint64_t FimpItem::Get_trig_time_long() const
{
    return trig_time_long;
}

inline uint16_t FimpItem::Get_channel() const
{
    return channel;
}

inline std::vector<uint16_t> FimpItem::Get_lead_coarse_time() const
{
    return lead_coarse_time;
}

inline std::vector<double> FimpItem::Get_lead_fine_time() const
{
    return lead_fine_time;
}

inline std::vector<uint16_t> FimpItem::Get_trail_coarse_time() const
{
    return trail_coarse_time;
}

inline std::vector<double> FimpItem::Get_trail_fine_time() const
{
    return trail_fine_time;
}

inline std::vector<uint16_t> FimpItem::Get_raw_lead_fine_time() const
{
    return raw_lead_fine_time;
}

inline std::vector<uint16_t> FimpItem::Get_raw_trail_fine_time() const
{
    return raw_trail_fine_time;
}


#endif