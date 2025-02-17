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

    dir_stats = dir_bb7->mkdir("Stats"); // not sure where to put this frankly
    dir_implants = dir_bb7->mkdir("Implants");
    dir_decays = dir_bb7->mkdir("Decays");

    // CEJ: All of these should be by detector (eventually?)
    // just decays , testing
    h1_side_x_mult = MakeTH1(dir_stats, "I", "h1_side_x_mult", "Side X Multiplicity", 33, 0, 33, "X Strips Fired", kRed-3, kBlack); // number of x strips fired
    h1_side_y_mult = MakeTH1(dir_stats, "I", "h1_side_y_mult", "Side Y Multiplicity", 33, 0, 33, "Y Strips Fired", kRed-3, kBlack); // number of y strips fired
    // maybe this one is meaningless with FEBEX? can you have multiple hits per event in same channel?
    h2_strip_mult = MakeTH2(dir_stats, "I", "h2_strip_mult", "Strip vs Strip Multiplicity", 65, 0, 65, 10, 0, 10, "Strip (X then Y)", "Strip Multiplicity"); // strip (x then y) vs # of times fired
    h1_side_x_hitpattern = MakeTH1(dir_stats, "I", "h1_side_x_hitpattern", "Side X Hit Pattern", 32, 0, 32, "X Strip", kRed-3, kBlack);
    h1_side_y_hitpattern = MakeTH1(dir_stats, "I", "h1_side_y_hitpattern", "Side Y Hit Pattern", 32, 0, 32, "Y Strip", kRed-3, kBlack);

    // Concept of "Stopped" is irrelevant right now
    h2_implant_strip_xy = MakeTH2(dir_implants, "I", "h2_implant_strip_xy", "Implant Pattern (Strips)", 32, 0, 32, 32, 0, 32);
    h1_implant_e = MakeTH1(dir_implants, "F", "h1_implant_e", "Implant Energy", 1000, 0, 200000);
    h2_implant_e_xy = MakeTH2(dir_implants, "F", "h2_implant_e_xy", "Implant Energy (X vs Y)", 1000, 0, 200000, 1000, 0, 200000);
    h2_implant_strip_1d_e = MakeTH2(dir_implants, "F", "h2_implant_strip_1d_e", "Implant Energy (X then Y strips)", 64, 0, 64, 1000, 0, 200000);

    h2_decay_strip_xy = MakeTH2(dir_decays, "I", "h2_decay_strip_xy", "Decay Hit Pattern", 32, 0, 32, 32, 0, 32);
    h1_decay_e = MakeTH1(dir_decays, "F", "h1_decay_e", "Decay Energy", 1000, 0, 200000);
    h2_decay_e_xy = MakeTH2(dir_decays, "F", "h2_decay_e_xy", "Decay Energy (X vs Y)", 1000, 0, 200000, 1000, 0, 200000);
    h2_decay_strip_1d_e = MakeTH2(dir_decays, "F", "h2_decay_strip_1d_e", "Decay Energy (X then Y strips)", 64, 0, 64, 1000, 0, 200000);

    for (int i = 0; i < 32; i++)
    {
        side_x_mult[i] = 0;
        side_y_mult[i] = 0;
    }
    strips_fired[0].clear(); strips_fired[1].clear();

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
        strips_fired[0].insert(d.StripX);
        strips_fired[1].insert(d.StripY);
        side_x_mult[int(d.StripX)]++;
        side_y_mult[int(d.StripY)]++;

        h2_decay_strip_xy->Fill(d.StripX, d.StripY);
        h1_side_x_hitpattern->Fill(d.StripX);
        h1_side_y_hitpattern->Fill(d.StripY);
    }

    h1_side_x_mult->Fill(strips_fired[0].size());
    h1_side_y_mult->Fill(strips_fired[1].size());
    for (int i = 0; i < 32; i++)
    {
        h2_strip_mult->Fill(i, side_x_mult[i]);
        h2_strip_mult->Fill(i+32, side_y_mult[i]);
    }
    // reset

    fNEvents++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void BB7FebexOnlineSpectra::FinishEvent()
{
    for (int i = 0; i < 32; i++)
    {
        side_x_mult[i] = 0;
        side_y_mult[i] = 0;
    }
    strips_fired[0].clear(); strips_fired[1].clear();
}

void BB7FebexOnlineSpectra::FinishTask()
{
    if (fNEvents > 0)
    {
        c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    }
}

ClassImp(BB7FebexOnlineSpectra)