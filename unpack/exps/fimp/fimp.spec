// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/clock_tdc.spec"

SUBEVENT(fimp_subev)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id=0x300);
    };

    select optional
    {
        mbs_param = CLOCK_TDC_MBS_PARAM(sfp_id_0=0, sfp_id_1=1, sfp_id_2=0, sfp_id_3=0, chan_per_ctdc=128);
    };

    // padding should probably be moved to general
    select several
    {
        padding = PADDING();
    };

    select several
    {
        data = CLOCK_TDC_EVENT_16PH(sfp_id=1, tdc_id=0); // match sfp ?
    };

}

EVENT
{
    fimp = fimp_subev(procid=100);
}