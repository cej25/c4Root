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
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "v1751TraceReader.h"
#include "v1751TraceData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_vme.h"
}

v1751TraceReader::v1751TraceReader(EXT_STR_h101_vme_onion* data, size_t offset)
    : c4Reader("v1751TraceReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("v1751TraceData"))
{
}

v1751TraceReader::~v1751TraceReader() { 
    delete fArray;

}

Bool_t v1751TraceReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_vme_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_vme, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("v1751TraceData", "Germanium Febex Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}


Bool_t v1751TraceReader::Read()
{
    c4LOG(debug1, "Event Data");

    if(!fData) return kTRUE;

    uint32_t board_id = fData->vme_v1751_board_id;
    
    uint32_t* vme_v1751_channels[] = {
        &fData->vme_v1751_channels1, &fData->vme_v1751_channels2, &fData->vme_v1751_channels3, &fData->vme_v1751_channels4,
        &fData->vme_v1751_channels5, &fData->vme_v1751_channels6, &fData->vme_v1751_channels7, &fData->vme_v1751_channels8
    };

    uint32_t* vme_v1751_nsamples[] = {
        &fData->vme_v1751_nsamples_trace1, &fData->vme_v1751_nsamples_trace2, &fData->vme_v1751_nsamples_trace3, &fData->vme_v1751_nsamples_trace4,
        &fData->vme_v1751_nsamples_trace5, &fData->vme_v1751_nsamples_trace6, &fData->vme_v1751_nsamples_trace7, &fData->vme_v1751_nsamples_trace8
    };

    uint32_t* vme_v1751_trigger_time[] = {
        &fData->vme_v1751_trigger_time1, &fData->vme_v1751_trigger_time2, &fData->vme_v1751_trigger_time3, &fData->vme_v1751_trigger_time4,
        &fData->vme_v1751_trigger_time5, &fData->vme_v1751_trigger_time6, &fData->vme_v1751_trigger_time7, &fData->vme_v1751_trigger_time8
    };

    uint32_t* vme_v1751_sample_trace[] = {
        &fData->vme_v1751_sample_trace1, &fData->vme_v1751_sample_trace2, &fData->vme_v1751_sample_trace3, &fData->vme_v1751_sample_trace4,
        &fData->vme_v1751_sample_trace5, &fData->vme_v1751_sample_trace6, &fData->vme_v1751_sample_trace7, &fData->vme_v1751_sample_trace8
    };

    uint32_t (*vme_v1751_sample_traceI[8])[2000] = {
        &fData->vme_v1751_sample_trace1I, &fData->vme_v1751_sample_trace2I, &fData->vme_v1751_sample_trace3I, &fData->vme_v1751_sample_trace4I,
        &fData->vme_v1751_sample_trace5I, &fData->vme_v1751_sample_trace6I, &fData->vme_v1751_sample_trace7I, &fData->vme_v1751_sample_trace8I
    };

    uint32_t (*vme_v1751_sample_traceV[8])[2000] = {
        &fData->vme_v1751_sample_trace1v, &fData->vme_v1751_sample_trace2v, &fData->vme_v1751_sample_trace3v, &fData->vme_v1751_sample_trace4v,
        &fData->vme_v1751_sample_trace5v, &fData->vme_v1751_sample_trace6v, &fData->vme_v1751_sample_trace7v, &fData->vme_v1751_sample_trace8v
    };

    int nfired_ch = 0;
    for (int ich = 0; ich < 8; ich++) {
        if (*vme_v1751_channels[ich] != 0) nfired_ch++; 
    }

    for (int ich = 0; ich<8; ich++){
        if (*vme_v1751_channels[ich] == 0) continue; // not fired, skip.
        //c4LOG(info,ich);
        v1751TraceData * event = new v1751TraceData(nfired_ch,board_id,ich,0,0);
        event->Set_length(*vme_v1751_sample_trace[ich]);
        for (int it = 0; it<*vme_v1751_sample_trace[ich];it++){
            event->Set_trace_val((uint16_t)((*vme_v1751_sample_traceV[ich])[it]), it);
        }
        new ((*fArray)[fArray->GetEntriesFast()]) v1751TraceData(*event);
    }


    fNEvent += 1;
    return kTRUE;
}



void v1751TraceReader::Reset()
{
    // reset output array
    fArray->Clear();
}



ClassImp(v1751TraceReader)
