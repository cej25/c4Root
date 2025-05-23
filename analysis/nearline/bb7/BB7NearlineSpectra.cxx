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
#include "FairRuntimeDb.h"

// c4
#include "BB7NearlineSpectra.h"
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


BB7NearlineSpectra::BB7NearlineSpectra()
    :   FairTask()
    ,   implantArray(nullptr)
    ,   decayArray(nullptr)
    ,   header(nullptr)
{
    bb7_config = TBB7VmeConfiguration::GetInstance();
}

BB7NearlineSpectra::~BB7NearlineSpectra()
{

}

InitStatus BB7NearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    implantArray = mgr->InitObjectAs<decltype(implantArray)>("BB7ImplantData");
    c4LOG_IF(fatal, !implantArray, "Branch BB7ImplantData not found!");
    decayArray = mgr->InitObjectAs<decltype(decayArray)>("BB7DecayData");
    c4LOG_IF(fatal, !decayArray, "Branch BB7DecayData not found!");

    // set up config later

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bb7 = gDirectory->mkdir("BB7");
    gDirectory->cd("BB7");

    dir_implants = dir_bb7->mkdir("Implants");
    dir_implant_raw_e = dir_implants->mkdir("Raw Energy");
    dir_implant_stats = dir_implants->mkdir("Stats");
    dir_implant_rates = dir_implants->mkdir("Rate Monitors");
    dir_decays = dir_bb7->mkdir("Decays");
    dir_decay_raw_e = dir_decays->mkdir("Raw Energy");
    dir_decay_stats = dir_decays->mkdir("Stats");
    dir_decay_rates = dir_decays->mkdir("Rate Monitors");

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
    

    // base on config later - add detector loop later also
    for (int det = 0; det < bb7_config->NDetectors(); det++)
    {
        for (int side = 0; side < bb7_config->NSides(); side++)
        {   
            for (int strip = 0; strip < bb7_config->NStrips(); strip++)
            {
                h1_implant_RawE[det][side][strip] = MakeTH1(dir_implant_raw_e, "D", Form("h1_implant_RawE_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Implant Raw Energy - Det %i Side %i, Strip %i", det, side, strip+1), 10000, 0, 10000, "Raw ADC [a.u.]", kOrange+7, kBlue+2);
                h1_decay_RawE[det][side][strip] = MakeTH1(dir_decay_raw_e, "D", Form("h1_decay_RawE_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Decay Raw Energy - Det %i Side %i, Strip %i", det, side, strip+1), 10000, 0, 10000, "Raw ADC [a.u.]", kSpring, kBlue+2);
                
                // these rates will need to change once we sort out clustering etc
                // i don't think they should be per side/strip, they should be per dssd
                // but for now, lets look at per side/strip and see what it shows
                h1_implant_rates[det][side][strip] = MakeTH1(dir_implant_rates, "I", Form("h1_implant_rates_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Implant Rate - Det %i Side %i Strip %i", det, side, strip+1), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
                h1_decay_rates[det][side][strip] = MakeTH1(dir_decay_rates, "I", Form("h1_decay_rates_Det%i_Side%i_Strip%i", det, side, strip+1), Form("Decay Rate - Det %i Side %i Strip %i", det, side, strip+1), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);
            }

            h1_implant_hitpattern[det][side] = MakeTH1(dir_implant_stats, "I", Form("h1_implant_hitpattern_Det%i_Side%i", det, side), Form("Implant Hit Pattern - Det %i Side %i", det, side), bb7_config->NStrips(), 0, bb7_config->NStrips(), "Strip", kRed+1, kBlack);
            h1_decay_hitpattern[det][side] = MakeTH1(dir_decay_stats, "I", Form("h1_decay_hitpattern_Det%i_Side%i", det, side), Form("Decay Hit Pattern - Det %i Side %i", det, side), bb7_config->NStrips(), 0, bb7_config->NStrips(), "Strip", kRed+1, kBlack);
        }
    }

    dir_bb7->cd();

    return kSUCCESS;
}

void BB7NearlineSpectra::Exec(Option_t* option)
{
    int64_t bb7_wr = 0;
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
}


void BB7NearlineSpectra::FinishEvent()
{

}

void BB7NearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bb7->Write();
    gDirectory = tmp;
    c4LOG(info, "Written BB7 analysis histograms to file.");
}
