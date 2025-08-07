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
#include "LisaNearlineSpectraDaq.h"
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

LisaNearlineSpectraDaq::LisaNearlineSpectraDaq()  :   LisaNearlineSpectraDaq("LisaNearlineSpectraDaq")
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaNearlineSpectraDaq::LisaNearlineSpectraDaq(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaNearlineSpectraDaq::~LisaNearlineSpectraDaq()
{
    c4LOG(info, "");
}

void LisaNearlineSpectraDaq::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaNearlineSpectraDaq::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");    
    c4LOG_IF(fatal, !header, "Branch EventHeader. not found");

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
    num_layers = lisa_config->NLayers();

    dir_lisa->cd();

    dir_stats = dir_lisa->mkdir("Stats");
    
    dir_energy = dir_lisa->mkdir("Energy");
    dir_febex = dir_energy->mkdir("Febex");
    dir_febex_channel = dir_febex->mkdir("Channels");
    dir_energy_MWD = dir_energy->mkdir("MWD");
    dir_MWD_channel = dir_energy_MWD->mkdir("Channels");

    dir_traces = dir_lisa->mkdir("Traces");
    
    dir_drift = dir_lisa->mkdir("Drift");

    c4LOG(info, "INIT Layer number" << layer_number);
    
    int traces_max = lisa_config->amplitude_max;
    int traces_min = lisa_config->amplitude_min;
    int traces_bin = (traces_max - traces_min)/2;

    //c4LOG(info, "INIT hit pattern");
    // ::: H I T  P A T T E R N S
    //     Total
    dir_stats->cd();
    // h1_hitpattern_total = new TH1I("h1_hitpattern_total", "Hit Pattern", det_number, 0, det_number);
    // for (auto & detector : detector_mapping)
    // {
    //     int l = detector.second.first.first;
    //     city = detector.second.first.second;
    //     int x = detector.second.second.first; 
    //     int y = detector.second.second.second;
    //     int h_bin = (ymax - (y + 1)) * xmax + x;
    //     int h_total_bin = (l - 1) * xmax * ymax + h_bin;
        
    //     h1_hitpattern_total->GetXaxis()->SetBinLabel(h_total_bin + 1 , city.c_str());

    // }
    //c4LOG(info, "INIT layer");
    //     Layer
    h1_hitpattern_layer.resize(layer_number);
    
    for (int i = 1; i < layer_number; i++)
    {   

        h1_hitpattern_layer[i] = new TH1I(Form("h1_hitpattern_layer_%i", i), Form("Hit Pattern - Layer: %i", i), xmax * ymax, 0, xmax * ymax);
      
        for (int j = 0; j < xmax * ymax; j++)
        {
            city = "";
            for (auto & detector : detector_mapping)
            {
                int x = detector.second.second.first; 
                int y = detector.second.second.second;
                if (detector.second.first.first == i +1 && ((ymax-(y+1))*xmax + x) == j)
                {
                    city = detector.second.first.second;
                    break;
                }
            }
            h1_hitpattern_layer[i]->GetXaxis()->SetBinLabel(j+1, city.c_str());
        }
       
    }
    //c4LOG(info, "INIT grid");
    //::: G R I D S 
    dir_stats->cd();
    h2_hitpattern_grid.resize(layer_number);
    //c4LOG(info, "INIT grid2");
    for (int i = 0; i < layer_number; i++)
    {   
        //c4LOG(info, "INIT grid3");
        h2_hitpattern_grid[i] = new TH2F(Form("h2_hitpattern_grid_layer_%i", i+1), Form("Hit Pattern Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_hitpattern_grid[i]->SetStats(0);
        h2_hitpattern_grid[i]->SetOption("colz");
        h2_hitpattern_grid[i]->GetXaxis()->SetTitle(Form("Hit Pattern Layer %i",i+1));
        h2_hitpattern_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetXaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_hitpattern_grid[i]->GetYaxis()->SetTickLength(0);
        h2_hitpattern_grid[i]->SetMinimum(1);
        //h2_hitpattern_grid[i]->SetContour(100);
        
    }
    //c4LOG(info, "INIT pileup");
    //     P I L E   U P
    dir_stats->cd();
    h2_pileup_grid.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {   

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
    //c4LOG(info, "INIT overflow");
    //     O V E R   F L O W
    dir_stats->cd();
    h2_overflow_grid.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {   

        h2_overflow_grid[i] = new TH2F(Form("h2_overflow_grid_layer_%i", i+1), Form("Over Flow Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_overflow_grid[i]->SetStats(0);
        h2_overflow_grid[i]->SetOption("COLZ");
        h2_overflow_grid[i]->GetXaxis()->SetTitle(Form("Over Flow Layer %i",i+1));
        h2_overflow_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetXaxis()->SetTickLength(0);
        h2_overflow_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetYaxis()->SetTickLength(0);
        h2_overflow_grid[i]->SetMinimum(1);
        h2_pileup_grid[i]->SetContour(100);
        
    }

    // ::: Multiplicity
    //c4LOG(info, "INIT multiplicity");
    //     Total Multiplicity
    h1_multiplicity = new TH1I("h1_multiplicity", "Total Multiplicity", det_number+1, -0.5, det_number+0.5);
    
    //     Multiplicity per layer
    h1_multiplicity_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h1_multiplicity_layer[i] = new TH1I(Form("Multiplicity_Layer_%i",i), Form("Multiplicity Layer %i",i), xmax * ymax+1, -0.5, xmax * ymax+0.5);

    }
  
    //     Layer Multiplicity
    h1_layer_multiplicity = new TH1I("h1_layer_multiplicity", "Layer Multiplicity", layer_number+1, -0.5, layer_number+0.5);

    //...................................END OF STATS 
    //c4LOG(info, "INIT energy");
    // ::: E N E R G Y :::
    dir_energy->cd();
    //     Febex per channel
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

                h1_energy_ch[i][j][k] = new TH1F(Form("energy_%s_%i%i%i", city.c_str(), i+1, j, k), city.c_str(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h1_energy_ch[i][j][k]->GetXaxis()->SetTitle("ADC [a.u.]");
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
    
    
    // :::  M W D   E N E R G Y
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

                h1_energy_MWD_ch[i][j][k] = new TH1F(Form("energy_MWD_%s_%i%i%i", city.c_str(), i+1, j, k), city.c_str(), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
                h1_energy_MWD_ch[i][j][k]->GetXaxis()->SetTitle("Charge [mV]");
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
    
       
    //::::::::::: E N E R G Y  VS  E V T N O ::::::::::::
    dir_drift->cd();
    //::: Layer vs Time (WR)
    h2_energy_ch_vs_evtno.resize(layer_number);
    h2_energy_MWD_ch_vs_evtno.resize(layer_number);

    for (int i = 0; i < layer_number; i++)
    {
        h2_energy_ch_vs_evtno[i].resize(xmax);
        h2_energy_MWD_ch_vs_evtno[i].resize(xmax);

        for (int j = 0; j < xmax; j++)
        {
            h2_energy_ch_vs_evtno[i][j].resize(ymax);
            h2_energy_MWD_ch_vs_evtno[i][j].resize(ymax);

            for (int k = 0; k < ymax; k++)
            {   
                
                city = "";
                for (auto & detector : detector_mapping)
                {
                    if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }
                
                h2_energy_ch_vs_evtno[i][j][k] = MakeTH2(dir_drift, "F", Form("h2_energy_ch_%d%d%d_vs_evtno",i,j,k), Form("E %d%d%d vs EVTno ",i,j,k), 1000, lisa_config->start_evtno, lisa_config->stop_evtno, lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h2_energy_ch_vs_evtno[i][j][k]->SetTitle(Form("E(%d%d%d) vs EVTno",i,j,k));
                h2_energy_ch_vs_evtno[i][j][k]->GetYaxis()->SetTitle(Form("Energy %d%d%d",i,j,k));
                h2_energy_ch_vs_evtno[i][j][k]->GetXaxis()->SetTitle("EVTno");

                h2_energy_MWD_ch_vs_evtno[i][j][k] = MakeTH2(dir_drift, "F", Form("h2_energyMWD_ch_%d%d%d_vs_evtno",i,j,k), Form("E_MWD_GM ch %d%d%d vs EVTno ",i,j,k), 1000, lisa_config->start_evtno, lisa_config->stop_evtno, lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
                h2_energy_MWD_ch_vs_evtno[i][j][k]->SetTitle(Form("E_MWD(%d%d%d) vs EVTno",i,j,k));
                h2_energy_MWD_ch_vs_evtno[i][j][k]->GetYaxis()->SetTitle(Form("Energy MWD %d%d%d",i,j,k));
                h2_energy_MWD_ch_vs_evtno[i][j][k]->GetXaxis()->SetTitle("EVtno");

            }
        }

    }
    
    // ::: T R A C E S :::
    if(lisa_config->trace_on)
    {
        dir_traces->cd();
        h2_traces_layer_ch.resize(layer_number);
        for (int i = 0; i < layer_number; i++) 
        {

            h2_traces_layer_ch[i].resize(xmax);
            for (int j = 0; j < xmax; j++)
            {
                h2_traces_layer_ch[i][j].resize(ymax);
                for (int k = 0; k < ymax; k++)
                {                   
                    city = "";
                    for (auto & detector : detector_mapping)
                    {
                        int x = detector.second.first.first;
                        int y = detector.second.second.second;
                        int l_id = detector.second.first.first;
                        if (l_id == i && x == j && y == k)
                        {
                            city = detector.second.first.second;
                            break;
                        }
                    }

                    h2_traces_layer_ch[i][j][k] = new TH2F(Form("h2_traces_%s_%i%i%i_stat", city.c_str(), i+1, j, k), city.c_str(), lisa_config->bin_traces, lisa_config->min_traces, lisa_config->max_traces,traces_bin,traces_min,traces_max);
                    h2_traces_layer_ch[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                    h2_traces_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                    h2_traces_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                    h2_traces_layer_ch[i][j][k]->SetOption("colz");
                }
            }
 

        }    
    }
    return kSUCCESS;
}


void LisaNearlineSpectraDaq::Exec(Option_t* option)
{   
    wr_time = 0;
    int multiplicity[layer_number] = {0};
    int total_multiplicity = 0;


    for (auto const & lisaCalItem : *lisaCalArray)
    {

        //::::::: Retrieve Data ::::::::::::::
        layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        
        float energy = lisaCalItem.Get_energy();
        float energy_MWD = lisaCalItem.Get_energy_MWD();
        float energy_GM = lisaCalItem.Get_energy_GM(); 
        float energy_MWD_GM = lisaCalItem.Get_energy_MWD_GM();
        
        std::vector<float> trace = lisaCalItem.Get_trace_febex();
        
        int pileup = lisaCalItem.Get_pileup();
        int overflow = lisaCalItem.Get_overflow();
        uint64_t evtno = header->GetEventno();
                
                
        // ::: For Hit Patterns, multiplicity and energy vs ID
        int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        int hp_total_bin = (layer - 1) * xmax * ymax + hp_bin;
        // ::: FOR     M U L T I P L I C I T Y  
        total_multiplicity++;
        multiplicity[layer-1]++;
        //....................
        // ::: Hit Pattern by layer
        h1_hitpattern_layer[layer]->Fill(hp_bin);
        //....................
        // ::: Grids (hit pattern, pile up and overflow)
        h2_hitpattern_grid[layer-1]->Fill(xpos,ypos);
        if (pileup != 0) h2_pileup_grid[layer-1]->Fill(xpos,ypos);
        if (overflow != 0) h2_overflow_grid[layer-1]->Fill(xpos,ypos);
        
        
        // ::: E N E R G Y :::

        // ::: Fill energy channels :::
        //     Febex
        // ::: Energy Febex per channel
        h1_energy_ch[layer-1][xpos][ypos]->Fill(energy_GM);
        //     MWD
        // ::: Energy MWD per channel
        h1_energy_MWD_ch[layer-1][xpos][ypos]->Fill(energy_MWD_GM);
       
            
        //     Febex
        // ::: Energy Febex per layer
        h1_energy_layer[layer-1]->Fill(energy_GM);
        //     MWD
        // ::: Energy MWD per layer
        h1_energy_MWD_layer[layer-1]->Fill(energy_MWD_GM);	            
                
        //::::::::: Fill Traces ::::::::::::::
        // :::: Fill traces histos febex
        if(lisa_config->trace_on)
        {
            for (int i = 0; i < trace.size(); i++)
            {   
                h2_traces_layer_ch[layer-1][xpos][ypos]->Fill(i*0.01,trace[i]);
            }
        }

        //Energy vs TIME
        h2_energy_ch_vs_evtno[layer][xpos][ypos]->Fill(evtno, energy); 
        h2_energy_MWD_ch_vs_evtno[layer][xpos][ypos]->Fill(evtno, energy_MWD); 


    }
    //c4LOG(info, "::::::::::END LOOP::::::::::::" << " Layer number :" << layer_number);

    //::::::: Fill Multiplicity ::::::::::
    for (int i = 0; i < layer_number; i++) h1_multiplicity_layer[i]->Fill(multiplicity[i]);
    h1_multiplicity->Fill(total_multiplicity);

    for (int i = 0; i < layer_number; i++)
    {
        if(multiplicity[i] != 0) h1_layer_multiplicity->Fill(i);
    }

    // for(int i = 0; i < layer_number; i++)
    // {
    //     c4LOG(info,"multiplicity : "<< multiplicity[i] << " i : " << i );
    // }


    fNEvents += 1;
}

void LisaNearlineSpectraDaq::FinishEvent()
{

}

void LisaNearlineSpectraDaq::FinishTask()
{

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "LISA events : " << fNEvents);


}

ClassImp(LisaNearlineSpectraDaq)
