#include <vector>

void histo_config(const std::string& config_path)
{
    
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_All_Boards.txt");

    // ::: Set ranges for histos 
    // :::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(0,200000);
    TLisaConfiguration::SetEnergyBin(1000);

    TLisaConfiguration::SetEnergyRangeMWD(0,50);
    TLisaConfiguration::SetEnergyBinMWD(1000);

    // :::  Channel Energy GM ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRangeGM(0,1000);
    TLisaConfiguration::SetEnergyBinGM(500);

    // ::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);

    // ::: Drifts
    TLisaConfiguration::SetEventNO(50000,1600000);
    
}
