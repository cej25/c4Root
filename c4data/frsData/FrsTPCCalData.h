#ifndef FrsTPCCalData_H
#define FrsTPCCalData_H

#include "TObject.h"
#include "TClonesArray.h"
#include "c4Logger.h"
#include <vector>

class TClonesArray;

class FrsTPCCalData : public TObject
{
    public:
        FrsTPCCalData();

        FrsTPCCalData(Bool_t* b_tpc_de,
                    Float_t* tpc_x,
                    Float_t* tpc_y,
                    Int_t tpc_csum[7][4],
                    Bool_t* b_tpc_xy,
                    Float_t tpc_angle_x_s2_foc_21_22,
                    Float_t tpc_angle_y_s2_foc_21_22,
                    Float_t tpc_x_s2_foc_21_22,
                    Float_t tpc_y_s2_foc_21_22,
                    Float_t tpc21_22_sc21_x,
                    Float_t tpc21_22_sc22_x,
                    Float_t tpc_angle_x_s2_foc_23_24,
                    Float_t tpc_angle_y_s2_foc_23_24,
                    Float_t tpc_x_s2_foc_23_24,
                    Float_t tpc_y_s2_foc_23_24,
                    Float_t tpc23_24_sc21_x,
                    Float_t tpc23_24_sc21_y,
                    Float_t tpc23_24_sc22_x,
                    Float_t tpc23_24_sc22_y,
                    Float_t tpc_angle_x_s2_foc_22_24,
                    Float_t tpc_angle_y_s2_foc_22_24,
                    Float_t tpc_x_s2_foc_22_24,
                    Float_t tpc_y_s2_foc_22_24,
                    Float_t tpc_angle_x_s4,
                    Float_t tpc_angle_y_s4,
                    Float_t tpc_x_s4,
                    Float_t tpc_y_s4,
                    Float_t tpc_sc41_x,
                    Float_t tpc_sc41_y,
                    Float_t tpc_sc42_x,
                    Float_t tpc_sc42_y,
                    Float_t tpc_sc43_x,
                    Float_t tpc_music41_x,
                    Float_t tpc_music42_x,
                    Float_t tpc_music43_x);

        virtual ~FrsTPCCalData() {}

        inline const Bool_t* Get_b_tpc_xy() const { return fb_tpc_xy; }
        inline const Float_t Get_tpc_x_s2_foc_21_22() const { return ftpc_x_s2_foc_21_22; }
        inline const Float_t Get_tpc_y_s2_foc_21_22() const { return ftpc_y_s2_foc_21_22; }
        inline const Float_t Get_tpc_angle_x_s2_foc_21_22() const { return ftpc_angle_x_s2_foc_21_22; }
        inline const Float_t Get_tpc_angle_y_s2_foc_21_22() const { return ftpc_angle_y_s2_foc_21_22; }
        inline const Float_t Get_tpc_x_s2_foc_22_24() const { return ftpc_x_s2_foc_22_24; }
        inline const Float_t Get_tpc_y_s2_foc_22_24() const { return ftpc_y_s2_foc_22_24; }
        inline const Float_t Get_tpc_angle_x_s2_foc_22_24() const { return ftpc_angle_x_s2_foc_22_24; }
        inline const Float_t Get_tpc_angle_y_s2_foc_22_24() const { return ftpc_angle_y_s2_foc_22_24; }
        inline const Float_t Get_tpc_x_s2_foc_23_24() const { return ftpc_x_s2_foc_23_24; }
        inline const Float_t Get_tpc_y_s2_foc_23_24() const { return ftpc_y_s2_foc_23_24; }
        inline const Float_t Get_tpc_angle_x_s2_foc_23_24() const { return ftpc_angle_x_s2_foc_23_24; }
        inline const Float_t Get_tpc_angle_y_s2_foc_23_24() const { return ftpc_angle_y_s2_foc_23_24; }
        inline const Float_t Get_tpc_angle_x_s4() const { return ftpc_angle_x_s4; }
        inline const Float_t Get_tpc_angle_y_s4() const { return ftpc_angle_y_s4; }
        inline const Float_t Get_tpc_x_s4() const { return ftpc_x_s4; }
        inline const Float_t Get_tpc_y_s4() const { return ftpc_y_s4; }
        inline const Float_t Get_tpc23_24_sc21_y() const {return ftpc23_24_sc21_y;}
        inline const Float_t Get_tpc23_24_sc22_y() const {return ftpc23_24_sc22_y;}
        inline const Float_t Get_tpc_sc41_x() const {return ftpc_sc41_x;}
        inline const Float_t Get_tpc_sc41_y() const {return ftpc_sc41_y;}
        inline const Float_t Get_tpc_sc42_x() const {return ftpc_sc42_x;}
        inline const Float_t Get_tpc_sc42_y() const {return ftpc_sc42_y;}
        inline const Float_t Get_tpc_sc43_x() const {return ftpc_sc43_x;}
        inline const Float_t Get_tpc_music43_x() const {return ftpc_music43_x;}

        inline const Float_t Get_tpc21_22_sc21_x() const { return ftpc21_22_sc21_x; }
        inline const Float_t Get_tpc23_24_sc21_x() const { return ftpc23_24_sc21_x; }
        inline const Float_t Get_tpc21_22_sc22_x() const { return ftpc21_22_sc22_x; }
        inline const Float_t Get_tpc23_24_sc22_x() const { return ftpc23_24_sc22_x; }

        inline const Float_t Get_tpc_music41_x() const { return ftpc_music41_x; }
        inline const Float_t Get_tpc_music42_x() const { return ftpc_music42_x; }

        inline const Int_t Get_tpc_csum(int tpc_nr, int anodenr) const {
            c4LOG_IF(fatal,(tpc_nr<0)||(tpc_nr>7)||(anodenr<0)||(anodenr>4),"Wrong indexing of TPC get tpc csum.");
            return ftpc_csum[tpc_nr][anodenr];
            }

    private:
        Bool_t fb_tpc_de[7];
        Float_t ftpc_x[7];
        Float_t ftpc_y[7];
        Bool_t fb_tpc_xy[7];
        Int_t ftpc_csum[7][4];
        Float_t ftpc_angle_x_s2_foc_21_22;
        Float_t ftpc_angle_y_s2_foc_21_22;
        Float_t ftpc_x_s2_foc_21_22;
        Float_t ftpc_y_s2_foc_21_22;
        Float_t ftpc21_22_sc21_x;
        Float_t ftpc21_22_sc22_x;
        Float_t ftpc_angle_x_s2_foc_23_24;
        Float_t ftpc_angle_y_s2_foc_23_24;
        Float_t ftpc_x_s2_foc_23_24;
        Float_t ftpc_y_s2_foc_23_24;
        Float_t ftpc23_24_sc21_x;
        Float_t ftpc23_24_sc21_y;
        Float_t ftpc23_24_sc22_x;
        Float_t ftpc23_24_sc22_y;
        Float_t ftpc_angle_x_s2_foc_22_24;
        Float_t ftpc_angle_y_s2_foc_22_24;
        Float_t ftpc_x_s2_foc_22_24;
        Float_t ftpc_y_s2_foc_22_24;
        Float_t ftpc_angle_x_s4;
        Float_t ftpc_angle_y_s4;
        Float_t ftpc_x_s4;
        Float_t ftpc_y_s4;
        Float_t ftpc_sc41_x;
        Float_t ftpc_sc41_y;
        Float_t ftpc_sc42_x;
        Float_t ftpc_sc42_y;
        Float_t ftpc_sc43_x;
        Float_t ftpc_music41_x;
        Float_t ftpc_music42_x;
        Float_t ftpc_music43_x;
    
    public:
        ClassDef(FrsTPCCalData, 1)
};

class FrsTPCCalItem : public TObject
{
    public:
        FrsTPCCalItem();

        void SetAll(Bool_t* b_tpc_xy,
                    Int_t** tpc_csum, // [7][4]
                    Float_t tpc_angle_x_s2_foc_21_22,
                    Float_t tpc_angle_y_s2_foc_21_22,
                    Float_t tpc_x_s2_foc_21_22,
                    Float_t tpc_y_s2_foc_21_22,
                    Float_t tpc21_22_sc21_x,
                    Float_t tpc21_22_sc22_x,
                    Float_t tpc_angle_x_s2_foc_23_24,
                    Float_t tpc_angle_y_s2_foc_23_24,
                    Float_t tpc_x_s2_foc_23_24,
                    Float_t tpc_y_s2_foc_23_24,
                    Float_t tpc23_24_sc21_x,
                    Float_t tpc23_24_sc21_y,
                    Float_t tpc23_24_sc22_x,
                    Float_t tpc23_24_sc22_y,
                    Float_t tpc_angle_x_s2_foc_22_24,
                    Float_t tpc_angle_y_s2_foc_22_24,
                    Float_t tpc_x_s2_foc_22_24,
                    Float_t tpc_y_s2_foc_22_24,
                    Float_t tpc_angle_x_s4,
                    Float_t tpc_angle_y_s4,
                    Float_t tpc_x_s4,
                    Float_t tpc_y_s4,
                    Float_t tpc_sc41_x,
                    Float_t tpc_sc41_y,
                    Float_t tpc_sc42_x,
                    Float_t tpc_sc42_y,
                    Float_t tpc_sc43_x,
                    Float_t tpc_music41_x,
                    Float_t tpc_music42_x,
                    Float_t tpc_music43_x);

        void Reset();

        Bool_t* Get_b_tpc_xy() const;
        Int_t** Get_tpc_csum() const;
        Float_t Get_tpc_x_s2_foc_21_22() const;
        Float_t Get_tpc_y_s2_foc_21_22() const;
        Float_t Get_tpc_angle_x_s2_foc_21_22() const;
        Float_t Get_tpc_angle_y_s2_foc_21_22() const;
        Float_t Get_tpc_x_s2_foc_22_24() const;
        Float_t Get_tpc_y_s2_foc_22_24() const;
        Float_t Get_tpc_angle_x_s2_foc_22_24() const;
        Float_t Get_tpc_angle_y_s2_foc_22_24() const;
        Float_t Get_tpc_x_s2_foc_23_24() const;
        Float_t Get_tpc_y_s2_foc_23_24() const;
        Float_t Get_tpc_angle_x_s2_foc_23_24() const;
        Float_t Get_tpc_angle_y_s2_foc_23_24() const;
        Float_t Get_tpc_angle_x_s4() const;
        Float_t Get_tpc_angle_y_s4() const;
        Float_t Get_tpc_x_s4() const;
        Float_t Get_tpc_y_s4() const;
        Float_t Get_tpc23_24_sc21_y() const;
        Float_t Get_tpc23_24_sc22_y() const;
        Float_t Get_tpc_sc41_x() const;
        Float_t Get_tpc_sc41_y() const;
        Float_t Get_tpc_sc42_x() const;
        Float_t Get_tpc_sc42_y() const;
        Float_t Get_tpc_sc43_x() const;
        Float_t Get_tpc21_22_sc21_x() const;
        Float_t Get_tpc23_24_sc21_x() const;
        Float_t Get_tpc21_22_sc22_x() const;
        Float_t Get_tpc23_24_sc22_x() const;
        Float_t Get_tpc_music41_x() const;
        Float_t Get_tpc_music42_x() const;
        Float_t Get_tpc_music43_x() const;

        ClassDefNV(FrsTPCCalItem, 2);
    
    private:

        // members
        Bool_t fb_tpc_de[7]; // not used yet, tpc_de not even passed along
        Float_t ftpc_x[7]; // used by frs for plotting and sc31
        Float_t ftpc_y[7]; // used by frs for plotting and sc31
        Bool_t* fb_tpc_xy; // [7]
        Int_t** ftpc_csum; //[7][4]
        Float_t ftpc_angle_x_s2_foc_21_22;
        Float_t ftpc_angle_y_s2_foc_21_22;
        Float_t ftpc_x_s2_foc_21_22;
        Float_t ftpc_y_s2_foc_21_22;
        Float_t ftpc21_22_sc21_x;
        Float_t ftpc21_22_sc22_x;
        Float_t ftpc_angle_x_s2_foc_23_24;
        Float_t ftpc_angle_y_s2_foc_23_24;
        Float_t ftpc_x_s2_foc_23_24;
        Float_t ftpc_y_s2_foc_23_24;
        Float_t ftpc23_24_sc21_x;
        Float_t ftpc23_24_sc21_y;
        Float_t ftpc23_24_sc22_x;
        Float_t ftpc23_24_sc22_y;
        Float_t ftpc_angle_x_s2_foc_22_24;
        Float_t ftpc_angle_y_s2_foc_22_24;
        Float_t ftpc_x_s2_foc_22_24;
        Float_t ftpc_y_s2_foc_22_24;
        Float_t ftpc_angle_x_s4;
        Float_t ftpc_angle_y_s4;
        Float_t ftpc_x_s4;
        Float_t ftpc_y_s4;
        Float_t ftpc_sc41_x;
        Float_t ftpc_sc41_y;
        Float_t ftpc_sc42_x;
        Float_t ftpc_sc42_y;
        Float_t ftpc_sc43_x;
        Float_t ftpc_music41_x;
        Float_t ftpc_music42_x;
        Float_t ftpc_music43_x;
    


};

inline Bool_t* FrsTPCCalItem::Get_b_tpc_xy() const
{
    return fb_tpc_xy;
}

inline Int_t** FrsTPCCalItem::Get_tpc_csum() const
{
    return ftpc_csum;
}

inline Float_t FrsTPCCalItem::Get_tpc_x_s2_foc_21_22() const
{
    return ftpc_x_s2_foc_21_22;
}

inline Float_t FrsTPCCalItem::Get_tpc_y_s2_foc_21_22() const
{
    return ftpc_y_s2_foc_21_22;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_x_s2_foc_21_22() const
{
    return ftpc_angle_x_s2_foc_21_22;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_y_s2_foc_21_22() const
{
    return ftpc_angle_y_s2_foc_21_22;
}

inline Float_t FrsTPCCalItem::Get_tpc_x_s2_foc_22_24() const
{
    return ftpc_x_s2_foc_22_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_y_s2_foc_22_24() const
{
    return ftpc_y_s2_foc_22_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_x_s2_foc_22_24() const
{
    return ftpc_angle_x_s2_foc_22_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_y_s2_foc_22_24() const
{
    return ftpc_angle_y_s2_foc_22_24;
}


inline Float_t FrsTPCCalItem::Get_tpc_x_s2_foc_23_24() const
{
    return ftpc_x_s2_foc_23_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_y_s2_foc_23_24() const
{
    return ftpc_y_s2_foc_23_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_x_s2_foc_23_24() const
{
    return ftpc_angle_x_s2_foc_23_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_y_s2_foc_23_24() const
{
    return ftpc_angle_y_s2_foc_23_24;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_x_s4() const
{
    return ftpc_angle_x_s4;
}

inline Float_t FrsTPCCalItem::Get_tpc_angle_y_s4() const
{
    return ftpc_angle_y_s4;
}

inline Float_t FrsTPCCalItem::Get_tpc_x_s4() const
{
    return ftpc_x_s4;
}

inline Float_t FrsTPCCalItem::Get_tpc_y_s4() const
{
    return ftpc_y_s4;
}

inline Float_t FrsTPCCalItem::Get_tpc23_24_sc21_y() const
{
    return ftpc23_24_sc21_y;
}

inline Float_t FrsTPCCalItem::Get_tpc23_24_sc22_y() const
{
    return ftpc23_24_sc22_y;
}

inline Float_t FrsTPCCalItem::Get_tpc_sc41_x() const
{
    return ftpc_sc41_x;
}

inline Float_t FrsTPCCalItem::Get_tpc_sc41_y() const
{
    return ftpc_sc41_y;
}

inline Float_t FrsTPCCalItem::Get_tpc_sc42_x() const
{
    return ftpc_sc42_x;
}

inline Float_t FrsTPCCalItem::Get_tpc_sc42_y() const
{
    return ftpc_sc42_y;
}

inline Float_t FrsTPCCalItem::Get_tpc_sc43_x() const
{
    return ftpc_sc43_x;
}

inline Float_t FrsTPCCalItem::Get_tpc21_22_sc21_x() const
{
    return ftpc21_22_sc21_x;
}

inline Float_t FrsTPCCalItem::Get_tpc23_24_sc21_x() const
{
    return ftpc23_24_sc21_x;
}

inline Float_t FrsTPCCalItem::Get_tpc21_22_sc22_x() const
{
    return ftpc21_22_sc22_x;
}

inline Float_t FrsTPCCalItem::Get_tpc23_24_sc22_x() const
{
    return ftpc23_24_sc22_x;
}

inline Float_t FrsTPCCalItem::Get_tpc_music41_x() const
{
    return ftpc_music41_x;
}

inline Float_t FrsTPCCalItem::Get_tpc_music42_x() const
{
    return ftpc_music42_x;
}

inline Float_t FrsTPCCalItem::Get_tpc_music43_x() const
{
    return ftpc_music43_x;
}

#endif