set(SYSTEM_INCLUDE_DIRECTORIES ${SYSTEM_INCLUDE_DIRECTORIES} ${BASE_INCLUDE_DIRECTORIES})

set(INCLUDE_DIRECTORIES
${C4ROOT_SOURCE_DIR}/c4base
${C4ROOT_SOURCE_DIR}/c4data
${C4ROOT_SOURCE_DIR}/c4data/fimpData
${C4ROOT_SOURCE_DIR}/c4source
${C4ROOT_SOURCE_DIR}/c4source/base
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR})

link_directories(${LINK_DIRECTORIES})

set(SRCS
FimpData.cxx
FimpCalData.cxx
TFimpConfiguration.cxx
)

# fill list of header files from list of source files by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF FimpDataLinkDef.h)
set(LIBRARY_NAME FimpData)

set(DEPENDENCIES Base FairTools FairLogger::FairLogger)

generate_library()
