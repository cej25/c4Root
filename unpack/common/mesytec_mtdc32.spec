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