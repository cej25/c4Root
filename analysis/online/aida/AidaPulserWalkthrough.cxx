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
 *                              N.J. Hubbard                                  *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "AnalysisTools.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaPulserWalkthrough.h"
#include "EventHeader.h"
#include "TAidaConfiguration.h"
#include "c4Logger.h"

// ROOT
#include <TDirectory.h>
#include <TError.h>
#include <TF1.h>
#include <TFile.h>
#include <TFitResult.h>
#include <THttpServer.h>
#include <TPaveText.h>
#include <TPolyMarker.h>
#include <TSpectrum.h>
#include <TTree.h>

// C++ STL
#include <chrono>
#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>

AidaPulserWalkthrough::AidaPulserWalkthrough() : AidaPulserWalkthrough("AidaPulserWalkthrough")
{
}

AidaPulserWalkthrough::AidaPulserWalkthrough(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , adcArray(nullptr)
    , flowArray(nullptr)
    , scalerArray(nullptr)
    , implantHitArray(nullptr)
    , header(nullptr)
    , fNEvents(0)
{
    // Default fit properties
    params.Sigma = 100;
    params.Threshold = 25;
    params.RemoveBG = false;
    params.Deconv = 1;
    params.Markov = true;
    params.Average = 5;
}

AidaPulserWalkthrough::~AidaPulserWalkthrough()
{
    c4LOG(info, "Destroyed AidaPulserWalkthrough properly.");

}

void AidaPulserWalkthrough::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaPulserWalkthrough::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // Raw data
    adcArray = mgr->InitObjectAs<decltype(adcArray)>("AidaAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaAdcData not found!");
    flowArray = mgr->InitObjectAs<decltype(flowArray)>("AidaFlowData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaFlowData not found!");
    scalerArray = mgr->InitObjectAs<decltype(scalerArray)>("AidaScalerData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaScalerData not found!");

    // Calibrated data
    implantCalArray = mgr->InitObjectAs<decltype(implantCalArray)>("AidaImplantCalAdcData");
    c4LOG_IF(fatal, !implantCalArray, "Branch AidaImplantCalAdcData not found!");
    decayCalArray = mgr->InitObjectAs<decltype(decayCalArray)>("AidaDecayCalAdcData");
    c4LOG_IF(fatal, !decayCalArray, "Branch AidaDecayCalAdcData not found!");

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");

    // Aida configuration
    conf = TAidaConfiguration::GetInstance();

    TDirectory* old = gDirectory;
    histos = new TFile("aida_offsets.root", "RECREATE");
    histos->cd();

    h_aida_adc.resize(conf->FEEs() * 64);
    for (int i = 0; i < conf->FEEs(); i++)
    {
        for(int j = 0; j < 64; j++)
        {
            int idx = (i * 64) + j;
            std::stringstream name;
            name << "h_aida_adc_" << (i + 1) << "_" << j;
            h_aida_adc[idx] = new TH1F(name.str().c_str(), name.str().c_str(), 65536, -32768, 32768);
            histos->Add(h_aida_adc[idx]);
        }
    }

    old->cd();

    return kSUCCESS;
}

void AidaPulserWalkthrough::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (auto const& entry : *adcArray)
    {
        int fee = entry.Fee();
        bool implant = entry.Range();
        int channel = entry.Channel();
        uint16_t value = entry.Value();

        if (!implant)
        {
            int idx = ((fee - 1) * 64) + channel;
            h_aida_adc[idx]->Fill(value - 32768);
        }
    }

    fNEvents += 1;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void AidaPulserWalkthrough::FinishEvent()
{
}

void AidaPulserWalkthrough::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warn, "No events found, not saving histograms!");
        return;
    }
    if (fNEvents > 0)
    {
        c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    }
    histos->Write();
}

void AidaPulserWalkthrough::FindOffsets()
{
    auto restore = gErrorIgnoreLevel;
    gErrorIgnoreLevel = kError;
    c4LOG(info, "Beginning pulser offset calibation");
    std::ofstream calf, logf;
    calf.open("AIDA_offsets.txt");
    logf.open("AIDA_offsets_log.log");

    if (!calf || !logf)
    {
        c4LOG(error, "Could not open output files :(");
        return;
    }

    calf << "FEE\tChannel\t   Offset\tPeaks\t        R2\tComment" << std::endl;
    std::unique_ptr<TCanvas> c1(new TCanvas("c1"));
    c1->Divide(2, 1);
    c1->Draw();
    for (int FEE = 1; FEE <= conf->FEEs(); FEE++)
    {
        int good = 0;
        bool NN = false;
        if (conf->FEE(FEE - 1).Side == DSSDSide::Ohmic)
            NN = true;
        for (int ch = 0; ch < 64; ch++)
        {
            logf << "Analysing Channel FEE#" << FEE << " Ch#" << ch << std::endl;
            int idx = ((FEE - 1) * 64) + ch;
            TH1& h = *h_aida_adc[idx];
            int max = h.GetMaximumBin();
            logf << "Peak maximum is " << max << std::endl;
            int start = -32768;
            int end = 32768;
            while (max >= 0 && max <= h.GetNbinsX()) {
                double c = h.GetBinContent(max);
                if (c < 5 && start == -32768 ) {
                    start = max;
                }
                if (c > 1) {
                    end = max;
                }
                if (NN) {
                    max += 1;
                }
                else {
                    max -= 1;
                }
            }
            if (!NN) {
                int tmp = start;
                start = end;
                end = tmp;
            }
            c1->cd(1);
            logf << "Found histo range: " << start << " - " << end << std::endl;
            h.GetXaxis()->SetRange(start, end);
            h.Draw();

            if (start > end)
                continue;

            int nbins = end - start;
            std::vector<double> source(nbins);
            std::vector<double> dest(nbins);

            for (int i = 0; i < nbins; i++) {
                source[i] = h.GetBinContent(i + start);
            }

            TSpectrum s;
            int nfound = s.SearchHighRes(
                    source.data(), dest.data(), nbins,
                    params.Sigma, params.Threshold, params.RemoveBG,
                    params.Deconv, params.Markov, params.Average);
            double* xpeaks = s.GetPositionX();
            double fx[100], fy[100];
            for (int i = 0; i < nfound; i++) {
                double a = xpeaks[i];
                int bin = start + int(a + 0.5);
                fx[i] = h.GetBinCenter(bin);
                fy[i] = h.GetBinContent(bin);
            }

            c1->cd(1);
            TPolyMarker* pm = new TPolyMarker(nfound, fx, fy);
            h.GetListOfFunctions()->Add(pm);
            pm->SetMarkerStyle(23);
            pm->SetMarkerColor(kRed);
            pm->SetMarkerSize(1.3);

            h.Draw();

            TH1D d("d", "", nbins, start, end);
            for (int i = 0; i < nbins; i++){
                d.SetBinContent(1 + i, dest[i]);
            }
            d.SetLineColor(kRed);
            d.Draw("SAME");

            std::vector<std::pair<double, double>> peaks(nfound);

            logf << "Found " << nfound << " peaks" << std::endl;
            for (int i = 0; i < nfound; i++) {
                peaks[i] = std::make_pair(fx[i], fy[i]);
            }
            std::sort(peaks.begin(), peaks.end());
            for (auto& peak : peaks)
            {
                logf << "X = " << peak.first << ", Y = " << peak.second << std::endl;
            }

            c1->cd(2);
            double fitX[100], fitY[100];
            if (nfound > 10) nfound = 10;
            double avg_space = 0;
            for (int i = 1; i < nfound; i++)
            {
                avg_space += peaks[i].first - peaks[i - 1].first;
            }
            double avg_space1 = avg_space / (nfound - 1);
            avg_space = 0;
            int avg_space_n = 0;
            for (int i = 1; i < nfound; i++)
            {
                double diff = peaks[i].first - peaks[i - 1].first;
                if ((diff - avg_space1) / avg_space1 < 0.3)
                {
                    avg_space += diff;
                    avg_space_n++;
                }
            }
            avg_space = std::abs(avg_space / (avg_space_n));
            logf << "--" << std::endl;
            for (int i = 0; i < nfound; i++)
            {
                fitX[i] = 10 - i;
                if (NN)
                {
                    fitY[i] = peaks[nfound -1 - i].first;
                }
                else
                {
                    fitY[i] = peaks[i].first;
                }
                if (nfound != 10)
                {
                    double Volts = round(std::abs(fitY[i] / avg_space));
                    fitX[i] = Volts;
                }
                logf << "Volts = " << fitX[i] << ", Peak = " << fitY[i] << std::endl;
            }

            TGraph tg(nfound, fitX, fitY);
            tg.SetTitle("aida_adc_" + TString::Itoa(FEE, 10) + "_" + TString::Itoa(ch, 10) + "_fit");
            tg.GetXaxis()->SetTitle("Pulser Voltage (V)");
            tg.GetYaxis()->SetTitle("ADC Value (ch)");
            auto fitresult = tg.Fit("pol1", "SQ");
            if (fitresult != 0)
            {
                calf << "#" << FEE << "\t" << (ch + 1) << "\t" << " FIT FAILED" << std::endl;
                continue;
            }
            fitresult->ROOT::Fit::FitResult::Print(logf, false);
            tg.Draw("AL*");

            double offset = fitresult->Parameter(0);
            double gain = fitresult->Parameter(1);
            double mean = 0;
            for (int i = 0; i < nfound; i++)
            {
                mean += fitY[i];
            }
            mean /= nfound;
            double ssres = 0, sstot = 0;
            for (int i = 0; i < nfound; i++)
            {
                double model = gain*fitX[i] + offset;
                double truth = fitY[i];
                ssres += std::pow(truth - model, 2);
                sstot += std::pow(truth - mean, 2);
            }
            double inl = 1 - (ssres / sstot);
            if (!NN) offset *= -1;

            TPaveText t(0.15, 0.65, 0.45, 0.85, "NDC");
            if (!NN)
            {
                t.SetX1(0.55);
                t.SetX2(0.85);
            }
            t.AddText("Offset: " + TString::Itoa(offset, 10));
            t.AddText("R^{2}: " + TString::Format("%.02f", inl));
            t.Draw();

            std::string comment;
            if (inl < 0.999) {
                comment = "Bad Fit ";
            }
            else if (inl == 1.00) {
                comment = "Perfect Fit? ";
            }
            if (nfound < 8) {
                comment += "Few Peaks ";
            }
            if (std::abs(offset) > 1000) {
                comment += "High Offset ";
            }
            if (!comment.length()) {
                good++;
            }
            calf << FEE << "\t" << (ch + 1) << "\t"
                << std::setw(10) << offset << "\t"
                << nfound << "\t"
                << std::setw(10) << inl << "\t"
                << comment << std::endl;

            c1->cd(0);
            c1->Update();
            c1->SaveAs("aida-offsets/h_aida_adc_" + TString::Itoa(FEE, 10)
                    + "_" + TString::Itoa(ch, 10) + "_peaks.png");
        }
        logf << "For FEE#" << FEE << " " << good << "/64 channels calibrated without comment" << std::endl;
        c4LOG(info, "For FEE#" << FEE << " " << good << "/64 channels calibrated without comment");
    }
    c4LOG(info, "Pulser calibration complete, please check the log for channels to manually fix");
    gErrorIgnoreLevel = restore;
}

ClassImp(AidaPulserWalkthrough)
