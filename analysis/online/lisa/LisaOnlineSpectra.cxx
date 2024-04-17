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

    /*
    //:::::::::::Channel IDs
    h1_channelID = new TH1I("h1_channelID","LISA Channel IDs",16,0,16);
    h1_channelID->GetXaxis()->SetTitle("ChID Fired");
    lisaFold->Add(h1_channelID);
    */

    //:::::::::::Multiplicity
    h1_multiplicity = new TH1I("h1_multiplicity","LISA Multiplicity",8,0,8); //for 3 layer 2x2 + 1
    h1_multiplicity->GetXaxis()->SetTitle("Multiplicity");
    h1_multiplicity->SetStats(0);
    lisaFold->Add(h1_multiplicity);


    //:::::::::::::Energy per Layer
    //get numbers of layer and detectors
    layer_number = lisa_config->NLayers();
    det_number = lisa_config->NDetectors();
    c_energy_layer_ch.resize(layer_number);
    h1_energy_layer_ch.resize(layer_number);
    c_traces_layer_ch.resize(layer_number);
    h2_traces_layer_ch.resize(layer_number);

    std::cout<<layer_number<<std::endl;
 
    //:::::::::::Energy canvas for layer 1 and 2
    //define name of detectors
    std::string det_names[layer_number][2][2] = {
    {{"Quito","Caracas"},{"Reykjavik","Amsterdam"}}, //Eris (Layer 1)
    {{"Novi Sad","Havana"},{"Dublin","Sucre"}} //Sparrow (Layer2)
    };
    
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        
        c_energy_layer_ch[i] = new TCanvas(Form("c_energy_layer_%d",i),Form("c_energy_layer_%d",i), 650,350);
        c_energy_layer_ch[i]->SetTitle(Form("Layer %d - Energy",i));

        c_energy_layer_ch[i]->Divide(2,2); 

        //h1_energy_layer_ch = new TH1F*[4];
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
            h1_energy_layer_ch[i][j]->SetLineColor(kBlack);
            h1_energy_layer_ch[i][j]->SetFillColor(kViolet+4);
            
            lisaFold->Add(h1_energy_layer_ch[i][j]);
        }
        
        lisaFold->Add(c_energy_layer_ch[i]);

    }

     //:::::::::::Traces canvas for layer 1 and 2   
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        
        c_traces_layer_ch[i] = new TCanvas(Form("c_traces_layer_%d",i),Form("c_traces_layer_%d",i), 650,350);
        c_traces_layer_ch[i]->SetTitle(Form("Layer %d - Traces",i));

        c_traces_layer_ch[i]->Divide(2,2); 

        //h1_energy_layer_ch = new TH1F*[4];
        for(int j = 0; j < 4; j++)
        {
            c_traces_layer_ch[i]->cd(j+1);
            h2_traces_layer_ch[i].resize(4);
            //put histo in each canvas per layer
            h2_traces_layer_ch[i][j] = new TH2F(Form("h1_traces_layer_%d_ch_%d",i,j),
                                                Form("Det %d%d%d - %s",i, (j % 2 == 0 ? 0 : 1), (j < 2 ? 1 : 0), det_names[i-1][j/2][j%2].c_str()),
                                                100, 0,20,100,8000,8500);            
            h2_traces_layer_ch[i][j]->GetXaxis()->SetTitle("Time [us]");
            h2_traces_layer_ch[i][j]->GetYaxis()->SetTitle("ADC [a.u.]");
            h2_traces_layer_ch[i][j]->Draw();
            h2_traces_layer_ch[i][j]->SetLineColor(kBlack);
            h2_traces_layer_ch[i][j]->SetFillColor(kViolet+4);
            h2_traces_layer_ch[i][j]->Draw("HIST L P");
            
            lisaFold->Add(h2_traces_layer_ch[i][j]);
        }
        
        lisaFold->Add(c_traces_layer_ch[i]);

    }
    /*
    //::::::::::::Traces
    c_h2_traces = new TCanvas("c_h2_traces","Traces LISA",650,350);
    h2_traces = new TH2F("h2_traces", "Traces", 100, 0,20,100,8000,8500);
    h2_traces->GetXaxis()->SetTitle("Time[us]");
    h2_traces->GetYaxis()->SetTitle("ADC [a.u.]");
    h2_traces->SetMarkerColor(kViolet+4);
    h2_traces->SetMarkerSize(20);
    //h2_traces->SetFillColor(kRed-6);
    h2_traces->Draw("HIST L P");
    //c_h2_traces->cd(0);
    
    //lisaFold->Add(h2_traces);
    //lisaFold->Add(c_h2_traces);
    */

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
            LisaData* hit = (LisaData*)fHitLisa->At(ihit);
            if (!hit)
                continue;

            //:::::::::::Channel ID

    
            //:::::::::::Multiplicity
            std::vector<uint32_t> M = hit->GetMultiplicity(); 
            //h1_multiplicity->Fill(M);

            //get stuff looping over M
            //:::::::::::Energy
            std::vector<uint32_t> ch_energy = hit->GetEnergy(); 

/*
            for (int index = 0; index < M[0]; index++)
            {
                h1_energy->Fill(ch_energy[index]);
            }
*/
            //:::::::::::Traces           
            std::vector<uint32_t> traces = hit->GetTraces();
            //std::cout << "trace size:" << traces.size() << "mult: " << M << std::endl;
            std::vector<uint32_t> tracesI = hit->GetTracesI();
            //int traceLenght = traces.size();

            h2_traces->Reset();
            for (int index = 0; index < M[0] ; index++)
            {
                uint32_t traceL = traces.size()/M[0];
                for (int i = 0; i < traceL ; i++)
                {
                    h2_traces->Fill(i*(0.01),traces[traceL*index + i]);
                }
            }

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
