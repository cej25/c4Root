#ifndef EventData_H
#define EventData_H

#include "TObject.h"

class EventData : public TObject
{
    public:
        EventData();

        ~EventData();

        // Get
        inline Bool_t Get_Spill_Flag() { return SpillOn; }
        
        // Set
        inline void Set_Spill_Flag(Bool_t flag) { SpillOn = flag; }

    private:

        Bool_t SpillOn;

    public:
        ClassDef(EventData, 1)
};



#endif
