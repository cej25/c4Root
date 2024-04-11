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

LisaOnlineSpectra::LisaOnlineSpectra()
{
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

    //:::::::::::Hit Pattern
    h1_hitpattern = new TH1I("h1_hitpattern","LISA Hit Pattern",16,0,16);
    h1_hitpattern->GetXaxis()->SetTitle("ChID Fired");
    lisaFold->Add(h1_hitpattern);

    //:::::::::::Multiplicity
    h1_multiplicity = new TH1I("h1_multiplicity","LISA Multiplicity",8,0,8); //for 3 layer 2x2 + 1
    h1_multiplicity->GetXaxis()->SetTitle("Multiplicity");
    h1_multiplicity->SetStats(0);
    lisaFold->Add(h1_multiplicity);



    //:::::::::::Energy Layer 1
    /*
    c_energy_layer1  = new TCanvas("c_energy_layer1","Energy - Layer 1",650,350);
    c_energy_layer1->Divide(2,2);
    h1_energy_layer1 = new TH1F*[4];
    for (int ihist = 0; ihist < 4; ihist++){ //this should be fine for 241test, but has to be integrated with mapping for experiment
        c_energy_layer1->cd(ihist+1);
        h1_energy_layer1[ihist] = new TH1F(Form("h1_energy_%d",ihist),Form("Layer 1 - %d",ihist),400,0,250000);
        h1_energy_layer1[ihist]->GetXaxis()->SetTitle("Energy (a.u.)");
        h1_energy_laye1[ihist]->Draw();
        h1_energy_layer1[ihist]->SetOption("logy");
        lisaFold->Add(h1_energy_layer[ihist]);
    }
    c_energy_layer1->cd(0);
    */

    h1_energy = new TH1F("h1_energy", "LISA Energy", 400,0,250000); //in case of data from 241Am
    h1_energy->SetOption("logy");
    h1_energy->SetLineColor(kBlack);
    h1_energy->SetFillColor(kBlue);
    lisaFold->Add(h1_energy);

    //::::::::::::Traces
    h2_traces = new TH2F("h2_traces", "Traces", 400, 0,2000,100,6000,9000);
    h2_traces->SetOption("colz");
    lisaFold->Add(h2_traces);


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
            //:::::::::::Hit Pattern
            std::vector<int> hit_pattern = hit->GetHitPattern(); 
            for (int n = 0; n< hit_pattern.size(); n++ )
            {
                h1_hitpattern->Fill(hit_pattern[n]);
            }
            //:::::::::::Multiplicity
            uint32_t M = hit->GetMultiplicity(); 
            h1_multiplicity->Fill(M);

            //get stuff looping over M
            //:::::::::::Energy
            std::vector<uint32_t> ch_energy = hit->GetEnergy(); 
            for (int index = 0; index < M; index++)
            {
                h1_energy->Fill(ch_energy[index]);
            }
            //:::::::::::Traces           
            std::vector<uint32_t> traces = hit->GetTraces();
            std::cout << "trace size:" << traces.size() << "mult: " << M << std::endl;
            std::vector<uint32_t> tracesI = hit->GetTracesI();
            //int traceLenght = traces.size();

            for (int index = 0; index < M ; index++)
            {
                uint32_t traceLength = traces.size()/M;
                for (int i = 0; i < traceLength ; i++)
                {
                    h2_traces->Fill(i,traces[traceLength*index + i]);
                    //h2_traces->SetBinContent(i,traces[traceLength*index + i],1); 
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
