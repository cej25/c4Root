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
 *                        C.E. Jones, D. Bittner                              *
 *                               06.05.25                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

// c4
#include "H10MCPNearlineSpectra.h"
#include "EventHeader.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>
#include <sstream>
#include "TBox.h"

  //std::string rootRunname = Runname + ".root";
std::string Runname =   "test" 	;	//outputfile
H10MCPNearlineSpectra::H10MCPNearlineSpectra() : H10MCPNearlineSpectra("H10MCPNearlineSpectra")
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPNearlineSpectra::H10MCPNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
    , fHitsMCP(NULL)
{    
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPNearlineSpectra::~H10MCPNearlineSpectra()
{
    // delete
}


InitStatus H10MCPNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // FairRunAna* run = FairRunAna::Instance();
    // run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp = gDirectory->mkdir("MCPs");
    gDirectory->cd("MCPs");

    h1_test_histogram = MakeTH1(dir_mcp, "F", "h1_test_histogram", "TEST HIST", 4000, -500, 100);  
	histogram2 = MakeTH2(dir_mcp,"b", "aaa", "test hist" , 100, -250, 250, 100, -100, 100);
	MCP1Heatmap = MakeTH2(dir_mcp,"b", "MCP1Heatmap", "MCP1Heatmap" , 500, -2500000, 2500000, 500, -2500000, 2500000);
	MCP2Heatmap = MakeTH2(dir_mcp,"b", "MCP2Heatmap", "MCP2Heatmap" , 500, -250, 250, 500, -250, 250);
	
	
	
	
	    MCP1X1ddiff = MakeTH1(dir_mcp, "F", "MCP1X1ddiff", "MCP1X1ddiff", 4000, -7000, 2000);  
	    MCP1Y1ddiff = MakeTH1(dir_mcp, "F", "MCP1Y1ddiff", "MCP1Y1ddiff", 4000, -7000, 2000);  


	
		MCP2HeatmapgatedMCP1Omiddle = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
		MCP2HeatmapgatedMCP1Oup = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1up", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
				MCP2HeatmapgatedMCP1Odown = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1down", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);

				
				
				
				MCP2HeatmapgatedMCP1centermiddle = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1centermiddle", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
		MCP2HeatmapgatedMCP1centerup = MakeTH2(dir_mcp,"b", "MCP2HeatmapTcenter1up", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
				MCP2HeatmapgatedMCP1centerdown = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1centerdown", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);		

	//MCP2Heatmap = MakeTH2(dir_mcp,"b", "MCP2Heatmap", "MCP2Heatmap" , 500, -250, 250, 500, -250, 250);
	//MCP2Heatmap = MakeTH2(dir_mcp,"b", "MCP2Heatmap", "MCP2Heatmap" , 500, -250, 250, 500, -250, 250);

	// gates
	//gatesmcp1T [] = {35,	45,	47,	57};

  // histogram = MakeTH1(dir_mcp,"a", "TDiff Distribution", 1000, -200000, -150000);

 //   h1_time = MakeTH1(dir_mcp, "F", "MCPtimediff", "TEST HIST2", 1000, -1000000, 100000);
  //  h2_mcp1 = MakeTH1(dir_mcp, "F", "Heatmapmcp1", "TEST HIST", 1000, -1000000, 10000000,1000, -1000000, 10000000);
  //  h2_mcp2 = MakeTH1(dir_mcp, "F", "Heatmapmcp1", "TEST HIST", 1000, -1000000, 10000000,1000, -1000000, 10000000);

    return kSUCCESS;
    
}

    

void H10MCPNearlineSpectra::Exec(Option_t* option)
{ 
	
	
	
		   // zwischenspeicher fuereventbuilding
	 T01=1000;
	 T02=-5000;
	 E1=0;
	 X01=1000;
	 X02=-5000;
	 Y01=1000;
	 Y02=-5000;
	 X11=1000;
	 X12=-5000;
	 Y11=1000;
	 Y12=-5000;
   SC41L=0;
   SC41R=0;
   SC42L=0;
   SC42R=0;
  DSSDAccept = 0;

//	  double T01Epoch=0;
//	  double T02Epoch=0;
//	  double X01Epoch=0;
//	  double X02Epoch=0;
//	  double Y01Epoch=0;
//	  double Y02Epoch=0;
//	  double X11Epoch=0;
//	  double X12Epoch=0;
//	  double Y11Epoch=0;
//	  double Y12Epoch=0;
	  
	  // fertige events speichern
//	  std::vector<Long64_t> TDiff;
//	  std::vector<Long64_t> XDiff;
//	  std::vector<Long64_t> YDiff;
	  // variables vor code

	  
    auto start = std::chrono::high_resolution_clock::now();
       // std::cout << fHitsMCP->GetEntriesFast() << std::endl;

    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   

        Long64_t mpc_wr = 0;
        Int_t nHits = fHitsMCP->GetEntriesFast();
      //  std::cout << "nHits in event: " << nHits  << std::endl;

        for (Int_t ihit = 0; ihit < nHits; ihit++) {
            H10MCPTwinpeaksCalData* hit = (H10MCPTwinpeaksCalData*)fHitsMCP->At(ihit);
            if (!hit) continue;
            mcp_wr = hit->Get_wr_t();
            
                   
            
            Int_t mcp_id = hit->Get_mcp_id();
            Int_t type = hit->Get_type();
            Int_t number = hit->Get_number();
            //std::cout << "ihit :: "<< ihit << std::endl;
		//	std::cout <<< "HIT" << ihit << ": " << "\t" <<  mcp_id << "\t" << type << "\t" << number << std::endl;
            

			if (mcp_id==0 && type==0 && number== 0 ){
			 T01 = hit->Get_fast_lead_time();
		//	 T01Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==1 && type==0 && number== 0 )
			{
			 T02 = hit->Get_fast_lead_time();
		//	 T02Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==0 && type==1 && number== 0 )
			{
			 X01 = hit->Get_fast_lead_time();
		//	 X01Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==0 && type==1 && number== 1 )
			{
			 X02 = hit->Get_fast_lead_time();
		//	 X02Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==0 && type==2 && number== 0 )
			{
			 Y01 = hit->Get_fast_lead_time(); 
		//	Y01Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==0 && type==2 && number== 1 )
			{
			 Y02 = hit->Get_fast_lead_time();
		//	 Y02Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==1 && type==1 && number== 0 )
			{
			 X11 = hit->Get_fast_lead_time(); 
		//	X11Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==1 && type==1 && number== 1 )
			{
			X12 = hit->Get_fast_lead_time(); 
		//	X12Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==1 && type==2 && number== 0 )
			{
			 Y11 = hit->Get_fast_lead_time();
		//	 Y11Epoch=hit->Get_fast_lead_epoch();
		}
			if (mcp_id==1 && type==2 && number== 1 )
			{
			 Y12 = hit->Get_fast_lead_time();
			// Y12Epoch=hit->Get_fast_lead_epoch();
			}
      if (mcp_id==0 && type==3 && number==0)
      {
        SC41L = hit->Get_fast_lead_time();
      }
      if (mcp_id==0 && type==3 && number==1)
      {
        SC41R = hit->Get_fast_lead_time();
      }
      if (mcp_id==0 && type==4 && number==0)
      {
        SC42L = hit->Get_fast_lead_time();
      }
      if (mcp_id==0 && type==4 && number==1)
      {
        SC42R = hit->Get_fast_lead_time();
      }
      if (mcp_id==0 && type==5 && number==0)
      {
        DSSDAccept = hit->Get_fast_lead_time();
      }
/*
          if (mcp_id==0 && type==0 && number== 0  && ch0counter == 0 )
          {
            T2 = hit->Get_fast_lead_time(); 
            ch0counter++;
            eventcounter++;
            E1 = hit->Get_slow_ToT();
            // 	std::cout << "ch0counter: " << ch0counter << std::endl;
          } 
          if (mcp_id==0 && type==1 && number== 0 && ch1counter == 0 && ch0counter == 1)
          {
            X1 = hit->Get_fast_lead_time(); 
            ch1counter++;
            eventcounter++;
             //	std::cout << "ch1counter: " << ch1counter << std::endl;
          }  
          if (mcp_id==0 && type==1 && number== 0 &&  ch2counter == 0 && ch0counter == 1)
          {
            X2 = hit->Get_fast_lead_time(); 
            ch2counter++;
            eventcounter++;
             //	std::cout << "ch2counter: " << ch2counter << std::endl;
          }
          if (mcp_id==0 && type==2 && number== 0&&  ch3counter == 0 && ch0counter == 1) 
          {
            Y1 = hit->Get_fast_lead_time(); 
            ch3counter++;
            eventcounter++;
             	//std::cout << "ch3counter: " << ch3counter << std::endl;
          }
          if (mcp_id==0 && type==2 && number== 1  && ch4counter == 0 && ch0counter == 1)
          {
            Y2 = hit->Get_fast_lead_time(); 
            ch4counter++;
            eventcounter++;
             //	std::cout << "ch4counter: " << ch4counter << std::endl;
          }
          if (mcp_id==1 && type==0 && number== 0 && ch5counter == 0 && ch0counter == 1)
          {
            T3 = hit->Get_fast_lead_time(); 
            ch5counter++;
            eventcounter++;
            //std::cout << "T3eventc: " << eventcounter << std::endl;//
            // 	std::cout << "ch1counter: " << ch1counter << std::endl;
          } 
*/
    
  }

  // h1_sc41_vs_mcp->Fill();

	h1_test_histogram->Fill(T01 - T02);
	MCP1X1ddiff->Fill(X02-X01);
	MCP1Y1ddiff->Fill(Y02-Y01);
	histogram2->Fill(X02-X01, T02-T01);
	MCP1Heatmap->Fill(X02-X01, Y02-Y01);
	MCP2Heatmap->Fill(X12-X11, Y12-Y11);
  
			//GATED
      if (gateBoxT->IsInside(X02-X01, Y02-Y01)) {
	    MCP2HeatmapgatedMCP1Omiddle->Fill(X12-X11,Y12-Y11   );}                                         
      if (gateBoxT->IsInside(X02-X01+10, Y02-Y01+10)) {
		            //  	std::cout << "ch1counter: " << ch1counter << std::endl;
	    MCP2HeatmapgatedMCP1Oup->Fill(X12-X11,Y12-Y11   );}  
	  if (gateBoxT->IsInside(X02-X01-10, Y02-Y01-10)) {
	    MCP2HeatmapgatedMCP1Odown->Fill(X12-X11,Y12-Y11   );}    
	    
	     if (gateBoxcenter->IsInside(X02-X01, Y02-Y01)) {
	    MCP2HeatmapgatedMCP1centermiddle->Fill(X12-X11,Y12-Y11   );}       
	                                  
  	}

	
  //std::cout << "start plotting: " << dataPointsCounter << std::endl;

  
  
  //  histogram2->Fill(XDiff[i], YDiff[i]);
    
   //    std::cout << "fill: " << dataPointsCounter << std::endl;


//  std::cout << "plotfin: " << std::endl;

  // canvas->cd(2); // Select the first part of the canvas
 // for (int i = 0; i < dataPointsCounter; i++)
//  {
  //  histogram2->Fill(XDiff[i], YDiff[i]);
 //   if (XDiff[i] > gates[0] && XDiff[i] < gates[1] && YDiff[i] > gates[2] && YDiff[i] < gates[3])
 //   {
 //     histogramxgated->Fill(XDiff[i]);
 //   }
 //   if (XDiff[i] > gates[6] && XDiff[i] < gates[7] && YDiff[i] > gates[4] && YDiff[i] < gates[5])
 //   {
 //     histogramygated->Fill(YDiff[i]);
 //   }
//d::cout << "plot2fin: " << std::endl;
  //canvas->cd(1);
  // Select the first part of the canvas
  //histogramxgated->Draw(); // Draw the first histogram
                           // Select the second part of the canvas
  // col2 for fast
 // canvas->cd(2);
////chatgpt


// Update the canvas
//canvas->Update();

//TPaveStats *stats = (TPaveStats*)histogram2->FindObject("stats"); not working

//if (stats) {
 //   stats->SetX1NDC(0.4); // Set the left edge position in NDC (normalized device coordinates)
  //  stats->SetY1NDC(0.4); // Set the bottom edge position in NDC
 //   stats->SetX2NDC(0.4); // Set the right edge position in NDC
 //   stats->SetY2NDC(0.4); // Set the top edge position in NDC
//}
///endechatgpt

// Redraw the histogram with updated axis labels
//histogram2->Draw("colz");

  //histogramygated->Draw();
  //canvas->Update();

 // canvas2d->cd();
 // histogram2->Draw("colz");
  //gPad->SetLogz(); // logcolorbar
  //canvas2d->Update();

 // std::cout << "kein neuer file gefunden" << std::endl;
 // std::string rootRunname = Runname + ".root";
 // const char *CRunname = rootRunname.c_str(); // umwandlung von string to c_string (vill)

  //TFile *file = new TFile(CRunname, "RECREATE");
 // canvas->cd();
 // canvas->Write();
 // canvas2d->cd();

 // canvas2d->Write();
   // h1_test_histogram->Write();
  // histogram2->Write();
 // std::cout << "finite: " << std::endl;

 // file->Close();

  // Clean up
 // delete canvas;
  // delete histogram;
//  delete histogram2;
 // delete file;
    




















    //    }

    
    


    fNEvents++;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void H10MCPNearlineSpectra::FinishEvent()
{
    // resets and whatever
}

void H10MCPNearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp->Write();
    gDirectory = tmp;
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(H10MCPNearlineSpectra)
