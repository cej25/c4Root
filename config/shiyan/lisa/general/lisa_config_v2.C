void lisa_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_4x4_shiyan_v1.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path + "/lisa/GM_threepoint_clust_Febex.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/lisa/GM_threepoint_clust_MWD.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/lisa/Lisa_GM_dEdX_shiyan_v2.txt");

    // ::: Z calibration
    TLisaConfiguration::SetZCalibrationFile(config_path + "/lisa/Lisa_Z_Calibration_shiyan_v0.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_shiyan_v2.txt");

}