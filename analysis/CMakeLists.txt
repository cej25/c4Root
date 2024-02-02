Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/frsData
${C4ROOT_SOURCE_DIR}/c4data/germaniumData
${C4ROOT_SOURCE_DIR}/c4data/aidaData
${C4ROOT_SOURCE_DIR}/c4data/bplastData
${C4ROOT_SOURCE_DIR}/c4data/fatimaData
${C4ROOT_SOURCE_DIR}/c4data/lisaData
${C4ROOT_SOURCE_DIR}/c4data/wrData
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
${C4ROOT_SOURCE_DIR}/c4data/timemachineData
${C4ROOT_SOURCE_DIR}/analysis
${C4ROOT_SOURCE_DIR}/analysis/pars
${C4ROOT_SOURCE_DIR}/analysis/offline
${C4ROOT_SOURCE_DIR}/analysis/fatima_aida_correlations
${C4ROOT_SOURCE_DIR}/analysis/online
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
./online/GermaniumOnlineSpectra.cxx
./online/BeamMonitorOnlineSpectra.cxx
./online/LisaOnlineSpectra.cxx
./online/AidaOnlineSpectra.cxx
./online/bPlastOnlineSpectra.cxx
./online/FatimaOnlineSpectra.cxx
./online/FrsOnlineSpectra.cxx
./online/FrsDetectorsOnline.cxx
./fatima_aida_correlations/FatimaAidaSpectra.cxx
./online/TimeMachineOnline.cxx
)


#file(GLOB SRCS ./online/*.cxx ./offline/*.cxx ./pars/*.cxx)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF AnaLinkDef.h)

Set(DEPENDENCIES
GeoBase ParBase MbsAPI Base FairTools c4Base c4Data Core Geom GenVector Physics Matrix MathCore

)

Set(LIBRARY_NAME c4Analysis)

GENERATE_LIBRARY()
