/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

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
    , fOnline(kFALSE)
{
    exp_config = TExperimentConfiguration::GetInstance();
}

UnpackReader::~UnpackReader()
{
    c4LOG(debug2, "");
    if (fHeader)
    {
        delete fHeader;
    }
}

Bool_t UnpackReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

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
   
    c4LOG(info, "Success (this step is vital)!");

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
        c4LOG(debug2, "event : " << fNEvent << ", trigger : " << fData->TRIGGER);
    }

    if (fHeader)
    {
        fHeader->SetTrigger(fData->TRIGGER);
        fHeader->SetEventno(fData->EVENTNO); //We seemingly skip eventnos - is this due to timestichting?
        if (fData->TRIGGER == exp_config->bos_trig) spill_flag = true;
        if (fData->TRIGGER == exp_config->eos_trig) spill_flag = false;
        fHeader->SetSpillFlag(spill_flag);
        fNEvent++;
    }

    return kTRUE;
}

void UnpackReader::Reset() {}

ClassImp(UnpackReader);
