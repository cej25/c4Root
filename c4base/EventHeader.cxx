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

#include "EventHeader.h"
#include "FairRootManager.h"

Bool_t EventHeader::fPersistance = true;

EventHeader::EventHeader()
    : FairEventHeader()
    , fEventno(0)
    , fTrigger(0)
    , fTimeStamp(0)
{
}

EventHeader::EventHeader(uint64_t Eventno, Int_t Trigger, uint64_t TimeStamp)
    : FairEventHeader()
    , fEventno(Eventno)
    , fTrigger(Trigger)
    , fTimeStamp(TimeStamp)
{
}

EventHeader::~EventHeader() {}

void EventHeader::Register(Bool_t Persistance)
{
    FairRootManager::Instance()->Register("EventHeader.", "EvtHeader", this, Persistance);
}

ClassImp(EventHeader);
