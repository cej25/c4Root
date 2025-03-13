#ifndef BB7GermaniumCorrelationsOnline_H
#define BB7GermaniumCorrelationsOnline_H

#include "BB7FebexData.h"
#include "BB7FebexCalData.h"
#include "BB7FebexHitData.h"
#include "GermaniumCalData.h"
#include "TBB7FebexConfiguration.h"
#include "TGermaniumConfiguration.h"

#include "TClonesArray.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TCutG.h"
#include "TFolder.h"
#include <vector>
#include <map>

class TClonesArray;
class EventHeader;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class BB7EmptyItem;
class BB7FebexItem;
class BB7FebexCalItem;
class BB7FebexHitItem;
class TBB7FebexConfiguration;
class TGermaniumConfiguration;
class TFolder;
class TDirectory;
class TGraph;

class BB7GermaniumCorrelationsOnline : public FairTask
{
    public:
        BB7GermaniumCorrelationsOnline();

        BB7GermaniumCorrelationsOnline(const TString& name, Int_t verbose);

        virtual ~BB7GermaniumCorrelationsOnline();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        TBB7FebexConfiguration const* bb7_config;
        TGermaniumConfiguration const* germanium_config;

        std::vector<BB7EmptyItem> const* bb7empty;
        std::vector<BB7FebexItem> const* bb7rawHits;
        std::vector<BB7FebexCalItem> const* bb7calImplants;
        std::vector<BB7FebexCalItem> const* bb7calDecays;
        std::vector<BB7FebexHitItem> const* bb7decays;
        std::vector<BB7FebexHitItem> const* bb7implants;
        TClonesArray const* germaniumHits;

        Int_t fNEvents;
        EventHeader* header;

        TFolder* histograms;
        TDirectory* dir_germanium;
        TDirectory* dir_germanium_bb7;

        TH1* h1_germanium_bb7_wr_dt;
        TH1* h1_gamma_after_decay;


        Int_t n_bb7_f0 = 0;
        Int_t n_bb7_empty = 0;
        Int_t n_cal_decay = 0;
        Int_t n_cal_implant = 0;
        Int_t n_decay_event = 0;
        Int_t n_implant_event = 0;
        Int_t n_coinc_f0 = 0;
        Int_t n_coinc_empty = 0;
        Int_t n_coinc_cal_decay = 0;
        Int_t n_coinc_cal_imp = 0;
        Int_t n_coinc_decay = 0;
        Int_t n_coinc_imp = 0;

        

    public:
        ClassDef(BB7GermaniumCorrelationsOnline, 1)
};



#endif
