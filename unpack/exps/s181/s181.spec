// -*- C++ -*-

#include "../../../config/setup.h"
#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"
#include "../../common/gsi_tamex4.spec"
#include "../../common/vme_caen_v1751.spec"
//#include "../../common/vme_caen_v1x90.spec"
#include "../frs/frs_s181.spec"
#include "fatima_vme.spec"
#include "../../common/general.spec"

#define BM_MAX_HITS 100000

// making a change

external EXT_AIDA();

V7X5_DUMMY()
{
	UINT32 dummy NOENCODE
	{
		0_23: nothing;
		24_27: id = RANGE(5,8);
		28_31: nothing22;

	}
}

SUBEVENT(bb7_subev)
{
    select optional 
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1800);
    }

    select several
    {
        v7x5_module[0] = VME_CAEN_V7X5_FRS(card=11);
	    v7x5_dummy = V7X5_DUMMY();
        v7x5_module[1] = VME_CAEN_V7X5_FRS(card=13);
        v7x5_module[2] = VME_CAEN_V7X5_FRS(card=15);
        v7x5_module[3] = VME_CAEN_V7X5_FRS(card=17);
        v1290_module = VME_CAEN_V1290_FRS();
    }
	
    list (0 <= i < 3)
    {
	    optional UINT32 more_eob_words NOENCODE;
    }

}

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

// this must change to be more general, or name should change from febex_subev
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
    };
}

SUBEVENT(fatima_tamex_subev)
{

    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1600);
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
    };
}

SUBEVENT(fatima_vme_subev)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = 0x1500);
    };

    select several
    {
        error1 = ERR_WORD_SIX();
    };

    select optional
    {
        scalers = FATIMA_VME_SCALERS();
    };

    // don't love this but ucesb is a real pain in the ass
    select optional
    {
        qdc1 = VME_CAEN_V1751(board=6);
    }

    select optional
    {
        qdc2 = VME_CAEN_V1751(board=7);
    }

    select optional
    {
        qdc3 = VME_CAEN_V1751(board=8);
    }

    select optional
    {
        qdc4 = VME_CAEN_V1751(board=9);
    }

    select optional
    {
        qdc5 = VME_CAEN_V1751(board=10);
    }
    
    /*qdc[0] = VME_CAEN_V1751(board=6);
    qdc[1] = VME_CAEN_V1751(board=7);
    qdc[2] = VME_CAEN_V1751(board=8);
    qdc[3] = VME_CAEN_V1751(board=9);
    qdc[4] = VME_CAEN_V1751(board=10);*/
   
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
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1700);
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
    revisit aida = aida_subev(type = 10, subtype = 1, procid = 90, control = 37);
    germanium = febex_subev(type = 10, subtype = 1, procid = 60, control = 20);
    fatima = fatima_tamex_subev(type = 10, subtype = 1, procid = 75, control = 20);
    fatimavme = fatima_vme_subev(type = 10, subtype = 1, procid = 70, control = 20);
    bplast = bplast_subev(type = 10, subtype = 1, procid = 80, control = 20);
    bgo = bgo_tamex_subevent(procid = 100);
    bbseven = bb7_subev(procid=31);

    frsmain = frs_main_subev(procid = 10);
    frstpc = frs_tpc_subev(procid = 20);
    frsuser = frs_user_subev(procid = 30);
    frstpat = frs_tpat_subev(procid = 15);
    
    beammonitor = bm_subev(procid = 1);

    ignore_unknown_subevent;
};
