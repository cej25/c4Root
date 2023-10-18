#include "bPlastTamexData.h"

bPlastTamexData::bPlastTamexData()
    :   fbPlastLeadTime(0),
        fbPlastTrailTime(0),
        fbPlastToT(0),
        fbPlastChannel(0),
        fbPlastEpoch(0),
        fbPlastSubSysID(0),
        fbPlastWrT(0)      
{
}

/* there are some pre-trigger times, but I will probably not save these as they are only used to calculate the time difference between events */
bPlastTamexData::bPlastTamexData(
    UInt_t bPlastLeadTime,
    UInt_t bPlastTrailTime,
    UInt_t bPlastToT,
    UInt_t bPlastChannel,
    UInt_t bPlastEpoch,
    UInt_t bPlastSubSysID,
    UInt_t bPlastWrT
    )

    :  fbPlastLeadTime(bPlastLeadTime),
       fbPlastTrailTime(bPlastTrailTime),
       fbPlastToT(bPlastToT),
       fbPlastChannel(bPlastChannel),
       fbPlastEpoch(bPlastEpoch),
       fbPlastSubSysID(bPlastSubSysID),
       fbPlastWrT(bPlastWrT)

{
}

ClassImp(bPlastTamexData)