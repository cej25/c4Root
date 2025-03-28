
bool Gate_Z_AoQ(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z){
    
    TString cuts;

    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";

    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    

    evt->Draw("FrsMultiHitData.fID_z_mhtdc:FrsMultiHitData.fID_AoQ_corr_mhtdc>>h2_Z_vs_AoQ(1000,2.4,2.8,1000,60,70)",cuts);
    
    TH2F * h2_Z_vs_AoQ = (TH2F*)gROOT->FindObject("h2_Z_vs_AoQ");
    
    h2_Z_vs_AoQ->SetTitle("Draw Z vs. AoQ gate.");
    h2_Z_vs_AoQ->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_Z_AoQ = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z_AoQ == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_Z_AoQ = (TCutG*)cut_Z_AoQ->Clone("cut_Z_AoQ");
        gROOT->FindObject("CUTG")->Delete();

        cut_Z_AoQ->SetVarY("FrsMultiHitData.fID_z_mhtdc");
        cut_Z_AoQ->SetVarX("FrsMultiHitData.fID_AoQ_corr_mhtdc");
        std::cout << "Created gate: " << cut_Z_AoQ->GetName() << std::endl;
        return true;
    }
};

bool Gate_Z_Z2(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_z_mhtdc:FrsMultiHitData.fID_z2_mhtdc>>h2_Z_vs_Z2(1000,60,70,1000,60,70)",cuts);
    
    TH2F * h2_Z_vs_Z2 = (TH2F*)gROOT->FindObject("h2_Z_vs_Z2");
    
    h2_Z_vs_Z2->SetTitle("Draw Z1 vs. Z2 gate.");
    h2_Z_vs_Z2->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_Z_Z2 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z_Z2 == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_Z_Z2 = (TCutG*)cut_Z_Z2->Clone("cut_Z_Z2");
        gROOT->FindObject("CUTG")->Delete();
        cut_Z_Z2->SetVarY("FrsMultiHitData.fID_z_mhtdc");
        cut_Z_Z2->SetVarX("FrsMultiHitData.fID_z2_mhtdc");
        std::cout << "Created gate: " << cut_Z_Z2->GetName() << std::endl;
        return true;
    }
}


bool Gate_x2_AoQ(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_s2x_mhtdc:FrsMultiHitData.fID_AoQ_corr_mhtdc>>h2_x2_vs_AoQ(1000,2.4,2.8,1000,-100,100)",cuts);
    
    TH2F * h2_x2_vs_AoQ = (TH2F*)gROOT->FindObject("h2_x2_vs_AoQ");
    
    h2_x2_vs_AoQ->SetTitle("Draw x2 vs. AoQ gate.");
    h2_x2_vs_AoQ->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_x2_AoQ = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_x2_AoQ == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_x2_AoQ = (TCutG*)cut_x2_AoQ->Clone("cut_x2_AoQ");
        gROOT->FindObject("CUTG")->Delete();
        cut_x2_AoQ->SetVarX("FrsMultiHitData.fID_AoQ_corr_mhtdc");
        cut_x2_AoQ->SetVarY("FrsMultiHitData.fID_s2x_mhtdc");
        std::cout << "Created gate: " << cut_x2_AoQ->GetName() << std::endl;
        return true;
    }
}

bool Gate_x4_AoQ(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_s4x_mhtdc:FrsMultiHitData.fID_AoQ_corr_mhtdc>>h2_x4_vs_AoQ(1000,2.4,2.8,1000,-100,100)",cuts);
    
    TH2F * h2_x4_vs_AoQ = (TH2F*)gROOT->FindObject("h2_x4_vs_AoQ");
    
    h2_x4_vs_AoQ->SetTitle("Draw x4 vs. AoQ gate.");
    h2_x4_vs_AoQ->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_x4_AoQ = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_x4_AoQ == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_x4_AoQ = (TCutG*)cut_x4_AoQ->Clone("cut_x4_AoQ");
        gROOT->FindObject("CUTG")->Delete();
        cut_x4_AoQ->SetVarX("FrsMultiHitData.fID_AoQ_corr_mhtdc");
        cut_x4_AoQ->SetVarY("FrsMultiHitData.fID_s4x_mhtdc");
        std::cout << "Created gate: " << cut_x4_AoQ->GetName() << std::endl;
        return true;
    }
}

bool Gate_dEdeg_Z(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_z_mhtdc:FrsMultiHitData.fID_dEdeg_mhtdc>>h2_dEdeg_vs_Z(1000,35,52,1000,60,70)",cuts);
    
    TH2F * h2_dEdeg_vs_Z = (TH2F*)gROOT->FindObject("h2_dEdeg_vs_Z");
    
    h2_dEdeg_vs_Z->SetTitle("Draw dEdeg vs. Z gate.");
    h2_dEdeg_vs_Z->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_dEdeg_Z = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_dEdeg_Z == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_dEdeg_Z = (TCutG*)cut_dEdeg_Z->Clone("cut_dEdeg_Z");
        gROOT->FindObject("CUTG")->Delete();
        cut_dEdeg_Z->SetVarY("FrsMultiHitData.fID_z_mhtdc");
        cut_dEdeg_Z->SetVarX("FrsMultiHitData.fID_dEdeg_mhtdc");
        std::cout << "Created gate: " << cut_dEdeg_Z->GetName() << std::endl;
        return true;
    }
}


void make_frs_gates_seq_multi(TString infilename){

    TFile * infile = TFile::Open(infilename,"READ");

    if (!infile->IsOpen()){
        std::cout << "Failed on file open." << std::endl;
        return;
    }

    TTree * evt;
    infile->GetObject("evt",evt);

    bool bool_Z_AoQ = false;
    bool bool_Z_Z2 = false;
    bool bool_x2_AoQ = false;
    bool bool_x4_AoQ = false;
    bool bool_dEdeg_Z = false;



    TString gatename;
    std::cout << "Please give this set of gates a name: "; 
    std::cin >> gatename;
    std::cout << std::endl;

    bool making_gates = true;
    while (making_gates){
        int gate;
        std::cout << "Please choose parameters to gate - (1) AoQ vs Z, (2) Z1 vs Z2, (3) x2 vs AoQ, (4) x4 vs AoQ or (5) dEdeg vs Z:" << std::endl << ">>>";
        std::cin >> gate;

        switch (gate){
            case 1:
                bool_Z_AoQ = Gate_Z_AoQ(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z);
            break;
            case 2:
                bool_Z_Z2 = Gate_Z_Z2(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z);
            break;
            case 3:
                bool_x2_AoQ = Gate_x2_AoQ(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z);
            break;
            case 4:
                bool_x4_AoQ = Gate_x4_AoQ(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z);
            break;
            case 5:
                bool_dEdeg_Z = Gate_dEdeg_Z(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z);
            break;

            default:
                std::cout << "Unrecognized option, exiting" << std::endl;
                making_gates = false;
            break;

        }
    }


    TFile * outfile =  TFile::Open(gatename + ".root","RECREATE");

    if (bool_Z_AoQ) gROOT->FindObject("cut_Z_AoQ")->Write();
    if (bool_Z_Z2) gROOT->FindObject("cut_Z_Z2")->Write();
    if (bool_x2_AoQ) gROOT->FindObject("cut_x2_AoQ")->Write();
    if (bool_x4_AoQ) gROOT->FindObject("cut_x4_AoQ")->Write();
    if (bool_dEdeg_Z)gROOT->FindObject("cut_dEdeg_Z")->Write();
    
    outfile->Close();
    
};

