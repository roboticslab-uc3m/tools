# Copyright: (C) 2013 Universidad Carlos III de Madrid
# Author: Juan G. Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.6)

YARP_PREPARE_PLUGIN(PlaybackThread CATEGORY device TYPE teo::PlaybackThread INCLUDE PlaybackThread.hpp)

IF (NOT SKIP_PlaybackThread)

  find_package(YARP REQUIRED)
  find_package(COLOR_DEBUG REQUIRED)

  # Include any directories needed for YARP
  include_directories(${YARP_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS} ${COLOR_DEBUG_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

  yarp_add_plugin(PlaybackThread DeviceDriverImpl.cpp IPlaybackThreadImpl.cpp ThreadImpl.cpp )

  TARGET_LINK_LIBRARIES(PlaybackThread ${YARP_LIBRARIES} Playback)
  install(TARGETS PlaybackThread DESTINATION lib)

  # Exporting dependencies for ROBOTICSLAB_TOOLSConfig.cmake quite manually for now... 
  set(ROBOTICSLAB_TOOLS_INCLUDE_DIRS ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "appended headers")
  #set(ROBOTICSLAB_TOOLS_LIBRARIES ${ROBOTICSLAB_TOOLS_LIBRARIES} LacqueyFetch CACHE INTERNAL "appended libraries")

  #install(TARGETS PlaybackThread DESTINATION lib)
  yarp_install(TARGETS PlaybackThread
             EXPORT YARP
             COMPONENT runtime
             LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
             ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

  yarp_install(FILES PlaybackThread.ini
              COMPONENT runtime
              DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

ENDIF (NOT SKIP_PlaybackThread)

