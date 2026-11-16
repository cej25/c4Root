#include "foot_wr.spec"
#include "foot_subev_ids.h"

#define __EMPTY_MACRO__(X)

external EXT_FOOT();

#define FOOT_TS_SUBEVENT(X) \
	SUBEVENT(foot##X##_ts) { \
		ts = TIMESTAMP_WHITERABBIT_EXTENDED(id = (FOOT_CONTROL_##X << 8)) ; \
		sync = TIMESTAMP_SYNC_CHECK(); \
	}
	__EMPTY_MACRO__(X)

FOOT_TS_SUBEVENT(1)
FOOT_TS_SUBEVENT(2)
FOOT_TS_SUBEVENT(3)
FOOT_TS_SUBEVENT(4)
FOOT_TS_SUBEVENT(5)
FOOT_TS_SUBEVENT(6)
FOOT_TS_SUBEVENT(7)
FOOT_TS_SUBEVENT(8)

SUBEVENT(foot_subev) { 
	external foot = EXT_FOOT(); 
}
