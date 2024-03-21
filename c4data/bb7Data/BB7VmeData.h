#ifndef BB7VmeData_H
#define BB7VmeData_H

#include "TObject.h"
#include <vector>

class BB7VmeData : public TObject
{
    public:
        BB7VmeData();

        virtual ~BB7VmeData() {};

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }
        
        inline std::vector<uint32_t> Get_v7x5_geo() const { return fv7x5_geo; }
        inline std::vector<uint32_t> Get_v7x5_channel() const { return fv7x5_channel; }
        inline std::vector<uint32_t> Get_v7x5_data() const { return fv7x5_data; }


        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }

        inline void Set_v7x5_geo(std::vector<uint32_t> geos) { fv7x5_geo = geos; }
        inline void Set_v7x5_channel(std::vector<uint32_t> channels) { fv7x5_channel = channels; }
        inline void Set_v7x5_data(std::vector<uint32_t> data) { fv7x5_data = data; }

    protected:

        // variables
        uint64_t fwr_t;

        std::vector<uint32_t> fv7x5_geo;
        std::vector<uint32_t> fv7x5_channel;
        std::vector<uint32_t> fv7x5_data;

    
    public:
        ClassDef(BB7VmeData, 1);
};


#endif