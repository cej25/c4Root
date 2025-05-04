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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               04.05.25                                    *
 ******************************************************************************/

// ::: Note::: No canvases in Nearline Tasks please :::

#include <sstream>
#include <iomanip>
#include <filesystem>
// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaNearlineSpectra.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

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
#include "TColor.h"
#include "TStyle.h"

LisaNearlineSpectra::LisaNearlineSpectra()  :   LisaNearlineSpectra("LisaNearlineSpectra")
{
    lisa_config = TLisaConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();
}

LisaNearlineSpectra::LisaNearlineSpectra(std::vector<LisaGate*> lg)
    :   FairTask()
    // , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    lisa_config = TLisaConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();
    for (auto & gate : lg) 
    {
        if (gate->GetType() == "energy") febex_gates.emplace_back(gate); 
        else if (gate->GetType() == "energy_mwd") mwd_gates.emplace_back(gate);
    }


}

LisaNearlineSpectra::LisaNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    // , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    lisa_config = TLisaConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();

}

LisaNearlineSpectra::~LisaNearlineSpectra()
{
    c4LOG(info, "");
}

void LisaNearlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaNearlineSpectra::Init()
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

    excluded = lisa_config->GetExcludedChannels();

    gate_number = febex_gates.size();
    mwd_gate_number = mwd_gates.size();

    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    int traces_max = lisa_config->amplitude_max;
    int traces_min = lisa_config->amplitude_min;
    int traces_bin = (traces_max - traces_min)/2;

    int drift_max = lisa_config->drift_max;
    int drift_min = lisa_config->drift_min;
    int drift_bin = (drift_max - drift_min); //1 bin per min
    
    // ::: Directories :::
    dir_lisa->cd();
    dir_stats = dir_lisa->mkdir("Stats");
    dir_rates = dir_stats->mkdir("Rates");
    
    dir_energy = dir_lisa->mkdir("Energy");
    dir_febex = dir_energy->mkdir("Febex");
    dir_febex_channel = dir_febex->mkdir("Channels");
    dir_energy_MWD = dir_energy->mkdir("MWD");
    dir_MWD_channel = dir_energy_MWD->mkdir("Channels");

    dir_traces = dir_lisa->mkdir("Traces");

    dir_drift = dir_lisa->mkdir("Drifts");
    dir_febex_drift = dir_drift->mkdir("Febex_Drift");
    dir_febex_ch_drift = dir_febex_drift->mkdir("Channels");
    dir_MWD_drift = dir_drift->mkdir("MWD_Drift");
    dir_MWD_ch_drift = dir_MWD_drift->mkdir("Channels");

    dir_lisa_gates = dir_lisa->mkdir("Gates-LISA");

    
    
    //c4LOG(info, "INIT Layer number" << layer_number);
    //c4LOG(info, "det_number :" << det_number << " layer number : " << layer_number);
    //....................................
  
    // ::: S T A T S :::


    //::: White Rabbit :::
    dir_stats->cd();
    h1_wr_diff = new TH1I("h1_wr_diff", "WR Difference", lisa_config->bin_wr_diff, lisa_config->min_wr_diff, lisa_config->max_wr_diff);
    h1_wr_diff->GetXaxis()->SetTitle("LISA WR Difference [ns]");
    h1_wr_diff->SetLineColor(kBlack);
    h1_wr_diff->SetFillColor(kRed-3);

    //::: Rates :::
    dir_rates->cd();

    detector_counter.resize(layer_number);
    detector_rate.resize(layer_number);
    h1_lisa_rate.resize(layer_number);

    layer_counter.resize(layer_number);
    layer_rate.resize(layer_number);
    h1_lisa_layer_rate.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {
        
        h1_lisa_layer_rate[i] = new TH1I(Form("h1_lisa_layer_%i_rate",i), Form("LISA Rate %i",i), lisa_config->bin_wr_rate, lisa_config->min_wr_rate, lisa_config->max_wr_rate);
        h1_lisa_layer_rate[i]->GetXaxis()->SetTitle("Time [s]");
        h1_lisa_layer_rate[i]->GetYaxis()->SetTitle(Form("LISA %i Rate [Hz]", i));
        h1_lisa_layer_rate[i]->SetLineColor(kBlack);
        h1_lisa_layer_rate[i]->SetFillColor(kRed-3);
        
        detector_counter[i].resize(xmax);
        detector_rate[i].resize(xmax);
        h1_lisa_rate[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            detector_counter[i][j].resize(ymax);
            detector_rate[i][j].resize(ymax);
            h1_lisa_rate[i][j].resize(ymax);

            for (int k = 0; k < ymax; k++)
            {
                h1_lisa_rate[i][j][k] = new TH1I(Form("h1_lisa_rate_%i%i%i",i,j,k), Form("LISA Rate %i%i%i",i,j,k), lisa_config->bin_wr_rate, lisa_config->min_wr_rate, lisa_config->max_wr_rate);
                h1_lisa_rate[i][j][k]->GetXaxis()->SetTitle("Time [s]");
                h1_lisa_rate[i][j][k]->GetYaxis()->SetTitle(Form("LISA %i%i%i Rate [Hz]", i,j,k));
                h1_lisa_rate[i][j][k]->SetLineColor(kBlack);
                h1_lisa_rate[i][j][k]->SetFillColor(kOrange-3);
            }
        }
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

    //::: Hit Patterns :::
    dir_stats->cd();
    //      Total  - this is too messy with too many detectors
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

    //      Layer
    h1_hitpattern_layer.resize(layer_number+1);
    for (int i = 1; i <= layer_number; i++)
    {   
        h1_hitpattern_layer[i] = new TH1I(Form("h1_hitpattern_layer_%i", i), Form("Hit Pattern - Layer: %i", i), xmax * ymax, 0, xmax * ymax);

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
            h1_hitpattern_layer[i]->GetXaxis()->SetBinLabel(j+1, city.Data());
        }
       
    }

    //      Grid
    h2_hitpattern_grid.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        // gPad->SetLeftMargin(0.15);
        // gPad->SetRightMargin(0.15);
        h2_hitpattern_grid[i] = new TH2F(Form("h2_hitpattern_grid_layer_%i", i+1), Form("Hit Pattern Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_hitpattern_grid[i]->SetStats(0);
        h2_hitpattern_grid[i]->SetOption("COLZ");
        h2_hitpattern_grid[i]->GetXaxis()->SetTitle(Form("Hit Pattern Layer %i",i+1));
        h2_hitpattern_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetXaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->SetMinimum(1);
        h2_hitpattern_grid[i]->SetContour(100);
        
    }   

    //  ::: Pile up
    h2_pileup_grid.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   

        // gPad->SetLeftMargin(0.15);
        // gPad->SetRightMargin(0.15);
        h2_pileup_grid[i] = new TH2F(Form("h2_pileup_grid_layer_%i", i+1), Form("Pile Up Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_pileup_grid[i]->SetStats(0);
        h2_pileup_grid[i]->SetOption("COLZ");
        h2_pileup_grid[i]->GetXaxis()->SetTitle(Form("Pile Up Layer %i",i+1));
        h2_pileup_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetXaxis()->SetTickLength(0);
        h2_pileup_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetYaxis()->SetTickLength(0);
        h2_pileup_grid[i]->SetMinimum(1);
        h2_pileup_grid[i]->SetContour(100);
        
    }    

    //  ::: Overflow
    h2_overflow_grid.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        // gPad->SetLeftMargin(0.15);
        // gPad->SetRightMargin(0.15);
        h2_overflow_grid[i] = new TH2F(Form("h2_overflow_grid_layer_%i", i+1), Form("Overflow Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_overflow_grid[i]->SetStats(0);
        h2_overflow_grid[i]->SetOption("COLZ");
        h2_overflow_grid[i]->GetXaxis()->SetTitle(Form("Overflow Layer %i",i+1));
        h2_overflow_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetXaxis()->SetTickLength(0);
        h2_overflow_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetYaxis()->SetTickLength(0);
        h2_overflow_grid[i]->SetMinimum(1);
        h2_overflow_grid[i]->SetContour(100);
        
    }

    // ::: Multiplicity 
    //      Total
    h1_multiplicity = new TH1I("h1_multiplicity", "Detector Multiplicity", det_number+1, -0.5, det_number+0.5);

    //      Multiplicity per layer
    h1_multiplicity_per_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h1_multiplicity_per_layer[i] = new TH1I(Form("h1_multiplicity_layer_%i",i+1), Form("Multiplicity Layer %i",i+1), xmax * ymax+1, -0.5, xmax * ymax+0.5);
    }

    //      Layer Multiplicity
    h1_layer_multiplicity = new TH1I("h1_layer_multiplicity", "Layer Multiplicity", layer_number+1, -0.5, layer_number+0.5);
    //...................................END OF STATS   

    // ::: E N E R G Y :::
    dir_energy->cd();
    //      Febex per channel
    dir_febex_channel->cd();
    h1_energy_ch.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h1_energy_ch[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_ch[i][j].resize(ymax);
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
                h1_energy_ch[i][j][k] = new TH1F(Form("energy_%s_%i%i%i", city.Data(), i+1, j, k), Form("Energy Febex %s",city.Data()), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h1_energy_ch[i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
                h1_energy_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_ch[i][j][k]->SetFillColor(kOrange-3);
            }
        }
    }

    //      Febex energy by layer
    h1_energy_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_layer[i] = MakeTH1(dir_febex, "F",
            Form("h1_energy_layer_%i", i+1), Form("Energy - Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E(LISA %i) [a.u.]", i+1), kRed-3, kBlue+1);
    }
    //....................................
    //      Febex energy vs channel ID per Layer
    dir_febex->cd();
    h2_energy_vs_ID.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h2_energy_vs_ID[i] = new TH2F(Form("h2_energy_vs_ID_%i", i+1), Form("Energy vs ID - Layer %i", i+1), xmax * ymax, 0, xmax * ymax, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h2_energy_vs_ID[i]->SetOption("COLZ");
        
        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            for (auto & detector : detector_mapping)
            {
                int x = detector.second.second.first; 
                int y = detector.second.second.second;
                if (detector.second.first.first == i+1 && ((ymax-(y+1))*xmax + x) == j)
                {
                    city = detector.second.first.second;
                    break;
                }
            }
            h2_energy_vs_ID[i]->GetXaxis()->SetBinLabel(j+1, city.Data());
        }
       
    }
    //....................................
    // This is too messy with too many channels
    //     Febex energy vs channel ID ALL Channels 
    // h2_energy_vs_ID_total = new TH2F("h2_energy_vs_ID_total", "Energy vs ID", det_number, 0, det_number, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
    // h2_energy_vs_ID_total->SetOption("colz");
    // for (auto & detector : detector_mapping)
    // {
    //     int l = detector.second.first.first;
    //     city = detector.second.first.second;
    //     int x = detector.second.second.first; 
    //     int y = detector.second.second.second;
    //     int h_bin = (ymax - (y + 1)) * xmax + x;
    //     int h_total_bin = (l - 1) * xmax * ymax + h_bin;
        
    //     h2_energy_vs_ID_total->GetXaxis()->SetBinLabel(h_total_bin + 1 , city.Data());
    // }

    //....................................
    //      Febex energy vs layer ID
    dir_febex->cd();
    h2_energy_vs_layer = new TH2F("h2_energy_vs_layer", "Energy vs Layer ID",layer_number, 0.5, layer_number + 0.5,lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
    h2_energy_vs_layer->GetXaxis()->SetTitle("Layer ID");
    h2_energy_vs_layer->GetYaxis()->SetTitle("Energy [a.u.]");
    h2_energy_vs_layer->SetOption("COLZ");
    //....................................
    // Febex energy Layer vs Layer
    dir_febex->cd();
    h2_energy_layer_vs_layer.resize(layer_number - 1);

    for (int i = 0; i < layer_number - 1; i++)
    {
        h2_energy_layer_vs_layer[i] = new TH2F(Form("h2_energy_layer_%i_vs_layer_%i", i + 2, i + 1),
                                            Form("E(Layer %i) vs E(Layer %i)", i + 2, i + 1),
                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);

        h2_energy_layer_vs_layer[i]->GetXaxis()->SetTitle(Form("E(Layer %i) [a.u.]", i + 1));  
        h2_energy_layer_vs_layer[i]->GetYaxis()->SetTitle(Form("E(Layer %i) [a.u.]", i + 2));  
        h2_energy_layer_vs_layer[i]->SetOption("COLZ");
    }
    //....................................
    // ::: Febex Energy First vs Last Layer
    dir_febex->cd();
    h2_energy_first_vs_last = new TH2F("h2_energy_first_vs_last",
                                    Form("E(Layer 1) vs E(Layer %d)", layer_number),
                                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
                                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);

    h2_energy_first_vs_last->GetXaxis()->SetTitle(Form("E(Layer %d) [a.u.]", layer_number));
    h2_energy_first_vs_last->GetYaxis()->SetTitle("E(Layer 1) [a.u.]");
    h2_energy_first_vs_last->SetOption("COLZ");
    //....................................
    // ::: E N E R G Y    M W D :::
    dir_MWD_channel->cd();
    //      MWD per channel
    h1_energy_MWD_ch.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h1_energy_MWD_ch[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_MWD_ch[i][j].resize(ymax);
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
                h1_energy_MWD_ch[i][j][k] = new TH1F(Form("energy_MWD_%s_%i%i%i", city.Data(), i+1, j, k), Form("Energy MWD %s",city.Data()), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
                h1_energy_MWD_ch[i][j][k]->GetXaxis()->SetTitle("E_MWD (LISA) [a.u.]");
                h1_energy_MWD_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_MWD_ch[i][j][k]->SetFillColor(kViolet-1);
            }
        }
    }
    //....................................
    //      MWD energy by layer
    dir_energy_MWD->cd();
    h1_energy_MWD_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_MWD_layer[i] = new TH1F(Form("h1_energy_MWD_layer_%i", i+1), Form("Energy MWD - Layer %i", i+1), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
        h1_energy_MWD_layer[i]->GetXaxis()->SetTitle(Form("E(LISA %i) [a.u.]", i+1));
        h1_energy_MWD_layer[i]->SetLineColor(kBlue+1);
        h1_energy_MWD_layer[i]->SetFillColor(kViolet+10);     
    }
    //....................................
    //      MWD energy vs channel ID per Layer
    h2_energy_MWD_vs_ID_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h2_energy_MWD_vs_ID_layer[i] = new TH2F(Form("h2_energy_MWD_vs_ID_layer_%i", i+1), Form("Energy MWD vs ID - Layer %i", i+1), xmax * ymax, 0, xmax * ymax, lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);

        h2_energy_MWD_vs_ID_layer[i]->SetOption("COLZ");
        h2_energy_MWD_vs_ID_layer[i]->GetZaxis()->SetLabelSize(0.005); 
        
        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            for (auto & detector : detector_mapping)
            {
                int x = detector.second.second.first; 
                int y = detector.second.second.second;
                if (detector.second.first.first == i+1 && ((ymax-(y+1))*xmax + x) == j)
                {
                    city = detector.second.first.second;
                    break;
                }
            }
            h2_energy_MWD_vs_ID_layer[i]->GetXaxis()->SetBinLabel(j+1, city.Data());
        }
       
    }
    //....................................
    //      MWD energy vs layer ID
    dir_energy_MWD->cd();
    h2_energy_MWD_vs_layer = new TH2F("h2_energy_MWD_vs_layer", "Energy MWD vs Layer ID",layer_number, 0.5, layer_number + 0.5,lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
    h2_energy_MWD_vs_layer->GetXaxis()->SetTitle("Layer ID");
    h2_energy_MWD_vs_layer->GetYaxis()->SetTitle("Energy MWD [a.u.]");
    h2_energy_MWD_vs_layer->SetOption("COLZ");
    //....................................
    // MWD energy Layer vs Layer
    dir_energy_MWD->cd();
    h2_energy_MWD_layer_vs_layer.resize(layer_number - 1);
    for (int i = 0; i < layer_number - 1; i++)
    {
        h2_energy_MWD_layer_vs_layer[i] = new TH2F(Form("h2_energy_MWD_layer_%i_vs_layer_%i", i + 2, i + 1),
                                            Form("E MWD (Layer %i) vs E MWD(Layer %i)", i + 2, i + 1),
                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,
                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);

        h2_energy_MWD_layer_vs_layer[i]->GetXaxis()->SetTitle(Form("E MWD(Layer %i) [a.u.]", i + 1));  
        h2_energy_MWD_layer_vs_layer[i]->GetYaxis()->SetTitle(Form("E MWD(Layer %i) [a.u.]", i + 2));  
        h2_energy_MWD_layer_vs_layer[i]->SetOption("COLZ");
    }
    //....................................
    // ::: MWD Energy First vs Last Layer
    dir_energy_MWD->cd();
    h2_energy_MWD_first_vs_last = new TH2F("h2_energy_MWD_first_vs_last",
                                    Form("E MWD(Layer 1) vs E MWD(Layer %d)", layer_number),
                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,
                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);

    h2_energy_MWD_first_vs_last->GetXaxis()->SetTitle(Form("E MWD (Layer %d) [a.u.]", layer_number));
    h2_energy_MWD_first_vs_last->GetYaxis()->SetTitle("E MWD (Layer 1) [a.u.]");
    h2_energy_MWD_first_vs_last->SetOption("COLZ");
    //.................................... END OF ENERGY
    // ::: T R A C E S
    if(lisa_config->trace_on)
    {
        h2_traces_ch.resize(layer_number);
        dir_traces->cd();
        for (int i = 0; i < layer_number; i++) 
        {
            h2_traces_ch[i].resize(xmax);
            for (int j = 0; j < xmax; j++)
            {
                h2_traces_ch[i][j].resize(ymax);
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

                    h2_traces_ch[i][j][k] = new TH2F(Form("h2_traces_%i%i%i", i+1, j, k), Form("%i%i%i_%s",i+1,j,k,city.Data()), lisa_config->bin_traces, lisa_config->min_traces, lisa_config->max_traces,traces_bin,traces_min,traces_max);
                    h2_traces_ch[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                    h2_traces_ch[i][j][k]->SetLineColor(kBlue+1);
                    h2_traces_ch[i][j][k]->SetFillColor(kOrange-3);
                    h2_traces_ch[i][j][k]->SetOption("colz");

                    
                }
            }

        }
    }
    //.................................... END OF TRACES
    // :::  D R I F T S :::
    //....................................
    // ::: Febex layer vs Time (WR)
    h2_energy_layer_vs_time.resize(layer_number);
    dir_febex_drift->cd();
    for (int i = 0; i < layer_number; i++)
    { 
        h2_energy_layer_vs_time[i] = MakeTH2(dir_febex_drift, "F", Form("h2_energy_layer_%i_vs_time",i), Form("E (Layer %i) vs WR [min]",i), drift_bin, drift_min, drift_max, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h2_energy_layer_vs_time[i]->SetTitle(Form("E (Layer %i) vs WR",i));
        h2_energy_layer_vs_time[i]->GetYaxis()->SetTitle(Form("Energy Layer %i",i));
        h2_energy_layer_vs_time[i]->GetXaxis()->SetTitle("WR Time [min]");  
    }
    //....................................
    //::: Febex channel vs WR Time
    h2_energy_ch_vs_time.resize(layer_number);
    dir_febex_ch_drift->cd();
    for (int i = 0 ; i < layer_number; i++)
    {
        h2_energy_ch_vs_time[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h2_energy_ch_vs_time[i][j].resize(ymax);
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
                h2_energy_ch_vs_time[i][j][k] = MakeTH2(dir_febex_ch_drift, "F", Form("h2_energy_%d%d%d_vs_time",i,j,k), Form("E %d%d%d vs WR [min]",i,j,k), drift_bin, drift_min, drift_max, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h2_energy_ch_vs_time[i][j][k]->SetTitle(Form("E (%d%d%d) vs WR",i,j,k));
                h2_energy_ch_vs_time[i][j][k]->GetYaxis()->SetTitle(Form("Energy %d%d%d",i,j,k));
                h2_energy_ch_vs_time[i][j][k]->GetXaxis()->SetTitle("WR Time [min]");
            }
        }
    }  
    //....................................
    // ::: MWD layer vs time (WR)
    h2_energy_MWD_layer_vs_time.resize(layer_number);
    dir_MWD_drift->cd();
    for (int i = 0; i < layer_number; i++)
    {     
        h2_energy_MWD_layer_vs_time[i] = MakeTH2(dir_MWD_drift, "F", Form("h2_energy_MWD_layer_%i_vs_time",i), Form("E_MWD (Layer %i) vs WR [min]",i), drift_bin, drift_min, drift_max, lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
        h2_energy_MWD_layer_vs_time[i]->SetTitle(Form("E_MWD (Layer %i) vs WR",i));
        h2_energy_MWD_layer_vs_time[i]->GetYaxis()->SetTitle(Form("Energy MWD Layer %i",i));
        h2_energy_MWD_layer_vs_time[i]->GetXaxis()->SetTitle("WR Time [min]");
    }
    //....................................
    //::: MWD channel vs WR Time
    h2_energy_MWD_ch_vs_time.resize(layer_number);
    dir_febex_ch_drift->cd();
    for (int i = 0 ; i < layer_number; i++)
    {
        h2_energy_MWD_ch_vs_time[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h2_energy_MWD_ch_vs_time[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {                   
                city = "";
                for (auto & detector : detector_mapping)
                {
                    if (detector.second.first.first == i + 1 && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }
                
                h2_energy_MWD_ch_vs_time[i][j][k] = MakeTH2(dir_MWD_ch_drift, "F", Form("h2_energy_MWD_%d%d%d_vs_time",i,j,k), Form("E_MWD %d%d%d vs WR [min]",i,j,k), drift_bin, drift_min, drift_max, lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
                h2_energy_MWD_ch_vs_time[i][j][k]->SetTitle(Form("E_MWD (%d%d%d) vs WR",i,j,k));
                h2_energy_MWD_ch_vs_time[i][j][k]->GetYaxis()->SetTitle(Form("Energy MWD %d%d%d",i,j,k));
                h2_energy_MWD_ch_vs_time[i][j][k]->GetXaxis()->SetTitle("WR Time [min]");
            }
        }
    } 
    //....................................END OF DRIFTS 

    // ::: Febex Gated
    dir_gated_febex = dir_lisa_gates->mkdir("Febex");
    dir_gated_mwd = dir_lisa_gates->mkdir("MWD");
    dir_febex_gates = new TDirectory*[gate_number];
    dir_febex_gates_channel = new TDirectory*[gate_number];
    dir_mwd_gates = new TDirectory*[mwd_gate_number];
    dir_mwd_gates_channel = new TDirectory*[mwd_gate_number];

    h1_energy_layer_gated.resize(gate_number);
    h1_energy_xy_gated.resize(gate_number);
    h1_energy_MWD_layer_gated.resize(mwd_gate_number);
    h1_energy_MWD_xy_gated.resize(mwd_gate_number);

    // Febex Gated
    for (int gate = 0; gate < febex_gates.size(); gate++)
    {   
        dir_febex_gates[gate] = dir_gated_febex->mkdir(TString(febex_gates.at(gate)->GetName()));
        h1_energy_layer_gated[gate].resize(layer_number);

        h1_energy_layer_gated[gate].resize(layer_number); 
        for (int i = 0; i < layer_number; ++i)
        {
            h1_energy_layer_gated[gate][i] = MakeTH1(dir_febex_gates[gate], "F",
                Form("h1_energy_layer_%i_gated", i+1),
                Form("LISA-Gated Energy - Layer %i", i+1),
                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                Form("E(LISA %i) [a.u.]", i+1), kRed-3, kBlue+1
            );
        }

        dir_febex_gates_channel[gate] = dir_febex_gates[gate]->mkdir("Channel");
        h1_energy_xy_gated[gate].resize(layer_number);
        for (int i = 0; i < layer_number; ++i)
        {
            h1_energy_xy_gated[gate][i] = MakeTH1(dir_febex_gates_channel[gate], "F",
                Form("h1_energy_%i%i%i_gated", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                Form("LISA-Gated Energy - %i%i%i", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
                Form("E(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate), kOrange-3, kBlue+1
            );
        }
    }

    // MWD Gated
    for (int gate = 0; gate < mwd_gates.size(); gate++)
    {   
        dir_mwd_gates[gate] = dir_gated_mwd->mkdir(TString(mwd_gates.at(gate)->GetName()));

        h1_energy_MWD_layer_gated[gate].resize(layer_number); 
        for (int i = 0; i < layer_number; ++i)
        {
            h1_energy_MWD_layer_gated[gate][i] = MakeTH1(dir_mwd_gates[gate], "F",
                Form("h1_energy_MWD_layer_%i_gated", i+1),
                Form("LISA-Gated Energy MWD - Layer %i", i+1),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,
                Form("E MWD (LISA %i) [a.u.]", i+1), kViolet+10, kBlue+1
            );
        }

        dir_mwd_gates_channel[gate] = dir_mwd_gates[gate]->mkdir("Channel");
        h1_energy_MWD_xy_gated[gate].resize(layer_number);
        for (int i = 0; i < layer_number; ++i)
        {
            h1_energy_MWD_xy_gated[gate][i] = MakeTH1(dir_mwd_gates_channel[gate], "F",
                Form("h1_energy_MWD_%i%i%i_gated", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                Form("LISA-Gated Energy MWD - %i%i%i", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,
                Form("E MWD (LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate), kViolet-1, kBlue+1
            );
        }
    }
    //....................................


    c4LOG(info, "Successful");
        
    return kSUCCESS;
}


void LisaNearlineSpectra::Exec(Option_t* option)
{   
    // ::: For WR histos and experiment start
    wr_time = 0;
    Long64_t LISA_time_mins = 0;
    // .........................
    int total_multiplicity = 0;
    int multiplicity[layer_number] = {0};
    int xpos_gate = lisa_config->xpos_gate;
    int ypos_gate = lisa_config->ypos_gate;

    // ::: For energy of each layer in the laver vs layer histos
    std::vector<std::vector<float>> energy_layer(layer_number);
    energy_layer.resize(layer_number);

    std::vector<std::vector<float>> energy_MWD_layer(layer_number);
    energy_MWD_layer.resize(layer_number);  

    // ::: Energy gated - Layer

    std::vector<float> energy_layer_gated[gate_number][layer_number];
    std::vector<float> energy_MWD_layer_gated[mwd_gate_number][layer_number];

    // ::: Energy gated - Channel
    std::vector<float> energy_xy_gated[gate_number][layer_number][xmax][ymax];
    std::vector<float> energy_MWD_xy_gated[mwd_gate_number][layer_number][xmax][ymax];
    

    for (auto const & lisaCalItem : *lisaCalArray)
    {
        // For WR histos and experiment start
        wr_time = lisaCalItem.Get_wr_t();
        if (lisa_config->wr_enable == true) 
        {
            if (wr_time == 0)return; 
        }
        if (wr_time == 0)return;
        if(wr_time > 0) LISA_time_mins = (wr_time - exp_config->exp_start_time)/ 60E9;
        //c4LOG(info, "LISA_time_mins: " << LISA_time_mins << " wr time: "<< std::fixed << std::setprecision(10)<< wr_time);

        //::: Retrieve Data :::
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

        std::vector<float> trace = lisaCalItem.Get_trace_febex();
        
        //uint64_t evtno = header->GetEventno();

        // ::: FOR   R A T E S 
        layer_counter[layer-1]++;
        detector_counter[layer-1][xpos][ypos]++;    //layers start from 1
        // ::: For Hit Patterns, multiplicity and energy vs ID
        int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        int hp_total_bin = (layer - 1) * xmax * ymax + hp_bin;
        //....................
        // ::: FOR     M U L T I P L I C I T Y  
        total_multiplicity++;
        multiplicity[layer-1]++;
        //....................

        // ::: Fill Stats Histo :::
        //h1_hitpattern_total->Fill(hp_total_bin);
        //....................
        // ::: Hit Pattern by layer
        h1_hitpattern_layer[layer]->Fill(hp_bin);
        //....................
        // ::: Grids (hit pattern, pile up and overflow)
        h2_hitpattern_grid[layer-1]->Fill(xpos,ypos);
        if (pileup != 0) h2_pileup_grid[layer-1]->Fill(xpos,ypos);
        if (overflow != 0) h2_overflow_grid[layer-1]->Fill(xpos,ypos);
        //....................  
        // :::: Fill traces histos febex
        if(lisa_config->trace_on)
        {
            for (int i = 0; i < trace.size(); i++)
            {   
                h2_traces_ch[layer-1][xpos][ypos]->Fill(i*0.01,trace[i]);
            }
        }
        //....................

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
        h2_energy_MWD_vs_ID_layer[layer-1]->Fill(hp_bin, energy_MWD_GM);


        // ::: Exclude channels but keep multiplicity :::
        if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

        // ::: FOR     E N E R G Y
        int xp_gate = lisa_config->xpos_gate;
        int yp_gate = lisa_config->ypos_gate;
        //c4LOG(info, " xpos_gate : " << xp_gate << " ypos_gate : " << yp_gate);

        energy_layer[layer-1].emplace_back(energy_GM);
        energy_MWD_layer[layer-1].emplace_back(energy_MWD_GM);

        
        // Loop over gates for LISA FEBEX
        int g = 0;
        for (auto & gate : febex_gates)
        {
            if (gate->PassedGate(layer, energy_GM))
            {
                energy_layer_gated[g][layer-1].push_back(energy_GM);
                energy_xy_gated[g][layer-1][xpos][ypos].push_back(energy_GM);
            }
            g++;
        }

        g = 0;
        for (auto & gate : mwd_gates)
        {   
            if (gate->PassedGate(layer, energy_MWD_GM))
            {
                energy_MWD_layer_gated[g][layer-1].push_back(energy_MWD_GM);
                energy_MWD_xy_gated[g][layer-1][xpos][ypos].push_back(energy_MWD_GM);
            }
            g++;
        }

        //::: F I L L   E N E R G Y   H I S T O S  :::        
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
            

        //c4LOG(info, "layer -1 " << layer-1 << " LISA_time_mins: " << LISA_time_mins << " energy : "<<  energy_GM);
        // ::: Drifts ::::
        //    Febex energy vs Time
        if (energy_GM > 0 && LISA_time_mins > 0)
        {
            //c4LOG(info, "conditions on LISA time: " << LISA_time_mins << " and energy: " << energy_GM );
            h2_energy_layer_vs_time[layer-1]->Fill(LISA_time_mins, energy_GM);
            h2_energy_ch_vs_time[layer-1][xpos][ypos]->Fill(LISA_time_mins, energy_GM); 
        }
        // //     MWD Energy vs Time
        if (energy_MWD_GM > 0 && LISA_time_mins > 0)
        {
            h2_energy_MWD_layer_vs_time[layer-1]->Fill(LISA_time_mins, energy_MWD_GM);
            h2_energy_MWD_ch_vs_time[layer-1][xpos][ypos]->Fill(LISA_time_mins, energy_MWD_GM); 
        }
    
    }
    //c4LOG(info, "LISA_time_mins: " << LISA_time_mins << " wr time: "<< std::fixed << std::setprecision(10)<< wr_time);

    // ::: WR Time Difference

    if (lisa_config->wr_enable == true) 
    {
        if (wr_time == 0)return; 
    }
    if ( wr_time == 0 ) return;
    
    if( prev_wr > 0 )
    {
        wr_diff = wr_time - prev_wr;
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
                //c4LOG(info, " Layer : " << i << " Layer rate : " << layer_rate[i] << " Layer counter : " << layer_counter[i] << " rate_wr_dt_db : " << rate_wr_dt_db);
                layer_rate[i] = layer_counter[i] / rate_wr_dt_db;
                h1_lisa_layer_rate[i]->SetBinContent(rate_running_count, layer_rate[i]);
                
                for (int j = 0; j < xmax; j++)
                {
                    for (int k = 0; k < ymax; k++)
                    {
                        detector_rate[i][j][k] = detector_counter[i][j][k] / rate_wr_dt_db;
                        h1_lisa_rate[i][j][k]->SetBinContent(rate_running_count, detector_rate[i][j][k]);
                    }
                }
            }
        }
        saved_wr = wr_time;
        rate_running_count++;

        for (int i = 0; i < layer; i++)
        {
            layer_counter[i] = 0;
            for (int j = 0; j < xmax; j++)
            {
                for (int k = 0; k < ymax; k++)
                {
                    detector_counter[i][j][k] = 0;
                }
            }
        }
    }
    //....................................

    // ::: Multiplicity
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
            h2_energy_MWD_first_vs_last->Fill(energy_MWD_layer[layer_number-1][j], energy_MWD_layer[0][i]);
        }
    }
    //....................................

    // ::: LISA Febex Gated on LISA-only
    // ::: Layer
    for (int g = 0; g < gate_number; ++g)  
    {
        for (int l = 0; l < layer_number; ++l) 
        {
            if (energy_layer_gated[g][l].empty()) continue;  

            for (int i = 0; i < energy_layer_gated[g][l].size(); ++i)
            {
                h1_energy_layer_gated[g][l]->Fill(energy_layer_gated[g][l].at(i));
            }
        }
    }
    // ::: Channel
    for (int g = 0; g < gate_number; ++g)  
    {
        for (int l = 0; l < layer_number; l++)
        {
            if (energy_xy_gated[g][l][xpos_gate][ypos_gate].size() == 0) break;
            for ( int i = 0; i < energy_xy_gated[g][l][xpos_gate][ypos_gate].size(); i++)
            {
                h1_energy_xy_gated[g][l]->Fill(energy_xy_gated[g][l][xpos_gate][ypos_gate].at(i));
            }
        }
    }
    //....................................
    // ::: LISA MWD Gated on LISA-only 
    // ::: Layer
    for (int g = 0; g < mwd_gate_number; g++)
    {
        for (int l = 0; l < layer_number; l++)
        {
            if (energy_MWD_layer_gated[g][l].size() == 0) break;
            for ( int i = 0; i < energy_MWD_layer_gated[g][l].size(); i++)
            {
                h1_energy_MWD_layer_gated[g][l]->Fill(energy_MWD_layer_gated[g][l].at(i));
            }
        }
    }
    // ::: Channel
    for (int g = 0; g < mwd_gate_number; g++)
    {
        for (int l = 0; l < layer_number; l++)
        {
            if (energy_MWD_xy_gated[g][l][xpos_gate][ypos_gate].size() == 0) break;
            for ( int i = 0; i < energy_MWD_xy_gated[g][l][xpos_gate][ypos_gate].size(); i++)
            {
                h1_energy_MWD_xy_gated[g][l]->Fill(energy_MWD_xy_gated[g][l][xpos_gate][ypos_gate].at(i));
            }
        }
    }

    //....................................

        
    fNEvents += 1;
}

void LisaNearlineSpectra::FinishEvent()
{

}

void LisaNearlineSpectra::FinishTask()
{

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "LISA events : " << fNEvents);


}

ClassImp(LisaNearlineSpectra)
