# ============================================================
# ATIMA module CMake configuration
# ============================================================

# --- System includes from base and other dependencies ---
set(SYSTEM_INCLUDE_DIRECTORIES 
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${BASE_INCLUDE_DIRECTORIES}
)

# ============================================================
# --- Catima setup ---
# ============================================================
# Default Catima path (can be overridden with -DCATIMA_PATH=...)
if(NOT DEFINED CATIMA_PATH)
    set(CATIMA_PATH /u/cjones/catima)
endif()

set(CATIMA_INCLUDE_DIR ${CATIMA_PATH}/include)
set(CATIMA_LIBRARY_DIR ${CATIMA_PATH}/lib)
set(CATIMA_LIBRARY ${CATIMA_LIBRARY_DIR}/libcatima.so)

# ============================================================
# --- Local includes for this module ---
# ============================================================
set(ATIMA_INCLUDE_DIR ${C4ROOT_SOURCE_DIR}/atima)

# ============================================================
# --- Source files ---
# ============================================================
set(SRCS
    Atima.cxx
)

set(HEADERS
    Atima.h
)

# ============================================================
# --- Library target name ---
# ============================================================
set(LIBRARY_NAME c4Atima)

# ============================================================
# --- Generate the library ---
# ============================================================
add_library(${LIBRARY_NAME} SHARED ${SRCS} ${HEADERS})

# ============================================================
# --- Include directories ---
# ============================================================
# PUBLIC: visible to both this target and any consumer that includes Atima.h
target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${ATIMA_INCLUDE_DIR}       # Your module's headers
        ${CATIMA_INCLUDE_DIR}      # Catima headers, needed in Atima.h
        ${SYSTEM_INCLUDE_DIRECTORIES}  # Base/system headers
)

# ============================================================
# --- Link libraries ---
# ============================================================
# PRIVATE: only used for building this target
target_link_libraries(${LIBRARY_NAME}
    PRIVATE
        FairLogger::FairLogger
        ${CATIMA_LIBRARY}
)

# ============================================================
# --- Link directories ---
# ============================================================
# Use BUILD_RPATH so runtime can find shared libraries
set_target_properties(${LIBRARY_NAME} PROPERTIES
    BUILD_RPATH "${CATIMA_LIBRARY_DIR}"
)

# ============================================================
# --- Optional ROOT/FairRoot dependencies ---
# ============================================================
link_directories(
    ${ROOT_LIBRARY_DIR}
    ${FAIRROOT_LIBRARY_DIR}
)

# ============================================================
# --- LinkDef (if ROOT dictionary generation is needed) ---
# ============================================================
# ROOT macros may need this, include as required
set_target_properties(${LIBRARY_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
)

# ============================================================
# --- Status message ---
# ============================================================
message(STATUS "Configured ${LIBRARY_NAME} with Catima support")
message(STATUS "  Catima include dir: ${CATIMA_INCLUDE_DIR}")
message(STATUS "  Catima library: ${CATIMA_LIBRARY}")
