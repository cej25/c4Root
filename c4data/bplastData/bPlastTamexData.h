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
        void SetLeadTime(UInt_t fbPlastLeadTime) {this->fbPlastLeadTime = fbPlastLeadTime;}
        void SetTrailTime(UInt_t fbPlastTrailTime) {this->fbPlastTrailTime = fbPlastTrailTime;}
        void SetToT(UInt_t fbPlastToT) {this->fbPlastToT = fbPlastToT;}
        void SetChannel(UInt_t fbPlastChannel) {this->fbPlastChannel = fbPlastChannel;}
        void SetEpoch(UInt_t fbPlastEpoch) {this->fbPlastEpoch = fbPlastEpoch;}
        void SetSubSysID(UInt_t fbPlastSubSysID) {this->fbPlastSubSysID = fbPlastSubSysID;}
        void SetWrT(UInt_t fbPlastWrT) {this->fbPlastWrT = fbPlastWrT;}

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