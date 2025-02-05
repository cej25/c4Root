// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"


SUBEVENT(bb7_subev)
{
    select optional 
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1800);
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
        data[5] = FEBEX_EVENT_TRACES(card=5);
        data[6] = FEBEX_EVENT_TRACES(card=6);
    }
	
}

EVENT
{
    bb7 = bb7_subev(procid=60);
}
