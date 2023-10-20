#ifndef FrsData_H
#define FrsData_H
#include "TObject.h"

class FrsData : public TObject
{
    public:
        // Default Constructor
        FrsData();

        FrsData(UInt_t time, UInt_t trig, UInt_t data);

        // Destructor
        virtual ~FrsData() {}

        // Getters
        inline const UInt_t GetTdcData() const { return tdcData; }
        inline const int GetChan() const { return channel; }
        inline const int GetLot() const { return leadOrTrail; }

        inline const UInt_t GetTpatTs() const { return tpat_ts; }
        inline const UInt_t GetTpatTrig() const { return tpat_trig; }
        inline const UInt_t GetTpatData() const { return tpat_data; }


        // Setters
        void SetTdcData(UInt_t v) { tdcData = v; }
        void SetChan(int v) { channel = v; }
        void SetLot(int v) { leadOrTrail = v; }


        void SetTpatTs(UInt_t v) { tpat_ts = v; }
        void SetTpatTrig(UInt_t v) { tpat_trig = v; }
        void SetTpatData(UInt_t v) { tpat_data = v; }


    protected:

        // tpat
        UInt_t tpat_ts; // combine lo+hi
        UInt_t tpat_trig;
        UInt_t tpat_data; 


        UInt_t tdcData;
        int channel, leadOrTrail;



    public:
        ClassDef(FrsData, 1)
};


class FrsUnpackTpatItem : public TObject
{
    public:
        FrsUnpackTpatItem();

        FrsUnpackTpatItem(uint64_t time, UInt_t trig, UInt_t value);

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

/*class FrsUnpackFrsItem : public TObject
{
    public:
        FrsUnpackFrsItem();
        FrsUnpackFrsItem(UInt_t g, UInt_t c, UInt_t v);

        virtual ~FrsUnpackFrsItem() {};

        // GET

        // SET
        void SetAll(UInt_t i, UInt_t v830, UInt_t g, UInt_t c, UInt_t v7x5);
    
    protected:
        // items
        UInt_t i;
        UInt_t v830;
        UInt_t geo, channel;
        UInt_t v7x5;

    
    public:
        ClassDef(FrsUnpackFrsItem, 1)
};*/

class FrsUnpackV830 : public TObject
{
    public:
        FrsUnpackV830();
        virtual ~FrsUnpackV830() {};

        void SetAll(UInt_t i, UInt_t d);
    
    protected:
        UInt_t index;
        UInt_t v830_data;
    
    public:
        ClassDef(FrsUnpackV830, 1)
};

class FrsUnpackV7X5 : public TObject
{
    public:
        FrsUnpackV7X5();
        virtual ~FrsUnpackV7X5() {};

        void SetAll(UInt_t g, UInt_t c, UInt_t d);

    protected:
        UInt_t geo;
        UInt_t channel;
        UInt_t v7x5_data;
    
    public:
        ClassDef(FrsUnpackV7X5, 1)
};


#endif
