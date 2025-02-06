#ifndef BB7FebexCal2Hit_H
#define BB7FebexCal2Hit_H

#include "BB7FebexCalData.h"
#include "BB7FebexHitData.h"
#include "FairTask.h"
#include "TBB7FebexConfiguration.h"
#include <vector>
#include "EventHeader.h"

class BB7Cluster;

class BB7FebexCal2Hit : public FairTask
{
    public:
        BB7FebexCal2Hit();
        virtual ~BB7FebexCal2Hit();
        virtual void Exec(Option_t* option);
        virtual InitStatus Init();
        void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishTask();

    private:
        std::vector<BB7FebexCalItem> const* bb7calImplants;
        std::vector<BB7FebexCalItem> const* bb7calDecays;
        std::vector<BB7FebexHitItem>* implantHitArray;
        std::vector<BB7FebexHitItem>* decayHitArray;

        EventHeader* header;

        void SetParameter();

        TBB7FebexConfiguration const* bb7_config;

        Int_t fExecs = 0;
        Bool_t fOnline;
        int total_time_microsecs = 0;

        std::vector<BB7Cluster> ItemsToClusters(std::vector<BB7FebexCalItem> const& );
        BB7FebexHitItem ClusterPairToHit(std::pair<BB7Cluster, BB7Cluster> const&);

    public:
        ClassDef(BB7FebexCal2Hit, 1)
};

class BB7Cluster
{
    public:

        int DSSD;
        int Side;
        int Strip;
        bool HighEnergy;
        double Energy;
        int64_t Time;

        int StripMin, StripMax;
        int64_t TimeMin, TimeMax;

        int StripSum;
        int N;

        BB7Cluster() { Zero(); }
        void Zero();
        ~BB7Cluster() {}
        void AddItem(BB7FebexCalItem const& item);
        void AddCluster(BB7Cluster const& cluster);
        bool IsAdjacent(BB7FebexCalItem const& item) const;
        bool IsGoodTime(BB7FebexCalItem const& item, int window = 2000) const;
        bool IsGoodTime(BB7Cluster const& cluster, int window) const;
};

#endif /* BB7FebexCal2Hit_H */

