// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/gsi_febex4.spec"

SUBEVENT(mcp_tamex_event)
{

    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1600);
    };

    select optional
    {
        trigger_window = TAMEX4_HEADER();
    };
    
    select several
    {
        padding = TAMEX4_PADDING();
    };

    select several
    {
        tamex[0] = TAMEX4_SFP(sfp = 0, card = 0);
        tamex[1] = TAMEX4_SFP(sfp = 0, card = 1);
    };
}

// this must change to be more general, or name should change from febex_subev
SUBEVENT(dssd_febex_event)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x400);
    };

    select several
    {
        padding = FEBEX_PADDING();
    };

    select several
    {
        data[0] = FEBEX_EVENT(card = 0);
        data[1] = FEBEX_EVENT(card = 1);
        data[2] = FEBEX_EVENT(card = 2);
        data[3] = FEBEX_EVENT(card = 3);
        data[4] = FEBEX_EVENT(card = 4);
        data[5] = FEBEX_EVENT(card = 5);
    };
}


EVENT
{
    mcp = mcp_tamex_event(procid = 10);

    dssd = dssd_febex_event(procid = 20);

    ignore_unknown_subevent;
}
