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
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

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
    bb7_config = TBB7FebexConfiguration::GetInstance();

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

    nDets = bb7_config->DSSDs();
    std::cout << nDets << std::endl;

    dir_dssd.resize(nDets);
    dir_implants.resize(nDets);
    dir_decays.resize(nDets);
    dir_stats.resize(nDets);

    h1_implant_side_x_mult.resize(nDets);
    h1_implant_side_y_mult.resize(nDets);
    h2_implant_strip_mult.resize(nDets);
    h1_implant_side_x_hitpattern.resize(nDets);
    h1_implant_side_y_hitpattern.resize(nDets);
    h2_implant_strip_xy.resize(nDets);
    h1_implant_e.resize(nDets);
    h2_implant_e_xy.resize(nDets);
    h2_implant_strip_1d_e.resize(nDets);

    h1_decay_side_x_mult.resize(nDets);
    h1_decay_side_y_mult.resize(nDets);
    h2_decay_strip_mult.resize(nDets);
    h1_decay_side_x_hitpattern.resize(nDets);
    h1_decay_side_y_hitpattern.resize(nDets);
    h2_decay_strip_xy.resize(nDets);
    h1_decay_e.resize(nDets);
    h2_decay_e_xy.resize(nDets);
    h2_decay_strip_1d_e.resize(nDets);

    // Counters
    implant_strips_fired = new std::set<int>*[nDets];
    implant_side_x_mult = new int*[nDets];
    implant_side_y_mult = new int*[nDets];
    
    decay_strips_fired = new std::set<int>*[nDets];
    decay_side_x_mult = new int*[nDets];
    decay_side_y_mult = new int*[nDets];


    for (int i = 0; i < nDets; i++)
    {
        dir_dssd[i] = dir_bb7->mkdir(Form("DSSD%i",i));
        dir_implants[i] = dir_dssd[i]->mkdir("Implants");
        dir_decays[i] = dir_dssd[i]->mkdir("Decays");
        dir_stats[i] = dir_dssd[i]->mkdir("Stats");

        // CEJ: All of these should be by detector (eventually?)
        // just decays , testing
        h1_decay_side_x_mult[i] = MakeTH1(dir_stats[i], "I", Form("h1_decay_side_x_mult_dssd%i", i), "Side X Multiplicity", 33, 0, 33, "X Strips Fired", kRed-3, kBlack); // number of x strips fired
        h1_decay_side_y_mult[i] = MakeTH1(dir_stats[i], "I", Form("h1_decay_side_y_mult_dssd%i", i), "Side Y Multiplicity", 33, 0, 33, "Y Strips Fired", kRed-3, kBlack); // number of y strips fired
        // maybe this one is meaningless with FEBEX? can you have multiple hits per event in same channel?
        h2_decay_strip_mult[i] = MakeTH2(dir_stats[i], "I", Form("h2_decay_strip_mult_dssd%i", i), "Strip vs Strip Multiplicity", 65, 0, 65, 10, 0, 10, "Strip (X then Y)", "Strip Multiplicity"); // strip (x then y) vs # of times fired
        h1_decay_side_x_hitpattern[i] = MakeTH1(dir_stats[i], "I", Form("h1_decay_side_x_hitpattern_dssd%i", i), "Side X Hit Pattern", 32, 0, 32, "X Strip", kRed-3, kBlack);
        h1_decay_side_y_hitpattern[i] = MakeTH1(dir_stats[i], "I", Form("h1_decay_side_y_hitpattern_dssd%i", i), "Side Y Hit Pattern", 32, 0, 32, "Y Strip", kRed-3, kBlack);

        h1_implant_side_x_mult[i] = MakeTH1(dir_stats[i], "I", Form("h1_implant_side_x_mult_dssd%i", i), "Side X Multiplicity", 33, 0, 33, "X Strips Fired", kRed-3, kBlack); // number of x strips fired
        h1_implant_side_y_mult[i] = MakeTH1(dir_stats[i], "I", Form("h1_implant_side_y_mult_dssd%i", i), "Side Y Multiplicity", 33, 0, 33, "Y Strips Fired", kRed-3, kBlack); // number of y strips fired
        // maybe this one is meaningless with FEBEX? can you have multiple hits per event in same channel?
        h2_implant_strip_mult[i] = MakeTH2(dir_stats[i], "I", Form("h2_implant_strip_mult_dssd%i", i), "Strip vs Strip Multiplicity", 65, 0, 65, 10, 0, 10, "Strip (X then Y)", "Strip Multiplicity"); // strip (x then y) vs # of times fired
        h1_implant_side_x_hitpattern[i] = MakeTH1(dir_stats[i], "I", Form("h1_implant_side_x_hitpattern_dssd%i", i), "Side X Hit Pattern", 32, 0, 32, "X Strip", kRed-3, kBlack);
        h1_implant_side_y_hitpattern[i] = MakeTH1(dir_stats[i], "I", Form("h1_implant_side_y_hitpattern_dssd%i", i), "Side Y Hit Pattern", 32, 0, 32, "Y Strip", kRed-3, kBlack);

        h2_decay_strip_xy[i] = MakeTH2(dir_decays[i], "I", Form("h2_decay_strip_xy_dssd%i", i), "Decay Hit Pattern", 32, 0, 32, 32, 0, 32);
        h1_decay_e[i] = MakeTH1(dir_decays[i], "F", Form("h1_decay_e_dssd%i", i), "Decay Energy", 1000, 0, 200000);
        h2_decay_e_xy[i] = MakeTH2(dir_decays[i], "F", Form("h2_decay_e_xy_dssd%i", i), "Decay Energy (X vs Y)", 1000, 0, 200000, 1000, 0, 200000);
        h2_decay_strip_1d_e[i] = MakeTH2(dir_decays[i], "F", Form("h2_decay_strip_1d_e_dssd%i",i), "Decay Energy (X then Y strips)", 64, 0, 64, 1000, 0, 200000);

        h2_implant_strip_xy[i] = MakeTH2(dir_implants[i], "I", Form("h2_implant_strip_xy_dssd%i", i), "Implant Pattern (Strips)", 32, 0, 32, 32, 0, 32);
        h1_implant_e[i] = MakeTH1(dir_implants[i], "F", Form("h1_implant_e_dssd%i", i), "Implant Energy", 1000, 0, 200000);
        h2_implant_e_xy[i] = MakeTH2(dir_implants[i], "F", Form("h2_implant_e_xy_dssd%i", i), "Implant Energy (X vs Y)", 1000, 0, 200000, 1000, 0, 200000);
        h2_implant_strip_1d_e[i] = MakeTH2(dir_implants[i], "F", Form("h2_implant_strip_1d_e_dssd%i", i), "Implant Energy (X then Y strips)", 64, 0, 64, 1000, 0, 200000);

        implant_strips_fired[i] = new std::set<int>[2];
        implant_side_x_mult[i] = new int[32];
        implant_side_y_mult[i] = new int[32];
        
        decay_strips_fired[i] = new std::set<int>[2];
        decay_side_x_mult[i] = new int[32];
        decay_side_y_mult[i] = new int[32];

        for (int j = 0; j < 32; j++)
        {
            implant_side_x_mult[i][j] = 0;
            implant_side_y_mult[i][j] = 0;
            decay_side_x_mult[i][j] = 0;
            decay_side_y_mult[i][j] = 0;
        }
        decay_strips_fired[i][0].clear(); decay_strips_fired[i][1].clear();
        implant_strips_fired[i][0].clear(); implant_strips_fired[i][1].clear();

    }

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

    if (implantHitArray->size() == 0 && decayHitArray->size() == 0) return;

    for (auto const & i : *implantHitArray)
    {
        implant_strips_fired[i.DSSD][0].insert(i.StripX);
        implant_strips_fired[i.DSSD][1].insert(i.StripY);
        implant_side_x_mult[i.DSSD][int(i.StripX)]++;
        implant_side_y_mult[i.DSSD][int(i.StripY)]++;

        h2_implant_strip_xy[i.DSSD]->Fill(i.StripX, i.StripY);
        h1_implant_side_x_hitpattern[i.DSSD]->Fill(i.StripX);
        h1_implant_side_y_hitpattern[i.DSSD]->Fill(i.StripY);

        h1_implant_e[i.DSSD]->Fill(i.Energy);

        h2_implant_e_xy[i.DSSD]->Fill(i.EnergyX, i.EnergyY);
        h2_implant_strip_1d_e[i.DSSD]->Fill(i.StripX, i.EnergyX);
        h2_implant_strip_1d_e[i.DSSD]->Fill(i.StripY + 32, i.EnergyY);

    }

    for (int i = 0; i < nDets; i++)
    {
        h1_implant_side_x_mult[i]->Fill(implant_strips_fired[i][0].size());
        h1_implant_side_y_mult[i]->Fill(implant_strips_fired[i][1].size());
        for (int j = 0; j < 32; j++)
        {
            h2_implant_strip_mult[i]->Fill(j, implant_side_x_mult[i][j]);
            h2_implant_strip_mult[i]->Fill(j+32, implant_side_y_mult[i][j]);
        }
    }

    for (auto const & d : *decayHitArray)
    {
        decay_strips_fired[d.DSSD][0].insert(d.StripX);
        decay_strips_fired[d.DSSD][1].insert(d.StripY);
        decay_side_x_mult[d.DSSD][int(d.StripX)]++;
        decay_side_y_mult[d.DSSD][int(d.StripY)]++;

        h2_decay_strip_xy[d.DSSD]->Fill(d.StripX, d.StripY);
        h1_decay_side_x_hitpattern[d.DSSD]->Fill(d.StripX);
        h1_decay_side_y_hitpattern[d.DSSD]->Fill(d.StripY);

        h1_decay_e[d.DSSD]->Fill(d.Energy);
        h2_decay_e_xy[d.DSSD]->Fill(d.EnergyX, d.EnergyY);
        h2_decay_strip_1d_e[d.DSSD]->Fill(d.StripX, d.EnergyX);
        h2_decay_strip_1d_e[d.DSSD]->Fill(d.StripY + 32, d.EnergyY);
    }

    for (int i = 0; i < nDets; i++)
    {
        h1_decay_side_x_mult[i]->Fill(decay_strips_fired[i][0].size());
        h1_decay_side_y_mult[i]->Fill(decay_strips_fired[i][1].size());
        for (int j = 0; j < 32; j++)
        {
            h2_decay_strip_mult[i]->Fill(j, decay_side_x_mult[i][j]);
            h2_decay_strip_mult[i]->Fill(j+32, decay_side_y_mult[i][j]);
        }
    }

    fNEvents++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void BB7FebexOnlineSpectra::FinishEvent()
{
    for (int i = 0; i < nDets; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            implant_side_x_mult[i][j] = 0;
            implant_side_y_mult[i][j] = 0;
            decay_side_x_mult[i][j] = 0;
            decay_side_y_mult[i][j] = 0;
        }
        decay_strips_fired[i][0].clear(); decay_strips_fired[i][1].clear();
        implant_strips_fired[i][0].clear(); implant_strips_fired[i][1].clear();
    }
    
   
}

void BB7FebexOnlineSpectra::FinishTask()
{
    if (fNEvents > 0)
    {
        c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    }
}

ClassImp(BB7FebexOnlineSpectra)