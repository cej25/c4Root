// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BB7OnlineSpectra.h"
#include "EventHeader.h"
#include "BB7VmeCalData.h"
#include "AnalysisTools.h"
#include "c4Logger.h"

// root
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"


BB7OnlineSpectra::BB7OnlineSpectra()
    :   FairTask()
    ,   fHitBB7(NULL)
    ,   implantArray(nullptr)
    ,   decayArray(nullptr)
    ,   header(nullptr)
{

}

BB7OnlineSpectra::~BB7OnlineSpectra()
{

}

InitStatus BB7OnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitBB7 = (TClonesArray*)mgr->GetObject("BB7VmeCalData");
    c4LOG_IF(fatal, !fHitBB7, "Branch BB7VmeCalData not found!");

    implantArray = mgr->InitObjectAs<decltype(implantArray)>("BB7ImplantData");
    c4LOG_IF(fatal, !implantArray, "Branch BB7ImplantData not found!");
    decayArray = mgr->InitObjectAs<decltype(decayArray)>("BB7DecayData");
    c4LOG_IF(fatal, !decayArray, "Branch BB7DecayData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    // set up config later

    TDirectory::TContext ctx(nullptr);

    dir_bb7 = new TDirectory("BB7", "BB7", "", 0);
    // mgr->Register("BB7", "BB7 Directory", dir_bb7, false); // allow other tasks to find directory
    histograms->Add(dir_bb7);

    // leave for now - combined
    dir_raw_e = dir_bb7->mkdir("Raw Energy");
    dir_stats = dir_bb7->mkdir("Stats");
    dir_rates = dir_bb7->mkdir("Rate Monitors");
    dir_implants = dir_bb7->mkdir("Implants");
    dir_implant_raw_e = dir_implants->mkdir("Raw Energy");
    dir_implant_stats = dir_implants->mkdir("Stats");
    dir_implant_rates = dir_implants->mkdir("Rate Monitors");
    dir_decays = dir_bb7->mkdir("Decays");
    dir_decay_raw_e = dir_decays->mkdir("Raw Energy");
    dir_decay_stats = dir_decays->mkdir("Stats");
    dir_decay_rates = dir_decays->mkdir("Rate Monitors");

    h1_implant_RawE = new TH1**[2];
    for (int i = 0; i < 2; i++) h1_implant_RawE[i] = new TH1*[32];
    h1_decay_RawE = new TH1**[2];
    for (int i = 0; i < 2; i++) h1_decay_RawE[i] = new TH1*[32];
    h1_implant_hitpattern = new TH1*[2];
    h1_decay_hitpattern = new TH1*[2];
    h1_implant_rates = new TH1**[2];
    for (int i = 0; i < 2; i++) h1_implant_rates[i] = new TH1*[32];
    h1_decay_rates = new TH1**[2];
    for (int i = 0; i < 2; i++) h1_decay_rates[i] = new TH1*[32];
    implant_counters = new int*[2];
    for (int i = 0; i < 2; i++) implant_counters[i] = new int[32];
    decay_counters = new int*[2];
    for (int i = 0; i < 2; i++) decay_counters[i] = new int[32];
    implant_rates = new float*[2];
    for (int i = 0; i < 2; i++) implant_rates[i] = new float[32];
    decay_rates = new float*[2];
    for (int i = 0; i < 2; i++) decay_rates[i] = new float[32];

    // base on config later - add detector loop later also
    for (int side = 0; side < 2; side++)
    {   
        for (int strip = 0; strip < 32; strip++)
        {
            h1_bb7_RawE[side][strip] = MakeTH1(dir_raw_e, "D", Form("h1_bb7_RawE_Side%i_Strip%i", side, strip+1), Form("Raw Energy BB7 Side %i Strip %i", side, strip+1), 10000, 0, 10000); // 12 bit adc should only be 4096 max but saw higher?

            h1_implant_RawE[side][strip] = MakeTH1(dir_implant_raw_e, "D", Form("h1_implant_RawE_Side%i_Strip%i", side, strip+1), Form("Implant Raw Energy - Side %i, Strip %i", side, strip+1), 10000, 0, 10000, "Raw ADC [a.u.]", kOrange+7, kBlue+2);
            h1_decay_RawE[side][strip] = MakeTH1(dir_decay_raw_e, "D", Form("h1_decay_RawE_Side%i_Strip%i", side, strip+1), Form("Decay Raw Energy - Side %i, Strip %i", side, strip+1), 10000, 0, 10000, "Raw ADC [a.u.]", kSpring, kBlue+2);
            
            // these rates will need to change once we sort out clustering etc
            // i don't think they should be per side/strip, they should be per dssd
            // but for now, lets look at per side/strip and see what it shows
            h1_implant_rates[side][strip] = MakeTH1(dir_implant_rates, "I", Form("h1_implant_rates_Side%i_Strip%i", side, strip+1), Form("Implant Rate - Side %i Strip %i", side, strip+1), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
            h1_decay_rates[side][strip] = MakeTH1(dir_decay_rates, "I", Form("h1_decay_rates_Side%i_Strip%i", side, strip+1), Form("Decay Rate - Side %i Strip %i", side, strip+1), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
        }

        h1_bb7_hitpattern[side] = MakeTH1(dir_stats, "I", Form("h1_bb7_hitpattern_Side%i", side), Form("BB7 Hit Pattern Side %i", side), 32, 0, 32);

        h1_implant_hitpattern[side] = MakeTH1(dir_implant_stats, "I", Form("h1_implant_hitpattern_Side%i", side), Form("Implant Hit Pattern - Side %i", side), 32, 0, 32, "Strip", kRed, kBlack);
        h1_decay_hitpattern[side] = MakeTH1(dir_decay_stats, "I", Form("h1_decay_hitpattern_Side%i", side), Form("Decay Hit Pattern - Side %i", side), 32, 0, 32, "Strip", kRed, kBlack);

    }



    
    dir_bb7->cd();

    return kSUCCESS;

}

void BB7OnlineSpectra::Exec(Option_t* option)
{
    int64_t bb7_wr = 0;
    if (fHitBB7 && fHitBB7->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitBB7->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            BB7VmeCalData* bb7VmeHit = (BB7VmeCalData*)fHitBB7->At(ihit);
            if (!bb7VmeHit) continue;

            std::vector<int> sides = bb7VmeHit->Get_Sides();
            std::vector<int> strips = bb7VmeHit->Get_Strips();
            std::vector<uint32_t> raw_adc = bb7VmeHit->Get_Raw_ADC();

            for (int j = 0; j < raw_adc.size(); j++)
            {
                h1_bb7_RawE[sides[j]][strips[j]-1]->Fill(raw_adc[j]);

                h1_bb7_hitpattern[sides[j]]->Fill(strips[j]-1);
            }
        }
    }

    for (auto const & implant : *implantArray)
    {   
        bb7_wr = implant.Get_wr_t();
        int side = implant.Get_side();
        int strip = implant.Get_strip();
        h1_implant_hitpattern[side]->Fill(strip-1);

        uint32_t raw_adc = implant.Get_raw_adc();
        h1_implant_RawE[side][strip-1]->Fill(raw_adc);

        implant_counters[side][strip-1]++;
    }

    for (auto const & decay : *decayArray)
    {
        bb7_wr = decay.Get_wr_t();
        int side = decay.Get_side();
        int strip = decay.Get_strip();
        h1_decay_hitpattern[side]->Fill(strip-1);

        uint32_t raw_adc = decay.Get_raw_adc();
        h1_decay_RawE[side][strip-1]->Fill(raw_adc);

        decay_counters[side][strip-1]++;
    }

    int64_t wr_dt = (bb7_wr - saved_bb7_wr) / 1e9; // conv to s
    if (wr_dt > 2) 
    {
        if (saved_bb7_wr != 0)
        {
            for (int side = 0; side < 2; side++)
            {
                for (int strip = 0; strip < 32; strip++)
                {
                    
                    implant_rates[side][strip] = implant_counters[side][strip] / wr_dt;
                    h1_implant_rates[side][strip]->SetBinContent(rate_running_count, implant_rates[side][strip]);
                    decay_rates[side][strip] = decay_counters[side][strip] / wr_dt;
                    h1_decay_rates[side][strip]->SetBinContent(rate_running_count, decay_rates[side][strip]);
                }
            }
        }
        
        saved_bb7_wr = bb7_wr;
        rate_running_count++;
        for (int side = 0; side < 2; side++) 
        {
            for (int strip = 0; strip < 32; strip++)
            {   
                implant_counters[side][strip] = 0;
                decay_counters[side][strip] = 0;
            }
        }
        if (rate_running_count == 1800) rate_running_count = 0;
    }
}

void BB7OnlineSpectra::FinishEvent()
{

}

void BB7OnlineSpectra::FinishTask()
{
    //c4LOG(info, Form("Plotted %i Events", fNEvents));
}
