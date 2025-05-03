#ifndef StefanCal2Hit_H
#define StefanCal2Hit_H

#include "StefanCalData.h"
#include "StefanHitData.h"
#include "FairTask.h"
#include "TStefanConfiguration.h"
#include <vector>
#include "EventHeader.h"

class StefanCluster;

class StefanCal2Hit : public FairTask
{
    public:
        StefanCal2Hit();
        virtual ~StefanCal2Hit();
        virtual void Exec(Option_t* option);
        virtual InitStatus Init();
        void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishTask();

    private:

        // implants vs decays or all hits? separate later perhaps
        std::vector<StefanCalItem> const* calArray;
        std::vector<StefanHitItem>* hitArray;

        EventHeader* header;

        void SetParameter();

        TStefanConfiguration const* stefan_config;

        Int_t fExecs = 0;
        Bool_t fOnline;
        int total_time_microsecs = 0;

        Int_t ncalImplantEvents = 0;
        Int_t ncalDecayEvents = 0;

        std::vector<StefanCluster> ItemsToClusters(std::vector<StefanCalItem> const& );
        StefanHitItem ClusterPairToHit(std::pair<StefanCluster, StefanCluster> const&);

    public:
        ClassDef(StefanCal2Hit, 1)
};

class StefanCluster
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

        StefanCluster() { Zero(); }
        void Zero();
        ~StefanCluster() {}
        void AddItem(StefanCalItem const& item);
        void AddCluster(StefanCluster const& cluster);
        bool IsAdjacent(StefanCalItem const& item) const;
        bool IsGoodTime(StefanCalItem const& item, int window = 2000) const;
        bool IsGoodTime(StefanCluster const& cluster, int window) const;
};

#endif /* StefanCal2Hit_H */

