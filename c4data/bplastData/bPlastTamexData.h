#ifndef bPlastTamexData_H
#define bPlastTamexData_H 1

#include "TObject.h"

class bPlastTamexData : public TObject
{
    public:
        bPlastTamexData();

        bPlastTamexData(UInt_t fbPlastLeadTime,
                        UInt_t fbPlastTrailTime,
                        UInt_t fbPlastToT,
                        UInt_t fbPlastChannel,
                        UInt_t fbPlastEpoch,
                        UInt_t fbPlastSubSysID,
                        UInt_t fbPlastWrT
                        );
        
        // Destructor

        virtual ~bPlastTamexData() {};

        // Getters
        inline const UInt_t GetLeadTime() const {return fbPlastLeadTime;}
        inline const UInt_t GetTrailTime() const {return fbPlastTrailTime;}
        inline const UInt_t GetToT() const {return fbPlastToT;}
        inline const UInt_t GetChannel() const {return fbPlastChannel;}
        inline const UInt_t GetEpoch() const {return fbPlastEpoch;}
        inline const UInt_t GetSubSysID() const {return fbPlastSubSysID;}
        inline const UInt_t GetWrT() const {return fbPlastWrT;}

        
        // Setters
        void SetLeadTime(UInt_t v) {fbPlastLeadTime = v;}
        void SetTrailTime(UInt_t v) {fbPlastTrailTime = v;}
        void SetToT(UInt_t v) {fbPlastToT = v;}
        void SetChannel(UInt_t v) {fbPlastChannel = v;}
        void SetEpoch(UInt_t v) {fbPlastEpoch = v;}
        void SetSubSysID(UInt_t v) {fbPlastSubSysID = v;}
        void SetWrT(UInt_t v) {fbPlastWrT = v;}


    protected:
        // stuff
        UInt_t fbPlastLeadTime;
        UInt_t fbPlastTrailTime;
        UInt_t fbPlastToT;
        UInt_t fbPlastChannel;
        UInt_t fbPlastEpoch;
        UInt_t fbPlastSubSysID;
        UInt_t fbPlastWrT;
        

    public:
        ClassDef(bPlastTamexData, 1);
};

#endif