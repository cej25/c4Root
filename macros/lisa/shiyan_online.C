#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 1
#define WR_ENABLED 1

// Define for online if testing or during experient
#define TEST 1
#define EXP 0

// Define FRS setup.C file - FRS should provide; place in /config/shiyan/frs/
extern "C"
{
    #include "../../config/shiyan/frs/setup/setup_160_49_2025_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

void shiyan_online()
{   
    if (WR_ENABLED)
    {
        TLisaConfiguration::SetWREnable(true);
    }else{
        TLisaConfiguration::SetWREnable(false);
    } 

    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    
    // ::: Experiment name - this set the path for all the config
    TString fExpName = "shiyan";

    // ::: Here you define commonly used path
    TString c4Root_path = "/u/lisa/c4/c4Root";
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
    
    // ::: ONLINE READING
    //TString filename = "stream://x86l-166"; //lisa daq (not time sorted/stitched)
    TString filename = "trans://lxg3107:6000"; //Set to stiched data
    
    // ::: OUTPUT - does not write a tree if it is not set layer
    TString outputpath = "/u/lisa/data/test_c4/"; //testing
    TString outputFileName = outputpath + "output_online.root";
    
    // ::: Create online run
    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 2222;
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));   // if commented - don't write after termintion
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
    // ::: Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

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
    // ::: C O R R E L A T I O N S - Initialise 
  
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: C O N F I G    F O R   S Y S T E M S   - Load
    
    // ::: Exp config
    TExperimentConfiguration::SetExperimentStart(1746597600000000000);// Start for Shiyan data: May 7th, 8a.m. //including testing
    // for S100, 3 and 4. for 2025+ 12 and 13.
    TExperimentConfiguration::SetBOSTrig(3);
    TExperimentConfiguration::SetEOSTrig(4);
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");

    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path +  "/frs/crate_map.txt");
    TFrsConfiguration::SetTravMusDriftFile(config_path +  "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path + "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path +  "/frs/AoQ_Drift_fragments.txt");

    // ::: Lisa config
    if ( TEST )
    {
        
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_All_Boards.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching_cards.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_cards.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_DAQtest.txt");
        
        TLisaConfiguration::SetExcludedChannels({
        std::make_tuple(1,0,0),
        }); 

    }
    if ( EXP )
    {
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_4x4_shiyan.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching_shiyan.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_shiyan.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_shiyan_v0.txt");

        // TLisaConfiguration::SetExcludedChannels({
        // std::make_tuple(1,0,0),
        // });        
    }


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::: READ Subsystem :::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISA_ON)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));

        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        source->AddReader(unpacklisa);
    }

    if (FRS_ON)
    {   
        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs)); 
        unpackfrs->SetOnline(true);
        source->AddReader(unpackfrs);
    }   


    // ::: CALIBRATE Subsystem  :::

    if (LISA_ON)    //this is analysis and calibration together
    {
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();
        lisaraw2ana->SetOnline(true);
        run->AddTask(lisaraw2ana); 
        
        LisaAna2Cal* lisaana2cal = new LisaAna2Cal();
        lisaana2cal->SetOnline(true);
        run->AddTask(lisaana2cal);
    }

    if (FRS_ON)
    {
        FrsRaw2Cal* calfrs = new FrsRaw2Cal();
        calfrs->SetOnline(true);
        run->AddTask(calfrs);
    }

    // ::: ANALYSE FRS  :::

    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        
        hitfrs->SetOnline(true); 
        run->AddTask(hitfrs);
    } 

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    // =========== **** SPECTRA ***** ========================================================= //
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    

    if (LISA_ON)
    {
        LisaOnlineSpectra* onlinelisa = new LisaOnlineSpectra();
        run->AddTask(onlinelisa);
    }
    
    if (FRS_ON)
    {
        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();
        //For monitoring FRS on our side
        //FrsRawSpectra* frsrawspec = new FrsRawSpectra();
        //FrsCalSpectra* frscalspec = new FrsCalSpectra();

        run->AddTask(onlinefrs);
        //run->AddTask(frsrawspec);
        //run->AddTask(frscalspec);
    }

    // ::: Correlation Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    if (LISA_ON && FRS_ON)
    {
        LisaFrsCorrelationsOnline* lisafrscorr = new LisaFrsCorrelationsOnline();
        run->AddTask(lisafrscorr);
    }

    // ::: CONFIGURATIONS FOR ONLINE HISTOS :::
    // ::: FRS
    TFrsConfiguration::Set_Z_range(10,60);
    TFrsConfiguration::Set_AoQ_range(1.8,3.5);
    TFrsConfiguration::Set_dE_music41_range(0,4000);
    TFrsConfiguration::Set_dE_music21_range(0,4000);

    // ::: LISA
    //      Channel Energy 
    TLisaConfiguration::SetEnergyRange(0,100000);
    TLisaConfiguration::SetEnergyBin(1000);

    //      MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,500);
    TLisaConfiguration::SetEnergyBinMWD(1000);

    //      LISA WR Time Difference 
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);
    TLisaConfiguration::SetWrRateRange(0,900);
    TLisaConfiguration::SetWrRateBin(900);

    //      LISA Traces Ranges 
    TLisaConfiguration::SetTracesRange(0,3.9);
    TLisaConfiguration::SetTracesBin(390);
    //TLisaConfiguration::SetAmplitudeMin(7500);
    //TLisaConfiguration::SetAmplitudeMax(8400);
   
    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
    cout << "\n\n" << endl;
    
    // create sink object before run starts    
    //FairSink* sf = FairRunOnline::Instance()->GetSink();

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

    // Finish
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    //std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
}
