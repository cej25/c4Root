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
    : FatimaVmeOnlineSpectra("FatimaVmeOnlineSpectra")
    {
        fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
    }

FatimaVmeOnlineSpectra::FatimaVmeOnlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fHitFatimaVme(NULL)
    ,   fNEvents(0)
    ,   header(nullptr)
{
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
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

    // Configuration
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
    nDetectors = fatima_vme_config->NDetectors();

    TDirectory::TContext ctx(nullptr);

    folder_fatima_vme = new TFolder("Fatima VME", "Fatima VME");

    run->AddObject(folder_fatima_vme);

    folder_stats_vme = new TFolder("Stats", "Stats");
    folder_raw_vme = new TFolder("Raw Spectra", "Raw Spectra");
    folder_cal_vme = new TFolder("Calibrated Spectra", "Calibrated Spectra");
    folder_fatima_vme->Add(folder_stats_vme);
    folder_fatima_vme->Add(folder_raw_vme);
    folder_fatima_vme->Add(folder_cal_vme);


    // Setting histogram sizes
    h1_FatVME_RawE.resize(nDetectors+1);
    h1_FatVME_E.resize(nDetectors+1);
    h1_FatVME_RawT.resize(nDetectors+1);
    h1_FatVME_TDC_dt_refCh1.resize(nDetectors+1);
    h1_FatVME_TDC_dT_refSC41L.resize(nDetectors+1);

    h1_FatVME_QDCMult = new TH1I("h1_FatVME_QDCMult", "Fatima VME QDC Multiplicity", nDetectors, 0, nDetectors);
    h1_FatVME_TDCMult = new TH1I("h1_FatVME_TDCMult", "Fatime VME TDC Multiplicity", nDetectors, 0, nDetectors);
    h1_FatVME_QDC_HitPattern = new TH1I("h1_FatVME_QDC_HitPattern", "Fatima VME QDC Hit Pattern", nDetectors, 0, nDetectors);
    h1_FatVME_TDC_HitPattern = new TH1I("h1_FatVME_TDC_HitPattern", "Fatima VME TDC Hit Pattern", nDetectors, 0, nDetectors);
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
    c_FatVME_RawE->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_RawE->cd(i+1);
        h1_FatVME_RawE[i] = new TH1D(Form("h1_FatVme_RawE%i", i), Form("Fatima VME Raw Energy - Detector %i", i), 2000, 0, 40000);
        h1_FatVME_RawE[i]->Draw();
        folder_raw_energy->Add(h1_FatVME_RawE[i]);
    }

    c_FatVME_RawE->cd(0);
    folder_raw_energy->Add(c_FatVME_RawE);

    c_FatVME_E = new TCanvas("c_FatVME_E", "Fatima VME Calibrated Energies", 650, 350);
    c_FatVME_E->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {

        c_FatVME_E->cd(i+1);
        h1_FatVME_E[i] = new TH1D(Form("h1_FatVME_E%i", i), Form("Fatima VME Energy - Detector %i", i), 4000, 0, 4000);
        h1_FatVME_E[i]->Draw();
        folder_cal_energy->Add(h1_FatVME_E[i]);
    }
    c_FatVME_E->cd(0);
    folder_cal_energy->Add(c_FatVME_E);

    h1_FatVME_E_Sum = new TH1D("h1_FatVME_E_Sum", "Fatima VME Energy - All Detectors summed", 4000, 0, 4000);
    folder_cal_energy->Add(h1_FatVME_E_Sum);
    
    c_FatVME_RawT = new TCanvas("c_FatVME_RawT", "Fatima VME Raw Time", 650, 350);
    c_FatVME_RawT->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_RawT->cd(i+1);
        h1_FatVME_RawT[i] = new TH1D(Form("h1_FatVme_RawT%i", i), Form("Fatima VME Raw Time - Detector %i", i), 5000, -1e6, 7e7);
        h1_FatVME_RawT[i]->Draw();
        folder_raw_time->Add(h1_FatVME_RawT[i]);
    }
    c_FatVME_RawT->cd(0);
    folder_raw_time->Add(c_FatVME_RawT);

    folder_tdc_dt = new TFolder("Time Differences", "Time Differences");
    folder_cal_vme->Add(folder_tdc_dt);
    folder_dt_sc41 = new TFolder("SC41L dT", "SC41L dT");
    folder_dt_ch1 = new TFolder("Ch1 dT", "Ch1 dT");
    folder_tdc_dt->Add(folder_dt_sc41);
    folder_tdc_dt->Add(folder_dt_ch1);

    c_FatVME_dTrefSC41 = new TCanvas("c_FatVME_dTrefSC41", "Fatima VME T - SC41L dT", 650, 350);
    c_FatVME_dTrefSC41->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_dTrefSC41->cd(i+1);
        h1_FatVME_TDC_dT_refSC41L[i] = new TH1D(Form("h1_FatVME_TDC%i_dT_refSC41L", i), Form("Detector %i TDC dT ref. SC41L", i), 250, -2e4, 2e4);
        h1_FatVME_TDC_dT_refSC41L[i]->Draw();
        folder_dt_sc41->Add(h1_FatVME_TDC_dT_refSC41L[i]);
        
    }
    c_FatVME_dTrefSC41->cd(0);
    folder_dt_sc41->Add(c_FatVME_dTrefSC41);

    c_FatVME_dTrefCh1 = new TCanvas("c_FatVME_dTrefCh1", "Fatima VME T - Ch1 T dT", 650, 350);
    c_FatVME_dTrefCh1->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_dTrefCh1->cd(i+1);
        h1_FatVME_TDC_dt_refCh1[i] = new TH1D(Form("h1_FatVME_TDC%i_dt_refCh1", i), Form("Detector %i TDC dT ref. Detector 1", i), 4e4, -2e4, 2e4);
        h1_FatVME_TDC_dt_refCh1[i]->Draw();
        folder_dt_ch1->Add(h1_FatVME_TDC_dt_refCh1[i]);
    }
    c_FatVME_dTrefCh1->cd(0);
    folder_dt_ch1->Add(c_FatVME_dTrefCh1);
    
    // energy spectrum
    h1_FatVME_time_machine_undelayed = new TH1D("h1_FatVME_time_machine_undelayed", "Time Machine Undelayed - FATIMA VME", 2000, 0, 40000);
    h1_FatVME_time_machine_delayed = new TH1D("h1_FatVME_time_machine_delayed", "Time Machine Delayed - FATIMA VME", 2000, 0, 40000);
    folder_fatima_vme->Add(h1_FatVME_time_machine_undelayed);
    folder_fatima_vme->Add(h1_FatVME_time_machine_delayed);
    
    h1_FatVME_sc41l = new TH1D("h1_FatVME_sc41l", "SC41L E - FATIMA VME", 2000, 0, 40000);
    h1_FatVME_sc41r = new TH1D("h1_FatVME_sc41r", "SC41R E - FATIMA VME", 2000, 0, 40000);
    folder_fatima_vme->Add(h1_FatVME_sc41l);
    folder_fatima_vme->Add(h1_FatVME_sc41r);
    h1_FatVME_sc41l_time = new TH1D("h1_FatVME_sc41l_time", "SC41L T - FATIMA VME", 5000, -1e6, 7e7);
    h1_FatVME_sc41r_time = new TH1D("h1_FatVME_sc41r_time", "SC41R T - FATIMA VME", 5000, -1e6, 7e7);
    folder_fatima_vme->Add(h1_FatVME_sc41l_time);
    folder_fatima_vme->Add(h1_FatVME_sc41r_time);

    run->GetHttpServer()->RegisterCommand("Reset_FATIMA_VME_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_FATIMA_VME_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));
    
    return kSUCCESS;

}

void FatimaVmeOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting FATIMA VME Histograms");

    for (int i = 0; i < nDetectors; i++) h1_FatVME_RawE[i]->Reset();
    for (int i = 0; i < nDetectors; i++) h1_FatVME_E[i]->Reset();
    for (int i = 0; i < nDetectors; i++) h1_FatVME_RawT[i]->Reset();
    for (int i = 0; i < nDetectors; i++) h1_FatVME_TDC_dt_refCh1[i]->Reset();
    for (int i = 0; i < nDetectors; i++) h1_FatVME_TDC_dT_refSC41L[i]->Reset();

    h1_FatVME_E_Sum->Reset();
    h1_FatVME_QDC_HitPattern->Reset();
    h1_FatVME_TDC_HitPattern->Reset();
    h1_FatVME_QDCMult->Reset();
    h1_FatVME_TDCMult->Reset();
    h1_FatVME_time_machine_undelayed->Reset();
    h1_FatVME_time_machine_delayed->Reset();
    h1_FatVME_sc41l->Reset();
    h1_FatVME_sc41r->Reset();
    h1_FatVME_sc41l_time->Reset();
    h1_FatVME_sc41r_time->Reset();
    c4LOG(info, "FATIMA VME Histograms reset");
}

void FatimaVmeOnlineSpectra::Snapshot_Histo()
{
    c4LOG(info, "Snapshotting Fatima VME Histograms");

    time_t now = time(0);
    tm *ltm = localtime(&now);

    TString snapshot_dir = Form("FatimaVme_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);

    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    c_fatima_vme_snapshot = new TCanvas("c_fatima_vme_snapshot", "Fatima VME snapshot", 650, 350);

    for (int i = 0; i < nDetectors; i++)
    {
        if (h1_FatVME_RawE[i]->GetEntries() != 0)
        {
            h1_FatVME_RawE[i]->Draw();
            c_fatima_vme_snapshot->SaveAs(Form("h1_FatVME_RawE%i.png", i));
            c_fatima_vme_snapshot->Clear();
        }
        if (h1_FatVME_E[i]->GetEntries() != 0)
        {
            h1_FatVME_E[i]->Draw();
            c_fatima_vme_snapshot->SaveAs(Form("h1_FatVME_E%i.png", i));
            c_fatima_vme_snapshot->Clear();
        }
        if (h1_FatVME_RawT[i]->GetEntries() != 0)
        {
            h1_FatVME_RawT[i]->Draw();
            c_fatima_vme_snapshot->SaveAs(Form("h1_FatVME_RawT%i.png", i));
            c_fatima_vme_snapshot->Clear();
        }
        if (h1_FatVME_TDC_dt_refCh1[i]->GetEntries() != 0)
        {
            h1_FatVME_TDC_dt_refCh1[i]->Draw();
            c_fatima_vme_snapshot->SaveAs(Form("h1_FatVME_TDC%i_dt_refCh1.png", i));
            c_fatima_vme_snapshot->Clear();
        }
        if (h1_FatVME_TDC_dT_refSC41L[i]->GetEntries() != 0)
        {
            h1_FatVME_TDC_dT_refSC41L[i]->Draw();
            c_fatima_vme_snapshot->SaveAs(Form("h1_FatVME_TDC%i_dT_refSC41L.png", i));
            c_fatima_vme_snapshot->Clear();
        }
    }

    delete c_fatima_vme_snapshot;

    file_fatima_vme_snapshot = new TFile(Form("FatimaVme_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec));
    file_fatima_vme_snapshot->cd();
    folder_fatima_vme->Write();
    file_fatima_vme_snapshot->Close();

    gSystem->cd("..");
    c4LOG(info, "Snapshots saved in: " << snapshot_dir);
}

void FatimaVmeOnlineSpectra::Exec(Option_t* option)
{
    if (fHitFatimaVme && fHitFatimaVme->GetEntriesFast())
    {
        Int_t nHits = fHitFatimaVme->GetEntriesFast();
        
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FatimaVmeCalData* FatimaVmeHit = (FatimaVmeCalData*)fHitFatimaVme->At(ihit);
            if (!FatimaVmeHit) continue;

            std::vector<uint32_t> QDC_IDs = FatimaVmeHit->Get_Singles_QDC_ID();
            std::vector<uint32_t> QDC_E_raw = FatimaVmeHit->Get_Singles_E_raw();
            std::vector<uint32_t> QDC_E = FatimaVmeHit->Get_Singles_E();

            h1_FatVME_QDCMult->Fill((int)QDC_IDs.size());
            for (int i = 0; i < QDC_IDs.size(); i++)
            {
                h1_FatVME_RawE[QDC_IDs[i]]->Fill(QDC_E_raw[i]);
                h1_FatVME_E[QDC_IDs[i]]->Fill(QDC_E[i]);
                h1_FatVME_QDC_HitPattern->Fill(QDC_IDs[i]);
                h1_FatVME_E_Sum->Fill(QDC_E[i]);
            }
            
            std::vector<uint32_t> TDC_IDs = FatimaVmeHit->Get_Singles_TDC_ID();
            std::vector<uint32_t> TDC_timestamp = FatimaVmeHit->Get_Singles_TDC_timestamp();
            std::vector<uint32_t> TDC_timestamp_raw = FatimaVmeHit->Get_Singles_TDC_timestamp_raw();
            std::vector<uint32_t> SC41L_Hits = FatimaVmeHit->Get_SC41L_hits();
            std::vector<uint32_t> SC41R_Hits = FatimaVmeHit->Get_SC41R_hits(); // for plotting if wanted?
            
            std::vector<uint32_t> SC41L_E_Hits = FatimaVmeHit->Get_SC41L_E_hits();
            std::vector<uint32_t> SC41R_E_Hits = FatimaVmeHit->Get_SC41R_E_hits();
            std::vector<uint32_t> TM_Undelayed_E_Hits = FatimaVmeHit->Get_TM_undelayed_E_hits();
            std::vector<uint32_t> TM_Delayed_E_Hits = FatimaVmeHit->Get_TM_delayed_E_hits();

            h1_FatVME_TDCMult->Fill(TDC_IDs.size());
            for (int i = 0; i < TDC_IDs.size(); i++)
            {
                h1_FatVME_RawT[TDC_IDs[i]]->Fill(TDC_timestamp[i] * 25); // time in [ps]
                h1_FatVME_TDC_HitPattern->Fill(TDC_IDs[i]);

                for (int j = 0; j < SC41L_Hits.size(); j++)
                {
                    double dt = SC41L_Hits[j] - TDC_timestamp[i];
                    if (dt != 0) h1_FatVME_TDC_dT_refSC41L[TDC_IDs[i]]->Fill(dt);
                }

                if (TDC_IDs[i] == 1 && TDC_timestamp[i] != 0)
                {
                    double t1 = TDC_timestamp[i];
                    for (int j = 0; j < TDC_IDs.size(); j++)
                    {
                        if (i != j)
                        {
                            double t2 = TDC_timestamp[j];
                            double dt = t2 - t1;
                            if (dt != 0) h1_FatVME_TDC_dt_refCh1[TDC_IDs[j]]->Fill(dt);
                        }
                    }
                }
            }

            // add loop for reference channel(s)
            
            
            // special channels
            for (int i = 0; i < TM_Undelayed_E_Hits.size(); i++)
            {
                h1_FatVME_time_machine_undelayed->Fill(TM_Undelayed_E_Hits[i]);
            }
            for (int i = 0; i < TM_Delayed_E_Hits.size(); i++)
            {
                h1_FatVME_time_machine_delayed->Fill(TM_Delayed_E_Hits[i]);
            }
            for (int i = 0; i < SC41L_E_Hits.size(); i++)
            {
                h1_FatVME_sc41l->Fill(SC41L_E_Hits[i]);
            }
            for (int i = 0; i < SC41R_E_Hits.size(); i++)
            {
                h1_FatVME_sc41r->Fill(SC41R_E_Hits[i]);
            }
            for (int i = 0; i < SC41L_Hits.size(); i++)
            {
                h1_FatVME_sc41l_time->Fill(SC41L_Hits[i]);
            }
            for (int i = 0; i < SC41R_Hits.size(); i++)
            {
                h1_FatVME_sc41r_time->Fill(SC41R_Hits[i]);
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
