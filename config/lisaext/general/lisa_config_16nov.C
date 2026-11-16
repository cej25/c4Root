void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "//Lisa_Mapping_3x3_Versoek_15Nov.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_3x3_Versoek_15Nov_fake.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_3x3_Versoek_15Nov_fake.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/Lisa_GainMatching_3x3_Versoek_15Nov_fake.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_3x3_CS.txt");

}
