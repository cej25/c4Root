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
#include "QDCReader.h"
#include "c4Logger.h"
#include "QDCData.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_qdc.h"
}

QDCReader::QDCReader(EXT_STR_h101_qdc_onion* data, size_t offset)
    : c4Reader("QDCReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("QDCData"))
{

}

QDCReader::~QDCReader() { 
    delete fArray;

}

Bool_t QDCReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_qdc_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_qdc, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("QDCData", "QDC V792 Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}


Bool_t QDCReader::Read()
{
    c4LOG(debug1, "Event Data");

    if(!fData) return kTRUE;
    
    
    for (int it_board_number = 0; it_board_number < NBoards; it_board_number ++){
        uint32_t num_channels_fired = fData->qdc_data[it_board_number].n;

        for (int ihit = 0; ihit < num_channels_fired; ihit++){
            int channel = (int)fData->qdc_data[it_board_number].nI[ihit];
            int16_t charge = (int16_t)fData->qdc_data[it_board_number].data[ihit];

            new ((*fArray)[fArray->GetEntriesFast()]) QDCData(
            it_board_number,
            channel,
            charge,
            0, //wr here if added in the future
            0
            );
        }

    }
    fNEvent += 1;
    return kTRUE;
}

void QDCReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(QDCReader)
