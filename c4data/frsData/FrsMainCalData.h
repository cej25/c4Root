#ifndef FrsMainCalData_H
#define FrsMainCalData_H

#include <vector>
#include "TObject.h"
#include "c4Logger.h"
#include "TString.h"

class FrsMainCalScalerItem : public TObject
{
    public:
        FrsMainCalScalerItem();

        void SetAll(uint32_t in, uint32_t sc);
        void Reset();

        uint32_t Get_index() const;
        uint32_t Get_scaler() const;
        
        
        ClassDefNV(FrsMainCalScalerItem, 2);
    
    private:

        uint32_t index;
        uint32_t scaler;

        // other misc things that need saving
};

class FrsMainCalSciItem : public TObject
{
    public:
        FrsMainCalSciItem();

        void SetAll(uint32_t* de, uint32_t** tdc, int * mh_counter);
        void SetdEArray(uint32_t *);

        void Reset();

        uint32_t* Get_de_array() const;
        uint32_t** Get_tdc_array() const;
        int Get_tdc_array_hits(int channel) const; // index to mh_counter

        //SC21L
        inline void Add_mhtdc_sc21l_hit(int32_t time);
        inline int Get_mhtdc_sc21l_nr_hits() const;
        inline int32_t Get_mhtdc_sc21l_hit(int hitnr) const;
        //SC21r
        inline void Add_mhtdc_sc21r_hit(int32_t time);
        inline int Get_mhtdc_sc21r_nr_hits() const;
        inline int32_t Get_mhtdc_sc21r_hit(int hitnr) const;
        //SC22l
        inline void Add_mhtdc_sc22l_hit(int32_t time);
        inline int Get_mhtdc_sc22l_nr_hits() const;
        inline int32_t Get_mhtdc_sc22l_hit(int hitnr) const;
        //SC22r
        inline void Add_mhtdc_sc22r_hit(int32_t time);
        inline int Get_mhtdc_sc22r_nr_hits() const;
        inline int32_t Get_mhtdc_sc22r_hit(int hitnr) const;
        //SC41l
        inline void Add_mhtdc_sc41l_hit(int32_t time);
        inline int Get_mhtdc_sc41l_nr_hits() const;
        inline int32_t Get_mhtdc_sc41l_hit(int hitnr) const;
        //SC41r
        inline void Add_mhtdc_sc41r_hit(int32_t time);
        inline int Get_mhtdc_sc41r_nr_hits() const;
        inline int32_t Get_mhtdc_sc41r_hit(int hitnr) const;
        //SC42l
        inline void Add_mhtdc_sc42l_hit(int32_t time);
        inline int Get_mhtdc_sc42l_nr_hits() const;
        inline int32_t Get_mhtdc_sc42l_hit(int hitnr) const;
        //SC42r
        inline void Add_mhtdc_sc42r_hit(int32_t time);
        inline int Get_mhtdc_sc42r_nr_hits() const;
        inline int32_t Get_mhtdc_sc42r_hit(int hitnr) const;
        //SC81l
        inline void Add_mhtdc_sc81l_hit(int32_t time);
        inline int Get_mhtdc_sc81l_nr_hits() const;
        inline int32_t Get_mhtdc_sc81l_hit(int hitnr) const;
        //SC81r
        inline void Add_mhtdc_sc81r_hit(int32_t time);
        inline int Get_mhtdc_sc81r_nr_hits() const;
        inline int32_t Get_mhtdc_sc81r_hit(int hitnr) const;
        //SC31l
        inline void Add_mhtdc_sc31l_hit(int32_t time);
        inline int Get_mhtdc_sc31l_nr_hits() const;
        inline int32_t Get_mhtdc_sc31l_hit(int hitnr) const;
        //SC31r
        inline void Add_mhtdc_sc31r_hit(int32_t time);
        inline int Get_mhtdc_sc31r_nr_hits() const;
        inline int32_t Get_mhtdc_sc31r_hit(int hitnr) const;
        //SC11
        inline void Add_mhtdc_sc11_hit(int32_t time);
        inline int Get_mhtdc_sc11_nr_hits() const;
        inline int32_t Get_mhtdc_sc11_hit(int hitnr) const;
        //SC43l
        inline void Add_mhtdc_sc43l_hit(int32_t time);
        inline int Get_mhtdc_sc43l_nr_hits() const;
        inline int32_t Get_mhtdc_sc43l_hit(int hitnr) const;
        //SC43r
        inline void Add_mhtdc_sc43r_hit(int32_t time);
        inline int Get_mhtdc_sc43r_nr_hits() const;
        inline int32_t Get_mhtdc_sc43r_hit(int hitnr) const;

        
        
        ClassDefNV(FrsMainCalSciItem, 2);
    
    private:

        // lets try arrays in a vector lol - I like this -  JEL :)
        uint32_t* de_array; // [14];
        uint32_t** tdc_array; // [15][mh_counter[15]]

        int * mh_counter; // this is the number of hits per channel [0-15] are the same as tdc_array and gives the multiplicity of the SCI events.

        const static int max_hits_in_mhtdc = 100;

        int32_t mhtdc_sc21l_time[max_hits_in_mhtdc];
        int mhtdc_sc21l_hits = 0;
        int32_t mhtdc_sc21r_time[max_hits_in_mhtdc];
        int mhtdc_sc21r_hits = 0;
        int32_t mhtdc_sc22l_time[max_hits_in_mhtdc];
        int mhtdc_sc22l_hits = 0;
        int32_t mhtdc_sc22r_time[max_hits_in_mhtdc];
        int mhtdc_sc22r_hits = 0;
        int32_t mhtdc_sc41l_time[max_hits_in_mhtdc];
        int mhtdc_sc41l_hits = 0;
        int32_t mhtdc_sc41r_time[max_hits_in_mhtdc];
        int mhtdc_sc41r_hits = 0;
        int32_t mhtdc_sc42l_time[max_hits_in_mhtdc];
        int mhtdc_sc42l_hits = 0;
        int32_t mhtdc_sc42r_time[max_hits_in_mhtdc];
        int mhtdc_sc42r_hits = 0;
        int32_t mhtdc_sc43l_time[max_hits_in_mhtdc];
        int mhtdc_sc43l_hits = 0;
        int32_t mhtdc_sc43r_time[max_hits_in_mhtdc];
        int mhtdc_sc43r_hits = 0;
        int32_t mhtdc_sc81l_time[max_hits_in_mhtdc];
        int mhtdc_sc81l_hits = 0;
        int32_t mhtdc_sc81r_time[max_hits_in_mhtdc];
        int mhtdc_sc81r_hits = 0;
        int32_t mhtdc_sc31l_time[max_hits_in_mhtdc];
        int mhtdc_sc31l_hits = 0;
        int32_t mhtdc_sc31r_time[max_hits_in_mhtdc];
        int mhtdc_sc31r_hits = 0;
        int32_t mhtdc_sc11_time[max_hits_in_mhtdc];
        int mhtdc_sc11_hits = 0;

};

class FrsMainCalMusicItem : public TObject
{
    public:
        FrsMainCalMusicItem();

        void SetAll(uint32_t* mt1, uint32_t* mt2);
        void Reset();

        uint32_t* Get_music_t1() const;
        uint32_t* Get_music_t2() const;

        ClassDefNV(FrsMainCalMusicItem, 2);
    
    private:

        uint32_t* music_t1; // [8]
        uint32_t* music_t2; // [8]
};

inline uint32_t FrsMainCalScalerItem::Get_index() const
{
    return index;
}

inline uint32_t FrsMainCalScalerItem::Get_scaler() const
{
    return scaler;
}

inline uint32_t* FrsMainCalSciItem::Get_de_array() const
{
    return de_array;
}

inline uint32_t** FrsMainCalSciItem::Get_tdc_array() const
{
    return tdc_array;
}
inline int FrsMainCalSciItem::Get_tdc_array_hits(int channel) const
{
    if (channel >= 32) c4LOG(fatal, Form("Indexed mh_counter array out of bounds : %i >= 32",channel) );
    return mh_counter[channel];
}


//SC21L
inline void FrsMainCalSciItem::Add_mhtdc_sc21l_hit(int32_t time){
    mhtdc_sc21l_time[mhtdc_sc21l_hits] = time;
    mhtdc_sc21l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc21l_nr_hits() const {
    return mhtdc_sc21l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc21l_hit(int hitnr) const {
    return mhtdc_sc21l_time[hitnr];
}
//SC21r
inline void FrsMainCalSciItem::Add_mhtdc_sc21r_hit(int32_t time){
    mhtdc_sc21r_time[mhtdc_sc21r_hits] = time;
    mhtdc_sc21r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc21r_nr_hits() const {
    return mhtdc_sc21r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc21r_hit(int hitnr) const {
    return mhtdc_sc21r_time[hitnr];
}
//SC22l
inline void FrsMainCalSciItem::Add_mhtdc_sc22l_hit(int32_t time){
    mhtdc_sc22l_time[mhtdc_sc22l_hits] = time;
    mhtdc_sc22l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc22l_nr_hits() const {
    return mhtdc_sc22l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc22l_hit(int hitnr) const {
    return mhtdc_sc22l_time[hitnr];
}
//SC22r
inline void FrsMainCalSciItem::Add_mhtdc_sc22r_hit(int32_t time){
    mhtdc_sc22r_time[mhtdc_sc22r_hits] = time;
    mhtdc_sc22r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc22r_nr_hits() const {
    return mhtdc_sc22r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc22r_hit(int hitnr) const {
    return mhtdc_sc22r_time[hitnr];
}
//SC41l
inline void FrsMainCalSciItem::Add_mhtdc_sc41l_hit(int32_t time){
    mhtdc_sc41l_time[mhtdc_sc41l_hits] = time;
    mhtdc_sc41l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc41l_nr_hits() const {
    return mhtdc_sc41l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc41l_hit(int hitnr) const {
    return mhtdc_sc41l_time[hitnr];
}
//SC41r
inline void FrsMainCalSciItem::Add_mhtdc_sc41r_hit(int32_t time){
    mhtdc_sc41r_time[mhtdc_sc41r_hits] = time;
    mhtdc_sc41r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc41r_nr_hits() const {
    return mhtdc_sc41r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc41r_hit(int hitnr) const {
    return mhtdc_sc41r_time[hitnr];
}
//SC42l
inline void FrsMainCalSciItem::Add_mhtdc_sc42l_hit(int32_t time){
    mhtdc_sc42l_time[mhtdc_sc42l_hits] = time;
    mhtdc_sc42l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc42l_nr_hits() const {
    return mhtdc_sc42l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc42l_hit(int hitnr) const {
    return mhtdc_sc42l_time[hitnr];
}
//SC42r
inline void FrsMainCalSciItem::Add_mhtdc_sc42r_hit(int32_t time){
    mhtdc_sc42r_time[mhtdc_sc42r_hits] = time;
    mhtdc_sc42r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc42r_nr_hits() const {
    return mhtdc_sc42r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc42r_hit(int hitnr) const {
    return mhtdc_sc42r_time[hitnr];
}
//SC81l
inline void FrsMainCalSciItem::Add_mhtdc_sc81l_hit(int32_t time){
    mhtdc_sc81l_time[mhtdc_sc81l_hits] = time;
    mhtdc_sc81l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc81l_nr_hits() const {
    return mhtdc_sc81l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc81l_hit(int hitnr) const {
    return mhtdc_sc81l_time[hitnr];
}
//SC81r
inline void FrsMainCalSciItem::Add_mhtdc_sc81r_hit(int32_t time){
    mhtdc_sc81r_time[mhtdc_sc81r_hits] = time;
    mhtdc_sc81r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc81r_nr_hits() const {
    return mhtdc_sc81r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc81r_hit(int hitnr) const {
    return mhtdc_sc81r_time[hitnr];
}
//SC31l
inline void FrsMainCalSciItem::Add_mhtdc_sc31l_hit(int32_t time){
    mhtdc_sc31l_time[mhtdc_sc31l_hits] = time;
    mhtdc_sc31l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc31l_nr_hits() const {
    return mhtdc_sc31l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc31l_hit(int hitnr) const {
    return mhtdc_sc31l_time[hitnr];
}
//SC31r
inline void FrsMainCalSciItem::Add_mhtdc_sc31r_hit(int32_t time){
    mhtdc_sc31r_time[mhtdc_sc31r_hits] = time;
    mhtdc_sc31r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc31r_nr_hits() const {
    return mhtdc_sc31r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc31r_hit(int hitnr) const {
    return mhtdc_sc31r_time[hitnr];
}
//SC11
inline void FrsMainCalSciItem::Add_mhtdc_sc11_hit(int32_t time){
    mhtdc_sc11_time[mhtdc_sc11_hits] = time;
    mhtdc_sc11_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc11_nr_hits() const {
    return mhtdc_sc11_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc11_hit(int hitnr) const {
    return mhtdc_sc11_time[hitnr];
}
//SC43l
inline void FrsMainCalSciItem::Add_mhtdc_sc43l_hit(int32_t time){
    mhtdc_sc43l_time[mhtdc_sc43l_hits] = time;
    mhtdc_sc43l_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc43l_nr_hits() const {
    return mhtdc_sc43l_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc43l_hit(int hitnr) const {
    return mhtdc_sc43l_time[hitnr];
}
//SC43r
inline void FrsMainCalSciItem::Add_mhtdc_sc43r_hit(int32_t time){
    mhtdc_sc43r_time[mhtdc_sc43r_hits] = time;
    mhtdc_sc43r_hits++;
}
inline int FrsMainCalSciItem::Get_mhtdc_sc43r_nr_hits() const {
    return mhtdc_sc43r_hits;
}
inline  int32_t FrsMainCalSciItem::Get_mhtdc_sc43r_hit(int hitnr) const {
    return mhtdc_sc43r_time[hitnr];
}



inline uint32_t* FrsMainCalMusicItem::Get_music_t1() const
{
    return music_t1;
}

inline uint32_t* FrsMainCalMusicItem::Get_music_t2() const
{
    return music_t2;
}

#endif