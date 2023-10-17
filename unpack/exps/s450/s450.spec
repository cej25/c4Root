// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/gsi_febex4.spec" // gsi_febex4.spec
// CEJ: grab setup file from S450 and stick in c4Root/config/s450/...
#include "../../../config/s452/setup.hh"

SUBEVENT(fatima_tamex_subev)
{

        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);

        trigger_window = TAMEX4_HEADER();
        select several 
        {
            padding = TAMEX4_PADDING();
        }
        list (0 <= index < 9)
        {
            tamex = TAMEX4_SFP(sfp = 0, card = index);
        }

}

SUBEVENT(plastic_subev)
{   
    //MEMBER(DATA12 am_fired[32] ZERO_SUPPRESS_MULTI(200));

    ts = TIMESTAMP_WHITERABBIT(id=0x500);
    /* CEJ: IS_TWINPEAKS should be removed
    * flag will exist but will be used in 
    * script that generates this .spec file
    */
    //if (IS_PLASTIC_TWINPEAKS)
    //{
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
            tamex[3] = TAMEX4_SFP(sfp = 0, card = 3);
            tamex[4] = TAMEX4_SFP(sfp = 0, card = 4);
            tamex[5] = TAMEX4_SFP(sfp = 0, card = 5);
            tamex[6] = TAMEX4_SFP(sfp = 0, card = 6);
            tamex[7] = TAMEX4_SFP(sfp = 0, card = 7);
            tamex[8] = TAMEX4_SFP(sfp = 0, card = 8);
        }
    /*else
    {
        
        trigger_window = TAMEX_WINDOW();
        select several 
        {
            padding = TAMEX_PADDING();
        }
        select several
        {
            tamex[0] = TAMEX_DATA(card = 0);
            tamex[1] = TAMEX_DATA(card = 1);
            tamex[2] = TAMEX_DATA(card = 2);
            tamex[3] = TAMEX_DATA(card = 0);
            tamex[4] = TAMEX_DATA(card = 1);
            tamex[5] = TAMEX_DATA(card = 2);
            tamex[6] = TAMEX_DATA(card = 0);
            tamex[7] = TAMEX_DATA(card = 1);
            tamex[8] = TAMEX_DATA(card = 2);
        }

    }*/

}


EVENT
{   
    // CEJ: UNCOMMENT SUBEVENTS YOU'RE INTERESTED IN HERE

    //revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    //germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    //fatima_vme = fatima_vme_subev(type = 10, subtype = 1, procid = 70, control = 20, subcrate = 0);
    //fatima_tamex = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20, subcrate = 0);
    plastic = plastic_subev(type = 10, subtype = 1, procid = 80, control = 20, subcrate = 0);

    // CEJ: NONE OF THIS WILL WORK WITH S450
    // white rabbit should be easy, do with Elisa wed
    // frs_whiterabbit = frs_whiterabbit_subev(type = 10, subtype = 1, procid = 10, control = 20); // whiterabbit
    // come back to
    // frs_main_crate = frs_main_crate_subev(type = 12, subtype = 1, procid = 10, control = 20); // main crate
    // // start extraction here
    // tpat = frs_tpat_subev(type = 36, subtype = 3600, procid = 10, control = 20); // tpat // works // 
    // frs_tof_crate = frs_tof_crate_subev(type = 12, subtype = 1, procid = 35, control = 20); // VFTX, MQDC, SIS 3820
    // frs_tpc_crate = frs_tpc_crate_subev(type = 12, subtype = 1, procid = 20, control = 21); // frs_main_scaler // music?
    // frs_crate = frs_crate_subev(type = 12, subtype = 1, procid = 30, control = 20); // sci_tx? // "frs crate"? // scaler_frs is here*/

    ignore_unknown_subevent;
};

// #include "mapping.hh"