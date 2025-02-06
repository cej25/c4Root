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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

//...Notes...
/******************************************************************************
 This Task contains the calculation for the Moving Window Deconvolution
 algorithm applied to the traces form febex (raw traces).
 It calculates the Trapezoidal shape from the trace, and finally the energy.
 The calculations reflect the ones from anaTraces:
 https://git.gsi.de/lisa/daq_analysis.git
 
 To check the calculation use macros/lisa/trace_analysis/trace_ana_histos.C
 Last update : January 2025.
 E.G.
*******************************************************************************/

// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "LisaRaw2Ana.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>

LisaRaw2Ana::LisaRaw2Ana()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaAnaArray(new std::vector<LisaAnaItem>)

{
    lisa_config = TLisaConfiguration::GetInstance();
}


LisaRaw2Ana::~LisaRaw2Ana()
{
    delete lisaArray;
    delete lisaAnaArray;
}

InitStatus LisaRaw2Ana::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");
    
    mgr->RegisterAny("LisaAnaData", lisaAnaArray, !fOnline);

    return kSUCCESS;
}


void LisaRaw2Ana::Exec(Option_t* option)
{
    lisaAnaArray->clear();

    double energy_sum;
    int amp_count;
    double sum;
    int count;
    double average_baseline;
    double DM;
    double sum0;
    double mwd_value;
    double energy_avg;
    double baseline_sum;
    int baseline_count;
    double baseline_avg;

    for (auto const & lisaItem : *lisaArray)
    {
               
        // ::: Calculate energy with MWD algorithm ::: 
        //     - Calculation of trapezoidal shape using moving windows (MWD trace)
        //     - Extraction of energy as amplitude to the flat top of the trapezoid (MWD energy) 

        if (lisa_config->MWDParametersLoaded())
        {
            
            energy_sum = 0.0;
            amp_count = 0;
            sum = 0.0;
            count = 0;
            average_baseline = 0.0;
            mwd_value = 0.0;
            energy_avg = 0.0;
            baseline_sum = 0.0;
            baseline_count = 0;
            baseline_avg = 0.0;

            // ::: M W D   T R A C E  ::: (trace_MWD)

            // 0. ::: Get trace and parameters :::
            //    ::: For MWD calculation
            std::vector<int16_t> trace_febex = lisaItem.Get_trace();            //vector with amplitude points of trace
            float smoothing_L = lisa_config->Get_Smoothing_L();                 //L parameters in MWD formula. This corresponds to RisingTime in anatrace. !!IT IS NOT THE TRACE RISING TIME!!
            float MWD_length = lisa_config->Get_MWD_Length();                   //lenght of MWD computation
            const float* decay_time = lisa_config->Get_Decay_Time();            //decay time of the trace
            float MWD_trace_start = lisa_config->Get_MWD_Trace_Start();         //start of MWD trace
            float MWD_trace_stop = lisa_config->Get_MWD_Trace_Stop();           //and stop
            float sampling = lisa_config->Get_Sampling();                       //Sampling Febex (10 ns)
            
            //    ::: Convert parameters to sample points
            int LL = static_cast<int>(smoothing_L / sampling);                   // Smoothing time in samples
            int MM = static_cast<int>(MWD_length / sampling);                    // MWD length in samples
            float tau[2];
            tau[1] = decay_time[1] / sampling;                                   // Decay constant in samples
            int k0 = static_cast<int>(MWD_trace_start / sampling);               // Start of MWD in samples
            int kend = static_cast<int>(MWD_trace_stop / sampling);              // Stop of MWD in samples
            if (kend > trace_febex.size()) kend = trace_febex.size();            // If kend out of bound, replace it with trace_febex limit

            //std::cout << "k0 : " << k0 << " kend : " << kend << "\n";
            // 1. ::: Baseline correction :::
            //        This corresponds to anaTraces function calcCorrectTrace
            // ::: Evaluate average from points 20 to 100
            for( int i = 20; i < 100; i++)
            {
                sum += trace_febex.at(i);
                count++;
            }
            average_baseline  = sum / count;  

            // ::: Shift the trace of the previously calculated value
            // ::: Calibrate amplitude from ADC to mV considering that febex dynamic range is -+ 1V that corresponds to 16000 ADC
            // ::: Calibration coefficent is 1/8 (8000 from febex corresponds to 1000 mV)
            // ::: Ref to the elog:  https://elog.gsi.de/LISA/X7+Lab/50

            for( int i = 0; i < trace_febex.size(); i++)
            {
                trace_febex.at(i) = (trace_febex.at(i) - average_baseline)/8;

            }

            // 2. ::: Calculation of trapezoid :::
            //        This corresponds to anaTraces function calcMWDTrace
            for (int kk = k0; kk < kend; ++kk) 
            {
                DM = 0.0;
                for (int j = kk - LL; j <= kk - 1; ++j) 
                {
                    if (j < 1) continue;                    // Skip if out-of-bounds
                    sum0 = 0.0;                      // Initialize sum for baseline subtraction
                    for (int i = j - MM; i <= j - 1; ++i) 
                    {
                        if (i < 0) continue;                // Skip if out-of-bounds
                        sum0 += trace_febex.at(i);          // Sum over the moving window
                    }
                    DM += trace_febex.at(j) - trace_febex.at(j - MM) + sum0 / tau[1];
                }
                // Calculate MWD value and index
                mwd_value = DM / LL;                 // Average over the rising time
                //double mwd_index = static_cast<double>(kk) / sample_rate; // Convert sample index to time in ns

                //std::cout<<" ::: mwd values : " << mwd_value << "\n";
                trace_MWD.push_back(mwd_value);
            }


            // :::  M D W   E N E R G Y  ::: (energy_MWD) 
            //      Steps below correspond to anaTraces function calcEnergy

            //    ::: Get parameters :::
            float MWD_amp_start = lisa_config->Get_MWD_Amp_Start();             //start of MWD trace flat top
            float MWD_amp_stop = lisa_config->Get_MWD_Amp_Stop();               //and stop
            float MWD_baseline_start = lisa_config->Get_MWD_Baseline_Start();   //start of baseline for MWD trace
            float MWD_baseline_stop = lisa_config->Get_MWD_Baseline_Stop();     //and stop

            //    ::: Convert parameters to sample points :::
            int amp_start_idx = static_cast<int>(MWD_amp_start / sampling); 
            int amp_stop_idx = static_cast<int>(MWD_amp_stop / sampling);
            int baseline_start_idx = static_cast<int>(MWD_baseline_start / sampling);
            int baseline_stop_idx = static_cast<int>(MWD_baseline_stop / sampling);         
            
            //    ::: Check ranges :::
            //std::cout<<"trace MWD size : " << trace_MWD.size()  << " start : " << k0 << " stop : " << kend <<"\n";            
            
            // 4. ::: Integration on the flat top
            amp_start_idx = amp_start_idx - k0;
            amp_stop_idx = amp_stop_idx - k0;
            
            for (int i = amp_start_idx; i < amp_stop_idx; ++i) 
            {
                energy_sum += trace_MWD.at(i);
                amp_count++;
                //std::cout<< " inside amp count : " << amp_count << " energy_sum : " << energy_sum << "\n";
            }

            energy_avg = energy_sum / amp_count;

            //5. ::: Integration of baseline 
            baseline_start_idx = baseline_start_idx - k0;
            baseline_stop_idx = baseline_stop_idx - k0;

            for (int i = baseline_start_idx; i < baseline_stop_idx; ++i) 
            {
                baseline_sum += trace_MWD.at(i);
                baseline_count++;
            }
    
            //std::cout << "energy_sum : " << energy_sum << " baseline sum : " << baseline_sum << "\n";
            baseline_avg = baseline_sum / baseline_count;
            
            // 6. ::: Calculate MWD |energy value|
            energy_MWD = energy_avg - baseline_avg;

            if (energy_MWD < 0) 
            {
                energy_MWD = - energy_MWD;
            }            
        
            //std::cout<<" energy MWD : " << energy_MWD << "\n";

            // ::::::::::::::::::::::::::::::::::::::::::::::::::::

            // ::: Calculation for MWD pileup (pileup_MWD) :::
            // ...
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::

            // ::: Calculation for MWD overflow (overflow_MWD) :::
            // ...
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::

            // debug stuff...
            // int channel_ID_trace = lisaItem.Get_channel_id_traces();
            // if (channel_ID_trace < 8)
            // {
            //     std::cout<<"ID : " << channel_ID_trace << " ___ energy MWD : "<< energy_MWD << " ___ size of trace MWD : " << trace_MWD.size() << "\n";

            // }

            auto & entry = lisaAnaArray->emplace_back();    
            
            uint64_t EVTno = header->GetEventno();
            entry.SetAll(
                lisaItem.Get_wr_t(),
                lisaItem.Get_wr_id(),
                lisaItem.Get_board_id(),
                lisaItem.Get_board_event_time(),
                lisaItem.Get_channel_id(),
                lisaItem.Get_channel_time(),
                lisaItem.Get_pileup(),
                //pileup_MWD,
                lisaItem.Get_overflow(),
                //overflow_MWD,
                lisaItem.Get_channel_energy(),
                energy_MWD,
                lisaItem.Get_channel_id_traces(),
                trace_febex,
                trace_MWD,
                lisaItem.Get_trace_x()
                //EVTno
            );
            
            trace_MWD.clear();
            trace_febex.clear();
        }


    }
}

void LisaRaw2Ana::FinishEvent()
{
    
}

void LisaRaw2Ana::FinishTask()
{
}