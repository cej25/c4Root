Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/baseData
${C4ROOT_SOURCE_DIR}/c4data/bgoData
${C4ROOT_SOURCE_DIR}/c4data/germaniumData
${C4ROOT_SOURCE_DIR}/c4data/timemachineData
${C4ROOT_SOURCE_DIR}/analysis
${C4ROOT_SOURCE_DIR}/analysis/online
${C4ROOT_SOURCE_DIR}/analysis/online/bgo
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
BGOOnlineSpectra.cxx
)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF BGOOnlineAnaLinkDef.h)

Set(DEPENDENCIES
GeoBase ParBase Base FairTools c4Base BGOData BaseData Core Geom GenVector Physics Matrix MathCore

)

Set(LIBRARY_NAME BGOOnlineAna)

GENERATE_LIBRARY()
