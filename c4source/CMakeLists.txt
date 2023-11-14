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
${C4ROOT_SOURCE_DIR}/c4source/wr
${C4ROOT_SOURCE_DIR}/c4source/frs
${C4ROOT_SOURCE_DIR}/c4source/lisa
${C4ROOT_SOURCE_DIR}/c4source/aida
${C4ROOT_SOURCE_DIR}/c4source/bplast
${C4ROOT_SOURCE_DIR}/c4source/fatima
${C4ROOT_SOURCE_DIR}/c4source/germanium
${C4ROOT_SOURCE_DIR}/c4source/beammonitor
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/frsData
${C4ROOT_SOURCE_DIR}/c4data/lisaData
${C4ROOT_SOURCE_DIR}/c4data/wrData
${C4ROOT_SOURCE_DIR}/c4data/aidaData
${C4ROOT_SOURCE_DIR}/c4data/bplastData
${C4ROOT_SOURCE_DIR}/c4data/fatimaData
${C4ROOT_SOURCE_DIR}/c4data/germaniumData
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
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
./base/UcesbSource.cxx
./base/UnpackReader.cxx
./base/c4Reader.cxx
./aida/c4AidaReader.cxx
./aida/AidaCal2Hit.cxx
./aida/AidaUnpack2Cal.cxx
./frs/FrsReader.cxx
./germanium/GermaniumReader.cxx
./lisa/LisaReader.cxx
./bplast/bPlastReader.cxx
./bplast/bPlastRaw2Cal.cxx
./beammonitor/BeamMonitorReader.cxx
./germanium/GermaniumRaw2Cal.cxx
./fatima/FatimaReader.cxx
./fatima/FatimaRaw2Cal.cxx
)

Set(STRUCT_HEADERS
./base/ext_h101_unpack.h
./aida/ext_h101_aida.h
./frs/ext_h101_frs.h
./lisa/ext_h101_lisa.h
./germanium/ext_h101_germanium.h
./bplast/ext_h101_bplast.h
./beammonitor/ext_h101_bm.h
./fatima/ext_h101_fatima.h
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF SourceLinkDef.h)
set(DEPENDENCIES
    GeoBase ParBase MbsAPI Base FairTools
    c4Base c4Data Core Geom GenVector
    Physics Matrix MathCore
    ${ucesb_LIBRARY_SHARED})
set(LIBRARY_NAME c4source)

GENERATE_LIBRARY()
