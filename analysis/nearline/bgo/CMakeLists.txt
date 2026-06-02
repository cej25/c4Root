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
${C4ROOT_SOURCE_DIR}/analysis/nearline
${C4ROOT_SOURCE_DIR}/analysis/nearline/bgo
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
BGONearlineSpectra.cxx
)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF BGONearlineAnaLinkDef.h)

Set(DEPENDENCIES
GeoBase ParBase Base FairTools c4Base BGOData BaseData Core Geom GenVector Physics Matrix MathCore

)

Set(LIBRARY_NAME BGONearlineAna)

GENERATE_LIBRARY()
