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
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "c4Logger.h"

#include "TClonesArray.h"

#include "FatimaVmeRaw2Cal.h"
#include "TFatimaVmeConfiguration.h"

#define FAT_VME_MAX_HITS 51

FatimaVmeRaw2Cal::FatimaVmeRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   funcal_data(new TClonesArray("FatimaVmeData"))
    ,   fcal_data(new TClonesArray("FatimaVmeCalData"))
    ,   fTimeMachineArray(new TClonesArray("TimeMachineData"))
    ,   qdcArray(nullptr)
    ,   tdcArray(nullptr)
    ,   qdcCalArray(new std::vector<FatimaVmeQDCCalItem>)
    ,   tdcCalArray(new std::vector<FatimaVmeTDCCalItem>)
    ,   residualArray(new std::vector<FatimaVmeResiduals>)
{
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
}

// named constructor
FatimaVmeRaw2Cal::FatimaVmeRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   funcal_data(new TClonesArray("FatimaVmeData"))
    ,   fcal_data(new TClonesArray("FatimaVmeCalData"))
    ,   fTimeMachineArray(new TClonesArray("TimeMachineData"))
    ,   qdcArray(nullptr)
    ,   tdcArray(nullptr)
    ,   qdcCalArray(new std::vector<FatimaVmeQDCCalItem>)
    ,   tdcCalArray(new std::vector<FatimaVmeTDCCalItem>)
    ,   residualArray(new std::vector<FatimaVmeResiduals>)
{
    fatima_vme_config = TFatimaVmeConfiguration::GetInstance();
}

FatimaVmeRaw2Cal::~FatimaVmeRaw2Cal()
{
    c4LOG(info, "Deleting FatimaVmeRaw2Cal task");

    if (qdcCalArray) delete qdcCalArray;
    if (tdcCalArray) delete tdcCalArray;
    if (residualArray) delete residualArray;

    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
    
}

InitStatus FatimaVmeRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("FatimaVmeData");
    c4LOG_IF(fatal, !funcal_data, "Fatima branch of FatimaVmeData not found!");

    mgr->Register("FatimaVmeCalData", "FatimaVmeCalDataFolder", fcal_data, !fOnline);
    mgr->Register("FatimaVmeTimeMachineData", "FatimaVmeTimeMachineDataFolder", fTimeMachineArray, !fOnline);

    qdcArray = mgr->InitObjectAs<decltype(qdcArray)>("FatimaVmeQDCData");
    c4LOG_IF(fatal, !qdcArray, "Branch qdcArray not found!");

    tdcArray = mgr->InitObjectAs<decltype(tdcArray)>("FatimaVmeTDCData");
    c4LOG_IF(fatal, !tdcArray, "Branch tdcArray not found!");

    mgr->RegisterAny("FatimaVmeQDCCalData", qdcCalArray, !fOnline);
    mgr->RegisterAny("FatimaVmeTDCCalData", tdcCalArray, !fOnline);
    mgr->RegisterAny("FatimaVmeResiduals", residualArray, !fOnline);

    extra_signals = fatima_vme_config->ExtraSignals();
    tm_undelayed = fatima_vme_config->TM_Undelayed();
    tm_delayed = fatima_vme_config->TM_Delayed();
    sc41l = fatima_vme_config->SC41L();
    sc41r = fatima_vme_config->SC41R();
    calib_coeffs_QDC_E = fatima_vme_config->QDC_E_Calib();
    calib_coeffs_QDC_T = fatima_vme_config->QDC_T_Calib();
    calib_coeffs_TDC_T = fatima_vme_config->TDC_T_Calib();

    fcal_data->Clear();

    return kSUCCESS;
 
}


void FatimaVmeRaw2Cal::Exec(Option_t* option)
{
    qdcCalArray->clear();
    tdcCalArray->clear();
    residualArray->clear();
    //timeMachineArray->clear();

    int Fat_QDC_ID;
    int Fat_TDC_ID_single;
    int Fat_TDC_ID[48];// ? why 
    int Fat_TDC_multi[FAT_VME_MAX_HITS] = {0};
    bool TimID[FAT_VME_MAX_HITS] = {0};
    bool EnID[FAT_VME_MAX_HITS] = {0};
    int counter = 0;
    int dummy_qdc_id[FAT_VME_MAX_HITS];
    Double_t dummy_qdc_E[FAT_VME_MAX_HITS] = {0};
    Double_t dum_qdc_E[FAT_VME_MAX_HITS] = {0};
    Double_t dummy_qdc_E_raw[FAT_VME_MAX_HITS] = {0};
    Double_t dum_qdc_E_raw[FAT_VME_MAX_HITS] = {0};
    Long64_t dummy_qdc_t_coarse[FAT_VME_MAX_HITS] = {0};
    Long64_t dum_qdc_t_coarse[FAT_VME_MAX_HITS] = {0};
    Double_t dummy_qdc_t_fine[FAT_VME_MAX_HITS] = {0};
    Double_t dum_qdc_t_fine[FAT_VME_MAX_HITS] = {0};
    int dummy_tdc_id[FAT_VME_MAX_HITS];
    Double_t dummy_tdc_t[FAT_VME_MAX_HITS] = {0};
    Double_t dum_tdc_t[FAT_VME_MAX_HITS] = {0};
    Double_t dummy_tdc_t_raw[FAT_VME_MAX_HITS] = {0};
    Double_t dum_tdc_t_raw[FAT_VME_MAX_HITS] = {0};

    int dum_qdc_id[FAT_VME_MAX_HITS];
    int dum_tdc_id[FAT_VME_MAX_HITS];

    int dummyqdcmult = 0;
    int dummytdcmult = 0;
    int matchedmult = 0;
    int SC41Lcount= 0;
    int SC41Rcount = 0;
    std::vector<uint32_t> SC41L;
    std::vector<uint32_t> SC41R;
    std::vector<uint32_t> SC41L_E;
    std::vector<uint32_t> SC41R_E;

    int FatVME_TMUcount = 0;
    int FatVME_TMDcount = 0;
    std::vector<uint32_t> FatVME_TMU;
    std::vector<uint32_t> FatVME_TMD;
    std::vector<uint32_t> FatVME_TMU_E;
    std::vector<uint32_t> FatVME_TMD_E;

    int singlesqdcmult = 0;
    int singlestdcmult = 0;

    bool qdc_multi_hit_exclude[100] = {0};
    bool tdc_multi_hit_exclude[100] = {0};

    for (int i = 0; i < FAT_VME_MAX_HITS; i++)
    {
        dummy_qdc_id[i] = -1;
        dummy_tdc_id[i] = -2;
        dum_qdc_id[i] = -1;
        dum_tdc_id[i] = -1;
    }

    std::vector<FatimaVmeTDCItem> const* tdcArray2 = tdcArray;
    std::vector<FatimaVmeQDCItem> const* qdcArray2 = qdcArray; 

    int m = 0;
    for (auto const & tdcItem : *tdcArray)
    {   
        int n = 0;
        for (auto const & tdcItem2 : *tdcArray2)
        {
            if (tdcItem.Get_detector() == tdcItem2.Get_detector() && m != n)
            {
                tdc_multi_hit_exclude[m] = true;
            }
            n++;
        }
        m++;     
    }

    for (auto const & tdcItem : *tdcArray)
    {   
        int det = tdcItem.Get_detector();
        uint32_t timestamp_raw = tdcItem.Get_v1290_tdc_data();
        double timestamp = Calibrate_TDC_T(timestamp_raw, det);
        uint64_t wr_t = tdcItem.Get_wr_t();

        if (det >= 0)
        {   
            // this is unnecessary;
            double singles_tdc_timestamp = timestamp;
            uint32_t singles_tdc_timestamp_raw = timestamp_raw;
            int tdc_id = det;

            auto & entry = tdcCalArray->emplace_back();
            entry.SetAll(wr_t, det, timestamp, timestamp_raw);

            singlestdcmult++;

            if (timestamp != 0. && tdc_multi_hit_exclude[det] == 0)
            {
                dummy_tdc_t[dummytdcmult] = timestamp;
                dummy_tdc_t_raw[dummytdcmult] = timestamp_raw;
                dummy_tdc_id[dummytdcmult] = det;
                dummytdcmult++;
            }
        }
        
        double ts_sc41l = 0;
        double ts_sc41r = 0;
        double ts_tmd = 0;
        double ts_tmu = 0;

        auto & res_entry = residualArray->emplace_back();

        // put in residuals 
        if (det == sc41l && timestamp != 0.)
        {
            SC41L.emplace_back(timestamp);
            ts_sc41l = timestamp;
        }
        if (det == sc41r && timestamp != 0.)
        {
            SC41R.emplace_back(timestamp);
            ts_sc41r = timestamp; 
        }

        if (((det == tm_delayed) || (det == tm_undelayed)) && tm_delayed != 0 && tm_undelayed != 0)
        {
            new ((*fTimeMachineArray)[fTimeMachineArray->GetEntriesFast()]) TimeMachineData((det == tm_undelayed) ? (timestamp * 0.025) : (0), (det == tm_undelayed) ? (0) : (timestamp * 0.025), tdcItem.Get_wr_subsystem_id(), tdcItem.Get_wr_t());
        }

        if (det == tm_undelayed && timestamp != 0.)
        {
            FatVME_TMU.emplace_back((timestamp * 0.025));
            ts_tmu = timestamp * 0.025;
        }
        if (det == tm_delayed && timestamp != 0.)
        {
            FatVME_TMD.emplace_back((timestamp * 0.025));
            ts_tmd = timestamp * 0.025;
        }

        res_entry.SetAll(ts_sc41l, ts_sc41r, ts_tmu, ts_tmd);

    }

    int p = 0;
    for (auto const & qdcItem : *qdcArray)
    {   
        int o = 0;
        for (auto const & qdcItem2 : *qdcArray2)
        {
            if (qdcItem.Get_detector() == qdcItem2.Get_detector() && p != o)
            {
                qdc_multi_hit_exclude[p] = true;
            }
            o++;
        }
        p++;     
    }
    
    int z = 0;
    for (auto const & qdcItem : *qdcArray)
    {
        int det = qdcItem.Get_detector();
        uint32_t qlong_raw = qdcItem.Get_qlong_raw();
        double qlong = Calibrate_QDC_E(qlong_raw, det);
        uint32_t qshort_raw = qdcItem.Get_qshort_raw();
        uint32_t coarse_time = qdcItem.Get_coarse_time();
        double cal_coarse_time = Calibrate_QDC_T(coarse_time, det);
        uint64_t fine_time = qdcItem.Get_fine_time();
        double cal_fine_time = Calibrate_QDC_T(fine_time, det);
        uint64_t wr_t = qdcItem.Get_wr_t();

        if (det >= 0)
        {
            // and presumably create an entry for all of these
            auto & entry = qdcCalArray->emplace_back();
            entry.SetAll(wr_t, det, cal_coarse_time, cal_fine_time, qlong, qlong_raw, qshort_raw);

            if (qlong > 10. && qdc_multi_hit_exclude[det] == 0)
            {
                dummy_qdc_E[dummyqdcmult] = qlong;
                dummy_qdc_E_raw[dummyqdcmult] = qlong_raw;
                dummy_qdc_t_coarse[dummyqdcmult] = cal_coarse_time;
                dummy_qdc_t_fine[dummyqdcmult] = cal_fine_time;
                dummy_qdc_id[z] = det;
                dummyqdcmult++;
            }
        }
        z++;
    }




/*

    if (funcal_data && funcal_data->GetEntriesFast() > 0)
    {
        Int_t nHits = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FatimaVmeData* FatimaHit = (FatimaVmeData*)funcal_data->At(ihit);

            FatimaVmeCalData* FatimaCalHit = new FatimaVmeCalData();

            FatimaCalHit->Set_wr_t(FatimaHit->Get_wr_t());

            int tdcs_fired = FatimaHit->Get_TDCs_fired();
            std::vector<uint32_t> tdc_detectors = FatimaHit->Get_TDC_detectors();
            std::vector<uint32_t> v1290_data = FatimaHit->Get_v1290_data();
            std::vector<uint32_t> v1290_lot = FatimaHit->Get_v1290_lot();
            // nope we can loop over tdc_fired now
            for (int i = 0; i < tdcs_fired; i++)
            {
                for (int j = 0; j < tdcs_fired; j++)
                {
                    if (tdc_detectors[i] == tdc_detectors[j] && i != j)
                    {
                        tdc_multi_hit_exclude[i] = true;
                    }
                }
            }

            std::vector<uint32_t> Singles_TDC_timestamp;
            std::vector<uint32_t> Singles_TDC_timestamp_raw;
            std::vector<uint32_t> Singles_TDC_ID;

            for (int i = 0; i < tdcs_fired; i++)
            {
                uint32_t timestamp_raw = v1290_data[i];
                double timestamp = Calibrate_TDC_T(v1290_data[i], tdc_detectors[i]);
                
                if (tdc_detectors[i] >= 0)
                {
                    //if (extra_signals.find(tdc_detectors[i]) == extra_signals.end())
                    //{  
                        Singles_TDC_timestamp.emplace_back(timestamp);
                        Singles_TDC_timestamp_raw.emplace_back(timestamp_raw);
                        Singles_TDC_ID.emplace_back(tdc_detectors[i]);

                        singlestdcmult++;

                        if (timestamp != 0. && tdc_multi_hit_exclude[tdc_detectors[i]] == 0)
                        {
                            dummy_tdc_t[dummytdcmult] = timestamp;
                            dummy_tdc_t_raw[dummytdcmult] = timestamp_raw;
                            dummy_tdc_id[dummytdcmult] = tdc_detectors[i];
                            dummytdcmult++;
                        }
                        
                    //}
                }

                if (tdc_detectors[i] == sc41l && timestamp != 0.)
                {
                    SC41L.emplace_back(timestamp);
                }
                if (tdc_detectors[i] == sc41r && timestamp != 0.)
                {
                    SC41R.emplace_back(timestamp);
                }

                if (((tdc_detectors[i] == tm_delayed) || (tdc_detectors[i] == tm_undelayed)) && tm_delayed != 0 && tm_undelayed != 0)
                {
                    new ((*fTimeMachineArray)[fTimeMachineArray->GetEntriesFast()]) TimeMachineData((tdc_detectors[i] == tm_undelayed) ? (timestamp * 0.025) : (0), (tdc_detectors[i] == tm_undelayed) ? (0) : (timestamp * 0.025), FatimaHit->Get_wr_subsystem_id(), FatimaHit->Get_wr_t());
                }

                if (tdc_detectors[i] == tm_undelayed && timestamp != 0.)
                {
                    FatVME_TMU.emplace_back((double)(timestamp * 0.025));
                }
                if (tdc_detectors[i] == tm_delayed && timestamp != 0.)
                {
                    FatVME_TMD.emplace_back((double)(timestamp * 0.025));
                }

                
            }

            int qdcs_fired = FatimaHit->Get_QDCs_fired();
            std::vector<uint32_t> qdc_detectors = FatimaHit->Get_QDC_detectors();
            std::vector<uint32_t> QDC_time_coarse = FatimaHit->Get_QDC_coarse_time();
            std::vector<uint64_t> QDC_time_fine = FatimaHit->Get_QDC_fine_time();
            std::vector<uint32_t> QLong_raw = FatimaHit->Get_QLong_raw();
            std::vector<uint32_t> QShort_raw = FatimaHit->Get_QShort_raw();

            for (int i = 0; i < qdcs_fired; i++)
            {
                for (int j = 0; j < qdcs_fired; j++)
                {
                    if (qdc_detectors[i] == qdc_detectors[j] && i != j)
                    {
                        qdc_multi_hit_exclude[qdc_detectors[i]] = true;
                    }
                }
            } // qdcs fired

            std::vector<uint32_t> QLong;
            std::vector<uint32_t> Singles_E;
            std::vector<uint32_t> Singles_E_raw;
            std::vector<uint32_t> Singles_coarse_time;
            std::vector<uint64_t> Singles_fine_time;
            std::vector<uint32_t> Singles_QDC_ID;

            for (int i = 0; i < qdcs_fired; i++)
            {
                // calibrate
                QLong.emplace_back(Calibrate_QDC_E(QLong_raw[i], qdc_detectors[i]));
                QDC_time_coarse[i] = Calibrate_QDC_T(QDC_time_coarse[i], qdc_detectors[i]);
                QDC_time_fine[i] = Calibrate_QDC_T(QDC_time_fine[i], qdc_detectors[i]);


                if (qdc_detectors[i] >= 0)
                {
                    //if (extra_signals.find(qdc_detectors[i]) == extra_signals.end())
                    //{   
                        Singles_E.emplace_back(QLong[i]);
                        Singles_QDC_ID.emplace_back(qdc_detectors[i]);
                        Singles_coarse_time.emplace_back(QDC_time_coarse[i]);
                        Singles_fine_time.emplace_back(QDC_time_fine[i]);
                        Singles_E_raw.emplace_back(QLong_raw[i]);

                        if (QLong[i] > 10. && qdc_multi_hit_exclude[qdc_detectors[i]] == 0)
                        {
                            dummy_qdc_E[dummyqdcmult] = QLong[i];
                            dummy_qdc_E_raw[dummyqdcmult] = QLong_raw[i];
                            dummy_qdc_t_coarse[dummyqdcmult] = QDC_time_coarse[i];
                            dummy_qdc_t_fine[dummyqdcmult] = QDC_time_fine[i];

                            dummy_qdc_id[i] = qdc_detectors[i];
                            dummyqdcmult++;
                        }
                    //}
                }
                
                if (qdc_detectors[i] == sc41l)
                {
                    SC41L_E.emplace_back(QLong_raw[i]);
                }
                if (qdc_detectors[i] == sc41r)
                {
                    SC41R_E.emplace_back(QLong_raw[i]);
                }

                if (qdc_detectors[i] == tm_undelayed)
                {
                    FatVME_TMU_E.emplace_back(QLong_raw[i]);
                }
                if (qdc_detectors[i] == tm_delayed)
                {
                    FatVME_TMD_E.emplace_back(QLong_raw[i]);
                }

            } // qdcs fired

            FatimaCalHit->Set_Singles_TDC_timestamp(Singles_TDC_timestamp);
            FatimaCalHit->Set_Singles_TDC_timestamp_raw(Singles_TDC_timestamp_raw);
            FatimaCalHit->Set_Singles_TDC_ID(Singles_TDC_ID);

            FatimaCalHit->Set_SC41L_hits(SC41L);
            FatimaCalHit->Set_SC41R_hits(SC41R);
            FatimaCalHit->Set_TM_undelayed_hits(FatVME_TMU);
            FatimaCalHit->Set_TM_delayed_hits(FatVME_TMD);
            FatimaCalHit->Set_SC41L_E_hits(SC41L_E);
            FatimaCalHit->Set_SC41R_E_hits(SC41R_E);
            FatimaCalHit->Set_TM_undelayed_E_hits(FatVME_TMU_E);
            FatimaCalHit->Set_TM_delayed_E_hits(FatVME_TMD_E);

            FatimaCalHit->Set_Singles_E(Singles_E);
            FatimaCalHit->Set_Singles_QDC_ID(Singles_QDC_ID);
            FatimaCalHit->Set_Singles_coarse_time(Singles_coarse_time);
            FatimaCalHit->Set_Singles_fine_time(Singles_fine_time);
            FatimaCalHit->Set_Singles_E_raw(Singles_E_raw);


            if (dummyqdcmult < dummytdcmult) counter = dummytdcmult;
            else if (dummytdcmult < dummyqdcmult) counter = dummyqdcmult;
            else if (dummyqdcmult == dummytdcmult) counter = dummyqdcmult;


            for (int i = 0; i < dummyqdcmult; i++)
            {
                if (dummy_qdc_id[i] == dummy_tdc_id[i] && EnID[i] && TimID[i] == 0)
                {
                    EnID[i] = true;
                    TimID[i] = true;

                    // unpackproc 1227

                    dum_qdc_id[matchedmult] = dummy_qdc_id[i];
                    dum_qdc_E[matchedmult] = dummy_qdc_E[i];
                    dum_qdc_E_raw[matchedmult] = dummy_qdc_E_raw[i];
                    dum_qdc_t_coarse[matchedmult] = dummy_qdc_t_coarse[i];
                    dum_qdc_t_fine[matchedmult] = dummy_qdc_t_fine[i];
                    dum_tdc_id[matchedmult] = dummy_tdc_id[i];
                    dum_tdc_t[matchedmult] = dummy_tdc_t[i];
                    dum_tdc_t_raw[matchedmult] = dummy_tdc_t_raw[i];

                    matchedmult++;

                    if (dummy_qdc_id[i] == -1)
                    {
                        c4LOG(warn, "There was a -1 match in Fatima VME");
                        matchedmult--;
                    }
                }
                else
                {
                    for (int j = 0; j < dummytdcmult; j++)
                    {
                        if (dummy_qdc_id[i] == dummy_tdc_id[j] && EnID[i] == 0 && TimID[j] == 0)
                        {
                            EnID[i] = true;
                            TimID[j] = true;

                            dum_qdc_id[matchedmult] = dummy_qdc_id[i];
                            dum_qdc_E[matchedmult] = dummy_qdc_E[i];
                            dum_qdc_E_raw[matchedmult] = dummy_qdc_E_raw[i];
                            dum_qdc_t_coarse[matchedmult] = dummy_qdc_t_coarse[i];
                            dum_qdc_t_fine[matchedmult] = dummy_qdc_t_fine[i];
                            dum_tdc_id[matchedmult] = dummy_tdc_id[j];
                            dum_tdc_t[matchedmult] = dummy_tdc_t[j];
                            dum_tdc_t_raw[matchedmult] = dummy_tdc_t_raw[j];

                            matchedmult++;

                            if (dummy_qdc_id[j] == -1 && dummy_tdc_id[j] == -1)
                            {   
                                c4LOG(warn, "There was a -1 match in Fatima VME");
                                matchedmult--;
                            }
                            
                        }
                    }
                }
            } // dummyqdcmult

            FatimaCalHit->Set_FatVME_Mult(matchedmult);

            std::vector<uint32_t> QDC_ID;
            std::vector<uint32_t> QDC_E;
            std::vector<uint32_t> QDC_E_raw;
            std::vector<uint32_t> QDC_T_coarse;
            std::vector<uint64_t> QDC_T_fine;
            std::vector<uint32_t> TDC_ID;
            std::vector<uint32_t> TDC_time;
            std::vector<uint32_t> TDC_time_raw;

            for (int i = 0; i < matchedmult; i++)
            {
                QDC_ID.emplace_back(dum_qdc_id[i]);
                QDC_E.emplace_back(dum_qdc_E[i]);
                QDC_E_raw.emplace_back(dum_qdc_E_raw[i]);
                QDC_T_coarse.emplace_back(dum_qdc_t_coarse[i]);
                QDC_T_fine.emplace_back(dum_qdc_t_fine[i]);

                TDC_ID.emplace_back(dum_tdc_id[i]);
                TDC_time.emplace_back(dum_tdc_t[i]);
                TDC_time_raw.emplace_back(dum_tdc_t_raw[i]);
            }

            FatimaCalHit->Set_QDC_ID(QDC_ID);
            FatimaCalHit->Set_QDC_E(QDC_E);
            FatimaCalHit->Set_QDC_E_raw(QDC_E_raw);
            FatimaCalHit->Set_QDC_T_coarse(QDC_T_coarse);
            FatimaCalHit->Set_QDC_T_fine(QDC_T_fine);
            FatimaCalHit->Set_TDC_ID(TDC_ID);
            FatimaCalHit->Set_TDC_time(TDC_time);
            FatimaCalHit->Set_TDC_time_raw(TDC_time_raw);

            new ((*fcal_data)[fcal_data->GetEntriesFast()]) FatimaVmeCalData(*FatimaCalHit);

        } // ihit loop
    } // if data*/

}


double FatimaVmeRaw2Cal::Calibrate_QDC_E(double E, int det_id)
{
    double Energy_c = calib_coeffs_QDC_E[det_id][0];
    for (int i = 1; i < 5; i++) Energy_c = Energy_c * E + calib_coeffs_QDC_E[det_id][i];
    Energy_c += (static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 0.5));
    return Energy_c;
}

// gain matching?

double FatimaVmeRaw2Cal::Calibrate_TDC_T(unsigned long T, int det_id)
{
    return ((double) T) + calib_coeffs_TDC_T[det_id];
}

double FatimaVmeRaw2Cal::Calibrate_QDC_T(unsigned long T, int det_id)
{
    return T + calib_coeffs_QDC_T[det_id];
}


void FatimaVmeRaw2Cal::FinishEvent()
{
    fcal_data->Clear();
    funcal_data->Clear();
    fTimeMachineArray->Clear();
}

void FatimaVmeRaw2Cal::FinishTask()
{
    
}
