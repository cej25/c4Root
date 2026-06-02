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
${C4ROOT_SOURCE_DIR}/c4source/lisa
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/lisaData
${C4ROOT_SOURCE_DIR}/c4data/frsData
${C4ROOT_SOURCE_DIR}/c4data/baseData
)

if (WITH_ATIMA)
    list(APPEND INCLUDE_DIRECTORIES ${C4ROOT_SOURCE_DIR}/atima)
endif()

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
${ucesb_LIBRARY_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories( ${LINK_DIRECTORIES})

set(SRCS
LisaReader.cxx
LisaRaw2Ana.cxx
LisaAna2Cal.cxx
LisaCal2Hit.cxx
LisaHit2Histo.cxx
)

Set(STRUCT_HEADERS
ext_h101_lisa.h
)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF LisaSourceLinkDef.h)
set(DEPENDENCIES
    GeoBase ParBase Base FairTools
    c4Base LisaData BaseData Core Geom GenVector
    Physics Matrix MathCore
    ${ucesb_LIBRARY_SHARED})
if (WITH_ATIMA)
    list(APPEND DEPENDENCIES c4Atima)
endif()
    
set(LIBRARY_NAME LisaSource)

GENERATE_LIBRARY()
