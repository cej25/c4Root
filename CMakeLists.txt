# ==============================================================================
# c4Root
# ==============================================================================

cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

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
# Terminal colours
# ==============================================================================

option(DISABLE_COLOR "Disable coloured CMake output" OFF)

if(NOT DISABLE_COLOR AND UNIX)

    string(ASCII 27 Esc)

    set(CReset   "${Esc}[m")
    set(CBold    "${Esc}[1m")

    set(CRed     "${Esc}[31m")
    set(CGreen   "${Esc}[32m")
    set(CYellow  "${Esc}[33m")
    set(CBlue    "${Esc}[34m")
    set(CMagenta "${Esc}[35m")
    set(CCyan    "${Esc}[36m")
    set(CWhite   "${Esc}[37m")

    set(BRed     "${Esc}[1;31m")
    set(BGreen   "${Esc}[1;32m")
    set(BYellow  "${Esc}[1;33m")
    set(BBlue    "${Esc}[1;34m")
    set(BMagenta "${Esc}[1;35m")
    set(BCyan    "${Esc}[1;36m")
    set(BWhite   "${Esc}[1;37m")

    # Compatibility with older FairRoot/c4Root naming.
    set(CR "${CReset}")

else()

    foreach(_colour
        CReset CBold
        CRed CGreen CYellow CBlue CMagenta CCyan CWhite
        BRed BGreen BYellow BBlue BMagenta BCyan BWhite CR
    )
        set(${_colour} "")
    endforeach()

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

message(STATUS "Using FairRoot ${BGreen}${FairRoot_VERSION}${CR}")


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
#   Prefer FairCMakeModules when available, but retain compatibility with
#   older installations where the helper is supplied by FairRoot itself.
# ==============================================================================

if("${FairRoot_VERSION}" VERSION_GREATER_EQUAL "19.0")

    find_package(FairCMakeModules 1.0 REQUIRED)
    include(FairFindPackage2)

else()

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
# FairLogger is directly used by c4Root.
#
# Boost is deliberately not propagated as a c4Root dependency because c4Root
# itself does not use Boost.
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
# FairRoot transitive compatibility dependencies
#
# FairRoot public headers use VMC headers such as TMCtls.h.
# c4Root does not directly use VMC, but FairRoot-dependent code must therefore
# be able to see the VMC include directories.
# ==============================================================================

find_package(VMC QUIET)

if(VMC_FOUND)

    message(STATUS "Found VMC required by FairRoot")

    if(VMC_INCLUDE_DIRS)

        include_directories(${VMC_INCLUDE_DIRS})

        list(
            APPEND
            BASE_INCLUDE_DIRECTORIES
            ${VMC_INCLUDE_DIRS}
        )

    endif()

else()

    message(FATAL_ERROR
        "VMC could not be found.\n"
        "FairRoot ${FairRoot_VERSION} exposes VMC headers through its public "
        "interfaces (for example FairLinkManager.h includes TMCtls.h).\n"
        "Please provide a VMC installation visible to CMake."
    )

endif()


# ==============================================================================
# ROOT/FairRoot dictionary macros
# ==============================================================================

include(ROOTMacros)


# ==============================================================================
# ROOT dictionary-generator compatibility
#
# Older FairRoot ROOTMacros search specifically for rootcint.
#
# Older ROOT installations may genuinely provide rootcint, in which case it is
# retained. Modern ROOT installations provide rootcling instead.
# ==============================================================================

if(NOT ROOT_CINT_EXECUTABLE
   OR ROOT_CINT_EXECUTABLE MATCHES "-NOTFOUND$")

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

    set(
        ROOT_CINT_EXECUTABLE
        "${C4ROOT_ROOTCLING_EXECUTABLE}"
        CACHE FILEPATH
        "ROOT dictionary generator used by legacy FairRoot macros"
        FORCE
    )

    message(
        STATUS
        "FairRoot requested legacy rootcint; using "
        "${BGreen}rootcling${CR} instead: "
        "${ROOT_CINT_EXECUTABLE}"
    )

else()

    message(
        STATUS
        "Using ROOT dictionary generator: "
        "${ROOT_CINT_EXECUTABLE}"
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

# Retained because existing c4Root scripts/macros use VMCWORKDIR as a project
# source-tree location. This does not imply a Geant4/VMC simulation dependency.
set(
    VMCWORKDIR
    "${CMAKE_SOURCE_DIR}"
)


# ==============================================================================
# Optional PATH information
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

set(
    C4ROOT_VERSION
    "${FairRoot_VERSION}"
)


if(ROOT_VERSION)

    set(
        ROOT_FOUND_VERSION
        "${ROOT_VERSION}"
    )

elseif(NOT ROOT_FOUND_VERSION AND DEFINED found_vers)

    set(
        ROOT_FOUND_VERSION
        "${found_vers}"
    )

endif()

message(
    STATUS
    "ROOT version: ${BGreen}${ROOT_FOUND_VERSION}${CR}"
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
# Optional. Required for unpacking raw/LMD data.
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

    message(STATUS "ROOT was built with OpenGL support.")

else()

    message(
        STATUS
        "The eventdisplay is not built; ROOT has no OpenGL support."
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
# Compiler/build-type summary
# ==============================================================================

if(CMAKE_CXX_FLAGS)

    message(STATUS "")

    message(
        STATUS
        "  ${BCyan}GLOBAL CXX FLAGS${CR}  "
        "${BGreen}${CMAKE_CXX_FLAGS}${CR}"
    )

endif()


if(CMAKE_CONFIGURATION_TYPES)

    message(STATUS "")

    message(
        STATUS
        "  ${BCyan}BUILD TYPE         CXX FLAGS${CR}"
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

            if("${FairRoot_VERSION}" VERSION_LESS "19.0"
               AND COMMAND pad)

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
                    "${BGreen}* ${type}${CR} "
                    "${CMAKE_CXX_FLAGS_${type_upper}}"
                )

            endif()

        else()

            if("${FairRoot_VERSION}" VERSION_LESS "19.0"
               AND COMMAND pad)

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

message(STATUS "")
message(STATUS "${BCyan}DEPENDENCY FOUND      VERSION              PREFIX${CR}")


function(c4_print_dependency NAME VERSION PREFIX)

    if("${VERSION}" STREQUAL "")
        set(_version "${BYellow}unknown${CR}")
    else()
        set(_version "${BGreen}${VERSION}${CR}")
    endif()

    if("${PREFIX}" STREQUAL "")
        set(_prefix "${BYellow}unknown${CR}")
    else()
        set(_prefix "${PREFIX}")
    endif()


    string(LENGTH "${NAME}" _name_length)
    math(EXPR _name_spaces "22 - ${_name_length}")

    if(_name_spaces LESS 1)
        set(_name_spaces 1)
    endif()

    set(_name_padding "")

    foreach(_i RANGE 1 ${_name_spaces})
        string(APPEND _name_padding " ")
    endforeach()


    string(LENGTH "${VERSION}" _version_length)
    math(EXPR _version_spaces "21 - ${_version_length}")

    if(_version_spaces LESS 1)
        set(_version_spaces 1)
    endif()

    set(_version_padding "")

    foreach(_i RANGE 1 ${_version_spaces})
        string(APPEND _version_padding " ")
    endforeach()


    message(
        STATUS
        "  ${BWhite}${NAME}${CR}"
        "${_name_padding}"
        "${_version}"
        "${_version_padding}"
        "${_prefix}"
    )

endfunction()


# FairCMakeModules
if(FairCMakeModules_FOUND)

    if(FairCMakeModules_PREFIX)
        set(_faircmake_prefix "${FairCMakeModules_PREFIX}")
    elseif(FairCMakeModules_DIR)
        get_filename_component(
            _faircmake_prefix
            "${FairCMakeModules_DIR}/../../.."
            ABSOLUTE
        )
    else()
        set(_faircmake_prefix "")
    endif()

    c4_print_dependency(
        "FairCMakeModules"
        "${FairCMakeModules_VERSION}"
        "${_faircmake_prefix}"
    )

endif()


# FairRoot
c4_print_dependency(
    "FairRoot"
    "${FairRoot_VERSION}"
    "${FAIRROOTPATH}"
)


# ROOT
if(ROOT_VERSION)
    set(_root_version "${ROOT_VERSION}")
else()
    set(_root_version "${ROOT_FOUND_VERSION}")
endif()

if(ROOT_INSTALL_DIR)

    set(
        _root_prefix
        "${ROOT_INSTALL_DIR}"
    )

elseif(ROOTSYS)

    set(
        _root_prefix
        "${ROOTSYS}"
    )

else()

    set(
        _root_prefix
        ""
    )

endif()

c4_print_dependency(
    "ROOT"
    "${_root_version}"
    "${_root_prefix}"
)


# FairLogger
if(FairLogger_PREFIX)

    set(
        _fairlogger_prefix
        "${FairLogger_PREFIX}"
    )

elseif(FairLogger_ROOT)

    set(
        _fairlogger_prefix
        "${FairLogger_ROOT}"
    )

else()

    set(
        _fairlogger_prefix
        ""
    )

endif()

c4_print_dependency(
    "FairLogger"
    "${FairLogger_VERSION}"
    "${_fairlogger_prefix}"
)


# FairLogger transitive dependencies
foreach(dep IN LISTS FairLogger_PACKAGE_DEPENDENCIES)

    if(NOT dep STREQUAL "Boost")

        if(DEFINED ${dep}_VERSION)
            set(_dep_version "${${dep}_VERSION}")
        else()
            set(_dep_version "")
        endif()

        if(DEFINED ${dep}_PREFIX)

            set(
                _dep_prefix
                "${${dep}_PREFIX}"
            )

        else()

            set(
                _dep_prefix
                ""
            )

        endif()

        c4_print_dependency(
            "${dep}"
            "${_dep_version}"
            "${_dep_prefix}"
        )

    endif()

endforeach()


# VMC
if(VMC_FOUND)

    if(VMC_PREFIX)

        set(
            _vmc_prefix
            "${VMC_PREFIX}"
        )

    elseif(VMC_DIR)

        get_filename_component(
            _vmc_prefix
            "${VMC_DIR}/../../.."
            ABSOLUTE
        )

    elseif(VMC_INCLUDE_DIRS)

        list(GET VMC_INCLUDE_DIRS 0 _vmc_include)

        get_filename_component(
            _vmc_prefix
            "${_vmc_include}/.."
            ABSOLUTE
        )

    else()

        set(
            _vmc_prefix
            ""
        )

    endif()

    c4_print_dependency(
        "VMC"
        "${VMC_VERSION}"
        "${_vmc_prefix}"
    )

endif()


# ucesb
if(WITH_UCESB)

    c4_print_dependency(
        "ucesb"
        "found"
        "${UCESBPATH}"
    )

else()

    c4_print_dependency(
        "ucesb"
        "not configured"
        ""
    )

endif()


# Git
if(GIT_FOUND)

    c4_print_dependency(
        "Git"
        "${GIT_VERSION_STRING}"
        "${GIT_EXECUTABLE}"
    )

endif()

message(STATUS "")