
 Find_Package(Git)

 If(GIT_FOUND AND EXISTS "${SOURCE_DIR}/.git")
   Execute_Process(COMMAND ${GIT_EXECUTABLE} describe
		               OUTPUT_VARIABLE C4ROOT_GIT_VERSION
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                   WORKING_DIRECTORY ${SOURCE_DIR}
                  )
   Execute_Process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd
                   OUTPUT_VARIABLE C4ROOT_GIT_DATE
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                   WORKING_DIRECTORY ${SOURCE_DIR}
                  )
   Message(STATUS "c4Root Version - ${C4ROOT_GIT_VERSION} from - ${C4ROOT_GIT_DATE}")
   Configure_File(${SOURCE_DIR}/cmake/scripts/c4RootVersion.h.tmp ${BINARY_DIR}/c4RootVersion.h @ONLY)
  
 Else()
   Configure_File(${SOURCE_DIR}/cmake/scripts/c4RootVersion.h.default ${BINARY_DIR}/c4RootVersion.h COPYONLY)
 EndIf()

