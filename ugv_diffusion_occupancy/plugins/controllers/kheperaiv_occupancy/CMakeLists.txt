add_library(kheperaiv_occupancy MODULE kheperaiv_occupancy_controller.h kheperaiv_occupancy_controller.cpp)
target_link_libraries(kheperaiv_occupancy
  argos3core_simulator
  argos3plugin_simulator_epuck
  argos3plugin_simulator_genericrobot)

#what is this garbage? I honestly don't really know where these things are supposed to go :P
#install(TARGETS kheperaiv_occupancy DESTINATION ${CMAKE_BINARY_DIR}/lib)
#install(TARGETS kheperaiv_occupancy DESTINATION /usr/local/lib/argos3)

install(TARGETS kheperaiv_occupancy DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES kheperaiv_occupancy_controller.h DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")