// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaOnlineSpectra.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include "LisaTraceData.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>

LisaOnlineSpectra::LisaOnlineSpectra()
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaOnlineSpectra::LisaOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    
}

LisaOnlineSpectra::~LisaOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitLisa)
        delete fHitLisa;
}

void LisaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitLisa = (TClonesArray*)mgr->GetObject("LisaData");
    c4LOG_IF(fatal, !fHitLisa, "Branch LisaData not found!");

    //sum time spectrum
    // spectra definition

    //Define histograms
    
    TFolder *lisaFold = new TFolder("Lisa", "Lisa");
    run->AddObject(lisaFold);

    
    //:::::::::::C H A N N E L S    I D:::::::::::::::
    c_channelID = new TCanvas("c_channelID","c_channelID", 650, 350);
    c_channelID->SetTitle("Channel ID");
    h1_channelID = new TH1I("h1_channelID","LISA Channel IDs",16,0,16);
    h1_channelID->GetXaxis()->SetTitle("ChID Fired");
    h1_channelID->SetStats(0);
    h1_channelID->Draw();
    lisaFold->Add(h1_channelID);
    lisaFold->Add(c_channelID);
    

    //:::::::::::T O T  M U L T I P L I C I T Y:::::::::::::::::
    c_multiplicity = new TCanvas("c_multiplicity","c_multiplicity", 650,350);
    c_multiplicity->SetTitle("Tot Multiplicity");
    h1_multiplicity = new TH1I("h1_multiplicity","LISA Multiplicity",8,0,8); //for 3 layers 2x2 + 1
    h1_multiplicity->GetXaxis()->SetTitle("Tot Multiplicity");
    h1_multiplicity->SetStats(0);
    h1_multiplicity->Draw();
    lisaFold->Add(h1_multiplicity);
    lisaFold->Add(c_multiplicity);


    //:::::::::::M U L T I P L I C I T Y   P E R   L A Y E R:::::::::::::::::
    std::vector<std::string> layer_names = {"Tokyo", "Eris", "Sparrow"};

    c_multiplicity_layer = new TCanvas("c_multiplicity_layer","c_multiplicity_layer", 650,350);
    c_multiplicity_layer->SetTitle("Multiplicity for Layer");

    c_multiplicity_layer->Divide(3,1);

    for (int i = 0; i < 3; i++) //create histo per each layer
    {
        c_multiplicity_layer->cd(i+1);
        h1_multiplicity_layer.resize(3); 
        h1_multiplicity_layer[i] = new TH1I("h1_multiplicity_layer",Form("Layer %s",layer_names[i].c_str()),4,0,4);            
        h1_multiplicity_layer[i]->GetXaxis()->SetTitle(Form("Multiplicity Layer %s",layer_names[i].c_str()));
        h1_multiplicity_layer[i]->SetStats(0);
        h1_multiplicity_layer[i]->Draw();
        h1_multiplicity_layer[i]->SetLineColor(kBlack);
        h1_multiplicity_layer[i]->SetFillColor(kViolet+4);
        
        lisaFold->Add(h1_multiplicity_layer[i]);
    }
    lisaFold->Add(c_multiplicity_layer);


    //get numbers of layer and detectors
    layer_number = lisa_config->NLayers();
    det_number = lisa_config->NDetectors();

    //:::::::::::::E N E R G Y:::::::::::::::::
    c_energy_layer_ch.resize(layer_number);
    h1_energy_layer_ch.resize(layer_number);

    std::cout<<layer_number<<std::endl;

    //:::::::::::Energy canvas for layer 0
    c_energy_layer0 = new TCanvas("c_energy_layer0","c_energy_layer0", 650,350);
    c_energy_layer0->SetTitle("Layer 0 - Energy");

    h1_energy_layer0 = new TH1F(Form("h1_energy_layer0"),"Tokyo",400, 0, 250000);            
    h1_energy_layer0->GetXaxis()->SetTitle("Energy [a.u.]");
    h1_energy_layer0->Draw();
    h1_energy_layer0->SetStats(0);
    h1_energy_layer0->SetLineColor(kBlack);
    h1_energy_layer0->SetFillColor(kViolet+4);
    
    lisaFold->Add(h1_energy_layer0);
    lisaFold->Add(c_energy_layer0);
 
    //:::::::::::Energy canvas for layer 1 and 2
    //define name of detectors
    std::string det_names[layer_number][2][2] = {
    {{"Quito","Caracas"},{"Reykjavik","Amsterdam"}}, //Eris (Layer 1)
    {{"Novi Sad","Havana"},{"Dublin","Sucre"}} //Sparrow (Layer2)
    };
    
    c_energy_layer_ch.resize(layer_number);
    h1_energy_layer_ch.resize(layer_number);

    for (int z = 1; z < layer_number; z++)
    {
        h1_energy_layer_ch[z].resize(2);
        c_energy_layer_ch[z] = new TCanvas(Form("c_energy_layer_%d",z),Form("c_energy_layer_%d",z), 650,350);
        c_energy_layer_ch[z]->SetTitle(Form("Layer %d - Energy",z));
        c_energy_layer_ch[z]->Divide(2,2);     

        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {       
                h1_energy_layer_ch[z][i].resize(2);

                if (i == 0 && j == 0){
                    c_energy_layer_ch[z]->cd(3);  
                    TString histTitle = Form("Detector %d%d%d - %s",z,i,j,det_names[z][i][j].c_str()); 
                    TString histName = Form("h1_energy_layer_%d_ch_%d%d", z, i, j);
                    h1_energy_layer_ch[z][i][j] = new TH1F(histName, histTitle, 400, 0, 250000); 

                } else if ( i == 0 && j == 1){
                    c_energy_layer_ch[z]->cd(1);
                    TString histTitle =  Form("Detector %d%d%d - %s",z,i,j,det_names[z][i][j].c_str());
                    TString histName = Form("h1_energy_layer_%d_ch_%d%d", z, i, j);
                    h1_energy_layer_ch[z][i][j] = new TH1F(histName, histTitle, 400, 0, 250000); 

                } else if ( i == 1 && j == 0){
                    c_energy_layer_ch[z]->cd(4);
                    TString histTitle =  Form("Detector %d%d%d - %s",z,i,j,det_names[z][i][j].c_str());
                    TString histName = Form("h1_energy_layer_%d_ch_%d%d", z, i, j);
                    h1_energy_layer_ch[z][i][j] = new TH1F(histName, histTitle, 400, 0, 250000); 

                } else if ( i == 1 && j == 1){
                    c_energy_layer_ch[z]->cd(2);
                    TString histTitle =  Form("Detector %d%d%d - %s",z,i,j,det_names[z][i][j].c_str());
                    TString histName = Form("h1_energy_layer_%d_ch_%d%d", z, i, j);
                    h1_energy_layer_ch[z][i][j] = new TH1F(histName, histTitle, 400, 0, 250000);
                }
            
                //TString histName = Form("h1_energy_layer_%d_ch_%d%d", z, i, j);
                //h1_energy_layer_ch[z][i][j] = new TH1F(histName, histTitle, 400, 0, 250000);
                h1_energy_layer_ch[z][i][j]->GetXaxis()->SetTitle("Energy [a.u.]");
                h1_energy_layer_ch[z][i][j]->SetStats(0);
                h1_energy_layer_ch[z][i][j]->SetLineColor(kBlack);
                h1_energy_layer_ch[z][i][j]->SetFillColor(kViolet+4);

                h1_energy_layer_ch[z][i][j]->Draw();
                lisaFold->Add(h1_energy_layer_ch[z][i][j]);
            }
        }
        lisaFold->Add(c_energy_layer_ch[z]);
    }

                    /*
                h1_energy_layer_ch[z][i].resize(2);
                h1_energy_layer_ch[z][i][j] = new TH1F(Form("h1_energy_layer_%d_ch_%d%d",z,i,j),"title",400, 0, 250000);  
                h1_energy_layer_ch[z][i][j]->GetXaxis()->SetTitle("Energy [a.u.]");
                h1_energy_layer_ch[z][i][j]->Draw();
                h1_energy_layer_ch[z][i][j]->SetStats(0);
                h1_energy_layer_ch[z][i][j]->SetLineColor(kBlack);
                h1_energy_layer_ch[z][i][j]->SetFillColor(kViolet+4);
                */

/*
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        
        c_energy_layer_ch[i] = new TCanvas(Form("c_energy_layer_%d",i),Form("c_energy_layer_%d",i), 650,350);
        c_energy_layer_ch[i]->SetTitle(Form("Layer %d - Energy",i));

        c_energy_layer_ch[i]->Divide(2,2); 

        for(int j = 0; j < 4; j++)
        {
            c_energy_layer_ch[i]->cd(j+1);
            h1_energy_layer_ch[i].resize(4);
            //put histo in each canvas per layer
            h1_energy_layer_ch[i][j] = new TH1F(Form("h1_energy_layer_%d_ch_%d",i,j),
                                                Form("Det %d%d%d - %s",i, (j % 2 == 0 ? 0 : 1), (j < 2 ? 1 : 0), det_names[i-1][j/2][j%2].c_str()),
                                                400, 0, 250000);            
            h1_energy_layer_ch[i][j]->GetXaxis()->SetTitle("Energy [a.u.]");
            h1_energy_layer_ch[i][j]->Draw();
            h1_energy_layer_ch[i][j]->SetStats(0);
            h1_energy_layer_ch[i][j]->SetLineColor(kBlack);
            h1_energy_layer_ch[i][j]->SetFillColor(kViolet+4);
            
            lisaFold->Add(h1_energy_layer_ch[i][j]);
        }
        
        lisaFold->Add(c_energy_layer_ch[i]);

    }
*/
    //:::::::::::::T R A C E S:::::::::::::::::
    c_traces_layer_ch.resize(layer_number);
    h2_traces_layer_ch.resize(layer_number);

    //:::::::::::Traces canvas for layer 0
    c_traces_layer0 = new TCanvas("c_traces_layer0","c_traces_layer0", 650,350);
    c_traces_layer0->SetTitle("Layer 0 - Traces");

    h2_traces_layer0 = new TH2F("h2_traces_layer0","Tokyo",100, 0,20,100,8000,8500);            
    h2_traces_layer0->GetXaxis()->SetTitle("Time [ns]");
    h2_traces_layer0->GetYaxis()->SetTitle("ADC [a.u.]");
    h2_traces_layer0->Draw();
    h2_traces_layer0->SetStats(0);
    h2_traces_layer0->SetLineColor(kBlack);
    h2_traces_layer0->SetFillColor(kViolet+4);
    
    lisaFold->Add(h2_traces_layer0);
    lisaFold->Add(c_traces_layer0);

    //:::::::::::Traces canvas for layer 1 and 2   
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        
        c_traces_layer_ch[i] = new TCanvas(Form("c_traces_layer_%d",i),Form("c_traces_layer_%d",i), 650,350);
        c_traces_layer_ch[i]->SetTitle(Form("Layer %d - Traces",i));

        c_traces_layer_ch[i]->Divide(2,2); 

        for(int j = 0; j < 4; j++)
        {
            c_traces_layer_ch[i]->cd(j+1);
            h2_traces_layer_ch[i].resize(4);
            //put histo in each canvas per layer
            h2_traces_layer_ch[i][j] = new TH2F(Form("h2_traces_layer_%d_ch_%d",i,j),
                                                Form("Det %d%d%d - %s",i, (j % 2 == 0 ? 0 : 1), (j < 2 ? 1 : 0), det_names[i-1][j/2][j%2].c_str()),
                                                100, 0,20,100,8000,8500);            
            h2_traces_layer_ch[i][j]->GetXaxis()->SetTitle("Time [us]");
            h2_traces_layer_ch[i][j]->GetYaxis()->SetTitle("ADC [a.u.]");
            h2_traces_layer_ch[i][j]->Draw();
            h2_traces_layer_ch[i][j]->SetStats(0);
            h2_traces_layer_ch[i][j]->SetLineColor(kBlack);
            h2_traces_layer_ch[i][j]->SetFillColor(kViolet+4);
            h2_traces_layer_ch[i][j]->Draw("HIST L P");
            
            lisaFold->Add(h2_traces_layer_ch[i][j]);
        }
        
        lisaFold->Add(c_traces_layer_ch[i]);

    }

    run->GetHttpServer()->RegisterCommand("Reset_Lisa_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void LisaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    //fh1_SumTime->Reset();
}

void LisaOnlineSpectra::Exec(Option_t* option)
{   

    if (fHitLisa && fHitLisa->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitLisa->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            LisaCalData* hit = (LisaCalData*)fHitLisa->At(ihit);
            if (!hit)
                continue;

            //:::::::::::Channel ID

    
            //:::::::::::Multiplicity
            //std::vector<uint32_t> M = hit->GetMultiplicity(); 
            //h1_multiplicity->Fill(M);

            //get stuff looping over M
            //:::::::::::Energy
            std::vector<uint32_t> ch_energy = hit->GetRawEnergy(); 

/*
            for (int index = 0; index < M[0]; index++)
            {
                h1_energy_layer_ch->Fill(ch_energy[index]);
            }
*/
            //:::::::::::Traces           
            //std::vector<uint32_t> traces = hit->GetTraces();
            //std::cout << "trace size:" << traces.size() << "mult: " << M << std::endl;
            //std::vector<uint32_t> tracesI = hit->GetTracesI();
            //int traceLenght = traces.size();

            /*
            h2_traces->Reset();
            for (int index = 0; index < M[0] ; index++)
            {
                uint32_t traceL = traces.size()/M[0];
                for (int i = 0; i < traceL ; i++)
                {
                    h2_traces->Fill(i*(0.01),traces[traceL*index + i]);
                }
            }
            */

        }
    }

    fNEvents += 1;
}

void LisaOnlineSpectra::FinishEvent()
{
    if (fHitLisa)
    {
        fHitLisa->Clear();
    }
}

void LisaOnlineSpectra::FinishTask()
{
    if (fHitLisa)
    {
        //fh1_SumTime->Write();
    }
}

ClassImp(LisaOnlineSpectra)
