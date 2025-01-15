bool Gate_Z_AoQ_driftcorr(TTree* evt) {
    
    TString cuts;

    std::cout << "Drawing Z_AoQ_driftcorr" << std::endl;
    evt->Draw("FrsHitData.fID_z_driftcorr:FrsHitData.fID_AoQ_driftcorr>>h2_Z_vs_AoQ_driftcorr(2000,1.0,4.0,2000,20,100)", cuts);

    TH2F* h2_Z_vs_AoQ_driftcorr = (TH2F*)gROOT->FindObject("h2_Z_vs_AoQ_driftcorr");

    if (h2_Z_vs_AoQ_driftcorr) {
        h2_Z_vs_AoQ_driftcorr->SetTitle("Draw Z vs. AoQ driftcorr gate");
        h2_Z_vs_AoQ_driftcorr->Draw("COLZ");
    }

    gPad->WaitPrimitive("CUTG");

    TCutG* cut_Z_AoQ_driftcorr = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z_AoQ_driftcorr == nullptr) {
        std::cout << "No Z vs AoQ_driftcorr gate given. Exiting." << std::endl;
        return false;
    } else {
        cut_Z_AoQ_driftcorr = (TCutG*)cut_Z_AoQ_driftcorr->Clone("cut_Z_AoQ_driftcorr");
        gROOT->FindObject("CUTG")->Delete();

        cut_Z_AoQ_driftcorr->SetVarY("FrsHitData.fID_z_driftcorr");
        cut_Z_AoQ_driftcorr->SetVarX("FrsHitData.fID_AoQ_driftcorr");
        std::cout << "Created gate: " << cut_Z_AoQ_driftcorr->GetName() << std::endl;
        return true;
    }
}

void make_Z_AoQ_driftcorr_gate(TString infilename) {
    TFile* infile = TFile::Open(infilename, "READ");
    if (!infile || !infile->IsOpen()) {
        std::cout << "Failed to open file: " << infilename << std::endl;
        return;
    }

    TTree* evt;
    infile->GetObject("evt", evt);
    if (!evt) {
        std::cout << "Failed to retrieve TTree 'evt' from file." << std::endl;
        infile->Close();
        return;
    }

    TString gatename;
    std::cout << "Please give this gate file a name: ";
    std::cin >> gatename;
    std::cout << std::endl;

    bool success = Gate_Z_AoQ_driftcorr(evt);

    if (success) {
        TFile* outfile = TFile::Open(gatename + ".root", "RECREATE");
        if (outfile && outfile->IsOpen()) {
            gROOT->FindObject("cut_Z_AoQ_driftcorr")->Write();
            outfile->Close();
            std::cout << "Gate saved to file: " << gatename << ".root" << std::endl;
        } else {
            std::cout << "Failed to create output file." << std::endl;
        }
    } else {
        std::cout << "Gate creation failed or was aborted." << std::endl;
    }

    infile->Close();
}


