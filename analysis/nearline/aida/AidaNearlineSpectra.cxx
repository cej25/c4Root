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
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaNearlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"

// ROOT
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <sstream>
#include "TFile.h"
#include <chrono>

AidaNearlineSpectra::AidaNearlineSpectra() : AidaNearlineSpectra("AidaNearline")
{
}

AidaNearlineSpectra::AidaNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , adcArray(nullptr)
    , flowArray(nullptr)
    , scalerArray(nullptr)
    , implantHitArray(nullptr)
    , header(nullptr)
    , fNEvents(0)
{
}

AidaNearlineSpectra::~AidaNearlineSpectra()
{
    c4LOG(info, "Destroyed AidaNearlineSpectra properly.");
    
}

InitStatus AidaNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();
  
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

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_aida = gDirectory->mkdir("AIDA");
    gDirectory->cd("AIDA"); // needed?

    dir_implant = dir_aida->mkdir("Implants");
    dir_stopped_implant = dir_aida->mkdir("Stopped Implants");
    dir_decay = dir_aida->mkdir("Decays");
    dir_scalers = dir_aida->mkdir("Scalers");

    // Aida configuration
    conf = TAidaConfiguration::GetInstance();

    int xstrips = conf->Wide() ? 386 : 128;
    double xmax = conf->Wide() ? 113.4 : 37.8;

    dir_implant_dssd.resize(conf->DSSDs());
    dir_stopped_implant_dssd.resize(conf->DSSDs());
    dir_decay_dssd.resize(conf->DSSDs());

    h_implant_strip_xy.resize(conf->DSSDs());
    h_implant_pos_xy.resize(conf->DSSDs());
    h_implant_e.resize(conf->DSSDs());
    h_implant_e_xy.resize(conf->DSSDs());
    h_implant_strip_1d_energy.resize(conf->DSSDs());
    h_implant_x_ex.resize(conf->DSSDs());
    h_implant_strip_xy_stopped.resize(conf->DSSDs());
    h_implant_pos_xy_stopped.resize(conf->DSSDs());
    h_implant_e_stopped.resize(conf->DSSDs());
    h_implant_x_ex_stopped.resize(conf->DSSDs());
    h_decay_strip_xy.resize(conf->DSSDs());
    h_decay_pos_xy.resize(conf->DSSDs());
    h_decay_e.resize(conf->DSSDs());
    h_decay_e_xy.resize(conf->DSSDs());
    h_decay_strip_1d_energy.resize(conf->DSSDs());
    aida_implant_scaler_queue.resize(conf->DSSDs());
    aida_implant_scaler_cur_sec.resize(conf->DSSDs());
    aida_implant_scaler_graph.resize(conf->DSSDs());
    aida_implant_stopped_scaler_queue.resize(conf->DSSDs());
    aida_implant_stopped_scaler_graph.resize(conf->DSSDs());
    aida_decay_scaler_queue.resize(conf->DSSDs());
    aida_decay_scaler_cur_sec.resize(conf->DSSDs());
    aida_decay_scaler_graph.resize(conf->DSSDs());

    for (int i = 0; i < conf->DSSDs(); i++)
    {
        std::stringstream name;
        std::stringstream title;
        name << "DSSD" << (i + 1);
        dir_implant_dssd[i] = dir_implant->mkdir(name.str().c_str());
        dir_stopped_implant_dssd[i] = dir_stopped_implant->mkdir(name.str().c_str());
        dir_decay_dssd[i] = dir_decay->mkdir(name.str().c_str());

        dir_implant_dssd[i]->cd();
        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_strip_xy";
        title << "DSSD " << (i + 1) << " implant hit pattern";
        h_implant_strip_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, 0, xstrips, 128, 0, 128);
        h_implant_strip_xy[i]->GetXaxis()->SetTitle("X strip");
        h_implant_strip_xy[i]->GetYaxis()->SetTitle("Y strip");

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_pos_xy";
        title << "DSSD " << (i + 1) << " implant position";
        h_implant_pos_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h_implant_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h_implant_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_e";
        title << "DSSD " << (i + 1) << " implant energy";
        h_implant_e[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h_implant_e[i]->GetXaxis()->SetTitle("Implant Energy/MeV");

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_e_xy";
        title << "DSSD " << (i + 1) << " implant energy X vs energy Y";
        h_implant_e_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000, 2000, 0, 20000);
        h_implant_e_xy[i]->GetXaxis()->SetTitle("Implant X Energy/MeV");
        h_implant_e_xy[i]->GetYaxis()->SetTitle("Implant Y Energy/MeV");

        // TODO move outof implants as it's not FB matched?
        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_strip_1d_energy";
        title << "DSSD " << (i + 1) << " 1D strip vs energy";
        h_implant_strip_1d_energy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                128 + xstrips, 0, 128 + xstrips, 2000, 0, 20000);
        h_implant_strip_1d_energy[i]->GetXaxis()->SetTitle("Strip (X then Y");
        h_implant_strip_1d_energy[i]->GetYaxis()->SetTitle("Implant Energy/MeV");

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_x_ex";
        title << "DSSD " << (i + 1) << " X position vs Energy";
        h_implant_x_ex[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 2000, 0, 20000);
        h_implant_x_ex[i]->GetXaxis()->SetTitle("X Position/mm");
        h_implant_x_ex[i]->GetYaxis()->SetTitle("Energy/MeV");

        dir_stopped_implant_dssd[i]->cd();
        name.str("");
        title.str("");
        name << "aida_implants_stopped_d" << (i + 1) << "_implants_strip_xy";
        title << "DSSD " << (i + 1) << " stopped implant hit pattern";
        h_implant_strip_xy_stopped[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, 0, xstrips, 128, 0, 128);
        h_implant_strip_xy_stopped[i]->GetXaxis()->SetTitle("X strip");
        h_implant_strip_xy_stopped[i]->GetYaxis()->SetTitle("Y strip");

        name.str("");
        title.str("");
        name << "aida_implants_stopped_d" << (i + 1) << "_implants_pos_xy";
        title << "DSSD " << (i + 1) << " stopped implant position";
        h_implant_pos_xy_stopped[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h_implant_pos_xy_stopped[i]->GetXaxis()->SetTitle("X position/mm");
        h_implant_pos_xy_stopped[i]->GetYaxis()->SetTitle("Y position/mm");

        name.str("");
        title.str("");
        name << "aida_implants_stopped_d" << (i + 1) << "_implants_e";
        title << "DSSD " << (i + 1) << " stopped implant energy";
        h_implant_e_stopped[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h_implant_e_stopped[i]->GetXaxis()->SetTitle("Implant Energy/MeV");

        name.str("");
        title.str("");
        name << "aida_implants_stopped_d" << (i + 1) << "_implants_x_ex";
        title << "DSSD " << (i + 1) << " stopped X position vs Energy";
        h_implant_x_ex_stopped[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 2000, 0, 20000);
        h_implant_x_ex_stopped[i]->GetXaxis()->SetTitle("X Position/mm");
        h_implant_x_ex_stopped[i]->GetYaxis()->SetTitle("Energy/MeV");

        dir_decay_dssd[i]->cd();
        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_strip_xy";
        title << "DSSD " << (i + 1) << " decay hit pattern";
        h_decay_strip_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, 0, xstrips, 128, 0, 128);
        h_decay_strip_xy[i]->GetXaxis()->SetTitle("X strip");
        h_decay_strip_xy[i]->GetYaxis()->SetTitle("Y strip");

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_pos_xy";
        title << "DSSD " << (i + 1) << " decay position";
        h_decay_pos_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h_decay_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h_decay_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_e";
        title << "DSSD " << (i + 1) << " decay energy";
        h_decay_e[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h_decay_e[i]->GetXaxis()->SetTitle("Decay Energy/keV");

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_e_xy";
        title << "DSSD " << (i + 1) << " decay energy X vs energy Y";
        h_decay_e_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000, 2000, 0, 20000);
        h_decay_e_xy[i]->GetXaxis()->SetTitle("Decay X Energy/keV");
        h_decay_e_xy[i]->GetYaxis()->SetTitle("Decay Y Energy/keV");

        // TODO move outof decays as it's not FB matched?
        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_strip_1d_energy";
        title << "DSSD " << (i + 1) << " 1D strip vs energy";
        h_decay_strip_1d_energy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                128 + xstrips, 0, 128 + xstrips, 2000, 0, 20000);
        h_decay_strip_1d_energy[i]->GetXaxis()->SetTitle("Strip (X then Y");
        h_decay_strip_1d_energy[i]->GetYaxis()->SetTitle("Decay Energy/keV");

        dir_scalers->cd();
        aida_implant_scaler_queue[i].clear();
        aida_implant_scaler_cur_sec[i] = -1;
        aida_implant_scaler_graph[i] = new TGraph(3600);
        name.str("");
        title.str("");
        name << "aida_scaler_implants_d" << (i + 1);
        title << "AIDA DSSD " << (i+ 1) << " Implant Rate";
        title << ";Time before now (s);Frequency (Hz)";
        aida_implant_scaler_graph[i]->SetName(name.str().c_str());
        aida_implant_scaler_graph[i]->SetTitle(title.str().c_str());
        aida_implant_scaler_graph[i]->SetMinimum(0);
        dir_scalers->Append(aida_implant_scaler_graph[i]);

        aida_implant_stopped_scaler_queue[i].clear();
        aida_implant_stopped_scaler_graph[i] = new TGraph(3600);
        name.str("");
        title.str("");
        name << "aida_scaler_implants_stopped_d" << (i + 1);
        title << "AIDA DSSD " << (i+ 1) << " Stopped Implant Rate";
        title << ";Time before now (s);Frequency (Hz)";
        aida_implant_stopped_scaler_graph[i]->SetName(name.str().c_str());
        aida_implant_stopped_scaler_graph[i]->SetTitle(title.str().c_str());
        aida_implant_stopped_scaler_graph[i]->SetMinimum(0);
        dir_scalers->Append(aida_implant_stopped_scaler_graph[i]);

        aida_decay_scaler_queue[i].clear();
        aida_decay_scaler_cur_sec[i] = -1;
        aida_decay_scaler_graph[i] = new TGraph(3600);
        name.str(""); title.str("");
        name << "aida_scaler_decays_d" << (i + 1);
        title << "AIDA DSSD " << (i+ 1) << " Decay Rate";
        title << ";Time before now (s);Frequency (Hz)";
        aida_decay_scaler_graph[i]->SetName(name.str().c_str());
        aida_decay_scaler_graph[i]->SetTitle(title.str().c_str());
        aida_decay_scaler_graph[i]->SetMinimum(0);
        dir_scalers->Append(aida_decay_scaler_graph[i]);
    }

    dir_scalers->cd();
    for (auto& scaler : conf->ScalerMap())
    {
        aida_scaler_queue[scaler.first].clear();
        aida_scaler_cur_sec[scaler.first] = -1;
        aida_scaler_graph[scaler.first] = new TGraph(3600);
        std::stringstream name;
        std::stringstream title;
        name << "aida_scaler_" << scaler.first << "_" << scaler.second;
        title << "AIDA Scaler #" << scaler.first << " - " << scaler.second;
        title << ";Time before now (s);Frequency (Hz)";
        aida_scaler_graph[scaler.first]->SetName(name.str().c_str());
        aida_scaler_graph[scaler.first]->SetTitle(title.str().c_str());
        aida_scaler_graph[scaler.first]->SetMinimum(0);
        dir_scalers->Append(aida_scaler_graph[scaler.first]);
    }

    dir_aida->cd();
    gDirectory = tmp;

    return kSUCCESS;
}


void AidaNearlineSpectra::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    //for (auto const& entry : *adcArray)
    //{
        //int fee = entry.Fee();
        //bool implant = entry.Range();
        //int channel = entry.Channel();
        //uint16_t value = entry.Value();

        //int implantIdx = implant ? 1 : 0;

        //if (!implant)
            //fhAdcs[fee - 1][channel][implantIdx]->Fill(value);
    //}
    //
    //
    bool implant_hredraw = false;
    for (auto const& hit : *implantHitArray)
    {
        h_implant_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
        h_implant_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        h_implant_e[hit.DSSD - 1]->Fill(hit.Energy);
        h_implant_e_xy[hit.DSSD - 1]->Fill(hit.EnergyX, hit.EnergyY);
        h_implant_x_ex[hit.DSSD - 1]->Fill(hit.PosX, hit.EnergyX);

        if (hit.Stopped)
        {
            h_implant_strip_xy_stopped[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
            h_implant_pos_xy_stopped[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
            h_implant_e_stopped[hit.DSSD - 1]->Fill(hit.Energy);
            h_implant_x_ex_stopped[hit.DSSD - 1]->Fill(hit.PosX, hit.EnergyX);
        }

        int second = (hit.Time / 1000000000ULL);
        if (second == aida_implant_scaler_cur_sec[hit.DSSD - 1])
        {
            aida_implant_scaler_queue[hit.DSSD - 1].front() += 1;
            if (hit.Stopped)
                aida_implant_scaler_queue[hit.DSSD - 1].front() += 1;
        }
        else
        {
            implant_hredraw = true;
            if (aida_implant_scaler_cur_sec[hit.DSSD - 1] != -1)
            {
                int diff = second - aida_implant_scaler_cur_sec[hit.DSSD - 1];
                if (diff > 3600) {
                    aida_implant_scaler_queue[hit.DSSD - 1].clear();
                    aida_implant_stopped_scaler_queue[hit.DSSD - 1].clear();
                }
                else
                    while (diff-- > 1) {
                        aida_implant_scaler_queue[hit.DSSD - 1].push_front(0);
                        aida_implant_stopped_scaler_queue[hit.DSSD - 1].push_front(0);
                    }
            }
            aida_implant_scaler_queue[hit.DSSD - 1].push_front(1);
            aida_implant_stopped_scaler_queue[hit.DSSD - 1].push_front(hit.Stopped ? 1 : 0);
            while (aida_implant_scaler_queue[hit.DSSD - 1].size() > 3600)
                aida_implant_scaler_queue[hit.DSSD - 1].pop_back();
            while (aida_implant_stopped_scaler_queue[hit.DSSD - 1].size() > 3600)
                aida_implant_stopped_scaler_queue[hit.DSSD - 1].pop_back();
        }
        aida_implant_scaler_cur_sec[hit.DSSD - 1] = second;
    }

    bool decay_hredraw = false;
    for (auto const& hit : *decayHitArray)
    {
        h_decay_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
        h_decay_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        h_decay_e[hit.DSSD - 1]->Fill(hit.Energy);
        h_decay_e_xy[hit.DSSD - 1]->Fill(hit.EnergyX, hit.EnergyY);

        int second = (hit.Time / 1000000000ULL);
        if (second == aida_decay_scaler_cur_sec[hit.DSSD - 1])
        {
            aida_decay_scaler_queue[hit.DSSD - 1].front() += 1;
        }
        else
        {
            decay_hredraw = true;
            if (aida_decay_scaler_cur_sec[hit.DSSD - 1] != -1)
            {
                int diff = second - aida_decay_scaler_cur_sec[hit.DSSD - 1];
                if (diff > 3600)
                    aida_decay_scaler_queue[hit.DSSD - 1].clear();
                else
                    while (diff-- > 1) aida_decay_scaler_queue[hit.DSSD - 1].push_front(0);
            }
            aida_decay_scaler_queue[hit.DSSD - 1].push_front(1);
            while (aida_decay_scaler_queue[hit.DSSD - 1].size() > 3600) aida_decay_scaler_queue[hit.DSSD - 1].pop_back();
        }
        aida_decay_scaler_cur_sec[hit.DSSD - 1] = second;
    }

    for (auto const& event : *implantCalArray)
    {
        int offset = 0;
        if (event.Side() == conf->DSSD(event.DSSD() - 1).YSide)
            offset = conf->Wide() ? 386 : 128;
        h_implant_strip_1d_energy[event.DSSD() - 1]->Fill(event.Strip() + offset, event.Energy());

    }
    for (auto const& event : *decayCalArray)
    {
        int offset = 0;
        if (event.Side() == conf->DSSD(event.DSSD() - 1).YSide)
            offset = conf->Wide() ? 386 : 128;
        h_decay_strip_1d_energy[event.DSSD() - 1]->Fill(event.Strip() + offset, event.Energy());
    }

    // Scaler tracking
    bool hredraw = false;
    for (auto& sv : *scalerArray)
    {
        int i = sv.Fee();
        int second = (sv.Time() / 1000000000ULL);
        if (second == aida_scaler_cur_sec[i])
        {
            aida_scaler_queue[i].front() += 1;
        }
        else
        {
            hredraw = true;
            if (aida_scaler_cur_sec[i] != -1)
            {
                int diff = second - aida_scaler_cur_sec[i];
                if (diff > 3600)
                    aida_scaler_queue[i].clear();
                else
                    while (diff-- > 1) aida_scaler_queue[i].push_front(0);
            }
            aida_scaler_queue[i].push_front(1);
            while (aida_scaler_queue[i].size() > 3600) aida_scaler_queue[i].pop_back();
        }
        aida_scaler_cur_sec[i] = second;
    }

    if (hredraw)
    {
        for (auto scaler : conf->ScalerMap())
        {
            aida_scaler_graph[scaler.first]->Set(aida_scaler_queue[scaler.first].size());
            int i = 0;
            for (auto p : aida_scaler_queue[scaler.first])
            {
                aida_scaler_graph[scaler.first]->SetPoint(i, i, p);
                i++;
            }
        }
    }

    if (implant_hredraw)
    {
        for (int dssd = 0; dssd < conf->DSSDs(); dssd++)
        {
            aida_implant_scaler_graph[dssd]->Set(aida_implant_scaler_queue[dssd].size());
            int i = 0;
            for (auto p : aida_implant_scaler_queue[dssd])
            {
                aida_implant_scaler_graph[dssd]->SetPoint(i, i, p);
                i++;
            }
        }
    }
    if (decay_hredraw)
    {
        for (int dssd = 0; dssd < conf->DSSDs(); dssd++)
        {
            aida_decay_scaler_graph[dssd]->Set(aida_decay_scaler_queue[dssd].size());
            int i = 0;
            for (auto p : aida_decay_scaler_queue[dssd])
            {
                aida_decay_scaler_graph[dssd]->SetPoint(i, i, p);
                i++;
            }
        }
    }

    // AIDA DeadTime Calculation
    // When a RESUME happens after a PAUSE get an interval
    // Track current second (from something?)
    // Push 0s until buffer[0] is at current_second ?
    // Calcualte amount of 1s from START to interval 
    // Calculate number of 1s blocks
    // Calculate amount of 1s from interval to END
    // Fill all from current_time?
    fNEvents += 1;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void AidaNearlineSpectra::FinishEvent()
{
}

void AidaNearlineSpectra::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warn, "No events found, not saving histograms!");
        return;
    }
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_aida->Write();
    gDirectory = tmp;

    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
    
}

ClassImp(AidaNearlineSpectra)
