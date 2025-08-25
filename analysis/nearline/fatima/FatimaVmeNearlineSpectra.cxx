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
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaVmeNearlineSpectra.h"
#include "EventHeader.h"
#include "FatimaVmeCalData.h"
#include "TFatimaVmeConfiguration.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"
#include "AnalysisTools.h"

FatimaVmeNearlineSpectra::FatimaVmeNearlineSpectra()
    : FatimaVmeNearlineSpectra("FatimaVmeNearlineSpectra")
    {
        fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
    }

FatimaVmeNearlineSpectra::FatimaVmeNearlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   qdcCalArray(nullptr)
    ,   tdcCalArray(nullptr)
    ,   residualArray(nullptr)
{
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
}

FatimaVmeNearlineSpectra::~FatimaVmeNearlineSpectra()
{
    c4LOG(info, "");
    if (fHitFatimaVme) delete fHitFatimaVme;
}

InitStatus FatimaVmeNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();
    c4LOG_IF(fatal, NULL == run, "FairRunAna not found!");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    qdcCalArray = mgr->InitObjectAs<decltype(qdcCalArray)>("FatimaVmeQDCCalData");
    c4LOG_IF(fatal, !qdcCalArray, "Branch qdcCalArray not found!");
    tdcCalArray = mgr->InitObjectAs<decltype(tdcCalArray)>("FatimaVmeTDCCalData");
    c4LOG_IF(fatal, !tdcCalArray, "Branch tdcCalArray not found!");
    residualArray = mgr->InitObjectAs<decltype(residualArray)>("FatimaVmeResiduals");
    c4LOG_IF(fatal, !residualArray, "Branch FatimaVmeResiduals not found!");

    
    nDetectors = fatima_vme_config->NDetectors();

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fatima_vme = gDirectory->mkdir("FATIMA VME");
    gDirectory->cd("FATIMA VME");

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

    h1_FatVME_QDCMult = MakeTH1(dir_stats_vme, "I", "h1_FatVME_QDCMult", "Fatima VME QDC Multiplicity", nDetectors, 0, nDetectors, "Multiplicity", kRed-3, kBlack);
    h1_FatVME_TDCMult = MakeTH1(dir_stats_vme, "I", "h1_FatVME_TDCMult", "Fatime VME TDC Multiplicity", nDetectors, 0, nDetectors, "Multiplicity", kRed-3, kBlack);
    h1_FatVME_QDC_HitPattern = MakeTH1(dir_stats_vme, "I", "h1_FatVME_QDC_HitPattern", "Fatima VME QDC Hit Pattern", nDetectors, 0, nDetectors, "Detector", kRed-3, kBlack);
    h1_FatVME_TDC_HitPattern = MakeTH1(dir_stats_vme, "I", "h1_FatVME_TDC_HitPattern", "Fatima VME TDC Hit Pattern", nDetectors, 0, nDetectors, "Detector", kRed-3, kBlack);

    dir_raw_energy = dir_raw_vme->mkdir("Raw Energy");
    dir_cal_energy = dir_cal_vme->mkdir("Calibrated Energy");
    dir_raw_time = dir_raw_vme->mkdir("Raw Time");

    dir_raw_energy->cd();
    for (int i = 0; i < nDetectors; i++)
    {
        h1_FatVME_RawE[i] = MakeTH1(dir_raw_energy, "F", Form("h1_FatVme_RawE%i", i), Form("Fatima VME Raw Energy - Detector %i", i), 2e3, 0, 15e3, "Energy [a.u.]", kSpring, kBlue+2);
    }

    // dir_cal_energy->cd();
    for (int i = 0; i < nDetectors; i++)
    {
        h1_FatVME_E[i] = MakeTH1(dir_cal_energy, "F", Form("h1_FatVME_E%i", i), Form("Fatima VME Energy - Detector %i", i), 4000, 0, 4000, "Energy [keV]", kViolet+1, kBlue+2);
    }

    h1_FatVME_E_Sum = new TH1D("h1_FatVME_E_Sum", "Fatima VME Energy - All Detectors summed", 4000, 0, 4000);
    
    dir_raw_time->cd();
    for (int i = 0; i < nDetectors; i++)
    {
        h1_FatVME_RawT[i] = new TH1D(Form("h1_FatVme_RawT%i", i), Form("Fatima VME Raw Time - Detector %i", i), 5000, -1e6, 7e7);
    }

    dir_tdc_dt = dir_fatima_vme->mkdir("Time Differences");
    dir_dt_sc41 = dir_tdc_dt->mkdir("SC41L dT");
    dir_dt_ch1 = dir_tdc_dt->mkdir("Ch1 dT");

    dir_dt_sc41->cd();
    for (int i = 0; i < nDetectors; i++)
    {
        h1_FatVME_TDC_dT_refSC41L[i] = new TH1D(Form("h1_FatVME_TDC%i_dT_refSC41L", i), Form("Detector %i TDC dT ref. SC41L", i), 250, -2e4, 2e4);
    }

    for (int i = 0; i < nDetectors; i++)
    {
        h2_FatVME_EvsdTsc41[i] = new TH2D(Form("h2_FatVME_EvsdTsc41_%i", i), Form("E vs dT (det - sc41) Det %i", i), 250, -5e3, 2e4, 2000, 0, 4e4);
    }
    h2_FatVME_EvsdTsc41_summed = new TH2D("h2_FatVME_EvsdTsc41_summed", "E vs dT (det - sc41) Summed", 250,-5e3, 2e4, 2000, 0, 4e4);

    dir_dt_ch1->cd();
    for (int i = 0; i < nDetectors; i++)
    {
        h1_FatVME_TDC_dt_refCh1[i] = new TH1D(Form("h1_FatVME_TDC%i_dt_refCh1", i), Form("Detector %i TDC dT ref. Detector 1", i), 4e4, -2e4, 2e4);
    }
    
    dir_residuals->cd();
    h1_FatVME_time_machine_undelayed = new TH1D("h1_FatVME_time_machine_undelayed", "Time Machine Undelayed - FATIMA VME", 2000, 0, 40000);
    h1_FatVME_time_machine_delayed = new TH1D("h1_FatVME_time_machine_delayed", "Time Machine Delayed - FATIMA VME", 2000, 0, 40000);
    h1_FatVME_sc41l_time = new TH1D("h1_FatVME_sc41l_time", "SC41L T - FATIMA VME", 5000, -1e6, 2e6);
    h1_FatVME_sc41r_time = new TH1D("h1_FatVME_sc41r_time", "SC41R T - FATIMA VME", 5000, -1e6, 236);

    dir_fatima_vme->cd();

    return kSUCCESS;

}

void FatimaVmeNearlineSpectra::Exec(Option_t* option)
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


void FatimaVmeNearlineSpectra::FinishEvent()
{

}

void FatimaVmeNearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fatima_vme->Write();
    gDirectory = tmp;
    
}
