#ifndef bPlastTamexData_H
#define bPlastTamexData_H 1

#include "TObject.h"

class bPlastTamexData : public TObject
{
    public:
        bPlastTamexData();

        bPlastTamexData(UInt_t detNum,
                        UInt_t chanNum,
                        UInt_t PMT_Lead);
        
        virtual ~bPlastTamexData() {};

        // Getters
        inline const UInt_t GetDet() const { return fDet; }
        inline const UInt_t GetChan() const { return fChan; }
        inline const UInt_t GetPMT_Lead() const { return fPMT_Lead; }

        
        // Setters
        void SetDet(UInt_t v) { fDet = v; }
        void SetChan(UInt_t v) { fChan = v; }
        void SetPMT_Lead(UInt_t v) { fPMT_Lead = v;}

    protected:
        // stuff
        UInt_t fDet;
        UInt_t fChan;
        UInt_t fPMT_Lead;

    public:
        ClassDef(bPlastTamexData, 1);
};

#endif