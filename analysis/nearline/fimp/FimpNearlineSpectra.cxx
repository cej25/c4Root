// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "FimpNearlineSpectra.h"
#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>

FimpNearlineSpectra::FimpNearlineSpectra()
{
    fimp_config = TFimpConfiguration::GetInstance();
    fNEvents=0;
}

FimpNearlineSpectra::FimpNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
    , fimpRawArray(nullptr)
    , fimpCalArray(nullptr)
{
    
}

FimpNearlineSpectra::~FimpNearlineSpectra()
{
    c4LOG(info, "Destroyied FimpNearlineSpectra properly.");
}

InitStatus FimpNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fimpRawArray = mgr->InitObjectAs<decltype(fimpRawArray)>("FimpData");
    c4LOG_IF(fatal, !fimpRawArray, "Branch FimpData not found!");
    fimpCalArray = mgr->InitObjectAs<decltype(fimpCalArray)>("FimpCalData");
    c4LOG_IF(fatal, !fimpCalArray, "Branch FimpCalData not found!");

    //detector_mapping = fimp_config->Mapping();

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fimp = gDirectory->mkdir("FIMP");
    mgr->Register("FIMP", "FIMP Directory", dir_fimp, false); 

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
    dir_hits = dir_fimp->mkdir("Hit map");
    dir_pos = dir_fimp->mkdir("Positions");

    // don't hardcode, change!
    h1_fimp_tot.resize(256);
    h1_fimp_lead_times.resize(256);
    h1_fimp_trail_times.resize(256);
    h1_fimp_sc41l_dT.resize(256);
    h1_fimp_sc41r_dT.resize(256);
    h1_fimp_coarse_clock_lead.resize(256);
    h1_fimp_coarse_clock_trail.resize(256);
    h1_fimp_fine_bin_lead.resize(256);
    h1_fimp_fine_bin_trail.resize(256);
    
    h1_fimp_whiterabbit = MakeTH1(dir_stats, "I", "h1_fimp_whiterabbit", "FIMP White Rabbit Time", 1e3, 1.7e19, 1.8e19, "WR Time [ns]");
    h1_fimp_wr_dt = MakeTH1(dir_stats, "I", "h1_fimp_wr_dt", "WR Time between successive FIMP events", 1e3, 0, 1e6, "dT [ns]", kMagenta, kBlue+2);
    h1_fimp_multiplicity = MakeTH1(dir_stats, "I", "h1_fimp_multiplicity", "FIMP Multiplicity", 256+1, 0, 256+1, "Multiplicity", kRed-3, kBlack);
    h1_fimp_hitpattern = MakeTH1(dir_stats, "I", "h1_fimp_hitpattern", "FIMP Hit Pattern", 256, 0, 256, "Channel", kRed-3, kBlack);
    h2_fimp_hits_layer1 = MakeTH2(dir_hits, "I", "h2_fimp_hits_layer1", "Hits map for layer 1", 16, 0, 17, 16, 0, 17, "x", "y");
    h2_fimp_hits_layer2 = MakeTH2(dir_hits, "I", "h2_fimp_hits_layer2", "Hits map for layer 1", 16, 0, 17, 16, 0, 17, "x", "y");
    h2_fimp_hits_layer3 = MakeTH2(dir_hits, "I", "h2_fimp_hits_layer3", "Hits map for layer 1", 16, 0, 17, 16, 0, 17, "x", "y");
    
    for (int i = 0; i < 256; i++)
    {
        h1_fimp_tot[i] = MakeTH1(dir_tot, "D", Form("h1_fimp_tot_channel_%i", i), Form("ToT Channel %i", i), 960, fimp_config->EnergyToTMin, fimp_config->EnergyToTMax, "ToT [ns]", kSpring, kBlue+2);
    }

    for (int i = 0; i < 256; i++)
    {   
        h1_fimp_lead_times[i] = MakeTH1(dir_time_lead, "D", Form("h1_fimp_lead_times_channel_%i", i), Form("Lead Times - Channel %i", i), 4e3, 0, 1e8, "Lead Time [ns]");
    }

    for (int i = 0; i < 256; i++)
    {
        h1_fimp_coarse_clock_lead[i] = MakeTH1(dir_coarse_clock_lead, "I", Form("h1_fimp_coarse_clock_lead_channel_%i", i), Form("Lead Coarse Clock - Channel %i", i), 4096, 0, 4096, "Coarse Clock");
    }
    
    for (int i = 0; i < 256; i++)
    {
        h1_fimp_fine_bin_lead[i] = MakeTH1(dir_fine_lead, "I", Form("h1_fimp_fine_bin_lead_channel_%i", i), Form("Lead Fine Time Bins - Channel %i", i), 19, 0, 19, "Fine Time Bin", kGreen+1, kBlack);
    }

    for (int i = 0; i < 256; i++)
    {
        h1_fimp_trail_times[i] = MakeTH1(dir_time_trail, "D", Form("h1_fimp_trail_times_channel_%i", i), Form("Trail times - Channel %i", i), 4e3, 0, 1e8, "Trail Time [ns]");
    }

    for (int i = 0; i < 256; i++)
    {
        h1_fimp_coarse_clock_trail[i] = MakeTH1(dir_coarse_clock_trail, "D", Form("h1_fimp_coarse_clock_trail_channel_%i", i), Form("Trail Coarse Clock - Channel %i", i), 4096, 0, 4096, "Coarse Clock");
    }
    
    for (int i = 0; i < 256; i++)
    {   
        h1_fimp_fine_bin_trail[i] = MakeTH1(dir_fine_trail, "I", Form("h1_fimp_fine_bin_trail_channel_%i", i), Form("Trail Fine Time Bins - Channel %i", i), 19, 0, 19, "Fine Time Bin", kGreen+1, kBlack);
    }

    for (int i = 0; i < 256; i++)
    {
        h1_fimp_sc41l_dT[i] = MakeTH1(dir_sc41, "D", Form("h1_fimp_sc41l_dT_channel_%i", i), Form("dT SC41L - Channel %i", i), 1e3, 0, 2e3, "dT [ns]", kMagenta, kBlue+2);
        h1_fimp_sc41r_dT[i] = MakeTH1(dir_sc41, "D", Form("h1_fimp_sc41r_dT_channel_%i", i), Form("dT SC41R - Channel %i", i), 1e3, 0, 2e3, "dT [ns]", kMagenta, kBlue+2);
    }

    //Position histograms
    h3_position = MakeTH3(dir_pos, "D", "h3_fimp_position", "FIMP Position", 16, 0, 16, 16, 0, 16, 3, 0, 3);

    return kSUCCESS;
}

void FimpNearlineSpectra::Exec(Option_t* option)
{   
    int hit_counter = 0;
    int hit_counter1=0, hit_counter2=0, hit_counter3=0;
    int x1T=-1, x1B=-2, x2T=-1, x2B=-2, x3T=-1, x3B=-2;
    int y1R=-1, y1L=-2, y2R=-1, y2L=-2, y3R=-1, y3L=-2;
    for (auto const & fimpCalItem : *fimpCalArray)
    {   
        // wr same for each hit/channel
        if (hit_counter == 0)
        {
            wr_t = fimpCalItem.Get_wr_t();
            h1_fimp_whiterabbit->Fill(wr_t);
        }

        int channel = fimpCalItem.Get_channel();
        h1_fimp_hitpattern->Fill(channel);

        double tot = fimpCalItem.Get_ToT();
        double lead_time = fimpCalItem.Get_lead_time();
        double trail_time = fimpCalItem.Get_trail_time();

        if (channel == 256) continue; // fill trigger stuff?

        h1_fimp_tot[channel]->Fill(tot);
        h1_fimp_lead_times[channel]->Fill(lead_time);
        h1_fimp_trail_times[channel]->Fill(trail_time);
        
        // layer 1:
        if (channel<16) x1T=channel, hit_counter1++;
        if (channel>127 && channel<144) x1B=channel-128, hit_counter1++;
        if (channel>47 && channel<64) y1R=channel-48, hit_counter1++;
        if (channel>175 && channel<192) y1L=channel-176, hit_counter1++;
        
        //layer 2:
        if (channel>15 && channel<32) x2T=channel-16, hit_counter2++;
        if (channel>143 && channel<160) x2B=channel-144, hit_counter2++;
        if (channel>63 && channel<80) y2R=channel-64, hit_counter2++;
        if (channel>191 && channel<208) y2L=channel-192, hit_counter2++;
        
        //layer 3:
        if (channel>31 && channel<48) x3T=channel-32, hit_counter3++;
        if (channel>159 && channel<176) x3B=channel-160, hit_counter3++;
        if (channel>79 && channel<96) y3R=channel-80, hit_counter3++;
        if (channel>207 && channel<224) y3L=channel-208, hit_counter3++;
        /* SC41
        if (channel == fimp_config->SC41L())
        {   
            // should we copy fimpCalArray to preserve it's pointer?
            for (const auto & fimpCalItem2 : *fimpCalArray)
            {
                if (fimpCalItem2.Get_channel() == 256) continue;
                h1_fimp_sc41l_dT[fimpCalItem2.Get_channel()]->Fill(lead_time - fimpCalItem2.Get_lead_time());
            }
        }
        else if (channel == fimp_config->SC41R())
        {
            for (const auto & fimpCalItem2 : *fimpCalArray)
            {
                if (fimpCalItem2.Get_channel() == 256) continue;
                h1_fimp_sc41r_dT[fimpCalItem2.Get_channel()]->Fill(lead_time - fimpCalItem2.Get_lead_time());
            }
        }
        */

        hit_counter++;
    }
    if (x1T==x1B && y1R==y1L && x1T>-1 && y1R>-1 && hit_counter1==4) h2_fimp_hits_layer1->Fill(x1T,y1R);
    if (x2T==x2B && y2R==y2L && x2T>-1 && y2R>-1 && hit_counter2==4) h2_fimp_hits_layer2->Fill(x2T,y2R);
    if (x3T==x3B && y3R==y3L && x3T>-1 && y3R>-1 && hit_counter3==4) h2_fimp_hits_layer3->Fill(x3T,y3R);
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

        if (channel == 256) continue;

        for (int i = 0; i < std::min(lead_coarse_time.size(), trail_coarse_time.size()); i++)
        {
            h1_fimp_coarse_clock_lead[channel]->Fill(lead_coarse_time[i] & 0xFFF);
            h1_fimp_fine_bin_lead[channel]->Fill(lead_ft_raw[i]);
            h1_fimp_coarse_clock_trail[channel]->Fill(trail_coarse_time[i] & 0xFFF);
            h1_fimp_fine_bin_trail[channel]->Fill(trail_ft_raw[i]);
        }
        
    }

    //Reconstruct the position of the hit
    std::vector<std::array<int, 3>> positions;
    for(const auto& fimpCalItem : *fimpCalArray)
    {
        int channel = fimpCalItem.Get_channel();
        positions.emplace_back(std::array<int, 3>{fimp_config->GetX(channel), fimp_config->GetY(channel), fimp_config->GetZ(channel)});
    }


    //Check for an x-y combination that has the same cordinate.
    //Here we do not ask for the t-b and l-r coincidence. 
    //Based on the data one can check if this is required or not
    std::map<int, std::array<int, 3>> positions_filtered;
    for (const auto& pos : positions)
    {
        auto& layer = positions_filtered[pos[2]];
        if (pos[0] > 0)
            layer[0] = pos[0];
        if (pos[1] > 0)
            layer[1] = pos[1];
    }

    for (const auto& pos : positions_filtered)
    {
        if (pos.second[0] > 0 && pos.second[1] > 0)
        {
            h3_position->Fill(pos.second[0], pos.second[1], pos.first);
        }
    }


    fNEvents += 1;
}


void FimpNearlineSpectra::FinishEvent()
{

}

void FimpNearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fimp->Write();
    gDirectory = tmp;
    c4LOG(info, " Fimp events : " << fNEvents );
}

ClassImp(FimpNearlineSpectra)
