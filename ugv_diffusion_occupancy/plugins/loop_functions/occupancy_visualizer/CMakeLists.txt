set(HEADERS
  occupancy_visualizer.h)

set(SOURCES
  occupancy_visualizer.cpp)

add_library(occupancy_visualizer SHARED ${HEADERS} ${SOURCES})

target_link_libraries(occupancy_visualizer
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_qtopengl
  ${ARGOS_QTOPENGL_LIBRARIES}
  occupancy_medium)

install(TARGETS occupancy_visualizer DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES ${HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")