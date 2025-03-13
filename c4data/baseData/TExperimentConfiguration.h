#ifndef TExperimentConfiguration_H
#define TExperimentConfiguration_H

#include "c4Logger.h"

class TExperimentConfiguration
{
    public:
        static TExperimentConfiguration const* GetInstance();
        static void Create();

        //Setter
        static void SetExperimentStart(uint64_t st) { exp_start_time = st; }
        static void SetExperimentEnd(uint64_t et) {exp_end_time = et;}
        static void SetBOSTrig(Int_t bos) { bos_trig = bos; }
        static void SetEOSTrig(Int_t eos) { eos_trig = eos; }

        static uint64_t exp_start_time;
        static uint64_t exp_end_time;
        static Int_t bos_trig; // beginning of spill
        static Int_t eos_trig; // end of spill

    private:
        static std::string filepath;
        TExperimentConfiguration();
    
        static TExperimentConfiguration* instance;

        // contain list of subsystems used - mainly for WR correlations..

        // stuff
    
};

inline TExperimentConfiguration const* TExperimentConfiguration::GetInstance()
{
    if (!instance)
    {
        TExperimentConfiguration::Create();
    }
    return instance;
}

inline void TExperimentConfiguration::Create()
{
    delete instance;
    instance = new TExperimentConfiguration();
}



#endif
