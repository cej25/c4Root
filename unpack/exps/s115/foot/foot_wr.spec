FOOT_TIMESTAMP_WHITERABBIT_EXTENDED(id)
{
	MEMBER(DATA32 t_lo);
	MEMBER(DATA32 t_hi);

	UINT32 header NOENCODE {
		0_13:  id = MATCH(id);
		14_15: 0;
		16: error_bit;
		17_31: 0;
	};
	UINT32 tll NOENCODE {
		0_15: val;
		16_31: 0x03e1;
	}
	UINT32 tlh NOENCODE {
		0_15: val;
		16_31: 0x04e1;
	}
	UINT32 thl NOENCODE {
		0_15: val;
		16_31: 0x05e1;
	}
	UINT32 thh NOENCODE {
		0_15: val;
		16_31: 0x06e1;
	}
	
	ENCODE(t_lo, (value = ((static_cast<unsigned>(tlh.val) << 16)) | tll.val)); 
	ENCODE(t_hi, (value = ((static_cast<unsigned>(thh.val) << 16)) | thl.val));
}

TIMESTAMP_SYNC_CHECK()
{
	MEMBER(DATA12 ref_recv);
	MEMBER(DATA16 value);

	UINT32 u32 NOENCODE {
		 0_15: value;
		16_19: ref_recv;
		20_31: 0xf1a;
		ENCODE(ref_recv, (value = ref_recv));
		ENCODE(value,    (value = value));
	};
}
