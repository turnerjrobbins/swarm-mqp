add_library(footbot_diffusion_cp SHARED footbot_diffusion.h footbot_diffusion.cpp)

#install(TARGETS file_name DESTINATION ${CMAKE_BINARY_DIR}/dest_file_directory)
#destination file is relative to cmake binary directory
target_link_libraries(footbot_diffusion_cp
  argos3core_simulator
  argos3plugin_simulator_footbot
  argos3plugin_simulator_genericrobot)