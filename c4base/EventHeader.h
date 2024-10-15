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

    // bplast metadata
    void SetBplastUpFired(bool b) { fUpFired = b; }
    void SetBplastDownFired(bool b) { fDownFired = b; }

    uint64_t GetEventno() const { return fEventno; }
    Int_t GetTrigger() const { return fTrigger; }
    uint64_t GetTimeStamp() const { return fTimeStamp; }
    inline bool GetSpillFlag() { return fSpillFlag; }

    // bplast metadata
    bool GetBplastUpFired() { return fUpFired; }
    bool GetBplastDownFired() { return fDownFired; }

    static void SetRegister(bool option) { fPersistance = option; }
    virtual void Register(Bool_t Persistance) override;

  private:
    uint64_t fEventno;
    Int_t fTrigger;
    uint64_t fTimeStamp;
    bool fSpillFlag;
    static bool fPersistance;

    // bplast metadata
    bool fUpFired;
    bool fDownFired;

  public:
    ClassDefOverride(EventHeader, 1)
};


#endif /* EventHeader_H */
