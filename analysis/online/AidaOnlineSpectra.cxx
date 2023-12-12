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
#include "AidaData.h"
#include "TAidaConfiguration.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <TDirectory.h>
#include <sstream>

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
    // ranges
{
}

AidaOnlineSpectra::~AidaOnlineSpectra()
{
    c4LOG(info, "");
    // do we delete pointers? we didn't create them
}

void AidaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    run->GetHttpServer()->RegisterCommand("Reset_Aida_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
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

    // Aida configuration
    conf = TAidaConfiguration::GetInstance();

    // Temporarily get rid of gDirectory
    TDirectory::TContext ctx(nullptr);

    // Create folders 
    aidaFolder = new TFolder("AIDA", "AIDA");
    run->AddObject(aidaFolder);

    implantFolder = new TFolder("Implants", "Implants");
    stoppedImplantFolder = new TFolder("Stopped_Implants", "Stopped Implants");
    decayFolder = new TFolder("Decays", "Decays");
    scalersFolder = new TFolder("Scalers", "Scalers");
    aidaFolder->Add(implantFolder);
    aidaFolder->Add(stoppedImplantFolder);
    aidaFolder->Add(decayFolder);
    aidaFolder->Add(scalersFolder);

    int xstrips = conf->Wide() ? 386 : 128;
    double xmax = conf->Wide() ? 113.4 : 37.8;

    implantDssdFolder.resize(conf->DSSDs());
    stoppedImplantDssdFolder.resize(conf->DSSDs());
    decayDssdFolder.resize(conf->DSSDs());

    h_implant_strip_xy.resize(conf->DSSDs());
    h_implant_pos_xy.resize(conf->DSSDs());
    h_implant_e.resize(conf->DSSDs());
    h_implant_e_xy.resize(conf->DSSDs());
    h_implant_strip_1d_energy.resize(conf->DSSDs());
    h_decay_strip_xy.resize(conf->DSSDs());
    h_decay_pos_xy.resize(conf->DSSDs());
    h_decay_e.resize(conf->DSSDs());
    h_decay_e_xy.resize(conf->DSSDs());
    h_decay_strip_1d_energy.resize(conf->DSSDs());

    for (int i = 0; i < conf->DSSDs(); i++)
    {
        std::stringstream name;
        std::stringstream title;
        name << "DSSD" << (i + 1);
        implantDssdFolder[i] = new TFolder(name.str().c_str(), name.str().c_str());
        implantDssdFolder[i]->SetOwner(true);
        implantFolder->Add(implantDssdFolder[i]);
        stoppedImplantDssdFolder[i] = new TFolder(name.str().c_str(), name.str().c_str());
        stoppedImplantFolder->Add(stoppedImplantDssdFolder[i]);
        decayDssdFolder[i] = new TFolder(name.str().c_str(), name.str().c_str());
        decayFolder->Add(decayDssdFolder[i]);

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_strip_xy";
        title << "DSSD " << (i + 1) << " implant hit pattern";
        h_implant_strip_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, 0, xstrips, 128, 0, 128);
        h_implant_strip_xy[i]->GetXaxis()->SetTitle("X strip");
        h_implant_strip_xy[i]->GetYaxis()->SetTitle("Y strip");
        implantDssdFolder[i]->Add(h_implant_strip_xy[i]);

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_pos_xy";
        title << "DSSD " << (i + 1) << " implant position";
        h_implant_pos_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h_implant_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h_implant_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");
        implantDssdFolder[i]->Add(h_implant_pos_xy[i]);

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_e";
        title << "DSSD " << (i + 1) << " implant energy";
        h_implant_e[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h_implant_e[i]->GetXaxis()->SetTitle("Implant Energy/MeV");
        implantDssdFolder[i]->Add(h_implant_e[i]);

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_e_xy";
        title << "DSSD " << (i + 1) << " implant energy X vs energy Y";
        h_implant_e_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000, 2000, 0, 20000);
        h_implant_e_xy[i]->GetXaxis()->SetTitle("Implant X Energy/MeV");
        h_implant_e_xy[i]->GetYaxis()->SetTitle("Implant Y Energy/MeV");
        implantDssdFolder[i]->Add(h_implant_e_xy[i]);

        // TODO move outof implants as it's not FB matched?
        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_strip_1d_energy";
        title << "DSSD " << (i + 1) << " 1D strip vs energy";
        h_implant_strip_1d_energy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                128 + xstrips, 0, 128 + xstrips, 2000, 0, 20000);
        h_implant_strip_1d_energy[i]->GetXaxis()->SetTitle("Strip (X then Y");
        h_implant_strip_1d_energy[i]->GetYaxis()->SetTitle("Implant Energy/MeV");
        implantDssdFolder[i]->Add(h_implant_strip_1d_energy[i]);

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_strip_xy";
        title << "DSSD " << (i + 1) << " decay hit pattern";
        h_decay_strip_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, 0, xstrips, 128, 0, 128);
        h_decay_strip_xy[i]->GetXaxis()->SetTitle("X strip");
        h_decay_strip_xy[i]->GetYaxis()->SetTitle("Y strip");
        decayDssdFolder[i]->Add(h_decay_strip_xy[i]);

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_pos_xy";
        title << "DSSD " << (i + 1) << " decay position";
        h_decay_pos_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h_decay_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h_decay_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");
        decayDssdFolder[i]->Add(h_decay_pos_xy[i]);

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_e";
        title << "DSSD " << (i + 1) << " decay energy";
        h_decay_e[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h_decay_e[i]->GetXaxis()->SetTitle("Decay Energy/MeV");
        decayDssdFolder[i]->Add(h_decay_e[i]);

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_e_xy";
        title << "DSSD " << (i + 1) << " decay energy X vs energy Y";
        h_decay_e_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000, 2000, 0, 20000);
        h_decay_e_xy[i]->GetXaxis()->SetTitle("Decay X Energy/MeV");
        h_decay_e_xy[i]->GetYaxis()->SetTitle("Decay Y Energy/MeV");
        decayDssdFolder[i]->Add(h_decay_e_xy[i]);

        // TODO move outof decays as it's not FB matched?
        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_strip_1d_energy";
        title << "DSSD " << (i + 1) << " 1D strip vs energy";
        h_decay_strip_1d_energy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                128 + xstrips, 0, 128 + xstrips, 2000, 0, 20000);
        h_decay_strip_1d_energy[i]->GetXaxis()->SetTitle("Strip (X then Y");
        h_decay_strip_1d_energy[i]->GetYaxis()->SetTitle("Decay Energy/MeV");
        decayDssdFolder[i]->Add(h_decay_strip_1d_energy[i]);
    }

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

        scalersFolder->Add(aida_scaler_graph[scaler.first]);
    }

    return kSUCCESS;
}

void AidaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (auto& h : h_implant_strip_xy) h->Reset();
    for (auto& h : h_implant_pos_xy) h->Reset();
    for (auto& h : h_implant_e) h->Reset();
    for (auto& h : h_implant_e_xy) h->Reset();
    for (auto& h : h_implant_strip_xy) h->Reset();

    for (auto& h : h_decay_strip_xy) h->Reset();
    for (auto& h : h_decay_pos_xy) h->Reset();
    for (auto& h : h_decay_e) h->Reset();
    for (auto& h : h_decay_e_xy) h->Reset();
    for (auto& h : h_decay_strip_1d_energy) h->Reset();
}

void AidaOnlineSpectra::Reset_Scalers()
{
    c4LOG(info, "");
    for (auto& scaler : conf->ScalerMap())
    {
        aida_scaler_queue[scaler.first].clear();
        aida_scaler_cur_sec[scaler.first] = -1;
    }
}

void AidaOnlineSpectra::Exec(Option_t* option)
{
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
    for (auto const& hit : *implantHitArray)
    {
        h_implant_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
        h_implant_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        h_implant_e[hit.DSSD - 1]->Fill(hit.Energy);
        h_implant_e_xy[hit.DSSD - 1]->Fill(hit.EnergyX, hit.EnergyY);
    }
    for (auto const& hit : *decayHitArray)
    {
        h_decay_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
        h_decay_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        h_decay_e[hit.DSSD - 1]->Fill(hit.Energy);
        h_decay_e_xy[hit.DSSD - 1]->Fill(hit.EnergyX, hit.EnergyY);
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
    fNEvents += 1;
}

void AidaOnlineSpectra::FinishEvent()
{
}

void AidaOnlineSpectra::FinishTask()
{
}

ClassImp(AidaOnlineSpectra)
