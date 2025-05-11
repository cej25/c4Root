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
 *                             E.M. Gandolfo                                  *
 *                               25.11.24                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaTraceCorrelation.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>

LisaTraceCorrelation::LisaTraceCorrelation()  :   LisaTraceCorrelation("LisaTraceCorrelation")
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaTraceCorrelation::LisaTraceCorrelation(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    // , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaTraceCorrelation::~LisaTraceCorrelation()
{
    c4LOG(info, "");
}

void LisaTraceCorrelation::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaTraceCorrelation::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa = gDirectory->mkdir("LISA");
    mgr->Register("LISA", "LISA Directory", dir_lisa, false); // allow other tasks to find this


    
    layer_number = lisa_config->NLayers();
    det_number = lisa_config->NDetectors();
    auto const & detector_mapping = lisa_config->Mapping();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    
    //TDirectory::TContext ctx(nullptr);

    dir_lisa->cd();
    dir_crosstalk = dir_lisa->mkdir("CrossTalk");
    //:::::::::::::T R A C E S:::::::::::::::::
    dir_crosstalk->cd();

    //for each detector a canvas
    
    c_traces_cross.resize(xmax*ymax*(layer_number-1));
    c_energies.resize(layer_number-1);

    h2_traces_hit.resize(xmax*ymax*(layer_number-1));
    h1_energies_hit.resize(xmax*ymax*(layer_number-1));
    h2_traces_nothit.resize(xmax*ymax*(layer_number-1));

    h2_maxmax.resize(2);
    h2_maxmin.resize(2);
    h2_minmin.resize(2);
    

    // pareeksha negative traces
    //int tracerange[2] = {0,10000};
    // jiken positive traces
    int tracerange[2] = {0,20000}; 
    
    //:::::::::::Traces canvas for layer 1 and 2   
    for (int i = 0; i < layer_number-1; i++) //create a canvas for each layer
      {
	c_energies[i] = new TCanvas(Form("c_energies_%d",i),Form("c_energies_%d",i), 650,350);
	c_energies[i]->Divide(xmax,ymax);
	dir_crosstalk->Append(c_energies[i]);
	h2_maxmax[i].resize(xmax*ymax);
	h2_maxmin[i].resize(xmax*ymax);
	h2_minmin[i].resize(xmax*ymax);
	for (int j = 0; j < xmax; j++)
	  {
	    for (int k = 0; k < ymax; k++)
	      {
		
		city = "";
		for (auto & detector : detector_mapping)
		  {
		    if (detector.second.first.first == i+1 && detector.second.second.first == j && detector.second.second.second == k)
		      {
			city = detector.second.first.second;
			break;
		      }
		  }
		c4LOG(info, "layer: " << i << " x max: " << xmax << " ymax: " << ymax << " j: " << j << " k: " << k<< " city: " << city<< " canvas " << i*(xmax*ymax)+ymax*j+k);
		
		
		c_energies[i]->cd((ymax-(k+1))*xmax + j + 1);

		h1_energies_hit[i*(xmax*ymax)+ymax*j+k] = new TH1F(Form("energies_hit_%s_%i_%i_%i", city.c_str(), i, j, k),Form("energies_hit_%s_%i_%i_%i", city.c_str(), i, j, k),10000,0,3e6);
		h1_energies_hit[i*(xmax*ymax)+ymax*j+k]->GetXaxis()->SetTitle("Amplitude [arb. units]");
		h1_energies_hit[i*(xmax*ymax)+ymax*j+k]->Draw();


		c_traces_cross[i*(xmax*ymax)+ymax*j+k] = new TCanvas(Form("c_traces_cross_%s",city.c_str()),Form("c_traces_cross_%s",city.c_str()), 650,350);
		
		c_traces_cross[i*(xmax*ymax)+ymax*j+k]->Divide(xmax,ymax);
		c_traces_cross[i*(xmax*ymax)+ymax*j+k]->cd((ymax-(k+1))*xmax + j + 1);

		h2_traces_hit[i*(xmax*ymax)+ymax*j+k] = new TH2F(Form("traces_hit_%s_%i_%i_%i", city.c_str(), i, j, k),Form("traces_hit_%s_%i_%i_%i", city.c_str(), i, j, k),2000,0,2000,1000,tracerange[0],tracerange[1]);
		h2_traces_hit[i*(xmax*ymax)+ymax*j+k]->GetXaxis()->SetTitle("Time [us]");
		h2_traces_hit[i*(xmax*ymax)+ymax*j+k]->GetYaxis()->SetTitle("Amplitude [arb. units]");
		h2_traces_hit[i*(xmax*ymax)+ymax*j+k]->Draw("colz");


		h2_traces_nothit[i*(xmax*ymax)+ymax*j+k].resize(xmax*ymax);
		h2_maxmax[i][j*ymax+k].resize(xmax*ymax);
		h2_maxmin[i][j*ymax+k].resize(xmax*ymax);
		h2_minmin[i][j*ymax+k].resize(xmax*ymax);
                for(int jj=0;jj<xmax;jj++){
		  for(int kk=0;kk<ymax;kk++){
		    if(jj==j && kk==k)
		      continue;
		    c_traces_cross[i*(xmax*ymax)+ymax*j+k]->cd((ymax-(kk+1))*xmax + jj + 1);
		    
		    h2_traces_nothit[i*(xmax*ymax)+ymax*j+k][ymax*jj+kk] = new TH2F(Form("traces_nothit_%s_%i_%i_%i", city.c_str(), i, jj, kk),Form("traces_nothit_%s_%i_%i_%i", city.c_str(), i, jj, kk),2000,0,2000,1000,tracerange[0],tracerange[1]);
		    h2_traces_nothit[i*(xmax*ymax)+ymax*j+k][ymax*jj+kk]->GetXaxis()->SetTitle("Time [us]");
		    h2_traces_nothit[i*(xmax*ymax)+ymax*j+k][ymax*jj+kk]->GetYaxis()->SetTitle("Amplitude [arb. units]");
		    h2_traces_nothit[i*(xmax*ymax)+ymax*j+k][ymax*jj+kk]->Draw("colz");
		    h2_maxmax[i][(j*ymax)+k][(jj*ymax)+kk] = new TH2F(Form("maxmax_l%i_%i_%i_%i_%i", i, j, k, jj, kk),Form("maxmax_l%i_%i_%i_%i_%i", i, j, k, jj, kk),1000,tracerange[0],tracerange[1],1000,tracerange[0],tracerange[1]);
		    h2_maxmin[i][(j*ymax)+k][(jj*ymax)+kk] = new TH2F(Form("maxmin_l%i_%i_%i_%i_%i", i, j, k, jj, kk),Form("maxmin_l%i_%i_%i_%i_%i", i, j, k, jj, kk),1000,tracerange[0],tracerange[1],1000,tracerange[0],tracerange[1]);
		    h2_minmin[i][(j*ymax)+k][(jj*ymax)+kk] = new TH2F(Form("minmin_l%i_%i_%i_%i_%i", i, j, k, jj, kk),Form("minmin_l%i_%i_%i_%i_%i", i, j, k, jj, kk),1000,tracerange[0],tracerange[1],1000,tracerange[0],tracerange[1]);
		  }// kk
		}// jj

		dir_crosstalk->Append(c_traces_cross[i*(xmax*ymax)+ymax*j+k]);

	      }// k to ymax
	  }// j to xmax
      }// i to layers
    h2_traces_Ams = new TH2F("traces_Ams","traces_Ams",1000,tracerange[0],tracerange[1],1000,tracerange[0],tracerange[1]);
    return kSUCCESS;
}


void LisaTraceCorrelation::Exec(Option_t* option){
  wr_time = 0;

  int lhit =-1;
  int xhit =-1;
  int yhit =-1;


  int tracemax[2][2][2] = {{{0,0},{0,0}},{{0,0},{0,0}}};
  int tracemin[2][2][2] = {{{9000,9000},{9000,9000}},{{9000,9000},{9000,9000}}};
  
  
  //c4LOG(info, "Comment to slow down program for testing");
  for (auto const & lisaCalItem : *lisaCalArray){

    wr_time = lisaCalItem.Get_wr_t();
    //if (wr_time == 0)return;

    //::::::: Retrieve Data ::::::::::::::
    layer = lisaCalItem.Get_layer_id();
    //c4LOG(info,"layer uncorrected " << layer);
    // remove tokyo
    if(layer<1)
      continue;
    layer-=1;
	
    city = lisaCalItem.Get_city();
    int xpos = lisaCalItem.Get_xposition();
    int ypos = lisaCalItem.Get_yposition();
    float energy = lisaCalItem.Get_energy();
    std::vector<float> trace = lisaCalItem.Get_trace_febex();
    int pileup = lisaCalItem.Get_pileup();
    int overflow = lisaCalItem.Get_overflow();
    uint64_t evtno = header->GetEventno();
        
    //c4LOG(info,"hit in x = " << xpos << ", y = " << ypos << ", z = " << layer << ", e = " <<energy);
        
    // //::::::::F I L L   H I S T O S:::::::
 
    //c4LOG(info,"filling h2_traces_hit[layer*(xmax*ymax)+ymax*xpos+ypos] " << layer*(xmax*ymax)+ymax*xpos+ypos);
    h1_energies_hit[layer*(xmax*ymax)+ymax*xpos+ypos]->Fill(energy);
    // since we do not have the energy, cut on a LED here
    bool thishit = false;
    for (int t = 0; t < trace.size(); t++){
      if(trace[t]>tracemax[layer][xpos][ypos])
	tracemax[layer][xpos][ypos] = trace[t];
      if(trace[t]<tracemin[layer][xpos][ypos])
	tracemin[layer][xpos][ypos] = trace[t];
      
      if(trace[t]>14000){
	lhit = layer;
	xhit = xpos;
	yhit = ypos;
	thishit = true;
	//break;
      }
    }//trace points
    if(thishit){
      for (int t = 0; t < trace.size(); t++){
	h2_traces_hit[layer*(xmax*ymax)+ymax*xpos+ypos]->Fill(t,trace[t]);
      }//trace points
    }
	
  }
  for(int l=0;l<2;l++){
    for(int x=0;x<2;x++){
      for(int y=0;y<2;y++){

	for(int xp=0;xp<2;xp++){
	  for(int yp=0;yp<2;yp++){
	    if(xp==x && yp==y)
	      continue;
	    h2_maxmax[l][(x*ymax)+y][(xp*ymax)+yp]->Fill(tracemax[l][x][y],tracemax[l][xp][yp]);
	    h2_maxmin[l][(x*ymax)+y][(xp*ymax)+yp]->Fill(tracemax[l][x][y],tracemin[l][xp][yp]);
	    h2_minmin[l][(x*ymax)+y][(xp*ymax)+yp]->Fill(tracemin[l][x][y],tracemin[l][xp][yp]);
	  }
	}
	//
      }
    }
  }
  
  for (auto const & lisaCalItem : *lisaCalArray){
    //::::::: Retrieve Data ::::::::::::::
    layer = lisaCalItem.Get_layer_id();
    // same layer
    layer-=1;
    if(layer < 0 || layer!=lhit)
      continue;
    int xpos = lisaCalItem.Get_xposition();
    int ypos = lisaCalItem.Get_yposition();
    if(xpos == xhit && ypos == yhit)
      continue;
    //c4LOG(info,"not hit in x = " << xpos << ", y = " << ypos << ", z = " << layer);
    //c4LOG(info,"filling h2_traces_nothit[layer*(xmax*ymax)+ymax*xpos+ypos][ymax*xpos+ypos] " << layer*(xmax*ymax)+ymax*xpos+ypos << " " << ymax*xpos+ypos);
    std::vector<float> trace = lisaCalItem.Get_trace_febex();
    for (int t = 0; t < trace.size(); t++)
      h2_traces_nothit[layer*(xmax*ymax)+ymax*xhit+yhit][ymax*xpos+ypos]->Fill(t,trace[t]);
  }

  // check amsterdam
  std::vector<int16_t> trace_Ams;
  for (auto const & lisaCalItem : *lisaCalArray){
    layer = lisaCalItem.Get_layer_id();
    if(layer<1)
      continue;
    layer-=1;
    
    int xpos = lisaCalItem.Get_xposition();
    int ypos = lisaCalItem.Get_yposition();
    if(layer==0 && xpos == 1 && ypos == 0){
      // trace_Ams = lisaCalItem.Get_trace_febex();
      break;
    }
  }
  if(trace_Ams.size()==0)
    return;
  for (auto const & lisaCalItem : *lisaCalArray){
    layer = lisaCalItem.Get_layer_id();
    if(layer<1)
      continue;
    layer-=1;
    
    int xpos = lisaCalItem.Get_xposition();
    int ypos = lisaCalItem.Get_yposition();
    if(layer==0 && xpos == 1 && ypos == 1){
      std::vector<float> trace = lisaCalItem.Get_trace_febex();
      for (int t = 0; t < trace.size(); t++)
	h2_traces_Ams->Fill(trace[t],trace_Ams[t]);
    }
  }//lisaCalArray


  //c4LOG(info,"done with event " << fNEvents);
  fNEvents += 1;
}

void LisaTraceCorrelation::FinishEvent()
{

}

void LisaTraceCorrelation::FinishTask()
{

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "LISA events : " << fNEvents);



}

ClassImp(LisaTraceCorrelation)
