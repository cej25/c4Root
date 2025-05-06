bool is_valid_number(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::string chooseHistogram(TString mode, int hist)
{
    if (mode == "TAC")
    {
        if (hist == 1) return "h2_Z41_vs_AoQs2s4";
        else if (hist == 2) return "h2_Z41_vs_Z42";
    }
    else if (mode == "MHTDC")
    {

    }

    return " ";
}

TH2* FindHistogramRecursive(TDirectory* dir, const std::string& histname) {
    TIter next(dir->GetListOfKeys());
    TKey* key;

    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();

        if (obj->InheritsFrom("TH2") && obj->GetName() == histname)
            return (TH2*)obj;

        if (obj->InheritsFrom("TDirectory")) {
            TH2* h = FindHistogramRecursive((TDirectory*)obj, histname);
            if (h) return h;
        }
    }

    return nullptr;
}


void make_frs_gates_from_histos(TString infilename) 
{
    TFile *infile = TFile::Open(infilename, "READ");
    if (!infile || !infile->IsOpen()) {
        std::cerr << "Error: Could not open file " << infilename << std::endl;
        return;
    }

    // Ask the user to choose between TAC or MHTDC
    TString mode_choice;
    std::cout << "Choose mode (TAC or MHTDC): ";
    std::cin >> mode_choice;
    mode_choice.ToUpper();

    if (mode_choice != "TAC" && mode_choice != "MHTDC") {
        std::cerr << "Invalid choice. Please choose either TAC or MHTDC." << std::endl;
        return;
    }

    int seq;
    std::cout << "Multiple sequential (1) or single (2) gate: ";
    std::cin >> seq;

    if (seq != 1 && seq != 2)
    {
        std::cerr << "Invalid choice. Please enter 1 to draw sequential gates, or 2 to draw a single gate!" << std::endl;
        return;
    }

    TString gatename;
    std::cout << "Name your gate file: " << std::endl;
    std::cin >> gatename;

    TFile *outfile = new TFile(gatename + ".root", "RECREATE");

    bool making_gates = true;
    int hist_choice;
    while (making_gates) 
    {
        std::string input;
        std::cout << "Choose what you would like to gate on: " << std::endl;
        std::cout << "1. Z41 vs AoQs2s4 - 2. Z41 vs Z42 - 3. AoQs2s4 vs x2 - 4. AoQs2s4 vs x4 - 5. dEdeg vs Z41" << std::endl;
        std::cout << "6. Z21 vs AoQs1s2 - 7. Z21 vs Z22 - 8. AoQs1s2 vs x1 - 9. AoQs1s2 vs x2 - 10. dEdeg vs Z21" << std::endl;
        std::cout << "11. Z21 vs Z41" << std::endl;
        std::cin >> input;

        if (is_valid_number(input)) 
        {
            hist_choice = std::stoi(input);
            if (hist_choice < 1 || hist_choice > 11)
            {
                std::cerr << "Please enter a valid choice between 1 and 11 (inclusive). " << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "You entered: " << input << std::endl;
            std::cerr << "Please enter a valid integer. " << std::endl;
            return;
        }

        std::string histname = chooseHistogram(mode_choice, hist_choice);
    


        // Try to get the histogram
        TH2* hist = FindHistogramRecursive(infile, histname);
        if (!hist) {
            std::cerr << "Histogram '" << histname << "' not found in file." << std::endl;
            continue;
        }
        else std::cout << "Found histogram " << histname << std::endl;

        // Draw histogram for gate selection
        hist->Draw("COLZ");
        gPad->Update();
        gPad->WaitPrimitive("CUTG");

        TCutG *cut = (TCutG*)gROOT->FindObject("CUTG");
        if (!cut) {
            std::cout << "No gate was drawn. Skipping..." << std::endl;
            continue;
        }

        TString cutname;
        std::cout << "Enter name for this gate (e.g., cut_Z_AoQ): ";
        std::cin >> cutname;

        TCutG *savedCut = (TCutG*)cut->Clone(cutname);
        savedCut->SetName(cutname);
        savedCut->Write();
        gROOT->FindObject("CUTG")->Delete();

        std::cout << "Gate '" << cutname << "' saved to " << gatename << ".root" << std::endl;
        
    }

    outfile->Close();
    infile->Close();
    std::cout << "All gates saved. Done." << std::endl;
}
