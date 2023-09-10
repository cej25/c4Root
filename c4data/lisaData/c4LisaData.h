#ifndef c4LisaData_H
#define c4LisaData_H
#include "TObject.h"

class c4LisaData : public TObject
{
    public:
        c4LisaData();

        c4LisaData(uint32_t board, 
                   uint32_t chn, 
                   uint32_t en,
                   uint32_t ts_lo, 
                   uint32_t ts_hi);

        virtual ~c4LisaData() {}

        // Getters
        inline const uint32_t GetBoard() const { return fBoard; }
        inline const uint32_t GetChn() const { return fChn; }
        inline const uint32_t GetEn() const { return fEn; }
        inline const uint32_t GetTsLo() const { return fTs_Lo; }
        inline const uint32_t GetTsHi() const { return fTs_Hi; }

        // Setters
        void SetBoard(uint32_t v) { fBoard = v; }
        void SetChn(uint32_t v) { fChn = v; }
        void SetEn(uint32_t v) { fEn = v; }
        void SetTsLo(uint32_t v) { fTs_Lo = v; }
        void SetTsHi(uint32_t v) { fTs_Hi = v; }



    protected:
        uint32_t fBoard, fChn;
        uint32_t fEn; // [16] channels?
        uint32_t fTs_Lo, fTs_Hi; // [16] channels?

    public:
        ClassDef(c4LisaData, 1)
};

#endif