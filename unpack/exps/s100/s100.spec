// -*- C++ -*-

// #include "../../../config/setup.h"
#include "s100_config.gen.spec"
#include "../../common/whiterabbit_13bit.spec"
#define FEBEX_EXPORT_BOARD_METADATA
#include "../../common/gsi_febex4.spec"
#undef FEBEX_EXPORT_BOARD_METADATA
#include "../../common/gsi_tamex4.spec"
#include "tamex_payload.spec"
#include "../../common/vme_caen_v1751.spec"
//#include "../../common/vme_caen_v1x90.spec"
#include "../frs/frs_s100.spec" //r3b frs
#include "../../common/vme_caen_v1290_geo.spec"
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
        S100_DEGAS_CARDS
    };
}

SUBEVENT(fatima_tamex_subev)
{
    S100_TAMEX_PAYLOAD(S100_WR_FATIMA, S100_TAMEX_CARDS_FATIMA)
}

SUBEVENT(fatima_vme_subev)
{
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
    // output slot tied to the board ID, even if earlier boards are absent.
    // The error marker can occur among module payloads.
    select several
    {
        S100_V1751_BANKS
        error2 = ERR_WORD_SIX();
    };

    // The installed V1290s use GEOs 12 and 13. The remaining slots are reserved.
    // Both modules can be absent, and error words can appear between them.
    // Their selection indices are fixed by GEO, not arrival order.
    select several
    {
        S100_V1290_BANKS
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
