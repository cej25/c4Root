Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/wrData
${C4ROOT_SOURCE_DIR}/c4data/frsData
${C4ROOT_SOURCE_DIR}/c4data/germaniumData
${C4ROOT_SOURCE_DIR}/c4data/aidaData
${C4ROOT_SOURCE_DIR}/c4data/bplastData
${C4ROOT_SOURCE_DIR}/c4data/fatimaData
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

link_directories(${FAIRROOT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

file(GLOB SRCS 
*.cxx 
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
install(FILES "c4Logger.h" DESTINATION include)

Set(LINKDEF BaseLinkDef.h)

# Set(DEPENDENCIES
#     GeoBase ParBase MbsAPI Base FairTools c4Data Core Geom GenVector Physics
#     Matrix MathCore Hist Graf Gpad Net Imt RIO RHTTP Spectrum)
Set(DEPENDENCIES
GeoBase ParBase Base FairTools c4Data Core Geom GenVector Physics
Matrix MathCore Hist Graf Gpad Net Imt RIO RHTTP Spectrum)

Set(LIBRARY_NAME c4Base)

GENERATE_LIBRARY()

