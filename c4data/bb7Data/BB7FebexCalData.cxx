#include "BB7FebexCalData.h"

BB7FebexCalItem::BB7FebexCalItem()
{
}

void BB7FebexCalItem::SetAll(int64_t wr,
                        int si,
                        int st,
                        int e,
                        std::vector<uint16_t> tr,
                        double e_cal,
                        uint64_t evt_t,
                        uint64_t ch_t,
                        int pu,
                        int ov
                        )
{   
    wr_t = wr;
    side = si;
    strip = st;
    energy = e;
    trace = tr;
    energy_cal = e_cal;
    board_event_time = evt_t;
    ch_event_time = ch_t;
    pileup = pu;
    overflow = ov;
}


void BB7FebexCalItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    side = -1;
    strip = -1;
    energy = 0;
    trace = {};
    energy_cal = 0;
    board_event_time = 0;
    ch_event_time = 0;
    pileup = 0;
    overflow = 0;
}

ClassImp(BB7FebexCalItem)