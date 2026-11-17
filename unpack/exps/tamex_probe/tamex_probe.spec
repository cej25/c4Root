// -*- C++ -*-
// UCESB-only feasibility probe: instantiate a single generic TAMEX4
// subevent definition for two different MBS procids.
// This does not replace the validated s100 unpacker.
#include "../../common/gsi_tamex4.spec"

SUBEVENT(tamex4_stream)
{
    select optional
    {
        trigger_window = TAMEX4_HEADER();
    };

    select several
    {
        padding = TAMEX4_PADDING();
    };

    select several
    {
        tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    };
}

EVENT
{
    stream_a = tamex4_stream(type=10,subtype=1,procid=75,control=20);
    stream_b = tamex4_stream(type=10,subtype=1,procid=80,control=20);
    ignore_unknown_subevent;
};
