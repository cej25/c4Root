// FairRoot
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsRaw2Cal.h"
#include "FrsCalData.h"
#include "FrsData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TMath.h"
#include <fstream>
#include <iomanip>

FrsRaw2Cal::FrsRaw2Cal()
    : FrsRaw2Cal("FrsRaw2Cal", 1)
{
}

FrsRaw2Cal::FrsRaw2Cal(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fFrsData(NULL)
    , fFrsCalData(NULL)
    , fMap_Par(NULL) // 
    , fOnline(kFALSE)
{
}

FrsRaw2Cal::~FrsRaw2Cal()
{
    c4LOG(DEBUG1, "Destructor");
    if (fFrsCalData)
        delete fFrsCalData;
}

void FrsRaw2Cal::SetParContainers()
{
    // Parameter Container
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    c4LOG_IF(FATAL, !rtdb, "FairRuntimeDb not found");

    fMap_Par = (FrsMappingPar*)rtdb->getContainer("FrsMappingPar");
    c4LOG_IF(FATAL, !fMap_Par, "Container FrsMappingPar not found");
}

void FrsRaw2Cal::SetParameter()
{
    fMap_Par->printParams();
}

InitStatus FrsRaw2Cal::Init()
{
    c4BLOG(INFO, "");
    FairRootManager* mgr = FairRootManager::Instance();
    if (!mgr)
    {
        c4BLOG(FATAL, "FairRootManager not found");
        return kFATAL;
    }

    // INPUT DATA
    fFrsData = (TClonesArray*)mgr->GetObject("FrsData");
    if (!fFrsData)
    {
        c4LOG(FATAL, "FrsData not found");
        return kFATAL;
    }

    // OUTPUT DATA
    fFrsCalData = new TClonesArray("FrsCalData");
    mgr->Register("FrsCalData", "FRS_Cal", fFrsCalData, !fOnline);

    SetParameter();
    return kSUCCESS;
}

InitStatus FrsRaw2Cal::ReInit()
{
    SetParContainers();
    SetParameter();
    return kSUCCESS;
}

void FrsRaw2Cal::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();

    // Reading the Input -- Mapped Data --
    Int_t nHits = fFrsData->GetEntries();
    if (!nHits)
        return;

    auto mappedData = new FrsData*[nHits];

    for (Int_t i = 0; i < nHits; i++)
    {
        mappedData[i] = (FrsData*)(FrsData->At(i));
        auto det = mappedData[i]->GetSensorId();
        auto col = mappedData[i]->GetCol();
        auto row = mappedData[i]->GetAds();
        if (fMap_Par->GetInUse(det, col, row) == 1)
            AddCalData(det, col, row);
    }
    if (mappedData)
        delete[] mappedData;
    return;
}

int FrsRaw2Cal::GetCol(int reg, int dcol, int ads)
{
    int col = reg * 32 + dcol * 2;
    int lr = ((ads % 4) < 2 ? 1 : 0);
    col += lr;
    return col;
}

int FrsRaw2Cal::GetRow(int ads)
{
    // This is OK for pixels within a group of 4
    return ads / 2;
}

void FrsRaw2Cal::Reset()
{
    R3BLOG(DEBUG1, "Clearing CalData Structure");
    if (fFrsCalData)
        fFrsCalData->Clear();
}

FrsCalData* FrsRaw2Cal::AddCalData(UShort_t senId, Int_t col, Int_t row)
{
    TClonesArray& clref = *fFrsCalData;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) FrsCalData(senId, col, row);
}

ClassImp(FrsRaw2Cal);



// stuff from unpacker
if (procid == 30 && type == 12)
    {   

        if (item.trigger == 13 || item.trigger == 12 || item.trigger == 10 || item.trigger == 11) return; // skip spill trigger
        
        if (item.scaler_check_first_event == 1)
        {
            for (int ii = 0; ii < 64; ii++)
            {
                item.scaler_initial[ii] = item.sc_long[ii];
                item.scaler_previous[ii] = item.sc_long[ii];

            }
            item.scaler_check_first_event = 0;
        }

        item.time_in_ms = item.sc_long[item.scaler_ch_1kHz] - item.scaler_initial[item.scaler_ch_spillstart];

        item.ibin_for_s = ((item.time_in_ms / 1000) % 1000) + 1;
        item.ibin_for_100ms = ((item.time_in_ms / 100) % 4000) + 1;
        item.ibin_for_spill = (item.spill_count % 1000) + 1;

        for (int kk = 0; kk < 64; kk++)
        {
            item.increase_scaler_temp[kk] = item.sc_long[kk] - item.scaler_previous[kk];
        }

        item.extraction_time_ms += item.sc_long[item.scaler_ch_1kHz] - item.scaler_previous[item.scaler_ch_1kHz];
        if ((item.sc_long[item.scaler_ch_spillstart] - item.scaler_previous[item.scaler_ch_spillstart]) != 0)
        {
            item.extraction_time_ms = 0;
        }

        item.ibin_clean_for_s = (((item.time_in_ms / 1000) + 20) % 1000) + 1;
        item.ibin_clean_for_100ms = (((item.time_in_ms / 100) + 200) % 4000) + 1;
        item.ibin_clean_for_spill = ((item.spill_count + 990) % 20) + 1;

        // put current data into previous for the next event
        for (int ii = 0; ii < 64; ii++)
        {
            item.scaler_previous[ii] = item.sc_long[ii]; 
        }
    }
