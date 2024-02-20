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

FrsAidaCorrelations::FrsAidaCorrelations(std::vector<std::vector<TCutG*>> fFrsGates)
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fAidaImplants(new std::vector<AidaHit>)
{
    // CEJ: this can be done more cleanly with a lookup map ikik
    // also need to work out nullptr check
    for (auto & GateType : fFrsGates)
    {
        if (strcmp(GateType[0]->GetVarX(), "AoQ") == 0)
        {
            if (strcmp(GateType[0]->GetVarY(), "Z") == 0)
            {
                cutID_Z_AoQ = GateType;
            }
            else if (strcmp(GateType[0]->GetVarY(), "x2") == 0)
            {
                cutID_x2AoQ = GateType;
            }
            else if (strcmp(GateType[0]->GetVarY(), "x4") == 0)
            {
                cutID_x4AoQ = GateType;
            }
        }
        else if (strcmp(GateType[0]->GetVarX(), "Z") == 0)
        {
            if (strcmp(GateType[0]->GetVarY(), "dEdeg") == 0)
            {
                cutID_dEdegZ = GateType;
            }
        }
        else if (strcmp(GateType[0]->GetVarX(), "Z1") == 0)
        {
            if (strcmp(GateType[0]->GetVarY(), "Z2") == 0)
            {
                cutID_Z_Z2 = GateType;
            }
        }
    }
}

FrsAidaCorrelations::FrsAidaCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fAidaImplants(new std::vector<AidaHit>)
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

    fAidaImplants = mgr->InitObjectAs<decltype(fAidaImplants)>("AidaImplantHits");
    c4LOG_IF(fatal, !fAidaImplants, "Branch AidaImplantHits not found!");

    // clear stuff

    frs_correlations = new TFolder("FRS_Correlations", "FRS_Correlations");
    frs_aida_correlations = new TFolder("FRS-AIDA_Correlations", "FRS_AIDA_Correlations");
    frs_correlations->Add(frs_aida_correlations);
    frs_implant_correlations = new TFolder("FRS-Implant_Corr", "FRS-Implant_Corr");
    frs_stopped_implant_correlations = new TFolder("Stopped_FRS-Implant_Corr", "Stopped_FRS-Implant_Corr");
    frs_aida_correlations->Add(frs_implant_correlations);
    frs_aida_correlations->Add(frs_stopped_implant_correlations);
    frs_implant_correlations_ZvsAoQ = new TFolder("ZvsAoQ-gated_FRS-Implant_Corr", "ZvsAoQ-gated_FRS-Implant_Corr");
    frs_implant_correlations_Z1vsZ2 = new TFolder("Z1vsZ2-gated_FRS-Implant_Corr", "Z1vsZ2-gated_FRS-Implant_Corr");
    //frs_implant_correlations_x2vsAoQ = new TFolder("x2vsAoQ-gated_FRS-Implant_Corr", "x2vsAoQ-gated_FRS-Implant_Corr");
    //frs_implant_correlations_x4vsAoQ = new TFolder("x4vsAoQ-gated_FRS-Implant_Corr", "x4vsAoQ-gated_FRS-Implant_Corr");
    frs_implant_correlations_ZvsAoQ_stopped = new TFolder("Stopped_ZvsAoQ-gated_FRS-Implant_Corr", "Stopped_ZvsAoQ-gated_FRS-Implant_Corr");
    frs_implant_correlations_Z1vsZ2_stopped = new TFolder("Stopped_Z1vsZ2-gated_FRS-Implant_Corr", "Stopped_Z1vsZ2-gated_FRS-Implant_Corr");
    //frs_implant_correlations_x2vsAoQ_stopped = new TFolder("Stopped_x2vsAoQ-gated_FRS-Implant_Corr", "Stopped_x2vsAoQ-gated_FRS-Implant_Corr");
    //frs_implant_correlations_x4vsAoQ_stopped = new TFolder("Stopped_x4vsAoQ-gated_FRS-Implant_Corr", "Stopped_x4vsAoQ-gated_FRS-Implant_Corr");
    frs_implant_correlations->Add(frs_implant_correlations_ZvsAoQ);
    frs_implant_correlations->Add(frs_implant_correlations_Z1vsZ2);
    //frs_implant_correlations->Add(frs_implant_correlations_x2vsAoQ);
    //frs_implant_correlations->Add(frs_implant_correlations_x4vsAoQ);
    frs_stopped_implant_correlations->Add(frs_implant_correlations_ZvsAoQ_stopped);
    frs_stopped_implant_correlations->Add(frs_implant_correlations_Z1vsZ2_stopped);
    //frs_stopped_implant_correlations->Add(frs_implant_correlations_x2vsAoQ_stopped);
    //frs_stopped_implant_correlations->Add(frs_implant_correlations_x4vsAoQ_stopped);
    frs_imp_corr_Z1Z2_x2vsAoQ = new TFolder("Z1Z2-x2vsAoQ-gated_FRS-Implant_Corr", "Z1Z2-x2vsAoQ-gated_FRS-Implant_Corr");
    frs_imp_corr_Z1Z2_x4vsAoQ = new TFolder("Z1Z2-x4vsAoQ-gated_FRS-Implant_Corr", "Z1Z2-x4vsAoQ-gated_FRS-Implant_Corr");
    frs_imp_corr_Z1Z2_x2vsAoQ_stopped = new TFolder("Stopped_Z1Z2-x2vsAoQ-gated_FRS-Implant_Corr", "Stopped_Z1Z2-x2vsAoQ-gated_FRS-Implant_Corr");
    frs_imp_corr_Z1Z2_x4vsAoQ_stopped = new TFolder("Stopped_Z1Z2-x4vsAoQ-gated_FRS-Implant_Corr", "Stopped_Z1Z2-x4vsAoQ-gated_FRS-Implant_Corr");
    frs_implant_correlations_Z1vsZ2->Add(frs_imp_corr_Z1Z2_x2vsAoQ);
    frs_implant_correlations_Z1vsZ2->Add(frs_imp_corr_Z1Z2_x4vsAoQ);
    frs_implant_correlations_Z1vsZ2_stopped->Add(frs_imp_corr_Z1Z2_x2vsAoQ_stopped);
    frs_implant_correlations_Z1vsZ2_stopped->Add(frs_imp_corr_Z1Z2_x4vsAoQ_stopped);

    // histograms
    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

    //hAida_Implant_deadtime
    h1_AidaImplant_Deadtime = new TH1I("h1_Aida_Implant_Deadtime", "Dead Time AIDA Implant", 500, 0, 500);
    frs_implant_correlations->Add(h1_AidaImplant_Deadtime);
    //hA_Imp_FRS_dT
    h1_AidaImplant_FRS_dT = new TH1I("h1_AidaImplant_FRS_dT", "White Rabbit Aida Implant-FRS", 16000, -40000, 40000);
    frs_implant_correlations->Add(h1_AidaImplant_FRS_dT);
    //hAIDA_FRS_x_vs_x4
    h2_AidaImplant_FRS_x_vs_x4 = new TH2F("h1_AidaImplant_FRS_x_vs_x4", "AIDA X position vs FRS ID_x4 position", 200, -20, 20, 200, -20, 20);
    frs_implant_correlations->Add(h2_AidaImplant_FRS_x_vs_x4);

    for (int dssd = 0; dssd < conf->DSSDs(); dssd++)
    {

        if (cutID_Z_AoQ[0] != nullptr)
        {
            for (int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
            {
                //hA_FRS_ZAoQ_implants_strip_xy
                h2_AidaImplant_FRS_ZAoQgate_strip_xy[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_ZAoQgate%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS ZAoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                frs_implant_correlations_ZvsAoQ->Add(h2_AidaImplant_FRS_ZAoQgate_strip_xy[dssd][gate]);
                //hA_FRS_ZAoQ_implants_e
                h1_AidaImplant_FRS_ZAoQgate_e[dssd].emplace_back(new TH1I(Form("h1_AidaImplant_FRS_ZAoQgate%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS ZAoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000));
                frs_implant_correlations_ZvsAoQ->Add(h1_AidaImplant_FRS_ZAoQgate_e[dssd][gate]);
                //hA_FRS_ZAoQ_implants_position
                h2_AidaImplant_FRS_ZAoQgate_position[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_ZAoQgate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS ZAoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                frs_implant_correlations_ZvsAoQ->Add(h2_AidaImplant_FRS_ZAoQgate_position[dssd][gate]);

                // ----- STOPPED -------
                //hA_FRS_ZAoQ_implants_strip_xy
                h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_ZAoQgate%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS ZAoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                frs_implant_correlations_ZvsAoQ_stopped->Add(h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[dssd][gate]);
                //hA_FRS_ZAoQ_implants_e
                h1_AidaImplant_FRS_ZAoQgate_e_stopped[dssd].emplace_back(new TH1I(Form("h1_AidaImplant_FRS_ZAoQgate%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS ZAoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000));
                frs_implant_correlations_ZvsAoQ_stopped->Add(h1_AidaImplant_FRS_ZAoQgate_e_stopped[dssd][gate]);
                //hA_FRS_ZAoQ_implants_position
                h2_AidaImplant_FRS_ZAoQgate_position_stopped[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_ZAoQgate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS ZAoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                frs_implant_correlations_ZvsAoQ_stopped->Add(h2_AidaImplant_FRS_ZAoQgate_position_stopped[dssd][gate]);
            }
        }

        if (cutID_Z_Z2[0] != nullptr)
        {
            for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
            {
                //hA_FRS_Z1Z2_implants_strip_xy
                h2_AidaImplant_FRS_Z1Z2gate_strip_xy[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_Z1Z2gate%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                frs_implant_correlations_Z1vsZ2->Add(h2_AidaImplant_FRS_Z1Z2gate_strip_xy[dssd][gate]);
                //hA_FRS_Z1Z2_implants_position
                h2_AidaImplant_FRS_Z1Z2gate_position[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_Z1Z2gate%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                frs_implant_correlations_Z1vsZ2->Add(h2_AidaImplant_FRS_Z1Z2gate_position[dssd][gate]);

                // ------- STOPPED --------------
                //hA_FRS_Z1Z2_implants_strip_xy
                h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_Z1Z2gate%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                frs_implant_correlations_Z1vsZ2_stopped->Add(h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[dssd][gate]);
                //hA_FRS_Z1Z2_implants_position
                h2_AidaImplant_FRS_Z1Z2gate_position_stopped[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_Z1Z2gate%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Z2 Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                frs_implant_correlations_Z1vsZ2_stopped->Add(h2_AidaImplant_FRS_Z1Z2gate_position_stopped[dssd][gate]);

                if (cutID_x2AoQ[0] != nullptr)
                {
                    //hA_FRS_Z1Z2_x2AoQ_implants_strip_xy
                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                    frs_imp_corr_Z1Z2_x2vsAoQ->Add(h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[dssd][gate]);
                    //hA_FRS_Z1Z2_x2AoQ_implants_position
                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                    frs_imp_corr_Z1Z2_x2vsAoQ->Add(h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[dssd][gate]);
                    //hA_FRS_Z1Z2_x2AoQ_implants_e
                    h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[dssd].emplace_back(new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x2AoQgates%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000));
                    frs_imp_corr_Z1Z2_x2vsAoQ->Add(h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[dssd][gate]);

                    // ------------- STOPPED ----------------
                    //hA_FRS_Z1Z2_x2AoQ_implants_strip_xy
                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                    frs_imp_corr_Z1Z2_x2vsAoQ_stopped->Add(h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[dssd][gate]);
                    //hA_FRS_Z1Z2_x2AoQ_implants_position
                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x2AoQgates%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                    frs_imp_corr_Z1Z2_x2vsAoQ_stopped->Add(h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[dssd][gate]);
                    //hA_FRS_Z1Z2_x2AoQ_implants_e
                    h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[dssd].emplace_back(new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x2AoQgates%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS Z1Zx2AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000));
                    frs_imp_corr_Z1Z2_x2vsAoQ_stopped->Add(h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[dssd][gate]);
                }

                if (cutID_x4AoQ[0] != nullptr)
                {
                    //hA_FRS_Z1Z2_x4AoQ_implants_strip_xy
                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_strip_xy_dssd%d", gate, dssd + 1), Form("DSSD %d Implant hit pattern FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                    frs_imp_corr_Z1Z2_x4vsAoQ->Add(h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[dssd][gate]);
                    //hA_FRS_Z1Z2_x4AoQ_implants_position
                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_position_dssd%d", gate, dssd + 1), Form("DSSD %d Implant position FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                    frs_imp_corr_Z1Z2_x4vsAoQ->Add(h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[dssd][gate]);
                    //hA_FRS_Z1Z2_x4AoQ_implants_e
                    h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[dssd].emplace_back(new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x4AoQgates%d_e_dssd%d", gate, dssd + 1), Form("DSSD %d Implant energy FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000));
                    frs_imp_corr_Z1Z2_x4vsAoQ->Add(h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[dssd][gate]);

                    // ---------- STOPPED
                    //hA_FRS_Z1Z2_x4AoQ_implants_strip_xy
                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[dssd].emplace_back(new TH2I(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_strip_xy_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) hit pattern FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, 0, 128, 128, 0, 128));
                    frs_imp_corr_Z1Z2_x4vsAoQ_stopped->Add(h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[dssd][gate]);
                    //hA_FRS_Z1Z2_x4AoQ_implants_position
                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[dssd].emplace_back(new TH2D(Form("h2_AidaImplant_FRS_Z1Z2x4AoQgates%d_position_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) position FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 128, -37.8, 37.8, 128, -37.8, 37.8));
                    frs_imp_corr_Z1Z2_x4vsAoQ_stopped->Add(h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[dssd][gate]);
                    //hA_FRS_Z1Z2_x4AoQ_implants_e
                    h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[dssd].emplace_back(new TH1I(Form("h1_AidaImplant_FRS_Z1Z2x4AoQgates%d_e_stopped_dssd%d", gate, dssd + 1), Form("DSSD %d Implant (stopped) energy FRS Z1Zx4AoQ Gate: %d", dssd + 1, gate), 1000, 0, 10000));
                    frs_imp_corr_Z1Z2_x4vsAoQ_stopped->Add(h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[dssd][gate]);
                }
            }
        }
    }


    return kSUCCESS;


}


void FrsAidaCorrelations::Exec(Option_t* option)
{ 
    int multFRS = 0;
    multFRS = fFrsHitArray->GetEntriesFast();
    if (multFRS == 0) return;

    if (fFrsHitArray && fFrsHitArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsHitArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FrsHitData* FrsHit = (FrsHitData*)fFrsHitArray->At(ihit);
            if (!FrsHit) continue;

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

                    if (cutID_Z_AoQ[0] != nullptr)
                    {
                        for (int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
                        {
                            if (cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                            {
                                h2_AidaImplant_FRS_ZAoQgate_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                h1_AidaImplant_FRS_ZAoQgate_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                h2_AidaImplant_FRS_ZAoQgate_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                            } // Z vs AoQ pass
                        } // gate loop
                    } // gate is not null

                    if (cutID_Z_Z2[0] != nullptr)
                    {
                        for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
                        {
                            if (cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {
                                h2_AidaImplant_FRS_Z1Z2gate_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                h2_AidaImplant_FRS_Z1Z2gate_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                
                                // CEJ: should we have a redundant check for x2AoQ gate != nullptr?
                                if (cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                                {
                                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                    h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                    h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                } // x2 vs AoQ pass

                                if (cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                                {
                                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                    h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                    h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                } // x4 vs AoQ pass

                            } // Z vs Z2 pass
                        } // Z vs Z2 gate loop
                    } // Z vs Z2 gate is not null

                    if (hit.Stopped)
                    {

                        if (cutID_Z_AoQ[0] != 0)
                        {
                            for (int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
                            {
                                if (cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                                {
                                    h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                    h1_AidaImplant_FRS_ZAoQgate_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                    h2_AidaImplant_FRS_ZAoQgate_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                } // Z vs AoQ pass
                            } // gate loop
                        } // Z vs AoQ gate is not null
                        
                        if (cutID_Z_Z2[0] != 0)
                        {
                            for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
                            {
                                if (cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                                {
                                    h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                    h2_AidaImplant_FRS_Z1Z2gate_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);

                                    // CEJ: again should we check for x2AoQ != nullptr? 
                                    if (cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                                    {
                                        h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                        h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                        h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                    } // x2 vs AoQ pass

                                    if (cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                                    {
                                        h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                                        h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                                        h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                    } // x4 vs AoQ pass
                                } // Z vs Z2 pass
                            } // Z vs Z2 gate loop
                        } // Z vs Z2 gate is not null

                    } // Stopped

                } // FRS-AIDA WR Gate
            } // Aida Implants
        } // nHits


        // CEJ: does anything need to be registered in the tree here?

        
    } // GetEntries() > 0

    fNEvents++; // ?? where do i iterate this?
}

void FrsAidaCorrelations::FinishEvent()
{

}

void FrsAidaCorrelations::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
    if (fFrsHitArray)
    {
        frs_correlations->Write();
    }
}


ClassImp(FrsAidaCorrelations)