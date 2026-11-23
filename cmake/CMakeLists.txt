include(GNUInstallDirs)

install(DIRECTORY
  modules
  scripts
  DESTINATION "${CMAKE_INSTALL_DATADIR}/c4Root/cmake"
)
