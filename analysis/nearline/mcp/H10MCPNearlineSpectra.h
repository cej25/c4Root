#ifndef H10MCPNearlineSpectra_H
#define H10MCPNearlineSpectra_H

#include "FairTask.h"
#include "TDirectory.h"
#include "TH10MCPConfiguration.h"
#include "H10MCPTwinpeaksAnaData.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>
#include "TBox.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1;
class TH1F;
class TH2F;
class TDirectory;
class TFolder;

class H10MCPNearlineSpectra : public FairTask
{
    public:
        H10MCPNearlineSpectra();
        H10MCPNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~H10MCPNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

    
    private:
        const TH10MCPConfiguration* mcp_config;

        TClonesArray* fHitsMCP;


        // ranges
        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;
        
        std::vector<int> detectors = {0,1,2};
        int number_detectors = 3;

        std::vector<int> dt_reference_detectors = {};
        std::vector<std::pair<double,double>> dt_reference_detectors_energy_gates = {};
        int number_reference_detectors = 0;
        
        // Directory
        TDirectory* dir_mcp;
        // Variable
        double T1 = 0;
        double E1 = 0;
        double X11 = 0;
        double X12 = 0;
        double Y11 = 0;
        double Y12 = 0;
        double T2 = 0;
        double E2 = 0;
        double X21 = 0;
        double X22 = 0;
        double Y21 = 0;
        double Y22 = 0;

        // Histograms 
        TH1* h1_dT;
        TH2* h2_dX1_dT;
        TH2* h2_dY1_dT;
        TH2* h2_dX2_dT;
        TH2* h2_dY2_dT;

        TH1* h1_dX1;
        TH1* h1_dY1;
        TH1* h1_dX2;
        TH1* h1_dY2;

        TH1* h1_E1;
        TH1* h1_E2;

        TH2* h2_MCP1_HeatMap;
        TH2* h2_MCP2_HeatMap;

        TH2* h2_E1_dT;
        TH2* h2_E2_dT;

        // Gated histogram
        TH1* h1_dT_Pos1Gate;
        TH1* h1_dT_Pos2Gate;

        TH1* h1_E1_Pos1Gate;
        TH1* h1_E2_Pos1Gate;
        TH1* h1_E2_Pos2Gate;

        TH2* h2_MCP1_HeatMap_Pos2Gate;
        TH2* h2_MCP2_HeatMap_Pos1Gate;

        TH2* h2_E1_dT_Pos1Gate;
        TH2* h2_E2_dT_Pos2Gate;
        
        TH2* h2_MCP2_HeatMap_Pos1Gate_dTGate;
        
        

        
        //TH1* MCP1Energy;
        //TH1* MCP2Energy;


        TH2* MCP2HeatmapgatedMCP1up;
        TH2* MCP2HeatmapgatedMCP1middle;
        TH2* MCP2HeatmapgatedMCP1bottom;
        TH1* MCPtimegatedwith2positiongate;
        
       //notation What to see "MCP2Heatmap" Option "gatedMCP1" "postion= "O" at gsi leftright etc  up middle down is a shift to the gates middle is neutral  
        TH2* MCP2HeatmapgatedMCP1Omiddle;
        TH2* MCP2HeatmapgatedMCP1Oup;
        TH2* MCP2HeatmapgatedMCP1Odown;

        TH2* MCP2HeatmapgatedMCP1centermiddle;
        TH2* MCP2HeatmapgatedMCP1centerup;
        TH2* MCP2HeatmapgatedMCP1centerdown;
       

    
	  	   // zwischenspeicher fuereventbuilding
	    ULong64_t ttrigger0; // T1 hat leider der CAEN stempel geklaut
	    //ULong64_t T1;
        // double T01=0;
        // double T02=0;
        // double E1=0;
        // double X01=0;
        // double X02=0;
        // double Y01=0;
        // double Y02=0;
        // double X11=0;
        // double X12=0;
        // double Y11=0;
        // double Y12=0;
	  

		// GATES
		
        int gatesmcp1T[4]={35,45,47,57};
        int gatesmcp1center[4]={1,5,14,17};

        TBox *gateBoxT = new TBox(gatesmcp1T[0], gatesmcp1T[1],
                                gatesmcp1T[2], gatesmcp1T[3]);
        TBox *gateBoxcenter = new TBox(gatesmcp1center[0], gatesmcp1center[1],
                                gatesmcp1center[2], gatesmcp1center[3]);                        
               
      

        Long64_t mcp_wr = 0;

    public:
        ClassDef(H10MCPNearlineSpectra, 1)
};

#endif
