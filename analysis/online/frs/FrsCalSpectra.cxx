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
 *                             C.E. Jones                                     *
 *                              17.12.24                                      *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsCalSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TDirectory.h"

FrsCalSpectra::FrsCalSpectra()
    : FrsCalSpectra("FrsCalSpectra", 1)
{
}

FrsCalSpectra::FrsCalSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   calSciArray(nullptr)
    ,   calTpcArray(nullptr)
{
}

FrsCalSpectra::~FrsCalSpectra()
{
    c4LOG(info, "");
    
}

InitStatus FrsCalSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    calSciArray = mgr->InitObjectAs<decltype(calSciArray)>("FrsCalSciData");
    c4LOG_IF(fatal, !calSciArray, "Branch FrsCalSciData not found!");
    calTpcArray = mgr->InitObjectAs<decltype(calTpcArray)>("FrsCalTpcData");
    c4LOG_IF(fatal, !calTpcArray, "Branch FrsCalTpcData not found!");
    

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Online Directory";
        dir_frs = new TDirectory("FRS Online", "FRS Online", "", 0);
        mgr->Register("FRS", "FRS Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }

    dir_frs_cal = dir_frs->mkdir("FRS Cal Spectra");
    dir_cal_sci = dir_frs_cal->mkdir("Scintillators");
    dir_cal_tpc = dir_frs_cal->mkdir("TPCs");


    // ::: SCIs :::: 
    dir_sci_tac = dir_cal_sci->mkdir("TAC");
    dir_sci_tac_de = dir_sci_tac->mkdir("dE");
    dir_sci_tac_dt = dir_sci_tac->mkdir("dT");
    dir_sci_mhtdc = dir_cal_sci->mkdir("MHTDC");
    dir_sci_mhtdc_t = dir_sci_mhtdc->mkdir("T");
    dir_sci_mhtdc_dt = dir_sci_mhtdc->mkdir("dT");

    int sc_xx_bins = 1000;
    int sc_xx_max_e= 4096; //12 bit adc

    // TAC dE
    h1_sci_tac_de_21l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_21l", "SCI 21L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_21r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_21r", "SCI 21R dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_22l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_22l", "SCI 22L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_22r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_22r", "SCI 22R dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_31l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_31l", "SCI 31L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_31r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_31r", "SCI 31R dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_41l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_41l", "SCI 41L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_41r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_41r", "SCI 41R dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_42l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_42l", "SCI 42L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_42r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_42r", "SCI 42R dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_43l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_43l", "SCI 43L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_43r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_43r", "SCI 43R dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_81l = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_81l", "SCI 81L dE", sc_xx_bins, 0, sc_xx_max_e);
    h1_sci_tac_de_81r = MakeTH1(dir_sci_tac_de, "D", "h1_sci_tac_de_81r", "SCI 81R dE", sc_xx_bins, 0, sc_xx_max_e);

    int tac_bins = 1000;
    int max_tac_value = 5000;
    h1_sci_tac_dt_21l_21r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_21l_21r", "SCI 21L - 21R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_41l_41r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_41l_41r", "SCI 41L - 41R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_42l_42r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_42l_42r", "SCI 42L - 42R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_43l_43r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_43l_43r", "SCI 43L - 43R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_81l_81r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_81l_81r", "SCI 81L - 81R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_21l_41l = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_21l_41l", "SCI 21L - 41L dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_21r_41r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_21r_41r", "SCI 21R - 41R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_42r_21r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_42r_21r", "SCI 42R - 21R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_42l_21l = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_42l_21l", "SCI 42L - 21L dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_21l_81l = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_21l_81l", "SCI 21L - 81L dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_21r_81r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_21r_81r", "SCI 21R - 81R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_22l_22r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_22l_22r", "SCI 22L - 22R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_22l_41l = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_22l_41l", "SCI 22L - 41L dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_22r_41r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_22r_41r", "SCI 22R - 41R dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_22l_81l = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_22l_81l", "SCI 22L - 81L dT (TAC)", tac_bins, 0, max_tac_value);
    h1_sci_tac_dt_22r_81r = MakeTH1(dir_sci_tac_dt, "D", "h1_sci_tac_dt_22r_81r", "SCI 22R - 81R dT (TAC)", tac_bins, 0, max_tac_value);


    // ::: MHTDC T
    int sc_xx_bins_t = 1000;
    double sc_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h1_sci_mhtdc_t_21l = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_21l", "SCI 21l T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_21r = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_21r", "SCI 21r T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_22l = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_22l", "SCI 22l T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_22r = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_22r", "SCI 22r T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_41l = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_41l", "SCI 41l T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_41r = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_41r", "SCI 41r T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_42l = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_42l", "SCI 42l T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_42r = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_42r", "SCI 42r T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_43l = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_43l", "SCI 43l T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_43r = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_43r", "SCI 43r T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_81l = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_81l", "SCI 81l T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);
    h1_sci_mhtdc_t_81r = MakeTH1(dir_sci_mhtdc_t, "D", "h1_sci_mhtdc_t_81r", "SCI 81r T (MHTDC)", sc_xx_bins_t, 0, sc_xx_max_t);

    // ::: MHTDC dT 
    int sc_xx_bins_dt = 2000;
    h1_sci_mhtdc_dt_21l_21r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_21l_21r", "SCI 21L - 21R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_22l_22r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_22l_22r", "SCI 22L - 22R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_41l_41r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_41l_41r", "SCI 41L - 41R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42l_42r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42l_42r", "SCI 42L - 42R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_22l_21l = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_22l_21l", "SCI 22L - 21L dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_22r_21r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_22r_21r", "SCI 22R - 21R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_41l_21l = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_41l_21l", "SCI 41L - 21L dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_41r_21r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_41r_21r", "SCI 41R - 21R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42l_21l = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42l_21l", "SCI 42L - 21L dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42r_21r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42r_21r", "SCI 42R - 21R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_41l_22l = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_41l_22l", "SCI 41L - 22L dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_41r_22r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_41r_22r", "SCI 41R - 22R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42l_22l = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42l_22l", "SCI 42L - 22L dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42r_22r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42r_22r", "SCI 42R - 22R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42l_41l = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42l_41l", "SCI 42L - 41L dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    h1_sci_mhtdc_dt_42r_41r = MakeTH1(dir_sci_mhtdc_dt, "D", "h1_sci_mhtdc_dt_42r_41r", "SCI 42R - 41R dT (MHTDC)", sc_xx_bins_dt, -10000, 10000);
    

    // ::: TPCs :::::
    int check_sums_bins = 1000;
    int check_sums_max = 20000;
    h2_tpc_check_sums = MakeTH2(dir_cal_tpc, "D", "h2_tpc_check_sums","Check sums calculated for each anode (7 tpcs * 4 anodes)", number_of_anodes_per_tpc*number_of_tpcs,0,number_of_anodes_per_tpc*number_of_tpcs, check_sums_bins,0,check_sums_max);

    int tpc_min_x = -100;
    int tpc_min_y = -100;
    int tpc_max_x = 100;
    int tpc_max_y = 100;
    int tpc_min_angle = -3.14*100;
    int tpc_max_angle = 3.14*100;
    int tpc_bins = 100;
    h1_tpc_angle_x_s2_foc_21_22 = MakeTH1(dir_cal_tpc, "D", "h1_tpc_angle_x_s2_foc_21_22", "TPC h_tpc_angle_x_s2_foc_21_22", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_angle_y_s2_foc_21_22 = MakeTH1(dir_cal_tpc, "D", "h1_tpc_angle_y_s2_foc_21_22", "TPC h_tpc_angle_y_s2_foc_21_22", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_x_s2_foc_21_22 = MakeTH1(dir_cal_tpc, "D", "h1_tpc_x_s2_foc_21_22", "TPC h_tpc_x_s2_foc_21_22", tpc_bins, tpc_min_x,tpc_max_x);
    h1_tpc_y_s2_foc_21_22 = MakeTH1(dir_cal_tpc, "D", "h1_tpc_y_s2_foc_21_22", "TPC h_tpc_y_s2_foc_21_22", tpc_bins, tpc_min_y,tpc_max_y);
    h1_tpc21_22_sc21_x = MakeTH1(dir_cal_tpc, "D", "h1_tpc21_22_sc21_x", "TPC h_tpc21_22_sc21_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc21_22_sc22_x = MakeTH1(dir_cal_tpc, "D", "h1_tpc21_22_sc22_x", "TPC h_tpc21_22_sc22_x", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc_angle_x_s2_foc_23_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_angle_x_s2_foc_23_24", "TPC h_tpc_angle_x_s2_foc_23_24", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_angle_y_s2_foc_23_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_angle_y_s2_foc_23_24", "TPC h_tpc_angle_y_s2_foc_23_24", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_x_s2_foc_23_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_x_s2_foc_23_24", "TPC h_tpc_x_s2_foc_23_24", tpc_bins,tpc_min_x, tpc_max_x);
    h1_tpc_y_s2_foc_23_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_y_s2_foc_23_24", "TPC h_tpc_y_s2_foc_23_24", tpc_bins,tpc_min_y, tpc_max_y);
    h1_tpc23_24_sc21_x = MakeTH1(dir_cal_tpc, "D", "h_tpc23_24_sc21_x", "TPC h_tpc23_24_sc21_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc23_24_sc21_y = MakeTH1(dir_cal_tpc, "D", "h_tpc23_24_sc21_y", "TPC h_tpc23_24_sc21_y", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc23_24_sc22_x = MakeTH1(dir_cal_tpc, "D", "h_tpc23_24_sc22_x", "TPC h_tpc23_24_sc22_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc23_24_sc22_y = MakeTH1(dir_cal_tpc, "D", "h_tpc23_24_sc22_y", "TPC h_tpc23_24_sc22_y", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc_angle_x_s2_foc_22_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_angle_x_s2_foc_22_24", "TPC h_tpc_angle_x_s2_foc_22_24", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_angle_y_s2_foc_22_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_angle_y_s2_foc_22_24", "TPC h_tpc_angle_y_s2_foc_22_24", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_x_s2_foc_22_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_x_s2_foc_22_24", "TPC h_tpc_x_s2_foc_22_24", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc_y_s2_foc_22_24 = MakeTH1(dir_cal_tpc, "D", "h_tpc_y_s2_foc_22_24", "TPC h_tpc_y_s2_foc_22_24", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc_angle_x_s4 = MakeTH1(dir_cal_tpc, "D", "h_tpc_angle_x_s4", "TPC h_tpc_angle_x_s4", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_angle_y_s4 = MakeTH1(dir_cal_tpc, "D", "h_tpc_angle_y_s4", "TPC h_tpc_angle_y_s4", tpc_bins, tpc_min_angle, tpc_max_angle);
    h1_tpc_x_s4 = MakeTH1(dir_cal_tpc, "D", "h_tpc_x_s4", "TPC h_tpc_x_s4", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc_y_s4 = MakeTH1(dir_cal_tpc, "D", "h_tpc_y_s4", "TPC h_tpc_y_s4", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc_sc41_x = MakeTH1(dir_cal_tpc, "D", "h_tpc_sc41_x", "TPC h_tpc_sc41_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc_sc41_y = MakeTH1(dir_cal_tpc, "D", "h_tpc_sc41_y", "TPC h_tpc_sc41_y", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc_sc42_x = MakeTH1(dir_cal_tpc, "D", "h_tpc_sc42_x", "TPC h_tpc_sc42_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc_sc42_y = MakeTH1(dir_cal_tpc, "D", "h_tpc_sc42_y", "TPC h_tpc_sc42_y", tpc_bins, tpc_min_y, tpc_max_y);
    h1_tpc_sc43_x = MakeTH1(dir_cal_tpc, "D", "h_tpc_sc43_x", "TPC h_tpc_sc43_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc_music41_x = MakeTH1(dir_cal_tpc, "D", "h_tpc_music41_x", "TPC h_tpc_music41_x", tpc_bins, tpc_min_x, tpc_max_x);
    h1_tpc_music42_x = MakeTH1(dir_cal_tpc, "D", "h_tpc_music42_x", "TPC h_tpc_music42_x", tpc_bins, tpc_min_x, tpc_max_x);
    

    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsCalSpectra::Reset_Histo()
{
    c4LOG(info, "");
    // incoming
}

void FrsCalSpectra::Exec(Option_t* option)
{   
    if (calSciArray->size() == 0 || calTpcArray->size() == 0) return;
    
    auto const & calSciItem = calSciArray->at(0);
    UInt_t de_21l = calSciItem.Get_dE_21l();
    UInt_t de_21r = calSciItem.Get_dE_21r();
    UInt_t de_22l = calSciItem.Get_dE_22l();
    UInt_t de_22r = calSciItem.Get_dE_22r();
    UInt_t de_31l = calSciItem.Get_dE_31l();  
    UInt_t de_31r = calSciItem.Get_dE_31r();
    UInt_t de_41l = calSciItem.Get_dE_41l();
    UInt_t de_41r = calSciItem.Get_dE_41r(); 
    UInt_t de_42l = calSciItem.Get_dE_42l();
    UInt_t de_42r = calSciItem.Get_dE_42r();
    UInt_t de_43l = calSciItem.Get_dE_43l();  
    UInt_t de_43r = calSciItem.Get_dE_43r();
    UInt_t de_81l = calSciItem.Get_dE_81l();
    UInt_t de_81r = calSciItem.Get_dE_81r();

    h1_sci_tac_de_21l->Fill(de_21l);
    h1_sci_tac_de_21r->Fill(de_21r);
    h1_sci_tac_de_22l->Fill(de_22l);
    h1_sci_tac_de_22r->Fill(de_22r);
    h1_sci_tac_de_31l->Fill(de_31l);
    h1_sci_tac_de_31r->Fill(de_31r);
    h1_sci_tac_de_41l->Fill(de_41l);
    h1_sci_tac_de_41r->Fill(de_41r);
    h1_sci_tac_de_42l->Fill(de_42l);
    h1_sci_tac_de_42r->Fill(de_42r);
    h1_sci_tac_de_43l->Fill(de_43l);
    h1_sci_tac_de_43r->Fill(de_43r);
    h1_sci_tac_de_81l->Fill(de_81l);
    h1_sci_tac_de_81r->Fill(de_81r);

    UInt_t dt_21l_21r = calSciItem.Get_dT_21l_21r();
    h1_sci_tac_dt_21l_21r->Fill(dt_21l_21r);
    UInt_t dt_22l_22r = calSciItem.Get_dT_22l_22r();
    h1_sci_tac_dt_22l_22r->Fill(dt_22l_22r);
    UInt_t dt_41l_41r = calSciItem.Get_dT_41l_41r();
    h1_sci_tac_dt_41l_41r->Fill(dt_41l_41r);
    UInt_t dt_42l_42r = calSciItem.Get_dT_42l_42r();
    h1_sci_tac_dt_42l_42r->Fill(dt_42l_42r);
    UInt_t dt_43l_43r = calSciItem.Get_dT_43l_43r();
    h1_sci_tac_dt_43l_43r->Fill(dt_43l_43r);
    UInt_t dt_81l_81r = calSciItem.Get_dT_81l_81r();
    h1_sci_tac_dt_81l_81r->Fill(dt_81l_81r);
    UInt_t dt_21l_41l = calSciItem.Get_dT_21l_41l();
    h1_sci_tac_dt_21l_41l->Fill(dt_21l_41l);
    UInt_t dt_21r_41r = calSciItem.Get_dT_21r_41r();
    h1_sci_tac_dt_21r_41r->Fill(dt_21r_41r);
    UInt_t dt_42l_21l = calSciItem.Get_dT_42l_21l();
    h1_sci_tac_dt_42l_21l->Fill(dt_42l_21l);
    UInt_t dt_42r_21r = calSciItem.Get_dT_42r_21r();
    h1_sci_tac_dt_42r_21r->Fill(dt_42r_21r);
    UInt_t dt_21l_81l = calSciItem.Get_dT_21l_81l();
    h1_sci_tac_dt_21l_81l->Fill(dt_21l_81l);
    UInt_t dt_21r_81r = calSciItem.Get_dT_21r_81r();
    h1_sci_tac_dt_21r_81r->Fill(dt_21r_81r);
    UInt_t dt_22l_41l = calSciItem.Get_dT_22l_41l();
    h1_sci_tac_dt_22l_41l->Fill(dt_22l_41l);
    UInt_t dt_22r_41r = calSciItem.Get_dT_22r_41r();
    h1_sci_tac_dt_22r_41r->Fill(dt_22r_41r);
    UInt_t dt_22l_81l = calSciItem.Get_dT_22l_81l();
    h1_sci_tac_dt_22l_81l->Fill(dt_22l_81l);
    UInt_t dt_22r_81r = calSciItem.Get_dT_22r_81r();
    h1_sci_tac_dt_22r_81r->Fill(dt_22r_81r);

    // getting the first hit only: mapping to int32 signed is okay since the max value is 2^20:
    std::vector<Int_t> sci21l_times = calSciItem.Get_mhtdc_sci21l_hits();
    std::vector<Int_t> sci21r_times = calSciItem.Get_mhtdc_sci21r_hits();
    std::vector<Int_t> sci22l_times = calSciItem.Get_mhtdc_sci22l_hits();
    std::vector<Int_t> sci22r_times = calSciItem.Get_mhtdc_sci22r_hits();
    std::vector<Int_t> sci41l_times = calSciItem.Get_mhtdc_sci41l_hits();
    std::vector<Int_t> sci41r_times = calSciItem.Get_mhtdc_sci41r_hits();
    std::vector<Int_t> sci42l_times = calSciItem.Get_mhtdc_sci42l_hits();
    std::vector<Int_t> sci42r_times = calSciItem.Get_mhtdc_sci42r_hits();
    std::vector<Int_t> sci43l_times = calSciItem.Get_mhtdc_sci43l_hits();
    std::vector<Int_t> sci43r_times = calSciItem.Get_mhtdc_sci43r_hits();
    std::vector<Int_t> sci81l_times = calSciItem.Get_mhtdc_sci81l_hits();
    std::vector<Int_t> sci81r_times = calSciItem.Get_mhtdc_sci81r_hits();

    if (sci21l_times.size() > 0) h1_sci_mhtdc_t_21l->Fill(sci21l_times.at(0));
    if (sci21r_times.size() > 0) h1_sci_mhtdc_t_21r->Fill(sci21r_times.at(0));    
    if (sci22l_times.size() > 0) h1_sci_mhtdc_t_22l->Fill(sci22l_times.at(0));
    if (sci22r_times.size() > 0) h1_sci_mhtdc_t_22r->Fill(sci22r_times.at(0));
    if (sci41l_times.size() > 0) h1_sci_mhtdc_t_41l->Fill(sci41l_times.at(0));
    if (sci41r_times.size() > 0) h1_sci_mhtdc_t_41r->Fill(sci41r_times.at(0));
    if (sci42l_times.size() > 0) h1_sci_mhtdc_t_42l->Fill(sci42l_times.at(0));
    if (sci42r_times.size() > 0) h1_sci_mhtdc_t_42r->Fill(sci42r_times.at(0));
    if (sci43l_times.size() > 0) h1_sci_mhtdc_t_43l->Fill(sci43l_times.at(0));
    if (sci43r_times.size() > 0) h1_sci_mhtdc_t_43r->Fill(sci43r_times.at(0));
    if (sci81l_times.size() > 0) h1_sci_mhtdc_t_81l->Fill(sci81l_times.at(0));
    if (sci81r_times.size() > 0) h1_sci_mhtdc_t_81r->Fill(sci81r_times.at(0));

    if (sci21l_times.size() > 0 && sci21r_times.size() > 0) h1_sci_mhtdc_dt_21l_21r->Fill(sci21l_times.at(0) - sci21r_times.at(0));
    if (sci22l_times.size() > 0 && sci22r_times.size() > 0) h1_sci_mhtdc_dt_22l_22r->Fill(sci22l_times.at(0) - sci22r_times.at(0));
    if (sci41l_times.size() > 0 && sci41r_times.size() > 0) h1_sci_mhtdc_dt_41l_41r->Fill(sci41l_times.at(0) - sci41r_times.at(0));
    if (sci42l_times.size() > 0 && sci42r_times.size() > 0) h1_sci_mhtdc_dt_42l_42r->Fill(sci42l_times.at(0) - sci42r_times.at(0));
    if (sci22l_times.size() > 0 && sci21l_times.size() > 0) h1_sci_mhtdc_dt_22l_21l->Fill(sci22l_times.at(0) - sci21l_times.at(0));
    if (sci22r_times.size() > 0 && sci21r_times.size() > 0) h1_sci_mhtdc_dt_22r_21r->Fill(sci22r_times.at(0) - sci21r_times.at(0));
    if (sci41l_times.size() > 0 && sci21l_times.size() > 0) h1_sci_mhtdc_dt_41l_21l->Fill(sci41l_times.at(0) - sci21l_times.at(0));
    if (sci41r_times.size() > 0 && sci21r_times.size() > 0) h1_sci_mhtdc_dt_41r_21r->Fill(sci41r_times.at(0) - sci21r_times.at(0));
    if (sci42l_times.size() > 0 && sci21l_times.size() > 0) h1_sci_mhtdc_dt_42l_21l->Fill(sci42l_times.at(0) - sci21l_times.at(0));
    if (sci42r_times.size() > 0 && sci21r_times.size() > 0) h1_sci_mhtdc_dt_42r_21r->Fill(sci42r_times.at(0) - sci21r_times.at(0));
    if (sci41l_times.size() > 0 && sci22l_times.size() > 0) h1_sci_mhtdc_dt_41l_22l->Fill(sci41l_times.at(0) - sci22l_times.at(0));
    if (sci41r_times.size() > 0 && sci22r_times.size() > 0) h1_sci_mhtdc_dt_41r_22r->Fill(sci41r_times.at(0) - sci22r_times.at(0));
    if (sci42l_times.size() > 0 && sci22l_times.size() > 0) h1_sci_mhtdc_dt_42l_22l->Fill(sci42l_times.at(0) - sci22l_times.at(0));
    if (sci42r_times.size() > 0 && sci22r_times.size() > 0) h1_sci_mhtdc_dt_42r_22r->Fill(sci42r_times.at(0) - sci22r_times.at(0));
    if (sci42l_times.size() > 0 && sci41l_times.size() > 0) h1_sci_mhtdc_dt_42l_41l->Fill(sci42l_times.at(0) - sci41l_times.at(0));
    if (sci42r_times.size() > 0 && sci41r_times.size() > 0) h1_sci_mhtdc_dt_42r_41r->Fill(sci42r_times.at(0) - sci41r_times.at(0));
    
    auto const & calTpcItem = calTpcArray->at(0);
    const Int_t (*tpc_csum)[4] = calTpcItem.Get_tpc_csum();
    for (int an = 0; an < number_of_anodes_per_tpc; an++)
    {
        for (int ntpc = 0; ntpc < number_of_tpcs; ntpc++)
        {
            h2_tpc_check_sums->Fill(ntpc*number_of_anodes_per_tpc + an, tpc_csum[ntpc][an]);
        }
    }

    h1_tpc_angle_x_s2_foc_21_22->Fill(calTpcItem.Get_tpc_angle_x_s2_foc_21_22());
    h1_tpc_angle_y_s2_foc_21_22->Fill(calTpcItem.Get_tpc_angle_y_s2_foc_21_22());
    h1_tpc_x_s2_foc_21_22->Fill(calTpcItem.Get_tpc_x_s2_foc_21_22());
    h1_tpc_y_s2_foc_21_22->Fill(calTpcItem.Get_tpc_y_s2_foc_21_22());
    h1_tpc21_22_sc21_x->Fill(calTpcItem.Get_tpc21_22_sc21_x());
    h1_tpc21_22_sc22_x->Fill(calTpcItem.Get_tpc21_22_sc22_x());
    h1_tpc_angle_x_s2_foc_23_24->Fill(calTpcItem.Get_tpc_angle_x_s2_foc_23_24());
    h1_tpc_angle_y_s2_foc_23_24->Fill(calTpcItem.Get_tpc_angle_y_s2_foc_23_24());
    h1_tpc_x_s2_foc_23_24->Fill(calTpcItem.Get_tpc_x_s2_foc_23_24());
    h1_tpc_y_s2_foc_23_24->Fill(calTpcItem.Get_tpc_y_s2_foc_23_24());
    h1_tpc23_24_sc21_x->Fill(calTpcItem.Get_tpc23_24_sc21_x());
    h1_tpc23_24_sc21_y->Fill(calTpcItem.Get_tpc23_24_sc21_y());
    h1_tpc23_24_sc22_x->Fill(calTpcItem.Get_tpc23_24_sc22_x());
    h1_tpc23_24_sc22_y->Fill(calTpcItem.Get_tpc23_24_sc22_y());
    h1_tpc_angle_x_s2_foc_22_24->Fill(calTpcItem.Get_tpc_angle_x_s2_foc_22_24());
    h1_tpc_angle_y_s2_foc_22_24->Fill(calTpcItem.Get_tpc_angle_y_s2_foc_22_24());
    h1_tpc_x_s2_foc_22_24->Fill(calTpcItem.Get_tpc_x_s2_foc_22_24());
    h1_tpc_y_s2_foc_22_24->Fill(calTpcItem.Get_tpc_y_s2_foc_22_24());
    h1_tpc_angle_x_s4->Fill(calTpcItem.Get_tpc_angle_x_s4());
    h1_tpc_angle_y_s4->Fill(calTpcItem.Get_tpc_angle_y_s4());
    h1_tpc_x_s4->Fill(calTpcItem.Get_tpc_x_s4());
    h1_tpc_y_s4->Fill(calTpcItem.Get_tpc_y_s4());
    h1_tpc_sc41_x->Fill(calTpcItem.Get_tpc_sc41_x());
    h1_tpc_sc41_y->Fill(calTpcItem.Get_tpc_sc41_y());
    h1_tpc_sc42_x->Fill(calTpcItem.Get_tpc_sc42_x());
    h1_tpc_sc42_y->Fill(calTpcItem.Get_tpc_sc42_y());
    h1_tpc_sc43_x->Fill(calTpcItem.Get_tpc_sc43_x());
    h1_tpc_music41_x->Fill(calTpcItem.Get_tpc_music41_x());
    h1_tpc_music42_x->Fill(calTpcItem.Get_tpc_music42_x());

    fNEvents++;

}

void FrsCalSpectra::FinishEvent()
{
}

void FrsCalSpectra::FinishTask()
{
    
}

ClassImp(FrsCalSpectra)
