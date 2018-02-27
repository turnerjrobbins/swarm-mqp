# Install script for directory: /home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/plugins/controllers/kheperaiv_occupancy

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
  if(EXISTS "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so"
         RPATH "/usr/local/lib/argos3")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib" TYPE MODULE FILES "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/plugins/controllers/kheperaiv_occupancy/libkheperaiv_occupancy.so")
  if(EXISTS "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so"
         OLD_RPATH "/usr/local/lib/argos3:"
         NEW_RPATH "/usr/local/lib/argos3")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/lib/libkheperaiv_occupancy.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/include/plugins/controllers/kheperaiv_occupancy/kheperaiv_occupancy_controller.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/include/plugins/controllers/kheperaiv_occupancy" TYPE FILE FILES "/home/tjrobbins/swarm-mqp/ugv_diffusion_occupancy/plugins/controllers/kheperaiv_occupancy/kheperaiv_occupancy_controller.h")
endif()

