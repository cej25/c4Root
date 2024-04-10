void make_frs_gates(TString infilename){

    TFile * infile = TFile::Open(infilename,"READ");

    if (!infile->IsOpen()){
        std::cout << "Failed on file open." << std::endl;
        return;
    }


    TFolder * fol = (TFolder*)infile->Get("FRS Analysis Histograms");
    TFolder* fol2 = (TFolder*)fol->FindObject("TAC");


    TCutG* cut_Z_AoQ;
    TCutG* cut_Z_Z2;
    TCutG* cut_x2_AoQ;
    TCutG* cut_x4_AoQ;
    TCutG* cut_dEdeg_Z;
    
    TH2F* h2_Z_vs_AoQ;
    TH2F* h2_Z_vs_Z2;
    TH2F* h2_x2_vs_AoQ;
    TH2F* h2_x4_vs_AoQ;
    TH2F* h2_dEdeg_vs_Z;


    h2_Z_vs_AoQ = (TH2F*)fol2->FindObject("h2_Z_vs_AoQ");
    h2_Z_vs_Z2 = (TH2F*)fol2->FindObject("h2_Z_vs_Z2");
    h2_x2_vs_AoQ = (TH2F*)fol2->FindObject("h2_x2_vs_AoQ");
    h2_x4_vs_AoQ = (TH2F*)fol2->FindObject("h2_x4_vs_AoQ");
    h2_dEdeg_vs_Z = (TH2F*)fol2->FindObject("h2_dEdeg_vs_Z");


    TString gatename;
    std::cout << "Please give this set of gates a name: "; 
    std::cin >> gatename;
    std::cout << std::endl;

    h2_Z_vs_AoQ->SetTitle("Draw Z vs. AoQ gate.");
    h2_Z_vs_AoQ->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    cut_Z_AoQ = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z_AoQ == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
    }else{
        cut_Z_AoQ = (TCutG*)cut_Z_AoQ->Clone("cut_Z_AoQ");
        gROOT->FindObject("CUTG")->Delete();

    }


    h2_Z_vs_Z2->SetTitle("Draw Z1 vs. Z2 gate.");
    h2_Z_vs_Z2->Draw("COLZ");
    gPad->Update();
    gPad->WaitPrimitive("CUTG");
    cut_Z_Z2 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z_Z2 == nullptr){
        std::cout << "No Z1 vs Z2 gate given. Continuing." << std::endl;
    }else{
        cut_Z_Z2 = (TCutG*)cut_Z_Z2->Clone("cut_Z_Z2");
        gROOT->FindObject("CUTG")->Delete();
    }

    h2_x2_vs_AoQ->SetTitle("Draw x2 vs. AoQ gate.");
    h2_x2_vs_AoQ->Draw("COLZ");
    gPad->Update();
    gPad->WaitPrimitive("CUTG");
    cut_x2_AoQ = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_x2_AoQ == nullptr){
        std::cout << "No x2 vs AoQ gate given. Continuing." << std::endl;
    }else{
        cut_x2_AoQ = (TCutG*)cut_x2_AoQ->Clone("cut_x2_AoQ");
        gROOT->FindObject("CUTG")->Delete();
    }


    h2_x4_vs_AoQ->SetTitle("Draw x4 vs. AoQ gate.");
    h2_x4_vs_AoQ->Draw("COLZ");
    gPad->Update();
    gPad->WaitPrimitive("CUTG");
    cut_x4_AoQ = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_x4_AoQ == nullptr){
        std::cout << "No x4 vs AoQ gate given. Continuing." << std::endl;
    }else{
        cut_x4_AoQ = (TCutG*)cut_x4_AoQ->Clone("cut_x4_AoQ");
        gROOT->FindObject("CUTG")->Delete();
    }



    h2_dEdeg_vs_Z->SetTitle("Draw dEdeg vs. Z gate.");
    h2_dEdeg_vs_Z->Draw("COLZ");
    gPad->Update();
    gPad->WaitPrimitive("CUTG");
    cut_dEdeg_Z = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_dEdeg_Z == nullptr){
        std::cout << "No dEdeg vs Z gate given. Continuing." << std::endl;
    }else{
        cut_dEdeg_Z = (TCutG*)cut_dEdeg_Z->Clone("cut_dEdeg_Z");
        gROOT->FindObject("CUTG")->Delete();
    }








    TFile * outfile =  TFile::Open(gatename+".root","RECREATE");

    if (cut_Z_AoQ != nullptr) cut_Z_AoQ->Write();
    if (cut_Z_Z2 != nullptr) cut_Z_Z2->Write();
    if (cut_x2_AoQ != nullptr) cut_x2_AoQ->Write();
    if (cut_x4_AoQ != nullptr) cut_x4_AoQ->Write();
    if (cut_dEdeg_Z != nullptr) cut_dEdeg_Z->Write();
    
    outfile->Close();
    
}