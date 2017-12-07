cmake_minimum_required (VERSION 2.6)

project (diffusion_occupancy_grid)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# Deactivate RPATH for MacOSX
set(CMAKE_MACOSX_RPATH 0)

set(Lua52_DIR)
find_package(Lua52)
if(LUA52_FOUND)
  set(ARGOS_WITH_LUA ON)
  include_directories(${LUA_INCLUDE_DIR})
endif(LUA52_FOUND)

#
# Check for ARGoS3
#
# Find the ARGoS package, make sure to save the ARGoS prefix
find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_simulator)
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)
# Set ARGoS include dir
include_directories(${ARGOS_INCLUDE_DIRS})
# Set ARGoS link dir
link_directories(${ARGOS_LIBRARY_DIRS})

# Check whether all the necessary libs have been installed to compile the
# code that depends on Qt and OpenGL
include(ARGoSCheckQTOpenGL)

#
# Add repository directory to the list of includes
# This makes it possible to say #include <argos3/...> with
# repository includes.
#
include_directories(${CMAKE_SOURCE_DIR})

# add buzz to the module path
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/share/buzz/cmake)

# Look for Buzz tools, libraries, and headers
find_package(Buzz)
if(BUZZ_FOUND)
  # Define Buzz-related commands
  include(UseBuzz)
  include_directories(${BUZZ_C_INCLUDE_DIR})
endif(BUZZ_FOUND)

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(plugins/robots/generic/control_interface/)

add_subdirectory(plugins)

set(CMAKE_CXX_EXTENSIONS OFF)
