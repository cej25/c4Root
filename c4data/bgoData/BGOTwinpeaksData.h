#ifndef BGOTwinpeaksData_H
#define BGOTwinpeaksData_H

#include "TObject.h"

class BGOTwinpeaksData : public TObject
{
    public:
        // Default Constructor
        BGOTwinpeaksData();

        BGOTwinpeaksData(
        UShort_t trig,
        UShort_t board_id,
        UInt_t ch_ID,

        Long64_t accepted_trigger_time,
        UInt_t accepted_lead_epoch_counter,
        UInt_t accepted_lead_coarse_T,
        Double_t accepted_lead_fine_T,
        
        UInt_t lead_epoch_counter,
        UInt_t lead_coarse_T,
        Double_t lead_fine_T,

        UInt_t trail_epoch_counter,
        UInt_t trail_coarse_T,
        Double_t trail_fine_T,
        UShort_t wr_subsystem_id,
        Long64_t wr_t);

        // Destructor
        virtual ~BGOTwinpeaksData() {}

        // Getters
        inline const UShort_t Get_trigger() const { return ftrig; }
        inline const UShort_t Get_board_id() const {return fboard_id; }
        inline const UInt_t Get_ch_ID() const {return fch_ID; }
        inline const Long64_t Get_accepted_trigger_time() const { return faccepted_trigger_time; }
        inline const UInt_t Get_accepted_lead_epoch_counter() const {return faccepted_lead_epoch_counter; }
        inline const UInt_t Get_accepted_lead_coarse_T() const {return faccepted_lead_coarse_T; }
        inline const Double_t Get_accepted_lead_fine_T() const {return faccepted_lead_fine_T; }
        inline const UInt_t Get_lead_epoch_counter() const {return flead_epoch_counter; }
        inline const UInt_t Get_lead_coarse_T() const {return flead_coarse_T; }
        inline const Double_t Get_lead_fine_T() const {return flead_fine_T; }
        inline const UInt_t Get_trail_epoch_counter() const {return ftrail_epoch_counter; }
        inline const UInt_t Get_trail_coarse_T() const {return ftrail_coarse_T; }
        inline const Double_t Get_trail_fine_T() const {return ftrail_fine_T; }
        inline const UShort_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const Long64_t Get_wr_t() const { return fwr_t; }

        // Setters
        void Set_trigger(UShort_t v) { ftrig = v; }
        void Set_board_id(UShort_t v){ fboard_id = v; }
        void Set_ch_ID(UInt_t v){ fch_ID = v; }
        void Set_accepted_trigger_time(Long64_t v) { faccepted_trigger_time = v; }
        void Set_accepted_lead_epoch_counter(UInt_t v){ faccepted_lead_epoch_counter = v; }
        void Set_accepted_lead_coarse_T(UInt_t v){ faccepted_lead_coarse_T = v; }
        void Set_accepted_lead_fine_T(Double_t v){ faccepted_lead_fine_T = v; }
        void Set_lead_epoch_counter(UInt_t v){ flead_epoch_counter = v; }
        void Set_lead_coarse_T(UInt_t v){ flead_coarse_T = v; }
        void Set_lead_fine_T(Double_t v){ flead_fine_T = v; }
        void Set_trail_epoch_counter(UInt_t v){ ftrail_epoch_counter = v; }
        void Set_trail_coarse_T(UInt_t v){ ftrail_coarse_T = v; }
        void Set_trail_fine_T(Double_t v){ ftrail_fine_T = v; }
        void Set_wr_subsystem_id(UShort_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(Long64_t v) { fwr_t = v; }

    protected:
        // Data items
        UShort_t ftrig;
        UShort_t fboard_id;
        UInt_t fch_ID;

        Long64_t faccepted_trigger_time;
        UInt_t faccepted_lead_epoch_counter;
        UInt_t faccepted_lead_coarse_T;
        Double_t faccepted_lead_fine_T;
    
        UInt_t flead_epoch_counter;
        UInt_t flead_coarse_T;
        Double_t flead_fine_T;

        //if these guys are zero, no trail was found:
        UInt_t ftrail_epoch_counter;
        UInt_t ftrail_coarse_T;
        Double_t ftrail_fine_T;

        //whiterabbit
        UShort_t fwr_subsystem_id;
        Long64_t fwr_t;
    

    public:
        ClassDef(BGOTwinpeaksData, 1);
};

#endif
