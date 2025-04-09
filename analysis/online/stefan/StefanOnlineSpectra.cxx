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

    // load stefan stuff

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);
    dir_stefan = new TDirectory("Stefan", "Stefan", "", 0);
    histograms->Add(dir_stefan);

    // copy over stuf 
   

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
/*
    Int_t nHits = fHitsStefany->GetEntriesFast();
    for (Int_t ihit = 0; ihit < nHits; ihit++)
        { 
*/
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
