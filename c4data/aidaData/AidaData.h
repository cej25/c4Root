#ifndef AidaData_H
#define AidaData_H

#include "TObject.h"

class AidaUnpackAdcItem : public TObject
{
    public:
        AidaUnpackAdcItem();

        void Reset();
        void SetAll(ULong64_t rt, ULong64_t st, ULong64_t ft, Int_t f, Int_t c, Bool_t r, UShort_t v);
        
        ULong64_t RawTime() const { return rawTime; }
        ULong64_t SlowTime() const { return slowTime; }
        ULong64_t FastTime() const { return fastTime; }
        Int_t Fee() const { return fee; }
        Int_t Channel() const { return channel; }
        Bool_t Range() const { return range; }
        UShort_t Value() const { return value; }

        ClassDefNV(AidaUnpackAdcItem, 2)
    
    private:

        ULong64_t rawTime;
        ULong64_t slowTime;
        ULong64_t fastTime;
        Int_t fee;
        Int_t channel;
        Bool_t range;
        UShort_t value;
};

class AidaUnpackScalerItem : public TObject
{
    public:
        AidaUnpackScalerItem();

        void Reset();
        void SetAll(ULong64_t time, ULong64_t value, Int_t fee);
        ULong64_t Time() const { return time; }
        Int_t Fee() const { return fee; }
        ULong64_t Value() const { return value; }

        ClassDefNV(AidaUnpackScalerItem, 2)
    
    private:
        ULong64_t time;
        Int_t fee;
        ULong64_t value;
};

class AidaUnpackFlowItem : public TObject
{
    public:
        AidaUnpackFlowItem();

        void Reset();
        void SetAll(ULong64_t time, Int_t fee, Bool_t pause);
        ULong64_t Time() const { return time; }
        Int_t Fee() const { return fee; }
        Bool_t Paused() const { return pause; }

        ClassDefNV(AidaUnpackFlowItem, 2)

    private:
        ULong64_t time;
        Int_t fee;
        Bool_t pause;
};

#endif /* AidaData_H */
