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
 *                        E.M.Gandolfo, C.E.Jones                             *
 *                               04.05.25                                     *
 ******************************************************************************/

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
#include "TVector.h"

LisaOnlineSpectra::LisaOnlineSpectra()  :   LisaOnlineSpectra("LisaOnlineSpectra")
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
    lisa_config = TLisaConfiguration::GetInstance();
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

    excluded = lisa_config->GetExcludedChannels();


    histograms = (TFolder*)mgr->GetObject("Histograms");
    TDirectory::TContext ctx(nullptr);

    dir_lisa = new TDirectory("LISA", "LISA", "", 0);
    mgr->Register("LISA", "LISA Directory", dir_lisa, false); // allow other tasks to access directory.
    histograms->Add(dir_lisa);

    dir_lisa->cd();
    dir_stats = dir_lisa->mkdir("Stats");
    dir_rates = dir_stats->mkdir("Rates");
    dir_energy = dir_lisa->mkdir("Energy");
    dir_febex = dir_energy->mkdir("Febex");
    dir_febex_channel = dir_febex->mkdir("Channels");
    dir_energy_MWD = dir_energy->mkdir("MWD");
    dir_MWD_channel = dir_energy_MWD->mkdir("Channels");
    dir_traces = dir_lisa->mkdir("Traces");

    // ::: S T A T S :::

    //::: White Rabbit :::
    dir_stats->cd();
    h1_wr_diff = new TH1I("h1_wr_diff", "WR Difference", lisa_config->bin_wr_diff, lisa_config->min_wr_diff, lisa_config->max_wr_diff);
    h1_wr_diff->GetXaxis()->SetTitle("LISA WR Difference [ns]");
    h1_wr_diff->SetLineColor(kBlack);
    h1_wr_diff->SetFillColor(kRed-3);
    //...................

    //::: Rates :::
    dir_rates->cd();

    detector_counter.resize(layer_number);
    detector_rate.resize(layer_number);
    h1_rate.resize(layer_number);
    c_channel_rates.resize(layer_number);

    layer_counter.resize(layer_number);
    layer_rate.resize(layer_number);
    h1_layer_rate.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {
        
        h1_layer_rate[i] = new TH1I(Form("h1_layer_%i_rate",i), Form("LISA Rate %i",i), lisa_config->bin_wr_rate, lisa_config->min_wr_rate, lisa_config->max_wr_rate);
        h1_layer_rate[i]->GetXaxis()->SetTitle("Time [s]");
        h1_layer_rate[i]->GetYaxis()->SetTitle(Form("LISA %i Rate [Hz]", i));
        h1_layer_rate[i]->SetLineColor(kBlack);
        h1_layer_rate[i]->SetFillColor(kRed-3);
        
        c_channel_rates[i] = new TCanvas(Form("c_LISA_ch_rate_layer_%d",i+1),Form("Layer %d Rates",i+1), 650,350);
        c_channel_rates[i]->SetTitle(Form("Layer %d - Rates",i+1));
        c_channel_rates[i]->Divide(xmax,ymax); 

        detector_counter[i].resize(xmax);
        detector_rate[i].resize(xmax);
        h1_rate[i].resize(xmax);

        for (int j = 0; j < xmax; j++)
        {
            detector_counter[i][j].resize(ymax);
            detector_rate[i][j].resize(ymax);
            h1_rate[i][j].resize(ymax);

            for (int k = 0; k < ymax; k++)
            {
                c_channel_rates[i]->cd((ymax-(k+1))*xmax + j + 1);

                h1_rate[i][j][k] = new TH1I(Form("h1_rate_%i%i%i",i+1,j,k), Form("Rate %i%i%i",i+1,j,k), lisa_config->bin_wr_rate, lisa_config->min_wr_rate, lisa_config->max_wr_rate);
                h1_rate[i][j][k]->GetXaxis()->SetTitle("Time [s]");
                h1_rate[i][j][k]->GetYaxis()->SetTitle(Form("LISA %i%i%i Rate [Hz]", i+1,j,k));
                h1_rate[i][j][k]->SetLineColor(kBlack);
                h1_rate[i][j][k]->SetFillColor(kOrange-3);

                h1_rate[i][j][k]->Draw();
            }
        }
        c_channel_rates[i]->cd(0);
        dir_rates->Append(c_channel_rates[i]);
    }
    // init rate counters
    for (int i = 0; i < layer_number; i++)
    {

        layer_counter[i] = 0;
        layer_rate[i] = 0; 
        for (int j = 0; j < xmax; j++)
        {
            for (int k = 0; k < ymax; k++)
            {
                detector_counter[i][j][k] = 0;
                detector_rate[i][j][k] = 0;
            }
        }
    }
    //...................

    // ::: Hit Pattern :::
    dir_stats->cd();
    /* :::  too messy with too many detectors
    //     Total 
    // h1_hitpattern_total = new TH1I("h1_hitpattern_total", "Hit Pattern", det_number, 0, det_number);
    // for (auto & detector : detector_mapping)
    // {
    //     int l = detector.second.first.first;
    //     city = detector.second.first.second;
    //     int x = detector.second.second.first; 
    //     int y = detector.second.second.second;
    //     int h_bin = (ymax - (y + 1)) * xmax + x;
    //     int h_total_bin = (l - 1) * xmax * ymax + h_bin;
        
    //     h1_hitpattern_total->GetXaxis()->SetBinLabel(h_total_bin + 1 , city.Data());
    // }
    */
    //....................................
    //      Layer
    c_hitpattern_layer = new TCanvas("c_hitpattern_layer", "Hit Pattern by Layer", 650, 350);
    c_hitpattern_layer->Divide(2, (layer_number+1)/2);
    h1_hitpattern_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_hitpattern_layer->cd(i+1);
        h1_hitpattern_layer[i] = new TH1I(Form("h1_hitpattern_layer_%i", i+1), Form("Hit Pattern - Layer %i", i+1), xmax * ymax, 0, xmax * ymax);
        h1_hitpattern_layer[i]->SetStats(0);
        h1_hitpattern_layer[i]->Draw();

        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            int x = -9;
            int y = -9;
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
            h1_hitpattern_layer[i]->GetXaxis()->SetBinLabel(j+1, Form("%i%i",x,y));
        }
       
    }
    c_hitpattern_layer->cd();
    dir_stats->Append(c_hitpattern_layer);
    //....................................
    //      Grid
    c_hitpattern_grid = new TCanvas("c_hitpattern_grid", "Hit Pattern Grid", 650, 350);
    c_hitpattern_grid->Divide(2, (layer_number+1)/2, 0.05, 0.05);
    h2_hitpattern_grid.resize(layer_number);
    c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_hitpattern_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_hitpattern_grid[i] = new TH2F(Form("h2_hitpattern_grid_layer_%i", i+1), Form("Hit Pattern Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_hitpattern_grid[i]->SetStats(0);
        h2_hitpattern_grid[i]->Draw("colz");
        h2_hitpattern_grid[i]->GetXaxis()->SetTitle(Form("Hit Pattern Layer %i",i+1));
        h2_hitpattern_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetXaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->SetMinimum(1);
        h2_hitpattern_grid[i]->SetContour(100);
        
    }   
    c_hitpattern_grid->cd();
    dir_stats->Append(c_hitpattern_grid);
    //....................................
    //  ::: Pile up
    c_pileup_grid = new TCanvas("c_pileup_grid", "Pile Up Grid", 650, 350);
    c_pileup_grid->Divide(2, (layer_number+1)/2, 0.05, 0.05);
    h2_pileup_grid.resize(layer_number);
    c_pileup_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_pileup_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_pileup_grid[i] = new TH2F(Form("h2_pileup_grid_layer_%i", i+1), Form("Pile Up Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_pileup_grid[i]->SetStats(0);
        h2_pileup_grid[i]->Draw("colz");
        h2_pileup_grid[i]->GetXaxis()->SetTitle(Form("Pile Up Layer %i",i+1));
        h2_pileup_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetXaxis()->SetTickLength(0);
        h2_pileup_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetYaxis()->SetTickLength(0);
        h2_pileup_grid[i]->SetMinimum(1);
        h2_pileup_grid[i]->SetContour(100);
        
    }    
    c_pileup_grid->cd();
    dir_stats->Append(c_pileup_grid);
    //....................................
    //  ::: Overflow
    c_overflow_grid = new TCanvas("c_overflow_grid", "Overflow Grid", 650, 350);
    c_overflow_grid->Divide(2, (layer_number+1)/2, 0.05, 0.05);
    h2_overflow_grid.resize(layer_number);
    c_overflow_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_overflow_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_overflow_grid[i] = new TH2F(Form("h2_overflow_grid_layer_%i", i+1), Form("Overflow Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_overflow_grid[i]->SetStats(0);
        h2_overflow_grid[i]->Draw("colz");
        h2_overflow_grid[i]->GetXaxis()->SetTitle(Form("Overflow Layer %i",i+1));
        h2_overflow_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetXaxis()->SetTickLength(0);
        h2_overflow_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetYaxis()->SetTickLength(0);
        h2_overflow_grid[i]->SetMinimum(1);
        h2_overflow_grid[i]->SetContour(100);
        
    }
    c_overflow_grid->cd();
    dir_stats->Append(c_overflow_grid);
    //....................................
    // ::: Multiplicity 
    //      Total
    h1_multiplicity = new TH1I("h1_multiplicity", "Detector Multiplicity", det_number+1, -0.5, det_number+0.5);
    h1_multiplicity->SetStats(0);
    //....................................
    //      Multiplicity per layer
    c_multiplicity_per_layer = new TCanvas("c_multiplicity_per_layer", "Multiplicty Per Layer", 650, 350);
    c_multiplicity_per_layer->Divide(2, (layer_number+1)/2); // was +1 dunno if matters
    h1_multiplicity_per_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_multiplicity_per_layer->cd(i+1);
        h1_multiplicity_per_layer[i] = new TH1I(Form("h1_multiplicity_layer_%i",i+1), Form("Multiplicity Layer %i",i+1), xmax * ymax+1, -0.5, xmax * ymax+0.5);
        h1_multiplicity_per_layer[i]->SetStats(0);
        h1_multiplicity_per_layer[i]->GetXaxis()->SetNdivisions(xmax * ymax+1, kTRUE);
        h1_multiplicity_per_layer[i]->Draw();
    }
    c_multiplicity_per_layer->cd();
    dir_stats->Append(c_multiplicity_per_layer);
    //....................................
    //      Layer Multiplicity
    h1_layer_multiplicity = new TH1I("h1_layer_multiplicity", "Layer Multiplicity", layer_number+1, -0.5, layer_number+0.5);
    h1_layer_multiplicity->SetStats(0);
    //....................................

    // ::: E N E R G Y :::
    //      Febex per channel - energy gain matched and/or calibrated
    dir_febex_channel->cd();
    c_energy_ch.resize(layer_number);
    h1_energy_ch.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_energy_ch[i] = new TCanvas(Form("c_energy_layer_%d_channels",i+1),Form("c_energy_layer_%d_channels",i+1), 650,350);
        c_energy_ch[i]->SetTitle(Form("Layer %d - Energies",i+1));
        c_energy_ch[i]->Divide(xmax,ymax); 
        h1_energy_ch[i].resize(xmax);
        
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_ch[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                c_energy_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
                city = "";
                int x = -9;
                int y = -9;
                for (auto & detector : detector_mapping)
                {
        
                int l_id = detector.second.first.first;
                if (l_id == i + 1 && ((ymax - (y + 1)) * xmax + x) == j)
                {
                    city = detector.second.second.second.first;
                    break;
                }
                }
                h1_energy_ch[i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i", city.Data(), i+1, j, k), Form("Energy Febex %s",city.Data()), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h1_energy_ch[i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
                h1_energy_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_energy_ch[i][j][k]->Draw();
            }
        }
        c_energy_ch[i]->cd();
        dir_febex_channel->Append(c_energy_ch[i]);

    }
    //....................................
    //      Febex energy by layer
    dir_febex->cd();
    c_energy_layer = new TCanvas("c_energy_layer", "Energy by Layer", 650, 350);
    c_energy_layer->Divide(2, (layer_number+1)/2);
    h1_energy_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_energy_layer->cd(i+1);
        h1_energy_layer[i] = new TH1F(Form("h1_energy_layer_%i", i+1), Form("Energy - Layer %i", i+1), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h1_energy_layer[i]->GetXaxis()->SetTitle(Form("E(LISA %i) [a.u.]", i+1));
        h1_energy_layer[i]->SetLineColor(kBlue+1);
        h1_energy_layer[i]->SetFillColor(kRed-3);
        h1_energy_layer[i]->Draw();       
    }
    c_energy_layer->cd();
    dir_febex->Append(c_energy_layer);
    //....................................
    //      Febex energy vs channel ID per Layer
    dir_febex->cd();
    c_energy_vs_ID = new TCanvas("c_energy_vs_ID", "Energy vs ID", 650, 350);
    c_energy_vs_ID->Divide(2, (layer_number+1)/2, 0.03, 0.03);
    h2_energy_vs_ID.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_energy_vs_ID->cd(i+1);
        h2_energy_vs_ID[i] = new TH2F(Form("h2_energy_vs_ID_%i", i+1), Form("Energy vs ID - Layer %i", i+1), xmax * ymax, 0, xmax * ymax, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h2_energy_vs_ID[i]->SetStats(0);
        h2_energy_vs_ID[i]->Draw("COLZ");
        
        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            int x = -9;
            int y = -9;
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
            h2_energy_vs_ID[i]->GetXaxis()->SetBinLabel(j+1, Form("%i%i",x,y));
        }
       
    }
    c_energy_vs_ID->cd();
    dir_febex->Append(c_energy_vs_ID);
    
    //....................................
    /* :::  too messy with too many detectors 
    //    Febex energy vs channel ID ALL Channels - 
    c_energy_vs_ID_total = new TCanvas("c_energy_vs_ID", "Energy vs ID", 650, 350);
    h2_energy_vs_ID_total = new TH2F("h2_energy_vs_ID_total", "Energy vs ID", det_number, 0, det_number, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
    h2_energy_vs_ID_total->Draw("COLZ");
    h2_energy_vs_ID_total->SetOption("colz");
    for (auto & detector : detector_mapping)
    {
        int l = detector.second.first.first;
        city = detector.second.first.second;
        int x = detector.second.second.first; 
        int y = detector.second.second.second;
        int h_bin = (ymax - (y + 1)) * xmax + x;
        int h_total_bin = (l - 1) * xmax * ymax + h_bin;
        
        h2_energy_vs_ID_total->GetXaxis()->SetBinLabel(h_total_bin + 1 , city.Data());
    }
    c_energy_vs_ID_total->cd();
    dir_febex->Append(c_energy_vs_ID_total);
     */
    //....................................
    //      Febex energy vs layer ID
    dir_febex->cd();
    c_energy_vs_layer = new TCanvas("c_energy_vs_layer", "Energy vs Layer ID", 600, 400);
    h2_energy_vs_layer = new TH2F("h2_energy_vs_layer", "Energy vs Layer ID",layer_number, 0.5, layer_number + 0.5,lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
    h2_energy_vs_layer->SetStats(0);
    h2_energy_vs_layer->GetXaxis()->SetTitle("Layer ID");
    h2_energy_vs_layer->GetYaxis()->SetTitle("Energy [a.u.]");
    h2_energy_vs_layer->Draw("COLZ");
    dir_febex->Append(c_energy_vs_layer);
    //....................................
    // Febex energy Layer vs Layer
    dir_febex->cd();
    c_energy_layer_vs_layer = new TCanvas("c_energy_layer_vs_layer", "Energy Layer vs Layer", 650, 350);
    c_energy_layer_vs_layer->Divide(2, (layer_number - 1)/2 + (layer_number - 1)%2);  
    h2_energy_layer_vs_layer.resize(layer_number - 1);

    for (int i = 0; i < layer_number - 1; i++)
    {
        c_energy_layer_vs_layer->cd(i + 1);

        h2_energy_layer_vs_layer[i] = new TH2F(Form("h2_energy_layer_%i_vs_layer_%i", i + 2, i + 1),
                                            Form("E(Layer %i) vs E(Layer %i)", i + 2, i + 1),
                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);

        h2_energy_layer_vs_layer[i]->GetXaxis()->SetTitle(Form("E(Layer %i) [a.u.]", i + 1));  
        h2_energy_layer_vs_layer[i]->GetYaxis()->SetTitle(Form("E(Layer %i) [a.u.]", i + 2));  
        h2_energy_layer_vs_layer[i]->Draw("COLZ");
    }
    c_energy_layer_vs_layer->cd();
    dir_febex->Append(c_energy_layer_vs_layer);
    //....................................
    // ::: Febex Energy First vs Last Layer
    dir_febex->cd();
    c_energy_first_vs_last = new TCanvas("c_energy_first_vs_last", "Energy First vs Last Layer", 650, 350);

    h2_energy_first_vs_last = new TH2F("h2_energy_first_vs_last",
                                    Form("E(Layer 1) vs E(Layer %d)", layer_number),
                                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
                                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);

    h2_energy_first_vs_last->GetXaxis()->SetTitle(Form("E(Layer %d) [a.u.]", layer_number));
    h2_energy_first_vs_last->GetYaxis()->SetTitle("E(Layer 1) [a.u.]");
    h2_energy_first_vs_last->Draw("COLZ");

    c_energy_first_vs_last->cd();
    dir_febex->Append(c_energy_first_vs_last);
    //....................................
    // ::: E N E R G Y     M W D:::
    //      MWD per channel - energy gain matched and/or calibrated
    dir_MWD_channel->cd();
    c_energy_MWD_ch.resize(layer_number);
    h1_energy_MWD_ch.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_energy_MWD_ch[i] = new TCanvas(Form("c_energy_MWD_layer_%d_channels",i+1),Form("c_energy_MWD_layer_%d_channels",i+1), 650,350);
        c_energy_MWD_ch[i]->SetTitle(Form("Layer %d - MWD Energy",i+1));
        c_energy_MWD_ch[i]->Divide(xmax,ymax); 
        h1_energy_MWD_ch[i].resize(xmax);
        
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_MWD_ch[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                c_energy_MWD_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
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
                h1_energy_MWD_ch[i][j][k] = new TH1F(Form("energy_MWD_%s_%i_%i_%i", city.Data(), i+1, j, k), Form("Energy MWD %s",city.Data()), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
                h1_energy_MWD_ch[i][j][k]->GetXaxis()->SetTitle("E MWD(LISA) [a.u.]");
                h1_energy_MWD_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_MWD_ch[i][j][k]->SetFillColor(kViolet-1);
                h1_energy_MWD_ch[i][j][k]->Draw();
            }
        }
        c_energy_MWD_ch[i]->cd();
        dir_MWD_channel->Append(c_energy_MWD_ch[i]);

    }
    //....................................
    //      MWD energy by layer
    dir_energy_MWD->cd();
    c_energy_MWD_layer = new TCanvas("c_energy_MWD_layer", "Energy MWD by Layer", 650, 350);
    c_energy_MWD_layer->Divide(2, (layer_number+1)/2);
    h1_energy_MWD_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_energy_MWD_layer->cd(i+1);
        h1_energy_MWD_layer[i] = new TH1F(Form("h1_energy_MWD_layer_%i", i+1), Form("Energy MWD - Layer %i", i+1), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
        h1_energy_MWD_layer[i]->GetXaxis()->SetTitle(Form("E MWD(LISA %i) [a.u.]", i+1));
        h1_energy_MWD_layer[i]->SetLineColor(kBlue+1);
        h1_energy_MWD_layer[i]->SetFillColor(kViolet+10);
        h1_energy_MWD_layer[i]->Draw();       
    }
    c_energy_MWD_layer->cd();
    dir_energy_MWD->Append(c_energy_MWD_layer);
    //....................................
    //      MWD energy vs channel ID per Layer
    dir_energy_MWD->cd();
    c_energy_MWD_vs_ID = new TCanvas("c_energy_MWD_vs_ID", "Energy MWD vs ID", 650, 350);
    c_energy_MWD_vs_ID->Divide(2, (layer_number+1)/2, 0.03, 0.03);
    h2_energy_MWD_vs_ID.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_energy_MWD_vs_ID->cd(i+1);
        h2_energy_MWD_vs_ID[i] = new TH2F(Form("h2_energy_MWD_vs_ID_%i", i+1), Form("Energy MWD vs ID - Layer %i", i+1), xmax * ymax, 0, xmax * ymax, lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
        h2_energy_MWD_vs_ID[i]->SetStats(0);
        h2_energy_MWD_vs_ID[i]->Draw("COLZ");
        
        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            int x = -9;
            int y = -9;
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
            h2_energy_MWD_vs_ID[i]->GetXaxis()->SetBinLabel(j+1, Form("%i%i",x,y));
        }
       
    }
    c_energy_MWD_vs_ID->cd();
    dir_energy_MWD->Append(c_energy_MWD_vs_ID);
    //....................................
    //      MWD energy vs layer ID
    dir_energy_MWD->cd();
    c_energy_MWD_vs_layer = new TCanvas("c_energy_MWD_vs_layer", "Energy MWD vs Layer ID", 600, 400);
    h2_energy_MWD_vs_layer = new TH2F("h2_energy_MWD_vs_layer", "Energy MWD vs Layer ID",layer_number, 0.5, layer_number + 0.5,lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
    h2_energy_MWD_vs_layer->SetStats(0);
    h2_energy_MWD_vs_layer->GetXaxis()->SetTitle("Layer ID");
    h2_energy_MWD_vs_layer->GetYaxis()->SetTitle("Energy MWD [a.u.]");
    h2_energy_MWD_vs_layer->Draw("COLZ");
    dir_energy_MWD->Append(c_energy_MWD_vs_layer);
    //....................................
    // MWD energy Layer vs Layer
    dir_energy_MWD->cd();
    c_energy_MWD_layer_vs_layer = new TCanvas("c_energy_MWD_layer_vs_layer", "Energy MWD Layer vs Layer", 650, 350);
    c_energy_MWD_layer_vs_layer->Divide(2, (layer_number - 1)/2 + (layer_number - 1)%2);  
    h2_energy_MWD_layer_vs_layer.resize(layer_number - 1);

    for (int i = 0; i < layer_number - 1; i++)
    {
        c_energy_MWD_layer_vs_layer->cd(i + 1);

        h2_energy_MWD_layer_vs_layer[i] = new TH2F(Form("h2_energy_MWD_layer_%i_vs_layer_%i", i + 2, i + 1),
                                            Form("E MWD (Layer %i) vs E MWD(Layer %i)", i + 2, i + 1),
                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,
                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);

        h2_energy_MWD_layer_vs_layer[i]->GetXaxis()->SetTitle(Form("E MWD(Layer %i) [a.u.]", i + 1));  
        h2_energy_MWD_layer_vs_layer[i]->GetYaxis()->SetTitle(Form("E MWD(Layer %i) [a.u.]", i + 2));  
        h2_energy_MWD_layer_vs_layer[i]->Draw("COLZ");
    }
    c_energy_MWD_layer_vs_layer->cd();
    dir_energy_MWD->Append(c_energy_MWD_layer_vs_layer);
    //....................................
    // ::: Febex Energy First vs Last Layer
    dir_energy_MWD->cd();
    c_energy_MWD_first_vs_last = new TCanvas("c_energy_MWD_first_vs_last", "Energy MWD_First vs Last Layer", 650, 350);

    h2_energy_MWD_first_vs_last = new TH2F("h2_energy_first_vs_last",
                                    Form("E(Layer 1) vs E(Layer %d)", layer_number),
                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,
                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);

    h2_energy_MWD_first_vs_last->GetXaxis()->SetTitle(Form("E MWD (Layer %d) [a.u.]", layer_number));
    h2_energy_MWD_first_vs_last->GetYaxis()->SetTitle("E MWD (Layer 1) [a.u.]");
    h2_energy_MWD_first_vs_last->Draw("COLZ");

    c_energy_MWD_first_vs_last->cd();
    dir_energy_MWD->Append(c_energy_MWD_first_vs_last);
    //....................................
    //:::  T R A C E S
    dir_traces->cd();
    c_traces_ch.resize(layer_number);
    h1_traces_ch.resize(layer_number);   
    for (int i = 0; i < layer_number; i++) 
    {
        c_traces_ch[i] = new TCanvas(Form("c_traces_layer_%d",i+1),Form("c_traces_layer_%d",i+1), 650,350);
        c_traces_ch[i]->SetTitle(Form("Layer %d - Traces",i+1));
        c_traces_ch[i]->Divide(xmax,ymax); 
        h1_traces_ch[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h1_traces_ch[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                c_traces_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
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

                h1_traces_ch[i][j][k] = new TH1F(Form("traces_%s_%i_%i_%i", city.Data(), i+1, j, k), city.Data(), lisa_config->bin_traces, lisa_config->min_traces, lisa_config->max_traces); 
                h1_traces_ch[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                //h1_traces_ch[i][j][k]->SetMinimum(lisa_config->amplitude_min);
                //h1_traces_ch[i][j][k]->SetMaximum(lisa_config->amplitude_max);
                h1_traces_ch[i][j][k]->SetStats(0);
                h1_traces_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_traces_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_traces_ch[i][j][k]->Draw();
            }
        }
        c_traces_ch[i]->cd();
        dir_traces->Append(c_traces_ch[i]);

    }
    //....................................

    run->GetHttpServer()->RegisterCommand("Reset_Lisa_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    c4LOG(info,"Get Name: " << GetName() );

    return kSUCCESS;
}

void LisaOnlineSpectra::Reset_Histo()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    c4LOG(info,"::: LISA Histos Reset on day " <<  ltm->tm_mday << "th," << " at " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec );

    // ::: S T A T S
    // Reset WR diff
    h1_wr_diff->Reset();
    // Reset Scalers and grid 
    for (int i = 0; i < layer_number; i++)
    {
        h2_hitpattern_grid[i]->Reset();
        h2_pileup_grid[i]->Reset();
        h2_overflow_grid[i]->Reset();
        for (int j = 0; j < xmax; j++)
        {
            h1_layer_rate[i]->Reset();
            for (int k = 0; k < ymax; k++)
            {
                h1_rate[i][j][k]->Reset();
            }
        }
    }
    // Reset hit grid
    //h1_hitpattern_total->Reset();
    // Reset hit patter by layer
    for (int i = 0; i < layer_number; i++)
    {
        h1_hitpattern_layer[i]->Reset();
    } 
    // Reset multiplicity
    h1_layer_multiplicity->Reset();
    h1_multiplicity->Reset();
    for (int i = 0; i < layer_number; i++)
    {
        h1_multiplicity_per_layer[i]->Reset();
    }  
    //...................
    // ::: E N E R G Y
    //h2_energy_vs_ID_total->Reset();
    h2_energy_vs_layer->Reset();
    h2_energy_MWD_vs_layer->Reset();
    for (int i = 0; i < layer_number; i++) 
    {
        h1_energy_layer[i]->Reset();
        h2_energy_vs_ID[i]->Reset();
        h1_energy_MWD_layer[i]->Reset();
        h2_energy_MWD_vs_ID[i]->Reset();
        for (int j = 0; j < xmax; j++)
        {
            for (int z = 0; z < ymax; z++)
            {
                h1_energy_ch[i][j][z]->Reset();
                h1_energy_MWD_ch[i][j][z]->Reset();
            }
        }
    }
    h2_energy_first_vs_last->Reset();
    for (int i = 0; i < layer_number-1; i++) 
    {
        h2_energy_layer_vs_layer[i]->Reset();
        h2_energy_MWD_layer_vs_layer[i]->Reset();
    }

    //...................
    // ::: T R A C E S
    for (int i = 0; i < layer_number; i++) 
    {
        for (int j = 0; j < xmax; j++)
        {
            for (int z = 0; z < ymax; z++)
            {
                h1_traces_ch[i][j][z]->Reset();
            }
        }
    }
    //...................
    
}

void LisaOnlineSpectra::Exec(Option_t* option)
{   
    wr_time = 0;
    int total_multiplicity = 0;
    int multiplicity[layer_number] = {0};

    // ::: For energy of each layer in the laver vs layer histos
    std::vector<std::vector<float>> energy_layer(layer_number);
    energy_layer.resize(layer_number);
    std::vector<std::vector<float>> energy_MWD_layer(layer_number);
    energy_MWD_layer.resize(layer_number);
    //........................................

    // ::: LOOP OVER ITEM :::
    for (auto const & lisaCalItem : *lisaCalArray)
    {
        
        wr_time = lisaCalItem.Get_wr_t();

        if (lisa_config->wr_enable == true) 
        {
            if (wr_time == 0)return; 
        }

        // ::: Retrieve Data :::
        layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        int pileup = lisaCalItem.Get_pileup();
        int overflow = lisaCalItem.Get_overflow();
        float energy = lisaCalItem.Get_energy();
        float energy_GM = lisaCalItem.Get_energy_GM();
        float energy_MWD = lisaCalItem.Get_energy_MWD();
        float energy_MWD_GM = lisaCalItem.Get_energy_MWD_GM();
        trace = lisaCalItem.Get_trace_febex();
        //uint64_t evtno = header->GetEventno();

        // ::: FOR    R A T E S :::
        layer_counter[layer-1]++;
        detector_counter[layer-1][xpos][ypos]++;  //layer - 1 cause the layer numbers are 1,2,3,4,5
        // ::: For Hit Patterns and multiplicity
        int hp_bin = (ymax-(ypos+1))*xmax + xpos;   // Note that hp_bin is actually not the bin number but the x-axis value mapped into the bin
        int hp_total_bin = (layer - 1) * xmax * ymax + hp_bin;
        //....................
        // ::: FOR    M U L T I P L I C I T Y :::
        total_multiplicity++;
        multiplicity[layer-1]++;
        //counter++;

        // Fill Stats histos
        // ::: Hit Pattern Total
        //h1_hitpattern_total->Fill(hp_total_bin);
        //....................
        // ::: Hit Pattern by layer
        h1_hitpattern_layer[layer-1]->Fill(hp_bin);
        //....................
        // ::: Grids (hit pattern, pile up and overflow)
        h2_hitpattern_grid[layer-1]->Fill(xpos,ypos);
        if (pileup != 0) h2_pileup_grid[layer-1]->Fill(xpos,ypos);
        if (overflow != 0) h2_overflow_grid[layer-1]->Fill(xpos,ypos);
        //....................
        //::: Fill traces histos Traces
        h1_traces_ch[layer-1][xpos][ypos]->Reset();
        for (int i = 0; i < trace.size(); i++)
        {
            h1_traces_ch[layer-1][xpos][ypos]->SetBinContent(i, trace[i]);
            //c4LOG(info, "layer -1: " << layer-1 << " x max: " << xmax << " ymax: " << ymax);
        }

        // ::: Fill energy channels :::
        //     Febex
        // ::: Energy Febex per channel
        h1_energy_ch[layer-1][xpos][ypos]->Fill(energy_GM);
        //     MWD
        // ::: Energy MWD per channel
        h1_energy_MWD_ch[layer-1][xpos][ypos]->Fill(energy_MWD_GM);
        // ::: Energy vs ID
        h2_energy_vs_ID[layer-1]->Fill(hp_bin, energy_GM);
        // ::: Energy MWD vs ID
        h2_energy_MWD_vs_ID[layer-1]->Fill(hp_bin, energy_MWD_GM);

        // ::: Exclude channels but keep multiplicity :::
        if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

        // ::: FOR     E N E R G Y :::
        energy_layer[layer-1].emplace_back(energy_GM);
        energy_MWD_layer[layer-1].emplace_back(energy_MWD_GM);

        //::: Fill energy Layer - without excluded channels  :::
        //     Febex
        // ::: Energy Febex per layer
        h1_energy_layer[layer-1]->Fill(energy_GM);
        // ::: Layer Energy vs ID
        h2_energy_vs_layer->Fill(layer,energy_GM);        
        //     MWD
        // ::: Energy MWD per layer
        h1_energy_MWD_layer[layer-1]->Fill(energy_MWD_GM);
        //....................
        // ::: Layer Energy MWD  vs ID
        h2_energy_MWD_vs_layer->Fill(layer,energy_MWD_GM);            
        

    }
    //....................................
    // END OF ITEM LOOP
    //....................................
    // Discard event without WR - ENABLE DURING BEAMTIME
    if (lisa_config->wr_enable == true)
    {
        if ( wr_time == 0 ) return;
    }
    if ( wr_time == 0 ) return;
    //:::::: WR Time Difference
    if( prev_wr > 0 )
    {
        wr_diff = wr_time - prev_wr; //to express wr difference in us
        h1_wr_diff->Fill(wr_diff);
    }
    prev_wr = wr_time;
    //....................................

    // ::: RATES
    double rate_wr_dt_db = (wr_time - saved_wr) / 1e9;

    if (rate_wr_dt_db > 1) 
    {
        if (saved_wr != 0 && rate_wr_dt_db < 2)
        {
            for (int i = 0; i < layer; i++)
            {
                layer_rate[i] = layer_counter[i] / rate_wr_dt_db;
                h1_layer_rate[i]->SetBinContent(rate_running_count, layer_rate[i]);

                for (int j = 0; j < xmax; j++)
                {
                    for (int k = 0; k < ymax; k++)
                    {
                        detector_rate[i][j][k] = detector_counter[i][j][k] / rate_wr_dt_db;
                        h1_rate[i][j][k]->SetBinContent(rate_running_count, detector_rate[i][j][k]);
                    }
                }
            }
        }
        saved_wr = wr_time;
        rate_running_count++;

        for (int i = 0; i < layer; i++)
        {
            if (rate_running_count == lisa_config->max_wr_rate) h1_layer_rate[i]->Reset();
            layer_counter[i] = 0;
            for (int j = 0; j < xmax; j++)
            {
                for (int k = 0; k < ymax; k++)
                {
                    if (rate_running_count == lisa_config->max_wr_rate) h1_rate[i][j][k]->Reset();
                    detector_counter[i][j][k] = 0;
                }
            }
        }
        if (rate_running_count == lisa_config->max_wr_rate) rate_running_count = 0;
    }
    //....................................

    //  Debug multiplicity
    
    // if (multiplicity[0] + multiplicity[1] == 0) std::cout << "zero multi, wr??:: " << wr_time << std::endl;
    // for(int i = 1; i <= layer_number; i++)
    // {
    //     c4LOG(info,"multiplicity : "<< multiplicity[i-1] << " i : " << i );
    // }
    
    // ::: Fill Multiplicity 
    h1_multiplicity->Fill(total_multiplicity);
    for (int i = 0; i < layer_number; i++) h1_multiplicity_per_layer[i]->Fill(multiplicity[i]);

    int layers_fired = 0;
    for (int i = 0; i < layer_number; i++)
    {
        if(multiplicity[i] != 0) layers_fired++;
    }
    h1_layer_multiplicity->Fill(layers_fired);
    //....................................
    // ::: Energy Layer vs Layer
    for ( int i = 0; i < layer_number-1; i++)
    {
        for( int j = 0; j < energy_layer[i].size(); j++)
        {
            for ( int k = 0 ; k < energy_layer[i+1].size(); k++)
            {
                h2_energy_layer_vs_layer[i]->Fill(energy_layer[i][j], energy_layer[i+1][k]);
            }
        }    
    }
    //....................................
    // ::: Energy First vs Last Layer
    for (int i = 0; i < energy_layer[0].size(); ++i)
    {
        for (int j = 0; j < energy_layer[layer_number-1].size(); ++j)
        {
            h2_energy_first_vs_last->Fill( energy_layer[layer_number-1][j], energy_layer[0][i]);
        }
    }
    //....................................
    // ::: Energy MWD Layer vs Layer
    for ( int i = 0; i < layer_number-1; i++)
    {
        for( int j = 0; j < energy_MWD_layer[i].size(); j++)
        {
            for ( int k = 0 ; k < energy_MWD_layer[i+1].size(); k++)
            {
                h2_energy_MWD_layer_vs_layer[i]->Fill(energy_MWD_layer[i][j], energy_MWD_layer[i+1][k]);
            }
        }    
    }
    //....................................
    // ::: Energy MWD First vs Last Layer
    for (int i = 0; i < energy_MWD_layer[0].size(); ++i)
    {
        for (int j = 0; j < energy_MWD_layer[layer_number-1].size(); ++j)
        {
            h2_energy_MWD_first_vs_last->Fill( energy_MWD_layer[layer_number-1][j], energy_MWD_layer[0][i]);
        }
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
