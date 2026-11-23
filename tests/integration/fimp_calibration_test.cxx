// Build the fimp_calibration_test target and run it in the configured c4Root environment.
#undef NDEBUG
#include <cassert>

#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairTask.h"
#include "FimpRaw2Cal.h"
#include "FimpReader.h"

#include <cstdint>
#include <vector>

int main()
{
    FairRunOnline run;
    EventHeader header;
    auto* manager = FairRootManager::Instance();
    manager->Register("EventHeader.", "EventHeader", &header, false);

    EXT_STR_h101_fimp_onion_t bank{};
    ext_data_struct_info info;
    FimpReader reader(&bank, 0);
    reader.SetOnline(true);
    assert(reader.Init(&info));
    reader.DoFineTimeCalibration();

    bank.fimp_ts_t[0] = 1;
    bank.fimp_data_time_coarseM = 2;
    bank.fimp_data_time_coarseMI[0] = 1;
    bank.fimp_data_time_coarseMI[1] = 2;
    bank.fimp_data_time_coarseME[0] = 2;
    bank.fimp_data_time_coarseME[1] = 3;
    bank.fimp_data_time_coarse = bank.fimp_data_time_fine = bank.fimp_data_lead_or_trail = 3;
    bank.fimp_data_time_coarsev[0] = 100;
    bank.fimp_data_time_coarsev[1] = 101;
    bank.fimp_data_time_coarsev[2] = 102;
    bank.fimp_data_time_finev[0] = 17;
    bank.fimp_data_time_finev[1] = 18; // First invalid fine-time code.
    bank.fimp_data_lead_or_trailv[2] = 1;

    assert(reader.Read());
    auto* hits = const_cast<std::vector<FimpItem>*>(
        manager->InitObjectAs<const std::vector<FimpItem>*>("FimpData"));
    assert(hits && hits->size() == 1);
    assert(hits->front().Get_lead_coarse_time() == std::vector<std::uint16_t>{100});
    assert(hits->front().Get_raw_lead_fine_time().front() == 17);

    // Exercise a saved hit with more coarse than fine samples on the trailing edge.
    hits->emplace_back().SetAll(1, 0, 0, 1, {10, 11}, {1, 2}, {12, 13}, {3}, {}, {});
    FimpRaw2Cal calibration;
    calibration.SetOnline(true);
    assert(calibration.Init() == kSUCCESS);
    calibration.Exec(nullptr);
    const auto* calibrated = manager->InitObjectAs<const std::vector<FimpCalItem>*>("FimpCalData");
    assert(calibrated && calibrated->size() == 2);
    assert(calibrated->back().Get_channel() == 1);
    assert(calibrated->back().Get_ToT() == 2 * 6667 - 2);
}
