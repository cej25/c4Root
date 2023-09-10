Set(SYSTEM_INCLUDE_DIRECTORIES 
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located 
${C4ROOT_SOURCE_DIR}/c4data 
${C4ROOT_SOURCE_DIR}/compilehelper
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINCLUDE_DIRECTORIES=\"${INCLUDE_DIRECTORIES};${SYSTEM_INCLUDE_DIRECTORIES}\"" )

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
c4MacroCompiler.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF LinkDef.h)
set(LIBRARY_NAME c4MacroCompiler)
set(DEPENDENCIES
    c4Data)

GENERATE_LIBRARY()

