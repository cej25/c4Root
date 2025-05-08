#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
        //LISA_ANA displays only energy and traces; LISA_CAL displays stats,energy,traces. Choose one.
        //Note that if FRS 1, LISA_CAL is needed. 
#define LISA_ANA 0
#define LISA_CAL 1

// Test or experiment settings
#define TEST 1
#define EXP 0

// If you want to have trace histos
#define TRACE_ON 1

#define FRS_ON 1
#define FRS_LISA_CORRELATIONS 1

#define WR_ENABLED 1
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// :::  Define FRS setup.C file - FRS should provide; place in /config/shiyan/frs/setup/
extern "C"
{
    #include "../../../config/pareeksha/frs/setup_Fragment_conv_updated.C" //pareeksha data
    //#include "../../../config/shiyan/frs/setup/setup_160_49_2025_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

void e_shiyan_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // ::: Experiment name
    TString fExpName = "pareeksha";

    // ::: Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    // ::: Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    // ::: Debug info - set level
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    // ::: P A T H   O F   F I L E  to read
    //TString inputpath = "/u/gandolfo/data/test_c4/layer_alpha/";
    TString inputpath = "/u/gandolfo/data/test_c4/shiyan_test/";

    //TString filename = inputpath + "run_0003_0001_tree_v2.root";
    TString filename = inputpath + "test_run_0075.root";  
    //TString filename = inputpath + "Ag101_withSC11a_s2trig_0121_0001_stitched_tree.root";  //FRS data with S2 PID
    
    // ::: O U T P U T
    TString outputpath = "/u/gandolfo/data/test_c4/shiyan_test/";   //testing
    //TString outputpath = "/u/gandolfo/data/test_c4/layer_alpha/";   //energy resolution output
    
    //TString outputFilename = outputpath + "run_0003_0001_histo_v2.root";
    TString outputFilename = outputpath + "test_run_0075_histo_GATE_narrow_v3.root";
    //TString outputFilename = outputpath + "Ag101_withSC11a_s2trig_0121_0001_stitched_histo_6May.root";     //FRS data with S2 PID


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    //Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: F R S parameter - Initialise

    TFRSParameter* frs = new TFRSParameter();
    TMWParameter* mw = new TMWParameter();
    TTPCParameter* tpc = new TTPCParameter();
    TMUSICParameter* music = new TMUSICParameter();
    TLABRParameter* labr = new TLABRParameter();
    TSCIParameter* sci = new TSCIParameter();
    TIDParameter* id = new TIDParameter();
    TSIParameter* si = new TSIParameter();
    TMRTOFMSParameter* mrtof = new TMRTOFMSParameter();
    TRangeParameter* range = new TRangeParameter();
    setup(frs,mw,tpc,music,labr,sci,id,si,mrtof,range); // Function defined in frs setup.C macro
    TFrsConfiguration::SetParameters(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: G A T E S - Initialise 

    FrsGate* cut_0 = new FrsGate("wide", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/wide.root"); 
    FrsGate* cut_1 = new FrsGate("narrow", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/narrow.root"); 
    FrsGate* cut_2 = new FrsGate("medium", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/medium.root"); 
    // FrsGate* cut_3 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/all_z_2.root"); 
    // FrsGate* cut_4 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/2p3n.root"); 
    // FrsGate* cut_5 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/2p4n.root"); 
    std::vector<FrsGate*> fgs = {};
    
    fgs.emplace_back(cut_0);
    fgs.emplace_back(cut_1);
    fgs.emplace_back(cut_2);
    // fgs.emplace_back(cut_3);
    // fgs.emplace_back(cut_4);
    // fgs.emplace_back(cut_5);

    //FrsGate* test = new FrsGate("Tester",config_path + "/frs/Gates/frs_real_gate_lisa.root");
    //std::vector<FrsGate*> fgs = {};
    //fgs.emplace_back(test);

    // ::: GATES config for histos ::::::::
    //TFrsConfiguration::Set_dE_travMusic_gate(1940,2000);

    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path +  "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path +  "/frs/crate_map.txt");
    TFrsConfiguration::SetTravMusDriftFile(config_path +  "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path +  "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path +  "/frs/AoQ_Drift_fragments.txt");

    // ...........................................

    std::vector<LisaGate*> lgs = {};
    // ::: Lisa config
    if ( TEST )
    {
        
        /*
        // testing with shiyan/frs data
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_4x4_shiyan.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching_shiyan.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_shiyan.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_shiyan_v0.txt");
        */
        
        //for testing with pareeksha data 
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_Detector_Map_names.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");
        

        LisaGate* FebGate1 = new LisaGate("Febex_Gate1", "energy", config_path + "/lisa/Febex_Gate1.txt");
        LisaGate* FebGate2 = new LisaGate("Febex_Gate2", "energy", config_path + "/lisa/Febex_Gate1.txt");
        LisaGate* FebGate3 = new LisaGate("Febex_Gate3", "energy", config_path + "/lisa/Febex_Gate1.txt");

        LisaGate* MWD_Gate1 = new LisaGate("MWD_Gate1", "energy_mwd", config_path + "/lisa/MWD_Gate1.txt");
        LisaGate* MWD_Gate2 = new LisaGate("MWD_Gate2", "energy_mwd", config_path + "/lisa/MWD_Gate1.txt");
        LisaGate* MWD_Gate3 = new LisaGate("MWD_Gate3", "energy_mwd", config_path + "/lisa/MWD_Gate1.txt");

        // LisaGate* MWD_Gate3 = new LisaGate("MWD_Gate3", "energy_mwd", config_path + "/lisa/Gates/MWD_Gate3.txt");

        lgs.emplace_back(FebGate1);
        lgs.emplace_back(FebGate2);
        lgs.emplace_back(FebGate3);

        lgs.emplace_back(MWD_Gate1);
        lgs.emplace_back(MWD_Gate2);
        lgs.emplace_back(MWD_Gate3);

        // TLisaConfiguration::SetExcludedChannels({
        // std::make_tuple(1,0,0),
        // std::make_tuple(2,0,0)
        // });
        

    }
    if ( EXP )
    {
        /*
        TLisaConfiguration::SetMappingFile(config_path + "/Lisa_5x5_shiyan.txt");
        TLisaConfiguration::SetGMFile(config_path + "/lisa/Lisa_GainMatching_shiyan.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_shiyan.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path +  "/lisa/Lisa_MWD_Parameters_shiyan.txt");
        TLisaConfiguration::SetLISAGateFebex(config_path + "/lisa/Gates/Lisa_Febex_Gates_shiyan.txt");
        TLisaConfiguration::SetLISAGateMWD(config_path + "/lisa/Gates/Lisa_MWD_Gates_shiyan.txt");
        */
        // for testing with pareeksha data
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_Detector_Map_names.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");
    }
  
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //TLisaConfiguration::SetXYDetectorGate(1,1);  //XY position of the detector you want to see the gate on

    // ::: Get run number :::
    //TFrsConfiguration::SetRunNumber(fileNumber);
    //std::cout << "Run number: " << fileNumber << std::endl;

    //::::::::: Set experiment configurations
    //TExperimentConfiguration::SetExperimentStart(1746597600000000000); // Start for Shiyan data: May 7th, 8a.m. //including testing
    TExperimentConfiguration::SetExperimentStart(1715727045000000000); //Start of pareeksha with primary beam: 15 May 00:50
    //TExperimentConfiguration::SetExperimentStart(1746172830000000000);

    // ::: FRS
    TFrsConfiguration::Set_Z_range(10,60);
    TFrsConfiguration::Set_AoQ_range(1.8,3.5);
    TFrsConfiguration::Set_dE_music41_range(0,4000); 
    TFrsConfiguration::Set_dE_music21_range(0,4000);
    
    //::::::::: Set ranges for histos :::::::::::::::
    // ::: LISA
    //  Channel Energy ::::: (h1_energy_)
    TLisaConfiguration::SetEnergyRange(0,2000); //(0,50000) shiyan
    TLisaConfiguration::SetEnergyBin(2000);

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,500); //0,100 shiyan
    TLisaConfiguration::SetEnergyBinMWD(1000);

    //  Traces Time and Amplitude Ranges 
    TLisaConfiguration::SetTracesRange(0,10);
    TLisaConfiguration::SetTracesBin(1000);
    TLisaConfiguration::SetAmplitudeMin(7900);
    TLisaConfiguration::SetAmplitudeMax(8700);

    // White Rabbit
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(50000);

    TLisaConfiguration::SetWrRateRange(0,3600);
    TLisaConfiguration::SetWrRateBin(3600);

    // Drift
    TLisaConfiguration::SetDriftRange(0,1000);

    // :::: ENABLE SYSTEMS  ::::::::::::::::::::::::::::::::::::::::
    if(TRACE_ON)
    {
        TLisaConfiguration::SetTrace(1);
    }else
    {
        TLisaConfiguration::SetTrace(0);
    }

    if (LISA_ON)
    {
        if(LISA_ANA)
        {
            LisaNearlineSpectraAna* nearlinelisaana = new LisaNearlineSpectraAna();
            run->AddTask(nearlinelisaana);
        }

        if(LISA_CAL)
        {
            LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra(lgs);
            run->AddTask(nearlinelisa);
        }

    }

    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra(fgs);
        run->AddTask(nearlinefrs);
    }
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    if(LISA_ON && FRS_ON)
    {
        if(FRS_LISA_CORRELATIONS)
        {
            LisaFrsCorrelations* LISA_FRS_corr = new LisaFrsCorrelations(fgs,lgs);
            run->AddTask(LISA_FRS_corr);
        }
    }

    // Initialise
    run->Init();

    // Run
    run->Run(0, totEvt); 

    // Finish
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Output file is " << outputFilename << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
}
