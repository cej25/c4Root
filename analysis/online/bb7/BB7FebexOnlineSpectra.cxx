// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AnalysisTools.h"
#include "BB7FebexOnlineSpectra.h"
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

BB7FebexOnlineSpectra::BB7FebexOnlineSpectra() : BB7FebexOnlineSpectra("BB7FebexOnlineSpectra")
{

}


BB7FebexOnlineSpectra::BB7FebexOnlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   bb7calImplants(nullptr)
    ,   bb7calDecays(nullptr)
    ,   implantHitArray(nullptr)
    ,   decayHitArray(nullptr)
    ,   header(nullptr)
    ,   fNEvents(0)
{

}

BB7FebexOnlineSpectra::~BB7FebexOnlineSpectra()
{
    c4LOG(info, "Destroyed BB7FebexOnlineSpectra properly.");
}

InitStatus BB7FebexOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found!");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    run->GetHttpServer()->RegisterCommand("Reset_BB7Febex_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found!");

    bb7calImplants = mgr->InitObjectAs<decltype(bb7calImplants)>("BB7FebexCalImplants");
    c4LOG_IF(fatal, !bb7calImplants, "Branch BB7FebexCalImplants not found!");
    bb7calDecays = mgr->InitObjectAs<decltype(bb7calDecays)>("BB7FebexCalDecays");
    c4LOG_IF(fatal, !bb7calDecays, "Branch BB7FebexCalDecays not found!");

    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("BB7FebexImplants");
    c4LOG_IF(fatal, !implantHitArray, "Branch BB7FebexImplants not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("BB7FebexDecays");
    c4LOG_IF(fatal, !decayHitArray, "Branch BB7FebexDecays not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);
    dir_bb7 = new TDirectory("BB7", "BB7", "", 0);
    histograms->Add(dir_bb7);

    dir_cal = dir_bb7->mkdir("CalData");
    dir_hit = dir_bb7->mkdir("HitData");

    dir_hit_implant = dir_hit->mkdir("Implants");
    dir_hit_decay = dir_hit->mkdir("Decays");

    // Concept of "Stopped" is irrelevant right now
    h2_implant_strip_xy = MakeTH2(dir_hit_implant, "I", "h2_implant_strip_xy", "Implant Pattern (Strips)", 32, 0, 32, 32, 0, 32);
    h1_implant_e = MakeTH1(dir_hit_implant, "F", "h1_implant_e", "Implant Energy", 1000, 0, 200000);
    h2_implant_e_xy = MakeTH2(dir_hit_implant, "F", "h2_implant_e_xy", "Implant Energy (X vs Y)", 1000, 0, 200000, 1000, 0, 200000);
    h2_implant_strip_1d_e = MakeTH2(dir_hit_implant, "F", "h2_implant_strip_1d_e", "Implant Energy (X then Y strips)", 64, 0, 64, 1000, 0, 200000);

    h2_decay_strip_xy = MakeTH2(dir_hit_decay, "I", "h2_decay_strip_xy", "Decay Hit Pattern", 32, 0, 32, 32, 0, 32);
    h1_decay_e = MakeTH1(dir_hit_decay, "F", "h1_decay_e", "Decay Energy", 1000, 0, 200000);
    h2_decay_e_xy = MakeTH2(dir_hit_decay, "F", "h2_decay_e_xy", "Decay Energy (X vs Y)", 1000, 0, 200000, 1000, 0, 200000);
    h2_decay_strip_1d_e = MakeTH2(dir_hit_decay, "F", "h2_decay_strip_1d_e", "Decay Energy (X then Y strips)", 64, 0, 64, 1000, 0, 200000);

    return kSUCCESS;

}

void BB7FebexOnlineSpectra::Reset_Histo() 
{
    c4LOG(info, "Resetting BB7Febex histograms.");

    // Assuming dir is a TDirectory pointer containing histograms
    if (dir_bb7) 
    {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_bb7);
        c4LOG(info, "BB7Febex histograms reset.");
    } 
    else 
    {
        c4LOG(error, "Failed to get list of histograms from directory.");
    }
}

void BB7FebexOnlineSpectra::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (auto const & i : *implantHitArray)
    {
        h2_implant_strip_xy->Fill(i.StripX, i.StripY);
    }

    for (auto const & d : *decayHitArray)
    {
        h2_decay_strip_xy->Fill(d.StripX, d.StripY);
    }

    fNEvents++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void BB7FebexOnlineSpectra::FinishEvent()
{

}

void BB7FebexOnlineSpectra::FinishTask()
{
    if (fNEvents > 0)
    {
        c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    }
}

ClassImp(BB7FebexOnlineSpectra)