// -*- C++ -*-

#include "../../../config/lisa/setup.hh"
#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"

DUMMY()
{
    UINT32 no NOENCODE;
}


SUBEVENT(febex_subev_traces)
{ 
    if (WR_USED)  
    {
        ts = TIMESTAMP_WHITERABBIT(id=WR_ID);
    }
    select several
    {
        padding = FEBEX_PADDING();
    }

    select several
    {   
        // it refuses to do this with a list loop, so we can auto-generate this with config settings
        data[0] = FEBEX_EVENT_TRACES(card = 0);
        // data[1] = FEBEX_EVENT_TRACES(card = 1);
    }
   
}

EVENT
{

  lisa = febex_subev_traces(procid = PROCID);

  ignore_unknown_subevent;
}

// for mapping UNPACK -> RAW
//#include "mapping.hh"