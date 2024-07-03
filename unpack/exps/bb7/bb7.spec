// -*- C++ -*-

#include "../../common/whiterabbit.spec"
//#include "../../common/gsi_febex4.spec"
#include "../../common/vme_caen_v7x5.spec"
#include "../../common/vme_caen_v1x90.spec"

V7X5_DUMMY()
{
	UINT32 dummy NOENCODE
	{
		0_23: 0x000000;
		24_27: id = RANGE(5,8);
		28_31: 0x0;

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

EVENT
{
    bb7 = bb7_subev(procid=31); // no idea about identifier
}
