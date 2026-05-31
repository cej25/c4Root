void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Mapping_All_Boards_FULL.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_4x4.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_MWD_4x4.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/Lisa_GainMatching_MWD_dEdX_4x4.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_v0.txt");

}