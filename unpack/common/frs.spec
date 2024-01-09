#include "vme_caen_v1x90.spec"
#include "vme_caen_v830.spec"
#include "vme_caen_v792.spec"
#include "vme_caen_v7x5.spec"
#include "mesytec_mqdc32.spec"
#include "mesytec_mtdc32.spec"
#include "sis3820_scalers.spec"
#include "gsi_vftx2.spec"

TRIG3EVENT()
{
    UINT32 trig3 NOENCODE
    {
        0_31: 0x20202020;
    }
}

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

MAIN_CRATE_DATA()
{

    barrier[0] = BARRIER();
    v830 = VME_CAEN_V830_FRS();
    
    filler[0] = ZERO_FILLER();
    barrier[1] = BARRIER();
    v792 = VME_CAEN_V792_FRS();

    barrier[2] = BARRIER();
    v1290 = VME_CAEN_V1290_FRS();

}

TPC_CRATE_DATA()
{
    // caen v775 and v785 (same readout, read 2)
    barrier[0] = BARRIER();
    v775 = VME_CAEN_V7X5_FRS();

    barrier[1] = BARRIER();
    v785 = VME_CAEN_V7X5_FRS();

    // caen v1190
    barrier[2] = BARRIER();
    v1190 = VME_CAEN_V1190_FRS();
}

USER_CRATE_DATA()
{
    // caen v820 or v830
    barrier[0] = BARRIER();
    v830 = VME_CAEN_V830_FRS();

    // caen v775 x2 and caen v785 x2
    filler[0] = ZERO_FILLER();
    barrier[1] = BARRIER();
    v775[0] = VME_CAEN_V7X5_FRS();

    barrier[2] = BARRIER();
    v775[1] = VME_CAEN_V7X5_FRS();

    barrier[3] = BARRIER();
    v785[0] = VME_CAEN_V7X5_FRS();

    barrier[4] = BARRIER();
    v785[1] = VME_CAEN_V7X5_FRS();

}

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