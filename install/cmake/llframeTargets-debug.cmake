#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "llframe" for configuration "Debug"
set_property(TARGET llframe APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(llframe PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/llframe_d.lib"
  )

list(APPEND _cmake_import_check_targets llframe )
list(APPEND _cmake_import_check_files_for_llframe "${_IMPORT_PREFIX}/lib/llframe_d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
