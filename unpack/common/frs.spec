#include "vme_caen_v1x90.spec"
#include "vme_caen_v830.spec"
#include "vme_caen_v792.spec"
#include "vme_caen_v7x5.spec"
#include "mesytec_mqdc32.spec"
#include "mesytec_mtdc32.spec"
#include "sis3820_scalers.spec"

SKIP(n)
{
    list (0 <= i < n)
    {
        optional UINT32 skip NOENCODE;
    }
}

BARRIER()
{
    UINT32 barrier NOENCODE
    {
        0_31: ba = MATCH(0xbabababa);
    }
}

MAIN_CRATE_DATA()
{
    skip[0] = SKIP(n=2);
    barrier[0] = BARRIER();
    select optional
    {   
        v1290 = VME_CAEN_V1290_FRS();
    }
    barrier[1] = BARRIER();
    select optional
    {
        v830 = VME_CAEN_V830_FRS();
    }
    select optional
    {
        v792 = VME_CAEN_V792_FRS();
    }
    barrier[2] = BARRIER();
    list (0 <= i < 4)
    {   
        // unused optionals for good events
        optional UINT32 eoe NOENCODE;
    }
}

TPAT_DATA(id)
{   
    MEMBER(DATA32 n);
	MEMBER(DATA16 tpat[170] NO_INDEX_LIST);
	MEMBER(DATA8 trig[170] NO_INDEX_LIST);
	MEMBER(DATA32 ts_lo[170] NO_INDEX_LIST);
	MEMBER(DATA32 ts_hi[170] NO_INDEX_LIST);

    // first word is 0x0000000 it seems
    skip = SKIP(n=1);

	UINT32 header NOENCODE {
		0_11:  count;
		12_23: eventno;
		24_31: id = MATCH(id);
		ENCODE(n, (value = count / 3));
	}

	list(0 <= index < header.count / 3) {
		UINT32 time_lo NOENCODE {
			0_31: ts;
			ENCODE(ts_lo APPEND_LIST, (value = ts));
		}
		UINT32 time_hi NOENCODE {
			0_30: ts;
			31:   overflow;
			ENCODE(ts_hi APPEND_LIST, (value = ts));
		}
		UINT32 trigger NOENCODE {
			 0_15: tpat;
			16_23: reserved;
			24_27: trig;
			28_31: reserved2;
			ENCODE(tpat APPEND_LIST, (value = tpat));
			ENCODE(trig APPEND_LIST, (value = trig));
		}
	}
}

TOF_DATA()
{   

    MEMBER(DATA32 coarse_time[32] ZERO_SUPPRESS_MULTI(32));
    MEMBER(DATA32 fine_time[32] ZERO_SUPPRESS_MULTI(32));

    // first 3 words
    skip0 = SKIP(n=2);
    barrier[0] = BARRIER();

    // --- vftx at S2 sofia ---
    UINT32 p32_tmp NOENCODE
    {   
        0_8: reserved;
        9_17: count;
        18_23: reserved2;
        24_31: marker;
    }
    
    if (p32_tmp.marker == 0xAB)
    {
        skip1 = SKIP(n=1);

        list (0 <= i < p32_tmp.count - 1)
        {
            UINT32 data NOENCODE
            {   
                0_10: fine_time;
                11_23: coarse_time;
                24_25: reserved;
                26_30: channel; // getbits(2,11,5) in Go4?
                //ENCODE(blah blah... );
            }
        }
    };
    // --- vftx at S2 sofia ---

    barrier[1] = BARRIER();

    select optional
    {
        qdc = MESYTEC_MQDC32_FRS(); // select optional?
    };

    barrier[2] = BARRIER();

    select optional
    {
        tdc = MESYTEC_MTDC32_FRS(); // not used in s452
    };

    select optional
    {
        sis3820 = SIS_3820_FRS(); // used in s452, not in s450
    };

    select optional // this is optional, for good events
    {
        barrier3 = BARRIER();
    }
}

TPC_DATA()
{   
    skip0 = SKIP(n=2);
    barrier[0] = BARRIER();
    select optional
    {
        v830 = VME_CAEN_V830_FRS();
    } // removed in s450
    barrier[1] = BARRIER();
    select optional
    {   
        v1190 = VME_CAEN_V1190_FRS();
    }

    barrier[2] = BARRIER();

}

FRS_DATA()
{
    skip0 = SKIP(n=2);
    barrier[0] = BARRIER();
    select optional // not used in S450...future?
    {
        v830 = VME_CAEN_V830_FRS();
    }
    select several
    {
        v7x5 = VME_CAEN_V7X5_FRS(); // must figure that out... v775 x2 and v785 x2
    }
  
}