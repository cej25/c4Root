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
 *                         G. Bruni-Campanella                                *
 *                              06.05.25                                      *
 ******************************************************************************/

/*..................................................................................................
....................................................................................................
...............................................:+#*:................................................
..............................................:*###*-...............................................
.............................................-*######-..............................................
............................................:#########::............................................
............................................*##########=:...........................................
..........................................-######-*#####-:..........................................
.........................................:######:..+#####=:.........................................
........................................-#####*..  .+#####=:........................................
.......................................-######:     .=#####+:.......................................
.....................................:-#####*.       .+#####*:......................................
.....................................=######..     ....-#####*:.....................................
...................................:=#####+..    .+@@+..-#####*-....................................
..................................:+#####+..-----:#@@*. .-#####*:...................................
.................................:+#####+.+@#*%@@@=...   .:######-..................................
................................:*#####+.-@#.=@@@@-        :######-.................................
...............................:*#####=..:+=#@@@@@-        ..*#####-................................
..............................-*#####-    .:#@@**@:          .######=...............................
.............................:######=.    +@@@+.%@:          ..*#####-:.............................
............................:*#####:.   .=@@.+@%-%*#..  .#@%:...*#####+:............................
...........................-######-.   .=@#...+@+. .=#:+@@@@@*...+#####=:...........................
..........................:#####*:..  .=@%.  .=@*. .-#@@@@@@@@@:..+#####+:..........................
.........................-######:     -@%.   .=@*..*@@@@@@@@@@@@*..+#####*:.........................
........................-######:.     :*..   ..++.#%%%%%%%%%%%%%%+..=#####*:........................
......................:=######:::::::::::::::::::::::::::::::::::::::+######:.......................
......................=#####################################################*:......................
.....................-#######################################################*:.....................
.....................:::::::::::::::::::::::::::::::::::::::::::::::::::::::::......................
....................................................................................................
....................................................................................................
....................................  STILL UNDER CONSTRUCTION  ....................................
....................................................................................................
..................................................................................................*/

#include "McpGate.h"

#include "TFile.h"
#include "TCutG.h"
#include "TString.h"
#include "TParameter.h"

#include "c4Logger.h"

McpGate::McpGate(TString& gateName, TString& fileName){
  this->gateName = gateName;
  this->fileName = fileName;

  GetGatesFromFile();
}

McpGate::GetGatesFromFile(){

  TFile* gateFile = dynamic_cast<TFile*>( TFile::Open(fileName, "READ") );

  // Position 
  gate_mcp1PosDxVsPosDy = dynamic_cast<TCutG*>(gateFile->Get("cut_mcp1PosDxVsPosDy"));
  gate_mcp2PosDxVsPosDy = dynamic_cast<TCutG*>(gateFile->Get("cut_mcp2PosDxVsPosDy"));
  
  // Time
  auto lowBound = dynamic_cast<TParameter<Double_t>*>(gateFile->Get("dtLowBound"));
  auto highBound =  dynamic_cast<TParameter<Double_t>*>(gateFile->Get("dtHighBound"));
  if (lowBound && highBound) gate_deltaTime = new DeltaTimeGate{true, lowBound->GetVal(), highBound->GetVal()};

  c4LOG(
    info, 
    Form("MCP gate %s loaded with cuts on mcp1Pos = %i, mcp2Pos = %i, mcpDt = %i",
      gateName,
      Does_mcp1PosDxVsPosDy_Exist(),
      Does_mcp1PosDxVsPosDy_Exist(),
      Does_deltaTime_Exist()
    )
  );

  gateFile->Close();
}

bool McpGate::Passed_mcp1PosDxVsPosDy(Double_t dx, Double_t dy){
  bool passed_mcp1PosDxVsPosDy = false;
  passed_mcp1PosDxVsPosDy = (Does_mcp1PosDxVsPosDy_Exist()) ? gate_mcp1PosDxVsPosDy->IsInside(dx, dy) : true;
  return passed_mcp1PosDxVsPosDy;
}

bool McpGate::Passed_mcp2PosDxVsPosDy(Double_t dx, Double_t dy){
  bool passed_mcp2PosDxVsPosDy = false;
  passed_mcp2PosDxVsPosDy = (Does_mcp2PosDxVsPosDy_Exist()) ? gate_mcp2PosDxVsPosDy->IsInside(dx, dy) : true;
  return passed_mcp2PosDxVsPosDy;
}

bool McpGate::Passed_deltaTime(Double_t dt){
  bool passed_deltaTime = false;
  passed_deltaTime = (Does_deltaTime_Exist()) ? gate_deltaTime->IsInside(dt) : true;
  return passed_mcp2PosDxVsPosDy;
}

bool McpGate::PassedAll(Double_t dx, Double_t dy, Double_t dt){
  bool passed_mcp1PosDxVsPosDy = Passed_mcp1PosDxVsPosDy(dx, dy);
  bool passed_mcp2PosDxVsPosDy = Passed_mcp2PosDxVsPosDy(dx, dy);
  bool passed_deltaTime = Passed_deltaTime(dt);

  return ( passed_mcp1PosDxVsPosDy && passed_mcp2PosDxVsPosDy && passed_deltaTime ); 
}

ClassImp(McpGate)