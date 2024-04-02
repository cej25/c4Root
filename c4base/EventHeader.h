#ifndef EventHeader_H
#define EventHeader_H

#include "FairEventHeader.h"
#include <stdexcept>

class EventHeader : public FairEventHeader
{
  public:
    EventHeader();
    EventHeader(
    uint64_t Eventno,
    Int_t Trigger,
    uint64_t TimeStamp);
    virtual ~EventHeader();

    void SetEventno(const uint64_t eventno) { fEventno = eventno; }
    void SetTrigger(const Int_t trigger) { fTrigger = trigger; }
    void SetTimeStamp(const uint64_t timeStamp) { fTimeStamp = timeStamp; }
    inline void SetSpillFlag(bool flag) { fSpillFlag = flag; }

    uint64_t GetEventno() const { return fEventno; }
    Int_t GetTrigger() const { return fTrigger; }
    uint64_t GetTimeStamp() const { return fTimeStamp; }
    inline bool GetSpillFlag() { return fSpillFlag; }

    virtual void Register(Bool_t Persistance = kTRUE);

  private:
    uint64_t fEventno;
    Int_t fTrigger;
    uint64_t fTimeStamp;
    bool fSpillFlag;

    ClassDef(EventHeader, 1)
};


#endif /* EventHeader_H */
