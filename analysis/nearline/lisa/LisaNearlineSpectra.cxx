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
 *                               25.11.24                                    *
 ******************************************************************************/
// ::: Note::: No canvases in Nearline Tasks please :::

#include <sstream>
#include <iomanip>
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
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    int traces_max = lisa_config->amplitude_max;
    int traces_min = lisa_config->amplitude_min;
    int traces_bin = traces_max - traces_min;

    // ::: Directories :::
    dir_lisa->cd();
    dir_stats = dir_lisa->mkdir("Stats");
    dir_rates = dir_stats->mkdir("Rates");
    
    dir_energy = dir_lisa->mkdir("Energy");
    dir_febex = dir_energy->mkdir("Febex");

    //dir_energy_febex = dir_lisa->mkdir("Energy_Febex");
    //dir_energy_febex_ch = dir_energy_febex->mkdir("Energy_Febex_Channels");

    //dir_energy_MWD = dir_lisa->mkdir("Energy_MWD");
    //dir_energy_MWD_ch = dir_energy_MWD->mkdir("Energy_MWD_Channels");

    dir_traces = dir_lisa->mkdir("Traces");
    
    //dir_drift = dir_lisa->mkdir("Drifts");
    //dir_drift_ch = dir_drift->mkdir("Drifts_Channels");

    c4LOG(info, "INIT Layer number" << layer_number);
    c4LOG(info, "det_number :" << det_number << " layer number : " << layer_number);
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

    for (int i = 0; i < layer_number; i++)
    {
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
                h1_lisa_rate[i][j][k]->SetFillColor(kRed-3);
            }
        }
    }
    // init rate counters
    for (int i = 0; i < layer_number; i++)
    {
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
    //      Total
    h1_hitpattern_total = new TH1I("h1_hitpattern_total", "Hit Pattern", det_number, 0, det_number);
    for (auto & detector : detector_mapping)
    {
        int l = detector.second.first.first;
        city = detector.second.first.second;
        int x = detector.second.second.first; 
        int y = detector.second.second.second;
        int h_bin = (ymax - (y + 1)) * xmax + x;
        int h_total_bin = (l - 1) * xmax * ymax + h_bin;
        
        h1_hitpattern_total->GetXaxis()->SetBinLabel(h_total_bin + 1 , city.Data());
    }  

    //      Layer
    h1_hitpattern_layer.resize(layer_number+1);
    for (int i = 1; i <= layer_number; i++)
    {   
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
            h1_hitpattern_layer[i]->GetXaxis()->SetBinLabel(j+1, city.Data());
        }
       
    }

    //      Grid
    h2_hitpattern_grid.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
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

    //  ::: Pile up
    h2_pileup_grid.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   

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

    //  ::: Overflow
    h2_overflow_grid.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
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

    // ::: Multiplicity 
    //      Total
    h1_multiplicity = new TH1I("h1_multiplicity", "Detector Multiplicity", det_number+1, -0.5, det_number+0.5);
    h1_multiplicity->SetStats(0);

    //      Multiplicity per layer
    h1_multiplicity_per_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h1_multiplicity_per_layer[i] = new TH1I(Form("h1_multiplicity_layer_%i",i+1), Form("Multiplicity Layer %i",i+1), xmax * ymax+1, -0.5, xmax * ymax+0.5);
        h1_multiplicity_per_layer[i]->SetStats(0);
        h1_multiplicity_per_layer[i]->Draw();
    }

    //      Layer Multiplicity
    h1_layer_multiplicity = new TH1I("h1_layer_multiplicity", "Layer Multiplicity", layer_number+1, -0.5, layer_number+0.5);
    h1_layer_multiplicity->SetStats(0);
    //....................................   

    // ::: E N E R G Y :::
    dir_energy->cd();
    //      Febex per channel
    dir_febex->cd();
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
                h1_energy_ch[i][j][k]->Draw();
            }
        }
    }
    //      Febex energy by layer
    dir_febex->cd();
    h1_energy_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_layer[i] = new TH1F(Form("h1_energy_layer_%i", i+1), Form("Energy - Layer %i", i+1), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h1_energy_layer[i]->SetStats(0);
        h1_energy_layer[i]->GetXaxis()->SetTitle(Form("E(LISA %i) [a.u.]", i+1));
        h1_energy_layer[i]->SetLineColor(kBlue+1);
        h1_energy_layer[i]->SetFillColor(kRed-3);
        h1_energy_layer[i]->Draw();       
    }
    //....................................
    //      Febex energy vs channel ID per Layer
    h2_energy_vs_ID_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h2_energy_vs_ID_layer[i] = new TH2F(Form("h2_energy_vs_ID_layer_%i", i+1), Form("Energy vs ID - Layer %i", i+1), xmax * ymax, 0, xmax * ymax, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h2_energy_vs_ID_layer[i]->SetStats(0);
        h2_energy_vs_ID_layer[i]->Draw("COLZ");
        gPad->Update();
        h2_energy_vs_ID_layer[i]->GetZaxis()->SetLabelSize(0.005); 
        
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
            h2_energy_vs_ID_layer[i]->GetXaxis()->SetBinLabel(j+1, city.Data());
        }
       
    }
    //....................................
    //     Febex energy vs channel ID ALL Channels
    h2_energy_vs_ID_total = new TH2F("h2_energy_vs_ID_total", "Energy vs ID", det_number, 0, det_number, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
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
    //....................................
    //:::::::: Gain Matched + Calibrated Energies 
    //h1_energy_febex.resize(layer_number);
    //h1_energy_MWD.resize(layer_number);

    //dir_energy_febex_ch->cd();
    //:::::::::::Energy GM for layer 1 and 2
    // for (int i = 1; i < layer_number; i++) 
    // {

    //     h1_energy_febex[i].resize(xmax);

    //     for (int j = 0; j < xmax; j++)
    //     {
    //         h1_energy_febex[i][j].resize(ymax);

    //         for (int k = 0; k < ymax; k++)
    //         {   
                
    //            city = "";
    //            for (auto & detector : detector_mapping)
    //            {
    //                if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
    //                {
    //                    city = detector.second.first.second;
    //                    break;
    //                }
    //            }

    //             h1_energy_febex[i][j][k] = new TH1F(Form("energy_febex_%i%i%i", i, j, k), city.Data(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
    //             h1_energy_febex[i][j][k]->GetXaxis()->SetTitle("E(LISA) [mV]");
    //             h1_energy_febex[i][j][k]->SetLineColor(kBlue+1);
    //             h1_energy_febex[i][j][k]->Draw();
    //         }
    //     }

    // }

    //dir_energy_MWD_ch->cd();
    //:::::::::::Energy GM for layer 1 and 2
    // for (int i = 1; i < layer_number; i++) 
    // {

    //     h1_energy_MWD[i].resize(xmax);

    //     for (int j = 0; j < xmax; j++)
    //     {
    //         h1_energy_MWD[i][j].resize(ymax);

    //         for (int k = 0; k < ymax; k++)
    //         {   
    //             //general formula to place correctly on canvas for x,y coordinates
    //             //c_energy_layer_ch[i]->cd((ymax-(k+1))*xmax + j + 1);
                
    //            city = "";
    //            for (auto & detector : detector_mapping)
    //            {
    //                if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
    //                {
    //                    city = detector.second.first.second;
    //                    break;
    //                }
    //            }

    //             h1_energy_MWD[i][j][k] = new TH1F(Form("energy_MWD_%i%i%i", i, j, k), city.Data(), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
    //             h1_energy_MWD[i][j][k]->GetXaxis()->SetTitle("E(LISA) MWD [mV]");
    //             h1_energy_MWD[i][j][k]->SetLineColor(kBlue+1);
    //             h1_energy_MWD[i][j][k]->Draw();
    //         }
    //     }

    // }
    
    //Gain Matched + Calibrated with summed stats for layer
    //h1_energy_febex_layer.resize(layer_number);
    //h1_energy_MWD_layer.resize(layer_number);

    //dir_energy_febex->cd();
    //:::::::::::Energy for layer 1 and layer 2 (summed stats between detectors in layer)
    // for (int i = 0; i < layer_number; i++) 
    // {          
    //     h1_energy_febex_layer[i] = new TH1F(Form("h1_energy_febex_layer_%i", i), Form("energy_layer_%i", i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
    //     h1_energy_febex_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [mV]",i));
    //     h1_energy_febex_layer[i]->SetLineColor(i);
    //     h1_energy_febex_layer[i]->Draw(); 
    // }
  
    //::::::::::: Energy Layer i vs Layer i+1
    // h2_energy_layer1_vs_layer2 = new TH2F("h2_energy_layer1_vs_layer2", "E(Layer 1) vs E(Layer 2)", lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy); 
    // h2_energy_layer1_vs_layer2->SetOption("colz");
    // h2_energy_layer1_vs_layer2->GetXaxis()->SetTitle(Form("Energy - Layer 2 [MeV]"));
    // h2_energy_layer1_vs_layer2->GetYaxis()->SetTitle(Form("Energy - Layer 1 [MeV]"));    


    //dir_energy_MWD->cd();
    //:::::::::::Energy GM for layer 1 and layer 2 (summed stats between detectors in layer)
    // for (int i = 1; i < layer_number; i++) 
    // {          
    //     h1_energy_MWD_layer[i] = new TH1F(Form("h1_energy_MWD_layer_%i", i), Form("energy_layer_MWD_%i", i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
    //     h1_energy_MWD_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) MWD Layer %i [MeV]",i));
    //     h1_energy_MWD_layer[i]->SetLineColor(i);
    //     h1_energy_MWD_layer[i]->Draw();   
    // }

    // h2_energy_MWD_layer1_vs_layer2 = new TH2F("h2_energy_MWD_layer1_vs_layer2_GM", "E(Layer 1) vs E(Layer 2) MWD GM", lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD,lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD); 
    // h2_energy_MWD_layer1_vs_layer2->SetOption("colz");
    // h2_energy_MWD_layer1_vs_layer2->GetXaxis()->SetTitle(Form("Energy MWD - Layer 2 [MeV]"));
    // h2_energy_MWD_layer1_vs_layer2->GetYaxis()->SetTitle(Form("Energy MWD - Layer 1 [MeV]"));

    //::::::::::::Sum Energy Layer 1 vs Layer 2 GAIN MATCHED
    // h2_sum_energy_layer1_vs_layer2_GM = new TH2F("h2_sum_energy_layer1_vs_layer2_GM", "Sum E(Layer 1) vs Sum E(Layer 2) GM", lisa_config->bin_energy_GM*4, lisa_config->min_energy_GM*4, lisa_config->max_energy_GM*4,lisa_config->bin_energy_GM*4, lisa_config->min_energy_GM*4, lisa_config->max_energy_GM*4); 
    // h2_sum_energy_layer1_vs_layer2_GM->SetOption("colz");
    // h2_sum_energy_layer1_vs_layer2_GM->GetXaxis()->SetTitle(Form("Layer 2 E[MeV]"));
    // h2_sum_energy_layer1_vs_layer2_GM->GetYaxis()->SetTitle(Form("Layer 1 E[MeV]"));

    //::::::::::: E N E R G Y  VS  T I M E::::::::::::
    //dir_drift->cd();
    //::: Layer vs Time (WR)
    //h2_energy_layer_vs_time.resize(layer_number);
    //h2_energy_MWD_layer_vs_time.resize(layer_number);

    
    // for (int i = 0; i < layer_number; i++)
    // { 
    //     h2_energy_layer_vs_time[i] = MakeTH2(dir_drift, "F", Form("h2_energyGM_layer%i_vs_time",i), Form("E_GM(Layer %i) vs WR [min]",i), 500, 0, 10000, lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //     h2_energy_layer_vs_time[i]->SetTitle(Form("E_GM(Layer %i) vs WR",i));
    //     h2_energy_layer_vs_time[i]->GetYaxis()->SetTitle(Form("Energy GM Layer %i",i));
    //     h2_energy_layer_vs_time[i]->GetXaxis()->SetTitle("WR Time [min]");
    //     h2_energy_layer_vs_time[i]->Draw();
    
    //     h2_energy_MWD_layer_vs_time[i] = MakeTH2(dir_drift, "F", Form("h2_energyMWD_GM_layer%i_vs_time",i), Form("E_MWD_GM(Layer %i) vs WR [min]",i), 500, 0, 10000, lisa_config->bin_energy_MWD_GM, lisa_config->min_energy_MWD_GM, lisa_config->max_energy_MWD_GM);
    //     h2_energy_MWD_layer_vs_time[i]->SetTitle(Form("E_MWD_GM(Layer %i) vs WR",i));
    //     h2_energy_MWD_layer_vs_time[i]->GetYaxis()->SetTitle(Form("Energy MWD GM Layer %i",i));
    //     h2_energy_MWD_layer_vs_time[i]->GetXaxis()->SetTitle("WR Time [min]");
    //     h2_energy_MWD_layer_vs_time[i]->Draw();
    
    // }
    
    //::: Channel vs WR Time
    //h2_energy_ch_vs_time.resize(layer_number);
    //h2_energy_MWD_ch_vs_time.resize(layer_number);

    //dir_drift_ch->cd();
    //::::::::::::Energy vs WR Time - Eris and Sparrow
    // for (int i = 1; i < layer_number; i++)
    // {
    //     h2_energy_ch_vs_time[i].resize(xmax);
    //     h2_energy_MWD_ch_vs_time[i].resize(xmax);

    //     for (int j = 0; j < xmax; j++)
    //     {
    //         h2_energy_ch_vs_time[i][j].resize(ymax);
    //         h2_energy_MWD_ch_vs_time[i][j].resize(ymax);

    //         for (int k = 0; k < ymax; k++)
    //         {   
    //             // general formula to place correctly on canvas for x,y coordinates
    //             //c_energy_ch_vs_time[i]->cd((ymax-(k+1))*xmax + j + 1);
                
    //             city = "";
    //             for (auto & detector : detector_mapping)
    //             {
    //                 if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
    //                 {
    //                     city = detector.second.first.second;
    //                     break;
    //                 }
    //             }
                
    //             h2_energy_ch_vs_time[i][j][k] = MakeTH2(dir_drift_ch, "F", Form("h2_energyGM_ch_%d%d%d_vs_time",i,j,k), Form("E_GM ch %d%d%d vs WR [min]",i,j,k), 500, 0, 10000, lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //             h2_energy_ch_vs_time[i][j][k]->SetTitle(Form("E_GM(%d%d%d) vs WR",i,j,k));
    //             h2_energy_ch_vs_time[i][j][k]->GetYaxis()->SetTitle(Form("Energy %d%d%d",i,j,k));
    //             h2_energy_ch_vs_time[i][j][k]->GetXaxis()->SetTitle("WR Time [min]");
    //             h2_energy_ch_vs_time[i][j][k]->Draw();

    //             h2_energy_MWD_ch_vs_time[i][j][k] = MakeTH2(dir_drift_ch, "F", Form("h2_energyMWD_GM_ch_%d%d%d_vs_time",i,j,k), Form("E_MWD_GM ch %d%d%d vs WR [min]",i,j,k), 500, 0, 10000, lisa_config->bin_energy_MWD_GM, lisa_config->min_energy_MWD_GM, lisa_config->max_energy_MWD_GM);
    //             h2_energy_MWD_ch_vs_time[i][j][k]->SetTitle(Form("E_MWD_GM(%d%d%d) vs WR",i,j,k));
    //             h2_energy_MWD_ch_vs_time[i][j][k]->GetYaxis()->SetTitle(Form("Energy MWD %d%d%d",i,j,k));
    //             h2_energy_MWD_ch_vs_time[i][j][k]->GetXaxis()->SetTitle("WR Time [min]");
    //             h2_energy_MWD_ch_vs_time[i][j][k]->Draw();
    //         }
    //     }

    // }    


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

    //c4LOG(info, "end INIT " );

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

    //std::vector<float> sum_energy_layer;
    //sum_energy_layer.resize(layer_number);

    //float energy_ch[layer_number][xmax][ymax] = {0.0, 0.0, 0.0};
    //float energy_ch_GM[layer_number][xmax][ymax] = {0.0 ,0.0 ,0.0};
    //float energy_ch_MWD_GM[layer_number][xmax][ymax] = {0.0 ,0.0 ,0.0};

    //std::vector<float> sum_energy_layer_GM;
    //sum_energy_layer_GM.resize(layer_number);

    //std::vector<float> energy_layer_GM;
    //energy_layer_GM.resize(layer_number);

    //std::vector<float> energy_layer_MWD_GM;
    //energy_layer_MWD_GM.resize(layer_number);

    

    //c4LOG(info, "Comment to slow down program for testing");
    for (auto const & lisaCalItem : *lisaCalArray)
    {
        // For WR histos and experiment start
        wr_time = lisaCalItem.Get_wr_t();
        if (lisa_config->wr_enable == true) 
        {
            if (wr_time == 0)return; 
        }
        //if (wr_time == 0)return;
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
    
        //float energy_MWD = lisaCalItem.Get_energy_MWD();
        //float energy_MWD_GM = lisaCalItem.Get_energy_MWD_GM();

        std::vector<float> trace = lisaCalItem.Get_trace_febex();
        
        //uint64_t evtno = header->GetEventno();

        // Debugging data
        //c4LOG(info, "energy: " << energy << " energy GM: "<< energy_GM);

        
        // ::: FOR   R A T E S 
        detector_counter[layer-1][xpos][ypos]++;    //layers start from 1
        // ::: For Hit Patterns, multiplicity and energy vs ID
        int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        int hp_total_bin = (layer - 1) * xmax * ymax + hp_bin;
        //....................
        // ::: FOR     M U L T I P L I C I T Y  
        total_multiplicity++;
        multiplicity[layer-1]++;

        //::: F I L L   H I S T O S  :::

        // ::: Hit Pattern Total
        h1_hitpattern_total->Fill(hp_total_bin);
        //....................
        // ::: Hit Pattern by layer
        h1_hitpattern_layer[layer]->Fill(hp_bin);
        //....................
        // ::: Grids (hit pattern, pile up and overflow)
        h2_hitpattern_grid[layer-1]->Fill(xpos,ypos);
        if (pileup != 0) h2_pileup_grid[layer-1]->Fill(xpos,ypos);
        if (overflow != 0) h2_overflow_grid[layer-1]->Fill(xpos,ypos);        
        //....................
        // ::: Energy Febex per channel
        h1_energy_ch[layer-1][xpos][ypos]->Fill(energy_GM);
        //....................
        // ::: Energy Febex per layer
        h1_energy_layer[layer-1]->Fill(energy_GM);
        //....................
        // ::: Energy vs ID
        h2_energy_vs_ID_layer[layer-1]->Fill(hp_bin, energy_GM);
        h2_energy_vs_ID_total->Fill(hp_total_bin, energy_GM);

        //::::::::Define Sum Energy
        //sum_energy_layer[layer] += energy;
        //energy_ch[layer][xpos][ypos] = energy;

        //::::::::Define Sum Energy GM
        //sum_energy_layer_GM[layer] += energy_GM;
        //energy_ch_GM[layer][xpos][ypos] = energy_GM;
        //energy_layer_GM[layer] = energy_GM;

        //energy_ch_MWD_GM[layer][xpos][ypos] = energy_MWD_GM;
        //energy_layer_MWD_GM[layer] = energy_MWD_GM;
        
        //:::Fill Energy Gain Matched
        //h1_energy_febex[layer][xpos][ypos]->Fill(energy_GM);	    //energy per layer and channel
        //h1_energy_MWD[layer][xpos][ypos]->Fill(energy_MWD_GM);	    //energy per layer and channel
        //      Fill energy for each layer
        //h1_energy_febex_layer[layer]->Fill(energy_GM);			        //energy per layer
        //h1_energy_MWD_layer[layer]->Fill(energy_MWD_GM);	        
        
        //:::::::Energy vs Time
        //if (energy_GM > 0 && LISA_time_mins > 0)
        //{
            //c4LOG(info, "conditions on LISA time: " << LISA_time_mins << "and energy: " << energy_GM );
            //h2_energy_layer_vs_time[layer]->Fill(LISA_time_mins, energy_GM);
            //h2_energy_ch_vs_time[layer][xpos][ypos]->Fill(LISA_time_mins, energy_GM); 
        //}

        //:::::::Energy MWD vs Time
        //if (energy_MWD_GM > 0 && LISA_time_mins > 0)
        //{
            //c4LOG(info, "conditions on LISA time: " << LISA_time_mins << "and energy: " << energy_GM );
            //h2_energy_MWD_layer_vs_time[layer]->Fill(LISA_time_mins, energy_MWD_GM);
            //h2_energy_MWD_ch_vs_time[layer][xpos][ypos]->Fill(LISA_time_mins, energy_MWD_GM); 
        //}
            
        // :::: Fill traces febex
        if(lisa_config->trace_on)
        {
            for (int i = 0; i < trace.size(); i++)
            {   
                h2_traces_ch[layer-1][xpos][ypos]->Fill(i*0.01,trace[i]);
            }
        }

    
    }
    //c4LOG(info, "LISA_time_mins: " << LISA_time_mins << " wr time: "<< std::fixed << std::setprecision(10)<< wr_time);
    
    // ::: WR Time Difference
    if (lisa_config->wr_enable == true) 
    {
        if (wr_time == 0)return; 
    }
    //if ( wr_time == 0 ) return;
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

    //:::::::Fill Sum Energy::::::::::
    //h2_sum_energy_layer1_vs_layer2->Fill(sum_energy_layer[2],sum_energy_layer[1]);
        
    //:::::::Fill Sum Energy GM::::::::::
    //h2_sum_energy_layer1_vs_layer2_GM->Fill(sum_energy_layer_GM[2],sum_energy_layer_GM[1]);

    //:::::: Fill Energy GM for layers 1 and 2 ::::::::::
    //h2_energy_layer1_vs_layer2->Fill(energy_layer_GM[2],energy_layer_GM[1]);

    //:::::: Fill Energy MWD GM for layers 1 and 2 ::::::::::
    //h2_energy_MWD_layer1_vs_layer2_GM->Fill(energy_layer_MWD_GM[2],energy_layer_MWD_GM[1]);
        

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
