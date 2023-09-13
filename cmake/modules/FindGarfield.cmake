message(STATUS "Looking for Garfield++...")

find_path(GARFIELD_INCLUDE_DIR NAMES Sensor.hh
  PATHS $ENV{GARFIELD_HOME}/Include
  NO_DEFAULT_PATH
  DOC   "Path to Garfield include header files."
)

find_path(GARFIELD_LIBRARY_DIR NAMES libGarfield${CMAKE_SHARED_LIBRARY_SUFFIX}
  PATHS $ENV{GARFIELD_HOME}/install/lib
  NO_DEFAULT_PATH
  DOC   "Path to Garfield library files."
)

if(GARFIELD_INCLUDE_DIR
   AND GARFIELD_LIBRARY_DIR
)
  set(GARFIELD_FOUND true)
else(GARFIELD_INCLUDE_DIR
     AND GARFIELD_LIBRARY_DIR
)
  set(GARFIELD_FOUND false)
endif(GARFIELD_INCLUDE_DIR
      AND GARFIELD_LIBRARY_DIR
)

message("    - ${Cyan}GARFIELD_INCLUDE_DIR${CR} = ${BGreen}${GARFIELD_INCLUDE_DIR}${CR}")
message("    - ${Cyan}GARFIELD_LIBRARY_DIR${CR} = ${BGreen}${GARFIELD_LIBRARY_DIR}${CR}")

if(GARFIELD_FOUND)
  message(STATUS "${BGreen}Garfield++ was FOUND${CR}")
else(GARFIELD_FOUND)
  message(STATUS "${BYellow}Could not find package Garfield++${CR}")
endif(GARFIELD_FOUND)

