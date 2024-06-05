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
#include "TGraph.h"
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
    num_layers = lisa_config->NLayers();

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
    //:::::::::::Total
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

    //:::::::::Layer
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



    //:::::::::::H I T  P A T T E R N - by grid ::::::::::::::::::
    dir_stats->cd();
    c_hitpattern_grid = new TCanvas("c_hitpattern_grid", "Hit Pattern Grid", 650, 350);
    c_hitpattern_grid->Divide(layer_number-1);
    h2_hitpattern_grid.resize(layer_number-1);
    //c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number-1; i++)
    {   

        c_hitpattern_grid->cd(i+1);
        h2_hitpattern_grid[i] = new TH2F(Form("h2_hitpattern_grid_layer_%i", i), Form("Hit Pattern Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_hitpattern_grid[i]->SetStats(0);
        h2_hitpattern_grid[i]->Draw("colz");
        h2_hitpattern_grid[i]->GetXaxis()->SetTitle(Form("Hit Pattern Layer %i",i+1));
        h2_hitpattern_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetXaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->SetMinimum(1);
        h2_hitpattern_grid[i]->SetContour(100);
        //gPad->SetLogz();
        
    }
    
    c_hitpattern_grid->cd();
    dir_stats->Append(c_hitpattern_grid);


    //:::::::::::P I L E   U P::::::::::::
    dir_stats->cd();
    c_pileup_grid = new TCanvas("c_pileup_grid", "Pileup Grid", 650, 350);
    c_pileup_grid->Divide(layer_number-1);
    h2_pileup_grid.resize(layer_number-1);
    //c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number-1; i++)
    {   

        c_pileup_grid->cd(i+1);
        h2_pileup_grid[i] = new TH2F(Form("h2_pileup_grid_layer_%i", i), Form("Pile Up Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_pileup_grid[i]->SetStats(0);
        h2_pileup_grid[i]->Draw("COLZ");
        h2_pileup_grid[i]->GetXaxis()->SetTitle(Form("Pile Up Layer %i",i+1));
        h2_pileup_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetXaxis()->SetTickLength(0);
        h2_pileup_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetYaxis()->SetTickLength(0);
        h2_pileup_grid[i]->SetMinimum(1);
        //h2_pileup_grid[i]->SetContour(100);
        //gPad->SetLogz();
        
    }
    
    c_pileup_grid->cd();
    dir_stats->Append(c_pileup_grid);
    

    //:::::::::::O V E R   F L O W:::::::::::
    dir_stats->cd();
    c_overflow_grid = new TCanvas("c_overflow_grid", "Over Flow Grid", 650, 350);
    c_overflow_grid->Divide(layer_number-1);
    h2_overflow_grid.resize(layer_number-1);

    for (int i = 0; i < layer_number-1; i++)
    {   

        c_overflow_grid->cd(i+1);
        h2_overflow_grid[i] = new TH2F(Form("h2_overflow_grid_layer_%i", i), Form("Over Flow Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_overflow_grid[i]->SetStats(0);
        h2_overflow_grid[i]->Draw("COLZ");
        h2_overflow_grid[i]->GetXaxis()->SetTitle(Form("Over Flow Layer %i",i+1));
        h2_overflow_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetXaxis()->SetTickLength(0);
        h2_overflow_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetYaxis()->SetTickLength(0);
        h2_overflow_grid[i]->SetMinimum(1);
        //h2_pileup_grid[i]->SetContour(100);
        //gPad->SetLogz();
        
    }
    
    c_overflow_grid->cd();
    dir_stats->Append(c_overflow_grid);


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

    //::::::::::Energy for now special case layer 0
    c_energy_layer_ch[0] = new TCanvas("c_energy_layer_ch0", "Tokyo layer", 650, 350);
    h1_energy_layer_ch[0].resize(1);
    h1_energy_layer_ch[0][0].resize(1);
    h1_energy_layer_ch[0][0][0] = new TH1F("tokyo", "Tokyo", 400, 0, 250000);
    h1_energy_layer_ch[0][0][0]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
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

                h1_energy_layer_ch[i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i", city.c_str(), i, j, k), city.c_str(), 900, 600000, 900000);
                h1_energy_layer_ch[i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
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

    //::::::::::: Sum Energy Layer 1 vs Sum Energy Layer 2
    dir_energy->cd();
    c_energy_layer1_vs_layer2 = new TCanvas("c_energy_layer1_vs_layer2","c_energy_layer1_vs_layer2", 650,350);
    h2_energy_layer1_vs_layer2 = new TH2F("h2_energy_layer1_vs_layer2", "E(Layer 1) vs E(Layer 2)", 2000, 2680000, 2710000, 2000, 2735000, 2750000); //modify limit so you change it only once
    h2_energy_layer1_vs_layer2->SetStats(0);
    h2_energy_layer1_vs_layer2->Draw("colz");
    h2_energy_layer1_vs_layer2->GetXaxis()->SetTitle(Form("Energy - Layer 2 [a.u]"));
    h2_energy_layer1_vs_layer2->GetYaxis()->SetTitle(Form("Energy - Layer 1 [a.u]"));
    gPad->SetLogz();
    dir_energy->Append(c_energy_layer1_vs_layer2);

    //::::::::::: E N E R G Y  VS  T I M E::::::::::::
    dir_energy->cd();
    c_energy_layer_vs_time = new TCanvas("c_energy_layer1_vs_wr","c_energy_layer1_vs_wr", 650,350);
    c_energy_layer_vs_time->Divide(1,3);
    hG_energy_layer_vs_time.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {
        c_energy_layer_vs_time->cd(i+1);
        hG_energy_layer_vs_time[i] = new TGraph(1);
        hG_energy_layer_vs_time[i]->SetName(Form("hG_energy_layer%i_vs_time",i));
        hG_energy_layer_vs_time[i]->SetTitle(Form("E(Layer %i) vs WR",i));
        hG_energy_layer_vs_time[i]->GetXaxis()->SetTimeDisplay(1);
        hG_energy_layer_vs_time[i]->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
        hG_energy_layer_vs_time[i]->GetXaxis()->SetTimeOffset(0, "local");
        hG_energy_layer_vs_time[i]->GetYaxis()->SetTitle(Form("Energy Layer %i",i));
        hG_energy_layer_vs_time[i]->GetXaxis()->SetTitle("WR Time [Y-M-D H:M]");
        hG_energy_layer_vs_time[i]->SetMarkerColor(kBlack);
        hG_energy_layer_vs_time[i]->SetMarkerStyle(20);
        hG_energy_layer_vs_time[i]->SetLineColor(kBlue);
        hG_energy_layer_vs_time[i]->SetLineWidth(2);
        hG_energy_layer_vs_time[i]->GetXaxis()->SetNdivisions(-4);
        hG_energy_layer_vs_time[i]->Draw();

    }
    
    c_energy_layer_vs_time->cd(0);
    dir_energy->Append(c_energy_layer_vs_time);
     

    //::::::::::: Each Energy Layer vs Time

    //::::::::::: Sum Energy Layers vs Time

    


    //:::::::::::::T R A C E S:::::::::::::::::
    dir_traces->cd();

    c_traces_layer_ch.resize(layer_number);
    h1_traces_layer_ch.resize(layer_number);

    //::::::::::::Traces for layer 0
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
    std::vector<uint32_t> sum_energy_layer;
    sum_energy_layer.resize(layer_number);

    //c4LOG(info, "Comment to slow down program for testing");
    for (auto const & lisaCalItem : *lisaCalArray)
    {
        //::::::: Retrieve Data ::::::::::::::
        int layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        uint32_t energy = lisaCalItem.Get_energy();
        std::vector<uint16_t> trace = lisaCalItem.Get_trace();
        int pileup = lisaCalItem.Get_pileup();
        int overflow = lisaCalItem.Get_overflow();
        
        
        //::::::::F I L L   H I S T O S:::::::
        //:::::::: H I T  P A T T E R N ::::::::::
        //:::::::::Layer
        int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        h1_hitpattern_layer[layer]->Fill(hp_bin);
        //:::::::::Total
        int hp_total_bin;
        if (layer != 0) hp_total_bin = layer * xmax * ymax + hp_bin - 3; // -3 is a fudge for uneven layers, temporary
        else hp_total_bin = 0;
        h1_hitpattern_total->Fill(hp_total_bin);
        //::::::::::By grid
        if (layer != 0) h2_hitpattern_grid[layer-1]->Fill(xpos,ypos);


        //:::::::::P I L E   UP:::::::::::::
        //::::::::::By grid
        if (pileup != 0) if (layer != 0) h2_pileup_grid[layer-1]->Fill(xpos,ypos);

        //:::::::::O V E R  F L O W:::::::::::::
        //::::::::::By grid
        if (overflow != 0) if (layer != 0) h2_overflow_grid[layer-1]->Fill(xpos,ypos);
        
        //:::::::: Count Multiplicity ::::::::
        multiplicity[layer]++;
        total_multiplicity++;

        //::::::::::counter for time display of energy point
        wr_time = lisaCalItem.Get_wr_t();
        //counter++;
        //c4LOG(info, "counter : "<< counter);
        //c4LOG(info, "pileup : "<< pileup<< "overflow : " << overflow );

        //::::::::: E N E R G Y :::::::::::::::
        h1_energy_layer_ch[layer][xpos][ypos]->Fill(energy);

        //::::::::Sum Energy
        
        sum_energy_layer[layer] += energy;
            
        
        //c4LOG(info, "sum_energy layer 1: "<< sum_energy_layer[1]);
        //c4LOG(info, "sum_energy layer 2: "<< sum_energy_layer[2]);
    

        //c4LOG(info, "num layer: " << num_layers << " x max: " << xmax << " ymax: " << ymax);

        //::::::::: Fill Traces ::::::::::::::
        h1_traces_layer_ch[layer][xpos][ypos]->Reset();
        for (int i = 0; i < trace.size(); i++)
        {
            h1_traces_layer_ch[layer][xpos][ypos]->SetBinContent(i, trace[i]);
            //c4LOG(info, "layer: " << layer << " x max: " << xmax << " ymax: " << ymax);

        }

    }

    //::::::: Fill Multiplicity ::::::::::
    for (int i = 0; i < layer_number; i++) h1_multiplicity_layer[i]->Fill(multiplicity[i]);
    h1_multiplicity->Fill(total_multiplicity);

    //:::::::Fill Sum Energy::::::::::
    h2_energy_layer1_vs_layer2->Fill(sum_energy_layer[2],sum_energy_layer[1]);

    //c4LOG(info, "counter again : "<< counter);
    //:::::::Energy vs Time
    //time_t rawtime;
    //time(&rawtime);

    int wr_r = round(wr_time/1000000000);

    if (fNEvents % 1000 == 0 && sum_energy_layer[1] > 0) 
    {
        for (int i = 0; i < layer_number; i++) hG_energy_layer_vs_time[i]->SetPoint(en_count, wr_r, sum_energy_layer[i]);
        //c4LOG(info, "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
        //c4LOG(info, " wr: " << wr_r << " wr tot "<< wr_time);
        en_count++;

    } 
    

    fNEvents += 1;
}

void LisaOnlineSpectra::FinishEvent()
{

}

void LisaOnlineSpectra::FinishTask()
{

}

ClassImp(LisaOnlineSpectra)
