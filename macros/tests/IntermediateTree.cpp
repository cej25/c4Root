#include "Tree_Structs.h"
// #include "AIDA_Decay_Event_Store.h"
// #include "tqdm.h"

#include "TCutG.h"
#include <TChain.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

#include <ROOT/TThreadedObject.hxx>
#include <ROOT/TTreeProcessorMT.hxx>
#include <chrono>
#include <fstream>
#include <memory>
#include "TH1F.h"
#include "TH2F.h"

#include "tqdm.h"

bool GoodDecay(AidaHit decay)
{
    bool good = false;

    double FBE = 100;
    double FBT = 1000;
    double minE = 350; // set individually?

    if (decay.ClusterSizeX > 1 || decay.ClusterSizeY > 1) return good;
    if ((decay.TimeY - decay.TimeX) < FBT && (decay.TimeY - decay.TimeX) > -FBT)
    {
        if ((decay.EnergyY - decay.EnergyX) < FBE && (decay.EnergyY - decay.EnergyX) > -FBE)
        {
            if (decay.EnergyY > minE && decay.EnergyX > minE)
            {
            }
        }
    }

    return good;
}

// B defines correlation grid :: 0 means implant pixel = decay pixel
bool PixelCorrelate(AidaHit implant, AidaHit decay, int B)
{
    bool correlated = false;

    if (decay.StripXMax >= (implant.StripXMin-B) && decay.StripXMin <= (implant.StripXMax+B))
    {
        if (decay.StripYMax >= (implant.StripYMin-B) && decay.StripYMin <= (implant.StripYMax+B))
        {
            correlated = true;
        }
    }

    return correlated;
}


void TreeReader()
{
    TChain ImplantTree("evt");
    ImplantTree.Add("~/lustre/gamma/jeroen/S100/cluster/trees/special/162Eu_new_0025_0001_aidaana.root");
    ImplantTree.Add("~/lustre/gamma/jeroen/S100/cluster/trees/special/162Eu_new_0025_0002_aidaana.root");
    ImplantTree.Add("~/lustre/gamma/jeroen/S100/cluster/trees/special/162Eu_new_0025_0003_aidaana.root");
    ImplantTree.Add("~/lustre/gamma/jeroen/S100/cluster/trees/special/162Eu_new_0025_0004_aidaana.root");
    ImplantTree.Add("~/lustre/gamma/jeroen/S100/cluster/trees/special/162Eu_new_0025_0005_aidaana.root");

    TTreeReader imp_tr(&ImplantTree);

    // Output
    TFile* f = new TFile("TreeReaderOutput.root", "RECREATE");

    // Histograms
    TH2F* h2_ZvsAoQ = new TH2F("h2_ZvsAoQ", "Z vs AoQ", 500, 2.4, 2.7, 500, 50, 70);
    TH2F* h2_ZvsAoQ_Tb166 = new TH2F("h2_ZvsAoQ_Tb166", "Z vs AoQ (Tb166)", 500, 2.4, 2.7, 500, 50, 70);

    TH2F* h2_implant_pos_xy = new TH2F("h2_implant_pos_xy", "Implant Pos XY", 260, -130, 130, 260, -130, 130);
    TH2F* h2_decay_pos_xy = new TH2F("h2_decay_pos_xy", "Decay Pos XY", 260, -130, 130, 260, -130, 130);
    TH2F* h2_implant_strip_xy = new TH2F("h2_implant_strip_xy", "Implant Strip XY", 390, 0, 390, 130, 0, 130);
    TH2F* h2_decay_strip_xy = new TH2F("h2_decay_strip_xy", "Decay Strip XY", 390, 0, 390, 130, 0, 130);

    TH1F* h1_implant_dt = new TH1F("h1_implant_dt", "Time between implants", 1000, 0, 10000);
    TH1F* h1_implant_decay_dt_Tb166 = new TH1F("h1_implant_decay_dt_Tb166", "Implant-Decay dT - Tb166", 100, 0, 100);

    TH1F* h1_implant_rate = new TH1F("h1_implant_rate", "Implant rate", 300, 0, 300);
    TH1F* h1_decay_rate = new TH1F("h1_decay_rate", "Decay rate", 300, 0, 300);
    TH1F* h1_decay_rate_offspill = new TH1F("h1_decay_rate_offspill", "Decay rate Offspill", 300, 0, 300);
    TH1F* h1_decay_rate_onspill = new TH1F("h1_decay_rate_onspill", "Decay rate Onspill", 300, 0, 300);
    TH1F* h1_spill_flag = new TH1F("h1_spill_flag", "Spill flag", 300, 0, 300);


    TH1F* h1_gamma_aida_dt = new TH1F("h1_gamma_aida_dt", "Gamma-AIDA time", 1000, -30000, 30000);
    TH1F* h1_energy = new TH1F("h1_energy", "Energy", 2000, 0, 2000);

    TH2I* h2_strip_mult_x_all = new TH2I("h2_strip_mult_x_all", "Strip Mult X ALL", 390, 0, 390, 19, 1, 20);
    TH2I* h2_strip_mult_y_all = new TH2I("h2_strip_mult_y_all", "Strip Mult Y ALL", 130, 0, 130, 19, 1, 20);
    TH2I* h2_strip_mult_x_offspill = new TH2I("h2_strip_mult_x_offspill", "Strip Mult X OffSpill", 390, 0, 390, 19, 1, 20);
    TH2I* h2_strip_mult_y_offspill = new TH2I("h2_strip_mult_y_offspill", "Strip Mult Y OffSpill", 130, 0, 130, 19, 1, 20);


    TH1F* h1_front_back_dt = new TH1F("h1_front_back_dt", "Front-Back time", 500, -5000, 5000);

    // FRS gates
    TCutG *Tb166 = new TCutG("Tb166", 12);
	Tb166->SetVarX("FRS_AoQ");
	Tb166->SetVarY("FRS_Z");
	Tb166->SetPoint(0,2.54322,65.5306);
	Tb166->SetPoint(1,2.54062,65.4287);
	Tb166->SetPoint(2,2.53911,65.2602);
	Tb166->SetPoint(3,2.54057,65.0954);
	Tb166->SetPoint(4,2.54487,64.9917);
	Tb166->SetPoint(5,2.54944,64.9694);
	Tb166->SetPoint(6,2.55182,65.112);
	Tb166->SetPoint(7,2.55182,65.312);
    Tb166->SetPoint(8,2.54981,65.4528);
	Tb166->SetPoint(9,2.5435,65.5546);
	Tb166->SetPoint(10,2.54341,65.5306);
	Tb166->SetPoint(11,2.54322,65.5306);

    // maps
    std::multimap<int64_t, AidaHit> implant_map;
    std::multimap<int64_t, AidaHit> decay_only_map;
    std::multimap<int64_t, AidaHit> decay_offspill_only_map;
    std::multimap<int64_t, std::pair<AidaHit, std::vector<GermaniumCalData>>> decay_map;



    TTreeReaderArray<FrsHitItem> tr_frs(imp_tr, "FrsHitData");
    TTreeReaderArray<AidaHit> tr_implants(imp_tr, "AidaImplantHits");
  
    int imp_processed = 0;
    int nImplantsTb166 = 0;

    int B = 0;
    double FBE = 100;
    double FBT = 1000;
    double minE = 350; // set individually?
    int64_t first_decay_time = 1714203270162533830;

    auto start = std::chrono::high_resolution_clock::now();

    int64_t last_implant_time = 0;
    while (imp_tr.Next())
    {
        imp_processed++;

        for (auto const & i : tr_implants)
        {
            AidaHit implant = i;
    
            if (implant.DSSD != 1 || !implant.Stopped) continue;

            h2_implant_strip_xy->Fill(implant.StripX, implant.StripY);

            // :::: FRS correlations :::: //
            if (tr_frs.GetSize() != 1) continue; // no FRS or too many FRS in single event
            FrsHitItem frsHit = tr_frs[0];

            h2_ZvsAoQ->Fill(frsHit.Get_ID_AoQ(), frsHit.Get_ID_z());
            
            // -- Isotope correlations -- //
            if (Tb166->IsInside(frsHit.Get_ID_AoQ(), frsHit.Get_ID_z()))
            {
                nImplantsTb166++;

                h2_ZvsAoQ_Tb166->Fill(frsHit.Get_ID_AoQ(), frsHit.Get_ID_z());

                implant_map.emplace(implant.Time, implant);
                h2_implant_pos_xy->Fill(implant.PosX, implant.PosY);

            } // Tb166

        } // implant loop

    } // reading tree   

    std::cout << "Implant map complete" << std::endl;
    std::cout << "Tb166 Implants                :" << nImplantsTb166 << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double time_elapsed = duration.count() / 1e6;
    std::cout << "Execution time: " << time_elapsed << " seconds." << std::endl;
    
    // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::;:::::::::::::::::::::: //


    // ::::::: DECAYS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //
    TTreeReader dec_tr(&ImplantTree);

    TTreeReaderValue<Bool_t> tr_spill(dec_tr, "EventHeader.fSpillFlag");
    TTreeReaderArray<AidaHit> tr_decays(dec_tr, "AidaDecayHits");
    TTreeReaderArray<GermaniumCalData> tr_germanium(dec_tr, "GermaniumCalData");

    auto start_decays = std::chrono::high_resolution_clock::now();

    while (dec_tr.Next())
    {
        for (auto const & d : tr_decays)
        {
            AidaHit decay = d;
            if (decay.DSSD != 1) continue;

            h1_front_back_dt->Fill(decay.TimeY - decay.TimeX);

            
            // Front-Back matching and Energy threshold
            if ((decay.TimeY - decay.TimeX) < FBT && (decay.TimeY - decay.TimeX) > -FBT)
            {
                if ((decay.EnergyY - decay.EnergyX) < FBE && (decay.EnergyY - decay.EnergyX) > -FBE)
                {
                    if (decay.EnergyY > minE && decay.EnergyX > minE)
                    {

                        
                        decay_only_map.emplace(decay.Time, decay);
                        int64_t t_since_start = decay.Time - first_decay_time;
                        if (t_since_start / 1e9 > 80 && t_since_start / 1e9 < 90 && *tr_spill == 0) std::cout << "hello" << std::endl;

                        // off-spill only
                        if (*tr_spill) continue;

                        decay_offspill_only_map.emplace(decay.Time, decay);

                        for (auto const & g : tr_germanium)
                        {
                            GermaniumCalData gamma = g;
                            int64_t dt = (gamma.Get_wr_t() - decay.Time);
                            
                            if (gamma.Get_wr_t() != 0) h1_gamma_aida_dt->Fill(dt);
                        }

                    }
                }
            }




        } // decay loop
    } // tree reading



    // std::cout << "decay map is done!" << std::endl;
    // std::cout << "total decays: " << total_decays << std::endl;
    // std::cout << "good decays: " << good_decays << std::endl;

    auto end_decays = std::chrono::high_resolution_clock::now();
    auto duration_decays = std::chrono::duration_cast<std::chrono::microseconds>(end_decays - start_decays);
    double time_elapsed_decays = duration_decays.count() / 1e6;
    std::cout << "Execution time: " << time_elapsed_decays << " seconds." << std::endl;


    for (auto dec = decay_offspill_only_map.begin(); dec != decay_offspill_only_map.end(); dec++)
    {
        AidaHit decay = dec->second;
        int64_t decay_time = decay.Time;

        // find implants before this time
        auto it = implant_map.lower_bound(decay_time);

        // If lower_bound returns the end, step back to the last element
        if (it == implant_map.end() || it->first > decay_time) 
        {
            if (it != implant_map.begin()) --it;
            else 
            {
                //std::cout << "No valid elements before the target time." << std::endl;
                continue;
            }
        }
        
        // Iterate backwards through the multimap starting from the found position
        for (auto rit = std::make_reverse_iterator(it); rit != implant_map.rend(); ++rit) 
        {
            AidaHit implant = rit->second;
            
            if (PixelCorrelate(implant, decay, B))
            {
                double dt = (decay.Time - implant.Time) / 1e9;
                if (dt < 0.4) continue;
                h1_implant_decay_dt_Tb166->Fill(dt);
                h2_decay_strip_xy->Fill(decay.StripX, decay.StripY);
                h2_decay_pos_xy->Fill(decay.PosX, decay.PosY);
                implant_map.erase(rit->first);
                break;
            }

        }
    }



    // Write histograms to file
    h2_ZvsAoQ->Write();
    h2_ZvsAoQ_Tb166->Write();

    h1_implant_dt->Write();
    h1_implant_decay_dt_Tb166->Write();

    h1_implant_rate->Write();
    h1_decay_rate->Write();
    h1_decay_rate_offspill->Write();
    h1_decay_rate_onspill->Write();

    h2_implant_pos_xy->Write();
    h2_decay_pos_xy->Write();

    h1_gamma_aida_dt->Write();
    h1_energy->Write();

    h1_spill_flag->Write();

    h2_strip_mult_x_all->Write();
    h2_strip_mult_y_all->Write();
    h2_strip_mult_x_offspill->Write();
    h2_strip_mult_y_offspill->Write();


    h2_implant_strip_xy->Write();
    h2_decay_strip_xy->Write();

    h1_front_back_dt->Write();

    f->Close();
        
};

