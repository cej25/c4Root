#ifndef FrsData_H
#define FrsData_H
#include "TObject.h"

class FrsData : public TObject
{
    public:
        // Default Constructor
        FrsData();

        FrsData(UInt_t tdc, int chan, int lot);

        // Destructor
        virtual ~FrsData() {}

        // Getters
        inline const UInt_t GetTdcData() const { return tdcData; }
        inline const int GetChan() const { return channel; }
        inline const int GetLot() const { return leadOrTrail; }
       
        // Setters
        void SetTdcData(UInt_t v) { tdcData = v; }
        void SetChan(int v) { channel = v; }
        void SetLot(int v) { leadOrTrail = v; }



    protected:
        UInt_t tdcData;
        int channel, leadOrTrail;



    public:
        ClassDef(FrsData, 1)
};

#endif
