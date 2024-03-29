// -*- C++ -*-

#include "../../common/vme_caen_v1x90.spec"
#include "../../common/vme_caen_v830.spec"
#include "../../common/vme_caen_v792.spec"
#include "../../common/vme_caen_v7x5.spec"
#include "../../common/mesytec_mqdc32.spec" // not needed, testing
#include "../../common/mesytec_mtdc32.spec"
#include "../../common/sis3820_scalers.spec"
#include "../../common/gsi_vftx2.spec"

TRIG3EVENT()
{
    UINT32 trig3 NOENCODE
    {
        0_31: 0x20202020;
    }
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
        
    // first three words are meaningless
    UINT32 w1;
    UINT32 w2;
    UINT32 w3;
    
    UINT32 trigger_pattern 
    {
        0_15: pattern;
        16_31: nothing;
        ENCODE(tpat, (value = pattern));
    }
    
}

// procID = 10
MAIN_CRATE_DATA()
{
    
    barrier[0] = BARRIER();
    v830 = VME_CAEN_V830_FRS();
    
    filler[0] = ZERO_FILLER();

    barrier[1] = BARRIER();
    v792 = VME_CAEN_V792_FRS();
    
    UINT32 aaahhh NOENCODE
    {
        0_31: 0xaaaa1290;
    };
    UINT32 exxxxx NOENCODE; // find out what word this is

    barrier[2] = BARRIER();
    v1290 = VME_CAEN_V1290_FRS();
    optional UINT32 eodb NOENCODE;

}

// procID = 20
TPC_CRATE_DATA()
{
    // caen v775 and v785 (same readout, read 2)
    select several
    {
        barrier0 = BARRIER();
        v775 = VME_CAEN_V7X5_FRS(card=12);
        v785 = VME_CAEN_V7X5_FRS(card=8);
    }
    
    /*
    barrier[0] = BARRIER();
    v775 = VME_CAEN_V7X5_FRS(card=12);

    barrier[1] = BARRIER();
    v785 = VME_CAEN_V7X5_FRS(card=8);
    */

    // caen v119
    
    UINT32 aaahhh NOENCODE
    {
        0_31: 0xaaaa1190;
    };
    UINT32 exxxxx NOENCODE;

    barrier[2] = BARRIER();
    v1190 = VME_CAEN_V1190_FRS();
}

// procID = 30
USER_CRATE_DATA()
{
    // caen v820 or v830
    barrier0 = BARRIER();
    v830 = VME_CAEN_V830_FRS();

    // caen v775 x2 and caen v785 x2

    filler[0] = ZERO_FILLER();

    select several
    {
        barrier1 = BARRIER();
        // really not sure if this is correct, we'll see
        v775[0] = VME_CAEN_V7X5_FRS(card=8);
        v775[1] = VME_CAEN_V7X5_FRS(card=9);
        v785[0] = VME_CAEN_V7X5_FRS(card=10);
        v785[1] = VME_CAEN_V7X5_FRS(card=12);
    }

    /*
    barrier[1] = BARRIER();
    v775[0] = VME_CAEN_V7X5_FRS(card=8);

    barrier[2] = BARRIER();
    v775[1] = VME_CAEN_V7X5_FRS(card=);

    barrier[3] = BARRIER();
    v785[0] = VME_CAEN_V7X5_FRS(card=);

    barrier[4] = BARRIER();
    v785[1] = VME_CAEN_V7X5_FRS(card=);*/

}

// procID = 40
VFTX_CRATE_DATA()
{
    // vftx (at s2)
    vftx = VFTX2(id=0);

    // mtdc
    barrier[1] = BARRIER();
    mtdc = MESYTEC_MTDC32_FRS();

    // mqdc - sometimes 0, 1 or 2 comes through?
    // and UCESB is bloody stupid
    barrier[2] = BARRIER();
    select optional
    {
        mqdc0 = MESYTEC_MQDC32_FRS();
    }
    select optional
    {
        mqdc1 = MESYTEC_MQDC32_FRS();
    }
    
}
