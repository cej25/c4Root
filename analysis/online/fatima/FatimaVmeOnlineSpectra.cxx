// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaVmeOnlineSpectra.h"
#include "EventHeader.h"
#include "TFatimaVmeConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

FatimaVmeOnlineSpectra::FatimaVmeOnlineSpectra() 
    : FatimaVmeOnlineSpectra("FatimaVmeOnlineSpectra")
    {
        fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
    }

FatimaVmeOnlineSpectra::FatimaVmeOnlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   qdcCalArray(nullptr)
    ,   tdcCalArray(nullptr)
    ,   residualArray(nullptr)
{
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
}

FatimaVmeOnlineSpectra::~FatimaVmeOnlineSpectra()
{
    c4LOG(info, "");
}

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

    qdcCalArray = mgr->InitObjectAs<decltype(qdcCalArray)>("FatimaVmeQDCCalData");
    c4LOG_IF(fatal, !qdcCalArray, "Branch qdcCalArray not found!");
    tdcCalArray = mgr->InitObjectAs<decltype(tdcCalArray)>("FatimaVmeTDCCalData");
    c4LOG_IF(fatal, !tdcCalArray, "Branch tdcCalArray not found!");
    residualArray = mgr->InitObjectAs<decltype(residualArray)>("FatimaVmeResiduals");
    c4LOG_IF(fatal, !residualArray, "Branch FatimaVmeResiduals not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    // Configuration
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
    nDetectors = fatima_vme_config->NDetectors();

    TDirectory::TContext ctx(nullptr);

    dir_fatima_vme = new TDirectory("Fatima VME", "Fatima VME", "", 0);
    //mgr->Register("Fatima VME", "Fatima VME Directory", dir_fatima_vme, false); // allows other tasks to access directory.
    histograms->Add(dir_fatima_vme);

    dir_stats_vme = dir_fatima_vme->mkdir("Stats");
    dir_raw_vme = dir_fatima_vme->mkdir("Raw Spectra");
    dir_cal_vme = dir_fatima_vme->mkdir("Calibrated Spectra");
    dir_residuals = dir_fatima_vme->mkdir("Residual Signals");


    // Setting histogram sizes
    h1_FatVME_RawE.resize(nDetectors);
    h1_FatVME_E.resize(nDetectors);
    h1_FatVME_RawT.resize(nDetectors);
    h1_FatVME_TDC_dt_refCh1.resize(nDetectors);
    h1_FatVME_TDC_dT_refSC41L.resize(nDetectors);
    h2_FatVME_EvsdTsc41.resize(nDetectors);

    dir_stats_vme->cd();
    h1_FatVME_QDCMult = new TH1I("h1_FatVME_QDCMult", "Fatima VME QDC Multiplicity", nDetectors, 0, nDetectors);
    h1_FatVME_TDCMult = new TH1I("h1_FatVME_TDCMult", "Fatime VME TDC Multiplicity", nDetectors, 0, nDetectors);
    h1_FatVME_QDC_HitPattern = new TH1I("h1_FatVME_QDC_HitPattern", "Fatima VME QDC Hit Pattern", nDetectors, 0, nDetectors);
    h1_FatVME_TDC_HitPattern = new TH1I("h1_FatVME_TDC_HitPattern", "Fatima VME TDC Hit Pattern", nDetectors, 0, nDetectors);

    dir_raw_energy = dir_raw_vme->mkdir("Raw Energy");
    dir_cal_energy = dir_cal_vme->mkdir("Calibrated Energy");
    dir_raw_time = dir_raw_vme->mkdir("Raw Time");

    dir_raw_energy->cd();
    c_FatVME_RawE = new TCanvas("c_FatVME_RawE","Fatima VME Raw Energies", 650, 350);
    c_FatVME_RawE->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_RawE->cd(i+1);
        h1_FatVME_RawE[i] = new TH1D(Form("h1_FatVme_RawE%i", i), Form("Fatima VME Raw Energy - Detector %i", i), 2000, 0, 40000);
        h1_FatVME_RawE[i]->Draw();
    }
    c_FatVME_RawE->cd(0);
    dir_raw_energy->Append(c_FatVME_RawE);

    dir_cal_energy->cd();
    c_FatVME_E = new TCanvas("c_FatVME_E", "Fatima VME Calibrated Energies", 650, 350);
    c_FatVME_E->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_E->cd(i+1);
        h1_FatVME_E[i] = new TH1D(Form("h1_FatVME_E%i", i), Form("Fatima VME Energy - Detector %i", i), 4000, 0, 4000);
        h1_FatVME_E[i]->Draw();
    }
    c_FatVME_E->cd(0);
    dir_cal_energy->Append(c_FatVME_E);

    h1_FatVME_E_Sum = new TH1D("h1_FatVME_E_Sum", "Fatima VME Energy - All Detectors summed", 4000, 0, 4000);
    
    dir_raw_time->cd();
    c_FatVME_RawT = new TCanvas("c_FatVME_RawT", "Fatima VME Raw Time", 650, 350);
    c_FatVME_RawT->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_RawT->cd(i+1);
        h1_FatVME_RawT[i] = new TH1D(Form("h1_FatVme_RawT%i", i), Form("Fatima VME Raw Time - Detector %i", i), 5000, -1e6, 7e7);
        h1_FatVME_RawT[i]->Draw();
    }
    c_FatVME_RawT->cd(0);
    dir_raw_time->Append(c_FatVME_RawT);

    dir_tdc_dt = dir_fatima_vme->mkdir("Time Differences");
    dir_dt_sc41 = dir_tdc_dt->mkdir("SC41L dT");
    dir_dt_ch1 = dir_tdc_dt->mkdir("Ch1 dT");

    dir_dt_sc41->cd();
    c_FatVME_dTrefSC41 = new TCanvas("c_FatVME_dTrefSC41", "Fatima VME T - SC41L dT", 650, 350);
    c_FatVME_dTrefSC41->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_dTrefSC41->cd(i+1);
        h1_FatVME_TDC_dT_refSC41L[i] = new TH1D(Form("h1_FatVME_TDC%i_dT_refSC41L", i), Form("Detector %i TDC dT ref. SC41L", i), 250, -2e4, 2e4);
        h1_FatVME_TDC_dT_refSC41L[i]->Draw();
    }
    c_FatVME_dTrefSC41->cd(0);
    dir_dt_sc41->Append(c_FatVME_dTrefSC41);

    c_FatVME_EvsdTsc41 = new TCanvas("c_FatVME_EvsdTsc41", "E vs dT (det - sc41)", 650, 350);
    c_FatVME_EvsdTsc41->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_EvsdTsc41->cd(i+1);
        h2_FatVME_EvsdTsc41[i] = new TH2D(Form("h2_FatVME_EvsdTsc41_%i", i), Form("E vs dT (det - sc41) Det %i", i), 250, -5e3, 2e4, 2000, 0, 4e4);
        h2_FatVME_EvsdTsc41[i]->Draw("COLZ");
    }
    c_FatVME_EvsdTsc41->cd(0);
    dir_dt_sc41->Append(c_FatVME_EvsdTsc41);
    h2_FatVME_EvsdTsc41_summed = new TH2D("h2_FatVME_EvsdTsc41_summed", "E vs dT (det - sc41) Summed", 250,-5e3, 2e4, 2000, 0, 4e4);

    dir_dt_ch1->cd();
    c_FatVME_dTrefCh1 = new TCanvas("c_FatVME_dTrefCh1", "Fatima VME T - Ch1 T dT", 650, 350);
    c_FatVME_dTrefCh1->Divide(4, nDetectors / 4);
    for (int i = 0; i < nDetectors; i++)
    {
        c_FatVME_dTrefCh1->cd(i+1);
        h1_FatVME_TDC_dt_refCh1[i] = new TH1D(Form("h1_FatVME_TDC%i_dt_refCh1", i), Form("Detector %i TDC dT ref. Detector 1", i), 4e4, -2e4, 2e4);
        h1_FatVME_TDC_dt_refCh1[i]->Draw();
    }
    c_FatVME_dTrefCh1->cd(0);
    dir_dt_ch1->Append(c_FatVME_dTrefCh1);
    
    dir_residuals->cd();
    h1_FatVME_time_machine_undelayed = new TH1D("h1_FatVME_time_machine_undelayed", "Time Machine Undelayed - FATIMA VME", 2000, 0, 40000);
    h1_FatVME_time_machine_delayed = new TH1D("h1_FatVME_time_machine_delayed", "Time Machine Delayed - FATIMA VME", 2000, 0, 40000);
    h1_FatVME_sc41l_time = new TH1D("h1_FatVME_sc41l_time", "SC41L T - FATIMA VME", 5000, -1e6, 2e6);
    h1_FatVME_sc41r_time = new TH1D("h1_FatVME_sc41r_time", "SC41R T - FATIMA VME", 5000, -1e6, 236);

    dir_fatima_vme->cd();

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
    //h1_FatVME_sc41l->Reset();
    //h1_FatVME_sc41r->Reset();
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
    dir_fatima_vme->Write();
    file_fatima_vme_snapshot->Close();

    gSystem->cd("..");
    c4LOG(info, "Snapshots saved in: " << snapshot_dir);
}

void FatimaVmeOnlineSpectra::Exec(Option_t* option)
{
    int qdc_mult = 0;
    for (auto const & qdcItem : *qdcCalArray)
    {   
        int det = qdcItem.Get_detector();
        int energy = qdcItem.Get_qlong();
        int energy_raw = qdcItem.Get_qlong_raw();

        h1_FatVME_RawE[det]->Fill(energy_raw);
        h1_FatVME_E[det]->Fill(energy);
        h1_FatVME_QDC_HitPattern->Fill(det);
        h1_FatVME_E_Sum->Fill(energy);

        qdc_mult++;

    }
    // fill qdc_mult
    h1_FatVME_QDCMult->Fill(qdc_mult);

    int tdc_mult = 0;
    for (auto const & tdcItem : *tdcCalArray)
    {   
        int det = tdcItem.Get_detector();
        double timestamp = tdcItem.Get_timestamp();
        
        h1_FatVME_RawT[det]->Fill(timestamp * 25); // time in [ps]
        h1_FatVME_TDC_HitPattern->Fill(det);

        tdc_mult++;
    }
    // fill tdc_mult
    h1_FatVME_TDCMult->Fill(tdc_mult);

    
    for (auto const & residualItem : *residualArray)
    {
        double ts_sc41l = residualItem.Get_SC41L();
        double ts_sc41r = residualItem.Get_SC41R();
        double ts_tmu = residualItem.Get_TM_Undelayed();
        double ts_tmd = residualItem.Get_TM_Delayed();

        if (ts_tmu > 0) h1_FatVME_time_machine_undelayed->Fill(ts_tmu);
        if (ts_tmd > 0) h1_FatVME_time_machine_delayed->Fill(ts_tmd);
        if (ts_sc41l > 0) h1_FatVME_sc41l_time->Fill(ts_sc41l);
        if (ts_sc41r > 0) h1_FatVME_sc41l_time->Fill(ts_sc41r);

    } 

    // CEJ: Maybe this is something I forgot .. 
    /*for (int j = 0; j < SC41L_Hits.size(); j++)
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
                }*/
    
}

void FatimaVmeOnlineSpectra::FinishEvent()
{

}

void FatimaVmeOnlineSpectra::FinishTask()
{
    
}
