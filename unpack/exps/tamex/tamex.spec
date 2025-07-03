// -*- C++ -*-


#include "../../common/gsi_tamex4.spec"
#include "../../common/whiterabbit.spec"


SUBEVENT(tamex_subev,procid)
{
    select optional
    {
        ts = TIMESTAMP_WHITERABBIT(id = 0x500);
    };

    MEMBER(DATA32 pid);
    ENCODE(pid, (value=procid));

    select optional
    {
        trigger_window = TAMEX4_HEADER();
    };

    select several
    {
        padding = TAMEX4_PADDING();
    };

    select several
    {
        bplast[0] = TAMEX4_SFP(sfp = 0, card = 0);
        fatima[0] = TAMEX4_SFP(sfp = 0, card = 1);
    }

    // if (procid==80)
    // {
    //     select several
    //     {
    //         bplast[0] = TAMEX4_SFP(sfp = 0, card = 0);
    //         bplast[1] = TAMEX4_SFP(sfp = 0, card = 1);
    //         bplast[2] = TAMEX4_SFP(sfp = 0, card = 2);
    //         bplast[3] = TAMEX4_SFP(sfp = 0, card = 3);
    //         bplast[4] = TAMEX4_SFP(sfp = 0, card = 4);
    //         bplast[5] = TAMEX4_SFP(sfp = 0, card = 5);
    //         bplast[6] = TAMEX4_SFP(sfp = 0, card = 6);
    //         bplast[7] = TAMEX4_SFP(sfp = 0, card = 7);
    //         bplast[8] = TAMEX4_SFP(sfp = 0, card = 8);
    //     };
    // }
    // else if (procid==70)
    // {
    //     select several
    //     {
    //         fatima[0] = TAMEX4_SFP(sfp = 0, card = 0);
    //         fatima[1] = TAMEX4_SFP(sfp = 0, card = 1);
    //         fatima[2] = TAMEX4_SFP(sfp = 0, card = 2);
    //         fatima[3] = TAMEX4_SFP(sfp = 0, card = 3);
    //         fatima[4] = TAMEX4_SFP(sfp = 0, card = 4);
    //         fatima[5] = TAMEX4_SFP(sfp = 0, card = 5);
    //         fatima[6] = TAMEX4_SFP(sfp = 0, card = 6);
    //         fatima[7] = TAMEX4_SFP(sfp = 0, card = 7);
    //         fatima[8] = TAMEX4_SFP(sfp = 0, card = 8);
    //     };
    // }
    // else 
    // {
    //     tamex[0] = TAMEX4_SFP(sfp = 0, card = 0);
    //     tamex[1] = TAMEX4_SFP(sfp = 0, card = 1);
    //     tamex[2] = TAMEX4_SFP(sfp = 0, card = 2);
    //     tamex[3] = TAMEX4_SFP(sfp = 0, card = 3);
    //     tamex[4] = TAMEX4_SFP(sfp = 0, card = 4);
    //     tamex[5] = TAMEX4_SFP(sfp = 0, card = 5);
    //     tamex[6] = TAMEX4_SFP(sfp = 0, card = 6);
    //     tamex[7] = TAMEX4_SFP(sfp = 0, card = 7);
    //     tamex[8] = TAMEX4_SFP(sfp = 0, card = 8);
    // }
    
}


EVENT
{
    tamex = tamex_subev(type = 10, subtype = 1, procid = 80, control = 20);

    ignore_unknown_subevent;
};

