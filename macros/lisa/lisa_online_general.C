#include <TROOT.h>
//............
// Switch all tasks related to LISA :::  on (1)/off (0) :::
#define LISA_ON 1       //always on
#define LISA_DAQ 0      //diplay all the channels from the boards (mapped up to 3 boards)
#define LISA_2x2 1      //display with pareesksha 2x2 mapping system
// WR syncronization
#define WR_ENABLED 0

extern "C"
{
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;

} EXT_STR_h101;


void lisa_online_general()
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
    //TString filename = "stream://x86l-166"; //lisa daq (not time sorted/stitched)

    //___O F F L I N E
    //TString filename = "/u/gandolfo/data/lustre/gamma/LISA/data/x7_241Am/multiple_cards_test/cards_A_B_C_D_E_F_G_0306.lmd"; 
    //TString filename = "/u/gandolfo/data/lustre/despec/s092_s143/run_0075_0001.lmd";  //data with only lisa
    TString filename = "/u/gandolfo/data/lustre/despec/lisa/LISAmp_10layers_0018_*.lmd";  //data with only lisa

    //___O U T P U T - only used if switched on 
    //TString outputpath = "/u/gandolfo/data/lustre/despec/lisa/3x3_board_1/";
    TString outputpath = "/u/gandolfo/data/lustre/gamma/s092_s143_files/ts/";
    TString outputFilename = outputpath + "run_0075_0001.lmd";

    //:::::::Create online run
    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 1111;
     
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
    if (LISA_2x2)
    {
        TLisaConfiguration::SetMappingFile(config_path + "/Lisa_All_Boards.txt");
        //TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Detector_Map_names.txt");
        TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_cards.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_LISAmp_highgain.txt");
        //TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_DAQtest.txt");
        TLisaConfiguration::SetGMFileMWD(config_path + "/Lisa_GainMatching_cards.txt");

    }

    if (LISA_DAQ)
    {
        TLisaConfiguration::SetMappingFile(config_path + "/Lisa_All_Boards.txt");
        //TLisaConfiguration::SetMappingFile(config_path + "/Lisa_3x3_test_board.txt");
        TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching_fake.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_DAQtest.txt");

    }


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::::::: READ Subsystem  ::::::::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISA_ON)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));
        
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();

        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        source->AddReader(unpacklisa);

        lisaraw2ana->SetOnline(true);
        run->AddTask(lisaraw2ana);
    }

    // ::::::: CALIBRATE Subsystem  ::::::::

    if (LISA_ON)
    {
        LisaAna2Cal* lisaana2cal = new LisaAna2Cal();

        lisaana2cal->SetOnline(true);
        run->AddTask(lisaana2cal);
    }

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Online Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    if (LISA_2x2)
    {

        LisaOnlineSpectra* onlinelisa = new LisaOnlineSpectra();
        run->AddTask(onlinelisa);

    }

    if (LISA_DAQ)
    {

        LisaOnlineSpectraDaq* onlinelisadaq = new LisaOnlineSpectraDaq();
        run->AddTask(onlinelisadaq);

    }
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    
    // Set Ranges for online histos

    //::::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(0,100000);
    TLisaConfiguration::SetEnergyBin(1000);

    //  MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(1,100);
    TLisaConfiguration::SetEnergyBinMWD(500);

    //:::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);

    //:::: LISA Traces Time and Amplitude Ranges :::::: (h1_traces_layer_ch)
    TLisaConfiguration::SetTracesRange(0,8);
    TLisaConfiguration::SetTracesBin(800);
    TLisaConfiguration::SetAmplitudeMin(7500);
    TLisaConfiguration::SetAmplitudeMax(8400);
    

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
}
