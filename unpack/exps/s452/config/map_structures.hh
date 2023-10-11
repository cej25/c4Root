#ifndef MapStructures_H
#define Map_Structures_H 1

#include "setup.hh"

struct bPlast_Map
{
    int TAMEX_bPlast_Chan[BPLAST_TAMEX_MODULES][BPLAST_TAMEX_CHANNELS];
    int TAMEX_bPlast_Det[BPLAST_TAMEX_MODULES][BPLAST_TAMEX_CHANNELS];
};

#endif /* Map_Structures_H */