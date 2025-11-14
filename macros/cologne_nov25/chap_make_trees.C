#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define MCP_ON 1

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_mcp_t mcp;
} EXT_STR_h101;


void chap_make_trees()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "hispec10";

    // Define important paths.
    TString c4Root_path = "/mnt/data/builds/c4rootnew/c4Root";
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

    // Input file - lmd
    TString filepath = "/mnt/data/lmd/test/";
    TString filename = filepath + "novemberpulser.lmd";
    //TString filename = filepath + "20250410-1505_0001.lmd";

    //TString filename ="/LynxOS/mbsusr/mbsdaq/mbsrun/x86_timesorter/20250410-1505_0001.lmd";

    // Output file - root
    TString outputpath = "/mnt/data/trees/";    
    TString outputFileName = outputpath + "novemberpulser_tree.root";
    //TString outputFileName = outputpath + "20250410-1505_0001_tree.root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 6060; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));

    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; // Define which level of data to unpack
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);



    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TH10MCPConfiguration::SetDetectorConfigurationFile(config_path + "/mcp/mcp_mapping_14nov25.txt");
 
    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
    if (MCP_ON)
    {
        H10MCPReader* unpackmcp = new H10MCPReader((EXT_STR_h101_mcp_onion*)&ucesb_struct.mcp, offsetof(EXT_STR_h101, mcp));
        //unpackmcp->DoFineTimeCalOnline(config_path + "/mcp/test_pulser_14nov25.root", 7000); //make the fine time calibration with a long file (2000000)
        unpackmcp->SetInputFileFineTimeHistos(config_path + "/mcp/test_pulser_14nov25.root"); //create a tree with this fine time calibration

        unpackmcp->SetOnline(false);
        source->AddReader(unpackmcp);
    }

    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //
    if (MCP_ON)
    {
        H10MCPRaw2Cal* calmcp = new H10MCPRaw2Cal();
        calmcp->SetOnline(true);
        run->AddTask(calmcp);

        H10MCPCal2Ana* anamcp = new H10MCPCal2Ana();
        anamcp->SetOnline(false);
        run->AddTask(anamcp);       
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

