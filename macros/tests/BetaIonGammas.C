#include <TROOT.h>

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s100/frs/setup_s100_dryrun.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;
    EXT_STR_h101_bgo_onion_t bgo;
} EXT_STR_h101;


void BetaIonGammas()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s100";

    // Define important paths.
    TString c4Root_path = "/u/cjones/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors --max-events=300000";
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
    //TString filename = "~/lustre/gamma/jeroen/S100/cluster/trees/162Eu_new_0025_0001_aidaana.root";
    TString filename = "~/162_combined.root";
    //TString filename = "~/lustre/gamma/s100_nearline/trees/162Eu_0031_0001_tree.root";
    TString outputpath = "test_BIG_43";
    TString outputFileName = outputpath + ".root";

    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);

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

    // ------------------------------------------------------------------------------------ //
    // *** Initialise Gates *************************************************************** //

    TbPlastConfiguration::SetDetectorMapFile(config_path + "/bplast/bplast_alloc_mar20.txt");
    TAidaConfiguration::SetBasePath(config_path + "/AIDA");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TGermaniumConfiguration::SetDetectorConfigurationFile(config_path + "/germanium/ge_alloc_mar21.txt");
    // TBGOTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/bgo/bgo_alloc.txt");

    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Nearline Spectra ********************************************************************* //

    //FrsGate* Eu162 = new FrsGate("162Eu", config_path + "/frs/Gates/162Eu_new.root");
    FrsGate* Tb166 = new FrsGate("166Tb", config_path + "/frs/Gates/166Tb.root");
    std::vector<FrsGate*> fgs = {};
    //fgs.emplace_back(Eu162);
    fgs.emplace_back(Tb166);

    BetaIonCorrelations* big_corrs = new BetaIonCorrelations(fgs);
    run->AddTask(big_corrs);
    
    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "\n\n" << endl;

    // Run
    //run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 
    run->Run(0,100000000); // most files around 9m events? can increase this number? dunno

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
