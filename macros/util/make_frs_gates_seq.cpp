
bool Gate_Z_AoQ(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";

    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    

    evt->Draw("FrsHitData.fID_z:FrsHitData.fID_AoQ>>h2_Z_vs_AoQ(2000,1.0,4.0,2000,20,100)",cuts);
    
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

        cut_Z_AoQ->SetVarY("FrsHitData.fID_z");
        cut_Z_AoQ->SetVarX("FrsHitData.fID_AoQ_corr");
        std::cout << "Created gate: " << cut_Z_AoQ->GetName() << std::endl;
        return true;
    }
};

bool Gate_Z_Z2(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_z:FrsHitData.fID_z2>>h2_Z_vs_Z2(1000,60,70,1000,60,70)",cuts);
    
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
        cut_Z_Z2->SetVarY("FrsHitData.fID_z");
        cut_Z_Z2->SetVarX("FrsHitData.fID_z2");
        std::cout << "Created gate: " << cut_Z_Z2->GetName() << std::endl;
        return true;
    }
}


bool Gate_x2_AoQ(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_x2:FrsHitData.fID_AoQ_corr>>h2_x2_vs_AoQ(1000,2.3,2.8,1000,-100,100)",cuts);
    
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
        cut_x2_AoQ->SetVarX("FrsHitData.fID_AoQ_corr");
        cut_x2_AoQ->SetVarY("FrsHitData.fID_x2");
        std::cout << "Created gate: " << cut_x2_AoQ->GetName() << std::endl;
        return true;
    }
}

bool Gate_x4_AoQ(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_x4:FrsHitData.fID_AoQ_corr>>h2_x4_vs_AoQ(1000,2.3,2.8,1000,-100,100)",cuts);
    
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
        cut_x4_AoQ->SetVarX("FrsHitData.fID_AoQ_corr");
        cut_x4_AoQ->SetVarY("FrsHitData.fID_x4");
        std::cout << "Created gate: " << cut_x4_AoQ->GetName() << std::endl;
        return true;
    }
}

bool Gate_dEdeg_Z(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_z:FrsHitData.fID_dEdeg>>h2_dEdeg_vs_Z(1000,30,52,1000,60,70)",cuts);
    
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
        cut_dEdeg_Z->SetVarY("FrsHitData.fID_z");
        cut_dEdeg_Z->SetVarX("FrsHitData.fID_dEdeg");
        std::cout << "Created gate: " << cut_dEdeg_Z->GetName() << std::endl;
        return true;
    }
}

bool Gate_sci42E_Z(TTree * evt, bool bool_Z_AoQ, bool  bool_Z_Z2, bool  bool_x2_AoQ, bool  bool_x4_AoQ, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z_AoQ) cuts = cuts + "cut_Z_AoQ && ";
    if (bool_Z_Z2) cuts = cuts + "cut_Z_Z2 && ";
    if (bool_x2_AoQ) cuts = cuts + "cut_x2_AoQ && ";
    if (bool_x4_AoQ) cuts = cuts + "cut_x4_AoQ && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_z:FrsHitData.fsci_e_42>>h2_sci42E_Z(1000,0,2500,1000,60,70)",cuts);
    
    TH2F * h2_sci42E_Z = (TH2F*)gROOT->FindObject("h2_sci42E_Z");
    
    h2_sci42E_Z->SetTitle("Draw sci42E vs. Z gate.");
    h2_sci42E_Z->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_sci42E_Z = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_sci42E_Z == nullptr){
        std::cout << "No Z vs AoQ gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_sci42E_Z = (TCutG*)cut_sci42E_Z->Clone("cut_sci42E_Z");
        gROOT->FindObject("CUTG")->Delete();
        cut_sci42E_Z->SetVarY("FrsHitData.fID_z");
        cut_sci42E_Z->SetVarX("FrsHitData.fsci_e_42");
        std::cout << "Created gate: " << cut_sci42E_Z->GetName() << std::endl;
        return true;
    }
}


void make_frs_gates_seq(TString infilename){

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
    bool bool_sci42E_Z = false;


    TString gatename;
    std::cout << "Please give this set of gates a name: "; 
    std::cin >> gatename;
    std::cout << std::endl;

    bool making_gates = true;
    while (making_gates){
        int gate;
        std::cout << "Please choose parameters to gate - (1) AoQ vs Z, (2) Z1 vs Z2, (3) x2 vs AoQ, (4) x4 vs AoQ or (5) dEdeg vs Z or (6) sci42 E vs Z:" << std::endl << ">>>";
        std::cin >> gate;

        switch (gate){
            case 1:
                bool_Z_AoQ = Gate_Z_AoQ(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 2:
                bool_Z_Z2 = Gate_Z_Z2(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 3:
                bool_x2_AoQ = Gate_x2_AoQ(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 4:
                bool_x4_AoQ = Gate_x4_AoQ(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 5:
                bool_dEdeg_Z = Gate_dEdeg_Z(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 6:
                bool_sci42E_Z = Gate_sci42E_Z(evt, bool_Z_AoQ, bool_Z_Z2, bool_x2_AoQ, bool_x4_AoQ, bool_dEdeg_Z, bool_sci42E_Z);
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
    if (bool_sci42E_Z)gROOT->FindObject("cut_sci42E_Z")->Write();
    
    outfile->Close();
    
};

