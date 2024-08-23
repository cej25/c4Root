#include "EventHeader.h"
#include "FairRootManager.h"

Bool_t EventHeader::fPersistance = false;

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

void EventHeader::Register(Bool_t Persistance)
{
    FairRootManager::Instance()->Register("EventHeader.", "EvtHeader", this, Persistance);
}

ClassImp(EventHeader);
