void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_4x4_shiyan_v1.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/lisa/GM_threepoint_clust_Febex.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/lisa/GM_threepoint_clust_MWD.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/lisa/Lisa_GM_dEdX_shiyan_v1.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_shiyan_v2.txt");


    // //for testing with pareeksha data 
    // TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_Detector_Map_names.txt");
    // TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching.txt");
    // TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD.txt");
    // TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");

}