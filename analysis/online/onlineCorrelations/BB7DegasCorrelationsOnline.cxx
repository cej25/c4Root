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
 *                                C.E. Jones                                  *
 *                                 06.05.25                                   *
 ******************************************************************************/

#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "BB7DegasCorrelationsOnline.h"
#include "BB7RawData.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TDirectory.h"
#include "THttpServer.h"

BB7DegasCorrelationsOnline::BB7DegasCorrelationsOnline()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
{
}

BB7DegasCorrelationsOnline::BB7DegasCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
{
    // bb7 and degas configs
    degas_config = TDegasConfiguration::GetInstance();
    bb7_config = TBB7FebexConfiguration::GetInstance();
}


BB7DegasCorrelationsOnline::~BB7DegasCorrelationsOnline()
{
    c4LOG(info, "Deleting BB7DegasCorrelationsOnline task.");
}

InitStatus BB7DegasCorrelationsOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    // bb7 and degas
    fRaw = mgr->InitObjectAs<decltype(fRaw)>("BB7FebexRawData");
    c4LOG_IF(fatal, !fRaw, "Branch BB7FebexRawData not found!");

    bb7calImplants = mgr->InitObjectAs<decltype(bb7calImplants)>("BB7FebexCalImplants");
    bb7calDecays = mgr->InitObjectAs<decltype(bb7calDecays)>("BB7FebexCalDecays");
    c4LOG_IF(fatal, !bb7calImplants, "Branch BB7FebexCalImplants not found!");
    c4LOG_IF(fatal, !bb7calDecays, "Branch BB7FebexCalDecays not found!");

    bb7decays = mgr->InitObjectAs<decltype(bb7decays)>("BB7FebexDecays");
    c4LOG_IF(fatal, !bb7decays, "Branch BB7FebexDecays not found!");
    bb7implants = mgr->InitObjectAs<decltype(bb7implants)>("BB7FebexImplants");
    c4LOG_IF(fatal, !bb7implants, "Branch BB7FebexImplants not found!");

    degasHits = (TClonesArray*)mgr->GetObject("DegasCalData");
    if (!degasHits || degasHits->GetClass() != DegasCalData::Class())
    {
        c4LOG(error, "Expected DEGAS hit objects in the input branch");
        return kFATAL;
    }

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_degas = (TDirectory*)mgr->GetObject("DEGAS");
    if (dir_degas == nullptr)
    {
        c4LOG(info, "Creating DEGAS Directory");
        dir_degas = new TDirectory("DEGAS", "DEGAS", "", 0);
        mgr->Register("DEGAS", "DEGAS Directory", dir_degas, false); // allow other tasks to find this
        histograms->Add(dir_degas);
        dir_degas->cd();
        dir_degas_bb7 = new TDirectory("BB7-DEGAS Correlations", "BB7-DEGAS Correlations", "", 0);
        mgr->Register("BB7-DEGAS", "BB7-DEGAS Correlations Directory", dir_degas_bb7, false);
    }
    // I want to not do this, would be really nice if we had a vector of Gates, js.
    else
    {
        dir_degas_bb7 = (TDirectory*)mgr->GetObject("BB7-DEGAS");
        if (dir_degas_bb7 == nullptr)
        {
            dir_degas->cd(); // does this work?
            dir_degas_bb7 = new TDirectory("BB7-DEGAS Correlations", "BB7-DEGAS Correlations", "", 0);
            mgr->Register("BB7-DEGAS", "BB7-DEGAS Correlations Directory", dir_degas_bb7, false);
        }
    }

    h1_degas_bb7_wr_dt = MakeTH1(dir_degas_bb7, "F", "h1_degas_bb7_wr_dt", "BB7-DEGAS WR dT", 2000, -1000, 1000);
    h1_gamma_after_decay = MakeTH1(dir_degas_bb7, "F", "h1_gamma_after_decay", "Gammas after BB7 decay", 2000, 0, 2000);




    return kSUCCESS;

}


void BB7DegasCorrelationsOnline::Exec(Option_t* option)
{
    bool hasHits = false;
    bool hasEmptyBoard = false;
    for (const auto* crate : {&fRaw->first, &fRaw->second})
    {
        for (const auto& board : crate->boards)
        {
            hasHits |= !board.summary.hits.empty();
            hasEmptyBoard |= board.reportedHits == 0;
        }
    }

    if (hasHits) n_bb7_f0++;
    if (hasEmptyBoard) n_bb7_empty++;
    if (bb7calDecays->size() > 0) n_cal_decay++;
    if (bb7calImplants->size() > 0) n_cal_implant++;
    if (bb7decays->size() > 0) n_decay_event++;
    if (bb7implants->size() > 0) n_implant_event++;

    if (degasHits->GetEntriesFast() > 0)
    {
        if (hasHits) n_coinc_f0++;
        if (hasEmptyBoard) n_coinc_empty++;
        if (bb7calDecays->size() > 0) n_coinc_cal_decay++;
        if (bb7calImplants->size() > 0) n_coinc_cal_imp++;
        if (bb7decays->size() > 0) n_coinc_decay++;
        if (bb7implants->size() > 0) n_coinc_imp++;
    }


    if (bb7decays->size() <= 0) return;

    fNEvents++;

    for (auto const & d : *bb7decays)
    {
        int64_t wr_bb7 = d.Time;

        // std::cout << "wr bb7: " << wr_bb7 << std::endl;

        if (degasHits && degasHits->GetEntriesFast() > 0)
        {
            std::cout << "hello1" << std::endl;

            Int_t nHits = degasHits->GetEntriesFast();

            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {
                std::cout << "hello2" << std::endl;
                DegasCalData* hit1 = (DegasCalData*)degasHits->At(ihit);

                int detector_id1 = hit1->Get_detector_id();
                // if (degas_config->IsDetectorAuxilliary(detector_id1)) continue;

                std::cout << "hello3? " << std::endl;

                int64_t wr_ge = hit1->Get_wr_t();
                int64_t dt = wr_ge - wr_bb7;

                if (ihit == 0) h1_degas_bb7_wr_dt->Fill(dt);
                h1_gamma_after_decay->Fill(hit1->Get_channel_energy());

            }
        }

        break; // don't double count

    }


} // nHits


void BB7DegasCorrelationsOnline::FinishEvent()
{
}

void BB7DegasCorrelationsOnline::FinishTask()
{
    c4LOG(info, Form("BB7 WR w/ F0:: %i", n_bb7_f0));
    c4LOG(info, Form("BB7 WR empty:: %i", n_bb7_empty));
    c4LOG(info, Form("BB7 WR w/ F0 Coinc w/ Degas:: %i", n_coinc_f0));
    c4LOG(info, Form("BB7 WR empty Coinc w/ Degas:: %i", n_coinc_empty));

    c4LOG(info, Form("Cal Decay Events:: %i", n_cal_decay));
    c4LOG(info, Form("Cal Implant Events:: %i", n_cal_implant));
    c4LOG(info, Form("Cal Decay Coinc w/ Degas:: %i", n_coinc_cal_decay));
    c4LOG(info, Form("Cal Implant Coinc w/ Degas:: %i", n_coinc_cal_imp));

    c4LOG(info, Form("Clustered Decays Events:: %i", n_decay_event));
    c4LOG(info, Form("Clustered Implant Events:: %i", n_implant_event));
    c4LOG(info, Form("Clustered Decay Coinc w/ Degas :: %i", n_coinc_decay));
    c4LOG(info, Form("Clustered Implant w/ Degas:: %i", n_coinc_imp));

}


ClassImp(BB7DegasCorrelationsOnline)
