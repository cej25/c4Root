// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/gsi_febex4.spec"

SUBEVENT(mcp_tamex_event)
{

    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x400);
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
        tamex[0] = TAMEX4_SFP(sfp = 1, card = 0);
        tamex[1] = TAMEX4_SFP(sfp = 1, card = 1);
    };
}

SUBEVENT(stefan_febex_event)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x200);
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

        // orrrr traces.. 
    };
}


EVENT
{
    mcp = mcp_tamex_event(procid = 248); // 248 for real data, 100 during pulser test for finetime

    stefan = stefan_febex_event(procid = 27);

    ignore_unknown_subevent;
}
