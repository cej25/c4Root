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
    num_layers = lisa_config->NLayers();

    dir_lisa->cd();
    dir_stats = dir_lisa->mkdir("Stats");
    dir_energy = dir_lisa->mkdir("Energy");
    dir_traces = dir_lisa->mkdir("Traces");

    c4LOG(info, "INIT Layer number" << layer_number);

      
    //:::::::::::White Rabbit:::::::::::::::
    // dir_stats->cd();
    // h1_wr_diff = new TH1I("h1_wr_diff", "WR Difference", lisa_config->bin_wr_diff, lisa_config->min_wr_diff, lisa_config->max_wr_diff);
    // h1_wr_diff->GetXaxis()->SetTitle("LISA WR Difference [ns]");
    // h1_wr_diff->SetLineColor(kBlack);
    // h1_wr_diff->SetFillColor(kRed-3);

    //:::::::::::H I T  P A T T E R N S:::::::::::::::
    //:::::::::::Total
    // dir_stats->cd();
    // h1_hitpattern_total = new TH1I("h1_hitpattern_total", "Hit Pattern", det_number, 0, det_number);
    // for (auto & detector : detector_mapping)
    // {
    //     int l = detector.second.first.first;
    //     city = detector.second.first.second;
    //     int x = detector.second.second.first; 
    //     int y = detector.second.second.second;
        
    //     h1_hitpattern_total->GetXaxis()->SetBinLabel(1, city.c_str());
    // }

    //:::::::::Layer
    c_hitpattern_layer = new TCanvas("c_hitpattern_layer", "Hit Pattern by Layer", 650, 350);
    c_hitpattern_layer->Divide(layer_number,1);
    h1_hitpattern_layer.resize(layer_number);
    
    for (int i = 0; i < layer_number; i++)
    {   
        c_hitpattern_layer->cd(i+1);
        h1_hitpattern_layer[i] = new TH1I(Form("h1_hitpattern_layer_%i", i), Form("Hit Pattern - Layer: %i", i), xmax * ymax, 0, xmax * ymax);
        //h1_hitpattern_layer[i]->SetStats(0);
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
    c_hitpattern_grid->Divide(layer_number);
    h2_hitpattern_grid.resize(layer_number);
    c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_hitpattern_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
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
        gPad->SetLogz();
    }
    
    c_hitpattern_grid->cd();
    dir_stats->Append(c_hitpattern_grid);

    //:::::::::::P I L E   U P::::::::::::
    dir_stats->cd();
    c_pileup_grid = new TCanvas("c_pileup_grid", "Pileup Grid", 650, 350);
    c_pileup_grid->Divide(layer_number);
    h2_pileup_grid.resize(layer_number);
    c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_pileup_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_pileup_grid[i] = new TH2F(Form("h2_pileup_grid_layer_%i", i), Form("Pile Up Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_pileup_grid[i]->SetStats(0);
        h2_pileup_grid[i]->Draw("COLZ");
        h2_pileup_grid[i]->GetXaxis()->SetTitle(Form("Pile Up Layer %i",i+1));
        h2_pileup_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetXaxis()->SetTickLength(0);
        h2_pileup_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_pileup_grid[i]->GetYaxis()->SetTickLength(0);
        h2_pileup_grid[i]->SetMinimum(1);
        gPad->SetLogz();
        
    }
    
    c_pileup_grid->cd();
    dir_stats->Append(c_pileup_grid);

    //:::::::::::O V E R   F L O W:::::::::::
    dir_stats->cd();
    c_overflow_grid = new TCanvas("c_overflow_grid", "Overflow Grid", 650, 350);
    c_pileup_grid->Divide(layer_number);
    h2_overflow_grid.resize(layer_number);
    c_hitpattern_grid->SetLogz();

    for (int i = 0; i < layer_number; i++)
    {   

        c_overflow_grid->cd(i+1);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.15);
        h2_overflow_grid[i] = new TH2F(Form("h2_overflow_grid_layer_%i", i), Form("Overflow Grid - Layer %i", i+1), xmax, 0, xmax, ymax, 0, ymax);
        h2_overflow_grid[i]->SetStats(0);
        h2_overflow_grid[i]->Draw("COLZ");
        h2_overflow_grid[i]->GetXaxis()->SetTitle(Form("Overflow Layer %i",i+1));
        h2_overflow_grid[i]->GetXaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetXaxis()->SetTickLength(0);
        h2_overflow_grid[i]->GetYaxis()->SetLabelSize(0);
        h2_overflow_grid[i]->GetYaxis()->SetTickLength(0);
        h2_overflow_grid[i]->SetMinimum(1);
        gPad->SetLogz();
        
    }
    
    c_overflow_grid->cd();
    dir_stats->Append(c_overflow_grid);
    //:::::::::::M U L T I P L I C I T Y:::::::::::::::

    // //:::::::::::Total Multiplicity
    // h1_multiplicity = new TH1I("h1_multiplicity", "Total Multiplicity", det_number, 0, det_number+1);
    // h1_multiplicity->SetStats(0);
    
    // //:::::::::::Multiplicity per layer
    // c_multiplicity_layer = new TCanvas("c_multiplicity_layer", "Multiplicty by Layer", 650, 350);
    // c_multiplicity_layer->Divide(2, (layer_number + 1)/2);
    // h1_multiplicity_layer.resize(layer_number);
    // for (int i = 0; i < layer_number; i++)
    // {
    //     c_multiplicity_layer->cd(i+1);
    //     h1_multiplicity_layer[i] = new TH1I(Form("Multiplicity_Layer_%i",i), Form("Multiplicity Layer %i",i), xmax * ymax+1, 0, xmax * ymax+1);
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

    //:::::::::::Energy canvas for all layers
    for (int i = 0; i < layer_number; i++) //create a canvas for each layer
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
                //general formula to place correctly on canvas for x,y coordinates
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

                h1_energy_layer_ch[i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i", city.c_str(), i, j, k), city.c_str(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h1_energy_layer_ch[i][j][k]->GetXaxis()->SetTitle("ADC [a.u.]");
                h1_energy_layer_ch[i][j][k]->SetLineColor(kBlue+1);
                h1_energy_layer_ch[i][j][k]->SetFillColor(kOrange-3);
                h1_energy_layer_ch[i][j][k]->Draw();
            }
        }
        c_energy_layer_ch[i]->cd(0);
        dir_energy->Append(c_energy_layer_ch[i]);

    }
      

    // //::::::::::: E N E R G Y  VS  E V T N O ::::::::::::
    // dir_energy->cd();
    // c_energy_layer_vs_evtno = new TCanvas("c_energy_layer_vs_evtno","c_energy_layer_vs_evtno", 650,350);
    // c_energy_layer_vs_evtno->Divide(layer_number,1);
    // h2_energy_layer_vs_evtno.resize(layer_number);

    // for (int i = 0; i < layer_number; i++)
    // {
    //     c_energy_layer_vs_evtno->cd(i+1);
    //     h2_energy_layer_vs_evtno[i] = new TH2F(Form("h2_energy_layer_%i_vs_evtno", i), Form("Energy Layer %i vs WR", i));
    //     h2_energy_layer_vs_evtno[i]->Draw("COLZ");
    //     h2_energy_layer_vs_evtno[i]->GetXaxis()->SetTitle(Form("EVTno - Layer %i",i));
    //     //gPad->SetLogz();
    
    // }
    
    // c_energy_layer_vs_evtno->cd(0);
    // dir_energy->Append(c_energy_layer_vs_evtno);
    
    //:::::::::::::T R A C E S:::::::::::::::::
    dir_traces->cd();
    c_traces_layer_ch.resize(layer_number);
    h1_traces_layer_ch.resize(layer_number);

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
                    if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }

                h1_traces_layer_ch[i][j][k] = new TH1F(Form("traces_%s_%i_%i_%i", city.c_str(), i, j, k), city.c_str(), 2000, 0, 20);
                h1_traces_layer_ch[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                h1_traces_layer_ch[i][j][k]->SetMinimum(lisa_config->AmplitudeMin);
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

    c_traces_layer_ch_stat.resize(layer_number);
    h2_traces_layer_ch_stat.resize(layer_number);

    for (int i = 0; i < layer_number; i++) 
    {
        c_traces_layer_ch_stat[i] = new TCanvas(Form("c_traces_layer_%d_stat",i),Form("c_traces_layer_%d_stat",i), 650,350);
        c_traces_layer_ch_stat[i]->SetTitle(Form("Layer %d - Traces",i));
        c_traces_layer_ch_stat[i]->Divide(xmax,ymax); 
        h2_traces_layer_ch_stat[i].resize(xmax);
        for (int j = 0; j < xmax; j++)
        {
            h2_traces_layer_ch_stat[i][j].resize(ymax);
            for (int k = 0; k < ymax; k++)
            {   
                // general formula to place correctly on canvas for x,y coordinates
                c_traces_layer_ch_stat[i]->cd((ymax-(k+1))*xmax + j + 1);
                
                city = "";
                for (auto & detector : detector_mapping)
                {
                    if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }

                h2_traces_layer_ch_stat[i][j][k] = new TH2F(Form("traces_%s_%i_%i_%i_stat", city.c_str(), i, j, k), city.c_str(), 1000, 0, 20,5000,3000,20000);
                h2_traces_layer_ch_stat[i][j][k]->GetXaxis()->SetTitle("Time [us]");
                h2_traces_layer_ch_stat[i][j][k]->SetMinimum(lisa_config->AmplitudeMin);
                h2_traces_layer_ch_stat[i][j][k]->SetMaximum(lisa_config->AmplitudeMax);
                h2_traces_layer_ch_stat[i][j][k]->SetLineColor(kBlue+1);
                h2_traces_layer_ch_stat[i][j][k]->SetFillColor(kOrange-3);
                h2_traces_layer_ch_stat[i][j][k]->Draw("colz");
                gPad->SetLogz();
            }
        }
        c_traces_layer_ch_stat[i]->cd(0);
        dir_traces->Append(c_traces_layer_ch_stat[i]);

    }

    return kSUCCESS;
}


void LisaNearlineSpectraDaq::Exec(Option_t* option)
{   
    wr_time = 0;
    int multiplicity[layer_number] = {0};
    int total_multiplicity = 0;

    std::vector<uint32_t> sum_energy_layer;
    sum_energy_layer.resize(layer_number);
    int energy_ch[layer_number][xmax][ymax] = {0,0,0};

    //int energy_ch_GM[layer_number][xmax][ymax] = {0,0,0};

    std::vector<uint32_t> sum_energy_layer_GM;
    sum_energy_layer_GM.resize(layer_number);

    std::vector<uint32_t> energy_layer_GM;
    energy_layer_GM.resize(layer_number);


    //c4LOG(info, "Comment to slow down program for testing");
    for (auto const & lisaCalItem : *lisaCalArray)
    {


        //wr_time = lisaCalItem.Get_wr_t();
        //if (wr_time == 0)return;

        //::::::: Retrieve Data ::::::::::::::
        layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        uint32_t energy = lisaCalItem.Get_energy();
        std::vector<uint16_t> trace = lisaCalItem.Get_trace();
        double energy_GM = lisaCalItem.Get_energy_GM();
        int pileup = lisaCalItem.Get_pileup();
        int overflow = lisaCalItem.Get_overflow();
        uint64_t evtno = header->GetEventno();
                
        //::::::::F I L L   H I S T O S:::::::
        //:::::::: H I T  P A T T E R N ::::::::::
        //:::::::::Layer
        // int hp_bin = (ymax-(ypos+1))*xmax + xpos; // -1 compared to canvas position
        // h1_hitpattern_layer[layer]->Fill(hp_bin);
        //:::::::::Total
        //int hp_total_bin;
        //hp_total_bin = layer * xmax * ymax + hp_bin - 3; 
        //h1_hitpattern_total->Fill(hp_total_bin);
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

        //::::::::: E N E R G Y :::::::::::::::
        
        //::::::::Define Sum Energy
        sum_energy_layer[layer] += energy;
        energy_ch[layer][xpos][ypos] = energy;

        //::::Fill Energy Raw
        h1_energy_layer_ch[layer][xpos][ypos]->Fill(energy);

        //::::::::Define Sum Energy GM
        //energy_ch_GM[layer][xpos][ypos] = energy_GM;
        
        //:::Fill Energy Gain Matched
        //h1_energy_layer_ch_GM[layer][xpos][ypos]->Fill(energy_GM);	//energy per layer and channel
        //h1_energy_layer[layer]->Fill(energy);			                //energy per layer
                
        //::::::::: Fill Traces ::::::::::::::
        for (int i = 0; i < trace.size(); i++)
        {
            if(layer==1)
            {
                //c4LOG(info, "EXEC Layer number" << layer_number << " layer id :" << layer);
            }
            
            h1_traces_layer_ch[layer][xpos][ypos]->SetBinContent(i, trace[i]);
            //c4LOG(info, "layer: " << layer << " x max: " << xmax << " ymax: " << ymax);
	        h2_traces_layer_ch_stat[layer][xpos][ypos]->Fill(i*0.01,trace[i]);

        }

    }
    //c4LOG(info, "::::::::::END LOOP::::::::::::" << " Layer number :" << layer_number);

    //if ( wr_time == 0 ) return;

    //:::::: WR Time Difference
    // if( prev_wr > 0 )
    // {
    //     wr_diff = wr_time - prev_wr; //to express wr difference in us
    //     h1_wr_diff->Fill(wr_diff);
    // }
    // prev_wr = wr_time;
    //c4LOG(info,"wr time: " << wr_time << "   prev wr: " << prev_wr << " wr diff: " << wr_diff);


    //::::::: Fill Multiplicity ::::::::::
    // for (int i = 0; i < layer_number; i++) h1_multiplicity_layer[i]->Fill(multiplicity[i]);
    // h1_multiplicity->Fill(total_multiplicity);

    // for (int i = 0; i < layer_number; i++)
    // {
    //     if(multiplicity[i] != 0) h1_layer_multiplicity->Fill(i);
    //     //c4LOG(info," layer number : " << layer_number << " layer : " << layer << " multiplicity [layer] : " << multiplicity[layer] << " multiplicity [i] : " << multiplicity[i]);
    // }


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
