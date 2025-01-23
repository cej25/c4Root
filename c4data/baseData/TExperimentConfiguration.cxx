#include "TExperimentConfiguration.h"

#include "c4Logger.h"
#include "FairLogger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TExperimentConfiguration* TExperimentConfiguration::instance = nullptr;
uint64_t TExperimentConfiguration::exp_start_time = 1.5e19;
uint64_t TExperimentConfiguration::exp_end_time = 1.5e19;




TExperimentConfiguration::TExperimentConfiguration()
{
    if(exp_start_time == 1.5e19)
    {
        c4LOG(warn, "Experiment start time not set.");
    }
    if(exp_end_time == 1.5e19)
    {
        c4LOG(warn, "Experiment end time not set.");
    }
}