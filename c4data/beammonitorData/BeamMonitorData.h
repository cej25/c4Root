#ifndef BeamMonitorData_H
#define BeamMonitorData_H

#include "TObject.h"
#include <cstdint>
#include <vector>


// we create an item because perhaps other members are needed, later
// for now it is literally just a time delta, UInt_t
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

class BeamMonitorRawData : public TObject
{
public:
    std::uint64_t wrTimestamp = 0;
    std::uint16_t wrId = 0;
    std::vector<std::uint32_t> S2;
    std::vector<std::uint32_t> S4;

    ClassDef(BeamMonitorRawData, 1);
};

#endif
