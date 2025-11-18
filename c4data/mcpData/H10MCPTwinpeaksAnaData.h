#ifndef H10MCPTwinpeaksAnaData_H
#define H10MCPTwinpeaksAnaData_H

#include "TObject.h"

class H10MCPTwinpeaksAnaData : public TObject
{
    public:
        // Default Constructor
        H10MCPTwinpeaksAnaData();

        H10MCPTwinpeaksAnaData(Long64_t abs_time, // white rabbit + relative board time
                            Long64_t wr, // white rabbit
                            Bool_t full, // All 10 informations
                            Bool_t mcp1, // All MCP 1 informations
                            Bool_t mcp2, // All MCP 2 informations
                            Double_t e1, // E MCP 1
                            Double_t e_x11, // E MCP1 from X11 channel
                            Double_t e_x12,
                            Double_t e_y11,
                            Double_t e_y12,
                            Double_t t1, // T MCP 1
                            Double_t x11, // X1 MCP 1
                            Double_t x12, // X2 MCP 1
                            Double_t y11, // Y1 MCP 1
                            Double_t y12, // Y2 MCP 1
                            Double_t e2, // E MCP 2
                            Double_t e_x21, // E MCP2 from X21 channel
                            Double_t e_x22,
                            Double_t e_y21,
                            Double_t e_y22,
                            Double_t t2, // T MCP 2
                            Double_t x21, // X1 MCP 2
                            Double_t x22, // X2 MCP 2
                            Double_t y21, // Y1 MCP 2
                            Double_t y22); // Y2 MCP 2
            

        // Destructor
        virtual ~H10MCPTwinpeaksAnaData() {}

        Long64_t absolute_event_time;
        Long64_t wr_t;
        Bool_t full_event;
        Bool_t mcp1_complete;
        Bool_t mcp2_complete;
        Double_t E1;
        Double_t E_X11;
        Double_t E_X12;
        Double_t E_Y11;
        Double_t E_Y12;
        Double_t T1;
        Double_t X11;
        Double_t X12;
        Double_t Y11;
        Double_t Y12;
        Double_t E2;
        Double_t E_X21;
        Double_t E_X22;
        Double_t E_Y21;
        Double_t E_Y22;
        Double_t T2;
        Double_t X21;
        Double_t X22;
        Double_t Y21;
        Double_t Y22;
       
        ClassDef(H10MCPTwinpeaksAnaData, 1);
};

#endif
