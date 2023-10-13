#include "bPlastTamexData.h"

bPlastTamexData::bPlastTamexData()
    :   fbPlastLeadTime(0),
        fbPlastTrailTime(0),
        fbPlastToT(0);
        fbPlastChannel(0),
        fbPlastEpoch(0),
        fbPlastSubSysID(0),
        fbPlastWrT(0)      
{
}

/* there are some pre-trigger times, but I will probably not save these as they are only used to calculate the time difference between events */
bPlastTamexData::bPlastTamexData(
    UInt_t fbPlastLeadTime,
    UInt_t fbPlastTrailTime,
    UInt_t fbPlastToT,
    UInt_t fbPlastChannel,
    UInt_t fbPlastEpoch,
    UInt_t fbPlastSubSysID,
    UInt_t fbPlastWrT
    )

    :  fbPlastLeadTime(fbPlastLeadTime),
       fbPlastTrailTime(fbPlastTrailTime),
       fbPlastToT(fbPlastToT),
       fbPlastChannel(fbPlastChannel),
       fbPlastEpoch(fbPlastEpoch),
       fbPlastSubSysID(fbPlastSubSysID),
       fbPlastWrT(fbPlastWrT)

{
}

ClassImp(bPlastTamexData)