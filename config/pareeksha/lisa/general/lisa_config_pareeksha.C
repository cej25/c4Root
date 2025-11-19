void lisa_config(const std::string& config_path)
{

    //for testing with pareeksha data 
    TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching.txt");
    TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD.txt");
    TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");

}