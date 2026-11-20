// The timestamp words are identical in both WR formats. The configured ID
// matches bits 0-12 exactly in the unified decoder. Standard IDs have
// bit 12 clear, so a standard packet still requires that bit to be zero.
#define DECLARE_WR_TIMESTAMP(decoder, id_type, id_bits, reserved_bits) \
decoder(id) \
{ \
	MEMBER(id_type subsystem_id); \
	MEMBER(DATA16 t1); \
	MEMBER(DATA16 t2); \
	MEMBER(DATA16 t3); \
	MEMBER(DATA16 t4); \
 \
	UINT32 header NOENCODE { \
		id_bits: id = MATCH(id); \
		reserved_bits: 0; \
		   16: error_bit; \
		17_31: 0; \
		ENCODE(subsystem_id, (value=id)); \
	}; \
	UINT32 d1 NOENCODE { \
		0_15:  t1; \
		16_31: 0x03e1; \
		ENCODE(t1, (value=t1)); \
	}; \
	UINT32 d2 NOENCODE { \
		0_15:  t2; \
		16_31: 0x04e1; \
		ENCODE(t2, (value=t2)); \
	}; \
	UINT32 d3 NOENCODE { \
		0_15:  t3; \
		16_31: 0x05e1; \
		ENCODE(t3, (value=t3)); \
	}; \
	UINT32 d4 NOENCODE { \
		0_15:  t4; \
		16_31: 0x06e1; \
		ENCODE(t4, (value=t4)); \
	}; \
}

#ifdef WR_USE_13BIT_ID
DECLARE_WR_TIMESTAMP(TIMESTAMP_WHITERABBIT, DATA16, 0_12, 13_15)
#else
// Compatibility for experiments with existing DATA12 SIGNAL mappings.
DECLARE_WR_TIMESTAMP(TIMESTAMP_WHITERABBIT, DATA12, 0_11, 12_15)
DECLARE_WR_TIMESTAMP(TIMESTAMP_WHITERABBIT_EXTENDED, DATA16, 0_12, 13_15)
#endif
#undef DECLARE_WR_TIMESTAMP

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

