#ifndef bPlastTamexData_H
#define bPlastTamexData_H 1

#include "TObject.h"

class bPlastTamexData : public TObject
{
    public:
        bPlastTamexData();

        bPlastTamexData(UInt_t detNum,
                        UInt_t chanNum,
                        UInt_t bPlastLeadT,
                        UInt_t bPlastTrailT,
                        UInt_t bPlastEpoch); // might not be needed, but diagnostic for now
        
        virtual ~bPlastTamexData() {};

        // Getters
        inline const UInt_t GetDet() const { return fDet; }
        inline const UInt_t GetChan() const { return fChan; }
        inline const UInt_t GetbPlastLeadT() const { return fbPlastLeadT; }
        inline const UInt_t GetbPlastTrailT() const { return fbPlastTrailT; }
        inline const UInt_t GetbPlastEpoch() const { return fbPlastEpoch; } // this might not be needed, but diagnostic for now

        
        // Setters
        void SetDet(UInt_t v) { fDet = v; }
        void SetChan(UInt_t v) { fChan = v; }
        void SetbPlastLeadT(UInt_t v) { fbPlastLeadT = v;}
        void SetbPlastTrailT(UInt_t v) { fbPlastTrailT = v;}
        void SetbPlastEpoch(UInt_t v) { fbPlastEpoch = v;} // this might not be needed, but diagnostic for now

    protected:
        // stuff
        UInt_t fDet;
        UInt_t fChan;
        UInt_t fbPlastLeadT;
        UInt_t fbPlastTrailT;
        UInt_t fbPlastEpoch; // this might not be needed, but diagnostic for now

    public:
        ClassDef(bPlastTamexData, 1);
};

#endif