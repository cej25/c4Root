Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/aidaData
${C4ROOT_SOURCE_DIR}/analysis
${C4ROOT_SOURCE_DIR}/analysis/nearline
${C4ROOT_SOURCE_DIR}/analysis/nearline/aida
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/base
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
AidaNearlineSpectra.cxx
)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF AidaNearlineAnaLinkDef.h)

Set(DEPENDENCIES
GeoBase ParBase Base FairTools c4Base AidaData BaseData Core Geom GenVector Physics Matrix MathCore

)

Set(LIBRARY_NAME AidaNearlineAna)

GENERATE_LIBRARY()
