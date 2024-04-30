// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaOnlineSpectra.h"
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
    // , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    
}

LisaOnlineSpectra::~LisaOnlineSpectra()
{
    c4LOG(info, "");
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

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");

    layer_number = lisa_config->NLayers();
    det_number = lisa_config->NDetectors();
    auto const & detector_mapping = lisa_config->Mapping();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_lisa = new TDirectory("LISA", "LISA", "", 0);
    mgr->Register("LISA", "LISA Directory", dir_lisa, false); // allow other tasks to access directory.
    histograms->Add(dir_lisa);

    dir_lisa->cd();
    dir_stats = dir_lisa->mkdir("Stats");
    dir_energy = dir_lisa->mkdir("Energy");
    dir_traces = dir_lisa->mkdir("Traces");
    
    dir_music = new TDirectory("MUSIC", "MUSIC", "", 0);
    mgr->Register("MUSIC", "MUSIC Directory", dir_music, false);
    histograms->Add(dir_music);

    dir_correlations = new TDirectory("Correlations", "Correlations", "", 0);
    mgr->Register("Correlations", "Correlations Directory", dir_correlations, false);
    histograms->Add(dir_correlations);

    // layer names: Tokyo, Eris, Sparrow
  
    //:::::::::::H I T  P A T T E R N S:::::::::::::::
    dir_stats->cd();

    h1_hitpattern_total = new TH1I("h1_hitpattern_total", "Hit Pattern", det_number, 0, det_number);
    for (auto & detector : detector_mapping)
    {
        int l = detector.second.first.first;
        city = detector.second.first.second;
        int x = detector.second.second.first; 
        int y = detector.second.second.second;
        
        // special case for weird layer
        if (l != 0) h1_hitpattern_total->GetXaxis()->SetBinLabel(l * xmax * ymax + (ymax-(y+1))*xmax + x + 1 - 3, city.c_str());
        else h1_hitpattern_total->GetXaxis()->SetBinLabel(1, city.c_str());
    }

    c_hitpattern_layer = new TCanvas("c_hitpattern_layer", "Hit Pattern by Layer", 650, 350);
    c_hitpattern_layer->Divide(2, (layer_number+1)/2);
    h1_hitpattern_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_hitpattern_layer->cd(i+1);
        h1_hitpattern_layer[i] = new TH1I(Form("h1_hitpattern_layer_%i", i), Form("Hit Pattern - Layer: %i", i), xmax * ymax, 0, xmax * ymax);
        h1_hitpattern_layer[i]->SetStats(0);
        h1_hitpattern_layer[i]->Draw();

        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            for (auto & detector : detector_mapping)
            {
                int x = detector.second.second.first; 
                int y = detector.second.second.second;
                if (detector.second.first.first == i && ((ymax-(y+1))*xmax + x) == j)
                {
                    city = detector.second.first.second;
                    break;
                }
            }
            h1_hitpattern_layer[i]->GetXaxis()->SetBinLabel(j+1, city.c_str());
        }
       
    }
    c_hitpattern_layer->cd();
    dir_stats->Append(c_hitpattern_layer);

    //:::::::::::M U L T I P L I C I T Y:::::::::::::::
    h1_multiplicity = new TH1I("h1_multiplicity", "Total Multiplicity", det_number, 0, det_number);
    
    c_multiplicity_layer = new TCanvas("c_multiplicity_layer", "Multiplicty by Layer", 650, 350);
    c_multiplicity_layer->Divide(2, (layer_number + 1)/2);
    h1_multiplicity_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_multiplicity_layer->cd(i+1);
        h1_multiplicity_layer[i] = new TH1I("", "", xmax * ymax, 0, xmax * ymax);
        h1_multiplicity_layer[i]->Draw();
    }
    c_multiplicity_layer->cd(0);
    dir_stats->Append(c_multiplicity_layer);


    //:::::::::::::E N E R G Y:::::::::::::::::
    dir_energy->cd();

    c_energy_layer_ch.resize(layer_number);
    h1_energy_layer_ch.resize(layer_number);

    // for now special case layer 0, maybe we can generalise though
    c_energy_layer_ch[0] = new TCanvas("c_energy_layer_ch0", "Tokyo layer", 650, 350);
    h1_energy_layer_ch[0].resize(1);
    h1_energy_layer_ch[0][0].resize(1);
    h1_energy_layer_ch[0][0][0] = new TH1F("tokyo", "Tokyo", 400, 0, 250000);
    h1_energy_layer_ch[0][0][0]->GetXaxis()->SetTitle("Energy [a.u.]");
    //h1_energy_layer_ch[0][0][0]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
    //h1_energy_layer_ch[0][0][0]->SetMaximum(lisa_config->AmplitudeMax);
    h1_energy_layer_ch[0][0][0]->SetStats(0);
    h1_energy_layer_ch[0][0][0]->SetLineColor(kBlue+1);
    h1_energy_layer_ch[0][0][0]->SetFillColor(kOrange-3);
    h1_energy_layer_ch[0][0][0]->Draw();
    dir_energy->Append(c_energy_layer_ch[0]);

 
    //:::::::::::Energy canvas for layer 1 and 2
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        c_energy_layer_ch[i] = new TCanvas(Form("c_energy_layer_%d",i),Form("c_energy_layer_%d",i), 650,350);
        c_energy_layer_ch[i]->SetTitle(Form("Layer %d - Energy",i));
        c_energy_layer_ch[i]->Divide(xmax,ymax); 
        h1_energy_layer_ch[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_layer_ch[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                // general formula to place correctly on canvas for x,y coordinates
                c_energy_layer_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
                
                city = "";
                for (auto & detector : detector_mapping)
                {
                    if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }

                h1_energy_layer_ch[i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i", city.c_str(), i, j, k), city.c_str(), 400, 0, 250000);
                h1_energy_layer_ch[i][j][k]->GetXaxis()->SetTitle("Energy [a.u.]");
                //h1_energy_layer_ch[i][j][k]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
                //h1_energy_layer_ch[i][j][k]->SetMaximum(lisa_config->AmplitudeMax);
                h1_energy_layer_ch[i][j][k]->SetStats(0);
                h1_energy_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_energy_layer_ch[i][j][k]->Draw();
            }
        }
        c_energy_layer_ch[i]->cd(0);
        dir_energy->Append(c_energy_layer_ch[i]);

    }


    //:::::::::::::T R A C E S:::::::::::::::::
    dir_traces->cd();

    c_traces_layer_ch.resize(layer_number);
    h1_traces_layer_ch.resize(layer_number);

    // for now special case layer 0, maybe we can generalise though
    c_traces_layer_ch[0] = new TCanvas("c_traces_layer_ch0", "Tokyo layer", 650, 350);
    h1_traces_layer_ch[0].resize(1);
    h1_traces_layer_ch[0][0].resize(1);
    h1_traces_layer_ch[0][0][0] = new TH1F("tokyo", "Tokyo", 2000, 0, 20); // microseconds
    h1_traces_layer_ch[0][0][0]->GetXaxis()->SetTitle("Time [us]");
    h1_traces_layer_ch[0][0][0]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
    h1_traces_layer_ch[0][0][0]->SetMaximum(lisa_config->AmplitudeMax);
    h1_traces_layer_ch[0][0][0]->SetStats(0);
    h1_traces_layer_ch[0][0][0]->SetLineColor(kBlue+1);
    h1_traces_layer_ch[0][0][0]->SetFillColor(kOrange-3);
    h1_traces_layer_ch[0][0][0]->Draw();
    dir_traces->Append(c_traces_layer_ch[0]);

    //:::::::::::Traces canvas for layer 1 and 2   
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        c_traces_layer_ch[i] = new TCanvas(Form("c_traces_layer_%d",i),Form("c_traces_layer_%d",i), 650,350);
        c_traces_layer_ch[i]->SetTitle(Form("Layer %d - Traces",i));
        c_traces_layer_ch[i]->Divide(xmax,ymax); 
        h1_traces_layer_ch[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h1_traces_layer_ch[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                // general formula to place correctly on canvas for x,y coordinates
                c_traces_layer_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
                
                city = "";
                for (auto & detector : detector_mapping)
                {
                    if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }

                h1_traces_layer_ch[i][j][k] = new TH1F(Form("traces_%s_%i_%i_%i", city.c_str(), i, j, k), city.c_str(), 2000, 0, 20);
                h1_traces_layer_ch[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                h1_traces_layer_ch[i][j][k]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
                h1_traces_layer_ch[i][j][k]->SetMaximum(lisa_config->AmplitudeMax);
                h1_traces_layer_ch[i][j][k]->SetStats(0);
                h1_traces_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_traces_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_traces_layer_ch[i][j][k]->Draw();
            }
        }
        c_traces_layer_ch[i]->cd(0);
        dir_traces->Append(c_traces_layer_ch[i]);

    }

    run->GetHttpServer()->RegisterCommand("Reset_Lisa_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void LisaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
}

void LisaOnlineSpectra::Exec(Option_t* option)
{   
    int multiplicity[layer_number] = {0};
    int total_multiplicity = 0;

    c4LOG(info, "Comment to slow down program for testing");
    for (auto const & lisaCalItem : *lisaCalArray)
    {
        //::::::: Retrieve Data ::::::::::::::
        int layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        uint32_t energy = lisaCalItem.Get_energy();
        std::vector<uint16_t> trace = lisaCalItem.Get_trace();
        
        //:::::::: Fill Hit Pattern ::::::::::
        int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        h1_hitpattern_layer[layer]->Fill(hp_bin);
        int hp_total_bin;
        if (layer != 0) hp_total_bin = layer * xmax * ymax + hp_bin - 3; // -3 is a fudge for uneven layers, temporary
        else hp_total_bin = 0;
        h1_hitpattern_total->Fill(hp_total_bin);
        
        //:::::::: Count Multiplicity ::::::::
        multiplicity[layer]++;
        total_multiplicity++;

        //::::::::: Fill Energy :::::::::::::::
        h1_energy_layer_ch[layer][xpos][ypos]->Fill(energy);

        c4LOG(info, "layer: " << layer << " x: " << xpos << " y: " << ypos);

        //::::::::: Fill Traces ::::::::::::::
        h1_traces_layer_ch[layer][xpos][ypos]->Reset();
        for (int i = 0; i < trace.size(); i++)
        {
            h1_traces_layer_ch[layer][xpos][ypos]->SetBinContent(i, trace[i]);
        }

    }

    //::::::: Fill Multiplicity ::::::::::
    for (int i = 0; i < layer_number; i++) h1_multiplicity_layer[i]->Fill(multiplicity[i]);
    h1_multiplicity->Fill(total_multiplicity);

    fNEvents += 1;
}

void LisaOnlineSpectra::FinishEvent()
{

}

void LisaOnlineSpectra::FinishTask()
{

}

ClassImp(LisaOnlineSpectra)
