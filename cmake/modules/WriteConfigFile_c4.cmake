# ==============================================================================
# Generate c4Root environment configuration files
# ==============================================================================

MACRO(WRITE_CONFIG_FILE filename)

  # ---------------------------------------------------------------------------
  # Determine whether this is a build-tree or install-tree configuration
  # ---------------------------------------------------------------------------

  string(REGEX REPLACE "^.*(install).*$" "\\1" INSTALL_VERSION "${filename}")
  string(COMPARE EQUAL "install" "${INSTALL_VERSION}" INSTALL_TRUE)

  # Do not duplicate the build library directory.
  list(REMOVE_ITEM LD_LIBRARY_PATH "${CMAKE_BINARY_DIR}/lib")

  if(INSTALL_TRUE)

    set(_INSTALLDIR "${CMAKE_INSTALL_PREFIX}")
    set(_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
    set(FAIRLIBDIR "${CMAKE_INSTALL_PREFIX}/lib")

    set(
      _LD_LIBRARY_PATH
      "${FAIRLIBDIR}"
      ${LD_LIBRARY_PATH}
    )

  else()

    set(_INSTALLDIR "${CMAKE_BINARY_DIR}")
    set(_BINDIR "${CMAKE_BINARY_DIR}")
    set(FAIRLIBDIR "${CMAKE_BINARY_DIR}/lib")

    set(
      _LD_LIBRARY_PATH
      "${FAIRLIBDIR}"
      ${LD_LIBRARY_PATH}
    )

  endif()


  # ---------------------------------------------------------------------------
  # System information
  # ---------------------------------------------------------------------------

  if(CMAKE_SYSTEM_NAME MATCHES "Linux")

    if(FAIRROOTPATH)

      configure_file(
        "${FAIRROOTPATH}/share/fairbase/cmake/scripts/check_system.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.sh"
      )

      configure_file(
        "${FAIRROOTPATH}/share/fairbase/cmake/scripts/check_system.csh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.csh"
      )

    else()

      configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/scripts/check_system.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.sh"
      )

      configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/scripts/check_system.csh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.csh"
      )

    endif()

    execute_process(
      COMMAND lsb_release -sd
      OUTPUT_VARIABLE _linux_flavour
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(_linux_flavour)
      string(REGEX REPLACE "^\"" "" _linux_flavour "${_linux_flavour}")
      string(REGEX REPLACE "\"$" "" _linux_flavour "${_linux_flavour}")
    endif()

    execute_process(
      COMMAND uname -m
      OUTPUT_VARIABLE _system
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )


  elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")

    if(FAIRROOTPATH)

      configure_file(
        "${FAIRROOTPATH}/share/fairbase/cmake/scripts/check_system_mac.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.sh"
      )

      configure_file(
        "${FAIRROOTPATH}/share/fairbase/cmake/scripts/check_system_mac.csh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.csh"
      )

    else()

      configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/scripts/check_system_mac.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.sh"
      )

      configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/scripts/check_system_mac.csh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/check_system.csh"
      )

    endif()

    execute_process(
      COMMAND uname -sr
      OUTPUT_VARIABLE _linux_flavour
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
      COMMAND uname -m
      OUTPUT_VARIABLE _system
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  endif()


  # ---------------------------------------------------------------------------
  # ROOT installation information
  #
  # Prefer root-config. This works for both older and modern ROOT versions
  # without relying on FairSoft/SIMPATH.
  # ---------------------------------------------------------------------------

  # ---------------------------------------------------------------------------
  # ROOT installation information
  #
  # Use the root-config belonging to the ROOT installation selected by CMake.
  # Do not simply use whichever root-config happens to appear first in PATH,
  # since that could belong to a different ROOT installation.
  # ---------------------------------------------------------------------------

  set(C4ROOT_ROOT_CONFIG_EXECUTABLE "")

  # ROOT_DIR normally points to:
  #
  #   <ROOT prefix>/share/root/cmake
  #
  # so derive the corresponding installation prefix from it.
  if(ROOT_DIR)

    get_filename_component(
      _ROOT_PREFIX_FROM_CMAKE
      "${ROOT_DIR}/../../.."
      ABSOLUTE
    )

    if(EXISTS "${_ROOT_PREFIX_FROM_CMAKE}/bin/root-config")

      set(
        C4ROOT_ROOT_CONFIG_EXECUTABLE
        "${_ROOT_PREFIX_FROM_CMAKE}/bin/root-config"
      )

    endif()

  endif()


  # Older ROOT/FairRoot setups may already provide ROOT_CONFIG_EXECUTABLE.
  if(NOT C4ROOT_ROOT_CONFIG_EXECUTABLE
     AND ROOT_CONFIG_EXECUTABLE
     AND EXISTS "${ROOT_CONFIG_EXECUTABLE}")

    set(
      C4ROOT_ROOT_CONFIG_EXECUTABLE
      "${ROOT_CONFIG_EXECUTABLE}"
    )

  endif()


  # Final compatibility fallback.
  #
  # This is intentionally last: PATH should only be consulted when the ROOT
  # CMake package itself did not tell us where ROOT lives.
  if(NOT C4ROOT_ROOT_CONFIG_EXECUTABLE)

    find_program(
      C4ROOT_ROOT_CONFIG_EXECUTABLE
      NAMES root-config
    )

  endif()


  if(C4ROOT_ROOT_CONFIG_EXECUTABLE)

    execute_process(
      COMMAND "${C4ROOT_ROOT_CONFIG_EXECUTABLE}" --prefix
      OUTPUT_VARIABLE ROOTSYS
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
      COMMAND "${C4ROOT_ROOT_CONFIG_EXECUTABLE}" --bindir
      OUTPUT_VARIABLE ROOT_BINDIR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
      COMMAND "${C4ROOT_ROOT_CONFIG_EXECUTABLE}" --libdir
      OUTPUT_VARIABLE ROOT_LIBRARY_DIR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
      COMMAND "${C4ROOT_ROOT_CONFIG_EXECUTABLE}" --incdir
      OUTPUT_VARIABLE ROOT_INCLUDE_DIR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    message(
      STATUS
      "ROOT environment configuration taken from: "
      "${C4ROOT_ROOT_CONFIG_EXECUTABLE}"
    )

  else()

    message(WARNING
      "Could not locate root-config for the ROOT installation selected by CMake. "
      "Existing ROOT CMake variables will be used instead."
    )

  endif()


  # Retain ROOT_LIBRARIES for compatibility with existing c4Root scripts.
  convert_list_to_string(${ROOT_LIBRARIES})
  set(ROOT_LIBRARIES "${output}")


  # ---------------------------------------------------------------------------
  # Runtime library path
  # ---------------------------------------------------------------------------

  if(ROOT_LIBRARY_DIR)
    list(APPEND _LD_LIBRARY_PATH "${ROOT_LIBRARY_DIR}")
  endif()

  if(FAIRROOTPATH)
    list(APPEND _LD_LIBRARY_PATH "${FAIRROOTPATH}/lib")
  endif()

  if(ucesb_FOUND AND ucesb_LIBRARY_DIR)
    list(APPEND _LD_LIBRARY_PATH "${ucesb_LIBRARY_DIR}")
  endif()

  list(REMOVE_DUPLICATES _LD_LIBRARY_PATH)

  convert_list_to_string(${_LD_LIBRARY_PATH})

  if(CMAKE_SYSTEM_NAME MATCHES "Linux")

    set(MY_LD_LIBRARY_PATH "${output}")

    set(DYLD_REPLACE "")
    set(DYLD_PREPEND "")
    set(DYLD_APPEND "")

  elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")

    set(MY_DYLD_LIBRARY_PATH "${output}")

    set(
      DYLD_REPLACE
      "export DYLD_LIBRARY_PATH=\"${MY_DYLD_LIBRARY_PATH}\""
    )

    set(
      DYLD_PREPEND
      "export DYLD_LIBRARY_PATH=\"${MY_DYLD_LIBRARY_PATH}\":$DYLD_LIBRARY_PATH"
    )

    set(
      DYLD_APPEND
      "export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:\"${MY_DYLD_LIBRARY_PATH}\""
    )

  endif()

  if(CMAKE_SYSTEM_NAME MATCHES "Linux")

    set(DYLD_REPLACE_CSH "")
    set(DYLD_PREPEND_CSH "")
    set(DYLD_APPEND_CSH "")

  elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")

    set(
      DYLD_REPLACE_CSH
      "setenv DYLD_LIBRARY_PATH \"${MY_DYLD_LIBRARY_PATH}\""
    )

    set(
      DYLD_PREPEND_CSH
      "setenv DYLD_LIBRARY_PATH \"${MY_DYLD_LIBRARY_PATH}\":$DYLD_LIBRARY_PATH"
    )

    set(
      DYLD_APPEND_CSH
      "setenv DYLD_LIBRARY_PATH $DYLD_LIBRARY_PATH:\"${MY_DYLD_LIBRARY_PATH}\""
    )

  endif()


  # ---------------------------------------------------------------------------
  # Python path
  #
  # Only add c4Root's own Python directory. The user's existing PYTHONPATH is
  # handled by the generated shell script when it is sourced.
  # ---------------------------------------------------------------------------

  set(_C4_PYTHONPATH)

  if(EXISTS "${CMAKE_SOURCE_DIR}/python")
    list(APPEND _C4_PYTHONPATH "${CMAKE_SOURCE_DIR}/python")
  endif()

  list(REMOVE_DUPLICATES _C4_PYTHONPATH)

  convert_list_to_string(${_C4_PYTHONPATH})
  set(MY_PYTHONPATH "${output}")

  if(MY_PYTHONPATH)

    set(
      PYTHONPATH_EXPORT
      "export PYTHONPATH=\"${MY_PYTHONPATH}\":$PYTHONPATH"
    )

  else()

    set(PYTHONPATH_EXPORT "")

  endif()

  if(MY_PYTHONPATH)

    set(
      PYTHONPATH_EXPORT_CSH
      "setenv PYTHONPATH \"${MY_PYTHONPATH}\":$PYTHONPATH"
    )

  else()

    set(PYTHONPATH_EXPORT_CSH "")

  endif()

  # ---------------------------------------------------------------------------
  # Executable path
  #
  # Do NOT copy the user's entire current PATH into config.sh. Only record the
  # directories provided by c4Root and its direct runtime dependencies.
  # ---------------------------------------------------------------------------

  set(_C4_PATH)

  if(_BINDIR)
    list(APPEND _C4_PATH "${_BINDIR}")
  endif()

  if(ROOT_BINDIR)
    list(APPEND _C4_PATH "${ROOT_BINDIR}")
  elseif(ROOTSYS)
    list(APPEND _C4_PATH "${ROOTSYS}/bin")
  endif()

  if(FAIRROOTPATH)
    list(APPEND _C4_PATH "${FAIRROOTPATH}/bin")
  endif()

  list(REMOVE_DUPLICATES _C4_PATH)

  convert_list_to_string(${_C4_PATH})
  set(MY_PATH "${output}")


  # ---------------------------------------------------------------------------
  # ROOT include path
  # ---------------------------------------------------------------------------

  set(_C4_ROOT_INCLUDE_PATH)

  if(ROOT_INCLUDE_DIR)
    list(APPEND _C4_ROOT_INCLUDE_PATH "${ROOT_INCLUDE_DIR}")
  endif()

  if(FAIRROOTPATH)
    list(APPEND _C4_ROOT_INCLUDE_PATH "${FAIRROOTPATH}/include")
  endif()

  list(REMOVE_DUPLICATES _C4_ROOT_INCLUDE_PATH)

  convert_list_to_string(${_C4_ROOT_INCLUDE_PATH})
  set(ROOT_INCLUDE_PATH "${output}")


  # ---------------------------------------------------------------------------
  # Generate shell configuration
  # ---------------------------------------------------------------------------

  if("${filename}" MATCHES "[.]csh.*$")

    if(C4ROOTPATH)

      configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/scripts/config.csh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
      )

    else()

      configure_file(
        "${FAIRROOTPATH}/share/fairbase/cmake/scripts/config.csh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
      )

    endif()

  else()

    if(C4ROOTPATH)

      configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/scripts/config.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
      )

    else()

      configure_file(
        "${FAIRROOTPATH}/share/fairbase/cmake/scripts/config.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
      )

    endif()

  endif()

ENDMACRO()


# ==============================================================================
# Convert a CMake list into a colon-separated shell path
# ==============================================================================

MACRO(CONVERT_LIST_TO_STRING)

  set(tmp "")

  foreach(_current ${ARGN})

    if(NOT "${_current}" STREQUAL "")

      if("${tmp}" STREQUAL "")
        set(tmp "${_current}")
      else()
        set(tmp "${tmp}:${_current}")
      endif()

    endif()

  endforeach()

  set(output "${tmp}")

ENDMACRO()