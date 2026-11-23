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
${C4ROOT_SOURCE_DIR}/c4data/fimpData
${C4ROOT_SOURCE_DIR}/c4data/mcpData
${C4ROOT_SOURCE_DIR}/c4data/tamexData
${C4ROOT_SOURCE_DIR}/c4data/febexData
${C4ROOT_SOURCE_DIR}/c4data/vmeData
${C4ROOT_SOURCE_DIR}/c4data/degasData
${C4ROOT_SOURCE_DIR}/c4data/stefanData
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/base
${C4ROOT_SOURCE_DIR}/c4source/frs
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR})

link_directories(${LINK_DIRECTORIES})

set(SRCS
frsData/FrsData.cxx
frsData/FrsCalData.cxx
frsData/FrsHitData.cxx
lisaData/LisaData.cxx
lisaData/LisaCalData.cxx
lisaData/LisaAnaData.cxx
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
vmeData/VmeDigitiserRawData.cxx
fatimaData/FatimaRawData.cxx
timemachineData/TimeMachineData.cxx
bb7Data/BB7RawData.cxx
bb7Data/BB7VmeCalData.cxx
bb7Data/BB7FebexCalData.cxx
bb7Data/BB7FebexHitData.cxx
bb7Data/TBB7VmeConfiguration.cxx
bb7Data/TBB7FebexConfiguration.cxx
fimpData/FimpData.cxx
fimpData/FimpCalData.cxx
fimpData/TFimpConfiguration.cxx
mcpData/H10MCPTwinpeaksData.cxx
tamexData/TamexRawData.cxx
febexData/FebexRawData.cxx
degasData/DegasRawData.cxx
mcpData/H10MCPTwinpeaksCalData.cxx
mcpData/H10MCPTwinpeaksAnaData.cxx
mcpData/TH10MCPConfiguration.cxx
stefanData/StefanFebexData.cxx
stefanData/StefanCalData.cxx
stefanData/StefanHitData.cxx
stefanData/TStefanConfiguration.cxx
frsData/TFRSParameter.cxx
frsData/TFrsConfiguration.cxx
frsData/FrsGate.cxx
baseData/TCorrelationsConfiguration.cxx
baseData/TExperimentConfiguration.cxx
lisaData/TLisaConfiguration.cxx
lisaData/LisaGate.cxx
)

# fill list of header files from list of source files by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF DataLinkDef.h)
set(LIBRARY_NAME c4Data)
set(DEPENDENCIES c4Base Base FairTools FairLogger::FairLogger Core RIO Hist Graf)


generate_library()
