# ==============================================================================
# c4Root
# ==============================================================================

cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

# Keep policy behaviour compatible with the historical c4Root/FairRoot build
# system while allowing newer CMake versions.
cmake_policy(VERSION 3.11...3.31)

project(C4ROOT LANGUAGES C CXX)


# ==============================================================================
# Prevent in-source builds
# ==============================================================================

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR
        "In-source builds are not supported. "
        "Please create a separate build directory."
    )
endif()


# ==============================================================================
# Check source tree
# ==============================================================================

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/macros")
    message(FATAL_ERROR
        "\nmacros repository is missing in the c4Root source directory\n"
        "cd ${CMAKE_SOURCE_DIR}\n"
        "git clone -b dev <github_link>"
    )
endif()


# ==============================================================================
# FairRoot location
#
# c4Root deliberately does NOT require SIMPATH/FairSoft.
#
# FAIRROOTPATH is retained for compatibility with FairRoot 18.x and existing
# c4Root installations.
# ==============================================================================

if(NOT DEFINED ENV{FAIRROOTPATH})
    message(FATAL_ERROR
        "FAIRROOTPATH is not defined. "
        "Please set FAIRROOTPATH to your FairRoot installation."
    )
endif()

set(FAIRROOTPATH "$ENV{FAIRROOTPATH}")

string(REGEX MATCHALL "[^:]+" PATH "$ENV{PATH}")


# ==============================================================================
# FairRoot version
#
# Determine this before selecting the FairRoot-18/FairRoot-19 CMake path.
# ==============================================================================

if(EXISTS "${FAIRROOTPATH}/bin/fairroot-config")

    execute_process(
        COMMAND "${FAIRROOTPATH}/bin/fairroot-config" --version
        COMMAND sed "s/^v//"
        OUTPUT_VARIABLE FairRoot_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE FAIRROOT_CONFIG_RESULT
    )

    if(NOT FAIRROOT_CONFIG_RESULT EQUAL 0)
        message(FATAL_ERROR
            "Could not determine FairRoot version using fairroot-config."
        )
    endif()

else()

    message(FATAL_ERROR
        "Could not find:\n"
        "  ${FAIRROOTPATH}/bin/fairroot-config\n"
        "Please check FAIRROOTPATH."
    )

endif()


if("${FairRoot_VERSION}" VERSION_LESS "18.2.1")

    message(FATAL_ERROR
        "Incompatible FairRoot version detected: ${FairRoot_VERSION}\n"
        "c4Root requires FairRoot 18.2.1 or later."
    )

endif()

message(STATUS "Using FairRoot ${FairRoot_VERSION}")


# ==============================================================================
# CMake module paths
# ==============================================================================

set(
    CMAKE_MODULE_PATH
    "${FAIRROOTPATH}/share/fairbase/cmake/modules"
    "${CMAKE_SOURCE_DIR}/cmake/modules"
    ${CMAKE_MODULE_PATH}
)

set(
    CheckSrcDir
    "${FAIRROOTPATH}/share/fairbase/cmake/checks"
)


# ==============================================================================
# FairRoot CMake compatibility
#
# FairRoot >= 19:
#   FairFindPackage2 lives in FairCMakeModules.
#
# FairRoot 18:
#   Some later releases can also use FairCMakeModules, while older releases
#   may provide the required helpers through FairRoot itself.
# ==============================================================================

if("${FairRoot_VERSION}" VERSION_GREATER_EQUAL "19.0")

    find_package(FairCMakeModules 1.0 REQUIRED)
    include(FairFindPackage2)

else()

    # FairRoot 18.x compatibility.
    #
    # Prefer FairCMakeModules where available (e.g. newer 18.x installations),
    # but do not make it an unconditional c4Root requirement for all 18.x.
    find_package(FairCMakeModules 1.0 QUIET)

    if(FairCMakeModules_FOUND)

        include(FairFindPackage2)

    elseif(EXISTS
           "${FAIRROOTPATH}/share/fairbase/cmake/modules/FairFindPackage2.cmake")

        include(
            "${FAIRROOTPATH}/share/fairbase/cmake/modules/FairFindPackage2.cmake"
        )

    else()

        message(STATUS
            "FairFindPackage2 is not available. "
            "Using standard CMake find_package() for FairRoot 18 compatibility."
        )

    endif()

endif()


# ==============================================================================
# Package-finding compatibility wrapper
#
# find_package2() is preferred when available because this is what the
# historical FairRoot/c4Root build infrastructure expects.
#
# Standard find_package() is used as a fallback.
# ==============================================================================

macro(c4_find_package VISIBILITY PACKAGE_NAME)

    if(COMMAND find_package2)

        find_package2(
            ${VISIBILITY}
            ${PACKAGE_NAME}
            ${ARGN}
        )

    else()

        find_package(
            ${PACKAGE_NAME}
            ${ARGN}
        )

    endif()

endmacro()


# ==============================================================================
# FairRoot
# ==============================================================================

c4_find_package(
    PUBLIC
    FairRoot
    REQUIRED
)


# ==============================================================================
# FairRoot/c4Root macros
# ==============================================================================

include(FairMacros)

include(c4Macros)
include(WriteConfigFile_c4)
include(WriteEnvCache)
include(CheckCompiler)


# ==============================================================================
# Required c4Root dependencies
# ==============================================================================

c4_find_package(
    PUBLIC
    ROOT
    VERSION 6.10.00
    REQUIRED
)

c4_find_package(
    PUBLIC
    FairLogger
    VERSION 1.2.0
    REQUIRED
)


# ==============================================================================
# FairLogger dependencies
#
# FairLogger is genuinely used directly by c4Root.
#
# Boost is deliberately not propagated as a c4Root dependency. c4Root itself
# contains no Boost usage.
# ==============================================================================

foreach(dep IN LISTS FairLogger_PACKAGE_DEPENDENCIES)

    if(NOT dep STREQUAL "Boost")

        if(COMMAND find_package2)

            find_package2(
                PUBLIC
                ${dep}
                REQUIRED
                VERSION ${FairLogger_${dep}_VERSION}
            )

        else()

            if(DEFINED FairLogger_${dep}_VERSION)

                find_package(
                    ${dep}
                    ${FairLogger_${dep}_VERSION}
                    REQUIRED
                )

            else()

                find_package(
                    ${dep}
                    REQUIRED
                )

            endif()

        endif()

    endif()

endforeach()


# ==============================================================================
# ROOT/FairRoot dictionary macros
#
# FairRoot 19 requires ROOTMacros to be included after finding ROOT.
# This is also safe for supported FairRoot 18 installations.
# ==============================================================================

find_package(VMC QUIET)

if(VMC_FOUND)
    message(STATUS "Found VMC required by FairRoot: ${VMC_INCLUDE_DIRS}")

    list(APPEND
        BASE_INCLUDE_DIRECTORIES
        ${VMC_INCLUDE_DIRS}
    )

    include_directories(
        ${VMC_INCLUDE_DIRS}
    )
else()
    message(FATAL_ERROR
        "FairRoot ${FairRoot_VERSION} requires VMC headers, "
        "but VMC could not be found. In particular, TMCtls.h is required "
        "by FairLinkManager.h."
    )
endif()

include(ROOTMacros)


# ==============================================================================
# ROOT dictionary-generator compatibility
#
# Older FairRoot ROOTMacros search for "rootcint".
#
# Older ROOT installations may genuinely provide rootcint, in which case it
# is retained.
#
# Modern ROOT installations provide rootcling instead. If rootcint was not
# found, use rootcling as the dictionary generator.
# ==============================================================================

if(NOT ROOT_CINT_EXECUTABLE
   OR ROOT_CINT_EXECUTABLE MATCHES "-NOTFOUND$")

    # ROOT_BINDIR is normally supplied by ROOT's CMake configuration.
    #
    # Obtain it from root-config as an additional compatibility mechanism.
    if(NOT ROOT_BINDIR AND ROOT_CONFIG_EXECUTABLE)

        execute_process(
            COMMAND "${ROOT_CONFIG_EXECUTABLE}" --bindir
            OUTPUT_VARIABLE ROOT_BINDIR
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

    endif()

    find_program(
        C4ROOT_ROOTCLING_EXECUTABLE
        NAMES rootcling
        HINTS
            "${ROOT_BINDIR}"
            "${ROOTSYS}/bin"
    )

    if(NOT C4ROOT_ROOTCLING_EXECUTABLE)

        message(FATAL_ERROR
            "Neither rootcint nor rootcling could be found.\n"
            "Please check your ROOT installation."
        )

    endif()

    # The legacy FairRoot dictionary macro expects this particular variable.
    set(
        ROOT_CINT_EXECUTABLE
        "${C4ROOT_ROOTCLING_EXECUTABLE}"
        CACHE FILEPATH
        "ROOT dictionary generator used by legacy FairRoot macros"
        FORCE
    )

    message(STATUS
        "FairRoot's legacy dictionary macro requested rootcint; "
        "using rootcling instead:\n"
        "  ${ROOT_CINT_EXECUTABLE}"
    )

else()

    message(STATUS
        "Using ROOT dictionary generator:\n"
        "  ${ROOT_CINT_EXECUTABLE}"
    )

endif()


# ==============================================================================
# c4Root install path
# ==============================================================================

set(C4ROOTPATH "${CMAKE_INSTALL_PREFIX}")


# ==============================================================================
# Git
# ==============================================================================

if(COMMAND find_package2)

    find_package2(PUBLIC Git)

else()

    find_package(Git)

endif()

if(GIT_FOUND)

    set(Git_VERSION "${GIT_VERSION_STRING}")

    get_filename_component(
        Git_ROOT
        "${GIT_EXECUTABLE}"
        DIRECTORY
    )

endif()


# ==============================================================================
# Compiler configuration
# ==============================================================================

check_compiler()

if(DEFINED ENV{WERROR} AND "$ENV{WERROR}")

    message(STATUS "Will compile with -Werror.")

    string(APPEND CMAKE_CXX_FLAGS
        " -Wall"
        " -Werror"
        " -Wno-sign-compare"
        " -Wno-reorder"
        " -Wno-unused-variable"
        " -Wno-unused-but-set-variable"
        " -Wfatal-errors"
    )

else()

    if(NOT APPLE)

        message(STATUS
            "Set env WERROR to 1 to enable -Werror. "
            "If origin/dev compiles on your platform with that option, "
            "it is definitely a good idea to do that."
        )

        string(APPEND CMAKE_CXX_FLAGS
            " -Wall"
            " -Wno-sign-compare"
            " -Wno-reorder"
            " -Wno-unused-variable"
            " -Wno-unused-but-set-variable"
        )

    endif()

endif()

string(PREPEND CMAKE_CXX_FLAGS "-D_GLIBCXX_ASSERTIONS ")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# ==============================================================================
# Output directories
# ==============================================================================

set(
    LIBRARY_OUTPUT_PATH
    "${CMAKE_BINARY_DIR}/lib"
)

set(
    EXECUTABLE_OUTPUT_PATH
    "${CMAKE_BINARY_DIR}/bin"
)

set(
    INCLUDE_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/include"
)

# Retained because existing c4Root scripts/macros make use of VMCWORKDIR as a
# source-tree location. This does NOT imply a VMC library dependency.
set(
    VMCWORKDIR
    "${CMAKE_SOURCE_DIR}"
)


# ==============================================================================
# Optional PATH information
#
# Retained for backwards compatibility with older c4Root/FairRoot setups.
# New installations generally do not need this.
# ==============================================================================

option(
    USE_PATH_INFO
    "Information from PATH and LD_LIBRARY_PATH are used."
    OFF
)

if(USE_PATH_INFO)

    set(PATH "$ENV{PATH}")

    if(APPLE)
        set(LD_LIBRARY_PATH "$ENV{DYLD_LIBRARY_PATH}")
    else()
        set(LD_LIBRARY_PATH "$ENV{LD_LIBRARY_PATH}")
    endif()

endif()


# ==============================================================================
# Platform/build checks
# ==============================================================================

if(COMMAND check_out_of_source_build)
    check_out_of_source_build()
endif()


if(NOT UNIX)

    message(FATAL_ERROR
        "c4Root has currently only been tested on UNIX systems."
    )

endif()


# Older FairRoot releases provided this helper.
# Newer releases removed it.
if(COMMAND check_external_package_install_dir)
    check_external_package_install_dir()
endif()


# ==============================================================================
# Basic FairRoot/c4Root variables
# ==============================================================================

SetBasicVariables()


# ==============================================================================
# Version information
# ==============================================================================

set(C4ROOT_MAJOR_VERSION 0)
set(C4ROOT_MINOR_VERSION 0)
set(C4ROOT_PATCH_VERSION 0)

# Preserve historical c4Root behaviour for ABI/library properties.
set(
    C4ROOT_VERSION
    "${FairRoot_VERSION}"
)


# ROOT_VERSION is the modern variable.
#
# Older FairRoot/ROOT combinations may instead populate ROOT_FOUND_VERSION or
# found_vers, so retain fallbacks.
if(ROOT_VERSION)

    set(ROOT_FOUND_VERSION "${ROOT_VERSION}")

elseif(NOT ROOT_FOUND_VERSION AND DEFINED found_vers)

    set(ROOT_FOUND_VERSION "${found_vers}")

endif()

message(
    STATUS
    "ROOT version: ${ROOT_FOUND_VERSION}"
)


set(
    FAIRROOT_LIBRARY_PROPERTIES
    ${FAIRROOT_LIBRARY_PROPERTIES}
    VERSION
    "${C4ROOT_VERSION}"
    SOVERSION
    "${C4ROOT_VERSION}"
)


# ==============================================================================
# Runtime library path
# ==============================================================================

string(
    COMPARE EQUAL
    "${CMAKE_GENERATOR}"
    "Xcode"
    IS_XCODE
)

set(
    C4LIBDIR
    "${CMAKE_BINARY_DIR}/lib"
)

if(IS_XCODE)

    set(
        LD_LIBRARY_PATH
        ${C4LIBDIR}/RELWITHDEBINFO
        ${C4LIBDIR}
        ${LD_LIBRARY_PATH}
    )

else()

    set(
        LD_LIBRARY_PATH
        ${C4LIBDIR}
        ${LD_LIBRARY_PATH}
    )

endif()


# ==============================================================================
# ucesb
#
# Optional.
#
# If unavailable, c4Root is still built, but c4source is skipped and LMD
# unpacking is unavailable.
# ==============================================================================

find_package(ucesb)

if(ucesb_FOUND)

    set(WITH_UCESB TRUE)

    set(
        UCESBPATH
        "$ENV{UCESB_DIR}"
    )

    set(
        LD_LIBRARY_PATH
        ${ucesb_LIBRARY_DIR}
        ${LD_LIBRARY_PATH}
    )

else()

    set(WITH_UCESB FALSE)

    message(WARNING
        "${BMagenta}"
        "No UCESB configured. "
        "You will not be able to unpack lmd files. "
        "Set UCESB_DIR to a ucesb installation to fix this. "
        "You may also need to make an experiment in /unpack/exps."
        "${CR}"
    )

endif()


# ==============================================================================
# c4Root configuration/version files
# ==============================================================================

configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/scripts/c4RootConfigVersion.cmake.in"
    "${CMAKE_BINARY_DIR}/c4RootConfigVersion.cmake"
    @ONLY
)

c4_generate_version_info()


# ==============================================================================
# Build c4Root
# ==============================================================================

if(MODULE)

    add_subdirectory("${MODULE}")

else()

    add_subdirectory(c4base)

    if(WITH_UCESB)
        add_subdirectory(c4source)
    endif()

    set(
        ENV{VMCWORKDIR}
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_subdirectory(c4data)
    add_subdirectory(compilehelper)
    add_subdirectory(analysis)
    add_subdirectory(macros)

endif()


add_subdirectory(cmake)


# ==============================================================================
# Git version
# ==============================================================================

if(0 AND GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")

    execute_process(
        COMMAND
            "${GIT_EXECUTABLE}"
            describe
            --tags
        OUTPUT_VARIABLE
            C4ROOT_GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY
            "${CMAKE_SOURCE_DIR}"
    )

else()

    set(
        C4ROOT_GIT_VERSION
        "v${C4ROOT_MAJOR_VERSION}.${C4ROOT_MINOR_VERSION}.${C4ROOT_PATCH_VERSION}"
    )

endif()


# ==============================================================================
# ROOT OpenGL/event-display information
# ==============================================================================

if(ROOT_CONFIG_EXECUTABLE)

    execute_process(
        COMMAND
            "${ROOT_CONFIG_EXECUTABLE}"
            --has-opengl
        OUTPUT_VARIABLE
            EveIsBuild
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

endif()


if(DEFINED EveIsBuild AND "${EveIsBuild}" STREQUAL "yes")

    message(
        STATUS
        "ROOT was built with OpenGL support."
    )

    # Historical eventdisplay build intentionally remains disabled here.
    #
    # if(NOT FAIRROOT_FOUND)
    #     add_subdirectory(eventdisplay)
    # endif()

else()

    message(
        STATUS
        "The eventdisplay is not built; "
        "ROOT has no OpenGL support."
    )

endif()


# ==============================================================================
# Doxygen
# ==============================================================================

option(
    BUILD_DOXYGEN
    "Build Doxygen"
    OFF
)

if(BUILD_DOXYGEN)

    message(
        STATUS
        "*** Building the Doxygen documentation ***"
    )

    add_subdirectory(doxygen)

endif()


# ==============================================================================
# Rule checker
# ==============================================================================

if(RULE_CHECKER_FOUND)

    add_custom_target(
        RULES

        COMMAND
            ${RULE_CHECKER_SCRIPT1}
            ${CMAKE_BINARY_DIR}
            viol
            >
            violations.html

        DEPENDS
            $ENV{ALL_RULES}
    )

endif()


# ==============================================================================
# Environment/configuration scripts
# ==============================================================================

write_config_file(config.sh)
write_config_file(config.csh)

write_config_file(config.sh_install)
write_config_file(config.csh_install)

write_env_cache(env_cache.sh)


# ==============================================================================
# c4 helper command
# ==============================================================================

file(
    APPEND
    "${CMAKE_BINARY_DIR}/config.sh"
"
c4() {
    if [ \"\$1\" = \"--help\" ]; then
        echo \"Usage: c4 [options]\"
        echo \"Options:\"
        echo \"  --help        Show this help message\"
        echo \"  --version     Show version information\"
        if [ \"\$2\" = \"me\" ]; then
            echo \"How may I help you, poor soul?\"
        fi
    elif [ \"\$1\" = \"--version\" ]; then
        echo \"c4 Version: Hmm, no idea... 0.9 probably.\"
    else
        echo \"Unknown command: \$1\"
        echo \"Try 'c4 --help' for usage information.\"
    fi
}
"
)


# ==============================================================================
# Configuration summary
# ==============================================================================

if(CMAKE_CXX_FLAGS)

    message(STATUS "")

    message(
        STATUS
        "  ${Cyan}GLOBAL CXX FLAGS${CR}  "
        "${BGreen}${CMAKE_CXX_FLAGS}${CR}"
    )

endif()


if(CMAKE_CONFIGURATION_TYPES)

    message(STATUS "")

    message(
        STATUS
        "  ${Cyan}BUILD TYPE         CXX FLAGS${CR}"
    )

    string(
        TOUPPER
        "${CMAKE_BUILD_TYPE}"
        selected_type
    )


    foreach(type IN LISTS CMAKE_CONFIGURATION_TYPES)

        string(
            TOUPPER
            "${type}"
            type_upper
        )


        if(type_upper STREQUAL selected_type)

            if("${FairRoot_VERSION}" VERSION_LESS "19.0")

                pad(
                    "${type}"
                    18
                    " "
                    type_padded
                )

                message(
                    STATUS
                    "${BGreen}* ${type_padded}"
                    "${CMAKE_CXX_FLAGS_${type_upper}}${CR}"
                )

            else()

                message(
                    STATUS
                    "${BGreen}* ${type} "
                    "${CMAKE_CXX_FLAGS_${type_upper}}${CR}"
                )

            endif()

        else()

            if("${FairRoot_VERSION}" VERSION_LESS "19.0")

                pad(
                    "${type}"
                    18
                    " "
                    type_padded
                )

                message(
                    STATUS
                    "  ${BWhite}${type_padded}${CR}"
                    "${CMAKE_CXX_FLAGS_${type_upper}}"
                )

            else()

                message(
                    STATUS
                    "  ${BWhite}${type}${CR} "
                    "${CMAKE_CXX_FLAGS_${type_upper}}"
                )

            endif()

        endif()


        unset(type_padded)
        unset(type_upper)

    endforeach()


    message(STATUS "")

    message(
        STATUS
        "  (Change the build type with "
        "${BMagenta}-DCMAKE_BUILD_TYPE=...${CR})"
    )

endif()


# ==============================================================================
# Dependency summary
# ==============================================================================

if(PROJECT_PACKAGE_DEPENDENCIES)

    message(STATUS "")

    message(
        STATUS
        "  ${Cyan}DEPENDENCY FOUND     VERSION                   PREFIX${CR}"
    )


    foreach(dep IN LISTS PROJECT_PACKAGE_DEPENDENCIES)

        unset(version_str)
        unset(version_padded)
        unset(version_req_str)
        unset(prefix)


        if(DEFINED ${dep}_VERSION AND ${dep}_VERSION)

            set(
                version_str
                "${BGreen}${${dep}_VERSION}${CR}"
            )

        else()

            set(
                version_str
                "${BYellow}unknown${CR}"
            )

        endif()


        if(DEFINED PROJECT_${dep}_VERSION
           AND PROJECT_${dep}_VERSION)

            set(
                version_req_str
                " (>= ${PROJECT_${dep}_VERSION})"
            )

        else()

            set(version_req_str "")

        endif()


        if("${FairRoot_VERSION}" VERSION_LESS "19.0"
           AND COMMAND pad)

            pad(
                "${dep}"
                20
                " "
                dep_padded
            )

            if(DISABLE_COLOR)

                pad(
                    "${version_str}${version_req_str}"
                    25
                    " "
                    version_padded
                )

            else()

                pad(
                    "${version_str}${version_req_str}"
                    25
                    " "
                    version_padded
                    COLOR 1
                )

            endif()

        else()

            set(
                dep_padded
                "${dep} "
            )

            set(
                version_padded
                "${version_str}${version_req_str} "
            )

        endif()


        set(prefix "${${dep}_PREFIX}")


        if("${dep}" STREQUAL "FairLogger")

            if(FairLogger_PREFIX)

                set(
                    prefix
                    "${FairLogger_PREFIX}"
                )

            elseif(FairLogger_ROOT)

                set(
                    prefix
                    "${FairLogger_ROOT}"
                )

            endif()


        elseif("${dep}" STREQUAL "ROOT")

            if(ROOT_INSTALL_DIR)

                set(
                    prefix
                    "${ROOT_INSTALL_DIR}"
                )

            elseif(ROOTSYS)

                set(
                    prefix
                    "${ROOTSYS}"
                )

            endif()


        elseif("${dep}" STREQUAL "Git")

            if(GIT_EXECUTABLE)

                get_filename_component(
                    prefix
                    "${GIT_EXECUTABLE}"
                    DIRECTORY
                )

            endif()

        endif()


        message(
            STATUS
            "  ${BWhite}${dep_padded}${CR}"
            "${version_padded}${prefix}"
        )

    endforeach()

endif()


# ==============================================================================
# Final summary
# ==============================================================================

message(STATUS "")
message(STATUS "==============================================================")
message(STATUS " c4Root configuration complete")
message(STATUS "")
message(STATUS " FairRoot:           ${FairRoot_VERSION}")
message(STATUS " ROOT:               ${ROOT_FOUND_VERSION}")
message(STATUS " ROOT dictionary:    ${ROOT_CINT_EXECUTABLE}")
message(STATUS " ucesb:              ${WITH_UCESB}")
message(STATUS "")
message(STATUS " c4Root SIMPATH requirement: NONE")
message(STATUS "==============================================================")
message(STATUS "")