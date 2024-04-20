#ifndef TimeMachineData_H
#define TimeMachineData_H

#include "TString.h"
#include "TObject.h"

class TimeMachineData : public TObject
{
    public:
        // Default Constructor
        TimeMachineData();

        TimeMachineData(double undelayed_time,double delta_time, uint32_t wr_subsystem_id, uint32_t wr_t);

        // Destructor
        virtual ~TimeMachineData() {};

        // Getters
        
        inline const double Get_undelayed_time() const {return fundelayed_time;}
        inline const double Get_delayed_time() const {return fdelayed_time;}
        //inline const double Get_delta_time() const {return fdelta_time;}
        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }



        // Setters
        
        void Set_undelayed_time(double v){fundelayed_time = v;}
        void Set_delayed_time(double v){fdelayed_time = v;}
        //void Set_delta_time(double v){fdelta_time = v;}
        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }

    protected:
        // Data items
        
        //system:
        double fundelayed_time;
        double fdelayed_time;
        //double fdelta_time;
        
        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(TimeMachineData, 1);
};

#endif
