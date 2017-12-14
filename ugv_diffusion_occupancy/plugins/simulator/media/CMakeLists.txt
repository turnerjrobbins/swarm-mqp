set(HEADERS
  occupancy_medium.h)

set(SOURCES
  occupancy_medium.cpp)

add_library(occupancy_medium SHARED ${HEADERS} ${SOURCES})

target_link_libraries(occupancy_medium
  argos3core_simulator)

install(TARGETS occupancy_medium DESTINATION ${CMAKE_BINARY_DIR}/lib)

FILE(RELATIVE_PATH relative_dir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES ${HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/include/${relative_dir}")