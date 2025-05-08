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
 *                              N.J. Hubbard                                  *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "AidaData.h"

AidaUnpackAdcItem::AidaUnpackAdcItem()
{
}

void AidaUnpackAdcItem::Reset()
{
    rawTime = slowTime = fastTime = 0;
    fee = channel = 0;
    range = false;
    value = 0;
}

void AidaUnpackAdcItem::SetAll(ULong64_t rt, ULong64_t st, ULong64_t ft, Int_t f, Int_t c, Bool_t r, UShort_t v)
{
    rawTime = rt;
    slowTime = st;
    fastTime = ft;
    fee = f;
    channel = c;
    range = r;
    value = v;
}

AidaUnpackScalerItem::AidaUnpackScalerItem()
{
}

void AidaUnpackScalerItem::Reset()
{
    time = value = 0;
    fee = 0;
}

void AidaUnpackScalerItem::SetAll(ULong64_t t, ULong64_t v, Int_t f)
{
    time = t;
    value = v;
    fee = f;
}

AidaUnpackFlowItem::AidaUnpackFlowItem()
{
}

void AidaUnpackFlowItem::Reset()
{
    time = 0;
    fee = 0;
    pause = false;
}

void AidaUnpackFlowItem::SetAll(ULong64_t t, Int_t f, Bool_t p)
{
    time = t;
    fee = f;
    pause = p;
}

ClassImp(AidaUnpackAdcItem)
ClassImp(AidaUnpackScalerItem)
ClassImp(AidaUnpackFlowItem)

