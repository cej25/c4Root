TCutG* cut_Z21_AoQs1s2 = nullptr;
TCutG* cut_Z41_AoQs2s4 = nullptr;
TCutG* cut_Z21_Z41 = nullptr;
TCutG* cut_x2_AoQs2s4 = nullptr;
TCutG* cut_x4_AoQs2s4 = nullptr;
TCutG* cut_dEdeg_Z = nullptr;
TCutG* cut_sci42E_Z = nullptr;

bool Gate_Z21_AoQs1s2(TTree * evt,  bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41,  bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4,  bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";

    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;

    evt->Draw("FrsMultiHitData.fID_z21_mhtdc:FrsMultiHitData.fID_AoQ_corr_s1s2_mhtdc>>h2_Z21_vs_AoQs1s2(2000,1,4,2000,0,70)", cuts);

    TH2F * h2_Z21_vs_AoQs1s2 = (TH2F*)gROOT->FindObject("h2_Z21_vs_AoQs1s2");

    h2_Z21_vs_AoQs1s2->SetTitle("Draw Z21 vs. AoQ(s1s2) MHTDC gate.");
    h2_Z21_vs_AoQs1s2->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_Z21_AoQs1s2 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z21_AoQs1s2 == nullptr){
        std::cout << "No Z(21) vs AoQ(S1S2) gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_Z21_AoQs1s2 = (TCutG*)cut_Z21_AoQs1s2->Clone("cut_Z21_AoQs1s2");
        gROOT->GetListOfSpecials()->Add(cut_Z21_AoQs1s2);
        gROOT->FindObject("CUTG")->Delete();

        cut_Z21_AoQs1s2->SetVarY("FrsMultiHitData.fID_z21_mhtdc");
        cut_Z21_AoQs1s2->SetVarX("FrsMultiHitData.fID_AoQ_corr_s1s2_mhtdc");
        std::cout << "Created gate: " << cut_Z21_AoQs1s2->GetName() << std::endl;
        return true;
    }
}

bool Gate_Z41_AoQs2s4(TTree * evt, bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41, bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4,  bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";

    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    

    evt->Draw("FrsMultiHitData.fID_z41_mhtdc:FrsMultiHitData.fID_AoQ_corr_s2s4_mhtdc>>h2_Z41_vs_AoQs2s4(2000,1,4,2000,0,70)",cuts);
    
    TH2F * h2_Z41_vs_AoQs2s4 = (TH2F*)gROOT->FindObject("h2_Z41_vs_AoQs2s4");
    
    h2_Z41_vs_AoQs2s4->SetTitle("Draw Z(41) vs. AoQ(S2S4) MHTDC gate.");
    h2_Z41_vs_AoQs2s4->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_Z41_AoQs2s4 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z41_AoQs2s4 == nullptr){
        std::cout << "No Z(41) vs AoQ(S2S4) gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_Z41_AoQs2s4 = (TCutG*)cut_Z41_AoQs2s4->Clone("cut_Z41_AoQs2s4");
        gROOT->GetListOfSpecials()->Add(cut_Z41_AoQs2s4);
        gROOT->FindObject("CUTG")->Delete();

        cut_Z41_AoQs2s4->SetVarY("FrsMultiHitData.fID_z41_mhtdc");
        cut_Z41_AoQs2s4->SetVarX("FrsMultiHitData.fID_AoQ_corr_s2s4_mhtdc");
        //return true;
        std::cout << "Created gate: " << cut_Z41_AoQs2s4->GetName() << std::endl;
        return true;
    }
};

bool Gate_Z21_Z41(TTree * evt, bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41,  bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_z21_mhtdc:FrsMultiHitData.fID_z41_mhtdc>>h2_Z21_vs_Z41(1e3,10,60,1e3,10,60)",cuts);
    
    TH2F * h2_Z21_vs_Z41 = (TH2F*)gROOT->FindObject("h2_Z21_vs_Z41");
    
    h2_Z21_vs_Z41->SetTitle("Draw Z21 vs. Z41 MHTDC gate.");
    h2_Z21_vs_Z41->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_Z21_Z41 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_Z21_Z41 == nullptr){
        std::cout << "No Z21 vs Z41 gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_Z21_Z41 = (TCutG*)cut_Z21_Z41->Clone("cut_Z21_Z41");
        gROOT->GetListOfSpecials()->Add(cut_Z21_Z41);
        gROOT->FindObject("CUTG")->Delete();
        cut_Z21_Z41->SetVarX("FrsMultiHitData.fID_z21_mhtdc");
        cut_Z21_Z41->SetVarY("FrsMultiHitData.fID_z41_mhtdc");
        std::cout << "Created gate: " << cut_Z21_Z41->GetName() << std::endl;
        return true;
    }
}


bool Gate_x2_AoQs2s4(TTree * evt, bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41, bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_x2:FrsMultiHitData.fID_AoQ_corr_s2s4_mhtdc>>h2_x2_vs_AoQs2s4(1000,1.5,3.5,1000,-100,100)",cuts);
    
    TH2F * h2_x2_vs_AoQs2s4 = (TH2F*)gROOT->FindObject("h2_x2_vs_AoQs2s4");
    
    h2_x2_vs_AoQs2s4->SetTitle("Draw x2 vs. AoQ S2S4 (MHTDC) gate.");
    h2_x2_vs_AoQs2s4->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_x2_AoQs2s4 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_x2_AoQs2s4 == nullptr){
        std::cout << "No x2 vs AoQS2S4 gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_x2_AoQs2s4 = (TCutG*)cut_x2_AoQs2s4->Clone("cut_x2_AoQs2s4");
        gROOT->GetListOfSpecials()->Add(cut_x2_AoQs2s4);
        gROOT->FindObject("CUTG")->Delete();
        cut_x2_AoQs2s4->SetVarX("FrsMultiHitData.fID_AoQ_corr_s2s4_mhtdc");
        cut_x2_AoQs2s4->SetVarY("FrsHitData.fID_x2");
        std::cout << "Created gate: " << cut_x2_AoQs2s4->GetName() << std::endl;
        return true;
    }
}

bool Gate_x4_AoQs2s4(TTree * evt, bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41, bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsHitData.fID_x4:FrsMultiHitData.fID_AoQ_corr_s2s4_mhtdc>>h2_x4_vs_AoQs2s4(1000,2.0,3.0,1000,-100,100)",cuts);
    
    TH2F * h2_x4_vs_AoQs2s4 = (TH2F*)gROOT->FindObject("h2_x4_vs_AoQs2s4");
    
    h2_x4_vs_AoQs2s4->SetTitle("Draw x4 vs. AoQ S2S4 (MHTDC) gate.");
    h2_x4_vs_AoQs2s4->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_x4_AoQs2s4 = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_x4_AoQs2s4 == nullptr){
        std::cout << "No x4 vs AoQs2s4 gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_x4_AoQs2s4 = (TCutG*)cut_x4_AoQs2s4->Clone("cut_x4_AoQs2s4");
        gROOT->GetListOfSpecials()->Add(cut_x4_AoQs2s4);
        gROOT->FindObject("CUTG")->Delete();
        cut_x4_AoQs2s4->SetVarX("FrsMultiHitData.fID_AoQ_corr_mhtdc");
        cut_x4_AoQs2s4->SetVarY("FrsHitData.fID_x4");
        std::cout << "Created gate: " << cut_x4_AoQs2s4->GetName() << std::endl;
        return true;
    }
}

bool Gate_dEdeg_Z(TTree * evt, bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41, bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";


    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_dEdeg_z41_mhtdc:FrsMultiHitData.fID_z41_mhtdc>>h2_dEdeg_vs_Z(1000,35,50,1000,0,100)",cuts);
    
    TH2F * h2_dEdeg_vs_Z = (TH2F*)gROOT->FindObject("h2_dEdeg_vs_Z");
    
    h2_dEdeg_vs_Z->SetTitle("Draw dEdeg vs. Z gate MHTDC.");
    h2_dEdeg_vs_Z->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_dEdeg_Z = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_dEdeg_Z == nullptr){
        std::cout << "No dEdeg vs Z41 gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_dEdeg_Z = (TCutG*)cut_dEdeg_Z->Clone("cut_dEdeg_Z");
        gROOT->GetListOfSpecials()->Add(cut_dEdeg_Z);
        gROOT->FindObject("CUTG")->Delete();
        cut_dEdeg_Z->SetVarX("FrsMultiHitData.fID_z41_mhtdc");
        cut_dEdeg_Z->SetVarY("FrsMultiHitData.fID_dEdeg_z41_mhtdc");
        std::cout << "Created gate: " << cut_dEdeg_Z->GetName() << std::endl;
        return true;
    }
}

bool Gate_sci42E_Z(TTree * evt, bool bool_Z21_AoQs1s2, bool bool_Z41_AoQs2s4, bool  bool_Z21_Z41, bool  bool_x2_AoQs2s4, bool  bool_x4_AoQs2s4, bool bool_dEdeg_Z, bool bool_sci42E_Z){
    
    TString cuts;

    if (bool_Z21_AoQs1s2) cuts = cuts + "cut_Z21_AoQs1s2 && ";
    if (bool_Z41_AoQs2s4) cuts = cuts + "cut_Z41_AoQs2s4 && ";
    if (bool_Z21_Z41) cuts = cuts + "cut_Z21_Z41 && ";
    if (bool_x2_AoQs2s4) cuts = cuts + "cut_x2_AoQs2s4 && ";
    if (bool_x4_AoQs2s4) cuts = cuts + "cut_x4_AoQs2s4 && ";
    if (bool_dEdeg_Z) cuts = cuts + "cut_dEdeg_Z && ";
    if (bool_sci42E_Z) cuts = cuts + "cut_sci42E_Z && ";
    

    if (cuts.EndsWith(" && ")) cuts = cuts(0,cuts.Length()-4);
    std::cout << "Drawing with the condition: " << cuts << std::endl;
    
    
    evt->Draw("FrsMultiHitData.fID_z42_mhtdc:FrsHitData.fsci_e_42>>h2_sci42E_Z(1000,0,2500,1000,60,70)",cuts);
    
    TH2F * h2_sci42E_Z = (TH2F*)gROOT->FindObject("h2_sci42E_Z");
    
    h2_sci42E_Z->SetTitle("Draw sci42E vs. Z(MHTDC) gate.");
    h2_sci42E_Z->Draw("COLZ");
    gPad->WaitPrimitive("CUTG");
    TCutG * cut_sci42E_Z = (TCutG*)gROOT->FindObject("CUTG");
    if (cut_sci42E_Z == nullptr){
        std::cout << "No Sci42E vs Z42 gate given. Continuing." << std::endl;
        return false;
    }else{
        cut_sci42E_Z = (TCutG*)cut_sci42E_Z->Clone("cut_sci42E_Z");
        gROOT->GetListOfSpecials()->Add(cut_sci42E_Z);
        gROOT->FindObject("CUTG")->Delete();
        cut_sci42E_Z->SetVarY("FrsMultiHitData.fID_z42");
        cut_sci42E_Z->SetVarX("FrsHitData.fsci_e_42");
        std::cout << "Created gate: " << cut_sci42E_Z->GetName() << std::endl;
        return true;
    }
}


void make_frs_gates_seq_mhtdc_lisa(TString infilename){

    TFile * infile = TFile::Open(infilename,"READ");

    if (!infile->IsOpen())
    {
        std::cout << "Failed on file open." << std::endl;
        return;
    }

    TTree * evt;
    infile->GetObject("evt",evt);

    bool bool_Z21_AoQs1s2 = false;
    bool bool_Z41_AoQs2s4 = false;
    bool bool_Z21_Z41 = false;
    bool bool_x2_AoQs2s4 = false;
    bool bool_x4_AoQs2s4 = false;
    bool bool_dEdeg_Z = false;
    bool bool_sci42E_Z = false;
    
    TString gatename;
    std::cout << "Please give this set of gates a name: "; 
    std::cin >> gatename;
    std::cout << std::endl;

    bool making_gates = true;
    while (making_gates){
        int gate;
        std::cout << "Please choose parameters to gate - (1) Z(11) vs AoQ(S1S2), (2) Z(41) vs AoQ(S2S4), (3) Z21 vs Z41, (4) x2 vs AoQs2s4, (5) x4 vs AoQs2s4, (6) dEdeg vs Z ,(7) sci42 E vs Z :" << std::endl;

        std::cin >> gate;

        switch (gate){
            case 1:
                bool_Z21_AoQs1s2 = Gate_Z21_AoQs1s2(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 2:
                bool_Z41_AoQs2s4 = Gate_Z41_AoQs2s4(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 3:
                bool_Z21_Z41 = Gate_Z21_Z41(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 4:
                bool_x2_AoQs2s4 = Gate_x2_AoQs2s4(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 5:
                bool_x4_AoQs2s4 = Gate_x4_AoQs2s4(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 6:
                bool_dEdeg_Z = Gate_dEdeg_Z(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;
            case 7:
                bool_sci42E_Z = Gate_sci42E_Z(evt, bool_Z21_AoQs1s2, bool_Z41_AoQs2s4, bool_Z21_Z41, bool_x2_AoQs2s4, bool_x4_AoQs2s4, bool_dEdeg_Z, bool_sci42E_Z);
            break;


            default:
                std::cout << "Unrecognized option, exiting" << std::endl;
                making_gates = false;
            break;

        }
    }


    TFile * outfile =  TFile::Open(gatename + ".root","RECREATE");

    if (bool_Z21_AoQs1s2) gROOT->FindObject("cut_Z21_AoQs1s2")->Write();
    if (bool_Z41_AoQs2s4) gROOT->FindObject("cut_Z41_AoQs2s4")->Write();
    if (bool_Z21_Z41) gROOT->FindObject("cut_Z21_Z41")->Write();
    if (bool_x2_AoQs2s4) gROOT->FindObject("cut_x2_AoQs2s4")->Write();
    if (bool_x4_AoQs2s4) gROOT->FindObject("cut_x4_AoQs2s4")->Write();
    if (bool_dEdeg_Z)gROOT->FindObject("cut_dEdeg_Z")->Write();
    if (bool_sci42E_Z)gROOT->FindObject("cut_sci42E_Z")->Write();
    
    outfile->Close();
    
};

