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

}


StefanOnlineSpectra::StefanOnlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    // stuff
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   StefanHit(nullptr)
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

    StefanHit = mgr->InitObjectAs<decltype(StefanHit)>("StefanHitData");
    c4LOG_IF(fatal, !StefanHit, "Branch StefanHitData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);
    dir_stefan = new TDirectory("Stefan", "Stefan", "", 0);
    histograms->Add(dir_stefan);

    int num_dssds = stefan_config->DSSDs();
    int n_sides = 2;

    dir_dssd = new TDirectory*[num_dssds];
    dir_stats = new TDirectory*[num_dssds];
    dir_hits = new TDirectory*[num_dssds];
    
    dir_raw.resize(num_dssds);
    dir_pixel.resize(num_dssds);
    
    
    h2_hit_strip_xy.resize(num_dssds);
    h1_raw_energy.resize(num_dssds); // h1_raw_energy[dssd#][side#][ch#]
    h1_pixel_energy.resize(num_dssds); // h1_pixel_energy[dssd#][pixel#]
    
    
    for (int i = 0; i < num_dssds; i++)
    {	
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
        	h1_raw_energy[i][0][j] = MakeTH1(dir_raw[i][0], "I", Form("h1_raw_energy_det%i_vertical_strip%i", i, j), Form("Raw Energy - Det %i Vertical side - Strip %i", i, j), 10000, 0, 1000000, "E []", kCyan, kBlack);
        	}
        
	dir_raw[i][1] = dir_dssd[i]->mkdir("Raw_energy_horizontal");
        for(int j=0; j<16; ++j) {//horizontal strips or stripX
        	h1_raw_energy[i][1][j] = MakeTH1(dir_raw[i][1], "I", Form("h1_raw_energy_det%i_horizontal_strip%i", i, j), Form("Raw Energy - Det %i Horizontal side - Strip %i", i, j), 10000, 0, 1000000, "E []", kSpring, kBlack);
        	}
        
        dir_pixel[i] = dir_dssd[i]->mkdir("Pixels_energy");
        h1_pixel_energy[i].resize(256);
        
 //      for(int j=0; j<256; ++j) { // pixel = stripX+16*stripY
 //       	h1_pixel_energy[i][j] = MakeTH1(dir_raw[i][1], "I", Form("h1_energy_pixel%i", j), Form("Energy - Det %i Pixel %i", i, j), 10000, 0, 1000000, "E []", kOrange, kBlack);
   //     	}
        	
        	
        	
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

    if (StefanHit->size() == 0) return;

    for (auto const & hit : *StefanHit)
    {
        // lets do some analysis.....
        // std::cout << "StripX: " << hit.StripX << " - StripY: " << hit.StripY << std::endl;
        // if (hit.ClusterSizeX > 1) std::cout << "ClusterSizeX > 1! :: Size =  " << hit.ClusterSizeX << std::endl;
        // if (hit.ClusterSizeY > 1) std::cout << "ClusterSizeY > 1! :: Size =  " << hit.ClusterSizeY << std::endl;

        h2_hit_strip_xy[hit.DSSD]->Fill(hit.StripX, hit.StripY);
        h1_raw_energy[hit.DSSD][0][hit.StripY]->Fill(hit.Energy);
        h1_raw_energy[hit.DSSD][1][hit.StripX]->Fill(hit.Energy);
      //  h1_pixel_energy[hit.DSSD][hit.StripX+ 16*hit.StripY]->Fill(hit.Energy);
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
