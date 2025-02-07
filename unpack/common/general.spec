// -*- C++ -*-


BAD_EVENT()
{
    MEMBER(DATA8 bad);
    
    UINT32 be NOENCODE
    {
        0_31: b = MATCH(0xbad00bad);
    }

    ENCODE(bad, (value = 1));
}

DUMMY()
{
    UINT32 no NOENCODE;
}
