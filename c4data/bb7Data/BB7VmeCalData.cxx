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

#include "BB7VmeCalData.h"

BB7VmeImplantItem::BB7VmeImplantItem()
{

}

void BB7VmeImplantItem::SetAll(Long64_t wr, Int_t det, Int_t si, Int_t st, UInt_t adc)
{
    wr_t = wr;
    detector = det;
    side = si;
    strip = st;
    raw_adc = adc;
}

void BB7VmeImplantItem::Reset()
{
    wr_t = 0;
    detector = 0;
    side = 0;
    strip = 0;
    raw_adc = 0;
}

ClassImp(BB7VmeImplantItem)


BB7VmeDecayItem::BB7VmeDecayItem()
{

}

void BB7VmeDecayItem::SetAll(Long64_t wr, Int_t det, Int_t si, Int_t st, UInt_t adc)
{
    wr_t = wr;
    detector = det;
    side = si;
    strip = st;
    raw_adc = adc;
}

void BB7VmeDecayItem::Reset()
{
    wr_t = 0;
    detector = 0;
    side = 0;
    strip = 0;
    raw_adc = 0;
}

BB7VmeResidualItem::BB7VmeResidualItem()
{

}

void BB7VmeResidualItem::SetAll(UInt_t left, UInt_t right, UInt_t del, UInt_t un)
{
    sc41l = left;
    sc41r = right;
    tm_delayed = del;
    tm_undelayed = un;
}

void BB7VmeResidualItem::Reset()
{
    sc41l = 0;
    sc41r = 0;
    tm_delayed = 0;
    tm_undelayed = 0;
}

ClassImp(BB7VmeResidualItem)
