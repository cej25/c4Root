include(CMakePackageConfigHelpers)

# Configure/Install CMake package
function(install_cmake_package)
  # Correct spelling, in local scope
  #set(PROJECT_NAME R3BRoot)
  set(PROJECT_NAME c4Root)

  set(PACKAGE_INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})
  if(PROJECT_EXPORT_SET)
    install(EXPORT ${PROJECT_EXPORT_SET}
      NAMESPACE ${PROJECT_NAME}::
      DESTINATION ${PACKAGE_INSTALL_DESTINATION}
      EXPORT_LINK_INTERFACE_LIBRARIES)
  endif()
  configure_package_config_file(
    "cmake/private/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${PACKAGE_INSTALL_DESTINATION}"
    PATH_VARS
      CMAKE_INSTALL_PREFIX
      CMAKE_INSTALL_FULL_BINDIR
      PACKAGE_INSTALL_DESTINATION)
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion)
  install(
    FILES
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${PACKAGE_INSTALL_DESTINATION}")
endfunction()
