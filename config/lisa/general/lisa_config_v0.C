void lisa_config(const std::string& config_path)
{

    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_All_Boards.txt");
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_MWD.txt");
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_HGpreLISA.txt");
}   