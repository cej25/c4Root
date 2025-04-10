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
${C4ROOT_SOURCE_DIR}/c4source/bgo
${C4ROOT_SOURCE_DIR}/c4source/beammonitor
${C4ROOT_SOURCE_DIR}/c4source/bb7
${C4ROOT_SOURCE_DIR}/c4source/fimp
${C4ROOT_SOURCE_DIR}/c4source/mcp
${C4ROOT_SOURCE_DIR}/c4source/stefan
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/frsData
${C4ROOT_SOURCE_DIR}/c4data/lisaData
${C4ROOT_SOURCE_DIR}/c4data/bgoData
${C4ROOT_SOURCE_DIR}/c4data/wrData
${C4ROOT_SOURCE_DIR}/c4data/aidaData
${C4ROOT_SOURCE_DIR}/c4data/bplastData
${C4ROOT_SOURCE_DIR}/c4data/fatimaData
${C4ROOT_SOURCE_DIR}/c4data/germaniumData
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
${C4ROOT_SOURCE_DIR}/c4data/timemachineData
${C4ROOT_SOURCE_DIR}/c4data/bb7Data
${C4ROOT_SOURCE_DIR}/c4data/fimpData
${C4ROOT_SOURCE_DIR}/c4data/mcpData
${C4ROOT_SOURCE_DIR}/c4data/stefanData
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
./base/UcesbSource.cxx
./base/UnpackReader.cxx
./base/c4Reader.cxx
./base/CorrelationsMap.cxx
./base/GainShift.cxx
./aida/AidaReader.cxx
./aida/AidaCal2Hit.cxx
./aida/AidaUnpack2Cal.cxx
./frs/FrsReader.cxx
./frs/FrsRaw2Cal.cxx
./frs/FrsCal2Hit.cxx
./germanium/GermaniumReader.cxx
./germanium/GermaniumTraceReader.cxx
./lisa/LisaReader.cxx
./lisa/LisaAna2Cal.cxx
./lisa/LisaRaw2Ana.cxx
./bplast/bPlastReader.cxx
./bplast/bPlastRaw2Cal.cxx
./beammonitor/BeamMonitorReader.cxx
./germanium/GermaniumRaw2Cal.cxx
./germanium/GermaniumCal2Anl.cxx
./fatima/FatimaReader.cxx
./fatima/FatimaRaw2Cal.cxx
./bgo/BGOReader.cxx
./bgo/BGORaw2Cal.cxx
./fatima/FatimaVmeReader.cxx
./fatima/FatimaVmeRaw2Cal.cxx
./bb7/BB7Reader.cxx
./bb7/BB7FebexReader.cxx
./bb7/BB7Raw2Cal.cxx
./bb7/BB7FebexRaw2Cal.cxx
./bb7/BB7FebexCal2Hit.cxx
./fimp/FimpReader.cxx
./fimp/FimpRaw2Cal.cxx
./mcp/H10MCPReader.cxx
./mcp/H10MCPRaw2Cal.cxx
./mcp/H10MCPCal2Ana.cxx
./stefan/StefanReader.cxx
./stefan/StefanRaw2Cal.cxx

./test/TestReader.cxx
)

Set(STRUCT_HEADERS
./base/ext_h101_unpack.h
./aida/ext_h101_aida.h
./frs/ext_h101_frs.h
./lisa/ext_h101_lisa.h
./germanium/ext_h101_germanium.h
./germanium/ext_h101_germanium_traces.h
./bplast/ext_h101_bplast.h
./beammonitor/ext_h101_beammonitor.h
./fatima/ext_h101_fatima.h
./fatima/ext_h101_fatimavme.h
./bgo/ext_h101_bgo.h
# ./bb7/ext_h101_bb7vme.h
./bb7/ext_h101_bbfebex.h
./fimp/ext_h101_fimp.h
./mcp/ext_h101_mcp.h
./stefan/ext_h101_stefan.h

./test/ext_h101_test.h
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF SourceLinkDef.h)
set(DEPENDENCIES
    GeoBase ParBase Base FairTools
    c4Base c4Data Core Geom GenVector
    Physics Matrix MathCore
    ${ucesb_LIBRARY_SHARED})
#MbsAPI
set(LIBRARY_NAME c4source)

GENERATE_LIBRARY()
