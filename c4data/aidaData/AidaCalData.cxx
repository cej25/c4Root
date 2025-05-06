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

#include "AidaCalData.h"

AidaCalAdcItem::AidaCalAdcItem()
{
}

void AidaCalAdcItem::Reset()
{
    slowTime = fastTime = 0;
    dssd = side = strip = 0;
    range = false;
    intensity = energy = 0.;
}

void AidaCalAdcItem::SetAll(ULong64_t st, ULong64_t ft, Int_t f, Int_t c, Int_t d, Int_t si, Int_t str, Bool_t r, Double_t i, Double_t e)
{
    slowTime = st;
    fastTime = ft;
    fee = f;
    channel = c;
    dssd = d;
    side = si;
    strip = str;
    range = r;
    intensity = i;
    energy = e;
}

ClassImp(AidaCalAdcItem)
