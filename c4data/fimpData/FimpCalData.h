#ifndef FimpCalData_H
#define FimpCalData_H

#include "TObject.h"

class FimpCalItem : public TObject
{
    public:
        FimpCalItem();

        virtual ~FimpCalItem() {}

        void SetAll(uint64_t wr, 
                    uint16_t id, 
                    int chan, 
                    double tot, 
                    double lead, 
                    double trail);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_wr_id() const;
        int Get_channel() const;
        double Get_ToT() const;
        double Get_lead_time() const;
        double Get_trail_time() const;

        ClassDefNV(FimpCalItem, 2);
    
    private:
        // members
        uint64_t wr_t;
        uint16_t wr_id;
        int channel;
        double time_over_threshold;
        double lead_time;
        double trail_time;
};

inline uint64_t FimpCalItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t FimpCalItem::Get_wr_id() const
{
    return wr_id;
}

inline int FimpCalItem::Get_channel() const
{
    return channel;
}

inline double FimpCalItem::Get_ToT() const
{
    return time_over_threshold;
}

inline double FimpCalItem::Get_lead_time() const
{
    return lead_time;
}

inline double FimpCalItem::Get_trail_time() const
{
    return trail_time;
}

#endif