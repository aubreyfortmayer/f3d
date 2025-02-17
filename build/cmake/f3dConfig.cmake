# When this file is run by CMake through the find_package command
#
# The following variables will be defined:
#
#   f3d_BINDINGS_JAVA              Will be enabled if F3D was built with java bindings
#   f3d_BINDINGS_PYTHON            Will be enabled if F3D was built with python bindings
#   f3d_BUILD_APPLICATION          Will be enabled if F3D application was built
#   f3d_CONFIG_DIR                 Path to F3D configuration directory, can be absolute or relative
#   f3d_MODULE_EXR                 Will be enabled if F3D was built with OpenEXR images support
#   f3d_MODULE_RAYTRACING          Will be enabled if F3D was built with raytracing support
#   f3d_MODULE_UI                  Will be enabled if F3D was built with ImGui support
#   f3d_PLUGINS_INSTALL_DIR        Path to the location to install plugins so that F3D can find them
#   f3d_PREFIX_DIR                 Absolute path to the directory where F3D was installed
#
# It is also possible to look for optional components.
#
# Optional components are:
#
# `application`: If found, it the following target will exist
#
#   f3d::f3d           Target that contains the F3D executable
#
# `library`: If found, it the following target will exist
#
#   f3d::libf3d        Target that contains the libf3d
#
# And the following local variable will also be defined
#
#   f3d_INCLUDE_DIR                Absolute path to the include directory of public f3d library classes
#
# `pluginsdk`: If found many plugin related cmake macros will be available as well as the following target:
#
#   f3d::vtkext
#
# And the following local variable will also be defined
#
#   f3d_INCLUDE_DIR                Absolute path to the include directory of classes needed to build a plugin
#
# Please note, if no components are set, `library` will be added by default


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was f3dConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

get_filename_component(f3d_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

include(${CMAKE_CURRENT_LIST_DIR}/f3dConfigVersion.cmake)
message(STATUS "Found f3d ${PACKAGE_VERSION}")

set(f3d_BUILD_APPLICATION "ON")
set(f3d_MODULE_RAYTRACING "OFF")
set(f3d_MODULE_EXR "OFF")
set(f3d_MODULE_UI "ON")
set(f3d_BINDINGS_PYTHON "OFF")
set(f3d_BINDINGS_JAVA "OFF")
set(f3d_CONFIG_DIR "f3d.app/Contents/Resources/configs")
set(f3d_PLUGINS_INSTALL_DIR "lib")

# If no components specified, look for `library` component
if(NOT f3d_FIND_COMPONENTS)
  set(f3d_FIND_COMPONENTS library)
  set(f3d_FIND_REQUIRED_library TRUE)
endif()

foreach(component ${f3d_FIND_COMPONENTS})
  # For requested component, execute its "config" script
  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${component}-config.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/${component}-config.cmake)
  else()
    if (${f3d_FIND_REQUIRED_${component}})
      message(FATAL_ERROR "${component} was requested but could not be found, "
        "${CMAKE_CURRENT_LIST_DIR}/${component}-config.cmake is missing, "
        "please check component was installed")
    endif ()
  endif()
endforeach()

check_required_components(f3d)
