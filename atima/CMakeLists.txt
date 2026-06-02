# ============================================================
# ATIMA module CMake configuration
# ============================================================

# --- System includes from base and other dependencies ---
set(SYSTEM_INCLUDE_DIRECTORIES 
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${BASE_INCLUDE_DIRECTORIES}
)

if(DEFINED ENV{CATIMA_PATH})
    set(CATIMA_PATH $ENV{CATIMA_PATH})
else()
    message(WARNING "CATIMA_PATH environment variable not set. Using default: /u/cjones/catima")
    set(CATIMA_PATH /u/cjones/catima)
endif()

set(CATIMA_INCLUDE_DIR ${CATIMA_PATH}/include)
set(CATIMA_LIBRARY_DIR ${CATIMA_PATH}/lib)
set(CATIMA_LIBRARY ${CATIMA_LIBRARY_DIR}/libcatima.so)

set(ATIMA_INCLUDE_DIR ${C4ROOT_SOURCE_DIR}/atima)

set(SRCS
    Atima.cxx
)

set(HEADERS
    Atima.h
)

set(LIBRARY_NAME c4Atima)

add_library(${LIBRARY_NAME} SHARED ${SRCS} ${HEADERS})

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${ATIMA_INCLUDE_DIR}       # Your module's headers
        ${CATIMA_INCLUDE_DIR}      # Catima headers, needed in Atima.h
        ${SYSTEM_INCLUDE_DIRECTORIES}  # Base/system headers
)

target_link_libraries(${LIBRARY_NAME}
    PRIVATE
        FairLogger::FairLogger
        ${CATIMA_LIBRARY}
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    BUILD_RPATH "${CATIMA_LIBRARY_DIR}"
)

link_directories(
    ${ROOT_LIBRARY_DIR}
    ${FAIRROOT_LIBRARY_DIR}
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
)


message(STATUS "Configured ${LIBRARY_NAME} with Catima support")
message(STATUS "  Catima include dir: ${CATIMA_INCLUDE_DIR}")
message(STATUS "  Catima library: ${CATIMA_LIBRARY}")
