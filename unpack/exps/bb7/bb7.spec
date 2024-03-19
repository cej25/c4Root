// -*- C++ -*-

#include "../../common/whiterabbit.spec"
#include "../../common/gsi_febex4.spec"

SUBEVENT(febex_subev)
{
    ts = TIMESTAMP_WHITERABBIT(id = 0x400); // no idea about wr signal

    select several
    {
        padding = FEBEX_PADDING();
    };

    select several
    {
        data[0] = FEBEX_EVENT(card = 0);
        data[1] = FEBEX_EVENT(card = 1);
        data[2] = FEBEX_EVENT(card = 2);
        data[3] = FEBEX_EVENT(card = 3);
        // no idea about how many cards
    };
}

EVENT
{
    bb7 = febex_subev(); // no idea about identifiers
}