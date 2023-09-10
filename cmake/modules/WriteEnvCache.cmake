
MACRO (WRITE_ENV_CACHE filename)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/env_cache.sh.in
	             ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                )
ENDMACRO (WRITE_ENV_CACHE)
