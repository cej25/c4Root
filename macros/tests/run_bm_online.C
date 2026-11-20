#include "BeamMonitorOnlineSpectra.h"
#include "BeamMonitorReader.h"
#include "EventHeader.h"
#include "FairLogger.h"
#include "FairRootFileSink.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "UcesbSource.h"

#include <TFolder.h>
#include <TStopwatch.h>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

R__LOAD_LIBRARY(libc4source)
R__LOAD_LIBRARY(libc4Analysis)

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_beammonitor_onion_t beammonitor;
} EXT_STR_h101;

void run_bm_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1,
                   const char* input = "trans://R4L-36", const char* output = "",
                   const char* unpacker = "/u/cjones/c4Root/unpack/exps/beammonitor/beammonitor")
{   

    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);

    TStopwatch timer;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();

    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);
    const TString filename = input;
    const TString outputFileName = output;
    const bool persist = !outputFileName.IsNull();

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 7070;
     
    TString ntuple_options = "UNPACK";
    TString ucesb_path = TString(unpacker) + " --allow-errors --input-buffer=200Mi";
    ucesb_path.ReplaceAll("//","/");

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    EvtHead->Register(false);
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    if (persist) run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histograms Folder", histograms, false);
    run->AddObject(histograms);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
   
    BeamMonitorReader* unpackbeammonitor = new BeamMonitorReader((EXT_STR_h101_beammonitor_onion*)&ucesb_struct.beammonitor, offsetof(EXT_STR_h101, beammonitor));

    // Add readers
    unpackbeammonitor->SetOnline(!persist);
    source->AddReader(unpackbeammonitor);

    run->SetSource(source);

    // Runtime data base
    FairRuntimeDb* rtdb = run->GetRuntimeDb();


    // Add analysis task
    BeamMonitorOnlineSpectra* online = new BeamMonitorOnlineSpectra();
    run->AddTask(online);

    // Initialise
    run->Init();
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    std::cout << "\n\n" << std::endl;
    std::cout << "Data stream is: " << filename << std::endl;
    std::cout << "Beam monitor online port server: " << port << std::endl;
    std::cout << "\n\n" << std::endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

    // Finish
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    std::cout << "CPU used: " << cpuUsage << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    if (persist) std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
}
