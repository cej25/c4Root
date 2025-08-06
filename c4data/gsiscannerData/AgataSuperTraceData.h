#ifndef AgataSuperTraceData_H
#define AgataSuperTraceData_H

#include "TObject.h"


#define TRACE_LENGTH 200

class AgataSuperTraceData : public TObject
{
    public:
        // Default Constructor
        AgataSuperTraceData();

        // Destructor
        virtual ~AgataSuperTraceData() {};

        // Getters
        inline const int Get_nfired_segments() const { return nfired_segments; }
        inline const uint64_t Get_event_trigger_time() const { return fevent_trigger_time; }
        inline const uint64_t Get_hit_pattern() const { return fhit_pattern; }

                
        inline const double Get_core_trigger_time() const { return fcore_trigger_time; }
        inline const double Get_core_energy() const { return fcore_energy; }


        inline const double Get_segment_energy(char segment_sector, int segment_layer) const { return fsegment_energy[Get_segment_id(segment_sector,segment_layer)]; }
        inline const double Get_segment_trigger_time(char segment_sector, int segment_layer) const { return fsegment_trigger_time[Get_segment_id(segment_sector,segment_layer)]; }
        
        inline const double* Get_supertrace() const { return supertrace; }
        inline const double Get_supertrace_index(int idx) const { return supertrace[idx]; }

        inline const double* Get_supertrace_range_ptr(char segment_sector, int segment_layer) const {
            
            size_t start = (Get_segment_id(segment_sector,segment_layer)+1)*TRACE_LENGTH;

            return supertrace + start;
        }

        inline const double* Get_supertrace_range_core() const {
            return supertrace;
        }
        
        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }


        inline const int Get_segment_id(char segment_sector, int segment_layer) const { return ((int)segment_sector-65)*6 + segment_layer -1; }


        //Setters:
        void Set_nfired_segments(int v) { nfired_segments = v; }
        void Set_event_trigger_time(uint64_t v) { fevent_trigger_time = v; }
        void Set_hit_pattern(uint64_t v) { fhit_pattern = v; }
        void Set_core_trigger_time(double v) { fcore_trigger_time = v; }
        void Set_core_energy(double v) { fcore_energy = v; }

        void Set_segment_energy(char segment_sector, int segment_layer, double energy) {
            fsegment_energy[Get_segment_id(segment_sector, segment_layer)] = energy;
        }

        void Set_segment_trigger_time(char segment_sector, int segment_layer, double time) {
            fsegment_trigger_time[Get_segment_id(segment_sector, segment_layer)] = time;
        }

        void Set_all_segment_energy(const double* energies) {
            for (int i = 0; i < 36; ++i)
                fsegment_energy[i] = energies[i];
        }

        void Set_all_segment_trigger_time(const double* times) {
            for (int i = 0; i < 36; ++i)
                fsegment_trigger_time[i] = times[i];
        }

        void Set_supertrace_sample(size_t index, double value) {
            supertrace[index] = value;  
        }

        void Set_supertrace(const double* trace) {
            for (size_t i = 0; i < 37*TRACE_LENGTH; ++i)
                supertrace[i] = trace[i];
        }

        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }

    protected:
        // Data items
        int nfired_segments;
        uint64_t fevent_trigger_time;
        uint64_t fhit_pattern;
        
        double fcore_trigger_time;
        double fcore_energy;

        double fsegment_trigger_time[36];
        double fsegment_energy[36];

        double supertrace[37*TRACE_LENGTH]; //core first
        
        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(AgataSuperTraceData, 1);
};



#endif
