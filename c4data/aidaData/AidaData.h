#ifndef AidaData_H
#define AidaData_H

#include "TObject.h"

class AidaUnpackAdcItem : public TObject
{
public:
    AidaUnpackAdcItem();

    void Reset();
    void SetAll(uint64_t rt, uint64_t st, uint64_t ft, int f, int c, bool r, uint16_t v);
    uint64_t RawTime() const;
    uint64_t SlowTime() const;
    uint64_t FastTime() const;
    int Fee() const;
    int Channel() const;
    bool Range() const;
    uint16_t Value() const;

    ClassDefNV(AidaUnpackAdcItem, 2)
private:

    uint64_t rawTime;
    uint64_t slowTime;
    uint64_t fastTime;
    int fee;
    int channel;
    bool range;
    uint16_t value;
};

class AidaUnpackScalerItem : public TObject
{
public:
    AidaUnpackScalerItem();

    void Reset();
    void SetAll(uint64_t time, uint64_t value, int fee);
    uint64_t Time() const;
    int Fee() const;
    uint64_t Value() const;

    ClassDefNV(AidaUnpackScalerItem, 2)
private:
    uint64_t time;
    uint64_t value;
    int fee;
};

class AidaUnpackFlowItem : public TObject
{
public:
    AidaUnpackFlowItem();

    void Reset();
    void SetAll(uint64_t time, int fee, bool pause);
    uint64_t Time() const;
    int Fee() const;
    bool Paused() const;

    ClassDefNV(AidaUnpackFlowItem, 2)
private:
    uint64_t time;
    int fee;
    bool pause;
};

inline uint64_t AidaUnpackAdcItem::RawTime() const
{
    return rawTime;
}

inline uint64_t AidaUnpackAdcItem::SlowTime() const
{
    return slowTime;
}

inline uint64_t AidaUnpackAdcItem::FastTime() const
{
    return fastTime;
}

inline int AidaUnpackAdcItem::Fee() const
{
    return fee;
}

inline int AidaUnpackAdcItem::Channel() const
{
    return channel;
}

inline bool AidaUnpackAdcItem::Range() const
{
    return range;
}

inline uint16_t AidaUnpackAdcItem::Value() const
{
    return value;
}

inline uint64_t AidaUnpackScalerItem::Time() const
{
    return time;
}

inline int AidaUnpackScalerItem::Fee() const
{
    return fee;
}

inline uint64_t AidaUnpackScalerItem::Value() const
{
    return value;
}

inline uint64_t AidaUnpackFlowItem::Time() const
{
    return time;
}

inline int AidaUnpackFlowItem::Fee() const
{
    return fee;
}

inline bool AidaUnpackFlowItem::Paused() const
{
    return pause;
}



#endif /* AidaData_H */
