
set(HEADERS
	simulator/occupancy_default_actuator.h)

set(SOURCES
	control_interface/ci_occupancy_actuator.cpp
	simulator/occupancy_default_actuator.cpp)

include_directories(~/swarm-mqp/)

add_library(argos3plugin_simulator_generic_occupancy SHARED ${HEADERS} ${SOURCES})

target_link_libraries(argos3plugin_simulator_generic_occupancy
  argos3core_simulator
  occupancy_medium
  )

install(TARGETS argos3plugin_simulator_generic_occupancy DESTINATION ${CMAKE_BINARY_DIR}/lib)

#FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#install(FILES ${HEADERS_1} DESTINATION "include/${relative_dir}/control_interface")
#install(FILES ${HEADERS_2} DESTINATION "include/${relative_dir}/simulator")