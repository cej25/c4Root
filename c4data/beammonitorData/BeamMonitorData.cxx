#include "BeamMonitorData.h"

BeamMonitorData::BeamMonitorData()
{
}

BeamMonitorItem::BeamMonitorItem()
{

}

void BeamMonitorItem::SetAll(uint32_t dt)
{
    tdelta = dt;
}


ClassImp(BeamMonitorItem)