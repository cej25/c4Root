#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "LisaFrsCorrelationsOnline.h"
#include "FrsHitData.h"
#include "FrsTravMusCalData.h"
#include "LisaCalData.h"
#include "TLisaConfiguration.h" // not here
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

LisaFrsCorrelationsOnline::LisaFrsCorrelationsOnline() 
    : LisaFrsCorrelationsOnline("LisaFrsCorrelationsOnline")
{

}

LisaFrsCorrelationsOnline::LisaFrsCorrelationsOnline(std::vector<FrsGate*> fg)
    : LisaFrsCorrelationsOnline("LisaFrsCorrelationsOnline")
{

}

LisaFrsCorrelationsOnline::LisaFrsCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   lisaCalArray(nullptr)
    ,   travMusicArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
}

LisaFrsCorrelationsOnline::~LisaFrsCorrelationsOnline()
{
    c4LOG(info, "Destroyed LisaFrsCorrelationsOnlineProperly.");
}

InitStatus LisaFrsCorrelationsOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");
    
    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");
    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");
    travMusicArray = mgr->InitObjectAs<decltype(travMusicArray)>("FrsTravMusCalData");
    c4LOG_IF(fatal, !travMusicArray, "Branch FrsTravMusCalData not found!");

    layer_number = lisa_config->NLayers();

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_corr = (TDirectory*)mgr->GetObject("Correlations");
    if (dir_corr == nullptr) 
    {   
        c4LOG(info, "Creating Correlations Directory");
        dir_corr = new TDirectory("Correlations", "Correlations", "", 0);
        mgr->Register("Correlations", "Correlations Directory", dir_corr, false); // allow other tasks to find this
        histograms->Add(dir_corr);
    }

    dir_lisa_frs = dir_corr->mkdir("LISA-FRS Correlations");
    
    dir_lisa_frs->cd();
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::::::: WR Time differences ::::::::::::::::::::::
    c_wr_diff = new TCanvas("c_wr_diff", "WR Time Differences", 650, 350);
    c_wr_diff->Divide(3);
    h1_wr_diff.resize(3);

    c_wr_diff->cd(1);
    h1_wr_diff[0] = new TH1I(" WR Difference LISA - FRS ", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    //h1_wr_diff[0]->SetStats(0);
    h1_wr_diff[0]->Draw();
    h1_wr_diff[0]->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");

    c_wr_diff->cd(2);
    h1_wr_diff[1] = new TH1I(" WR Difference LISA - TravMUSIC ", " WR Difference LISA - TravMUSIC ", 6000, -3000, 3000);
    //h1_wr_diff[1]->SetStats(0);
    h1_wr_diff[1]->Draw();
    h1_wr_diff[1]->GetXaxis()->SetTitle("WR(LISA) - WR (travMUSIC)");

    c_wr_diff->cd(3);
    h1_wr_diff[2] = new TH1I(" WR Difference TravMUSIC - FRS ", " WR Difference TravMUSIC - FRS ", 6000, -3000, 3000);
    //h1_wr_diff[2]->SetStats(0);
    h1_wr_diff[2]->Draw();
    h1_wr_diff[2]->GetXaxis()->SetTitle("WR (travMUSIC) - WR (FRS)");

    c_wr_diff->cd();
    dir_lisa_frs->Append(c_wr_diff);

    //FRS position vs LISA position
    //::::::::::::: Layer 1 ::::::::::::::::::
    c_xy_pos_layer1 = new TCanvas("c_xy_position_layer_1", "FRS vs LISA Position Layer 1", 650, 350);
    c_xy_pos_layer1->Divide(2);
    h2_xy_pos_layer1.resize(2);
    for (int i = 0; i < 2; i++)
    {
        c_xy_pos_layer1->cd(i+1);
        h2_xy_pos_layer1[i] = new TH2F(Form("FRS_vs_LISA_Position_%i_Layer_1",i), Form("FRS vs LISA Position %i Layer 1",i), 2, 0, 2, 400,-50,50);//change lisa range from macro - sim to sum energy for our online
        h2_xy_pos_layer1[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 1",i));
        h2_xy_pos_layer1[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
        //h2_xy_position[i]->SetStats(0);
        h2_xy_pos_layer1[i]->Draw("colz");
    }
    c_xy_pos_layer1->cd(0);
    dir_lisa_frs->Append(c_xy_pos_layer1);   

    //FRS position vs LISA position
    //::::::::::::: Layer 2 ::::::::::::::::::
    c_xy_pos_layer2 = new TCanvas("c_xy_position_layer_2", "FRS vs LISA Position Layer 2", 650, 350);
    c_xy_pos_layer2->Divide(2);
    h2_xy_pos_layer2.resize(2);
    for (int i = 0; i < 2; i++)
    {
        c_xy_pos_layer2->cd(i+1);
        h2_xy_pos_layer2[i] = new TH2F(Form("FRS_vs_LISA_Position_%i_Layer_2",i), Form("FRS vs LISA Position %i Layer 2",i), 2, 0, 2, 300,-100,100);//change lisa range from macro - sim to sum energy for our online
        h2_xy_pos_layer2[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 2",i));
        h2_xy_pos_layer2[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
        //h2_xy_position[i]->SetStats(0);
        h2_xy_pos_layer2[i]->Draw("colz");
    }
    c_xy_pos_layer2->cd(0);

    dir_lisa_frs->Append(c_xy_pos_layer2);   

    //MUSIC1 - LISA
    //:::::::::::::::::::::::::::::::
    c_MUSIC_1_layer = new TCanvas("c_MUSIC_1_layer", "MUSIC(1) vs E(LISA) per Layer", 650, 350);
    c_MUSIC_1_layer->Divide(3);
    h2_MUSIC_1_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_1_layer->cd(i+1);
        h2_MUSIC_1_layer[i] = new TH2F(Form("MUSIC(1) vs E(LISA) Layer %i",i), Form("MUSIC(1) vs E(LISA) Layer %i",i), 2000, 1000, 3510000, 400,0,4096);//change lisa range from macro - sim to sum energy for our online
        h2_MUSIC_1_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) - Layer %i",i));
        h2_MUSIC_1_layer[i]->GetYaxis()->SetTitle("dE MUSIC(1)");
        //h2_MUSIC_1_layer[i]->SetStats(0);
        h2_MUSIC_1_layer[i]->Draw("colz");
    }
    c_MUSIC_1_layer->cd(0);
    dir_lisa_frs->Append(c_MUSIC_1_layer);

    //MUSIC 2 VS LISA
    //:::::::::::::::::::::::::::::::
    c_MUSIC_2_layer = new TCanvas("c_MUSIC_2_layer", "MUSIC(1) vs E(LISA) per Layer", 650, 350);
    c_MUSIC_2_layer->Divide(3);
    h2_MUSIC_2_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_2_layer->cd(i+1);
        h2_MUSIC_2_layer[i] = new TH2F(Form("MUSIC(2) vs E(LISA) Layer %i",i), Form("MUSIC(2) vs E(LISA) Layer %i",i), 2000, 1000, 3510000, 400,0,4096);//change lisa range from macro - sim to sum energy for our online
        h2_MUSIC_2_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) - Layer %i",i));
        h2_MUSIC_2_layer[i]->GetYaxis()->SetTitle("dE MUSIC(2)");
        //h2_MUSIC_2_layer[i]->SetStats(0);
        h2_MUSIC_2_layer[i]->Draw("colz");
    }
    c_MUSIC_2_layer->cd(0);
    dir_lisa_frs->Append(c_MUSIC_2_layer);

    //travMUSIC VS LISA
    c_travMUSIC_layer = new TCanvas("c_travMUSIC_layer", "travMUSIC vs E(LISA) per Layer", 650, 350);
    c_travMUSIC_layer->Divide(3);
    h2_travMUSIC_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_travMUSIC_layer->cd(i+1);
        h2_travMUSIC_layer[i] = new TH2F(Form("travMUSIC vs E(LISA) Layer %i",i), Form("travMUSIC vs E(LISA) Layer %i",i), 2000, 1000, 3510000, 400,0,4096);//change lisa range from macro - sim to sum energy for our online
        h2_travMUSIC_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) - Layer %i",i));
        h2_travMUSIC_layer[i]->GetYaxis()->SetTitle("dE travMUSIC");
        //h2_travMUSIC_layer[i]->SetStats(0);
        h2_travMUSIC_layer[i]->Draw("colz");
    }
    c_travMUSIC_layer->cd(0);
    dir_lisa_frs->Append(c_travMUSIC_layer);
 

    run->GetHttpServer()->RegisterCommand("Reset_LisaFRS_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    return kSUCCESS;

}


void LisaFrsCorrelationsOnline::Reset_Histo()
{
    c4LOG(info, "");
}


void LisaFrsCorrelationsOnline::Exec(Option_t* option)
{   
    // reject events without both subsystems
    if (lisaCalArray->size() <= 0 || frsHitArray->size() <= 0) return; //frs and trav music are there
    //if (lisaCalArray->size() <= 0 ) return; //for when travmusic is there but not frs

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event
    const auto & travMusicHitItem = travMusicArray->at(0); 

    // FRS WR
    Int_t count_wr = 0;

    //wr_travMUSIC = frsHitItem.Get_wr_travmus();
    wr_FRS = frsHitItem.Get_wr_t();
    wr_travMUSIC = travMusicHitItem.Get_wr_t();

    //S2 Position x-y
    s2_x = frsHitItem.Get_ID_x2();
    s2_y = frsHitItem.Get_ID_y2();
    //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    // Energy from frs
    std::vector<uint32_t> sum_energy_layer;
    sum_energy_layer.resize(layer_number);
    //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    energy_MUSIC_1 = frsHitItem.Get_music_dE(0); 
    energy_MUSIC_2 = frsHitItem.Get_music_dE(1);
    energy_travMUSIC = frsHitItem.Get_travmusic_dE();
    //energy_travMUSIC = travMusHitItem.Get_travmusic_dE();
    //c4LOG(info, "travMUS en : " << energy_travMUSIC << " music 1 : " << energy_MUSIC_1 << " sum energy 1 : " << sum_energy_layer[1]);


    // correlation with main FRS (10, 20, 30, 15)
    for (const auto & lisaCalItem : *lisaCalArray)
    {        
        //::::::: Retrieve Data ::::::::::::::

        //:::: White Rabbit
        if (count_wr == 0)
        {
            wr_LISA = lisaCalItem.Get_wr_t();
        }
        count_wr++;
        if (wr_LISA == 0)return;

        //::::Position
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();

        //:::::::::::::: FRS - LISA position ::::::::::::::::::::::::::
        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
        
        if (layer == 1)
        {
        h2_xy_pos_layer1[0]->Fill(xpos,s2_x);
        h2_xy_pos_layer1[1]->Fill(ypos,s2_y);
        }

        if (layer == 2)
        {
        h2_xy_pos_layer2[0]->Fill(xpos,s2_x);
        h2_xy_pos_layer2[1]->Fill(ypos,s2_y);
        }
        

        //:::: Energies
        uint32_t energy_LISA = lisaCalItem.Get_energy();
        layer = lisaCalItem.Get_layer_id();
        sum_energy_layer[layer] += energy_LISA;

    }
    
    //:::::::::::::: WR Time differences ::::::::::::::::::::::::::
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    wr_LISA_FRS = wr_LISA - wr_FRS;
    wr_LISA_travMUSIC = wr_LISA - wr_travMUSIC;
    wr_travMUSIC_FRS = wr_travMUSIC - wr_FRS;

    h1_wr_diff[2]->Fill(wr_travMUSIC_FRS);

    
    //c4LOG(info, "travMUS en : " << energy_travMUSIC << " music 1 : " << energy_MUSIC_1 << " sum energy 1 : " << sum_energy_layer[1]);
    if(wr_travMUSIC == 0) return;
    h1_wr_diff[1]->Fill(wr_LISA_travMUSIC);

    if (wr_FRS != 0 && wr_LISA != 0) h1_wr_diff[0]->Fill(wr_LISA_FRS);


    //:::::::::::::: ENERGY correlation ::::::::::::::::::::::::::
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    for (int i = 0; i < layer_number; i++)
    {
        //MUSIC 1
        h2_MUSIC_1_layer[i]->Fill(sum_energy_layer[i],energy_MUSIC_1);
        //MUSIC 2
        h2_MUSIC_2_layer[i]->Fill(sum_energy_layer[i],energy_MUSIC_2);
        //travMUSIC
        h2_travMUSIC_layer[i]->Fill(sum_energy_layer[i],energy_travMUSIC);
        
    }


    fNEvents++;

}

void LisaFrsCorrelationsOnline::FinishEvent()
{

}

void LisaFrsCorrelationsOnline::FinishTask()
{

}


ClassImp(LisaFrsCorrelationsOnline)