#ifndef AidaCalData_H
#define AidaCalData_H

#include "TObject.h"

class AidaCalAdcItem : public TObject
{
public:
    AidaCalAdcItem();

    void Reset();
    void SetAll(uint64_t st, uint64_t ft, int f, int c, int d, int si, int str, bool r, double i, double e);
    uint64_t SlowTime() const;
    uint64_t FastTime() const;
    int Fee() const;
    int Channel() const;
    int DSSD() const;
    int Side() const;
    int Strip() const;
    bool Range() const;
    double Intensity() const;
    double Energy() const;

    ClassDefNV(AidaCalAdcItem, 2)

private:
    uint64_t slowTime;
    uint64_t fastTime;
    int fee;
    int channel;
    int dssd;
    int side;
    int strip;
    bool range;
    double intensity; // only for gain matching code?
    double energy;
};

inline uint64_t AidaCalAdcItem::SlowTime() const
{
    return slowTime;
}

inline uint64_t AidaCalAdcItem::FastTime() const
{
    return fastTime;
}

inline int AidaCalAdcItem::Fee() const
{
    return fee;
}

inline int AidaCalAdcItem::Channel() const
{
    return channel;
}

inline int AidaCalAdcItem::DSSD() const
{
    return dssd;
}

inline int AidaCalAdcItem::Side() const
{
    return side;
}

inline int AidaCalAdcItem::Strip() const
{
    return strip;
}

inline bool AidaCalAdcItem::Range() const
{
    return range;
}

inline double AidaCalAdcItem::Intensity() const
{
    return intensity;
}

inline double AidaCalAdcItem::Energy() const
{
    return energy;
}

#endif /* AidaCalData_H */

