#include "EventHeader.h"

EventHeader::EventHeader()
    : FairEventHeader()
    , fEventno(0)
    , fTrigger(0)
    , fTimeStamp(0)
{
}

EventHeader::EventHeader(uint64_t Eventno, Int_t Trigger, uint64_t TimeStamp)
    : FairEventHeader()
    , fEventno(Eventno)
    , fTrigger(Trigger)
    , fTimeStamp(TimeStamp)
{
}

EventHeader::~EventHeader() {}

void EventHeader::Register(Bool_t Persistence) {}

ClassImp(EventHeader);
