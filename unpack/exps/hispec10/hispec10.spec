// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/gsi_febex4.spec"
#include "../frs/frs_shiyan.spec"
#include "../../common/vme_mesytec_mdpp16.spec"

SUBEVENT(mcp_tamex_event)
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
        tamex[0] = TAMEX4_SFP(sfp = 1, card = 0);
        tamex[1] = TAMEX4_SFP(sfp = 1, card = 1);
    };
}

SUBEVENT(stefan_febex_event)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x700);
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

        // orrrr traces.. 
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

SUBEVENT(travmus_subev)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id=0x200);
    };

    UINT32 barrier NOENCODE
    {
        0_15: counter;
        16_31: bar = MATCH(0xF520);

    };

    select several
    {
        data = VME_MESYTEC_MDPP16(geom=8);
    };
}


EVENT
{
    mcp = mcp_tamex_event(procid = 50); // 248 for real data, 100 during pulser test for finetime

    stefan = stefan_febex_event(procid = 70);

    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frstpat = frs_tpat_subev(procid = 15);

    ignore_unknown_subevent;
}

#include "mapping.hh"
