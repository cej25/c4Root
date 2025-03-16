#ifndef AIDA_ANL_CONFIG
#define AIDA_ANL_CONFIG

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>

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

// type 1 = regular AIDA, type 2 = BB7
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
    int Type;
    int Full;
    // Side mapping
    DSSDSide XSide;
    DSSDSide YSide;
};

struct FEEConfiguration
{
    int DSSD;
    int Type;
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

        int FEEs() const { return fees; }
        int DSSDs() const { return dssds; }
        bool Wide() const { return wide; }

        bool AdjustADC() const { return adjustadc; }
        bool ucesb() const { return useucesb; }
        bool IgnoreMBSTS() const { return ignorembsts; }
        bool ShowStats() const  { return stats; }
        int ucesbShift() const { return ucesbshift; }

        double EventWindow() const { return eventwindow; }
        double FrontBackWindow() const { return fbwindow; }
        double FrontBackEnergyH() const { return fbenergyh; }
        double FrontBackEnergyL() const { return fbenergyl; }

        bool ReduceNoise() const { return reducenoise; }
        bool ClusterImplants() const { return clusterimplants; }
        bool ClusterDecays() const { return clusterdecays; }
        bool Calibrate() const { return calibrate; }
        bool ParallelCalibrate() const { return parallelcalibrate; }
        int HugeThreshold() const { return hugethreshold; }
        int PulserThreshold() const { return pulserthreshold; }

        DSSDConfiguration DSSD(int i) const { return dssd[i]; }
        FEEConfiguration FEE(int i) const { return fee[i]; }
        std::string Scaler(int i) const { return (scalers.find(i) != scalers.end()) ? scalers.at(i) : ""; }
        std::map<int, std::string> const& ScalerMap() const { return scalers; }

        int TM_Undelayed() const { return tm_undelayed; }
        int TM_Delayed() const { return tm_delayed; }
        int SC41L() const { return sc41l_d; }
        int SC41R() const { return sc41r_d; }

        int GetAdcOffset(int f, int channel) const { return adcOffsets[f][channel]; }
        double GetDssdGain(int d, bool yside, int strip) const { return dssdGains[d][yside ? 1 : 0][strip]; }
        int GetFeeTimeOffset(int f) const { return feeTimeOffsets[f]; }
        double GetDssdStripThreshold(int d, bool yside, int strip) const { return stripThresholds[d][yside ? 1 :0][strip]; }

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
        bool clusterimplants;
        bool clusterdecays;
        bool calibrate;
        bool parallelcalibrate;
        int hugethreshold;
        int pulserthreshold;

        std::vector<DSSDConfiguration> dssd;
        std::vector<FEEConfiguration> fee;
        std::map<int, std::string> scalers;

        // special channels
        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

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

#endif /* AIDA_ANL_CONFIG */
