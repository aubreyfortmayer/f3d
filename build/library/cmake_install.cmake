# Install script for directory: /Users/aubreyfortmayer/f3d/library

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES
    "/Users/aubreyfortmayer/f3d/build/cmake/f3dConfig.cmake"
    "/Users/aubreyfortmayer/f3d/build/cmake/f3dConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/aubreyfortmayer/f3d/build/lib/libf3d.3.0.dylib"
    "/Users/aubreyfortmayer/f3d/build/lib/libf3d.3.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libf3d.3.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libf3d.3.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /Users/aubreyfortmayer/anaconda3/bin/install_name_tool
        -delete_rpath "/opt/homebrew/lib"
        -delete_rpath "/Users/aubreyfortmayer/f3d/build/lib"
        -add_rpath "@loader_path"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/aubreyfortmayer/f3d/build/lib/libf3d.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dependencies")
  file(GET_RUNTIME_DEPENDENCIES
    RESOLVED_DEPENDENCIES_VAR _CMAKE_DEPS
    LIBRARIES
      "/Users/aubreyfortmayer/f3d/build/lib/libf3d.dylib"
    PRE_EXCLUDE_REGEXES
      "api-ms-"
      "ext-ms-"
    POST_EXCLUDE_REGEXES
      ".*system32/.*"
      "^/usr/lib.*"
      "^/lib.*"
      "^/var/lib.*"
    POST_EXCLUDE_FILES_STRICT
      "/Users/aubreyfortmayer/f3d/build/lib/libvtkext.dylib"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dependencies")
  foreach(_CMAKE_TMP_dep IN LISTS _CMAKE_DEPS)
    if(NOT _CMAKE_TMP_dep MATCHES "\\.framework/")
      file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES ${_CMAKE_TMP_dep}
        FOLLOW_SYMLINK_CHAIN)
      get_filename_component(_CMAKE_TMP_dep_name "${_CMAKE_TMP_dep}" NAME)
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dependencies")
  foreach(_CMAKE_TMP_dep IN LISTS _CMAKE_DEPS)
    if(_CMAKE_TMP_dep MATCHES "^(.*/)?([^/]*\\.framework)/(.*)$")
      set(_CMAKE_TMP_dir "${CMAKE_MATCH_1}")
      set(_CMAKE_TMP_name "${CMAKE_MATCH_2}")
      set(_CMAKE_TMP_file "${CMAKE_MATCH_3}")
      set(_CMAKE_TMP_path "${_CMAKE_TMP_dir}${_CMAKE_TMP_name}")
      file(INSTALL DESTINATION "" TYPE DIRECTORY FILES ${_CMAKE_TMP_path}
        USE_SOURCE_PERMISSIONS)
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/f3d" TYPE FILE FILES
    "/Users/aubreyfortmayer/f3d/build/library/public/export.h"
    "/Users/aubreyfortmayer/f3d/build/library/public/options.h"
    "/Users/aubreyfortmayer/f3d/library/plugin/plugin.h"
    "/Users/aubreyfortmayer/f3d/library/plugin/reader.h"
    "/Users/aubreyfortmayer/f3d/library/public/camera.h"
    "/Users/aubreyfortmayer/f3d/library/public/context.h"
    "/Users/aubreyfortmayer/f3d/library/public/engine.h"
    "/Users/aubreyfortmayer/f3d/library/public/exception.h"
    "/Users/aubreyfortmayer/f3d/library/public/image.h"
    "/Users/aubreyfortmayer/f3d/library/public/interactor.h"
    "/Users/aubreyfortmayer/f3d/library/public/log.h"
    "/Users/aubreyfortmayer/f3d/library/public/scene.h"
    "/Users/aubreyfortmayer/f3d/library/public/types.h"
    "/Users/aubreyfortmayer/f3d/library/public/utils.h"
    "/Users/aubreyfortmayer/f3d/library/public/window.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "sdk")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dLibraryTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dLibraryTargets.cmake"
         "/Users/aubreyfortmayer/f3d/build/library/CMakeFiles/Export/b837c8e1dffe8e5616e49eed5af44cb9/f3dLibraryTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dLibraryTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dLibraryTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES "/Users/aubreyfortmayer/f3d/build/library/CMakeFiles/Export/b837c8e1dffe8e5616e49eed5af44cb9/f3dLibraryTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES "/Users/aubreyfortmayer/f3d/build/library/CMakeFiles/Export/b837c8e1dffe8e5616e49eed5af44cb9/f3dLibraryTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES
    "/Users/aubreyfortmayer/f3d/cmake/library-config.cmake"
    "/Users/aubreyfortmayer/f3d/cmake/f3dEmbed.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "plugin_sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/f3d" TYPE FILE FILES
    "/Users/aubreyfortmayer/f3d/library/plugin/reader.h"
    "/Users/aubreyfortmayer/f3d/library/plugin/plugin.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "plugin_sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES
    "/Users/aubreyfortmayer/f3d/cmake/pluginsdk-config.cmake"
    "/Users/aubreyfortmayer/f3d/cmake/f3dPlugin.cmake"
    "/Users/aubreyfortmayer/f3d/cmake/plugin.cxx.in"
    "/Users/aubreyfortmayer/f3d/cmake/plugin.desktop.in"
    "/Users/aubreyfortmayer/f3d/cmake/plugin.thumbnailer.in"
    "/Users/aubreyfortmayer/f3d/cmake/readerBoilerPlate.h.in"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/aubreyfortmayer/f3d/build/library/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
