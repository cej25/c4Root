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

        void SetAll(uint32_t dt);
        void Reset();

        uint32_t GetTimeDelta() const;

        ClassDef(BeamMonitorItem, 1);
    
    private:
        
        uint32_t tdelta;
};

inline uint32_t BeamMonitorItem::GetTimeDelta() const
{
    return tdelta;
}



#endif
