# Install script for directory: /home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/plugins/simulator/media

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so"
         RPATH "/usr/local/lib/argos3")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/argos3/liboccupancy_medium.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib/argos3" TYPE SHARED_LIBRARY FILES "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/plugins/simulator/media/liboccupancy_medium.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so"
         OLD_RPATH "/usr/local/lib/argos3:"
         NEW_RPATH "/usr/local/lib/argos3")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/argos3/liboccupancy_medium.so")
    endif()
  endif()
endif()

