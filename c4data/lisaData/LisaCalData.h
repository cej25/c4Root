#ifndef LisaCalData_H
#define LisaCalData_H

#include "TObject.h"
#include <vector>

// :: Not in use -> use CalItam instead
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

        //inline uint64_t Get_board_event_t() const { return f_board_event_t; }
        //inline uint64_t Get_channel_event_t() const { return f_channel_event_t; }
       


        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }

        inline void SetLayers(std::vector<int> layers) { f_layers = layers; }
        inline void SetCities(std::vector<std::string> cities) { f_cities = cities; }
        inline void SetXPositions(std::vector<int> xpositions) { f_xpositions = xpositions; }
        inline void SetYPositions(std::vector<int> ypositions) { f_ypositions = ypositions; }
        inline void SetRawEnergy(std::vector<uint32_t> raw_energy) { f_raw_energy = raw_energy; }
        inline void SetRawTraces(std::vector<uint32_t> raw_traces) { f_raw_traces = raw_traces; }

        //inline void Set_board_event_t(uint64_t evt_t) { f_board_event_t = evt_t; }
        //inline void Set_channel_event_t(uint64_t ch_t) { f_channel_event_t = ch_t; }

    protected:

        // variables
        uint64_t fwr_t;
        std::vector<int> f_layers;
        std::vector<std::string> f_cities;
        std::vector<int> f_xpositions;
        std::vector<int> f_ypositions;
        std::vector<uint32_t> f_raw_energy;
        std::vector<uint32_t> f_raw_traces;
        
        uint64_t f_board_event_t;
        uint64_t f_channel_event_t;


    
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
                    std::vector<uint16_t> tr,
                    double e_GM,
                    uint64_t evt_t,
                    uint64_t ch_t,
                    uint64_t evtno,
                    int pu,
                    int ov); 
        void Reset();

        uint64_t Get_wr_t() const;
        int Get_layer_id() const;
        std::string Get_city() const;
        int Get_xposition() const;
        int Get_yposition() const;
        uint32_t Get_energy() const;
        std::vector<uint16_t> Get_trace() const;
        double Get_energy_GM() const;
        // uint64_t Get_board_eventt_time();
        // uint64_t Get_channel_event_time();
        uint64_t Get_evtno();
        int Get_pileup() const;
        int Get_overflow() const;

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
        double energy_GM;
        uint64_t board_event_time;
        uint64_t ch_event_time;
        uint64_t event_no;
        int pileup;
        int overflow;
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

inline double LisaCalItem::Get_energy_GM() const
{
    return energy_GM;
}

// inline uint64_t LisaCalItem::Get_board_event_time() const
// {
//     return board_event_time;
// }

// inline uint64_t LisaCalItem::Get_channel_event_time() const
// {
//     return ch_event_time;
// }

inline int LisaCalItem::Get_pileup() const
{
    return pileup;
}

inline int LisaCalItem::Get_overflow() const
{
    return overflow;
}


#endif