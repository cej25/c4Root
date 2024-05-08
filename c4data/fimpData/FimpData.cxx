#include "FimpData.h"

FimpItem::FimpItem()
{

}

void FimpItem::SetAll(uint64_t wr, 
                    uint16_t id,
                    uint64_t trig_t, 
                    uint16_t chan, 
                    uint16_t lead_ct, 
                    double lead_ft, 
                    uint16_t trail_ct, 
                    double trail_ft,
                    uint16_t raw_lead_ft,
                    uint16_t raw_trail_ft)
{
    wr_t = wr;
    wr_id = id;
    trig_time_long = trig_t;
    channel = chan;
    lead_coarse_time = lead_ct;
    lead_fine_time = lead_ft;
    trail_coarse_time = trail_ct;
    trail_fine_time = trail_ft;
    raw_lead_fine_time = raw_lead_ft;
    raw_trail_fine_time = raw_trail_ft;
}

void FimpItem::Reset()
{
    wr_t = 0;
    wr_id = 0;
    trig_time_long = 0;
    channel = 0;
    lead_coarse_time = 0;
    lead_fine_time = 0;
    trail_coarse_time = 0;
    trail_fine_time = 0;
    raw_lead_fine_time = 0;
    raw_trail_fine_time = 0;
}

ClassImp(FimpItem)