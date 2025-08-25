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
 *                              C.E. Jones                                    *
 *                               06.05.25                                     *
 ******************************************************************************/

#include "H10MCPTwinpeaksAnaData.h"

H10MCPTwinpeaksAnaData::H10MCPTwinpeaksAnaData()
{
    absolute_event_time = 0;
    wr_t = 0;
    full_event = 0;
    mcp1_complete = 0;
    mcp2_complete = 0;
    T1 = 0;
    X11 = 0;
    X12 = 0;
    Y11 = 0;
    Y12 = 0;
    T2 = 0;
    X21 = 0;
    X22 = 0;
    Y21 = 0;
    Y22 = 0;
    SC41 = 0;
    SC42 = 0;
    DSSDAccept = 0;
}

H10MCPTwinpeaksAnaData::H10MCPTwinpeaksAnaData(Long64_t abs_time,
                                            Long64_t wr,
                                            Bool_t full,
                                            Bool_t mcp1,
                                            Bool_t mcp2,
                                            Double_t t1,
                                            Double_t x11,
                                            Double_t x12,
                                            Double_t y11,
                                            Double_t y12,
                                            Double_t t2,
                                            Double_t x21,
                                            Double_t x22,
                                            Double_t y21,
                                            Double_t y22,
                                            Double_t sc41,
                                            Double_t sc42,
                                            Double_t dssdaccept)
{
    absolute_event_time = abs_time;
    wr_t = wr;
    full_event = full;
    mcp1_complete = mcp1;
    mcp2_complete = mcp2;
    T1 = t1;
    X11 = x11;
    X12 = x12;
    Y11 = y11;
    Y12 = y12;
    T2 = t2;
    X21 = x21;
    X22 = x22;
    Y21 = y21;
    Y22 = y22;
    SC41 = sc41;
    SC42 = sc42;
    DSSDAccept = dssdaccept;
}

ClassImp(H10MCPTwinpeaksAnaData)