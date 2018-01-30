add_library(kheperaiv_occupancy SHARED kheperaiv_occupancy_controller.h kheperaiv_occupancy_controller.cpp)
target_link_libraries(kheperaiv_occupancy
  argos3core_simulator
  argos3plugin_simulator_epuck
  argos3plugin_simulator_genericrobot
  argos3plugin_simulator_kheperaiv.so
  argos3plugin_simulator_generic_occupancy
  liboctomap.so
  liboctomath.so
  liboctovis.so
  )

install(TARGETS kheperaiv_occupancy DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES kheperaiv_occupancy_controller.h DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")