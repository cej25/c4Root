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
${C4ROOT_SOURCE_DIR}/c4data/bgoData
${C4ROOT_SOURCE_DIR}/c4data/lisaData
${C4ROOT_SOURCE_DIR}/c4data/wrData
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
${C4ROOT_SOURCE_DIR}/c4data/timemachineData
${C4ROOT_SOURCE_DIR}/c4data/baseData
${C4ROOT_SOURCE_DIR}/c4data/bb7Data
${C4ROOT_SOURCE_DIR}/c4data/fimpData
${C4ROOT_SOURCE_DIR}/analysis
${C4ROOT_SOURCE_DIR}/analysis/frs
${C4ROOT_SOURCE_DIR}/analysis/pars
${C4ROOT_SOURCE_DIR}/analysis/offline
${C4ROOT_SOURCE_DIR}/analysis/nearline
${C4ROOT_SOURCE_DIR}/analysis/nearline/bplast
${C4ROOT_SOURCE_DIR}/analysis/online
${C4ROOT_SOURCE_DIR}/analysis/online/frs
${C4ROOT_SOURCE_DIR}/correlations
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/frs
${C4ROOT_SOURCE_DIR}/c4source/base
${C4ROOT_SOURCE_DIR}/c4source/bplast
${C4ROOT_SOURCE_DIR}/c4source/bb7
${C4ROOT_SOURCE_DIR}/c4source/fimp
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
#online
./online/germanium/GermaniumOnlineSpectra.cxx
./nearline/germanium/GermaniumResolution.cxx
./online/beammonitor/BeamMonitorOnlineSpectra.cxx
./online/lisa/LisaOnlineSpectra.cxx
./online/aida/AidaOnlineSpectra.cxx
./online/bplast/bPlastOnlineSpectra.cxx
./online/fatima/FatimaOnlineSpectra.cxx
./online/fatima/FatimaVmeOnlineSpectra.cxx
./online/frs/FrsOnlineSpectra.cxx
./online/frs/FrsRawSpectra.cxx
./online/frs/FrsCalSpectra.cxx
./online/frs/FrsTravMusSpectra.cxx
./online/bgo/BGOOnlineSpectra.cxx
./online/timemachine/TimeMachineOnline.cxx
./online/wr/WhiterabbitCorrelationOnline.cxx
./online/bb7/BB7OnlineSpectra.cxx
./online/fimp/FimpOnlineSpectra.cxx

# nearline/offline
./nearline/bplast/bPlastNearlineSpectra.cxx
./nearline/fatima/FatimaNearlineSpectra.cxx
./nearline/fatima/FatimaVmeNearlineSpectra.cxx
./nearline/aida/AidaNearlineSpectra.cxx
./nearline/frs/FrsNearlineSpectra.cxx
./nearline/frs/FrsNearlineTravMusSpectra.cxx
./nearline/germanium/GermaniumNearlineSpectra.cxx
./nearline/bgo/BGONearlineSpectra.cxx
./nearline/wr/WhiterabbitCorrelationNearline.cxx
./nearline/timemachine/TimeMachineNearline.cxx
./nearline/fimp/FimpNearlineSpectra.cxx
./nearline/bb7/BB7NearlineSpectra.cxx
./nearline/lisa/LisaNearlineSpectra.cxx

## correlations ##
./correlations/FrsAidaCorrelations.cxx
./online/onlineCorrelations/FrsAidaCorrelationsOnline.cxx
./correlations/FrsFatimaCorrelations.cxx
#./correlations/FrsFatimaVmeCorrelations.cxx
./correlations/FrsGermaniumCorrelations.cxx
./correlations/FrsFatimaCorrelationsNearline.cxx
./correlations/FrsGermaniumCorrelationsNearline.cxx
./correlations/AidaFatimaCorrelations.cxx
./nearline/fatima/FatimaTimingAnalysis.cxx
./nearline/fatima/FatimaSinglesAnalysis.cxx
./correlations/AidaGermaniumCorrelations.cxx
./correlations/bPlastGermaniumCorrelations.cxx
./online/onlineCorrelations/bPlastGermaniumCorrelationsOnline.cxx


./frs/MHTDCSpectra.cxx
./frs/TPCCorrections.cxx
#./correlations/FrsBplastCorrelations.cxx
./online/onlineCorrelations/LisaFrsCorrelationsOnline.cxx
./correlations/LisaFrsCorrelations.cxx

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
