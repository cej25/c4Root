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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

#ifndef LisaRaw2Ana_H
#define LisaRaw2Ana_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "LisaData.h"
#include "LisaAnaData.h"
#include <map>
#include <vector>

// This is the adjustment to use TVectors instead of std::vector
//This was to try to read vectors of vectors form external macro without sourcing c4. It does not work.
//template <typename T>
//using StdVector = std::vector<T>;

class EventHeader;
class LisaItem;
class LisaAnaItem;

class LisaRaw2Ana : public FairTask
{
    public:
        LisaRaw2Ana();

        virtual ~LisaRaw2Ana();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TLisaConfiguration const* lisa_config;
    
        std::vector<LisaItem> const* lisaArray;
        std::vector<LisaAnaItem>* lisaAnaArray;
        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        //::: Variable calculated with MWD algorithm
        double energy_MWD;
        std::vector<int16_t> trace_MWD;
        //bool pileup_MWD;
        //bool overflow_MWD;

    public:
        ClassDef(LisaRaw2Ana, 1)

};



#endif