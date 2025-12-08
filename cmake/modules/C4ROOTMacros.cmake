#based on FairRoot's cmake/modules/ROOTMacros.cmake
INCLUDE(ROOTMacros)
MACRO (GENERATE_ROOTPLUS_TEST_SCRIPT SCRIPT_FULL_NAME)
  get_filename_component(path_name ${SCRIPT_FULL_NAME} PATH)
  get_filename_component(file_extension ${SCRIPT_FULL_NAME} EXT)
  get_filename_component(file_name ${SCRIPT_FULL_NAME} NAME_WE)
  set(shell_script_name "${file_name}.sh")

  string(REPLACE ${PROJECT_SOURCE_DIR}
         ${PROJECT_BINARY_DIR} new_path ${path_name}
        )

  file(MAKE_DIRECTORY ${new_path}/data)

  CONVERT_LIST_TO_STRING(${LD_LIBRARY_PATH})
  set(MY_LD_LIBRARY_PATH ${output})

  CONVERT_LIST_TO_STRING(${ROOT_INCLUDE_PATH})
  set(MY_ROOT_INCLUDE_PATH ${output})

  set(my_script_name ${SCRIPT_FULL_NAME})

  Write_Geant4Data_Variables_sh()
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/rootplus_macro.sh.in
                   ${new_path}/${shell_script_name}
                  )
  execute_process(COMMAND /bin/chmod u+x ${new_path}/${shell_script_name} OUTPUT_QUIET)


ENDMACRO (GENERATE_ROOTPLUS_TEST_SCRIPT)
