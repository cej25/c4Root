#ifndef BeamMonitorData_H
#define BeamMonitorData_H

#include "TObject.h"
#include <vector>


// we create an item because perhaps other members are needed, later
// for now it is literally just a time delta, uint32_t
class BeamMonitorItem : public TObject
{
    public:
        BeamMonitorItem();

        void SetAll(UInt_t dt);
        void Reset();

        UInt_t GetTimeDelta() const { return tdelta; }

        ClassDef(BeamMonitorItem, 1);
    
    private:
        UInt_t tdelta;
};

#endif
