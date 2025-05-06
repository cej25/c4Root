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
 *                            J.E.L. Larsson                                  *
 *                               06.05.25                                     *
 ******************************************************************************/

#include "TimeMachineData.h"


TimeMachineData::TimeMachineData():
                        fundelayed_time(0),
                        fdelayed_time(0),
                        //fdelta_time(0),
                        fwr_subsystem_id(0),
                        fwr_t(0){};

TimeMachineData::TimeMachineData(double undelayed_time,double delayed_time,uint32_t wr_subsystem_id, uint64_t wr_t):
                        fundelayed_time(undelayed_time),
                        fdelayed_time(delayed_time),
                        //fdelta_time(delta_time),
                        fwr_subsystem_id(wr_subsystem_id),
                        fwr_t(wr_t){};

ClassImp(TimeMachineData)