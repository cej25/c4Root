// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "AnalysisTools.h"
#include "StefanNearlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"

// ROOT
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <cmath>
#include <sstream>
#include "TFile.h"
#include <chrono>

StefanNearlineSpectra::StefanNearlineSpectra() : StefanNearlineSpectra("StefanNearlineSpectra")
{

}


StefanNearlineSpectra::StefanNearlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    // stuff
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   StefanHit(nullptr)
{
    stefan_config = TStefanConfiguration::GetInstance();

}

StefanNearlineSpectra::~StefanNearlineSpectra()
{
    c4LOG(info, "Destroyed StefanNearlineSpectra properly.");
}

InitStatus StefanNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found!");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found!");

    // stefan failure is fatal foe now, altough we could turn this into a complete "HISPEC10" task, and just make it a warning
    StefanHit = mgr->InitObjectAs<decltype(StefanHit)>("StefanHitData");
    c4LOG_IF(fatal, !StefanHit, "Branch StefanHitData not found - no correlations with Stefan possible!");

    // correlations
    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksAnaData");
    c4LOG_IF(warn, !fHitsMCP, "Branch H10MCPTwinpeaksAnaData not found - no correlations with MCPs possible!");
    hitArray = mgr->InitObjectAs<decltype(hitArray)>("FrsHitData");
    c4LOG_IF(warn, !hitArray, "Branch FrsHitData not found - no correlations with FRS (TAC) possible!");
    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(warn, !multihitArray, "Branch FrsMultiHitData not found - no correlations with FRS (MHTDC) possible!");


    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_stefan = gDirectory->mkdir("Stefan");
    gDirectory->cd("Stefan");


    int num_dssds = stefan_config->DSSDs();
    int n_sides = 2;

    dir_dssd = new TDirectory*[num_dssds];
    dir_stats = new TDirectory*[num_dssds];
    dir_hits = new TDirectory*[num_dssds];
    
    dir_raw.resize(num_dssds);
    dir_pixel.resize(num_dssds);
    
    double max_energy= pow(10,7);
    h2_hit_strip_xy.resize(num_dssds);
    h1_raw_energy.resize(num_dssds); // h1_raw_energy[dssd#][side#][ch#]
    h1_pixel_energy.resize(num_dssds); // h1_pixel_energy[dssd#][pixel#]
    
    
    for (int i = 0; i < num_dssds; i++)
    {	
	if(i==1) max_energy = pow(10,5);
    	dir_raw[i].resize(n_sides);
    	dir_raw[i][0] = new TDirectory;
    	dir_raw[i][1] = new TDirectory;
    	
    	dir_pixel[i] = new TDirectory;
    	
    	h1_raw_energy[i].resize(2); //two sides
    	h1_raw_energy[i][0].resize(16);
    	h1_raw_energy[i][1].resize(16);
    	
        dir_dssd[i] = dir_stefan->mkdir(Form("DSSD%i",i));
        dir_hits[i] = dir_dssd[i]->mkdir("Hits");
        h2_hit_strip_xy[i] = MakeTH2(dir_hits[i], "I", Form("h2_hit_strip_xy_dssd%d", i) , Form("XY Hit Pattern DSSD %d", i), 16, 0, 16, 16, 0, 16);
        
	dir_raw[i][0] = dir_dssd[i]->mkdir("Raw_energy_vertical");
	
        for(int j=0; j<16; ++j) { //vertical strips or stripY
        	h1_raw_energy[i][0][j] = MakeTH1(dir_raw[i][0], "I", Form("h1_raw_energy_det%i_vertical_strip%i", i, j), Form("Raw Energy - Det %i Vertical side - Strip %i", i, j), 10000, 0, max_energy, "E []", kCyan, kBlack);
        	}
        
	dir_raw[i][1] = dir_dssd[i]->mkdir("Raw_energy_horizontal");
        for(int j=0; j<16; ++j) {//horizontal strips or stripX
        	h1_raw_energy[i][1][j] = MakeTH1(dir_raw[i][1], "I", Form("h1_raw_energy_det%i_horizontal_strip%i", i, j), Form("Raw Energy - Det %i Horizontal side - Strip %i", i, j), 10000, 0, max_energy, "E []", kSpring, kBlack);
        	}
        
        dir_pixel[i] = dir_dssd[i]->mkdir("Pixels_energy");
        h1_pixel_energy[i].resize(256);
        
       for(int j=0; j<256; ++j) { // pixel = stripX+16*stripY
        	h1_pixel_energy[i][j] = MakeTH1(dir_pixel[i], "I", Form("h1_energy_pixel%i", j), Form("Energy - Det %i Pixel %i", i, j), 10000, 0, pow(10,7), "E []", kOrange, kBlack);
        	}
        	strips4_stefan = new TCanvas("strips4_stefan","4 stefan strips",650,350);
        	strips4_stefan->Divide(2,2);
        	strips4_stefan->cd(1);
        	h1_raw_energy[0][0][12]->Draw();
        	strips4_stefan->cd(2);
        	h1_raw_energy[0][0][15]->Draw();
        	strips4_stefan->cd(3);
        	h1_raw_energy[0][1][2]->Draw();
        	strips4_stefan->cd(4);
        	h1_raw_energy[0][1][12]->Draw();
        	
    }

    // corr
        // mcp vs stefan
            // dssd breakdown
                // 2d hists
                // strip breakdown
                    // 2d hists
        // frs vs stefan
            // tof 
                // dssd breakdown
                    // 2d hist
                    // strip breakdown
                        // 2d hist
            // z
                // dssd breakdown
                    // 2d hist
                    // strip breakdown
                        // 2d hist
        // frs vs mcp
            // 2d hist

    dir_corr = dir_stefan->mkdir("Correlations");
    

    
    if (fHitsMCP)
    {
        dir_mcp_stefan = dir_corr->mkdir("MCP_vs_STEFAN");
        dir_mcp_stefan_dssds = new TDirectory*[num_dssds];
        dir_mcp_stefan_dssds_strips = new TDirectory*[num_dssds];
        for (int i = 0; i < num_dssds; i++)
        {
            dir_mcp_stefan_dssds[i] = dir_mcp_stefan->mkdir(Form("DSSD%i", i));
            dir_mcp_stefan_dssds_strips[i] = dir_mcp_stefan_dssds[i]->mkdir("Strips");
        }

        h2_mcp_tof_vs_e_dssd.resize(num_dssds);
        h2_mcp_tof_vs_e_vertical_strip.resize(num_dssds);
        h2_mcp_tof_vs_e_horizontal_strip.resize(num_dssds);

        for (int i = 0; i < num_dssds; i++)
        {
            h2_mcp_tof_vs_e_dssd[i] = MakeTH2(dir_mcp_stefan_dssds[i], "D", Form("h2_mcp_tof_vs_e_dssd_%i", i), Form("MCP TOF vs DSSD %i E", i), 1000, -100, 100, 750, 0, 5000000);

            h2_mcp_tof_vs_e_vertical_strip[i].resize(16);
            h2_mcp_tof_vs_e_horizontal_strip[i].resize(16);
            for (int j = 0; j < 16; j++)
            {
                h2_mcp_tof_vs_e_vertical_strip[i][j] = MakeTH2(dir_mcp_stefan_dssds_strips[i], "D", Form("h2_mcp_tof_vs_e_dssd_%i_vertical_strip_%i", i, j), Form("MCP TOF vs DSSD %i Veritcal Strip %i E", i, j), 1000, -100, 100, 750, 0, 5000000);
                h2_mcp_tof_vs_e_horizontal_strip[i][j] = MakeTH2(dir_mcp_stefan_dssds_strips[i], "D", Form("h2_mcp_tof_vs_e_dssd_%i_horizontal_strip_%i", i, j), Form("MCP TOF vs DSSD %i Horizontal Strip %i E", i, j), 1000, -100, 100, 750, 0, 5000000);
            }
        }
    }


    if (multihitArray)
    {
        dir_frs_stefan = dir_corr->mkdir("FRS_vs_STEFAN");
        dir_frs_tof_stefan = dir_frs_stefan->mkdir("TOF");
        dir_frs_z_stefan = dir_frs_stefan->mkdir("Z");
        dir_frs_tof_stefan_dssds = new TDirectory*[num_dssds];
        dir_frs_tof_stefan_dssds_strips = new TDirectory*[num_dssds];
        dir_frs_z_stefan_dssds = new TDirectory*[num_dssds];
        dir_frs_z_stefan_dssds_strips = new TDirectory*[num_dssds];

        for (int i = 0; i < num_dssds; i++)
        {
            dir_frs_tof_stefan_dssds[i] = dir_frs_tof_stefan->mkdir(Form("DSSD%i", i));
            dir_frs_tof_stefan_dssds_strips[i] = dir_frs_tof_stefan_dssds[i]->mkdir("Strips");
            dir_frs_z_stefan_dssds[i] = dir_frs_z_stefan->mkdir(Form("DSSD%i", i));
            dir_frs_z_stefan_dssds_strips[i] = dir_frs_z_stefan_dssds[i]->mkdir("Strips");
        }

        h2_s2s4_tof_vs_e_dssd.resize(num_dssds);
        h2_s2s4_tof_vs_e_vertical_strip.resize(num_dssds);
        h2_s2s4_tof_vs_e_horizontal_strip.resize(num_dssds);
        h2_z41_vs_e_dssd.resize(num_dssds);
        h2_z41_vs_e_vertical_strip.resize(num_dssds);
        h2_z41_vs_e_horizontal_strip.resize(num_dssds);
        h2_z42_vs_e_dssd.resize(num_dssds);
        h2_z42_vs_e_vertical_strip.resize(num_dssds);
        h2_z42_vs_e_horizontal_strip.resize(num_dssds);
        
        for (int i = 0; i < num_dssds; i++)
        {
            h2_s2s4_tof_vs_e_dssd[i] = MakeTH2(dir_frs_tof_stefan_dssds[i], "F", Form("h2_s2s4_tof_vs_e_dssd_%i", i), Form("S2S4 TOF vs DSSD %i E", i), 750, 0, 5000000, 500, 150, 250);
            h2_z41_vs_e_dssd[i] = MakeTH2(dir_frs_z_stefan_dssds[i], "F", Form("h2_z41_vs_e_dssd_%i", i), Form("Z41 vs DSSD %i E", i), 750, 0, 5000000, 200, 0, 40);
            h2_z42_vs_e_dssd[i] = MakeTH2(dir_frs_z_stefan_dssds[i], "F", Form("h2_z42_vs_e_dssd_%i", i), Form("Z42 vs DSSD %i E", i), 750, 0, 5000000, 200, 0, 40); // max_energy
 
            h2_s2s4_tof_vs_e_vertical_strip[i].resize(16);
            h2_s2s4_tof_vs_e_horizontal_strip[i].resize(16);
            h2_z41_vs_e_vertical_strip[i].resize(16);
            h2_z41_vs_e_horizontal_strip[i].resize(16);
            h2_z42_vs_e_vertical_strip[i].resize(16);
            h2_z42_vs_e_horizontal_strip[i].resize(16);

            for (int j = 0; j < 16; j++)
            {
                h2_s2s4_tof_vs_e_vertical_strip[i][j] = MakeTH2(dir_frs_tof_stefan_dssds_strips[i], "D", Form("h2_s2s4_tof_vs_e_dssd_%i_vertical_strip_%i", i, j), Form("S2S4 TOF vs DSSD %i Vertical Strip %i E", i, j), 750, 0, 5000000, 500, 150, 250);
                h2_s2s4_tof_vs_e_horizontal_strip[i][j] = MakeTH2(dir_frs_tof_stefan_dssds_strips[i], "D", Form("h2_s2s4_tof_vs_e_dssd_%i_horizontal_strip_%i", i, j), Form("S2S4 TOF vs DSSD %i Horizontal Strip %i E", i, j), 750, 0, 5000000, 500, 150, 250);
                h2_z41_vs_e_vertical_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z41_vs_e_dssd_%i_vertical_strip_%i", i, j), Form("Z41 vs DSSD %i Vertical Strip %i E", i, j), 750, 0, 5000000, 200, 0, 40);
                h2_z41_vs_e_horizontal_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z41_vs_e_dssd_%i_horizontal_strip_%i", i, j),  Form("Z41 vs DSSD %i Horizontal Strip %i E", i, j), 750, 0, 5000000, 200, 0, 40);
                h2_z42_vs_e_vertical_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z42_vs_e_dssd_%i_vertical_strip_%i", i, j),  Form("Z42 vs DSSD %i Vertical Strip %i E", i, j), 750, 0, 5000000, 200, 0, 40);
                h2_z42_vs_e_horizontal_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z42_vs_e_dssd_%i_horizontal_strip_%i", i, j),  Form("Z42 vs DSSD %i Horizontal Strip %i E", i, j), 750, 0, 5000000, 200, 0, 40);
            }
        }

   

        if (fHitsMCP)
        {
            dir_frs_mcp = dir_corr->mkdir("FRS_vs_MCP");

            h2_s2s4_tof_vs_mcp_tof = MakeTH2(dir_frs_mcp, "D", "h2_s2s4_tof_vs_mcp_tof", "S2S4 TOF vs MCP TOF", 1000, -100, 100, 500, 150, 250);
            h2_z41_vs_mcp_tof = MakeTH2(dir_frs_mcp, "D", "h2_z41_vs_mcp_tof", "Z41 vs MCP TOF", 1000, -100, 100, 200, 0, 40);
            h2_z42_vs_mcp_tof = MakeTH2(dir_frs_mcp, "D", "h2_z42_vs_mcp_tof", "Z42 vs MCP TOF", 1000, -100, 100, 200, 0, 40);

        }
        

    }

   

    return kSUCCESS;

}

void StefanNearlineSpectra::Reset_Histo() 
{
    c4LOG(info, "Resetting Stefan histograms.");

    // Assuming dir is a TDirectory pointer containing histograms
    if (dir_stefan) 
    {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_stefan);
        c4LOG(info, "Stefan histograms reset.");
    } 
    else 
    {
        c4LOG(error, "Failed to get list of histograms from directory.");
    }
}

void StefanNearlineSpectra::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    if (StefanHit->size() == 0) return; // for now

    for (auto const & hit : *StefanHit)
    {
        // lets do some analysis.....
        // std::cout << "StripX: " << hit.StripX << " - StripY: " << hit.StripY << std::endl;
        // if (hit.ClusterSizeX > 1) std::cout << "ClusterSizeX > 1! :: Size =  " << hit.ClusterSizeX << std::endl;
        // if (hit.ClusterSizeY > 1) std::cout << "ClusterSizeY > 1! :: Size =  " << hit.ClusterSizeY << std::endl;

        h2_hit_strip_xy[hit.DSSD]->Fill(hit.StripX, hit.StripY);
        h1_raw_energy[hit.DSSD][0][hit.StripY]->Fill(hit.Energy);
        h1_raw_energy[hit.DSSD][1][hit.StripX]->Fill(hit.Energy);
        h1_pixel_energy[hit.DSSD][hit.StripX+ 16*hit.StripY]->Fill(hit.Energy);

        // Stefan vs FRS
        if (multihitArray)
        {
            if (multihitArray->size() > 0)
            {
                auto const & multiHitItem = multihitArray->at(0);
                std::vector<Float_t> tof_s2s4_mhtdc = multiHitItem.Get_ID_tof_s2s4_mhtdc();
                std::vector<Float_t> z41_mhtdc = multiHitItem.Get_ID_z41_mhtdc();
                std::vector<Float_t> z42_mhtdc = multiHitItem.Get_ID_z42_mhtdc();

                for (int i = 0; i < z41_mhtdc.size(); i++)
                {
                    h2_s2s4_tof_vs_e_dssd[hit.DSSD]->Fill(hit.Energy, tof_s2s4_mhtdc.at(i));
                    h2_z41_vs_e_dssd[hit.DSSD]->Fill(hit.Energy, z41_mhtdc.at(i));
                    h2_z42_vs_e_dssd[hit.DSSD]->Fill(hit.Energy, z42_mhtdc.at(i));

                    h2_s2s4_tof_vs_e_vertical_strip[hit.DSSD][hit.StripY]->Fill(hit.Energy, tof_s2s4_mhtdc.at(i));
                    h2_s2s4_tof_vs_e_horizontal_strip[hit.DSSD][hit.StripX]->Fill(hit.Energy, tof_s2s4_mhtdc.at(i));
                   
                    h2_z41_vs_e_vertical_strip[hit.DSSD][hit.StripY]->Fill(hit.Energy, z41_mhtdc.at(i));
                    h2_z41_vs_e_horizontal_strip[hit.DSSD][hit.StripX]->Fill(hit.Energy, z41_mhtdc.at(i));

                    h2_z42_vs_e_vertical_strip[hit.DSSD][hit.StripY]->Fill(hit.Energy, z42_mhtdc.at(i));
                    h2_z42_vs_e_horizontal_strip[hit.DSSD][hit.StripX]->Fill(hit.Energy, z42_mhtdc.at(i));
                }

            }
        }

        // Stefan vs MCP
        for (int ihit = 0; ihit < fHitsMCP->GetEntriesFast(); ihit++) 
        {
            H10MCPTwinpeaksAnaData* mcphit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(ihit);
            if (!mcphit) return;
            
            h2_mcp_tof_vs_e_dssd[hit.DSSD]->Fill(mcphit->T2-mcphit->T1, hit.Energy);
            h2_mcp_tof_vs_e_vertical_strip[hit.DSSD][hit.StripY]->Fill(mcphit->T2-mcphit->T1, hit.Energy);
            h2_mcp_tof_vs_e_horizontal_strip[hit.DSSD][hit.StripX]->Fill(mcphit->T2-mcphit->T1, hit.Energy);

        }
    }



    // MCP vs FRS
    if (multihitArray && fHitsMCP)
    {
        if (multihitArray->size() > 0 && fHitsMCP->GetEntriesFast() > 0)
        {
            auto const & multiHitItem = multihitArray->at(0);
            std::vector<Float_t> tof_s2s4_mhtdc = multiHitItem.Get_ID_tof_s2s4_mhtdc();
            std::vector<Float_t> z41_mhtdc = multiHitItem.Get_ID_z41_mhtdc();
            std::vector<Float_t> z42_mhtdc = multiHitItem.Get_ID_z42_mhtdc();

            for (int i = 0; i < z41_mhtdc.size(); i++)
            {
                for (int ihit = 0; ihit < fHitsMCP->GetEntriesFast(); ihit++) 
                {
                    H10MCPTwinpeaksAnaData* hit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(ihit);
                    if (!hit) return;
                    
                    h2_s2s4_tof_vs_mcp_tof->Fill(hit->T2-hit->T1, tof_s2s4_mhtdc.at(i));
                    h2_z41_vs_mcp_tof->Fill(hit->T2-hit->T1, z41_mhtdc.at(i));
                    h2_z42_vs_mcp_tof->Fill(hit->T2-hit->T1, z42_mhtdc.at(i));

                }
            }
        }
    }


    fNEvents++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void StefanNearlineSpectra::FinishEvent()
{
    // resets and whateves  
}

void StefanNearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_stefan->Write();
    gDirectory = tmp;
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
}

ClassImp(StefanNearlineSpectra)
