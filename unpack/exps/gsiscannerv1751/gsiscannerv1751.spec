// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/general.spec"
#include "../../common/vme_caen_v7x5.spec"
#include "../../common/vme_caen_v1751_traces.spec"



// Reads the Padding between FEBEX events:
TRAIL()
{
    UINT32 trail NOENCODE
    {
        0_31: trail_1;
    }
}



SUBEVENT(vme_subev_qdc){
    qdc = VME_CAEN_V792(geom=6);
    v1751 = VME_CAEN_V1751_TRACES(geom=6);
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
  vme = vme_subev_qdc(procid=70);
  //agata = febex_subev_traces(procid = 60);
  //ignore_unknown_subevent;
}
