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
${C4ROOT_SOURCE_DIR}/c4source/fatima
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/fatimaData
${C4ROOT_SOURCE_DIR}/c4data/baseData
${C4ROOT_SOURCE_DIR}/c4data/timemachineData
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
FatimaReader.cxx
FatimaRaw2Cal.cxx
FatimaVmeReader.cxx
FatimaVmeRaw2Cal.cxx
)

Set(STRUCT_HEADERS
ext_h101_fatima.h
ext_h101_fatimavme.h
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF FatimaSourceLinkDef.h)
set(DEPENDENCIES
    GeoBase ParBase Base FairTools
    c4Base FatimaData BaseData Core Geom GenVector
    Physics Matrix MathCore
    ${ucesb_LIBRARY_SHARED})

set(LIBRARY_NAME FatimaSource)

GENERATE_LIBRARY()
