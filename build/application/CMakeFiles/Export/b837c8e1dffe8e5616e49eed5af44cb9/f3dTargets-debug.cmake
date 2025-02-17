#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "f3d::f3d" for configuration "Debug"
set_property(TARGET f3d::f3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(f3d::f3d PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./f3d.app/Contents/MacOS/f3d"
  )

list(APPEND _cmake_import_check_targets f3d::f3d )
list(APPEND _cmake_import_check_files_for_f3d::f3d "${_IMPORT_PREFIX}/./f3d.app/Contents/MacOS/f3d" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
