#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "BB7GermaniumCorrelationsOnline.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TDirectory.h"
#include "THttpServer.h"

BB7GermaniumCorrelationsOnline::BB7GermaniumCorrelationsOnline()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
{
}

BB7GermaniumCorrelationsOnline::BB7GermaniumCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
{
    // bb7 and germanium configs
    germanium_config = TGermaniumConfiguration::GetInstance();
    bb7_config = TBB7FebexConfiguration::GetInstance();
}


BB7GermaniumCorrelationsOnline::~BB7GermaniumCorrelationsOnline()
{
    c4LOG(info, "Deleting BB7GermaniumCorrelationsOnline task.");
}

InitStatus BB7GermaniumCorrelationsOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    // bb7 and germanium
    bb7empty = mgr->InitObjectAs<decltype(bb7empty)>("BB7EmptyData");
    c4LOG_IF(fatal, !bb7empty, "Branch BB7EmptyData not found!");
    bb7rawHits = mgr->InitObjectAs<decltype(bb7rawHits)>("BB7FebexData");
    c4LOG_IF(fatal, !bb7rawHits, "Branch BB7FebexData not found!");

    bb7calImplants = mgr->InitObjectAs<decltype(bb7calImplants)>("BB7FebexCalImplants");
    bb7calDecays = mgr->InitObjectAs<decltype(bb7calDecays)>("BB7FebexCalDecays");
    c4LOG_IF(fatal, !bb7calImplants, "Branch BB7FebexCalImplants not found!");
    c4LOG_IF(fatal, !bb7calDecays, "Branch BB7FebexCalDecays not found!");

    bb7decays = mgr->InitObjectAs<decltype(bb7decays)>("BB7FebexDecays");
    c4LOG_IF(fatal, !bb7decays, "Branch BB7FebexDecays not found!");
    bb7implants = mgr->InitObjectAs<decltype(bb7implants)>("BB7FebexImplants");
    c4LOG_IF(fatal, !bb7implants, "Branch BB7FebexImplants not found!");

    germaniumHits = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !germaniumHits, "Branch GermaniumCalData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_germanium = (TDirectory*)mgr->GetObject("DEGAS");
    if (dir_germanium == nullptr) 
    {   
        c4LOG(info, "Creating DEGAS Directory");
        dir_germanium = new TDirectory("DEGAS", "DEGAS", "", 0);
        mgr->Register("DEGAS", "DEGAS Directory", dir_germanium, false); // allow other tasks to find this
        histograms->Add(dir_germanium);
        dir_germanium->cd();
        dir_germanium_bb7 = new TDirectory("BB7-DEGAS Correlations", "BB7-DEGAS Correlations", "", 0);
        mgr->Register("BB7-DEGAS", "BB7-DEGAS Correlations Directory", dir_germanium_bb7, false);
    }
    // I want to not do this, would be really nice if we had a vector of Gates, js.
    else
    {
        dir_germanium_bb7 = (TDirectory*)mgr->GetObject("BB7-DEGAS");
        if (dir_germanium_bb7 == nullptr)
        {
            dir_germanium->cd(); // does this work?
            dir_germanium_bb7 = new TDirectory("BB7-DEGAS Correlations", "BB7-DEGAS Correlations", "", 0);
            mgr->Register("BB7-DEGAS", "BB7-DEGAS Correlations Directory", dir_germanium_bb7, false);
        }
    }

    h1_germanium_bb7_wr_dt = MakeTH1(dir_germanium_bb7, "F", "h1_germanium_bb7_wr_dt", "BB7-DEGAS WR dT", 2000, -1000, 1000);
    h1_gamma_after_decay = MakeTH1(dir_germanium_bb7, "F", "h1_gamma_after_decay", "Gammas after BB7 decay", 2000, 0, 2000);

    
    

    return kSUCCESS;

}


void BB7GermaniumCorrelationsOnline::Exec(Option_t* option)
{ 
    // stuff
    if (bb7rawHits->size() > 0) n_bb7_f0++;
    if (bb7empty->size() > 0) n_bb7_empty++;
    if (bb7calDecays->size() > 0) n_cal_decay++;
    if (bb7calImplants->size() > 0) n_cal_implant++;
    if (bb7decays->size() > 0) n_decay_event++;
    if (bb7implants->size() > 0) n_implant_event++;

    if (germaniumHits->GetEntriesFast() > 0)
    {
        if (bb7rawHits->size() > 0) n_coinc_f0++;
        if (bb7empty->size() > 0) n_coinc_empty++;
        if (bb7calDecays->size() > 0) n_coinc_cal_decay++;
        if (bb7calImplants->size() > 0) n_coinc_cal_imp++;
        if (bb7decays->size() > 0) n_coinc_decay++;
        if (bb7implants->size() > 0) n_coinc_imp++;
    }


    // if (germaniumHits->GetEntriesFast() > 0) std::cout << germaniumHits->GetEntriesFast() << std::endl;

    // if (bb7rawHits->size() > 0 && germaniumHits->GetEntriesFast() > 0)
    // {
    //     auto const & rawHit = bb7rawHits->at(0);
    //     int64_t wr_bb7 = rawHit.Get_wr_t();
    //     Int_t nHits = germaniumHits->GetEntriesFast();
        
    //     for (Int_t ihit = 0; ihit < nHits; ihit++)
    //     {
    //         GermaniumCalData* hit1 = (GermaniumCalData*)germaniumHits->At(ihit);

    //         int detector_id1 = hit1->Get_detector_id();
    //         // if (germanium_config->IsDetectorAuxilliary(detector_id1)) continue;

    //         int64_t wr_germ = hit1->Get_wr_t();
    //         std::cout << "bb7 wr::: " << wr_bb7 << " (crate: " << rawHit.Get_crate_id() << ")" << std::endl;
    //         std::cout << "germanium wr:: " << wr_germ << std::endl;
    //         std::cout << "dt:: " << wr_germ - wr_bb7 << std::endl;

    //         break;
    //     }
    // }

    if (bb7decays->size() <= 0) return;

    fNEvents++;

    for (auto const & d : *bb7decays)
    {
        int64_t wr_bb7 = d.Time;

        // std::cout << "wr bb7: " << wr_bb7 << std::endl;

        if (germaniumHits && germaniumHits->GetEntriesFast() > 0)
        {
            std::cout << "hello1" << std::endl;
    
            Int_t nHits = germaniumHits->GetEntriesFast();
        
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {
                std::cout << "hello2" << std::endl;
                GermaniumCalData* hit1 = (GermaniumCalData*)germaniumHits->At(ihit);

                int detector_id1 = hit1->Get_detector_id();
                // if (germanium_config->IsDetectorAuxilliary(detector_id1)) continue;

                std::cout << "hello3? " << std::endl;

                int64_t wr_ge = hit1->Get_wr_t();
                int64_t dt = wr_ge - wr_bb7;

                if (ihit == 0) h1_germanium_bb7_wr_dt->Fill(dt);
                h1_gamma_after_decay->Fill(hit1->Get_channel_energy());

            }
        }

        break; // don't double count

    }

        
} // nHits


void BB7GermaniumCorrelationsOnline::FinishEvent()
{
}

void BB7GermaniumCorrelationsOnline::FinishTask()
{
    c4LOG(info, Form("BB7 WR w/ F0:: %i", n_bb7_f0));
    c4LOG(info, Form("BB7 WR empty:: %i", n_bb7_empty));
    c4LOG(info, Form("BB7 WR w/ F0 Coinc w/ Germanium:: %i", n_coinc_f0));
    c4LOG(info, Form("BB7 WR empty Coinc w/ Germanium:: %i", n_coinc_empty));

    c4LOG(info, Form("Cal Decay Events:: %i", n_cal_decay));
    c4LOG(info, Form("Cal Implant Events:: %i", n_cal_implant));
    c4LOG(info, Form("Cal Decay Coinc w/ Germanium:: %i", n_coinc_cal_decay));
    c4LOG(info, Form("Cal Implant Coinc w/ Germanium:: %i", n_coinc_cal_imp));

    c4LOG(info, Form("Clustered Decays Events:: %i", n_decay_event));
    c4LOG(info, Form("Clustered Implant Events:: %i", n_implant_event));
    c4LOG(info, Form("Clustered Decay Coinc w/ Germanium :: %i", n_coinc_decay));
    c4LOG(info, Form("Clustered Implant w/ Germanium:: %i", n_coinc_imp));

}


ClassImp(BB7GermaniumCorrelationsOnline)
