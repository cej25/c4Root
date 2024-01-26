#ifndef c4Reader_H
#define c4Reader_H 1

#include "TObject.h"
#include "TString.h"
#include "EventHeader.h"

extern "C"
{
#include "ext_data_struct_info.hh"
}

class TClonesArray;

class c4Reader : public TObject
{
  public:
    c4Reader(TString const&);
    virtual ~c4Reader();

    /* Setup structure information */
    virtual Bool_t Init(ext_data_struct_info*) = 0;
    virtual void SetParContainers() {}
    virtual Bool_t ReInit() { return kTRUE; }
    /* Read data from full event structure */
    virtual Bool_t Read() = 0;
    /* Reset */
    virtual void Reset() = 0;
    /* Return actual name of the reader */
    const char* GetName() { return fName.Data(); }

  protected:
    TString fName;

  public:
    ClassDef(c4Reader, 0);
};

#endif /* c4Reader_H */
