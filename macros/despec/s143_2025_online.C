#include "/home/fair_install/fair_soft/FairSoft/install/include/root/TROOT.h"

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FIMP_ON 1
#define FATIMA_ON 1
#define FRS_ON 1
#define BPLAST_ON 1
#define TRAV_MUSIC_ON 0
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently DO NOT USE!!

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "/home/c4Root/config/s143/frs/setup_s092_001_2024_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fimp_onion_t fimp;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_frs_onion_t frs;
} EXT_STR_h101;



void s143_2025_online()
{
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s143";

    // Define important paths.
    TString c4Root_path = "/u/despec/s143_online/c4Root";
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
    FairLogger::GetLogger()->SetLogToScreen(true);
    FairLogger::GetLogger()->SetColoredLog(true);
   
    // Define where to read data from. Online = stream/trans server, Nearline = .lmd file.
    TString filename = "trans://lxg1257";
    //TString filename = "stream://x86l-164";
    
    // Create online run
    Int_t refresh = 2; // Refresh rate for online histograms
    Int_t port = 6969;

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFilename));

    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    run->GetHttpServer()->SetItemField("/","_toptitle","FIMP Online Monitoring");
    run->GetHttpServer()->SetItemField("/","_layout","grid2x2");

// Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; // Define which level of data to unpack - we don't use "RAW" or "CAL"
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    TFRSParameter* frs= new TFRSParameter();
    TMWParameter* mw = new TMWParameter();
    TTPCParameter* tpc = new TTPCParameter();
    TMUSICParameter* music = new TMUSICParameter();
    TLABRParameter* labr = new TLABRParameter();
    TSCIParameter* sci = new TSCIParameter();
    TIDParameter* id = new TIDParameter();
    TSIParameter* si = new TSIParameter();
    TMRTOFMSParameter* mrtof = new TMRTOFMSParameter();
    TRangeParameter* range = new TRangeParameter();
    setup(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);

    TFrsConfiguration::SetParameters(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);

    TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/fatima/labr_alloc_may13.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
    TFimpConfiguration::SetMappingFile(config_path + "/fimp/FIMP_Channel_2025.txt");
   

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (FATIMA_ON)
    {
        FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
        unpackfatima->DoFineTimeCalOnline(config_path + "/fatima/fine_time_fatima_july2025.root", 100000);
        //unpackfatima->SetInputFileFineTimeHistos(config_path + "/fatima/fine_time_july2025.root");

        unpackfatima->SetOnline(true);
        source->AddReader(unpackfatima);
    }

    if (FIMP_ON)
    {
        FimpReader* unpackfimp = new FimpReader((EXT_STR_h101_fimp_onion*)&ucesb_struct.fimp, offsetof(EXT_STR_h101, fimp));
        unpackfimp->DoFineTimeCalOnline(config_path + "/fimp/fine_time_fimp_july2025.root", 100000);
        //unpackfimp->SetInputFileFineTimeHistos(config_path + "/fimp/fine_time_fimp_july2025.root");

        unpackfimp->SetOnline(true);
        source->AddReader(unpackfimp);
    }
    
    if (BPLAST_ON)
    {
        bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
        unpackfatima->DoFineTimeCalOnline(config_path + "/bplast/fine_time_bplast_july2025.root", 100000);
        //unpackbplast->SetInputFileFineTimeHistos(config_path + "/bplast/fine_time_bplast_july2025.root");

        unpackfatima->SetOnline(true);
        source->AddReader(unpackbplast);
    }

    if (FRS_ON)
    {

        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs));
        
        unpackfrs->SetOnline(true);

        source->AddReader(unpackfrs);
    }



    if (FATIMA_ON)
    {
        FatimaRaw2Cal* calfatima = new FatimaRaw2Cal();

        calfatima->SetOnline(true);
        run->AddTask(calfatima);
    }

    if (FIMP_ON)
    {
        FimpRaw2Cal* calfimp = new FimpRaw2Cal();

        calfimp->SetOnline(true);
        run->AddTask(calfimp);
    }

    if (BPLAST_ON)
    {
        bPlastRaw2Cal* calbplast = new bPlastRaw2Cal();

        calbplast->SetOnline(true);
        run->AddTask(calbplast);
    }
    
    if (FRS_ON)
    {

        FrsRaw2Cal* calfrs = new FrsRaw2Cal();

        calfrs->SetOnline(true);
        run->AddTask(calfrs);
    }
 // ---------------------------------------------------------------------------------------- //
    // *** Analyse Subsystem Hits ************************************************************* //

    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();

        hitfrs->SetOnline(true); 
        run->AddTask(hitfrs);
    } 

    if (FIMP_ON)
    {
        // Add analysis task here at some point
        FimpOnlineSpectra* onlinefimp = new FimpOnlineSpectra();

        run->AddTask(onlinefimp);
    }
    if (FATIMA_ON)
    {
        // Add analysis task here at some point
        FatimaOnlineSpectra* onlinefatima = new FatimaOnlineSpectra();

        run->AddTask(onlinefatima);
    }
    if (BPLAST_ON)
    {
        // Add analysis task here at some point
        bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();

        run->AddTask(onlinebplast);
    }
    if (FRS_ON)
    {
        // Add analysis task here at some point
        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();

        run->AddTask(onlinefrs);
    }

    TFrsConfiguration::Set_Z_range(50,75);
    TFrsConfiguration::Set_AoQ_range(2.3,3.0);

    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "FIMP online port server: " << port << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

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

