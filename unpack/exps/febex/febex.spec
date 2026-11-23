// -*- C++ -*-

#include "../../common/whiterabbit_13bit.spec"
#include "../../common/gsi_febex4.spec"


SUBEVENT(bb_first_subev)
{
    select optional 
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x1800);
    }

    select several
    {
        add = FEBEX_PADDING();
    }

    select several
    {
	    data[0] = FEBEX_EVENT_TRACES(card=0);
	    data[1] = FEBEX_EVENT_TRACES(card=1);
        data[2] = FEBEX_EVENT_TRACES(card=2);
        data[3] = FEBEX_EVENT_TRACES(card=3);
        data[4] = FEBEX_EVENT_TRACES(card=4);
        // data[5] = FEBEX_EVENT_TRACES(card=5);
        // data[6] = FEBEX_EVENT_TRACES(card=6);
        // data[7] = FEBEX_EVENT_TRACES(card=7);
    }
	
}

SUBEVENT(bb_second_subev)
{
    select optional 
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x1900);
    }

    select several
    {
        add = FEBEX_PADDING();
    }

    select several
    {
	    data[0] = FEBEX_EVENT_TRACES(card=0);
	    data[1] = FEBEX_EVENT_TRACES(card=1);
        data[2] = FEBEX_EVENT_TRACES(card=2);
        data[3] = FEBEX_EVENT_TRACES(card=3);
        // data[4] = FEBEX_EVENT_TRACES(card=4);
        // data[5] = FEBEX_EVENT_TRACES(card=5);
        // data[6] = FEBEX_EVENT_TRACES(card=6);
        // data[7] = FEBEX_EVENT_TRACES(card=7);
    }
	
}

#ifdef DEGAS_WITH_TRACES
#define DEGAS_FEBEX_BOARD FEBEX_EVENT_TRACES
#else
#define DEGAS_FEBEX_BOARD FEBEX_EVENT
#endif

SUBEVENT(febex_subev)
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
        data[0] = DEGAS_FEBEX_BOARD(card = 0);
        data[1] = DEGAS_FEBEX_BOARD(card = 1);
        data[2] = DEGAS_FEBEX_BOARD(card = 2);
        data[3] = DEGAS_FEBEX_BOARD(card = 3);
        data[4] = DEGAS_FEBEX_BOARD(card = 4);
        data[5] = DEGAS_FEBEX_BOARD(card = 5); // max 6 boards ever
    };
}

EVENT
{
    bbfirst = bb_first_subev(procid=35, control=20);
    bbsecond = bb_second_subev(procid=36);

#ifdef DEGAS_WITH_TRACES
    degastrace = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
#else
    germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
#endif

    ignore_unknown_subevent;
}