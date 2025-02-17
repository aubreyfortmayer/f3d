# Install script for directory: /Users/aubreyfortmayer/f3d/vtkext/public/module

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "plugin_sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/f3d" TYPE FILE FILES
    "/Users/aubreyfortmayer/f3d/vtkext/public/module/vtkF3DFaceVaryingPointDispatcher.h"
    "/Users/aubreyfortmayer/f3d/vtkext/public/module/vtkF3DGLTFImporter.h"
    "/Users/aubreyfortmayer/f3d/vtkext/public/module/vtkF3DImporter.h"
    "/Users/aubreyfortmayer/f3d/vtkext/public/module/vtkF3DBitonicSort.h"
    "/Users/aubreyfortmayer/f3d/build/vtkext/public/module/vtkextModule.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "plugin_sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/vtk/hierarchy/f3d_vtkext" TYPE FILE RENAME "vtkext-hierarchy.txt" FILES "/Users/aubreyfortmayer/f3d/build/lib/vtk/hierarchy/f3d_vtkext/vtkext-hierarchy.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/aubreyfortmayer/f3d/build/lib/libvtkext.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkext.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkext.dylib")
    execute_process(COMMAND /Users/aubreyfortmayer/anaconda3/bin/install_name_tool
      -delete_rpath "/opt/homebrew/lib"
      -add_rpath "@loader_path"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkext.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkext.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "plugin_sdk" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/aubreyfortmayer/f3d/build/vtkext/public/module/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
