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
 *                              C.E. Jones                                    *
 *                               06.05.25                                     *
 ******************************************************************************/

// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "c4Logger.h"
#include "TClonesArray.h"
#include <chrono>

#include "H10MCPCal2Ana.h"

/*
empty constructor required for FairRoot.
*/
H10MCPCal2Ana::H10MCPCal2Ana()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fcal_data(new TClonesArray("H10MCPTwinpeaksCalData"))
    ,   fana_data(new TClonesArray("H10MCPTwinpeaksAnaData"))
{

}

/*
Named constructor with verbosity level.
*/
H10MCPCal2Ana::H10MCPCal2Ana(const TString& name, Int_t verbose) 
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fcal_data(new TClonesArray("H10MCPTwinpeaksCalData"))
    ,   fana_data(new TClonesArray("H10MCPTwinpeaksAnaData"))
{

}
/*
Clearing old constructed objects.
*/
H10MCPCal2Ana::~H10MCPCal2Ana()
{
    c4LOG(info, "Deleting H10MCPCal2Ana task");
}


/*
Initializer called by the FairRoot manager. Gets the required FairRootManager objects to read and register the data to be written to the tree.
*/
InitStatus H10MCPCal2Ana::Init()
{  
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fcal_data = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fcal_data, "Fatima branch of H10MCPTwinpeaksCalData not found.");
    
    //need to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("H10MCPTwinpeaksAnaData", "H10MCPTwinpeaksAnaDataFolder", fana_data, !fOnline);

    fcal_data->Clear();
    fana_data->Clear();

    return kSUCCESS;
};
       

void H10MCPCal2Ana::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    if (fcal_data && fcal_data->GetEntriesFast() > 0)
    {
        fNEvents++;
        Int_t event_multiplicity = fcal_data->GetEntriesFast();

        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {
            H10MCPTwinpeaksCalData* hit = (H10MCPTwinpeaksCalData*)fcal_data->At(ihit);
            
            absolute_event_time = hit->Get_absolute_event_time();
            wr_t = hit->Get_wr_t();
            Int_t mcp_id = hit->Get_mcp_id();
            Int_t type = hit->Get_type();
            Int_t number = hit->Get_number();

            //std::cout << "reading event in cal2ana::  " << " mpc:: " << mcp_id << " type :: " << type << " number:: " << number << std::endl;

            if (mcp_id == 0 && type == 0 && number == 0) 
            { 
                if (t1_seen) { t1_discard++; continue; }
                else { T1 = hit->Get_fast_lead_time(); t1_seen = true; }
            }
            if (mcp_id == 0 && type == 1 && number == 0) 
            { 
                if (x11_seen) { x11_discard++; continue; }
                else { X11 = hit->Get_fast_lead_time(); x11_seen = true; }
            }
            if (mcp_id == 0 && type == 1 && number == 1) 
            { 
                if (x12_seen) { x12_discard++; continue; }
                else { X12 = hit->Get_fast_lead_time(); x12_seen = true; }
            }
            if (mcp_id == 0 && type == 2 && number == 0) 
            { 
                if (y11_seen) { y11_discard++; continue; }
                else { Y11 = hit->Get_fast_lead_time(); y11_seen = true; }
            }
            if (mcp_id == 0 && type == 2 && number == 1) 
            { 
                if (y12_seen) { y12_discard++; continue; }
                else { Y12 = hit->Get_fast_lead_time(); y12_seen = true; } 
            }

            if (mcp_id == 1 && type == 0 && number == 0) 
            { 
                if (t2_seen) { t2_discard++; continue; }
                else { T2 = hit->Get_fast_lead_time(); t2_seen = true; }
            }
            if (mcp_id == 1 && type == 1 && number == 0) 
            { 
                if (x21_seen) { x21_discard++; continue; }
                else { X21 = hit->Get_fast_lead_time(); x21_seen = true; }
            }
            if (mcp_id == 1 && type == 1 && number == 1) 
            { 
                if (x22_seen) { x22_discard++; continue; }
                else { X22 = hit->Get_fast_lead_time(); x22_seen = true; }
            }
            if (mcp_id == 1 && type == 2 && number == 0) 
            { 
                if (y21_seen) { y21_discard++; continue; }
                else { Y21 = hit->Get_fast_lead_time(); y21_seen = true; }
            }
            if (mcp_id == 1 && type == 2 && number == 1) 
            { 
                if (y22_seen) { y22_discard++; continue; }
                else { Y22 = hit->Get_fast_lead_time(); y22_seen = true; }
            }
            if (mcp_id == 0 && type == 3 && number == 0)
            {
                if (sc41l_seen) { sc41l_discard++; continue; }
                else { SC41L = hit->Get_fast_lead_time(); sc41l_seen = true; }
            }
            if (mcp_id == 0 && type == 3 && number == 1)
            {
                if (sc41r_seen) { sc41r_discard++; continue; }
                else { SC41R = hit->Get_fast_lead_time(); sc41r_seen = true; }
            }
            if (mcp_id == 0 && type == 4 && number == 0)
            {
                if (sc42l_seen) { sc42l_discard++; continue; }
                else { SC42L = hit->Get_fast_lead_time(); sc42l_seen = true; }
            }
            if (mcp_id == 0 && type == 4 && number == 1)
            {
                if (sc42r_seen) { sc42r_discard++; continue; }
                else { SC42R = hit->Get_fast_lead_time(); sc42r_seen = true; }
            }
            if (mcp_id == 0 && type == 5 && number == 0)
            {
                if (dssdaccept_seen) { dssdaccept_discard++; continue; }
                else { DSSDAccept = hit->Get_fast_lead_time(); dssdaccept_seen = true; }
            }
        
        }

        if (t1_seen && x11_seen && x12_seen && y11_seen && y12_seen) mcp1_complete = true;
        if (t2_seen && x21_seen && x22_seen && y21_seen && y22_seen) mcp2_complete = true;
        if (mcp1_complete && mcp2_complete) { full_event = true; full_event_counter++; }

        if (sc41l_seen && sc41r_seen) SC41 = (SC41L + SC41R) / 2;
        if (sc42l_seen && sc42r_seen) SC42 = (SC42L + SC42R) / 2;

        new ((*fana_data)[fana_data->GetEntriesFast()]) H10MCPTwinpeaksAnaData(
                absolute_event_time,
                wr_t,
                full_event,
                mcp1_complete,
                mcp2_complete,
                T1,
                X11,
                X12,
                Y11,
                Y12,
                T2,
                X21,
                X22,
                Y21,
                Y22,
                SC41,
                SC42,
                DSSDAccept);
    }

    fExecs++;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();

}


void H10MCPCal2Ana::FinishEvent()
{
    // reset output array
    fana_data->Clear();
    t1_seen = false; 
    x11_seen = false;
    x12_seen = false;
    y11_seen = false;
    y12_seen = false;
    t2_seen = false; 
    x21_seen = false;
    x22_seen = false;
    y21_seen = false;
    y22_seen = false;
    full_event = false;
    mcp1_complete = false;
    mcp2_complete = false;
    sc41l_seen = false;
    sc41r_seen = false;
    sc42l_seen = false;
    sc42r_seen = false;
    dssdaccept_seen = false;
    T1 = 0;
    X11 = 0;
    X12 = 0;
    Y11 = 0;
    Y12 = 0;
    T2 = 0;
    X21 = 0;
    X22 = 0;
    Y21 = 0;
    Y22 = 0;
    SC41L = 0;
    SC41R = 0;
    SC42L = 0;
    SC42R = 0;
    DSSDAccept = 0;

};

/*
Some stats are written when finishing.
*/
void H10MCPCal2Ana::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
    c4LOG(info, "Full events: " << full_event_counter);
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}


ClassImp(H10MCPCal2Ana)
