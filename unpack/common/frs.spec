//#include ""


// ZSM(128) is a somewhat arbitrary i think? 
// Especially as we discard anything beyond 10. 
// Maybe can choose 64 or 32? 32 is max?
#define MEMBERS \
    MEMBER(DATA24 data[32] ZERO_SUPPRESS_MULTI(32)); \
    MEMBER(DATA8 channel[32] NO_INDEX_LIST); \
    MEMBER(DATA8 leadOrTrail[32] NO_INDEX_LIST);// not sure how to define this properly


// should it be 32 channels? lets see

#define PARAMS_DEF \
    data, \
	channel, \
    leadOrTrail

#define PARAMS \
    data = data, \
	channel = channel, \
    leadOrTrail = leadOrTrail

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

TDC_DATA_V1290(PARAMS_DEF)
{   
    MEMBERS

    UINT32 tdc_data NOENCODE
    {
        0_20: value;
        21_25: chn;
        26: lot;
        27_31: 0b00000;
        
        ENCODE(data[chn],(value = value/*,trailing=trailing*/));
        ENCODE(channel APPEND_LIST, (value = chn));
        ENCODE(leadOrTrail APPEND_LIST, (value = lot));
    }
}

TDC_DATA_V1190() // PARAMS_DEF
{   
    //MEMBERS

    UINT32 tdc_data NOENCODE
    {
        0_18: value;
        19_25: chn;
        26: lot;
        27_31: 0b00000;
        
       //ENCODE(data[chn],(value = value/*,trailing=trailing*/));
       //ENCODE(channel APPEND_LIST, (value = chn));
       //ENCODE(leadOrTrail APPEND_LIST, (value = lot));
    }
}


TDC_HEADER()
{   
    // don't think we need to encode this?
    UINT32 tdc_header NOENCODE
    {
        0_11: bunch_id;
        12_23: event_id;
        24_25: tdc;
        26: unused;
        27_31: 0b00001;
    }
}

TDC_ERROR()
{   
    // don't need to encode
    UINT32 tdc_err NOENCODE
    {
        0_14: error_flags;
        15_23: unused1;
        24_25: tdc;
        26: unused2;    
        27_31: 0b00100;
    }
}

TDC_TRAILER()
{   
    // don't need to encode any of this
    UINT32 tdc_trailer NOENCODE
    {
        0_11: word_count;
        12_23: event_id;
        24_25: tdc;
        26: unused;
        27_31: 0b00011;
    }
}

ADC_DATA()
{
    UINT32 adc_data NOENCODE
    {   
        0_11: adc;
        12: overflow;
        13: underthreshold;
        14_15: unused;
        16_20: channel;
        21_23: unused2;
        24_26: 0b000;
        27_31: geo;
    };
}


VME_CAEN_V1290_FRS()
{   

    MEMBERS

    UINT32 v1290_header NOENCODE
    {   
        0_4: geo;
        5_26: event_count;
        27_31: 0b01000;
    };

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1290(PARAMS);
        tdc_error = TDC_ERROR();
        tdc_trailer = TDC_TRAILER(); 
    };
 
    // if enabled
    optional UINT32 ext_time_tag NOENCODE
    {
        0_26: time_tag;
        27_31: 0b10001;
    };

    UINT32 trailer NOENCODE
    {
        0_4: geo;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };

}

VME_CAEN_V830_FRS()
{
    UINT32 v830_header NOENCODE
    {   
        0_15: trigger_number;
        16_17: ts;
        18_23: nwords;
        24_25: unused;
        26: 0b1; // distinguish header from 26bit word
        27_31: geo;
    };

    list (0 <= i < v830_header.nwords)
    {
        UINT32 data_word NOENCODE
        {
            0_31: data;
        };
    }
 
/*
    UINT32 eob NOENCODE
    {

    };

    */
}

VME_CAEN_V792_FRS()
{
    UINT32 v792_header NOENCODE
    {   
        0_7: unused;
        8_13: cnt;
        14_15: 0b00;
        16_23: crate;
        24_26: 0b010;
        27_31: geo;
    };
    
    several UINT32 adc_data NOENCODE
    {   
        0_11: adc;
        12: overflow;
        13: underthreshold;
        14_15: unused;
        16_20: channel;
        21_23: unused2;
        24_26: 0b000;
        27_31: geo;
    };

    UINT32 eob NOENCODE
    {   
        0_23: eventcounter;
        24_26: 0b100;
        27_31: geo;
    };
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
        // end of event unused words
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

MESYTEC_MQDC32_FRS()
{   
    // MEMBER
    MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS); // overflow....wat

    UINT32 header NOENCODE
    {
        0_11:  word_number;
        12_14: 0b000;
        16_23: geom;
        24_29: 0b000000;
        30_31: 0b01;
    };

    several UINT32 ch_data NOENCODE
    {
      0_11:  value;
      15:    outofrange;
      16_20: channel;
      21_29: 0b000100000;
      30_31: 0b00;

      ENCODE(data[channel], (value = value, overflow = outofrange));
    };

    optional UINT32 zero NOENCODE
    {
        0_31: 0x00000000;
    };

    UINT32 end_of_event NOENCODE
    {
        0_29:  counter;
        30_31: 0b11;
    }
   
}

MESYTEC_MTDC32_FRS()
{
    MEMBER(DATA16 data[34] ZERO_SUPPRESS);

    UINT32 header NOENCODE
    {
        0_11:  word_number;
        12_15: tdc_resol;
        16_23: geom;
        24_29: 0b000000; // was 24_29: 0b000000 or something
        30_31: 0b01; // was 30_31: 0b01 as word was 0x4, but data doesn't seem to agree w this.
    };

    list (0 <= index < header.word_number)
    {
        UINT32 ch_data NOENCODE
        {
            0_15:  value;
            16_20: channel;
            21:    trig;
            22_29: 0b00010000;
            30_31: 0b00;

            ENCODE(data[trig * 32 + channel], (value = value));
        }
    }

    optional UINT32 zero NOENCODE
    {
        0_31: 0x00000000;
    };
  
    UINT32 end_of_event NOENCODE
    {
        0_29:  counter;
        30_31: 0b11;
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


VME_CAEN_V1190_FRS()
{
    //MEMBERS

    UINT32 v1190_header NOENCODE
    {
        0_4: geo;
        5_26: event_count;
        27_31: 0b01000;
    }

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1190(); // PARAMS
        tdc_error = TDC_ERROR();
        tdc_trailer = TDC_TRAILER();
    }

    // if enabled
    optional UINT32 ext_time_tag NOENCODE
    {
        0_26: time_tag;
        27_31: 0b10001;
    };

    UINT32 trailer NOENCODE
    {
        0_4: geo;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };
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

VME_CAEN_V775_FRS()
{
    MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS);
    //MEMBER(DATA32 data[32] ZERO_SUPPRESS);

    UINT32 header NOENCODE
    {
        0_5: count;
        //   6_15: 0b0000000000;
        16_23: crate;
        24_26: 0b010;
        27_31: geom;
    }

    list(0 <= index < header.count)
    {
        UINT32 ch_data NOENCODE
	    {
	        0_11: value;
            12: overflow;
            13: underflow;
            14: valid;
            // 15: undefined;
            16_20: channel;
            24_26: 0b000;
            27_31: geom;
	  	    ENCODE(data[channel],(value=value,overflow = overflow));
	    }
    }
  
    UINT32 eob
    {
        0_23:  event_number;
        24_26: 0b100;
        27_31: geom;
    }
}

VME_CAEN_V785_FRS()
{
    MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS);

  UINT32 header NOENCODE
    {
      // 0_7: undefined;
      8_13:  count;
      16_23: crate;// = MATCH(crate);
      24_26: 0b010;
      27_31: geom;// = MATCH(geom);
    }

  list(0<=index<header.count)
    {
      UINT32 ch_data NOENCODE
	{
	  0_11:  value;

	  12:    overflow;
	  13:    underflow;
	  14:    valid;

	  // 15: undefined;

	  16_20: channel;

	  24_26: 0b000;
	  27_31: geom;// = CHECK(geom);

	  ENCODE(data[channel],(value=value,overflow=overflow));
	}
    }

  UINT32 eob
    {
      0_23:  event_number;
      24_26: 0b100;
      27_31: geom;// = CHECK(geom);
      // NOENCODE;
    }
}

SIS_3820_FRS()
{
    MEMBER(DATA32 data[32] ZERO_SUPPRESS);

	UINT32 custom_header NOENCODE
	{
		  0_7: nchs;
		 8_21: nevts;
		   22: latching;
		23_26: data_format;
		27_31: id; // MATCH(GEOM)
	}

	list(0 <= index < custom_header.nchs) {
		if (1 == custom_header.data_format) {
			UINT32 event NOENCODE {
				0_31: val;
			}
			ENCODE(data[index], (value = event.val));
		}
		if (0 == custom_header.data_format || 3 == custom_header.data_format) {
			UINT32 event NOENCODE {
				 0_23: val;
				24_28: channel;
				   29: 0b0;
				30_31: user_bits;
			}
			ENCODE(data[event.channel], (value=event.val));
		}
	}

}


FRS_DATA()
{
    skip0 = SKIP(n=2);
    barrier[0] = BARRIER();
    select optional
    {
        v830 = VME_CAEN_V830_FRS();
    }
    //barrier[1] = BARRIER();
    select several // optional
    {
        //v775 = VME_CAEN_V775_FRS();
        v785 = VME_CAEN_V785_FRS(); // v775 x2 and v785 x2
    }
    /*select optional
    {
        v785 = VME_CAEN_V785_FRS();
    }*/
    
}