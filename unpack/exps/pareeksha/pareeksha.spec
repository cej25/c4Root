// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/vme_mesytec_mdpp16.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/general.spec"
#include "../frs/frs_pareeksha.spec"

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
        // Eventually: 125 detectors in 5x5x5 layers. Each layer 2 cards (25 diamonds + 7 spare) -> Max 10 cards.
        data[0] = FEBEX_EVENT_TRACES(card = 0);
        data[1] = FEBEX_EVENT_TRACES(card = 1);
        data[2] = FEBEX_EVENT_TRACES(card = 2);
        data[3] = FEBEX_EVENT_TRACES(card = 3);
        data[4] = FEBEX_EVENT_TRACES(card = 4);
        data[5] = FEBEX_EVENT_TRACES(card = 5);
        data[6] = FEBEX_EVENT_TRACES(card = 6);
        data[7] = FEBEX_EVENT_TRACES(card = 7);
        data[8] = FEBEX_EVENT_TRACES(card = 8);
        data[9] = FEBEX_EVENT_TRACES(card = 9);
    }
   
}

EVENT
{
    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frstpat = frs_tpat_subev(procid = 15);

    travmus = travmus_subev(procid=35);

    lisa = febex_subev_traces(procid = 60);

    ignore_unknown_subevent;
}

#include "mapping.hh"
