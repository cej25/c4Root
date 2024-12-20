// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/gsi_febex4.spec"
#include "../frs/frs_NovTest.spec"

external EXT_AIDA();


SUBEVENT(aida_subev)
{   

    ts = TIMESTAMP_WHITERABBIT(id=0x700);
    external data = EXT_AIDA();

}


SUBEVENT(febex_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id=0x400);

    select several
    {
        padding = FEBEX_PADDING();
    }
    select several
    {   // do once per card
        data[0] = FEBEX_EVENT(card = 0);
        data[1] = FEBEX_EVENT(card = 1);
        data[2] = FEBEX_EVENT(card = 2);
        data[3] = FEBEX_EVENT(card = 3);
    }
}

SUBEVENT(fatima_tamex_subev)
{
    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
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

SUBEVENT(bplast_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id=0x500);
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
        tamex[3] = TAMEX4_SFP(sfp=0,card=3);
        tamex[4] = TAMEX4_SFP(sfp=0,card=4);
    }  
}

SUBEVENT(frs_main_subev)
{
    // whiterabbit ts merged into ProcID (for now)
    select several
    {
        wr = TIMESTAMP_WHITERABBIT(id=0x100);
    };

    // catch trigger 3 events
    select several
    {
        trig3 = TRIG3EVENT();
    };

    // trigger 1 events
    select several
    {
        data = MAIN_CRATE_DATA();
    }  
}

SUBEVENT(frs_tpc_subev)
{
    select several
    {
        trig3 = TRIG3EVENT();
    };

    // trigger 1 events
    select several
    {
        data = TPC_CRATE_DATA();
    }
}

SUBEVENT(frs_user_subev)
{
    select several
    {
        trig3 = TRIG3EVENT();
    }

    // trigger 1 events
    select several
    {
        data = USER_CRATE_DATA();
    }
}

SUBEVENT(frs_vftx_subev)
{
    select several
    {
        trig3 = TRIG3EVENT();
    }

    // trigger 1 events
    select several
    {
        data = VFTX_CRATE_DATA();
    }
}


EVENT
{   
    // CEJ: UNCOMMENT SUBEVENTS YOU'RE INTERESTED IN HERE
    
    // revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    // germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    
    fatima = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20, subcrate = 0);
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20, subcrate = 0);

    // frsmain = frs_main_subev(procid = 10);
    // frstpc = frs_tpc_subev(procid = 20);
    // frsuser = frs_user_subev(procid = 30);
    // frsvftx = frs_vftx_subev(procid = 40);

    ignore_unknown_subevent;
};

// #include "mapping.hh"
