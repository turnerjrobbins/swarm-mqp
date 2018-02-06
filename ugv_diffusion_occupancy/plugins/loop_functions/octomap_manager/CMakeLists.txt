set(HEADERS
  octomap_manager.h)

set(SOURCES
  octomap_manager.cpp)

add_library(octomap_manager SHARED ${HEADERS} ${SOURCES})

target_link_libraries(octomap_manager
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_kheperaiv
  kheperaiv_occupancy
  argos3plugin_simulator_qtopengl
  ${ARGOS_QTOPENGL_LIBRARIES}
  occupancy_medium
  )

install(TARGETS octomap_manager DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES ${HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")