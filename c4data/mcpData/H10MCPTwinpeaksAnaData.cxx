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
                                            Double_t y22)
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
}

ClassImp(H10MCPTwinpeaksAnaData)