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
 *                             E.M.Gandolfo                                   *
 *                               17.12.24                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaOnlineSpectraDaq.h"
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
#include <cmath>

LisaOnlineSpectraDaq::LisaOnlineSpectraDaq()  :   LisaOnlineSpectraDaq("LisaOnlineSpectraDaq")
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaOnlineSpectraDaq::LisaOnlineSpectraDaq(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaOnlineSpectraDaq::~LisaOnlineSpectraDaq()
{
    c4LOG(info, "");
}

void LisaOnlineSpectraDaq::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaOnlineSpectraDaq::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // ::: To remove for nearline class
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

    histograms = (TFolder*)mgr->GetObject("Histograms"); //to remove for nearline
    TDirectory::TContext ctx(nullptr); //to remove for nearline

    dir_lisa = new TDirectory("LISA", "LISA", "", 0);
    mgr->Register("LISA", "LISA Directory", dir_lisa, false); // allow other tasks to access directory.
    histograms->Add(dir_lisa); //to remove for nearline

    dir_lisa->cd();
    dir_stats = dir_lisa->mkdir("Stats");
    dir_energy = dir_lisa->mkdir("Energy");
    dir_traces = dir_lisa->mkdir("Traces");
  
    //:::::::::::White Rabbit:::::::::::::::
    dir_stats->cd();

    h1_wr_diff = new TH1I("h1_wr_diff", "WR Difference", lisa_config->bin_wr_diff, lisa_config->min_wr_diff, lisa_config->max_wr_diff);
    h1_wr_diff->GetXaxis()->SetTitle("LISA WR Difference [ns]");
    h1_wr_diff->SetLineColor(kBlack);
    h1_wr_diff->SetFillColor(kRed-3);

    //:::::::::::H I T  P A T T E R N S:::::::::::::::
    //:::::::::::Total
    dir_stats->cd();

    h1_hitpattern_total = new TH1I("h1_hitpattern_total", "Hit Pattern", det_number, 0, det_number);
    for (auto & detector : detector_mapping)
    {
        int x = detector.second.first.second.first;
        int y = detector.second.first.second.second;
        int l_id = detector.second.first.first;
        city = detector.second.second.second.first;

        
        //h1_hitpattern_total->GetXaxis()->SetBinLabel(l * xmax * ymax + (ymax-(y+1))*xmax + x + 1 - 3, city.Data());
    }

    //:::::::::Layer
    c_hitpattern_layer = new TCanvas("c_hitpattern_layer", "Hit Pattern by Layer", 650, 350);
    c_hitpattern_layer->Divide(ceil((layer_number)/2),2, 0.01, 0.01);
    h1_hitpattern_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_hitpattern_layer->cd(i+1);
        h1_hitpattern_layer[i] = new TH1I(Form("h1_hitpattern_layer_%i", i), Form("Hit Pattern - Layer: %i", i), xmax * ymax, 0, xmax * ymax);
        h1_hitpattern_layer[i]->Draw();

        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            for (auto & detector : detector_mapping)
            {
                int x = detector.second.first.second.first;
                int y = detector.second.first.second.second;
                int l_id = detector.second.first.first;
                if (l_id == i + 1 && ((ymax - (y + 1)) * xmax + x) == j)
                {
                    city = detector.second.second.second.first;
                    break;
                }
            }
            h1_hitpattern_layer[i]->GetXaxis()->SetBinLabel(j+1, city.Data());
        }
       
    }
    c_hitpattern_layer->cd();
    dir_stats->Append(c_hitpattern_layer);


    //:::::::::::H I T  P A T T E R N - by grid ::::::::::::::::::
    dir_stats->cd();
    c_hitpattern_grid = new TCanvas("c_hitpattern_grid", "Hit Pattern Grid", 650, 350);
    c_hitpattern_grid->Divide(ceil((layer_number)/2),2, 0.01, 0.01);
    h2_hitpattern_grid.resize(layer_number);
    c_hitpattern_grid->SetLogz();
    c4LOG(info, " before hit pattern layer : " << layer_number );


    for (int i = 0; i < layer_number; i++)
    {   

        c_hitpattern_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_hitpattern_grid[i] = new TH2F(Form("h2_hitpattern_grid_layer_%i", i), Form("Hit Pattern Grid - Layer %i", i), xmax, 0, xmax, ymax, 0, ymax);
        h2_hitpattern_grid[i]->SetStats(0);
        h2_hitpattern_grid[i]->Draw("colz");
        h2_hitpattern_grid[i]->GetXaxis()->SetTitle(Form("Hit Pattern Layer %i",i));
        h2_hitpattern_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetXaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->SetMinimum(1);
        h2_hitpattern_grid[i]->SetContour(100);
        gPad->SetLogz();
        
    }
    
    c_hitpattern_grid->cd();
    dir_stats->Append(c_hitpattern_grid);


    //:::::::::::P I L E   U P::::::::::::
    dir_stats->cd();
    c_pileup_grid = new TCanvas("c_pileup_grid", "Pileup Grid", 650, 350);
    c_pileup_grid->Divide(ceil((layer_number)/2), 2, 0.01, 0.01);
    h2_pileup_grid.resize(layer_number);
    //c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_pileup_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_pileup_grid[i] = new TH2F(Form("h2_pileup_grid_layer_%i", i), Form("Pile Up Grid - Layer %i", i), xmax, 0, xmax, ymax, 0, ymax);
        h2_pileup_grid[i]->SetStats(0);
        h2_pileup_grid[i]->Draw("COLZ");
        h2_pileup_grid[i]->GetXaxis()->SetTitle(Form("Pile Up Layer %i",i));
        h2_pileup_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetXaxis()->SetTickLength(0);
        h2_pileup_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetYaxis()->SetTickLength(0);
        h2_pileup_grid[i]->SetMinimum(1);
        //h2_pileup_grid[i]->SetContour(100);
        gPad->SetLogz();
        
    }
    
    c_pileup_grid->cd();
    dir_stats->Append(c_pileup_grid);
    

    //:::::::::::O V E R   F L O W:::::::::::
    dir_stats->cd();
    c_overflow_grid = new TCanvas("c_overflow_grid", "Over Flow Grid", 650, 350);
    c_overflow_grid->Divide(ceil((layer_number)/2), 2, 0.01, 0.01);
    h2_overflow_grid.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {   

        c_overflow_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_overflow_grid[i] = new TH2F(Form("h2_overflow_grid_layer_%i", i), Form("Over Flow Grid - Layer %i", i), xmax, 0, xmax, ymax, 0, ymax);
        h2_overflow_grid[i]->SetStats(0);
        h2_overflow_grid[i]->Draw("COLZ");
        h2_overflow_grid[i]->GetXaxis()->SetTitle(Form("Over Flow Layer %i",i));
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

    //:::::::::::Total Multiplicity
    // h1_multiplicity = new TH1I("h1_multiplicity", "Total Multiplicity", det_number, 0, det_number+1);
    // h1_multiplicity->SetStats(0);
    
    // //:::::::::::Multiplicity per layer
    // c_multiplicity_layer = new TCanvas("c_multiplicity_layer", "Multiplicty by Layer", 650, 350);
    // c_multiplicity_layer->Divide(layer_number,1);
    // h1_multiplicity_layer.resize(layer_number);
    // for (int i = 0; i < layer_number -1; i++)
    // {
    //     c_multiplicity_layer->cd(i+1);
    //     h1_multiplicity_layer[i] = new TH1I(Form("Multiplicity Layer %i",i), Form("Multiplicity Layer %i",i), xmax * ymax+1, 0, xmax * ymax+1);
    //     h1_multiplicity_layer[i]->SetStats(0);
    //     h1_multiplicity_layer[i]->Draw();
    // }
    // c_multiplicity_layer->cd(0);
    // dir_stats->Append(c_multiplicity_layer);

    //:::::::::::Layer Multiplicity
    h1_layer_multiplicity = new TH1I("h1_layer_multiplicity", "Layer Multiplicity", layer_number, 0, layer_number);
    h1_layer_multiplicity->SetStats(0);

    //:::::::::::::E N E R G Y:::::::::::::::::
    dir_energy->cd();

    c_energy_layer_ch.resize(layer_number);
    h1_energy_layer_ch.resize(layer_number);
 
    //:::::::::::Energy canvas for each layer
    for (int i = 0; i < layer_number; i++) 
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
                    int x = detector.second.first.second.first;
                    int y = detector.second.first.second.second;
                    int l_id = detector.second.first.first;
                    if (l_id == i + 1 && ((ymax - (y + 1)) * xmax + x) == j)
                    {
                        city = detector.second.second.second.first;
                        break;
                    }
                }

                h1_energy_layer_ch[i][j][k] = new TH1F(Form("energy_%i_%i_%i_%s", i, j, k, city.Data()), city.Data(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h1_energy_layer_ch[i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
                //h1_energy_layer_ch[i][j][k]->SetStats(0);
                h1_energy_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_energy_layer_ch[i][j][k]->Draw();
            }
        }
        c_energy_layer_ch[i]->cd(0);
        dir_energy->Append(c_energy_layer_ch[i]);

    }

    //:::::::::::::E N E R G Y     M W D:::::::::::::::::
    dir_energy->cd();

    c_energy_MWD_layer_ch.resize(layer_number);
    h1_energy_MWD_layer_ch.resize(layer_number);
 
    //:::::::::::Energy canvas for each layer
    for (int i = 0; i < layer_number; i++) 
    {
        c_energy_MWD_layer_ch[i] = new TCanvas(Form("c_energy_MWD_layer_%d",i),Form("c_energy_MWD_layer_%d",i), 650,350);
        c_energy_MWD_layer_ch[i]->SetTitle(Form("Layer %d - Energy MWD",i));
        c_energy_MWD_layer_ch[i]->Divide(xmax,ymax); 
        h1_energy_MWD_layer_ch[i].resize(xmax);
        
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_MWD_layer_ch[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                // general formula to place correctly on canvas for x,y coordinates
                c_energy_MWD_layer_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
                
                city = "";
                for (auto & detector : detector_mapping)
                {
                    int x = detector.second.first.second.first;
                    int y = detector.second.first.second.second;
                    int l_id = detector.second.first.first;
                    if (l_id == i + 1 && ((ymax - (y + 1)) * xmax + x) == j)
                    {
                        city = detector.second.second.second.first;
                        break;
                    }
                }

                h1_energy_MWD_layer_ch[i][j][k] = new TH1F(Form("energy_MWD_%i_%i_%i_%s", i, j, k, city.Data()), city.Data(), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
                h1_energy_MWD_layer_ch[i][j][k]->GetXaxis()->SetTitle("E MWD(LISA) [a.u.]");
                //h1_energy_MWD_layer_ch[i][j][k]->SetStats(0);
                h1_energy_MWD_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_MWD_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_energy_MWD_layer_ch[i][j][k]->Draw();
            }
        }
        c_energy_MWD_layer_ch[i]->cd(0);
        dir_energy->Append(c_energy_MWD_layer_ch[i]);

    }
  
    //:::::::::::::T R A C E S:::::::::::::::::
    dir_traces->cd();

    c_traces_layer_ch.resize(layer_number);
    h1_traces_layer_ch.resize(layer_number);
    //:::::::::::Traces canvas for each layer   
    for (int i = 0; i < layer_number; i++) 
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
                    int x = detector.second.first.second.first;
                    int y = detector.second.first.second.second;
                    int l_id = detector.second.first.first;
                    if (l_id == i + 1 && ((ymax - (y + 1)) * xmax + x) == j)
                    {
                        city = detector.second.second.second.first;
                        break;
                    }
                }

                h1_traces_layer_ch[i][j][k] = new TH1F(Form("traces_%i_%i_%i_%s", i, j, k, city.Data()), city.Data(), lisa_config->bin_traces, lisa_config->min_traces, lisa_config->max_traces); 
                h1_traces_layer_ch[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                h1_traces_layer_ch[i][j][k]->SetMinimum(lisa_config->amplitude_min);
                h1_traces_layer_ch[i][j][k]->SetMaximum(lisa_config->amplitude_max);
                h1_traces_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_traces_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_traces_layer_ch[i][j][k]->Draw();
            }
        }
        c_traces_layer_ch[i]->cd(0);
        dir_traces->Append(c_traces_layer_ch[i]);

    }

    run->GetHttpServer()->RegisterCommand("Reset_Lisa_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    c4LOG(info,"Get Name: " << GetName() );

    return kSUCCESS;
}

void LisaOnlineSpectraDaq::Reset_Histo()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    c4LOG(info,"::: Histos Reset on day " <<  ltm->tm_mday << "th," << " at " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec );
    
    //::: Reset WR
    h1_wr_diff->Reset();

    //::: Reset Energy histos
    for (int i = 0; i < layer_number; i++) 
    {
        for (int j = 0; j < xmax; j++)
        {
            for (int z = 0; z < ymax; z++)
            {
                h1_energy_layer_ch[i][j][z]->Reset();
                h1_energy_MWD_layer_ch[i][j][z]->Reset();
            }
        }
    }

    //::: Reset multiplicity
    // for (int i = 0; i < layer_number; i++)
    // {
    //     h1_multiplicity_layer[i]->Reset();
    // }
    h1_layer_multiplicity->Reset();
    //h1_multiplicity->Reset();


    //::: Reset grids for pileup, overflow, hitpattern
    for (int i = 0; i < layer_number; i++)
    {
        h1_hitpattern_layer[i]->Reset();
    }

    for (int i = 0; i < layer_number-1; i++)
    {
        h2_hitpattern_grid[i]->Reset();
        h2_overflow_grid[i]->Reset();
        h2_pileup_grid[i]->Reset();

    }


    //::: Reset Traces
    for (int i = 0; i < layer_number; i++) 
    {
        for (int j = 0; j < xmax; j++)
        {
            for (int k = 0; k < ymax; k++)
            {
                h1_traces_layer_ch[i][j][k]->Reset();
            }
        }
    }
    

}

void LisaOnlineSpectraDaq::Exec(Option_t* option)
{   
    //c4LOG(info, ":::::::beginning exec :::::::: ");
    wr_time = 0;
    int multiplicity[layer_number] = {0};
    int total_multiplicity = 0;
    
    std::vector<uint32_t> sum_energy_layer;
    sum_energy_layer.resize(layer_number);
    int energy_ch[layer_number][xmax][ymax] = {0,0,0};

    //c4LOG(info, "Comment to slow down program for testing");
    for (auto const & lisaCalItem : *lisaCalArray)
    {
        
        //c4LOG(info, ":::::::beginning loop inside exec :::::::: ");
        wr_time = lisaCalItem.Get_wr_t();

        if (lisa_config->wr_enable == true)
        {
            if (wr_time == 0)return; 
        }

        //c4LOG(info, ":::::::beginning loop after return :::::::: ");

        //::::::: Retrieve Data ::::::::::::::
        layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        float energy = lisaCalItem.Get_energy();
        float energy_MWD = lisaCalItem.Get_energy_MWD();
        trace = lisaCalItem.Get_trace_febex();
        int pileup = lisaCalItem.Get_pileup();
        int overflow = lisaCalItem.Get_overflow();
        uint64_t evtno = header->GetEventno();
        //c4LOG(info, " exec layer : " << layer << "layer number : "<< layer_number );
        
        //::::::::F I L L   H I S T O S:::::::
        //:::::::: H I T  P A T T E R N ::::::::::
        //:::::::::Layer
        int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        h1_hitpattern_layer[layer]->Fill(hp_bin);
        //:::::::::Total
        int hp_total_bin;
        hp_total_bin = layer * xmax * ymax + hp_bin - 3; // -3 is a fudge for uneven layers, temporary
        h1_hitpattern_total->Fill(hp_total_bin);
        //::::::::::By grid
        h2_hitpattern_grid[layer]->Fill(xpos,ypos);

        //:::::::::P I L E   UP:::::::::::::
        //::::::::::By grid
        if (pileup != 0) h2_pileup_grid[layer]->Fill(xpos,ypos);

        //:::::::::O V E R  F L O W:::::::::::::
        //::::::::::By grid
        if (overflow != 0) h2_overflow_grid[layer]->Fill(xpos,ypos);
        
        //:::::::: Count Multiplicity ::::::::
        multiplicity[layer]++;
        total_multiplicity++;

        //::::::::::counter for time display of energy point
        
        xp = lisaCalItem.Get_xposition();
        yp = lisaCalItem.Get_yposition();
        //lay = lisaCalItem.Get_layer_id();
        //en = lisaCalItem.Get_energy();
        //counter++;
        //c4LOG(info, "counter : "<< counter);
        //c4LOG(info, "pileup : "<< pileup<< "overflow : " << overflow );

        //::::::::: E N E R G Y :::::::::::::::
        h1_energy_layer_ch[layer][xpos][ypos]->Fill(energy);
        h1_energy_MWD_layer_ch[layer][xpos][ypos]->Fill(energy_MWD);

        //::::::::Sum Energy
        
        
        energy_ch[layer][xpos][ypos] = energy;
        
        //c4LOG(info, "num layer: " << num_layers << " x max: " << xmax << " ymax: " << ymax);

        
        //::::::::: T R A C E S :::::::::

        //::::::::: Fill Traces ::::::::::::::
        h1_traces_layer_ch[layer][xpos][ypos]->Reset();
        for (int i = 0; i < trace.size(); i++)
        {
            h1_traces_layer_ch[layer][xpos][ypos]->SetBinContent(i, trace[i]);
            //c4LOG(info, " Trace Febex : " << trace.size());
            //c4LOG(info, "layer: " << layer << " x max: " << xmax << " ymax: " << ymax);
        }

    }

    //c4LOG(info, "::::::::::END LOOP::::::::::::" << " Layer number :" << layer_number);


    //c4LOG(info, " layer : "<<layer << " multiplicity layer : "<<multiplicity[layer]);
    if ( wr_time == 0 ) return;

    //:::::: WR Time Difference
    if( prev_wr > 0 )
    {
        wr_diff = wr_time - prev_wr; //to express wr difference in us
        h1_wr_diff->Fill(wr_diff);
    }
    prev_wr = wr_time;
    //c4LOG(info,"wr time: " << wr_time << "   prev wr: " << prev_wr << " wr diff: " << wr_diff);


    //::::::: Fill Multiplicity ::::::::::
    //for (int i = 0; i < layer_number; i++) h1_multiplicity_layer[i]->Fill(multiplicity[i]);
    //h1_multiplicity->Fill(total_multiplicity);
    //c4LOG(info, " outside exec layer number: " << layer_number );

    for (int i = 0; i < layer_number; i++)
    {
        if(multiplicity[i] != 0) h1_layer_multiplicity->Fill(i);
        c4LOG(info," layer number : " << layer_number << " layer : " << layer << " multiplicity [layer] : " << multiplicity[layer] << " multiplicity [i] : " << multiplicity[i]);
    }

    for(int i = 0; i < layer_number; i++)
    {
        c4LOG(info,"layer_number : " << layer_number << "multiplicity : "<< multiplicity[i] << " i : " << i );
    }

    c4LOG(info, "counter again : "<< counter);
 
    fNEvents += 1;
}

void LisaOnlineSpectraDaq::FinishEvent()
{

}

void LisaOnlineSpectraDaq::FinishTask()
{

}

ClassImp(LisaOnlineSpectraDaq)
