// -*- C++ -*-

#include "../../common/whiterabbit.spec"
//#include "../../common/frs.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../../config/s452/setup.hh"

external EXT_AIDA();


DUMMY()
{
    UINT32 no NOENCODE;
}

/*
SUBEVENT(aida_subev)
{   

    ts = TIMESTAMP_WHITERABBIT(id=0x700);
    external data = EXT_AIDA();

}
*/

SUBEVENT(febex_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id=0x400); // can be autogenerated or simply in config.

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
/*
SUBEVENT(fatima_tamex_subev)
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
        tamex[5] = TAMEX4_SFP(sfp=0,card=5);
        tamex[6] = TAMEX4_SFP(sfp=0,card=6);
        tamex[7] = TAMEX4_SFP(sfp=0,card=7);
        tamex[8] = TAMEX4_SFP(sfp=0,card=8);
    }  
}
*/
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
    }  
}

/*

SUBEVENT(frs_whiterabbit_subev)
{
  
    ts = TIMESTAMP_WHITERABBIT(id=0x100);

}

SUBEVENT(frs_main_crate_subev)
{
  
    data = MAIN_CRATE_DATA();
    
}

SUBEVENT(frs_tpat_subev)
{
    
    data = TPAT_DATA(id=0xCF);

}

SUBEVENT(frs_crate_subev)
{

    frs = FRS_DATA();

}


SUBEVENT (frs_tpc_crate_subev)
{

    tpc = TPC_DATA();

}

SUBEVENT(frs_tof_crate_subev)
{   

    data = TOF_DATA();

}
*/

EVENT
{
    //revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    //fatima_vme = fatima_vme_subev(type = 10, subtype = 1, procid = 70, control = 20, subcrate = 0);
    //fatima_tamex = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20, subcrate = 0);
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20, subcrate = 0);

    // frs stuff
    // all works as spec but needs a major cleanup
    // frs_whiterabbit = frs_whiterabbit_subev(type = 10, subtype = 1, procid = 10, control = 20); // whiterabbit
    frs_main_crate = frs_main_crate_subev(type = 12, subtype = 1, procid = 10, control = 20); // main crate
    tpat = frs_tpat_subev(type = 36, subtype = 3600, procid = 10, control = 20); // tpat // works
    // frs_tof_crate = frs_tof_crate_subev(type = 12, subtype = 1, procid = 35, control = 20); // VFTX, MQDC, SIS 3820
    // frs_tpc_crate = frs_tpc_crate_subev(type = 12, subtype = 1, procid = 20, control = 21); // frs_main_scaler // music?
    frs_crate = frs_crate_subev(type = 12, subtype = 1, procid = 30, control = 20); // sci_tx? // "frs crate"? // scaler_frs is here*/


    ignore_unknown_subevent;
};
