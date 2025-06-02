// FairROOT
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FimpReader.h"
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
        for (int i = 0; i < chans_per_tdc; i++) fine_time_hits[i] = new TH1I(Form("fine_time_hits_channel_%i", i), Form("fine_time_hits_channel_%i", i), max_fine_time_bins, 0, max_fine_time_bins);
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
            fine_time_calibration_coeffs[i][j] = cycle_time * ((double)running_sum + (double)fine_time_hits[i]->GetBinContent(j)) / (double)total_counts;
            running_sum += fine_time_hits[i]->GetBinContent(j);
            
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

    if (!outputfile->IsOpen()) { c4LOG(warn, "Fine Time histogram file was not opened, cannot write calibrations to file!"); return; }

    for (int i = 0; i < chans_per_tdc; i++)
    { 
        if (fine_time_hits[i] != nullptr)
        {
            outputfile->WriteObject(fine_time_hits[i], Form("fine_time_hits_channel_%i", i), "RECREATE");
        }
    }

    LOG(info) << "Fimp Fine Time calibrations (i.e. raw fine time histograms) written to " << fine_time_histo_outfile.Data();
    outputfile->Close();

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
        if (a)
        {
            fine_time_hits[i] = (TH1I*)a->Clone();
            c4LOG_IF(fatal, fine_time_hits == nullptr, "Failed reading fine time calibration histograms - aborting!");
            delete a;
            a = nullptr;
            fine_time_hits[i]->SetDirectory(0); // this is a trick to access histos after closing inputfile.
        }
    }

    inputfile->Close();
    LOG(info) << Form("Fatima fine time calibration read from file: %s", fine_time_histo_infile.Data());

}

Bool_t FimpReader::Read()
{

    if ((fNEvent == fine_time_calibration_after) & (!fine_time_calibration_set))
    {
        DoFineTimeCalibration();
        if (fine_time_calibration_save) WriteFineTimeHistosToFile();
    }

    ctdc_data_store last_hit;

    uint64_t wr_t = (((uint64_t)fData->fimp_ts_t[3]) << 48) + 
    (((uint64_t)fData->fimp_ts_t[2]) << 32) + 
    (((uint64_t)fData->fimp_ts_t[1]) << 16) + 
    (uint64_t)(fData->fimp_ts_t[0]);

    if (wr_t == 0) return kTRUE;

    uint32_t wr_id = fData->fimp_ts_subsystem_id;

    uint64_t trig_time_long = (((uint64_t)fData->fimp_data_trig_coarse_time_hi) << 22) +
                            ((uint64_t)fData->fimp_data_trig_coarse_time_lo);

    // coarse time
    int hit_index = 0;
    int channel = -1;
    int prev_channel = -1;
    int prev_LoT = -1;

    for (uint32_t channel_index = 0; channel_index < fData->fimp_data_time_coarseM; channel_index++)
    {
        int current_channel = fData->fimp_data_time_coarseMI[channel_index]; // channel to read now
        int next_channel_start = fData->fimp_data_time_coarseME[channel_index]; // read current channel data until this index

        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {
            counter++;
            uint16_t raw_ft = fData->fimp_data_time_finev[j];
            // fill ft calibration histo, or calibrate
            if (!fine_time_calibration_set)
            {
                fine_time_hits[current_channel]->Fill(raw_ft);
                continue;
            }

            uint16_t coarse_time = fData->fimp_data_time_coarsev[j];
            double fine_time = GetFineTime(current_channel, raw_ft);

            int leadOrTrail = fData->fimp_data_lead_or_trailv[j] & 0x1;
            channel = (current_channel - leadOrTrail)/2; // Get actual channel, 256 = trigger

            //std::cout << "lead or trail: " << leadOrTrail << " channel : " << channel << std::endl;


            if (channel != prev_channel && channel < 256)
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
            else if (channel == prev_channel && channel < 256)
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
            else if (channel == 256 && !leadOrTrail) // trigger stuff
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

            }






            /*// trigger leading edge
            if (channel == 256 && !leadOrTrail)
            {
                auto & entry = fimpArray->emplace_back();
                entry.SetAll(wr_t, 
                            wr_id,
                            trig_time_long, 
                            channel, 
                            coarse_time, // lead coarse
                            fine_time, // lead fine
                            0, // no trig trails
                            0,
                            raw_ft,
                            0
                            );
            }
            else if (channel < 256)
            {
                // check == is_leading
                if (!leadOrTrail)
                {   
                    // 2 leads in a row
                    if (last_hit.leadOrTrail == 0) 
                    {
                        unmatchedLeads++;
                        //c4LOG(warn, "Unmatched lead in FIMP data: " << unmatchedLeads);
                    }

                    last_hit.channel = channel;
                    last_hit.coarse_time = coarse_time;
                    last_hit.fine_time = fine_time;
                    last_hit.leadOrTrail = leadOrTrail;
                    last_hit.raw_ft = raw_ft;
                }
                else
                {   
                    if (last_hit.leadOrTrail == -1) //c4LOG(warn, "First data item is a trail");
                    {}
                    else if (last_hit.leadOrTrail == 1) 
                    {
                        //c4LOG(warn, "Two trails in a row");
                        continue;
                    }
                    else
                    {   
                        if (channel != last_hit.channel)
                        {
                            c4LOG(warn, "Couldn't match lead and trail channels!");
                            lead_trail_unmatched_counter++;
                            last_hit.channel = channel;
                            last_hit.coarse_time = coarse_time;
                            last_hit.fine_time = fine_time;
                            last_hit.leadOrTrail = leadOrTrail;
                            last_hit.raw_ft = raw_ft;
                            continue;
                        }
                        auto & entry = fimpArray->emplace_back();

                        entry.SetAll(wr_t, 
                                    wr_id,
                                    trig_time_long, 
                                    channel, 
                                    last_hit.coarse_time, // lead coarse
                                    last_hit.fine_time, // lead fine
                                    coarse_time, // trail coarse
                                    fine_time, // trail fine
                                    last_hit.raw_ft, // lead fine time bin
                                    raw_ft // trail fine time bin
                                    );

                        last_hit.channel = channel;
                        last_hit.coarse_time = coarse_time;
                        last_hit.fine_time = fine_time;
                        last_hit.leadOrTrail = leadOrTrail;
                    }
                }

            }
            else continue; // dummy data*/

            prev_channel = channel;
            prev_LoT = leadOrTrail;

        }
        hit_index = next_channel_start;
    }

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
