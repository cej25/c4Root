#include "FimpData.h"

FimpItem::FimpItem()
{

}

void FimpItem::SetAll(uint64_t wr, 
                    uint16_t id,
                    uint64_t trig_t, 
                    uint16_t chan, 
                    std::vector<uint16_t> lead_ct, 
                    std::vector<double> lead_ft, 
                    std::vector<uint16_t> trail_ct, 
                    std::vector<double> trail_ft,
                    std::vector<uint16_t> raw_lead_ft,
                    std::vector<uint16_t> raw_trail_ft)
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
    lead_coarse_time.clear();
    lead_fine_time.clear();
    trail_coarse_time.clear();
    trail_fine_time.clear();
    raw_lead_fine_time.clear();
    raw_trail_fine_time.clear();
}

ClassImp(FimpItem)