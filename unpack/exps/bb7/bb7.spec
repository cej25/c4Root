// -*- C++ -*-

#include "../../common/whiterabbit_13bit.spec"
//#include "../../common/gsi_febex4.spec"
#include "../../common/vme_caen_v775_raw.spec"
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
        ts = TIMESTAMP_WHITERABBIT(id = 0x1800);
    }

    select several
    {
        v7x5[0] = VME_CAEN_V775_RAW(geom=6);
        v7x5_dummy = V7X5_DUMMY();
        v7x5[1] = VME_CAEN_V775_RAW(geom=8);
        v7x5[2] = VME_CAEN_V775_RAW(geom=10);
       // v7x5[3] = VME_CAEN_V775_RAW(geom=17);
        //v1290 = VME_CAEN_V1290_N();
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
