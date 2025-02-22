// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TString.h"

// c4
#include "BB7FebexRaw2Cal.h"
#include "c4Logger.h"

// ROOT
#include <vector>
#include <numeric>

BB7FebexRaw2Cal::BB7FebexRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   bb7array(nullptr)
    ,   bb7calImplants(new std::vector<BB7FebexCalItem>)
    ,   bb7calDecays(new std::vector<BB7FebexCalItem>)
{
    bb7_config = TBB7FebexConfiguration::GetInstance();
    detector_mapping = bb7_config->Mapping();   // ??
}



BB7FebexRaw2Cal::~BB7FebexRaw2Cal()
{
    delete bb7array;
    delete bb7calImplants;
    delete bb7calDecays;
}

InitStatus BB7FebexRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    bb7array = mgr->InitObjectAs<decltype(bb7array)>("BB7FebexData");
    c4LOG_IF(fatal, !bb7array, "Branch BB7FebexData not found!");
    
    mgr->RegisterAny("BB7FebexCalImplants", bb7calImplants, !fOnline);
    mgr->RegisterAny("BB7FebexCalDecays", bb7calDecays, !fOnline);

    return kSUCCESS;
}


void BB7FebexRaw2Cal::Exec(Option_t* option)
{
    bb7calImplants->clear();
    bb7calDecays->clear();

    // std::cout << "EVENT :: " << std::endl;
    for (auto const & bb7item : *bb7array)
    {
        if (bb7item.Get_crate_id() == 0)
        {
            std::cout << "board:: " << bb7item.Get_board_id() << std::endl;
            std::cout << "channel:: " << bb7item.Get_channel_id_traces() << std::endl;
        }
        // std::cout << "Crate :: " << bb7item.Get_crate_id() << std::endl;
        // std::cout << "Board :: " << bb7item.Get_board_id() << std::endl;
        // std::cout << "Channel :: " << bb7item.Get_channel_id_traces() << std::endl;
        // channel id or channel id traces?
        std::pair<int, int> febex_mc = {bb7item.Get_board_id(), bb7item.Get_channel_id_traces()};
        std::pair<int, std::pair<int, int>> unmapped_channel = {bb7item.Get_crate_id(), febex_mc};
        //Get_channel_id_traces() when taking the id information from the trace header
        //Get_channel_id() when taking the id information from the header

        if (bb7_config->MappingLoaded())
        {
            if (detector_mapping.count(unmapped_channel) > 0)
            {
                int dssd = detector_mapping.at(unmapped_channel).first;
                int side = detector_mapping.at(unmapped_channel).second.first;
                int strip = detector_mapping.at(unmapped_channel).second.second;

                // std::cout << "dssd:: " << dssd << std::endl;
                // std::cout << "side:: " << side << std::endl;
                // std::cout << "strip:: " << strip << std::endl;

                uint32_t energy = bb7item.Get_channel_energy();
                double energy_calib = energy;

                if (bb7_config->CalibrationLoaded())
                {
                    // do calibration, calculation, whatever
                    // energy_calib = ... 
                }

                if (energy > 400000000)
                {
                    // std::cout << "weird energy, I guess:: " << std::endl;
                    // std::cout << "Channel:: " << bb7item.Get_channel_id() << std::endl;
                    // std::cout << "Time:: " << bb7item.Get_channel_time() << std::endl;

                    continue;
                }

                int64_t absolute_time = bb7item.Get_wr_t() + bb7item.Get_channel_time() - bb7item.Get_board_event_time();

                if (energy > implantThreshold)
                {
                    // implant 
                    auto & entry = bb7calImplants->emplace_back();
                    entry.SetAll(
                        bb7item.Get_wr_t(),
                        dssd,
                        side,
                        strip,
                        bb7item.Get_channel_energy(),
                        bb7item.Get_trace(),
                        energy_calib,
                        bb7item.Get_board_event_time(),
                        bb7item.Get_channel_time(),
                        absolute_time,
                        bb7item.Get_pileup(),
                        bb7item.Get_overflow()
                    );
                }
                else if (energy > decayThreshold)
                {
                    // decay
                    auto & entry = bb7calDecays->emplace_back();
                    entry.SetAll(
                        bb7item.Get_wr_t(),
                        dssd,
                        side,
                        strip,
                        bb7item.Get_channel_energy(),
                        bb7item.Get_trace(),
                        energy_calib,
                        bb7item.Get_board_event_time(),
                        bb7item.Get_channel_time(),
                        absolute_time,
                        bb7item.Get_pileup(),
                        bb7item.Get_overflow()
                    );
                }
            }
            // else c4LOG(warn, "Unmapped data? Board: "  << unmapped_channel.second.first << " Channel: " << unmapped_channel.second.second);

            // possibly stuff with residuals

        }
    }
}

void BB7FebexRaw2Cal::FinishEvent()
{

}

void BB7FebexRaw2Cal::FinishTask()
{
}