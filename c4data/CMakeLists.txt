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
${C4ROOT_SOURCE_DIR}/c4data/stefanData
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/base
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR})

link_directories(${LINK_DIRECTORIES})

if (LISA_ONLY)
    set(SRCS
    frsData/FrsData.cxx
    frsData/FrsCalData.cxx
    frsData/FrsHitData.cxx
    lisaData/LisaData.cxx
    lisaData/LisaCalData.cxx
    lisaData/LisaAnaData.cxx
    lisaData/LisaHitData.cxx
    lisaData/LisaHistoData.cxx
    lisaData/LisaTraceData.cxx
    frsData/TFRSParameter.cxx
    frsData/TFrsConfiguration.cxx
    frsData/FrsGate.cxx
    # frsData/FrsStructures.cxx
    baseData/TCorrelationsConfiguration.cxx
    baseData/TExperimentConfiguration.cxx
    lisaData/TLisaConfiguration.cxx
    lisaData/LisaGate.cxx)

    set(SRC_CLASSES
    FrsTpatItem
    FrsScalerItem
    FrsMusicItem
    FrsSciItem
    FrsTpcItem
    FrsCalSciItem
    FrsCalMusicItem
    FrsCalTpcItem
    FrsHitItem
    FrsMultiHitItem
    FrsGate
    Scintillator
    ParticleID
    TFrsConfiguration
    TFRSParameter
    TMWParameter
    TTPCParameter
    TMUSICParameter
    TSCIParameter
    TIDParameter
    TSIParameter
    TRangeParameter
    TLABRParameter
    TMRTOFMSParameter
    LisaItem
    LisaCalItem
    LisaAnaItem
    LisaHitItem
    LisaHistoItem
    LisaTraceData
    LisaGate
    )
endif()

if (NOT LISA_ONLY)
    set(SRCS
    frsData/FrsData.cxx
    frsData/FrsCalData.cxx
    frsData/FrsHitData.cxx
    lisaData/LisaData.cxx
    lisaData/LisaCalData.cxx
    lisaData/LisaAnaData.cxx
    lisaData/LisaHitData.cxx
    lisaData/LisaHistoData.cxx
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
    bb7Data/BB7FebexData.cxx
    bb7Data/BB7FebexCalData.cxx
    bb7Data/BB7FebexHitData.cxx
    bb7Data/TBB7VmeConfiguration.cxx
    bb7Data/TBB7FebexConfiguration.cxx
    fimpData/FimpData.cxx
    fimpData/FimpCalData.cxx
    fimpData/TFimpConfiguration.cxx
    mcpData/H10MCPTwinpeaksData.cxx
    mcpData/H10MCPTwinpeaksCalData.cxx
    mcpData/H10MCPTwinpeaksAnaData.cxx
    mcpData/TH10MCPConfiguration.cxx
    stefanData/StefanFebexData.cxx
    stefanData/StefanCalData.cxx
    stefanData/TStefanConfiguration.cxx
    frsData/TFRSParameter.cxx
    frsData/TFrsConfiguration.cxx
    frsData/FrsGate.cxx
    # frsData/FrsStructures.cxx
    baseData/TCorrelationsConfiguration.cxx
    baseData/TExperimentConfiguration.cxx
    lisaData/TLisaConfiguration.cxx
    lisaData/LisaGate.cxx
    )
endif()

# Generate LinkDef
if (LISA_ONLY)
    set(LINKDEF "${CMAKE_CURRENT_BINARY_DIR}/DataLinkDef.h")
    file(WRITE ${LINKDEF} "// Auto-generated LinkDef\n#ifdef __CINT__\n")
    file(APPEND ${LINKDEF} "#pragma link off all globals;\n")
    file(APPEND ${LINKDEF} "#pragma link off all classes;\n")
    file(APPEND ${LINKDEF} "#pragma link off all functions;\n\n")
    foreach(cls IN LISTS SRC_CLASSES)
        file(APPEND ${LINKDEF} "#pragma link C++ class ${cls}+;\n")
    endforeach()
    file(APPEND ${LINKDEF} "#endif\n")
else()
    set(LINKDEF DataLinkDef.h) #everything
endif()

# fill list of header files from list of source files by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

#set(LINKDEF DataLinkDef.h)
set(LIBRARY_NAME c4Data)

set(DEPENDENCIES Base FairTools FairLogger::FairLogger)

GENERATE_LIBRARY()
