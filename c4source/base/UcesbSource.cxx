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
 *                            R3BRoot Developers                              *
 *                                06.05.25                                    *
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"

// c4
#include "EventHeader.h"
#include "UcesbSource.h"
#include "c4Logger.h"

#include "ext_data_client.h"

UcesbSource::UcesbSource(const TString& FileName,
                               const TString& NtupleOptions,
                               const TString& UcesbPath,
                               EXT_STR_h101* event,
                               size_t event_size)
    : FairSource()
    , fFd(nullptr)
    , fClient()
    , fStructInfo()
    , fFileName(FileName)
    , fNtupleOptions(NtupleOptions)
    , fUcesbPath(UcesbPath)
    , fNEvent(0)
    , fEvent(event)
    , fEventSize(event_size)
    , fLastEventNo(-1)
    , fEventHeader(nullptr)
    , fInputFile()
    , fEntryMax(0)
    , fReaders(new TObjArray())
    , fTimeStitcherPath()
    , fTimeStitcherOptions()
{
}

UcesbSource::~UcesbSource()
{
    c4LOG(debug2, "UcesbSource destructor.");
    if (fReaders)
    {
        fReaders->Delete();
        delete fReaders;
    }
    Close();
}

Bool_t UcesbSource::Init()
{
    // Register of EventHeader in the output root file

    c4LOG(debug2, "checking whether EventHeader has been defined in FairRun");
    auto run = FairRun::Instance();
    auto EvtHead = dynamic_cast<EventHeader*>(run->GetEventHeader());
    if (EvtHead)
    {
        c4LOG(info, "EventHeader. was defined properly - success!");
    }
    else
    {
        EvtHead = new EventHeader();
        run->SetEventHeader(EvtHead); // Implicit conversion and transfer ownership to FairRun
        c4LOG(warn, "EventHeader. has been created from EventHeader");
    }

    Bool_t status;
    std::ostringstream command;

    if (fTimeStitcherPath.Length()) {
	command << fTimeStitcherPath << " " << fFileName << " " 
	    << fTimeStitcherOptions << " --output=- "
	    << " | " << fUcesbPath << " file://- "
	    << "--ntuple=" << fNtupleOptions << ",STRUCT,-";
    }
    else {
        /* Call ucesb with this command */
        command << fUcesbPath << " " << fFileName << " "
	    << "--ntuple=" << fNtupleOptions << ",STRUCT,-"; // just STRUCT
    }

    if (fLastEventNo != -1)
    {
        command << " --max-events=" << fLastEventNo;
    }
    c4LOG(debug2, "Calling ucesb with command: " + command.str());

    /* Fork off ucesb (calls fork() and pipe()) */
    fFd = popen(command.str().c_str(), "r");
    if (nullptr == fFd)
    {
        c4LOG(fatal, "popen() failed");
        return kFALSE;
    }

    /* Connect to forked instance */
    status = fClient.connect(fileno(fFd));
    if (kFALSE == status)
    {
        c4LOG(error, "ext_data_clnt::connect() failed");
        c4LOG(fatal, "ucesb error: " << fClient.last_error());
        return kFALSE;
    }

    // Open configuration file with runid values if needed in this step
    fInputFile.open(fInputFileName.Data(), std::fstream::in);
    if (!fInputFile.is_open())
    {   
        c4LOG(warn, "Input file for RunIds could not be open, it is Ok!");
    }
    else
    {
        c4LOG(info, "Input file for RunIds " << fInputFileName.Data() << " is open!");
        fInputFile.clear();
        fInputFile.seekg(0, std::ios::beg);
    }

    return kTRUE;
}

Bool_t UcesbSource::InitUnpackers()
{
    // Register of EventHeader in the output root file
    FairRootManager* frm = FairRootManager::Instance();
    c4LOG_IF(fatal, !frm, "FairRootManager no found");

    fEventHeader = dynamic_cast<EventHeader*>(frm->GetObject("EventHeader."));
    if (!fEventHeader)
    {
        c4LOG(error, "EventHeader. was not defined properly!");
    }
    // CEJ: changed this because we don't need multiple success statements for the header from UCESB

    /* Initialize all readers */
    for (int i = 0; i < fReaders->GetEntriesFast(); ++i)
    {
        if (!((c4Reader*)fReaders->At(i))->Init(&fStructInfo))
        {
            c4LOG(fatal, "UCESB error: " << fClient.last_error());
            return kFALSE;
        }
    }

    /* Setup client */
    /* this is the version for ucesb setup with extended mapping info */
    uint32_t struct_map_success = 0;
    Bool_t status = fClient.setup(NULL, 0, &fStructInfo, &struct_map_success, fEventSize);
    if (status != 0)
    {
        // perror("ext_data_clnt::setup()");
        c4LOG(error, "ext_data_clnt::setup() failed");
        c4LOG(fatal, "UCESB error: " << fClient.last_error());
        return kFALSE;
    }
    /*
     * It is not needed, that *all* items are matched.
     * However, mapping should fail, if items are requested that don't exist
     * on the server, or if items are requested with wrong parameters.
     * See ucesb/hbook/ext_data_client.h for more information.
     */
    uint32_t map_ok = EXT_DATA_ITEM_MAP_OK | EXT_DATA_ITEM_MAP_NO_DEST;
    if (struct_map_success & ~(map_ok))
    {
        c4LOG(warn, "ext_data_clnt::setup() failed to map all items:");
        ext_data_struct_info_print_map_success(fStructInfo, stderr, map_ok);
        /* FairRunOnline::Init() ignores the return value from
         * GetSource()->InitUnpackers(); so do a (FATAL) error.
         */
        c4LOG(error,
               "ext_data_clnt::setup() mapping failure may "
               "cause unexpected analysis results due to missing "
               "data members. Unpacker needs fixing.");
        return kFALSE;
    }

    return kTRUE;
}

void UcesbSource::SetParUnpackers()
{
    for (int i = 0; i < fReaders->GetEntriesFast(); ++i)
    {
        ((c4Reader*)fReaders->At(i))->SetParContainers();
    }
}

Bool_t UcesbSource::ReInitUnpackers()
{
    /* Initialize all readers */
    for (int i = 0; i < fReaders->GetEntriesFast(); ++i)
    {
        if (!((c4Reader*)fReaders->At(i))->ReInit())
        {
            c4LOG(fatal, "ReInit of a reader failed.");
            return kFALSE;
        }
    }

    return kTRUE;
}

Int_t UcesbSource::ReadIntFromString(const std::string& wholestr, const std::string& pattern)
{
    std::string tempstr = wholestr;
    tempstr.replace(0, tempstr.find(pattern) + pattern.length(), "");
    tempstr.replace(0, tempstr.find('=') + 1, "");
    return atoi(tempstr.c_str());
}

Int_t UcesbSource::ReadEvent(UInt_t i)
{
    const void* raw;
    ssize_t raw_words;
    int ret;
    (void)i; /* Why is i not used? Outer loop seems not to use it. */

    c4LOG(debug2, "ReadEvent " << fNEvent);

    fNEvent++;

    if (fNEvent > fEntryMax && fEntryMax != -1 && fInputFile.is_open())
    {

        c4LOG(info, "ReadEvent()");

        std::string buffer;
        do
        {
            getline(fInputFile, buffer);
            LOG(info) << "read from file: \"" << buffer << "\"";
            if (buffer.find("EVENT BEGIN") == 0)
            {
                fRunId = ReadIntFromString(buffer, "RUNID");
                fEventHeader->SetRunId(fRunId);
                
            }
            if (buffer.find("EVENT") == 0){
                continue;
            }
            Int_t fInit = atoi(buffer.c_str());
            buffer.erase(0, buffer.find(' ') + 1);
            fEntryMax = atoi(buffer.c_str());


        } while (fInputFile && buffer.compare("EVENT END"));
    }

    /* Need to initialize first */
    if (nullptr == fFd)
    {
        Init();
    }

    /* Fetch data */
    ret = fClient.fetch_event(fEvent, fEventSize);
    if (0 == ret)
    {
        LOG(info) << "End of input";
        return 1;
    }
    if (-1 == ret)
    {
        perror("ext_data_clnt::fetch_event()");
        c4LOG(error, "ext_data_clnt::fetch_event() failed");
        c4LOG(fatal, "UCESB error: " << fClient.last_error());
        return 0;
    }

    /* Get raw data, if any */
    ret = fClient.get_raw_data(&raw, &raw_words);
    if (0 != ret)
    {
        perror("ext_data_clnt::get_raw_data()");
        c4LOG(fatal, "Failed to get raw data.");
        return 0;
    }

    /* Run detector specific readers */
    for (int r = 0; r < fReaders->GetEntriesFast(); ++r)
    {   
        c4Reader* reader = (c4Reader*)fReaders->At(r);

        LOG(debug2) << "  Reading reader " << r << " (" << reader->GetName() << ")";
        reader->Read();
    }

    /* Display raw data */
    if (raw) // default "raw"
    {
        int w, j;
        const uint32_t* u = (const uint32_t*)raw;

        LOG(info) << "  Raw data:";
        for (w = 0; w < raw_words; w += 8)
        {
            printf("    RAW%4x:", w);
            for (j = 0; j < 8 && w + j < raw_words; j++)
                printf(" %08x", u[w + j]);
            printf("\n");
        }
    }

    return 0;
}

void UcesbSource::Close()
{
    // Shuffled to remove the double-call crash - NH
    //
    /* Close pipe */
    if (nullptr != fFd)
    {
        int ret;

        /* Close client connection */
        ret = fClient.close();
        // CEJ
        // this returns 0 (correct for closing)
        // then it tries again and receives -1, and thus "fails"
        // second attempt occurs upon gApplication->Terminate();
        // not sure whats going on.

        if (0 != ret)
        {
            c4LOG(fatal, "ext_data_clnt::close() failed ret = " << ret);
        }
        int status;
        status = pclose(fFd);
        if (-1 == status)
        {
            // perror("pclose()");
            c4LOG(fatal, "pclose() failed");
            abort();
        }
        fFd = nullptr;
    }

    if (fInputFile.is_open())
        fInputFile.close();
}

void UcesbSource::Reset()
{
    for (int i = 0; i < fReaders->GetEntriesFast(); ++i)
    {
        ((c4Reader*)fReaders->At(i))->Reset();
    }
}

Bool_t UcesbSource::SpecifyRunId()
{
    if (ReadEvent(0) == 0)
        return true;
    return false;
}

//_____________________________________________________________________________

void UcesbSource::FillEventHeader(EventHeader* feh) { 
    ((EventHeader*)feh)->SetRunId(fRunId);
    }

ClassImp(UcesbSource);
