// -*- C++ -*-

#include "config.spec"
#include "whiterabbit.spec"
#include "febex.spec"

DUMMY()
{
  UINT32 no NOENCODE;
}

SUBEVENT(febex_subev)
{
  // white rabbit
  if (withWR)
  {
    wr = TIMESTAMP_WHITERABBIT(id=0x400);
  }
  
  // padding (select several essential)
  select several
  {
    padding = FEBEX_PADDING();
  }
  
  data = FEBEX_TRACES();

}

EVENT
{

  lisa = febex_subev(procid = 60);

  ignore_unknown_subevent;
}

// for mapping UNPACK -> RAW
#include "mapping.hh"