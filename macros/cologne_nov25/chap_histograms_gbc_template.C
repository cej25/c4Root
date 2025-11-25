#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define MCP_ON 1

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_mcp_t mcp;

} EXT_STR_h101;


void chap_histograms()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "hispec10";

    // Define important paths.
    TString c4Root_path = "/lustre/gamma/gbrunic/McpTest/c4Root";
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

    /*// Define where to read data from. Online = stream/trans server, Nearline = .lmd file.*/
    /*// Input file - root trees*/
    /*TString filepath = "/mnt/data/trees/";*/
    /*TString filename = filepath + "novemberpulser_tree.root";*/
    /*//TString filename = filepath + "20250410-1505_0001_tree.root";*/
    /**/
    /*// Output file - histos file*/
    /*TString outputpath = "/mnt/data/histos/";*/
    /*TString outputFileName =  outputpath + "novemberpulser_histos.root";*/
    /*//TString outputFileName =  outputpath + "20250410-1505_0001_histos.root";*/
 
    // Define where to read data from. Online = stream/trans server, Nearline = .lmd file.
    // Input file - root trees
    TString filepath = "/lustre/gamma/gbrunic/McpTest/test_files/";
    TString filename = filepath + "20250410-1505_0001_tree.root";

    // Output file - histos file
    TString outputpath = "/lustre/gamma/gbrunic/McpTest/test_files/";
    TString outputFileName =  outputpath + "20250410-1505_0001_histos_postgate.root";


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);


    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TH10MCPConfiguration::SetDetectorConfigurationFile(config_path + "/mcp/mcp_mapping_14nov25.txt");
   
    McpGate* testGate0 = new McpGate("testGate0", "/lustre/gamma/gbrunic/McpTest/test_files/testGates.root");
    McpGate* testGate1 = new McpGate("testGate1", "/lustre/gamma/gbrunic/McpTest/test_files/testGatesSecond.root");
    std::vector<McpGate*> mcpGateVector = {testGate0, testGate1};
   
    // ---------------------------------------------------------------------------------------- //
    if (MCP_ON)
    {
        H10MCPNearlineSpectra* nearlinemcp = new H10MCPNearlineSpectra(mcpGateVector);
        
        run->AddTask(nearlinemcp);
    }
       
  
    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "\n\n" << endl;

    // Run
   // run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 
    run->Run(1000000000); 
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

