#include <vector>

std::vector<LisaGate*> lgs;

void histo_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Mapping_3x3_Num8.txt");    
    //..................................................

    // ::: Start of experiment
    //TExperimentConfiguration::SetExperimentStart(1746684000000000000);
    //..................................................

    // ::: Exclude channels from layer 
    // TLisaConfiguration::SetExcludedChannels({
    // std::make_tuple(1,0,0),
    // std::make_tuple(2,0,0)
    // });
    //..................................................

    // ::: LISA ranges
    //  Channel Energy 
    TLisaConfiguration::SetEnergyRange(0,90000); 
    TLisaConfiguration::SetEnergyBin(500); 

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,500);
    TLisaConfiguration::SetEnergyBinMWD(500);

    TLisaConfiguration::SetdEdXRange(0,1); 
    TLisaConfiguration::SetdEdXBin(500); 

    //  Traces Time and Amplitude Ranges 
    TLisaConfiguration::SetTracesRange(0,10);
    TLisaConfiguration::SetTracesBin(100);
    TLisaConfiguration::SetAmplitudeMin(7500);
    TLisaConfiguration::SetAmplitudeMax(8000);

    // Black Rabbit
    TLisaConfiguration::SetBrDiffRange(0,10000);
    TLisaConfiguration::SetBrDiffBin(50000);

    TLisaConfiguration::SetBrRateRange(0,3600);
    TLisaConfiguration::SetBrRateBin(3600);

    // Drift
    TLisaConfiguration::SetDriftRange(0,1400);
    //..................................................

    // ::: Gates
    TLisaConfiguration::SetXYDetectorGate(2,1); 

    // L I S A 
    
}
