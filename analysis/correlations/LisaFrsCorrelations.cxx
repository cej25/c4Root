#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "LisaFrsCorrelations.h"
#include "FrsHitData.h"
#include "TravMusCalData.h"
#include "LisaCalData.h"
#include "TLisaConfiguration.h" // not here
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

LisaFrsCorrelations::LisaFrsCorrelations() 
    : LisaFrsCorrelations("LisaFrsCorrelations")
{

}

LisaFrsCorrelations::LisaFrsCorrelations(std::vector<FrsGate*> fg)
    : LisaFrsCorrelations("LisaFrsCorrelations")
{
    FrsGates = fg;
}

LisaFrsCorrelations::LisaFrsCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   lisaCalArray(nullptr)
    ,   travMusicArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
    ,   multihitArray(nullptr)

{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
}

LisaFrsCorrelations::~LisaFrsCorrelations()
{
    c4LOG(info, "Destroyed LisaFrsCorrelationsProperly.");
}

InitStatus LisaFrsCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");
    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    travMusicArray = mgr->InitObjectAs<decltype(travMusicArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusicArray, "Branch TravMusCalData not found!");

    //c4LOG(info," start init ");

    layer_number = lisa_config->NLayers();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    auto const & detector_mapping = lisa_config->Mapping();

    /*
    if (dir_corr == nullptr) 
    {   
        c4LOG(info, "Creating Correlations Directory");
        dir_corr = new TDirectory("Correlations", "Correlations", "", 0);
        mgr->Register("Correlations", "Correlations Directory", dir_corr, false); // allow other tasks to find this
    }
    */

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr = gDirectory->mkdir("LISA-FRS Correlations");
    //dir_corr = new TDirectory("Correlations", "Correlations", "", 0);    
    dir_corr->cd();
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
    dir_corr->Append(c_wr_diff);

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
    dir_corr->Append(c_xy_pos_layer1);   

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

    dir_corr->Append(c_xy_pos_layer2);   

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
    dir_corr->Append(c_MUSIC_1_layer);

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
    dir_corr->Append(c_MUSIC_2_layer);

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
    dir_corr->Append(c_travMUSIC_layer);


    h1_energy_layer_ch.resize(layer_number);
    
    for (int i = 1; i < layer_number; i++) //create a canvas for each layer
    {
        h1_energy_layer_ch[i].resize(xmax);
        
        for (int j = 0; j < xmax; j++)
        {
            h1_energy_layer_ch[i][j].resize(ymax);

            for (int k = 0; k < ymax; k++)
            {                           
                city = "";
                for (auto & detector : detector_mapping)
                {
                    if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                    {
                        city = detector.second.first.second;
                        break;
                    }
                }

                h1_energy_layer_ch[i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i", city.c_str(), i, j, k), city.c_str(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                h1_energy_layer_ch[i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
                //h1_energy_layer_ch_gated[gate][i][j][k]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
                //h1_energy_layer_ch_gated[gate][i][j][k]->SetMaximum(lisa_config->AmplitudeMax);
                //h1_energy_layer_ch_gated[gate][i][j][k]->SetStats(0);
                h1_energy_layer_ch[i][j][k]->SetLineColor(kBlack);
                h1_energy_layer_ch[i][j][k]->SetFillColor(kOrange-3);

            }
        }
    }

    c4LOG(info," before gate");
    if (!FrsGates.empty())
    {
        h1_energy_layer_ch_gated.resize(FrsGates.size());
        c_energy.resize(FrsGates.size());

        h1_energy_layer_ch_gated_T.resize(FrsGates.size());

    
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            
            //:::.Energy spectra Gated with FRS
    
            //c_energy[gate].resize(layer_number);

            h1_energy_layer_ch_gated[gate].resize(layer_number);
            h1_energy_layer_ch_gated[gate][0].resize(1);
            h1_energy_layer_ch_gated[gate][0][0].resize(1);
            h1_energy_layer_ch_gated[gate][0][0][0] = new TH1F(Form("energy_000_gated_%i",gate), "Tokyo", lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);

            h1_energy_layer_ch_gated_T[gate].resize(layer_number);
            h1_energy_layer_ch_gated_T[gate][0].resize(1);
            h1_energy_layer_ch_gated_T[gate][0][0].resize(1);
            h1_energy_layer_ch_gated_T[gate][0][0][0] = new TH1F(Form("energy_000_gated%i_T",gate), "Tokyo T", lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);

            //:::::::::::Energy canvas for layer 1 and 2
            //c4LOG(info," after 000 ");
            for (int i = 1; i < layer_number; i++) //create a canvas for each layer
            {
                h1_energy_layer_ch_gated[gate][i].resize(xmax);
                h1_energy_layer_ch_gated_T[gate][i].resize(xmax);

                //c_energy[gate][i].resize(xmax);
                
                for (int j = 0; j < xmax; j++)
                {
                    h1_energy_layer_ch_gated[gate][i][j].resize(ymax);
                    h1_energy_layer_ch_gated_T[gate][i][j].resize(ymax);
                    //c_energy[gate][i][j].resize(ymax);

                    for (int k = 0; k < ymax; k++)
                    {                           
                        city = "";
                        for (auto & detector : detector_mapping)
                        {
                            if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                            {
                                city = detector.second.first.second;
                                break;
                            }
                        }
                        
                        h1_energy_layer_ch_gated[gate][i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i_gate_%i", city.c_str(), i, j, k, gate), city.c_str(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                        h1_energy_layer_ch_gated[gate][i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.]");
                        //h1_energy_layer_ch_gated[gate][i][j][k]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
                        //h1_energy_layer_ch_gated[gate][i][j][k]->SetMaximum(lisa_config->AmplitudeMax);
                        //h1_energy_layer_ch_gated[gate][i][j][k]->SetStats(0);
                        h1_energy_layer_ch_gated[gate][i][j][k]->SetLineColor(kBlack);
                        h1_energy_layer_ch_gated[gate][i][j][k]->SetFillColor(kBlue);

                        h1_energy_layer_ch_gated_T[gate][i][j][k] = new TH1F(Form("energy_%s_%i_%i_%i_gate_%i_T", city.c_str(), i, j, k, gate), city.c_str(), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
                        h1_energy_layer_ch_gated_T[gate][i][j][k]->GetXaxis()->SetTitle("E(LISA) [a.u.] ");
                        //h1_energy_layer_ch_gated_T[gate][i][j][k]->SetMinimum(lisa_config->AmplitudeMin); // set in macro
                        //h1_energy_layer_ch_gated_T[gate][i][j][k]->SetMaximum(lisa_config->AmplitudeMax);
                        //h1_energy_layer_ch_gated_T[gate][i][j][k]->SetStats(0);
                        h1_energy_layer_ch_gated_T[gate][i][j][k]->SetLineColor(kBlack);
                        h1_energy_layer_ch_gated_T[gate][i][j][k]->SetFillColor(kRed-3);


                        //c_energy[gate][i][j][k]->cd();
                        //h1_energy_layer_ch_gated[gate][i][j][k]->Draw("");
                        //h1_energy_layer_ch_gated_T[gate][i][j][k]->Draw("");

                        

                    }
                }
            }
            
            
        }

    }

    if (!FrsGates.empty())
    {
        
        c_energy.resize(FrsGates.size());

        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            c_energy[gate].resize(layer_number);
            for (int i = 1; i < layer_number; i++) //create a canvas for each layer
            {
                c_energy[gate][i].resize(xmax);
                
                for (int j = 0; j < xmax; j++)
                {
                    c_energy[gate][i][j].resize(ymax);

                    for (int k = 0; k < ymax; k++)
                    {                           
                        city = "";
                        for (auto & detector : detector_mapping)
                        {
                            if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
                            {
                                city = detector.second.first.second;
                                break;
                            }
                        }

                        c_energy[gate][i][j][k] = new TCanvas(Form("c1_%s_%i_%i_%i_gate_%i", city.c_str(), i, j, k, gate), Form("Canvas for %s %i %i %i gate %i", city.c_str(), i, j, k, gate), 800, 600);
                        h1_energy_layer_ch[i][j][k]->Draw("");
                        h1_energy_layer_ch_gated[gate][i][j][k]->Draw("SAME");
                        h1_energy_layer_ch_gated_T[gate][i][j][k]->Draw("SAME");
                        dir_corr->Append(c_energy[gate][i][j][k]);

                    }
                }
            }
        }

    }


 
    return kSUCCESS;

}



void LisaFrsCorrelations::Exec(Option_t* option)
{   
    // reject events without both subsystems
    if (lisaCalArray->size() <= 0 || frsHitArray->size() <= 0) return; //frs and trav music are there
    //if (lisaCalArray->size() <= 0 ) return; //for when travmusic is there but not frs

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event
    const auto & travMusicHitItem = travMusicArray->at(0); 
    
    //const auto & multihitItem = multihitArray->at(0); // *should* only be 1 FRS subevent per event


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

        //::::::::: E N E R G Y GATED :::::::::::::::
        h1_energy_layer_ch[layer][xpos][ypos]->Fill(energy_LISA);
        int mh_counter = 0;

        for ( auto const & multihitItem : *multihitArray )
        {    
            if (mh_counter > 0) break;
            if (!FrsGates.empty())
            {
               for (int gate = 0; gate < FrsGates.size(); gate++)
                {  
                    if (FrsGates[gate]->Passed_ZvsAoQ(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_AoQ_mhtdc()))
                    {
                        h1_energy_layer_ch_gated[gate][layer][xpos][ypos]->Fill(energy_LISA);

                        if(frsHitItem.Get_travmusic_dE() >= frs_config->fMin_dE_travMus_gate && frsHitItem.Get_travmusic_dE() <= frs_config->fMax_dE_travMus_gate)
                        {   
                            h1_energy_layer_ch_gated_T[gate][layer][xpos][ypos]->Fill(energy_LISA);
                        }
                    }
                }
            } 
        
            mh_counter++;
            multi_evt++;
        }

        


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

void LisaFrsCorrelations::FinishEvent()
{

}

void LisaFrsCorrelations::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "Multi hit events when LISA is in the event (correlated) : " <<  multi_evt++ << " LISA-FRS events : " << fNEvents);


}


ClassImp(LisaFrsCorrelations)