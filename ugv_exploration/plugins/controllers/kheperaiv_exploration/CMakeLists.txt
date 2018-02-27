include_directories(${PROJECT_SOURCE_DIR}/plugins/loop_functions/octomap_manager/)
set(HEADERS ${PROJECT_SOURCE_DIR}/plugins/loop_functions/octomap_manager/octomap_manager.h)
set(SOURCES kheperaiv_exploration_controller.h kheperaiv_exploration_controller.cpp)

add_library(kheperaiv_exploration SHARED ${SOURCES} ${HEADERS})


target_link_libraries(kheperaiv_exploration
  argos3core_simulator
  argos3plugin_simulator_epuck
  argos3plugin_simulator_genericrobot
  argos3plugin_simulator_kheperaiv.so
  liboctomap.so
  liboctomath.so
  liboctovis.so)

install(TARGETS kheperaiv_exploration DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES kheperaiv_occupancy_controller.h DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")