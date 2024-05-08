#include "FimpCalData.h"

FimpCalItem::FimpCalItem()
{

}

void FimpCalItem::SetAll(uint64_t wr, 
                        uint16_t id, 
                        int chan, 
                        double tot, 
                        double lead, 
                        double trail)
{
    wr_t = wr;
    wr_id = id;
    channel = chan;
    time_over_threshold = tot;
    lead_time = lead;
    trail_time = trail;
}
