# Copyright: (C) 2013 Universidad Carlos III de Madrid
# Author: Juan G. Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

yarp_prepare_plugin(PlaybackThread CATEGORY device TYPE teo::PlaybackThread INCLUDE PlaybackThread.hpp)

if(NOT SKIP_PlaybackThread)

  find_package(COLOR_DEBUG REQUIRED)

  include_directories(${COLOR_DEBUG_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

  yarp_add_plugin(PlaybackThread DeviceDriverImpl.cpp IPlaybackThreadImpl.cpp ThreadImpl.cpp PlaybackThread.hpp)

  target_link_libraries(PlaybackThread ${YARP_LIBRARIES} Playback)

  yarp_install(TARGETS PlaybackThread
               EXPORT ROBOTICSLAB_TOOLS
               COMPONENT runtime
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

  yarp_install(FILES PlaybackThread.ini
               COMPONENT runtime
               DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()

