// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "FimpOnlineSpectra.h"
#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>

FimpOnlineSpectra::FimpOnlineSpectra()
{
}

FimpOnlineSpectra::FimpOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fimpRawArray(nullptr)
    , fimpCalArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
    fimp_config = TFimpConfiguration::GetInstance();
}

FimpOnlineSpectra::~FimpOnlineSpectra()
{
    c4LOG(info, "");
}

InitStatus FimpOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fimpRawArray = mgr->InitObjectAs<decltype(fimpRawArray)>("FimpData");
    c4LOG_IF(fatal, !fimpRawArray, "Branch FimpData not found!");
    fimpCalArray = mgr->InitObjectAs<decltype(fimpCalArray)>("FimpCalData");
    c4LOG_IF(fatal, !fimpCalArray, "Branch FimpCalData not found!");

    detector_mapping = fimp_config->Mapping();

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_fimp = new TDirectory("FIMP", "FIMP", "", 0);
    mgr->Register("FIMP", "FIMP Directory", dir_fimp, false);
    histograms->Add(dir_fimp);

    dir_fimp->cd();
    dir_stats = dir_fimp->mkdir("Stats");
    dir_tot = dir_fimp->mkdir("ToT");
    dir_leads = dir_fimp->mkdir("Lead times");
    dir_time_lead = dir_leads->mkdir("Times");
    dir_coarse_clock_lead = dir_leads->mkdir("Coarse Clock");
    dir_fine_lead = dir_leads->mkdir("Fine Times");
    dir_trails = dir_fimp->mkdir("Trail times");
    dir_time_trail = dir_trails->mkdir("Times");
    dir_coarse_clock_trail = dir_trails->mkdir("Coarse Clock");
    dir_fine_trail = dir_trails->mkdir("Fine Times");
    dir_sc41 = dir_fimp->mkdir("SC41");

    // don't hardcode, change!
    h1_fimp_tot.resize(128);
    h1_fimp_lead_times.resize(128);
    h1_fimp_trail_times.resize(128);
    h1_fimp_sc41l_dT.resize(128);
    h1_fimp_sc41r_dT.resize(128);
    h1_fimp_coarse_clock_lead.resize(128);
    h1_fimp_coarse_clock_trail.resize(128);
    h1_fimp_fine_bin_lead.resize(128);
    h1_fimp_fine_bin_trail.resize(128);

    h1_fimp_whiterabbit = MakeTH1(dir_stats, "I", "h1_fimp_whiterabbit", "FIMP White Rabbit Time", 1e3, 1.7e19, 1.8e19, "WR Time [ns]");
    h1_fimp_wr_dt = MakeTH1(dir_stats, "I", "h1_fimp_wr_dt", "WR Time between successive FIMP events", 1e3, 0, 1e6, "dT [ns]", kMagenta, kBlue+2);
    h1_fimp_multiplicity = MakeTH1(dir_stats, "I", "h1_fimp_multiplicity", "FIMP Multiplicity", 128+1, 0, 128+1, "Multiplicity", kRed-3, kBlack);
    h1_fimp_hitpattern = MakeTH1(dir_stats, "I", "h1_fimp_hitpattern", "FIMP Hit Pattern", 128, 0, 128, "Channel", kRed-3, kBlack);

    for (int i = 0; i < 128; i++)
    {
        h1_fimp_tot[i] = MakeTH1(dir_tot, "D", Form("h1_fimp_tot_channel_%i", i), Form("ToT Channel %i", i), 960, fimp_config->EnergyToTMin, fimp_config->EnergyToTMax, "ToT [ns]", kSpring, kBlue+2);
    }

    for (int i = 0; i < 128; i++)
    {   
        h1_fimp_lead_times[i] = MakeTH1(dir_time_lead, "D", Form("h1_fimp_lead_times_channel_%i", i), Form("Lead Times - Channel %i", i), 4e3, 0, 1e8, "Lead Time [ns]");
    }

    for (int i = 0; i < 128; i++)
    {
        h1_fimp_coarse_clock_lead[i] = MakeTH1(dir_coarse_clock_lead, "I", Form("h1_fimp_coarse_clock_lead_channel_%i", i), Form("Lead Coarse Clock - Channel %i", i), 4096, 0, 4096, "Coarse Clock");
    }
    
    for (int i = 0; i < 128; i++)
    {
        h1_fimp_fine_bin_lead[i] = MakeTH1(dir_fine_lead, "I", Form("h1_fimp_fine_bin_lead_channel_%i", i), Form("Lead Fine Time Bins - Channel %i", i), 19, 0, 19, "Fine Time Bin", kGreen+1, kBlack);
    }

    for (int i = 0; i < 128; i++)
    {
        h1_fimp_trail_times[i] = MakeTH1(dir_time_trail, "D", Form("h1_fimp_trail_times_channel_%i", i), Form("Trail times - Channel %i", i), 4e3, 0, 1e8, "Trail Time [ns]");
    }

    for (int i = 0; i < 128; i++)
    {
        h1_fimp_coarse_clock_trail[i] = MakeTH1(dir_coarse_clock_trail, "D", Form("h1_fimp_coarse_clock_trail_channel_%i", i), Form("Trail Coarse Clock - Channel %i", i), 4096, 0, 4096, "Coarse Clock");
    }
    
    for (int i = 0; i < 128; i++)
    {   
        h1_fimp_fine_bin_trail[i] = MakeTH1(dir_fine_trail, "I", Form("h1_fimp_fine_bin_trail_channel_%i", i), Form("Trail Fine Time Bins - Channel %i", i), 19, 0, 19, "Fine Time Bin", kGreen+1, kBlack);
    }

    for (int i = 0; i < 128; i++)
    {
        h1_fimp_sc41l_dT[i] = MakeTH1(dir_sc41, "D", Form("h1_fimp_sc41l_dT_channel_%i", i), Form("dT SC41L - Channel %i", i), 1e3, 0, 2e3, "dT [ns]", kMagenta, kBlue+2);
        h1_fimp_sc41r_dT[i] = MakeTH1(dir_sc41, "D", Form("h1_fimp_sc41r_dT_channel_%i", i), Form("dT SC41R - Channel %i", i), 1e3, 0, 2e3, "dT [ns]", kMagenta, kBlue+2);
    }

    run->GetHttpServer()->RegisterCommand("Reset_Fimp_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void FimpOnlineSpectra::Reset_Histo()
{
    for (int i = 0; i < 128; i++)
    {   
        h1_fimp_tot[i]->Reset();
        h1_fimp_lead_times[i]->Reset();
        h1_fimp_coarse_clock_lead[i]->Reset();
        h1_fimp_fine_bin_lead[i]->Reset();
        h1_fimp_trail_times[i]->Reset();
        h1_fimp_coarse_clock_trail[i]->Reset();
        h1_fimp_fine_bin_trail[i]->Reset();
        h1_fimp_sc41l_dT[i]->Reset();
        h1_fimp_sc41r_dT[i]->Reset();
    }

    h1_fimp_whiterabbit->Reset();
    h1_fimp_wr_dt->Reset();
    h1_fimp_multiplicity->Reset();
    h1_fimp_hitpattern->Reset();



    c4LOG(info, "Success!");
}

void FimpOnlineSpectra::Exec(Option_t* option)
{   
    int hit_counter = 0;
    int64_t wr_t = 0;
    for (auto const & fimpCalItem : *fimpCalArray)
    {   
        // wr same for each hit/channel
        wr_t = fimpCalItem.Get_wr_t();
        if (hit_counter == 0) h1_fimp_whiterabbit->Fill(wr_t);
       
        int channel = fimpCalItem.Get_channel();
        h1_fimp_hitpattern->Fill(channel);

        double tot = fimpCalItem.Get_ToT();
        double lead_time = fimpCalItem.Get_lead_time();
        double trail_time = fimpCalItem.Get_trail_time();

        if (channel == 128) continue; // fill trigger stuff?

        h1_fimp_tot[channel]->Fill(tot);
        h1_fimp_lead_times[channel]->Fill(lead_time);
        h1_fimp_trail_times[channel]->Fill(trail_time);

        if (channel == fimp_config->SC41L())
        {   
            // should we copy fimpCalArray to preserve it's pointer?
            for (const auto & fimpCalItem2 : *fimpCalArray)
            {
                if (fimpCalItem2.Get_channel() == 128) continue;
                h1_fimp_sc41l_dT[fimpCalItem2.Get_channel()]->Fill(lead_time - fimpCalItem2.Get_lead_time());
            }
        }
        else if (channel == fimp_config->SC41R())
        {
            for (const auto & fimpCalItem2 : *fimpCalArray)
            {
                if (fimpCalItem2.Get_channel() == 128) continue;
                h1_fimp_sc41r_dT[fimpCalItem2.Get_channel()]->Fill(lead_time - fimpCalItem2.Get_lead_time());
            }
        }

        hit_counter++;
    }

    if (wr_t == 0) return;

    int64_t wr_dt = wr_t - prev_wr_t;
    h1_fimp_wr_dt->Fill(wr_dt);
    prev_wr_t = wr_t;

    h1_fimp_multiplicity->Fill(hit_counter);

    for (auto const & fimpRawItem : *fimpRawArray)
    {
        uint16_t channel = fimpRawItem.Get_channel();
        std::vector<uint16_t> lead_coarse_time = fimpRawItem.Get_lead_coarse_time();
        std::vector<uint16_t> trail_coarse_time = fimpRawItem.Get_trail_coarse_time();
        std::vector<uint16_t> lead_ft_raw = fimpRawItem.Get_raw_lead_fine_time();
        std::vector<uint16_t> trail_ft_raw = fimpRawItem.Get_raw_trail_fine_time();

        if (channel == 128) continue;

        for (int i = 0; i < std::min(lead_coarse_time.size(), trail_coarse_time.size()); i++)
        {
            h1_fimp_coarse_clock_lead[channel]->Fill(lead_coarse_time[i] & 0xFFF);
            h1_fimp_fine_bin_lead[channel]->Fill(lead_ft_raw[i]);
            h1_fimp_coarse_clock_trail[channel]->Fill(trail_coarse_time[i] & 0xFFF);
            h1_fimp_fine_bin_trail[channel]->Fill(trail_ft_raw[i]);
        }
        
    }
    
    fNEvents += 1;
}

void FimpOnlineSpectra::FinishEvent()
{

}

void FimpOnlineSpectra::FinishTask()
{

}

ClassImp(FimpOnlineSpectra)
