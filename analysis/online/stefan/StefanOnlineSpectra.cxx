// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AnalysisTools.h"
#include "StefanOnlineSpectra.h"
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

StefanOnlineSpectra::StefanOnlineSpectra() : StefanOnlineSpectra("StefanOnlineSpectra")
{
    stefan_config = TStefanConfiguration::GetInstance();
}

StefanOnlineSpectra::StefanOnlineSpectra(std::vector<FrsGate*> fg) : StefanOnlineSpectra("StefanOnlineSpectra")
{
    stefan_config = TStefanConfiguration::GetInstance();
    FrsGates = fg;
}

StefanOnlineSpectra::StefanOnlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    // stuff
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   StefanHit(nullptr)
    ,   calArray(nullptr)
{
    stefan_config = TStefanConfiguration::GetInstance();

}

StefanOnlineSpectra::~StefanOnlineSpectra()
{
    c4LOG(info, "Destroyed StefanOnlineSpectra properly.");
}

InitStatus StefanOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found!");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    run->GetHttpServer()->RegisterCommand("Reset_Stefan_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found!");

    // stefan failure is fatal foe now, altough we could turn this into a complete "HISPEC10" task, and just make it a warning
    StefanHit = mgr->InitObjectAs<decltype(StefanHit)>("StefanHitData");
    c4LOG_IF(fatal, !StefanHit, "Branch StefanHitData not found - no correlations with Stefan possible!");
	
    calArray = mgr->InitObjectAs<decltype(calArray)>("StefanCalData");
    c4LOG_IF(warn, !calArray, "Branch StefanCalData not found!");
    
    // correlations
    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksAnaData");
    c4LOG_IF(warn, !fHitsMCP, "Branch H10MCPTwinpeaksAnaData not found - no correlations with MCPs possible!");
    hitArray = mgr->InitObjectAs<decltype(hitArray)>("FrsHitData");
    c4LOG_IF(warn, !hitArray, "Branch FrsHitData not found - no correlations with FRS (TAC) possible!");
    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(warn, !multihitArray, "Branch FrsMultiHitData not found - no correlations with FRS (MHTDC) possible!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);
    dir_stefan = new TDirectory("Stefan", "Stefan", "", 0);
    histograms->Add(dir_stefan);

    num_frs_gates = FrsGates.size();

    int num_dssds = stefan_config->DSSDs();
    int n_sides = 2;

    dir_dssd = new TDirectory*[num_dssds];
    dir_stats = new TDirectory*[num_dssds];
    dir_hits = new TDirectory*[num_dssds];
    
    dir_raw.resize(num_dssds);
    dir_pixel.resize(num_dssds);
    
    
    max_energy.resize(num_dssds);
    max_energy[0] = 5*pow(10,6);
    max_energy[1] = 5*pow(10,5);
    
    double maxTOF=50;
    double minTOF=0;
    
    h2_hit_strip_xy.resize(num_dssds);
    h1_raw_energy.resize(num_dssds); // h1_raw_energy[dssd#][side#][ch#]
    h1_energy_clusters.resize(num_dssds); //[dssd#][side#][ch#]
    h1_pixel_energy.resize(num_dssds); // h1_pixel_energy[dssd#][pixel#]
    
   // h1_test = MakeTH1(dir_stefan, "I", "h1_test", "h1_test", 10000, 0, max_energy, "E []", kSpring, kBlack);
   
        h2_dE_E = MakeTH2(dir_stefan, "I", "h2_dE_E" , "dE-E", 200, 0, max_energy[0], 200, 0,  max_energy[1]);
        h2_Z_M = MakeTH2(dir_stefan, "I", "h2_Z_M" , "Z-M", 200, 0, pow(10,7), 200, 0,  pow(10,5));
        
    for (int i = 0; i < num_dssds; i++)
    {	
    	dir_raw[i].resize(n_sides*2);
    	dir_raw[i][0] = new TDirectory;
    	dir_raw[i][1] = new TDirectory;
    	dir_raw[i][2] = new TDirectory;
    	dir_raw[i][3] = new TDirectory;
    	
    	dir_pixel[i] = new TDirectory;
    	
    	h1_raw_energy[i].resize(2); //two sides
    	h1_raw_energy[i][0].resize(16);
    	h1_raw_energy[i][1].resize(16);
    	
    	h1_energy_clusters[i].resize(2); //two sides
    	h1_energy_clusters[i][0].resize(16);
    	h1_energy_clusters[i][1].resize(16);
    	
        dir_dssd[i] = dir_stefan->mkdir(Form("DSSD%i",i));
        dir_hits[i] = dir_dssd[i]->mkdir("Hits");
        h2_hit_strip_xy[i] = MakeTH2(dir_hits[i], "I", Form("h2_hit_strip_xy_dssd%d", i) , Form("XY Hit Pattern DSSD %d", i), 16, 0, 16, 16, 0, 16);
        
        dir_raw[i][0] = dir_dssd[i]->mkdir("Raw_energy_vertical");
	
        for(int j=0; j<16; ++j) { //vertical strips or stripY
        	h1_raw_energy[i][0][j] = MakeTH1(dir_raw[i][0], "I", Form("h1_raw_energy_det%i_vertical_strip%i", i, j), Form("Raw Energy - Det %i Vertical side - Strip %i", i, j), 10000, 0, max_energy[i], "E []", kCyan, kBlack);
        	}
        	
	dir_raw[i][1] = dir_dssd[i]->mkdir("Cluster_energy_vertical");
	
        for(int j=0; j<16; ++j) { //vertical strips or stripY
        	h1_energy_clusters[i][0][j] = MakeTH1(dir_raw[i][1], "I", Form("h1_energy_clusters_det%i_vertical_strip%i", i, j), Form("Cluster Energy - Det %i Vertical side - Strip %i", i, j), 10000, 0, max_energy[i], "E []", kCyan, kBlack);
        	}
        	
        dir_raw[i][2] = dir_dssd[i]->mkdir("Raw_energy_horizontal");
        for(int j=0; j<16; ++j) {//horizontal strips or stripX
        	h1_raw_energy[i][1][j] = MakeTH1(dir_raw[i][2], "I", Form("h1_raw_energy_det%i_horizontal_strip%i", i, j), Form("Raw Energy - Det %i Horizontal side - Strip %i", i, j), 10000, 0, max_energy[i], "E []", kSpring, kBlack);
        	}
        	
	dir_raw[i][3] = dir_dssd[i]->mkdir("Cluster_energy_horizontal");
        for(int j=0; j<16; ++j) {//horizontal strips or stripX
        	h1_energy_clusters[i][1][j] = MakeTH1(dir_raw[i][3], "I", Form("h1_energy_clusters_det%i_horizontal_strip%i", i, j), Form("Cluster Energy - Det %i Horizontal side - Strip %i", i, j), 10000, 0, max_energy[i], "E []", kSpring, kBlack);
        	}
        
        dir_pixel[i] = dir_dssd[i]->mkdir("Pixels_energy");
        h1_pixel_energy[i].resize(256);
        
       for(int j=0; j<256; ++j) { // pixel = stripX+16*stripY
        	h1_pixel_energy[i][j] = MakeTH1(dir_pixel[i], "I", Form("h1_energy_pixel%i", j), Form("Energy - Det %i Pixel %i", i, j), 10000, 0, max_energy[i], "E []", kOrange, kBlack);
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
        	strips4_stefan->SetLogy();
        	
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
            h2_mcp_tof_vs_e_dssd[i] = MakeTH2(dir_mcp_stefan_dssds[i], "D", Form("h2_mcp_tof_vs_e_dssd_%i", i), Form("MCP TOF vs DSSD %i E", i), 600, minTOF, maxTOF, 1000, 0, max_energy[i]);

            h2_mcp_tof_vs_e_vertical_strip[i].resize(16);
            h2_mcp_tof_vs_e_horizontal_strip[i].resize(16);
            for (int j = 0; j < 16; j++)
            {
                h2_mcp_tof_vs_e_vertical_strip[i][j] = MakeTH2(dir_mcp_stefan_dssds_strips[i], "D", Form("h2_mcp_tof_vs_e_dssd_%i_vertical_strip_%i", i, j), Form("MCP TOF vs DSSD %i Veritcal Strip %i E", i, j), 1000, minTOF, maxTOF, 750, 0, max_energy[i]);
                h2_mcp_tof_vs_e_horizontal_strip[i][j] = MakeTH2(dir_mcp_stefan_dssds_strips[i], "D", Form("h2_mcp_tof_vs_e_dssd_%i_horizontal_strip_%i", i, j), Form("MCP TOF vs DSSD %i Horizontal Strip %i E", i, j), 1000, minTOF, maxTOF, 750, 0, max_energy[i]);
            }
        }

        // Same as above gated on FRS
        // if (num_frs_gates > 0)
        // {
        //     dir_frs_gated = dir_mcp_stefan->mkdir("FRS_Gated");
        //     dir_frs_gates = new TDirectory*[num_frs_gates];
        //     dir_frs_gated_dssds = new TDirectory**[num_frs_gates];
        //     dir_frs_gated_dssds_strips = new TDirectory**[num_frs_gates];

        //     h2_mcp_tof_vs_e_dssd_gated.resize(num_frs_gates);
        //     h2_mcp_tof_vs_e_vertical_strip_gated.resize(num_frs_gates);
        //     h2_mcp_tof_vs_e_horizontal_strip_gated.resize(num_frs_gates);


        //     for (int gate = 0; gate < num_frs_gates; gate++)
        //     {
        //         std::string gname = "" + FrsGates.at(gate)->GetName();
        //         dir_frs_gates[gate] = dir_frs_gated->mkdir(gname.c_str());
        //         dir_frs_gated_dssds[gate] = new TDirectory*[num_dssds];
        //         dir_frs_gated_dssds_strips[gate] = new TDirectory*[num_dssds];

        //         h2_mcp_tof_vs_e_dssd_gated[gate].resize(num_dssds);
        //         h2_mcp_tof_vs_e_vertical_strip_gated[gate].resize(num_dssds);
        //         h2_mcp_tof_vs_e_horizontal_strip_gated[gate].resize(num_dssds);

        //         for (int d = 0; d < num_dssds; d++)
        //         {
        //             dir_frs_gated_dssds[gate][d] = dir_frs_gated_dssds[gate]->mkdir(Form("DSSD%i", d));
        //             dir_frs_gated_dssds_strips[gate][d] = dir_frs_gated_dssds_strips[gate]->mkdir("Strips");

        //             h2_mcp_tof_vs_e_dssd_gated[gate][d] = MakeTH2(dir_frs_gated_dssds[gate][d], "F", Form("h2_mcp_tof_vs_e_dssd_%i_gated_%s", d, gname.c_str()), Form("MCP TOF vs DSSD %i E - S2S4 Gate: %s", d, gname.c_str()), );

        //             h2_mcp_tof_vs_e_vertical_strip_gated[gate][d].resize(16);
        //             h2_mcp_tof_vs_e_horizontal_strip_gated[gate][d].resize(16);
        //             for (int s = 0; s < 16; s++)
        //             {
        //                 h2_mcp_tof_vs_e_vertical_strip_gated[gate][d][s] = MakeTH2(dir_frs_gated_dssds_strips[gate][d], "F", Form(), Form(), );
        //                 h2_mcp_tof_vs_e_horizontal_strip_gated[gate][d][s] = MakeTH2(dir_frs_gated_dssds_strips[gate][d], "F", Form(), Form(), );
        //             }
                  
        //         }

                
        //     }

        // }

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
            h2_s2s4_tof_vs_e_dssd[i] = MakeTH2(dir_frs_tof_stefan_dssds[i], "F", Form("h2_s2s4_tof_vs_e_dssd_%i", i), Form("S2S4 TOF vs DSSD %i E", i), 750, 0, max_energy[i], 500, 150, 250);
            h2_z41_vs_e_dssd[i] = MakeTH2(dir_frs_z_stefan_dssds[i], "F", Form("h2_z41_vs_e_dssd_%i", i), Form("Z41 vs DSSD %i E", i), 750, 0, max_energy[i], 200, 0, 40);
            h2_z42_vs_e_dssd[i] = MakeTH2(dir_frs_z_stefan_dssds[i], "F", Form("h2_z42_vs_e_dssd_%i", i), Form("Z42 vs DSSD %i E", i), 750, 0, max_energy[i], 200, 0, 40); // max_energy
 
            h2_s2s4_tof_vs_e_vertical_strip[i].resize(16);
            h2_s2s4_tof_vs_e_horizontal_strip[i].resize(16);
            h2_z41_vs_e_vertical_strip[i].resize(16);
            h2_z41_vs_e_horizontal_strip[i].resize(16);
            h2_z42_vs_e_vertical_strip[i].resize(16);
            h2_z42_vs_e_horizontal_strip[i].resize(16);

            for (int j = 0; j < 16; j++)
            {
                h2_s2s4_tof_vs_e_vertical_strip[i][j] = MakeTH2(dir_frs_tof_stefan_dssds_strips[i], "D", Form("h2_s2s4_tof_vs_e_dssd_%i_vertical_strip_%i", i, j), Form("S2S4 TOF vs DSSD %i Vertical Strip %i E", i, j), 750, 0, max_energy[i], 500, 150, 250);
                h2_s2s4_tof_vs_e_horizontal_strip[i][j] = MakeTH2(dir_frs_tof_stefan_dssds_strips[i], "D", Form("h2_s2s4_tof_vs_e_dssd_%i_horizontal_strip_%i", i, j), Form("S2S4 TOF vs DSSD %i Horizontal Strip %i E", i, j), 750, 0, max_energy[i], 500, 150, 250);
                h2_z41_vs_e_vertical_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z41_vs_e_dssd_%i_vertical_strip_%i", i, j), Form("Z41 vs DSSD %i Vertical Strip %i E", i, j), 750, 0, max_energy[i], 200, 0, 40);
                h2_z41_vs_e_horizontal_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z41_vs_e_dssd_%i_horizontal_strip_%i", i, j),  Form("Z41 vs DSSD %i Horizontal Strip %i E", i, j), 750, 0, max_energy[i], 200, 0, 40);
                h2_z42_vs_e_vertical_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z42_vs_e_dssd_%i_vertical_strip_%i", i, j),  Form("Z42 vs DSSD %i Vertical Strip %i E", i, j), 750, 0, max_energy[i], 200, 0, 40);
                h2_z42_vs_e_horizontal_strip[i][j] = MakeTH2(dir_frs_z_stefan_dssds_strips[i], "F", Form("h2_z42_vs_e_dssd_%i_horizontal_strip_%i", i, j),  Form("Z42 vs DSSD %i Horizontal Strip %i E", i, j), 750, 0, max_energy[i], 200, 0, 40);
            }
        }

   

        if (fHitsMCP)
        {
            dir_frs_mcp = dir_corr->mkdir("FRS_vs_MCP");

            h2_s2s4_tof_vs_mcp_tof = MakeTH2(dir_frs_mcp, "D", "h2_s2s4_tof_vs_mcp_tof", "S2S4 TOF vs MCP TOF", 1000, minTOF, maxTOF, 500, 150, 250);
            h2_z41_vs_mcp_tof = MakeTH2(dir_frs_mcp, "D", "h2_z41_vs_mcp_tof", "Z41 vs MCP TOF", 1000, minTOF, maxTOF, 200, 0, 40);
            h2_z42_vs_mcp_tof = MakeTH2(dir_frs_mcp, "D", "h2_z42_vs_mcp_tof", "Z42 vs MCP TOF", 1000, minTOF, maxTOF, 200, 0, 40);

        }
        

    }

    return kSUCCESS;

}

void StefanOnlineSpectra::Reset_Histo() 
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

void StefanOnlineSpectra::Exec(Option_t* option)
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
        h1_energy_clusters[hit.DSSD][0][hit.StripY]->Fill(hit.Energy);
        h1_energy_clusters[hit.DSSD][1][hit.StripX]->Fill(hit.Energy);
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
   /*     for (int ihit = 0; ihit < fHitsMCP->GetEntriesFast(); ihit++) 
        {
            H10MCPTwinpeaksAnaData* mcphit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(ihit);
            if (!mcphit) break;
            
            h2_mcp_tof_vs_e_dssd[hit.DSSD]->Fill(mcphit->T2-mcphit->T1, hit.Energy);
            h2_mcp_tof_vs_e_vertical_strip[hit.DSSD][hit.StripY]->Fill(mcphit->T2-mcphit->T1, hit.Energy);
            h2_mcp_tof_vs_e_horizontal_strip[hit.DSSD][hit.StripX]->Fill(mcphit->T2-mcphit->T1, hit.Energy);

        }*/
    }

	// STEFAN data before clustering
   if (calArray->size() > 0) { 
   
   	int current_dssd =-1;
	int current_side =-1;
	int current_strip =-1;
	double current_energy =-1;
	double mcpTOF=-1;
	int previous_dssd =-1;
	int previous_side =-1;
	int previous_strip =-1;
	double previous_energy =-1;
    
    	for (auto const & cHit : *calArray) {
 	   	if (cHit.DSSD == -1 || cHit.Side==-1 || cHit.Strip==-1) continue;
 	   	
 	   	//h1_test->Fill(cHit.Energy);
 	   	//std::cout << cHit.DSSD << "\t" << cHit.Side << "\t" << cHit.Strip << "\t" << cHit.Energy << std::endl;
 	   	h1_raw_energy[cHit.DSSD][cHit.Side][cHit.Strip]->Fill(cHit.Energy);
 		
    		
	    	
		// Stefan vs Stefan
		current_dssd =  cHit.DSSD;
		current_side =  cHit.Side;
		current_strip =  cHit.Strip;
		current_energy = cHit.Energy;
		if(previous_dssd!=-1 && previous_strip!=-1 && previous_energy > 0) {
			if(current_dssd!=previous_dssd && current_energy>0) {
				if(current_dssd==1) h2_dE_E->Fill(previous_energy, current_energy);
				if(current_dssd==0) h2_dE_E->Fill(current_energy, previous_energy);
				}
			}
			
			// Stefan vs MCP
		for (int ihit = 0; ihit < fHitsMCP->GetEntriesFast(); ihit++) 
			{
			    H10MCPTwinpeaksAnaData* mcphit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(ihit);
			    if (!mcphit) break;
			    
			    if(cHit.Side==0) h2_mcp_tof_vs_e_vertical_strip[cHit.DSSD][cHit.Strip]->Fill(mcphit->T2-mcphit->T1, cHit.Energy);
			    if(cHit.Side==1) h2_mcp_tof_vs_e_horizontal_strip[cHit.DSSD][cHit.Strip]->Fill(mcphit->T2-mcphit->T1, cHit.Energy);
			    
			    mcpTOF=mcphit->T2-mcphit->T1;
			    
			    if(previous_dssd!=-1 && previous_strip!=-1 && previous_energy > 0) {
				if(current_dssd!=previous_dssd && current_energy>0) {
					if(current_dssd==1) h2_Z_M->Fill(current_energy*mcpTOF*mcpTOF/100., sqrt(previous_energy));
					if(current_dssd==0) h2_Z_M->Fill(previous_energy*mcpTOF*mcpTOF/100., sqrt(current_energy));
					}
				}
			    if(current_side==0 && current_strip==1) continue; //this channel has some issues, leaving it out of the TOF vs E hist for now
			    h2_mcp_tof_vs_e_dssd[cHit.DSSD]->Fill(mcphit->T2-mcphit->T1, cHit.Energy);
			    
			}
			
		previous_dssd = current_dssd;
		previous_side = current_side;
		previous_strip = current_strip;
		previous_energy = current_energy;
		
		
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

void StefanOnlineSpectra::FinishEvent()
{
    // resets and whateves  
}

void StefanOnlineSpectra::FinishTask()
{
    if (fNEvents > 0)
    {
        c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    }
}

ClassImp(StefanOnlineSpectra)
