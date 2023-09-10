#include "EventHeader.h"

EventHeader::EventHeader()
    : FairEventHeader()
    , fEventno(0)
    , fTrigger(0)
    , fTimeStamp(0)
{
}

EventHeader::~EventHeader() {}

void EventHeader::Register(Bool_t Persistence) {}

ClassImp(EventHeader);
