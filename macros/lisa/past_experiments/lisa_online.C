#include <TROOT.h>
//............
// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define WR_ENABLED 0

extern "C"
{
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;

} EXT_STR_h101;
\
void lisa_online()
{   
    if (WR_ENABLED)
    {
        TLisaConfiguration::SetWREnable(true);
    }else{
        TLisaConfiguration::SetWREnable(false);
    } 
    

    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "lisa";

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
    TString filename = "stream://x86l-166"; //lisa daq (not time sorted/stitched)

    //___O F F L I N E
    //TString filename = "/u/gandolfo/data/lustre/despec/lisa/daq_test_0167_*.lmd";  //data with only lisa

    //___O U T P U T - only used if switched on 
    TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/c4data/";
    TString outputFilename = outputpath + "lisa_test.root";

    //:::::::Create online run
    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 2222;
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName)); // don't write after termintion
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
    //:::::::Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R   D E T E C T O R - Load
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching.txt");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::::::: READ Subsystem  ::::::::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (1 == 1)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));
        //unpacklisa->DoFineTimeCalOnline("....root", 100000);
        //unpacklisa->SetInputFileFineTimeHistos(config_path + "....root");

        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        source->AddReader(unpacklisa);
    }

    // ::::::: CALIBRATE Subsystem  ::::::::

    if (LISA_ON)
        {
            LisaRaw2Cal* lisaraw2cal = new LisaRaw2Cal();

            lisaraw2cal->SetOnline(true);
            run->AddTask(lisaraw2cal);
        }

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Online Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    if (LISA_ON)
    {
        // Add analysis task here at some point
        LisaOnlineSpectra* onlinelisa = new LisaOnlineSpectra();

        run->AddTask(onlinelisa);

    }

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // Set Ranges for online histos

    //::::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(0,300000);
    //TLisaConfiguration::SetEnergyRange(0,3500000); //for Chen
    //TLisaConfiguration::SetEnergyBin(1200); // for Chen
    TLisaConfiguration::SetEnergyBin(900);

    //:::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);

    //:::: LISA Traces Time and Amplitude Ranges :::::: (h1_traces_layer_ch)
    TLisaConfiguration::SetTracesRange(0,30);
    TLisaConfiguration::SetTracesBin(3000);
    //TLisaConfiguration::SetTracesBin(5000); //for Chens positive signals
    TLisaConfiguration::SetAmplitudeMin(7000);
    TLisaConfiguration::SetAmplitudeMax(9000);
    //TLisaConfiguration::SetAmplitudeMax(15000); //for Chens positiv signals
    

    //::::::: Initialise
    run->Init();

    //::::::: Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
    cout << "\n\n" << endl;

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
    std::cout << "Output file is " << outputFilename << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
}
