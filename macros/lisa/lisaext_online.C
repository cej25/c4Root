#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define WR_ENABLED 1

extern "C"
{
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisaext_onion_t lisa;

} EXT_STR_h101;

void lisaext_online()
{   
    if (WR_ENABLED)
    {
        TLisaConfiguration::SetBREnable(true);
    }else{
        TLisaConfiguration::SetBREnable(false);
    } 

    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    
    // ::: Experiment name - this set the path for all the config
    TString fExpName = "lisaext";

    // ::: Here you define commonly used path
    TString c4Root_path = "/home/lisa/programs/c4/c4Root";
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
    TString filename = "stream://134.95.192.248:6002"; 

    // ::: OFFLINE READING - For testing
    //TString inputpath = "/home/lisa/data/server/lmd/";                   
    //TString filename = inputpath + "run_0076_0001.lmd"; 
    
    // ::: OUTPUT - does not write a tree if it is not set later
    TString outputpath = "/home/lisa/data/"; //testing
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
    // ::: C O N F I G    F O R   S Y S T E M S   - Load
    
    // ::: Lisa config

    // ::: Mapping
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Mapping_5x5_L2_180deg.txt");
    
    // ::: Gain Matching Febex, MWD, dEdX
    TLisaConfiguration::SetGMFile(config_path +     "/Lisa_GainMatching_5x5_L2_180deg.txt");
    TLisaConfiguration::SetGMFileMWD(config_path +  "/Lisa_GainMatching_5x5_L2_180deg.txt");
    TLisaConfiguration::SetGMFiledEdX(config_path + "/Lisa_GainMatching_5x5_L2_180deg.txt");
    
    // ::: MWD parameters
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_v1.txt");
    
    TLisaConfiguration::SetExcludedChannels({
    std::make_tuple(1,0,0),
    }); 


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::: READ Subsystem :::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISA_ON)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisaext_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));

        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        source->AddReader(unpacklisa);
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

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    // =========== **** SPECTRA ***** ========================================================= //
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    

    if (LISA_ON)
    {
        LisaOnlineSpectra* onlinelisa = new LisaOnlineSpectra();
        run->AddTask(onlinelisa);
    }

    // ::: CONFIGURATIONS FOR ONLINE HISTOS :::

    // ::: LISA
    //      Channel Energy 
    TLisaConfiguration::SetEnergyRange(0,120000); 
    TLisaConfiguration::SetEnergyBin(1000); 

    //      MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,200);
    TLisaConfiguration::SetEnergyBinMWD(1000);

    //      LISA WR Time Difference 
    TLisaConfiguration::SetBrDiffRange(0,100000000);
    TLisaConfiguration::SetBrDiffBin(20000);
    TLisaConfiguration::SetBrRateRange(0,900);
    TLisaConfiguration::SetBrRateBin(900);

    //      LISA Traces Ranges 
    TLisaConfiguration::SetTracesRange(0,950);
    //TLisaConfiguration::SetTracesBin(20);
    //TLisaConfiguration::SetAmplitudeMin(5000);
    //TLisaConfiguration::SetAmplitudeMax(16000);
   
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
