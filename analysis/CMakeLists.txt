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
${C4ROOT_SOURCE_DIR}/c4data/degasData
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
${C4ROOT_SOURCE_DIR}/c4data/digitisers/febexData
${C4ROOT_SOURCE_DIR}/c4data/digitisers/vmeData
${C4ROOT_SOURCE_DIR}/c4data/fimpData
${C4ROOT_SOURCE_DIR}/c4data/mcpData
${C4ROOT_SOURCE_DIR}/c4data/stefanData
${C4ROOT_SOURCE_DIR}/analysis
${C4ROOT_SOURCE_DIR}/analysis/frs
${C4ROOT_SOURCE_DIR}/analysis/pars
${C4ROOT_SOURCE_DIR}/analysis/offline
${C4ROOT_SOURCE_DIR}/analysis/nearline
${C4ROOT_SOURCE_DIR}/analysis/nearline/bplast
${C4ROOT_SOURCE_DIR}/analysis/online
${C4ROOT_SOURCE_DIR}/analysis/online/frs
${C4ROOT_SOURCE_DIR}/analysis/correlations
${C4ROOT_SOURCE_DIR}/analysis/nearline/degas
${C4ROOT_SOURCE_DIR}/analysis/nearline/fatima
${C4ROOT_SOURCE_DIR}/analysis/online/degas
${C4ROOT_SOURCE_DIR}/analysis/online/fatima
${C4ROOT_SOURCE_DIR}/analysis/online/bplast
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/frs
${C4ROOT_SOURCE_DIR}/c4source/base
${C4ROOT_SOURCE_DIR}/c4source/degas
${C4ROOT_SOURCE_DIR}/c4source/digitisers/febex
${C4ROOT_SOURCE_DIR}/c4source/bplast
${C4ROOT_SOURCE_DIR}/c4source/bb7
${C4ROOT_SOURCE_DIR}/c4source/fimp
${C4ROOT_SOURCE_DIR}/c4source/mcp
${C4ROOT_SOURCE_DIR}/c4source/stefan
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

set(SRCS
#online
./online/germanium/GermaniumOnlineSpectra.cxx
./online/degas/DegasOnlineSpectra.cxx
./online/germanium/GermaniumLabTest.cxx
./online/degas/DegasLabTest.cxx
./nearline/germanium/GermaniumResolution.cxx
./nearline/degas/DegasResolution.cxx
./online/beammonitor/BeamMonitorOnlineSpectra.cxx
./online/lisa/LisaOnlineSpectra.cxx
./online/lisa/LisaOnlineSpectraDaq.cxx
./online/aida/AidaOnlineSpectra.cxx
./online/aida/AidaPulserWalkthrough.cxx
./online/bplast/bPlastOnlineSpectra.cxx
./online/fatima/FatimaOnlineSpectra.cxx
./online/fatima/FatimaVmeOnlineSpectra.cxx
./online/frs/FrsOnlineSpectra.cxx
./online/frs/FrsRawSpectra.cxx
./online/frs/FrsCalSpectra.cxx
./online/bgo/BGOOnlineSpectra.cxx
./online/degas/DegasBGOOnlineSpectra.cxx
./online/bb7/BB7OnlineSpectra.cxx
./online/bb7/BB7FebexOnlineSpectra.cxx
./online/fimp/FimpOnlineSpectra.cxx
./online/mcp/H10MCPOnlineSpectra.cxx
./online/stefan/StefanOnlineSpectra.cxx

# nearline/offline
./nearline/bplast/bPlastNearlineSpectra.cxx
./nearline/fatima/FatimaNearlineSpectra.cxx
./nearline/fatima/FatimaVmeNearlineSpectra.cxx
./nearline/aida/AidaNearlineSpectra.cxx
./nearline/frs/FrsNearlineSpectra.cxx
./nearline/frs/FrsRawNearlineSpectra.cxx
./nearline/germanium/GermaniumNearlineSpectra.cxx
./nearline/degas/DegasNearlineSpectra.cxx
./nearline/bgo/BGONearlineSpectra.cxx
./nearline/degas/DegasBGONearlineSpectra.cxx
./nearline/lisa/LisaNearlineSpectra.cxx
./nearline/lisa/LisaNearlineSpectraDaq.cxx
./nearline/lisa/LisaNearlineSpectraAna.cxx
./nearline/lisa/LisaTraceAnalysis.cxx
./nearline/lisa/LisaTraceCorrelation.cxx
./nearline/fimp/FimpNearlineSpectra.cxx
./nearline/bb7/BB7NearlineSpectra.cxx
./nearline/lisa/LisaNearlineSpectra.cxx
./nearline/mcp/H10MCPNearlineSpectra.cxx
./nearline/stefan/StefanNearlineSpectra.cxx

## correlations ##
./correlations/online/TimeMachineOnline.cxx
./correlations/online/WhiterabbitCorrelationOnline.cxx
./correlations/nearline/WhiterabbitCorrelationNearline.cxx
./correlations/nearline/TimeMachineNearline.cxx
./correlations/IonCorrelations.cxx
./correlations/online/IonCorrelationsOnline.cxx
./correlations/nearline/IonCorrelationsNearline.cxx
./correlations/FrsAidaCorrelations.cxx
./correlations/online/FrsAidaCorrelationsOnline.cxx
./correlations/FrsFatimaCorrelations.cxx
./correlations/FrsGermaniumCorrelations.cxx
./correlations/FrsDegasCorrelations.cxx
./correlations/nearline/FrsFatimaCorrelationsNearline.cxx
./correlations/nearline/FrsGermaniumCorrelationsNearline.cxx
./correlations/nearline/FrsDegasCorrelationsNearline.cxx
./correlations/AidaFatimaCorrelations.cxx
./nearline/fatima/FatimaTimingAnalysis.cxx
./nearline/fatima/FatimaTimingAnalysisSummed.cxx
./correlations/nearline/FatimaTimingAnalysisSummedGeGated.cxx
./correlations/nearline/FatimaTimingAnalysisSummedDegasGated.cxx
./nearline/fatima/FatimaSinglesAnalysis.cxx
./correlations/AidaGermaniumCorrelations.cxx
./correlations/AidaDegasCorrelations.cxx
./correlations/bPlastGermaniumCorrelations.cxx
./correlations/bPlastDegasCorrelations.cxx
./correlations/online/bPlastGermaniumCorrelationsOnline.cxx
./correlations/online/bPlastDegasCorrelationsOnline.cxx
./correlations/online/BB7GermaniumCorrelationsOnline.cxx
./correlations/online/BB7DegasCorrelationsOnline.cxx
./correlations/triplePlusCorrs/BetaIonCorrelations.cxx
./correlations/triplePlusCorrs/BetaIonDegasCorrelations.cxx


./correlations/online/LisaFrsCorrelationsOnline.cxx
./correlations/LisaFrsCorrelations.cxx

)


#file(GLOB SRCS ./online/*.cxx ./offline/*.cxx ./pars/*.cxx)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF AnaLinkDef.h)

# Set(DEPENDENCIES
# GeoBase ParBase MbsAPI Base FairTools c4Base c4Data Core Geom GenVector Physics Matrix MathCore

# )

Set(DEPENDENCIES
GeoBase ParBase Base FairTools Online c4Base c4Data Core Geom GenVector Physics Matrix MathCore

)

Set(LIBRARY_NAME c4Analysis)

GENERATE_LIBRARY()
