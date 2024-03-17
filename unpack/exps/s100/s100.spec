// -*- C++ -*-

#include "../../../config/setup.h"
#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/vme_caen_v1751.spec"
#include "../../common/vme_caen_v1x90.spec"
#include "../frs/frs_s100.spec"
#include "fatima_vme.spec"

external EXT_AIDA();

SUBEVENT(aida_subev)
{
    ts =TIMESTAMP_WHITERABBIT(id = 0x700);
    external data = EXT_AIDA();
}

// this must change to be more general, or name should change from febex_subev
SUBEVENT(febex_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id = 0x400);

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
    };
}

SUBEVENT(fatima_tamex_subev)
{

    // !! catch bad events like LISA

    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1600);

    trigger_window = TAMEX4_HEADER();

    select several
    {
        padding = TAMEX4_PADDING();
    };

    select several
    {
        tamex[0] = TAMEX4_SFP(sfp = 0, card = 0);
        tamex[1] = TAMEX4_SFP(sfp = 0, card = 1);
    };
}

SUBEVENT(fatima_vme_subev)
{
    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1500);

    select several
    {
        error1 = ERR_WORD_SIX();
    }

    select optional
    {
        scalers = FATIMA_VME_SCALERS();
    }

    // we always get some readout from 5 QCD boards
    qdc[0] = VME_CAEN_V1751();
    qdc[1] = VME_CAEN_V1751();
    qdc[2] = VME_CAEN_V1751();
    qdc[3] = VME_CAEN_V1751();
    qdc[4] = VME_CAEN_V1751();

    select several
    {
        error2 = ERR_WORD_SIX();
    };

    // we don't always get information from both TDC boards
    select optional
    {
        tdc1 = VME_CAEN_V1290_FRS();
    };

    select several
    {
        error3 = ERR_WORD_SIX();
    };

    select optional
    {
        tdc2 = VME_CAEN_V1290_FRS();
    };
}

SUBEVENT(bplast_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id = 0x500);

    trigger_window = TAMEX4_HEADER();

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
    };
}

SUBEVENT(frs_main_subev)
{   
    // CEJ: I don't remember why this has to be select several
    select several
    {
        wr = TIMESTAMP_WHITERABBIT(id = 0x100);
    };

    // catch weird trig3 events
    select several
    {
        trig3 = TRIG3EVENT();
    };

    // CEJ: this should be optional vs several? if several then we get overwritten - check.
    select several
    {
        data = MAIN_CRATE_DATA();
    };
}

SUBEVENT(frs_tpc_subev)
{
    select several
    {
        trig3 = TRIG3EVENT();
    };

    // as above should be select optional i think
    select several
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

    // same as above
    select several
    {
        data = USER_CRATE_DATA();
    }
}

// unpacking very occasionally throws error
SUBEVENT(frs_vftx_subev)
{
    select several
    {
        trig3 = TRIG3EVENT();
    }

    // as above
    select several
    {
        data = VFTX_CRATE_DATA();
    };
}

EVENT
{
    revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    fatima = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20);
    // fatimavme = fatima_vme_subev(type = 10, subtype = 1, procid = 70, control = 20); // apparenlty there are fatimavme things in NovTest data..comment out
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20);

    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frsvftx = frs_vftx_subev(procid = 40);

    ignore_unknown_subevent;
};