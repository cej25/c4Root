// Standalone UCESB grammar probe. Do not integrate into s100.
#include "../../common/gsi_tamex4.spec"
SUBEVENT(tamex4_stream)
{
    select optional { trigger_window = TAMEX4_HEADER(); };
    select several { padding = TAMEX4_PADDING(); };
    select several { tamex[0] = TAMEX4_SFP(sfp=0,card=0); };
}
EVENT
{
    tamex[0] = tamex4_stream(procid=75);
    tamex[1] = tamex4_stream(procid=80);
    ignore_unknown_subevent;
};
