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

#include "FatimaVmeCalData.h"


FatimaVmeQDCCalItem::FatimaVmeQDCCalItem()
{

}

void FatimaVmeQDCCalItem::SetAll(uint64_t wr, int det, double ct, double ft, int fb, double ql, uint32_t qlr, uint32_t qsr)
{
    wr_t = wr;
    coarse_time = ct;
    fine_time = ft;
    fine_bin = fb;
    qlong = ql;
    qlong_raw = qlr;
    qshort_raw = qsr;
    detector = det;
}

void FatimaVmeQDCCalItem::Reset()
{
    wr_t = 0;
    coarse_time = 0;
    fine_time = 0;
    fine_bin = 0;
    qlong = 0;
    qlong_raw = 0;
    qshort_raw = 0;
    detector = 0;
}

ClassImp(FatimaVmeQDCCalItem)

FatimaVmeTDCCalItem::FatimaVmeTDCCalItem()
{

}

void FatimaVmeTDCCalItem::SetAll(uint64_t wr, int det, double ts, uint32_t ts_raw)
{
    wr_t = wr;
    timestamp = ts;
    timestamp_raw = ts_raw;
    detector = det;
}

void FatimaVmeTDCCalItem::Reset()
{
    wr_t = 0;
    timestamp = 0;
    timestamp_raw = 0;
    detector = 0;
}

ClassImp(FatimaVmeTDCCalItem)

FatimaVmeResiduals::FatimaVmeResiduals()
{

}

void FatimaVmeResiduals::SetAll(double left, double right, double tmu, double tmd)
{
    sc41l = left;
    sc41r = right;
    tm_delayed = tmd;
    tm_undelayed = tmu;
}

void FatimaVmeResiduals::Reset()
{
    sc41l = 0;
    sc41r = 0;
    tm_delayed = 0;
    tm_undelayed = 0;
}


ClassImp(FatimaVmeResiduals)