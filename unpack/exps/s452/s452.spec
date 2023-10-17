// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/frs.spec"
#include "../../common/gsi_febex4.spec" // gsi_febex4.spec
#include "../../common/gsi_tamex4.spec"
#include "../../../config/s452/setup.hh" // ../../../config/s452

// one by one we will remove all but AIDA...
external EXT_AIDA();

external EXT_FATIMA_VME();
external EXT_FATIMA_TAMEX(); // twinpeaks?


DUMMY()
{
    UINT32 no NOENCODE;
}

SUBEVENT(aida_subev)
{   

    ts = TIMESTAMP_WHITERABBIT(id=0x700);
    external data = EXT_AIDA();

}

SUBEVENT(febex_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id=0x400); // can be autogenerated or simply in config.

    select several
    {
        padding = FEBEX_PADDING();
    }
    select several
    {   // do once per card
        data = FEBEX_EVENT();
    }
}

SUBEVENT(fatima_vme_subev)
{
    
    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1500);
    external data = EXT_FATIMA_VME();
    
}

SUBEVENT(fatima_tamex_subev)
{
  
    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
    external data = EXT_FATIMA_TAMEX();

    /*trigger_window = TAMEX_WINDOW();
    select several 
    {
        padding = TAMEX_PADDING();
    }
    list (0 <= index < 4)
    {
        tamex = TAMEX_DATA();
    }*/
  
}

SUBEVENT(plastic_subev)
{   
    //MEMBER(DATA12 am_fired[32] ZERO_SUPPRESS_MULTI(200));

    ts = TIMESTAMP_WHITERABBIT(id=0x500);
    
    // IF(TWINPEAKS) done in generation of this spec file

    trigger_window = TAMEX4_HEADER();
    select several 
    {
        padding = TAMEX4_PADDING();
    }
    select several
    {
        tamex[0] = TAMEX4_SFP(sfp = 0, card = 0);
        tamex[1] = TAMEX4_SFP(sfp = 0, card = 1);
        tamex[2] = TAMEX4_SFP(sfp = 0, card = 2);
    }

}

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

EVENT
{
    //revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    //germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    //fatima_vme = fatima_vme_subev(type = 10, subtype = 1, procid = 70, control = 20, subcrate = 0);
    //fatima_tamex = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20, subcrate = 0);
    //plastic = plastic_subev(type = 10, subtype = 1, procid = 80, control = 20, subcrate = 0);

    // frs stuff
    // white rabbit should be easy, do with Elisa wed
    //frs_whiterabbit = frs_whiterabbit_subev(type = 10, subtype = 1, procid = 10, control = 20); // whiterabbit
    // come back to
    //frs_main_crate = frs_main_crate_subev(type = 12, subtype = 1, procid = 10, control = 20); // main crate
    // start extraction here
    tpat = frs_tpat_subev(type = 36, subtype = 3600, procid = 10, control = 20); // tpat // works
    //frs_tof_crate = frs_tof_crate_subev(type = 12, subtype = 1, procid = 35, control = 20); // VFTX, MQDC, SIS 3820
    //frs_tpc_crate = frs_tpc_crate_subev(type = 12, subtype = 1, procid = 20, control = 21); // frs_main_scaler // music?
    frs_crate = frs_crate_subev(type = 12, subtype = 1, procid = 30, control = 20); // sci_tx? // "frs crate"? // scaler_frs is here*/


    ignore_unknown_subevent;
};

#include "mapping.hh"
