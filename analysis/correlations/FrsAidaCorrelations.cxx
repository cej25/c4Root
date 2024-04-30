#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "FrsAidaCorrelations.h"
#include "FrsHitData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"
#include "c4Logger.h"
#include "TFile.h"

FrsAidaCorrelations::FrsAidaCorrelations(std::vector<FrsGate*> fg)
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   hitArrayFrs(nullptr)
    ,   fAidaImplants(nullptr)
{
    aida_config = TAidaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    correl_config = TCorrelationsConfiguration::GetInstance();
    Correl = correl_config->CorrelationsMap();
    FrsGates = fg;
}

FrsAidaCorrelations::FrsAidaCorrelations(const TString& name, Int_t verbose)
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

FrsAidaCorrelations::~FrsAidaCorrelations()
{
    c4LOG(info, "Deleting FrsAidaCorrelations task.");
}

InitStatus FrsAidaCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // don't look for Ana, allow it to latch to online or offline

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
    c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!");

    fAidaImplants = mgr->InitObjectAs<decltype(fAidaImplants)>("AidaImplantHits");
    c4LOG_IF(fatal, !fAidaImplants, "Branch AidaImplantHits not found!");

    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Directory";
        dir_frs = new TDirectory("FRS", "FRS", "", 0);
        mgr->Register("FRS", "FRS Directory", dir_frs, false); // allow other tasks to find this
        found_dir_frs = false;
    }

    dir_frs_aida_corrs = dir_frs->mkdir("FRS-AIDA Correlations");
    dir_implant_corrs = dir_frs_aida_corrs->mkdir("Implants");
    dir_stopped_implant_corrs = dir_frs_aida_corrs->mkdir("Stopped Implants");
    dir_implant_corrs_ZvsAoQ = dir_implant_corrs->mkdir("ZvsAoQ Gated");
    dir_implant_corrs_Z1vsZ2 = dir_implant_corrs->mkdir("Z1vsZ2 Gated");
    dir_implant_corrs_x2vsAoQ = dir_implant_corrs->mkdir("x2vsAoQ Gated");
    dir_implant_corrs_x4vsAoQ = dir_implant_corrs->mkdir("x4vsAoQ Gated");
    dir_implant_corrs_ZvsAoQ_stopped = dir_stopped_implant_corrs->mkdir("ZvsAoQ Gated");
    dir_implant_corrs_Z1vsZ2_stopped = dir_stopped_implant_corrs->mkdir("Z1vsZ2 Gated");
    dir_implant_corrs_x2vsAoQ_stopped = dir_stopped_implant_corrs->mkdir("x2vsAoQ Gated");
    dir_implant_corrs_x4vsAoQ_stopped = dir_stopped_implant_corrs->mkdir("x4vsAoQ Gated");
    dir_implant_corrs_Z1Z2_x2vsAoQ = dir_implant_corrs_Z1vsZ2->mkdir("x2vsAoQ Gated");
    dir_implant_corrs_Z1Z2_x4vsAoQ = dir_implant_corrs_Z1vsZ2->mkdir("x4vsAoQ Gated");
    dir_implant_corrs_Z1Z2_x2vsAoQ_stopped = dir_implant_corrs_Z1vsZ2_stopped->mkdir("x2vsAoQ Gated");
    dir_implant_corrs_Z1Z2_x4vsAoQ_stopped = dir_implant_corrs_Z1vsZ2_stopped->mkdir("x4vsAoQ Gated");
    
    double xmax = aida_config->Wide() ? 113.4 : 37.8;
    int xstrips = aida_config->Wide() ? 386 : 128;

    dir_implant_corrs->cd();
    h1_AidaImplant_Deadtime = new TH1I("h1_Aida_Implant_Deadtime", "Dead Time AIDA Implant", 500, 0, 500);
    h1_AidaImplant_FRS_dT = new TH1I("h1_AidaImplant_FRS_dT", "White Rabbit Aida Implant-FRS", 16000, -40000, 40000);
    h2_AidaImplant_FRS_x_vs_x4 = new TH2F("h1_AidaImplant_FRS_x_vs_x4", "AIDA X position vs FRS ID_x4 position", 200, -20, 20, 200, -20, 20);

    h2_AidaImplant_FRS_ZAoQgate_strip_xy.resize(aida_config->DSSDs());
    h1_AidaImplant_FRS_ZAoQgate_e.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_ZAoQgate_position.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped.resize(aida_config->DSSDs());
    h1_AidaImplant_FRS_ZAoQgate_e_stopped.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_ZAoQgate_position_stopped.resize(aida_config->DSSDs());

    h2_AidaImplant_FRS_Z1Z2gate_strip_xy.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2gate_position.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2gate_position_stopped.resize(aida_config->DSSDs());

    h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2x2AoQgates_position.resize(aida_config->DSSDs());
    h1_AidaImplant_FRS_Z1Z2x2AoQgates_e.resize(aida_config->DSSDs());

    h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped.resize(aida_config->DSSDs());
    h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped.resize(aida_config->DSSDs());

    h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2x4AoQgates_position.resize(aida_config->DSSDs());
    h1_AidaImplant_FRS_Z1Z2x4AoQgates_e.resize(aida_config->DSSDs());

    h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped.resize(aida_config->DSSDs());
    h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped.resize(aida_config->DSSDs());
    h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped.resize(aida_config->DSSDs());

    for (int dssd = 0; dssd < aida_config->DSSDs(); dssd++)
    {
        if (!FrsGates.empty())
        {
            h2_AidaImplant_FRS_ZAoQgate_strip_xy[dssd].resize(FrsGates.size());
            h1_AidaImplant_FRS_ZAoQgate_e[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_ZAoQgate_position[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[dssd].resize(FrsGates.size());
            h1_AidaImplant_FRS_ZAoQgate_e_stopped[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_ZAoQgate_position_stopped[dssd].resize(FrsGates.size());

            h2_AidaImplant_FRS_Z1Z2gate_strip_xy[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2gate_position[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2gate_position_stopped[dssd].resize(FrsGates.size());

            h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[dssd].resize(FrsGates.size());
            h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[dssd].resize(FrsGates.size());

            h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[dssd].resize(FrsGates.size());
            h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[dssd].resize(FrsGates.size());

            h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[dssd].resize(FrsGates.size());
            h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[dssd].resize(FrsGates.size());

            h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[dssd].resize(FrsGates.size());
            h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[dssd].resize(FrsGates.size());
            h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[dssd].resize(FrsGates.size());
            
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {
                dir_implant_corrs_ZvsAoQ->cd();
                h2_AidaImplant_FRS_ZAoQgate_strip_xy[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_ZAoQgate%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS ZAoQ Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h1_AidaImplant_FRS_ZAoQgate_e[dssd][gate] = new TH1I(Form("h1_AidaImplant_FRS_ZAoQgate%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS ZAoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
                h2_AidaImplant_FRS_ZAoQgate_position[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_ZAoQgate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS ZAoQ Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);

                // ----- STOPPED -------
                dir_implant_corrs_ZvsAoQ_stopped->cd();
                h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_ZAoQgate%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS ZAoQ Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h1_AidaImplant_FRS_ZAoQgate_e_stopped[dssd][gate] = new TH1I(Form("h1_AidaImplant_FRS_ZAoQgate%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS ZAoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
                h2_AidaImplant_FRS_ZAoQgate_position_stopped[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_ZAoQgate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS ZAoQ Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);
            
                dir_implant_corrs_Z1vsZ2->cd();
                h2_AidaImplant_FRS_Z1Z2gate_strip_xy[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2gate%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Z2 Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h2_AidaImplant_FRS_Z1Z2gate_position[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2gate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Z2 Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);

                // ------- STOPPED --------------
                dir_implant_corrs_Z1vsZ2_stopped->cd();
                h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2gate%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Z2 Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);            
                h2_AidaImplant_FRS_Z1Z2gate_position_stopped[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2gate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Z2 Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);        

                // Second gate x2vsAoQ
                dir_implant_corrs_Z1Z2_x2vsAoQ->cd();
                h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);
                h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[dssd][gate] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x2AoQgates%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);

                // ------------- STOPPED ----------------
                dir_implant_corrs_Z1Z2_x2vsAoQ_stopped->cd();
                h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);
                h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[dssd][gate] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x2AoQgates%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);

                // Second gate x4vsAoQ
                dir_implant_corrs_Z1Z2_x4vsAoQ->cd();
                h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);
                h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[dssd][gate] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x4AoQgates%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);

                dir_implant_corrs_Z1Z2_x4vsAoQ_stopped->cd();
                h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[dssd][gate] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), xstrips, 0, xstrips, 128, 0, 128);
                h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[dssd][gate] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), xstrips, -xmax, xmax, 128, -37.8, 37.8);
                h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[dssd][gate] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x4AoQgates%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
            }
        }
    }

    dir_frs->cd();

    return kSUCCESS;

}


void FrsAidaCorrelations::Exec(Option_t* option)
{ 
    if (fAidaImplants->size() <= 0 || hitArrayFrs->size() <= 0) return;

    const auto & hitItemFrs = hitArrayFrs->at(0);

    for (auto & i : *fAidaImplants)
    {
        AidaHit hit = i;
        if (hit.Time > 0)
        {
            if (AidaLastWR == 0)
            {
                AidaLastWR = hit.Time;
            }
            else
            {
                h1_AidaImplant_Deadtime->Fill((hit.Time - AidaLastWR) / 1000);
                AidaLastWR = hit.Time;
            }
        } // aida implant deadtime
                
        if (hit.Time > 0 && hitItemFrs.Get_wr_t() > 0) h1_AidaImplant_FRS_dT->Fill(hit.Time - hitItemFrs.Get_wr_t());

        if (hit.Time - hitItemFrs.Get_wr_t() > Correl["FRS-AIDA WR Gate"][0] && hit.Time - hitItemFrs.Get_wr_t() < Correl["FRS-AIDA WR Gate"][1])
        {
            h2_AidaImplant_FRS_x_vs_x4->Fill(hit.PosX, hitItemFrs.Get_ID_x4());

            if (!FrsGates.empty())
            {
                for (int gate = 0; gate < FrsGates.size(); gate++)
                {
                    if (FrsGates[gate]->Passed_ZvsAoQ(hitItemFrs.Get_ID_z(), hitItemFrs.Get_ID_AoQ()))
                    {
                        h2_AidaImplant_FRS_ZAoQgate_strip_xy[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                        h1_AidaImplant_FRS_ZAoQgate_e[hit.DSSD-1][gate]->Fill(hit.Energy);
                        h2_AidaImplant_FRS_ZAoQgate_position[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                    } // Z vs AoQ pass

                    if (FrsGates[gate]->Passed_ZvsZ2(hitItemFrs.Get_ID_z(), hitItemFrs.Get_ID_z2()))
                    {
                        h2_AidaImplant_FRS_Z1Z2gate_strip_xy[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                        h2_AidaImplant_FRS_Z1Z2gate_position[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                        
                        if (FrsGates[gate]->Passed_x2vsAoQ(hitItemFrs.Get_ID_x2(), hitItemFrs.Get_ID_AoQ()))
                        {
                            h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                            h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                            h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[hit.DSSD-1][gate]->Fill(hit.Energy);
                        } // x2 vs AoQ pass

                        if (FrsGates[gate]->Passed_x4vsAoQ(hitItemFrs.Get_ID_x4(), hitItemFrs.Get_ID_AoQ()))
                        {
                            h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                            h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                            h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[hit.DSSD-1][gate]->Fill(hit.Energy);
                        } // x4 vs AoQ pass
                    } // Z vs Z2 pass
                } // gate loop
            } // gate is not null

            if (hit.Stopped)
            {
                if (!FrsGates.empty())
                {
                    for (int gate = 0; gate < FrsGates.size(); gate++)
                    {
                        if (FrsGates[gate]->Passed_ZvsAoQ(hitItemFrs.Get_ID_z(), hitItemFrs.Get_ID_AoQ()))
                        {
                            h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                            h1_AidaImplant_FRS_ZAoQgate_e_stopped[hit.DSSD-1][gate]->Fill(hit.Energy);
                            h2_AidaImplant_FRS_ZAoQgate_position_stopped[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                        } // Z vs AoQ pass

                        if (FrsGates[gate]->Passed_ZvsZ2(hitItemFrs.Get_ID_z(), hitItemFrs.Get_ID_z2()))
                        {
                            h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                            h2_AidaImplant_FRS_Z1Z2gate_position_stopped[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);

                            if (FrsGates[gate]->Passed_x2vsAoQ(hitItemFrs.Get_ID_x2(), hitItemFrs.Get_ID_AoQ()))
                            {
                                h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                                h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[hit.DSSD-1][gate]->Fill(hit.Energy);
                                h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                            } // x2 vs AoQ pass

                            if (FrsGates[gate]->Passed_x4vsAoQ(hitItemFrs.Get_ID_x4(), hitItemFrs.Get_ID_AoQ()))
                            {
                                h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[hit.DSSD-1][gate]->Fill(hit.StripX, hit.StripY);
                                h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[hit.DSSD-1][gate]->Fill(hit.Energy);
                                h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[hit.DSSD-1][gate]->Fill(hit.PosX, hit.PosY);
                            } // x4 vs AoQ pass
                        } // Z vs Z2 pass
                    } // gate loop
                } // Z vs AoQ gate is not null
            } // Stopped
        } // FRS-AIDA WR Gate
    } // Aida Implants

    fNEvents++;
}

void FrsAidaCorrelations::FinishEvent()
{

}

void FrsAidaCorrelations::FinishTask()
{
    if (found_dir_frs == false && FairRunOnline::Instance() == NULL)
    {
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs->Write();
        gDirectory = tmp;
        c4LOG(info, "Written FRS-AIDA Correlations histograms to file.");
    }
}


ClassImp(FrsAidaCorrelations)
