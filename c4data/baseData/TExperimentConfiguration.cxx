#include "TExperimentConfiguration.h"

#include "c4Logger.h"
#include "FairLogger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TExperimentConfiguration* TExperimentConfiguration::instance = nullptr;
uint64_t TExperimentConfiguration::exp_start_time = 0;


TExperimentConfiguration::TExperimentConfiguration()
{
    
}