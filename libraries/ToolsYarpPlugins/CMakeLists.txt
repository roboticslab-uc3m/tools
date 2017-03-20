# Copyright: (C) 2017 Universidad Carlos III de Madrid
# Authors: Juan G. Victores & Raul de Santos Rico
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.6)

#IF (ENABLE_ToolsYarpPlugins)

  # option(ENABLE_launchToolsYarpPlugins "Choose if you want to compile launchToolsYarpPlugins" TRUE)

  find_package(YARP REQUIRED)
  include_directories(${YARP_INCLUDE_DIRS})
  list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})  
  include(YarpPlugin)

  # Exporting dependencies for ROBOTICSLAB_TOOLSConfig.cmake quite manually for now... 
  # Note: Need ICanBusSharer.h, which will also need CanBusHico/*.hpp for now
  set(ROBOTICSLAB_TOOLS_INCLUDE_DIRS ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "appended headers")
  # Note: ToolsYarpPlugins bodybot works, but bodybot ToolsYarpPlugins fails.
  #set(ROBOTICSLAB_TOOLS_LIBRARIES ${ROBOTICSLAB_TOOLS_LIBRARIES} ToolsYarpPlugins CACHE INTERNAL "appended libraries") 
  
 #  yarp_begin_plugin_library(ToolsYarpPlugins)
    add_subdirectory(PlaybackThread)
  # yarp_end_plugin_library(ToolsYarpPlugins)

  #install(TARGETS ToolsYarpPlugins DESTINATION lib)

  #IF (ENABLE_launchToolsYarpPlugins)

  #  YARP_ADD_PLUGIN_YARPDEV_EXECUTABLE(launchToolsYarpPlugins ToolsYarpPlugins)
  #  install(TARGETS launchToolsYarpPlugins DESTINATION bin)

  #ENDIF (ENABLE_launchToolsYarpPlugins)

  # Exporting dependencies for ROBOTICSLAB_TOOLSConfig.cmake quite manually for now... 
  set(ROBOTICSLAB_TOOLS_INCLUDE_DIRS ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "appended libraries")

#ENDIF (ENABLE_ToolsYarpPlugins)

