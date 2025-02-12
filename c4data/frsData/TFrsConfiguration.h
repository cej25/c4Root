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
        static void SetCrateMapFile(std::string fp) { crate_map_file = fp; }

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

        Bool_t plot_tac_1d = true;
        Bool_t plot_tac_2d = true;
        Bool_t plot_mhtdc_1d = true;
        Bool_t plot_mhtdc_2d = true;


        //:::: Drift for TravMus
        std::map<int, std::pair<double,double>> TravMusDriftCoefficients() const;
        bool TravMusDriftLoaded() const;
        std::map<int, std::pair<double,double>> AoQDriftCoefficients() const;
        bool AoQDriftLoaded() const;
        std::map<int, std::pair<double,double>> Z1DriftCoefficients() const;
        bool Z1DriftLoaded() const;

        Int_t Get_music_e_geo() const;

        // tac
        Int_t Get_sci_dE_geo() const;
        Int_t Get_dE_11l_chan() const;
        Int_t Get_dE_11r_chan() const;
        Int_t Get_dE_21l_chan() const;
        Int_t Get_dE_21r_chan() const;
        Int_t Get_dE_22l_chan() const;
        Int_t Get_dE_22r_chan() const;
        Int_t Get_dE_31l_chan() const;
        Int_t Get_dE_31r_chan() const;
        Int_t Get_dE_41l_chan() const;
        Int_t Get_dE_41r_chan() const;
        Int_t Get_dE_42l_chan() const;
        Int_t Get_dE_42r_chan() const;
        Int_t Get_dE_43l_chan() const;
        Int_t Get_dE_43r_chan() const;
        Int_t Get_dE_81l_chan() const;
        Int_t Get_dE_81r_chan() const;

        Int_t Get_sci_dT_geo() const;
        Int_t Get_dT_11l_11r_chan() const;
        Int_t Get_dT_21l_21r_chan() const;
        Int_t Get_dT_41l_41r_chan() const;
        Int_t Get_dT_42l_42r_chan() const;
        Int_t Get_dT_43l_43r_chan() const;
        Int_t Get_dT_81l_81r_chan() const;
        Int_t Get_dT_11l_21l_chan() const;
        Int_t Get_dT_11r_21r_chan() const;
        Int_t Get_dT_21l_41l_chan() const;
        Int_t Get_dT_21r_41r_chan() const;
        Int_t Get_dT_42r_21r_chan() const;
        Int_t Get_dT_42l_21l_chan() const;
        Int_t Get_dT_21l_81l_chan() const;
        Int_t Get_dT_21r_81r_chan() const;
        Int_t Get_dT_22l_22r_chan() const;
        Int_t Get_dT_22l_41l_chan() const;
        Int_t Get_dT_22r_41r_chan() const;
        Int_t Get_dT_22l_81l_chan() const;
        Int_t Get_dT_22r_81r_chan() const;

        Int_t Get_mhtdc_11LA_chan() const;
        Int_t Get_mhtdc_11LB_chan() const;
        Int_t Get_mhtdc_11LC_chan() const;
        Int_t Get_mhtdc_11LD_chan() const;
        Int_t Get_mhtdc_11RA_chan() const;
        Int_t Get_mhtdc_11RB_chan() const;
        Int_t Get_mhtdc_11RC_chan() const;
        Int_t Get_mhtdc_11RD_chan() const;
        Int_t Get_mhtdc_21L_chan() const;
        Int_t Get_mhtdc_21R_chan() const;
        Int_t Get_mhtdc_22L_chan() const;
        Int_t Get_mhtdc_22R_chan() const;
        Int_t Get_mhtdc_31L_chan() const;
        Int_t Get_mhtdc_31R_chan() const;
        Int_t Get_mhtdc_41L_chan() const;
        Int_t Get_mhtdc_41R_chan() const;
        Int_t Get_mhtdc_42L_chan() const;
        Int_t Get_mhtdc_42R_chan() const;
        Int_t Get_mhtdc_43L_chan() const;
        Int_t Get_mhtdc_43R_chan() const;
        Int_t Get_mhtdc_81L_chan() const;
        Int_t Get_mhtdc_81R_chan() const;


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

        static std::string crate_map_file;
        void ReadCrateMapFile();

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

        // ::_ Drift
        std::map<Int_t, std::pair<Double_t,Double_t> > travmus_drift_coeff;
        Bool_t travmus_drift_loaded = 0;
        std::map<Int_t, std::pair<Double_t,Double_t> > aoq_drift_coeff;
        Bool_t aoq_drift_loaded = 0;
        std::map<Int_t, std::pair<Double_t,Double_t> > z1_drift_coeff;
        Bool_t z1_drift_loaded = 0;

        Int_t music_e_geo = 0;

        // tac
        Int_t sci_dE_geo = -1;
        Int_t de_11l_ch = -1;
        Int_t de_11r_ch = -1;
        Int_t de_21l_ch = -1;
        Int_t de_21r_ch = -1;
        Int_t de_22l_ch = -1;
        Int_t de_22r_ch = -1;
        Int_t de_31l_ch = -1;
        Int_t de_31r_ch = -1;
        Int_t de_41l_ch = -1;
        Int_t de_41r_ch = -1;
        Int_t de_42l_ch = -1;
        Int_t de_42r_ch = -1;
        Int_t de_43l_ch = -1;
        Int_t de_43r_ch = -1;
        Int_t de_81l_ch = -1;
        Int_t de_81r_ch = -1;
        Bool_t dE_mapping_loaded = false;

        Int_t sci_dT_geo = -1;
        Int_t dt_11l_11r_ch = -1;
        Int_t dt_21l_21r_ch = -1;
        Int_t dt_41l_41r_ch = -1;
        Int_t dt_42l_42r_ch = -1;
        Int_t dt_43l_43r_ch = -1;
        Int_t dt_81l_81r_ch = -1;
        Int_t dt_11l_21l_ch = -1;
        Int_t dt_11r_21r_ch = -1;
        Int_t dt_21l_41l_ch = -1;
        Int_t dt_21r_41r_ch = -1;
        Int_t dt_42r_21r_ch = -1;
        Int_t dt_42l_21l_ch = -1;
        Int_t dt_21l_81l_ch = -1;
        Int_t dt_21r_81r_ch = -1;
        Int_t dt_22l_22r_ch = -1;
        Int_t dt_22l_41l_ch = -1;
        Int_t dt_22r_41r_ch = -1;
        Int_t dt_22l_81l_ch = -1;
        Int_t dt_22r_81r_ch = -1;
        Bool_t dT_mapping_loaded = false;

        // MHTDC scintillator timestamps
        Int_t mhtdc_11LA_ch = -1;
        Int_t mhtdc_11LB_ch = -1;
        Int_t mhtdc_11LC_ch = -1;
        Int_t mhtdc_11LD_ch = -1;
        Int_t mhtdc_11RA_ch = -1;
        Int_t mhtdc_11RB_ch = -1;
        Int_t mhtdc_11RC_ch = -1;
        Int_t mhtdc_11RD_ch = -1;
        Int_t mhtdc_21L_ch = -1;
        Int_t mhtdc_21R_ch = -1;
        Int_t mhtdc_22L_ch = -1;
        Int_t mhtdc_22R_ch = -1;
        Int_t mhtdc_31L_ch = -1;
        Int_t mhtdc_31R_ch = -1;
        Int_t mhtdc_41L_ch = -1;
        Int_t mhtdc_41R_ch = -1;
        Int_t mhtdc_42L_ch = -1;
        Int_t mhtdc_42R_ch = -1;
        Int_t mhtdc_43L_ch = -1;
        Int_t mhtdc_43R_ch = -1;
        Int_t mhtdc_81L_ch = -1;
        Int_t mhtdc_81R_ch = -1;


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

inline int TFrsConfiguration::Get_music_e_geo() const
{
    return music_e_geo;
};

inline int TFrsConfiguration::Get_sci_dE_geo() const
{
    return sci_dE_geo;
};

inline int TFrsConfiguration::Get_dE_11l_chan() const
{
    return de_11l_ch;
};

inline int TFrsConfiguration::Get_dE_11r_chan() const
{
    return de_11r_ch;
};

inline int TFrsConfiguration::Get_dE_21l_chan() const
{
    return de_21l_ch;
};

inline int TFrsConfiguration::Get_dE_21r_chan() const
{
    return de_21r_ch;
};

inline int TFrsConfiguration::Get_dE_22l_chan() const
{
    return de_22l_ch;
};

inline int TFrsConfiguration::Get_dE_22r_chan() const
{
    return de_22r_ch;
};

inline int TFrsConfiguration::Get_dE_31l_chan() const
{
    return de_31l_ch;
};

inline int TFrsConfiguration::Get_dE_31r_chan() const
{
    return de_31r_ch;
};

inline int TFrsConfiguration::Get_dE_41l_chan() const
{
    return de_41l_ch;
};

inline int TFrsConfiguration::Get_dE_41r_chan() const
{
    return de_41r_ch;
};

inline int TFrsConfiguration::Get_dE_42l_chan() const
{
    return de_42l_ch;
};

inline int TFrsConfiguration::Get_dE_42r_chan() const
{
    return de_42r_ch;
};

inline int TFrsConfiguration::Get_dE_43l_chan() const
{
    return de_43l_ch;
};

inline int TFrsConfiguration::Get_dE_43r_chan() const
{
    return de_43r_ch;
};

inline int TFrsConfiguration::Get_dE_81l_chan() const
{
    return de_81l_ch;
};

inline int TFrsConfiguration::Get_dE_81r_chan() const
{
    return de_81r_ch;
};

inline int TFrsConfiguration::Get_sci_dT_geo() const
{
    return sci_dT_geo;
};

inline int TFrsConfiguration::Get_dT_11l_11r_chan() const
{
    return dt_11l_11r_ch;
};

inline int TFrsConfiguration::Get_dT_21l_21r_chan() const
{
    return dt_21l_21r_ch;
};

inline int TFrsConfiguration::Get_dT_41l_41r_chan() const
{
    return dt_41l_41r_ch;
};

inline int TFrsConfiguration::Get_dT_42l_42r_chan() const
{
    return dt_42l_42r_ch;
};

inline int TFrsConfiguration::Get_dT_43l_43r_chan() const
{
    return dt_43l_43r_ch;
};

inline int TFrsConfiguration::Get_dT_81l_81r_chan() const
{
    return dt_81l_81r_ch;
};

inline int TFrsConfiguration::Get_dT_11l_21l_chan() const
{
    return dt_11l_21l_ch;
};

inline int TFrsConfiguration::Get_dT_11r_21r_chan() const
{
    return dt_11r_21r_ch;
};

inline int TFrsConfiguration::Get_dT_21l_41l_chan() const
{
    return dt_21l_41l_ch;
};

inline int TFrsConfiguration::Get_dT_21r_41r_chan() const
{
    return dt_21r_41r_ch;
};

inline int TFrsConfiguration::Get_dT_42r_21r_chan() const
{
    return dt_42r_21r_ch;
};

inline int TFrsConfiguration::Get_dT_42l_21l_chan() const
{
    return dt_42l_21l_ch;
};

inline int TFrsConfiguration::Get_dT_21l_81l_chan() const
{
    return dt_21l_81l_ch;
};

inline int TFrsConfiguration::Get_dT_21r_81r_chan() const
{
    return dt_21r_81r_ch;
};

inline int TFrsConfiguration::Get_dT_22l_22r_chan() const
{
    return dt_22l_22r_ch;
};

inline int TFrsConfiguration::Get_dT_22l_41l_chan() const
{
    return dt_22l_41l_ch;
};

inline int TFrsConfiguration::Get_dT_22r_41r_chan() const
{
    return dt_22r_41r_ch;
};

inline int TFrsConfiguration::Get_dT_22l_81l_chan() const
{
    return dt_22l_81l_ch;
};

inline int TFrsConfiguration::Get_dT_22r_81r_chan() const
{
    return dt_22r_81r_ch;
};

inline int TFrsConfiguration::Get_mhtdc_11LA_chan() const
{
    return mhtdc_11LA_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11LB_chan() const
{
    return mhtdc_11LB_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11LC_chan() const
{
    return mhtdc_11LC_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11LD_chan() const
{
    return mhtdc_11LD_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11RA_chan() const
{
    return mhtdc_11RA_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11RB_chan() const
{
    return mhtdc_11RB_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11RC_chan() const
{
    return mhtdc_11RC_ch;
}

inline int TFrsConfiguration::Get_mhtdc_11RD_chan() const
{
    return mhtdc_11RD_ch;
}

inline int TFrsConfiguration::Get_mhtdc_21L_chan() const
{
    return mhtdc_21L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_21R_chan() const
{
    return mhtdc_21R_ch;
}

inline int TFrsConfiguration::Get_mhtdc_22L_chan() const
{
    return mhtdc_22L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_22R_chan() const
{
    return mhtdc_22R_ch;
}

inline int TFrsConfiguration::Get_mhtdc_31L_chan() const
{
    return mhtdc_31L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_31R_chan() const
{
    return mhtdc_31R_ch;
}

inline int TFrsConfiguration::Get_mhtdc_41L_chan() const
{
    return mhtdc_41L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_41R_chan() const
{
    return mhtdc_41R_ch;
}

inline int TFrsConfiguration::Get_mhtdc_42L_chan() const
{
    return mhtdc_42L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_42R_chan() const
{
    return mhtdc_42R_ch;
}

inline int TFrsConfiguration::Get_mhtdc_43L_chan() const
{
    return mhtdc_43L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_43R_chan() const
{
    return mhtdc_43R_ch;
}

inline int TFrsConfiguration::Get_mhtdc_81L_chan() const
{
    return mhtdc_81L_ch;
}

inline int TFrsConfiguration::Get_mhtdc_81R_chan() const
{
    return mhtdc_81R_ch;
}


#endif