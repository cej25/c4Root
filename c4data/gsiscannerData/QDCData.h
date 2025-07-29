#ifndef QDCData_H
#define QDCData_H

#include "TObject.h"

class QDCData : public TObject
{
    public:
        // Default Constructor
        QDCData();

        QDCData(
        int board_id,
        int ch_ID,

        int16_t charge,

        int wr_subsystem_id,
        int64_t wr_t
        );

        // Destructor
        virtual ~QDCData() {}

        // Getters
        inline const int Get_board_id() const {return fboard_id; }
        inline const int Get_ch_ID() const {return fch_ID; }
        
        
        inline const int16_t Get_charge() const {return fcharge; }
        
        inline const int Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const int64_t Get_wr_t() const { return fwr_t; }

        // Setters
        void Set_board_id(int v){ fboard_id = v; }
        void Set_ch_ID(int v){ fch_ID = v; }
        
        void Set_charge(int16_t v){ fch_ID = v; }

        void Set_wr_subsystem_id(int v) { fwr_subsystem_id = v; }
        void Set_wr_t(int64_t v) { fwr_t = v; }

    protected:
        // Data items
        int fboard_id;
        int fch_ID;
        
        int16_t fcharge;
        
        //whiterabbit
        int fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(QDCData, 1);
};

#endif
