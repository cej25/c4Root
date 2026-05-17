// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/general.spec"

SUBEVENT(febex_subev_traces)
{ 
    select several
    {
        badevent = BAD_EVENT();
    }
  
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTERNAL(id=0x0300);
    }
    
    select several
    {
        padding = FEBEX_PADDING();
    }

    select several
    {   
        // Eventually: 125 detectors in 5x5x5 layers. Each layer 2 cards (25 diamonds + 7 spare) -> Max 10 cards.
        data[0] = FEBEX_EVENT_TRACES(card = 0);
        data[1] = FEBEX_EVENT_TRACES(card = 1);
        data[2] = FEBEX_EVENT_TRACES(card = 2);
        data[3] = FEBEX_EVENT_TRACES(card = 3);
        data[4] = FEBEX_EVENT_TRACES(card = 4);
        data[5] = FEBEX_EVENT_TRACES(card = 5);
        data[6] = FEBEX_EVENT_TRACES(card = 6);
        data[7] = FEBEX_EVENT_TRACES(card = 7);
        data[8] = FEBEX_EVENT_TRACES(card = 8);
        data[9] = FEBEX_EVENT_TRACES(card = 9);
    }
   
}

EVENT
{
    lisa = febex_subev_traces(procid = 60);

    ignore_unknown_subevent;
}

