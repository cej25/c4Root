#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
        //LISA_ANA displays only energy and traces; LISA_CAL displays stats,energy,traces. Choose one.
        //Note that if FRS 1, LISA_CAL is needed. 
#define LISA_ANA 0
#define LISA_CAL 1

// If you want to have trace histos
#define TRACE_ON 1

#define FRS_ON 0
#define FRS_LISA_CORRELATIONS 0

#define WR_ENABLED 0
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// Define FRS setup.C file - FRS should provide; place in /config/pareeksha/frs/
extern "C"
{
    #include "../../config/pareeksha/frs/setup_Fragment_conv_updated.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

void lisadev_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "pareeskha";

    //:::::::::Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    //:::::::::Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    //:::::::::::Debug info - set level
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    //::::::::::P A T H   O F   F I L E  to read
    //___O F F L I N E
    TString inputpath = "/u/gandolfo/data/test_c4/";
    TString filename = inputpath + "LISAmp_10layers_0012_0001.root";  
    
    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/test_c4/"; //test output
    TString outputFilename = outputpath + "LISAmp_10layers_0012_0001_histos.root";


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
    //::::: F R S parameter - Initialise

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
    //:::: G A T E S - Initialise 

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

    //:::: GATES config for histos ::::::::
    TFrsConfiguration::Set_dE_travMusic_gate(1940,2000);
    TLisaConfiguration::SetLISAGate(1070,1110); //Gate on LISA 1 for histo of LISA 2 energy (mean +- 3sigma)
    //98Nb -> 1090 (6.6)
    //96Zr -> 1044 (8)
    //95Zr -> 1027 (5)
    //after98Nb -> 1171 (9)

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: FRS config
    // TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    // TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
    // TFrsConfiguration::SetTravMusDriftFile(config_path + "/frs/TM_Drift_fragments.txt");
    // TFrsConfiguration::SetZ1DriftFile(config_path + "/frs/Z1_Drift_fragments.txt");
    // TFrsConfiguration::SetAoQDriftFile(config_path + "/frs/AoQ_Drift_fragments.txt");

    // ::: LISA config
    // TLisaConfiguration::SetMappingFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_Detector_Map_names.txt");
    // TLisaConfiguration::SetGMFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_GainMatching_fake.txt");
    // TLisaConfiguration::SetGMFileMWD("/u/gandolfo/c4/c4Root/config/lisa/Lisa_GainMatching_fake.txt");
    // TLisaConfiguration::SetMWDParametersFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_MWD_Parameters_DAQtest.txt");

    TLisaConfiguration::SetMappingFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_All_Boards.txt");
    //TLisaConfiguration::SetMappingFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_GainMatching.txt");
    TLisaConfiguration::SetGMFileMWD("/u/gandolfo/c4/c4Root/config/lisa/Lisa_GainMatching.txt");
    TLisaConfiguration::SetMWDParametersFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_MWD_Parameters_LISAmp_lowgain.txt");
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    
    // ::: Get run number :::
    //TFrsConfiguration::SetRunNumber(fileNumber);
    //std::cout << "Run number: " << fileNumber << std::endl;

    //::::::::: Set experiment configurations
    TExperimentConfiguration::SetExperimentStart(1715734200000000000);
    
    //::::::::: Set ranges for histos :::::::::::::::
    // ::: LISA

    //  Channel Energy ::::: (h1_energy_)
    TLisaConfiguration::SetEnergyRange(0,100000);
    TLisaConfiguration::SetEnergyBin(1000);

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,100);
    TLisaConfiguration::SetEnergyBinMWD(500);

    TLisaConfiguration::SetEnergyRangeMWDGM(0,1000);
    TLisaConfiguration::SetEnergyBinMWDGM(450);

    //  Traces Time and Amplitude Ranges 
    TLisaConfiguration::SetTracesRange(0,20);
    TLisaConfiguration::SetTracesBin(2000);
    TLisaConfiguration::SetAmplitudeMin(7000);
    TLisaConfiguration::SetAmplitudeMax(9000);

    // White Rabbit
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(50000);

    TLisaConfiguration::SetWrRateRange(0,3600);
    TLisaConfiguration::SetWrRateBin(3600);

    // ::: FRS
    TFrsConfiguration::Set_Z_range(0,80);
    TFrsConfiguration::Set_AoQ_range(1,10);

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

    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra();
        run->AddTask(nearlinefrs);
    }

    if(LISA_ON && FRS_ON)
    {
        if(FRS_LISA_CORRELATIONS)
        {
            LisaFrsCorrelations* LISA_FRS_corr = new LisaFrsCorrelations(fg);
            run->AddTask(LISA_FRS_corr);
        }
    }


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // FrsLisa

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
