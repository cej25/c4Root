TIMESTAMP_WHITERABBIT(id)
{
	MEMBER(DATA12 subsystem_id);
	MEMBER(DATA16 t1);
	MEMBER(DATA16 t2);
	MEMBER(DATA16 t3);
	MEMBER(DATA16 t4);

	UINT32 header NOENCODE {
		0_11:  id = MATCH(id);
		12_15: 0;
		   16: error_bit;
		17_31: 0;
		ENCODE(subsystem_id, (value=id));
	};
	UINT32 d1 NOENCODE {
		0_15:  t1;
		16_31: 0x03e1;
		ENCODE(t1, (value=t1));
	};
	UINT32 d2 NOENCODE {
		0_15:  t2;
		16_31: 0x04e1;
		ENCODE(t2, (value=t2));
	};
	UINT32 d3 NOENCODE {
		0_15:  t3;
		16_31: 0x05e1;
		ENCODE(t3, (value=t3));
	};
	UINT32 d4 NOENCODE {
		0_15:  t4;
		16_31: 0x06e1;
		ENCODE(t4, (value=t4));
	};
}

TIMESTAMP_WHITERABBIT_EXTENDED(id)
{
	MEMBER(DATA16 subsystem_id);
	MEMBER(DATA16 t1);
	MEMBER(DATA16 t2);
	MEMBER(DATA16 t3);
	MEMBER(DATA16 t4);

	UINT32 header NOENCODE {
		0_12:  id = MATCH(id);
		13_15: 0;
		   16: error_bit;
		17_31: 0;
		ENCODE(subsystem_id, (value=id));
	};
	UINT32 d1 NOENCODE {
		0_15:  t1;
		16_31: 0x03e1;
		ENCODE(t1, (value=t1));
	};
	UINT32 d2 NOENCODE {
		0_15:  t2;
		16_31: 0x04e1;
		ENCODE(t2, (value=t2));
	};
	UINT32 d3 NOENCODE {
		0_15:  t3;
		16_31: 0x05e1;
		ENCODE(t3, (value=t3));
	};
	UINT32 d4 NOENCODE {
		0_15:  t4;
		16_31: 0x06e1;
		ENCODE(t4, (value=t4));
	};
}

WR_MULTI()
{
	MEMBER(DATA32 time_hi);
	MEMBER(DATA32 time_lo);

	UINT32 hi NOENCODE {
		0_31: time;
		ENCODE(time_hi, (value = time));
	}
	UINT32 lo NOENCODE {
		0_31: time;
		ENCODE(time_lo, (value = time));
	}
}

