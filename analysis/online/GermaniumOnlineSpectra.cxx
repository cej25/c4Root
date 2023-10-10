// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumOnlineSpectra.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

GermaniumOnlineSpectra::GermaniumOnlineSpectra()
{
}

GermaniumOnlineSpectra::GermaniumOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

GermaniumOnlineSpectra::~GermaniumOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void GermaniumOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus GermaniumOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");

    //sum time spectrum
    cSumTime = new TCanvas("SumTime1", "Sum Time 1", 10, 10, 800, 700);
    fh1_SumTime = new TH1F("fh1_SumTime", "Sum time", 1000, 0, 1.55e13);
    fh1_SumTime->Draw("");


    //summed energy
    cEnergySpectraTest = new TCanvas("EnergySpectraTest","Energy uncal det 1",10,10,800,700);
    fh1_EnergySpectraTest = new TH1F("fh1_EnergySpectraTest","Energy uncal det 1", 10000, 0, 9e6);
    fh1_EnergySpectraTest->Draw("");

    //energy per detector:
    cEnergySpectra = new TCanvas("EnergySpectra","Uncalibrated energy spectra Germanium per detector",10,10,800,700);
    fh2_EnergySpectra = new TH2F("fh2_EnergySpectra", "Uncalibrated energy spectra Germanium per detector",10000,0,9e6,16,0,16);
    fh2_EnergySpectra->Draw("COLZ");
    
    //calibrated energy per detector:
    cCalEnergySpectra = new TCanvas("CalEnergySpectra","Calibrated energy spectra Germanium per detector",10,10,800,700);
    fh2_CalEnergySpectra = new TH2F("fh2_CalEnergySpectra", "Calibrated energy spectra Germanium per detector;energy (keV); channel id",10000,0,10e3,16,0,16);
    fh2_CalEnergySpectra->Draw("COLZ");
    
    TFolder *geFold = new TFolder("Germanium", "Germanium");
    geFold->Add(cSumTime);
    geFold->Add(cEnergySpectraTest);
    geFold->Add(cEnergySpectra);
    geFold->Add(cCalEnergySpectra);



    run->AddObject(geFold);

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    fh1_SumTime->Reset();
    fh1_EnergySpectraTest->Reset();
    fh2_EnergySpectra->Reset();
    fh2_CalEnergySpectra->Reset();
}

void GermaniumOnlineSpectra::Exec(Option_t* option)
{   
    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitGe->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            GermaniumCalData* hit = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit)
                continue;

            
            fh1_SumTime->Fill(hit->Get_event_trigger_time());
            fh2_EnergySpectra->Fill(hit->Get_channel_energy(),hit->Get_crystal_id());
            if (hit->Get_crystal_id() == 1) fh1_EnergySpectraTest->Fill(hit->Get_channel_energy());
            fh2_CalEnergySpectra->Fill(hit->Get_channel_energy(),hit->Get_crystal_id());

        }
    }

    fNEvents += 1;
}

void GermaniumOnlineSpectra::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
}

void GermaniumOnlineSpectra::FinishTask()
{
    if (fHitGe)
    {
        fh1_SumTime->Write();
        fh2_EnergySpectra->Write();
        fh1_EnergySpectraTest->Write();
        fh2_CalEnergySpectra->Write();
    }
}

ClassImp(GermaniumOnlineSpectra)