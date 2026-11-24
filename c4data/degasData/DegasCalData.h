#ifndef DEGAS_CAL_DATA_H
#define DEGAS_CAL_DATA_H

#include "TObject.h"

#include <vector>

class DegasCalData : public TObject
{
    public:

        DegasCalData();

        DegasCalData(UShort_t trig,
                             ULong64_t event_trigger_time, // ns


                              Bool_t pileup,
                              UChar_t overflow,

                              Double_t channel_trigger_time, // ns
                              Double_t channel_energy, // keV
                              UInt_t crystal_id,
                              UInt_t detector_id,

                              UShort_t wr_subsystem_id,
                              ULong64_t wr_t, // ns
                              Long64_t absolute_event_time // ns
                              );

        ~DegasCalData() override = default;


        UShort_t Get_trigger() const { return ftrig; }
        ULong64_t Get_event_trigger_time() const { return fevent_trigger_time; }


        Bool_t Get_pileup() const { return fpileup; }
        UChar_t Get_overflow() const { return foverflow; }

        Double_t Get_channel_trigger_time() const { return fchannel_trigger_time; }
        Double_t Get_channel_energy() const { return fchannel_energy; }
        UInt_t Get_crystal_id() const { return fcrystal_id; }
        UInt_t Get_detector_id() const { return fdetector_id; }
        UShort_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        ULong64_t Get_wr_t() const { return fwr_t; }
        Long64_t Get_absolute_event_time() const { return fabsolute_event_time; }
        const std::vector<UShort_t>& Get_trace() const { return ftrace; }


        void Set_trigger(UShort_t v) { ftrig = v; }
        void Set_event_trigger_time(ULong64_t v) { fevent_trigger_time = v; }


        void Set_pileup(Bool_t v) { fpileup = v; }
        void Set_overflow(UChar_t v) { foverflow = v; }

        void Set_channel_trigger_time(Double_t v) { fchannel_trigger_time = v; }
        void Set_channel_energy(Double_t v) { fchannel_energy = v; }
        void Set_crystal_id(UInt_t v) { fcrystal_id = v; }
        void Set_detector_id(UInt_t v) { fdetector_id = v; }
        void Set_wr_subsystem_id(UShort_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(ULong64_t v) { fwr_t = v; }
        void Set_absolute_event_time(Long64_t v) { fabsolute_event_time = v; }
        void Set_trace(const std::vector<UShort_t>& trace) { ftrace = trace; }

    protected:


        UShort_t ftrig;
        ULong64_t fevent_trigger_time;


        Bool_t fpileup;
        UChar_t foverflow;

        Double_t fchannel_trigger_time;
        Double_t fchannel_energy;
        UInt_t fcrystal_id;
        UInt_t fdetector_id;

        UShort_t fwr_subsystem_id;
        ULong64_t fwr_t;
        Long64_t fabsolute_event_time;
        std::vector<UShort_t> ftrace;


    public:
        ClassDefOverride(DegasCalData, 1);
};

#endif
