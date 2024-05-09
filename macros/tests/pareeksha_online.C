typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_travmus_onion_t travmus;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;
} EXT_STR_h101;

extern "C"
{
    #include "../../config/s100/frs/setup_des_s100_030_2024_conv.C"
}

void pareeksha_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   
    TString fExpName = "pareeksha";

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
    
    TString filename = "/u/cjones/cs_170er_check_0170_timestitched.lmd";
    //TString filename = "/u/cjones/lustre/gamma/s100_files/ts/168Dy_new_0020_0065.lmd";
    TString outputpath = "";
    TString outputFilename = outputpath + "pareeksha_test.root";

    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 6969;
     
    TString ntuple_options = "UNPACK";
    TString c4Root_path = "/u/cjones/c4Root/";
    TString ucesb_path = c4Root_path + "unpack/exps/" + fExpName + "/" + fExpName + " --allow-errors --input-buffer=200Mi";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    //set mapping/configuration

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
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

    TFrsConfiguration::SetConfigPath(config_path + "/frs/");



    // ::::::: READ DATA FROM UCESB ::::::::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    FrsTravMusReader* unpacktravmus = new FrsTravMusReader((EXT_STR_h101_travmus_onion*)&ucesb_struct.travmus, offsetof(EXT_STR_h101, travmus));
    
    unpacktravmus->SetOnline(true); //false= write to a tree; true=doesn't write to tree
    source->AddReader(unpacktravmus);

    FrsMainReader* unpackfrsmain = new FrsMainReader((EXT_STR_h101_frsmain_onion*)&ucesb_struct.frsmain, offsetof(EXT_STR_h101, frsmain));
    FrsTPCReader* unpackfrstpc = new FrsTPCReader((EXT_STR_h101_frstpc_onion*)&ucesb_struct.frstpc, offsetof(EXT_STR_h101, frstpc));
    FrsUserReader* unpackfrsuser = new FrsUserReader((EXT_STR_h101_frsuser_onion*)&ucesb_struct.frsuser, offsetof(EXT_STR_h101, frsuser));
    FrsTpatReader* unpackfrstpat = new FrsTpatReader((EXT_STR_h101_frstpat_onion*)&ucesb_struct.frstpat, offsetof(EXT_STR_h101, frstpat));
    
    unpackfrsmain->SetOnline(true);
    unpackfrstpc->SetOnline(true);
    unpackfrsuser->SetOnline(true);
    unpackfrstpat->SetOnline(true);
    source->AddReader(unpackfrsmain);
    source->AddReader(unpackfrstpc);
    source->AddReader(unpackfrsuser);
    source->AddReader(unpackfrstpat);


    // ::::::: MAP AND CALIBRATE :::::::::::::
    FrsTravMusRaw2Cal* caltravmus = new FrsTravMusRaw2Cal();

    caltravmus->SetOnline(false);
    run->AddTask(caltravmus);

    FrsMainRaw2Cal* calfrsmain = new FrsMainRaw2Cal();
    FrsTPCRaw2Cal* calfrstpc = new FrsTPCRaw2Cal();
    FrsUserRaw2Cal* calfrsuser = new FrsUserRaw2Cal();
    
    calfrsmain->SetOnline(true);
    calfrstpc->SetOnline(true);
    calfrsuser->SetOnline(true);
    run->AddTask(calfrsmain);
    run->AddTask(calfrstpc);
    run->AddTask(calfrsuser);


    // :::::::: ANALYSIS/MAKE "HITS" :::::::::::
    FrsCal2Hit* hitfrs = new FrsCal2Hit();
     
    hitfrs->SetOnline(false); 
    run->AddTask(hitfrs);


    // ::::::::: ONLINE SPECTRA ::::::::::::::::
    TFrsConfiguration::Set_Z_range(50, 80);
    //FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();
    //run->AddTask(onlinefrs);

    FrsTravMusSpectra* onlinetravmus = new FrsTravMusSpectra();
    run->AddTask(onlinetravmus);

    

    // Initialise
    run->Init();
    //FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
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
