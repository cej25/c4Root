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
 *                       C.E.Jones, J.E.L. Larsson                            *
 *                               17.12.24                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "DegasOnlineSpectra.h"
#include "EventHeader.h"
#include "DegasCalData.h"
#include "TDegasConfiguration.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include <sstream>

DegasOnlineSpectra::DegasOnlineSpectra() : DegasOnlineSpectra("DegasOnlineSpectra")
{
    degas_configuration = TDegasConfiguration::GetInstance();
}

DegasOnlineSpectra::DegasOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{
    degas_configuration = TDegasConfiguration::GetInstance();
}

DegasOnlineSpectra::~DegasOnlineSpectra()
{
    c4LOG(info, "");
    // fHitGe is borrowed from FairRootManager; it is not owned by this task.
}

void DegasOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus DegasOnlineSpectra::Init()
{
    const auto canvasName = [this](const char* name) {
        return fSpectraDirectory.IsNull() ? TString(name) : fSpectraDirectory + "_" + name;
    };

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    if (run && run->GetHttpServer()) run->GetHttpServer()->Register("", this);

    if (run && run->GetHttpServer())
        run->GetHttpServer()->RegisterCommand(fSpectraDirectory.IsNull() ? "Reset_Ge_Histos" : Form("Reset_%s", fSpectraDirectory.Data()), Form("/Objects/%s/->Reset_Histo()", GetName()));


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = dynamic_cast<TClonesArray*>(mgr->GetObject("DegasCalData"));
    if (!fHitGe || fHitGe->GetClass() != DegasCalData::Class())
    {
        c4LOG(error, "Expected DEGAS hit objects in the input branch");
        return kFATAL;
    }

    histograms = (TFolder*)mgr->GetObject("Histograms");


    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = degas_configuration->Mapping();

    for (auto it_mapping = gmap.begin(); it_mapping != gmap.end(); ++it_mapping)
    {
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(std::pair<int,int>(it_mapping->second.first,it_mapping->second.second));
    }

    number_of_detectors_to_plot = crystals_to_plot.size();

    TDirectory::TContext ctx(nullptr);

    dir_degas = new TDirectory(fSpectraDirectory.IsNull() ? "DEGAS" : fSpectraDirectory.Data(), "DEGAS", "", 0);
    if (fSpectraDirectory.IsNull()) mgr->Register("DEGAS", "DEGAS Directory", dir_degas, false);
    if (!histograms) return kFATAL;
    histograms->Add(dir_degas);

    dir_degas_energy = dir_degas->mkdir("Calibrated Energy Spectra");
    dir_degas_time = dir_degas->mkdir("Time Spectra");
    dir_degas_hitpattern = dir_degas->mkdir("Hit Pattern");
    dir_degas_multiplicity = dir_degas->mkdir("Multiplicity");
    dir_degas_sci41 = dir_degas->mkdir("SCI41");
    dir_degas_resolution = dir_degas->mkdir("Resolutions");
    dir_degas_rates = dir_degas->mkdir("Rate Monitors");

    detector_labels = new const char*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        detector_labels[ihist] = Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65));
    }


    // energy spectra:
    c_degas_energy  = new TCanvas(canvasName("c_degas_energy"),"Calibrated Degas spectra",650,350);
    c_degas_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_degas_energy = new TH1*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c_degas_energy->cd(ihist+1);
        h1_degas_energy[ihist] = MakeTH1(dir_degas_energy, "F", Form("h1_degas_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
        h1_degas_energy[ihist]->Draw();
    }
    c_degas_energy->cd(0);
    dir_degas_energy->Append(c_degas_energy);

    // time spectra:
    c_degas_time  = new TCanvas(canvasName("c_degas_time"),"Calibrated Degas spectra",650,350);
    c_degas_time->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_degas_time = new TH1*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c_degas_time->cd(ihist+1);
        h1_degas_time[ihist] = MakeTH1(dir_degas_time, "F", Form("h1_degas_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e16, "Time [ns]");
        h1_degas_time[ihist]->Draw();
    }
    c_degas_time->cd(0);

    c_degas_energy_vs_detidx = new TCanvas(canvasName("c_degas_energy_vs_detidx"),"Calibrated Degas spectra vs. detector index",650,350);
    h2_degas_energy_vs_detidx = MakeTH2(dir_degas_energy, "F", "h2_degas_energy_vs_detidx","Calibrated Degas spectra vs. detector index",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Energy [keV]", "Detector");
    h2_degas_energy_vs_detidx->Draw();
    c_degas_energy_vs_detidx->cd(0);
    dir_degas_energy->Append(c_degas_energy_vs_detidx);

    c_degas_energy_summed = new TCanvas(canvasName("c_degas_energy_summed"),"Calibrated Degas spectra summed all dets",650,350);
    h1_degas_energy_summed = MakeTH1(dir_degas_energy, "F", "h1_degas_energy_summed","Calibrated Degas spectra summed all dets",fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
    h1_degas_energy_summed->Draw();
    c_degas_energy_summed->cd(0);
    dir_degas_energy->Append(c_degas_energy_summed);

    // Spectra relating to SCI41:
    c_degas_energy_summed_vetosci41 = new TCanvas(canvasName("c_degas_energy_summed_vetosci41"),"Calibrated Degas spectra summed all dets veto sci41",650,350);
    h1_degas_energy_summed_vetosci41 = MakeTH1(dir_degas_sci41, "F", "h1_degas_energy_summed_vetosci41","Calibrated Degas spectra summed all dets veto sci 41",fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
    h1_degas_energy_summed_vetosci41->Draw();
    c_degas_energy_summed_vetosci41->cd(0);
    dir_degas_sci41->Append(c_degas_energy_summed_vetosci41);


    c_degas_energy_summed_vs_tsci41 = new TCanvas(canvasName("c_degas_energy_summed_vs_tsci41"),"Calibrated Degas spectra summed all energyies vs t(det) - t(sci41)",650,350);
    h2_degas_energy_summed_vs_tsci41 = MakeTH2(dir_degas_sci41, "F", "h2_degas_energy_summed_vs_tsci41","Calibrated Degas spectra summed all energyies vs t(det) - t(sci41)",1000,-500,5000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Time difference [ns]", "Energy [keV]");
    h2_degas_energy_summed_vs_tsci41->Draw();
    c_degas_energy_summed_vs_tsci41->cd(0);
    dir_degas_sci41->Append(c_degas_energy_summed_vs_tsci41);

    c_degas_energy_summed_vs_tsci41_cut = new TCanvas(canvasName("c_degas_energy_summed_vs_tsci41_cut"),"Calibrated Degas spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h1_degas_energy_summed_vs_tsci41_cut = MakeTH1(dir_degas_sci41, "F", "h1_degas_energy_summed_vs_tsci41_cut","Calibrated Degas spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
    h1_degas_energy_summed_vs_tsci41_cut->Draw();
    c_degas_energy_summed_vs_tsci41_cut->cd(0);
    dir_degas_sci41->Append(c_degas_energy_summed_vs_tsci41_cut);

    c_degas_energy_energy_vetosci41 = new TCanvas(canvasName("c_degas_energy_energy_vetosci41"),"Calibrated Degas spectra summed all energies, t(det) - t(sci41) > 200 ns",650,350);
    h2_degas_energy_energy_vetosci41 = MakeTH2(dir_degas_sci41, "F", "h2_degas_energy_energy_vetosci41","Calibrated Degas spectra summed all energies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", "Energy [keV]");
    h2_degas_energy_energy_vetosci41->Draw();
    c_degas_energy_energy_vetosci41->cd(0);
    dir_degas_sci41->Append(c_degas_energy_energy_vetosci41);

    c_degas_energy_energy_sci41_cut = new TCanvas(canvasName("c_degas_energy_energy_sci41_cut"),"Calibrated Degas spectra summed all energies, t(det) - t(sci41) > 200 ns",650,350);
    h2_degas_energy_energy_sci41_cut = MakeTH2(dir_degas_sci41, "F", "h2_degas_energy_energy_sci41_cut","Calibrated Degas spectra summed all energies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", "Energy [keV]");
    h2_degas_energy_energy_sci41_cut->Draw();
    c_degas_energy_energy_sci41_cut->cd(0);
    dir_degas_sci41->Append(c_degas_energy_energy_sci41_cut);


    dir_degas_multiplicity->cd();
    c_degas_multiplicity = new TCanvas(canvasName("c_degas_multiplicity"),"Multiplicity of Degas events",650,350);
    h1_degas_multiplicity = MakeTH1(dir_degas_multiplicity, "I", "h1_degas_multiplicity","Multiplicity of Degas events",number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Event Multiplicity", kRed-3, kBlack);
    h1_degas_multiplicity->Draw();
    dir_degas_multiplicity->Append(c_degas_multiplicity);

    //time differences!
    number_reference_detectors = dt_reference_detectors.size();
    dir_degas_time_differences.resize(number_reference_detectors);

    h1_degas_time_differences = new TH1**[number_reference_detectors];
    h2_degas_time_differences_vs_energy = new TH2**[number_reference_detectors];
    for (int ihist = 0; ihist < number_reference_detectors; ihist++)
    {
        std::stringstream name;
        name << "time_differences_rel_" << dt_reference_detectors.at(ihist).first << "_" << dt_reference_detectors.at(ihist).second << "_energy_gate_" << (int)dt_reference_detectors_energy_gates.at(ihist).first << "_" << (int)dt_reference_detectors_energy_gates.at(ihist).second;
        dir_degas_time_differences[ihist] = dir_degas->mkdir(name.str().c_str());

        c_degas_time_differences  = new TCanvas(canvasName(Form("c_degas_time_differences_rel_det_%d_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second)),"degas relative time differences",650,350);
        c_degas_time_differences->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h1_degas_time_differences[ihist] = new TH1*[number_of_detectors_to_plot];

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++)
        {
            c_degas_time_differences->cd(detid_idx+1);
            h1_degas_time_differences[ihist][detid_idx] = MakeTH1(dir_degas_time_differences[ihist], "F", Form("h1_degas_rel_time_det_%d_%d_to_det_%d_%d_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("Degas delta time t(%d%c) - t(%d%c) gated %d and %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),2e3,-20e3,20e3, Form("dT t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)), kMagenta, kBlue+2);
            h1_degas_time_differences[ihist][detid_idx]->Draw();
        }
        c_degas_time_differences->cd(0);
        dir_degas_time_differences[ihist]->Append(c_degas_time_differences);

        c_degas_time_differences_vs_energy  = new TCanvas(canvasName(Form("c_degas_time_differences_rel_det_%d_%d_vs_energy_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second)),"degas relative time differences vs energy",650,350);
        c_degas_time_differences_vs_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h2_degas_time_differences_vs_energy[ihist] = new TH2*[number_of_detectors_to_plot];

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++)
        {
            c_degas_time_differences_vs_energy->cd(detid_idx+1);
            h2_degas_time_differences_vs_energy[ihist][detid_idx] = MakeTH2(dir_degas_time_differences[ihist], "F", Form("h1_degas_rel_time_det_%d_%d_to_det_%d_%d_vs_energy_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("DEGAS dT t(%d%c) - t(%d%c) vs Energy, energy gate %d, %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,500,-2e4,2e4, Form("Energy (Detector %d%c) [keV]",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65)), Form("dT t(%d%c) - t(%d%c) [ns]",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h2_degas_time_differences_vs_energy[ihist][detid_idx]->Draw();

        }
        c_degas_time_differences_vs_energy->cd(0);
        dir_degas_time_differences[ihist]->Append(c_degas_time_differences_vs_energy);

    }

    detector_counters = new int[number_of_detectors_to_plot];
    detector_rates = new int[number_of_detectors_to_plot];
    h1_degas_rates = new TH1*[number_of_detectors_to_plot];
    for (int i = 0; i < number_of_detectors_to_plot; i++) h1_degas_rates[i] = MakeTH1(dir_degas_rates, "I", Form("h1_degas_rates_det%i_crystal%i", crystals_to_plot.at(i).first, crystals_to_plot.at(i).second), Form("DEGAS Rate Detector %i Crystal %i", crystals_to_plot.at(i).first, crystals_to_plot.at(i).second), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);


    c_degas_hitpattern = new TCanvas(canvasName("c_degas_hitpattern"),"Hit pattern DEGAS",650,350);
    h1_degas_hitpattern = MakeTH1(dir_degas_hitpattern, "I", "h1_degas_hitpattern","Hit pattern of DEGAS",number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Crystal", kRed-3, kBlack);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_degas_hitpattern->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }
    h1_degas_hitpattern->GetXaxis()->SetAlphanumeric();
    h1_degas_hitpattern->GetXaxis()->LabelsOption("a");
    h1_degas_hitpattern->SetStats(0); // ???
    h1_degas_hitpattern->Draw();
    c_degas_hitpattern->cd(0);
    dir_degas_hitpattern->Append(c_degas_hitpattern);


    // RESOLUTIONS:
    f1_gaussian = new TF1("f1_gaussian","gaus",centroid_resolution-width_resolution,centroid_resolution+width_resolution);

    c1_degas_energy_last  = new TCanvas(canvasName("c1_degas_energy_last"),"Calibrated Degas spectra",650,350);
    c1_degas_energy_last->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_degas_energy_last = new TH1*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c1_degas_energy_last->cd(ihist+1);
        h1_degas_energy_last[ihist] = MakeTH1(dir_degas_resolution, "F", Form("h1_degas_energy_last_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
        h1_degas_energy_last[ihist]->Draw();
    }
    c1_degas_energy_last->cd(0);
    dir_degas_resolution->Append(c1_degas_energy_last);

    c1_degas_energy_last_fitted  = new TCanvas(canvasName("c1_degas_energy_last_fitted"),"Calibrated Degas spectra",650,350);
    c1_degas_energy_last_fitted->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_degas_energy_last_fitted = new TH1*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c1_degas_energy_last_fitted->cd(ihist+1);
        h1_degas_energy_last_fitted[ihist] = MakeTH1(dir_degas_resolution, "F", Form("h1_degas_energy_last_fitted_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
        h1_degas_energy_last_fitted[ihist]->Draw();
    }
    c1_degas_energy_last_fitted->cd(0);
    dir_degas_resolution->Append(c1_degas_energy_last_fitted);

    dir_degas_resolution->cd();
    c_last_resolutions_FWHM = new TCanvas(canvasName("c_last_resolutions_FWHM"),Form("Last measurement of the resolution at E = %i keV DEGAS",(int)centroid_resolution),650,350);
    c_last_resolutions_FWHM->Divide(3);
    c_last_resolutions_FWHM->cd(1);

    h1_last_resolutions_FWHM = MakeTH1(dir_degas_resolution, "F", "h1_last_resolutions_FWHM",Form("Last measurement of the FWHM at E = %i keV DEGAS",(int)centroid_resolution),number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Crystal", kTeal+1, kBlack);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_last_resolutions_FWHM->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }
    h1_last_resolutions_FWHM->GetXaxis()->SetAlphanumeric();
    h1_last_resolutions_FWHM->GetXaxis()->LabelsOption("a");
        h1_last_resolutions_FWHM->GetYaxis()->SetTitle("FWHM [keV]");
    h1_last_resolutions_FWHM->SetStats(0);
    h1_last_resolutions_FWHM->Draw("HIST");

    c_last_resolutions_FWHM->cd(2);
    h1_last_resolutions_FWTM = MakeTH1(dir_degas_resolution, "F", "h1_last_resolutions_FWTM",Form("Last measurement of the FWTM at E = %i keV DEGAS",(int)centroid_resolution),number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Crystal", kTeal+1, kBlack);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_last_resolutions_FWTM->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }
    h1_last_resolutions_FWTM->GetXaxis()->SetAlphanumeric();
    h1_last_resolutions_FWTM->GetXaxis()->LabelsOption("a");
    h1_last_resolutions_FWTM->GetYaxis()->SetTitle("Counts");
    h1_last_resolutions_FWTM->SetStats(0);
    h1_last_resolutions_FWTM->Draw("HIST");

    c_last_resolutions_FWHM->cd(3);
    h1_last_resolutions_gratio = MakeTH1(dir_degas_resolution, "F", "h1_last_resolutions_gratio",Form("Last measurement of the FWTM at E = %i keV DEGAS",(int)centroid_resolution),number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Crystal", kTeal+1, kBlack);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_last_resolutions_gratio->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }
    h1_last_resolutions_gratio->GetXaxis()->SetAlphanumeric();
    h1_last_resolutions_gratio->GetXaxis()->LabelsOption("a");
    h1_last_resolutions_gratio->GetYaxis()->SetTitle("counts");
    h1_last_resolutions_gratio->SetStats(0);
    h1_last_resolutions_gratio->Draw("HIST");
    dir_degas_resolution->Append(c_last_resolutions_FWHM);

    c_resolutions_FWHM  = new TCanvas(canvasName("c_resolutions_FWHM"),"Resolutions",650,350);
    c_resolutions_FWHM->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    g1_resolutions_FWHM = new TGraph*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c_resolutions_FWHM->cd(ihist+1);
        g1_resolutions_FWHM[ihist] = new TGraph(1);
        g1_resolutions_FWHM[ihist]->SetName(Form("g1_resolutions_FWHM_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        g1_resolutions_FWHM[ihist]->SetTitle(Form("DEGAS resolution FWHM detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1_resolutions_FWHM[ihist]->GetXaxis()->SetTitle("Time since start [s]");
        g1_resolutions_FWHM[ihist]->GetYaxis()->SetTitle("FWHM [keV]");
        g1_resolutions_FWHM[ihist]->Draw("ALP");
        dir_degas_resolution->Append(g1_resolutions_FWHM[ihist]);
    }
    c_resolutions_FWHM->cd(0);
    dir_degas_resolution->Append(c_resolutions_FWHM);


    c_resolutions_FWTM  = new TCanvas(canvasName("c_resolutions_FWTM"),"Resolutions",650,350);
    c_resolutions_FWTM->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    g1_resolutions_FWTM = new TGraph*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c_resolutions_FWTM->cd(ihist+1);
        g1_resolutions_FWTM[ihist] = new TGraph(1);
        g1_resolutions_FWTM[ihist]->SetName(Form("g1_resolutions_FWTM_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        g1_resolutions_FWTM[ihist]->SetTitle(Form("DEGAS resolution FWTM detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1_resolutions_FWTM[ihist]->GetXaxis()->SetTitle("Time since start [s]");
        g1_resolutions_FWTM[ihist]->GetYaxis()->SetTitle("FWTM [keV]");
        g1_resolutions_FWTM[ihist]->Draw("ALP");
        dir_degas_resolution->Append(g1_resolutions_FWTM[ihist]);
    }
    c_resolutions_FWTM->cd(0);
    dir_degas_resolution->Append(c_resolutions_FWTM);


    c_resolutions_gratio  = new TCanvas(canvasName("c_resolutions_gratio"),"Resolutions",650,350);
    c_resolutions_gratio->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    g1_resolutions_gratio = new TGraph*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        c_resolutions_gratio->cd(ihist+1);
        g1_resolutions_gratio[ihist] = new TGraph(1);
        g1_resolutions_gratio[ihist]->SetName(Form("g1_resolutions_gratio_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        g1_resolutions_gratio[ihist]->SetTitle(Form("DEGAS resolution gratio detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1_resolutions_gratio[ihist]->GetXaxis()->SetTitle("Time since start [s]");
        g1_resolutions_gratio[ihist]->GetYaxis()->SetTitle("gratio [keV]");
        g1_resolutions_gratio[ihist]->Draw("ALP");
        dir_degas_resolution->Append(g1_resolutions_gratio[ihist]);

    }
    c_resolutions_gratio->cd(0);
    dir_degas_resolution->Append(c_resolutions_gratio);


    return kSUCCESS;
}

void DegasOnlineSpectra::Reset_Histo() {
    c4LOG(info, "Resetting Degas histograms.");

    // Assuming dir is a TDirectory pointer containing histograms
    if (dir_degas) {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_degas);
        c4LOG(info, "Degas histograms reset.");
    } else {
        c4LOG(error, "Failed to get list of histograms from directory.");
    }
}

void DegasOnlineSpectra::Exec(Option_t*)
{
    FillEvent();
}

void DegasOnlineSpectra::FillEvent()
{
    int sc41_hits_seen = 0;
    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {

        if (first_time == 0) first_time = ((DegasCalData*)fHitGe->At(0))->Get_wr_t();

        Int_t nHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        int64_t degas_wr = 0;

        bool sci41_seen = false; // off-spill raw spectra

        for (Int_t ihit = 0; ihit < nHits; ihit++) // core loop for basic detector spectra and simple conincidences.
        {

            DegasCalData* hit1 = (DegasCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            if (ihit == 0) current_wr = hit1->Get_wr_t();
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();


            if (!(degas_configuration->IsDetectorAuxilliary(detector_id1))) event_multiplicity ++; // count only physical events in degass

            if (detector_id1 == degas_configuration->SC41L() || detector_id1 == degas_configuration->SC41R())
            {
                sc41_hits_seen++;
                sci41_seen = true;
            }

            int crystal_index1 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id1,crystal_id1)));

            // Hits not present in the configured plot list must not index its arrays.
            if (crystal_index1 >= static_cast<int>(crystals_to_plot.size())) continue;

            detector_counters[crystal_index1]++; // for rates
            degas_wr = hit1->Get_wr_t();

            h1_degas_energy[crystal_index1]->Fill(energy1);
            h1_degas_energy_last[crystal_index1]->Fill(energy1);
            h2_degas_energy_vs_detidx->Fill(hit1->Get_channel_energy(),crystal_index1);
            h1_degas_time[crystal_index1]->Fill(time1);
            h1_degas_hitpattern->Fill(Form("%d%c",crystals_to_plot.at(crystal_index1).first,(char)(crystals_to_plot.at(crystal_index1).second+65)),1);
            if (!(degas_configuration->IsDetectorAuxilliary(detector_id1))) h1_degas_energy_summed->Fill(energy1);



            if (nHits >= 2 && dt_reference_detectors.size()>=0){ // reference detector id loop.
                for (int ihit2 = 0; ihit2 < nHits; ihit2++){
                    if (ihit == ihit2) continue;
                    DegasCalData * hit2 = (DegasCalData*)fHitGe->At(ihit2);
                    int detector_id2 = hit2->Get_detector_id();
                    int crystal_id2 = hit2->Get_crystal_id();
                    double energy2 = hit2->Get_channel_energy();
                    double time2 = hit2->Get_channel_trigger_time();

                    int crystal_index2 = std::distance(dt_reference_detectors.begin(), std::find(dt_reference_detectors.begin(),dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)));
                    if (crystal_index2 >= dt_reference_detectors.size()) continue;

                    while (crystal_index2 < dt_reference_detectors.size()){

                    if (dt_reference_detectors_energy_gates.at(crystal_index2).first > 0 && dt_reference_detectors_energy_gates.at(crystal_index2).second > 0){
                        if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(crystal_index2).first) < energygate_width) && (TMath::Abs(energy1 - dt_reference_detectors_energy_gates.at(crystal_index2).second) < energygate_width)){
                            h1_degas_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                            h2_degas_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                        }
                    }else{ // no gates            TCanvas* c_degas_rates;

                        h1_degas_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                        h2_degas_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                    }

                    crystal_index2 = std::distance(dt_reference_detectors.begin()+crystal_index2+1, std::find(dt_reference_detectors.begin()+crystal_index2+1,dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)))+crystal_index2+1;
                    }
                }
            }
        }


        if (!sci41_seen){ // sci41 vetoed spectra:
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {
                DegasCalData* hit1 = (DegasCalData*)fHitGe->At(ihit);
                if (!hit1) continue;
                int detector_id1 = hit1->Get_detector_id();
                int crystal_id1 = hit1->Get_crystal_id();
                double energy1 = hit1->Get_channel_energy();
                double time1 = hit1->Get_channel_trigger_time();
                if (degas_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                h1_degas_energy_summed_vetosci41->Fill(energy1);

                if (nHits >= 2){
                    for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++)
                    {
                        if (ihit2 == ihit) continue;
                        DegasCalData* hit2 = (DegasCalData*)fHitGe->At(ihit2);
                        if (!hit2) continue;
                        int detector_id2 = hit2->Get_detector_id();
                        int crystal_id2 = hit2->Get_crystal_id();
                        double energy2 = hit2->Get_channel_energy();
                        double time2 = hit2->Get_channel_trigger_time();

                        if (degas_configuration->IsDetectorAuxilliary(detector_id2) && detector_id1 != detector_id2) continue;
                        if (TMath::Abs(time2 - time1) < 200) {
                            h2_degas_energy_energy_vetosci41->Fill(energy1,energy2);
                        }
                    }

                }
            }
        }


        // Spectra with respect to SCI41:
        if (nHits >= 2 && sci41_seen)
        {
            for (int ihit1 = 0; ihit1 < nHits; ihit1 ++)
            {

                DegasCalData* hit_sci41 = (DegasCalData*)fHitGe->At(ihit1);
                if (!hit_sci41) continue;
                int detector_id_sci41 = hit_sci41->Get_detector_id();
                int crystal_id_sci41 = hit_sci41->Get_crystal_id();
                double energy_sci41 = hit_sci41->Get_channel_energy();
                double time_sci41 = hit_sci41->Get_channel_trigger_time();

                // after this test we have the sci41 hit.
                if (detector_id_sci41 != degas_configuration->SC41L() && detector_id_sci41 != degas_configuration->SC41R()) continue;

                for (int ihit2 = 0; ihit2 < nHits; ihit2 ++)
                {
                    DegasCalData* hit2 = (DegasCalData*)fHitGe->At(ihit2);
                    if (!hit2) continue;
                    int detector_id1 = hit2->Get_detector_id();
                    int crystal_id1 = hit2->Get_crystal_id();
                    double energy1 = hit2->Get_channel_energy();
                    double time1 = hit2->Get_channel_trigger_time();

                    if (degas_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                    double timediff = time1 - time_sci41 - degas_configuration->GetTimeshiftCoefficient(detector_id1,crystal_id1);

                    h2_degas_energy_summed_vs_tsci41->Fill(timediff ,energy1);



                    if ((TMath::Abs(time1-time_sci41 > 0)) && (degas_configuration->IsInsidePromptFlashCut(timediff ,energy1)==false) ) h1_degas_energy_summed_vs_tsci41_cut->Fill(energy1);

                    for (int ihit3 = ihit2+1; ihit3 < nHits; ihit3 ++)
                    {
                        DegasCalData* hit3 = (DegasCalData*)fHitGe->At(ihit3);
                        if (!hit3) continue;
                        int detector_id2 = hit3->Get_detector_id();
                        int crystal_id2 = hit3->Get_crystal_id();
                        double energy2 = hit3->Get_channel_energy();
                        double time2 = hit3->Get_channel_trigger_time();

                        if (degas_configuration->IsDetectorAuxilliary(detector_id2)) continue;

                        if (TMath::Abs(time1 - time2) < 500) h2_degas_energy_energy_sci41_cut->Fill(energy1,energy2);
                    }
                }
                break;
            }
        }

        h1_degas_multiplicity->Fill(event_multiplicity);

        int64_t wr_dt = (degas_wr - saved_degas_wr) / 1e9; // conv to s
        if (wr_dt > 2)
        {
            if (saved_degas_wr != 0)
            {
                for (int i = 0; i < number_of_detectors_to_plot; i++)
                {
                    detector_rates[i] = detector_counters[i] / wr_dt;
                    h1_degas_rates[i]->SetBinContent(rate_running_count, detector_rates[i]);
                }
            }

            saved_degas_wr = degas_wr;
            rate_running_count++;
            for (int i = 0; i < number_of_detectors_to_plot; i++)
            {
                if (rate_running_count == 1800) h1_degas_rates[i]->Reset();
                detector_counters[i] = 0;
            }
            if (rate_running_count == 1800) rate_running_count = 0;
        }
    }

    fNEvents += 1;
}

void DegasOnlineSpectra::FinishEvent()
{
    /*
    if (first_time > 0)
    {
        if (((int64_t)current_wr - (int64_t)last_time_resolution_was_measured)/1e9 > seconds_to_collect_resolution){
            // c4LOG(info, "Finding resolutions"); // CEJ: commenting out for now
            h1_last_resolutions_FWHM->Reset();
            h1_last_resolutions_FWTM->Reset();
            h1_last_resolutions_gratio->Reset();


            // measure resolutions:
            for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
                f1_gaussian->SetParameter(0,1e3);
                f1_gaussian->SetParameter(1,centroid_resolution);
                f1_gaussian->SetParameter(2,width_resolution);

                c1_degas_energy_last_fitted->cd(ihist+1);

                TString name = h1_degas_energy_last_fitted[ihist]->GetName();
                if (h1_degas_energy_last_fitted[ihist] != nullptr){
                    delete h1_degas_energy_last_fitted[ihist];
                }
                h1_degas_energy_last_fitted[ihist] = (TH1F*)h1_degas_energy_last[ihist]->Clone(name);

                Int_t fitresult = h1_degas_energy_last_fitted[ihist]->Fit(f1_gaussian,"QRL");


                if (fitresult == 0)
                {

                    h1_degas_energy_last_fitted[ihist]->Draw();
                    //f1_gaussian->Draw();

                    double fwhm = f1_gaussian->GetParameter(2)*2.355;

                    double tenthmaximum = f1_gaussian->Eval(f1_gaussian->GetParameter(1))/10.0;

                    int binnr1 = h1_degas_energy[ihist]->FindBin(centroid_resolution-50);
                    int binnr2 = h1_degas_energy[ihist]->FindBin(centroid_resolution+50);
                    int binlow = h1_degas_energy_last_fitted[ihist]->FindFirstBinAbove(tenthmaximum,1,binnr1,binnr2);
                    int binhigh = h1_degas_energy_last_fitted[ihist]->FindLastBinAbove(tenthmaximum,1,binnr1,binnr2);

                    double fwtm = h1_degas_energy_last_fitted[ihist]->GetBinCenter(binhigh) - h1_degas_energy_last_fitted[ihist]->GetBinCenter(binlow);

                    c_resolutions_FWHM->cd(ihist+1);
                    g1_resolutions_FWHM[ihist]->AddPoint(((int64_t)current_wr - (int64_t)first_time)/1e9, fwhm);
                    g1_resolutions_FWHM[ihist]->Draw("ALP");

                    c_resolutions_FWTM->cd(ihist+1);
                    g1_resolutions_FWTM[ihist]->AddPoint(((int64_t)current_wr - (int64_t)first_time)/1e9, fwtm);
                    g1_resolutions_FWTM[ihist]->Draw("ALP");

                    c_resolutions_gratio->cd(ihist+1);
                    g1_resolutions_gratio[ihist]->AddPoint(((int64_t)current_wr - (int64_t)first_time)/1e9, fwtm/fwhm);
                    g1_resolutions_gratio[ihist]->Draw("ALP");
                    //c_resolutions_FWHM->cd(0);

                    c_last_resolutions_FWHM->cd(1);
                    h1_last_resolutions_FWHM->Fill(Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fwhm);
                    h1_last_resolutions_FWHM->Draw("HIST");
                    c_last_resolutions_FWHM->cd(2);
                    h1_last_resolutions_FWTM->Fill(Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fwtm);
                    h1_last_resolutions_FWTM->Draw("HIST");
                    c_last_resolutions_FWHM->cd(3);
                    h1_last_resolutions_gratio->Fill(Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fwtm/fwhm);
                    h1_last_resolutions_gratio->Draw("HIST");
                    c_last_resolutions_FWHM->cd(0);

                }

                last_time_resolution_was_measured = current_wr;

                h1_degas_energy_last[ihist]->Reset();
            }
        }
    }
    */



}

void DegasOnlineSpectra::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitGe)
    {
        c4LOG(info, "DEGAS histograms written to file.");
    }
}

ClassImp(DegasOnlineSpectra)
