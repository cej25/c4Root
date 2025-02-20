// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BetaIonCorrelations.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumFebexData.h"
#include "FrsHitData.h"
#include "AidaData.h"
#include "AidaHitData.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

BetaIonCorrelations::BetaIonCorrelations() : BetaIonCorrelations("BetaIonCorrelations")
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();
}

BetaIonCorrelations::BetaIonCorrelations(std::vector<FrsGate*> fgs) : BetaIonCorrelations("BetaIonCorrelations")
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();

    FrsGates = fgs;
}

BetaIonCorrelations::BetaIonCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , implantHitArray(nullptr)
    , decayHitArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
}

BetaIonCorrelations::~BetaIonCorrelations()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
    if (fHitGe)
        delete fHitGe;
   
}


InitStatus BetaIonCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance(); // do we need to grab the run? maybe we can add objects to it

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");
    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");
    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");
    hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
    c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!");

    dir_corrs = (TDirectory*)mgr->GetObject("Correlations");
    if (dir_corrs == nullptr) 
    {
        LOG(info) << "Creating Correlations Directory";
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_corrs = gDirectory->mkdir("Correlations");
        mgr->Register("Correlations", "Correlations Directory", dir_corrs, false); // allow other tasks to find this
        found_dir_corrs = false;
    }


    // get correlations folder?
    dir_beta_gamma = dir_corrs->mkdir("Beta-Gamma Correlations");

    h1_aida_germanium_dt = MakeTH1(dir_beta_gamma, "I", "h1_aida_germanium_dt", "AIDA - DEGAS dT (with some conditions)", 2000, -50000, 50000);
    h1_beta_gamma_corr_energy = MakeTH1(dir_beta_gamma, "F", "h1_beta_gamma_corr_energy", "Gamma energy after Beta decay", 2000, 0., 2000.);
    h1_beta_gamma_bkg = MakeTH1(dir_beta_gamma, "F", "h1_beta_gamma_bkg", "Ion-Beta is 35-200 seconds", 2000, 0., 2000.);
    h1_beta_gamma_diff = MakeTH1(dir_beta_gamma, "F", "h1_beta_gamma_diff", "Difference?", 2000, 0, 2000);

    //h1_imp_decay_dt = MakeTH1(dir_beta_gamma, "I", "h1_imp_decay_dt", "Implant Decay dT w/ some conditions", 20000, 0, 200e9);

    h2_ZvsAoQ = MakeTH2(dir_beta_gamma, "F", "h2_ZvsAoQ", "Z vs AoQ", 1000, 2, 4, 1000, 50, 100);
    h2_ZvsAoQ_inside_gate = MakeTH2(dir_beta_gamma, "F", "h2_ZvsAoQ_inside_gate", "Z vs AoQ inside gate", 1000, 2, 4, 1000, 50, 100);

    h1_gammas_inside_gate = MakeTH1(dir_beta_gamma, "F", "h1_gammas_inside_gate", "Gammas inside Gate", 2000, 0, 2000);

    int xstrips = aida_config->Wide() ? 386 : 128;
    double xmax = aida_config->Wide() ? 113.4 : 37.8;

    h2_implant_pos_xy.resize(aida_config->DSSDs());
    h2_imp_stopped_pos_xy.resize(aida_config->DSSDs());
    h1_implant_e.resize(aida_config->DSSDs());
    h2_decay_pos_xy.resize(aida_config->DSSDs());
    h1_decay_e.resize(aida_config->DSSDs());


    for (int i = 0; i < aida_config->DSSDs(); i++)
    {
        std::stringstream name;
        std::stringstream title;

        // implant 
        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_pos_xy";
        title << "DSSD " << (i + 1) << " implant position";
        h2_implant_pos_xy[i] = MakeTH2(dir_beta_gamma, "F", name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h2_implant_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h2_implant_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");

        // NEW
        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_stopped_implants_pos_xy";
        title << "DSSD " << (i + 1) << " implant position";
        h2_imp_stopped_pos_xy[i] = MakeTH2(dir_beta_gamma, "F", name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h2_imp_stopped_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h2_imp_stopped_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");

        name.str("");
        title.str("");
        name << "aida_implants_d" << (i + 1) << "_implants_e";
        title << "DSSD " << (i + 1) << " implant energy";
        h1_implant_e[i] = MakeTH1(dir_beta_gamma, "F", name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h1_implant_e[i]->GetXaxis()->SetTitle("Implant Energy/MeV");

        // decays
        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_pos_xy";
        title << "DSSD " << (i + 1) << " decay position";
        h2_decay_pos_xy[i] = MakeTH2(dir_beta_gamma, "F", name.str().c_str(), title.str().c_str(),
                xstrips, -xmax, xmax, 128, -37.8, 37.8);
        h2_decay_pos_xy[i]->GetXaxis()->SetTitle("X position/mm");
        h2_decay_pos_xy[i]->GetYaxis()->SetTitle("Y position/mm");

        name.str("");
        title.str("");
        name << "aida_decays_d" << (i + 1) << "_decays_e";
        title << "DSSD " << (i + 1) << " decay energy";
        h1_decay_e[i] = MakeTH1(dir_beta_gamma, "F", name.str().c_str(), title.str().c_str(),
                2000, 0, 20000);
        h1_decay_e[i]->GetXaxis()->SetTitle("Decay Energy/keV");

    }


    h1_imp_mult = MakeTH1(dir_beta_gamma, "I", "h1_imp_mult", "Implant Multiplicity", 10, 0, 10);
    h1_imp_stopped_mult = MakeTH1(dir_beta_gamma, "I", "h1_imp_stopped_mult", "Stopped Implant Multiplicity", 10, 0, 10);
    h1_decay_mult = MakeTH1(dir_beta_gamma, "I", "h1_decay_mult", "Decay Multiplicity", 128, 0, 128);
    h1_strip_mult = MakeTH1(dir_beta_gamma, "I", "h1_strip_mult", "Strip Multiplicity", 128, 0, 128);
    h1_cluster_size_x = MakeTH1(dir_beta_gamma, "I", "h1_cluster_size_x", "Cluster Size X", 10, 0, 10);
    h1_cluster_size_y = MakeTH1(dir_beta_gamma, "I", "h1_cluster_size_y", "Cluster Size Y", 10, 0, 10);

    h1_relevant_imps_per_decay = MakeTH1(dir_beta_gamma, "I", "h1_relevant_imps_per_decay", "Relevant Implants per Decay", 20, 0, 20);

    h1_relevant_decay_mult = MakeTH1(dir_beta_gamma, "I", "h1_relevant_decay_mult", "Relevant Decay Mult", 20, 0, 20);
    h1_relevant_decay_mult_less_than = MakeTH1(dir_beta_gamma, "I", "h1_relevant_decay_mult_less_than", "Relevant Decay Mult w/ < last_dt Condition", 20, 0, 20);


    h1_all_gammas = MakeTH1(dir_beta_gamma, "F", "h1_all_gammas", "All Gammas", 2000, 0, 2000);


    int half_life = 21;
    // ns->s * n_halflives * half_life
    correlation_window = 1e9 * 3 * half_life;
    // ns->s * half_life / ln(2)
    mean_lifetime = 1e9 * half_life / 0.69314718056;

    h1_imp_decay_dt = MakeTH1(dir_beta_gamma, "F", "h1_imp_decay_dt", "Imp-Decay dT", 1000, 0, 2 * mean_lifetime);

    h1_decay_gamma_dt = MakeTH1(dir_beta_gamma, "F", "h1_decay_gamma_dt", "Germanium - AIDA decay", 1000, -50000, 0);

    c4LOG(info, "Success");

    return kSUCCESS;
    
}


void BetaIonCorrelations::Exec(Option_t* option)
{
    fNEvents += 1;

  
    if (hitArrayFrs->size() > 0 && !FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            const auto & hitItemFrs = hitArrayFrs->at(0);
            double z = hitItemFrs.Get_ID_z41();
            double z2 = hitItemFrs.Get_ID_z42();
            double aoq = hitItemFrs.Get_ID_AoQ_s2s4();
            double x2 = hitItemFrs.Get_ID_x2();
            double x4 = hitItemFrs.Get_ID_x4();
            double dEdeg = hitItemFrs.Get_ID_dEdeg_z41();

            h2_ZvsAoQ->Fill(hitItemFrs.Get_ID_AoQ_s2s4(), hitItemFrs.Get_ID_z41());

            //if (FrsGates[gate]->PassedGate(z, z2, x2, x4, aoq, dEdeg))
            if (FrsGates[gate]->Passed_Z41vsAoQs2s4(z, aoq))
            {
                h2_ZvsAoQ_inside_gate->Fill(hitItemFrs.Get_ID_AoQ_s2s4(), hitItemFrs.Get_ID_z41());

                int imp_mult = 0; int imp_stopped_mult = 0;
                for (auto & i : *implantHitArray)
                {
                    imp_mult++;
                    AidaHit implant = i;
                    
                    if (implant.Stopped && implant.DSSD == 1)
                    {
                        imp_stopped_mult++;

                        std::vector<std::pair<AidaHit,std::vector<GermaniumCalData*>>> decays = {};
                        std::pair<AidaHit, std::vector<std::pair<AidaHit,std::vector<GermaniumCalData*>>>> implant_decays = {implant, decays};
                        implant_map.emplace(implant.Time, implant_decays);
                        nImplants++;

                        h2_imp_stopped_pos_xy[implant.DSSD-1]->Fill(implant.PosX, implant.PosY);
                    }

                    if (imp_stopped_mult == 1) break;

                } // implant loop

                // we need a breakout so these are sort of irrelevant for now
                //if (imp_mult > 0) h1_imp_mult->Fill(imp_mult);
                //if (imp_stopped_mult > 0) h1_imp_stopped_mult->Fill(imp_stopped_mult);

                if (fHitGe && fHitGe->GetEntriesFast() > 0)
                {
                    Int_t nHits = fHitGe->GetEntriesFast();
                    
                    //find sci41:
                    int nGe_hit = 0;
                    for (Int_t ihit = 0; ihit < nHits; ihit++)
                    {
                
                        GermaniumCalData* gamma = (GermaniumCalData*)fHitGe->At(ihit);
                        if (!gamma) continue;
                        
                        h1_gammas_inside_gate->Fill(gamma->Get_channel_energy());
                    }
                }
            
            } // Passed FRS Gate
        } // FRS Gate loop
    } // FRS Gates exist

    // 10 for now, maybe 3 will be better. what is so fucking slow though?
    //if (decayHitArray->size() >= 40) return;
    int decay_mult = 0; int good_decay_mult = 0;
    //if (hitArrayFrs->size() > 0) return; // not quite a spill condition..

    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
    for (auto & d : *decayHitArray)
    {
        decay_mult++;
        AidaHit current_decay = d;

        if (current_decay.DSSD != 1) continue;

        if (decay_mult == 1)
        {
            int64_t min_decay_time = current_decay.Time - correlation_window;

            auto it_low = implant_map.lower_bound(min_decay_time);
            if (it_low != implant_map.begin()) // there are implants out of correlation range
            {
                for (auto candidate = implant_map.begin(); candidate != it_low;)
                {
                    std::vector<std::pair<AidaHit,std::vector<GermaniumCalData*>>> decay_candidates = candidate->second.second;
                    //std::cout << "decay candidates size: " << decay_candidates.size() << "\n";
                    double max_likelihood = 0;

                    std::pair<AidaHit,std::vector<GermaniumCalData*>> best_decay_candidate;
                    for (int i = 0;i < decay_candidates.size(); i++)
                    {
                        std::pair<AidaHit,std::vector<GermaniumCalData*>> decay_candidate = decay_candidates.at(i);
                        double likelihood = CalcLL(decay_candidate.first.Time - candidate->first, mean_lifetime);
                        // just for now so I can cope with the output
                        //if (decay_candidates.size() <= 30) std::cout << likelihood << std::endl;;

                        if (likelihood > max_likelihood)
                        {
                            //std::cout << "test 5\n";
                            max_likelihood = likelihood;
                            best_decay_candidate = decay_candidate;
                        }
                    }

                    // do something interesting with the implant and decay.
                    double best_time = best_decay_candidate.first.Time;
                    int64_t id_dt = best_time - candidate->first;
                    h1_imp_decay_dt->Fill(id_dt);
                    std::cout << "chosen! gamma vector size... " << best_decay_candidate.second.size() << "\n"; 
                    AidaHit implant_candidate = candidate->second.first;
                    std::pair<AidaHit, std::pair<AidaHit, std::vector<GermaniumCalData*>>> implant_beta_gammas = {implant_candidate, best_decay_candidate};
                    implant_decay_map.emplace(best_time, implant_beta_gammas);
                    nID_Pairs++;

                    // remove implant from implant_map and decay from all implant_candidates
                    candidate = implant_map.erase(candidate);
                    for (auto remaining_implants = implant_map.begin(); remaining_implants != implant_map.end(); remaining_implants++)
                    {
                        std::vector<std::pair<AidaHit,std::vector<GermaniumCalData*>>>& remaining_decays = remaining_implants->second.second;
                        for (int i = 0; i < remaining_decays.size(); i++)
                        {
                            if (remaining_decays.at(i).first.Time == best_time)
                            {
                                remaining_decays.erase(remaining_decays.begin() + i);
                            }
                        }
                    }

                }
            } // implants out of correlation range
        } // decay_mult = 1

        // now we work with the current decay..
        // we can just analyse implant-decay pairs when we have decays? I don't think this is a problem?
        
        // only put a decay through if it matches good criteria
        if ((current_decay.TimeY - current_decay.TimeX) < FrontBack_dT && (current_decay.TimeY - current_decay.TimeX) > -FrontBack_dT)
        {
            if ((current_decay.EnergyY - current_decay.EnergyX) < FrontBack_dE && (current_decay.EnergyY - current_decay.EnergyX) > -FrontBack_dE)
            {  
                for (auto implant_key = implant_map.begin(); implant_key != implant_map.end(); implant_key++)
                {
                    AidaHit implant = implant_key->second.first;
                    std::vector<std::pair<AidaHit,std::vector<GermaniumCalData*>>>& decays_vector = implant_key->second.second;

                    if (current_decay.DSSD == implant.DSSD)
                    {
                        if (current_decay.StripXMax >= (implant.StripXMin-1) && current_decay.StripXMin <= (implant.StripXMax+1))
                        {
                            if (current_decay.StripYMax >= (implant.StripYMin-1) && current_decay.StripYMin <= (implant.StripYMax+1))
                            {

                                h1_decay_e[current_decay.DSSD-1]->Fill(current_decay.Energy);
                                if (current_decay.Energy > 250)
                                {

                                
                                    // this is theoretically a "good" decay, although perhaps an energy gate is required
                                    // if Energy is good, move onwards. If energy is not good, attempt reconstruction?
                                    good_decay_mult++;
                                
                                    // we need to find gammas now.. 
                                    std::vector<GermaniumCalData*> gamma_vector;

                                    if (fHitGe && fHitGe->GetEntriesFast() > 0)
                                    {
                                        Int_t nHits = fHitGe->GetEntriesFast();
                                        
                    
                                        int nGe_hit = 0;
                                        for (Int_t ihit = 0; ihit < nHits; ihit++)
                                        {
                                
                                            GermaniumCalData* gamma = (GermaniumCalData*)fHitGe->At(ihit);
                                            if (!gamma) continue;
                                            
                                            int64_t wr_ge = gamma->Get_wr_t();
                                            int64_t beta_gamma_dt = wr_ge - current_decay.Time;
                                            if (beta_gamma_dt > WR_AIDA_GE_LO && beta_gamma_dt < WR_AIDA_GE_HI) // high condition true by default
                                            {
                                                gamma_vector.emplace_back(gamma);
                                                nGammasInRange++;
                                            }
                                            else
                                            {
                                                nGammasOutOfRange++;
                                            }
                                        }

                                    }

                                    std::pair<AidaHit,std::vector<GermaniumCalData*>> beta_gammas = {current_decay, gamma_vector};
                                    decays_vector.emplace_back(beta_gammas);
                                
                                }
                                else if (current_decay.Energy < 250)
                                {
                                    // RECONSTRUCT ?? 
                                }

                            } // strip Y match
                        } // strip X match
                    } // DSSD match

                } // implant map loop   

            } // FrontBack energy match
        } // FrontBack time match

        if (good_decay_mult > 0) break; 

    } // decay hit loop
    }
    // plot gammas
    for (auto implant_decay_pair = implant_decay_map.begin(); implant_decay_pair != implant_decay_map.end(); )
    {
        std::vector<GermaniumCalData*> gammas = implant_decay_pair->second.second.second;
        for (int i = 0; i < gammas.size(); i++)
        {
            h1_beta_gamma_corr_energy->Fill(gammas.at(i)->Get_channel_energy());
            nGammas++;
            h1_decay_gamma_dt->Fill(gammas.at(i)->Get_wr_t() - implant_decay_pair->first);
        }

        implant_decay_pair = implant_decay_map.erase(implant_decay_pair);
    }



    if (fNEvents % 100000 == 0)
    {
        std::cout << "Processed " << fNEvents << " events.\n";
    }

}

// in progress
double BetaIonCorrelations::CalcLL(double time, double lifetime)
{   
    // BAD, INCORRECT CALCULATION THAT RETURNS THE SAME RESULT FOR NOW

    double likelihood = 1 / TMath::Abs(time - lifetime);
    return likelihood;
}

void BetaIonCorrelations::FinishEvent()
{

}

void BetaIonCorrelations::FinishTask()
{
    c4LOG(info, "TERMINATION: " << fNEvents << " EVENTS PROCESSED!");


    c4LOG(info, "Total implants: " << nImplants);
    c4LOG(info, "Total ID correlated pairs: " << nID_Pairs);
    c4LOG(info, "Total gammas plotted: " << nGammas);
    c4LOG(info, "Total pass FRS: " << nPass);
    c4LOG(info, "Gammas in Range: " << nGammasInRange);
    c4LOG(info, "Gammas out of Range: " << nGammasOutOfRange);


    //h1_beta_gamma_diff = (TH1*)h1_beta_gamma_corr_energy->Clone("h1_beta_gamma_diff");
    h1_beta_gamma_diff->Add(h1_beta_gamma_bkg, -1);

    if (found_dir_corrs == false) // && FairRunOnline::Instance() == NULL 
    {
        std::cout << "we should now be writing to file.. " << std::endl;
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_corrs->Write();
        gDirectory = tmp;
        c4LOG(info, "Written Beta-Ion Correlations histograms to file.");
    }
}

ClassImp(BetaIonCorrelations)


// so should we erase an implant from the map once we determine which decay its paired with?