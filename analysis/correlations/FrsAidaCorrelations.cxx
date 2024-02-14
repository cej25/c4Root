#include "FairRootManager.h"
#include "FairTask.h"

#include "FrsAidaCorrelations.h"
#include "FrsHitData.h"
#include "FrsAnalysisData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"
#include "c4Logger.h"
#include "../../config/frs_config.h"

#include <vector>

FrsAidaCorrelations::FrsAidaCorrelations()
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysisData"))
    ,   fAidaImplants(new std::vector<AidaHit>)
    ,   fFrsAidaCorrelation(new TClonesArray("FrsAidaCorrelationData"))
{
}

FrsAidaCorrelations::FrsAidaCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysisData"))
    ,   fAidaImplants(new std::vector<AidaHit>)
    ,   fFrsAidaCorrelation(new TClonesArray("FrsAidaCorrelationData"))
{

}

FrsAidaCorrelations::~FrsAidaCorrelations()
{
    c4LOG(info, "Deleting FrsAidaCorrelations task.");
    if (fFrsHitArray) delete fFrsHitArray;
}

InitStatus FrsAidaCorrelations::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fFrsHitArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fFrsHitArray, "FrsHitData branch not found!");

    fFrsAnalysisArray = (TClonesArray*)mgr->GetObject("FrsAnalysisData");
    c4LOG_IF(fatal, !fFrsAnalysisArray, "FrsAnalysisData branch not found!");

    /*fAidaHitArray = (TClonesArray*)mgr->GetObject("AidaHitData");
    c4LOG_IF(fatal, !fAidaHitArray, "FrsHitData branch not found!");*/

    fAidaImplants = (std::vector<AidaHit>*)mgr->GetObject("AidaImplantHits");
    c4LOG_IF(fatal, !fAidaImplants, "AidaImplantHits branch not found!");

    mgr->Register("FrsAidaCorrelationData", "FRS-AIDA Correlation Data", fFrsAidaCorrelation, !fOnline);


    // clear stuff


    // histograms
    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

    //hAida_Implant_deadtime
    h1_AidaImplant_Deadtime = new TH1I("h1_Aida_Implant_Deadtime", "Dead Time AIDA Implant", 500, 0, 500);
    //hA_Imp_FRS_dT
    h1_AidaImplant_FRS_dT = new TH1I("h1_AidaImplant_FRS_dT", "White Rabbit Aida Implant-FRS", 16000, -40000, 40000);
    //hAIDA_FRS_x_vs_x4
    h2_AidaImplant_FRS_x_vs_x4 = new TH2F("h1_AidaImplant_FRS_x_vs_x4", "AIDA X position vs FRS ID_x4 position", 200, -20, 20, 200, -20, 20);

    for (int dssd = 0; dssd < conf->DSSDs(); dssd++)
    {
        for (int gate = 0; gate < FRS_GATES; gate++)
        {
            //hA_FRS_ZAoQ_implants_strip_xy
            h2_AidaImplant_FRS_ZAoQgate_strip_xy[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_ZAoQgate%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS ZAoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_ZAoQ_implants_e
            h1_AidaImplant_FRS_ZAoQgate_e[gate][dssd] = new TH1I(Form("h1_AidaImplant_FRS_ZAoQgate%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS ZAoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
            //hA_FRS_ZAoQ_implants_position
            h2_AidaImplant_FRS_ZAoQgate_position[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_ZAoQgate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS ZAoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_implants_strip_xy
            h2_AidaImplant_FRS_Z1Z2gate_strip_xy[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2gate%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_Z1Z2_implants_position
            h2_AidaImplant_FRS_Z1Z2gate_position[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2gate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_x2AoQ_implants_strip_xy
            h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_Z1Z2_x2AoQ_implants_position
            h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_x2AoQ_implants_e
            h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[gate][dssd] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x2AoQgates%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
            //hA_FRS_Z1Z2_x4AoQ_implants_strip_xy
            h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_Z1Z2_x4AoQ_implants_position
            h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_x4AoQ_implants_e
            h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[gate][dssd] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x4AoQgates%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);

            // ----- same again but stopped ---

            //hA_FRS_ZAoQ_implants_strip_xy
            h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_ZAoQgate%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS ZAoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_ZAoQ_implants_e
            h1_AidaImplant_FRS_ZAoQgate_e_stopped[gate][dssd] = new TH1I(Form("h1_AidaImplant_FRS_ZAoQgate%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS ZAoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
            //hA_FRS_ZAoQ_implants_position
            h2_AidaImplant_FRS_ZAoQgate_position_stopped[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_ZAoQgate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS ZAoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_implants_strip_xy
            h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2gate%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_Z1Z2_implants_position
            h2_AidaImplant_FRS_Z1Z2gate_position_stopped[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2gate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_x2AoQ_implants_strip_xy
            h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_Z1Z2_x2AoQ_implants_position
            h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_x2AoQ_implants_e
            h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[gate][dssd] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x2AoQgates%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);
            //hA_FRS_Z1Z2_x4AoQ_implants_strip_xy
            h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[gate][dssd] = new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128);
            //hA_FRS_Z1Z2_x4AoQ_implants_position
            h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[gate][dssd] = new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8);
            //hA_FRS_Z1Z2_x4AoQ_implants_e
            h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[gate][dssd] = new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x4AoQgates%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000);


        }
    }


    return kSUCCESS;


}


void FrsAidaCorrelations::Exec(Option_t* option)
{ 
    int multFRS = 0;
    int multAIDA = 0;

    if (multFRS == 0 || multAIDA == 0) return;

    if (fFrsHitArray && fFrsHitArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsHitArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FrsHitData* FrsHit = (FrsHitData*)fFrsHitArray->At(ihit);
            FrsAnalysisData* FrsAnalysisHit = (FrsAnalysisData*)fFrsAnalysisArray->At(ihit);
            if (!FrsHit) continue;
            if (!FrsAnalysisHit) continue;

            TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

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
                
                if (hit.Time > 0 && FrsHit->Get_WR() > 0) h1_AidaImplant_FRS_dT->Fill(hit.Time - FrsHit->Get_WR());

                if (hit.Time - FrsHit->Get_WR() > FRS_AIDA_WR_GATE_LOW && hit.Time - FrsHit->Get_WR() < FRS_AIDA_WR_GATE_HIGH)
                {
                    h2_AidaImplant_FRS_x_vs_x4->Fill(hit.PosX, FrsHit->Get_ID_x4());

                    for (int gate = 0; gate < FRS_GATES; gate++)
                    {

                        if (FrsAnalysisHit->Get_ZvsAoQ_gate(gate) == true)
                        {
                            h2_AidaImplant_FRS_ZAoQgate_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                            h1_AidaImplant_FRS_ZAoQgate_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                            h2_AidaImplant_FRS_ZAoQgate_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                        } // Z vs AoQ pass

                        if (FrsAnalysisHit->Get_ZvsZ2_gate(gate) == true)
                        {
                            h2_AidaImplant_FRS_Z1Z2gate_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                            h2_AidaImplant_FRS_Z1Z2gate_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);

                            if (FrsAnalysisHit->Get_x2vsAoQ_gate(gate) == true)
                            {
                                h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                            } // x2 vs AoQ pass

                            if (FrsAnalysisHit->Get_x4vsAoQ_gate(gate) == true)
                            {
                                h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                            } // x4 vs AoQ pass

                        } // Z vs Z2 pass

                        if (hit.Stopped)
                        {
                            if (FrsAnalysisHit->Get_ZvsAoQ_gate(gate) == true)
                            {
                                h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                h1_AidaImplant_FRS_ZAoQgate_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                h2_AidaImplant_FRS_ZAoQgate_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                            } // Z vs AoQ pass

                            if (FrsAnalysisHit->Get_ZvsZ2_gate(gate) == true)
                            {
                                h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                h2_AidaImplant_FRS_Z1Z2gate_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);

                                if (FrsAnalysisHit->Get_x2vsAoQ_gate(gate) == true)
                                {
                                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                    h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                } // x2 vs AoQ pass

                                if (FrsAnalysisHit->Get_x4vsAoQ_gate(gate) == true)
                                {
                                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                    h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                } // x4 vs AoQ pass
                            } // Z vs Z2 pass
                        } // Stopped
                    } // FRS Gates
                } // FRS-AIDA WR Gate
            } // Aida Implants
        } // nHits
    } // GetEntries() > 0
}

void FrsAidaCorrelations::FinishEvent()
{

}

void FrsAidaCorrelations::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
}


ClassImp(FrsAidaCorrelations)