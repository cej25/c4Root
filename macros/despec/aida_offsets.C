#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define AIDA_ON 1

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_fatimavme_onion_t fatimavme;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;
    EXT_STR_h101_beammonitor_onion_t beammonitor;
    EXT_STR_h101_bgo_onion_t bgo;
    EXT_STR_h101_bb7vme_onion_t bb7vme;
} EXT_STR_h101;


void aida_offsets()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    // TString fExpName = "NovTest";
    TString fExpName = "s181";
    //TString fExpName = "beammonitor";

    // Define important paths.
    //TString c4Root_path = "/u/jbormans/c4Root";
    //TString c4Root_path = "/u/despec/s181_online/c4Root";
    TString c4Root_path = "/home/nhubbard/c4root/c4Root";
    TString screenshot_path = "~/lustre/gamma/dryrunmarch24/screenshots/";
    //TString c4Root_path = "/u/cjones/c4Root";
    // Some pulser events are huge allow it
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --allow-errors --input-buffer=200Mi --event-sizes";
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
    //TString filename = "stream://x86l-182"; // BGO
    // DO NOT CHANGE THIS DURING A RUN!!!!!!!
    //TString filename = "trans://x86l-144"; // ??
//    TString filename = "trans://x86l-86"; // ??.
    TString filename = "/home/nhubbard/c4root/aida_*_pulser_eb_0001.lmd"; // 
    //TString filename = "stream://x86l-182"; // bgo
    //TString filename = "trans://lxg1257"; // timesorter.
    //TString filename = "trans://R4L-21"; // beammonitor
    // TString filename = "stream://x86l-87"; // bplast
    //TString filename = "stream://x86l-117"; // fatima tamex
    //TString filename = "~/lustre/gamma/dryrunmarch24/ts/Au_beam_0010_0001.lmd";
    //TString filename = "~/lustre/gamma/s100_files/ts/calibrations/152Eu_calib_0016_*.lmd";
   // TString filename = "~/lustre/gamma/s100_files/ts/168Dy_0033_0003.lmd";
    TString outputpath = "output";
    TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5000; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // trying to kill ParSet errors
    /*FairRuntimeDb* rtdb = FairRunOnline::Instance()->GetRuntimeDb();
    FairGeoParSet* geo = new FairGeoParSet("FairGeoParSet");
    FairBaseParSet* base = new FairBaseParSet("FairBaseParSet");
    rtdb->addContainer(geo);rtdb->addContainer(base);*/

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; // Define which level of data to unpack - we don't use "RAW" or "CAL"
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    TAidaConfiguration::SetBasePath(config_path + "/AIDA");

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
    if (AIDA_ON)
    {
        AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));
        
        unpackaida->SetOnline(true);
        source->AddReader(unpackaida);
    }

   
    if (AIDA_ON)
    {
        AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
        
        aidaCalibrator->SetOnline(true);
        run->AddTask(aidaCalibrator);
        
    }
    


    // ---------------------------------------------------------------------------------------- //
    // *** Analyse Subsystem Hits ************************************************************* //
    
    if (AIDA_ON)
    {        
        AidaCal2Hit* aidaHitter = new AidaCal2Hit();
        
        aidaHitter->SetOnline(true);
        run->AddTask(aidaHitter);
    }


    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //
    
    
    AidaPulserWalkthrough* aidaOnline = new AidaPulserWalkthrough();
    if (AIDA_ON)
    {
        run->AddTask(aidaOnline);
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

    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //
     

    aidaOnline->FindOffsets();


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

