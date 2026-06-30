#include <vector>

std::vector<LisaGate*> lgs;

void histo_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Mapping_5x5_Versoek_0-0deg_v1.txt");    
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
    TLisaConfiguration::SetEnergyRange(10000,100000); 
    TLisaConfiguration::SetEnergyBin(800); 

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,500);
    TLisaConfiguration::SetEnergyBinMWD(500);

    TLisaConfiguration::SetdEdXRange(0,1); 
    TLisaConfiguration::SetdEdXBin(500); 

    //  Traces Time and Amplitude Ranges 
    TLisaConfiguration::SetTracesRange(0,10);
    TLisaConfiguration::SetTracesBin(100);
    TLisaConfiguration::SetAmplitudeMin(4000);
    TLisaConfiguration::SetAmplitudeMax(9000);

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
    
    // 1
    LisaGate* Wide_F1 = new LisaGate("wide_feb_1", "energy", config_path + "/Gates/Febex_Gate1shiyan.txt");
    LisaGate* Wide_M1 = new LisaGate("wide_mwd_1", "energy_mwd", config_path + "/Gates/MWD_Gate1shiyan.txt");
    LisaGate* Wide_D1 = new LisaGate("wide_dedx_1", "dedx_mwd", config_path + "/Gates/dEdX_Gate1shiyan.txt");

    lgs.emplace_back(Wide_F1);
    lgs.emplace_back(Wide_M1);
    lgs.emplace_back(Wide_D1);
    

}
