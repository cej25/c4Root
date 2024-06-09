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
    ,   residualArray(nullptr)
    ,   header(nullptr)
{
    bb7_config = TBB7VmeConfiguration::GetInstance();
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
    residualArray = mgr->InitObjectAs<decltype(residualArray)>("BB7ResidualData");
    c4LOG_IF(fatal, !residualArray, "Branch BB7ResidualData not found!");

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
    dir_residuals = dir_bb7->mkdir("Residual Signals");

    h1_implant_RawE = new TH1***[bb7_config->NDetectors()];
    h1_decay_RawE = new TH1***[bb7_config->NDetectors()];
    h1_implant_rates = new TH1***[bb7_config->NDetectors()];
    h1_decay_rates = new TH1***[bb7_config->NDetectors()];
    h1_implant_hitpattern = new TH1**[bb7_config->NDetectors()];
    h1_decay_hitpattern = new TH1**[bb7_config->NDetectors()];
    
    implant_counters = new int**[bb7_config->NDetectors()];
    decay_counters = new int**[bb7_config->NDetectors()];
    implant_rates = new float**[bb7_config->NDetectors()];
    decay_rates = new float**[bb7_config->NDetectors()];
    
    for (int i = 0; i < bb7_config->NDetectors(); i++) 
    {
        h1_implant_RawE[i] = new TH1**[bb7_config->NSides()];
        h1_decay_RawE[i] = new TH1**[bb7_config->NSides()];
        h1_implant_rates[i] = new TH1**[bb7_config->NSides()];
        h1_decay_rates[i] = new TH1**[bb7_config->NSides()];
        h1_implant_hitpattern[i] = new TH1*[bb7_config->NSides()];
        h1_decay_hitpattern[i] = new TH1*[bb7_config->NSides()];
        
        implant_counters[i] = new int*[bb7_config->NSides()];
        decay_counters[i] = new int*[bb7_config->NSides()];
        implant_rates[i] = new float*[bb7_config->NSides()];
        decay_rates[i] = new float*[bb7_config->NSides()];

        for (int j = 0; j < bb7_config->NSides(); j++) 
        {
            h1_implant_RawE[i][j] = new TH1*[bb7_config->NStrips()];
            h1_decay_RawE[i][j] = new TH1*[bb7_config->NStrips()];
            h1_implant_rates[i][j] = new TH1*[bb7_config->NStrips()];
            h1_decay_rates[i][j] = new TH1*[bb7_config->NStrips()];

            implant_counters[i][j] = new int[bb7_config->NStrips()];
            decay_counters[i][j] = new int[bb7_config->NStrips()];
            implant_rates[i][j] = new float[bb7_config->NStrips()];
            decay_rates[i][j] = new float[bb7_config->NStrips()];
        }
    }

    for (int det = 0; det < bb7_config->NDetectors(); det++)
    {
        for (int side = 0; side < bb7_config->NSides(); side++)
        {   
            for (int strip = 0; strip < bb7_config->NStrips(); strip++)
            {   
                // old, remove when unused full
                if (det == 0) h1_bb7_RawE[side][strip] = MakeTH1(dir_raw_e, "D", Form("h1_bb7_RawE_Side%i_Strip%i", side, strip+1), Form("Raw Energy BB7 - Side %i Strip %i", side, strip+1), 10000, 0, 10000); // 12 bit adc should only be 4096 max but saw higher?

                h1_implant_RawE[det][side][strip] = MakeTH1(dir_implant_raw_e, "D", Form("h1_implant_RawE_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Implant Raw Energy - Det %i Side %i, Strip %i", det, side, strip+1), 10000, 0, 10000, "Raw ADC [a.u.]", kOrange+7, kBlue+2);
                h1_decay_RawE[det][side][strip] = MakeTH1(dir_decay_raw_e, "D", Form("h1_decay_RawE_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Decay Raw Energy - Det %i Side %i, Strip %i", det, side, strip+1), 10000, 0, 10000, "Raw ADC [a.u.]", kSpring, kBlue+2);
                
                // these rates will need to change once we sort out clustering etc
                // i don't think they should be per side/strip, they should be per dssd
                // but for now, lets look at per side/strip and see what it shows
                h1_implant_rates[det][side][strip] = MakeTH1(dir_implant_rates, "I", Form("h1_implant_rates_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Implant Rate - Det %i Side %i Strip %i", det, side, strip+1), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
                h1_decay_rates[det][side][strip] = MakeTH1(dir_decay_rates, "I", Form("h1_decay_rates_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Decay Rate - Det %i Side %i Strip %i", det, side, strip+1), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
            }

            // old, removed when fully unused
            if (det == 0) h1_bb7_hitpattern[side] = MakeTH1(dir_stats, "I", Form("h1_bb7_hitpattern_Side%i", side), Form("BB7 Hit Pattern Side %i", side), bb7_config->NStrips(), 0, bb7_config->NStrips());

            h1_implant_hitpattern[det][side] = MakeTH1(dir_implant_stats, "I", Form("h1_implant_hitpattern_Det%i_Side%i", det, side), Form("Implant Hit Pattern - Det %i Side %i", det, side), bb7_config->NStrips(), 0, bb7_config->NStrips(), "Strip", kRed+1, kBlack);
            h1_decay_hitpattern[det][side] = MakeTH1(dir_decay_stats, "I", Form("h1_decay_hitpattern_Det%i_Side%i", det, side), Form("Decay Hit Pattern - Det %i Side %i", det, side), bb7_config->NStrips(), 0, bb7_config->NStrips(), "Strip", kRed+1, kBlack);
        }
    }

    // grab # of residuals 
    // /h1_residual_signals = new TH1*[4];
    h1_residual_signals[0] = MakeTH1(dir_residuals, "I", "h1_residual_signals_sc41l", "SC41L", 4000, 0, 20000);
    h1_residual_signals[1] = MakeTH1(dir_residuals, "I", "h1_residual_signals_sc41r", "SC41R", 4000, 0, 20000);
    h1_residual_signals[2] = MakeTH1(dir_residuals, "I", "h1_residual_signals_tmd", "Time Machine Delayed", 4000, 0, 20000);
    h1_residual_signals[3] = MakeTH1(dir_residuals, "I", "h1_residual_signals_tmu", "Time Machine Undelayed", 4000, 0, 20000);

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
        int detector = implant.Get_detector();
        int side = implant.Get_side();
        int strip = implant.Get_strip();
        h1_implant_hitpattern[detector][side]->Fill(strip-1);

        uint32_t raw_adc = implant.Get_raw_adc();
        h1_implant_RawE[detector][side][strip-1]->Fill(raw_adc);

        implant_counters[detector][side][strip-1]++;
    }

    for (auto const & decay : *decayArray)
    {
        bb7_wr = decay.Get_wr_t();
        int detector = decay.Get_detector();
        int side = decay.Get_side();
        int strip = decay.Get_strip();
        h1_decay_hitpattern[detector][side]->Fill(strip-1);

        uint32_t raw_adc = decay.Get_raw_adc();
        h1_decay_RawE[detector][side][strip-1]->Fill(raw_adc);

        decay_counters[detector][side][strip-1]++;
    }

    int64_t wr_dt = (bb7_wr - saved_bb7_wr) / 1e9; // conv to s
    if (wr_dt > 2) 
    {
        if (saved_bb7_wr != 0)
        {
            //std::cout << "hm we should get here" << std::endl;
            for (int det = 0; det < bb7_config->NDetectors(); det++)
            {
                for (int side = 0; side < bb7_config->NSides(); side++)
                {
                    for (int strip = 0; strip < bb7_config->NStrips(); strip++)
                    {
                        implant_rates[det][side][strip] = implant_counters[det][side][strip] / wr_dt;
                        h1_implant_rates[det][side][strip]->SetBinContent(rate_running_count, implant_rates[det][side][strip]);
                        decay_rates[det][side][strip] = decay_counters[det][side][strip] / wr_dt;
                        h1_decay_rates[det][side][strip]->SetBinContent(rate_running_count, decay_rates[det][side][strip]);
                    }
                }
            }
        }
        
        saved_bb7_wr = bb7_wr;
        rate_running_count++;
        for (int det = 0; det < bb7_config->NDetectors(); det++)
        {
            for (int side = 0; side < bb7_config->NSides(); side++) 
            {
                for (int strip = 0; strip < bb7_config->NStrips(); strip++)
                {   
                    implant_counters[det][side][strip] = 0;
                    decay_counters[det][side][strip] = 0;
                }
            }
        }
        if (rate_running_count == 1800) rate_running_count = 0;
    }

    for (auto const & residualItem : *residualArray)
    {
        uint32_t tmd = residualItem.Get_TM_Delayed();
        if (tmd > 0) h1_residual_signals[0]->Fill(tmd);
        uint32_t tmu = residualItem.Get_TM_Undelayed();
        if (tmu > 0) h1_residual_signals[1]->Fill(tmu);
        uint32_t sc41l = residualItem.Get_SC41L();
        if (sc41l > 0) h1_residual_signals[2]->Fill(sc41l);
        uint32_t sc41r = residualItem.Get_SC41R();
        if (sc41r > 0) h1_residual_signals[3]->Fill(sc41r);
    }
}

void BB7OnlineSpectra::FinishEvent()
{

}

void BB7OnlineSpectra::FinishTask()
{
    //c4LOG(info, Form("Plotted %i Events", fNEvents));
}
