#ifndef FrsData_H
#define FrsData_H
#include "TObject.h"

struct V1290_item
{
    public:
       // void SetAll(/*stuff*/);
    
    public:
        // items
        UInt_t channel;
        UInt_t leadOrTrail;
        UInt_t data;
};

struct V830_item
{
    public:
        void SetAll(UInt_t i, UInt_t d);
    
    public:
        UInt_t index;
        UInt_t data;
};

struct V792_item
{
    public:
        UInt_t data;
};

struct V7X5_item
{
    public:
        void SetAll(UInt_t g, UInt_t c, UInt_t d);

    public:
        UInt_t geo;
        UInt_t channel;
        UInt_t data;
};

class FrsUnpackMainItem : public TObject
{
    public:
        FrsUnpackMainItem();
        virtual ~FrsUnpackMainItem() {};
    
        void SetAll(std::vector<V1290_item>& v1290, std::vector<V830_item>& v830, std::vector<V792_item>& v792);
    
    protected:
        std::vector<V1290_item> v1290Array;
        std::vector<V830_item> v830Array;
        std::vector<V792_item> v792Array;
    
    public:
        ClassDef(FrsUnpackMainItem, 1)

};


class FrsUnpackTpatItem : public TObject
{
    public:
        FrsUnpackTpatItem();
        virtual ~FrsUnpackTpatItem() {};

        inline const uint64_t GetTpatTs() const { return ts_long; }
        inline const UInt_t GetTpatTrig() const { return trigger; }
        inline const UInt_t GetTpatData() const { return data; }

        void SetTpatTs(uint64_t v) { ts_long = v; }
        void SetTpatTrig(UInt_t v) { trigger = v; }
        void SetTpatData(UInt_t v) { data = v; }
        void SetAll(uint64_t time, UInt_t trig, UInt_t value);


    protected:
        uint64_t ts_long;
        UInt_t trigger;
        UInt_t data;

    public:
        ClassDef(FrsUnpackTpatItem, 1)
};


class FrsUnpackFrsItem : public TObject
{
    public:
        FrsUnpackFrsItem();
        virtual ~FrsUnpackFrsItem() {};

        // GET

        // SET
        void SetAll(std::vector<V830_item>& v830, std::vector<V7X5_item>& v7x5);
    
    protected:
        // items
        std::vector<V830_item> v830Array;
        std::vector<V7X5_item> v7x5Array;

    
    public:
        ClassDef(FrsUnpackFrsItem, 1)
};



#endif
