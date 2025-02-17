# Install script for directory: /Users/aubreyfortmayer/f3d/application

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "application" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/Users/aubreyfortmayer/f3d/build/bin/f3d.app" USE_SOURCE_PERMISSIONS)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./f3d.app/Contents/MacOS/f3d" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./f3d.app/Contents/MacOS/f3d")
    execute_process(COMMAND /Users/aubreyfortmayer/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/aubreyfortmayer/f3d/build/lib"
      -add_rpath "@loader_path/../../../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./f3d.app/Contents/MacOS/f3d")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "sdk")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dTargets.cmake"
         "/Users/aubreyfortmayer/f3d/build/application/CMakeFiles/Export/b837c8e1dffe8e5616e49eed5af44cb9/f3dTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d/f3dTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES "/Users/aubreyfortmayer/f3d/build/application/CMakeFiles/Export/b837c8e1dffe8e5616e49eed5af44cb9/f3dTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES "/Users/aubreyfortmayer/f3d/build/application/CMakeFiles/Export/b837c8e1dffe8e5616e49eed5af44cb9/f3dTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "sdk")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/f3d" TYPE FILE FILES "/Users/aubreyfortmayer/f3d/cmake/application-config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "configuration")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/f3d.app/Contents/Resources/configs" TYPE DIRECTORY FILES "/Users/aubreyfortmayer/f3d/resources/configs/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "colormaps")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/f3d.app/Contents/Resources/colormaps" TYPE DIRECTORY FILES "/Users/aubreyfortmayer/f3d/resources/colormaps/")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/aubreyfortmayer/f3d/build/application/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
