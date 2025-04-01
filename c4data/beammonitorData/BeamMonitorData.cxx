#include "BeamMonitorData.h"

BeamMonitorItem::BeamMonitorItem()
{

}

void BeamMonitorItem::SetAll(UInt_t dt)
{
    tdelta = dt;
}


ClassImp(BeamMonitorItem)