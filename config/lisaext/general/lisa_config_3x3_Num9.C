void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Mapping_3x3_Num9.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_3x3_fake.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_3x3_fake.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/Lisa_GainMatching_3x3_fake.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_v1.txt");

}
