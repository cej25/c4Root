// -*- C++ -*-

#ifndef BAD_EVENT_H
#define BAD_EVENT_H

// Your BAD_EVENT structure definition

BAD_EVENT()
{
    MEMBER(DATA8 bad);
    
    UINT32 be NOENCODE
    {
        0_31: b = MATCH(0xbad00bad);
    }

    ENCODE(bad, (value = 1));
}

#endif // BAD_EVENT_H

#ifndef DUMMY_H
#define DUMMY_H

// Your DUMMY structure definition

DUMMY()
{
    UINT32 no NOENCODE;
}
<<<<<<< HEAD

#endif // DUMMY_H
=======
>>>>>>> main
