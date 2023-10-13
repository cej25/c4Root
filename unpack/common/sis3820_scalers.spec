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