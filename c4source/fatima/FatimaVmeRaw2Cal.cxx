// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
//#include "TimeMachineData.h" // ? maybe
#include "c4Logger.h"

#include "TClonesArray.h"

#include "FatimaVmeRaw2Cal.h"

FatimaVmeRaw2Cal::FatimaVmeRaw2Cal()
    :   FairTask
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    //,

{
}

// named constructor
FatimaVmeRaw2Cal::FatimaVmeRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    //,
{
}

FatimaVmeRaw2Cal::~FatimaVmeRaw2Cal()
{
    c4LOG(info, "Deleting FatimaVmeRaw2Cal task");

    // delete
    
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
    // time machine?

    fcal_data->Clear();

    return kSUCCESS;
 
}



void FatimaVmeRaw2Cal::Exec(Option_t* option)
{
    // if (funcal_data && funcal_data->GetEntriesFast() > )

    // reject if there's no data

    int Fat_QDC_ID;
    int Fat_TDC_ID_single;
    int Fat_TDC_ID[48];// ? why 
    int Fat_TDC_multi[FAT_VME_MAX_HITS] = {0};// max VME channels?
    bool TimID[FAT_VME_MAX_HITS] = {0};
    bool EnID[FAT_VME_MAX_HITS] = {0};
    int counter = 0;
    int dummy_qdc_id[FAT_VME_MAX_HITS];
    Double_t dummy_qdc_E[FAT_VME_MAX_HITS] = {0};
    Double_t dummy_qdc_E_raw[FAT_VME_MAX_HITS] = {0};
    Long64_t dummy_qdc_t_coarse[FAT_VME_MAX_HITS] = {0};
    Double_t dummy_qdc_t_fine[FAT_VME_MAX_HITS] = {0};
    int dummy_tdc_id[FAT_VME_MAX_HITS];
    Double_t dummy_tdc_t[FAT_VME_MAX_HITS] = {0};
    Double_t dummy_tdc_t_raw[FAT_VME_MAX_HITS] = {0};

    int dum_qdc_id[FAT_VME_MAX_HITS];
    int dum_tdc_id[FAT_VME_MAX_HITS];

    int dummyqdcmult = 0;
    int dummytdcmult = 0;
    int matchedmult = 0;
    int sc40count = 0;
    int sc41count = 0;

    int FatVmeTMCh1_count = 0;
    int FatVmeTMCh2_count = 0;

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

    int tdcs_fired = FatimaHit->Get_TDCs_fired();
    std::vector<int> tdc_detectors = FatimaHit->Get_TDC_detectors();
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

    for (int i = 0; i < tdcs_fired; i++)
    {
        // Calibrate - actually should we calibrate?
        // in go4 the raw ts is taken, why
        // timestamp = Calibrate_TDC_T(v1290_data[i], tdc_detectors[i]);
        // timestamp_raw = Calibrate_TDC_T(v1290_data[i], tdc_detectors[i]);

        if (tdc_detectors[i] > -1 && tdc_detectors[i] < FAT_VME_MAX_DETS)
        {
            if (tdc_detectors[i] != ALL THOSE SHIT DETECTORS)
            {   
                // pass along timestamp? and id? idk
                singlestdcmult++;

                if (timestamp != 0. && tdc_multi_hit_exclude[tdc_detectors[i]] == 0)
                {
                    dummy_tdc_t[dummytdcmult] = timestamp;
                    dummy_tdc_t_raw[dummytdcmult] = timestamp_raw;
                    dummy_tdc_id[dummytdcmult] = tdc_detectors[i];
                    dummytdcmult++;
                }
                
            }
        }

        if (tdc_detectors[i] == SC41L && timestamp != 0.)
        {
            // pass along [sc40count] timestamp
            sc40count++;
        }

        // same for all weird channels (SC41R, TM, etc)
    }

    int qdcs_fired = FatimaHit->Get_QDCs_fired();
    std::vector<uint32_t> qdc_detectors = FatimaHit->Get_QDC_detectors();
    std::vector<uint32_t> QDC_time_coarse = FatimaHit->Get_QDC_coarse_time();
    std::vector<uint64_t> QDC_time_fine = FatimaHit->Get_QDC_fine_time();
    std::vector<uint32_t> QLong_raw = FatimaHit->Get_QLong_raw();
    std::vector<uint32_t> QShort_raw = FatimaHit;

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

    for (int i = 0; i < qdcs_fired; i++)
    {
        // calibrate?
        QLong[i] = Calibrate_QDC_E(QLong_raw[i], qdc_detectors[i]);
        QDC_time_coarse[i] = Calibrate_QDC_T(QDC_time_coarse[i], qdc_detectors[i]);
        QDC_time_fine[i] = Calibrate_QDC_T(QDC_time_fine[i], qdc_detectors[i]);

        if (qdc_detectors[i] > - 1 && qdc_detectors[i] < FAT_VME_MAX_DETS)
        {
            if (qdc_detectors[i] != shit channels)
            {

                Singles_E = qlong;
                Singles_ID = qdc_detectors[i];
                Singles_t_coarse = time_coarse;
                Singles_t_fine = time_fine;
                Singles_E_raw = QLong_raw;

                singlesqdcmult++;

                if (QLong > 10. && qdc_multi_hit_exclude[qdc_detectors[i]] == 0)
                {
                    dummy_qdc_E[dummyqdcmult] = Qlong;
                    dummy_qdc_E_raw[dummyqdcmult] = Qlong_raw;
                    dummy_qdc_t_coarse[dummyqdcmult] = time_coarse;
                    dummy_qdc_t_fine[dummyqdcmult] = time_fine;

                    dummy_qdc_id[i] = qdc_detectors[i];
                    dummyqdcmult++;
                }
            }
        }

    } // qdcs fired

    if (dummyqdcmult < dummytdcmult) counter = dummytdcmult;
    else if (dummytdcmult < dummyqdcmult) counter = dummyqdcmult;
    else if (dummyqdcmult == dummytdcmult) counter = dummyqdcmult;

    // bunch of other stuff

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
            for (j = 0; j < dummytdcmult; j++)
            {
                if (dummy_qdc_id[i] == dummy_tdc_id[j] && EnID[i] == 0 && TimID[] == 0)
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

    Fatmult = matchedmult;
    sc40mult = sc40mult;
    sc41mult = sc41mult;

    tm1mult = tm1mult;
    tm2mult = tm2mult;

    tdcsinglescount = singlestdcmult;
    qdcsinglescount = singlesqdcmult;

    for (int i = 0; i < matchedmult; i++)
    {
        QDC_ID[i] = dum_qdc_id[i];
        QDC_E[i] = dum_qdc_E[i];
        QDC_E_raw[i] = dum_qdc_E_raw[i];
        QDC_T_coarse[i] = dum_qdc_t_coarse[i];
        QDC_T_fine[i] = dum_qdc_t_fine[i];

        TDC_ID[i] = dum_tdc_id[i];
        TDC_Time[i] = dum_tdc_t[i];
        TDC_Time_Raw[i] = dum_tdc_t_raw[i];
    }

    // end

}


void FatimaVmeRaw2Cal::Load_QDC_Energy_Calibration_File(TString& filepath)
{
    std::ifstream file(filepath);
    std::string line;

    const char* format = "%d %lf %lf %lf %lf %lf";

    if (file.fail())
    {
        c4LOG(warn, "Could not find Fatima (VME) Energy Calibration File");
    }

    double tmp_coeffs[5] = {0,0,0,0,0};
    int det_id = 0;

    while (file.good())
    {
        std::getline(file, line, '\n');
        if (line[0] == '#' || line.empty()) continue;

        sscanf(line.c_str(), format, &det_id, &tmp_coeffs[0], &tmp_coeffs[1], &tmp_coeffs[2], &tmp_coeffs[3], &tmp_coeffs[4]);

        for (int i = 0; i < 5; i++)
        {
            calib_coeffs[det_id][i] = tmp_coeffs[i];
            original_calib_coeffs[det_id][i] = tmp_coeffs[i];
        }
    }
}

void FatimaVmeRaw2Cal::Load_TDC_Time_Calibration_File(TString& filename)
{
    const char* format = "%d %lf";

    std::ifstream file(filepath);
    std::string line;

    if (file.fail())
    {
        c4LOG(warn, "Could not find Fatima (VME) TDC Time Calibration file");
        // we need a default cal file to use I think, to prevent fatal crashes
    }

    double tmp_coeffs;
    int det_id = 0;

    while (file.good())
    {
        std::getline(file, line, '\n');
        if (line[0] == '#' || line.empty()) continue;
        
        sscanf(line.c_str(), format, &det_id, &tmp_coeffs);

        calib_coeffs_TDC[det_id] = tmp_coeffs;
    }

    file.close()
}

void FatimaVmeRaw2Cal::Load_QDC_Time_Calibration_File(TString& filename)
{
    const char* format = "%d %lf";

    std::ifstream file(filepath);
    std::string line;

    if (file.fail())
    {
        c4LOG(warn, "Could not find Fatima (VME) QDC Time Calibration file");
        // we need a default cal file to use I think, to prevent fatal crashes
    }

    double tmp_coeffs;
    int det_id = 0;

    while (file.good())
    {
        std::getline(file, line, '\n');
        if (line[0] == '#' || line.empty()) continue;
        
        sscanf(line.c_str(), format, &det_id, &tmp_coeffs);

        calib_coeffs_QDC[det_id] = tmp_coeffs;
    }

    file.close()
}

double FatimaVmeRaw2Cal::Calibrate_QDC_E(double E, int det_id)
{
    double Energy_c = calib_coeffs_QDC_E[det_id][0];
    for (int i = 1; i < 5; i++) Energy_c = Energy_c * E + calib_coeffs[det_id][i];
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