#ifndef EventHeader_H
#define EventHeader_H 1

#include "FairEventHeader.h"
#include <stdexcept>

class EventHeader : public FairEventHeader
{
  public:
    EventHeader();
    virtual ~EventHeader();

    void SetEventno(const uint64_t eventno) { fEventno = eventno; }
    void SetTrigger(const Int_t trigger) { fTrigger = trigger; }
    void SetTimeStamp(const uint64_t timeStamp) { fTimeStamp = timeStamp; }

    uint64_t GetEventno() const { return fEventno; }
    Int_t GetTrigger() const { return fTrigger; }
    uint64_t GetTimeStamp() const { return fTimeStamp; }

    virtual void Register(Bool_t Persistance = kTRUE);

  private:
    uint64_t fEventno;
    Int_t fTrigger;
    uint64_t fTimeStamp;

    ClassDef(EventHeader, 8)
};

#endif /* EventHeader_H */
