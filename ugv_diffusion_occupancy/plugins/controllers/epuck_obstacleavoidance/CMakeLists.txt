add_library(epuck_obstacleavoidance SHARED epuck_obstacleavoidance.h epuck_obstacleavoidance.cpp)
target_link_libraries(epuck_obstacleavoidance
  argos3core_simulator
  argos3plugin_simulator_epuck
  argos3plugin_simulator_genericrobot)

#what is this garbage? I honestly don't really know where these things are supposed to go :P
#install(TARGETS epuck_obstacleavoidance DESTINATION ${CMAKE_BINARY_DIR}/lib)
#install(TARGETS epuck_obstacleavoidance DESTINATION /usr/local/lib/argos3)

install(TARGETS epuck_obstacleavoidance DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES epuck_obstacleavoidance.h DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")