void find_timeshi2fts(){


    TFile* infile = TFile::Open("60Calib.root");

    TDirectory* DEGAS = (TDirectory*)infile->Get("DEGAS");
    TDirectory* efol = (TDirectory*)DEGAS->Get("time_differences_rel_1_0_energy_gate_1173_1332");


    std::vector<int> dets = {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9,10,10,10,11,11,11,12,12,12};
    std::vector<int> crys = {0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2};

    int ndets = dets.size();

    TH1F * h_time;

    TF1 * g = new TF1("g","gaus",-100,100);
    for (int i = 0; i<ndets; i++){
        h_time = (TH1F*)efol->Get(Form("h1_germanium_rel_time_det_%i_%i_to_det_1_0_energy_gate_1173_1332",dets.at(i),crys.at(i)));

        //std::cout << "Counts: " << h_time->GetEntries() << std::endl;
        if (h_time->GetEntries() == 0){
            std::cout << dets.at(i) << " " << crys.at(i) << " " << 0.0 << std::endl;
            continue;
        }
        h_time->Fit(g,"QR");
        std::cout << dets.at(i) << " " << crys.at(i) << " " << g->GetParameter(1) << std::endl;
        

    }


}
void find_timeshifts(){


    TFile* infile = TFile::Open("152Eu_0044_summed.root");

    TDirectory* FATIMA = (TDirectory*)infile->Get("FATIMA");
    TDirectory* efol = (TDirectory*)FATIMA->Get("time_differences_rel_1_energy_gate_344_778");


    std::vector<int> dets = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};

    int ndets = dets.size();
    int dt_low_limit = -60;
    int dt_high_limit = 60;

    TH1F * h_time;

    for (int i = 0; i<ndets; i++){
        h_time = (TH1F*)efol->Get(Form("h1_fatima_rel_time_det_1_to_det_%i_energy_gate_344_778",dets.at(i)));

        //std::cout << "Counts: " << h_time->GetEntries() << std::endl;
        if (h_time->GetEntries() == 0){
            std::cout << dets.at(i) << " " << 0.0 << std::endl;
            continue;
        }
        h_time->Draw();
        //gPad->WaitPrimitive();
        double delayed_integral_err;
        double delayed_integral = h_time->IntegralAndError(h_time->FindBin(dt_low_limit),h_time->FindBin(dt_high_limit),delayed_integral_err);
        TF1 * f = new TF1("f","x",-100,100);
        
        h_time->Multiply(f);

        double delayed_wintegral_err;
        double delayed_wintegral = h_time->IntegralAndError(h_time->FindBin(dt_low_limit),h_time->FindBin(dt_high_limit),delayed_wintegral_err);


        std::cout << dets.at(i) << " " << delayed_wintegral/delayed_integral << std::endl;


        double Cdelayed = delayed_wintegral / delayed_integral ;

        

    }


}