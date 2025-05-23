if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)

    message(FATAL_ERROR "In-source builds are not supported, please, create a folder build.")

endif()

cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

cmake_policy(VERSION 3.11...3.31)

project(C4ROOT LANGUAGES C CXX)

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/macros")
    message(FATAL_ERROR
            "\nmacros repository is missing in the c4Root source directory\ncd ${CMAKE_SOURCE_DIR}\ngit clone -b dev <github_link>"
            )
endif(NOT EXISTS "${PROJECT_SOURCE_DIR}/macros")

# Check for needed environment variables
if(NOT DEFINED ENV{SIMPATH})

    message(

        FATAL_ERROR

            "You did not define the environment variable SIMPATH which is nedded to find the external packages. Please set this variable and execute cmake again."

    )

endif(NOT DEFINED ENV{SIMPATH})

if(NOT DEFINED ENV{FAIRROOTPATH})

    message(

        FATAL_ERROR

            "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot. Please set this variable and execute cmake again."

    )

endif()

set(SIMPATH $ENV{SIMPATH})
set(FAIRROOTPATH $ENV{FAIRROOTPATH})

STRING(REGEX MATCHALL "[^:]+" PATH $ENV{PATH})

set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

Set(CheckSrcDir "${FAIRROOTPATH}/share/fairbase/cmake/checks")

# find_package(FairCMakeModules 0.1 QUIET)
# if(FairCMakeModules_FOUND)
#   include(FairFindPackage2)
# else()
#   message(STATUS "Could not find FairCMakeModules. "
#           "It is recommended to install https://github.com/FairRootGroup/FairCMakeModules")
# endif()

find_package(FairCMakeModules 1.0 REQUIRED)
include(FairFindPackage2)

if(COMMAND find_package2)
  find_package2(PUBLIC FairRoot)
else()
  find_package(FairRoot)
endif()

# FairRoot_VERSION is eventually set by find_package, for now let's set it explicitly
execute_process(
  COMMAND ${FAIRROOTPATH}/bin/fairroot-config --version
  COMMAND sed "s/^v//"
  OUTPUT_VARIABLE FairRoot_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
if( "${FairRoot_VERSION}"  VERSION_LESS 18.2.1 )
  Message(FATAL_ERROR "Incompatible FairRoot version detected: ${FairRoot_VERSION}. c4Root requires FairRoot v18.2.1 or later")
else()
  message(STATUS "You seem to be using FairRoot ${FairRoot_VERSION}.")
endif()

set(C4ROOTPATH ${CMAKE_INSTALL_PREFIX})

if(SIMPATH)
  set(CMAKE_PREFIX_PATH ${SIMPATH} ${CMAKE_PREFIX_PATH})
endif()

# Load some basic macros which are needed later on
include(FairMacros)

find_package2(PUBLIC ROOT  VERSION 6.10.00 REQUIRED)
if("${ROOT_vmc_FOUND}" MATCHES "no")
  find_package2(PUBLIC VMC REQUIRED)
  set(VMCLIB VMCLibrary)
else()
  set(VMCLIB VMC)
endif()

include(c4Macros)
include(WriteConfigFile_c4)
include(WriteEnvCache)
include(Dart)
include(CheckCompiler)
include(ROOTMacros) # This is from FR, see https://github.com/FairRootGroup/FairRoot/issues/1221

find_package2(PUBLIC FairLogger  VERSION 1.2.0 REQUIRED) # maybe 1.6 now

foreach(dep IN LISTS FairLogger_PACKAGE_DEPENDENCIES)
    if(NOT dep STREQUAL "Boost")
        find_package2(
            PUBLIC
            ${dep}
            REQUIRED
            VERSION
            ${FairLogger_${dep}_VERSION})
    endif()
endforeach()

# if( "${FairRoot_VERSION}"  VERSION_GREATER 18.6.4 )
#   add_definitions(-DACTIVATEOVERRIDE)

#   find_package2(PUBLIC DDS)

# Endif()


if("${FairRoot_VERSION}" VERSION_GREATER 18.6.4)

    find_package2(
        PUBLIC
        FairMQ
        VERSION
        1.4.0
        REQUIRED)
    find_package2(PUBLIC DDS)

    if(FAIRSOFT_EXTERN)
        set(Boost_ROOT ${SIMPATH})
        set(GSL_DIR ${SIMPATH})
    else(FAIRSOFT_EXTERN)
        set(Boost_ROOT ${SIMPATH}/basics/boost)
        set(GSL_DIR ${SIMPATH}/basics/gsl)
    endif(FAIRSOFT_EXTERN)

    if(NOT DEFINED Boost_NO_SYSTEM_PATHS)
        set(Boost_NO_SYSTEM_PATHS TRUE)
    endif()
    if(NOT DEFINED Boost_NO_BOOST_CMAKE AND CMAKE_VERSION VERSION_LESS 3.15)
        set(Boost_NO_BOOST_CMAKE TRUE)
    endif()
    if(Boost_NO_BOOST_CMAKE)
        # If an older version of boost is found both of the variables below are
        # cached and in a second cmake run, a good boost version is found even
        # if the version is to old.
        # To overcome this problem both variables are cleared before checking
        # for boost.
        unset(Boost_INCLUDE_DIR CACHE)
        unset(Boost_LIBRARY_DIRS CACHE)
    endif()

    list(
        APPEND
        boost_dependencies
        thread
        system
        timer
        program_options
        random
        filesystem
        chrono
        exception
        iostreams
        regex
        serialization
        log
        atomic)

    find_package2(
        PUBLIC
        Boost
        VERSION
        1.67
        COMPONENTS
        ${boost_dependencies}
        ADD_REQUIREMENTS_OF
        FairMQ)
    #  If (FairMQ_FOUND AND Boost_FOUND)
    #    add_subdirectory(base/MQ)
    #    add_subdirectory(parmq)
    #  Else ()
    #    Message(STATUS "base/MQ and parmq will not be built, because FairMQ and/or Boost was not found.")
    #  EndIf ()
else()
    set(Boost_NO_SYSTEM_PATHS TRUE)
    set(Boost_NO_BOOST_CMAKE TRUE)

    if(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
        set(Boost_ROOT ${SIMPATH})
        set(GSL_DIR ${SIMPATH})
    else(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
        set(Boost_ROOT ${SIMPATH}/basics/boost)
        set(GSL_DIR ${SIMPATH}/basics/gsl)
    endif(${ROOT_LIBRARY_DIR} MATCHES /lib/root)

    unset(Boost_INCLUDE_DIR CACHE)
    unset(Boost_LIBRARY_DIRS CACHE)
    find_package2(
        PUBLIC
        Boost
        VERSION
        1.67
        ${FairMQ_Boost_VERSION}
        COMPONENTS
        thread
        system
        timer
        program_options
        random
        filesystem
        chrono
        exception
        iostreams
        regex
        serialization
        log
        log_setup
        atomic
        date_time
        ${FairMQ_Boost_COMPONENTS}
        REQUIRED)
endif() #end of r3b fairroot version if statement


find_package2(PUBLIC Pythia6)
find_package2(PUBLIC Pythia8)

find_package2(PUBLIC VGM)

find_package(HEPMC)

find_package2(PUBLIC IWYU)

find_package2(PUBLIC GSL)
if(NOT DEFINED GTEST_ROOT)
  set(GTEST_ROOT ${SIMPATH})
endif()

find_package2(PUBLIC Git)
set (Git_VERSION ${GIT_VERSION_STRING})
string(REPLACE "git" " " Git_ROOT ${GIT_EXECUTABLE} )

# Check the compiler and set the compile and link flags
check_compiler()

if(DEFINED ENV{WERROR} AND "$ENV{WERROR}")
  message(STATUS "Will compile with -Werror. ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-sign-compare -Wno-reorder -Wno-unused-variable -Wno-unused-but-set-variable -Wfatal-errors")
else()
  if (NOT APPLE)
    message(STATUS "Set env WERROR to 1 to enable -Werror. If origin/dev compiles on your platform with that option, it is definitly a good idea to do that.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare -Wno-reorder -Wno-unused-variable -Wno-unused-but-set-variable")
  endif()
endif()
set(CMAKE_CXX_FLAGS "-D_GLIBCXX_ASSERTIONS ${CMAKE_CXX_FLAGS}" )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # used by clang-tidy

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(INCLUDE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/include")
set(VMCWORKDIR ${CMAKE_SOURCE_DIR})

option(USE_PATH_INFO "Information from PATH and LD_LIBRARY_PATH are
used." OFF)
if(USE_PATH_INFO)
    set(PATH $ENV{PATH})
    if(APPLE)
        set(LD_LIBRARY_PATH $ENV{DYLD_LIBRARY_PATH})
    else(APPLE)
        set(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})
    endif(APPLE)
endif(USE_PATH_INFO)

# Check if the user wants to build the project in the source directory
check_out_of_source_build()

# Check if we are on an UNIX system. If not stop with an error message
if(NOT UNIX)
    message(
        FATAL_ERROR
            "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory."
        )
endif(NOT UNIX)

# Check if the external packages are installed into a separate install directory
if (COMMAND check_external_package_install_dir)
  check_external_package_install_dir()
endif()

# set(Boost_NO_SYSTEM_PATHS TRUE)
# set(Boost_NO_BOOST_CMAKE TRUE)

# If(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
#   set(BOOST_ROOT ${SIMPATH})
#   set(GSL_DIR ${SIMPATH})
# Else(${ROOT_LIBRARY_DIR} MATCHES /lib/root)
#   set(BOOST_ROOT ${SIMPATH}/basics/boost)
#   set(GSL_DIR ${SIMPATH}/basics/gsl)
# EndIf(${ROOT_LIBRARY_DIR} MATCHES /lib/root)

# unset(Boost_INCLUDE_DIR CACHE)
# unset(Boost_LIBRARY_DIRS CACHE)
# find_package2(PUBLIC Boost
#   VERSION 1.67 ${FairMQ_Boost_VERSION}
#   COMPONENTS thread system timer program_options random filesystem chrono exception iostreams regex serialization log log_setup atomic date_time ${FairMQ_Boost_COMPONENTS}
#   REQUIRED
# )
if(Boost_FOUND)
  set(Boost_Avail 1)
else(Boost_FOUND)
    set(Boost_Avail 0)
endif(Boost_FOUND)

find_package2(PUBLIC yaml-cpp)
# Workaround missing exported include directories
# Upstream has fixed this in https://github.com/jbeder/yaml-cpp/commit/ab5f9259a4e67d3fe0e4832bd407a9e596e2d884 (since 0.6.3)
if(yaml-cpp_FOUND)
  get_filename_component(YAML_CPP_INCLUDE_DIR "${YAML_CPP_INCLUDE_DIR}" REALPATH BASE_DIR "/")
endif()
if(    yaml-cpp_FOUND
   AND TARGET yaml-cpp
   AND EXISTS YAML_CPP_INCLUDE_DIR
   AND yaml-cpp_VERSION VERSION_LESS 0.6.3
)
  set_target_properties(yaml-cpp PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${YAML_CPP_INCLUDE_DIR}"
  )
endif()

SetBasicVariables()

# Set the library version in the main CMakeLists.txt
set(C4ROOT_MAJOR_VERSION 0)
set(C4ROOT_MINOR_VERSION 0)
set(C4ROOT_PATCH_VERSION 0)
set(C4ROOT_VERSION "${FairRoot_VERSION}")

if(NOT DEFINED ROOT_FOUND_VERSION)
    set(ROOT_FOUND_VERSION "${found_vers}")
endif()
message("ROOT_FOUND_VERSION = ${ROOT_FOUND_VERSION}")

set(FAIRROOT_LIBRARY_PROPERTIES
    ${FAIRROOT_LIBRARY_PROPERTIES}
    VERSION
    "${C4ROOT_VERSION}"
    SOVERSION
    "${C4ROOT_VERSION}")

string(COMPARE EQUAL
               "${CMAKE_GENERATOR}"
               "Xcode"
               IS_XCODE)
set(C4LIBDIR ${CMAKE_BINARY_DIR}/lib)
if(${IS_XCODE})
    set(LD_LIBRARY_PATH ${C4LIBDIR}/RELWITHDEBINFO ${C4LIBDIR} ${LD_LIBRARY_PATH})
else(${IS_XCODE})
    set(LD_LIBRARY_PATH ${C4LIBDIR} ${LD_LIBRARY_PATH})
endif(${IS_XCODE})

find_package(ucesb)
if(ucesb_FOUND)
    set(WITH_UCESB true)
    SET(UCESBPATH $ENV{UCESB_DIR})
    set(LD_LIBRARY_PATH ${ucesb_LIBRARY_DIR} ${LD_LIBRARY_PATH})
else()
  message(WARNING "${BMagenta}No UCESB configured. You will not be able to unpack lmd files. Set UCESB_DIR"
    " to a ucesb installation to fix this. You may also need to > make an experiment in /unpack/exps.${CR}")
endif(ucesb_FOUND)

configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/c4RootConfigVersion.cmake.in "${CMAKE_BINARY_DIR}/c4RootConfigVersion.cmake" @ONLY)

c4_generate_version_info()

# Recurse into the given subdirectories.  This does not actually cause another cmake executable to
# run.  The same process will walk through the project's entire directory structure.

# FIXME in FairSoft / FairRoot
find_package(VMC QUIET)
set (BASE_INCLUDE_DIRECTORIES ${BASE_INCLUDE_DIRECTORIES} ${VMC_INCLUDE_DIRS})

if(MODULE)
    add_subdirectory(${MODULE})
endif(MODULE)

if(NOT MODULE)
    add_subdirectory(c4base)
    if(WITH_UCESB)
        add_subdirectory(c4source)
    endif(WITH_UCESB)
    set(ENV{VMCWORKDIR} ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(c4data)
    add_subdirectory(compilehelper)
    add_subdirectory(analysis)
    add_subdirectory(macros)
endif(NOT MODULE)

add_subdirectory(cmake)

#this whole thing might have to be commented out until a github thing is setup? dunno
If(0 AND GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
  Execute_Process(COMMAND ${GIT_EXECUTABLE} describe --tags
                  OUTPUT_VARIABLE C4ROOT_GIT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                 )
Else()
  Set(C4ROOT_GIT_VERSION v${C4ROOT_MAJOR_VERSION}.${C4ROOT_MINOR_VERSION}.${C4ROOT_PATCH_VERSION})
EndIf()

execute_process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --has-opengl
                OUTPUT_VARIABLE EveIsBuild
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# if(${EveIsBuild} STREQUAL yes)
#     message("Build the eventdisplay.")
#     if(NOT FAIRROOT_FOUND)
#         add_subdirectory(eventdisplay)
#     endif(NOT FAIRROOT_FOUND)
# else(${EveIsBuild} STREQUAL yes)
#     message("The eventdisplay is not build, there is no OpenGL support.")
# endif(${EveIsBuild} STREQUAL yes)
if (DEFINED EveIsBuild AND "${EveIsBuild}" STREQUAL "yes")
    message("Build the eventdisplay.")
    if (NOT FAIRROOT_FOUND)
        add_subdirectory(eventdisplay)
    endif()
else()
    message("The eventdisplay is not built, there is no OpenGL support.")
endif()


option(BUILD_DOXYGEN "Build Doxygen" OFF)
if(BUILD_DOXYGEN)
    message(STATUS "*** Building the Doxygen documentaion ***")
    add_subdirectory(doxygen)
endif(BUILD_DOXYGEN)

if(RULE_CHECKER_FOUND)

    add_custom_target(RULES
                      COMMAND ${RULE_CHECKER_SCRIPT1} ${CMAKE_BINARY_DIR} viol > violations.html
                      DEPENDS $ENV{ALL_RULES})

endif(RULE_CHECKER_FOUND)

write_config_file(config.sh)
write_config_file(config.csh)
WRITE_CONFIG_FILE(config.sh_install)
WRITE_CONFIG_FILE(config.csh_install)

write_env_cache(env_cache.sh)


# help
file(APPEND ${CMAKE_BINARY_DIR}/config.sh "
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
")


# Summary ######################################################################
if(CMAKE_CXX_FLAGS)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}GLOBAL CXX FLAGS${CR}  ${BGreen}${CMAKE_CXX_FLAGS}${CR}")
endif()
if(CMAKE_CONFIGURATION_TYPES)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}BUILD TYPE         CXX FLAGS${CR}")
  string(TOUPPER "${CMAKE_BUILD_TYPE}" selected_type)
  foreach(type IN LISTS CMAKE_CONFIGURATION_TYPES)
   string(TOUPPER "${type}" type_upper)
   if(type_upper STREQUAL selected_type)
    if( "${FairRoot_VERSION}" VERSION_LESS 19.0)
      pad("${type}" 18 " " type_padded)
      message(STATUS "${BGreen}* ${type_padded}${CMAKE_CXX_FLAGS_${type_upper}}${CR}")
    else()
      # fair_pad("${type}" 19 " " type_padded)
      message(STATUS "${BGreen}* ${type_padded}${CMAKE_CXX_FLAGS_${type_upper}}${CR}")
    endif()
    else()
    if( "${FairRoot_VERSION}" VERSION_LESS 19.0)
     pad("${type}" 18 " " type_padded)
     message(STATUS "  ${BWhite}${type_padded}${CR}${CMAKE_CXX_FLAGS_${type_upper}}")
    else()
      # fair_pad("${type}" 19 " " type_padded)
      message(STATUS "  ${BWhite}${type_padded}${CR}${CMAKE_CXX_FLAGS_${type_upper}}")
    endif()
   endif()
   unset(type_padded)
   unset(type_upper)
 endforeach()
message(STATUS "  ")
message(STATUS "  (Change the build type with ${BMagenta}-DCMAKE_BUILD_TYPE=...${CR})")
endif()

if(PROJECT_PACKAGE_DEPENDENCIES)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}DEPENDENCY FOUND     VERSION                   PREFIX${CR}")
  foreach(dep IN LISTS PROJECT_PACKAGE_DEPENDENCIES)
    if(${dep}_VERSION)
      if(${dep} STREQUAL DDS)
        set(version_str "${BGreen}${${dep}_MAJOR_VERSION}.${${dep}_MINOR_VERSION}${CR}")
      elseif(${dep} STREQUAL Boost)
        if(Boost_VERSION_MAJOR)
          set(version_str "${BGreen}${${dep}_VERSION_MAJOR}.${${dep}_VERSION_MINOR}${CR}")
        else()
          set(version_str "${BGreen}${${dep}_MAJOR_VERSION}.${${dep}_MINOR_VERSION}${CR}")
        endif()
      else()
        set(version_str "${BGreen}${${dep}_VERSION}${CR}")
      endif()
    else()
      set(version_str "${BYellow}unknown${CR}")
    endif()
    if(PROJECT_${dep}_VERSION)
      set(version_req_str " (>= ${PROJECT_${dep}_VERSION})")
    endif()
    if( "${FairRoot_VERSION}" VERSION_LESS 19.0)
      pad(${dep} 20 " " dep_padded)
      if(DISABLE_COLOR)
        pad("${version_str}${version_req_str}" 25 " " version_padded)
      else()
        pad("${version_str}${version_req_str}" 25 " " version_padded COLOR 1)
      endif()
    else()
      # fair_pad(${dep} 20 " " dep_padded)
      if(DISABLE_COLOR)
        # fair_pad("${version_str}${version_req_str}" 25 " " version_padded)
      else()
        # fair_pad("${version_str}${version_req_str}" 25 " " version_padded COLOR 1)
      endif()
    endif()
    set(prefix ${${dep}_PREFIX})
    if(${dep} STREQUAL Boost)
      if(TARGET Boost::headers)
        get_target_property(boost_include Boost::headers INTERFACE_INCLUDE_DIRECTORIES)
      else()
        get_target_property(boost_include Boost::boost INTERFACE_INCLUDE_DIRECTORIES)
      endif()
      get_filename_component(prefix ${boost_include}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Protobuf)
      get_filename_component(prefix ${Protobuf_INCLUDE_DIRS}/.. ABSOLUTE)
    elseif(${dep} STREQUAL msgpack)
      get_target_property(msgpack_include msgpackc INTERFACE_INCLUDE_DIRECTORIES)
      get_filename_component(prefix ${msgpack_include}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Pythia6)
      get_filename_component(prefix ${PYTHIA6_LIBRARY_DIR}/.. ABSOLUTE)
    elseif(${dep} STREQUAL Pythia8)
      get_filename_component(prefix ${PYTHIA8_LIB_DIR}/.. ABSOLUTE)
    elseif(${dep} STREQUAL FairLogger)
      if(FairLogger_PREFIX)
        set(prefix ${FairLogger_PREFIX})
      else()
        set(prefix ${FairLogger_ROOT})
      endif()
    elseif(${dep} STREQUAL FairMQ)
      if(FairMQ_PREFIX)
        set(prefix ${FairMQ_PREFIX})
      else()
        set(prefix ${FairMQ_ROOT})
      endif()
    elseif(${dep} STREQUAL yaml-cpp)
      get_filename_component(prefix ${YAML_CPP_INCLUDE_DIR}/.. ABSOLUTE)
    elseif(${dep} STREQUAL VGM)
      string(REPLACE ":" ";" vgm_include ${VGM_INCLUDE_DIRS})
      list(GET vgm_include 0 vgm_include)
      get_filename_component(prefix ${vgm_include}/.. ABSOLUTE)
    elseif(${dep} STREQUAL ROOT)
      set(prefix ${ROOT_INSTALL_DIR})
    elseif(${dep} STREQUAL IWYU)
      get_filename_component(prefix ${IWYU_BINARY}/.. ABSOLUTE)
    elseif(${dep} STREQUAL yaml-cpp)
      get_filename_component(prefix ${YAML_CPP_INCLUDE_DIR}/.. ABSOLUTE)
    endif()

    message(STATUS "  ${BWhite}${dep_padded}${CR}${version_padded}${prefix}")

    unset(version_str)
    unset(version_padded)
    unset(version_req_str)
  endforeach()
endif()

message(STATUS "  ")
################################################################################
