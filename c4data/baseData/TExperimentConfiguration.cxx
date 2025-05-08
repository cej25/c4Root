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
Int_t TExperimentConfiguration::bos_trig = 12;
Int_t TExperimentConfiguration::eos_trig = 13;




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