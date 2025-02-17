#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "f3d::libf3d" for configuration "Debug"
set_property(TARGET f3d::libf3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(f3d::libf3d PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "VTK::CommonSystem;VTK::IOImage;VTK::InteractionWidgets;f3d::vtkext"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libf3d.3.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libf3d.3.dylib"
  )

list(APPEND _cmake_import_check_targets f3d::libf3d )
list(APPEND _cmake_import_check_files_for_f3d::libf3d "${_IMPORT_PREFIX}/lib/libf3d.3.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
