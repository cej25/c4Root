/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                                C.E. Jones                                  *
 *                                 06.05.25                                   *
 ******************************************************************************/

#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "FrsAidaCorrelationsOnline.h"
#include "FrsHitData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"
#include "c4Logger.h"

#include "TDirectory.h"
#include "THttpServer.h"

FrsAidaCorrelationsOnline::FrsAidaCorrelationsOnline(std::vector<FrsGate*> fg)
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   hitArrayFrs(nullptr)
    ,   fAidaImplants(nullptr)
{
    FrsGates = fg;
    aida_config = TAidaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    correl_config = TCorrelationsConfiguration::GetInstance();
    Correl = correl_config->CorrelationsMap();
}

FrsAidaCorrelationsOnline::FrsAidaCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   hitArrayFrs(nullptr)
    ,   fAidaImplants(nullptr)
{
    aida_config = TAidaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    correl_config = TCorrelationsConfiguration::GetInstance();
    Correl = correl_config->CorrelationsMap();
}

FrsAidaCorrelationsOnline::~FrsAidaCorrelationsOnline()
{
    c4LOG(info, "Deleting FrsAidaCorrelationsOnline task.");
}

InitStatus FrsAidaCorrelationsOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
    c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!");

    fAidaImplants = mgr->InitObjectAs<decltype(fAidaImplants)>("AidaImplantHits");
    c4LOG_IF(fatal, !fAidaImplants, "Branch AidaImplantHits not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {   
        c4LOG(info, "Creating FRS Online Directory");
        dir_frs = new TDirectory("FRS Online", "FRS Online", "", 0);
        mgr->Register("FRS", "FRS Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }

    dir_frs_aida_corr = dir_frs->mkdir("FRS-AIDA Correlations");
    dir_implants = dir_frs_aida_corr->mkdir("Implants");
    dir_stopped_implants = dir_frs_aida_corr->mkdir("Stopped Implants");

    // init tgraphs/histograms here
    dir_stopped_implants->cd();
    int bins = FrsGates.size() * aida_config->DSSDs();
    h1_stopped_implanted_passed_gate = new TH1I("h1_stopped_implanted_passed_gate", "Stopped ions by DSSD, passing FRS PID Gates", bins, 0, bins);

    for (int i = 0; i < bins; i++)
    {
        const char* labelDSSD;
        const char* labelPID;
        int DSSD = (i % aida_config->DSSDs() + 1);

        if (i % aida_config->DSSDs() == 0)
        {
            std::string stringPID = "PID: " + FrsGates[i/aida_config->DSSDs()]->GetName();
            labelPID = stringPID.c_str();
            h1_stopped_implanted_passed_gate->GetXaxis()->SetBinLabel(i+1, Form("#splitline{DSSD %i}{%s}",DSSD,labelPID));
        }
        else h1_stopped_implanted_passed_gate->GetXaxis()->SetBinLabel(i+1, Form("DSSD %i", DSSD));

    }

    stopped_implant_passed_gate_count_dssd1 = new int[FrsGates.size()];
    for (int i = 0; i < FrsGates.size(); i++) stopped_implant_passed_gate_count_dssd1[i] = 0;
    stopped_implant_passed_gate_count_dssd2 = new int[FrsGates.size()];
    for (int i = 0; i < FrsGates.size(); i++) stopped_implant_passed_gate_count_dssd2[i] = 0;
    // dssd3 ?

    hG_stopped_implants_ratio.resize(FrsGates.size());
    r_plotted = new int[FrsGates.size()];
    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
        r_plotted[gate] = 0;
        hG_stopped_implants_ratio[gate] = new TGraph(1);
        hG_stopped_implants_ratio[gate]->SetName(Form("hG_stopped_implants_ratio_gate%i",gate));
        hG_stopped_implants_ratio[gate]->SetTitle(Form("Ratio of %s Gated ions stopped in DSSD1:DSSD2", FrsGates[gate]->GetName().c_str()));
        hG_stopped_implants_ratio[gate]->GetXaxis()->SetTimeDisplay(1);
        hG_stopped_implants_ratio[gate]->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
        hG_stopped_implants_ratio[gate]->GetXaxis()->SetTimeOffset(0, "local");
        hG_stopped_implants_ratio[gate]->GetYaxis()->SetTitle("Ratio");
        hG_stopped_implants_ratio[gate]->GetXaxis()->SetTitle("Time [Y-M-D H:M]");
        hG_stopped_implants_ratio[gate]->SetMarkerColor(kBlack);
        hG_stopped_implants_ratio[gate]->SetMarkerStyle(20);
        if (gate == 0) hG_stopped_implants_ratio[gate]->SetLineColor(kBlue);
        else if (gate == 1) hG_stopped_implants_ratio[gate]->SetLineColor(kRed);
        hG_stopped_implants_ratio[gate]->SetLineWidth(2);
        hG_stopped_implants_ratio[gate]->GetXaxis()->SetNdivisions(-4);
        dir_stopped_implants->Append(hG_stopped_implants_ratio[gate]);
    }

    double xmax = aida_config->Wide() ? 113.4 : 37.8;
    int xstrips = aida_config->Wide() ? 386 : 128;
    
    h2_AidaImplant_ZvsAoQGated_position.resize(aida_config->DSSDs());
    h1_AidaImplant_ZvsAoQGated_energy.resize(aida_config->DSSDs());
    h2_AidaImplant_ZvsAoQGated_position_stopped.resize(aida_config->DSSDs());
    h1_AidaImplant_ZvsAoQGated_energy_stopped.resize(aida_config->DSSDs());
    for (int dssd = 0; dssd < aida_config->DSSDs(); dssd++)
    {
        h2_AidaImplant_ZvsAoQGated_position[dssd].resize(FrsGates.size());
        h1_AidaImplant_ZvsAoQGated_energy[dssd].resize(FrsGates.size());
        h2_AidaImplant_ZvsAoQGated_position_stopped[dssd].resize(FrsGates.size());
        h1_AidaImplant_ZvsAoQGated_energy_stopped[dssd].resize(FrsGates.size());

        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            dir_implants->cd();
            h2_AidaImplant_ZvsAoQGated_position[dssd][gate] = new TH2I(Form("h2_AidaImplant_ZvsAoQGate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS ZAoQ Gate: %s", dssd + 1, FrsGates[gate]->GetName().c_str()), xstrips, -xmax, xmax, 128, -37.8, 37.8);
            h2_AidaImplant_ZvsAoQGated_position[dssd][gate]->GetXaxis()->SetTitle("X position [mm]");
            h2_AidaImplant_ZvsAoQGated_position[dssd][gate]->GetYaxis()->SetTitle("Y position [mm]");
            h2_AidaImplant_ZvsAoQGated_position[dssd][gate]->SetOption("COLZ");
            h1_AidaImplant_ZvsAoQGated_energy[dssd][gate] = new TH1I(Form("h1_AidaImplant_ZvsAoQGate%d_energy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS ZAoQ Gate: %s", dssd + 1, FrsGates[gate]->GetName().c_str()), 1000, 0, 10000);
            dir_stopped_implants->cd();
            h2_AidaImplant_ZvsAoQGated_position_stopped[dssd][gate] = new TH2I(Form("h2_AidaImplant_ZvsAoQGate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS ZAoQ Gate: %s", dssd + 1, FrsGates[gate]->GetName().c_str()), xstrips, -xmax, xmax, 128, -37.8, 37.8);
            h2_AidaImplant_ZvsAoQGated_position_stopped[dssd][gate]->GetXaxis()->SetTitle("X position [mm]");
            h2_AidaImplant_ZvsAoQGated_position_stopped[dssd][gate]->GetYaxis()->SetTitle("Y position [mm]");
            h2_AidaImplant_ZvsAoQGated_position_stopped[dssd][gate]->SetOption("COLZ");
            h1_AidaImplant_ZvsAoQGated_energy_stopped[dssd][gate] = new TH1I(Form("h1_AidaImplant_ZvsAoQGate%d_energy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS ZAoQ Gate: %s", dssd + 1, FrsGates[gate]->GetName().c_str()), 1000, 0, 10000);
        }
    }
    

    return kSUCCESS;

}


void FrsAidaCorrelationsOnline::Exec(Option_t* option)
{ 
    if (fAidaImplants->size() <= 0 || hitArrayFrs->size() <= 0) return;

    const auto & hitItemFrs = hitArrayFrs->at(0);

    for (auto & i : *fAidaImplants)
    {
        AidaHit hit = i;
        
        if (hit.Time - hitItemFrs.Get_wr_t() > Correl["FRS-AIDA WR Gate"][0] && hit.Time - hitItemFrs.Get_wr_t() < Correl["FRS-AIDA WR Gate"][1])
        {
            if (!FrsGates.empty())
            {
                for (int gate = 0; gate < FrsGates.size(); gate++)
                {
                    // hit pattern and energy
                    if (FrsGates[gate]->Passed_Z41vsAoQs2s4(hitItemFrs.Get_ID_z41(), hitItemFrs.Get_ID_AoQ_s2s4()))
                    {
                        h2_AidaImplant_ZvsAoQGated_position[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                        h1_AidaImplant_ZvsAoQGated_energy[hit.DSSD-1][gate]->Fill(hit.Energy);
                    }
                }
            }

            if (hit.Stopped)
            {
                if (!FrsGates.empty())
                {
                    for (int gate = 0; gate < FrsGates.size(); gate++)
                    {
                        if (FrsGates[gate]->PassedGate(hitItemFrs.Get_ID_z41(), hitItemFrs.Get_ID_z42(), hitItemFrs.Get_ID_x2(), hitItemFrs.Get_ID_x4(), hitItemFrs.Get_ID_AoQ_s2s4(), hitItemFrs.Get_ID_dEdeg_z41(), hitItemFrs.Get_sci_e_42()))
                        {
                            h1_stopped_implanted_passed_gate->Fill(gate * aida_config->DSSDs() + hit.DSSD - 1);

                            if (hit.DSSD == 1) stopped_implant_passed_gate_count_dssd1[gate]++;
                            else if (hit.DSSD == 2) stopped_implant_passed_gate_count_dssd2[gate]++;
                        }

                        int sum = stopped_implant_passed_gate_count_dssd1[gate] + stopped_implant_passed_gate_count_dssd2[gate];
                        if (sum % plotRatioEvery == 0 && sum > 0)
                        {   
                            time_t rawtime; time(&rawtime);
                            double ratio = (double)stopped_implant_passed_gate_count_dssd1[gate] / (double)stopped_implant_passed_gate_count_dssd2[gate]; // for testing graph
                            hG_stopped_implants_ratio[gate]->SetPoint(r_plotted[gate], rawtime, (double)ratio);
                            r_plotted[gate]++;
                            stopped_implant_passed_gate_count_dssd1[gate] = 0;
                            stopped_implant_passed_gate_count_dssd2[gate] = 0;
                        }

                        // hit pattern and energy
                        if (FrsGates[gate]->Passed_Z41vsAoQs2s4(hitItemFrs.Get_ID_z41(), hitItemFrs.Get_ID_AoQ_s2s4()))
                        {
                            h2_AidaImplant_ZvsAoQGated_position_stopped[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                            h1_AidaImplant_ZvsAoQGated_energy_stopped[hit.DSSD-1][gate]->Fill(hit.Energy);
                        }
                    }
                }          
            } // Stopped
        } // FRS-AIDA WR Gate
    } // Aida Implants

    fNEvents++;
        
} // nHits


void FrsAidaCorrelationsOnline::FinishEvent()
{

}

void FrsAidaCorrelationsOnline::FinishTask()
{

}


ClassImp(FrsAidaCorrelationsOnline)
