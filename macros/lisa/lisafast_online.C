#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISAFAST_ON 1


extern "C"
{
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisafast_onion_t lisafast;

} EXT_STR_h101;


void lisafast_online()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "lisafast";

    // Define important paths.
    TString c4Root_path = "/home/lisa/programs/c4/fast_c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    // Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    // Set level of debug information
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    // ::: ONLINE READING
    //TString filename = "stream://134.95.192.248:6002";

    // ::: OFFLINE READING - For testing
    TString inputpath = "/home/lisa/data/lmd/"; 
    TString filename = inputpath + "tamex_0012_0001.lmd";

    // ::: OUTPUT - does not write a tree if it is not set later
    TString outputpath = "/home/lisa/data/"; //testing
    TString outputFileName = outputpath + "output_online.root";


    // Create Online run
    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 2222; 

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // ::: Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; 
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);



    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TLisaFastConfiguration::SetDetectorConfigurationFile(config_path + "/Lisa_Mapping_LaBr3.txt");
    //TLisaFastConfiguration::SetDetectorCoefficientFile(config_path + "/lisafast");
    //TLisaFastConfiguration::SetDetectorTimeshiftsFile(config_path + "/lisafast");
    

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);
    
    if (LISAFAST_ON)
    {
        LisaFastReader* unpacklisafast = new LisaFastReader((EXT_STR_h101_lisafast_onion*)&ucesb_struct.lisafast, offsetof(EXT_STR_h101, lisafast));
        //unpacklisafast->DoFineTimeCalOnline(config_path + "/lisafast/fine_time_histos_1709.root", 100000);
        unpacklisafast->SetInputFileFineTimeHistos(config_path + "/fine_time_histos_1709.root");

        unpacklisafast->SetOnline(true);
        source->AddReader(unpacklisafast);
    }
    

    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //
    
    if (LISAFAST_ON)
    {
        LisaFastRaw2Cal* callisafast = new LisaFastRaw2Cal();
        // callisafast->PrintDetectorMap();
        // callisafast->PrintDeteclisafast();
        
        callisafast->SetOnline(true);
        run->AddTask(callisafast);
    }
    
    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //
    
    if (LISAFAST_ON)
    {
        LisaFastOnlineSpectra* onlinelisafast = new LisaFastOnlineSpectra();
        // onlinelisafast->SetBinningSlowToT(2000,560,660);
        // onlinelisafast->SetBinningFastToT(1000,0.1,100.1);
        // onlinelisafast->SetBinningEnergy(2000,0,3500);

        std::vector<int> dets = {1};
        onlinelisafast->SetDetectorsToPlot(dets);
        
        //onlinelisafast->AddReferenceDetectorForTimeDifferencesWithEnergyGates(1,1332);
        //onlinelisafast->SetEnergyGateWidth(20);
        
        run->AddTask(onlinelisafast);
    }
    


    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Online port server: " << port << endl;
    cout << "\n\n" << endl;

    // create sink object before run starts    
    FairSink* sf = FairRunOnline::Instance()->GetSink();

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 

    // write online histograms if desired.
    //TFile* tf = new TFile(sf->GetFileName(), "UPDATE");
    //histograms->Write();

    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //
    


    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
   
   // ----------------------------------------------------------------------------------------- //

}

