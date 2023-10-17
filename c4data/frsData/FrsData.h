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


#endif
