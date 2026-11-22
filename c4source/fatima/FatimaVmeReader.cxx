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
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "FatimaVmeReader.h"

#include "FairRootManager.h"
#include "FatimaRawData.h"
#include "TClonesArray.h"
#include "TFatimaVmeConfiguration.h"
#include "c4Logger.h"

FatimaVmeReader::FatimaVmeReader()
    : c4Reader("FatimaVmeReader"),
      fArray(new TClonesArray("FatimaVmeData")),
      qdcArray(new std::vector<FatimaVmeQDCItem>),
      tdcArray(new std::vector<FatimaVmeTDCItem>)
{
}

FatimaVmeReader::~FatimaVmeReader()
{
    delete fArray;
    delete qdcArray;
    delete tdcArray;
}

Bool_t FatimaVmeReader::Init(ext_data_struct_info*)
{
    auto* manager = FairRootManager::Instance();
    fFatimaRaw = manager->InitObjectAs<const FatimaRawData*>("FatimaRawData");
    if (!fFatimaRaw)
    {
        c4LOG(error, "FATIMA VME requires an earlier reader providing FatimaRawData");
        return kFALSE;
    }

    manager->Register("FatimaVmeData", "FatimaVmeDataFolder", fArray, !fOnline);
    manager->RegisterAny("FatimaVmeQDCData", qdcArray, !fOnline);
    manager->RegisterAny("FatimaVmeTDCData", tdcArray, !fOnline);

    const auto* config = TFatimaVmeConfiguration::GetInstance();
    dets_qdc = config->QDCMapping();
    dets_tdc = config->TDCMapping();

    return kTRUE;
}

Bool_t FatimaVmeReader::Read()
{
    qdcArray->clear();
    tdcArray->clear();

    for (const auto& raw : fFatimaRaw->VMEChain.QDC)
    {
        if (raw.board_id == 0) continue;
        const auto mapping = dets_qdc.find({raw.board_id, raw.channel});
        if (mapping == dets_qdc.end()) continue;
        const double fine_time = (std::uint64_t(raw.coarse) + (std::uint64_t(raw.extended) << 32))
                                 + raw.fine / 1024.;
        qdcArray->emplace_back().SetAll(raw.wr_timestamp, mapping->second, raw.coarse,
                                       fine_time, raw.fine, raw.qlong, raw.qshort, raw.waveform);
    }
    for (const auto& raw : fFatimaRaw->VMEChain.TDC)
    {
        if (raw.geo == 0) continue;
        const auto mapping = dets_tdc.find({raw.geo, raw.channel});
        if (mapping == dets_tdc.end()) continue;
        tdcArray->emplace_back().SetAll(raw.wr_timestamp, raw.wr_subsystem, mapping->second,
                                       raw.measurement, raw.leading_or_trailing);
    }
    return kTRUE;
}

void FatimaVmeReader::Reset()
{
    fArray->Clear();
}

ClassImp(FatimaVmeReader)
