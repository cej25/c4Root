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
#include "BeamMonitorOnlineSpectra.h"
#include "EventHeader.h"
#include "BeamMonitorData.h"
#include "c4Logger.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <cmath>
#include <chrono>

#define DEBUG_MODE 0

BeamMonitorOnlineSpectra::BeamMonitorOnlineSpectra() : BeamMonitorOnlineSpectra("BeamMonitorOnlineSpectra")
{
}

BeamMonitorOnlineSpectra::BeamMonitorOnlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   s2HitsBM(nullptr)
    ,   s4HitsBM(nullptr)
{
}

BeamMonitorOnlineSpectra::~BeamMonitorOnlineSpectra()
{
    c4LOG(info, "");
    delete s2HitsBM;
    delete s4HitsBM;
}

InitStatus BeamMonitorOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    s2HitsBM = mgr->InitObjectAs<decltype(s2HitsBM)>("BeamMonitorS2Data");
    c4LOG_IF(fatal, !s2HitsBM, "Branch BeamMonitorS2Data not found!");

    s4HitsBM = mgr->InitObjectAs<decltype(s4HitsBM)>("BeamMonitorS4Data");
    c4LOG_IF(fatal, !s4HitsBM, "Branch BeamMonitorS4Data not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_beammonitor = new TDirectory("Beam Monitor", "Beam Monitor", "", 0);
    //mgr->Register("Beam Monitor", "Beam Monitor Directory", dir_beammonitor, false); // allow other tasks to access
    histograms->Add(dir_beammonitor);

    dir_beammonitor->cd();

    hG_BM_s4h_norm_tdiff = new TH1D("hG_BM_s4h_norm_tdiff", "S4 Normalised Hit Time Difference [100ns]", 100000, 0, 100000);
    hG_BM_s4h_tdiff = new TH1D("hG_BM_s4h_tdiff", "S4 Hit Time Difference [100ns]", 100000, 0, 100000);
    hG_BM_s4h_t1 = new TH1D("hG_BM_s4h_t1", "S4 Hit Time [ms]: bins are 100us wide", 100000, 0, 100000);
    hG_BM_s4h_n = new TH1D("hG_BM_s4h_n", "S4 Hits per Spill", 600, 0, 6000);
    hG_BM_s4h_poisson = new TH1D("hG_BM_s4h_poisson", "S4 Poisson", 100000, 0, 100000);
    hG_BM_s4h_c = new TH1D("hG_BM_s4h_c", "S4 Cumulative Hit Times [100ns]", 100000, 0, 100000);
    hG_BM_s4h_dc = new TH1D("hG_BM_s4h_dc", "S4 Deviation of Cumulative Hit Times [100ns]", 100000, 0, 100000);
    hG_BM_s4h_cp = new TH1D("hG_BM_s4h_cp", "S4 Cumulative Poissson [100ns]", 100000, 0, 100000);

    hG_BM_s4gr_dt_avg = new TGraph(1);
    hG_BM_s4gr_dt_avg->SetName("hG_BM_s4gr_dt_avg");
    hG_BM_s4gr_dt_avg->SetTitle("S4 Average Time Difference");
    hG_BM_s4gr_dt_avg->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s4gr_dt_avg->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s4gr_dt_avg->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s4gr_dt_avg->GetYaxis()->SetTitle("t [us]");
    hG_BM_s4gr_dt_avg->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s4gr_dt_avg->SetMarkerColor(kBlack);
    hG_BM_s4gr_dt_avg->SetMarkerStyle(20);
    hG_BM_s4gr_dt_avg->SetLineColor(kBlue);
    hG_BM_s4gr_dt_avg->SetLineWidth(2);
    hG_BM_s4gr_dt_avg->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s4gr_dt_avg);

    hG_BM_s4gr_qf = new TGraph(1);
    hG_BM_s4gr_qf->SetName("hG_BM_s4gr_qf");
    hG_BM_s4gr_qf->SetTitle("S4 Quality Factor");
    hG_BM_s4gr_qf->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s4gr_qf->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s4gr_qf->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s4gr_qf->GetYaxis()->SetTitle("QF");
    hG_BM_s4gr_qf->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s4gr_qf->SetMarkerColor(kBlack);
    hG_BM_s4gr_qf->SetMarkerStyle(20);
    hG_BM_s4gr_qf->SetLineColor(kBlue);
    hG_BM_s4gr_qf->SetLineWidth(2);
    hG_BM_s4gr_qf->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s4gr_qf);

    hG_BM_s4gr_dcmin = new TGraph(1);
    hG_BM_s4gr_dcmin->SetName("hG_BM_s4gr_dcmin");
    hG_BM_s4gr_dcmin->SetTitle("S4 Largest Deviation From Ideal");
    hG_BM_s4gr_dcmin->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s4gr_dcmin->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s4gr_dcmin->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s4gr_dcmin->GetYaxis()->SetTitle("QF2");
    hG_BM_s4gr_dcmin->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s4gr_dcmin->SetMarkerColor(kBlack);
    hG_BM_s4gr_dcmin->SetMarkerStyle(20);
    hG_BM_s4gr_dcmin->SetLineColor(kBlue);
    hG_BM_s4gr_dcmin->SetLineWidth(2);
    hG_BM_s4gr_dcmin->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s4gr_dcmin);

    hG_BM_s4gr_dctime = new TGraph(1);
    hG_BM_s4gr_dctime->SetName("hG_BM_s4gr_dctime");
    hG_BM_s4gr_dctime->SetTitle("S4 Time difference with the largest deviation [us]");
    hG_BM_s4gr_dctime->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s4gr_dctime->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s4gr_dctime->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s4gr_dctime->GetYaxis()->SetTitle("QF3 time [us]");
    hG_BM_s4gr_dctime->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s4gr_dctime->SetMarkerColor(kBlack);
    hG_BM_s4gr_dctime->SetMarkerStyle(20);
    hG_BM_s4gr_dctime->SetLineColor(kBlue);
    hG_BM_s4gr_dctime->SetLineWidth(2);
    hG_BM_s4gr_dctime->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s4gr_dctime);

    hG_BM_S4_Tmean = new TH1D("hG_BM_S4_Tmean", "S4 Average time difference", 100000, 0, 100000);

    hG_BM_s2h_norm_tdiff = new TH1D("hG_BM_s2h_norm_tdiff", "S2 Normalised Hit Time Difference [100ns]", 100000, 0, 100000);
    hG_BM_s2h_tdiff = new TH1D("hG_BM_s2h_tdiff", "S2 Hit Time Difference [100ns]", 100000, 0, 100000);
    hG_BM_s2h_t1 = new TH1D("hG_BM_s2h_t1", "S2 Hit Time [ms]: bins are 100us wide", 100000l, 0, 100000);
    hG_BM_s2h_n = new TH1D("hG_BM_s2h_n", "S2 Hits per Spill", 600, 0, 6000);
    hG_BM_s2h_poisson = new TH1D("hG_BM_s2h_poisson", "S2 Poisson", 100000, 0, 100000);
    hG_BM_s2h_c = new TH1D("hG_BM_s2h_c", "S2 Cumulative Hit Times [100ns]", 100000, 0, 100000);
    hG_BM_s2h_dc = new TH1D("hG_BM_s2h_dc", "S2 Deviation of Cumulative Hit Times [100ns]", 100000, 0, 100000);
    hG_BM_s2h_cp = new TH1D("hG_BM_s2h_cp", "S2 Cumulative Poisson [100ns]", 100000, 0, 100000);

    hG_BM_s2gr_dt_avg = new TGraph(1);
    hG_BM_s2gr_dt_avg->SetName("hG_BM_s2gr_dt_avg");
    hG_BM_s2gr_dt_avg->SetTitle("S2 Average Time Difference");
    hG_BM_s2gr_dt_avg->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s2gr_dt_avg->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s2gr_dt_avg->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s2gr_dt_avg->GetYaxis()->SetTitle("t [us]");
    hG_BM_s2gr_dt_avg->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s2gr_dt_avg->SetMarkerColor(kBlack);
    hG_BM_s2gr_dt_avg->SetMarkerStyle(20);
    hG_BM_s2gr_dt_avg->SetLineColor(kRed);
    hG_BM_s2gr_dt_avg->SetLineWidth(2);
    hG_BM_s2gr_dt_avg->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s2gr_dt_avg);

    hG_BM_s2gr_qf = new TGraph(1);
    hG_BM_s2gr_qf->SetName("hG_BM_s2gr_qf");
    hG_BM_s2gr_qf->SetTitle("S2 Quality Factor");
    hG_BM_s2gr_qf->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s2gr_qf->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s2gr_qf->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s2gr_qf->GetYaxis()->SetTitle("QF");
    hG_BM_s2gr_qf->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s2gr_qf->SetMarkerColor(kBlack);
    hG_BM_s2gr_qf->SetMarkerStyle(20);
    hG_BM_s2gr_qf->SetLineColor(kRed);
    hG_BM_s2gr_qf->SetLineWidth(2);
    hG_BM_s2gr_qf->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s2gr_qf);

    hG_BM_s2gr_dcmin = new TGraph(1);
    hG_BM_s2gr_dcmin->SetName("hG_BM_s2gr_dcmin");
    hG_BM_s2gr_dcmin->SetTitle("S2 Largest Deviation From Ideal");
    hG_BM_s2gr_dcmin->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s2gr_dcmin->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s2gr_dcmin->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s2gr_dcmin->GetYaxis()->SetTitle("QF2");
    hG_BM_s2gr_dcmin->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s2gr_dcmin->SetMarkerColor(kBlack);
    hG_BM_s2gr_dcmin->SetMarkerStyle(20);
    hG_BM_s2gr_dcmin->SetLineColor(kRed);
    hG_BM_s2gr_dcmin->SetLineWidth(2);
    hG_BM_s2gr_dcmin->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s2gr_dcmin);

    hG_BM_s2gr_dctime = new TGraph(1);
    hG_BM_s2gr_dctime->SetName("hG_BM_s2gr_dctime");
    hG_BM_s2gr_dctime->SetTitle("S2 Time difference with the largest deviation [us]");
    hG_BM_s2gr_dctime->GetXaxis()->SetTimeDisplay(1);
    hG_BM_s2gr_dctime->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
    hG_BM_s2gr_dctime->GetXaxis()->SetTimeOffset(0, "local");
    hG_BM_s2gr_dctime->GetYaxis()->SetTitle("QF3 time [us]");
    hG_BM_s2gr_dctime->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
    hG_BM_s2gr_dctime->SetMarkerColor(kBlack);
    hG_BM_s2gr_dctime->SetMarkerStyle(20);
    hG_BM_s2gr_dctime->SetLineColor(kRed);
    hG_BM_s2gr_dctime->SetLineWidth(2);
    hG_BM_s2gr_dctime->GetXaxis()->SetNdivisions(-4);
    dir_beammonitor->Append(hG_BM_s2gr_dctime);

    hG_BM_S2_Tmean = new TH1D("hG_BM_S2_Tmean", "S2 Average time difference", 100000, 0, 100000);

    // add S2 and S4 equivalent TGraphs to same canvas
    c_quality_factor = new TCanvas("Quality Factors", "Quality Factors");
    c_quality_factor->Divide(2, 1);
    c_quality_factor->cd(1);
    hG_BM_s2gr_qf->Draw();
    c_quality_factor->cd(2);
    hG_BM_s4gr_qf->Draw();
    dir_beammonitor->Append(c_quality_factor);
    


    run->GetHttpServer()->RegisterCommand("Reset_BM_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void BeamMonitorOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Not currently functional.");
}

void BeamMonitorOnlineSpectra::Exec(Option_t* option)
{   
    std::vector<uint32_t> BM_S2_Hits = {};
    std::vector<uint32_t> BM_S4_Hits = {};
    for (auto const & s2Item : *s2HitsBM)
    {
        BM_S2_Hits.emplace_back(s2Item.GetTimeDelta());
    }
    
    for (auto const & s4Item : *s4HitsBM)
    {
        BM_S4_Hits.emplace_back(s4Item.GetTimeDelta());
    }
    


    // S2
    //Int_t BM_Hits; // actually we do this slightly differently
    Double_t BM_CountRate;
    Double_t BM_CR_timesum;
    Int_t BM_CR_relevanthits;
    Double_t BM_CR_Tlimit = pow(10,6); // should be much lower than time between spills, units [100ns]

    Double_t BM_Tdiff_integral;
    Double_t BM_dc_MinValue;
    Int_t BM_dc_MinBin;

    Double_t BM_QF;
    Double_t BM_Tmean;
    Float_t BM_S2_Tdiffs[BM_S2_MaxTdiffs] = {0};
    Float_t BM_S4_Tdiffs[BM_S4_MaxTdiffs] = {0};


    // S2
    for (Int_t i = 0; i < BM_S2_Hits.size(); i++)
    {
        BM_S2_Tdiffs[BM_S2_count] = BM_S2_Hits.at(i) / 10; // [10ns] -> [100ns]
        hG_BM_s2h_tdiff->Fill(BM_S2_Tdiffs[BM_S2_count]);
        BM_S2_count++;

        if (BM_S2_count > BM_S2_MaxTdiffs)
        {
            BM_S2_count = BM_S2_count % BM_S2_MaxTdiffs;
        }

        if (BM_S2_count % BM_S2_DoAnalysisEvery == 0)
        {
            BM_CR_timesum = 0;
            BM_CR_relevanthits = 0;

            for (Int_t k = 0; k < BM_S2_MaxTdiffs; k++)
            {
                if ((Double_t) BM_S2_SumTdiff < (Double_t) BM_NTimeMax * pow(10,5))
                {
                    BM_S2_SumTdiff += BM_S2_Tdiffs[(BM_S2_count + k) % BM_S2_MaxTdiffs];
                    hG_BM_s2h_t1->Fill((Double_t) BM_S2_SumTdiff * pow(10,-5));
                }
                else
                {
                    hG_BM_s2h_t1->Reset("ICESM");
                    BM_S2_SumTdiff = 0;
                }

                if (BM_S2_Tdiffs[k] < BM_CR_Tlimit)
                {
                    BM_CR_timesum += BM_S2_Tdiffs[k];
                    BM_CR_relevanthits++;
                }
            }

            BM_CountRate = (Double_t) BM_CR_relevanthits / BM_CR_timesum;

            BM_Tdiff_integral = hG_BM_s2h_tdiff->Integral(0, BM_MaxTimeDiff);

            for (Int_t j = 0; j < BM_S2_MaxTdiffs; j++)
            {
                hG_BM_s2h_norm_tdiff->SetBinContent(j, hG_BM_s2h_tdiff->GetBinContent(j) / BM_Tdiff_integral);
                hG_BM_s2h_poisson->SetBinContent(j, exp(-BM_CountRate * ((Double_t) j)) - exp(-BM_CountRate * ((Double_t) j+1)));

                if (j == 0)
                {
                    hG_BM_s2h_c->SetBinContent(j, 0);
                    hG_BM_s2h_cp->SetBinContent(j, 0);
                }
                else
                {
                    hG_BM_s2h_c->SetBinContent(j, hG_BM_s2h_c->GetBinContent(j-1) + hG_BM_s2h_norm_tdiff->GetBinContent(j));
                    hG_BM_s2h_cp->SetBinContent(j, hG_BM_s2h_cp->GetBinContent(j-1) + hG_BM_s2h_poisson->GetBinContent(j));
                }
                hG_BM_s2h_dc->SetBinContent(j, hG_BM_s2h_cp->GetBinContent(j) - hG_BM_s2h_c->GetBinContent(j));
            }

            BM_dc_MinBin = hG_BM_s2h_dc->GetMinimumBin();
            BM_dc_MinValue = hG_BM_s2h_dc->GetBinContent(BM_dc_MinBin);
            BM_Tmean = hG_BM_s2h_norm_tdiff->GetMean();

            hG_BM_S2_Tmean->Fill(BM_Tmean);

            // QF
            BM_QF = 100.0 * (1.0 - (hG_BM_s2h_norm_tdiff->Integral(0, (Int_t) BM_Tmean) / hG_BM_s2h_poisson->Integral(0, (Int_t) BM_Tmean)));
            
            // we could use chrono to get ns resolution? otherwise s
            time_t rawtime;
            time(&rawtime);

            if (std::isnan(BM_QF)) continue; // skip divisions by zero

            // add integral between two time difference ranges...


            hG_BM_s2gr_qf->SetPoint(BM_S2_QFcount, rawtime, BM_QF);
            hG_BM_s2gr_dcmin->SetPoint(BM_S2_QFcount, rawtime, BM_dc_MinValue);
            hG_BM_s2gr_dctime->SetPoint(BM_S2_QFcount, rawtime, BM_dc_MinBin / 10);
            hG_BM_s2gr_dt_avg->SetPoint(BM_S2_QFcount, rawtime, (Double_t) BM_Tmean / 10.);
            BM_S2_QFcount++;                    
        }
    }

    // S4

    for (int i = 0; i < BM_S4_Hits.size(); i++)
    {
        BM_S4_Tdiffs[BM_S4_count] = BM_S4_Hits[i] / 10;
        hG_BM_s4h_tdiff->Fill(BM_S4_Tdiffs[BM_S4_count]);
        BM_S4_count++;

        if (BM_S4_count > BM_S4_MaxTdiffs)
        {
            BM_S4_count = BM_S4_count % BM_S4_MaxTdiffs;
        }

        if (BM_S4_count % BM_S4_DoAnalysisEvery == 0)
        {
            BM_CR_timesum = 0;
            BM_CR_relevanthits = 0;


            for (Int_t k = 0; k < BM_S4_MaxTdiffs; k++)
            {
                if ((Double_t) BM_S4_SumTdiff < (Double_t) BM_NTimeMax * pow(10, 5))
                {
                    BM_S4_SumTdiff += BM_S4_Tdiffs[(BM_S4_count + k) % BM_S4_MaxTdiffs];
                    hG_BM_s4h_t1->Fill((Double_t) BM_S4_SumTdiff * pow(10, -5));
                }
                else
                {
                    hG_BM_s4h_t1->Reset("ICESM");
                    BM_S4_SumTdiff = 0;
                }

                if (BM_S4_Tdiffs[k] < BM_CR_Tlimit)
                {
                    BM_CR_timesum += BM_S4_Tdiffs[k];
                    BM_CR_relevanthits++;
                }
            }


            BM_CountRate = (Double_t) BM_CR_relevanthits / BM_CR_timesum;

            BM_Tdiff_integral = hG_BM_s4h_tdiff->Integral(0, BM_MaxTimeDiff);

            for (Int_t j = 0; j < BM_S4_MaxTdiffs; j++)
            {
                hG_BM_s4h_norm_tdiff->SetBinContent(j, hG_BM_s4h_tdiff->GetBinContent(j) / BM_Tdiff_integral);
                hG_BM_s4h_poisson->SetBinContent(j, exp(-BM_CountRate * ((Double_t) j)) - exp(-BM_CountRate * ((Double_t) j+1)));

                // Cumulative histograms
                if (j == 0)
                {
                    hG_BM_s4h_c->SetBinContent(j, 0);
                    hG_BM_s4h_cp->SetBinContent(j, 0);
                }
                else
                {
                    hG_BM_s4h_c->SetBinContent(j, hG_BM_s4h_c->GetBinContent(j-1) + hG_BM_s4h_norm_tdiff->GetBinContent(j));
                    hG_BM_s4h_cp->SetBinContent(j, hG_BM_s4h_cp->GetBinContent(j-1) + hG_BM_s4h_poisson->GetBinContent(j));
                }
                hG_BM_s4h_dc->SetBinContent(j, hG_BM_s4h_cp->GetBinContent(j) - hG_BM_s4h_c->GetBinContent(j));
            }

            BM_dc_MinBin = hG_BM_s4h_dc->GetMinimumBin();
            BM_dc_MinValue = hG_BM_s4h_dc->GetBinContent(BM_dc_MinBin);
            BM_Tmean = hG_BM_s4h_norm_tdiff->GetMean();

            hG_BM_S4_Tmean->Fill(BM_Tmean);

            BM_QF = 100.0 * (1.0 - (hG_BM_s4h_norm_tdiff->Integral(0, (Int_t) BM_Tmean) / hG_BM_s4h_poisson->Integral(0, (Int_t) BM_Tmean)));

            // get local time
            time_t rawtime;
            time(&rawtime);

            if (std::isnan(BM_QF)) continue; // skip divisions by zero

            hG_BM_s4gr_qf->TGraph::SetPoint(BM_S4_QFcount, rawtime, BM_QF);
            hG_BM_s4gr_dcmin->TGraph::SetPoint(BM_S4_QFcount, rawtime, BM_dc_MinValue);
            hG_BM_s4gr_dctime->TGraph::SetPoint(BM_S4_QFcount, rawtime, BM_dc_MinBin / 10);
            hG_BM_s4gr_dt_avg->TGraph::SetPoint(BM_S4_QFcount, rawtime, (Double_t) BM_Tmean / 10.);
            BM_S4_QFcount++;

        } // analysis every N
    } // S4 Hits


    fNEvents += 1;
}

void BeamMonitorOnlineSpectra::FinishEvent()
{
    // clear?
}

void BeamMonitorOnlineSpectra::FinishTask()
{

}

ClassImp(BeamMonitorOnlineSpectra)
