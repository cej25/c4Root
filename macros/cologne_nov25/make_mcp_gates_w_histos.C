#include "TH2F.h"
#include "TFile.h"
#include "TCutG.h"
#include "TString.h"
#include "TParameter.h"

bool MakeMcp1PosGate(TH2F* hist){

  hist->Draw("COLZ");
  gPad->Update();
  gPad->WaitPrimitive("CUTG");
  TCutG* mcp1PosGate = dynamic_cast<TCutG*>(gROOT->FindObject("CUTG"));
  if (mcp1PosGate == nullptr){
    std::cout << "No mcp1PosGate gate given. Continuing..." << std::endl;
    return false;
  }
  else{
    mcp1PosGate = dynamic_cast<TCutG*>(mcp1PosGate->Clone("mcp1PosGate"));
    // gROOT->FindObject("CUTG")->Delete();
    mcp1PosGate->SetVarY("dy");
    mcp1PosGate->SetVarX("dx");
    std::cout << "Created gate: " << mcp1PosGate->GetName() << std::endl;
    return true;
  }
} 

bool MakeMcp2PosGate(TH2F* hist){

  hist->Draw("COLZ");
  gPad->Update();
  gPad->WaitPrimitive("CUTG");
  TCutG* mcp2PosGate = dynamic_cast<TCutG*>(gROOT->FindObject("CUTG"));
  if (mcp2PosGate == nullptr){
    std::cout << "No mcp2PosGate gate given. Continuing..." << std::endl;
    return false;
  }
  else{
    mcp2PosGate = dynamic_cast<TCutG*>(mcp2PosGate->Clone("mcp2PosGate"));
    // gROOT->FindObject("CUTG")->Delete();
    mcp2PosGate->SetVarY("dy");
    mcp2PosGate->SetVarX("dx");
    std::cout << "Created gate: " << mcp2PosGate->GetName() << std::endl;
    return true;
  }
} 

bool MakeDtGate(TH1F* hist){
  Double_t lowBound, highBound;  
  hist->Draw();
  gPad->Update();
  
  std::cout << "Provide the lower bound for the dt gate \nLower Bound: ";
  std::cin >> lowBound;
  std::cout << std::endl;

  std::cout << "Provide the upper bound for the dt gate \nUpper Bound: ";
  std::cin >> highBound;
  std::cout << std::endl;

  TParameter<Double_t>* lowBoundParameter = new TParameter<Double_t>("dtLowBound", lowBound);
  TParameter<Double_t>* highBoundParameter = new TParameter<Double_t>("dtHighBound", highBound);
  gROOT->GetListOfSpecials()->Add(lowBoundParameter);
  gROOT->GetListOfSpecials()->Add(highBoundParameter);

  std::cout << "Created gate: mcpDtGate" << std::endl;
  return true;
} 

void make_mcp_gates_w_histos(TString infileName){

  TFile* infile = TFile::Open(infileName, "READ");

  if (!infile || !infile->IsOpen()){
    std::cout << "\nFailed on file open." << std::endl;
    return;
  }

  TH2F* h2_mcp1HeatMap = dynamic_cast<TH2F*>(infile->Get("MCPs/Position/h2_MCP1_HeatMap"));
  TH2F* h2_mcp2HeatMap = dynamic_cast<TH2F*>(infile->Get("MCPs/Position/h2_MCP2_HeatMap"));
  TH1F* h1_dT = dynamic_cast<TH1F*>(infile->Get("MCPs/h1_dT"));

  if (!h2_mcp1HeatMap) throw std::runtime_error("Could not find \'h2_mcp1HeatMap\' in " + infileName );
  if (!h2_mcp2HeatMap) throw std::runtime_error("Could not find \'h2_mcp2HeatMap\' in " + infileName );
  if (!h1_dT) throw std::runtime_error("Could not find \'h1_dT\' in " + infileName );
  

  bool madeMcp1PosGate = false;
  bool madeMcp2PosGate = false;
  bool madeDtGate = false;

  TString gateName;
  std::cout << "\nProvide a name for these gates: ";
  std::cin >> gateName;
  std::cout << std::endl;

  bool makingGates = true;

  while (makingGates){

    if (madeMcp1PosGate && madeMcp2PosGate && madeDtGate){
      std::cout << "\nAll Possible gates made. Saving..." << std::endl;
      makingGates=true;
      break;
    }

    TString cuts;
    if (!madeMcp1PosGate) cuts += "(1) MCP 1 Position || ";  
    if (!madeMcp2PosGate) cuts += "(2) MCP 2 Position || ";  
    if (!madeDtGate) cuts += "(3) MCP dT ";  
    if (cuts.EndsWith(" || ")) cuts = cuts(0,cuts.Length()-4);

    int gateType;
    std::cout << "Choose a gate: " << cuts << "|| (q to quit)\nGate to make: ";
    std::cin >> gateType;
    std::cout << std::endl;

    switch (gateType){
      case 1:{
        if (madeMcp1PosGate){
          std::cout << "MCP 1 position gate already made. Continuing..." << std::endl; 
          break;
        }
        madeMcp1PosGate = MakeMcp1PosGate(h2_mcp1HeatMap);
        break;
      }
      case 2:{
        if (madeMcp2PosGate){
          std::cout << "MCP 2 position gate already made. Continuing..." << std::endl; 
          break;
        }
        madeMcp2PosGate = MakeMcp2PosGate(h2_mcp2HeatMap);
        break;
      }
      case 3:{
        if (madeDtGate){
          std::cout << "MCP dt gate already made. Continuing..." << std::endl; 
          break;
        }
        madeDtGate = MakeDtGate(h1_dT);
        break;
      }
      default:{
        std::cout << "Option not recognised. Exiting..." << std::endl;
        makingGates = false;
        break;
      }
    }
  }

  TFile* outfile = new TFile(gateName + ".root", "RECREATE");

  if (madeMcp1PosGate) gROOT->FindObject("mcp1PosGate")->Write();
  if (madeMcp2PosGate) gROOT->FindObject("mcp2PosGate")->Write();
  if (madeDtGate){
    gROOT->FindObject("dtLowBound")->Write();
    gROOT->FindObject("dtHighBound")->Write();
  } 

  outfile->Close();
}