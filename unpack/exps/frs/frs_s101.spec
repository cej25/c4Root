// -*- C++ -*-

#include "../../common/vme_caen_v1x90.spec"
#include "../../common/vme_caen_v830.spec"
#include "../../common/vme_caen_v7x5.spec"

TRIG3EVENT()
{
    UINT32 trig3 NOENCODE
    {
        0_31: 0x20202020;
    };
}

SPILL_ON()
{
    MEMBER(DATA8 spillon);
    UINT32 on NOENCODE
    {
        0_31: 0x30303030;
    }
    ENCODE(spillon, (value = 1));
}

SPILL_OFF()
{
    MEMBER(DATA8 spilloff);

    UINT32 off1 NOENCODE
    {
        0_31: 0x4040400a;
    };
    UINT32 off2 NOENCODE
    {
        0_31: 0x4040400b;
    };
    UINT32 off3 NOENCODE
    {
        0_31: 0x4040400c;
    };

    ENCODE(spilloff, (value = 1));
}


// for now this catches all of the barrier
BARRIER()
{
    UINT32 barrier NOENCODE
    {
        0_19: no;
        20_31: ba = RANGE(0xF52,0xF58);
    }
}

ZERO_FILLER()
{
    UINT32 filler NOENCODE
    {
        0_31: zero = MATCH(0x00000000);
    }
}

// procID = 15
TPAT_CRATE_DATA() 
{
    MEMBER(DATA16 tpat);
        
    // ignore first 3 words
    UINT32 w1;
    UINT32 w2;
    UINT32 w3;
    
    UINT32 trigger_pattern 
    {
        0_15: pattern;
        16_31: nothing; // trigger type?
        ENCODE(tpat, (value = pattern));
    }

    // sometimes this word is wrong... then what ...
    UINT32 coffee NOENCODE
    {
        0_7: scaler_words;
        8_31: coffee; // 0xc0ffee;
    }

    if (coffee.coffee == 0xc0ffee)
    {
        list (0 <= i < coffee.scaler_words * 3)
        {
            UINT32 scaler NOENCODE
            {
                0_31: something;
            }
        }

        UINT32 dead NOENCODE
        {
            0_31: 0xDEADDEAD;
        }

        several UINT32 eob NOENCODE;
    }
    else
    {
        // bad event?
        several UINT32 filler NOENCODE;
    }

    
}

MVLC_SCALER(geo)
{
    MEMBER(DATA32 scalers[32] ZERO_SUPPRESS);

    UINT32 header NOENCODE
    {
        0_15: whatever;
        16: 0;
        18_23: nlw;
        24_26: type;
        27_31: geom = MATCH(geo);
    };

    list (0 <= i < header.nlw) 
    {
        UINT32 scaler NOENCODE 
        {
            0_31: value;
            ENCODE(scalers[i], (value=value));
        }
    }

    UINT32 trailer NOENCODE;

}

// procID = 10
MAIN_CRATE_DATA()
{
    
    barrier0 = BARRIER();
    //v830 = VME_CAEN_V830(geom=8);
    v830 = MVLC_SCALER(geo=8); // geom = 8?
    
   // filler0 = ZERO_FILLER();

    barrier1 = BARRIER();
    v792 = VME_CAEN_V792(geom=14);
    
    UINT32 aaahhh NOENCODE { 0_31: 0xaaaa1290; }
    UINT32 exxxxx NOENCODE;

    barrier2 = BARRIER();
    v1290 = VME_CAEN_V1290_N();
    optional UINT32 eodb NOENCODE;

}

// procID = 20
TPC_CRATE_DATA()
{
    select several
    {
        barrier0 = BARRIER();
        v785 = VME_CAEN_V785(geom=8);
        v775 = VME_CAEN_V775(geom=12);
    }
    
    UINT32 aaahhh NOENCODE { 0_31: 0xaaaa1190; }
    UINT32 exxxxx NOENCODE;

    barrier1 = BARRIER();
    v1190 = VME_CAEN_V1190_N();

    // unknown data at the end of some events.. asklater
    select several
    {
        dummy = DUMMY();
    }
}

// procID = 30
USER_CRATE_DATA()
{
    barrier0 = BARRIER();
    // v830 = VME_CAEN_V830(geom=6);

    v830 = MVLC_SCALER(geo=8); // geom = 6? // 6 doesn't work..

    // filler0 = ZERO_FILLER();

    select several
    {
        barrier1 = BARRIER();
        v775[0] = VME_CAEN_V775(geom=8); // 8
        v775[1] = VME_CAEN_V775(geom=9); // 9
        v785[0] = VME_CAEN_V785(geom=10); // 31
        v785[1] = VME_CAEN_V785(geom=12); // 12
    }

    UINT32 aaahhh NOENCODE { 0_31: 0xaaaa1290; };
    UINT32 filler1 NOENCODE;
    barrier2 = BARRIER();
    v1290 = VME_CAEN_V1290_N();
    optional UINT32 eodb NOENCODE;
}