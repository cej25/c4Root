// 32-channel V775 with status bits retained in the sparse channel data.
// FRS uses the value-only V7X5 decoder for its existing signal mappings.
VME_CAEN_V775_RAW(geom)
{
    MEMBER(DATA8 geo);
    MEMBER(DATA16 data[32] ZERO_SUPPRESS);

    UINT32 header NOENCODE
    {
        0_7: unused;
        8_13: count;
        16_23: crate;
        24_26: 0b010;
        27_31: address = MATCH(geom);

        ENCODE(geo, (value = address));
    }

    list (0 <= index < header.count)
    {
        UINT32 ch_data NOENCODE
        {
            0_14: sample; // 12-bit value, overflow, under threshold, valid
            15: unused;
            16_20: channel;
            21_23: unused2;
            24_26: 0b000;
            27_31: address;

            ENCODE(data[channel], (value = sample));
        }
    }

    UINT32 eob NOENCODE
    {
        0_23: event_counter;
        24_26: 0b100;
        27_31: address = MATCH(geom);
    }

    // Empty-buffer words may follow the trailer. Their GEO is undefined.
    list (0 <= index < 2)
    {
        optional UINT32 padding NOENCODE
        {
            0_23: unused;
            24_26: type = MATCH(0b110);
            27_31: unused2;
        }
    }
}
