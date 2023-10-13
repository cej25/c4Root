#include "FairRootManager.h"
#include "c4Logger.h"

#include "EventHeader.h"
#include "UnpackReader.h"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_unpack.h"
}
#include <iostream>

UnpackReader::UnpackReader(EXT_STR_h101_unpack* data, size_t offset)
    : c4Reader("UnpackReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fHeader(NULL)
{}

UnpackReader::~UnpackReader()
{
    c4LOG(debug1, "");
    if (fHeader)
    {
        delete fHeader;
    }
}

Bool_t UnpackReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");
    EXT_STR_h101_unpack_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_unpack, 0);
    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information.");
        return kFALSE;
    }

    // Look for the EventHeader
    auto frm = FairRootManager::Instance();
    fHeader = dynamic_cast<EventHeader*>(frm->GetObject("EventHeader."));
    if (!fHeader)
    {
        c4LOG(warn, "EventHeader. not found");
    }
    else
        c4LOG(info, "EventHeader. found");

    return kTRUE;
}

Bool_t UnpackReader::Read()
{
    /* Display data */
    //	LOG(info) << "  Event data:";
    //  char strMessage[1000];
    //	sprintf(strMessage, "  %10d (d%10d): %2d\n",
    //		fData->EVENTNO,
    //		fData->EVENTNO - fNEvent,
    //		fData->TRIGGER);
    //  LOG(info) << strMessage;

    // fNEvent = fData->EVENTNO;

    if (0 == (fNEvent % 1000))
    {
        c4LOG(debug1, "event : " << fNEvent << ", trigger : " << fData->TRIGGER);
    }

    if (fHeader)
    {
        fHeader->SetTrigger(fData->TRIGGER);
        //fHeader->SetEventno(fNEvent++);
        fNEvent++;
        fHeader->SetEventno(fData->EVENTNO);
    }

    return kTRUE;
}

void UnpackReader::Reset() {}

ClassImp(UnpackReader);
