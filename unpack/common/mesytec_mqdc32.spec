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