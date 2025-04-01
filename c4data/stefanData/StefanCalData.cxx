#include "StefanCalData.h"

StefanCalItem::StefanCalItem()
{
}

void StefanCalItem::SetAll(Long64_t wr,
                            Int_t d,
                            Int_t si,
                            Int_t st,
                            Int_t e,
                            std::vector<UShort_t> tr,
                            Double_t e_cal,
                            ULong64_t evt_t,
                            ULong64_t ch_t,
                            Long64_t ab_t,
                            Bool_t pu,
                            Bool_t ov)
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


void StefanCalItem::Reset()
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

ClassImp(StefanCalItem)