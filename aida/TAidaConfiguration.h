#ifndef AIDA_ANL_CONFIG
#define AIDA_ANL_CONFIG

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum DSSDSide
{
  Junction = -1,
  Ohmic = 1,
};

enum WideAIDASegment
{
  Left,
  Centre,
  Right
};

struct DSSDConfiguration
{
  int DSSD;
  int Top;
  int Bottom;
  int Left;
  int Right;
  // Wide AIDA only mappings
  int LeftRight;
  int CentreLeft;
  int CentreRight;
  int RightLeft;
  // Side mapping
  DSSDSide XSide;
  DSSDSide YSide;
};

struct FEEConfiguration
{
  int DSSD;
  DSSDSide Side;
  bool High;
  // Wide AIDA only data
  WideAIDASegment Segment;
};

class TAidaConfiguration
{
public:
    static TAidaConfiguration const* GetInstance();
    static void Create();
    static void SetBasePath(std::string bp) { base_path = bp; }

    int FEEs() const;
    int DSSDs() const;
    bool Wide() const;

    bool AdjustADC() const;
    bool ucesb() const;
    bool IgnoreMBSTS() const;
    bool ShowStats() const;
    int ucesbShift() const;

    double EventWindow() const;
    double FrontBackWindow() const;
    double FrontBackEnergyH() const;
    double FrontBackEnergyL() const;

    bool ReduceNoise() const;
    bool ClusterImplants() const;
    bool ClusterDecays() const;
    bool Calibrate() const;
    bool ParallelCalibrate() const;
    int HugeThreshold() const;
    int PulserThreshold() const;

    DSSDConfiguration DSSD(int i) const;
    FEEConfiguration FEE(int i) const;
    std::string Scaler(int i) const;
    std::map<int, std::string> const& ScalerMap() const;

    int GetAdcOffset(int f, int channel) const;
    double GetDssdGain(int d, bool yside, int strip) const;
    int GetFeeTimeOffset(int f) const;
    double GetDssdStripThreshold(int d, bool yside, int strip) const;

private:
    static std::string base_path;
    TAidaConfiguration();
    void ReadConfiguration();
    void DSSDtoFEE();

    static TAidaConfiguration* instance;

    int fees;
    int dssds;
    bool wide;
    bool adjustadc;
    bool useucesb;
    bool ignorembsts;
    bool stats;
    int ucesbshift;
    double eventwindow;
    double fbwindow;
    double fbenergyh;
    double fbenergyl;

    // analysis options
    bool reducenoise;
    bool clusterimpants;
    bool clusterdecays;
    bool calibrate;
    bool parallelcalibrate;
    int hugethreshold;
    int pulserthreshold;

    std::vector<DSSDConfiguration> dssd;
    std::vector<FEEConfiguration> fee;
    std::map<int, std::string> scalers;

    // calibration parameters
    std::vector<std::array<int, 64>> adcOffsets;
    std::vector<std::array<std::vector<double>, 2>> dssdGains;
    std::vector<int> feeTimeOffsets; // should always be 0
    std::vector<std::array<std::vector<double>, 2>> stripThresholds;
};

inline TAidaConfiguration const* TAidaConfiguration::GetInstance()
{
  if (!instance)
  {
    TAidaConfiguration::Create();
  }
  return instance;
}

inline void TAidaConfiguration::Create()
{
  delete instance;
  instance = new TAidaConfiguration();
}

inline int TAidaConfiguration::FEEs() const
{
  return fees;
}

inline int TAidaConfiguration::DSSDs() const
{
  return dssds;
}

inline bool TAidaConfiguration::Wide() const
{
  return wide;
}

inline bool TAidaConfiguration::AdjustADC() const
{
  return adjustadc;
}

inline bool TAidaConfiguration::IgnoreMBSTS() const
{
  return ignorembsts;
}

inline bool TAidaConfiguration::ucesb() const
{
  return useucesb;
}

inline bool TAidaConfiguration::ShowStats() const
{
  return stats;
}

inline int TAidaConfiguration::ucesbShift() const
{
  return ucesbshift;
}

inline double TAidaConfiguration::EventWindow() const
{
  return eventwindow;
}

inline double TAidaConfiguration::FrontBackWindow() const
{
  return fbwindow;
}

inline double TAidaConfiguration::FrontBackEnergyH() const
{
  return fbenergyh;
}

inline double TAidaConfiguration::FrontBackEnergyL() const
{
  return fbenergyl;
}

inline bool TAidaConfiguration::ReduceNoise() const
{
  return reducenoise;
}

inline bool TAidaConfiguration::ClusterImplants() const
{
  return clusterimpants;
}

inline bool TAidaConfiguration::ClusterDecays() const
{
  return clusterdecays;
}

inline bool TAidaConfiguration::Calibrate() const
{
  return calibrate;
}

inline bool TAidaConfiguration::ParallelCalibrate() const
{
  return parallelcalibrate;
}

inline int TAidaConfiguration::HugeThreshold() const
{
  return hugethreshold;
}

inline int TAidaConfiguration::PulserThreshold() const
{
  return pulserthreshold;
}

inline DSSDConfiguration TAidaConfiguration::DSSD(int i) const
{
  return dssd[i];
}

inline FEEConfiguration TAidaConfiguration::FEE(int i) const
{
  return fee[i];
}

inline std::string TAidaConfiguration::Scaler(int i) const
{
  if (scalers.find(i) != scalers.end())
  {
    return scalers.at(i);
  }
  else
  {
    return "";
  }
}

inline std::map<int, std::string> const& TAidaConfiguration::ScalerMap() const
{
  return scalers;
}

inline int TAidaConfiguration::GetAdcOffset(int f, int channel) const
{
  return adcOffsets[f][channel];
}

inline double TAidaConfiguration::GetDssdGain(int d, bool yside, int strip) const
{
  return dssdGains[d][yside ? 1 : 0][strip];
}

inline int TAidaConfiguration::GetFeeTimeOffset(int f) const
{
  return feeTimeOffsets[f];
}

inline double TAidaConfiguration::GetDssdStripThreshold(int d, bool yside, int strip) const
{
  return stripThresholds[d][yside ? 1 :0][strip];
}

#endif /* AIDA_ANL_CONFIG */
