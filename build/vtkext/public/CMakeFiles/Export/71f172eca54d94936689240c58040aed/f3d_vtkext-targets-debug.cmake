#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "f3d::vtkext" for configuration "Debug"
set_property(TARGET f3d::vtkext APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(f3d::vtkext PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "VTK::CommonCore;VTK::RenderingOpenGL2"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkext.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libvtkext.dylib"
  )

list(APPEND _cmake_import_check_targets f3d::vtkext )
list(APPEND _cmake_import_check_files_for_f3d::vtkext "${_IMPORT_PREFIX}/lib/libvtkext.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
