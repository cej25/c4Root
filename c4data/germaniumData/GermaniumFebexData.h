#ifndef GermaniumFebexData_H
#define GermaniumFebexData_H

#include "TObject.h"

class GermaniumFebexData : public TObject
{
    public:
        // Default Constructor
        GermaniumFebexData();

        GermaniumFebexData(Int_t GeFired,
                             uint32_t sumTimeLo,
                             uint32_t sumTimeHi,
                             uint32_t hitPattern,
                             uint32_t chanEnergy,
                             uint32_t chanTimeLo,
                             uint32_t chanTimeHi,
                             uint32_t chanCFLo,
                             uint32_t chanCFHi,
                             uint32_t pileup,
                             uint32_t overflow,
                             uint32_t detIds,
                             uint32_t crystalIds);

        // Destructor
        virtual ~GermaniumFebexData() {};

        // Getters
        inline const Int_t GetGeFired() const { return fGeFired; }
        inline const uint32_t GetSumTimeLo() const { return fSumTimeLo; }
        inline const uint32_t GetSumTimeHi() const { return fSumTimeHi; }
        inline const uint32_t GetHitPattern() const { return fHitPattern; }
        inline const uint32_t GetChanEnergy() const { return fChanEnergy; }
        inline const uint32_t GetChanTimeLo() const { return fChanTimeLo; }
        inline const uint32_t GetChanTimeHi() const { return fChanTimeHi; }
        inline const uint32_t GetChanCFLo() const { return fChanCFLo; }
        inline const uint32_t GetChanCFHi() const { return fChanCFHi; }
        inline const uint32_t GetPileup() const { return fPileup; }
        inline const uint32_t GetOverflow() const { return fOverflow; }
        inline const uint32_t GetDetIds() const { return fDetIds; }
        inline const uint32_t GetCrystalIds() const { return fCrystalIds; }

        // Setters
        void SetGeFired(Int_t v) { fGeFired = v;}
        void SetSumTimeLo(uint32_t v) { fSumTimeLo = v; }
        void SetSumTimeHi(uint32_t v) { fSumTimeHi = v; }
        void SetHitPattern(uint32_t v) { fHitPattern = v; }
        void SetChanEnergy(uint32_t v) { fChanEnergy = v; }
        void SetChanTimeLo(uint32_t v) { fChanTimeLo = v; }
        void SetChanTimeHi(uint32_t v) { fChanTimeHi = v; }
        void SetChanCFLo(uint32_t v) { fChanCFLo = v; }
        void SetChanCFHi(uint32_t v) { fChanCFHi = v; }
        void SetPileup(uint32_t v) { fPileup = v; }
        void SetOverflow(uint32_t v) { fOverflow = v; }
        void SetDetIds(uint32_t v) { fDetIds = v; }
        void SetCrystalIds(uint32_t v) { fCrystalIds = v; }

    protected:
        // Data items
        Int_t fGeFired;
        uint32_t fSumTimeLo;
        uint32_t fSumTimeHi;
        uint32_t fHitPattern;
        uint32_t fChanEnergy;
        uint32_t fChanTimeLo;
        uint32_t fChanTimeHi;
        uint32_t fChanCFLo;
        uint32_t fChanCFHi;
        uint32_t fPileup;
        uint32_t fOverflow;
        uint32_t fDetIds;
        uint32_t fCrystalIds;
    

    public:
        ClassDef(GermaniumFebexData, 1)
};

#endif
