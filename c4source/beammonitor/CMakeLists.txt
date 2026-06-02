set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
${ucesb_INCLUDE_DIR}
)

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/base
${C4ROOT_SOURCE_DIR}/c4source/beammonitor
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
${C4ROOT_SOURCE_DIR}/c4data/baseData
)

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
${ucesb_LIBRARY_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories( ${LINK_DIRECTORIES})

set(SRCS
BeamMonitorReader.cxx
)

Set(STRUCT_HEADERS
ext_h101_beammonitor.h
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF BeamMonitorSourceLinkDef.h)
set(DEPENDENCIES
    GeoBase ParBase Base FairTools
    c4Base BeamMonitorData BaseData Core Geom GenVector
    Physics Matrix MathCore
    ${ucesb_LIBRARY_SHARED})
#MbsAPI
set(LIBRARY_NAME BeamMonitorSource)

GENERATE_LIBRARY()
