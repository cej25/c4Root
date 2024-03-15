// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaVmeOnlineSpectra.h"
#include "EventHeader.h"
#include "FatimaVmeCalData.h"
#include "TFatimaVmeConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include "TDirectory.h"

FatimaVmeOnlineSpectra::FatimaVmeOnlineSpectra()
{
}

FatimaVmeOnlineSpectra::FatimaVmeOnlineSpectra(TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fHitFatimaVme(NULL)
    ,   fNEvents(0)
    ,   header(nullptr)
{

}

FatimaVmeOnlineSpectra::~FatimaVmeOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitFatimaVme) delete fHitFatimaVme;
}

// par containers

InitStatus FatimaVmeOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaVme = (TClonesArray*)mgr->GetObject("FatimaVmeCalData");
    c4LOG_IF(fatal, !fHitFatimaVme, "Branch FatimaVmeCalData not found!");

    TFatimaVmeConfiguration const* fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
    int num_detectors = fatima_vme_config->NDetectors();

    TDirectory::TContext ctx(nullptr);

    folder_fatima_vme = new TFolder("Fatima VME", "Fatima VME");

    run->AddObject(folder_fatima_vme);

    folder_stats_vme = new TFolder("Stats", "Stats");
    folder_raw_vme = new TFolder("Raw Spectra", "Raw Spectra");
    folder_cal_vme = new TFolder("Calibrated Spectra", "Calibrated Spectra");
    folder_fatima_vme->Add(folder_stats_vme);
    folder_fatima_vme->Add(folder_raw_vme);
    folder_fatima_vme->Add(folder_cal_vme);


    h1_FatVME_QDCMult = new TH1I("h1_FatVME_QDCMult", "Fatima VME QDC Multiplicity", num_detectors, 0, num_detectors);
    h1_FatVME_TDCMult = new TH1I("h1_FatVME_TDCMult", "Fatime VME TDC Multiplicity", num_detectors, 0, num_detectors);
    h1_FatVME_QDC_HitPattern = new TH1I("h1_FatVME_QDC_HitPattern", "Fatima VME QDC Hit Pattern", num_detectors, 0, num_detectors);
    h1_FatVME_TDC_HitPattern = new TH1I("h1_FatVME_QDC_HitPattern", "Fatima VME TDC Hit Pattern", num_detectors, 0, num_detectors);
    folder_stats_vme->Add(h1_FatVME_QDCMult);
    folder_stats_vme->Add(h1_FatVME_TDCMult);
    folder_stats_vme->Add(h1_FatVME_QDC_HitPattern);
    folder_stats_vme->Add(h1_FatVME_TDC_HitPattern);

    folder_raw_energy = new TFolder("Raw Energy", "Raw Energy");
    folder_cal_energy = new TFolder("Calibrated Energy", "Calibrated Energy");
    folder_raw_time = new TFolder("Raw Time", "Raw Time");
    folder_cal_time = new TFolder("Calibrated Time", "Calibrated Time");
    folder_raw_vme->Add(folder_raw_energy);
    folder_raw_vme->Add(folder_raw_time);
    folder_cal_vme->Add(folder_cal_energy);
    folder_cal_vme->Add(folder_cal_time);

    c_FatVME_RawE = new TCanvas("c_FatVME_RawE","Fatima VME Raw Energies", 650, 350);
    c_FatVME_RawE->Divide(4, num_detectors / 4);
    for (int i = 0; i < num_detectors; i++)
    {
        c_FatVME_RawE->cd(i+1);
        h1_FatVME_RawE[i] = new TH1D(Form("h1_FatVme_RawE%i", i), Form("Fatima VME Raw Energy - Detector %i", i), 2000, 0, 40000);
        h1_FatVME_RawE[i]->Draw();
        folder_raw_energy->Add(h1_FatVME_RawE[i]);
    }
    c_FatVME_RawE->cd(0);
    folder_raw_energy->Add(c_FatVME_RawE);

    c_FatVME_E = new TCanvas("c_FatVME_E", "Fatima VME Calibrated Energies", 650, 350);
    c_FatVME_E->Divide(4, num_detectors / 4);
    for (int i = 0; i < num_detectors; i++)
    {
        c_FatVME_E->cd(i+1);
        h1_FatVME_E[i] = new TH1D(Form("h1_FatVME_E%i", i), Form("Fatima VME Energy - Detector %i", i), 4000, 0, 4000);
        h1_FatVME_E[i]->Draw();
        folder_cal_energy->Add(h1_FatVME_E[i]);
    }
    c_FatVME_E->cd(0);
    folder_cal_energy->Add(c_FatVME_E);
    
    c_FatVME_RawT = new TCanvas("c_FatVME_RawT", "Fatima VME Raw Time", 650, 350);
    c_FatVME_RawT->Divide(4, num_detectors / 4);
    for (int i = 0; i < num_detectors; i++)
    {
        c_FatVME_RawT->cd(i+1);
        h1_FatVME_RawT[i] = new TH1D(Form("h1_FatVme_RawT%i", i), Form("Fatima VME Raw Time - Detector %i", i), 5000, -1e6, 7e7);
        h1_FatVME_RawT[i]->Draw();
        folder_raw_time->Add(h1_FatVME_RawT[i]);
    }
    c_FatVME_RawT->cd(0);
    folder_raw_time->Add(c_FatVME_RawT);

    run->GetHttpServer()->RegisterCommand("Reset_Histo", "/Objects/%s/->Reset_Histo()", GetName());
    run->GetHttpServer()->RegisterCommand("Snapshot_Histo", "/Objects/%s/->Snapshot_Histo()", GetName());
    
    return kSUCCESS;

}

void FatimaVmeOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting Fatima VME Histograms");
}

void FatimaVmeOnlineSpectra::Snapshot_Histo()
{
    c4LOG(info, "Snapshotting Fatima VME Histograms");

    c4LOG(info, "Snapshots saved in: ");
}

void FatimaVmeOnlineSpectra::Exec(Option_t* option)
{
    if (fHitFatimaVme && fHitFatimaVme->GetEntriesFast())
    {
        Int_t nHits = fHitFatimaVme->GetEntriesFast();
        std::cout << "nHits: " << nHits << std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FatimaVmeCalData* FatimaVmeHit = (FatimaVmeCalData*)fHitFatimaVme->At(ihit);
            if (!FatimaVmeHit) continue;

            std::vector<uint32_t> QDC_IDs = FatimaVmeHit->Get_Singles_QDC_ID();
            std::vector<uint32_t> QDC_E_raw = FatimaVmeHit->Get_Singles_E_raw();
            std::vector<uint32_t> QDC_E = FatimaVmeHit->Get_Singles_E();

            h1_FatVME_QDCMult->Fill(QDC_IDs.size());
            for (int i = 0; i < QDC_IDs.size(); i++)
            {
                h1_FatVME_RawE[QDC_IDs[i]]->Fill(QDC_E_raw[i]);
                h1_FatVME_E[QDC_IDs[i]]->Fill(QDC_E[i]);
            }
            
            std::vector<uint32_t> TDC_IDs = FatimaVmeHit->Get_Singles_TDC_ID();
            std::vector<uint32_t> TDC_timestamp = FatimaVmeHit->Get_Singles_TDC_timestamp();

            h1_FatVME_TDCMult->Fill(TDC_IDs.size());
            for (int i = 0; i < TDC_IDs.size(); i++)
            {
                h1_FatVME_RawT[TDC_IDs[i]]->Fill(TDC_timestamp[i] * 25); // time in [ps]
            }
        }
    }
}

void FatimaVmeOnlineSpectra::FinishEvent()
{

}

void FatimaVmeOnlineSpectra::FinishTask()
{
   folder_fatima_vme->Write();
}
