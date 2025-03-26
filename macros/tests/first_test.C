#include <TROOT.h>

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
} EXT_STR_h101;


void first_test()
{   
    const Int_t nev = -1;

    // Define important paths.
    TString c4Root_path = "$C4ROOT_DIR";
    TString ucesb_path = "$UCESB_DIR/empty/empty --input-buffer=200Mi --event-sizes --allow-errors";
    gSystem->ExpandPathName(ucesb_path);

    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    TString filename = "~/lustre/gamma/s100_files/ts/168Dy_new_0006_0104.lmd";

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; // Define which level of data to unpack - we don't use "RAW" or "CAL"
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);
   
    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
 
    
    // Initialise
    run->Init();

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 

    std::cout << "Macro finished successfully." << std::endl;   

}

