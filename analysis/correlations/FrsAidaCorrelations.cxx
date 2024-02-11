#include "FrsAidaCorrelations.h"

#include "FrsHitData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"

#include <vector.h>

FrsAidaCorrelations::FrsAidaCorrelations()
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
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

    /*fAidaHitArray = (TClonesArray*)mgr->GetObject("AidaHitData");
    c4LOG_IF(fatal, !fAidaHitArray, "FrsHitData branch not found!");*/

    fAidaImplants = (TClonesArray*)mgr->GetObject("AidaImplantHits");
    c4LOG_IF(fatal, !fAidaImplants, "AidaImplantHits branch not found!");

    mgr->Register("FrsAidaCorrelationData", "FRS-AIDA Correlation Data", fFrsAidaCorrelation, !fOnline);


    // clear stuff


    // set up histograms?

    return kSUCCESS;


}


void FrsAidaCorrelations::Exec(Option_t* option)
{ 
    int multFRS = 0;
    int multAIDA = 0;

    if (multFRS == 0 || multAIDA == 0) return;

    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

    for (auto & i : fAidaImplants)
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
                hAida_Implant_deadtime->Fill((long long)(hit.Time - lastAIDAWR) / 1000);
                AidaLastWR = hit.Time;
            }
        } // aida implant deadtime
        
        if (hit.Time > 0 && fFrsHitArray->Get_WR() > 0) hA_Imp_FRS_dT->Fill(hit.Time - fFrsHitArray->Get_WR());

        if (hit.Time - fFrsHitArray->Get_WR() > FRS_AIDA_WR_GATE_LOW && hit.Time - fFrsHitArray->Get_WR() < FRS_AIDA_WR_GATE_HIGH)
        {
            hAIDA_FRS_x_vs_x4->Fill(hit.PosX, fFrsHitArray->Get_ID_x4());

            for (int gate = 0; gate < FRS_GATES; gate++)
            {

                if (fFrsHitArray->Get_ZvsAoQ_gates(gate) == true)
                {
                    hA_FRS_ZAoQ_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                    hA_FRS_ZAoQ_implants_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                    hA_FRS_ZAoQ_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                } // Z vs AoQ pass

                if (fFrsHitArray->Get_ZvsZ2_gates(gate) == true)
                {
                    hA_FRS_Z1Z2_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                    hA_FRS_Z1Z2_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);

                    if (fFrsHitArray->Get_x2vsAoQ_gates(gate) == true)
                    {
                        hA_FRS_Z1Z2_x2AoQ_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                        hA_FRS_Z1Z2_x2AoQ_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                        hA_FRS_Z1Z2_x2AoQ_implants_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                    } // x2 vs AoQ pass

                    if (fFrsHitArray->Get_x4vsAoQ_gates(gate) == true)
                    {
                        hA_FRS_Z1Z2_x4AoQ_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                        hA_FRS_Z1Z2_x4AoQ_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                        hA_FRS_Z1Z2_x4AoQ_implants_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
                    } // x4 vs AoQ pass

                } // Z vs Z2 pass

                if (hit.Stopped)
                {
                    if (fFrsHitArray->Get_ZvsAoQ_gates(gate) == true)
                    {
                        hA_FRS_ZAoQ_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                        hA_FRS_ZAoQ_implants_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                        hA_FRS_ZAoQ_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                    } // Z vs AoQ pass

                    if (fFrsHitArray->Get_ZvsZ2_gates(gate) == true)
                    {
                        hA_FRS_Z1Z2_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                        hA_FRS_Z1Z2_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);

                        if (fFrsHitArray->Get_x2vsAoQ_gates(gate) == true)
                        {
                            hA_FRS_Z1Z2_x2AoQ_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                            hA_FRS_Z1Z2_x2AoQ_implants_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                            hA_FRS_Z1Z2_x2AoQ_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                        } // x2 vs AoQ pass

                        if (fFrsHitArray->Get_x4vsAoQ_gates(gate) == true)
                        {
                            hA_FRS_Z1Z2_x4AoQ_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
                            hA_FRS_Z1Z2_x4AoQ_implants_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
                            hA_FRS_Z1Z2_x4AoQ_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                        } // x4 vs AoQ pass
                    } // Z vs Z2 pass
                } // Stopped
            } // FRS Gates
        } // FRS-AIDA WR Gate
    }
}

void FrsAidaCorrelations::FinishEvent()
{

}

void FrsAidaCorrelations::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
}


ClassImp(FrsAidaCorrelations)