ERR_WORD_SIX()
{
    UINT32 err NOENCODE
    {
        0_31: err = MATCH(0x06000000);
    }
}

FATIMA_VME_SCALERS()
{   
    MEMBER(DATA32 data[32] ZERO_SUPPRESS);

    // do stuff init
    UINT32 sc_header NOENCODE
    {      
        0_7: empty1;
        8_12: nwords;
        13_26: empty2;
        27_31: geo = MATCH(0b01111);
    }

    list (0 <= index < sc_header.nwords)
    {
        UINT32 sc_data NOENCODE
        {
            0_31: value;
        }
        ENCODE(data[index], (value = sc_data.value));
    }

    UINT32 scaler_trailer NOENCODE;

}