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
 *                             C.E. Jones                                     *
 *                              06.05.25                                      *
 ******************************************************************************/

#include "FrsData.h"
#include <iostream>

FrsTpatItem::FrsTpatItem() {}

void FrsTpatItem::SetAll(Long64_t wr, Short_t tp, Long64_t tmwr)
{
    wr_t = wr;
    tpat = tp;
    travmus_wr_t = tmwr;
}

void FrsTpatItem::Reset()
{
    wr_t = 0;
    tpat = 0;
    travmus_wr_t = 0;
}

ClassImp(FrsTpatItem)


FrsScalerItem::FrsScalerItem() {}

void FrsScalerItem::SetAll(Int_t i, UInt_t sc)
{   
    index = i;
    scaler = sc;
}

void FrsScalerItem::Reset()
{
    index = -1;
    scaler = 0;
}

ClassImp(FrsScalerItem)


FrsSciItem::FrsSciItem() {}

void FrsSciItem::SetAll(UInt_t de[32], UInt_t dt[32], std::vector<Int_t> mhtdc[32])
{
    for (int i = 0; i < 32; i++) sciDE[i] = de[i];
    for (int i = 0; i < 32; i++) sciDT[i] = dt[i];
    for (int i = 0; i < 32; i++) sciMHTDC[i] = mhtdc[i];

}

ClassImp(FrsSciItem)

FrsMusicItem::FrsMusicItem() {}

void FrsMusicItem::SetAll(uint32_t e[5][8], uint32_t t[5][8])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++) musicE[i][j] = e[i][j];
        for (int j = 0; j < 8; j++) musicT[i][j] = t[i][j];
    }
}

ClassImp(FrsMusicItem)


FrsTpcItem::FrsTpcItem() {}

void FrsTpcItem::SetAll(UInt_t adc[7][8], std::vector<UInt_t> tdc[128])
{
    for (int i = 0; i < 7; i++) for (int j = 0; j < 8; j++) adcData[i][j] = adc[i][j];
    for (int i = 0; i < 128; i++) tdcData[i] = tdc[i];
}

ClassImp(FrsTpcItem)