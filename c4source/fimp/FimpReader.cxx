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

// FairROOT
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FimpReader.h"
#include "ClockTdcReader.h"
#include "FimpFineTimeBins.h"
#include "c4Logger.h"

// ROOT
#include "TFile.h"

// UCESB
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_fimp.h"
}

FimpReader::FimpReader(EXT_STR_h101_fimp_onion* data, size_t offset)
    : c4Reader("FimpReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fimpArray(new std::vector<FimpItem>)
{
}

FimpReader::~FimpReader()
{
    c4LOG(info, "Counter: " << counter);
    c4LOG(info, "unmatched lead trail counter: " << lead_trail_unmatched_counter);
    c4LOG(info, "fNEvents: " << fNEvent);

    if (fine_time_hits)
    {
        for (int i = 0; i < chans_per_tdc; ++i) delete fine_time_hits[i];
        delete[] fine_time_hits;
    }

    if (fine_time_calibration_coeffs)
    {
        for (int i = 0; i < chans_per_tdc; ++i) delete[] fine_time_calibration_coeffs[i];
        delete[] fine_time_calibration_coeffs;
    }

    delete fimpArray; // The FimpData output container is created and owned by this reader.
}

Bool_t FimpReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
  
    EXT_STR_h101_fimp_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_fimp, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    fine_time_calibration_coeffs = new double*[chans_per_tdc];
    for (int i = 0; i < chans_per_tdc; i++) 
    {
        fine_time_calibration_coeffs[i] = new double[max_fine_time_bins];
        for (int j = 0; j < max_fine_time_bins; j++) fine_time_calibration_coeffs[i][j] = 0.0;
        // initialise other counter variables?
    }

    if (fine_time_calibration_read_from_file)
    {
        ReadFineTimeHistosFromFile();
        DoFineTimeCalibration();
        fine_time_calibration_set = true;
    }
    else
    {
        fine_time_hits = new TH1I*[chans_per_tdc];
        for (int i = 0; i < chans_per_tdc; i++)
        {
            fine_time_hits[i] = new TH1I(Form("fine_time_hits_channel_%i", i),
                                        Form("fine_time_hits_channel_%i", i),
                                        max_fine_time_bins, 0, max_fine_time_bins);
            fine_time_hits[i]->SetDirectory(nullptr); // Reader owns the histogram.
        }
        fine_time_calibration_set = false;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // register output array in a tree
    mgr->RegisterAny("FimpData", fimpArray, !fOnline);

    fimpArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

void FimpReader::DoFineTimeCalibration()
{
    // std::vector<std::pair<int, int>> warning_channels;
    // int warning_counter = 0;

    // for now we don't loop over sfp. adjust once we have this working for test data.
    for (int i = 0; i < chans_per_tdc; i++)
    {
        int running_sum = 0;
        int total_counts = fine_time_hits[i]->GetEntries();
        if (total_counts == 0)
        {
            // warning channel stuff, work out later.
        }

        for (int j = 0; j < max_fine_time_bins; j++)
        {
            if (total_counts == 0)
            {
                fine_time_calibration_coeffs[i][j] = j * cycle_time / max_fine_time_bins;
                continue;
            }
            // not sure why we would need to divide by 2? is it for lead/trail? or fast/slow?
            const double bin_counts = fine_time_hits[i]->GetBinContent(fimp_fine_time_bins::RootBinForRawFineTime(j));
            fine_time_calibration_coeffs[i][j] = cycle_time * ((double)running_sum + bin_counts) / (double)total_counts;
            running_sum += bin_counts;
            
        }
    }

    fine_time_calibration_set = true;

    c4LOG(info, "Success.");

}

double FimpReader::GetFineTime(int channel_id, int tdc_ft_channel)
{
    return fine_time_calibration_coeffs[channel_id][tdc_ft_channel];
}

void FimpReader::WriteFineTimeHistosToFile()
{
    if (!fine_time_calibration_set)
    {
        c4LOG(warn, "Fine time calibrations not set, cannot write to file!");
        return;
    }

    TFile* outputfile = TFile::Open(Form("%s", fine_time_histo_outfile.Data()), "RECREATE");

    if (!outputfile || !outputfile->IsOpen())
    {
        c4LOG(warn, "Fine Time histogram file was not opened, cannot write calibrations to file!");
        delete outputfile;
        return;
    }

    for (int i = 0; i < chans_per_tdc; i++)
    { 
        if (fine_time_hits[i] != nullptr)
        {
            outputfile->WriteObject(fine_time_hits[i], Form("fine_time_hits_channel_%i", i), "RECREATE");
        }
    }

    LOG(info) << "Fimp Fine Time calibrations (i.e. raw fine time histograms) written to " << fine_time_histo_outfile.Data();
    outputfile->Close();
    delete outputfile;

    c4LOG(info, "You have successfully done fine time calibration. These are written to file - please restart the program and add set the correct fine time calibration file for FimpReader.");
}

void FimpReader::ReadFineTimeHistosFromFile()
{
    TFile* inputfile = TFile::Open(fine_time_histo_infile, "READ");
    if (!inputfile || inputfile->IsZombie()) c4LOG(fatal, "Fine time calibration file could not be opened, aborting program.");
    
    fine_time_hits = new TH1I*[chans_per_tdc];
    for (int i = 0; i < chans_per_tdc; i++) fine_time_hits[i] = nullptr; //new TH1I[max_fine_time_bins];

    for (int i = 0; i < chans_per_tdc; i++)
    {
        TH1I* a = nullptr;
        inputfile->GetObject(Form("fine_time_hits_channel_%i", i), a);
        c4LOG_IF(fatal, !a, "Missing FIMP fine time calibration histogram for channel " << i);
        fine_time_hits[i] = static_cast<TH1I*>(a->Clone());
        c4LOG_IF(fatal, !fine_time_hits[i], "Failed cloning FIMP fine time histogram for channel " << i);
        fine_time_hits[i]->SetDirectory(nullptr); // Keep the clone after the input file closes.
    }

    inputfile->Close();
    delete inputfile;
    LOG(info) << Form("Fatima fine time calibration read from file: %s", fine_time_histo_infile.Data());

}

Bool_t FimpReader::Read()
{

    if ((fNEvent == fine_time_calibration_after) & (!fine_time_calibration_set))
    {
        DoFineTimeCalibration();
        if (fine_time_calibration_save) WriteFineTimeHistosToFile();
    }

    uint64_t wr_t = (((uint64_t)fData->fimp_ts_t[3]) << 48) + 
    (((uint64_t)fData->fimp_ts_t[2]) << 32) + 
    (((uint64_t)fData->fimp_ts_t[1]) << 16) + 
    (uint64_t)(fData->fimp_ts_t[0]);

    if (wr_t == 0) return kTRUE;

    uint32_t wr_id = fData->fimp_ts_subsystem_id;

    const auto& input = *fData;
    const auto trig_time_long = clocktdc::TriggerCoarseTime(
        input.fimp_data_trig_coarse_time_hi, input.fimp_data_trig_coarse_time_lo);

    int prev_channel = -1;
    int prev_LoT = -1;
    clocktdc::ReadEdges(input.fimp_data_time_coarseM,
        input.fimp_data_time_coarseMI, input.fimp_data_time_coarseME,
        clocktdc::PackedColumn{input.fimp_data_time_coarse, input.fimp_data_time_coarsev},
        clocktdc::PackedColumn{input.fimp_data_time_fine, input.fimp_data_time_finev},
        clocktdc::PackedColumn{input.fimp_data_lead_or_trail, input.fimp_data_lead_or_trailv},
        [&](const clocktdc::RawEdge& edge)
        {
            counter++;
            const auto current_channel = edge.sparseIndex;
            if (current_channel >= static_cast<unsigned>(chans_per_tdc) ||
                edge.fine >= static_cast<unsigned>(max_fine_time_bins)) return;

            const auto raw_ft = static_cast<std::uint16_t>(edge.fine);
            if (!fine_time_calibration_set)
            {
                fine_time_hits[current_channel]->Fill(raw_ft);
                return;
            }

            const auto coarse_time = static_cast<std::uint16_t>(edge.coarse);
            const auto fine_time = GetFineTime(current_channel, raw_ft);
            const int leadOrTrail = edge.trailing;
            const int channel = edge.channel;

            if (channel != prev_channel && channel < 128)
            {
                // create an entry for anything that came before.
                if (lead_coarse.size() > 0 && trail_coarse.size() > 0)
                {
                    auto & entry = fimpArray->emplace_back();
                    entry.SetAll(wr_t, 
                                wr_id,
                                trig_time_long, 
                                prev_channel, 
                                lead_coarse, // lead coarse
                                lead_fine, // lead fine
                                trail_coarse, // trail coarse
                                trail_fine, // trail fine
                                lead_raw_ft, // lead fine time bin
                                trail_raw_ft // trail fine time bin
                    );

                    lead_coarse.clear();
                    lead_fine.clear();
                    lead_raw_ft.clear();
                    trail_coarse.clear();
                    trail_fine.clear();
                    trail_raw_ft.clear();
                }

                if (!leadOrTrail)
                {
                    // open lead array, collect up to 3 (?)
                    lead_coarse.emplace_back(coarse_time);
                    lead_fine.emplace_back(fine_time);
                    lead_raw_ft.emplace_back(raw_ft);
                }
                else
                {
                    c4LOG(debug2, "Unmatched trail(s). Channel = " << channel << " Prev channel = " << prev_channel);
                }

            }
            else if (channel == prev_channel && channel < 128)
            {
                if (!leadOrTrail && !prev_LoT && lead_coarse.size() < 3)
                {
                    lead_coarse.emplace_back(coarse_time);
                    lead_fine.emplace_back(fine_time);
                    lead_raw_ft.emplace_back(raw_ft);
                }
                else if (!leadOrTrail && prev_LoT == 1)
                {
                    c4LOG(warn, "Unmatched leads or trails/leads swapped? Should we account for this?");
                }
                else if (leadOrTrail == 1 && !prev_LoT)
                {
                    trail_coarse.emplace_back(coarse_time);
                    trail_fine.emplace_back(fine_time);
                    trail_raw_ft.emplace_back(raw_ft);
                }
                else if (leadOrTrail == 1 && prev_LoT == 1 && trail_coarse.size() < 3)
                {
                    trail_coarse.emplace_back(coarse_time);
                    trail_fine.emplace_back(fine_time);
                    trail_raw_ft.emplace_back(raw_ft);
                }
            }
            else if (channel == 128 && !leadOrTrail) // trigger stuff
            {
                lead_coarse.clear();
                lead_fine.clear();
                lead_raw_ft.clear();
                trail_coarse.clear();
                trail_fine.clear();
                trail_raw_ft.clear();

                lead_coarse.emplace_back(coarse_time);
                lead_fine.emplace_back(fine_time);
                lead_raw_ft.emplace_back(raw_ft);

                auto & entry = fimpArray->emplace_back();
                entry.SetAll(wr_t, 
                            wr_id,
                            trig_time_long, 
                            channel, // Trigger channel 128, not the preceding detector channel

                            lead_coarse, // lead coarse
                            lead_fine, // lead fine
                            trail_coarse, // trail coarse
                            trail_fine, // trail fine
                            lead_raw_ft, // lead fine time bin
                            trail_raw_ft // trail fine time bin
                );

                lead_coarse.clear();
                lead_fine.clear();
                lead_raw_ft.clear();

            }

            prev_channel = channel;
            prev_LoT = leadOrTrail;
        });

    // create entry for last data
    if (lead_coarse.size() > 0)
    {
        auto & entry = fimpArray->emplace_back();
        entry.SetAll(wr_t, 
                    wr_id,
                    trig_time_long, 
                    prev_channel, 
                    lead_coarse, // lead coarse
                    lead_fine, // lead fine
                    trail_coarse, // trail coarse
                    trail_fine, // trail fine
                    lead_raw_ft, // lead fine time bin
                    trail_raw_ft // trail fine time bin
        );

        lead_coarse.clear();
        lead_fine.clear();
        lead_raw_ft.clear();
        trail_coarse.clear();
        trail_fine.clear();
        trail_raw_ft.clear();
    }

    fNEvent++;

    return kTRUE;
}

// You must clear any arrays and vectors you use or things will get weird
void FimpReader::ZeroArrays()
{ 

}

void FimpReader::ClearVectors()
{
    lead_coarse.clear();
    lead_fine.clear();
    lead_raw_ft.clear();
    trail_coarse.clear();
    trail_fine.clear();
    trail_raw_ft.clear();
    fimpArray->clear();
}

void FimpReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FimpReader);
