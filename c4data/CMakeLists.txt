set(SYSTEM_INCLUDE_DIRECTORIES ${SYSTEM_INCLUDE_DIRECTORIES} ${BASE_INCLUDE_DIRECTORIES})

set(INCLUDE_DIRECTORIES
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/frsData
${C4ROOT_SOURCE_DIR}/c4data/lisaData
${C4ROOT_SOURCE_DIR}/c4data/aidaData
${C4ROOT_SOURCE_DIR}/c4data/fatimaData
${C4ROOT_SOURCE_DIR}/c4data/bplastData
${C4ROOT_SOURCE_DIR}/c4data/bgoData
${C4ROOT_SOURCE_DIR}/c4data/germaniumData
${C4ROOT_SOURCE_DIR}/c4data/beammonitorData
${C4ROOT_SOURCE_DIR}/c4data/timemachineData
${C4ROOT_SOURCE_DIR}/c4data/baseData
${C4ROOT_SOURCE_DIR}/c4data/bb7Data
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/frs
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR})

link_directories(${LINK_DIRECTORIES})

set(SRCS
frsData/FrsMainData.cxx
frsData/FrsTPCData.cxx
frsData/FrsUserData.cxx
frsData/FrsVFTXData.cxx
frsData/FrsTpatData.cxx
frsData/FrsMainCalData.cxx
frsData/FrsTPCCalData.cxx
frsData/FrsUserCalData.cxx
frsData/FrsVFTXCalData.cxx
frsData/FrsHitData.cxx
lisaData/LisaData.cxx
lisaData/LisaCalData.cxx
lisaData/LisaTraceData.cxx
aidaData/AidaData.cxx
aidaData/AidaCalData.cxx
aidaData/AidaHitData.cxx
aidaData/TAidaConfiguration.cxx
germaniumData/GermaniumFebexData.cxx
germaniumData/GermaniumCalData.cxx
germaniumData/TGermaniumConfiguration.cxx
bplastData/bPlastTwinpeaksData.cxx
bplastData/bPlastTwinpeaksCalData.cxx
bplastData/TbPlastConfiguration.cxx
beammonitorData/BeamMonitorData.cxx
fatimaData/FatimaTwinpeaksData.cxx
fatimaData/FatimaTwinpeaksCalData.cxx
fatimaData/TFatimaTwinpeaksConfiguration.cxx
bgoData/BGOTwinpeaksData.cxx
bgoData/BGOTwinpeaksCalData.cxx
bgoData/TBGOTwinpeaksConfiguration.cxx
fatimaData/TFatimaVmeConfiguration.cxx
fatimaData/FatimaVmeData.cxx
fatimaData/FatimaVmeCalData.cxx
timemachineData/TimeMachineData.cxx
bb7Data/BB7VmeData.cxx
bb7Data/BB7VmeCalData.cxx
bb7Data/TBB7VmeConfiguration.cxx
fimpData/FimpData.cxx
fimpData/TFimpConfiguration.cxx
frsData/TFRSParameter.cxx
frsData/TFrsConfiguration.cxx
frsData/FrsGate.cxx
baseData/TCorrelationsConfiguration.cxx
lisaData/TLisaConfiguration.cxx
)

# fill list of header files from list of source files by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF DataLinkDef.h)
set(LIBRARY_NAME c4Data)
set(DEPENDENCIES Base FairTools ${VMCLIB} FairLogger::FairLogger)

generate_library()
