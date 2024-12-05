#ifndef BeamMonitorData_H
#define BeamMonitorData_H

#include "TObject.h"
#include <vector>

class BeamMonitorData : public TObject
{
    public:
        // Default Constructor
        BeamMonitorData();

        // Destructor
        virtual ~BeamMonitorData() {};

        // Getters
        inline const std::vector<uint32_t> Get_S2_data() const { return dtS2; }
        inline const std::vector<uint32_t> Get_S4_data() const { return dtS4; }

        // Setters
        void Set_S2_data(std::vector<uint32_t> data) { dtS2 = data; }
        void Set_S4_data(std::vector<uint32_t> data) { dtS4 = data; }

    protected:
        // Data items
        std::vector<uint32_t> dtS2;
        std::vector<uint32_t> dtS4;
    

    public:
        ClassDef(BeamMonitorData, 1)
};

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
