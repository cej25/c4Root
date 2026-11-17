#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <iostream>
#include <cstdint>

#include "TamexRawData.h"

// Read the finished output in a fresh ROOT session.
// Reject unexpected procids/names/board ranges and report raw word totals.
void s100_tamex_combined_inspect(TString file_name = "s100_tamex_combined_validation.root")
{
    TFile file(file_name, "READ");
    if (file.IsZombie())
    {
        std::cerr << "Cannot open " << file_name << '\n';
        return;
    }
    auto* events = dynamic_cast<TTree*>(file.Get("evt"));
    if (!events)
    {
        std::cerr << "Missing FairRoot event tree 'evt' in " << file_name << '\n';
        return;
    }
    if (!events->GetBranch("TamexRawData"))
    {
        std::cerr << "Missing shared TamexRawData branch.\n";
        return;
    }

    TClonesArray* boards = nullptr;
    if (events->SetBranchAddress("TamexRawData", &boards) < 0)
    {
        std::cerr << "Cannot bind TamexRawData branch.\n";
        return;
    }
    std::uint64_t counts[3] = {}, word_counts[3] = {};
    std::uint64_t bad_metadata = 0, wr_mismatches = 0, multi_source_events = 0;

    const auto n = events->GetEntries();
    for (Long64_t entry = 0; entry < n; ++entry)
    {
        events->GetEntry(entry);
        unsigned seen = 0;
        if (!boards) continue;
        for (int i = 0; i < boards->GetEntriesFast(); ++i)
        {
            auto* raw = static_cast<TamexRawData*>(boards->At(i));
            if (!raw) continue;
            int k = -1, max_board = 0;
            std::uint16_t expected_wr = 0;
            if (raw->ProcId() == 75 && raw->DetectorName() == "FATIMA")
                { k = 0; max_board = 4; expected_wr = 0x1600; }
            else if (raw->ProcId() == 80 && raw->DetectorName() == "bPlast")
                { k = 1; max_board = 9; expected_wr = 0x500; }
            else if (raw->ProcId() == 100 && raw->DetectorName() == "BGO")
                { k = 2; max_board = 3; expected_wr = 0x1900; }

            if (k < 0 || raw->Board() >= max_board || raw->FormatVersion() != 4)
            {
                ++bad_metadata;
                continue;
            }
            seen |= 1u << k;
            ++counts[k];
            word_counts[k] += raw->Words().size();
            // An absent optional WR header may yield zero; count only
            // present-but-conflicting subsystem IDs.
            if (raw->WrSubsystem() && raw->WrSubsystem() != expected_wr)
                ++wr_mismatches;
        }
        if ((seen & (seen - 1)) != 0) ++multi_source_events;
    }

    std::cout << "Events: " << n << "\n"
              << "Procid  Detector  Boards  Raw words\n"
              << "75      FATIMA    " << counts[0] << "      " << word_counts[0] << "\n"
              << "80      bPlast    " << counts[1] << "      " << word_counts[1] << "\n"
              << "100     BGO       " << counts[2] << "      " << word_counts[2] << "\n"
              << "Events containing multiple TAMEX sources: " << multi_source_events << "\n"
              << "Invalid procid/name/board/version: " << bad_metadata << "\n"
              << "Present WR subsystem mismatches: " << wr_mismatches << "\n";
    if (bad_metadata || wr_mismatches)
        std::cerr << "WARNING: Shared TAMEX metadata validation failed.\n";
}
