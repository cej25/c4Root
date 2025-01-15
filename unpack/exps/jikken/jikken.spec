// -*- C++ -*-

#include "../../../config/lisa/setup.hh"
#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4_bug.spec"
#include "../../common/general.spec"

#define TRACE_LENGTH 3000

SUBEVENT(febex_subev_traces)
{ 
    select several
    {
        badevent = BAD_EVENT();
    }
  
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1200);
    }
    
    select several
    {
        padding = FEBEX_PADDING();
    }

    select several
    {   
        // eventually 125 detectors requires 8 cards
        data[0] = FEBEX_EVENT_TRACES(card = 0);
        data[1] = FEBEX_EVENT_TRACES(card = 1);
        data[2] = FEBEX_EVENT_TRACES(card = 2);
        data[3] = FEBEX_EVENT_TRACES(card = 3);
        data[4] = FEBEX_EVENT_TRACES(card = 4);
        data[5] = FEBEX_EVENT_TRACES(card = 5);
        data[6] = FEBEX_EVENT_TRACES(card = 6);
        data[7] = FEBEX_EVENT_TRACES(card = 7);
    }
   
}

EVENT
{

  lisa = febex_subev_traces(procid = 60);

  ignore_unknown_subevent;
}
