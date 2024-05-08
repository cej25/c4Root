

#include "../../common/whiterabbit.spec"
#include "../../common/vme_mesytec_mdpp16.spec"

SUBEVENT(travmus_subev)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id=0x200);
    };

    UINT32 barrier NOENCODE
    {
        0_15: counter;
        16_31: bar = MATCH(0xF520);

    };

    select several
    {
        data = VME_MESYTEC_MDPP16(geom=8);
    };
}

EVENT
{
    travmus = travmus_subev(procid=35);

    ignore_unknown_subevent;
}