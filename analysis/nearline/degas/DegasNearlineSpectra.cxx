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
#include "DegasNearlineSpectra.h"
#include "EventHeader.h"
#include "DegasCalData.h"
#include "TDegasConfiguration.h"

#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include <sstream>

DegasNearlineSpectra::DegasNearlineSpectra() : DegasNearlineSpectra("DegasNearlineSpectra")
{
    degas_configuration = TDegasConfiguration::GetInstance();
}

DegasNearlineSpectra::DegasNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{
    degas_configuration = TDegasConfiguration::GetInstance();
}

DegasNearlineSpectra::~DegasNearlineSpectra()
{
    c4LOG(info, "");
    // fHitGe is borrowed from FairRootManager.
}

InitStatus DegasNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("DegasCalData");
    if (!fHitGe || fHitGe->GetClass() != DegasCalData::Class())
    {
        c4LOG(error, "Expected DEGAS hit objects in the input branch");
        return kFATAL;
    }

    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = degas_configuration->Mapping();

    for (auto it_mapping = gmap.begin(); it_mapping != gmap.end(); ++it_mapping){
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(std::pair<int,int>(it_mapping->second.first,it_mapping->second.second));
    }

    number_of_detectors_to_plot = crystals_to_plot.size();

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_degas = gDirectory->mkdir(fSpectraDirectory.IsNull() ? "DEGAS" : fSpectraDirectory.Data());
    if (!dir_degas || !dir_degas->cd()) return kFATAL;

    dir_degas_energy = dir_degas->mkdir("Calibrated Energy Spectra");
    dir_degas_drift = dir_degas->mkdir("Drift Time Spectra");
    dir_degas_time = dir_degas->mkdir("Time Spectra");
    dir_degas_hitpattern = dir_degas->mkdir("Hit Pattern");
    dir_degas_multiplicity = dir_degas->mkdir("Multiplicity");
    dir_degas_sci41 = dir_degas->mkdir("SCI41");
    dir_degas_rates = dir_degas->mkdir("Rates");

    // energy spectra:
    h1_degas_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_degas_energy[ihist] = MakeTH1(dir_degas_energy, "F", Form("h1_degas_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
    }

    h2_degas_energy_vs_detidx = MakeTH2(dir_degas_energy, "F", "h2_degas_energy_vs_detidx","Calibrated Degas spectra vs. detector index",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Energy [keV]", "Detector");
    h1_degas_energy_summed = MakeTH1(dir_degas_energy, "F", "h1_degas_energy_summed","Calibrated Degas spectra summed all dets",fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);

    h2_degas_energy_vs_t.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h2_degas_energy_vs_t[ihist] = MakeTH2(dir_degas_drift, "F", Form("h2_degas_energy_vs_t_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy vs time detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),2150,0,10750,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Time [mins]", "Energy [keV]");
    }

    // Spectra relating to SCI41:
    h1_degas_energy_summed_vetosci41 = MakeTH1(dir_degas_sci41, "F", "h1_degas_energy_summed_vetosci41","Calibrated Degas spectra summed all dets veto sci 41",fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
    h2_degas_energy_summed_vs_tsci41 = MakeTH2(dir_degas_sci41, "F", "h2_degas_energy_summed_vs_tsci41","Calibrated Degas spectra summed all energyies vs t(det) - t(sci41)",1000,-500,5000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Time difference [ns]", "Energy [keV]");
    h1_degas_energy_summed_vs_tsci41_cut = MakeTH1(dir_degas_sci41, "F", "h1_degas_energy_summed_vs_tsci41_cut","Calibrated Degas spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", kOrange-3, kBlue+2);
    h2_degas_energy_energy_vetosci41 = MakeTH2(dir_degas_sci41, "F", "h2_degas_energy_energy_vetosci41","Calibrated Degas spectra summed all energies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", "Energy [keV]");
    h2_degas_energy_energy_sci41_cut = MakeTH2(dir_degas_sci41, "F", "h2_degas_energy_energy_sci41_cut","Calibrated Degas spectra summed all energies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [keV]", "Energy [keV]");


    // time spectra:
    h1_degas_time.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_degas_time[ihist] = MakeTH1(dir_degas_time, "F", Form("h1_degas_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e16, "Time [ns]");
    }

    dir_degas_multiplicity->cd();
    h1_degas_multiplicity = MakeTH1(dir_degas_multiplicity, "I", "h1_degas_multiplicity","Multiplicity of Degas events",number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Event Multiplicity", kRed-3, kBlack);

    //time differences!
    number_reference_detectors = dt_reference_detectors.size();
    dir_degas_time_differences.resize(number_reference_detectors);

    h1_degas_time_differences.resize(number_reference_detectors);
    h2_degas_time_differences_vs_energy.resize(number_reference_detectors);
    for (int ihist = 0; ihist < number_reference_detectors; ihist++)
    {
        std::stringstream name;
        name << "time_differences_rel_" << dt_reference_detectors.at(ihist).first << "_" << dt_reference_detectors.at(ihist).second << "_energy_gate_" << (int)dt_reference_detectors_energy_gates.at(ihist).first << "_" << (int)dt_reference_detectors_energy_gates.at(ihist).second;
        dir_degas_time_differences[ihist] = dir_degas->mkdir(name.str().c_str());

        h1_degas_time_differences[ihist].resize(number_of_detectors_to_plot);
        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++)
        {
            h1_degas_time_differences[ihist][detid_idx] = MakeTH1(dir_degas_time_differences[ihist], "F", Form("h1_degas_rel_time_det_%d_%d_to_det_%d_%d_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("Degas delta time t(%d%c) - t(%d%c) gated %d and %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),1e3,-1e3,1e3, Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)), kMagenta, kBlue+2);
        }

        h2_degas_time_differences_vs_energy[ihist].resize(number_of_detectors_to_plot);
        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++)
        {
            h2_degas_time_differences_vs_energy[ihist][detid_idx] = MakeTH2(dir_degas_time_differences[ihist], "F", Form("h1_degas_rel_time_det_%d_%d_to_det_%d_%d_vs_energy_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("DEGAS dT t(%d%c) - t(%d%c) vs Energy, energy gate %d, %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,500,-2e4,2e4, Form("Energy (Detector %d%c) [keV]",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65)), Form("dT t(%d%c) - t(%d%c) [ns]",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
        }
    }

    detector_counters = new int[number_of_detectors_to_plot];
    detector_rates = new int[number_of_detectors_to_plot];
    h1_degas_rates = new TH1*[number_of_detectors_to_plot];
    for (int i = 0; i < number_of_detectors_to_plot; i++) h1_degas_rates[i] = MakeTH1(dir_degas_rates, "I", Form("h1_degas_rates_det%i_crystal%i", crystals_to_plot.at(i).first, crystals_to_plot.at(i).second), Form("DEGAS Rate Detector %i Crystal %i", crystals_to_plot.at(i).first, crystals_to_plot.at(i).second), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);


    detector_labels = new char*[number_of_detectors_to_plot];
    h1_degas_hitpattern = MakeTH1(dir_degas_hitpattern, "I", "h1_degas_hitpattern","Hit pattern of DEGAS",number_of_detectors_to_plot,0,number_of_detectors_to_plot, "Crystal", kRed-3, kBlack);
    h1_degas_hitpattern->GetXaxis()->SetAlphanumeric();
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        detector_labels[ihist] = Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65));
        h1_degas_hitpattern->GetXaxis()->SetBinLabel(ihist+1,detector_labels[ihist]);
    }
    h1_degas_hitpattern->GetXaxis()->LabelsOption("a");
    h1_degas_hitpattern->SetStats(0);

    gDirectory = tmp;

    return kSUCCESS;
}

void DegasNearlineSpectra::Exec(Option_t*)
{
    FillEvent();
}

void DegasNearlineSpectra::FillEvent()
{

    if (fHitGe && fHitGe->GetEntriesFast() > 0){

        Int_t nHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        int64_t degas_wr = 0;
        Long64_t degas_time = 0;


        bool sci41_seen = false; // off-spill raw spectra

        for (Int_t ihit = 0; ihit < nHits; ihit++){ // core loop for basic detector spectra and simple conincidences.

            DegasCalData* hit1 = (DegasCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();
            if (hit1->Get_wr_t() > 0) degas_time = (hit1->Get_wr_t() - 1.7137224e+18)/ 60E9; // convert ns start to minutes

            if (!(degas_configuration->IsDetectorAuxilliary(detector_id1))) event_multiplicity ++; // count only physical events in degass

            if (detector_id1 == degas_configuration->SC41L() || detector_id1 == degas_configuration->SC41R()) sci41_seen = true;

            int crystal_index1 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id1,crystal_id1)));

            detector_counters[crystal_index1]++; // for rates
            degas_wr = hit1->Get_wr_t();

            if (crystal_index1 >= crystals_to_plot.size()) continue;

            h1_degas_energy[crystal_index1]->Fill(energy1);
            h2_degas_energy_vs_detidx->Fill(hit1->Get_channel_energy(),crystal_index1);
            h2_degas_energy_vs_t[crystal_index1]->Fill(degas_time,energy1);
            h1_degas_time[crystal_index1]->Fill(time1);
            h1_degas_hitpattern->Fill(detector_labels[crystal_index1],1);
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
                    }else{ // no gates
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

                    if ((TMath::Abs(time1-time_sci41 > 0)) || (degas_configuration->IsInsidePromptFlashCut(timediff ,energy1)==false) ) h1_degas_energy_summed_vs_tsci41_cut->Fill(energy1);

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


void DegasNearlineSpectra::FinishEvent()
{
    // Input is cleared by its producing task.
}

void DegasNearlineSpectra::FinishTask()
{
    if (fNEvents == 0 && fSpectraDirectory.IsNull())
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_degas->Write();
    gDirectory = tmp;
    c4LOG(info, "DEGAS histograms written to file.");
}

ClassImp(DegasNearlineSpectra)
