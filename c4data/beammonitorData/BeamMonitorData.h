#ifndef BeamMonitorData_H
#define BeamMonitorData_H

#include "TObject.h"

class BeamMonitorData : public TObject
{
    public:
        // Default Constructor
        BeamMonitorData();

        BeamMonitorData(UInt_t S2, UInt_t S4);

        // Destructor
        virtual ~BeamMonitorData() {};

        // Getters
        inline const UInt_t GetS2Data() const { return dtS2; }
        inline const UInt_t GetS4Data() const { return dtS4; }

        // Setters
        void SetS2Data(UInt_t v) { dtS2 = v; }
        void SetS4Data(UInt_t v) { dtS4 = v; }

    protected:
        // Data items
        UInt_t dtS2;
        UInt_t dtS4;
    

    public:
        ClassDef(BeamMonitorData, 1)
};

#endif
