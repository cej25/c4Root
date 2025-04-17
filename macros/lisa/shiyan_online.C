#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 1
#define WR_ENABLED 0

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

void shiyan_online()
{   
    if (WR_ENABLED)
    {
        TLisaConfiguration::SetWREnable(true);
    }else{
        TLisaConfiguration::SetWREnable(false);
    } 

    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "pareeksha";

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
    //___O N L I N E
    //TString filename = "stream://x86l-166"; //lisa daq (not time sorted/stitched)
    //TString filename = "trans://lxg1257:6000"; // time stitched

    //___O F F L I N E
    TString filename = "/u/gandolfo/data/lustre/gamma/s092_s143_files/ts/run_0075_0001.lmd"; 

    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/c4data/";
    TString outputFileName = outputpath + "pareeksha_test.root";


    //:::::::Create online run
    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 2020;
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName)); 
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
    //:::::::Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

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

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::: C O R R E L A T I O N S - Initialise 
  
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R   D E T E C T O R - Load
    // ::: Exp config
    TExperimentConfiguration::SetExperimentStart(1715734200000000000);//Start of pareeksha with primary beam: 15 May 00:50
    // for S100, 3 and 4. for 2025+ 12 and 13.
    TExperimentConfiguration::SetBOSTrig(3);
    TExperimentConfiguration::SetEOSTrig(4);
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");

    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path + "/pareeksha/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/../pareeksha/frs/crate_map.txt");
    TFrsConfiguration::SetTravMusDriftFile(config_path + "/../pareeksha/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path + "/../pareeksha/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path + "/../pareeksha/frs/AoQ_Drift_fragments.txt");

    // ::: Lisa config
    //TLisaConfiguration::SetMappingFile(config_path + "/Lisa_5x5_shiyan.txt");
    TLisaConfiguration::SetMappingFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_Detector_Map_names.txt");

    TLisaConfiguration::SetGMFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_GainMatching_pareeksha.txt");
    TLisaConfiguration::SetGMFileMWD("/u/gandolfo/c4/c4Root/config/lisa/Lisa_GainMatching_pareeksha.txt");
    TLisaConfiguration::SetMWDParametersFile("/u/gandolfo/c4/c4Root/config/lisa/Lisa_MWD_Parameters_DAQtest.txt");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R  H I S T O S
    // White Rabbit
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(50000);
    TLisaConfiguration::SetWrRateRange(0,900);
    TLisaConfiguration::SetWrRateBin(900);
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::::::: READ Subsystem  ::::::::

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


    // ::::::: CALIBRATE Subsystem  ::::::::

    if (LISA_ON) //this is analysis and calibration together
    {
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();
        lisaraw2ana->SetOnline(true);
        run->AddTask(lisaraw2ana); 
        
        LisaAna2Cal* lisaana2cal = new LisaAna2Cal();
        lisaana2cal->SetOnline(false);
        run->AddTask(lisaana2cal);
    }

    if (FRS_ON)
    {
        FrsRaw2Cal* calfrs = new FrsRaw2Cal();
        calfrs->SetOnline(true);
        run->AddTask(calfrs);
    }


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::::::: ANALYSE FRS  ::::::::

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

    TFrsConfiguration::Set_Z_range(50,75);
    TFrsConfiguration::Set_AoQ_range(2.3,3.0);
    
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

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // FrsLisa

    // if (LISA_ON && FRS_ON)
    // {
    //     LisaFrsCorrelations* lisafrscorr = new LisaFrsCorrelations();
    //     run->AddTask(lisafrscorr);
    // }

    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
    cout << "\n\n" << endl;
    
    // create sink object before run starts    
    FairSink* sf = FairRunOnline::Instance()->GetSink();

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
    //std::cout << "Output file is " << outputFilename << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
}
