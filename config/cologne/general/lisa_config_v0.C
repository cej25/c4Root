void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_4x4.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_cards.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_MWD_cards.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/Lisa_GM_dEdX.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters.txt");

}