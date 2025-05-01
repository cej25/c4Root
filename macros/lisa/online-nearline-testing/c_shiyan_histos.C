#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 0
        //LISA_ANA displays only energy and traces; LISA_CAL displays stats,energy,traces. Choose one.
        //Note that if FRS 1, LISA_CAL is needed. 
#define LISA_ANA 0
#define LISA_CAL 0

// Test or experiment settings
#define TEST 1
#define EXP 0

// If you want to have trace histos
#define TRACE_ON 1

#define FRS_ON 1
#define FRS_LISA_CORRELATIONS 0

#define WR_ENABLED 1
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// :::  Define FRS setup.C file - FRS should provide; place in /config/shiyan/frs/setup/
extern "C"
{
    #include "../../../config/shiyan/frs/setup/setup_160_49_2025_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

void c_shiyan_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // ::: Experiment name
    TString fExpName = "shiyan";

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
    TString inputpath = "./";
    //TString filename = inputpath + "test_0003_tree.root";  
    TString filename = inputpath + "c_test_Ag_with_whatever.root";  
    
    // ::: O U T P U T
    TString outputpath = "./"; //test output
    //TString outputFilename = outputpath + "test_0003_histo_shiyan.root";
    TString outputFilename = outputpath + "c_test_Ag_histos_whatever.root";


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

    std::vector<FrsGate*> fg;
    FrsGate* cut_0 = new FrsGate("cut", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/all_z_1.root"); 
    FrsGate* cut_1 = new FrsGate("0", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/1p1n.root"); 
    FrsGate* cut_2 = new FrsGate("1", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/1p2n.root"); 
    FrsGate* cut_3 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/all_z_2.root"); 
    FrsGate* cut_4 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/2p3n.root"); 
    FrsGate* cut_5 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/2p4n.root"); 

    
    fg.emplace_back(cut_0);
    fg.emplace_back(cut_1);
    fg.emplace_back(cut_2);
    fg.emplace_back(cut_3);
    fg.emplace_back(cut_4);
    fg.emplace_back(cut_5);

    // ::: GATES config for histos ::::::::
    TFrsConfiguration::Set_dE_travMusic_gate(1940,2000);
    //TLisaConfiguration::SetLISAGate(1070,1110); //Gate on LISA 1 for histo of LISA 2 energy (mean +- 3sigma)
    TLisaConfiguration::SetXYDetectorGate(2,2);  //XY position of the detector you want to see the gate on

    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path +  "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path +  "/frs/crate_map.txt");
    TFrsConfiguration::SetTravMusDriftFile(config_path +  "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path +  "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path +  "/frs/AoQ_Drift_fragments.txt");

    // ::: Lisa config
    if ( TEST )
    {
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_All_Boards.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching_cards.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_cards.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_LISAmp_lowgain.txt");
        TLisaConfiguration::SetLISAGateFebex(config_path + "/lisa/Lisa_Febex_Gates.txt");
        TLisaConfiguration::SetLISAGateMWD(config_path + "/lisa/Lisa_MWD_Gates.txt");

    }
    if ( EXP )
    {
        TLisaConfiguration::SetMappingFile(config_path + "/Lisa_5x5_shiyan.txt");
        TLisaConfiguration::SetGMFile(config_path + "/lisa/Lisa_GainMatching_shiyan.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_shiyan.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path +  "/lisa/Lisa_MWD_Parameters_shiyan.txt");
        TLisaConfiguration::SetLISAGateFebex(config_path + "/lisa/Lisa_Febex_Gates_shiyan.txt");
        TLisaConfiguration::SetLISAGateMWD(config_path + "/lisa/Lisa_MWD_Gates_shiyan.txt");
    }
  
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    
    // ::: Get run number :::
    //TFrsConfiguration::SetRunNumber(fileNumber);
    //std::cout << "Run number: " << fileNumber << std::endl;

    //::::::::: Set experiment configurations
    TExperimentConfiguration::SetExperimentStart(1745599200000000000);
    // ::: FRS
    TFrsConfiguration::Set_Z_range(10,60);
    TFrsConfiguration::Set_AoQ_range(1.8,3.5);
    TFrsConfiguration::Set_dE_Music1_range(0,64000);
    
    //::::::::: Set ranges for histos :::::::::::::::
    // ::: LISA
    //  Channel Energy ::::: (h1_energy_)
    TLisaConfiguration::SetEnergyRange(30000,50000);
    TLisaConfiguration::SetEnergyBin(1000);

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,100);
    TLisaConfiguration::SetEnergyBinMWD(1000);

    //  Traces Time and Amplitude Ranges 
    TLisaConfiguration::SetTracesRange(0,5);
    TLisaConfiguration::SetTracesBin(500);
    TLisaConfiguration::SetAmplitudeMin(7900);
    TLisaConfiguration::SetAmplitudeMax(8700);

    // White Rabbit
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(50000);

    TLisaConfiguration::SetWrRateRange(0,3600);
    TLisaConfiguration::SetWrRateBin(3600);

    // Drift
    TLisaConfiguration::SetDriftRange(0,100);

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
            LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra();
            run->AddTask(nearlinelisa);
        }

    }

    FrsGate* test = new FrsGate("Tester","/u/cjones/c4Root/config/shiyan/frs/Gates/frs_PID_gate_lisa.root");
    std::vector<FrsGate*> fgs = {};
    fgs.emplace_back(test);

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
            LisaFrsCorrelations* LISA_FRS_corr = new LisaFrsCorrelations(fg);
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
