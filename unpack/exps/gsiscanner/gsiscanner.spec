// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/general.spec"
#include "../../common/vme_caen_v7x5.spec"

#define TRACE_LENGTH 3000

SUBEVENT(vme_subev_qdc){

    data[0] = VME_CAEN_V792(geom=6);
    //data[1] = VME_CAEN_V792(geom=8);

}

SUBEVENT(febex_subev_traces)
{ 
    select several
    {
        badevent = BAD_EVENT();
    }
  
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x0400);
    }
    
    select several
    {
        padding = FEBEX_PADDING();
    }

    select several
    {   
        // for AGATA test cryostat 36 + 1 channels
        data[0] = FEBEX_EVENT_TRACES(card = 0);
        data[1] = FEBEX_EVENT_TRACES(card = 1);
        data[2] = FEBEX_EVENT_TRACES(card = 2);
        data[3] = FEBEX_EVENT_TRACES(card = 3);
    }
   
}

EVENT
{
  qdc = vme_subev_qdc(procid=20);
  agata = febex_subev_traces(procid = 60);
  ignore_unknown_subevent;
}
