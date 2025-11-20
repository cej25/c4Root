std::string outstring = "\n\
....................................................................................................\n\
....................................................................................................\n\
...............................................:+#*:................................................\n\
..............................................:*###*-...............................................\n\
.............................................-*######-..............................................\n\
............................................:#########::............................................\n\
............................................*##########=:...........................................\n\
..........................................-######-*#####-:..........................................\n\
.........................................:######:..+#####=:.........................................\n\
........................................-#####*..  .+#####=:........................................\n\
.......................................-######:     .=#####+:.......................................\n\
.....................................:-#####*.       .+#####*:......................................\n\
.....................................=######..     ....-#####*:.....................................\n\
...................................:=#####+..    .+@@+..-#####*-....................................\n\
..................................:+#####+..-----:#@@*. .-#####*:...................................\n\
.................................:+#####+.+@#*%@@@=...   .:######-..................................\n\
................................:*#####+.-@#.=@@@@-        :######-.................................\n\
...............................:*#####=..:+=#@@@@@-        ..*#####-................................\n\
..............................-*#####-    .:#@@**@:          .######=...............................\n\
.............................:######=.    +@@@+.%@:          ..*#####-:.............................\n\
............................:*#####:.   .=@@.+@%-%*#..  .#@%:...*#####+:............................\n\
...........................-######-.   .=@#...+@+. .=#:+@@@@@*...+#####=:...........................\n\
..........................:#####*:..  .=@%.  .=@*. .-#@@@@@@@@@:..+#####+:..........................\n\
.........................-######:     -@%.   .=@*..*@@@@@@@@@@@@*..+#####*:.........................\n\
........................-######:.     :*..   ..++.#%%%%%%%%%%%%%%+..=#####*:........................\n\
......................:=######:::::::::::::::::::::::::::::::::::::::+######:.......................\n\
......................=#####################################################*:......................\n\
.....................-#######################################################*:.....................\n\
.....................:::::::::::::::::::::::::::::::::::::::::::::::::::::::::......................\n\
....................................................................................................\n\
....................................................................................................\n\
....................................  STILL UNDER CONSTRUCTION  ....................................\n\
....................................................................................................\n\
....................................................................................................";

#include "TH2F.h"
#include "TFile.h"
#include "TCutG.h"
#include "TString.h"
#include "TParameter.h"

bool MakeMcp1PosGate(TH2F* hist, bool madeMcp1PosGate, bool madeMcp2PosGate, bool madeDtGate){
  // TString cuts;
  // if (madeMcp1PosGate) cuts += "mcp1PosGate && ";  
  // if (madeMcp2PosGate) cuts += "mcp2PosGate && ";  
  // if (madeDtGate) cuts += "dtGate && ";  

  // if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
  // std::cout << "Drawing with the condition: " << cuts << std::endl;

  hist->Draw("COLZ");
  gPad->WaitPrimitive("CUTG");
  TCutG* mcp1PosGate = dynamic_cast<TCutG*>(gROOT->FindObject("CUTG"));
  if (mcp1PosGate == nullptr){
    std::cout << "No mcp1PosGate gate given. Continuing..." << std::endl;
    return false;
  }
  else{
    mcp1PosGate = dynamic_cast<TCutG*>(mcp1PosGate->Clone("mcp1PosGate"));
    gROOT->FindObject("CUTG")->Delete();
    mcp1PosGate->SetVarY("dy");
    mcp1PosGate->SetVarX("dx");
    std::cout << "Created gate: " << mcp1PosGate->GetName() << std::endl;
    return true;
  }
} 

bool MakeMcp2PosGate(TH2F* hist, bool madeMcp1PosGate, bool madeMcp2PosGate, bool madeDtGate){
  // TString cuts;
  // if (madeMcp1PosGate) cuts += "mcp1PosGate && ";  
  // if (madeMcp2PosGate) cuts += "mcp2PosGate && ";  
  // if (madeDtGate) cuts += "dtGate && ";  

  // if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
  // std::cout << "Drawing with the condition: " << cuts << std::endl;

  hist->Draw("COLZ");
  gPad->WaitPrimitive("CUTG");
  TCutG* mcp2PosGate = dynamic_cast<TCutG*>(gROOT->FindObject("CUTG"));
  if (mcp2PosGate == nullptr){
    std::cout << "No mcp2PosGate gate given. Continuing..." << std::endl;
    return false;
  }
  else{
    mcp2PosGate = dynamic_cast<TCutG*>(mcp2PosGate->Clone("mcp2PosGate"));
    gROOT->FindObject("CUTG")->Delete();
    mcp2PosGate->SetVarY("dy");
    mcp2PosGate->SetVarX("dx");
    std::cout << "Created gate: " << mcp2PosGate->GetName() << std::endl;
    return true;
  }
} 

bool MakeDtGate(TH1F* hist, bool madeMcp1PosGate, bool madeMcp2PosGate, bool madeDtGate){
  Double_t lowBound, highBound;  
  TCanvas* c = new TCanvas("c", "", 800, 600);
  hist->Draw();
  c->Update();
  
  std::cout << "Provide the lower bound for the dt gate \nLower Bound: ";
  std::cin >> lowBound;
  std::cout << std::endl;

  std::cout << "Provide the upper bound for the dt gate \nUpper Bound: ";
  std::cin >> highBound;
  std::cout << std::endl;

  TParameter<Double_t> lowBoundParameter("lowBound", lowBound);
  TParameter<Double_t> highBoundParameter("highBound", highBound);

  c->Close();
  delete c;

  std::cout << "Created gate: mcpDtGate" << std::endl;
  return true;
} 

void make_mcp_gates_w_trees(TString infileName){

  // For self-evident reasons
  std::cout << outstring << std::endl;
  return;

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
    int gateType;
    std::cout << "Choose a gate: (1) MCP 1 Position || (2) MCP 2 Position || (3) MCP dT \nGate to make: ";
    std::cin >> gateType;
    std::cout << std::endl;

    switch (gateType){
      case 1:{
        madeMcp1PosGate = MakeMcp1PosGate(h2_mcp1HeatMap, madeMcp1PosGate, madeMcp2PosGate, madeDtGate);
        break;
      }
      case 2:{
        madeMcp2PosGate = MakeMcp2PosGate(h2_mcp2HeatMap, madeMcp1PosGate, madeMcp2PosGate, madeDtGate);
        break;
      }
      case 3:{
        madeDtGate = MakeDtGate(h1_dT, madeMcp1PosGate, madeMcp2PosGate, madeDtGate);
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
    gROOT->FindObject("lowBound")->Write();
    gROOT->FindObject("highBound")->Write();
  } 

  outfile->Close();
}