#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define MCP_ON 1
#define STEFAN_ON 1
#define FRS_ON 1 

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s115/frs/setup_115_022_2025_s1calib_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_mcp_t mcp;
    EXT_STR_h101_stefan_t stefan;
    EXT_STR_h101_frs_onion_t frs;
} EXT_STR_h101;


void g_hispec10_online()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "hispec10";

    // Define important paths.
    TString c4Root_path = "/u/despec/s103_online/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --input-buffer=200Mi --event-sizes --allow-errors";
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

    // Define where to read data from. Online = stream/trans server, Nearline = .lmd file.
    //TString filename = "/u/cjones/onlymcp09041755.lmd";
//    TString filename = "/data.local1/lustre/despec/s092_s103/run_0007_0001.lmd"; 
//	TString filename ="stream://x86l-168";  
  TString filename = "trans://lxg3107:6000";
    TString outputpath = "htest_events";
    TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 2; // Refresh rate for online histograms
    Int_t port = 3333; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->ActivateHttpServer(refresh, port);
    run->SetSink(new FairRootFileSink(outputFileName));
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

  
    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; // Define which level of data to unpack
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    // ------------------------------------------------------------------------------------ //
    // *** Initialise FRS parameters ****************************************************** //
    
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
    //TFrsConfiguration::SetParameterFilename();
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Gates *************************************************************** //
    
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");

    
    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TH10MCPConfiguration::SetDetectorConfigurationFile(config_path + "/mcp/mcp_mapping.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
 
    TStefanConfiguration::SetDetectorConfigurationFile(config_path + "/stefan/stefan_mapping.txt");
    TStefanConfiguration::SetDetectorCoefficientFile(config_path + "/stefan/stefan_cal.txt");

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
    if (MCP_ON)
    {
        H10MCPReader* unpackmcp = new H10MCPReader((EXT_STR_h101_mcp_onion*)&ucesb_struct.mcp, offsetof(EXT_STR_h101, mcp));
        //unpackmcp->DoFineTimeCalOnline(config_path + "/mcp/mcp_fine_time_0905.root", 80000);
        unpackmcp->SetInputFileFineTimeHistos(config_path + "/mcp/mcp_fine_time_1105.root");
        
        unpackmcp->SetOnline(true);
        source->AddReader(unpackmcp);
    }

    if (STEFAN_ON)
    {
        StefanReader* unpackstefan = new StefanReader((EXT_STR_h101_stefan_onion*)&ucesb_struct.stefan, offsetof(EXT_STR_h101, stefan));
        
        unpackstefan->SetOnline(true);
        source->AddReader(unpackstefan);
    }
    
    if (FRS_ON)
    {
        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs));
        
        unpackfrs->SetOnline(true);
        
        source->AddReader(unpackfrs);
    }
    
    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //
    if (MCP_ON)
    {
        H10MCPRaw2Cal* calmcp = new H10MCPRaw2Cal();
        
        calmcp->SetOnline(false);
        run->AddTask(calmcp);
    }

    TStefanConfiguration::SetFrontBackEnergy(10000000);
    TStefanConfiguration::SetFrontBackTime(4000);
    
    if (STEFAN_ON)
    {
        StefanRaw2Cal* calstefan = new StefanRaw2Cal();

        calstefan->SetOnline(true);
        run->AddTask(calstefan);
    }
    
    if (FRS_ON)
    {
        FrsRaw2Cal* calfrs = new FrsRaw2Cal();
        
        calfrs->SetOnline(true);
        run->AddTask(calfrs);
    }


    // ---------------------------------------------------------------------------------------- //
    // *** Analyse Subsystem Hits ************************************************************* //
    
    // Stefan MCP etc..
    if (MCP_ON)
    {
        H10MCPCal2Ana* anamcp = new H10MCPCal2Ana();
        
        anamcp->SetOnline(false);
        run->AddTask(anamcp);
    }

    if (STEFAN_ON)
    {
        StefanCal2Hit* hitstefan = new StefanCal2Hit();
        
        hitstefan->SetOnline(true);
        run->AddTask(hitstefan);
    }
    
    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        
        hitfrs->SetOnline(true); 
        run->AddTask(hitfrs);
    } 


    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //   
    if (MCP_ON)
    {
        H10MCPOnlineSpectra* onlinemcp = new H10MCPOnlineSpectra();
        
        run->AddTask(onlinemcp);
        
    }
    
    if (STEFAN_ON)
    {
        StefanOnlineSpectra* onlinestefan = new StefanOnlineSpectra();
        // onlinestefan->SetBinningEnergy(65000,0,65000);
        run->AddTask(onlinestefan);
    }

    TFrsConfiguration::Set_Z_range(30,50);
    TFrsConfiguration::Set_AoQ_range(1.8,2.4);
    TFrsConfiguration::Set_x2_range(-120,120);
    TFrsConfiguration::Set_x4_range(-120,120);
    std::vector<FrsGate*> frsgates{};
 
    if (FRS_ON)
    {
        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra(frsgates);
        // For monitoring FRS on our side
        FrsRawSpectra* frsrawspec = new FrsRawSpectra();
        FrsCalSpectra* frscalspec = new FrsCalSpectra();
    
        run->AddTask(onlinefrs);
        run->AddTask(frsrawspec);
        run->AddTask(frscalspec);
    }
   
  
    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Online port server: " << port << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 

    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   
   // ----------------------------------------------------------------------------------------- //

}

