#ifndef BB7VmeCalData_H
#define BB7VmeCalData_H

#include "TObject.h"
#include <vector>

class BB7VmeCalData : public TObject
{
    public:
        BB7VmeCalData();

        virtual ~BB7VmeCalData() {};

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }
        
        inline std::vector<int> Get_Sides() const { return fsides; }
        inline std::vector<int> Get_Strips() const { return fstrips; }
        inline std::vector<uint32_t> Get_Raw_ADC() const { return fraw_adc; }


        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }

        inline void Set_Sides(std::vector<int> sides) { fsides = sides; }
        inline void Set_Strips(std::vector<int> strips) { fstrips = strips; }
        inline void Set_Raw_ADC(std::vector<uint32_t> adc) { fraw_adc = adc; }

    protected:

        // variables
        uint64_t fwr_t;

        std::vector<int> fsides;
        std::vector<int> fstrips;
        std::vector<uint32_t> fraw_adc;

    
    public:
        ClassDef(BB7VmeCalData, 1);
};


#endif