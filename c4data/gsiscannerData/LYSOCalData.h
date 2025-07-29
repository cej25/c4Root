#ifndef LYSOCalData_H
#define LYSOCalData_H

#include "TObject.h"

class LYSOCalData : public TObject
{
    public:
        // Default Constructor
        LYSOCalData(){
            fired_anodes = 0;

            for (int i = 0; i<16;i++){
                board_id_x[i] = 0;
                board_id_y[i] = 0;
                ch_id_x[i] = 0;
                ch_id_y[i] = 0;
                charge_x[i] = 0;
                charge_y[i] = 0;
                e_x[i] = 0;
                e_y[i] = 0;
            }
        };

        // Destructor
        virtual ~LYSOCalData() {}

        // Getters
        inline const int Get_fired_anodes() const { return fired_anodes; }

        inline const int Get_board_id_x(int anode_number) const {return board_id_x[anode_number-1]; }
        inline const int Get_ch_ID_x(int anode_number) const {return ch_id_x[anode_number-1]; }
        inline const int16_t Get_charge_x(int anode_number) const {return charge_x[anode_number-1]; }
        inline const double Get_energy_x(int anode_number) const {return e_x[anode_number-1]; }
        
        inline const int Get_board_id_y(int anode_number) const {return board_id_y[anode_number-1]; }
        inline const int Get_ch_ID_y(int anode_number) const {return ch_id_y[anode_number-1]; }
        inline const int16_t Get_charge_y(int anode_number) const {return charge_y[anode_number-1]; }
        inline const double Get_energy_y(int anode_number) const {return e_y[anode_number-1]; }
        
        
        inline const double Get_posx() const {return posx; }
        inline const double Get_posy() const {return posy; }
        
        inline const int Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const int64_t Get_wr_t() const { return fwr_t; }

        // Setters
        void Set_board_id_x(int anode_number, int v) {board_id_x[anode_number-1] = v; }
        void Set_ch_ID_x(int anode_number, int v) {ch_id_x[anode_number-1] = v; }
        void Set_charge_x(int anode_number, int16_t v) {charge_x[anode_number-1] = v; }
        void Set_energy_x(int anode_number, double v) {e_x[anode_number-1] = v; fired_anodes++; }
        
        void Set_board_id_y(int anode_number, int v) {board_id_y[anode_number-1] = v; }
        void Set_ch_ID_y(int anode_number, int v) {ch_id_y[anode_number-1] = v; }
        void Set_charge_y(int anode_number, int16_t v) {charge_y[anode_number-1] = v; }
        void Set_energy_y(int anode_number, double v) {e_y[anode_number-1] = v; fired_anodes++; }

        void Set_posx(double x) {posx = x;}
        void Set_posy(double y) {posy = y;}

        void Set_wr_subsystem_id(int v) { fwr_subsystem_id = v; }
        void Set_wr_t(int64_t v) { fwr_t = v; }

    protected:
        // Data items

        //index is the anode number 0 - 15 for the x and y grids:
        int board_id_x[16];
        int board_id_y[16];
        
        int ch_id_x[16];
        int ch_id_y[16];


        int16_t charge_x[16];
        int16_t charge_y[16];
        
        double e_x[16];
        double e_y[16];

        double posx;
        double posy;

        int fired_anodes;

        //raw x?
        //raw y?
            
        //whiterabbit if needed in future but not yet used:
        int fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(LYSOCalData, 1);
};

#endif
