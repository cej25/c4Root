// -*- C++ -*-

#include "../../../config/setup.h"
#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4_v2.spec"
#include "../../common/vme_caen_v1751.spec"
#include "../../common/general.spec"

external EXT_AIDA();

SUBEVENT(bgo_tamex_subevent)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1900);
    };

    optional UINT32 be { 0_31: b = MATCH(0xbad00bad);}

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
        tamex[0] = TAMEX4_SFP(sfp=1,card=0);
        tamex[1] = TAMEX4_SFP(sfp=1,card=1);
        tamex[2] = TAMEX4_SFP(sfp=1,card=2);
    }  
}


SUBEVENT(bplast_subev)
{
    // lets say this has to occur
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x500);
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
        tamex[0] = TAMEX4_SFP(sfp = 0, card = 0);
        tamex[1] = TAMEX4_SFP(sfp = 0, card = 1);
        tamex[2] = TAMEX4_SFP(sfp = 0, card = 2);
        tamex[3] = TAMEX4_SFP(sfp = 0, card = 3);
        tamex[4] = TAMEX4_SFP(sfp = 0, card = 4);
        tamex[5] = TAMEX4_SFP(sfp = 0, card = 5);
        tamex[6] = TAMEX4_SFP(sfp = 0, card = 6);
        tamex[7] = TAMEX4_SFP(sfp = 0, card = 7);
        tamex[8] = TAMEX4_SFP(sfp = 0, card = 8);
    };
}

SUBEVENT(aida_subev)
{
    ts =TIMESTAMP_WHITERABBIT(id = 0x700);
    external data = EXT_AIDA();
}


EVENT
{
    
    revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20);
    bgo = bgo_tamex_subevent(procid = 100);

    ignore_unknown_subevent;
};
