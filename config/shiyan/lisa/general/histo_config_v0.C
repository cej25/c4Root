#include <vector>

std::vector<FrsGate*> fgs;
std::vector<LisaGate*> lgs;

void histo_config(const std::string& config_path)
{
    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_4x4_shiyan_v1.txt");
    TFrsConfiguration::SetConfigPath(config_path +  "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path +  "/frs/crate_map.txt");
    
    //..................................................

    // ::: Start of experiment
    TExperimentConfiguration::SetExperimentStart(1746684000000000000);
    //..................................................

    // ::: Exclude channels from layer 
    // TLisaConfiguration::SetExcludedChannels({
    // std::make_tuple(1,0,0),
    // std::make_tuple(2,0,0)
    // });
    //..................................................

    // ::: FRS ranges
    TFrsConfiguration::Set_Z_range(10,45);
    TFrsConfiguration::Set_AoQ_range(1.8,2.4);
    TFrsConfiguration::Set_dE_music41_range(0,5000); 
    TFrsConfiguration::Set_dE_music21_range(0,40000);
    //..................................................

    // ::: LISA ranges
    //  Channel Energy 
    TLisaConfiguration::SetEnergyRange(0,500); 
    TLisaConfiguration::SetEnergyBin(500); 

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,500);
    TLisaConfiguration::SetEnergyBinMWD(500);

    TLisaConfiguration::SetdEdXRange(0,1); 
    TLisaConfiguration::SetdEdXBin(500); 

    //  Traces Time and Amplitude Ranges 
    TLisaConfiguration::SetTracesRange(0,4);
    TLisaConfiguration::SetTracesBin(400);
    TLisaConfiguration::SetAmplitudeMin(6000);
    TLisaConfiguration::SetAmplitudeMax(8500);

    // White Rabbit
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(50000);

    TLisaConfiguration::SetWrRateRange(0,3600);
    TLisaConfiguration::SetWrRateBin(3600);

    // Drift
    TLisaConfiguration::SetDriftRange(0,10100);
    //..................................................

    // ::: Gates
    TLisaConfiguration::SetXYDetectorGate(2,1); 

    // F R S
    FrsGate* Cr_1p = new FrsGate("Cr_1p",config_path + "/frs/Gates/Cr_1p_Z42.root");
    FrsGate* Cr_1p1n = new FrsGate("Cr_1p1n",config_path + "/frs/Gates/Cr_1p1n_Z42.root");

    fgs.emplace_back(Cr_1p);
    fgs.emplace_back(Cr_1p1n);

    // L I S A 
    LisaGate* Wide_F1 = new LisaGate("wide_feb_1", "energy", config_path + "/lisa/Gates/Febex_Gate1shiyan.txt");
    LisaGate* Wide_M1 = new LisaGate("wide_mwd_1", "energy_mwd", config_path + "/lisa/Gates/MWD_Gate1shiyan.txt");

    lgs.emplace_back(Wide_F1);
    lgs.emplace_back(Wide_M1);
    

    LisaGate* Wide_F2 = new LisaGate("wide_feb_2", "energy", config_path + "/lisa/Gates/Febex_Gate1shiyan.txt");
    LisaGate* Wide_M2 = new LisaGate("wide_mwd_2", "energy_mwd", config_path + "/lisa/Gates/MWD_Gate1shiyan.txt");
    
    lgs.emplace_back(Wide_F2);
    lgs.emplace_back(Wide_M2);
    
    


}