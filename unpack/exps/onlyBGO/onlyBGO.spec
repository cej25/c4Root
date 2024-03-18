// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"

SUBEVENT(bgo_tamex_subevent)
{
    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600); //change id
    trigger_window = TAMEX4_HEADER();
    select several 
    {
        padding = TAMEX4_PADDING();
    }
    select several
    {
        tamex[0] = TAMEX4_SFP(sfp=0,card=0);
        tamex[1] = TAMEX4_SFP(sfp=0,card=1);
    }  
}


EVENT
{   
    bgo = bgo_tamex_subevent(type = 10, subtype = 1, procid = 75, control = 20, subcrate = 0); //change vals

    //ignore_unknown_subevent;
};

