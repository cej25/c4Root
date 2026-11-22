#ifndef FatimaVmeReader_H
#define FatimaVmeReader_H

#include "c4Reader.h"
#include "FatimaVmeData.h"

#include <map>
#include <utility>
#include <vector>

class FatimaRawData;
class TClonesArray;

// Publishes legacy VME branches from the bank already decoded by FatimaReader.
class FatimaVmeReader : public c4Reader
{
public:
    FatimaVmeReader();
    ~FatimaVmeReader() override;

    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;

    void SetOnline(Bool_t online) { fOnline = online; }

    ClassDefOverride(FatimaVmeReader, 0);

private:
    Bool_t fOnline = kFALSE;
    const FatimaRawData* fFatimaRaw = nullptr; //! Borrowed event from FatimaReader
    TClonesArray* fArray; //! Legacy branch required by FatimaVmeRaw2Cal
    std::vector<FatimaVmeQDCItem>* qdcArray; //! Owned QDC branch
    std::vector<FatimaVmeTDCItem>* tdcArray; //! Owned TDC branch
    std::map<std::pair<int, int>, int> dets_qdc;
    std::map<std::pair<int, int>, int> dets_tdc;
};

#endif
