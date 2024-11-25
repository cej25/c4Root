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
        static void SetScalerMappingPath(std::string fp) { scaler_mapping_file = fp; }
        //static void SetExpStartTime();
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
        static void SetTravMusDriftFile(std::string fp) { tm_drift_coeff_file = fp; }
        static void SetAoQDriftFile(std::string fp) { aoq_drift_coeff_file = fp; }
        static void SetZ1DriftFile(std::string fp) { z1_drift_coeff_file = fp; }

    

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
        std::string ScalerName(int index) const;
        std::string SciName(int index) const;

        // Unpacking / Sorting
        // These should be set after reading some mapping, change later.
        int tpc_s2_geo = 12;
        int tpc_s3_geo = 8;
        int tpc_s4_geo = 8;


        // Analysis / Histograms
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
        static int frun_num;


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

        static Double_t fMin_dE_travMusic, fMax_dE_travMusic;
        static void Set_dE_travMusic_range(Double_t, Double_t);

        void Plot_TAC_1D(bool option) { plot_tac_1d = option; }
        void Plot_TAC_2D(bool option) { plot_tac_2d = option; }
        void Plot_MHTDC_1D(bool option) { plot_mhtdc_1d = option; }
        void Plot_MHTDC_2D(bool option) { plot_mhtdc_1d = option; }

        static void SetRunNumber(int run_num) { frun_num = run_num; }

        bool plot_tac_1d = true;
        bool plot_tac_2d = true;
        bool plot_mhtdc_1d = true;
        bool plot_mhtdc_2d = true;


        //:::: Drift for TravMus
        std::map<int, std::pair<double,double>> TravMusDriftCoefficients() const;
        bool TravMusDriftLoaded() const;
        std::map<int, std::pair<double,double>> AoQDriftCoefficients() const;
        bool AoQDriftLoaded() const;
        std::map<int, std::pair<double,double>> Z1DriftCoefficients() const;
        bool Z1DriftLoaded() const;



    private:

        static std::string config_path;
        TFrsConfiguration();

        static std::string scaler_mapping_file;
        void ReadScalerNames();

        static std::string tm_drift_coeff_file;
        void ReadTravMusDriftFile();

        static std::string aoq_drift_coeff_file;
        void ReadAoQDriftFile();

        static std::string z1_drift_coeff_file;
        void ReadZ1DriftFile();

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
        std::string scaler_name[66];
        std::string sci_names[6];

        // ::_ Drift
        std::map<int, std::pair<double,double> > travmus_drift_coeff;
        bool travmus_drift_loaded = 0;
        std::map<int, std::pair<double,double> > aoq_drift_coeff;
        bool aoq_drift_loaded = 0;
        std::map<int, std::pair<double,double> > z1_drift_coeff;
        bool z1_drift_loaded = 0;


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

inline std::string TFrsConfiguration::ScalerName(int index) const
{
    return scaler_name[index];
}

inline std::string TFrsConfiguration::SciName(int index) const
{
    return sci_names[index];
}

inline std::string TFrsConfiguration::GetConfigPath() const
{
    return config_path;
}

//::: Drift Trav Mus
inline std::map<int, std::pair<double,double> > TFrsConfiguration::TravMusDriftCoefficients() const
{
    return travmus_drift_coeff;
}

inline bool TFrsConfiguration::TravMusDriftLoaded() const
{
    return travmus_drift_loaded;
}

inline std::map<int, std::pair<double,double> > TFrsConfiguration::AoQDriftCoefficients() const
{
    return aoq_drift_coeff;
}

inline bool TFrsConfiguration::AoQDriftLoaded() const
{
    return aoq_drift_loaded;
}

inline std::map<int, std::pair<double,double> > TFrsConfiguration::Z1DriftCoefficients() const
{
    return z1_drift_coeff;
}

inline bool TFrsConfiguration::Z1DriftLoaded() const
{
    return z1_drift_loaded;
}

#endif