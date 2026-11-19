// -*- C++ -*-

// #include "../../../config/setup.h"
#include "s100_whiterabbit.generated.spec"
#define C4_WR_UNIFIED
#include "../../common/whiterabbit.spec"
#undef C4_WR_UNIFIED
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4.spec"
#include "tamex_payload.spec"
#include "vme_caen_v1751_lab.spec"
//#include "../../common/vme_caen_v1x90.spec"
#include "../frs/frs_s100.spec" //r3b frs
#include "vme_caen_v1290_geo.spec"
#include "fatima_vme.spec"
#include "../../common/general.spec"

#define BM_MAX_HITS 100000
#define AIDA_MAX_HITS 13000

// making a change

external EXT_AIDA();

SUBEVENT(bgo_tamex_subevent)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = S100_WR_BGO);
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
        S100_TAMEX_CARDS_BGO
    }  
}

SUBEVENT(aida_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id = S100_WR_AIDA);
    external data = EXT_AIDA();
}

// this must change to be more general, or name should change from febex_subev
SUBEVENT(febex_subev)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = S100_WR_GERMANIUM);
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
        data[5] = FEBEX_EVENT(card = 5);
    };
}

SUBEVENT(fatima_tamex_subev)
{
    S100_TAMEX_PAYLOAD(S100_WR_FATIMA, S100_TAMEX_CARDS_FATIMA)
}

SUBEVENT(fatima_vme_subev)
{
    // Experimental VME QDC + GEO-matched TDC grouping; production unchanged.
    // V1751 boards are matched by their hardware ID, not arrival position.
    // Do not install experimental generated headers into c4Root.
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = S100_WR_FATIMAVME);
    };

    select several
    {
        error1 = ERR_WORD_SIX();
    };

    select optional
    {
        scalers = FATIMA_VME_SCALERS();
    };

    // V1751 aggregate header identifies the physical board. Keep the
    // array slot tied to the board ID, even if earlier boards are absent.
    // The error marker can occur among module payloads.
    select several
    {
        qdc[0] = VME_CAEN_V1751(board=6);
        qdc[1] = VME_CAEN_V1751(board=7);
        qdc[2] = VME_CAEN_V1751(board=8);
        qdc[3] = VME_CAEN_V1751(board=9);
        qdc[4] = VME_CAEN_V1751(board=10);
        qdc[5] = VME_CAEN_V1751(board=31);
        error2 = ERR_WORD_SIX();
    };

    // Experimental GEO-driven TDC selection (assumed installed GEOs 12, 13).
    // Both modules can be absent, and error words can appear between them.
    // Their selection indices are fixed by GEO, not arrival order.
    select several
    {
        tdc[0] = VME_CAEN_V1290_GEO(geom_expected=12);
        tdc[1] = VME_CAEN_V1290_GEO(geom_expected=13);
        tdc[2] = VME_CAEN_V1290_GEO(geom_expected=31);
        tdc[3] = VME_CAEN_V1290_GEO(geom_expected=30);
        tdc[4] = VME_CAEN_V1290_GEO(geom_expected=29);
        tdc[5] = VME_CAEN_V1290_GEO(geom_expected=28);
        error3 = ERR_WORD_SIX();
    };
}

SUBEVENT(bplast_subev)
{
    S100_TAMEX_PAYLOAD(S100_WR_BPLAST, S100_TAMEX_CARDS_BPLAST)
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
    optional UINT32 be { 0_31: b = MATCH(0xbad00bad); }

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
        wr = TIMESTAMP_WHITERABBIT(id = S100_WR_FRSTPAT);
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

SUBEVENT(bm_subev)
{

    MEMBER(DATA32 dataS2[BM_MAX_HITS] NO_INDEX_LIST);// ZERO_SUPPRESS);
    MEMBER(DATA32 dataS4[BM_MAX_HITS] NO_INDEX_LIST);// ZERO_SUPPRESS);

    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = S100_WR_BEAMMONITOR);
    }

    // CEJ: wrap in select several later to catch bad events
    UINT32 headS2 NOENCODE
    {
        0_12: l_hit_ct;
        13_15: reserved;
        16_31: l_id = MATCH(0xAAAA);
    };

    list (0 <= l_i < headS2.l_hit_ct)
    {
        UINT32 hit NOENCODE
        {
            0_31: data;
            ENCODE(dataS2 APPEND_LIST, (value = data));
        };

    }

    UINT32 headS4 NOENCODE
    {
        0_12: l_hit_ct;
        13_15: reserved;
        16_31: l_id = MATCH(0xBBBB);
    }

    list (0 <= l_i < headS4.l_hit_ct)
    {
        UINT32 hit NOENCODE
        {
            0_31: data;
            ENCODE(dataS4 APPEND_LIST, (value = data));
        }
    }

    UINT32 trailer NOENCODE
    {
        0_15: reserved;
        16_31: l_id = MATCH(0xCCCC);
    }
}

EVENT
{
    revisit aida = aida_subev(type = 10, subtype = 1, procid = S100_PROCID_AIDA, control = 37);
    germanium = febex_subev(type = 10, subtype = 1, procid = S100_PROCID_GERMANIUM, control = 20);
    fatima = fatima_tamex_subev(type = 10, subtype = 1, procid = S100_PROCID_FATIMA, control = 20);
    fatimavme = fatima_vme_subev(procid = S100_PROCID_FATIMAVME); // control 20, type 10, subtype 1
    bplast = bplast_subev(type = 10, subtype = 1, procid = S100_PROCID_BPLAST, control = 20);
    bgo = bgo_tamex_subevent(procid = S100_PROCID_BGO);

    frsmain = frs_main_subev(procid = S100_PROCID_FRSMAIN);
    frstpc = frs_tpc_subev(procid = S100_PROCID_FRSTPC);
    frsuser = frs_user_subev(procid = S100_PROCID_FRSUSER);
    frstpat = frs_tpat_subev(procid = S100_PROCID_FRSTPAT);
    
    beammonitor = bm_subev(procid = S100_PROCID_BEAMMONITOR);

    ignore_unknown_subevent;
};

#include "mapping.hh"
