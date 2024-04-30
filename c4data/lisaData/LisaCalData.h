#ifndef LisaCalData_H
#define LisaCalData_H

#include "TObject.h"
#include <vector>

class LisaCalData : public TObject
{
    public:
        LisaCalData();
        
        virtual ~LisaCalData() {};

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }

        inline std::vector<int> GetLayers() const { return f_layers; }
        inline std::vector<std::string> GetCities() const { return f_cities; }
        inline std::vector<int> GetXPositions() const { return f_xpositions; }
        inline std::vector<int> GetYPositions() const { return f_ypositions; }
        inline std::vector<uint32_t> GetRawEnergy() const { return f_raw_energy; }
        inline std::vector<uint32_t> GetRawTraces() const { return f_raw_traces; }
       


        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }

        inline void SetLayers(std::vector<int> layers) { f_layers = layers; }
        inline void SetCities(std::vector<std::string> cities) { f_cities = cities; }
        inline void SetXPositions(std::vector<int> xpositions) { f_xpositions = xpositions; }
        inline void SetYPositions(std::vector<int> ypositions) { f_ypositions = ypositions; }
        inline void SetRawEnergy(std::vector<uint32_t> raw_energy) { f_raw_energy = raw_energy; }
        inline void SetRawTraces(std::vector<uint32_t> raw_traces) { f_raw_traces = raw_traces; }

    protected:

        // variables
        uint64_t fwr_t;
        std::vector<int> f_layers;
        std::vector<std::string> f_cities;
        std::vector<int> f_xpositions;
        std::vector<int> f_ypositions;
        std::vector<uint32_t> f_raw_energy;
        std::vector<uint32_t> f_raw_traces;


    
    public:
        ClassDef(LisaCalData, 1);
};


class LisaCalItem : public TObject
{
    public:
        LisaCalItem();

        void SetAll(uint64_t wr,
                    int layer,
                    std::string c,
                    int xpos,
                    int ypos,
                    int e,
                    std::vector<uint16_t> tr); // ?
        void Reset();

        uint64_t Get_wr_t() const;
        int Get_layer_id() const;
        std::string Get_city() const;
        int Get_xposition() const;
        int Get_yposition() const;
        uint32_t Get_energy() const;
        std::vector<uint16_t> Get_trace() const;

        // Getters
        ClassDefNV(LisaCalItem, 2);
    private:
        uint64_t wr_t;
        int layer_id;
        std::string city; // name
        int xposition;
        int yposition;
        uint32_t energy; // double? int?
        std::vector<uint16_t> trace;
        // timing info for correlations

};

inline uint64_t LisaCalItem::Get_wr_t() const
{
    return wr_t;
}

inline int LisaCalItem::Get_layer_id() const
{
    return layer_id;
}

inline std::string LisaCalItem::Get_city() const
{
    return city;
}

inline int LisaCalItem::Get_xposition() const
{
    return xposition;
}

inline int LisaCalItem::Get_yposition() const
{
    return yposition;
}

inline uint32_t LisaCalItem::Get_energy() const
{
    return energy;
}

inline std::vector<uint16_t> LisaCalItem::Get_trace() const
{
    return trace;
}

#endif