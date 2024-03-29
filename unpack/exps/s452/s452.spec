// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../../config/s452/setup.hh"

#include "../../common/vme_caen_v1x90.spec"
#include "../../common/vme_caen_v1751.spec"
#include "../../common/vme_caen_v830.spec"

FATIMA_VME_SCALERS()
{   
    MEMBER(DATA32 data[32] ZERO_SUPPRESS);

    // do stuff init
    UINT32 sc_header NOENCODE
    {      
        0_7: empty1;
        8_12: nwords;
        13_26: empty2;
        27_31: geo = MATCH(0b01111);
    }

    list (0 <= index < sc_header.nwords)
    {
        UINT32 sc_data NOENCODE
        {
            0_31: value;
        }
        ENCODE(data[index], (value = sc_data.value));
    }

    UINT32 scaler_trailer NOENCODE;

}

ERR_WORD_SIX()
{
    UINT32 err NOENCODE
    {
        0_31: err = MATCH(0x06000000);
    }
}

//external EXT_AIDA();

/*
SUBEVENT(aida_subev)
{   

    ts = TIMESTAMP_WHITERABBIT(id=0x700);
    external data = EXT_AIDA();

}
*/
/*
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
*/
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


SUBEVENT(fatima_vme_subev)
{   

    // we have...
    // WR TS
    // possible random 0x060 word
    // scalers
    // possible random 0x060 word?
    // qdc
    // possible random 0x060 word?
    // tdc x1 or x2? x0?
    // possible eob/0x060 word?

    ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1500);

    select several
    {
        e = ERR_WORD_SIX();
    }

    // SCALERS
    select optional
    {
        scalers = FATIMA_VME_SCALERS();
    }

    // number of boards 
    
    
        qdc[0] = VME_CAEN_V1751();
    
        qdc[1] = VME_CAEN_V1751();
        qdc[2] = VME_CAEN_V1751();
        qdc[3] = VME_CAEN_V1751();
       //qdc[4] = VME_CAEN_V1751();
    
    select several
    {
        e2 = ERR_WORD_SIX();
    }

    // TDC
    select optional
    {
        tdc1 = VME_CAEN_V1290_FRS();
    }

    select several
    {
        e3 = ERR_WORD_SIX();
    }
    
    select optional
    {
        tdc2 = VME_CAEN_V1290_FRS();
    }

}

/*
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
*/

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
    //germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    fatimavme = fatima_vme_subev(type = 10, subtype = 1, procid = 70, control = 20, subcrate = 0);
    //fatima_tamex = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20, subcrate = 0);
    //bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20, subcrate = 0);

    // frs stuff
    // all works as spec but needs a major cleanup
    // frs_whiterabbit = frs_whiterabbit_subev(type = 10, subtype = 1, procid = 10, control = 20); // whiterabbit
    //frs_main_crate = frs_main_crate_subev(type = 12, subtype = 1, procid = 10, control = 20); // main crate
    //tpat = frs_tpat_subev(type = 36, subtype = 3600, procid = 10, control = 20); // tpat // works
    // frs_tof_crate = frs_tof_crate_subev(type = 12, subtype = 1, procid = 35, control = 20); // VFTX, MQDC, SIS 3820
    // frs_tpc_crate = frs_tpc_crate_subev(type = 12, subtype = 1, procid = 20, control = 21); // frs_main_scaler // music?
    //frs_crate = frs_crate_subev(type = 12, subtype = 1, procid = 30, control = 20); // sci_tx? // "frs crate"? // scaler_frs is here*/


    ignore_unknown_subevent;
};
