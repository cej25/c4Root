// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"

SUBEVENT(bplast_subev)
{
    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x500);
    trigger_window = TAMEX4_HEADER();
    select several 
    {
        padding = TAMEX4_PADDING();
    }
    select several
    {
        tamex[0] = TAMEX4_SFP(sfp=0,card=0);
        tamex[1] = TAMEX4_SFP(sfp=0,card=1);
        tamex[2] = TAMEX4_SFP(sfp=0,card=2);
        tamex[3] = TAMEX4_SFP(sfp=0, card=3);
        tamex[4] = TAMEX4_SFP(sfp=0,card=4);
        tamex[5] = TAMEX4_SFP(sfp=0,card=5);
        tamex[6] = TAMEX4_SFP(sfp=0,card=6);
        tamex[7] = TAMEX4_SFP(sfp=0,card=7);
        tamex[8] = TAMEX4_SFP(sfp=0,card=8);

    }  
}


EVENT
{   
    
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20, subcrate = 0);

    //ignore_unknown_subevent;
};

