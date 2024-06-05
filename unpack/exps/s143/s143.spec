// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/clock_tdc.spec"
#include "../../common/vme_mesytec_mdpp16.spec"
#include "../frs/frs_pareeksha.spec" // same frs
//#include "../../common/general.spec"
#include "../../common/gsi_tamex4.spec"

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

SUBEVENT(fimp_subev)
{
    optional UINT32 be { 0_31: b = MATCH(0xbad00bad);}

    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1300);
    };

    select optional
    {
        mbs_param = CLOCK_TDC_MBS_PARAM(sfp_id_0=0, sfp_id_1=1, sfp_id_2=0, sfp_id_3=0, chan_per_ctdc=128);
    };

    select several
    {
        padding = PADDING();
    };

    select several
    {
        data = CLOCK_TDC_EVENT_16PH(sfp_id=1, tdc_id=0); // match sfp ?
    };

}

SUBEVENT(fatima_tamex_subev)
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
        tamex[0] = TAMEX4_SFP(sfp = 1, card = 0); // we'll only use this
        tamex[1] = TAMEX4_SFP(sfp = 0, card = 1);
        tamex[2] = TAMEX4_SFP(sfp = 0, card = 2);
        tamex[3] = TAMEX4_SFP(sfp = 0, card = 3);
    };
}

EVENT
{
    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frstpat = frs_tpat_subev(procid = 15);
    travmus = travmus_subev(procid=35);

    fimp = fimp_subev(procid=100);

    fatima = fatima_tamex_subev(type = 10, subtype = 1, procid = 80, control = 20);

    ignore_unknown_subevent;
}
