#include "BB7FebexCalData.h"

BB7FebexCalItem::BB7FebexCalItem()
{
}

void BB7FebexCalItem::SetAll(int64_t wr,
                        int d,
                        int si,
                        int st,
                        int e,
                        std::vector<uint16_t> tr,
                        double e_cal,
                        uint64_t evt_t,
                        uint64_t ch_t,
                        int64_t ab_t,
                        int pu,
                        int ov
                        )
{   
    wr_t = wr;
    DSSD = d;
    Side = si;
    Strip = st;
    Energy = e;
    Trace = tr;
    EnergyCal = e_cal;
    EventTime = evt_t;
    ChannelTime = ch_t;
    AbsoluteTime = ab_t;
    Pileup = pu;
    Overflow = ov;
}


void BB7FebexCalItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    DSSD = -1;
    Side = -1;
    Strip = -1;
    Energy = 0;
    Trace = {};
    EnergyCal = 0;
    EventTime = 0;
    ChannelTime = 0;
    AbsoluteTime = 0;
    Pileup = 0;
    Overflow = 0;
}

ClassImp(BB7FebexCalItem)