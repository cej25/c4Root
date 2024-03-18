// -*- C++ -*-

#include "../../../config/setup.h"
#include "../../common/whiterabbit.spec"

#define BM_MAX_HITS 100000


SUBEVENT(bm_subev)
{

    MEMBER(DATA32 dataS2[BM_MAX_HITS] NO_INDEX_LIST);// ZERO_SUPPRESS);
    MEMBER(DATA32 dataS4[BM_MAX_HITS] NO_INDEX_LIST);// ZERO_SUPPRESS);

    select optional
    {
        ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1700);
    }

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

    UINT32 trailer NOENCODE
    {
        0_15: reserved;
        16_31: l_id = MATCH(0xCCCC); // MATCH(0xCCCC);
    }
}

EVENT
{
    beammonitor = bm_subev(procid = 70);

    ignore_unknown_subevent;
}
