void frs_config(const std::string& config_path)
{
    // Experiment info
    TExperimentConfiguration::SetExperimentStart(1746597600000000000); // Start for Shiyan data: May 7th, 8a.m.
    TExperimentConfiguration::SetBOSTrig(12); // beginning of spill trigger type (12 from 2025+, 3 before)
    TExperimentConfiguration::SetEOSTrig(13); // end of spill trigger type (13 from 2025+, 4 before)

    // General
    TFrsConfiguration::SetConfigPath(config_path +  "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path +  "/frs/crate_map.txt");

    // Drift
    TFrsConfiguration::SetTravMusDriftFile(config_path +  "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path +  "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path +  "/frs/AoQ_Drift_fragments.txt");

    // Limit for Scintillator time difference left-right
    TFrsConfiguration::Set_scilr_mhtdc_limit(40);

    // Ranges for the tof 
    TFrsConfiguration::Set_tof_limit_2111(0,400);
    TFrsConfiguration::Set_tof_limit_4121(0,400);
    TFrsConfiguration::Set_tof_limit_4122(0,400);
    TFrsConfiguration::Set_tof_limit_4221(0,400);
    TFrsConfiguration::Set_tof_limit_4321(0,400);
    TFrsConfiguration::Set_tof_limit_3121(0,400);

}