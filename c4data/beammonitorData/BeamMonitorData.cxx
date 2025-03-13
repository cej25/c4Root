#include "BeamMonitorData.h"

BeamMonitorItem::BeamMonitorItem()
{

}

void BeamMonitorItem::SetAll(uint32_t dt)
{
    tdelta = dt;
}


ClassImp(BeamMonitorItem)