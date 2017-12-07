add_library(epuck_obstacleavoidance MODULE epuck_obstacleavoidance.h epuck_obstacleavoidance.cpp)
target_link_libraries(epuck_obstacleavoidance
  argos3core_simulator
  argos3plugin_simulator_epuck
  argos3plugin_simulator_genericrobot)
#install(TARGETS epuck_obstacleavoidance DESTINATION ${CMAKE_BINARY_DIR}/lib)
install(TARGETS epuck_obstacleavoidance DESTINATION /usr/local/lib/argos3)