// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsGermaniumCorrelationsNearline.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "TGermaniumConfiguration.h"

#include "c4Logger.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

FrsGermaniumCorrelationsNearline::FrsGermaniumCorrelationsNearline() : FrsGermaniumCorrelationsNearline("FrsGermaniumCorrelationsNearline")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    frs_configuration = TFrsConfiguration::GetInstance();

}

FrsGermaniumCorrelationsNearline::FrsGermaniumCorrelationsNearline(FrsGate * fg) : FrsGermaniumCorrelationsNearline("FrsGermaniumCorrelationsNearline")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    frsgate = fg;
    frs_configuration = TFrsConfiguration::GetInstance();
}

FrsGermaniumCorrelationsNearline::FrsGermaniumCorrelationsNearline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , hitArrayFrs(nullptr)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

FrsGermaniumCorrelationsNearline::~FrsGermaniumCorrelationsNearline()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}


InitStatus FrsGermaniumCorrelationsNearline::Init()
{

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");
    hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
    c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!");


    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_germanium = gDirectory->mkdir(TString("DEGAS FRS GATE " + frsgate->GetName()));
    gDirectory->cd(TString("DEGAS FRS GATE " + frsgate->GetName()));

    dir_germanium->cd();
    //Implant rate
    g_frs_rate = new TGraph();
    g_frs_rate->SetName(TString("g_frs_germanium_rate_monitor_gated_")+frsgate->GetName());
    g_frs_rate->SetTitle(TString("FRS identified ions per second, avg 60 secs"));
    g_frs_rate->GetXaxis()->SetTitle("seconds");

    g_frs_total = new TGraph();
    g_frs_total->SetName(TString("g_frs_germanium_total_monitor_gated_")+frsgate->GetName());
    g_frs_total->SetTitle(TString("FRS identified ions in total"));
    g_frs_total->GetXaxis()->SetTitle("seconds");

    h2_frs_Z_vs_AoQ_gated = new TH2F(TString("h2_frs_germanium_Z_vs_AoQ_gated_")+frsgate->GetName(),TString("Z vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_AoQ,frs_configuration->fMax_AoQ,1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z);
    h2_frs_Z_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_Z_vs_AoQ_gated->GetYaxis()->SetTitle("Z");

    h2_frs_Z_vs_Z2_gated = new TH2F(TString("h2_frs_germanium_Z_vs_Z2_gated_")+frsgate->GetName(),TString("Z1 vs Z2 plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z,1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z);
    h2_frs_Z_vs_Z2_gated->GetXaxis()->SetTitle("Z1");
    h2_frs_Z_vs_Z2_gated->GetYaxis()->SetTitle("Z2");



    h2_frs_x2_vs_AoQ_gated = new TH2F(TString("h2_frs_germanium_x2_vs_AoQ_gated_")+frsgate->GetName(),TString("x2 vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_AoQ,frs_configuration->fMax_AoQ,1000,frs_configuration->fMin_x2,frs_configuration->fMax_x2);
    h2_frs_x2_vs_AoQ_gated->GetYaxis()->SetTitle("x2");
    h2_frs_x2_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");


    h2_frs_x4_vs_AoQ_gated = new TH2F(TString("h2_frs_germanium_x4_vs_AoQ_gated_")+frsgate->GetName(),TString("x4 vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_AoQ,frs_configuration->fMax_AoQ,1000,frs_configuration->fMin_x4,frs_configuration->fMax_x4);
    h2_frs_x4_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_x4_vs_AoQ_gated->GetYaxis()->SetTitle("x4");

    
    h2_germanium_energy_vs_tsci41 = new TH2F(TString("h2_germanium_energy_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Germanium energies vs t(det) - t(sci41), short lifetime,  gated FRS on "+frsgate->GetName()),10000,-2000,stop_short_lifetime_collection,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_germanium_energy_vs_tsci41->GetYaxis()->SetTitle("energy (keV)");

    
    h1_germanium_energy_promptflash_cut = new TH1F(TString("h1_germanium_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Germanium energy, prompt flash cut out, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_promptflash_cut->GetXaxis()->SetTitle("energy (keV)");


    
    h2_germanium_energy_energy_promptflash_cut = new TH2F(TString("h2_germanium_energy_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString(Form("Germanium energy vs energy, |t(det1)-t(det2)|<%i ns, prompt flash cut out, short lifetime, gated FRS on ",germanium_coincidence_gate)+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_energy_promptflash_cut->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_energy_promptflash_cut->GetYaxis()->SetTitle("energy (keV)");




    h2_germanium_energy_vs_sci41_wr_long = new TH2F(TString("h2_germanium_energy_vs_sci41_wr_long_frs_gate_"+frsgate->GetName()),TString("Germanium energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_vs_sci41_wr_long->GetXaxis()->SetTitle("time difference (ns)");
    h2_germanium_energy_vs_sci41_wr_long->GetYaxis()->SetTitle("energy (keV)");

    
    h1_germanium_energy_promptflash_cut_long = new TH1F(TString("h1_germanium_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Germanium energy, prompt flash cut out, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_promptflash_cut_long->GetXaxis()->SetTitle("energy (keV)");

    h2_germanium_energy_energy_promptflash_cut_long = new TH2F(TString("h2_germanium_energy_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString(Form("Germanium energy vs energy, |t(det1)-t(det2)|<%i ns, prompt flash cut out, long lifetime, gated FRS on ",germanium_coincidence_gate)+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_energy_promptflash_cut_long->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_energy_promptflash_cut_long->GetYaxis()->SetTitle("energy (keV)");
    

    //energy-gated spectra:
    folder_energy_gated = new TDirectory*[gamma_energies_of_interest.size()];

    h1_germanium_tsci41_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    h1_germanium_energy_promptflash_cut_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    //long:
    h1_germanium_energy_promptflash_cut_long_energy_gated = new TH1F*[gamma_energies_of_interest.size()];

    h1_germanium_twr_sci41_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    
    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
        folder_energy_gated[idx_gamma_gate] = dir_germanium->mkdir(Form("Energy gated coincidence spectra, Eg = %i",(int)gamma_energies_of_interest.at(idx_gamma_gate)));
        folder_energy_gated[idx_gamma_gate]->cd();

        h1_germanium_tsci41_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_germanium_tsci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),10000,-2e3,stop_short_lifetime_collection);
        h1_germanium_tsci41_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("time (ns)");

        
        h1_germanium_energy_promptflash_cut_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_germanium_energy_promptflash_cut_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy_promptflash_cut_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("Energy (keV)");

        h1_germanium_twr_sci41_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_germanium_twr_sci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("WR t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh);
        h1_germanium_twr_sci41_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("time (ns)");

        h1_germanium_energy_promptflash_cut_long_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_germanium_energy_promptflash_cut_long_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("Energy (keV)");

    }
    
    dir_germanium->cd();
    gDirectory = tmp;

    return kSUCCESS;
}


void FrsGermaniumCorrelationsNearline::Exec(Option_t* option)
{
    if (hitArrayFrs->size() == 0) return;

    positive_PID = false;
    auto const & frshit = hitArrayFrs->at(0);

    int64_t wr_t = frshit.Get_wr_t();
    if(wr_t_first_frs_hit == 0) wr_t_first_frs_hit = wr_t;
    double ID_x2 = frshit.Get_ID_x2();
    double ID_y2 = frshit.Get_ID_y2();
    double ID_x4 = frshit.Get_ID_x4();
    double ID_AoQ = frshit.Get_ID_AoQ();
    double ID_z = frshit.Get_ID_z();
    double ID_z2 = frshit.Get_ID_z2();
    double ID_dEdeg = frshit.Get_ID_dEdeg();

    // this must pass all gates given to FrsGate:
    positive_PID = frsgate->PassedGate(ID_z, ID_z2, ID_x2, ID_x4, ID_AoQ, ID_dEdeg);
    if (positive_PID)
    {
        wr_t_last_frs_hit = wr_t;
        frs_rate_implanted ++;
        frs_total_implanted ++;

        h2_frs_Z_vs_AoQ_gated->Fill(ID_AoQ,ID_z);
        h2_frs_Z_vs_Z2_gated->Fill(ID_z,ID_z2);
        h2_frs_x2_vs_AoQ_gated->Fill(ID_AoQ,ID_x2);
        h2_frs_x4_vs_AoQ_gated->Fill(ID_AoQ,ID_x4);

        if (wr_t_last_frs_hit - frs_rate_time > 60e9)
        {
            g_frs_rate->AddPoint((wr_t_last_frs_hit - wr_t_first_frs_hit)/1000000000, frs_rate_implanted/60.0);
            g_frs_total->AddPoint((wr_t_last_frs_hit - wr_t_first_frs_hit)/1000000000, frs_total_implanted);
            frs_rate_time = wr_t_last_frs_hit;
            frs_rate_implanted = 0;
        }
    }else{
        wr_t_last_frs_hit = 0;
    }

    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
    
        Int_t nHits = fHitGe->GetEntriesFast();
        
        
        bool sci41_seen = false; // off-spill raw spectra
        int sci41_hit_idx = -1; // sci41's hit index, for getting the time
        int detector_id_sci41 = 0;
        int crystal_id_sci41 = 0;
        double energy_sci41 = 0;
        double time_sci41 = 0;
        

        //find sci41:
        for (Int_t ihit = 0; ihit < nHits; ihit++){ // find the sci41 hit if it is there.
    
            GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();

            if (detector_id1 == germanium_configuration->SC41L() /*|| detector_id1 == germanium_configuration->SC41R()*/) {
                
                if (sci41_seen == true) return;
                
                detector_id_sci41 = hit1->Get_detector_id();
                crystal_id_sci41 = hit1->Get_crystal_id();
                energy_sci41 = hit1->Get_channel_energy();
                time_sci41 = hit1->Get_channel_trigger_time();
                
                sci41_seen = true;
                sci41_hit_idx = ihit;
                break;
            }
        }

        // Spectra with respect to SCI41 - 'short' isomers
        if (nHits >= 2 && sci41_seen && positive_PID){
            for (int ihit2 = 0; ihit2 < nHits; ihit2 ++){
                if (ihit2 == sci41_hit_idx) continue;
                GermaniumCalData* hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                if (!hit2) continue;
                int detector_id1 = hit2->Get_detector_id();
                int crystal_id1 = hit2->Get_crystal_id();
                double energy1 = hit2->Get_channel_energy();
                double time1 = hit2->Get_channel_trigger_time();

                if (germanium_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                double timediff1 = time1 - time_sci41 - germanium_configuration->GetTimeshiftCoefficient(detector_id1,crystal_id1);
                
                h2_germanium_energy_vs_tsci41->Fill(timediff1 ,energy1);

                //after this test, the prompt flash is cut out.
                if ((germanium_configuration->IsInsidePromptFlashCut(timediff1 ,energy1)==true) ) continue;
                if ((timediff1 < -400 || timediff1 > stop_short_lifetime_collection)) continue;
                
                h1_germanium_energy_promptflash_cut->Fill(energy1);

                for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
                    if (!(TMath::Abs(energy1 - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                    
                    //now energy1 fulfills the energy requirement and is outside prompt flash
                    h1_germanium_tsci41_energy_gated[idx_gamma_gate]->Fill(timediff1);
                }
        
                
                if (nHits >= 3){
                
                for (int ihit3 = 0; ihit3<nHits; ihit3 ++){
                    if (ihit3 == sci41_hit_idx) continue;
                    if (ihit3 == ihit2) continue;

                    GermaniumCalData* hit3 = (GermaniumCalData*)fHitGe->At(ihit3);
                    if (!hit3) continue;
                    
                    int detector_id2 = hit3->Get_detector_id();
                    if (detector_id1 == detector_id2) continue; //this is likely a good veto before the add-back is done ... 
                    
                    int crystal_id2 = hit3->Get_crystal_id();
                    double energy2 = hit3->Get_channel_energy();
                    double time2 = hit3->Get_channel_trigger_time();

                    if (germanium_configuration->IsDetectorAuxilliary(detector_id2)) continue;
                    if (TMath::Abs(time2-time1) > germanium_coincidence_gate) continue;

                    double timediff2 = time2 - time_sci41 - germanium_configuration->GetTimeshiftCoefficient(detector_id2,crystal_id2);
                    
                    if ((germanium_configuration->IsInsidePromptFlashCut(timediff2, energy2)==true)) continue;
                    if ((timediff2 < -400 || timediff2 > stop_short_lifetime_collection)) continue;

                    if (ihit3 > ihit2) h2_germanium_energy_energy_promptflash_cut->Fill(energy1,energy2); // avoid double filling ... 


                    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
                        if (!(TMath::Abs(energy1 - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                            // energy1 and energy2 are both in coincidence and outside the promptflash here:
                            h1_germanium_energy_promptflash_cut_energy_gated[idx_gamma_gate]->Fill(energy2);
                        }
                    }
                }
            }
        }

        

        if (nHits >= 1 && wr_t_last_frs_hit != 0){
            //long isomer
        for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){

            GermaniumCalData* hit_long1 = (GermaniumCalData*)fHitGe->At(ihit1);
            if (!hit_long1) continue;
            int detector_id_long = hit_long1->Get_detector_id();
            int crystal_id_long = hit_long1->Get_crystal_id();
            double energy_long = hit_long1->Get_channel_energy();
            double time_long = hit_long1->Get_channel_trigger_time();
            int64_t ge_wr_long = hit_long1->Get_absolute_event_time();

            if (germanium_configuration->IsDetectorAuxilliary(detector_id_long)==true) continue;


            h2_germanium_energy_vs_sci41_wr_long->Fill(ge_wr_long-wr_t_last_frs_hit, energy_long);
            

            // cut the prompt flash on the whiterabbit, roughly, but you are after long isomers ... :)
            if (ge_wr_long - wr_t_last_frs_hit < start_long_lifetime_collection) continue;


            
            if (ge_wr_long - wr_t_last_frs_hit < stop_long_lifetime_collection) h1_germanium_energy_promptflash_cut_long->Fill(energy_long);

                for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++)
                {
                    if (!(TMath::Abs(energy_long - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                    //now energy1 fulfills the energy requirement and is outside prompt flash
                        
                        h1_germanium_twr_sci41_energy_gated[idx_gamma_gate]->Fill(ge_wr_long-wr_t_last_frs_hit);
                }

                        
                if (nHits >= 2)
                {
                
                for (int ihit2 = 0; ihit2<nHits; ihit2 ++){
                    GermaniumCalData* hit_long2 = (GermaniumCalData*)fHitGe->At(ihit2);
                    if (!hit_long2) continue;
                    if (ihit1 == ihit2) continue;
                    int detector_id_long2 = hit_long2->Get_detector_id();
                    int crystal_id_long2 = hit_long2->Get_crystal_id();
                    double energy_long2 = hit_long2->Get_channel_energy();
                    double time_long2 = hit_long2->Get_channel_trigger_time();
                    int64_t ge_wr_long2 = hit_long2->Get_absolute_event_time();


                    if (germanium_configuration->IsDetectorAuxilliary(detector_id_long2)) continue;
                    
                    if (ge_wr_long2 - wr_t_last_frs_hit < start_long_lifetime_collection) continue;
                    if (detector_id_long == detector_id_long2) continue; //this is likely a good veto before the add-back is done
                    
                    // check coincidence, this should also make it so that the second hit is outside the prompt flash as well...:
                    if (TMath::Abs(time_long2-time_long- germanium_configuration->GetTimeshiftCoefficient(detector_id_long2,crystal_id_long2)- germanium_configuration->GetTimeshiftCoefficient(detector_id_long,crystal_id_long)) > germanium_coincidence_gate) continue; 

                    //avoid double filling:
                    if (ihit2>ihit1) h2_germanium_energy_energy_promptflash_cut_long->Fill(energy_long,energy_long2);
                    
                    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++)
                    {
                        if (!(TMath::Abs(energy_long - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                        //now energy1 fulfills the energy requirement and is outside prompt flash
                        // energy1 and energy2 are both in coincidence and outside the promptflash here:
                        if (ge_wr_long2 - wr_t_last_frs_hit < stop_long_lifetime_collection) h1_germanium_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->Fill(energy_long2);
                    }
                }
            }   
        }
        }
    }

    fNEvents += 1;
}

void FrsGermaniumCorrelationsNearline::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
}

void FrsGermaniumCorrelationsNearline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_germanium->Write();
    gDirectory = tmp;
    c4LOG(info, "FRS-DEGAS histograms written to file.");
}

ClassImp(FrsGermaniumCorrelationsNearline)
