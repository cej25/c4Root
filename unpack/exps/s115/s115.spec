// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4.spec"
#include "../frs/frs_s115.spec"
#include "../../common/general.spec"


external EXT_AIDA();



SUBEVENT(aida_subev)
{
    ts =TIMESTAMP_WHITERABBIT(id = 0x700);
    external data = EXT_AIDA();
}

// this must change to be more general, or name should change from febex_subev
SUBEVENT(febex_subev)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x400);
    };

    select several
    {
        padding = FEBEX_PADDING();
    };

    select several
    {
        data[0] = FEBEX_EVENT(card = 0);
        data[1] = FEBEX_EVENT(card = 1);
        data[2] = FEBEX_EVENT(card = 2);
        data[3] = FEBEX_EVENT(card = 3);
        data[4] = FEBEX_EVENT(card = 4);
        data[5] = FEBEX_EVENT(card = 5); // max 6 boards ever
    };
}


SUBEVENT(bplast_subev)
{
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

SUBEVENT(frs_main_subev)
{   
    select several
    {
        trig3 = TRIG3EVENT();
    };

    select several
    {
        spill_on = SPILL_ON();
    };

    select several
    {
        spill_off = SPILL_OFF();
    };

    UINT32 sevens NOENCODE
    {
        0_31: 0x77777777;
    }

    select optional
    {
        data = MAIN_CRATE_DATA();
    };
}

SUBEVENT(frs_tpc_subev)
{
    optional UINT32 be { 0_31: b = MATCH(0xbad00bad);}

    select several
    {
        trig3 = TRIG3EVENT();
    };

    select several
    {
        spill_on = SPILL_ON();
    };

    select several
    {
        spill_off = SPILL_OFF();
    };

    select optional
    {
        data = TPC_CRATE_DATA();
    };
}

SUBEVENT(frs_user_subev)
{
    select several
    {
        trig3 = TRIG3EVENT();
    };

    select several
    {
        spill_on = SPILL_ON();
    };

    select several
    {
        spill_off = SPILL_OFF();
    };
    
    UINT32 sevens NOENCODE
    {
        0_31: 0x77777777;
    };

    // same as above
    select optional
    {
        data = USER_CRATE_DATA();
    }
}

SUBEVENT(frs_tpat_subev)
{
    select optional
    {
        wr = TIMESTAMP_WHITERABBIT(id = 0x100);
    };

    select several
    {
        trig3 = TRIG3EVENT();
    };

    select optional
    {
        data = TPAT_CRATE_DATA();
    }
}

EVENT
{
    revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20);

    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frstpat = frs_tpat_subev(procid = 15);

    ignore_unknown_subevent;
};

#include "mapping.hh"
