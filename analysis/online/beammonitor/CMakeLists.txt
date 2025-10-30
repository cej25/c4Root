Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
${C4ROOT_SOURCE_DIR}/analysis
${C4ROOT_SOURCE_DIR}/analysis/online
${C4ROOT_SOURCE_DIR}/analysis/online/beammonitor
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/base
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
BeamMonitorOnlineSpectra.cxx
)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

#online but there is no nearline
Set(LINKDEF BeamMonitorAnaLinkDef.h)

Set(DEPENDENCIES
GeoBase ParBase Base FairTools c4Base BeamMonitorData BaseData Core Geom GenVector Physics Matrix MathCore

)

Set(LIBRARY_NAME BeamMonitorAna)

GENERATE_LIBRARY()
