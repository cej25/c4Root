// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/vme_caen_v1751.spec"
#include "../frs/frs_s101.spec"
#include "../../common/general.spec"

#define BM_MAX_HITS 100000

// making a change

external EXT_AIDA();

SUBEVENT(bgo_tamex_subevent)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1900);
    };

    optional UINT32 be { 0_31: b = MATCH(0xbad00bad);}

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
        tamex[0] = TAMEX4_SFP(sfp=1,card=0);
        tamex[1] = TAMEX4_SFP(sfp=1,card=1);
        tamex[2] = TAMEX4_SFP(sfp=1,card=2);
    }  
}

SUBEVENT(aida_subev)
{
    ts =TIMESTAMP_WHITERABBIT(id = 0x700);
    external data = EXT_AIDA();
}


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

    // changed for s101 I believe
    select several
    {
        trig3 = TRIG3EVENT();
    };

    select optional
    {
        data = TPAT_CRATE_DATA();
    }
}


S2_DATA()
{

    MEMBER(DATA32 dataS2[BM_MAX_HITS] NO_INDEX_LIST);// ZERO_SUPPRESS);


    UINT32 headS2 NOENCODE
    {
        0_12: l_hit_ct;
        13_15: reserved;
        16_31: l_id = MATCH(0xAAAA); // MATCH(0xAAAA);
    };

    list (0 <= l_i < headS2.l_hit_ct)
    {
        UINT32 hit NOENCODE
        {
            0_31: data;
            ENCODE(dataS2 APPEND_LIST, (value = data));
        };

    }
}

S4_DATA()
{
    MEMBER(DATA32 dataS4[BM_MAX_HITS] NO_INDEX_LIST);// ZERO_SUPPRESS);
    UINT32 headS4 NOENCODE
    {
        0_12: l_hit_ct;
        13_15: reserved;
        16_31: l_id = MATCH(0xBBBB); // MATCH(0xBBBB);
    }

    list (0 <= l_i < headS4.l_hit_ct)
    {
        UINT32 hit NOENCODE
        {
            0_31: data;
            ENCODE(dataS4 APPEND_LIST, (value = data));
        }
    }
}

BM_TRAILER()
{
    UINT32 trailer NOENCODE
    {
        0_15: reserved;
        16_31: l_id = MATCH(0xCCCC); // MATCH(0xCCCC);
    }
}

BM_SCALERS()
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

SUBEVENT(bm_subev)
{ 
   select optional 
   {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1700);
   }

   select optional
   {
        sc = BM_SCALERS();
   }

   select optional
   {
       s2 = S2_DATA();
   }
   select optional
   {
       s4 = S4_DATA();
   }

   select optional
   {
       t = BM_TRAILER();
   }
}


EVENT
{
    revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20);
    bgo = bgo_tamex_subevent(procid = 100);

    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frstpat = frs_tpat_subev(procid = 15);
    
    beammonitor = bm_subev(procid = 1);

    ignore_unknown_subevent;
};

#include "mapping.hh"