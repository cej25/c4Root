#ifndef TFrsConfiguration_H
#define TFrsConfiguration_H

#include "TFRSParameter.h"
#include "TCutG.h"
#include <iostream>
#include <map> // needed?
#include <string>
#include <vector>
#include <set> // needed?

// TODO: add scaler map

class TFrsConfiguration
{
    public:
        static TFrsConfiguration const* GetInstance();
        static void Create();
        static void SetParameters(TFRSParameter*,
                        TMWParameter*,
                        TTPCParameter*,
                        TMUSICParameter*,
                        TLABRParameter*,
                        TSCIParameter*,
                        TIDParameter*,
                        TSIParameter*,
                        TMRTOFMSParameter*,
                        TRangeParameter*);
        static void SetConfigPath(std::string cp) { config_path = cp; }

        TFRSParameter* FRS() const;
        TMWParameter* MW() const;
        TTPCParameter* TPC() const;
        TMUSICParameter* MUSIC() const;
        TLABRParameter* LABR() const;
        TSCIParameter* SCI() const;
        TIDParameter* ID() const;
        TSIParameter* SI() const;
        TMRTOFMSParameter* MRTOF() const;
        TRangeParameter* Range() const;
        std::string GetConfigPath() const;

        // public should allow access with arrow operator?
        static Double_t fMin_Z, fMax_Z;
        static Double_t fMin_AoQ, fMax_AoQ;
        static Double_t fMin_x2, fMax_x2;
        static Double_t fMin_x4, fMax_x4;
        static Double_t fMin_a2, fMax_a2;
        static Double_t fMin_a4, fMax_a4;
        static Double_t fMin_y2, fMax_y2;
        static Double_t fMin_y4, fMax_y4;
        static Double_t fMin_b2, fMax_b2;
        static Double_t fMin_b4, fMax_b4;
        static Double_t fMin_dE, fMax_dE;
        static Double_t fMin_dEoQ, fMax_dEoQ;
        static Double_t fMin_dE_Music1, fMax_dE_Music1;
        static Double_t fMin_dE_Music2, fMax_dE_Music2;
        static Double_t fMin_dE_travMus_gate, fMax_dE_travMus_gate;

        static void Set_Z_range(Double_t, Double_t);
        static void Set_AoQ_range(Double_t, Double_t);
        static void Set_x2_range(Double_t, Double_t);
        static void Set_y2_range(Double_t, Double_t);
        static void Set_a2_range(Double_t, Double_t);
        static void Set_b2_range(Double_t, Double_t);
        static void Set_x4_range(Double_t, Double_t);
        static void Set_y4_range(Double_t, Double_t);
        static void Set_a4_range(Double_t, Double_t);
        static void Set_b4_range(Double_t, Double_t);
        static void Set_dEdeg_range(Double_t, Double_t);
        static void Set_dEdegoQ_range(Double_t, Double_t);
        static void Set_dE_Music1_range(Double_t, Double_t);
        static void Set_dE_Music2_range(Double_t, Double_t);
        static void Set_dE_travMusic_gate(Double_t, Double_t);


        //travMUSIC
        static Double_t fMin_dE_travMusic, fMax_dE_travMusic;
        static void Set_dE_travMusic_range(Double_t, Double_t);


        // need to be able to add 1 or multiple PIDs from different filetypes


        void Plot1D(bool option) { plot_1d = option; }

        bool plot_1d = true;
        

    private:

        static std::string config_path;
        TFrsConfiguration();

        static TFrsConfiguration* instance;

        static TFRSParameter* ffrs;
        static TMWParameter* fmw;
        static TTPCParameter* ftpc;
        static TMUSICParameter* fmusic;
        static TLABRParameter* flabr;
        static TSCIParameter* fsci;
        static TIDParameter* fid;
        static TSIParameter* fsi;
        static TMRTOFMSParameter* fmrtof;
        static TRangeParameter* frange;

        // Gates

        // Mappings
        char scaler_name_map[66][256];
};

inline TFrsConfiguration const* TFrsConfiguration::GetInstance()
{
    if (!instance)
    {
        TFrsConfiguration::Create();
    }
    return instance;
}

inline void TFrsConfiguration::Create()
{
    delete instance;
    instance = new TFrsConfiguration();
}

inline TFRSParameter* TFrsConfiguration::FRS() const
{
    return ffrs;
}

inline TMWParameter* TFrsConfiguration::MW() const
{
    return fmw;
}
inline TTPCParameter* TFrsConfiguration::TPC() const
{
    return ftpc;
}

inline TMUSICParameter* TFrsConfiguration::MUSIC() const
{
    return fmusic;
}

inline TLABRParameter* TFrsConfiguration::LABR() const
{
    return flabr;
}

inline TSCIParameter* TFrsConfiguration::SCI() const
{
    return fsci;
}

inline TIDParameter* TFrsConfiguration::ID() const
{
    return fid;
}

inline TSIParameter* TFrsConfiguration::SI() const
{
    return fsi;
}

inline TMRTOFMSParameter* TFrsConfiguration::MRTOF() const
{
    return fmrtof;
}

inline TRangeParameter* TFrsConfiguration::Range() const
{
    return frange;
}

inline std::string TFrsConfiguration::GetConfigPath() const
{
    return config_path;
}



#endif