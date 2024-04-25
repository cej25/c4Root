#ifndef AidaCal2Hit_H
#define AidaCal2Hit_H

#include "AidaData.h"
#include "AidaCalData.h"
#include "AidaHitData.h"
#include "FairTask.h"
#include "TAidaConfiguration.h"
#include <vector>
#include "EventHeader.h"

class AidaCluster;

class AidaCal2Hit : public FairTask
{
public:
    AidaCal2Hit();
    virtual ~AidaCal2Hit();
    virtual void Exec(Option_t* option);
    virtual void SetParContainers();
    virtual InitStatus Init();
    void SetOnline(Bool_t option) { SetImplantOnline(option); SetDecayOnline(option); }
    void SetImplantOnline(Bool_t option) { fImplantOnline = option; }
    void SetDecayOnline(Bool_t option) { fDecayOnline = option; }

    virtual void FinishTask();

private:
    std::vector<AidaCalAdcItem> const* implantCalArray;
    std::vector<AidaCalAdcItem> const* decayCalArray;
    std::vector<AidaHit>* implantHitArray;
    std::vector<AidaHit>* decayHitArray;

    EventHeader* header;

    void SetParameter();
    bool fImplantOnline;
    bool fDecayOnline;

    TAidaConfiguration const* conf;

    Int_t fExecs = 0;
    int total_time_microsecs = 0;

    std::vector<AidaCluster> ItemsToClusters(std::vector<AidaCalAdcItem> const& );
    AidaHit ClusterPairToHit(std::pair<AidaCluster, AidaCluster> const&);

public:
    ClassDef(AidaCal2Hit, 2)
};

// AidaCluster: Collect adjacent strips for charge splitting
class AidaCluster
{
public:
    int DSSD;
    int Side;
    bool HighEnergy;
    double Intensity;
    double Energy;
    double Strip;
    int64_t Time, FastTime;
    int N;

    int StripMin, StripMax;
    int64_t TimeMin, TimeMax;
    int64_t FastTimeMin, FastTimeMax;
    int StripSum;

    AidaCluster() { Zero(); }
    void Zero();
    ~AidaCluster() {}
    void AddItem(AidaCalAdcItem const& item);
    void AddCluster(AidaCluster const& cluster);
    bool IsAdjacent(AidaCalAdcItem const& item) const;
    bool IsGoodTime(AidaCalAdcItem const& item, int window = 2000) const;
    bool IsGoodTime(AidaCluster const& cluster, int window) const;
};

#endif /* AidaCal2Hit_H */

