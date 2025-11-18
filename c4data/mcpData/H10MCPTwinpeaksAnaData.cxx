#include "H10MCPTwinpeaksAnaData.h"

H10MCPTwinpeaksAnaData::H10MCPTwinpeaksAnaData()
{
    absolute_event_time = 0;
    wr_t = 0;
    full_event = 0;
    mcp1_complete = 0;
    mcp2_complete = 0;
    E1 = 0;
    E_X11 = 0;
    E_X12 = 0;
    E_Y11 = 0;
    E_Y12 = 0;
    T1 = 0;
    X11 = 0;
    X12 = 0;
    Y11 = 0;
    Y12 = 0;
    E2 = 0;
    E_X21 = 0;
    E_X22 = 0;
    E_Y21 = 0;
    E_Y22 = 0;
    T2 = 0;
    X21 = 0;
    X22 = 0;
    Y21 = 0;
    Y22 = 0;
}

H10MCPTwinpeaksAnaData::H10MCPTwinpeaksAnaData(Long64_t abs_time,
                                            Long64_t wr,
                                            Bool_t full,
                                            Bool_t mcp1,
                                            Bool_t mcp2,
                                            Double_t e1,
                                            Double_t e_x11,
                                            Double_t e_x12,
                                            Double_t e_y11,
                                            Double_t e_y12,
                                            Double_t t1,
                                            Double_t x11,
                                            Double_t x12,
                                            Double_t y11,
                                            Double_t y12,
                                            Double_t e2,
                                            Double_t e_x21,
                                            Double_t e_x22,
                                            Double_t e_y21,
                                            Double_t e_y22,
                                            Double_t t2,
                                            Double_t x21,
                                            Double_t x22,
                                            Double_t y21,
                                            Double_t y22)
{
    absolute_event_time = abs_time;
    wr_t = wr;
    full_event = full;
    mcp1_complete = mcp1;
    mcp2_complete = mcp2;
    E1 = e1;
    E_X11 = e_x11;
    E_X12 = e_x12;
    E_Y11 = e_y11;
    E_Y12 = e_y12;
    T1 = t1;
    X11 = x11;
    X12 = x12;
    Y11 = y11;
    Y12 = y12;
    E2 = e2;
    E_X21 = e_x21;
    E_X22 = e_x22;
    E_Y21 = e_y21;
    E_Y22 = e_y22;
    T2 = t2;
    X21 = x21;
    X22 = x22;
    Y21 = y21;
    Y22 = y22;
}

ClassImp(H10MCPTwinpeaksAnaData)