#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "llframe_memory" for configuration "Debug"
set_property(TARGET llframe_memory APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(llframe_memory PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/llframe_memory_d.lib"
  )

list(APPEND _cmake_import_check_targets llframe_memory )
list(APPEND _cmake_import_check_files_for_llframe_memory "${_IMPORT_PREFIX}/lib/llframe_memory_d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
