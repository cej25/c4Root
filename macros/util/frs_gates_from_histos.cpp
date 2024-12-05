TH2* findTH2(TDirectory* dir, const std::string& histName) {
    if (!dir) return nullptr;

    // Iterate over all keys in the current directory
    TIter next(dir->GetListOfKeys());
    TKey* key;
    while ((key = (TKey*)next())) {
        // Get the class name and check type
        std::string className = key->GetClassName();
        
        // Check if the object is a TH1 (or derived from TH1)
        if (className.find("TH2") != std::string::npos) {
            TH2* hist = dynamic_cast<TH2*>(key->ReadObj());
            if (hist && hist->GetName() == histName) {
                return hist; // Histogram found
            }
        }
        
        // If it's a TDirectory, recursively search within it
        if (className == "TDirectoryFile") {
            TDirectory* subDir = dynamic_cast<TDirectory*>(key->ReadObj());
            std::cout << subDir->GetName() << std::endl;
            TH2* hist = findTH2(subDir, histName);
            if (hist) {
                std::cout << "found :)" << std::endl;
                return hist; // Histogram found in a subdirectory
            }
        }
    }

    std::cout << "not found :(" << std::endl;
    return nullptr; // Histogram not found

}

void frs_gates_from_histos(TString infilename)
{
    TFile* infile = TFile::Open(infilename, "READ");

    if (!infile->IsOpen() || infile->IsZombie())
    {
        std::cout << "Failed to open file. Do you have the correct path?" << std::endl;
    }

    TString gatename;
    std::cout << "Please give this set of gates a name: "; 
    std::cin >> gatename;


    TDirectory* topDir = infile;

    TH2* h2_z_vs_aoq = findTH2(topDir, "h2_Z_vs_AoQ");;
    //infile->GetObject("h2_Z_vs_AoQ", h2_z_vs_aoq);
    
    h2_z_vs_aoq->Draw("COLZ");

    gPad->WaitPrimitive("CUTG");
    TCutG* cut_Z_AoQ = (TCutG*)gROOT->FindObject("CUTG");

    if (cut_Z_AoQ == nullptr)
    {
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }
    else
    {
        cut_Z_AoQ = (TCutG*)cut_Z_AoQ->Clone("cut_Z_AoQ");
        gROOT->FindObject("CUTG")->Delete();

        std::cout << "Created gate: " << cut_Z_AoQ->GetName() << std::endl;

        TFile * outfile =  TFile::Open("test.root","RECREATE");

        gROOT->FindObject("cut_Z_AoQ")->Write();
    }

}