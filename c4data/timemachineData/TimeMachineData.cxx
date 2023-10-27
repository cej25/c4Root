#include "TimeMachineData.h"



TimeMachineData::TimeMachineData():
                        fdetector_system(""),
                        fundelayed_time(0),
                        fdelayed_time(0),
                        //fdelta_time(0),
                        fwr_subsystem_id(0),
                        fwr_t(0){};

TimeMachineData::TimeMachineData(TString detector_system,double undelayed_time,double delayed_time,uint32_t wr_subsystem_id, uint32_t wr_t):
                        fdetector_system(detector_system),
                        fundelayed_time(undelayed_time),
                        fdelayed_time(delayed_time),
                        //fdelta_time(delta_time),
                        fwr_subsystem_id(wr_subsystem_id),
                        fwr_t(wr_t){};

ClassImp(TimeMachineData)