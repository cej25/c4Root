// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaOnlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"

// ROOT
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <cmath>
#include <sstream>
#include "TFile.h"
#include <chrono>

AidaOnlineSpectra::AidaOnlineSpectra() : AidaOnlineSpectra("AidaOnline")
{
}

AidaOnlineSpectra::AidaOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , adcArray(nullptr)
    , flowArray(nullptr)
    , scalerArray(nullptr)
    , implantHitArray(nullptr)
    , header(nullptr)
    , fNEvents(0)
{
}

AidaOnlineSpectra::~AidaOnlineSpectra()
{
    c4LOG(info, "Destroyed AidaOnlineSpectra properly.");
    
}

void AidaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    run->GetHttpServer()->RegisterCommand("Reset_Aida_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Aida_Hist", Form("/Objects/%s/->Snapshot_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Reset_Aida_Scalers", Form("/Objects/%s/->Reset_Scalers()", GetName()));

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

    histograms = (TFolder*)mgr->GetObject("Histograms");

    // Temporarily get rid of gDirectory
    TDirectory::TContext ctx(nullptr);

    dir_aida = new TDirectory("AIDA", "AIDA", "", 0);
    //mgr->Register("AIDA", "AIDA", dir_aida, false); // allow other tasks to find directory
    histograms->Add(dir_aida);

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
    h_aida_frontback_time.resize(conf->DSSDs());
    aida_implant_scaler_queue.resize(conf->DSSDs());
    aida_implant_scaler_cur_sec.resize(conf->DSSDs());
    aida_implant_scaler_graph.resize(conf->DSSDs());
    aida_implant_stopped_scaler_queue.resize(conf->DSSDs());
    aida_implant_stopped_scaler_graph.resize(conf->DSSDs());
    aida_decay_scaler_queue.resize(conf->DSSDs());
    aida_decay_scaler_cur_sec.resize(conf->DSSDs());
    aida_decay_scaler_graph.resize(conf->DSSDs());
    deadtime_queue.resize(conf->FEEs());
    deadtime_pos.resize(conf->FEEs());
    last_pauses.resize(conf->FEEs());
    deadtime_graph.resize(conf->FEEs());

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

        name.str("");
        title.str("");
        name << "aida_frontback_time_d" << (i + 1);
        title << "DSSD " << (i + 1) << " front-back time";
        h_aida_frontback_time[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                1000, -1e4, 1e4);
        h_aida_frontback_time[i]->GetXaxis()->SetTitle("Front-back time/ns");


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

    for (int i = 0; i < conf->FEEs(); i++)
    {
        std::stringstream name;
        std::stringstream title;
        deadtime_graph[i] = new TGraph(3600);
        name.str(""); title.str("");
        name << "aida_deadtime_f" << (i + 1);
        title << "AIDA FEE " << (i+ 1) << " Dead Time";
        title << ";Time before now (s);Dead Time(%)";
        deadtime_graph[i]->SetName(name.str().c_str());
        deadtime_graph[i]->SetTitle(title.str().c_str());
        deadtime_graph[i]->SetMinimum(0);
        dir_scalers->Append(deadtime_graph[i]);
        deadtime_pos[i] = -1;
        last_pauses[i] = 0;
    }

    dir_aida->cd();

    return kSUCCESS;
}

void AidaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting AIDA histograms.");
    //implants
    for (auto& h : h_implant_strip_xy) h->Reset();
    for (auto& h : h_implant_pos_xy) h->Reset();
    for (auto& h : h_implant_e) h->Reset();
    for (auto& h : h_implant_e_xy) h->Reset();
    for (auto& h : h_implant_strip_1d_energy) h->Reset();
    for (auto& h : h_implant_x_ex) h->Reset();
    // for (auto& h : h_implant_y_ey) h->Reset();
    // for (auto& h : h_implant_time_delta) h->Reset();

    // stopped implants
    for (auto& h : h_implant_strip_xy_stopped) h->Reset();
    for (auto& h : h_implant_pos_xy_stopped) h->Reset();
    for (auto& h : h_implant_e_stopped) h->Reset();
    for (auto& h : h_implant_x_ex_stopped) h->Reset();

    //decays
    for (auto& h : h_decay_strip_xy) h->Reset();
    for (auto& h : h_decay_pos_xy) h->Reset();
    for (auto& h : h_decay_e) h->Reset();
    for (auto& h : h_decay_e_xy) h->Reset();
    for (auto& h : h_decay_strip_1d_energy) h->Reset();
    // for (auto& h : h_decay_time_delta) h->Reset();
    c4LOG(info, "AIDA histograms reset.");
    
}

void AidaOnlineSpectra::Snapshot_Histo()
{
    c4LOG(info, "Snapshotting AIDA histograms.");

    //date and timestamp
    time_t now = time(0);
    tm *ltm = localtime(&now);
    const char* snapshot_dir = Form("AIDA_Snapshots_%d_%02d_%02d_%02d_%02d_%02d",
            1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->mkdir(screenshot_path, true);
    gSystem->mkdir(snapshot_dir, true);
    gSystem->cd(snapshot_dir);

    //save histograms for implants
    c_aida_snapshots = new TCanvas("c", "c", 1000, 1000);

    for(int i = 0; i < conf->DSSDs(); i++)
    {
        //implants
        h_implant_strip_xy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_strip_xy.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_pos_xy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_pos_xy.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_e[i]->Draw();
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_e.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_e_xy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_e_xy.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_strip_1d_energy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_strip_1d_energy.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_x_ex[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_x_ex.png", i + 1));
        c_aida_snapshots->Clear();
        // h_implant_y_ey[i]->Draw("COLZ");
        // c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_y_ey.png", i + 1));
        // c_aida_snapshots->Clear();
        // h_implant_time_delta[i]->Draw();
        // c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_time_delta.png", i + 1));
        // c_aida_snapshots->Clear();

        //stopped implants
        h_implant_strip_xy_stopped[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_strip_xy_stopped.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_pos_xy_stopped[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_pos_xy_stopped.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_e_stopped[i]->Draw();
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_e_stopped.png", i + 1));
        c_aida_snapshots->Clear();
        h_implant_x_ex_stopped[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_implants_DSSD_%d_implants_x_ex_stopped.png", i + 1));
        c_aida_snapshots->Clear();

        //decays
        h_decay_strip_xy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_decays_DSSD_%d_decays_strip_xy.png", i + 1));
        c_aida_snapshots->Clear();
        h_decay_pos_xy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_decays_DSSD_%d_decays_pos_xy.png", i + 1));
        c_aida_snapshots->Clear();
        h_decay_e[i]->Draw();
        c_aida_snapshots->SaveAs(Form("aida_decays_DSSD_%d_decays_e.png", i + 1));
        c_aida_snapshots->Clear();
        h_decay_e_xy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_decays_DSSD_%d_decays_e_xy.png", i + 1));
        c_aida_snapshots->Clear();
        h_decay_strip_1d_energy[i]->Draw("COLZ");
        c_aida_snapshots->SaveAs(Form("aida_decays_DSSD_%d_decays_strip_1d_energy.png", i + 1));
        c_aida_snapshots->Clear();
        // h_decay_time_delta[i]->Draw();
        // c_aida_snapshots->SaveAs(Form("aida_decays_DSSD_%d_decays_time_delta.png", i + 1));
        // c_aida_snapshots->Clear();
    }


    //save scalers
    for (auto& scaler : conf->ScalerMap())
    {
        aida_scaler_graph[scaler.first]->Draw("ALP");
        c_aida_snapshots->SaveAs(Form("aida_scalers#%d.png",scaler.first));
        c_aida_snapshots->Clear();
    }

    delete c_aida_snapshots;

    // commented for now. I cannot implement the snapshot from the directory.
    // // snapshot .root file with date and time
    // file_aida_snapshot = new TFile(Form("AIDA_snapshot_%d_%d_%d_%d_%d_%d.root", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec), "RECREATE");
    // file_aida_snapshot->cd();
    // dir_aida->Write();
    // file_aida_snapshot->Close();
    // delete file_aida_snapshot;

    // gSystem->cd("..");
    c4LOG(info, "AIDA snapshot saved in:" << snapshot_dir);

}

void AidaOnlineSpectra::Reset_Scalers()
{
    c4LOG(info, "Resetting AIDA scalers.");
    for (auto& scaler : conf->ScalerMap())
    {
        aida_scaler_queue[scaler.first].clear();
        aida_scaler_cur_sec[scaler.first] = -1;
    }
    for (int i = 0; i < conf->DSSDs(); i++)
    {
        aida_implant_scaler_queue[i].clear();
        aida_implant_scaler_cur_sec[i] = -1;
        aida_implant_stopped_scaler_queue[i].clear();
        aida_decay_scaler_queue[i].clear();
        aida_decay_scaler_cur_sec[i] = -1;
    }
    c4LOG(info, "AIDA scalers reset.");
}

void AidaOnlineSpectra::Exec(Option_t* option)
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
        // hacky/stupid BB7 stuff for now
        if (hit.DSSD > conf->DSSDs())
        {
            continue;
        }



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

        int dt = hit.FastTimeX - hit.FastTimeY;

        h_aida_frontback_time[hit.DSSD - 1]->Fill(dt);

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
        // hacky/stupid BB7 stuff for now
        if (hit.DSSD > conf->DSSDs())
        {
            continue;
        }

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
        // hacky/stupid BB7 stuff for now
        if (event.DSSD() > conf->DSSDs())
        {
            continue;
        }


        int offset = 0;
        if (event.Side() == conf->DSSD(event.DSSD() - 1).YSide)
            offset = conf->Wide() ? 386 : 128;
        h_implant_strip_1d_energy[event.DSSD() - 1]->Fill(event.Strip() + offset, event.Energy());

    }
    for (auto const& event : *decayCalArray)
    {
        // hacky/stupid BB7 stuff for now
        if (event.DSSD() > conf->DSSDs())
        {
            continue;
        }

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
    //
    // Decay time from DSSD0 as the deadtime second
    hredraw = false;
    uint64_t deadtime_wr = aida_decay_scaler_cur_sec[0];
    uint64_t deadtime_bins = deadtime_wr / 1;
    for (int i = 0; i < conf->FEEs(); i++)
    {
        if (deadtime_pos[i] != deadtime_bins)
        {
            hredraw = true;
            double value = last_pauses[i] ? 1 : 0;
            if (deadtime_pos[i] != -1)
            {
                int diff = deadtime_wr - deadtime_pos[i];
                if (diff > 3600)
                {
                    deadtime_queue[i].clear();
                }
                else
                {
                    while (diff-- > 1) deadtime_queue[i].push_front(value);
                }
            }
            deadtime_queue[i].push_front(value);
            while (deadtime_queue[i].size() > 3600) deadtime_queue[i].pop_back();
            deadtime_pos[i] = deadtime_bins;
        }
    }
    for (auto& pr : *flowArray)
    {
        if (pr.Paused())
        {
            last_pauses[pr.Fee() - 1] = pr.Time();
            uint64_t ns_left = pr.Time() - (deadtime_bins * 1e9);
            double frac_left = 1 - (ns_left / 1e9);
            deadtime_queue[pr.Fee() - 1].front() = frac_left;
        }
        else
        {
            if (last_pauses[pr.Fee() - 1] == 0) continue;

            int64_t deadtime = pr.Time() - last_pauses[pr.Fee() - 1];
            int64_t pausebin = last_pauses[pr.Fee() - 1] / 1e9;
            int64_t resbin = pr.Time() / 1e9;
            if (pausebin == resbin)
            {
                deadtime_queue[pr.Fee() - 1].front() = ((double)deadtime / 1e9);
            }
            else
            {
                int64_t ns_left = pr.Time() - (deadtime_bins * 1e9);
                double frac_left = (ns_left / 1e9);
                deadtime_queue[pr.Fee() - 1].front() = frac_left;
            }
            last_pauses[pr.Fee() - 1] = 0;
        }
    }
    if (hredraw)
    {
        for (int i = 0; i < conf->FEEs(); i++)
        {
            deadtime_graph[i]->Set(deadtime_queue[i].size());
            int j = 0;
            for (auto p : deadtime_queue[i])
            {
                deadtime_graph[i]->SetPoint(j, j, p * 100.0);
                j++;
            }
        }
    }
    fNEvents += 1;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void AidaOnlineSpectra::FinishEvent()
{
}

void AidaOnlineSpectra::FinishTask()
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
    
}

ClassImp(AidaOnlineSpectra)
