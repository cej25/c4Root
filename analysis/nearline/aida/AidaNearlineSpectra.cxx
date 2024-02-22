// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaNearlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AidaData.h"
#include "TAidaConfiguration.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <sstream>

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
    // ranges
{
}

AidaNearlineSpectra::~AidaNearlineSpectra()
{
    c4LOG(info, "");
    // do we delete pointers? we didn't create them
}

void AidaNearlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaNearlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    run->GetHttpServer()->RegisterCommand("Reset_Aida_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

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
    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

    // Create folders 
    aidaFolder = new TFolder("AIDA", "AIDA");
    run->AddObject(aidaFolder);

    implantFolder = new TFolder("Implants", "Implants");
    stoppedImplantFolder = new TFolder("Stopped_Implants", "Stopped Implants");
    decayFolder = new TFolder("Decays", "Decays");
    aidaFolder->Add(implantFolder);
    aidaFolder->Add(stoppedImplantFolder);
    aidaFolder->Add(decayFolder);

    int xstrips = conf->Wide() ? 386 : 128;
    double xmax = conf->Wide() ? 113.4 : 37.8;

    implantDssdFolder.resize(conf->DSSDs());
    stoppedImplantDssdFolder.resize(conf->DSSDs());
    decayDssdFolder.resize(conf->DSSDs());

    h2_implant_strip_xy.resize(conf->DSSDs());
    h2_implant_pos_xy.resize(conf->DSSDs());
    h1_implant_e.resize(conf->DSSDs());

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
        h2_implant_strip_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, 0, xstrips, 128, 0, 128);
        h2_implant_strip_xy[i]->GetXaxis()->SetTitle("X strip");
        h2_implant_strip_xy[i]->GetYaxis()->SetTitle("Y strip");
        implantDssdFolder[i]->Add(h2_implant_strip_xy[i]);

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_pos_xy";
        title << "DSSD " << (i + 1) << " implant position";
        h2_implant_pos_xy[i] = new TH2F(name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h2_implant_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h2_implant_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");
        implantDssdFolder[i]->Add(h2_implant_pos_xy[i]);

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_e";
        title << "DSSD " << (i + 1) << "implant energy";
        h1_implant_e[i] = new TH1F(name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h1_implant_e[i]->GetXaxis()->SetTitle("Implant Energy/MeV");
        implantDssdFolder[i]->Add(h1_implant_e[i]);
    }

    return kSUCCESS;
}

void AidaNearlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (auto& h : h2_implant_strip_xy) h->Clear();
}

void AidaNearlineSpectra::Exec(Option_t* option)
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
    for (auto const& hit : *decayHitArray)
    {
        h2_implant_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
        h2_implant_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        h1_implant_e[hit.DSSD - 1]->Fill(hit.Energy);
    }
    fNEvents += 1;
}

void AidaNearlineSpectra::FinishEvent()
{
}

void AidaNearlineSpectra::FinishTask()
{       
}

ClassImp(AidaNearlineSpectra)
