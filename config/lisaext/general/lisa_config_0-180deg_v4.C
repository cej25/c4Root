void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Mapping_5x5_Versoek_0-180deg_v1.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_5x5_Versoek_0-180deg_v2.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_MWD_5x5_Versoek_0-180deg_v0.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/Lisa_GainMatching_dedx_5x5_Versoek_0-180deg_v0.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_v0.txt");

}
