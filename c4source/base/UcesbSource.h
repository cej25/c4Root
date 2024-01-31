
#ifndef UcesbSource_H
#define UcesbSource_H

#include "FairSource.h"

#include "c4Reader.h"

#include "TObjArray.h"
#include "TString.h"
#include <Rtypes.h>

#include "EventHeader.h"

#include <fstream>
#include <list>

/* External data client interface (ucesb) */
#include "ext_data_clnt.hh"
#include "ext_data_struct_info.hh"

/* External data structure
 * This structure is produced using ucesb in the following way:
 * ./ucesb --ntuple=RAW,STRUCT_HH,ext_h101.h
 * */


struct EXT_STR_h101_t;
typedef struct EXT_STR_h101_t EXT_STR_h101;




class UcesbSource : public FairSource
{
  public:
    UcesbSource(const TString&, const TString&, const TString&, EXT_STR_h101*, size_t);
    virtual ~UcesbSource();

    Source_Type GetSourceType() { return kONLINE; }

    /* Init() will fork a ucesb instance to deliver the unpacked data for
     * . It makes use of the ext_data_ interface of ucesb.
     * */
    virtual Bool_t Init();
   
#ifdef ACTIVATEOVERRIDE
    virtual Bool_t SpecifyRunId() override;
#else
    virtual Bool_t SpecifyRunId();
#endif
    
    virtual Bool_t InitUnpackers();
    virtual void SetParUnpackers();
    virtual Bool_t ReInitUnpackers();
    /* A wrapper for ext_data_fetch_event() */
    Int_t ReadEvent(UInt_t);
    /* Close the ext_data_ interface */
    virtual void Close();
    /* Reset the readers */
    virtual void Reset();
    /* The reader interface */
    void AddReader(c4Reader* a_reader) { fReaders->Add(a_reader); }
    /* Limit the number of events */
    void SetMaxEvents(int a_max) { fLastEventNo = a_max; }
    /* Get readers */
    const TObjArray* GetReaders() const { return fReaders; }

    virtual void FillEventHeader(EventHeader* feh);

    void SetInputFileName(TString tstr) { fInputFileName = tstr; }

  private:
    /* File descriptor returned from popen() */
    FILE* fFd;
    /* The ucesb interface class */
    ext_data_clnt fClient;
    /* The ucesb structure info class */
    ext_data_struct_info fStructInfo;
    /* The filename to read */
    const TString fFileName;
    /* Ucesb output options */
    const TString fNtupleOptions;
    /* The location of the unpacker */
    const TString fUcesbPath;
    /* The event counter */
    unsigned int fNEvent;
    /* The full event structure */
    EXT_STR_h101* fEvent;
    size_t fEventSize;
    /* Last event requested */
    int fLastEventNo;
    /* The array of readers */
    TObjArray* fReaders;
    /* header */
    EventHeader* fEventHeader;
    Int_t ReadIntFromString(const std::string& wholestr, const std::string& pattern);
    TString fInputFileName;
    std::ifstream fInputFile;
    Int_t fEntryMax;

  public:
    
    ClassDef(UcesbSource, 1)
};

#endif /* UcesbSource_H */
